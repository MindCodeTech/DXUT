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

#	pragma region MHVECTOR4

//------------------------------------------------------------------------------
// MHVECTOR4 operations
//------------------------------------------------------------------------------
#pragma region operations

inline bool XM_CALLCONV MHVECTOR4::VInBounds(FMHVECTOR4& Bounds) const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat4( this );
    XMVECTOR v2 = XMLoadFloat4( &Bounds );
    return XMVector4InBounds( v1, v2 );
}

inline float XM_CALLCONV MHVECTOR4::VLength() const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat4( this );
    XMVECTOR X = XMVector4Length( v1 );
    return XMVectorGetX( X );
}

inline float XM_CALLCONV MHVECTOR4::VLengthSquared() const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat4( this );
    XMVECTOR X = XMVector4LengthSq( v1 );
    return XMVectorGetX( X );
}

inline float XM_CALLCONV MHVECTOR4::VDot(FMHVECTOR4& V) const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat4( this );
    XMVECTOR v2 = XMLoadFloat4( &V );
    XMVECTOR X = XMVector4Dot( v1, v2 );
    return XMVectorGetX( X );
}

inline void XM_CALLCONV MHVECTOR4::VCross(FMHVECTOR4& v1, FMHVECTOR4& v2, MHVECTOR4& result) const
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4( this );
    XMVECTOR x2 = XMLoadFloat4( &v1 );
    XMVECTOR x3 = XMLoadFloat4( &v2 );
    XMVECTOR R = XMVector4Cross( x1, x2, x3 );
    XMStoreFloat4( &result, R );
}

inline MHVECTOR4 XM_CALLCONV MHVECTOR4::VCross(FMHVECTOR4& v1, FMHVECTOR4& v2) const
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4( this );
    XMVECTOR x2 = XMLoadFloat4( &v1 );
    XMVECTOR x3 = XMLoadFloat4( &v2 );
    XMVECTOR R = XMVector4Cross( x1, x2, x3 );

    MHVECTOR4 result;
    XMStoreFloat4( &result, R );
    return result;
}

inline void XM_CALLCONV MHVECTOR4::VNormalize()
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat4( this );
    XMVECTOR X = XMVector4Normalize( v1 );
    XMStoreFloat4( this, X );
}

inline void XM_CALLCONV MHVECTOR4::VNormalize(MHVECTOR4& result) const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat4( this );
    XMVECTOR X = XMVector4Normalize( v1 );
    XMStoreFloat4( &result, X );
}

inline void XM_CALLCONV MHVECTOR4::VClamp(FMHVECTOR4& vmin, FMHVECTOR4& vmax)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat4( this );
    XMVECTOR v2 = XMLoadFloat4( &vmin );
    XMVECTOR v3 = XMLoadFloat4( &vmax );
    XMVECTOR X = XMVectorClamp( v1, v2, v3 );
    XMStoreFloat4( this, X );
}

inline void XM_CALLCONV MHVECTOR4::VClamp(FMHVECTOR4& vmin, FMHVECTOR4& vmax, MHVECTOR4& result) const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat4( this );
    XMVECTOR v2 = XMLoadFloat4( &vmin );
    XMVECTOR v3 = XMLoadFloat4( &vmax );
    XMVECTOR X = XMVectorClamp( v1, v2, v3 );
    XMStoreFloat4( &result, X );
}

//------------------------------------------------------------------------------
// Static functions
//------------------------------------------------------------------------------

inline bool XM_CALLCONV MHVECTOR4::InBounds(FMHVECTOR4& V, FMHVECTOR4& Bounds)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(&V);
	XMVECTOR v2 = XMLoadFloat4(&Bounds);
	return XMVector4InBounds(v1, v2);
}

inline float XM_CALLCONV MHVECTOR4::Length(FMHVECTOR4& V)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(&V);
	XMVECTOR X = XMVector4Length(v1);
	return XMVectorGetX(X);
}

inline float XM_CALLCONV MHVECTOR4::LengthSquared(FMHVECTOR4& V)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(&V);
	XMVECTOR X = XMVector4LengthSq(v1);
	return XMVectorGetX(X);
}

