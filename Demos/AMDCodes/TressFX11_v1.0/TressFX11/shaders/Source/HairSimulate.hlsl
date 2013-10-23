//--------------------------------------------------------------------------------------
// File: HairSimulate.hlsl
//
// Physics simulation of hair using compute shaders 
// 
// Copyright © AMD Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

//constants that change frame to frame
cbuffer ConstBufferCS_Per_Frame : register( b0 )
{
    row_major float4x4 g_ModelTransformForHead;
    row_major float4x4 g_ModelPrevInvTransformForHead;

    float4 g_ModelRotateForHead; // quaternion

	float4 g_Wind;
	float4 g_Wind1;
	float4 g_Wind2;
	float4 g_Wind3;

    int g_NumLengthConstraintIterations;
    int g_bCollision;

    float g_GravityMagnitude;
    float g_TimeStep;
        
    // top
    float g_Damping0;
    float g_StiffnessForLocalShapeMatching0;
    float g_StiffnessForGlobalShapeMatching0;
    float g_GlobalShapeMatchingEffectiveRange0;
    
    // back
    float g_Damping1;
    float g_StiffnessForLocalShapeMatching1;
    float g_StiffnessForGlobalShapeMatching1;
    float g_GlobalShapeMatchingEffectiveRange1;

    // ponytail
    float g_Damping2;
    float g_StiffnessForLocalShapeMatching2;
    float g_StiffnessForGlobalShapeMatching2;
    float g_GlobalShapeMatchingEffectiveRange2;
    
    // front long
    float g_Damping3;
    float g_StiffnessForLocalShapeMatching3;
    float g_StiffnessForGlobalShapeMatching3;	
    float g_GlobalShapeMatchingEffectiveRange3;
}

RWStructuredBuffer<float4> g_GuideHairVertexPositions		: register(u0); 
RWStructuredBuffer<float4> g_GuideHairVertexPositionsPrev	: register(u1); 
RWStructuredBuffer<float4> g_GuideHairVertexTangents		: register(u2); 
RWStructuredBuffer<float4> g_InitialGuideHairPositions		: register(u3);
RWStructuredBuffer<float4> g_GlobalRotations				: register(u4); 
RWStructuredBuffer<float4> g_LocalRotations					: register(u5); 

Buffer<int>		g_GuideHairVerticesOffsetsSRV	: register(t0); 
Buffer<float>	g_GuideHairRestLengthSRV		: register(t1);
Buffer<int>		g_GuideHairStrandType			: register(t2); 
Buffer<float3>	g_GuideHairRefVecsInLocalFrame	: register(t3); 

#define GROUP_SIZE 64
groupshared float4 sharedPos[GROUP_SIZE];
groupshared float  sharedLength[GROUP_SIZE];
groupshared float4 sharedLocalRotation[GROUP_SIZE];

bool IsMovable(float4 particle)
{
    if ( particle.w > 0 )
        return true;
    return false;      
}

float2 ConstraintMultiplier(float4 particle0, float4 particle1)
{
    if (IsMovable(particle0)) 
    {
        if (IsMovable(particle1))
            return float2(0.5, 0.5);
        else
            return float2(1, 0);
    }
    else 
    {
        if (IsMovable(particle1))
            return float2(0, 1);
        else
            return float2(0, 0);
    }    
}

float4 MakeQuaternion(float angle_radian, float3 axis)
{
    // create quaternion using angle and rotation axis
    float4 quaternion;
    float halfAngle = 0.5f * angle_radian;
    float sinHalf = sin(halfAngle);

    quaternion.w = cos(halfAngle);
    quaternion.xyz = sinHalf * axis.xyz;

    return quaternion;
}

float4 InverseQuaternion(float4 q)
{
    float lengthSqr = q.x*q.x + q.y*q.y + q.z*q.z + q.w*q.w;

    if ( lengthSqr < 0.001 )
        return float4(0, 0, 0, 1.0f);

    q.x = -q.x / lengthSqr;
    q.y = -q.y / lengthSqr;
    q.z = -q.z / lengthSqr;
    q.w = q.w / lengthSqr;

    return q;
}

