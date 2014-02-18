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

#	pragma region MHVECTOR2

//------------------------------------------------------------------------------
// MHVECTOR2 operations
//------------------------------------------------------------------------------
#pragma region operations

inline bool XM_CALLCONV MHVECTOR2::VInBounds(FMHVECTOR2& Bounds) const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2( this );
    XMVECTOR v2 = XMLoadFloat2( &Bounds );
    return XMVector2InBounds( v1, v2 );
}

inline float XM_CALLCONV MHVECTOR2::VLength() const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2( this );
    XMVECTOR X = XMVector2Length( v1 );
    return XMVectorGetX( X );
}

inline float XM_CALLCONV MHVECTOR2::VLengthSquared() const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2( this );
    XMVECTOR X = XMVector2LengthSq( v1 );
    return XMVectorGetX( X );
}

inline float XM_CALLCONV MHVECTOR2::VDot(FMHVECTOR2& V) const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2( this );
    XMVECTOR v2 = XMLoadFloat2( &V );
    XMVECTOR X = XMVector2Dot( v1, v2 );
    return XMVectorGetX( X );
}

inline void XM_CALLCONV MHVECTOR2::VCross(FMHVECTOR2& V, MHVECTOR2& result) const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2( this );
    XMVECTOR v2 = XMLoadFloat2( &V );
    XMVECTOR R = XMVector2Cross( v1, v2 );
    XMStoreFloat2( &result, R );
}

inline MHVECTOR2 XM_CALLCONV MHVECTOR2::VCross(FMHVECTOR2& V) const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2( this );
    XMVECTOR v2 = XMLoadFloat2( &V );
    XMVECTOR R = XMVector2Cross( v1, v2 );

    MHVECTOR2 result;
    XMStoreFloat2( &result, R );
    return result;
}

inline void XM_CALLCONV MHVECTOR2::VNormalize()
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2( this );
    XMVECTOR X = XMVector2Normalize( v1 );
    XMStoreFloat2( this, X );
}

inline void XM_CALLCONV MHVECTOR2::VNormalize(MHVECTOR2& result) const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2( this );
    XMVECTOR X = XMVector2Normalize( v1 );
    XMStoreFloat2( &result, X );
}

inline void XM_CALLCONV MHVECTOR2::VClamp(FMHVECTOR2& vmin, FMHVECTOR2& vmax)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2( this );
    XMVECTOR v2 = XMLoadFloat2( &vmin );
    XMVECTOR v3 = XMLoadFloat2( &vmax );
    XMVECTOR X = XMVectorClamp( v1, v2, v3 );
    XMStoreFloat2( this, X );
}

inline void XM_CALLCONV MHVECTOR2::VClamp(FMHVECTOR2& vmin, FMHVECTOR2& vmax, MHVECTOR2& result) const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2( this );
    XMVECTOR v2 = XMLoadFloat2( &vmin );
    XMVECTOR v3 = XMLoadFloat2( &vmax );
    XMVECTOR X = XMVectorClamp( v1, v2, v3 );
    XMStoreFloat2( &result, X );
}

//------------------------------------------------------------------------------
// Static functions
//------------------------------------------------------------------------------

inline bool XM_CALLCONV MHVECTOR2::InBounds(FMHVECTOR2& V, FMHVECTOR2& Bounds)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(&V);
	XMVECTOR v2 = XMLoadFloat2(&Bounds);
	return XMVector2InBounds(v1, v2);
}

inline float XM_CALLCONV MHVECTOR2::Length(FMHVECTOR2& V)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(&V);
	XMVECTOR X = XMVector2Length(v1);
	return XMVectorGetX(X);
}

inline float XM_CALLCONV MHVECTOR2::LengthSquared(FMHVECTOR2& V)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(&V);
	XMVECTOR X = XMVector2LengthSq(v1);
	return XMVectorGetX(X);
}

inline float XM_CALLCONV MHVECTOR2::Dot(FMHVECTOR2& V1, FMHVECTOR2& V2)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(&V1);
	XMVECTOR v2 = XMLoadFloat2(&V2);
	XMVECTOR X = XMVector2Dot(v1, v2);
	return XMVectorGetX(X);
}