inline float XM_CALLCONV MHVECTOR4::Dot(FMHVECTOR4& V1, FMHVECTOR4& V2)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(&V1);
	XMVECTOR v2 = XMLoadFloat4(&V2);
	XMVECTOR X = XMVector4Dot(v1, v2);
	return XMVectorGetX(X);
}

inline MHVECTOR4 XM_CALLCONV MHVECTOR4::Cross(FMHVECTOR4& V1, FMHVECTOR4& V2, FMHVECTOR4& V3)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(&V1);
	XMVECTOR v2 = XMLoadFloat4(&V2);
	XMVECTOR v3 = XMLoadFloat4(&V3);
	XMVECTOR R = XMVector4Cross(v1, v2, v3);

	MHVECTOR4 result;
	XMStoreFloat4(&result, R);
	return result;
}

inline void XM_CALLCONV MHVECTOR4::Cross(FMHVECTOR4& V1, FMHVECTOR4& V2, FMHVECTOR4& V3, MHVECTOR4& result)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(&V1);
	XMVECTOR v2 = XMLoadFloat4(&V2);
	XMVECTOR v3 = XMLoadFloat4(&V3);
	XMVECTOR R = XMVector4Cross(v1, v2, v3);
	XMStoreFloat4(&result, R);
}

inline MHVECTOR4 XM_CALLCONV MHVECTOR4::Normalize(FMHVECTOR4& V)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(&V);
	XMVECTOR X = XMVector4Normalize(v1);

	MHVECTOR4 result;
	XMStoreFloat4(&result, X);
	return result;
}

inline void XM_CALLCONV MHVECTOR4::Normalize(FMHVECTOR4& V, MHVECTOR4& result)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(&V);
	XMVECTOR X = XMVector4Normalize(v1);
	XMStoreFloat4(&result, X);
}

inline MHVECTOR4 XM_CALLCONV MHVECTOR4::Clamp(FMHVECTOR4& V, FMHVECTOR4& vmin, FMHVECTOR4& vmax)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(&V);
	XMVECTOR v2 = XMLoadFloat4(&vmin);
	XMVECTOR v3 = XMLoadFloat4(&vmax);
	XMVECTOR X = XMVectorClamp(v1, v2, v3);

	MHVECTOR4 result;
	XMStoreFloat4(&result, X);
	return result;
}

inline void XM_CALLCONV MHVECTOR4::Clamp(FMHVECTOR4& V, FMHVECTOR4& vmin, FMHVECTOR4& vmax, MHVECTOR4& result)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(&V);
	XMVECTOR v2 = XMLoadFloat4(&vmin);
	XMVECTOR v3 = XMLoadFloat4(&vmax);
	XMVECTOR X = XMVectorClamp(v1, v2, v3);
	XMStoreFloat4(&result, X);
}

inline MHVECTOR4 XM_CALLCONV MHVECTOR4::ClampLength(FMHVECTOR4& V, float LengthMin, float LengthMax)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(&V);
	XMVECTOR X = XMVector4ClampLength(v1, LengthMin, LengthMax);

	MHVECTOR4 result;
	XMStoreFloat4(&result, X);
	return result;
}

inline void XM_CALLCONV MHVECTOR4::ClampLength(FMHVECTOR4& V, float LengthMin, float LengthMax, MHVECTOR4& result)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(&V);
	XMVECTOR X = XMVector4ClampLength(v1, LengthMin, LengthMax);
	XMStoreFloat4(&result, X);
}

inline float XM_CALLCONV MHVECTOR4::Distance(FMHVECTOR4& v1, FMHVECTOR4& v2)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4( &v1 );
    XMVECTOR x2 = XMLoadFloat4( &v2 );
    XMVECTOR V = XMVectorSubtract( x2, x1 );
    XMVECTOR X = XMVector4Length( V );
    return XMVectorGetX( X );
}

inline float XM_CALLCONV MHVECTOR4::DistanceSquared(FMHVECTOR4& v1, FMHVECTOR4& v2)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4( &v1 );
    XMVECTOR x2 = XMLoadFloat4( &v2 );
    XMVECTOR V = XMVectorSubtract( x2, x1 );
    XMVECTOR X = XMVector4LengthSq( V );
    return XMVectorGetX( X );
}

