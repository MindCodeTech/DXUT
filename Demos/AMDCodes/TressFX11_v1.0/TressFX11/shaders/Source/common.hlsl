//--------------------------------------------------------------------------------------
// File: common.hlsl
//
// Include file for TressFX shaders. 
// 
// Copyright © AMD Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#define MAX_24BIT_UINT  ( (1<<24) - 1 )

#define MAX_TOP_LAYERS_EYE	8

#define MAX_FRAGMENT_LOOKUP_EYE 768

#define PI 3.1415926
#define e 2.71828183

// techniques: has to match the define in cpp
#define SHADOW_SDSM		2

//--------------------------------------------------------------------------------------
// Helper functions
//--------------------------------------------------------------------------------------
uint PackFloat4IntoUint(float4 vValue)
{
    return ( (uint(vValue.x*255)& 0xFFUL) << 24 ) | ( (uint(vValue.y*255)& 0xFFUL) << 16 ) | ( (uint(vValue.z*255)& 0xFFUL) << 8) | (uint(vValue.w * 255)& 0xFFUL);
}

float4 UnpackUintIntoFloat4(uint uValue)
{
    return float4( ( (uValue & 0xFF000000)>>24 ) / 255.0, ( (uValue & 0x00FF0000)>>16 ) / 255.0, ( (uValue & 0x0000FF00)>>8 ) / 255.0, ( (uValue & 0x000000FF) ) / 255.0);
}

// Pack depth into 24 MSBs
uint PackDepthIntoUint(float fDepth)
{
    return ((uint)(fDepth * MAX_24BIT_UINT)) << 8;
}

//--------------------------------------------------------------------------------------
// Constant Buffers
//--------------------------------------------------------------------------------------

cbuffer cbPerFrame : register( b0 )
{
    matrix		g_mWorld			: packoffset( c0  );
    matrix		g_mViewProj			: packoffset( c4  );
	matrix		g_mInvViewProj		: packoffset( c8  );
    matrix		g_mViewProjLight	: packoffset( c12 );

    float3		g_vEye				: packoffset( c16 );
	float		g_fvFov				: packoffset( c16.w );

    float4      g_AmbientLightColor : packoffset( c17 );
    float4		g_PointLightColor	: packoffset( c18 );
    float4		g_PointLightPos		: packoffset( c19 );
    float4		g_MatBaseColor		: packoffset( c20 );
    float4		g_MatKValue			: packoffset( c21 ); // Ka, Kd, Ks, Ex
    
    float		g_FiberAlpha		: packoffset( c22.x );
    float		g_HairShadowAlpha	: packoffset( c22.y );
    float		g_bExpandPixels		: packoffset( c22.z );
    float		g_FiberRadius		: packoffset( c22.w );

    float		g_fHairKs2			: packoffset( c23.x ); // for second highlight
    float		g_fHairEx2			: packoffset( c23.y ); // for second highlight
    float2		g_WinSize			: packoffset( c23.z ); // screen size
    
    float		g_FiberSpacing		: packoffset( c24.x ); // average spacing between fibers
    float		g_bThinTip			: packoffset( c24.y );
    float		g_fNearLight		: packoffset( c24.z );
    float		g_fFarLight			: packoffset( c24.w );
    
    int			g_iTechSM			: packoffset( c25.x );
    int			g_bUseCoverage		: packoffset( c25.y );
	int			g_bUseAltCoverage	: packoffset( c25.z );
	int			g_iStrandCopies		: packoffset( c25.w ); // strand copies that the transparency shader will produce
};

cbuffer cbPerMaterial : register( b1 )
{
    float4		g_MatAmbient	: packoffset( c0 );
    float4		g_MatDiffuse	: packoffset( c1 ); 
    float4		g_MatSpecular	: packoffset( c2 );
    float4		g_ScalpColor	: packoffset( c3 );
};

