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

#	pragma region MHVECTOR3

//------------------------------------------------------------------------------
// MHVECTOR3 operations
//------------------------------------------------------------------------------
#pragma region operations

inline bool XM_CALLCONV MHVECTOR3::VInBounds(FMHVECTOR3& Bounds) const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3( this );
    XMVECTOR v2 = XMLoadFloat3( &Bounds );
    return XMVector3InBounds( v1, v2 );
}

inline float XM_CALLCONV MHVECTOR3::VLength() const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3( this );
    XMVECTOR X = XMVector3Length( v1 );
    return XMVectorGetX( X );
}

inline float XM_CALLCONV MHVECTOR3::VLengthSquared() const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3( this );
    XMVECTOR X = XMVector3LengthSq( v1 );
    return XMVectorGetX( X );
}

inline float XM_CALLCONV MHVECTOR3::VDot(FMHVECTOR3& V) const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3( this );
    XMVECTOR v2 = XMLoadFloat3( &V );
    XMVECTOR X = XMVector3Dot( v1, v2 );
    return XMVectorGetX( X );
}

inline void XM_CALLCONV MHVECTOR3::VCross(FMHVECTOR3& V, MHVECTOR3& result) const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3( this );
    XMVECTOR v2 = XMLoadFloat3( &V );
    XMVECTOR R = XMVector3Cross( v1, v2 );
    XMStoreFloat3( &result, R );
}

inline MHVECTOR3 XM_CALLCONV MHVECTOR3::VCross(FMHVECTOR3& V) const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3( this );
    XMVECTOR v2 = XMLoadFloat3( &V );
    XMVECTOR R = XMVector3Cross( v1, v2 );

    MHVECTOR3 result;
    XMStoreFloat3( &result, R );
    return result;
}

inline void XM_CALLCONV MHVECTOR3::VNormalize()
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3( this );
    XMVECTOR X = XMVector3Normalize( v1 );
    XMStoreFloat3( this, X );
}

inline void XM_CALLCONV MHVECTOR3::VNormalize(MHVECTOR3& result) const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3( this );
    XMVECTOR X = XMVector3Normalize( v1 );
    XMStoreFloat3( &result, X );
}

inline void XM_CALLCONV MHVECTOR3::VClamp(FMHVECTOR3& vmin, FMHVECTOR3& vmax)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3( this );
    XMVECTOR v2 = XMLoadFloat3( &vmin );
    XMVECTOR v3 = XMLoadFloat3( &vmax );
    XMVECTOR X = XMVectorClamp( v1, v2, v3 );
    XMStoreFloat3( this, X );
}

inline void XM_CALLCONV MHVECTOR3::VClamp(FMHVECTOR3& vmin, FMHVECTOR3& vmax, MHVECTOR3& result) const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3( this );
    XMVECTOR v2 = XMLoadFloat3( &vmin );
    XMVECTOR v3 = XMLoadFloat3( &vmax );
    XMVECTOR X = XMVectorClamp( v1, v2, v3 );
    XMStoreFloat3( &result, X );
}

//------------------------------------------------------------------------------
// Static functions
//------------------------------------------------------------------------------

inline bool XM_CALLCONV MHVECTOR3::InBounds(FMHVECTOR3& V, FMHVECTOR3& Bounds)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(&V);
	XMVECTOR v2 = XMLoadFloat3(&Bounds);
	return XMVector3InBounds(v1, v2);
}

inline float XM_CALLCONV MHVECTOR3::Length(FMHVECTOR3& V)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(&V);
	XMVECTOR X = XMVector3Length(v1);
	return XMVectorGetX(X);
}

inline float XM_CALLCONV MHVECTOR3::LengthSquared(FMHVECTOR3& V)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(&V);
	XMVECTOR X = XMVector3LengthSq(v1);
	return XMVectorGetX(X);
}

inline float XM_CALLCONV MHVECTOR3::Dot(FMHVECTOR3& V1, FMHVECTOR3& V2)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(&V1);
	XMVECTOR v2 = XMLoadFloat3(&V2);
	XMVECTOR X = XMVector3Dot(v1, v2);
	return XMVectorGetX(X);
}