inline void XM_CALLCONV MHVECTOR4::Min(FMHVECTOR4& v1, FMHVECTOR4& v2, MHVECTOR4& result)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4( &v1 );
    XMVECTOR x2 = XMLoadFloat4( &v2 );
    XMVECTOR X = XMVectorMin( x1, x2 );
    XMStoreFloat4( &result, X );
}

inline MHVECTOR4 XM_CALLCONV MHVECTOR4::Min(FMHVECTOR4& v1, FMHVECTOR4& v2)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4( &v1 );
    XMVECTOR x2 = XMLoadFloat4( &v2 );
    XMVECTOR X = XMVectorMin( x1, x2 );

    MHVECTOR4 result;
    XMStoreFloat4( &result, X );
    return result;
}

inline void XM_CALLCONV MHVECTOR4::Max(FMHVECTOR4& v1, FMHVECTOR4& v2, MHVECTOR4& result)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4( &v1 );
    XMVECTOR x2 = XMLoadFloat4( &v2 );
    XMVECTOR X = XMVectorMax( x1, x2 );
    XMStoreFloat4( &result, X );
}

inline MHVECTOR4 XM_CALLCONV MHVECTOR4::Max(FMHVECTOR4& v1, FMHVECTOR4& v2)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4( &v1 );
    XMVECTOR x2 = XMLoadFloat4( &v2 );
    XMVECTOR X = XMVectorMax( x1, x2 );

    MHVECTOR4 result;
    XMStoreFloat4( &result, X );
    return result;
}

inline void XM_CALLCONV MHVECTOR4::Lerp(FMHVECTOR4& v1, FMHVECTOR4& v2, float t, MHVECTOR4& result)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4( &v1 );
    XMVECTOR x2 = XMLoadFloat4( &v2 );
    XMVECTOR X = XMVectorLerp( x1, x2, t );
    XMStoreFloat4( &result, X );
}

inline MHVECTOR4 XM_CALLCONV MHVECTOR4::Lerp(FMHVECTOR4& v1, FMHVECTOR4& v2, float t)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4( &v1 );
    XMVECTOR x2 = XMLoadFloat4( &v2 );
    XMVECTOR X = XMVectorLerp( x1, x2, t );

    MHVECTOR4 result;
    XMStoreFloat4( &result, X );
    return result;
}

inline void XM_CALLCONV MHVECTOR4::SmoothStep(FMHVECTOR4& v1, FMHVECTOR4& v2, float t, MHVECTOR4& result)
{
    using namespace DirectX;
    t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);  // Clamp value to 0 to 1
    t = t*t*(3.f - 2.f*t);
    XMVECTOR x1 = XMLoadFloat4( &v1 );
    XMVECTOR x2 = XMLoadFloat4( &v2 );
    XMVECTOR X = XMVectorLerp( x1, x2, t );
    XMStoreFloat4( &result, X );
}

inline MHVECTOR4 XM_CALLCONV MHVECTOR4::SmoothStep(FMHVECTOR4& v1, FMHVECTOR4& v2, float t)
{
    using namespace DirectX;
    t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);  // Clamp value to 0 to 1
    t = t*t*(3.f - 2.f*t);
    XMVECTOR x1 = XMLoadFloat4( &v1 );
    XMVECTOR x2 = XMLoadFloat4( &v2 );
    XMVECTOR X = XMVectorLerp( x1, x2, t );

    MHVECTOR4 result;
    XMStoreFloat4( &result, X );
    return result;
}

inline void XM_CALLCONV MHVECTOR4::Barycentric(FMHVECTOR4& v1, FMHVECTOR4& v2, FMHVECTOR4& v3, float f, float g, MHVECTOR4& result)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4( &v1 );
    XMVECTOR x2 = XMLoadFloat4( &v2 );
    XMVECTOR x3 = XMLoadFloat4( &v3 );
    XMVECTOR X = XMVectorBaryCentric( x1, x2, x3, f, g );
    XMStoreFloat4( &result, X );
}

inline MHVECTOR4 XM_CALLCONV MHVECTOR4::Barycentric(FMHVECTOR4& v1, FMHVECTOR4& v2, FMHVECTOR4& v3, float f, float g)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4( &v1 );
    XMVECTOR x2 = XMLoadFloat4( &v2 );
    XMVECTOR x3 = XMLoadFloat4( &v3 );
    XMVECTOR X = XMVectorBaryCentric( x1, x2, x3, f, g );

    MHVECTOR4 result;
    XMStoreFloat4( &result, X );
    return result;
}

