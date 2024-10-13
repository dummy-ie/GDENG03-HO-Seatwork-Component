struct PS_INPUT
{
    float4 position : SV_POSITION;
    float3 color : COLOR;
    float3 color1 : COLOR1;
};

cbuffer constant : register(b0)
{
    row_major float4x4 worldMatrix;
    row_major float4x4 viewMatrix;
    row_major float4x4 projMatrix;
    float time;
};

cbuffer editor : register(b1)
{
    bool wireframe;
}

float4 psmain(PS_INPUT input) : SV_TARGET
{
    if (wireframe)
        return float4(0.0, 0.0, 0.0, 0.0);
    return float4(lerp(input.color, input.color1, (sin(time) + 1.0f) / 2.0f), 1.0f);
}