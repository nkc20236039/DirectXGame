#include "SpriteMesh.h"
#include "../ApplicationConfig.h";

using namespace DirectX;

void SpriteMesh::Init(std::shared_ptr<ShaderResource> shaderResource) {
	// �V�F�[�_�[�̏���ۑ�
	_shaderResource = shaderResource;

	for (int32_t i = 0; i < SPRITE_VERTEX_COUNT; i++) {
		// ���_���W
		_vertexList[i].Position.x = (i < 2) ? -0.5f : 0.5f;
		_vertexList[i].Position.y = ((i % 2) == 0) ? -0.5f : 0.5f;
		_vertexList[i].Position.z = 0.0f;
		// ���_�̐F
		_vertexList[i].Color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		// UV
		_vertexList[i].UV.x = (i < 2) ? 0.0f : 1.0f;
		_vertexList[i].UV.y = ((i % 2) == 0) ? 1.0f : 0.0f;
		// �m�[�}���}�b�v
		_vertexList[i].Normal = XMFLOAT3(0.0f, 0.0f, 1.0f);
	}

	// �o�b�t�@��ݒ�
	D3D11_BUFFER_DESC descBuffer = {};
	descBuffer.Usage = D3D11_USAGE_DEFAULT;							// �o�b�t�@�őz�肳��Ă���R/W���@������
	descBuffer.ByteWidth = sizeof(Vertex) * SPRITE_VERTEX_COUNT;	// �o�b�t�@�̃T�C�Y
	descBuffer.BindFlags = D3D11_BIND_VERTEX_BUFFER;				// �p�C�v���C�����ǂ̂悤�Ƀo�C���h���邩������
	descBuffer.CPUAccessFlags = 0;									// CPU�̃A�N�Z�X�t���O

	// �T�u���\�[�X��ݒ�
	D3D11_SUBRESOURCE_DATA subResourceData = {};
	subResourceData.pSysMem = _vertexList;	// �������f�[�^�ւ̃|�C���^
	subResourceData.SysMemPitch = 0;		// �e�N�X�`���ɂ��郉�C���̋���
	subResourceData.SysMemSlicePitch = 0;	// 3D�e�N�X�`���Ɋւ���l
	_system.GetDevice()->CreateBuffer(
		&descBuffer,
		&subResourceData,
		_shaderResource->VertexBuffer.GetAddressOf());

	// TODO:: �r���[�|�[�g�ݒ�(��)
	D3D11_VIEWPORT viewPort = {};
	viewPort.TopLeftX = 0.0f;
	viewPort.TopLeftY = 0.0f;
	viewPort.Width = WINDOW_W;
	viewPort.Height = WINDOW_H;
	viewPort.MinDepth = 0.0f;
	viewPort.MaxDepth = 1.0f;

	_system.GetDeviceContext()->RSSetViewports(
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
	_system.GetDevice()->CreateSamplerState(&sampler, _samplerState.GetAddressOf());
}

void SpriteMesh::Rendering(const TextureResource& textureResource) {
	ConstantBuffer constantBuffer = {};
	constantBuffer.world = DirectX::XMMatrixTranspose(DirectX::XMMatrixIdentity());
	constantBuffer.view = DirectX::XMMatrixTranspose(DirectX::XMMatrixIdentity());
	constantBuffer.projection = DirectX::XMMatrixTranspose(DirectX::XMMatrixIdentity());
	_system.GetDeviceContext()->UpdateSubresource(_system.GetConstantBuffer().Get(), 0, nullptr, &constantBuffer, 0, 0);

	// �T�u���\�[�X�̍X�V
	_system.GetDeviceContext()->UpdateSubresource(
		_shaderResource->VertexBuffer.Get(),
		0,
		nullptr,
		_vertexList,
		0,
		0);
	// ���̓A�Z���u���X�e�[�W�ɓ��̓��C�A�E�g�I�u�W�F�N�g���o�C���h
	_system.GetDeviceContext()->IASetInputLayout(_shaderResource->VertexLayout.Get());
	// ���̓A�Z���u���X�e�[�W�ɒ��_�o�b�t�@�̔z����o�C���h
	UINT strides = sizeof(Vertex);
	UINT offset = 0;
	_system.GetDeviceContext()->IASetVertexBuffers(
		0,		// �o�C���h�Ɏg�p����ŏ��̓��̓X���b�g
		1,		// �z����̒��_�o�b�t�@�̐�
		_shaderResource->VertexBuffer.GetAddressOf(),	// ���_�o�b�t�@�̔z��ւ̃|�C���^
		&strides,	// �X�g���C�h�l
		&offset);	// �I�t�Z�b�g
	// ���_�f�[�^���f�o�C�X�ɐݒ�
	_system.GetDeviceContext()->VSSetShader(
		_shaderResource->VertexSahder.Get(),	// ���_�V�F�[�_�[�ւ̃|�C���^
		nullptr,								// �N���X�C���X�^���X�C���^�[�t�F�[�X�̔z��ւ̃|�C���^
		0);										// �z��̃N���X�C���X�^���X�C���^�[�t�F�[�X�̐�
	// ���_�V�F�[�_�[�̃p�C�v���C���X�e�[�W�Ŏg�p�����萔�o�b�t�@���w��
	_system.GetDeviceContext()->VSSetConstantBuffers(
		0,		// �f�o�C�X�̔z��̒��Œ萔�o�b�t�@�̐ݒ���J�n����ʒu
		1,		// �ݒ肷��o�b�t�@�̐�
		_system.GetConstantBuffer().GetAddressOf());	// �f�o�C�X�ɐݒ肷��萔�o�b�t�@�̔z��

	// �s�N�Z���V�F�[�_�[���f�o�C�X�ɐݒ�
	_system.GetDeviceContext()->PSSetShader(
		_shaderResource->PixelShader.Get(),	// �s�N�Z���V�F�[�_�[�ւ̃|�C���^
		nullptr,							// �N���X�C���X�^���X�C���^�[�t�F�[�X�ւ̔z��ւ̃|�C���^
		0);									// �z��̃N���X�C���X�^���X�C���^�[�t�F�[�X�̐�
	// �e�N�X�`�����V�F�[�_�[�ɓn��
	_system.GetDeviceContext()->PSSetSamplers(
		0,
		1,
		_samplerState.GetAddressOf());
	_system.GetDeviceContext()->PSSetShaderResources(
		0,
		1,
		textureResource.ShaderResourceView.GetAddressOf());
	// ���̓A�Z���u���X�e�[�W�Ƀv���~�e�B�u�̌`����o�C���h
	_system.GetDeviceContext()->IASetPrimitiveTopology(
		// ���_�f�[�^���O�p�`�̃��X�g�Ƃ��ĉ���
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	// �v���~�e�B�u��`��
	_system.GetDeviceContext()->Draw(
		SPRITE_VERTEX_COUNT,
		0);
}