inline MHVECTOR2 XM_CALLCONV MHVECTOR2::Cross(FMHVECTOR2& V1, FMHVECTOR2& V2)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(&V1);
	XMVECTOR v2 = XMLoadFloat2(&V2);
	XMVECTOR R = XMVector2Cross(v1, v2);

	MHVECTOR2 result;
	XMStoreFloat2(&result, R);
	return result;
}

inline void XM_CALLCONV MHVECTOR2::Cross(FMHVECTOR2& V1, FMHVECTOR2& V2, MHVECTOR2& result)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(&V1);
	XMVECTOR v2 = XMLoadFloat2(&V2);
	XMVECTOR R = XMVector2Cross(v1, v2);
	XMStoreFloat2(&result, R);
}

inline MHVECTOR2 XM_CALLCONV MHVECTOR2::Normalize(FMHVECTOR2& V)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(&V);
	XMVECTOR X = XMVector2Normalize(v1);
	
	MHVECTOR2 result;
	XMStoreFloat2(&result, X);
	return result;
}

inline void XM_CALLCONV MHVECTOR2::Normalize(FMHVECTOR2& V, MHVECTOR2& result)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(&V);
	XMVECTOR X = XMVector2Normalize(v1);
	XMStoreFloat2(&result, X);
}

inline MHVECTOR2 XM_CALLCONV MHVECTOR2::Clamp(FMHVECTOR2& V, FMHVECTOR2& vmin, FMHVECTOR2& vmax)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(&V);
	XMVECTOR v2 = XMLoadFloat2(&vmin);
	XMVECTOR v3 = XMLoadFloat2(&vmax);
	XMVECTOR X = XMVectorClamp(v1, v2, v3);
	
	MHVECTOR2 result;
	XMStoreFloat2(&result, X);
	return result;
}

inline void XM_CALLCONV MHVECTOR2::Clamp(FMHVECTOR2& V, FMHVECTOR2& vmin, FMHVECTOR2& vmax, MHVECTOR2& result)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(&V);
	XMVECTOR v2 = XMLoadFloat2(&vmin);
	XMVECTOR v3 = XMLoadFloat2(&vmax);
	XMVECTOR X = XMVectorClamp(v1, v2, v3);
	XMStoreFloat2(&result, X);
}

inline MHVECTOR2 XM_CALLCONV MHVECTOR2::ClampLength(FMHVECTOR2& V, float LengthMin, float LengthMax)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(&V);
	XMVECTOR X = XMVector2ClampLength(v1, LengthMin, LengthMax);
	
	MHVECTOR2 result;
	XMStoreFloat2(&result, X);
	return result;
}

inline void XM_CALLCONV MHVECTOR2::ClampLength(FMHVECTOR2& V, float LengthMin, float LengthMax, MHVECTOR2& result)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(&V);
	XMVECTOR X = XMVector2ClampLength(v1, LengthMin, LengthMax);
	XMStoreFloat2(&result, X);
}

inline float XM_CALLCONV MHVECTOR2::Distance(FMHVECTOR2& v1, FMHVECTOR2& v2)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat2( &v1 );
    XMVECTOR x2 = XMLoadFloat2( &v2 );
    XMVECTOR V = XMVectorSubtract( x2, x1 );
    XMVECTOR X = XMVector2Length( V );
    return XMVectorGetX( X );
}

inline float XM_CALLCONV MHVECTOR2::DistanceSquared(FMHVECTOR2& v1, FMHVECTOR2& v2)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat2( &v1 );
    XMVECTOR x2 = XMLoadFloat2( &v2 );
    XMVECTOR V = XMVectorSubtract( x2, x1 );
    XMVECTOR X = XMVector2LengthSq( V );
    return XMVectorGetX( X );
}

inline void XM_CALLCONV MHVECTOR2::Min(FMHVECTOR2& v1, FMHVECTOR2& v2, MHVECTOR2& result)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat2( &v1 );
    XMVECTOR x2 = XMLoadFloat2( &v2 );
    XMVECTOR X = XMVectorMin( x1, x2 );
    XMStoreFloat2( &result, X );
}

