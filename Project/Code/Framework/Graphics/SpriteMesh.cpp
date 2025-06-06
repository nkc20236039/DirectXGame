#include "SpriteMesh.h"
#include "../ApplicationConfig.h";

using namespace DirectX;

void SpriteMesh::Init(std::shared_ptr<ShaderResource> shaderResource) {
	// シェーダーの情報を保存
	_shaderResource = shaderResource;

	for (int32_t i = 0; i < SPRITE_VERTEX_COUNT; i++) {
		// 頂点座標
		_vertexList[i].Position.x = (i < 2) ? -0.5f : 0.5f;
		_vertexList[i].Position.y = ((i % 2) == 0) ? -0.5f : 0.5f;
		_vertexList[i].Position.z = 0.0f;
		// 頂点の色
		_vertexList[i].Color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		// UV
		_vertexList[i].UV.x = (i < 2) ? 0.0f : 1.0f;
		_vertexList[i].UV.y = ((i % 2) == 0) ? 1.0f : 0.0f;
		// ノーマルマップ
		_vertexList[i].Normal = XMFLOAT3(0.0f, 0.0f, 1.0f);
	}

	// バッファを設定
	D3D11_BUFFER_DESC descBuffer = {};
	descBuffer.Usage = D3D11_USAGE_DEFAULT;							// バッファで想定されているR/W方法を識別
	descBuffer.ByteWidth = sizeof(Vertex) * SPRITE_VERTEX_COUNT;	// バッファのサイズ
	descBuffer.BindFlags = D3D11_BIND_VERTEX_BUFFER;				// パイプラインをどのようにバインドするかを識別
	descBuffer.CPUAccessFlags = 0;									// CPUのアクセスフラグ

	// サブリソースを設定
	D3D11_SUBRESOURCE_DATA subResourceData = {};
	subResourceData.pSysMem = _vertexList;	// 初期化データへのポインタ
	subResourceData.SysMemPitch = 0;		// テクスチャにあるラインの距離
	subResourceData.SysMemSlicePitch = 0;	// 3Dテクスチャに関する値
	_system.GetDevice()->CreateBuffer(
		&descBuffer,
		&subResourceData,
		_shaderResource->VertexBuffer.GetAddressOf());

	// TODO:: ビューポート設定(仮)
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

	// サンプラーを作成
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

	// サブリソースの更新
	_system.GetDeviceContext()->UpdateSubresource(
		_shaderResource->VertexBuffer.Get(),
		0,
		nullptr,
		_vertexList,
		0,
		0);
	// 入力アセンブラステージに入力レイアウトオブジェクトをバインド
	_system.GetDeviceContext()->IASetInputLayout(_shaderResource->VertexLayout.Get());
	// 入力アセンブラステージに頂点バッファの配列をバインド
	UINT strides = sizeof(Vertex);
	UINT offset = 0;
	_system.GetDeviceContext()->IASetVertexBuffers(
		0,		// バインドに使用する最初の入力スロット
		1,		// 配列内の頂点バッファの数
		_shaderResource->VertexBuffer.GetAddressOf(),	// 頂点バッファの配列へのポインタ
		&strides,	// ストライド値
		&offset);	// オフセット
	// 頂点データをデバイスに設定
	_system.GetDeviceContext()->VSSetShader(
		_shaderResource->VertexSahder.Get(),	// 頂点シェーダーへのポインタ
		nullptr,								// クラスインスタンスインターフェースの配列へのポインタ
		0);										// 配列のクラスインスタンスインターフェースの数
	// 頂点シェーダーのパイプラインステージで使用される定数バッファを指定
	_system.GetDeviceContext()->VSSetConstantBuffers(
		0,		// デバイスの配列の中で定数バッファの設定を開始する位置
		1,		// 設定するバッファの数
		_system.GetConstantBuffer().GetAddressOf());	// デバイスに設定する定数バッファの配列

	// ピクセルシェーダーをデバイスに設定
	_system.GetDeviceContext()->PSSetShader(
		_shaderResource->PixelShader.Get(),	// ピクセルシェーダーへのポインタ
		nullptr,							// クラスインスタンスインターフェースへの配列へのポインタ
		0);									// 配列のクラスインスタンスインターフェースの数
	// テクスチャをシェーダーに渡す
	_system.GetDeviceContext()->PSSetSamplers(
		0,
		1,
		_samplerState.GetAddressOf());
	_system.GetDeviceContext()->PSSetShaderResources(
		0,
		1,
		textureResource.ShaderResourceView.GetAddressOf());
	// 入力アセンブラステージにプリミティブの形状をバインド
	_system.GetDeviceContext()->IASetPrimitiveTopology(
		// 頂点データを三角形のリストとして解釈
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	// プリミティブを描画
	_system.GetDeviceContext()->Draw(
		SPRITE_VERTEX_COUNT,
		0);
}