float3 MultQuaternionAndVector(float4 q, float3 v)
{
    float3 uv, uuv;
    float3 qvec = float3(q.x, q.y, q.z);
    uv = cross(qvec, v);
    uuv = cross(qvec, uv);
    uv *= (2.0f * q.w);
    uuv *= 2.0f;

    return v + uv + uuv;
}

float4 MultQuaternionAndQuaternion(float4 qA, float4 qB)
{
    float4 q;

    q.w = qA.w * qB.w - qA.x * qB.x - qA.y * qB.y - qA.z * qB.z;
    q.x = qA.w * qB.x + qA.x * qB.w + qA.y * qB.z - qA.z * qB.y;
    q.y = qA.w * qB.y + qA.y * qB.w + qA.z * qB.x - qA.x * qB.z;
    q.z = qA.w * qB.z + qA.z * qB.w + qA.x * qB.y - qA.y * qB.x;
    
    return q;
}

void ApplyDistanceConstraint(inout float4 pos0, inout float4 pos1, float targetDistance, float stiffness = 1.0)
{
    float3 delta = pos1.xyz - pos0.xyz;
    float distance = max(length(delta), 1e-7);
    float stretching = 1 - targetDistance / distance;
    delta = stretching * delta;
    float2 multiplier = ConstraintMultiplier(pos0, pos1);
    
    pos0.xyz += multiplier[0] * delta * stiffness;
    pos1.xyz -= multiplier[1] * delta * stiffness;
}

float4 Integrate(float4 curPosition, float4 oldPosition, float4 initialPos, float4 force, int globalVertexIndex, int localVertexIndex, int numVerticesInTheStrand, float dampingCoeff = 1.0f)
{  
    float4 outputPos = curPosition;

    force.xyz += g_GravityMagnitude * float3(0, -1.0f, 0);
    outputPos.xyz = curPosition.xyz + (1.0 - dampingCoeff)*(curPosition.xyz - oldPosition.xyz) + force.xyz*g_TimeStep*g_TimeStep; 
    
    return outputPos;  
}

struct CollisionCapsule
{
	float4 p1; // xyz = position 1 of capsule, w = radius
	float4 p2; // xyz = position 2 of capsule, w = radius * radius
};

float3 CapsuleCollision(float4 curPosition, float4 oldPosition, CollisionCapsule cc, float friction = 0.4f)
{
	float3 newPos = curPosition.xyz;
	const float radius = cc.p1.w;
	const float radius2 = cc.p2.w;
		
	if ( !IsMovable(curPosition) )
		return newPos;
			
	float3 segment = cc.p2.xyz - cc.p1.xyz;
	float3 delta1 = curPosition.xyz - cc.p1.xyz;
	float3 delta2 = cc.p2.xyz - curPosition.xyz;
		
	float dist1 = dot(delta1, segment);
	float dist2 = dot(delta2, segment);
		
	// colliding with sphere 1
	if ( dist1 < 0.f )
	{
		if ( dot(delta1, delta1) < radius2 )
		{
			float3 n = normalize(delta1);
			newPos = radius * n + cc.p1.xyz;
		}
		return newPos;
	}
		
	// colliding with sphere 2
	if ( dist2 < 0.f )
	{
		if ( dot(delta2, delta2) < radius2 )
		{
			float3 n = normalize(-delta2);
			newPos = radius * n + cc.p2.xyz;
		}
		return newPos;
	}
		
	// colliding with middle cylinder
	float3 x = (dist1 * cc.p2.xyz + dist2 * cc.p1.xyz) / (dist1 + dist2);
	float3 delta = curPosition.xyz - x;
		
	if ( dot(delta, delta) < radius2 )
	{
		float3 n = normalize(delta);
		float3 vec = curPosition.xyz - oldPosition.xyz;
		float3 segN = normalize(segment);
		float3 vecTangent = dot(vec, segN) * segN;
		float3 vecNormal = vec - vecTangent;
		newPos.xyz = oldPosition.xyz + friction * vecTangent + (vecNormal + radius * n - delta);
	}
	return newPos;
}

void UpdateFinalVertexPositions(float4 oldPosition, float4 newPosition, int globalVertexIndex, int localVertexIndex, int numVerticesInTheStrand)
{ 
	if ( localVertexIndex < numVerticesInTheStrand )
	{
		g_GuideHairVertexPositionsPrev[globalVertexIndex] = oldPosition;        
		g_GuideHairVertexPositions[globalVertexIndex] = newPosition;
	}        
}

