#include "SpriteMesh.h"
#include "../ApplicationConfig.h"

using namespace DirectX;

void SpriteMesh::init(std::shared_ptr<ShaderResource> shaderResource) {
	// �V�F�[�_�[�̏���ۑ�
	this->shaderResource = shaderResource;

	for (int32_t i = 0; i < SPRITE_VERTEX_COUNT; i++) {
		// ���_���W
		vertexList[i].position.x = (i < 2) ? -0.5f : 0.5f;
		vertexList[i].position.y = ((i % 2) == 0) ? -0.5f : 0.5f;
		vertexList[i].position.z = 0.0f;
		// ���_�̐F
		vertexList[i].color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		// UV
		vertexList[i].uv.x = (i < 2) ? 0.0f : 1.0f;
		vertexList[i].uv.y = ((i % 2) == 0) ? 1.0f : 0.0f;
		// �m�[�}���}�b�v
		vertexList[i].normal = XMFLOAT3(0.0f, 0.0f, 1.0f);
	}

	// �o�b�t�@��ݒ�
	D3D11_BUFFER_DESC descBuffer = {};
	descBuffer.Usage = D3D11_USAGE_DEFAULT;							// �o�b�t�@�őz�肳��Ă���R/W���@������
	descBuffer.ByteWidth = sizeof(Vertex) * SPRITE_VERTEX_COUNT;	// �o�b�t�@�̃T�C�Y
	descBuffer.BindFlags = D3D11_BIND_VERTEX_BUFFER;				// �p�C�v���C�����ǂ̂悤�Ƀo�C���h���邩������
	descBuffer.CPUAccessFlags = 0;									// CPU�̃A�N�Z�X�t���O

	// �T�u���\�[�X��ݒ�
	D3D11_SUBRESOURCE_DATA subResourceData = {};
	subResourceData.pSysMem = vertexList;	// �������f�[�^�ւ̃|�C���^
	subResourceData.SysMemPitch = 0;		// �e�N�X�`���ɂ��郉�C���̋���
	subResourceData.SysMemSlicePitch = 0;	// 3D�e�N�X�`���Ɋւ���l
	system.get_device()->CreateBuffer(
		&descBuffer,
		&subResourceData,
		this->shaderResource->vertexBuffer.GetAddressOf());

	// TODO:: �r���[�|�[�g�ݒ�(��)
	D3D11_VIEWPORT viewPort = {};
	viewPort.TopLeftX = 0.0f;
	viewPort.TopLeftY = 0.0f;
	viewPort.Width = WINDOW_WIDTH;
	viewPort.Height = WINDOW_HEIGHT;
	viewPort.MinDepth = 0.0f;
	viewPort.MaxDepth = 1.0f;

	system.get_deviceContext()->RSSetViewports(
		1,
		&viewPort
	);

	// �T���v���[���쐬
	D3D11_SAMPLER_DESC sampler = {};
	sampler.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampler.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampler.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampler.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampler.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampler.MinLOD = 0;
	sampler.MaxLOD = D3D11_FLOAT32_MAX;
	system.get_device()->CreateSamplerState(&sampler, samplerState.GetAddressOf());
}

void SpriteMesh::rendering(const DirectX::XMMATRIX& wvp, const TextureResource& textureResource) {
	system.get_deviceContext()->UpdateSubresource(
		system.get_constantBuffer().Get(),
		0, 
		nullptr,
		&wvp,
		0,
		0);

	// �T�u���\�[�X�̍X�V
	system.get_deviceContext()->UpdateSubresource(
		shaderResource->vertexBuffer.Get(),
		0,
		nullptr,
		vertexList,
		0,
		0);
	// ���̓A�Z���u���X�e�[�W�ɓ��̓��C�A�E�g�I�u�W�F�N�g���o�C���h
	system.get_deviceContext()->IASetInputLayout(shaderResource->vertexLayout.Get());
	// ���̓A�Z���u���X�e�[�W�ɒ��_�o�b�t�@�̔z����o�C���h
	UINT strides = sizeof(Vertex);
	UINT offset = 0;
	system.get_deviceContext()->IASetVertexBuffers(
		0,		// �o�C���h�Ɏg�p����ŏ��̓��̓X���b�g
		1,		// �z����̒��_�o�b�t�@�̐�
		shaderResource->vertexBuffer.GetAddressOf(),	// ���_�o�b�t�@�̔z��ւ̃|�C���^
		&strides,	// �X�g���C�h�l
		&offset);	// �I�t�Z�b�g
	// ���_�f�[�^���f�o�C�X�ɐݒ�
	system.get_deviceContext()->VSSetShader(
		shaderResource->vertexSahder.Get(),	// ���_�V�F�[�_�[�ւ̃|�C���^
		nullptr,								// �N���X�C���X�^���X�C���^�[�t�F�[�X�̔z��ւ̃|�C���^
		0);										// �z��̃N���X�C���X�^���X�C���^�[�t�F�[�X�̐�
	// ���_�V�F�[�_�[�̃p�C�v���C���X�e�[�W�Ŏg�p�����萔�o�b�t�@���w��
	system.get_deviceContext()->VSSetConstantBuffers(
		0,		// �f�o�C�X�̔z��̒��Œ萔�o�b�t�@�̐ݒ���J�n����ʒu
		1,		// �ݒ肷��o�b�t�@�̐�
		system.get_constantBuffer().GetAddressOf());	// �f�o�C�X�ɐݒ肷��萔�o�b�t�@�̔z��

	// �s�N�Z���V�F�[�_�[���f�o�C�X�ɐݒ�
	system.get_deviceContext()->PSSetShader(
		shaderResource->pixelShader.Get(),	// �s�N�Z���V�F�[�_�[�ւ̃|�C���^
		nullptr,							// �N���X�C���X�^���X�C���^�[�t�F�[�X�ւ̔z��ւ̃|�C���^
		0);									// �z��̃N���X�C���X�^���X�C���^�[�t�F�[�X�̐�
	// �e�N�X�`�����V�F�[�_�[�ɓn��
	system.get_deviceContext()->PSSetSamplers(
		0,
		1,
		samplerState.GetAddressOf());
	system.get_deviceContext()->PSSetShaderResources(
		0,
		1,
		textureResource.shaderResourceView.GetAddressOf());
	// ���̓A�Z���u���X�e�[�W�Ƀv���~�e�B�u�̌`����o�C���h
	system.get_deviceContext()->IASetPrimitiveTopology(
		// ���_�f�[�^���O�p�`�̃��X�g�Ƃ��ĉ���
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	// �v���~�e�B�u��`��
	system.get_deviceContext()->Draw(
		SPRITE_VERTEX_COUNT,
		0);
}