struct Eye_Fragment_STRUCT
{
    uint    uPixelColor;
    uint    uDepthAndCoverage;       // Coverage is only used in the MSAA case
    uint    uNext;
};

struct Eye_Node_STRUCT
{
    uint next;
    uint uColor;
    uint uDepth;
};

struct HAIR_VERTEX
{
    float3 pos;
    float3 tangent;
    float4 texcoord;
};


//--------------------------------------------------------------------------------------
// SRV buffers
//--------------------------------------------------------------------------------------
Buffer<uint>							EyeRefSRV					: register(t0);
StructuredBuffer<Eye_Fragment_STRUCT>	EyeFragmentSRV				: register(t1);

Texture2D								g_txSMScene					: register( t2 );
Texture2D								g_txSMHair					: register( t3 );
Texture2D								g_txObj						: register( t4 );
Texture2D								g_txNoise					: register( t5 );

Buffer<uint>							g_HairIndices               : register( t6 );
Buffer<float>							g_HairThicknessCoeffs       : register( t7 );

StructuredBuffer<float4>				g_GuideHairVertexPositions	: register( t8 );
StructuredBuffer<float4>				g_GuideHairVertexTangents	: register( t9 );

//--------------------------------------------------------------------------------------
// Samplers
//--------------------------------------------------------------------------------------
SamplerState							g_samLinearWrap				: register( s0 );
SamplerState							g_samPointClamp				: register( s1 );
SamplerComparisonState					g_samShadow					: register( s2 );

//--------------------------------------------------------------------------------------
// UAVs
//--------------------------------------------------------------------------------------
RWByteAddressBuffer						EyeRefUAV					: register(u1); // store linked list head
RWStructuredBuffer<Eye_Fragment_STRUCT>	EyeFragmentUAV				: register(u2); // store fragment linked list

//--------------------------------------------------------------------------------------
// shader input/output structure
//--------------------------------------------------------------------------------------
struct VS_INPUT_SCENE
{
    float3 Position     : POSITION;		// vertex position 
    float3 Normal       : NORMAL;		// this normal comes in per-vertex
    float2 Texcoord	    : TEXCOORD0;	// vertex texture coords 
};

struct VS_INPUT_Hair
{
    float3 Position     : POSITION;		// vertex position 
    float3 Tangent      : TANGENT;		// this normal comes in per-vertex
    float4 Texcoord		: TEXCOORD0;	// vertex texture coords 
    uint   id			: SV_VERTEXID;
};

struct PS_INPUT_HAIR_AA
{
    float4 Position	: SV_POSITION;
    float3 Tangent	: Tangent;
    float4 Texcoord	: TEXCOORD0;
    float3 WorldPos	: TEXCOORD1;
    float3 p0		: TEXCOORD2;
    float3 p1		: TEXCOORD3;
};

struct VS_OUTPUT_SM
{
    float4 Position     : SV_POSITION; // vertex position
    float3 WorldPos		: TEXCOORD0;
};


///////////////////////////////////////////////////////////////////////////////////////////
// Screen quad
//////////////////////////////////////////////////////////////////////////////////////////
struct VS_OUTPUT_SCREENQUAD
{
    float4 vPosition : SV_POSITION;
    float2 vTex      : TEXCOORD;
};


// A compute or pixel shader takes the StartOffsetBuffer as input and write the color to final hair RT
VS_OUTPUT_SCREENQUAD VS_ScreenQuad(VS_INPUT_SCENE input)
{
    VS_OUTPUT_SCREENQUAD output;

    output.vPosition = float4(input.Position.xyz, 1.0);
    output.vTex = input.Texcoord.xy;

    return output;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
struct VS_OUTPUT_SCENE
{
    float4 Position     : SV_POSITION; // vertex position
    float3 Normal		: TEXCOORD0;
    float2 Texcoord	    : TEXCOORD1;   // vertex texture coords 
    float3 WorldPos	    : TEXCOORD2;
};

#include "shadow.hlsl"