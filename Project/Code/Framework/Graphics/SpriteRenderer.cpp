#include "SpriteRenderer.h"

using namespace DirectX;
using namespace Microsoft::WRL;

const TextureResource& SpriteRenderer::GetOrCreateSprite(std::string path) {
	// 既に読み込まれたリソースがある場合
	if (_textureResourceMap.contains(path)) {
		// インスタンスのポインターを返す
		return _textureResourceMap[path];
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
		&textureResource.Metadata,
		textureResource.ScratchImage);
	if (FAILED(hr)) { throw; }

	// GPUテクスチャ作成
	ComPtr<ID3D11Resource> texture;
	hr = CreateTexture(
		_system.GetDevice().Get(),
		textureResource.ScratchImage.GetImages(),
		textureResource.ScratchImage.GetImageCount(),
		textureResource.Metadata,
		&texture);
	if (FAILED(hr)) { throw; }

	// ShaderResourceView作成
	hr = _system.GetDevice().Get()->CreateShaderResourceView(
		texture.Get(),
		nullptr,
		&textureResource.ShaderResourceView);

	_textureResourceMap[path] = std::move(textureResource);

	return _textureResourceMap[path];
}