inline MHVECTOR3 XM_CALLCONV MHVECTOR3::Cross(FMHVECTOR3& V1, FMHVECTOR3& V2)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(&V1);
	XMVECTOR v2 = XMLoadFloat3(&V2);
	XMVECTOR R = XMVector3Cross(v1, v2);

	MHVECTOR3 result;
	XMStoreFloat3(&result, R);
	return result;
}

inline void XM_CALLCONV MHVECTOR3::Cross(FMHVECTOR3& V1, FMHVECTOR3& V2, MHVECTOR3& result)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(&V1);
	XMVECTOR v2 = XMLoadFloat3(&V2);
	XMVECTOR R = XMVector3Cross(v1, v2);
	XMStoreFloat3(&result, R);
}

inline MHVECTOR3 XM_CALLCONV MHVECTOR3::Normalize(FMHVECTOR3& V)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(&V);
	XMVECTOR X = XMVector3Normalize(v1);

	MHVECTOR3 result;
	XMStoreFloat3(&result, X);
	return result;
}

inline void XM_CALLCONV MHVECTOR3::Normalize(FMHVECTOR3& V, MHVECTOR3& result)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(&V);
	XMVECTOR X = XMVector3Normalize(v1);
	XMStoreFloat3(&result, X);
}

inline MHVECTOR3 XM_CALLCONV MHVECTOR3::Clamp(FMHVECTOR3& V, FMHVECTOR3& vmin, FMHVECTOR3& vmax)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(&V);
	XMVECTOR v2 = XMLoadFloat3(&vmin);
	XMVECTOR v3 = XMLoadFloat3(&vmax);
	XMVECTOR X = XMVectorClamp(v1, v2, v3);

	MHVECTOR3 result;
	XMStoreFloat3(&result, X);
	return result;
}

inline void XM_CALLCONV MHVECTOR3::Clamp(FMHVECTOR3& V, FMHVECTOR3& vmin, FMHVECTOR3& vmax, MHVECTOR3& result)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(&V);
	XMVECTOR v2 = XMLoadFloat3(&vmin);
	XMVECTOR v3 = XMLoadFloat3(&vmax);
	XMVECTOR X = XMVectorClamp(v1, v2, v3);
	XMStoreFloat3(&result, X);
}

inline MHVECTOR3 XM_CALLCONV MHVECTOR3::ClampLength(FMHVECTOR3& V, float LengthMin, float LengthMax)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(&V);
	XMVECTOR X = XMVector3ClampLength(v1, LengthMin, LengthMax);

	MHVECTOR3 result;
	XMStoreFloat3(&result, X);
	return result;
}

inline void XM_CALLCONV MHVECTOR3::ClampLength(FMHVECTOR3& V, float LengthMin, float LengthMax, MHVECTOR3& result)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(&V);
	XMVECTOR X = XMVector3ClampLength(v1, LengthMin, LengthMax);
	XMStoreFloat3(&result, X);
}

inline float XM_CALLCONV MHVECTOR3::Distance(FMHVECTOR3& v1, FMHVECTOR3& v2)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat3( &v1 );
    XMVECTOR x2 = XMLoadFloat3( &v2 );
    XMVECTOR V = XMVectorSubtract( x2, x1 );
    XMVECTOR X = XMVector3Length( V );
    return XMVectorGetX( X );
}

inline float XM_CALLCONV MHVECTOR3::DistanceSquared(FMHVECTOR3& v1, FMHVECTOR3& v2)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat3( &v1 );
    XMVECTOR x2 = XMLoadFloat3( &v2 );
    XMVECTOR V = XMVectorSubtract( x2, x1 );
    XMVECTOR X = XMVector3LengthSq( V );
    return XMVectorGetX( X );
}

inline void XM_CALLCONV MHVECTOR3::Min(FMHVECTOR3& v1, FMHVECTOR3& v2, MHVECTOR3& result)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat3( &v1 );
    XMVECTOR x2 = XMLoadFloat3( &v2 );
    XMVECTOR X = XMVectorMin( x1, x2 );
    XMStoreFloat3( &result, X );
}

