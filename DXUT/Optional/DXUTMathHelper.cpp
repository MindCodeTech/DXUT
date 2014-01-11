//***************************************************************************************
// MathHelper.cpp by Frank Luna (C) 2011 All Rights Reserved.
//***************************************************************************************

#include "dxutpch.h"

using namespace DirectX;

using namespace DXUT;

using MathHelper::CMathHelper;

#ifdef __cplusplus
EXTERN_C_BEGIN
#endif

NAMESPACE_DXUT
NAMESPACE_MathHelper

static const float Infinity = FLT_MAX;
static const float Pi = 3.1415926535f;

DXUTAPI float CMathHelper::AngleFromXY(float x, float y)
{
	float theta = 0.0f;

	// Quadrant I or IV
	if (x >= 0.0f)
	{
		// If x = 0, then atanf(y/x) = +pi/2 if y > 0
		//                atanf(y/x) = -pi/2 if y < 0
		theta = atanf(y / x); // in [-pi/2, +pi/2]

		if (theta < 0.0f)
			theta += 2.0f*Pi; // in [0, 2*pi).
	}

	// Quadrant II or III
	else
		theta = atanf(y / x) + Pi; // in [0, 2*pi).

	return theta;
}

DXUTAPI XMVECTOR CMathHelper::RandUnitVec3()
{
	XMVECTOR One = XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f);
	XMVECTOR Zero = XMVectorZero();

	// Keep trying until we get a point on/in the hemisphere.
	while (true)
	{
		// Generate random point in the cube [-1,1]^3.
		XMVECTOR v = XMVectorSet(CMathHelper::SRand(-1.0f, 1.0f), CMathHelper::SRand(-1.0f, 1.0f), CMathHelper::SRand(-1.0f, 1.0f), 0.0f);

		// Ignore points outside the unit sphere in order to get an even distribution
		// over the unit sphere.  Otherwise points will clump more on the sphere near
		// the corners of the cube.

		if (XMVector3Greater(XMVector3LengthSq(v), One))
			continue;

		return XMVector3Normalize(v);
	}
}

DXUTAPI XMVECTOR CMathHelper::RandHemisphereUnitVec3(XMVECTOR n)
{
	XMVECTOR One = XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f);
	XMVECTOR Zero = XMVectorZero();

	// Keep trying until we get a point on/in the hemisphere.
	while (true)
	{
		// Generate random point in the cube [-1,1]^3.
		XMVECTOR v = XMVectorSet(CMathHelper::SRand(-1.0f, 1.0f), CMathHelper::SRand(-1.0f, 1.0f), CMathHelper::SRand(-1.0f, 1.0f), 0.0f);

		// Ignore points outside the unit sphere in order to get an even distribution
		// over the unit sphere.  Otherwise points will clump more on the sphere near
		// the corners of the cube.

		if (XMVector3Greater(XMVector3LengthSq(v), One))
			continue;

		// Ignore points in the bottom hemisphere.
		if (XMVector3Less(XMVector3Dot(n, v), Zero))
			continue;

		return XMVector3Normalize(v);
	}
}

NAMESPACE_MathHelper_END
NAMESPACE_DXUT_END

#ifdef __cplusplus
EXTERN_C_END
#endif