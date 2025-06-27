#include "SpriteMesh.h"
#include "../ApplicationConfig.h"

using namespace DirectX;

void SpriteMesh::init(std::shared_ptr<ShaderResource> shaderResource) {
	// シェーダーの情報を保存
	this->shaderResource = shaderResource;

	for (int32_t i = 0; i < SPRITE_VERTEX_COUNT; i++) {
		// 頂点座標
		vertexList[i].position.x = (i < 2) ? -0.5f : 0.5f;
		vertexList[i].position.y = ((i % 2) == 0) ? -0.5f : 0.5f;
		vertexList[i].position.z = 0.0f;
		// 頂点の色
		vertexList[i].color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		// UV
		vertexList[i].uv.x = (i < 2) ? 0.0f : 1.0f;
		vertexList[i].uv.y = ((i % 2) == 0) ? 1.0f : 0.0f;
		// ノーマルマップ
		vertexList[i].normal = XMFLOAT3(0.0f, 0.0f, 1.0f);
	}

	// バッファを設定
	D3D11_BUFFER_DESC descBuffer = {};
	descBuffer.Usage = D3D11_USAGE_DEFAULT;							// バッファで想定されているR/W方法を識別
	descBuffer.ByteWidth = sizeof(Vertex) * SPRITE_VERTEX_COUNT;	// バッファのサイズ
	descBuffer.BindFlags = D3D11_BIND_VERTEX_BUFFER;				// パイプラインをどのようにバインドするかを識別
	descBuffer.CPUAccessFlags = 0;									// CPUのアクセスフラグ

	// サブリソースを設定
	D3D11_SUBRESOURCE_DATA subResourceData = {};
	subResourceData.pSysMem = vertexList;	// 初期化データへのポインタ
	subResourceData.SysMemPitch = 0;		// テクスチャにあるラインの距離
	subResourceData.SysMemSlicePitch = 0;	// 3Dテクスチャに関する値
	system.get_device()->CreateBuffer(
		&descBuffer,
		&subResourceData,
		this->shaderResource->vertexBuffer.GetAddressOf());

	// TODO:: ビューポート設定(仮)
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

	// サンプラーを作成
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

	// サブリソースの更新
	system.get_deviceContext()->UpdateSubresource(
		shaderResource->vertexBuffer.Get(),
		0,
		nullptr,
		vertexList,
		0,
		0);
	// 入力アセンブラステージに入力レイアウトオブジェクトをバインド
	system.get_deviceContext()->IASetInputLayout(shaderResource->vertexLayout.Get());
	// 入力アセンブラステージに頂点バッファの配列をバインド
	UINT strides = sizeof(Vertex);
	UINT offset = 0;
	system.get_deviceContext()->IASetVertexBuffers(
		0,		// バインドに使用する最初の入力スロット
		1,		// 配列内の頂点バッファの数
		shaderResource->vertexBuffer.GetAddressOf(),	// 頂点バッファの配列へのポインタ
		&strides,	// ストライド値
		&offset);	// オフセット
	// 頂点データをデバイスに設定
	system.get_deviceContext()->VSSetShader(
		shaderResource->vertexSahder.Get(),	// 頂点シェーダーへのポインタ
		nullptr,								// クラスインスタンスインターフェースの配列へのポインタ
		0);										// 配列のクラスインスタンスインターフェースの数
	// 頂点シェーダーのパイプラインステージで使用される定数バッファを指定
	system.get_deviceContext()->VSSetConstantBuffers(
		0,		// デバイスの配列の中で定数バッファの設定を開始する位置
		1,		// 設定するバッファの数
		system.get_constantBuffer().GetAddressOf());	// デバイスに設定する定数バッファの配列

	// ピクセルシェーダーをデバイスに設定
	system.get_deviceContext()->PSSetShader(
		shaderResource->pixelShader.Get(),	// ピクセルシェーダーへのポインタ
		nullptr,							// クラスインスタンスインターフェースへの配列へのポインタ
		0);									// 配列のクラスインスタンスインターフェースの数
	// テクスチャをシェーダーに渡す
	system.get_deviceContext()->PSSetSamplers(
		0,
		1,
		samplerState.GetAddressOf());
	system.get_deviceContext()->PSSetShaderResources(
		0,
		1,
		textureResource.shaderResourceView.GetAddressOf());
	// 入力アセンブラステージにプリミティブの形状をバインド
	system.get_deviceContext()->IASetPrimitiveTopology(
		// 頂点データを三角形のリストとして解釈
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	// プリミティブを描画
	system.get_deviceContext()->Draw(
		SPRITE_VERTEX_COUNT,
		0);
}