//--------------------------------------------------------------------------------------
// File: HairBasic.hlsl
//
// Hair rendering functions. 
// 
// Copyright © AMD Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#include "common.hlsl"
// calculate the pixel coverage of a fiber by computing ray fiber distance
float ComputeCoverage(float3 eye, float3 ray_dir, float3 p0, float3 p1, float2 winSizeEye, float fiber_radius)
{
    float pixel_coverage = 0;

    //find the common perpendicular of ray(direction: v0) and line(direction: v1) by cross product
    float3 nv0 = normalize(ray_dir);
    float3 nv1 = normalize(p1 - p0);

    // common perpendicular direction
    float3 norm = cross(nv0, nv1);
    float3 nnorm = normalize(norm);
    // sin value of the angle of ray and line
    float sin_v0_v1 = length(norm);
    
    // vector p0 - eye
    float3 eye_p0 = p0 - eye;

    // calculate the distance between ray and line by projecting any connecting line to common perpendicular
    float dis_lines = dot(eye_p0, nnorm);

    // move p0 along norm direction to p2
    float3 eye_p2 = eye_p0 - nnorm * dis_lines;
    float3 nv2 = normalize(eye_p2);

    // calculate angle between v2, v0
    float dis_eye_p2 = length(eye_p2);

    float sin_v1_mv2 = length(cross(nv1, -nv2));

    float depth = sin_v1_mv2 * dis_eye_p2/sin_v0_v1;
	
    // potaintial intersection
    if( depth>0 )
    {
        // calculate pixel size
        float lengthPerPixel = 2 * depth* tan(g_fvFov/2)/winSizeEye.y;

        float coverage_right = min(lengthPerPixel/2, dis_lines+fiber_radius);
        float coverage_left = max(-lengthPerPixel/2, dis_lines-fiber_radius);

        pixel_coverage = max(0, coverage_right - coverage_left)/lengthPerPixel;
    }
    
    return pixel_coverage;
}

float FastComputeCoverage(float2 p0, float2 p1, float2 pixelLoc)
{
	// p0, p1, pixelLoc are in d3d clip space (-1 to 1)x(-1 to 1)

	// Scale positions so 1.f = half pixel width
	p0 *= g_WinSize.xy;
	p1 *= g_WinSize.xy;
	pixelLoc *= g_WinSize.xy;

	float p0dist = length(p0 - pixelLoc);
	float p1dist = length(p1 - pixelLoc);
	float hairWidth = length(p0 - p1);

	// will be 1.f if pixel outside hair, 0.f if pixel inside hair
	float outside = any( float2(step(hairWidth, p0dist), step(hairWidth,p1dist)) );
	
	// if outside, set sign to -1, else set sign to 1
	float sign = outside > 0.f ? -1.f : 1.f;
	
	// signed distance (positive if inside hair, negative if outside hair)
	float relDist = sign * saturate( min(p0dist, p1dist) );
	
	// returns coverage based on the relative distance
	// 0, if completely outside hair edge
	// 1, if completely inside hair edge
	return (relDist + 1.f) * 0.5f;
}

VS_OUTPUT_SM VS_GenerateHairSM( VS_INPUT_Hair input )
{
    VS_OUTPUT_SM Output;
    
    float4 pos = g_GuideHairVertexPositions[input.id];

    // Transform the position from object space to homogeneous projection space
    Output.Position = mul( float4(pos.xyz, 1), g_mViewProjLight );
    
    Output.WorldPos = pos.xyz;
    
    return Output;    
}