inline void XM_CALLCONV MHVECTOR4::CatmullRom(FMHVECTOR4& v1, FMHVECTOR4& v2, FMHVECTOR4& v3, FMHVECTOR4& v4, float t, MHVECTOR4& result)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4( &v1 );
    XMVECTOR x2 = XMLoadFloat4( &v2 );
    XMVECTOR x3 = XMLoadFloat4( &v3 );
    XMVECTOR x4 = XMLoadFloat4( &v4 );
    XMVECTOR X = XMVectorCatmullRom( x1, x2, x3, x4, t );
    XMStoreFloat4( &result, X );
}

inline MHVECTOR4 XM_CALLCONV MHVECTOR4::CatmullRom(FMHVECTOR4& v1, FMHVECTOR4& v2, FMHVECTOR4& v3, FMHVECTOR4& v4, float t)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4( &v1 );
    XMVECTOR x2 = XMLoadFloat4( &v2 );
    XMVECTOR x3 = XMLoadFloat4( &v3 );
    XMVECTOR x4 = XMLoadFloat4( &v4 );
    XMVECTOR X = XMVectorCatmullRom( x1, x2, x3, x4, t );

    MHVECTOR4 result;
    XMStoreFloat4( &result, X );
    return result;
}

inline void XM_CALLCONV MHVECTOR4::Hermite(FMHVECTOR4& v1, FMHVECTOR4& t1, FMHVECTOR4& v2, FMHVECTOR4& t2, float t, MHVECTOR4& result)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4( &v1 );
    XMVECTOR x2 = XMLoadFloat4( &t1 );
    XMVECTOR x3 = XMLoadFloat4( &v2 );
    XMVECTOR x4 = XMLoadFloat4( &t2 );
    XMVECTOR X = XMVectorHermite( x1, x2, x3, x4, t );
    XMStoreFloat4( &result, X );
}

inline MHVECTOR4 XM_CALLCONV MHVECTOR4::Hermite(FMHVECTOR4& v1, FMHVECTOR4& t1, FMHVECTOR4& v2, FMHVECTOR4& t2, float t)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4( &v1 );
    XMVECTOR x2 = XMLoadFloat4( &t1 );
    XMVECTOR x3 = XMLoadFloat4( &v2 );
    XMVECTOR x4 = XMLoadFloat4( &t2 );
    XMVECTOR X = XMVectorHermite( x1, x2, x3, x4, t );

    MHVECTOR4 result;
    XMStoreFloat4( &result, X );
    return result;
}

inline void XM_CALLCONV MHVECTOR4::Reflect(FMHVECTOR4& ivec, FMHVECTOR4& nvec, MHVECTOR4& result)
{
    using namespace DirectX;
    XMVECTOR i = XMLoadFloat4( &ivec );
    XMVECTOR n = XMLoadFloat4( &nvec );
    XMVECTOR X = XMVector4Reflect( i, n );
    XMStoreFloat4( &result, X );
}

inline MHVECTOR4 XM_CALLCONV MHVECTOR4::Reflect(FMHVECTOR4& ivec, FMHVECTOR4& nvec)
{
    using namespace DirectX;
    XMVECTOR i = XMLoadFloat4( &ivec );
    XMVECTOR n = XMLoadFloat4( &nvec );
    XMVECTOR X = XMVector4Reflect( i, n );

    MHVECTOR4 result;
    XMStoreFloat4( &result, X );
    return result;
}

inline void XM_CALLCONV MHVECTOR4::Refract(FMHVECTOR4& ivec, FMHVECTOR4& nvec, float refractionIndex, MHVECTOR4& result)
{
    using namespace DirectX;
    XMVECTOR i = XMLoadFloat4( &ivec );
    XMVECTOR n = XMLoadFloat4( &nvec );
    XMVECTOR X = XMVector4Refract( i, n, refractionIndex );
    XMStoreFloat4( &result, X );
}

