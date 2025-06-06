#include "SpriteRenderer.h"

using namespace DirectX;
using namespace Microsoft::WRL;

const TextureResource& SpriteRenderer::GetOrCreateSprite(std::string path) {
	// ���ɓǂݍ��܂ꂽ���\�[�X������ꍇ
	if (_textureResourceMap.contains(path)) {
		// �C���X�^���X�̃|�C���^�[��Ԃ�
		return _textureResourceMap[path];
	}

	// �ǂݍ��܂�Ă��郊�\�[�X���Ȃ��ꍇ�V�����쐬����

	HRESULT hr = S_OK;
	size_t bufferSize = path.length() + 1;
	// string��wchar_t�ɕϊ�����
	std::wstring wFileName(bufferSize, L'\0');
	size_t convertedChars = 0;
	mbstowcs_s(&convertedChars, &wFileName[0], bufferSize, path.c_str(), bufferSize);
	// �V�������\�[�X���쐬
	TextureResource textureResource = {};

	// WTC�摜�ǂݍ���
	hr = LoadFromWICFile(
		&wFileName[0],
		WIC_FLAGS_NONE,
		&textureResource.Metadata,
		textureResource.ScratchImage);
	if (FAILED(hr)) { throw; }

	// GPU�e�N�X�`���쐬
	ComPtr<ID3D11Resource> texture;
	hr = CreateTexture(
		_system.GetDevice().Get(),
		textureResource.ScratchImage.GetImages(),
		textureResource.ScratchImage.GetImageCount(),
		textureResource.Metadata,
		&texture);
	if (FAILED(hr)) { throw; }

	// ShaderResourceView�쐬
	hr = _system.GetDevice().Get()->CreateShaderResourceView(
		texture.Get(),
		nullptr,
		&textureResource.ShaderResourceView);

	_textureResourceMap[path] = std::move(textureResource);

	return _textureResourceMap[path];
}