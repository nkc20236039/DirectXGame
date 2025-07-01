#include <filesystem>
#include <fstream>
#include "Shader.h"
#include "../Utility.h"

using namespace Microsoft::WRL;
using csoPair = std::pair<std::unique_ptr<uint8_t[]>, int32_t>;	// cso用のペアを短縮

bool Shader::CreateStandardShader(const std::string& vertexShaderPath, const std::string& pixcelShaderPath, std::shared_ptr<ShaderResource>& outShaderResource) {
	// どちらかのファイルパスが無効の場合falseを返す
	if (!std::filesystem::exists(vertexShaderPath)
		|| !std::filesystem::exists(pixcelShaderPath)) {
		return false;
	}

	// 頂点シェーダーを作成
	createVertexShader(vertexShaderPath, *outShaderResource);
	// ピクセルシェーダーを作成
	createPixcelShader(pixcelShaderPath, *outShaderResource);

	// StandardShaderの保存パスを記録
	standardShaderPath = vertexShaderPath;
	standardShaderPath.append("-");
	standardShaderPath.append(pixcelShaderPath);

	// 管理権をマップに移す
	shaderResourceMap[standardShaderPath] = *outShaderResource;
	return true;
}

const ShaderResource& Shader::GetOrCreateShader(std::string vertexShaderPath = "", std::string pixcelShaderPath = "") {
	/* 保存キーのためにファイル名を結合する */
	// ファイルが存在しない場合はStandardに置き換える
	std::string vertexShaderName = (std::filesystem::exists(vertexShaderPath)) ? STANDARD_PATH_NAME : vertexShaderPath;
	std::string pixcelShaderName = (std::filesystem::exists(pixcelShaderPath)) ? STANDARD_PATH_NAME : pixcelShaderPath;
	// ファイル名を結合
	std::string shaderKey = vertexShaderName;
	shaderKey.append("-");	// 頂点シェーダーパスとピクセルシェーダーパスの分割用文字
	shaderKey.append(pixcelShaderName);

	// 既に同じ組み合わせのシェーダーが作成されていた場合
	if (shaderResourceMap.contains(shaderKey)) {
		// 存在するシェーダーリソースを返す
		return shaderResourceMap[shaderKey];
	}

	// StandardのShaderResourceをコピーする
	ShaderResource shaderResource = shaderResourceMap[standardShaderPath];

	/* 頂点シェーダーを作成 */
	// 頂点シェーダーが指定されている場合
	if (vertexShaderName != STANDARD_PATH_NAME) {
		// 頂点シェーダーを作成
		createVertexShader(vertexShaderPath, shaderResource);
	}
	/* ピクセルシェーダーを作成 */
	// ピクセルシェーダーが指定されている場合
	if (pixcelShaderName != STANDARD_PATH_NAME) {
		// ピクセルシェーダーを作成
		createPixcelShader(pixcelShaderPath, shaderResource);
	}

	// 管理権をマップに移す
	shaderResourceMap[shaderKey] = std::move(shaderResource);
	return shaderResourceMap[shaderKey];
}

void Shader::createVertexShader(const std::string& path, ShaderResource& shaderResource) {
	// 正常終了チェック
	HRESULT hr = S_OK;
	// ファイルの拡張子を取得
	size_t dotSplit = path.find_last_of('.');
	std::string extension = path.substr(dotSplit + 1);
	std::wstring vertexShader = convertWstringPath(path);

	// 読み込むファイルの拡張子がhlslの場合
	if (extension == "hlsl") {
		ComPtr<ID3DBlob> vertexShaderBlob = nullptr;

		// hlslをコンパイルする
		hr = compileShaderFromFile(
			vertexShader.c_str(),								// ファイルパス
			"main",								// エントリーポイントの名前
			"vs_5_0",							// シェーダーのバージョン
			vertexShaderBlob.GetAddressOf());	// 保存先
		// エラーチェック
		if (FAILED(hr)) { return; }

		// 頂点シェーダーの作成
		hr = system.get_device()->CreateVertexShader(
			vertexShaderBlob->GetBufferPointer(),
			vertexShaderBlob->GetBufferSize(),
			nullptr,
			shaderResource.vertexSahder.GetAddressOf());
		if (FAILED(hr)) { return; }

		// インプットレイアウトの作成
		hr = system.get_device().Get()->CreateInputLayout(
			vertexDesc,
			ARRAYSIZE(vertexDesc),
			vertexShaderBlob.Get()->GetBufferPointer(),
			vertexShaderBlob.Get()->GetBufferSize(),
			shaderResource.vertexLayout.GetAddressOf());

		vertexShaderBlob.Reset();
		if (FAILED(hr)) { return; }
	}
	else if (extension == "cso") {	// 読み込むファイルの拡張子がcsoの場合
		auto result = loadCSOFile(vertexShader.c_str());	// 戻り値の型が長いため省略
		auto& [csoBuffer, csoSize] = *result;
		// 頂点シェーダーの作成
		hr = system.get_device().Get()->CreateVertexShader(
			csoBuffer.get(),
			csoSize,
			nullptr,
			shaderResource.vertexSahder.GetAddressOf());

		if (FAILED(hr)) { return; }

		// インプットレイアウトの作成
		hr = system.get_device().Get()->CreateInputLayout(
			vertexDesc,
			ARRAYSIZE(vertexDesc),
			csoBuffer.get(),
			csoSize,
			shaderResource.vertexLayout.GetAddressOf());
		if (FAILED(hr)) { return; }
	}
}

