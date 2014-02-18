//--------------------------------------------------------------------------------------
// File: DirectXMathHelper.inl
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//
// http://go.microsoft.com/fwlink/?LinkId=320437
//--------------------------------------------------------------------------------------

#ifdef _MSC_VER
#pragma once
#endif

#ifdef __cplusplus
EXTERN_CC_BEGIN
#endif

#	pragma region MHRAY

//-----------------------------------------------------------------------------
// MHRAY operations
//------------------------------------------------------------------------------
#pragma region operations

inline bool XM_CALLCONV MHRAY::Intersects(const BoundingSphere& sphere, _Out_ float& Dist) const
{
    return sphere.Intersects( position, direction, Dist );
}

inline bool XM_CALLCONV MHRAY::Intersects(const BoundingBox& box, _Out_ float& Dist) const
{
    return box.Intersects( position, direction, Dist );
}

inline bool XM_CALLCONV MHRAY::Intersects(FMHVECTOR3& tri0, FMHVECTOR3& tri1, FMHVECTOR3& tri2, _Out_ float& Dist) const
{
    return TriangleTests::Intersects( position, direction, tri0, tri1, tri2, Dist );
}

inline bool XM_CALLCONV MHRAY::Intersects(FMHPLANE& plane, _Out_ float& Dist) const
{
    using namespace DirectX;

    XMVECTOR p = XMLoadFloat4( &plane );
    XMVECTOR dir = XMLoadFloat3( &direction );

    XMVECTOR nd = XMPlaneDotNormal( p, dir );

    if ( XMVector3LessOrEqual( XMVectorAbs( nd ), g_RayEpsilon ) )
    {
        Dist = 0.f;
        return false;
    }
    else
    {
        // t = -(dot(n,origin) + D) / dot(n,dir)
        XMVECTOR pos = XMLoadFloat3( &position );
        XMVECTOR v = XMPlaneDotNormal( p, pos );
        v = XMVectorAdd( v, XMVectorSplatW(p) );
        v = XMVectorDivide( v, nd );
        float dist = - XMVectorGetX( v );
        if (dist < 0)
        {
            Dist = 0.f;
            return false;
        }
        else
        {
            Dist = dist;
            return true;
        }
    }
}

#pragma endregion

//-----------------------------------------------------------------------------
// MHRAY operators
//------------------------------------------------------------------------------
#pragma region operators

//-----------------------------------------------------------------------------
// Comparision operators
//------------------------------------------------------------------------------
inline bool XM_CALLCONV MHRAY::operator == (FMHRAY& r) const
{
	using namespace DirectX;
	XMVECTOR r1p = XMLoadFloat3(&position);
	XMVECTOR r2p = XMLoadFloat3(&r.position);
	XMVECTOR r1d = XMLoadFloat3(&direction);
	XMVECTOR r2d = XMLoadFloat3(&r.direction);
	return XMVector3Equal(r1p, r2p) && XMVector3Equal(r1d, r2d);
}

inline bool XM_CALLCONV MHRAY::operator != (FMHRAY& r) const
{
	using namespace DirectX;
	XMVECTOR r1p = XMLoadFloat3(&position);
	XMVECTOR r2p = XMLoadFloat3(&r.position);
	XMVECTOR r1d = XMLoadFloat3(&direction);
	XMVECTOR r2d = XMLoadFloat3(&r.direction);
	return XMVector3NotEqual(r1p, r2p) && XMVector3NotEqual(r1d, r2d);
}

#pragma endregion

#	pragma endregion

#ifdef __cplusplus
EXTERN_CC_END
#endif