inline MHVECTOR2 XM_CALLCONV MHVECTOR2::Min(FMHVECTOR2& v1, FMHVECTOR2& v2)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat2( &v1 );
    XMVECTOR x2 = XMLoadFloat2( &v2 );
    XMVECTOR X = XMVectorMin( x1, x2 );

    MHVECTOR2 result;
    XMStoreFloat2( &result, X );
    return result;
}

inline void XM_CALLCONV MHVECTOR2::Max(FMHVECTOR2& v1, FMHVECTOR2& v2, MHVECTOR2& result)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat2( &v1 );
    XMVECTOR x2 = XMLoadFloat2( &v2 );
    XMVECTOR X = XMVectorMax( x1, x2 );
    XMStoreFloat2( &result, X );
}

inline MHVECTOR2 XM_CALLCONV MHVECTOR2::Max(FMHVECTOR2& v1, FMHVECTOR2& v2)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat2( &v1 );
    XMVECTOR x2 = XMLoadFloat2( &v2 );
    XMVECTOR X = XMVectorMax( x1, x2 );

    MHVECTOR2 result;
    XMStoreFloat2( &result, X );
    return result;
}

inline void XM_CALLCONV MHVECTOR2::Lerp(FMHVECTOR2& v1, FMHVECTOR2& v2, float t, MHVECTOR2& result)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat2( &v1 );
    XMVECTOR x2 = XMLoadFloat2( &v2 );
    XMVECTOR X = XMVectorLerp( x1, x2, t );
    XMStoreFloat2( &result, X );
}

inline MHVECTOR2 XM_CALLCONV MHVECTOR2::Lerp(FMHVECTOR2& v1, FMHVECTOR2& v2, float t)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat2( &v1 );
    XMVECTOR x2 = XMLoadFloat2( &v2 );
    XMVECTOR X = XMVectorLerp( x1, x2, t );

    MHVECTOR2 result;
    XMStoreFloat2( &result, X );
    return result;
}

inline void XM_CALLCONV MHVECTOR2::SmoothStep(FMHVECTOR2& v1, FMHVECTOR2& v2, float t, MHVECTOR2& result)
{
    using namespace DirectX;
    t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);  // Clamp value to 0 to 1
    t = t*t*(3.f - 2.f*t);
    XMVECTOR x1 = XMLoadFloat2( &v1 );
    XMVECTOR x2 = XMLoadFloat2( &v2 );
    XMVECTOR X = XMVectorLerp( x1, x2, t );
    XMStoreFloat2( &result, X );
}

inline MHVECTOR2 XM_CALLCONV MHVECTOR2::SmoothStep(FMHVECTOR2& v1, FMHVECTOR2& v2, float t)
{
    using namespace DirectX;
    t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);  // Clamp value to 0 to 1
    t = t*t*(3.f - 2.f*t);
    XMVECTOR x1 = XMLoadFloat2( &v1 );
    XMVECTOR x2 = XMLoadFloat2( &v2 );
    XMVECTOR X = XMVectorLerp( x1, x2, t );

    MHVECTOR2 result;
    XMStoreFloat2( &result, X );
    return result;
}

inline void XM_CALLCONV MHVECTOR2::Barycentric(FMHVECTOR2& v1, FMHVECTOR2& v2, FMHVECTOR2& v3, float f, float g, MHVECTOR2& result)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat2( &v1 );
    XMVECTOR x2 = XMLoadFloat2( &v2 );
    XMVECTOR x3 = XMLoadFloat2( &v3 );
    XMVECTOR X = XMVectorBaryCentric( x1, x2, x3, f, g );
    XMStoreFloat2( &result, X );
}

inline MHVECTOR2 XM_CALLCONV MHVECTOR2::Barycentric(FMHVECTOR2& v1, FMHVECTOR2& v2, FMHVECTOR2& v3, float f, float g)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat2( &v1 );
    XMVECTOR x2 = XMLoadFloat2( &v2 );
    XMVECTOR x3 = XMLoadFloat2( &v3 );
    XMVECTOR X = XMVectorBaryCentric( x1, x2, x3, f, g );

    MHVECTOR2 result;
    XMStoreFloat2( &result, X );
    return result;
}