inline MHVECTOR3 XM_CALLCONV MHVECTOR3::Min(FMHVECTOR3& v1, FMHVECTOR3& v2)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat3( &v1 );
    XMVECTOR x2 = XMLoadFloat3( &v2 );
    XMVECTOR X = XMVectorMin( x1, x2 );

    MHVECTOR3 result;
    XMStoreFloat3( &result, X );
    return result;
}

inline void XM_CALLCONV MHVECTOR3::Max(FMHVECTOR3& v1, FMHVECTOR3& v2, MHVECTOR3& result)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat3( &v1 );
    XMVECTOR x2 = XMLoadFloat3( &v2 );
    XMVECTOR X = XMVectorMax( x1, x2 );
    XMStoreFloat3( &result, X );
}

inline MHVECTOR3 XM_CALLCONV MHVECTOR3::Max(FMHVECTOR3& v1, FMHVECTOR3& v2)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat3( &v1 );
    XMVECTOR x2 = XMLoadFloat3( &v2 );
    XMVECTOR X = XMVectorMax( x1, x2 );

    MHVECTOR3 result;
    XMStoreFloat3( &result, X );
    return result;
}

inline void XM_CALLCONV MHVECTOR3::Lerp(FMHVECTOR3& v1, FMHVECTOR3& v2, float t, MHVECTOR3& result)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat3( &v1 );
    XMVECTOR x2 = XMLoadFloat3( &v2 );
    XMVECTOR X = XMVectorLerp( x1, x2, t );
    XMStoreFloat3( &result, X );
}

inline MHVECTOR3 XM_CALLCONV MHVECTOR3::Lerp(FMHVECTOR3& v1, FMHVECTOR3& v2, float t)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat3( &v1 );
    XMVECTOR x2 = XMLoadFloat3( &v2 );
    XMVECTOR X = XMVectorLerp( x1, x2, t );

    MHVECTOR3 result;
    XMStoreFloat3( &result, X );
    return result;
}

inline void XM_CALLCONV MHVECTOR3::SmoothStep(FMHVECTOR3& v1, FMHVECTOR3& v2, float t, MHVECTOR3& result)
{
    using namespace DirectX;
    t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);  // Clamp value to 0 to 1
    t = t*t*(3.f - 2.f*t);
    XMVECTOR x1 = XMLoadFloat3( &v1 );
    XMVECTOR x2 = XMLoadFloat3( &v2 );
    XMVECTOR X = XMVectorLerp( x1, x2, t );
    XMStoreFloat3( &result, X );
}

inline MHVECTOR3 XM_CALLCONV MHVECTOR3::SmoothStep(FMHVECTOR3& v1, FMHVECTOR3& v2, float t)
{
    using namespace DirectX;
    t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);  // Clamp value to 0 to 1
    t = t*t*(3.f - 2.f*t);
    XMVECTOR x1 = XMLoadFloat3( &v1 );
    XMVECTOR x2 = XMLoadFloat3( &v2 );
    XMVECTOR X = XMVectorLerp( x1, x2, t );

    MHVECTOR3 result;
    XMStoreFloat3( &result, X );
    return result;
}

inline void XM_CALLCONV MHVECTOR3::Barycentric(FMHVECTOR3& v1, FMHVECTOR3& v2, FMHVECTOR3& v3, float f, float g, MHVECTOR3& result)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat3( &v1 );
    XMVECTOR x2 = XMLoadFloat3( &v2 );
    XMVECTOR x3 = XMLoadFloat3( &v3 );
    XMVECTOR X = XMVectorBaryCentric( x1, x2, x3, f, g );
    XMStoreFloat3( &result, X );
}

inline MHVECTOR3 XM_CALLCONV MHVECTOR3::Barycentric(FMHVECTOR3& v1, FMHVECTOR3& v2, FMHVECTOR3& v3, float f, float g)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat3( &v1 );
    XMVECTOR x2 = XMLoadFloat3( &v2 );
    XMVECTOR x3 = XMLoadFloat3( &v3 );
    XMVECTOR X = XMVectorBaryCentric( x1, x2, x3, f, g );

    MHVECTOR3 result;
    XMStoreFloat3( &result, X );
    return result;
}

