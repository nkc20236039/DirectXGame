#pragma once

#include <memory>

#include "Graphics/Shader.h"
#include "Graphics/SpriteRenderer.h"
#include "System/DirectXApplication.h"

#pragma comment(lib, "d3d11.lib")
#pragma	comment(lib, "d3dCompiler.lib")

namespace UtX {
	struct Vertex {
	public:
		DirectX::XMFLOAT3 position;
		DirectX::XMFLOAT4 color;
		DirectX::XMFLOAT2 uv;
		DirectX::XMFLOAT3 normal;
	};

	struct ConstantBuffer {
	public:
		DirectX::XMMATRIX world;
		DirectX::XMMATRIX view;
		DirectX::XMMATRIX projection;
	};

	class SpriteMesh {
	public:
		SpriteMesh(DirectXApplication& system) : system(system) {}
		~SpriteMesh() {}

		void init(std::shared_ptr<ShaderResource> shaderResource);
		void rendering(const DirectX::XMMATRIX& wvp, const TextureResource& textureResource);
	private:
		const int32_t SPRITE_VERTEX_COUNT = 4;

		DirectXApplication& system;
		std::shared_ptr<ShaderResource> shaderResource;
		Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerState;
		Vertex vertexList[4] = {};
	};
}