inline void XM_CALLCONV MHVECTOR2::CatmullRom(FMHVECTOR2& v1, FMHVECTOR2& v2, FMHVECTOR2& v3, FMHVECTOR2& v4, float t, MHVECTOR2& result)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat2( &v1 );
    XMVECTOR x2 = XMLoadFloat2( &v2 );
    XMVECTOR x3 = XMLoadFloat2( &v3 );
    XMVECTOR x4 = XMLoadFloat2( &v4 );
    XMVECTOR X = XMVectorCatmullRom( x1, x2, x3, x4, t );
    XMStoreFloat2( &result, X );
}

inline MHVECTOR2 XM_CALLCONV MHVECTOR2::CatmullRom(FMHVECTOR2& v1, FMHVECTOR2& v2, FMHVECTOR2& v3, FMHVECTOR2& v4, float t)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat2( &v1 );
    XMVECTOR x2 = XMLoadFloat2( &v2 );
    XMVECTOR x3 = XMLoadFloat2( &v3 );
    XMVECTOR x4 = XMLoadFloat2( &v4 );
    XMVECTOR X = XMVectorCatmullRom( x1, x2, x3, x4, t );

    MHVECTOR2 result;
    XMStoreFloat2( &result, X );
    return result;
}

inline void XM_CALLCONV MHVECTOR2::Hermite(FMHVECTOR2& v1, FMHVECTOR2& t1, FMHVECTOR2& v2, FMHVECTOR2& t2, float t, MHVECTOR2& result)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat2( &v1 );
    XMVECTOR x2 = XMLoadFloat2( &t1 );
    XMVECTOR x3 = XMLoadFloat2( &v2 );
    XMVECTOR x4 = XMLoadFloat2( &t2 );
    XMVECTOR X = XMVectorHermite( x1, x2, x3, x4, t );
    XMStoreFloat2( &result, X );
}

inline MHVECTOR2 XM_CALLCONV MHVECTOR2::Hermite(FMHVECTOR2& v1, FMHVECTOR2& t1, FMHVECTOR2& v2, FMHVECTOR2& t2, float t)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat2( &v1 );
    XMVECTOR x2 = XMLoadFloat2( &t1 );
    XMVECTOR x3 = XMLoadFloat2( &v2 );
    XMVECTOR x4 = XMLoadFloat2( &t2 );
    XMVECTOR X = XMVectorHermite( x1, x2, x3, x4, t );

    MHVECTOR2 result;
    XMStoreFloat2( &result, X );
    return result;
}

inline void XM_CALLCONV MHVECTOR2::Reflect(FMHVECTOR2& ivec, FMHVECTOR2& nvec, MHVECTOR2& result)
{
    using namespace DirectX;
    XMVECTOR i = XMLoadFloat2( &ivec );
    XMVECTOR n = XMLoadFloat2( &nvec );
    XMVECTOR X = XMVector2Reflect( i, n );
    XMStoreFloat2( &result, X );
}

inline MHVECTOR2 XM_CALLCONV MHVECTOR2::Reflect(FMHVECTOR2& ivec, FMHVECTOR2& nvec)
{
    using namespace DirectX;
    XMVECTOR i = XMLoadFloat2( &ivec );
    XMVECTOR n = XMLoadFloat2( &nvec );
    XMVECTOR X = XMVector2Reflect( i, n );

    MHVECTOR2 result;
    XMStoreFloat2( &result, X );
    return result;
}

inline void XM_CALLCONV MHVECTOR2::Refract(FMHVECTOR2& ivec, FMHVECTOR2& nvec, float refractionIndex, MHVECTOR2& result)
{
    using namespace DirectX;
    XMVECTOR i = XMLoadFloat2( &ivec );
    XMVECTOR n = XMLoadFloat2( &nvec );
    XMVECTOR X = XMVector2Refract( i, n, refractionIndex );
    XMStoreFloat2( &result, X );
}

inline MHVECTOR2 XM_CALLCONV MHVECTOR2::Refract(FMHVECTOR2& ivec, FMHVECTOR2& nvec, float refractionIndex)
{
    using namespace DirectX;
    XMVECTOR i = XMLoadFloat2( &ivec );
    XMVECTOR n = XMLoadFloat2( &nvec );
    XMVECTOR X = XMVector2Refract( i, n, refractionIndex );

    MHVECTOR2 result;
    XMStoreFloat2( &result, X );
    return result;
}

