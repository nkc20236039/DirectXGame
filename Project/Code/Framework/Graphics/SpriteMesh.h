#pragma once
#include <memory>
#include "Shader.h"
#include "SpriteRenderer.h"
#include "Direct3D.h"

#pragma comment(lib, "d3d11.lib")
#pragma	comment(lib, "d3dCompiler.lib")

struct Vertex {
	DirectX::XMFLOAT3 Position;
	DirectX::XMFLOAT4 Color;
	DirectX::XMFLOAT2 UV;
	DirectX::XMFLOAT3 Normal;
};

struct ConstantBuffer {
	DirectX::XMMATRIX world;
	DirectX::XMMATRIX view;
	DirectX::XMMATRIX projection;
};

class SpriteMesh {
public:
	SpriteMesh(Direct3D& system) : _system(system) {}
	~SpriteMesh() {}

	void Init(std::shared_ptr<ShaderResource> shaderResource);
	void Rendering(const TextureResource& textureResource);
private:
	const int32_t SPRITE_VERTEX_COUNT = 4;

	Direct3D& _system;
	std::shared_ptr<ShaderResource> _shaderResource;
	Microsoft::WRL::ComPtr<ID3D11SamplerState> _samplerState;
	Vertex _vertexList[4] = {};
};