// The number of vertices in each strand must be less than or equal to GROUP_SIZE because each thread group computes one strand. 
[numthreads(GROUP_SIZE, 1, 1)]
void SkipSimulateHair(uint GIndex : SV_GroupIndex,
                  uint3 GId : SV_GroupID,
                  uint3 DTid : SV_DispatchThreadID)
{
    int offset = 0;
    int strandType = 0;

    uint globalStrandIndex = GId.x;

    if( globalStrandIndex > 0 ) 
    {
        offset =  g_GuideHairVerticesOffsetsSRV.Load(globalStrandIndex - 1);
    }

    uint numVerticesInTheStrand = g_GuideHairVerticesOffsetsSRV.Load(globalStrandIndex) - offset;
 
    uint localVertexIndex = GIndex;
    uint globalVertexIndex = offset + localVertexIndex;

	if (localVertexIndex >= numVerticesInTheStrand )
		return;

	float4 oldPosition = g_GuideHairVertexPositionsPrev[globalVertexIndex];
	float4 newPosition = g_GuideHairVertexPositions[globalVertexIndex];
	
	oldPosition.xyz = mul(float4( oldPosition.xyz, 1), g_ModelPrevInvTransformForHead).xyz;
	oldPosition.xyz = mul(float4( oldPosition.xyz, 1), g_ModelTransformForHead).xyz;
	
	newPosition.xyz = mul(float4( newPosition.xyz, 1), g_ModelPrevInvTransformForHead).xyz;
	newPosition.xyz = mul(float4( newPosition.xyz, 1), g_ModelTransformForHead).xyz;
	
	// Update final global position buffers
	UpdateFinalVertexPositions(oldPosition, newPosition, globalVertexIndex, localVertexIndex, numVerticesInTheStrand);
		
	return;
}