////////////////////////////////////////////////////////////////////////////////
//
static const uint  HairVertexSelection[] = {   0,    1,   0,    1,   1,   0};
static const float OffsetDirection[]     = {-1.f, -1.f, 1.f, -1.f, 1.f, 1.f};
static const uint OffsetDirectionIndex[] = {0, 0, 1, 0, 1, 1};
#define GENERATED_VERTEX_COUNT (6)
PS_INPUT_HAIR_AA VS_RenderHairNoGS( uint vertexId : SV_VertexID )
{
    //depends upon integer arith.
    uint offset = 2 * (vertexId / GENERATED_VERTEX_COUNT);

    //access the current line segment
    uint2 indices;
    indices.x = g_HairIndices.Load(offset);
    indices.y = g_HairIndices.Load(offset + 1);

    //compute desired thickness
    float ratio[] = { 1.f, 1.f };

    if( g_bThinTip > 0 )
    {
        ratio[0] = g_HairThicknessCoeffs[indices.x];
        ratio[1] = g_HairThicknessCoeffs[indices.y];
    }

    //get updated positions and tangents from simulation result
    float3 t[]          = { normalize(g_GuideHairVertexTangents[indices.x].xyz), normalize(g_GuideHairVertexTangents[indices.y].xyz) };
    float3 v[]          = { g_GuideHairVertexPositions[indices.x].xyz, g_GuideHairVertexPositions[indices.y].xyz };
    float3 right[]      = { normalize(cross(t[0], normalize(v[0] - g_vEye))), normalize(cross(t[1], normalize(v[1] - g_vEye)))};
    float2 proj_right[] = { normalize( mul(float4(right[0], 0), g_mViewProj).xy ), normalize( mul(float4(right[1], 0), g_mViewProj).xy ) };

    float expandPixels = .71f;
    if (g_bExpandPixels < 0 )
        expandPixels = 0.f;

    PS_INPUT_HAIR_AA Output = (PS_INPUT_HAIR_AA)0;

    //Look up the correct data for the newly created vertex
    uint localVertId = vertexId % GENERATED_VERTEX_COUNT;
    uint idx         = HairVertexSelection[localVertId];
    float offDirCoef = OffsetDirection[localVertId];

    float3 temp     = v[idx] +  offDirCoef * right[idx] * ratio[idx] * g_FiberRadius;
    Output.Position = mul(float4(temp, 1.f), g_mViewProj);
    Output.Position = (Output.Position/Output.Position.w) + offDirCoef * float4(proj_right[idx] * expandPixels/ g_WinSize.y, 0.f, 0.f);
    Output.Texcoord = float4(0.f, 0.f, ratio[idx], 0.f);
    Output.Tangent  = t[idx];
    Output.WorldPos = v[idx];
    Output.p0       = v[0];
    Output.p1       = v[1];

    return Output;
}

PS_INPUT_HAIR_AA VS_RenderHairNoGS_StrandCopies( uint vertexId : SV_VertexID )
{
	uint RANDOMIZED_GENERATED_VERTEX_COUNT = GENERATED_VERTEX_COUNT * g_iStrandCopies;

    //depends upon integer arith.
    uint offset = 2 * (vertexId / RANDOMIZED_GENERATED_VERTEX_COUNT);
	
	//identifies which copy of the strand this is (0 is the original, 1 is the first copy, etc.)
	uint randOffsetIndex = (vertexId % RANDOMIZED_GENERATED_VERTEX_COUNT) / GENERATED_VERTEX_COUNT;
	
	//Getting a random offset value
	uint seedRand = ((offset / 64 + 1) * (randOffsetIndex + 1)) % 512;
	float2 seedTexcorrd = float2( float(seedRand % 512), float(seedRand / 512) ) * (1.f/512.f);
	float3 randOffset = float3(0,0,0);
	randOffset = float(randOffsetIndex) * g_txNoise.SampleLevel(g_samLinearWrap, seedTexcorrd, 0).xyz;
	randOffset = 2.f * randOffset - 1.f; // so we have random offsets between -1 and 1

    //access the current line segment
    uint2 indices;
    indices.x = g_HairIndices.Load(offset);
    indices.y = g_HairIndices.Load(offset + 1);

    //compute desired thickness
    float ratio[] = { 1.f, 1.f };

    if( g_bThinTip > 0 )
    {
        ratio[0] = g_HairThicknessCoeffs[indices.x];
        ratio[1] = g_HairThicknessCoeffs[indices.y];
    }

    //get updated positions and tangents from simulation result
    float3 t[]          = { normalize(g_GuideHairVertexTangents[indices.x].xyz), normalize(g_GuideHairVertexTangents[indices.y].xyz) };
    float3 v[]          = { randOffset+g_GuideHairVertexPositions[indices.x].xyz, randOffset+g_GuideHairVertexPositions[indices.y].xyz };
    float3 right[]      = { normalize(cross(t[0], normalize(v[0] - g_vEye))), normalize(cross(t[1], normalize(v[1] - g_vEye)))};
    float2 proj_right[] = { normalize( mul(float4(right[0], 0), g_mViewProj).xy ), normalize( mul(float4(right[1], 0), g_mViewProj).xy ) };

    float expandPixels = .71f;
    if (g_bExpandPixels < 0 )
        expandPixels = 0.f;

    PS_INPUT_HAIR_AA Output = (PS_INPUT_HAIR_AA)0;

    //Look up the correct data for the newly created vertex
    uint localVertId = vertexId % GENERATED_VERTEX_COUNT;
    uint idx         = HairVertexSelection[localVertId];
    float offDirCoef = OffsetDirection[localVertId];

    float3 temp     = v[idx] +  offDirCoef * right[idx] * ratio[idx] * g_FiberRadius;
    Output.Position = mul(float4(temp, 1.f), g_mViewProj);
    Output.Position = (Output.Position/Output.Position.w) + offDirCoef * float4(proj_right[idx] * expandPixels/ g_WinSize.y, 0.f, 0.f);
    Output.Texcoord = float4(0.f, 0.f, ratio[idx], 0.f);
    Output.Tangent  = t[idx];
    Output.WorldPos = v[idx];
    Output.p0       = v[0];
    Output.p1       = v[1];

    return Output;
}

