#include <filesystem>
#include <fstream>
#include "Shader.h"
#include "../Utility.h"

using namespace Microsoft::WRL;
using csoPair = std::pair<std::unique_ptr<uint8_t[]>, int32_t>;	// cso�p�̃y�A��Z�k

bool Shader::CreateStandardShader(const std::string& vertexShaderPath, const std::string& pixcelShaderPath, std::shared_ptr<ShaderResource>& outShaderResource) {
	// �ǂ��炩�̃t�@�C���p�X�������̏ꍇfalse��Ԃ�
	if (!std::filesystem::exists(vertexShaderPath)
		|| !std::filesystem::exists(pixcelShaderPath)) {
		return false;
	}

	// ���_�V�F�[�_�[���쐬
	createVertexShader(vertexShaderPath, *outShaderResource);
	// �s�N�Z���V�F�[�_�[���쐬
	createPixcelShader(pixcelShaderPath, *outShaderResource);

	// StandardShader�̕ۑ��p�X���L�^
	standardShaderPath = vertexShaderPath;
	standardShaderPath.append("-");
	standardShaderPath.append(pixcelShaderPath);

	// �Ǘ������}�b�v�Ɉڂ�
	shaderResourceMap[standardShaderPath] = *outShaderResource;
	return true;
}

const ShaderResource& Shader::GetOrCreateShader(std::string vertexShaderPath = "", std::string pixcelShaderPath = "") {
	/* �ۑ��L�[�̂��߂Ƀt�@�C�������������� */
	// �t�@�C�������݂��Ȃ��ꍇ��Standard�ɒu��������
	std::string vertexShaderName = (std::filesystem::exists(vertexShaderPath)) ? STANDARD_PATH_NAME : vertexShaderPath;
	std::string pixcelShaderName = (std::filesystem::exists(pixcelShaderPath)) ? STANDARD_PATH_NAME : pixcelShaderPath;
	// �t�@�C����������
	std::string shaderKey = vertexShaderName;
	shaderKey.append("-");	// ���_�V�F�[�_�[�p�X�ƃs�N�Z���V�F�[�_�[�p�X�̕����p����
	shaderKey.append(pixcelShaderName);

	// ���ɓ����g�ݍ��킹�̃V�F�[�_�[���쐬����Ă����ꍇ
	if (shaderResourceMap.contains(shaderKey)) {
		// ���݂���V�F�[�_�[���\�[�X��Ԃ�
		return shaderResourceMap[shaderKey];
	}

	// Standard��ShaderResource���R�s�[����
	ShaderResource shaderResource = shaderResourceMap[standardShaderPath];

	/* ���_�V�F�[�_�[���쐬 */
	// ���_�V�F�[�_�[���w�肳��Ă���ꍇ
	if (vertexShaderName != STANDARD_PATH_NAME) {
		// ���_�V�F�[�_�[���쐬
		createVertexShader(vertexShaderPath, shaderResource);
	}
	/* �s�N�Z���V�F�[�_�[���쐬 */
	// �s�N�Z���V�F�[�_�[���w�肳��Ă���ꍇ
	if (pixcelShaderName != STANDARD_PATH_NAME) {
		// �s�N�Z���V�F�[�_�[���쐬
		createPixcelShader(pixcelShaderPath, shaderResource);
	}

	// �Ǘ������}�b�v�Ɉڂ�
	shaderResourceMap[shaderKey] = std::move(shaderResource);
	return shaderResourceMap[shaderKey];
}

