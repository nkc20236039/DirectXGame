// �󂯎�钸�_�f�[�^�̒l
struct VS_INPUT
{
    float4 position : POSITION0;
    float4 color : COLOR0;
    float2 texcoord : TEXCOORD0;
    float3 normal : NORMAL0;
};

// �s�N�Z���V�F�[�_�[�ɑ���l
struct VS_OUTPUT
{
    float4 position : SV_POSITION;
    float4 color : COLOR0;
    float2 texcoord  : TEXCOORD0;
    float3 normal : NORMAL0;
};

// ���W�s��f�[�^���󂯎��
cbuffer ConstantBuffer : register(b0)
{
    matrix World; // ���[���h���W�s��
    matrix View; // �r���[�ϊ��s��
    matrix Projection; // �v���W�F�N�V�����ϊ��s��
}


VS_OUTPUT main(VS_INPUT input)
{
    VS_OUTPUT output;

    output.position = mul(input.position, World); // ���݂̍��W�ƃ��[���h�ϊ��s��ŏ�Z���s��
    output.position = mul(input.position, View); // ��L�v�Z��̍��W�ƃr���[�ϊ��s��ŏ�Z���s��
    output.position = mul(input.position, Projection); // ��L�v�Z��̍��W�ƃv���W�F�N�V�����ϊ��s��ŏ�Z���s��

    output.color = input.color;
    output.texcoord  = input.texcoord;

    return output;
}