//------------------------------------------
// Integrate and global shape constraints
// One thread computes one vertex
//------------------------------------------
[numthreads(GROUP_SIZE, 1, 1)]
void SimulateHair_A(uint GIndex : SV_GroupIndex,
                  uint3 GId : SV_GroupID,
                  uint3 DTid : SV_DispatchThreadID)
{
    int offset = 0;
    int strandType = 0;

	uint globalStrandIndex = 0;
	uint localVertexIndex = 0; 
	uint indexForSharedMem = GIndex;
	uint numOfStrandsPerThreadGroup = 2;
	uint maxPossibleVertsInStrand = (GROUP_SIZE / numOfStrandsPerThreadGroup);

	if ( GIndex < maxPossibleVertsInStrand )
	{
		globalStrandIndex = 2 * GId.x;
		localVertexIndex = GIndex;
	}
	else
	{
		globalStrandIndex = 2 * GId.x + 1;
		localVertexIndex = GIndex - maxPossibleVertsInStrand;
	}
	
    if( globalStrandIndex > 0 ) 
    {
        offset =  g_GuideHairVerticesOffsetsSRV.Load(globalStrandIndex - 1);
        strandType = g_GuideHairStrandType.Load(globalStrandIndex - 1);
    }

	uint globalVertexIndex = offset + localVertexIndex;
    uint numVerticesInTheStrand = g_GuideHairVerticesOffsetsSRV.Load(globalStrandIndex) - offset;

	if ( numVerticesInTheStrand > maxPossibleVertsInStrand )
		numVerticesInTheStrand = maxPossibleVertsInStrand;

    float4 currentPos = float4(0, 0, 0, 0); // position when this step starts. In other words, a position from the last step. 
    float4 initialPos = float4(0, 0, 0, 0); // rest position

    //------------------------------
    // Copy data into shared memory
    //------------------------------
    if (localVertexIndex < numVerticesInTheStrand )
    {
        currentPos = sharedPos[indexForSharedMem] = g_GuideHairVertexPositions[globalVertexIndex];
        initialPos = g_InitialGuideHairPositions[globalVertexIndex];
        initialPos.xyz = mul(float4( initialPos.xyz, 1), g_ModelTransformForHead).xyz;

        sharedLength[indexForSharedMem] = g_GuideHairRestLengthSRV[globalVertexIndex]; 
        sharedLocalRotation[indexForSharedMem] = g_LocalRotations[globalVertexIndex];
    }
        
    GroupMemoryBarrierWithGroupSync();

    //-----------
    // Integrate
    //-----------
    if ( localVertexIndex < numVerticesInTheStrand )
    {  
        float dampingCoeff = 0;

        if ( strandType == 0 ) // top
            dampingCoeff = g_Damping0;
        else if ( strandType == 1 ) // back
            dampingCoeff = g_Damping1;
        else if ( strandType == 2 ) // ponytail
            dampingCoeff = g_Damping2;
        else if ( strandType == 3 ) // front long
            dampingCoeff = g_Damping3;

        float4 oldPos = g_GuideHairVertexPositionsPrev[globalVertexIndex];
        float4 force = float4(0, 0, 0, 0);

        if ( IsMovable(currentPos) )  
            sharedPos[indexForSharedMem] = Integrate(currentPos, oldPos, initialPos, force, globalVertexIndex, localVertexIndex, numVerticesInTheStrand, dampingCoeff); 
        else
            sharedPos[indexForSharedMem] = initialPos;
    }    

    //--------------------------------------------
    // Global shaping matching style enforcement
    //--------------------------------------------
    float stiffnessForGlobalShapeMatching = 0;
    float globalShapeMatchingEffectiveRange = 0;

    if ( strandType == 0 ) // top
    {
        stiffnessForGlobalShapeMatching = g_StiffnessForGlobalShapeMatching0;
        globalShapeMatchingEffectiveRange = g_GlobalShapeMatchingEffectiveRange0;
    }
    else if ( strandType == 1 ) // back
    {
        stiffnessForGlobalShapeMatching = g_StiffnessForGlobalShapeMatching1;
        globalShapeMatchingEffectiveRange = g_GlobalShapeMatchingEffectiveRange1;
    }
    else if ( strandType == 2 ) // ponytail
    {
        stiffnessForGlobalShapeMatching = g_StiffnessForGlobalShapeMatching2;
        globalShapeMatchingEffectiveRange = g_GlobalShapeMatchingEffectiveRange2;
    }
    else if ( strandType == 3 ) // front long
    {
        stiffnessForGlobalShapeMatching = g_StiffnessForGlobalShapeMatching3;
        globalShapeMatchingEffectiveRange = g_GlobalShapeMatchingEffectiveRange3;
    }
    
    if ( stiffnessForGlobalShapeMatching > 0 && globalShapeMatchingEffectiveRange ) // top
    {
        if ( IsMovable(sharedPos[indexForSharedMem]) )  
        {
            if ( (float)localVertexIndex < globalShapeMatchingEffectiveRange * (float)numVerticesInTheStrand )
            {
                float factor = stiffnessForGlobalShapeMatching;
                float3 del = factor * (initialPos - sharedPos[indexForSharedMem]).xyz;
                sharedPos[indexForSharedMem].xyz += del;
            }
        }
    }

	//---------------------------------------
    // update global position buffers
    //---------------------------------------
    UpdateFinalVertexPositions(currentPos, sharedPos[indexForSharedMem], globalVertexIndex, localVertexIndex, numVerticesInTheStrand);
}

