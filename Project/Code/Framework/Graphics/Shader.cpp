#include <filesystem>
#include <fstream>
#include "Shader.h"

using namespace Microsoft::WRL;
using csoPair = std::pair<std::unique_ptr<uint8_t[]>, int32_t>;	// cso�p�̃y�A��Z�k

bool Shader::CreateStandardShader(const std::string& vertexShaderPath, const std::string& pixcelShaderPath, std::shared_ptr<ShaderResource>& outShaderResource) {
	// �ǂ��炩�̃t�@�C���p�X�������̏ꍇfalse��Ԃ�
	if (!std::filesystem::exists(vertexShaderPath)
		|| !std::filesystem::exists(pixcelShaderPath)) {
		return false;
	}

	// ���_�V�F�[�_�[���쐬
	CreateVertexShader(vertexShaderPath, *outShaderResource);
	// �s�N�Z���V�F�[�_�[���쐬
	CreatePixcelShader(pixcelShaderPath, *outShaderResource);

	// StandardShader�̕ۑ��p�X���L�^
	_standardShaderPath = vertexShaderPath;
	_standardShaderPath.append("-");
	_standardShaderPath.append(pixcelShaderPath);

	// �Ǘ������}�b�v�Ɉڂ�
	_shaderResourceMap[_standardShaderPath] = *outShaderResource;
	return true;
}

const ShaderResource& Shader::GetOrCreateShader(std::string vertexShaderPath = NULLPATH, std::string pixcelShaderPath = NULLPATH) {
	/* �ۑ��L�[�̂��߂Ƀt�@�C�������������� */
	// �t�@�C�������݂��Ȃ��ꍇ��Standard�ɒu��������
	std::string vertexShaderName = (std::filesystem::exists(vertexShaderPath)) ? STANDARD_PATH_NAME : vertexShaderPath;
	std::string pixcelShaderName = (std::filesystem::exists(pixcelShaderPath)) ? STANDARD_PATH_NAME : pixcelShaderPath;
	// �t�@�C����������
	std::string shaderKey = vertexShaderName;
	shaderKey.append("-");	// ���_�V�F�[�_�[�p�X�ƃs�N�Z���V�F�[�_�[�p�X�̕����p����
	shaderKey.append(pixcelShaderName);

	// ���ɓ����g�ݍ��킹�̃V�F�[�_�[���쐬����Ă����ꍇ
	if (_shaderResourceMap.contains(shaderKey)) {
		// ���݂���V�F�[�_�[���\�[�X��Ԃ�
		return _shaderResourceMap[shaderKey];
	}

	// Standard��ShaderResource���R�s�[����
	ShaderResource shaderResource = _shaderResourceMap[_standardShaderPath];

	/* ���_�V�F�[�_�[���쐬 */
	// ���_�V�F�[�_�[���w�肳��Ă���ꍇ
	if (vertexShaderName != STANDARD_PATH_NAME) {
		// ���_�V�F�[�_�[���쐬
		CreateVertexShader(vertexShaderPath, shaderResource);
	}
	/* �s�N�Z���V�F�[�_�[���쐬 */
	// �s�N�Z���V�F�[�_�[���w�肳��Ă���ꍇ
	if (pixcelShaderName != STANDARD_PATH_NAME) {
		// �s�N�Z���V�F�[�_�[���쐬
		CreatePixcelShader(pixcelShaderPath, shaderResource);
	}

	// �Ǘ������}�b�v�Ɉڂ�
	_shaderResourceMap[shaderKey] = std::move(shaderResource);
	return _shaderResourceMap[shaderKey];
}

