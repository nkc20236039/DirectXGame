#pragma once
#include <D3D11.h>
#include <wrl/client.h>
#include <d3dcompiler.h>
#include <unordered_map>
#include <string>
#include <memory>
#include <optional>
#include "DirectXApplication.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dCompiler.lib")

// ‹ó‚ÌƒpƒX
const std::string STANDARD_PATH_NAME = "Standard";

struct ShaderResource {
public:
	Microsoft::WRL::ComPtr<ID3D11InputLayout> vertexLayout = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Buffer> vertexBuffer = nullptr;
	Microsoft::WRL::ComPtr<ID3D11VertexShader> vertexSahder = nullptr;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pixelShader = nullptr;
};


class Shader {
public:
	Shader(DirectXApplication& system) : system(system) {}
	~Shader() {}
	bool CreateStandardShader(const std::string& vertexShaderPath, const std::string& pixcelShaderPath, std::shared_ptr<ShaderResource>& result);
	const ShaderResource& GetOrCreateShader(std::string vertexShaderPath, std::string pixcelShaderPath);

private:
	DirectXApplication& system;
	std::string standardShaderPath;
	std::unordered_map<std::string, ShaderResource> shaderResourceMap;

	D3D11_INPUT_ELEMENT_DESC vertexDesc[4]{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0,                            0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,		 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",	  0, DXGI_FORMAT_R32G32B32_FLOAT,	 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	HRESULT compileShaderFromFile(LPCWSTR fileName, LPCSTR entryPoint, LPCSTR shaderModel, ID3DBlob** blobOut);
	void createVertexShader(const std::string& path, ShaderResource& shaderResource);
	void createPixcelShader(const std::string& path, ShaderResource& shaderResource);
	std::optional<std::pair<std::unique_ptr<uint8_t[]>, int32_t>> loadCSOFile(LPCWSTR fileName);
};