inline MHVECTOR4 XM_CALLCONV MHVECTOR4::Refract(FMHVECTOR4& ivec, FMHVECTOR4& nvec, float refractionIndex)
{
    using namespace DirectX;
    XMVECTOR i = XMLoadFloat4( &ivec );
    XMVECTOR n = XMLoadFloat4( &nvec );
    XMVECTOR X = XMVector4Refract( i, n, refractionIndex );

    MHVECTOR4 result;
    XMStoreFloat4( &result, X );
    return result;
}

inline void XM_CALLCONV MHVECTOR4::Transform(FMHVECTOR2& v, FMHQUATERNION& quat, MHVECTOR4& result)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2( &v );
    XMVECTOR q = XMLoadFloat4( &quat );
    XMVECTOR X = XMVector3Rotate( v1, q );
    X = XMVectorSelect( g_XMIdentityR3, X, g_XMSelect1110 ); // result.w = 1.f
    XMStoreFloat4( &result, X );
}

inline MHVECTOR4 XM_CALLCONV MHVECTOR4::Transform(FMHVECTOR2& v, FMHQUATERNION& quat)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2( &v );
    XMVECTOR q = XMLoadFloat4( &quat );
    XMVECTOR X = XMVector3Rotate( v1, q );
    X = XMVectorSelect( g_XMIdentityR3, X, g_XMSelect1110 ); // result.w = 1.f

    MHVECTOR4 result;
    XMStoreFloat4( &result, X );
    return result;
}

inline void XM_CALLCONV MHVECTOR4::Transform(FMHVECTOR3& v, FMHQUATERNION& quat, MHVECTOR4& result)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3( &v );
    XMVECTOR q = XMLoadFloat4( &quat );
    XMVECTOR X = XMVector3Rotate( v1, q );
    X = XMVectorSelect( g_XMIdentityR3, X, g_XMSelect1110 ); // result.w = 1.f
    XMStoreFloat4( &result, X );
}

inline MHVECTOR4 XM_CALLCONV MHVECTOR4::Transform(FMHVECTOR3& v, FMHQUATERNION& quat)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3( &v );
    XMVECTOR q = XMLoadFloat4( &quat );
    XMVECTOR X = XMVector3Rotate( v1, q );
    X = XMVectorSelect( g_XMIdentityR3, X, g_XMSelect1110 ); // result.w = 1.f

    MHVECTOR4 result;
    XMStoreFloat4( &result, X );
    return result;
}

inline void XM_CALLCONV MHVECTOR4::Transform(FMHVECTOR4& v, FMHQUATERNION& quat, MHVECTOR4& result)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat4( &v );
    XMVECTOR q = XMLoadFloat4( &quat );
    XMVECTOR X = XMVector3Rotate( v1, q );
    X = XMVectorSelect( v1, X, g_XMSelect1110 ); // result.w = v.w
    XMStoreFloat4( &result, X );
}

inline MHVECTOR4 XM_CALLCONV MHVECTOR4::Transform(FMHVECTOR4& v, FMHQUATERNION& quat)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat4( &v );
    XMVECTOR q = XMLoadFloat4( &quat );
    XMVECTOR X = XMVector3Rotate( v1, q );
    X = XMVectorSelect( v1, X, g_XMSelect1110 ); // result.w = v.w

    MHVECTOR4 result;
    XMStoreFloat4( &result, X );
    return result;
}

inline void XM_CALLCONV MHVECTOR4::Transform(FMHVECTOR4& v, FMHMATRIX& m, MHVECTOR4& result)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat4( &v );
    XMMATRIX M = XMLoadFloat4x4( &m );
    XMVECTOR X = XMVector4Transform( v1, M );
    XMStoreFloat4( &result, X );
}

inline MHVECTOR4 XM_CALLCONV MHVECTOR4::Transform(FMHVECTOR4& v, FMHMATRIX& m)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat4( &v );
    XMMATRIX M = XMLoadFloat4x4( &m );
    XMVECTOR X = XMVector4Transform( v1, M );

    MHVECTOR4 result;
    XMStoreFloat4( &result, X );
    return result;
}

_Use_decl_annotations_
inline void XM_CALLCONV MHVECTOR4::Transform(FMHVECTOR4* varray, size_t count, FMHMATRIX& m, MHVECTOR4* resultArray)
{
    using namespace DirectX;
    XMMATRIX M = XMLoadFloat4x4( &m );
    XMVector4TransformStream( resultArray, sizeof(XMFLOAT4), varray, sizeof(XMFLOAT4), count, M );
}