inline void XM_CALLCONV MHVECTOR3::CatmullRom(FMHVECTOR3& v1, FMHVECTOR3& v2, FMHVECTOR3& v3, FMHVECTOR3& v4, float t, MHVECTOR3& result)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat3( &v1 );
    XMVECTOR x2 = XMLoadFloat3( &v2 );
    XMVECTOR x3 = XMLoadFloat3( &v3 );
    XMVECTOR x4 = XMLoadFloat3( &v4 );
    XMVECTOR X = XMVectorCatmullRom( x1, x2, x3, x4, t );
    XMStoreFloat3( &result, X );
}

inline MHVECTOR3 XM_CALLCONV MHVECTOR3::CatmullRom(FMHVECTOR3& v1, FMHVECTOR3& v2, FMHVECTOR3& v3, FMHVECTOR3& v4, float t)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat3( &v1 );
    XMVECTOR x2 = XMLoadFloat3( &v2 );
    XMVECTOR x3 = XMLoadFloat3( &v3 );
    XMVECTOR x4 = XMLoadFloat3( &v4 );
    XMVECTOR X = XMVectorCatmullRom( x1, x2, x3, x4, t );

    MHVECTOR3 result;
    XMStoreFloat3( &result, X );
    return result;
}

inline void XM_CALLCONV MHVECTOR3::Hermite(FMHVECTOR3& v1, FMHVECTOR3& t1, FMHVECTOR3& v2, FMHVECTOR3& t2, float t, MHVECTOR3& result)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat3( &v1 );
    XMVECTOR x2 = XMLoadFloat3( &t1 );
    XMVECTOR x3 = XMLoadFloat3( &v2 );
    XMVECTOR x4 = XMLoadFloat3( &t2 );
    XMVECTOR X = XMVectorHermite( x1, x2, x3, x4, t );
    XMStoreFloat3( &result, X );
}

inline MHVECTOR3 XM_CALLCONV MHVECTOR3::Hermite(FMHVECTOR3& v1, FMHVECTOR3& t1, FMHVECTOR3& v2, FMHVECTOR3& t2, float t)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat3( &v1 );
    XMVECTOR x2 = XMLoadFloat3( &t1 );
    XMVECTOR x3 = XMLoadFloat3( &v2 );
    XMVECTOR x4 = XMLoadFloat3( &t2 );
    XMVECTOR X = XMVectorHermite( x1, x2, x3, x4, t );

    MHVECTOR3 result;
    XMStoreFloat3( &result, X );
    return result;
}

inline void XM_CALLCONV MHVECTOR3::Reflect(FMHVECTOR3& ivec, FMHVECTOR3& nvec, MHVECTOR3& result)
{
    using namespace DirectX;
    XMVECTOR i = XMLoadFloat3( &ivec );
    XMVECTOR n = XMLoadFloat3( &nvec );
    XMVECTOR X = XMVector3Reflect( i, n );
    XMStoreFloat3( &result, X );
}

inline MHVECTOR3 XM_CALLCONV MHVECTOR3::Reflect(FMHVECTOR3& ivec, FMHVECTOR3& nvec)
{
    using namespace DirectX;
    XMVECTOR i = XMLoadFloat3( &ivec );
    XMVECTOR n = XMLoadFloat3( &nvec );
    XMVECTOR X = XMVector3Reflect( i, n );

    MHVECTOR3 result;
    XMStoreFloat3( &result, X );
    return result;
}

inline void XM_CALLCONV MHVECTOR3::Refract(FMHVECTOR3& ivec, FMHVECTOR3& nvec, float refractionIndex, MHVECTOR3& result)
{
    using namespace DirectX;
    XMVECTOR i = XMLoadFloat3( &ivec );
    XMVECTOR n = XMLoadFloat3( &nvec );
    XMVECTOR X = XMVector3Refract( i, n, refractionIndex );
    XMStoreFloat3( &result, X );
}

inline MHVECTOR3 XM_CALLCONV MHVECTOR3::Refract(FMHVECTOR3& ivec, FMHVECTOR3& nvec, float refractionIndex)
{
    using namespace DirectX;
    XMVECTOR i = XMLoadFloat3( &ivec );
    XMVECTOR n = XMLoadFloat3( &nvec );
    XMVECTOR X = XMVector3Refract( i, n, refractionIndex );

    MHVECTOR3 result;
    XMStoreFloat3( &result, X );
    return result;
}

