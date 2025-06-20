#include <filesystem>
#include "SpriteRenderer.h"

using namespace DirectX;
using namespace Microsoft::WRL;

bool SpriteRenderer::createStandardSprite(std::string path) {
	// ファイルパスが無効であればエラー終了
	if (!std::filesystem::exists(path)) {
		return false;
	}
}

const TextureResource& SpriteRenderer::getSprite(std::string path) {
	// 既に読み込まれたリソースがある場合
	if (textureResourceMap.contains(path)) {
		// インスタンスのポインターを返す
		return textureResourceMap[path];
	}

	// 読み込まれているリソースがない場合新しく作成する
	HRESULT hr = S_OK;
	size_t bufferSize = path.length() + 1;
	// stringをwchar_tに変換する
	std::wstring wFileName(bufferSize, L'\0');
	size_t convertedChars = 0;
	mbstowcs_s(&convertedChars, &wFileName[0], bufferSize, path.c_str(), bufferSize);
	// 新しいリソースを作成
	TextureResource textureResource = {};

	// WTC画像読み込み
	hr = LoadFromWICFile(
		&wFileName[0],
		WIC_FLAGS_NONE,
		&textureResource.metadata,
		textureResource.scratchImage);
	if (FAILED(hr)) {
		return textureResourceMap[standardSpritePath];
	}

	// GPUテクスチャ作成
	ComPtr<ID3D11Resource> texture;
	hr = CreateTexture(
		system.get_device().Get(),
		textureResource.scratchImage.GetImages(),
		textureResource.scratchImage.GetImageCount(),
		textureResource.metadata,
		&texture);
	if (FAILED(hr)) {
		return textureResourceMap[standardSpritePath];
	}

	// ShaderResourceView作成
	hr = system.get_device().Get()->CreateShaderResourceView(
		texture.Get(),
		nullptr,
		&textureResource.shaderResourceView);

	textureResourceMap[path] = std::move(textureResource);

	return textureResourceMap[path];
}