void Shader::createPixcelShader(const std::string& path, ShaderResource& shaderResource) {
	HRESULT hr = S_OK;
	// ファイルの拡張子を取得
	size_t dotSplit = path.find_last_of('.');
	std::string extension = path.substr(dotSplit + 1);
	std::wstring pixcelShader = convertWstringPath(path);

	// 読み込むファイルの拡張子がhlslの場合
	if (extension == "hlsl") {
		ComPtr<ID3DBlob> pixcelShaderBlob = nullptr;

		hr = compileShaderFromFile(
			pixcelShader.c_str(),
			"main",
			"ps_5_0",
			pixcelShaderBlob.GetAddressOf());

		if (FAILED(hr)) { return; }

		// ピクセルシェーダーの作成
		hr = system.get_device().Get()->CreatePixelShader(
			pixcelShaderBlob.Get()->GetBufferPointer(),
			pixcelShaderBlob.Get()->GetBufferSize(),
			nullptr,
			shaderResource.pixelShader.GetAddressOf());

		pixcelShaderBlob.Reset();
		if (FAILED(hr)) { return; }
	}
	else if (extension == "cso") {	// 読み込むファイルの拡張子がcsoの場合
		std::optional<csoPair> result = loadCSOFile(pixcelShader.c_str());
		auto& [csoBuffer, csoSize] = *result;

		// ピクセルシェーダーの作成
		hr = system.get_device().Get()->CreatePixelShader(
			csoBuffer.get(),
			csoSize,
			nullptr,
			shaderResource.pixelShader.GetAddressOf());

		if (FAILED(hr)) { return; }
	}
}

HRESULT Shader::compileShaderFromFile(LPCWSTR fileName, LPCSTR entryPoint, LPCSTR shaderModel, ID3DBlob** blobOut) {
	HRESULT hr = S_OK;

	// コンパイラがHLSLコードをコンパイルする方法を指定
	DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;	// 厳密なコンパイルを強制
#ifdef _DEBUG
	shaderFlags |= D3DCOMPILE_DEBUG;	// デバッグファイル/行/型/シンボル情報をコンソールに出力する
	shaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;	// コード生成中に最適化ステップをスキップする
#endif
	// コンパイル後のバイナリデータを取得する
	ComPtr<ID3DBlob> errorBlob = nullptr;
	// ファイルからシェーダーをコンパイル
	hr = D3DCompileFromFile(
		fileName,
		nullptr,
		nullptr,
		entryPoint,
		shaderModel,
		shaderFlags,
		0,
		blobOut,
		errorBlob.GetAddressOf());

	// エラーチェック
	if (FAILED(hr)) {
		if (errorBlob.Get()) {
			// 文字列をデバッガに送信
			OutputDebugStringA(reinterpret_cast<const char*>(errorBlob.Get()->GetBufferPointer()));
			errorBlob.Reset();
		}
		return hr;
	}
	// 無事に終了
	errorBlob.Reset();
	return hr;
}

std::optional<csoPair> Shader::loadCSOFile(LPCWSTR fileName) {
	std::fstream binfile(fileName, std::ios::in | std::ios::binary);

	if (binfile.is_open()) {
		binfile.seekg(0, std::ios::end);
		int32_t csoSize = static_cast<int32_t>(binfile.tellg());
		binfile.seekg(0, std::ios::beg);

		std::unique_ptr<uint8_t[]> csoBuffer = std::make_unique<uint8_t[]>(csoSize);
		binfile.read(reinterpret_cast<char*>(csoBuffer.get()), csoSize);

		return std::make_pair(std::move(csoBuffer), csoSize);
	}

	return std::nullopt;
}