//--------------------------------------------------------------------------------------
// File: shader_include.hlsl
//
// Include file for common shader definitions and functions.
//
// Copyright © AMD Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
// Defines
//--------------------------------------------------------------------------------------                  
#define ADD_SPECULAR 0
                                          
//--------------------------------------------------------------------------------------
// Textures
//--------------------------------------------------------------------------------------
Texture2D g_txDiffuse      : register( t0 );   // Diffuse color texture
Texture2D g_txNormalHeight : register( t1 );   // Normal map and height map texture pair
Texture2D g_txSpecular     : register( t2 );   // Specular texture
Texture2D g_txDensity      : register( t3 );   // Density texture (only used for debug purposes)

Texture2D g_txHiZ          : register( t4 );   // HiZ texture


//--------------------------------------------------------------------------------------
// Samplers
//--------------------------------------------------------------------------------------
SamplerState g_samLinear      : register( s0 );
SamplerState g_samPoint       : register( s1 );
SamplerState g_samAnisotropic : register( s2 );


//--------------------------------------------------------------------------------------
// Constant Buffers
//--------------------------------------------------------------------------------------
cbuffer cbMain : register( b0 )
{
    // Matrices
	matrix g_mView;                             // View matrix
	matrix g_mProjection;                       // Projection matrix
    matrix g_mViewProjection;                   // VP matrix
    matrix g_mInvView;                          // Inverse of view matrix
    matrix g_mInvViewProjectionViewport;        // Inverse of viewprojectionviewport matrix
	matrix g_mWorld;                            // World matrix
    
    // Camera
    float4 g_vEye;					    	    // Camera's location
	float4 g_vCameraViewVector;                 // Camera's view vector
    
    // Frustum
    float4 g_vScreenResolution;                 // Screen resolution
    
    // Light
    float4 g_vLightPosition;                 	// Light's position in world space, plus light's max radius in .w
	float4 g_vLightDiffuse;                  	// Light's diffuse color
	float4 g_vLightAmbient;                  	// Light's ambient color

	// visualization
	float g_ShowDiscardedPixels;				// visualization to show discarded pixels
};