inline void XM_CALLCONV MHVECTOR3::Transform(FMHVECTOR3& v, FMHQUATERNION& quat, MHVECTOR3& result)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3( &v );
    XMVECTOR q = XMLoadFloat4( &quat );
    XMVECTOR X = XMVector3Rotate( v1, q );
    XMStoreFloat3( &result, X );
}

inline MHVECTOR3 XM_CALLCONV MHVECTOR3::Transform(FMHVECTOR3& v, FMHQUATERNION& quat)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3( &v );
    XMVECTOR q = XMLoadFloat4( &quat );
    XMVECTOR X = XMVector3Rotate( v1, q );

    MHVECTOR3 result;
    XMStoreFloat3( &result, X );
    return result;
}

inline void XM_CALLCONV MHVECTOR3::Transform(FMHVECTOR3& v, FMHMATRIX& m, MHVECTOR3& result)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3( &v );
    XMMATRIX M = XMLoadFloat4x4( &m );
    XMVECTOR X = XMVector3TransformCoord( v1, M );
    XMStoreFloat3( &result, X );
}

inline MHVECTOR3 XM_CALLCONV MHVECTOR3::Transform(FMHVECTOR3& v, FMHMATRIX& m)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3( &v );
    XMMATRIX M = XMLoadFloat4x4( &m );
    XMVECTOR X = XMVector3TransformCoord( v1, M );

    MHVECTOR3 result;
    XMStoreFloat3( &result, X );
    return result;
}

_Use_decl_annotations_
inline void XM_CALLCONV MHVECTOR3::Transform(FMHVECTOR3* varray, size_t count, FMHMATRIX& m, MHVECTOR3* resultArray)
{
    using namespace DirectX;
    XMMATRIX M = XMLoadFloat4x4( &m );
    XMVector3TransformCoordStream( resultArray, sizeof(XMFLOAT3), varray, sizeof(XMFLOAT3), count, M );
}

inline void XM_CALLCONV MHVECTOR3::Transform(FMHVECTOR3& v, FMHMATRIX& m, MHVECTOR4& result)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3( &v );
    XMMATRIX M = XMLoadFloat4x4( &m );
    XMVECTOR X = XMVector3Transform( v1, M );
    XMStoreFloat4( &result, X );
}

_Use_decl_annotations_
inline void XM_CALLCONV MHVECTOR3::Transform(FMHVECTOR3* varray, size_t count, FMHMATRIX& m, MHVECTOR4* resultArray)
{
    using namespace DirectX;
    XMMATRIX M = XMLoadFloat4x4( &m );
    XMVector3TransformStream( resultArray, sizeof(XMFLOAT4), varray, sizeof(XMFLOAT3), count, M );
}

inline void XM_CALLCONV MHVECTOR3::TransformNormal(FMHVECTOR3& v, FMHMATRIX& m, MHVECTOR3& result)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3( &v );
    XMMATRIX M = XMLoadFloat4x4( &m );
    XMVECTOR X = XMVector3TransformNormal( v1, M );
    XMStoreFloat3( &result, X );
}

inline MHVECTOR3 XM_CALLCONV MHVECTOR3::TransformNormal(FMHVECTOR3& v, FMHMATRIX& m)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3( &v );
    XMMATRIX M = XMLoadFloat4x4( &m );
    XMVECTOR X = XMVector3TransformNormal( v1, M );

    MHVECTOR3 result;
    XMStoreFloat3( &result, X );
    return result;
}

_Use_decl_annotations_
inline void XM_CALLCONV MHVECTOR3::TransformNormal(FMHVECTOR3* varray, size_t count, FMHMATRIX& m, MHVECTOR3* resultArray)
{
    using namespace DirectX;
    XMMATRIX M = XMLoadFloat4x4( &m );
    XMVector3TransformNormalStream( resultArray, sizeof(XMFLOAT3), varray, sizeof(XMFLOAT3), count, M );
}

#pragma endregion

