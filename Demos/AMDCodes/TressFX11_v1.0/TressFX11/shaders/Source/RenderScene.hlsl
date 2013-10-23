//--------------------------------------------------------------------------------------
// File: RenderScene.hlsl
//
// Scene rendering (non-hair) shaders
// 
// Copyright © AMD Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#include "common.hlsl"

VS_OUTPUT_SM VS_GenerateSceneSM( VS_INPUT_SCENE input )
{
    VS_OUTPUT_SM Output;
    
    // Transform the position from object space to homogeneous projection space
    float3 pos = mul(float4(input.Position, 1), g_mWorld).xyz;
    Output.Position = mul( float4(pos, 1), g_mViewProjLight );
    
    // output position
    Output.WorldPos = input.Position;
    
    return Output;    
}

VS_OUTPUT_SCENE VS_RenderScene( VS_INPUT_SCENE input )
{
    VS_OUTPUT_SCENE Output;
    
    // Transform the position from object space to homogeneous projection space
        
    float3 pos = mul(float4(input.Position, 1), g_mWorld).xyz;
    Output.Position = mul( float4(pos, 1), g_mViewProj );

    // output tangent and texture coordinate value
    Output.Normal = input.Normal;
    Output.Texcoord = input.Texcoord;

    // output position
    Output.WorldPos = pos;
    
    return Output;    
}

//basic phong shading
float4 PhongShading(float3 iPos, float3 iNormal, float2 tex, float amountLight)
{
    // define ambient, diffuse and specular term for material
    float4 matAmbient = g_MatAmbient;
    float4 matDiffuse = float4(g_MatDiffuse.xyz, 1);

    float4 matSpecular = float4(g_MatSpecular.xyz, 1);
    float exponent = g_MatSpecular.w;

    float3 lightPos = g_PointLightPos.xyz;
    float3 vLightDir = normalize(lightPos - iPos);
    float3 normal = normalize(iNormal);

    float LDotN = dot(normal, vLightDir);
    float vDiffuse = max(0, LDotN);
    
    float3 vEyeDir = normalize(g_vEye.xyz - iPos.xyz);
    float3 vHalf = normalize(vEyeDir + vLightDir);
    float HDotN = dot(vHalf, normal);
    float vSpecular = max(0, HDotN);

    if(g_MatDiffuse.w > 0)
    {
        float4 texColor = g_txObj.Sample( g_samLinearWrap, tex );
        
        if ( texColor.x == 0 && texColor.y == 0 && texColor.z == 0 )
        {
            matAmbient = 0.7 * g_ScalpColor;
            matDiffuse = 0.7 * g_ScalpColor;
            vSpecular = 0;
        }
        else
        {
            matAmbient *= texColor;
            matDiffuse *= texColor;
        }
    }

    float4 vColor = matAmbient * g_AmbientLightColor + amountLight * 
        g_PointLightColor *	( matDiffuse * vDiffuse  + matSpecular * pow(vSpecular, exponent));

    return vColor;
}

float4 ComputeSceneShading(float3 pos, float3 normal, float2 tex, float amountLight)
{
    return PhongShading(pos, normal, tex, amountLight);
}

[earlydepthstencil]
float4 PS_RenderScene(VS_OUTPUT_SCENE input):SV_Target
{
    INPUT_SHADOW inShadow;
    inShadow.pos = input.WorldPos;
    AmountLight amountLight = ComputeShadow(inShadow, 0.001, g_iTechSM);
    float light = (amountLight.amountLight_hair*amountLight.amountLight_scene)*0.95+0.05;
    return ComputeSceneShading(input.WorldPos, input.Normal, input.Texcoord, light);	
}
