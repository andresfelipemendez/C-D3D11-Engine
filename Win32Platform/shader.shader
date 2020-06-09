cbuffer MatrixBuffer
{
    matrix worldMatrix;
    matrix viewMatrix;
    matrix projectionMatrix;
};


struct VOut
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
    float2 tex : TEXCOORD0;
};

Texture2D shaderTexture;
SamplerState SampleType;

VOut VShader(float4 position : POSITION, float4 color : COLOR, float2 tex : TEXCOORD0)
{
    VOut output;

    output.position = mul(position,worldMatrix);
    output.position = mul(output.position,viewMatrix);
    output.position = mul(output.position,projectionMatrix);
    output.color = color;
    output.tex = tex;

    return output;
}

float4 PShader(float4 position : SV_POSITION, float4 color : COLOR, float2 tex : TEXCOORD0) : SV_TARGET
{
       
    return color * shaderTexture.Sample(SampleType, tex);
}