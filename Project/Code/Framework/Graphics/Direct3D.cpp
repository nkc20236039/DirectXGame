#include "Direct3D.h"
#include "../Application.h"
#include "../ApplicationConfig.h"
#include "SpriteMesh.h"

Direct3D::~Direct3D() = default;

bool Direct3D::init() {
	// アプリケーションの初期化を先に行う
	Application::init();

	// 生成結果を格納する
	HRESULT hr = S_OK;

	// デバイスとスワイプチェインの初期化
	{
		DXGI_SWAP_CHAIN_DESC chain = {};	// スワップチェインを初期化宣言
		chain.BufferCount = 1;	// バックバッファの数
		chain.BufferDesc.Width = WINDOW_W;	// バックバッファの幅
		chain.BufferDesc.Width = WINDOW_H;	// バックバッファの高さ
		chain.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;	// フォーマット
		chain.BufferDesc.RefreshRate.Numerator = 60;		// リフレッシュレート
		chain.BufferDesc.RefreshRate.Denominator = 1;	// リフレッシュレート
		chain.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;	// 走査線描画
		chain.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;	// スケーリング
		chain.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;			// バックバッファの使用方法
		chain.OutputWindow = hWnd;	// 出力ウィンドウへの関連付け
		chain.SampleDesc.Count = 1;	// ピクセル単位のマルチサンプリングの数
		chain.SampleDesc.Quality = 0;// マルチサンプリングのクオリティ
		chain.Windowed = TRUE;		// ウィンドウモード
		chain.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;	// スワップチェインの動作オプション

		D3D_FEATURE_LEVEL level;
		// デバイスとスワップチェインの作成
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

		// エラーがあればfalseで終了
		if (FAILED(hr)) { return false; }
	}

	// バックバッファを描画ターゲットに設定
	{
		// スワップチェインから最初のバックバッファを取得
		Microsoft::WRL::ComPtr<ID3D11Texture2D> backBuffer;	// バッファのアクセスに使うインターフェース
		hr = swapChain.Get()->GetBuffer(
			0,
			__uuidof(ID3D11Texture2D),
			(LPVOID*)backBuffer.GetAddressOf()
		);

		// エラーがあればfalseで終了
		if (FAILED(hr)) { return false; }

		hr = device->CreateRenderTargetView(
			backBuffer.Get(),
			nullptr,
			renderTargetView.GetAddressOf()
		);

		// エラーがあればfalseで終了
		if (FAILED(hr)) { return false; }
	}

	// 深度/ステンシルテクスチャの作成
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

		// 2Dテクスチャの配列を作成
		hr = device->CreateTexture2D(
			&depth,
			nullptr,
			depthStencil.GetAddressOf()
		);

		// エラーがあればfalseで終了
		if (FAILED(hr)) { return false; }

		// 深度/ステンシルビューの作成
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

		// エラーがあればfalseで終了
		if (FAILED(hr)) { return false; }

		// 描画ターゲットビューを出力マネージャーの描画ターゲットとして設定
		deviceContext.Get()->OMSetRenderTargets(
			1,
			renderTargetView.GetAddressOf(),
			depthStencilView.Get()
		);
	}

	// ラスタライズステートオブジェクトの設定
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

		// ラスタライズステートオブジェクトの作成
		device.Get()->CreateRasterizerState(
			&rasterizer,
			rasterizerState.GetAddressOf()
		);

		// ラスタライザーをコンテキストに設定
		deviceContext.Get()->RSSetState(rasterizerState.Get());
	}

	// ブレンディングステートの作成
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

		// ブレンディングステートの設定
		float blendFactor[4] = {
			D3D11_BLEND_ZERO,
			D3D11_BLEND_ZERO,
			D3D11_BLEND_ZERO,
			D3D11_BLEND_ZERO
		};

		// ブレンディングステートの設定
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