#pragma endregion

//------------------------------------------------------------------------------
// MHVECTOR4 operators
//------------------------------------------------------------------------------
#pragma region operators

//------------------------------------------------------------------------------
// Comparision operators
//------------------------------------------------------------------------------

inline bool XM_CALLCONV MHVECTOR4::operator == (FMHVECTOR4& V) const
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(this);
	XMVECTOR v2 = XMLoadFloat4(&V);
	return XMVector4Equal(v1, v2);
}

inline bool XM_CALLCONV MHVECTOR4::operator != (FMHVECTOR4& V) const
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(this);
	XMVECTOR v2 = XMLoadFloat4(&V);
	return XMVector4NotEqual(v1, v2);
}

//------------------------------------------------------------------------------
// Assignment operators
//------------------------------------------------------------------------------

inline MHVECTOR4& XM_CALLCONV MHVECTOR4::operator+= (FMHVECTOR4& V)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(this);
	XMVECTOR v2 = XMLoadFloat4(&V);
	XMVECTOR X = XMVectorAdd(v1, v2);
	XMStoreFloat4(this, X);
	return *this;
}

inline MHVECTOR4& XM_CALLCONV MHVECTOR4::operator+= (float S)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(this);
	XMVECTOR v2 = XMLoadFloat(&S);
	XMVECTOR X = XMVectorAdd(v1, v2);
	XMStoreFloat4(this, X);
	return *this;
}

inline MHVECTOR4& XM_CALLCONV MHVECTOR4::operator-= (FMHVECTOR4& V)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(this);
	XMVECTOR v2 = XMLoadFloat4(&V);
	XMVECTOR X = XMVectorSubtract(v1, v2);
	XMStoreFloat4(this, X);
	return *this;
}

inline MHVECTOR4& XM_CALLCONV MHVECTOR4::operator-= (float S)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(this);
	XMVECTOR v2 = XMLoadFloat(&S);
	XMVECTOR X = XMVectorSubtract(v1, v2);
	XMStoreFloat4(this, X);
	return *this;
}

inline MHVECTOR4& XM_CALLCONV MHVECTOR4::operator*= (FMHVECTOR4& V)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(this);
	XMVECTOR v2 = XMLoadFloat4(&V);
	XMVECTOR X = XMVectorMultiply(v1, v2);
	XMStoreFloat4(this, X);
	return *this;
}

inline MHVECTOR4& XM_CALLCONV MHVECTOR4::operator*= (float S)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(this);
	XMVECTOR X = XMVectorScale(v1, S);
	XMStoreFloat4(this, X);
	return *this;
}

inline MHVECTOR4& XM_CALLCONV MHVECTOR4::operator/= (FMHVECTOR4& V)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(this);
	XMVECTOR v2 = XMLoadFloat4(&V);
	XMVECTOR X = XMVectorDivide(v1, v2);
	XMStoreFloat4(this, X);
	return *this;
}

inline MHVECTOR4& XM_CALLCONV MHVECTOR4::operator/= (float S)
{
	using namespace DirectX;
	assert(S != 0.0f);
	XMVECTOR v1 = XMLoadFloat4(this);
	XMVECTOR X = XMVectorScale(v1, 1.f / S);
	XMStoreFloat4(this, X);
	return *this;
}

//------------------------------------------------------------------------------
// Urnary operators
//------------------------------------------------------------------------------

/*
inline MHVECTOR4 XM_CALLCONV MHVECTOR4::operator+ () const
{
using namespace DirectX;
XMVECTOR v1 = XMLoadFloat4(this);
XMVECTOR X = +v1;
MHVECTOR4 R;
XMStoreFloat4(&R, X);
return R;
}*/

inline MHVECTOR4 XM_CALLCONV MHVECTOR4::operator- () const
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(this);
	XMVECTOR X = XMVectorNegate(v1);
	MHVECTOR4 R;
	XMStoreFloat4(&R, X);
	return R;
}

//------------------------------------------------------------------------------
// Binary operators
//------------------------------------------------------------------------------