inline void XM_CALLCONV MHVECTOR2::Transform(FMHVECTOR2& v, FMHQUATERNION& quat, MHVECTOR2& result)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2( &v );
    XMVECTOR q = XMLoadFloat4( &quat );
    XMVECTOR X = XMVector3Rotate( v1, q );
    XMStoreFloat2( &result, X );
}

inline MHVECTOR2 XM_CALLCONV MHVECTOR2::Transform(FMHVECTOR2& v, FMHQUATERNION& quat)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2( &v );
    XMVECTOR q = XMLoadFloat4( &quat );
    XMVECTOR X = XMVector3Rotate( v1, q );

    MHVECTOR2 result;
    XMStoreFloat2( &result, X );
    return result;
}

inline void XM_CALLCONV MHVECTOR2::Transform(FMHVECTOR2& v, FMHMATRIX& m, MHVECTOR2& result)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2( &v );
    XMMATRIX M = XMLoadFloat4x4( &m );
    XMVECTOR X = XMVector2TransformCoord( v1, M );
    XMStoreFloat2( &result, X );
}

inline MHVECTOR2 XM_CALLCONV MHVECTOR2::Transform(FMHVECTOR2& v, FMHMATRIX& m)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2( &v );
    XMMATRIX M = XMLoadFloat4x4( &m );
    XMVECTOR X = XMVector2TransformCoord( v1, M );

    MHVECTOR2 result;
    XMStoreFloat2( &result, X );
    return result;
}

_Use_decl_annotations_
inline void XM_CALLCONV MHVECTOR2::Transform(FMHVECTOR2* varray, size_t count, FMHMATRIX& m, MHVECTOR2* resultArray)
{
    using namespace DirectX;
    XMMATRIX M = XMLoadFloat4x4( &m );
    XMVector2TransformCoordStream( resultArray, sizeof(XMFLOAT2), varray, sizeof(XMFLOAT2), count, M );
}

inline void XM_CALLCONV MHVECTOR2::Transform(FMHVECTOR2& v, FMHMATRIX& m, MHVECTOR4& result)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2( &v );
    XMMATRIX M = XMLoadFloat4x4( &m );
    XMVECTOR X = XMVector2Transform( v1, M );
    XMStoreFloat4( &result, X );
}

_Use_decl_annotations_
inline void XM_CALLCONV MHVECTOR2::Transform(FMHVECTOR2* varray, size_t count, FMHMATRIX& m, MHVECTOR4* resultArray)
{
    using namespace DirectX;
    XMMATRIX M = XMLoadFloat4x4( &m );
    XMVector2TransformStream( resultArray, sizeof(XMFLOAT4), varray, sizeof(XMFLOAT2), count, M );
}

inline void XM_CALLCONV MHVECTOR2::TransformNormal(FMHVECTOR2& v, FMHMATRIX& m, MHVECTOR2& result)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2( &v );
    XMMATRIX M = XMLoadFloat4x4( &m );
    XMVECTOR X = XMVector2TransformNormal( v1, M );
    XMStoreFloat2( &result, X );
}

inline MHVECTOR2 XM_CALLCONV MHVECTOR2::TransformNormal(FMHVECTOR2& v, FMHMATRIX& m)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2( &v );
    XMMATRIX M = XMLoadFloat4x4( &m );
    XMVECTOR X = XMVector2TransformNormal( v1, M );

    MHVECTOR2 result;
    XMStoreFloat2( &result, X );
    return result;
}

_Use_decl_annotations_
inline void XM_CALLCONV MHVECTOR2::TransformNormal(FMHVECTOR2* varray, size_t count, FMHMATRIX& m, MHVECTOR2* resultArray)
{
    using namespace DirectX;
    XMMATRIX M = XMLoadFloat4x4( &m );
    XMVector2TransformNormalStream( resultArray, sizeof(XMFLOAT2), varray, sizeof(XMFLOAT2), count, M );
}

#pragma endregion

