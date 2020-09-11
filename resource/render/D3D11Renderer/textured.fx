cbuffer VS_CONSTANT_BUFFER {
    float4x4 gWVP;
};

Texture2D shaderTexture;
SamplerState SampleType
{
    Filter = MIN_MAG_MIP_LINEAR;
};

struct VS_Input
{
    float4 position : POSITION0;
    float2 uvcoord : TEXCOORD0;
};

struct VSOut
{
    float4 position : SV_POSITION;
    float2 uvcoord: TEXCOORD0;
};

VSOut VShader(VS_Input input)
{
    VSOut output;

    output.position = mul(input.position, gWVP);
    output.uvcoord = input.uvcoord;

    return output;
}


float4 PShader(VSOut input) : SV_TARGET
{
    return shaderTexture.Sample(SampleType, input.uvcoord);
}