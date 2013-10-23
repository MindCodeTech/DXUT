//--------------------------------------------------------------------------------------
// File: shadow.hlsl
//
// Shaders for generating and rendering shadows
// 
// Copyright © AMD Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#define SM_EPSLON 0.01
#define kernel_size 3

struct INPUT_SHADOW
{
	float3 pos;
};

struct AmountLight
{
	float amountLight_scene;
	float amountLight_hair;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////
// render with shadow effects
////////////////////////////////////////////////////////////////////////////////////////////////////////

// Simplified deep shadow map
AmountLight ComputeShadow_SDSM(INPUT_SHADOW input, float alpha)
{
	float4 projPosLight = mul(float4(input.pos,1), g_mViewProjLight);
    float2 texSM = float2(projPosLight.x/projPosLight.w+1, -projPosLight.y/projPosLight.w+1)*0.5;
	float depth = projPosLight.z/projPosLight.w;
	float epslon = depth * SM_EPSLON;
	float depth_fragment = projPosLight.w;

	// for shadow casted by scene objs, use PCF shadow
	float total_weight = 0;
	AmountLight amountLight;
	amountLight.amountLight_hair = 0;
	amountLight.amountLight_scene =0;
	
	[unroll] for (int dx = (1-kernel_size)/2; dx <= kernel_size/2; dx++) 
	{ 
		[unroll] for (int dy = (1-kernel_size)/2; dy <= kernel_size/2; dy++) 
		{ 
			float size = 2.4;
			float sigma = (kernel_size/2.0)/size; // standard deviation, when kernel/2 > 3*sigma, it's close to zero, here we use 1.5 instead
			float exp = -1* (dx*dx + dy*dy)/ (2* sigma * sigma);
			float weight = 1/(2*PI*sigma*sigma) * pow(e, exp);

			// shadow casted by scene object: pcf shadow
			amountLight.amountLight_scene += weight * g_txSMScene.SampleCmpLevelZero(g_samShadow, texSM, depth-epslon, int2(dx, dy));

			// shadow casted by hair: simplified deep shadow map
			float depthSMHair = g_txSMHair.SampleLevel( g_samPointClamp, texSM, 0, int2(dx, dy) ).x; //z/w

			float depth_smPoint = g_fNearLight/(1 - depthSMHair*(g_fFarLight - g_fNearLight)/g_fFarLight);

			float depth_range = max(0, depth_fragment-depth_smPoint); 
			float numFibers =  depth_range/(g_FiberSpacing*g_FiberRadius);

			// if occluded by hair, there is at least one fiber
			if(depth_range > 1e-5)
				numFibers += 1;
			amountLight.amountLight_hair += pow(abs(1-alpha), numFibers)*weight;

			total_weight += weight;
		}
	}
	amountLight.amountLight_hair /= total_weight;
	amountLight.amountLight_scene /= total_weight;
	return amountLight;
}

AmountLight ComputeShadow(INPUT_SHADOW input, float alpha, int iTechSM)
{
	AmountLight amountLight;
	amountLight.amountLight_hair = 1;
	amountLight.amountLight_scene = 1;

	if( iTechSM == SHADOW_SDSM )
		amountLight = ComputeShadow_SDSM(input, alpha);

	return amountLight;
}