//------------------------------------------------------------------------------
// MHVECTOR2 operators
//------------------------------------------------------------------------------
#	pragma region opeartors
//------------------------------------------------------------------------------
// Comparision operators
//------------------------------------------------------------------------------

inline bool XM_CALLCONV MHVECTOR2::operator == (FMHVECTOR2& V) const
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(this);
	XMVECTOR v2 = XMLoadFloat2(&V);
	return XMVector2Equal(v1, v2);
}

inline bool XM_CALLCONV MHVECTOR2::operator != (FMHVECTOR2& V) const
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(this);
	XMVECTOR v2 = XMLoadFloat2(&V);
	return XMVector2NotEqual(v1, v2);
}

//------------------------------------------------------------------------------
// Assignment operators
//------------------------------------------------------------------------------

inline MHVECTOR2& XM_CALLCONV MHVECTOR2::operator+= (FMHVECTOR2& V)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(this);
	XMVECTOR v2 = XMLoadFloat2(&V);
	XMVECTOR X = XMVectorAdd(v1, v2);
	XMStoreFloat2(this, X);
	return *this;
}

inline MHVECTOR2& XM_CALLCONV MHVECTOR2::operator+= (float S)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(this);
	XMVECTOR v2 = XMLoadFloat(&S);
	XMVECTOR X = XMVectorAdd(v1, v2);
	XMStoreFloat2(this, X);
	return *this;
}

inline MHVECTOR2& XM_CALLCONV MHVECTOR2::operator-= (FMHVECTOR2& V)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(this);
	XMVECTOR v2 = XMLoadFloat2(&V);
	XMVECTOR X = XMVectorSubtract(v1, v2);
	XMStoreFloat2(this, X);
	return *this;
}

inline MHVECTOR2& XM_CALLCONV MHVECTOR2::operator-= (float S)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(this);
	XMVECTOR v2 = XMLoadFloat(&S);
	XMVECTOR X = XMVectorSubtract(v1, v2);
	XMStoreFloat2(this, X);
	return *this;
}

inline MHVECTOR2& XM_CALLCONV MHVECTOR2::operator*= (FMHVECTOR2& V)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(this);
	XMVECTOR v2 = XMLoadFloat2(&V);
	XMVECTOR X = XMVectorMultiply(v1, v2);
	XMStoreFloat2(this, X);
	return *this;
}

inline MHVECTOR2& XM_CALLCONV MHVECTOR2::operator*= (float S)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(this);
	XMVECTOR X = XMVectorScale(v1, S);
	XMStoreFloat2(this, X);
	return *this;
}

inline MHVECTOR2& XM_CALLCONV MHVECTOR2::operator/= (FMHVECTOR2& V)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(this);
	XMVECTOR v2 = XMLoadFloat2(&V);
	XMVECTOR X = XMVectorDivide(v1, v2);
	XMStoreFloat2(this, X);
	return *this;
}

inline MHVECTOR2& XM_CALLCONV MHVECTOR2::operator/= (float S)
{
	using namespace DirectX;
	assert(S != 0.0f);
	XMVECTOR v1 = XMLoadFloat2(this);
	XMVECTOR X = XMVectorScale(v1, 1.f / S);
	XMStoreFloat2(this, X);
	return *this;
}

//------------------------------------------------------------------------------
// Urnary operators
//------------------------------------------------------------------------------

/*
inline MHVECTOR2 XM_CALLCONV MHVECTOR2::operator+ () const
{
using namespace DirectX;
XMVECTOR v1 = XMLoadFloat2(this);
XMVECTOR X = +v1;
MHVECTOR2 R;
XMStoreFloat2(&R, X);
return R;
}*/

/*
inline MHVECTOR2 XM_CALLCONV MHVECTOR2::operator- () const
{
using namespace DirectX;
XMVECTOR v1 = XMLoadFloat2(this);
XMVECTOR X = XMVectorNegate(v1);
MHVECTOR2 R;
XMStoreFloat2(&R, X);
return R;
}*/

//------------------------------------------------------------------------------
// Binary operators
//------------------------------------------------------------------------------