void Shader::CreateVertexShader(const std::string& path, ShaderResource& shaderResource) {
	// ����I���`�F�b�N
	HRESULT hr = S_OK;
	// �t�@�C���̊g���q���擾
	size_t dotSplit = path.find_last_of('.');
	std::string extension = path.substr(dotSplit + 1);
	std::wstring vertexShader = ConvertWstring(path);

	// �ǂݍ��ރt�@�C���̊g���q��hlsl�̏ꍇ
	if (extension == "hlsl") {
		ComPtr<ID3DBlob> vertexShaderBlob = nullptr;

		// hlsl���R���p�C������
		hr = CompileShaderFromFile(
			vertexShader.c_str(),								// �t�@�C���p�X
			"main",								// �G���g���[�|�C���g�̖��O
			"vs_5_0",							// �V�F�[�_�[�̃o�[�W����
			vertexShaderBlob.GetAddressOf());	// �ۑ���
		// �G���[�`�F�b�N
		if (FAILED(hr)) { return; }

		// ���_�V�F�[�_�[�̍쐬
		hr = _system.GetDevice()->CreateVertexShader(
			vertexShaderBlob->GetBufferPointer(),
			vertexShaderBlob->GetBufferSize(),
			nullptr,
			shaderResource.VertexSahder.GetAddressOf());
		if (FAILED(hr)) { return; }

		// �C���v�b�g���C�A�E�g�̍쐬
		hr = _system.GetDevice().Get()->CreateInputLayout(
			_vertexDesc,
			ARRAYSIZE(_vertexDesc),
			vertexShaderBlob.Get()->GetBufferPointer(),
			vertexShaderBlob.Get()->GetBufferSize(),
			shaderResource.VertexLayout.GetAddressOf());

		vertexShaderBlob.Reset();
		if (FAILED(hr)) { return; }
	}
	else if (extension == "cso") {	// �ǂݍ��ރt�@�C���̊g���q��cso�̏ꍇ
		auto result = LoadCSOFile(vertexShader.c_str());	// �߂�l�̌^���������ߏȗ�
		auto& [csoBuffer, csoSize] = *result;
		// ���_�V�F�[�_�[�̍쐬
		hr = _system.GetDevice().Get()->CreateVertexShader(
			csoBuffer.get(),
			csoSize,
			nullptr,
			shaderResource.VertexSahder.GetAddressOf());

		if (FAILED(hr)) { return; }

		// �C���v�b�g���C�A�E�g�̍쐬
		hr = _system.GetDevice().Get()->CreateInputLayout(
			_vertexDesc,
			ARRAYSIZE(_vertexDesc),
			csoBuffer.get(),
			csoSize,
			shaderResource.VertexLayout.GetAddressOf());
		if (FAILED(hr)) { return; }
	}
}

void Shader::CreatePixcelShader(const std::string& path, ShaderResource& shaderResource) {
	HRESULT hr = S_OK;
	// �t�@�C���̊g���q���擾
	size_t dotSplit = path.find_last_of('.');
	std::string extension = path.substr(dotSplit + 1);
	std::wstring pixcelShader = ConvertWstring(path);

	// �ǂݍ��ރt�@�C���̊g���q��hlsl�̏ꍇ
	if (extension == "hlsl") {
		ComPtr<ID3DBlob> pixcelShaderBlob = nullptr;

		hr = CompileShaderFromFile(
			pixcelShader.c_str(),
			"main",
			"ps_5_0",
			pixcelShaderBlob.GetAddressOf());

		if (FAILED(hr)) { return; }

		// �s�N�Z���V�F�[�_�[�̍쐬
		hr = _system.GetDevice().Get()->CreatePixelShader(
			pixcelShaderBlob.Get()->GetBufferPointer(),
			pixcelShaderBlob.Get()->GetBufferSize(),
			nullptr,
			shaderResource.PixelShader.GetAddressOf());

		pixcelShaderBlob.Reset();
		if (FAILED(hr)) { return; }
	}
	else if (extension == "cso") {	// �ǂݍ��ރt�@�C���̊g���q��cso�̏ꍇ
		std::optional<csoPair> result = LoadCSOFile(pixcelShader.c_str());
		auto& [csoBuffer, csoSize] = *result;

		// �s�N�Z���V�F�[�_�[�̍쐬
		hr = _system.GetDevice().Get()->CreatePixelShader(
			csoBuffer.get(),
			csoSize,
			nullptr,
			shaderResource.PixelShader.GetAddressOf());

		if (FAILED(hr)) { return; }
	}
}

HRESULT Shader::CompileShaderFromFile(LPCWSTR fileName, LPCSTR entryPoint, LPCSTR shaderModel, ID3DBlob** blobOut) {
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

std::optional<csoPair> Shader::LoadCSOFile(LPCWSTR fileName) {
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

std::wstring Shader::ConvertWstring(const std::string& str) {
	// �o�b�t�@�̑傫�������߂�
	size_t bufferSize = str.length() + 1;
	// string��wchar_t�ɕϊ�����
	std::wstring wStr(bufferSize, L'\0');
	size_t convertedChars = 0;
	// �ϊ������s
	mbstowcs_s(&convertedChars, &wStr[0], bufferSize, str.c_str(), bufferSize);

	return wStr;
}