//---------------------------------
// Local shape constraints
// One thread computes one strand
//---------------------------------
[numthreads(GROUP_SIZE, 1, 1)]
void SimulateHair_B(uint GIndex : SV_GroupIndex,
                  uint3 GId : SV_GroupID,
                  uint3 DTid : SV_DispatchThreadID)
{
    uint globalStrandIndex = GROUP_SIZE*GId.x;
	globalStrandIndex += GIndex;

	int offset = 0;
    int strandType = 0;

	if ( globalStrandIndex > 0 )
    {
        offset =  g_GuideHairVerticesOffsetsSRV.Load(globalStrandIndex - 1);
        strandType = g_GuideHairStrandType.Load(globalStrandIndex - 1);
    }

    uint numVerticesInTheStrand = g_GuideHairVerticesOffsetsSRV.Load(globalStrandIndex) - offset;

	// stiffness for local shape constraints
	float stiffnessForLocalShapeMatching = 0;

	if ( strandType == 2 ) // ponytail
		stiffnessForLocalShapeMatching = g_StiffnessForLocalShapeMatching2;
	else if ( strandType == 3 ) // front long
		stiffnessForLocalShapeMatching = g_StiffnessForLocalShapeMatching3;
	else if ( strandType == 1 ) // back
		stiffnessForLocalShapeMatching = g_StiffnessForLocalShapeMatching1;
	else if ( strandType == 0 ) // top
		stiffnessForLocalShapeMatching = g_StiffnessForLocalShapeMatching0;

	// 1.0 for stiffness makes things unstable sometimes.
	if ( stiffnessForLocalShapeMatching >= 0.95f )
		stiffnessForLocalShapeMatching = 0.95f;

	//--------------------------------------------
	// Local shape constraint for bending/twisting 
	//--------------------------------------------    
	{
		float4 pos_minus_one = g_GuideHairVertexPositions[offset];
		float4 pos = g_GuideHairVertexPositions[offset+1];
		float4 pos_plus_one;
		uint globalVertexIndex = 0;
		float4 rotGlobal = g_GlobalRotations[offset];
	
		for ( uint localVertexIndex = 1; localVertexIndex < numVerticesInTheStrand-1; localVertexIndex++ )
		{
			globalVertexIndex = offset + localVertexIndex;
			pos_plus_one = g_GuideHairVertexPositions[globalVertexIndex+1];

			//--------------------------------
			// Update position i and i_plus_1
			//--------------------------------
			float4 rotGlobalWorld = MultQuaternionAndQuaternion(g_ModelRotateForHead, rotGlobal); 

			float3 orgPos_i_plus_1_InLocalFrame_i = g_GuideHairRefVecsInLocalFrame[globalVertexIndex+1];	
			float3 orgPos_i_plus_1_InGlobalFrame = MultQuaternionAndVector(rotGlobalWorld, orgPos_i_plus_1_InLocalFrame_i) + pos.xyz;

			float3 del = stiffnessForLocalShapeMatching * 0.5f * (orgPos_i_plus_1_InGlobalFrame - pos_plus_one.xyz).xyz;

			if ( IsMovable(pos) )
				pos.xyz -= del.xyz;

			if ( IsMovable(pos_plus_one) )
				pos_plus_one.xyz += del.xyz;
	
			//---------------------------
			// Update local/global frames
			//---------------------------
			float4 invRotGlobalWorld = InverseQuaternion(rotGlobalWorld);	
			float3 vec = normalize(pos_plus_one.xyz - pos.xyz);		
    
			float3 x_i_plus_1_frame_i = normalize(MultQuaternionAndVector(invRotGlobalWorld, vec));
			float3 e = float3(1.0f, 0, 0);
			float3 rotAxis = cross(e, x_i_plus_1_frame_i);
    
			if ( length(rotAxis) > 0.001 )
			{
				float angle_radian = acos(dot(e, x_i_plus_1_frame_i));
				rotAxis = normalize(rotAxis);

				float4 localRot = MakeQuaternion(angle_radian, rotAxis);
				rotGlobal = MultQuaternionAndQuaternion(rotGlobal, localRot);
			}	

			g_GuideHairVertexPositions[globalVertexIndex].xyz = pos.xyz;			
			g_GuideHairVertexPositions[globalVertexIndex+1].xyz = pos_plus_one.xyz;

			pos_minus_one = pos;
			pos = pos_plus_one;
		}	  
	}

	return;
}

