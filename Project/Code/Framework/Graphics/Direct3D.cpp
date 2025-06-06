#include "Direct3D.h"
#include "../Application.h"
#include "../ApplicationConfig.h"
#include "SpriteMesh.h"

Direct3D::~Direct3D() = default;

bool Direct3D::init() {
	// �A�v���P�[�V�����̏��������ɍs��
	Application::init();

	// �������ʂ��i�[����
	HRESULT hr = S_OK;

	// �f�o�C�X�ƃX���C�v�`�F�C���̏�����
	{
		DXGI_SWAP_CHAIN_DESC chain = {};	// �X���b�v�`�F�C�����������錾
		chain.BufferCount = 1;	// �o�b�N�o�b�t�@�̐�
		chain.BufferDesc.Width = WINDOW_W;	// �o�b�N�o�b�t�@�̕�
		chain.BufferDesc.Width = WINDOW_H;	// �o�b�N�o�b�t�@�̍���
		chain.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;	// �t�H�[�}�b�g
		chain.BufferDesc.RefreshRate.Numerator = 60;		// ���t���b�V�����[�g
		chain.BufferDesc.RefreshRate.Denominator = 1;	// ���t���b�V�����[�g
		chain.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;	// �������`��
		chain.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;	// �X�P�[�����O
		chain.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;			// �o�b�N�o�b�t�@�̎g�p���@
		chain.OutputWindow = hWnd;	// �o�̓E�B���h�E�ւ̊֘A�t��
		chain.SampleDesc.Count = 1;	// �s�N�Z���P�ʂ̃}���`�T���v�����O�̐�
		chain.SampleDesc.Quality = 0;// �}���`�T���v�����O�̃N�I���e�B
		chain.Windowed = TRUE;		// �E�B���h�E���[�h
		chain.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;	// �X���b�v�`�F�C���̓���I�v�V����

		D3D_FEATURE_LEVEL level;
		// �f�o�C�X�ƃX���b�v�`�F�C���̍쐬
		hr = D3D11CreateDeviceAndSwapChain(
			nullptr,
			D3D_DRIVER_TYPE_HARDWARE,
			nullptr,
			0,
			nullptr,
			0,
			D3D11_SDK_VERSION,
			&chain,
			swapChain.GetAddressOf(),
			device.GetAddressOf(),
			&level,
			deviceContext.GetAddressOf()
		);

		// �G���[�������false�ŏI��
		if (FAILED(hr)) { return false; }
	}

	// �o�b�N�o�b�t�@��`��^�[�Q�b�g�ɐݒ�
	{
		// �X���b�v�`�F�C������ŏ��̃o�b�N�o�b�t�@���擾
		Microsoft::WRL::ComPtr<ID3D11Texture2D> backBuffer;	// �o�b�t�@�̃A�N�Z�X�Ɏg���C���^�[�t�F�[�X
		hr = swapChain.Get()->GetBuffer(
			0,
			__uuidof(ID3D11Texture2D),
			(LPVOID*)backBuffer.GetAddressOf()
		);

		// �G���[�������false�ŏI��
		if (FAILED(hr)) { return false; }

		hr = device->CreateRenderTargetView(
			backBuffer.Get(),
			nullptr,
			renderTargetView.GetAddressOf()
		);

		// �G���[�������false�ŏI��
		if (FAILED(hr)) { return false; }
	}

	// �[�x/�X�e���V���e�N�X�`���̍쐬
	{
		D3D11_TEXTURE2D_DESC depth;
		depth.Width = WINDOW_W;
		depth.Height = WINDOW_H;
		depth.MipLevels = 1;
		depth.ArraySize = 1;
		depth.Format = DXGI_FORMAT_D32_FLOAT;
		depth.SampleDesc.Count = 1;
		depth.SampleDesc.Quality = 0;
		depth.Usage = D3D11_USAGE_DEFAULT;
		depth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		depth.CPUAccessFlags = 0;
		depth.MiscFlags = 0;

		// 2D�e�N�X�`���̔z����쐬
		hr = device->CreateTexture2D(
			&depth,
			nullptr,
			depthStencil.GetAddressOf()
		);

		// �G���[�������false�ŏI��
		if (FAILED(hr)) { return false; }

		// �[�x/�X�e���V���r���[�̍쐬
		D3D11_DEPTH_STENCIL_VIEW_DESC dsv;
		dsv.Format = depth.Format;
		dsv.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		dsv.Flags = 0;
		dsv.Texture2D.MipSlice = 0;
		hr = device->CreateDepthStencilView(
			depthStencil.Get(),
			&dsv,
			depthStencilView.GetAddressOf()
		);

		// �G���[�������false�ŏI��
		if (FAILED(hr)) { return false; }

		// �`��^�[�Q�b�g�r���[���o�̓}�l�[�W���[�̕`��^�[�Q�b�g�Ƃ��Đݒ�
		deviceContext.Get()->OMSetRenderTargets(
			1,
			renderTargetView.GetAddressOf(),
			depthStencilView.Get()
		);
	}

	// ���X�^���C�Y�X�e�[�g�I�u�W�F�N�g�̐ݒ�
	{
		D3D11_RASTERIZER_DESC rasterizer = {
			D3D11_FILL_SOLID,
			D3D11_CULL_NONE,
			FALSE,
			0,
			0.0f,
			0.0f,
			FALSE,
			FALSE,
			FALSE,
			FALSE
		};

		// ���X�^���C�Y�X�e�[�g�I�u�W�F�N�g�̍쐬
		device.Get()->CreateRasterizerState(
			&rasterizer,
			rasterizerState.GetAddressOf()
		);

		// ���X�^���C�U�[���R���e�L�X�g�ɐݒ�
		deviceContext.Get()->RSSetState(rasterizerState.Get());
	}

	// �u�����f�B���O�X�e�[�g�̍쐬
	{
		D3D11_BLEND_DESC blend = {};
		blend.AlphaToCoverageEnable = FALSE;
		blend.IndependentBlendEnable = FALSE;
		blend.RenderTarget[0].BlendEnable = TRUE;
		blend.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		blend.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		blend.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		blend.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		blend.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		blend.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		blend.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		device.Get()->CreateBlendState(
			&blend,
			blendState.GetAddressOf()
		);

		// �u�����f�B���O�X�e�[�g�̐ݒ�
		float blendFactor[4] = {
			D3D11_BLEND_ZERO,
			D3D11_BLEND_ZERO,
			D3D11_BLEND_ZERO,
			D3D11_BLEND_ZERO
		};

		// �u�����f�B���O�X�e�[�g�̐ݒ�
		deviceContext.Get()->OMSetBlendState(
			blendState.Get(),
			blendFactor,
			0xffffffff
		);
	}

	{
		D3D11_BUFFER_DESC bufferDesc = {};
		bufferDesc.Usage = D3D11_USAGE_DEFAULT;
		bufferDesc.ByteWidth = sizeof(ConstantBuffer);
		bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bufferDesc.CPUAccessFlags = 0;

		hr = device->CreateBuffer(
			&bufferDesc,
			nullptr,
			constantBuffer.GetAddressOf());

		if (FAILED(hr)) { return false; }
	}

	return true;
}

void Direct3D::renderBegin(float r, float g, float b, float a) {
	float color[4] = { r, g, b, a };
	deviceContext.Get()->ClearRenderTargetView(renderTargetView.Get(), color);
	deviceContext.Get()->ClearDepthStencilView(depthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

void Direct3D::renderEnd() {
	swapChain->Present(0, 0);
}

void Direct3D::end() {

}