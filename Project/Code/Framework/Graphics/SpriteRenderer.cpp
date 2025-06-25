#include <filesystem>
#include "SpriteRenderer.h"
#include "../Utility.h"

using namespace DirectX;
using namespace Microsoft::WRL;

bool SpriteRenderer::createStandardSprite(std::string path) {
	// ファイルパスが無効であればエラー終了
	if (!std::filesystem::exists(path)) {
		return false;
	}

	// 画像を作成する
	bool isCreated = createSprite(path);

	// 作成に成功した場合
	if (isCreated) {
		// 標準のスプライトリソースのパスに設定する
		standardSpritePath = path;
		return true;
	}

	return false;
}

const TextureResource& SpriteRenderer::getSprite(std::string path) {
	// 既に読み込まれたリソースがある場合
	if (textureResourceMap.contains(path)) {
		// インスタンスのポインターを返す
		return textureResourceMap[path];
	}

	bool isCreated = createSprite(path);

	// 作成に失敗した場合
	if (!isCreated) {
		// 標準のテクスチャリソースを返す
		return textureResourceMap[standardSpritePath];
	}

	// 作成したテクスチャリソースを返す
	return textureResourceMap[path];
}

bool SpriteRenderer::createSprite(std::string path) {
	// 読み込まれているリソースがない場合新しく作成する
	HRESULT hr = S_OK;
	std::wstring wFileName = convertWstringPath(path);
	// 新しいリソースを作成
	TextureResource textureResource = {};

	// WTC画像読み込み
	hr = LoadFromWICFile(
		&wFileName[0],
		WIC_FLAGS_NONE,
		&textureResource.metadata,
		textureResource.scratchImage);
	if (FAILED(hr)) {
		return false;
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
		return false;
	}

	// ShaderResourceView作成
	hr = system.get_device().Get()->CreateShaderResourceView(
		texture.Get(),
		nullptr,
		&textureResource.shaderResourceView);

	textureResourceMap[path] = std::move(textureResource);
	return true;
}