PS_INPUT_HAIR_AA VS_RenderHairNoGS_AlternativeCoverage( uint vertexId : SV_VertexID )
{
    //depends upon integer arith.
    uint offset = 2 * (vertexId / GENERATED_VERTEX_COUNT);

    //access the current line segment
    uint2 indices;
    indices.x = g_HairIndices.Load(offset);
    indices.y = g_HairIndices.Load(offset + 1);

    //compute desired thickness
    float ratio[] = { 1.f, 1.f };

    if( g_bThinTip > 0 )
    {
        ratio[0] = g_HairThicknessCoeffs[indices.x];
        ratio[1] = g_HairThicknessCoeffs[indices.y];
    }

    //get updated positions and tangents from simulation result
    float3 t[]          = { normalize(g_GuideHairVertexTangents[indices.x].xyz), normalize(g_GuideHairVertexTangents[indices.y].xyz) };
    float3 v[]          = { g_GuideHairVertexPositions[indices.x].xyz, g_GuideHairVertexPositions[indices.y].xyz };
    float3 right[]      = { normalize(cross(t[0], normalize(v[0] - g_vEye))), normalize(cross(t[1], normalize(v[1] - g_vEye)))};
    float2 proj_right[] = { normalize( mul(float4(right[0], 0), g_mViewProj).xy ), normalize( mul(float4(right[1], 0), g_mViewProj).xy ) };

    float expandPixels = .71f;
    if (g_bExpandPixels < 0 )
        expandPixels = 0.f;

    PS_INPUT_HAIR_AA Output = (PS_INPUT_HAIR_AA)0;

    //Look up the correct data for the newly created vertex
    uint localVertId = vertexId % GENERATED_VERTEX_COUNT;
    uint idx         = HairVertexSelection[localVertId];
	uint offDirIndex = OffsetDirectionIndex[localVertId];

	// calculate the negative and positive offset screenspace positions
	float4 hairEdgePositions[2]; // 0 is negative, 1 is positive
	hairEdgePositions[0] = float4(v[idx] +  -1.f * right[idx] * ratio[idx] * g_FiberRadius, 1.f);
	hairEdgePositions[1] = float4(v[idx] +   1.f * right[idx] * ratio[idx] * g_FiberRadius, 1.f);
	hairEdgePositions[0] = mul(hairEdgePositions[0], g_mViewProj);
	hairEdgePositions[1] = mul(hairEdgePositions[1], g_mViewProj);
	hairEdgePositions[0] = hairEdgePositions[0]/hairEdgePositions[0].w;
	hairEdgePositions[1] = hairEdgePositions[1]/hairEdgePositions[1].w;

	Output.Position = hairEdgePositions[offDirIndex] + OffsetDirection[localVertId] * float4(proj_right[idx] * expandPixels / g_WinSize.y, 0.0f, 0.0f);
    Output.Texcoord = float4(0.f, 0.f, ratio[idx], 0.f);
    Output.Tangent  = t[idx];
    Output.WorldPos = v[idx];
    Output.p0       = hairEdgePositions[0].xyz;
    Output.p1       = hairEdgePositions[1].xyz;

    return Output;
}

