Texture2D g_Texture : register(t0);
SamplerState g_Sampler : register(s0);

// 頂点シェーダから受け取る値
struct PS_INPUT
{
    float4 position : SV_POSITION;
    float4 color : COLOR0;
    float2 texcoord : TEXCOORD0;
    float3 normal : NORMAL0;
};

float4 main(PS_INPUT input) : SV_TARGET
{
    float4 inputTexture = float4(0.0f, 0.5f, 1.0f, 1.0f);
    inputTexture = g_Texture.Sample(g_Sampler, input.texcoord);
    return inputTexture;
}