//----------------------------------
// Wind and edge length constraints
// One thread computes one vertex
//----------------------------------
[numthreads(GROUP_SIZE, 1, 1)]
void SimulateHair_C(uint GIndex : SV_GroupIndex,
                  uint3 GId : SV_GroupID,
                  uint3 DTid : SV_DispatchThreadID)
{
	int offset = 0;

	uint globalStrandIndex = 0;
	uint localVertexIndex = 0; 
	uint indexForSharedMem = GIndex;
	uint numOfStrandsPerThreadGroup = 2;
	uint maxPossibleVertsInStrand = (GROUP_SIZE / numOfStrandsPerThreadGroup);
	uint offsetForLocalVertexIndex = 0;

	// With offsetForLocalVertexIndex, we can convert localVertexIndex into indexForSharedMem by doing below.
	// indexForSharedMem = localVertexIndex + offsetForLocalVertexIndex

	if ( GIndex < maxPossibleVertsInStrand )
	{
		globalStrandIndex = 2 * GId.x;
		localVertexIndex = GIndex;
		offsetForLocalVertexIndex = 0;
	}
	else
	{
		globalStrandIndex = 2 * GId.x + 1;
		localVertexIndex = GIndex - maxPossibleVertsInStrand;
		offsetForLocalVertexIndex = maxPossibleVertsInStrand;
	}
	
    if( globalStrandIndex > 0 ) 
    {
        offset =  g_GuideHairVerticesOffsetsSRV.Load(globalStrandIndex - 1);
    }

	uint globalVertexIndex = offset + localVertexIndex;
    uint numVerticesInTheStrand = g_GuideHairVerticesOffsetsSRV.Load(globalStrandIndex) - offset;

	if ( numVerticesInTheStrand > maxPossibleVertsInStrand )
		numVerticesInTheStrand = maxPossibleVertsInStrand;
				
    //------------------------------
    // Copy data into shared memory
    //------------------------------
    if (localVertexIndex < numVerticesInTheStrand )
    {
        sharedPos[indexForSharedMem] = g_GuideHairVertexPositions[globalVertexIndex];
        sharedLength[indexForSharedMem] = g_GuideHairRestLengthSRV[globalVertexIndex]; 
    }
        
    GroupMemoryBarrierWithGroupSync();

	//------------
	// Wind
	//------------
	if ( g_Wind.x != 0 || g_Wind.y != 0 || g_Wind.z != 0 )
	{  
		float4 force = float4(0, 0, 0, 0);

		float frame = g_Wind.w;

		if ( localVertexIndex >= 2 && localVertexIndex < numVerticesInTheStrand-1 )
		{
			// combining four winds.
			float a = ((float)(globalStrandIndex % 20))/20.0f;
			float3	w = a*g_Wind.xyz + (1.0f-a)*g_Wind1.xyz + a*g_Wind2.xyz + (1.0f-a)*g_Wind3.xyz;

			float3 v = sharedPos[indexForSharedMem].xyz - sharedPos[indexForSharedMem+1].xyz;
			float3 force = -cross(cross(v, w), v);
			sharedPos[indexForSharedMem].xyz += force*g_TimeStep*g_TimeStep; 				
		}
	}

	GroupMemoryBarrierWithGroupSync();

	// We do the length constraints in SimulateHair_B. 
	// Below code is vertex level parallel process and uses shared memory. So it is better than doing it in SimulateHair_B.
	// But we need one directional position update to prevent exessive stretchy problem under fast head movement. 
	//----------------------------
	// Enforce length constraints
	//----------------------------
	uint a = floor(numVerticesInTheStrand/2.0f);
	uint b = floor((numVerticesInTheStrand-1)/2.0f); 
	
	for ( int iterationE=0; iterationE < g_NumLengthConstraintIterations; iterationE++ )
	{
		uint sharedIndex = localVertexIndex*2 + offsetForLocalVertexIndex;

		if( localVertexIndex < a )
			ApplyDistanceConstraint(sharedPos[sharedIndex], sharedPos[sharedIndex+1], sharedLength[sharedIndex].x);

		GroupMemoryBarrierWithGroupSync();

		if( localVertexIndex < b )
			ApplyDistanceConstraint(sharedPos[sharedIndex+1], sharedPos[sharedIndex+2], sharedLength[sharedIndex+1].x);

		GroupMemoryBarrierWithGroupSync();
	}

	//---------------------------------------
    // update global position buffers
    //---------------------------------------
	if ( localVertexIndex < numVerticesInTheStrand )
	    g_GuideHairVertexPositions[globalVertexIndex] = sharedPos[indexForSharedMem];
	
	return;
}