inline MHVECTOR4 XM_CALLCONV operator+ (FMHVECTOR4& V1, FMHVECTOR4& V2)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(&V1);
	XMVECTOR v2 = XMLoadFloat4(&V2);
	XMVECTOR X = XMVectorAdd(v1, v2);
	MHVECTOR4 R;
	XMStoreFloat4(&R, X);
	return R;
}

inline MHVECTOR4 XM_CALLCONV operator+ (FMHVECTOR4& V, float S)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(&V);
	XMVECTOR v2 = XMLoadFloat(&S);
	XMVECTOR X = XMVectorAdd(v1, v2);
	MHVECTOR4 R;
	XMStoreFloat4(&R, X);
	return R;
}

inline MHVECTOR4 XM_CALLCONV operator+ (float S, FMHVECTOR4& V)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat(&S);
	XMVECTOR v2 = XMLoadFloat4(&V);
	XMVECTOR X = XMVectorAdd(v1, v2);
	MHVECTOR4 R;
	XMStoreFloat4(&R, X);
	return R;
}

inline MHVECTOR4 XM_CALLCONV operator- (FMHVECTOR4& V1, FMHVECTOR4& V2)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(&V1);
	XMVECTOR v2 = XMLoadFloat4(&V2);
	XMVECTOR X = XMVectorSubtract(v1, v2);
	MHVECTOR4 R;
	XMStoreFloat4(&R, X);
	return R;
}

inline MHVECTOR4 XM_CALLCONV operator- (FMHVECTOR4& V, float S)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(&V);
	XMVECTOR v2 = XMLoadFloat(&S);
	XMVECTOR X = XMVectorSubtract(v1, v2);
	MHVECTOR4 R;
	XMStoreFloat4(&R, X);
	return R;
}

inline MHVECTOR4 XM_CALLCONV operator- (float S, FMHVECTOR4& V)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat(&S);
	XMVECTOR v2 = XMLoadFloat4(&V);
	XMVECTOR X = XMVectorSubtract(v1, v2);
	MHVECTOR4 R;
	XMStoreFloat4(&R, X);
	return R;
}

inline MHVECTOR4 XM_CALLCONV operator* (FMHVECTOR4& V1, FMHVECTOR4& V2)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(&V1);
	XMVECTOR v2 = XMLoadFloat4(&V2);
	XMVECTOR X = XMVectorMultiply(v1, v2);
	MHVECTOR4 R;
	XMStoreFloat4(&R, X);
	return R;
}

inline MHVECTOR4 XM_CALLCONV operator* (FMHVECTOR4& V, float S)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(&V);
	XMVECTOR X = XMVectorScale(v1, S);
	MHVECTOR4 R;
	XMStoreFloat4(&R, X);
	return R;
}

inline MHVECTOR4 XM_CALLCONV operator* (float S, FMHVECTOR4& V)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(&V);
	XMVECTOR X = XMVectorScale(v1, S);
	MHVECTOR4 R;
	XMStoreFloat4(&R, X);
	return R;
}

inline MHVECTOR4 XM_CALLCONV operator/ (FMHVECTOR4& V1, FMHVECTOR4& V2)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(&V1);
	XMVECTOR v2 = XMLoadFloat4(&V2);
	XMVECTOR X = XMVectorDivide(v1, v2);
	MHVECTOR4 R;
	XMStoreFloat4(&R, X);
	return R;
}

inline MHVECTOR4 XM_CALLCONV operator/ (FMHVECTOR4& V, float S)
{
	using namespace DirectX;
	assert(S != 0.0f);
	XMVECTOR v1 = XMLoadFloat4(&V);
	XMVECTOR X = XMVectorScale(v1, 1.f / S);
	MHVECTOR4 R;
	XMStoreFloat4(&R, X);
	return R;
}

inline MHVECTOR4 XM_CALLCONV operator/ (float S, FMHVECTOR4& V)
{
	using namespace DirectX;
	assert(S != 0.0f);
	XMVECTOR v1 = XMLoadFloat4(&V);
	XMVECTOR X = XMVectorScale(v1, 1.f / S);
	MHVECTOR4 R;
	XMStoreFloat4(&R, X);
	return R;
}

#pragma endregion

#	pragma endregion

#ifdef __cplusplus
EXTERN_CC_END
#endif
