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
#include "Direct3D.h"

struct TextureResource {
public:
	DirectX::TexMetadata metadata;
	DirectX::ScratchImage scratchImage;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> shaderResourceView;
};

class SpriteRenderer {
public:
	SpriteRenderer(Direct3D& system) : system(system) {}
	~SpriteRenderer() {}

	void createStandardSprite(std::string path);
	const TextureResource& getOrCreateSprite(std::string path);

private:
	Direct3D& system;
	TextureResource standardSprite;
	std::unordered_map<std::string, TextureResource> textureResourceMap;
};