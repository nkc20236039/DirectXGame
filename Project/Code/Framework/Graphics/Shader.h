#pragma once
#include <D3D11.h>
#include <wrl/client.h>
#include <d3dcompiler.h>
#include <unordered_map>
#include <string>
#include <memory>
#include <optional>
#include "Direct3D.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dCompiler.lib")

// ‹ó‚ÌƒpƒX
#define NULLPATH "NULL"

struct ShaderResource {
	Microsoft::WRL::ComPtr<ID3D11InputLayout> VertexLayout = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Buffer> VertexBuffer = nullptr;
	Microsoft::WRL::ComPtr<ID3D11VertexShader> VertexSahder = nullptr;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> PixelShader = nullptr;
};

constexpr char STANDARD_PATH_NAME[] = "Standard";

class Shader {
public:
	Shader(Direct3D& system) : _system(system) {}
	~Shader() {}
	bool CreateStandardShader(const std::string& vertexShaderPath, const std::string& pixcelShaderPath, std::shared_ptr<ShaderResource>& result);
	const ShaderResource& GetOrCreateShader(std::string vertexShaderPath, std::string pixcelShaderPath);

private:
	Direct3D& _system;
	std::string _standardShaderPath;
	std::unordered_map<std::string, ShaderResource> _shaderResourceMap;

	D3D11_INPUT_ELEMENT_DESC _vertexDesc[4]{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0,                            0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,		 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",	  0, DXGI_FORMAT_R32G32B32_FLOAT,	 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	HRESULT CompileShaderFromFile(LPCWSTR fileName, LPCSTR entryPoint, LPCSTR shaderModel, ID3DBlob** blobOut);
	void CreateVertexShader(const std::string& path, ShaderResource& shaderResource);
	void CreatePixcelShader(const std::string& path, ShaderResource& shaderResource);
	std::wstring ConvertWstring(const std::string& str);
	std::optional<std::pair<std::unique_ptr<uint8_t[]>, int32_t>> LoadCSOFile(LPCWSTR fileName);
};