//------------------------------------------------------------------------------
// MHVECTOR3 operators
//------------------------------------------------------------------------------
#	pragma region operators

//------------------------------------------------------------------------------
// Comparision operators
//------------------------------------------------------------------------------

inline bool XM_CALLCONV MHVECTOR3::operator == (FMHVECTOR3& V) const
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(this);
	XMVECTOR v2 = XMLoadFloat3(&V);
	return XMVector3Equal(v1, v2);
}

inline bool XM_CALLCONV MHVECTOR3::operator != (FMHVECTOR3& V) const
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(this);
	XMVECTOR v2 = XMLoadFloat3(&V);
	return XMVector3NotEqual(v1, v2);
}

//------------------------------------------------------------------------------
// Assignment operators
//------------------------------------------------------------------------------

inline MHVECTOR3& XM_CALLCONV MHVECTOR3::operator+= (FMHVECTOR3& V)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(this);
	XMVECTOR v2 = XMLoadFloat3(&V);
	XMVECTOR X = XMVectorAdd(v1, v2);
	XMStoreFloat3(this, X);
	return *this;
}

inline MHVECTOR3& XM_CALLCONV MHVECTOR3::operator+= (float S)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(this);
	XMVECTOR v2 = XMLoadFloat(&S);
	XMVECTOR X = XMVectorAdd(v1, v2);
	XMStoreFloat3(this, X);
	return *this;
}

inline MHVECTOR3& XM_CALLCONV MHVECTOR3::operator-= (FMHVECTOR3& V)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(this);
	XMVECTOR v2 = XMLoadFloat3(&V);
	XMVECTOR X = XMVectorSubtract(v1, v2);
	XMStoreFloat3(this, X);
	return *this;
}

inline MHVECTOR3& XM_CALLCONV MHVECTOR3::operator-= (float S)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(this);
	XMVECTOR v2 = XMLoadFloat(&S);
	XMVECTOR X = XMVectorSubtract(v1, v2);
	XMStoreFloat3(this, X);
	return *this;
}

inline MHVECTOR3& XM_CALLCONV MHVECTOR3::operator*= (FMHVECTOR3& V)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(this);
	XMVECTOR v2 = XMLoadFloat3(&V);
	XMVECTOR X = XMVectorMultiply(v1, v2);
	XMStoreFloat3(this, X);
	return *this;
}

inline MHVECTOR3& XM_CALLCONV MHVECTOR3::operator*= (float S)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(this);
	XMVECTOR X = XMVectorScale(v1, S);
	XMStoreFloat3(this, X);
	return *this;
}

inline MHVECTOR3& XM_CALLCONV MHVECTOR3::operator/= (FMHVECTOR3& V)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(this);
	XMVECTOR v2 = XMLoadFloat3(&V);
	XMVECTOR X = XMVectorDivide(v1, v2);
	XMStoreFloat3(this, X);
	return *this;
}

inline MHVECTOR3& XM_CALLCONV MHVECTOR3::operator/= (float S)
{
	using namespace DirectX;
	assert(S != 0.0f);
	XMVECTOR v1 = XMLoadFloat3(this);
	XMVECTOR X = XMVectorScale(v1, 1.f / S);
	XMStoreFloat3(this, X);
	return *this;
}

//------------------------------------------------------------------------------
// Urnary operators
//------------------------------------------------------------------------------

/*
inline MHVECTOR3 XM_CALLCONV MHVECTOR3::operator+ () const
{
using namespace DirectX;
XMVECTOR v1 = XMLoadFloat3(this);
XMVECTOR X = +v1;
MHVECTOR3 R;
XMStoreFloat3(&R, X);
return R;
}*/

inline MHVECTOR3 XM_CALLCONV MHVECTOR3::operator- () const
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(this);
	XMVECTOR X = XMVectorNegate(v1);
	MHVECTOR3 R;
	XMStoreFloat3(&R, X);
	return R;
}

//------------------------------------------------------------------------------
// Binary operators
//------------------------------------------------------------------------------