//------------------------------------
// Collision and tangents
// One thread computes one vertex
//------------------------------------
[numthreads(GROUP_SIZE, 1, 1)]
void SimulateHair_D(uint GIndex : SV_GroupIndex,
                  uint3 GId : SV_GroupID,
                  uint3 DTid : SV_DispatchThreadID)
{
	int offset = 0;

	uint globalStrandIndex = 0;
	uint localVertexIndex = 0; 
	uint indexForSharedMem = GIndex;
	uint numOfStrandsPerThreadGroup = 2;
	uint maxPossibleVertsInStrand = (GROUP_SIZE / numOfStrandsPerThreadGroup);
	
	if ( GIndex < maxPossibleVertsInStrand )
	{
		globalStrandIndex = 2 * GId.x;
		localVertexIndex = GIndex;
	}
	else
	{
		globalStrandIndex = 2 * GId.x + 1;
		localVertexIndex = GIndex - maxPossibleVertsInStrand;
	}
	
    if( globalStrandIndex > 0 ) 
    {
        offset =  g_GuideHairVerticesOffsetsSRV.Load(globalStrandIndex - 1);
    }

	uint globalVertexIndex = offset + localVertexIndex;
    uint numVerticesInTheStrand = g_GuideHairVerticesOffsetsSRV.Load(globalStrandIndex) - offset;

	if ( numVerticesInTheStrand > maxPossibleVertsInStrand )
		numVerticesInTheStrand = maxPossibleVertsInStrand;
		
    //------------------------------
    // Copy data into shared memory
    //------------------------------
    if (localVertexIndex < numVerticesInTheStrand )
    {
        sharedPos[indexForSharedMem] = g_GuideHairVertexPositions[globalVertexIndex];
        sharedLength[indexForSharedMem] = g_GuideHairRestLengthSRV[globalVertexIndex]; 
    }

	float4 oldPos = g_GuideHairVertexPositionsPrev[globalVertexIndex];
        
    GroupMemoryBarrierWithGroupSync();
	
    //-------------------------------------------------
    // Collision handling hard-code collision shapes
    //-------------------------------------------------
    if ( g_bCollision > 0 )
    {
        // Collision spheres are hard-coded. 
        {
            float3 centerSphere = float3(-0.095, 92.000, -9.899);
            centerSphere = mul(float4( centerSphere.xyz, 1), g_ModelTransformForHead).xyz;
            float radius = 26.5;

			CollisionCapsule cc;
			cc.p1.xyz = centerSphere;
			cc.p1.w = radius;
			cc.p2.xyz = centerSphere + float3(0.0,1.0,0.0);
			cc.p2.w = radius * radius;
			sharedPos[indexForSharedMem].xyz = CapsuleCollision(sharedPos[indexForSharedMem], oldPos, cc);
        }

        {
            float3 centerSphere = float3(-0.405, 93.707, 5.111);
            centerSphere = mul(float4( centerSphere.xyz, 1), g_ModelTransformForHead).xyz;
            float radius = 24.113;

			CollisionCapsule cc;
			cc.p1.xyz = centerSphere;
			cc.p1.w = radius;
			cc.p2.xyz = centerSphere + float3(0.0,1.0,0.0);
			cc.p2.w = radius * radius;
			sharedPos[indexForSharedMem].xyz = CapsuleCollision(sharedPos[indexForSharedMem], oldPos, cc);
        }

        {
            float3 centerSphere = float3(-0.072, 68.548, 10.561);
            centerSphere = mul(float4( centerSphere.xyz, 1), g_ModelTransformForHead).xyz;
            float radius = 25.500;

			CollisionCapsule cc;
			cc.p1.xyz = centerSphere;
			cc.p1.w = radius;
			cc.p2.xyz = centerSphere + float3(0.0,1.0,0.0);
			cc.p2.w = radius * radius;
			sharedPos[indexForSharedMem].xyz = CapsuleCollision(sharedPos[indexForSharedMem], oldPos, cc);
        }
    }

    GroupMemoryBarrierWithGroupSync();
    
    //-------------------
    // Compute tangent
    //-------------------
    if ( localVertexIndex < numVerticesInTheStrand-1  ) 
    {
        float3 tangent = sharedPos[indexForSharedMem+1].xyz - sharedPos[indexForSharedMem].xyz;
        g_GuideHairVertexTangents[globalVertexIndex].xyz = normalize(tangent);
    }
	
    //---------------------------------------
    // update global position buffers
    //---------------------------------------
	if ( localVertexIndex < numVerticesInTheStrand )
	    g_GuideHairVertexPositions[globalVertexIndex] = sharedPos[indexForSharedMem];

	return;
}