PS_INPUT_HAIR_AA VS_RenderHairNoGS_AlternativeCoverage_StrandCopies( uint vertexId : SV_VertexID )
{
	uint RANDOMIZED_GENERATED_VERTEX_COUNT = GENERATED_VERTEX_COUNT * g_iStrandCopies;

    //depends upon integer arith.
    uint offset = 2 * (vertexId / RANDOMIZED_GENERATED_VERTEX_COUNT);
	
	//identifies which copy of the strand this is (0 is the original, 1 is the first copy, etc.)
	uint randOffsetIndex = (vertexId % RANDOMIZED_GENERATED_VERTEX_COUNT) / GENERATED_VERTEX_COUNT;
	
	//Getting a random offset value
	uint seedRand = ((offset / 64 + 1) * (randOffsetIndex + 1)) % 512;
	float2 seedTexcorrd = float2( float(seedRand % 512), float(seedRand / 512) ) * (1.f/512.f);
	float3 randOffset = float3(0,0,0);
	randOffset = float(randOffsetIndex) * g_txNoise.SampleLevel(g_samLinearWrap, seedTexcorrd, 0).xyz;
	randOffset = 2.f * randOffset - 1.f; // so we have random offsets between -1 and 1

    //access the current line segment
    uint2 indices;
    indices.x = g_HairIndices.Load(offset);
    indices.y = g_HairIndices.Load(offset + 1);

    //compute desired thickness
    float ratio[] = { 1.f, 1.f };

    if( g_bThinTip > 0 )
    {
        ratio[0] = g_HairThicknessCoeffs[indices.x];
        ratio[1] = g_HairThicknessCoeffs[indices.y];
    }

    //get updated positions and tangents from simulation result
    float3 t[]          = { normalize(g_GuideHairVertexTangents[indices.x].xyz), normalize(g_GuideHairVertexTangents[indices.y].xyz) };
    float3 v[]          = { randOffset+g_GuideHairVertexPositions[indices.x].xyz, randOffset+g_GuideHairVertexPositions[indices.y].xyz };
    float3 right[]      = { normalize(cross(t[0], normalize(v[0] - g_vEye))), normalize(cross(t[1], normalize(v[1] - g_vEye)))};
    float2 proj_right[] = { normalize( mul(float4(right[0], 0), g_mViewProj).xy ), normalize( mul(float4(right[1], 0), g_mViewProj).xy ) };

    float expandPixels = .71f;
    if (g_bExpandPixels < 0 )
        expandPixels = 0.f;

    PS_INPUT_HAIR_AA Output = (PS_INPUT_HAIR_AA)0;

    //Look up the correct data for the newly created vertex
    uint localVertId = vertexId % GENERATED_VERTEX_COUNT;
    uint idx         = HairVertexSelection[localVertId];
	uint offDirIndex = OffsetDirectionIndex[localVertId];

	// calculate the negative and positive offset screenspace positions
	float4 hairEdgePositions[2]; // 0 is negative, 1 is positive
	hairEdgePositions[0] = float4(v[idx] +  -1.f * right[idx] * ratio[idx] * g_FiberRadius, 1.f);
	hairEdgePositions[1] = float4(v[idx] +   1.f * right[idx] * ratio[idx] * g_FiberRadius, 1.f);
	hairEdgePositions[0] = mul(hairEdgePositions[0], g_mViewProj);
	hairEdgePositions[1] = mul(hairEdgePositions[1], g_mViewProj);
	hairEdgePositions[0] = hairEdgePositions[0]/hairEdgePositions[0].w;
	hairEdgePositions[1] = hairEdgePositions[1]/hairEdgePositions[1].w;
	
	Output.Position = hairEdgePositions[offDirIndex] + OffsetDirection[localVertId] * float4(proj_right[idx] * expandPixels / g_WinSize.y, 0.0f, 0.0f);
    Output.Texcoord = float4(0.f, 0.f, ratio[idx], 0.f);
    Output.Tangent  = t[idx];
    Output.WorldPos = v[idx];
    Output.p0       = hairEdgePositions[0].xyz;
    Output.p1       = hairEdgePositions[1].xyz;

    return Output;
}