inline MHVECTOR3 XM_CALLCONV operator+ (FMHVECTOR3& V1, FMHVECTOR3& V2)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(&V1);
	XMVECTOR v2 = XMLoadFloat3(&V2);
	XMVECTOR X = XMVectorAdd(v1, v2);
	MHVECTOR3 R;
	XMStoreFloat3(&R, X);
	return R;
}

inline MHVECTOR3 XM_CALLCONV operator+ (FMHVECTOR3& V, float S)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(&V);
	XMVECTOR v2 = XMLoadFloat(&S);
	XMVECTOR X = XMVectorAdd(v1, v2);
	MHVECTOR3 R;
	XMStoreFloat3(&R, X);
	return R;
}

inline MHVECTOR3 XM_CALLCONV operator+ (float S, FMHVECTOR3& V)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat(&S);
	XMVECTOR v2 = XMLoadFloat3(&V);
	XMVECTOR X = XMVectorAdd(v1, v2);
	MHVECTOR3 R;
	XMStoreFloat3(&R, X);
	return R;
}

inline MHVECTOR3 XM_CALLCONV operator- (FMHVECTOR3& V1, FMHVECTOR3& V2)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(&V1);
	XMVECTOR v2 = XMLoadFloat3(&V2);
	XMVECTOR X = XMVectorSubtract(v1, v2);
	MHVECTOR3 R;
	XMStoreFloat3(&R, X);
	return R;
}

inline MHVECTOR3 XM_CALLCONV operator- (FMHVECTOR3& V, float S)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(&V);
	XMVECTOR v2 = XMLoadFloat(&S);
	XMVECTOR X = XMVectorSubtract(v1, v2);
	MHVECTOR3 R;
	XMStoreFloat3(&R, X);
	return R;
}

inline MHVECTOR3 XM_CALLCONV operator- (float S, FMHVECTOR3& V)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat(&S);
	XMVECTOR v2 = XMLoadFloat3(&V);
	XMVECTOR X = XMVectorSubtract(v1, v2);
	MHVECTOR3 R;
	XMStoreFloat3(&R, X);
	return R;
}

inline MHVECTOR3 XM_CALLCONV operator* (FMHVECTOR3& V1, FMHVECTOR3& V2)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(&V1);
	XMVECTOR v2 = XMLoadFloat3(&V2);
	XMVECTOR X = XMVectorMultiply(v1, v2);
	MHVECTOR3 R;
	XMStoreFloat3(&R, X);
	return R;
}

inline MHVECTOR3 XM_CALLCONV operator* (FMHVECTOR3& V, float S)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(&V);
	XMVECTOR X = XMVectorScale(v1, S);
	MHVECTOR3 R;
	XMStoreFloat3(&R, X);
	return R;
}

inline MHVECTOR3 XM_CALLCONV operator* (float S, FMHVECTOR3& V)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(&V);
	XMVECTOR X = XMVectorScale(v1, S);
	MHVECTOR3 R;
	XMStoreFloat3(&R, X);
	return R;
}

inline MHVECTOR3 XM_CALLCONV operator/ (FMHVECTOR3& V1, FMHVECTOR3& V2)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(&V1);
	XMVECTOR v2 = XMLoadFloat3(&V2);
	XMVECTOR X = XMVectorDivide(v1, v2);
	MHVECTOR3 R;
	XMStoreFloat3(&R, X);
	return R;
}

inline MHVECTOR3 XM_CALLCONV operator/ (FMHVECTOR3& V, float S)
{
	using namespace DirectX;
	assert(S != 0.0f);
	XMVECTOR v1 = XMLoadFloat3(&V);
	XMVECTOR X = XMVectorScale(v1, 1.f / S);
	MHVECTOR3 R;
	XMStoreFloat3(&R, X);
	return R;
}

inline MHVECTOR3 XM_CALLCONV operator/ (float S, FMHVECTOR3& V)
{
	using namespace DirectX;
	assert(S != 0.0f);
	XMVECTOR v1 = XMLoadFloat3(&V);
	XMVECTOR X = XMVectorScale(v1, 1.f / S);
	MHVECTOR3 R;
	XMStoreFloat3(&R, X);
	return R;
}

#pragma endregion

#	pragma endregion

#ifdef __cplusplus
EXTERN_CC_END
#endif
