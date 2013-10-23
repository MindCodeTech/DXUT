//--------------------------------------------------------------------------------------
// File: kbuffer.hlsl
//
// K-buffer implementation using a per-pixel linked list
// 
// Copyright © AMD Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#include "hairbasic.hlsl"

//////////////////////////////////////////////////////////////////////////////////////////////
// Render hair from eye camera, store all fragments
//////////////////////////////////////////////////////////////////////////////////////////////

// store fragment(x, y) with depth: depthNDC and color: vColor
void StoreFragments_Hair(uint x, uint y, float depthNDC, float4 vColor)
{
    //////////////////////////////////////////////////////////////////////////////////////////////
    // Write fragment into UAVs
    float2 winSizeEye = float2(g_WinSize.xy);

    // Retrieve current pixel count and increase counter
    uint uPixelCount = EyeFragmentUAV.IncrementCounter();
    uint uStartOffsetLinearAddress = 4 *(winSizeEye.x * y + x);
    uint uOldStartOffset;

    // Exchange indices in StartOffsetTexture corresponding to pixel location 
    EyeRefUAV.InterlockedExchange(uStartOffsetLinearAddress, uPixelCount, uOldStartOffset);  // link head texture

    // Append new element at the end of the Fragment and Link Buffer
    Eye_Fragment_STRUCT Element;
    Element.uPixelColor         = PackFloat4IntoUint(vColor);
    Element.uDepthAndCoverage   = PackDepthIntoUint(depthNDC);
    Element.uNext               = uOldStartOffset;
    EyeFragmentUAV[uPixelCount] = Element; // buffer that stores the fragments
}

//////////////////////////////////////////////////////////////////////////////////////////////////
// AA fragments
[earlydepthstencil]
float4 PS_ABuffer_Hair( PS_INPUT_HAIR_AA In) : SV_Target
{ 
    /////////////////////////////////////////////////////////////////////////////////
    // shadow and shading
    INPUT_SHADOW inShadow;
    inShadow.pos = In.WorldPos;
    AmountLight amountLight = ComputeShadow(inShadow, g_HairShadowAlpha, g_iTechSM);
    float light = amountLight.amountLight_scene * amountLight.amountLight_hair;
    float4 vColor = ComputeHairShading( In.WorldPos, In.Tangent, In.Texcoord, light);	
    // transmittance value
    vColor.w = g_FiberAlpha;

    //////////////////////////////////////////////////////////////////////////////////////////////
    // Render AA Line, calculate pixel coverage
    float2 winSizeEye = float2(g_WinSize.xy);
    float4 proj_pos = float4(2*(In.Position.x - winSizeEye.x/2)/winSizeEye.x, 
                             2*(winSizeEye.y/2 - In.Position.y)/winSizeEye.y, 1, 1);

    float4 original_pos = mul(proj_pos, g_mInvViewProj);
    float3 ray_dir = normalize(original_pos.xyz/original_pos.w - g_vEye);
    
    float curve_scale = 1;
    if(g_bThinTip >0 )
        curve_scale = In.Texcoord.z;
    
    float fiber_radius = curve_scale * g_FiberRadius;
	
	float coverage = 1.f;
	if(g_bUseCoverage)
	{	
		if(g_bUseAltCoverage)
			coverage = FastComputeCoverage(In.p0.xy, In.p1.xy, proj_pos.xy);
		else
			coverage = ComputeCoverage(g_vEye, ray_dir, In.p0, In.p1, winSizeEye, fiber_radius);
		
		vColor.w *= coverage;
	}

    /////////////////////////////////////////////////////////////////////////////
    // only store fragments with non-zero alpha value
    if(vColor.w > 0.99f/255.f) // ensure alpha is at least 1/255 with applied coverage
    {
        float4 projPosEye = mul(float4(In.WorldPos,1), g_mViewProj);
        float depthNDC = projPosEye.z / projPosEye.w;
        StoreFragments_Hair(In.Position.x, In.Position.y, depthNDC, vColor);
    }
    // output a mask RT for final pass    
    return float4(1, 0, 0, 0);
}

[earlydepthstencil]
float4 PS_DrawTopKEye_SelectBlend(VS_OUTPUT_SCREENQUAD In): SV_Target
{
    float4 fcolor = float4(0,0,0,1);

    // A local Array to store the top k fragments(depth and color)
    uint2 nodeList[MAX_TOP_LAYERS_EYE];

    [unroll]for(int t=0; t<MAX_TOP_LAYERS_EYE; t++)
        nodeList[t] = uint2(0xFFFFFFFF, 0x00000000);

    float2 winSizeEye = float2(g_WinSize.xy);
    uint x = In.vPosition.x;
    uint y = In.vPosition.y;
    uint linearAddress = winSizeEye.x * y + x;

    uint pointer = EyeRefSRV.Load(linearAddress);

    // Get the first MAX_TOP_LAYERS_EYE
    [unroll]for(int p=0; p<MAX_TOP_LAYERS_EYE; p++)
    {
        [flatten]if(pointer != 0xFFFFFFFF)
        {
            Eye_Fragment_STRUCT node = EyeFragmentSRV[pointer];
            nodeList[p] = uint2(node.uDepthAndCoverage, node.uPixelColor);
            pointer = node.uNext;
        }
    }

    // go through the rest linked list nodes, and keep the min 16 elements
    [allow_uav_condition]
    for(int l=0; l<MAX_FRAGMENT_LOOKUP_EYE; l++)
    {
        if(pointer == 0xFFFFFFFF)	break;

        Eye_Fragment_STRUCT node = EyeFragmentSRV[pointer];

        int id = 0;
        uint max_depth = 0;

        [unroll]for(int i=0; i<MAX_TOP_LAYERS_EYE; i++)
        {
            if(max_depth < nodeList[i].x)
            {
                max_depth = nodeList[i].x;
                id = i;
            }
        }

        uint uColor = node.uPixelColor;

        // exchange the local array with incoming node
        if(max_depth > node.uDepthAndCoverage)
        {
            uColor = nodeList[id].y;
            nodeList[id] = uint2(node.uDepthAndCoverage, node.uPixelColor);
        }

        // blend the non-min-k nodes out of order
        float4 color = UnpackUintIntoFloat4(uColor);
        fcolor.xyz = fcolor.xyz * (1-color.w) + color.xyz * color.w;
        fcolor.w *= 1-color.w;

        pointer = node.uNext;
    }

    /////////////////////////////////////////////////////////////////////////
    // Blend layers of color
    for(int j=0; j<MAX_TOP_LAYERS_EYE; j++)
    {
        int id = 0;
        uint max_depth = 0;

        [unroll]for(int i=0; i<MAX_TOP_LAYERS_EYE; i++)
        {
            if(max_depth < nodeList[i].x)
            {
                max_depth = nodeList[i].x;
                id = i;
            }
        }

        nodeList[id].x = 0x00000000;
        uint uColor = nodeList[id].y;

        float4 color = UnpackUintIntoFloat4(uColor);
        fcolor.xyz = fcolor.xyz * (1-color.w) + color.xyz * color.w;
        fcolor.w *= 1-color.w;
    }

    return fcolor;
}