float4 HairColor(float4 iTex, float amountLight)
{
    float4 baseColor =  g_MatBaseColor; // better: read from a texture that has varying color
    baseColor.xyz = saturate(baseColor.xyz);
    baseColor.xyz*= amountLight;
    return baseColor;
}

//////////////////////////////////////////////////////////////////////////////////////////
// hair shading using dual highlight approach and kajiya lighting model
// dual highlight: marschner 03 
// kajiya model: kajiya 84
/////////////////////////////////////////////////////////////////////////////////////////
float4 KajiyaShading(float3 iPos, float3 iTangent, float4 iTex, float amountLight)
{
    float4 baseColor = HairColor(iTex, 1);
    float4 rand_value = float4(1,1,1,1);
    
    if(abs(iTex.x) + abs(iTex.y) >1e-5) // if texcoord is available, use texture map
        rand_value = g_txNoise.SampleLevel(g_samLinearWrap, iTex.xy, 0);
    
    // define baseColor and Ka Kd Ks coefficient for hair
    float Ka = g_MatKValue.x, Kd = g_MatKValue.y, 
          Ks1 = g_MatKValue.z, Ex1 = g_MatKValue.w,
          Ks2 = g_fHairKs2, Ex2 = g_fHairEx2;

    float3 lightPos = g_PointLightPos.xyz;
    float3 vLightDir = normalize(lightPos - iPos.xyz);
    float3 vEyeDir = normalize(g_vEye.xyz - iPos.xyz);
    float3 tangent = normalize(iTangent);

    // in Kajiya's model: diffuse component: sin(t, l)
    float cosTL = (dot(tangent, vLightDir));
    float sinTL = sqrt(1 - cosTL*cosTL);
    float vDiffuse = sinTL; // here sinTL is apparently larger than 0

    float alpha = (rand_value.x*10)*PI/180; // tiled angle (5-10 dgree)

    // in Kajiya's model: specular component: cos(t, rl)*cos(t, e) + sin(t, rl)sin(t, e)
    float cosTRL = -cosTL;
    float sinTRL = sinTL;
    float cosTE = (dot(tangent, vEyeDir));
    float sinTE = sqrt(1- cosTE*cosTE);

    // primary highlight: reflected direction shift towards root (2*Alpha)
    float cosTRL_r = cosTRL*cos(2*alpha) - sinTRL*sin(2*alpha);
    float sinTRL_r = sqrt(1 - cosTRL_r*cosTRL_r);
    float vSpecular_r = max(0, cosTRL_r*cosTE + sinTRL_r*sinTE);

    // secondary highlight: reflected direction shifted toward tip (3*Alpha)
    float cosTRL_trt = cosTRL*cos(-3*alpha) - sinTRL*sin(-3*alpha);
    float sinTRL_trt = sqrt(1 - cosTRL_trt*cosTRL_trt);
    float vSpecular_trt = max(0, cosTRL_trt*cosTE + sinTRL_trt*sinTE);
    
    float4 vColor = Ka * g_AmbientLightColor * baseColor + // ambient
                    amountLight * g_PointLightColor * (
                    Kd * vDiffuse* baseColor + // diffuse
                    Ks1 * pow(vSpecular_r, Ex1)  + // primary hightlight r
                    Ks2 * pow(vSpecular_trt, Ex2) * baseColor); // secondary highlight rtr 
    
    return vColor;
}

float4 ComputeHairShading(float3 iPos, float3 iTangent, 
                    float4 iTex, float amountLight)
{
    return KajiyaShading(iPos, iTangent, iTex, amountLight);
}