void Shader::createVertexShader(const std::string& path, ShaderResource& shaderResource) {
	// ����I���`�F�b�N
	HRESULT hr = S_OK;
	// �t�@�C���̊g���q���擾
	size_t dotSplit = path.find_last_of('.');
	std::string extension = path.substr(dotSplit + 1);
	std::wstring vertexShader = convertWstringPath(path);

	// �ǂݍ��ރt�@�C���̊g���q��hlsl�̏ꍇ
	if (extension == "hlsl") {
		ComPtr<ID3DBlob> vertexShaderBlob = nullptr;

		// hlsl���R���p�C������
		hr = compileShaderFromFile(
			vertexShader.c_str(),								// �t�@�C���p�X
			"main",								// �G���g���[�|�C���g�̖��O
			"vs_5_0",							// �V�F�[�_�[�̃o�[�W����
			vertexShaderBlob.GetAddressOf());	// �ۑ���
		// �G���[�`�F�b�N
		if (FAILED(hr)) { return; }

		// ���_�V�F�[�_�[�̍쐬
		hr = system.get_device()->CreateVertexShader(
			vertexShaderBlob->GetBufferPointer(),
			vertexShaderBlob->GetBufferSize(),
			nullptr,
			shaderResource.vertexSahder.GetAddressOf());
		if (FAILED(hr)) { return; }

		// �C���v�b�g���C�A�E�g�̍쐬
		hr = system.get_device().Get()->CreateInputLayout(
			vertexDesc,
			ARRAYSIZE(vertexDesc),
			vertexShaderBlob.Get()->GetBufferPointer(),
			vertexShaderBlob.Get()->GetBufferSize(),
			shaderResource.vertexLayout.GetAddressOf());

		vertexShaderBlob.Reset();
		if (FAILED(hr)) { return; }
	}
	else if (extension == "cso") {	// �ǂݍ��ރt�@�C���̊g���q��cso�̏ꍇ
		auto result = loadCSOFile(vertexShader.c_str());	// �߂�l�̌^���������ߏȗ�
		auto& [csoBuffer, csoSize] = *result;
		// ���_�V�F�[�_�[�̍쐬
		hr = system.get_device().Get()->CreateVertexShader(
			csoBuffer.get(),
			csoSize,
			nullptr,
			shaderResource.vertexSahder.GetAddressOf());

		if (FAILED(hr)) { return; }

		// �C���v�b�g���C�A�E�g�̍쐬
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
	// �t�@�C���̊g���q���擾
	size_t dotSplit = path.find_last_of('.');
	std::string extension = path.substr(dotSplit + 1);
	std::wstring pixcelShader = convertWstringPath(path);

	// �ǂݍ��ރt�@�C���̊g���q��hlsl�̏ꍇ
	if (extension == "hlsl") {
		ComPtr<ID3DBlob> pixcelShaderBlob = nullptr;

		hr = compileShaderFromFile(
			pixcelShader.c_str(),
			"main",
			"ps_5_0",
			pixcelShaderBlob.GetAddressOf());

		if (FAILED(hr)) { return; }

		// �s�N�Z���V�F�[�_�[�̍쐬
		hr = system.get_device().Get()->CreatePixelShader(
			pixcelShaderBlob.Get()->GetBufferPointer(),
			pixcelShaderBlob.Get()->GetBufferSize(),
			nullptr,
			shaderResource.pixelShader.GetAddressOf());

		pixcelShaderBlob.Reset();
		if (FAILED(hr)) { return; }
	}
	else if (extension == "cso") {	// �ǂݍ��ރt�@�C���̊g���q��cso�̏ꍇ
		std::optional<csoPair> result = loadCSOFile(pixcelShader.c_str());
		auto& [csoBuffer, csoSize] = *result;

		// �s�N�Z���V�F�[�_�[�̍쐬
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

	// �R���p�C����HLSL�R�[�h���R���p�C��������@���w��
	DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;	// �����ȃR���p�C��������
#ifdef _DEBUG
	shaderFlags |= D3DCOMPILE_DEBUG;	// �f�o�b�O�t�@�C��/�s/�^/�V���{�������R���\�[���ɏo�͂���
	shaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;	// �R�[�h�������ɍœK���X�e�b�v���X�L�b�v����
#endif
	// �R���p�C����̃o�C�i���f�[�^���擾����
	ComPtr<ID3DBlob> errorBlob = nullptr;
	// �t�@�C������V�F�[�_�[���R���p�C��
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

	// �G���[�`�F�b�N
	if (FAILED(hr)) {
		if (errorBlob.Get()) {
			// ��������f�o�b�K�ɑ��M
			OutputDebugStringA(reinterpret_cast<const char*>(errorBlob.Get()->GetBufferPointer()));
			errorBlob.Reset();
		}
		return hr;
	}
	// �����ɏI��
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