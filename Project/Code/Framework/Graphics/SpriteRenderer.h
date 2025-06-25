#pragma once

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

#include <string>
#include <unordered_map>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXColors.h>
#include <memory>
#include <DirectXTex.h>
#include "DirectXApplication.h"

struct TextureResource {
public:
	DirectX::TexMetadata metadata;
	DirectX::ScratchImage scratchImage;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> shaderResourceView;
};

class SpriteRenderer {
public:
	SpriteRenderer(DirectXApplication& system) : system(system) {}
	~SpriteRenderer() {}

	bool createStandardSprite(std::string path);
	const TextureResource& getSprite(std::string path);

private:
	DirectXApplication& system;
	std::string standardSpritePath;
	std::unordered_map<std::string, TextureResource> textureResourceMap;

	bool createSprite(std::string path);
};