inline MHVECTOR2 XM_CALLCONV operator+ (FMHVECTOR2& V1, FMHVECTOR2& V2)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(&V1);
	XMVECTOR v2 = XMLoadFloat2(&V2);
	XMVECTOR X = XMVectorAdd(v1, v2);
	MHVECTOR2 R;
	XMStoreFloat2(&R, X);
	return R;
}

inline MHVECTOR2 XM_CALLCONV operator+ (FMHVECTOR2& V, float S)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(&V);
	XMVECTOR v2 = XMLoadFloat(&S);
	XMVECTOR X = XMVectorAdd(v1, v2);
	MHVECTOR2 R;
	XMStoreFloat2(&R, X);
	return R;
}

inline MHVECTOR2 XM_CALLCONV operator+ (float S, FMHVECTOR2& V)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat(&S);
	XMVECTOR v2 = XMLoadFloat2(&V);
	XMVECTOR X = XMVectorAdd(v1, v2);
	MHVECTOR2 R;
	XMStoreFloat2(&R, X);
	return R;
}

inline MHVECTOR2 XM_CALLCONV operator- (FMHVECTOR2& V1, FMHVECTOR2& V2)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(&V1);
	XMVECTOR v2 = XMLoadFloat2(&V2);
	XMVECTOR X = XMVectorSubtract(v1, v2);
	MHVECTOR2 R;
	XMStoreFloat2(&R, X);
	return R;
}

inline MHVECTOR2 XM_CALLCONV operator- (FMHVECTOR2& V, float S)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(&V);
	XMVECTOR v2 = XMLoadFloat(&S);
	XMVECTOR X = XMVectorSubtract(v1, v2);
	MHVECTOR2 R;
	XMStoreFloat2(&R, X);
	return R;
}

inline MHVECTOR2 XM_CALLCONV operator- (float S, FMHVECTOR2& V)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat(&S);
	XMVECTOR v2 = XMLoadFloat2(&V);
	XMVECTOR X = XMVectorSubtract(v1, v2);
	MHVECTOR2 R;
	XMStoreFloat2(&R, X);
	return R;
}

inline MHVECTOR2 XM_CALLCONV operator* (FMHVECTOR2& V1, FMHVECTOR2& V2)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(&V1);
	XMVECTOR v2 = XMLoadFloat2(&V2);
	XMVECTOR X = XMVectorMultiply(v1, v2);
	MHVECTOR2 R;
	XMStoreFloat2(&R, X);
	return R;
}

inline MHVECTOR2 XM_CALLCONV operator* (FMHVECTOR2& V, float S)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(&V);
	XMVECTOR X = XMVectorScale(v1, S);
	MHVECTOR2 R;
	XMStoreFloat2(&R, X);
	return R;
}

inline MHVECTOR2 XM_CALLCONV operator* (float S, FMHVECTOR2& V)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(&V);
	XMVECTOR X = XMVectorScale(v1, S);
	MHVECTOR2 R;
	XMStoreFloat2(&R, X);
	return R;
}

inline MHVECTOR2 XM_CALLCONV operator/ (FMHVECTOR2& V1, FMHVECTOR2& V2)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(&V1);
	XMVECTOR v2 = XMLoadFloat2(&V2);
	XMVECTOR X = XMVectorDivide(v1, v2);
	MHVECTOR2 R;
	XMStoreFloat2(&R, X);
	return R;
}

inline MHVECTOR2 XM_CALLCONV operator/ (FMHVECTOR2& V, float S)
{
	using namespace DirectX;
	assert(S != 0.0f);
	XMVECTOR v1 = XMLoadFloat2(&V);
	XMVECTOR X = XMVectorScale(v1, 1.f / S);
	MHVECTOR2 R;
	XMStoreFloat2(&R, X);
	return R;
}

inline MHVECTOR2 XM_CALLCONV operator/ (float S, FMHVECTOR2& V)
{
	using namespace DirectX;
	assert(S != 0.0f);
	XMVECTOR v1 = XMLoadFloat2(&V);
	XMVECTOR X = XMVectorScale(v1, 1.f / S);
	MHVECTOR2 R;
	XMStoreFloat2(&R, X);
	return R;
}

#pragma endregion

#	pragma endregion

#ifdef __cplusplus
EXTERN_CC_END
#endif
