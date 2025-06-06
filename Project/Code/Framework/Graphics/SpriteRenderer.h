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
	DirectX::TexMetadata Metadata;
	DirectX::ScratchImage ScratchImage;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> ShaderResourceView;
};

class SpriteRenderer {
public:
	SpriteRenderer(Direct3D& system) : _system(system) {}
	~SpriteRenderer() {}

	const TextureResource& GetOrCreateSprite(std::string path);

private:
	Direct3D& _system;
	std::unordered_map<std::string, TextureResource> _textureResourceMap;
};