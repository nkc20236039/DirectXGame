#pragma once
#include <Windows.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXColors.h>
#include <wrl/client.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dCompiler.lib")

#include "../Application.h"


class Direct3D : public Application {
public:
	using Application::Application;
	~Direct3D();

	bool Init() override;
	void RenderBegin(float r, float g, float b, float a);
	void RenderEnd();
	void End() override;

	Microsoft::WRL::ComPtr<ID3D11Device> GetDevice() { return _device; }
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> GetDeviceContext() { return _deviceContext; }
	Microsoft::WRL::ComPtr<ID3D11Buffer> GetConstantBuffer() { return _constantBuffer; }

private:

	Microsoft::WRL::ComPtr<ID3D11Device> _device = nullptr;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> _deviceContext = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Buffer> _constantBuffer = nullptr;
	Microsoft::WRL::ComPtr<IDXGISwapChain> _swapChain = nullptr;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> _renderTargetView = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Texture2D> _depthStencil = nullptr;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> _depthStencilView = nullptr;
	Microsoft::WRL::ComPtr<ID3D11BlendState> _blendState = nullptr;
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> _rasterizerState = nullptr;
};