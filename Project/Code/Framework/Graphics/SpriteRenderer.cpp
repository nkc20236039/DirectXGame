#include "SpriteRenderer.h"

using namespace DirectX;
using namespace Microsoft::WRL;

bool SpriteRenderer::createStandardSprite(std::string path) {

}

const TextureResource& SpriteRenderer::getOrCreateSprite(std::string path) {
	// ���ɓǂݍ��܂ꂽ���\�[�X������ꍇ
	if (textureResourceMap.contains(path)) {
		// �C���X�^���X�̃|�C���^�[��Ԃ�
		return textureResourceMap[path];
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
		&textureResource.metadata,
		textureResource.scratchImage);
	if (FAILED(hr)) { throw; }

	// GPU�e�N�X�`���쐬
	ComPtr<ID3D11Resource> texture;
	hr = CreateTexture(
		system.get_device().Get(),
		textureResource.scratchImage.GetImages(),
		textureResource.scratchImage.GetImageCount(),
		textureResource.metadata,
		&texture);
	if (FAILED(hr)) { throw; }

	// ShaderResourceView�쐬
	hr = system.get_device().Get()->CreateShaderResourceView(
		texture.Get(),
		nullptr,
		&textureResource.shaderResourceView);

	textureResourceMap[path] = std::move(textureResource);

	return textureResourceMap[path];
}