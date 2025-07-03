#pragma once

#include <Windows.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXColors.h>
#include <wrl/client.h>

#include "System/Application.h"

#pragma comment(lib, "d3dCompiler.lib")
#pragma comment(lib, "d3d11.lib")

namespace UtX {
	class DirectXApplication : public Application {
	public:
		using Application::Application;
		~DirectXApplication();

		bool init() override;
		void clearView(DirectX::XMVECTORF32 color);
		void present();
		void end() override;

		Microsoft::WRL::ComPtr<ID3D11Device> get_device() { return device; }
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> get_deviceContext() { return deviceContext; }
		Microsoft::WRL::ComPtr<ID3D11Buffer> get_constantBuffer() { return constantBuffer; }

	private:
		Microsoft::WRL::ComPtr<ID3D11Device> device = nullptr;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext = nullptr;
		Microsoft::WRL::ComPtr<ID3D11Buffer> constantBuffer = nullptr;
		Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain = nullptr;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTargetView = nullptr;
		Microsoft::WRL::ComPtr<ID3D11Texture2D> depthStencil = nullptr;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> depthStencilView = nullptr;
		Microsoft::WRL::ComPtr<ID3D11BlendState> blendState = nullptr;
		Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerState = nullptr;
	};
}