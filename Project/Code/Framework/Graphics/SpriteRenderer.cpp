#include <filesystem>
#include "SpriteRenderer.h"
#include "../Utility.h"

using namespace DirectX;
using namespace Microsoft::WRL;

bool SpriteRenderer::createStandardSprite(std::string path) {
	// �t�@�C���p�X�������ł���΃G���[�I��
	if (!std::filesystem::exists(path)) {
		return false;
	}

	// �摜���쐬����
	bool isCreated = createSprite(path);

	// �쐬�ɐ��������ꍇ
	if (isCreated) {
		// �W���̃X�v���C�g���\�[�X�̃p�X�ɐݒ肷��
		standardSpritePath = path;
		return true;
	}

	return false;
}

const TextureResource& SpriteRenderer::getSprite(std::string path) {
	// ���ɓǂݍ��܂ꂽ���\�[�X������ꍇ
	if (textureResourceMap.contains(path)) {
		// �C���X�^���X�̃|�C���^�[��Ԃ�
		return textureResourceMap[path];
	}

	bool isCreated = createSprite(path);

	// �쐬�Ɏ��s�����ꍇ
	if (!isCreated) {
		// �W���̃e�N�X�`�����\�[�X��Ԃ�
		return textureResourceMap[standardSpritePath];
	}

	// �쐬�����e�N�X�`�����\�[�X��Ԃ�
	return textureResourceMap[path];
}

bool SpriteRenderer::createSprite(std::string path) {
	// �ǂݍ��܂�Ă��郊�\�[�X���Ȃ��ꍇ�V�����쐬����
	HRESULT hr = S_OK;
	std::wstring wFileName = convertWstringPath(path);
	// �V�������\�[�X���쐬
	TextureResource textureResource = {};

	// WTC�摜�ǂݍ���
	hr = LoadFromWICFile(
		&wFileName[0],
		WIC_FLAGS_NONE,
		&textureResource.metadata,
		textureResource.scratchImage);
	if (FAILED(hr)) {
		return false;
	}

	// GPU�e�N�X�`���쐬
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

	// ShaderResourceView�쐬
	hr = system.get_device().Get()->CreateShaderResourceView(
		texture.Get(),
		nullptr,
		&textureResource.shaderResourceView);

	textureResourceMap[path] = std::move(textureResource);
	return true;
}