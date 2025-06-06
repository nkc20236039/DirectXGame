// 受け取る頂点データの値
struct VS_INPUT
{
    float4 position : POSITION0;
    float4 color : COLOR0;
    float2 texcoord : TEXCOORD0;
    float3 normal : NORMAL0;
};

// ピクセルシェーダーに送る値
struct VS_OUTPUT
{
    float4 position : SV_POSITION;
    float4 color : COLOR0;
    float2 texcoord  : TEXCOORD0;
    float3 normal : NORMAL0;
};

// 座標行列データを受け取る
cbuffer ConstantBuffer : register(b0)
{
    matrix World; // ワールド座標行列
    matrix View; // ビュー変換行列
    matrix Projection; // プロジェクション変換行列
}


VS_OUTPUT main(VS_INPUT input)
{
    VS_OUTPUT output;

    output.position = mul(input.position, World); // 現在の座標とワールド変換行列で乗算を行う
    output.position = mul(input.position, View); // 上記計算後の座標とビュー変換行列で乗算を行う
    output.position = mul(input.position, Projection); // 上記計算後の座標とプロジェクション変換行列で乗算を行う

    output.color = input.color;
    output.texcoord  = input.texcoord;

    return output;
}