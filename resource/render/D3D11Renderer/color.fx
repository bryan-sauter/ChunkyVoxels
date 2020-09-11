cbuffer VS_CONSTANT_BUFFER {
    float4x4 gWVP;
};

struct VOut
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
};

VOut VShader(float4 position : POSITION, float4 color : COLOR)
{
    VOut output;

    output.position = mul(position, gWVP);
    output.color = color;

    return output;
}


float4 PShader(VOut input) : SV_TARGET
{
    return input.color;
}