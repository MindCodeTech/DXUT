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

#	pragma region MHPLANE

 //------------------------------------------------------------------------------
 /// MHPLANE methods
 //------------------------------------------------------------------------------
#pragma region methods

inline MHPLANE::MHPLANE(FMHVECTOR3& point1, FMHVECTOR3& point2, FMHVECTOR3& point3 )
{
    using namespace DirectX;
    XMVECTOR P0 = XMLoadFloat3( &point1 );
    XMVECTOR P1 = XMLoadFloat3( &point2 );
    XMVECTOR P2 = XMLoadFloat3( &point3 );
    XMStoreFloat4( this, XMPlaneFromPoints( P0, P1, P2 ) );
}

inline MHPLANE::MHPLANE(FMHVECTOR3& point, FMHVECTOR3& normal)
{
    using namespace DirectX;
    XMVECTOR P = XMLoadFloat3( &point );
    XMVECTOR N = XMLoadFloat3( &normal );
    XMStoreFloat4( this, XMPlaneFromPointNormal( P, N ) );
}

#pragma endregion

//------------------------------------------------------------------------------
/// MHPLANE operators
//------------------------------------------------------------------------------
#pragma region operators

//------------------------------------------------------------------------------
// Comparision operators
//------------------------------------------------------------------------------
inline bool XM_CALLCONV MHPLANE::operator == (FMHPLANE& p) const
{
    using namespace DirectX;
    XMVECTOR p1 = XMLoadFloat4( this );
    XMVECTOR p2 = XMLoadFloat4( &p );
    return XMPlaneEqual( p1, p2 );
}

inline bool XM_CALLCONV MHPLANE::operator != (FMHPLANE& p) const
{
    using namespace DirectX;
    XMVECTOR p1 = XMLoadFloat4( this );
    XMVECTOR p2 = XMLoadFloat4( &p );
    return XMPlaneNotEqual( p1, p2 );
}

#pragma endregion

//------------------------------------------------------------------------------
/// MHPLANE operations
//------------------------------------------------------------------------------
#pragma region operations

inline void XM_CALLCONV MHPLANE::PNormalize()
{
    using namespace DirectX;
    XMVECTOR p = XMLoadFloat4( this );
    XMStoreFloat4( this, XMPlaneNormalize( p ) );
}

inline void XM_CALLCONV MHPLANE::PNormalize(MHPLANE& result) const
{
    using namespace DirectX;
    XMVECTOR p = XMLoadFloat4( this );
    XMStoreFloat4( &result, XMPlaneNormalize( p ) );
}

inline float XM_CALLCONV MHPLANE::PDot(FMHVECTOR4& v) const
{
    using namespace DirectX;
    XMVECTOR p = XMLoadFloat4( this );
    XMVECTOR v0 = XMLoadFloat4( &v );
    return XMVectorGetX( XMPlaneDot( p, v0 ) );
}

inline float XM_CALLCONV MHPLANE::PDotCoordinate(FMHVECTOR3& position) const
{
    using namespace DirectX;
    XMVECTOR p = XMLoadFloat4( this );
    XMVECTOR v0 = XMLoadFloat3( &position );
    return XMVectorGetX( XMPlaneDotCoord( p, v0 ) );
}

inline float XM_CALLCONV MHPLANE::PDotNormal(FMHVECTOR3& normal) const
{
    using namespace DirectX;
    XMVECTOR p = XMLoadFloat4( this );
    XMVECTOR n0 = XMLoadFloat3( &normal );
    return XMVectorGetX( XMPlaneDotNormal( p, n0 ) );
}

//------------------------------------------------------------------------------
// Static functions
//------------------------------------------------------------------------------

inline MHPLANE XM_CALLCONV MHPLANE::Normalize(FMHPLANE& plane)
{
	using namespace DirectX;
	XMVECTOR p = XMLoadFloat4(&plane);
	MHPLANE R;
	XMStoreFloat4(&R, XMPlaneNormalize(p));
	return R;
}

inline void XM_CALLCONV MHPLANE::Normalize(FMHPLANE& plane, MHPLANE& result)
{
	using namespace DirectX;
	XMVECTOR p = XMLoadFloat4(&plane);
	XMStoreFloat4(&result, XMPlaneNormalize(p));
}

inline float XM_CALLCONV MHPLANE::Dot(FMHPLANE& plane, FMHVECTOR4& v)
{
	using namespace DirectX;
	XMVECTOR p = XMLoadFloat4(&plane);
	XMVECTOR v0 = XMLoadFloat4(&v);
	return XMVectorGetX(XMPlaneDot(p, v0));
}

inline float XM_CALLCONV MHPLANE::DotCoordinate(FMHPLANE& plane, FMHVECTOR3& position)
{
	using namespace DirectX;
	XMVECTOR p = XMLoadFloat4(&plane);
	XMVECTOR v0 = XMLoadFloat3(&position);
	return XMVectorGetX(XMPlaneDotCoord(p, v0));
}

inline float XM_CALLCONV MHPLANE::DotNormal(FMHPLANE& plane, FMHVECTOR3& normal)
{
	using namespace DirectX;
	XMVECTOR p = XMLoadFloat4(&plane);
	XMVECTOR n0 = XMLoadFloat3(&normal);
	return XMVectorGetX(XMPlaneDotNormal(p, n0));
}

inline void XM_CALLCONV MHPLANE::Transform(FMHPLANE& plane, FMHMATRIX& M, MHPLANE& result)
{
    using namespace DirectX;
    XMVECTOR p = XMLoadFloat4( &plane );
    XMMATRIX m0 = XMLoadFloat4x4( &M );
    XMStoreFloat4( &result, XMPlaneTransform( p, m0 ) );
}

inline MHPLANE XM_CALLCONV MHPLANE::Transform(FMHPLANE& plane, FMHMATRIX& M)
{
    using namespace DirectX;
    XMVECTOR p = XMLoadFloat4( &plane );
    XMMATRIX m0 = XMLoadFloat4x4( &M );

    MHPLANE result;
    XMStoreFloat4( &result, XMPlaneTransform( p, m0 ) );
    return result;
}

inline void XM_CALLCONV MHPLANE::Transform(FMHPLANE& plane, FMHQUATERNION& rotation, MHPLANE& result)
{
    using namespace DirectX;
    XMVECTOR p = XMLoadFloat4( &plane );
    XMVECTOR q = XMLoadFloat4( &rotation );
    XMVECTOR X = XMVector3Rotate( p, q );
    X = XMVectorSelect( p, X, g_XMSelect1110 ); // result.d = plane.d
    XMStoreFloat4( &result, X );
}

inline MHPLANE XM_CALLCONV MHPLANE::Transform(FMHPLANE& plane, FMHQUATERNION& rotation)
{
    using namespace DirectX;
    XMVECTOR p = XMLoadFloat4( &plane );
    XMVECTOR q = XMLoadFloat4( &rotation );
    XMVECTOR X = XMVector3Rotate( p, q );
    X = XMVectorSelect( p, X, g_XMSelect1110 ); // result.d = plane.d

    MHPLANE result;
    XMStoreFloat4( &result, X );
    return result;
}

#pragma endregion

#	pragma endregion

#ifdef __cplusplus
EXTERN_CC_END
#endif
