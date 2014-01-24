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

inline float MHRand()
{
	return (float)(rand()) / (float)RAND_MAX;
}

inline float MHRand(float a, float b)
{
	return a + MHRand() * (b - a);
}

inline float XM_CALLCONV MHFresnelTerm(float CosIAngle, float RefIndex)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat(&CosIAngle);
	XMVECTOR v2 = XMLoadFloat(&RefIndex);
	XMVECTOR RF = (XMFresnelTerm(v1, v2));
	float R;
	XMStoreFloat(&R, RF);
	return R;
}

inline float MHRestrict(float val, float Min, float Max)
{
	if (val < Min) return Min;
	if (val > Max) return Max;
	return val;
}

inline XMFLOAT3 XM_CALLCONV XMMatrixForward(const XMMATRIX& m)
{
	using namespace DirectX;
	XMFLOAT4X4 float4x4;
	XMStoreFloat4x4(&float4x4, m);
	return XMFLOAT3(-float4x4._31, -float4x4._32, -float4x4._33);
}

inline XMFLOAT3 XM_CALLCONV XMMatrixBackward(const XMMATRIX& m)
{
	using namespace DirectX;
	XMFLOAT4X4 float4x4;
	XMStoreFloat4x4(&float4x4, m);
	return XMFLOAT3(float4x4._31, float4x4._32, float4x4._33);
}

inline XMFLOAT3 XM_CALLCONV XMMatrixUp(const XMMATRIX& m)
{
	using namespace DirectX;
	XMFLOAT4X4 float4x4;
	XMStoreFloat4x4(&float4x4, m);
	return XMFLOAT3(float4x4._21, float4x4._22, float4x4._23);
}

inline XMFLOAT3 XM_CALLCONV XMMatrixDown(const XMMATRIX& m)
{
	using namespace DirectX;
	XMFLOAT4X4 float4x4;
	XMStoreFloat4x4(&float4x4, m);
	return XMFLOAT3(-float4x4._21, -float4x4._22, -float4x4._23);
}

inline XMFLOAT3 XM_CALLCONV XMMatrixRight(const XMMATRIX& m)
{
	using namespace DirectX;
	XMFLOAT4X4 float4x4;
	XMStoreFloat4x4(&float4x4, m);
	return XMFLOAT3(float4x4._11, float4x4._12, float4x4._13);
}

inline XMFLOAT3 XM_CALLCONV XMMatrixLeft(const XMMATRIX& m)
{
	using namespace DirectX;
	XMFLOAT4X4 float4x4;
	XMStoreFloat4x4(&float4x4, m);
	return XMFLOAT3(-float4x4._11, -float4x4._12, -float4x4._13);
}

inline float XM_CALLCONV MHDot(XMFLOAT3& a, XMFLOAT3& b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

inline float XM_CALLCONV MHLength(XMFLOAT3& a)
{
	return sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
}

inline XMFLOAT3 XM_CALLCONV MHCross(XMFLOAT3& a, XMFLOAT3& b)
{
	using namespace DirectX;
	return XMFLOAT3((a.y*b.z) - (a.z*b.y), (a.z*b.x) - (a.x*b.z), (a.x*b.y) - (a.y*b.x));
}

inline XMFLOAT3 XM_CALLCONV MHNormalize(XMFLOAT3& v)
{
	using namespace DirectX;
	auto len = MHLength(v);
	return XMFLOAT3(v.x / len, v.y / len, v.z / len);
}

inline XMFLOAT3 XM_CALLCONV VectorToFloat3(XMVECTOR& v)
{
	using namespace DirectX;
	return XMFLOAT3(XMVectorGetX(v), XMVectorGetY(v), XMVectorGetZ(v));
}

inline XMFLOAT4 XM_CALLCONV VectorToFloat4(XMVECTOR& v)
{
	using namespace DirectX;
	return XMFLOAT4(XMVectorGetX(v), XMVectorGetY(v)
		, XMVectorGetZ(v), XMVectorGetW(v));
}

inline XMFLOAT3 XM_CALLCONV MHTransform(XMFLOAT3& v, XMMATRIX& m)
{
	using namespace DirectX;
	return VectorToFloat3(XMVector3Transform(XMVectorSet(v.x, v.y, v.z, 1.0f), m));
}

inline XMFLOAT4 XM_CALLCONV MHTransform(XMFLOAT4& f, XMMATRIX& m)
{
	return VectorToFloat4(XMVector3Transform(XMVectorSet(f.x, f.y, f.z, f.w), m));
}

inline XMFLOAT3 XM_CALLCONV MHTransformNormal(XMFLOAT3& v, XMMATRIX& m)
{
	using namespace DirectX;
	return VectorToFloat3(XMVector3TransformNormal(XMVectorSet(v.x, v.y, v.z, 1.0f), m));
}

inline XMFLOAT4 XM_CALLCONV MHTransformNormal(XMFLOAT4& f, XMMATRIX& m)
{
	using namespace DirectX;
	return VectorToFloat4(XMVector3TransformNormal(XMVectorSet(f.x, f.y, f.z, f.w), m));
}

/****************************************************************************
 *
 * MHVECTOR2
 *
 ****************************************************************************/
#	pragma region MHVECTOR2

//------------------------------------------------------------------------------
// Comparision operators
//------------------------------------------------------------------------------

inline bool XM_CALLCONV MHVECTOR2::operator == (const MHVECTOR2& V) const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2( this );
    XMVECTOR v2 = XMLoadFloat2( &V );
    return XMVector2Equal( v1, v2 );
}

inline bool XM_CALLCONV MHVECTOR2::operator != (const MHVECTOR2& V) const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2( this );
    XMVECTOR v2 = XMLoadFloat2( &V );
    return XMVector2NotEqual( v1, v2 );
}

//------------------------------------------------------------------------------
// Assignment operators
//------------------------------------------------------------------------------

inline MHVECTOR2& XM_CALLCONV MHVECTOR2::operator+= (const MHVECTOR2& V)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2( this );
    XMVECTOR v2 = XMLoadFloat2( &V );
    XMVECTOR X = XMVectorAdd(v1,v2);
    XMStoreFloat2( this, X );
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

inline MHVECTOR2& XM_CALLCONV MHVECTOR2::operator-= (const MHVECTOR2& V)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2( this );
    XMVECTOR v2 = XMLoadFloat2( &V );
    XMVECTOR X = XMVectorSubtract(v1,v2);
    XMStoreFloat2( this, X );
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

inline MHVECTOR2& XM_CALLCONV MHVECTOR2::operator*= (const MHVECTOR2& V)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2( this );
    XMVECTOR v2 = XMLoadFloat2( &V );
    XMVECTOR X = XMVectorMultiply(v1,v2);
    XMStoreFloat2( this, X );
    return *this;
}

inline MHVECTOR2& XM_CALLCONV MHVECTOR2::operator*= (float S)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2( this );
    XMVECTOR X = XMVectorScale(v1,S);
    XMStoreFloat2( this, X );
    return *this;
} 

inline MHVECTOR2& XM_CALLCONV MHVECTOR2::operator/= (const MHVECTOR2& V)
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
    assert( S != 0.0f );
    XMVECTOR v1 = XMLoadFloat2( this );
    XMVECTOR X = XMVectorScale(v1, 1.f/S);
    XMStoreFloat2( this, X );
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

inline MHVECTOR2 XM_CALLCONV operator+ (const MHVECTOR2& V1, const MHVECTOR2& V2)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2( &V1 );
    XMVECTOR v2 = XMLoadFloat2( &V2 );
    XMVECTOR X = XMVectorAdd(v1,v2);
    MHVECTOR2 R;
    XMStoreFloat2( &R, X );
    return R;
}

inline MHVECTOR2 XM_CALLCONV operator+ (const MHVECTOR2& V, float S)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(&V);
	XMVECTOR v2 = XMLoadFloat(&S);
	XMVECTOR X = XMVectorAdd(v1, v2);
	MHVECTOR2 R;
	XMStoreFloat2(&R, X);
	return R;
}

inline MHVECTOR2 XM_CALLCONV operator+ (float S, const MHVECTOR2& V)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat(&S);
	XMVECTOR v2 = XMLoadFloat2(&V);
	XMVECTOR X = XMVectorAdd(v1, v2);
	MHVECTOR2 R;
	XMStoreFloat2(&R, X);
	return R;
}

inline MHVECTOR2 XM_CALLCONV operator- (const MHVECTOR2& V1, const MHVECTOR2& V2)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2( &V1 );
    XMVECTOR v2 = XMLoadFloat2( &V2 );
    XMVECTOR X = XMVectorSubtract(v1,v2);
    MHVECTOR2 R;
    XMStoreFloat2( &R, X );
    return R;
}

inline MHVECTOR2 XM_CALLCONV operator- (const MHVECTOR2& V, float S)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(&V);
	XMVECTOR v2 = XMLoadFloat(&S);
	XMVECTOR X = XMVectorSubtract(v1, v2);
	MHVECTOR2 R;
	XMStoreFloat2(&R, X);
	return R;
}

inline MHVECTOR2 XM_CALLCONV operator- (float S, const MHVECTOR2& V)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat(&S);
	XMVECTOR v2 = XMLoadFloat2(&V);
	XMVECTOR X = XMVectorSubtract(v1, v2);
	MHVECTOR2 R;
	XMStoreFloat2(&R, X);
	return R;
}

inline MHVECTOR2 XM_CALLCONV operator* (const MHVECTOR2& V1, const MHVECTOR2& V2)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2( &V1 );
    XMVECTOR v2 = XMLoadFloat2( &V2 );
    XMVECTOR X = XMVectorMultiply(v1,v2);
    MHVECTOR2 R;
    XMStoreFloat2( &R, X );
    return R;
}

inline MHVECTOR2 XM_CALLCONV operator* (const MHVECTOR2& V, float S)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2( &V );
    XMVECTOR X = XMVectorScale(v1,S);
    MHVECTOR2 R;
    XMStoreFloat2( &R, X );
    return R;
}

inline MHVECTOR2 XM_CALLCONV operator* (float S, const MHVECTOR2& V)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(&V);
	XMVECTOR X = XMVectorScale(v1, S);
	MHVECTOR2 R;
	XMStoreFloat2(&R, X);
	return R;
}

inline MHVECTOR2 XM_CALLCONV operator/ (const MHVECTOR2& V1, const MHVECTOR2& V2)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(&V1);
	XMVECTOR v2 = XMLoadFloat2(&V2);
	XMVECTOR X = XMVectorDivide(v1, v2);
	MHVECTOR2 R;
	XMStoreFloat2(&R, X);
	return R;
}

inline MHVECTOR2 XM_CALLCONV operator/ (const MHVECTOR2& V, float S)
{
	using namespace DirectX;
	assert(S != 0.0f);
	XMVECTOR v1 = XMLoadFloat2(&V);
	XMVECTOR X = XMVectorScale(v1, 1.f/S);
	MHVECTOR2 R;
	XMStoreFloat2(&R, X);
	return R;
}

inline MHVECTOR2 XM_CALLCONV operator/ (float S, const MHVECTOR2& V)
{
	using namespace DirectX;
	assert(S != 0.0f);
	XMVECTOR v1 = XMLoadFloat2(&V);
	XMVECTOR X = XMVectorScale(v1, 1.f/S);
	MHVECTOR2 R;
	XMStoreFloat2(&R, X);
	return R;
}

//------------------------------------------------------------------------------
// Vector operations
//------------------------------------------------------------------------------

inline bool XM_CALLCONV MHVECTOR2::VInBounds(const MHVECTOR2& Bounds) const
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

inline float XM_CALLCONV MHVECTOR2::VDot(const MHVECTOR2& V) const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2( this );
    XMVECTOR v2 = XMLoadFloat2( &V );
    XMVECTOR X = XMVector2Dot( v1, v2 );
    return XMVectorGetX( X );
}

inline void XM_CALLCONV MHVECTOR2::VCross(const MHVECTOR2& V, MHVECTOR2& result) const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2( this );
    XMVECTOR v2 = XMLoadFloat2( &V );
    XMVECTOR R = XMVector2Cross( v1, v2 );
    XMStoreFloat2( &result, R );
}

inline MHVECTOR2 XM_CALLCONV MHVECTOR2::VCross(const MHVECTOR2& V) const
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

inline void XM_CALLCONV MHVECTOR2::VClamp(const MHVECTOR2& vmin, const MHVECTOR2& vmax)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2( this );
    XMVECTOR v2 = XMLoadFloat2( &vmin );
    XMVECTOR v3 = XMLoadFloat2( &vmax );
    XMVECTOR X = XMVectorClamp( v1, v2, v3 );
    XMStoreFloat2( this, X );
}

inline void XM_CALLCONV MHVECTOR2::VClamp(const MHVECTOR2& vmin, const MHVECTOR2& vmax, MHVECTOR2& result) const
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

inline bool XM_CALLCONV MHVECTOR2::InBounds(const MHVECTOR2& V, const MHVECTOR2& Bounds)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(&V);
	XMVECTOR v2 = XMLoadFloat2(&Bounds);
	return XMVector2InBounds(v1, v2);
}

inline float XM_CALLCONV MHVECTOR2::Length(const MHVECTOR2& V)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(&V);
	XMVECTOR X = XMVector2Length(v1);
	return XMVectorGetX(X);
}

inline float XM_CALLCONV MHVECTOR2::LengthSquared(const MHVECTOR2& V)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(&V);
	XMVECTOR X = XMVector2LengthSq(v1);
	return XMVectorGetX(X);
}

inline float XM_CALLCONV MHVECTOR2::Dot(const MHVECTOR2& V1, const MHVECTOR2& V2)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(&V1);
	XMVECTOR v2 = XMLoadFloat2(&V2);
	XMVECTOR X = XMVector2Dot(v1, v2);
	return XMVectorGetX(X);
}

inline MHVECTOR2 XM_CALLCONV MHVECTOR2::Cross(const MHVECTOR2& V1, const MHVECTOR2& V2)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(&V1);
	XMVECTOR v2 = XMLoadFloat2(&V2);
	XMVECTOR R = XMVector2Cross(v1, v2);

	MHVECTOR2 result;
	XMStoreFloat2(&result, R);
	return result;
}

inline void XM_CALLCONV MHVECTOR2::Cross(const MHVECTOR2& V1, const MHVECTOR2& V2, MHVECTOR2& result)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(&V1);
	XMVECTOR v2 = XMLoadFloat2(&V2);
	XMVECTOR R = XMVector2Cross(v1, v2);
	XMStoreFloat2(&result, R);
}

inline MHVECTOR2 XM_CALLCONV MHVECTOR2::Normalize(const MHVECTOR2& V)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(&V);
	XMVECTOR X = XMVector2Normalize(v1);
	
	MHVECTOR2 result;
	XMStoreFloat2(&result, X);
	return result;
}

inline void XM_CALLCONV MHVECTOR2::Normalize(const MHVECTOR2& V, MHVECTOR2& result)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(&V);
	XMVECTOR X = XMVector2Normalize(v1);
	XMStoreFloat2(&result, X);
}

inline MHVECTOR2 XM_CALLCONV MHVECTOR2::Clamp(MHVECTOR2& V, const MHVECTOR2& vmin, const MHVECTOR2& vmax)
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

inline void XM_CALLCONV MHVECTOR2::Clamp(const MHVECTOR2& V, const MHVECTOR2& vmin, const MHVECTOR2& vmax, MHVECTOR2& result)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(&V);
	XMVECTOR v2 = XMLoadFloat2(&vmin);
	XMVECTOR v3 = XMLoadFloat2(&vmax);
	XMVECTOR X = XMVectorClamp(v1, v2, v3);
	XMStoreFloat2(&result, X);
}

inline MHVECTOR2 XM_CALLCONV MHVECTOR2::ClampLength(MHVECTOR2& V, float LengthMin, float LengthMax)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(&V);
	XMVECTOR X = XMVector2ClampLength(v1, LengthMin, LengthMax);
	
	MHVECTOR2 result;
	XMStoreFloat2(&result, X);
	return result;
}

inline void XM_CALLCONV MHVECTOR2::ClampLength(const MHVECTOR2& V, float LengthMin, float LengthMax, MHVECTOR2& result)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(&V);
	XMVECTOR X = XMVector2ClampLength(v1, LengthMin, LengthMax);
	XMStoreFloat2(&result, X);
}

inline float XM_CALLCONV MHVECTOR2::Distance(const MHVECTOR2& v1, const MHVECTOR2& v2)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat2( &v1 );
    XMVECTOR x2 = XMLoadFloat2( &v2 );
    XMVECTOR V = XMVectorSubtract( x2, x1 );
    XMVECTOR X = XMVector2Length( V );
    return XMVectorGetX( X );
}

inline float XM_CALLCONV MHVECTOR2::DistanceSquared(const MHVECTOR2& v1, const MHVECTOR2& v2)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat2( &v1 );
    XMVECTOR x2 = XMLoadFloat2( &v2 );
    XMVECTOR V = XMVectorSubtract( x2, x1 );
    XMVECTOR X = XMVector2LengthSq( V );
    return XMVectorGetX( X );
}

inline void XM_CALLCONV MHVECTOR2::Min(const MHVECTOR2& v1, const MHVECTOR2& v2, MHVECTOR2& result)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat2( &v1 );
    XMVECTOR x2 = XMLoadFloat2( &v2 );
    XMVECTOR X = XMVectorMin( x1, x2 );
    XMStoreFloat2( &result, X );
}

inline MHVECTOR2 XM_CALLCONV MHVECTOR2::Min(const MHVECTOR2& v1, const MHVECTOR2& v2)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat2( &v1 );
    XMVECTOR x2 = XMLoadFloat2( &v2 );
    XMVECTOR X = XMVectorMin( x1, x2 );

    MHVECTOR2 result;
    XMStoreFloat2( &result, X );
    return result;
}

inline void XM_CALLCONV MHVECTOR2::Max(const MHVECTOR2& v1, const MHVECTOR2& v2, MHVECTOR2& result)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat2( &v1 );
    XMVECTOR x2 = XMLoadFloat2( &v2 );
    XMVECTOR X = XMVectorMax( x1, x2 );
    XMStoreFloat2( &result, X );
}

inline MHVECTOR2 XM_CALLCONV MHVECTOR2::Max(const MHVECTOR2& v1, const MHVECTOR2& v2)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat2( &v1 );
    XMVECTOR x2 = XMLoadFloat2( &v2 );
    XMVECTOR X = XMVectorMax( x1, x2 );

    MHVECTOR2 result;
    XMStoreFloat2( &result, X );
    return result;
}

inline void XM_CALLCONV MHVECTOR2::Lerp(const MHVECTOR2& v1, const MHVECTOR2& v2, float t, MHVECTOR2& result)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat2( &v1 );
    XMVECTOR x2 = XMLoadFloat2( &v2 );
    XMVECTOR X = XMVectorLerp( x1, x2, t );
    XMStoreFloat2( &result, X );
}

inline MHVECTOR2 XM_CALLCONV MHVECTOR2::Lerp(const MHVECTOR2& v1, const MHVECTOR2& v2, float t)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat2( &v1 );
    XMVECTOR x2 = XMLoadFloat2( &v2 );
    XMVECTOR X = XMVectorLerp( x1, x2, t );

    MHVECTOR2 result;
    XMStoreFloat2( &result, X );
    return result;
}

inline void XM_CALLCONV MHVECTOR2::SmoothStep(const MHVECTOR2& v1, const MHVECTOR2& v2, float t, MHVECTOR2& result)
{
    using namespace DirectX;
    t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);  // Clamp value to 0 to 1
    t = t*t*(3.f - 2.f*t);
    XMVECTOR x1 = XMLoadFloat2( &v1 );
    XMVECTOR x2 = XMLoadFloat2( &v2 );
    XMVECTOR X = XMVectorLerp( x1, x2, t );
    XMStoreFloat2( &result, X );
}

inline MHVECTOR2 XM_CALLCONV MHVECTOR2::SmoothStep(const MHVECTOR2& v1, const MHVECTOR2& v2, float t)
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

inline void XM_CALLCONV MHVECTOR2::Barycentric(const MHVECTOR2& v1, const MHVECTOR2& v2, const MHVECTOR2& v3, float f, float g, MHVECTOR2& result)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat2( &v1 );
    XMVECTOR x2 = XMLoadFloat2( &v2 );
    XMVECTOR x3 = XMLoadFloat2( &v3 );
    XMVECTOR X = XMVectorBaryCentric( x1, x2, x3, f, g );
    XMStoreFloat2( &result, X );
}

inline MHVECTOR2 XM_CALLCONV MHVECTOR2::Barycentric(const MHVECTOR2& v1, const MHVECTOR2& v2, const MHVECTOR2& v3, float f, float g)
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

inline void XM_CALLCONV MHVECTOR2::CatmullRom(const MHVECTOR2& v1, const MHVECTOR2& v2, const MHVECTOR2& v3, const MHVECTOR2& v4, float t, MHVECTOR2& result)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat2( &v1 );
    XMVECTOR x2 = XMLoadFloat2( &v2 );
    XMVECTOR x3 = XMLoadFloat2( &v3 );
    XMVECTOR x4 = XMLoadFloat2( &v4 );
    XMVECTOR X = XMVectorCatmullRom( x1, x2, x3, x4, t );
    XMStoreFloat2( &result, X );
}

inline MHVECTOR2 XM_CALLCONV MHVECTOR2::CatmullRom(const MHVECTOR2& v1, const MHVECTOR2& v2, const MHVECTOR2& v3, const MHVECTOR2& v4, float t)
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

inline void XM_CALLCONV MHVECTOR2::Hermite(const MHVECTOR2& v1, const MHVECTOR2& t1, const MHVECTOR2& v2, const MHVECTOR2& t2, float t, MHVECTOR2& result)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat2( &v1 );
    XMVECTOR x2 = XMLoadFloat2( &t1 );
    XMVECTOR x3 = XMLoadFloat2( &v2 );
    XMVECTOR x4 = XMLoadFloat2( &t2 );
    XMVECTOR X = XMVectorHermite( x1, x2, x3, x4, t );
    XMStoreFloat2( &result, X );
}

inline MHVECTOR2 XM_CALLCONV MHVECTOR2::Hermite(const MHVECTOR2& v1, const MHVECTOR2& t1, const MHVECTOR2& v2, const MHVECTOR2& t2, float t)
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

inline void XM_CALLCONV MHVECTOR2::Reflect(const MHVECTOR2& ivec, const MHVECTOR2& nvec, MHVECTOR2& result)
{
    using namespace DirectX;
    XMVECTOR i = XMLoadFloat2( &ivec );
    XMVECTOR n = XMLoadFloat2( &nvec );
    XMVECTOR X = XMVector2Reflect( i, n );
    XMStoreFloat2( &result, X );
}

inline MHVECTOR2 XM_CALLCONV MHVECTOR2::Reflect(const MHVECTOR2& ivec, const MHVECTOR2& nvec)
{
    using namespace DirectX;
    XMVECTOR i = XMLoadFloat2( &ivec );
    XMVECTOR n = XMLoadFloat2( &nvec );
    XMVECTOR X = XMVector2Reflect( i, n );

    MHVECTOR2 result;
    XMStoreFloat2( &result, X );
    return result;
}

inline void XM_CALLCONV MHVECTOR2::Refract(const MHVECTOR2& ivec, const MHVECTOR2& nvec, float refractionIndex, MHVECTOR2& result)
{
    using namespace DirectX;
    XMVECTOR i = XMLoadFloat2( &ivec );
    XMVECTOR n = XMLoadFloat2( &nvec );
    XMVECTOR X = XMVector2Refract( i, n, refractionIndex );
    XMStoreFloat2( &result, X );
}

inline MHVECTOR2 XM_CALLCONV MHVECTOR2::Refract(const MHVECTOR2& ivec, const MHVECTOR2& nvec, float refractionIndex)
{
    using namespace DirectX;
    XMVECTOR i = XMLoadFloat2( &ivec );
    XMVECTOR n = XMLoadFloat2( &nvec );
    XMVECTOR X = XMVector2Refract( i, n, refractionIndex );

    MHVECTOR2 result;
    XMStoreFloat2( &result, X );
    return result;
}

inline void XM_CALLCONV MHVECTOR2::Transform(const MHVECTOR2& v, const MHQUATERNION& quat, MHVECTOR2& result)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2( &v );
    XMVECTOR q = XMLoadFloat4( &quat );
    XMVECTOR X = XMVector3Rotate( v1, q );
    XMStoreFloat2( &result, X );
}

inline MHVECTOR2 XM_CALLCONV MHVECTOR2::Transform(const MHVECTOR2& v, const MHQUATERNION& quat)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2( &v );
    XMVECTOR q = XMLoadFloat4( &quat );
    XMVECTOR X = XMVector3Rotate( v1, q );

    MHVECTOR2 result;
    XMStoreFloat2( &result, X );
    return result;
}

inline void XM_CALLCONV MHVECTOR2::Transform(const MHVECTOR2& v, const MHMATRIX& m, MHVECTOR2& result)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2( &v );
    XMMATRIX M = XMLoadFloat4x4( &m );
    XMVECTOR X = XMVector2TransformCoord( v1, M );
    XMStoreFloat2( &result, X );
}

inline MHVECTOR2 XM_CALLCONV MHVECTOR2::Transform(const MHVECTOR2& v, const MHMATRIX& m)
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
inline void XM_CALLCONV MHVECTOR2::Transform(const MHVECTOR2* varray, size_t count, const MHMATRIX& m, MHVECTOR2* resultArray)
{
    using namespace DirectX;
    XMMATRIX M = XMLoadFloat4x4( &m );
    XMVector2TransformCoordStream( resultArray, sizeof(XMFLOAT2), varray, sizeof(XMFLOAT2), count, M );
}

inline void XM_CALLCONV MHVECTOR2::Transform(const MHVECTOR2& v, const MHMATRIX& m, MHVECTOR4& result)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2( &v );
    XMMATRIX M = XMLoadFloat4x4( &m );
    XMVECTOR X = XMVector2Transform( v1, M );
    XMStoreFloat4( &result, X );
}

_Use_decl_annotations_
inline void XM_CALLCONV MHVECTOR2::Transform(const MHVECTOR2* varray, size_t count, const MHMATRIX& m, MHVECTOR4* resultArray)
{
    using namespace DirectX;
    XMMATRIX M = XMLoadFloat4x4( &m );
    XMVector2TransformStream( resultArray, sizeof(XMFLOAT4), varray, sizeof(XMFLOAT2), count, M );
}

inline void XM_CALLCONV MHVECTOR2::TransformNormal(const MHVECTOR2& v, const MHMATRIX& m, MHVECTOR2& result)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2( &v );
    XMMATRIX M = XMLoadFloat4x4( &m );
    XMVECTOR X = XMVector2TransformNormal( v1, M );
    XMStoreFloat2( &result, X );
}

inline MHVECTOR2 XM_CALLCONV MHVECTOR2::TransformNormal(const MHVECTOR2& v, const MHMATRIX& m)
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
inline void XM_CALLCONV MHVECTOR2::TransformNormal(const MHVECTOR2* varray, size_t count, const MHMATRIX& m, MHVECTOR2* resultArray)
{
    using namespace DirectX;
    XMMATRIX M = XMLoadFloat4x4( &m );
    XMVector2TransformNormalStream( resultArray, sizeof(XMFLOAT2), varray, sizeof(XMFLOAT2), count, M );
}

#	pragma endregion

/****************************************************************************
 *
 * MHVECTOR3
 *
 ****************************************************************************/
#	pragma region MHVECTOR3

//------------------------------------------------------------------------------
// Comparision operators
//------------------------------------------------------------------------------

inline bool XM_CALLCONV MHVECTOR3::operator == (const MHVECTOR3& V) const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3( this );
    XMVECTOR v2 = XMLoadFloat3( &V );
    return XMVector3Equal( v1, v2 );
}

inline bool XM_CALLCONV MHVECTOR3::operator != (const MHVECTOR3& V) const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3( this );
    XMVECTOR v2 = XMLoadFloat3( &V );
    return XMVector3NotEqual( v1, v2 );
}

//------------------------------------------------------------------------------
// Assignment operators
//------------------------------------------------------------------------------

inline MHVECTOR3& XM_CALLCONV MHVECTOR3::operator+= (const MHVECTOR3& V)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3( this );
    XMVECTOR v2 = XMLoadFloat3( &V );
    XMVECTOR X = XMVectorAdd(v1,v2);
    XMStoreFloat3( this, X );
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

inline MHVECTOR3& XM_CALLCONV MHVECTOR3::operator-= (const MHVECTOR3& V)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3( this );
    XMVECTOR v2 = XMLoadFloat3( &V );
    XMVECTOR X = XMVectorSubtract(v1,v2);
    XMStoreFloat3( this, X );
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

inline MHVECTOR3& XM_CALLCONV MHVECTOR3::operator*= (const MHVECTOR3& V)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3( this );
    XMVECTOR v2 = XMLoadFloat3( &V );
    XMVECTOR X = XMVectorMultiply(v1,v2);
    XMStoreFloat3( this, X );
    return *this;
}

inline MHVECTOR3& XM_CALLCONV MHVECTOR3::operator*= (float S)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3( this );
    XMVECTOR X = XMVectorScale(v1,S);
    XMStoreFloat3( this, X );
    return *this;
} 

inline MHVECTOR3& XM_CALLCONV MHVECTOR3::operator/= (const MHVECTOR3& V)
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
    assert( S != 0.0f );
    XMVECTOR v1 = XMLoadFloat3( this );
    XMVECTOR X = XMVectorScale(v1, 1.f/S);
    XMStoreFloat3( this, X );
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
    XMVECTOR v1 = XMLoadFloat3( this );
    XMVECTOR X = XMVectorNegate( v1 );
    MHVECTOR3 R;
    XMStoreFloat3( &R, X );
    return R;
}

//------------------------------------------------------------------------------
// Binary operators
//------------------------------------------------------------------------------

inline MHVECTOR3 XM_CALLCONV operator+ (const MHVECTOR3& V1, const MHVECTOR3& V2)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3( &V1 );
    XMVECTOR v2 = XMLoadFloat3( &V2 );
    XMVECTOR X = XMVectorAdd(v1,v2);
    MHVECTOR3 R;
    XMStoreFloat3( &R, X );
    return R;
}

inline MHVECTOR3 XM_CALLCONV operator+ (const MHVECTOR3& V, float S)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(&V);
	XMVECTOR v2 = XMLoadFloat(&S);
	XMVECTOR X = XMVectorAdd(v1, v2);
	MHVECTOR3 R;
	XMStoreFloat3(&R, X);
	return R;
}

inline MHVECTOR3 XM_CALLCONV operator+ (float S, const MHVECTOR3& V)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat(&S);
	XMVECTOR v2 = XMLoadFloat3(&V);
	XMVECTOR X = XMVectorAdd(v1, v2);
	MHVECTOR3 R;
	XMStoreFloat3(&R, X);
	return R;
}

inline MHVECTOR3 XM_CALLCONV operator- (const MHVECTOR3& V1, const MHVECTOR3& V2)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3( &V1 );
    XMVECTOR v2 = XMLoadFloat3( &V2 );
    XMVECTOR X = XMVectorSubtract(v1,v2);
    MHVECTOR3 R;
    XMStoreFloat3( &R, X );
    return R;
}

inline MHVECTOR3 XM_CALLCONV operator- (const MHVECTOR3& V, float S)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(&V);
	XMVECTOR v2 = XMLoadFloat(&S);
	XMVECTOR X = XMVectorSubtract(v1, v2);
	MHVECTOR3 R;
	XMStoreFloat3(&R, X);
	return R;
}

inline MHVECTOR3 XM_CALLCONV operator- (float S, const MHVECTOR3& V)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat(&S);
	XMVECTOR v2 = XMLoadFloat3(&V);
	XMVECTOR X = XMVectorSubtract(v1, v2);
	MHVECTOR3 R;
	XMStoreFloat3(&R, X);
	return R;
}

inline MHVECTOR3 XM_CALLCONV operator* (const MHVECTOR3& V1, const MHVECTOR3& V2)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3( &V1 );
    XMVECTOR v2 = XMLoadFloat3( &V2 );
    XMVECTOR X = XMVectorMultiply(v1, v2);
    MHVECTOR3 R;
    XMStoreFloat3( &R, X );
    return R;
}

inline MHVECTOR3 XM_CALLCONV operator* (const MHVECTOR3& V, float S)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3( &V );
    XMVECTOR X = XMVectorScale(v1, S);
    MHVECTOR3 R;
    XMStoreFloat3( &R, X );
    return R;
}

inline MHVECTOR3 XM_CALLCONV operator* (float S, const MHVECTOR3& V)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(&V);
	XMVECTOR X = XMVectorScale(v1, S);
	MHVECTOR3 R;
	XMStoreFloat3(&R, X);
	return R;
}

inline MHVECTOR3 XM_CALLCONV operator/ (const MHVECTOR3& V1, const MHVECTOR3& V2)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3( &V1 );
    XMVECTOR v2 = XMLoadFloat3( &V2 );
    XMVECTOR X = XMVectorDivide(v1,v2);
    MHVECTOR3 R;
    XMStoreFloat3( &R, X );
    return R;
}

inline MHVECTOR3 XM_CALLCONV operator/ (const MHVECTOR3& V, float S)
{
	using namespace DirectX;
	assert(S != 0.0f);
	XMVECTOR v1 = XMLoadFloat3(&V);
	XMVECTOR X = XMVectorScale(v1, 1.f/S);
	MHVECTOR3 R;
	XMStoreFloat3(&R, X);
	return R;
}

inline MHVECTOR3 XM_CALLCONV operator/ (float S, const MHVECTOR3& V)
{
	using namespace DirectX;
	assert(S != 0.0f);
	XMVECTOR v1 = XMLoadFloat3(&V);
	XMVECTOR X = XMVectorScale(v1, 1.f/S);
	MHVECTOR3 R;
	XMStoreFloat3(&R, X);
	return R;
}

//------------------------------------------------------------------------------
// Vector operations
//------------------------------------------------------------------------------

inline bool XM_CALLCONV MHVECTOR3::VInBounds(const MHVECTOR3& Bounds) const
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

inline float XM_CALLCONV MHVECTOR3::VDot(const MHVECTOR3& V) const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3( this );
    XMVECTOR v2 = XMLoadFloat3( &V );
    XMVECTOR X = XMVector3Dot( v1, v2 );
    return XMVectorGetX( X );
}

inline void XM_CALLCONV MHVECTOR3::VCross(const MHVECTOR3& V, MHVECTOR3& result) const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3( this );
    XMVECTOR v2 = XMLoadFloat3( &V );
    XMVECTOR R = XMVector3Cross( v1, v2 );
    XMStoreFloat3( &result, R );
}

inline MHVECTOR3 XM_CALLCONV MHVECTOR3::VCross(const MHVECTOR3& V) const
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

inline void XM_CALLCONV MHVECTOR3::VClamp(const MHVECTOR3& vmin, const MHVECTOR3& vmax)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3( this );
    XMVECTOR v2 = XMLoadFloat3( &vmin );
    XMVECTOR v3 = XMLoadFloat3( &vmax );
    XMVECTOR X = XMVectorClamp( v1, v2, v3 );
    XMStoreFloat3( this, X );
}

inline void XM_CALLCONV MHVECTOR3::VClamp(const MHVECTOR3& vmin, const MHVECTOR3& vmax, MHVECTOR3& result) const
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

inline bool XM_CALLCONV MHVECTOR3::InBounds(const MHVECTOR3& V, const MHVECTOR3& Bounds)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(&V);
	XMVECTOR v2 = XMLoadFloat3(&Bounds);
	return XMVector3InBounds(v1, v2);
}

inline float XM_CALLCONV MHVECTOR3::Length(const MHVECTOR3& V)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(&V);
	XMVECTOR X = XMVector3Length(v1);
	return XMVectorGetX(X);
}

inline float XM_CALLCONV MHVECTOR3::LengthSquared(const MHVECTOR3& V)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(&V);
	XMVECTOR X = XMVector3LengthSq(v1);
	return XMVectorGetX(X);
}

inline float XM_CALLCONV MHVECTOR3::Dot(const MHVECTOR3& V1, const MHVECTOR3& V2)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(&V1);
	XMVECTOR v2 = XMLoadFloat3(&V2);
	XMVECTOR X = XMVector3Dot(v1, v2);
	return XMVectorGetX(X);
}

inline MHVECTOR3 XM_CALLCONV MHVECTOR3::Cross(const MHVECTOR3& V1, const MHVECTOR3& V2)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(&V1);
	XMVECTOR v2 = XMLoadFloat3(&V2);
	XMVECTOR R = XMVector3Cross(v1, v2);

	MHVECTOR3 result;
	XMStoreFloat3(&result, R);
	return result;
}

inline void XM_CALLCONV MHVECTOR3::Cross(const MHVECTOR3& V1, const MHVECTOR3& V2, MHVECTOR3& result)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(&V1);
	XMVECTOR v2 = XMLoadFloat3(&V2);
	XMVECTOR R = XMVector3Cross(v1, v2);
	XMStoreFloat3(&result, R);
}

inline MHVECTOR3 XM_CALLCONV MHVECTOR3::Normalize(const MHVECTOR3& V)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(&V);
	XMVECTOR X = XMVector3Normalize(v1);

	MHVECTOR3 result;
	XMStoreFloat3(&result, X);
	return result;
}

inline void XM_CALLCONV MHVECTOR3::Normalize(const MHVECTOR3& V, MHVECTOR3& result)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(&V);
	XMVECTOR X = XMVector3Normalize(v1);
	XMStoreFloat3(&result, X);
}

inline MHVECTOR3 XM_CALLCONV MHVECTOR3::Clamp(MHVECTOR3& V, const MHVECTOR3& vmin, const MHVECTOR3& vmax)
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

inline void XM_CALLCONV MHVECTOR3::Clamp(const MHVECTOR3& V, const MHVECTOR3& vmin, const MHVECTOR3& vmax, MHVECTOR3& result)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(&V);
	XMVECTOR v2 = XMLoadFloat3(&vmin);
	XMVECTOR v3 = XMLoadFloat3(&vmax);
	XMVECTOR X = XMVectorClamp(v1, v2, v3);
	XMStoreFloat3(&result, X);
}

inline MHVECTOR3 XM_CALLCONV MHVECTOR3::ClampLength(MHVECTOR3& V, float LengthMin, float LengthMax)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(&V);
	XMVECTOR X = XMVector3ClampLength(v1, LengthMin, LengthMax);

	MHVECTOR3 result;
	XMStoreFloat3(&result, X);
	return result;
}

inline void XM_CALLCONV MHVECTOR3::ClampLength(const MHVECTOR3& V, float LengthMin, float LengthMax, MHVECTOR3& result)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(&V);
	XMVECTOR X = XMVector3ClampLength(v1, LengthMin, LengthMax);
	XMStoreFloat3(&result, X);
}

inline float XM_CALLCONV MHVECTOR3::Distance(const MHVECTOR3& v1, const MHVECTOR3& v2)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat3( &v1 );
    XMVECTOR x2 = XMLoadFloat3( &v2 );
    XMVECTOR V = XMVectorSubtract( x2, x1 );
    XMVECTOR X = XMVector3Length( V );
    return XMVectorGetX( X );
}

inline float XM_CALLCONV MHVECTOR3::DistanceSquared(const MHVECTOR3& v1, const MHVECTOR3& v2)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat3( &v1 );
    XMVECTOR x2 = XMLoadFloat3( &v2 );
    XMVECTOR V = XMVectorSubtract( x2, x1 );
    XMVECTOR X = XMVector3LengthSq( V );
    return XMVectorGetX( X );
}

inline void XM_CALLCONV MHVECTOR3::Min(const MHVECTOR3& v1, const MHVECTOR3& v2, MHVECTOR3& result)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat3( &v1 );
    XMVECTOR x2 = XMLoadFloat3( &v2 );
    XMVECTOR X = XMVectorMin( x1, x2 );
    XMStoreFloat3( &result, X );
}

inline MHVECTOR3 XM_CALLCONV MHVECTOR3::Min(const MHVECTOR3& v1, const MHVECTOR3& v2)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat3( &v1 );
    XMVECTOR x2 = XMLoadFloat3( &v2 );
    XMVECTOR X = XMVectorMin( x1, x2 );

    MHVECTOR3 result;
    XMStoreFloat3( &result, X );
    return result;
}

inline void XM_CALLCONV MHVECTOR3::Max(const MHVECTOR3& v1, const MHVECTOR3& v2, MHVECTOR3& result)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat3( &v1 );
    XMVECTOR x2 = XMLoadFloat3( &v2 );
    XMVECTOR X = XMVectorMax( x1, x2 );
    XMStoreFloat3( &result, X );
}

inline MHVECTOR3 XM_CALLCONV MHVECTOR3::Max(const MHVECTOR3& v1, const MHVECTOR3& v2)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat3( &v1 );
    XMVECTOR x2 = XMLoadFloat3( &v2 );
    XMVECTOR X = XMVectorMax( x1, x2 );

    MHVECTOR3 result;
    XMStoreFloat3( &result, X );
    return result;
}

inline void XM_CALLCONV MHVECTOR3::Lerp(const MHVECTOR3& v1, const MHVECTOR3& v2, float t, MHVECTOR3& result)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat3( &v1 );
    XMVECTOR x2 = XMLoadFloat3( &v2 );
    XMVECTOR X = XMVectorLerp( x1, x2, t );
    XMStoreFloat3( &result, X );
}

inline MHVECTOR3 XM_CALLCONV MHVECTOR3::Lerp(const MHVECTOR3& v1, const MHVECTOR3& v2, float t)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat3( &v1 );
    XMVECTOR x2 = XMLoadFloat3( &v2 );
    XMVECTOR X = XMVectorLerp( x1, x2, t );

    MHVECTOR3 result;
    XMStoreFloat3( &result, X );
    return result;
}

inline void XM_CALLCONV MHVECTOR3::SmoothStep(const MHVECTOR3& v1, const MHVECTOR3& v2, float t, MHVECTOR3& result)
{
    using namespace DirectX;
    t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);  // Clamp value to 0 to 1
    t = t*t*(3.f - 2.f*t);
    XMVECTOR x1 = XMLoadFloat3( &v1 );
    XMVECTOR x2 = XMLoadFloat3( &v2 );
    XMVECTOR X = XMVectorLerp( x1, x2, t );
    XMStoreFloat3( &result, X );
}

inline MHVECTOR3 XM_CALLCONV MHVECTOR3::SmoothStep(const MHVECTOR3& v1, const MHVECTOR3& v2, float t)
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

inline void XM_CALLCONV MHVECTOR3::Barycentric(const MHVECTOR3& v1, const MHVECTOR3& v2, const MHVECTOR3& v3, float f, float g, MHVECTOR3& result)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat3( &v1 );
    XMVECTOR x2 = XMLoadFloat3( &v2 );
    XMVECTOR x3 = XMLoadFloat3( &v3 );
    XMVECTOR X = XMVectorBaryCentric( x1, x2, x3, f, g );
    XMStoreFloat3( &result, X );
}

inline MHVECTOR3 XM_CALLCONV MHVECTOR3::Barycentric(const MHVECTOR3& v1, const MHVECTOR3& v2, const MHVECTOR3& v3, float f, float g)
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

inline void XM_CALLCONV MHVECTOR3::CatmullRom(const MHVECTOR3& v1, const MHVECTOR3& v2, const MHVECTOR3& v3, const MHVECTOR3& v4, float t, MHVECTOR3& result)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat3( &v1 );
    XMVECTOR x2 = XMLoadFloat3( &v2 );
    XMVECTOR x3 = XMLoadFloat3( &v3 );
    XMVECTOR x4 = XMLoadFloat3( &v4 );
    XMVECTOR X = XMVectorCatmullRom( x1, x2, x3, x4, t );
    XMStoreFloat3( &result, X );
}

inline MHVECTOR3 XM_CALLCONV MHVECTOR3::CatmullRom(const MHVECTOR3& v1, const MHVECTOR3& v2, const MHVECTOR3& v3, const MHVECTOR3& v4, float t)
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

inline void XM_CALLCONV MHVECTOR3::Hermite(const MHVECTOR3& v1, const MHVECTOR3& t1, const MHVECTOR3& v2, const MHVECTOR3& t2, float t, MHVECTOR3& result)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat3( &v1 );
    XMVECTOR x2 = XMLoadFloat3( &t1 );
    XMVECTOR x3 = XMLoadFloat3( &v2 );
    XMVECTOR x4 = XMLoadFloat3( &t2 );
    XMVECTOR X = XMVectorHermite( x1, x2, x3, x4, t );
    XMStoreFloat3( &result, X );
}

inline MHVECTOR3 XM_CALLCONV MHVECTOR3::Hermite(const MHVECTOR3& v1, const MHVECTOR3& t1, const MHVECTOR3& v2, const MHVECTOR3& t2, float t)
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

inline void XM_CALLCONV MHVECTOR3::Reflect(const MHVECTOR3& ivec, const MHVECTOR3& nvec, MHVECTOR3& result)
{
    using namespace DirectX;
    XMVECTOR i = XMLoadFloat3( &ivec );
    XMVECTOR n = XMLoadFloat3( &nvec );
    XMVECTOR X = XMVector3Reflect( i, n );
    XMStoreFloat3( &result, X );
}

inline MHVECTOR3 XM_CALLCONV MHVECTOR3::Reflect(const MHVECTOR3& ivec, const MHVECTOR3& nvec)
{
    using namespace DirectX;
    XMVECTOR i = XMLoadFloat3( &ivec );
    XMVECTOR n = XMLoadFloat3( &nvec );
    XMVECTOR X = XMVector3Reflect( i, n );

    MHVECTOR3 result;
    XMStoreFloat3( &result, X );
    return result;
}

inline void XM_CALLCONV MHVECTOR3::Refract(const MHVECTOR3& ivec, const MHVECTOR3& nvec, float refractionIndex, MHVECTOR3& result)
{
    using namespace DirectX;
    XMVECTOR i = XMLoadFloat3( &ivec );
    XMVECTOR n = XMLoadFloat3( &nvec );
    XMVECTOR X = XMVector3Refract( i, n, refractionIndex );
    XMStoreFloat3( &result, X );
}

inline MHVECTOR3 XM_CALLCONV MHVECTOR3::Refract(const MHVECTOR3& ivec, const MHVECTOR3& nvec, float refractionIndex)
{
    using namespace DirectX;
    XMVECTOR i = XMLoadFloat3( &ivec );
    XMVECTOR n = XMLoadFloat3( &nvec );
    XMVECTOR X = XMVector3Refract( i, n, refractionIndex );

    MHVECTOR3 result;
    XMStoreFloat3( &result, X );
    return result;
}

inline void XM_CALLCONV MHVECTOR3::Transform(const MHVECTOR3& v, const MHQUATERNION& quat, MHVECTOR3& result)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3( &v );
    XMVECTOR q = XMLoadFloat4( &quat );
    XMVECTOR X = XMVector3Rotate( v1, q );
    XMStoreFloat3( &result, X );
}

inline MHVECTOR3 XM_CALLCONV MHVECTOR3::Transform(const MHVECTOR3& v, const MHQUATERNION& quat)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3( &v );
    XMVECTOR q = XMLoadFloat4( &quat );
    XMVECTOR X = XMVector3Rotate( v1, q );

    MHVECTOR3 result;
    XMStoreFloat3( &result, X );
    return result;
}

inline void XM_CALLCONV MHVECTOR3::Transform(const MHVECTOR3& v, const MHMATRIX& m, MHVECTOR3& result)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3( &v );
    XMMATRIX M = XMLoadFloat4x4( &m );
    XMVECTOR X = XMVector3TransformCoord( v1, M );
    XMStoreFloat3( &result, X );
}

inline MHVECTOR3 XM_CALLCONV MHVECTOR3::Transform(const MHVECTOR3& v, const MHMATRIX& m)
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
inline void XM_CALLCONV MHVECTOR3::Transform(const MHVECTOR3* varray, size_t count, const MHMATRIX& m, MHVECTOR3* resultArray)
{
    using namespace DirectX;
    XMMATRIX M = XMLoadFloat4x4( &m );
    XMVector3TransformCoordStream( resultArray, sizeof(XMFLOAT3), varray, sizeof(XMFLOAT3), count, M );
}

inline void XM_CALLCONV MHVECTOR3::Transform(const MHVECTOR3& v, const MHMATRIX& m, MHVECTOR4& result)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3( &v );
    XMMATRIX M = XMLoadFloat4x4( &m );
    XMVECTOR X = XMVector3Transform( v1, M );
    XMStoreFloat4( &result, X );
}

_Use_decl_annotations_
inline void XM_CALLCONV MHVECTOR3::Transform(const MHVECTOR3* varray, size_t count, const MHMATRIX& m, MHVECTOR4* resultArray)
{
    using namespace DirectX;
    XMMATRIX M = XMLoadFloat4x4( &m );
    XMVector3TransformStream( resultArray, sizeof(XMFLOAT4), varray, sizeof(XMFLOAT3), count, M );
}

inline void XM_CALLCONV MHVECTOR3::TransformNormal(const MHVECTOR3& v, const MHMATRIX& m, MHVECTOR3& result)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3( &v );
    XMMATRIX M = XMLoadFloat4x4( &m );
    XMVECTOR X = XMVector3TransformNormal( v1, M );
    XMStoreFloat3( &result, X );
}

inline MHVECTOR3 XM_CALLCONV MHVECTOR3::TransformNormal(const MHVECTOR3& v, const MHMATRIX& m)
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
inline void XM_CALLCONV MHVECTOR3::TransformNormal(const MHVECTOR3* varray, size_t count, const MHMATRIX& m, MHVECTOR3* resultArray)
{
    using namespace DirectX;
    XMMATRIX M = XMLoadFloat4x4( &m );
    XMVector3TransformNormalStream( resultArray, sizeof(XMFLOAT3), varray, sizeof(XMFLOAT3), count, M );
}

#	pragma endregion

/****************************************************************************
 *
 * MHVECTOR4
 *
 ****************************************************************************/
#	pragma region MHVECTOR4

//------------------------------------------------------------------------------
// Comparision operators
//------------------------------------------------------------------------------

inline bool XM_CALLCONV MHVECTOR4::operator == (const MHVECTOR4& V) const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat4( this );
    XMVECTOR v2 = XMLoadFloat4( &V );
    return XMVector4Equal( v1, v2 );
}

inline bool XM_CALLCONV MHVECTOR4::operator != (const MHVECTOR4& V) const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat4( this );
    XMVECTOR v2 = XMLoadFloat4( &V );
    return XMVector4NotEqual( v1, v2 );
}

//------------------------------------------------------------------------------
// Assignment operators
//------------------------------------------------------------------------------

inline MHVECTOR4& XM_CALLCONV MHVECTOR4::operator+= (const MHVECTOR4& V)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat4( this );
    XMVECTOR v2 = XMLoadFloat4( &V );
    XMVECTOR X = XMVectorAdd(v1,v2);
    XMStoreFloat4( this, X );
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

inline MHVECTOR4& XM_CALLCONV MHVECTOR4::operator-= (const MHVECTOR4& V)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat4( this );
    XMVECTOR v2 = XMLoadFloat4( &V );
    XMVECTOR X = XMVectorSubtract(v1,v2);
    XMStoreFloat4( this, X );
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

inline MHVECTOR4& XM_CALLCONV MHVECTOR4::operator*= (const MHVECTOR4& V)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat4( this );
    XMVECTOR v2 = XMLoadFloat4( &V );
    XMVECTOR X = XMVectorMultiply(v1,v2);
    XMStoreFloat4( this, X );
    return *this;
}

inline MHVECTOR4& XM_CALLCONV MHVECTOR4::operator*= (float S)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat4( this );
    XMVECTOR X = XMVectorScale(v1,S);
    XMStoreFloat4( this, X );
    return *this;
} 

inline MHVECTOR4& XM_CALLCONV MHVECTOR4::operator/= (const MHVECTOR4& V)
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
    assert( S != 0.0f );
    XMVECTOR v1 = XMLoadFloat4( this );
    XMVECTOR X = XMVectorScale(v1, 1.f/S);
    XMStoreFloat4( this, X );
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
    XMVECTOR v1 = XMLoadFloat4( this );
    XMVECTOR X = XMVectorNegate( v1 );
    MHVECTOR4 R;
    XMStoreFloat4( &R, X );
    return R;
}

//------------------------------------------------------------------------------
// Binary operators
//------------------------------------------------------------------------------

inline MHVECTOR4 XM_CALLCONV operator+ (const MHVECTOR4& V1, const MHVECTOR4& V2)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat4( &V1 );
    XMVECTOR v2 = XMLoadFloat4( &V2 );
    XMVECTOR X = XMVectorAdd(v1,v2);
    MHVECTOR4 R;
    XMStoreFloat4( &R, X );
    return R;
}

inline MHVECTOR4 XM_CALLCONV operator+ (const MHVECTOR4& V, float S)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(&V);
	XMVECTOR v2 = XMLoadFloat(&S);
	XMVECTOR X = XMVectorAdd(v1, v2);
	MHVECTOR4 R;
	XMStoreFloat4(&R, X);
	return R;
}

inline MHVECTOR4 XM_CALLCONV operator+ (float S, const MHVECTOR4& V)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat(&S);
	XMVECTOR v2 = XMLoadFloat4(&V);
	XMVECTOR X = XMVectorAdd(v1, v2);
	MHVECTOR4 R;
	XMStoreFloat4(&R, X);
	return R;
}

inline MHVECTOR4 XM_CALLCONV operator- (const MHVECTOR4& V1, const MHVECTOR4& V2)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat4( &V1 );
    XMVECTOR v2 = XMLoadFloat4( &V2 );
    XMVECTOR X = XMVectorSubtract(v1,v2);
    MHVECTOR4 R;
    XMStoreFloat4( &R, X );
    return R;
}

inline MHVECTOR4 XM_CALLCONV operator- (const MHVECTOR4& V, float S)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(&V);
	XMVECTOR v2 = XMLoadFloat(&S);
	XMVECTOR X = XMVectorSubtract(v1, v2);
	MHVECTOR4 R;
	XMStoreFloat4(&R, X);
	return R;
}

inline MHVECTOR4 XM_CALLCONV operator- (float S, const MHVECTOR4& V)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat(&S);
	XMVECTOR v2 = XMLoadFloat4(&V);
	XMVECTOR X = XMVectorSubtract(v1, v2);
	MHVECTOR4 R;
	XMStoreFloat4(&R, X);
	return R;
}

inline MHVECTOR4 XM_CALLCONV operator* (const MHVECTOR4& V1, const MHVECTOR4& V2)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat4( &V1 );
    XMVECTOR v2 = XMLoadFloat4( &V2 );
    XMVECTOR X = XMVectorMultiply(v1,v2);
    MHVECTOR4 R;
    XMStoreFloat4( &R, X );
    return R;
}

inline MHVECTOR4 XM_CALLCONV operator* (const MHVECTOR4& V, float S)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat4( &V );
    XMVECTOR X = XMVectorScale(v1, S);
    MHVECTOR4 R;
    XMStoreFloat4( &R, X );
    return R;
}

inline MHVECTOR4 XM_CALLCONV operator* (float S, const MHVECTOR4& V)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(&V);
	XMVECTOR X = XMVectorScale(v1, S);
	MHVECTOR4 R;
	XMStoreFloat4(&R, X);
	return R;
}

inline MHVECTOR4 XM_CALLCONV operator/ (const MHVECTOR4& V1, const MHVECTOR4& V2)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat4( &V1 );
    XMVECTOR v2 = XMLoadFloat4( &V2 );
    XMVECTOR X = XMVectorDivide(v1, v2);
    MHVECTOR4 R;
    XMStoreFloat4( &R, X );
    return R;
}

inline MHVECTOR4 XM_CALLCONV operator/ (const MHVECTOR4& V, float S)
{
	using namespace DirectX;
	assert(S != 0.0f);
	XMVECTOR v1 = XMLoadFloat4(&V);
	XMVECTOR X = XMVectorScale(v1, 1.f / S);
	MHVECTOR4 R;
	XMStoreFloat4(&R, X);
	return R;
}

inline MHVECTOR4 XM_CALLCONV operator/ (float S, const MHVECTOR4& V)
{
	using namespace DirectX;
	assert(S != 0.0f);
	XMVECTOR v1 = XMLoadFloat4(&V);
	XMVECTOR X = XMVectorScale(v1, 1.f / S);
	MHVECTOR4 R;
	XMStoreFloat4(&R, X);
	return R;
}


//------------------------------------------------------------------------------
// Vector operations
//------------------------------------------------------------------------------

inline bool XM_CALLCONV MHVECTOR4::VInBounds(const MHVECTOR4& Bounds) const
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

inline float XM_CALLCONV MHVECTOR4::VDot(const MHVECTOR4& V) const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat4( this );
    XMVECTOR v2 = XMLoadFloat4( &V );
    XMVECTOR X = XMVector4Dot( v1, v2 );
    return XMVectorGetX( X );
}

inline void XM_CALLCONV MHVECTOR4::VCross(const MHVECTOR4& v1, const MHVECTOR4& v2, MHVECTOR4& result) const
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4( this );
    XMVECTOR x2 = XMLoadFloat4( &v1 );
    XMVECTOR x3 = XMLoadFloat4( &v2 );
    XMVECTOR R = XMVector4Cross( x1, x2, x3 );
    XMStoreFloat4( &result, R );
}

inline MHVECTOR4 XM_CALLCONV MHVECTOR4::VCross(const MHVECTOR4& v1, const MHVECTOR4& v2) const
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

inline void XM_CALLCONV MHVECTOR4::VClamp(const MHVECTOR4& vmin, const MHVECTOR4& vmax)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat4( this );
    XMVECTOR v2 = XMLoadFloat4( &vmin );
    XMVECTOR v3 = XMLoadFloat4( &vmax );
    XMVECTOR X = XMVectorClamp( v1, v2, v3 );
    XMStoreFloat4( this, X );
}

inline void XM_CALLCONV MHVECTOR4::VClamp(const MHVECTOR4& vmin, const MHVECTOR4& vmax, MHVECTOR4& result) const
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

inline bool XM_CALLCONV MHVECTOR4::InBounds(const MHVECTOR4& V, const MHVECTOR4& Bounds)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(&V);
	XMVECTOR v2 = XMLoadFloat4(&Bounds);
	return XMVector4InBounds(v1, v2);
}

inline float XM_CALLCONV MHVECTOR4::Length(const MHVECTOR4& V)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(&V);
	XMVECTOR X = XMVector4Length(v1);
	return XMVectorGetX(X);
}

inline float XM_CALLCONV MHVECTOR4::LengthSquared(const MHVECTOR4& V)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(&V);
	XMVECTOR X = XMVector4LengthSq(v1);
	return XMVectorGetX(X);
}

inline float XM_CALLCONV MHVECTOR4::Dot(const MHVECTOR4& V1, const MHVECTOR4& V2)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(&V1);
	XMVECTOR v2 = XMLoadFloat4(&V2);
	XMVECTOR X = XMVector4Dot(v1, v2);
	return XMVectorGetX(X);
}

inline MHVECTOR4 XM_CALLCONV MHVECTOR4::Cross(const MHVECTOR4& V1, const MHVECTOR4& V2, const MHVECTOR4& V3)
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

inline void XM_CALLCONV MHVECTOR4::Cross(const MHVECTOR4& V1, const MHVECTOR4& V2, const MHVECTOR4& V3, MHVECTOR4& result)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(&V1);
	XMVECTOR v2 = XMLoadFloat4(&V2);
	XMVECTOR v3 = XMLoadFloat4(&V3);
	XMVECTOR R = XMVector4Cross(v1, v2, v3);
	XMStoreFloat4(&result, R);
}

inline MHVECTOR4 XM_CALLCONV MHVECTOR4::Normalize(const MHVECTOR4& V)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(&V);
	XMVECTOR X = XMVector4Normalize(v1);

	MHVECTOR4 result;
	XMStoreFloat4(&result, X);
	return result;
}

inline void XM_CALLCONV MHVECTOR4::Normalize(const MHVECTOR4& V, MHVECTOR4& result)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(&V);
	XMVECTOR X = XMVector4Normalize(v1);
	XMStoreFloat4(&result, X);
}

inline MHVECTOR4 XM_CALLCONV MHVECTOR4::Clamp(MHVECTOR4& V, const MHVECTOR4& vmin, const MHVECTOR4& vmax)
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

inline void XM_CALLCONV MHVECTOR4::Clamp(const MHVECTOR4& V, const MHVECTOR4& vmin, const MHVECTOR4& vmax, MHVECTOR4& result)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(&V);
	XMVECTOR v2 = XMLoadFloat4(&vmin);
	XMVECTOR v3 = XMLoadFloat4(&vmax);
	XMVECTOR X = XMVectorClamp(v1, v2, v3);
	XMStoreFloat4(&result, X);
}

inline MHVECTOR4 XM_CALLCONV MHVECTOR4::ClampLength(MHVECTOR4& V, float LengthMin, float LengthMax)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(&V);
	XMVECTOR X = XMVector4ClampLength(v1, LengthMin, LengthMax);

	MHVECTOR4 result;
	XMStoreFloat4(&result, X);
	return result;
}

inline void XM_CALLCONV MHVECTOR4::ClampLength(const MHVECTOR4& V, float LengthMin, float LengthMax, MHVECTOR4& result)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(&V);
	XMVECTOR X = XMVector4ClampLength(v1, LengthMin, LengthMax);
	XMStoreFloat4(&result, X);
}

inline float XM_CALLCONV MHVECTOR4::Distance(const MHVECTOR4& v1, const MHVECTOR4& v2)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4( &v1 );
    XMVECTOR x2 = XMLoadFloat4( &v2 );
    XMVECTOR V = XMVectorSubtract( x2, x1 );
    XMVECTOR X = XMVector4Length( V );
    return XMVectorGetX( X );
}

inline float XM_CALLCONV MHVECTOR4::DistanceSquared(const MHVECTOR4& v1, const MHVECTOR4& v2)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4( &v1 );
    XMVECTOR x2 = XMLoadFloat4( &v2 );
    XMVECTOR V = XMVectorSubtract( x2, x1 );
    XMVECTOR X = XMVector4LengthSq( V );
    return XMVectorGetX( X );
}

inline void XM_CALLCONV MHVECTOR4::Min(const MHVECTOR4& v1, const MHVECTOR4& v2, MHVECTOR4& result)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4( &v1 );
    XMVECTOR x2 = XMLoadFloat4( &v2 );
    XMVECTOR X = XMVectorMin( x1, x2 );
    XMStoreFloat4( &result, X );
}

inline MHVECTOR4 XM_CALLCONV MHVECTOR4::Min(const MHVECTOR4& v1, const MHVECTOR4& v2)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4( &v1 );
    XMVECTOR x2 = XMLoadFloat4( &v2 );
    XMVECTOR X = XMVectorMin( x1, x2 );

    MHVECTOR4 result;
    XMStoreFloat4( &result, X );
    return result;
}

inline void XM_CALLCONV MHVECTOR4::Max(const MHVECTOR4& v1, const MHVECTOR4& v2, MHVECTOR4& result)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4( &v1 );
    XMVECTOR x2 = XMLoadFloat4( &v2 );
    XMVECTOR X = XMVectorMax( x1, x2 );
    XMStoreFloat4( &result, X );
}

inline MHVECTOR4 XM_CALLCONV MHVECTOR4::Max(const MHVECTOR4& v1, const MHVECTOR4& v2)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4( &v1 );
    XMVECTOR x2 = XMLoadFloat4( &v2 );
    XMVECTOR X = XMVectorMax( x1, x2 );

    MHVECTOR4 result;
    XMStoreFloat4( &result, X );
    return result;
}

inline void XM_CALLCONV MHVECTOR4::Lerp(const MHVECTOR4& v1, const MHVECTOR4& v2, float t, MHVECTOR4& result)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4( &v1 );
    XMVECTOR x2 = XMLoadFloat4( &v2 );
    XMVECTOR X = XMVectorLerp( x1, x2, t );
    XMStoreFloat4( &result, X );
}

inline MHVECTOR4 XM_CALLCONV MHVECTOR4::Lerp(const MHVECTOR4& v1, const MHVECTOR4& v2, float t)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4( &v1 );
    XMVECTOR x2 = XMLoadFloat4( &v2 );
    XMVECTOR X = XMVectorLerp( x1, x2, t );

    MHVECTOR4 result;
    XMStoreFloat4( &result, X );
    return result;
}

inline void XM_CALLCONV MHVECTOR4::SmoothStep(const MHVECTOR4& v1, const MHVECTOR4& v2, float t, MHVECTOR4& result)
{
    using namespace DirectX;
    t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);  // Clamp value to 0 to 1
    t = t*t*(3.f - 2.f*t);
    XMVECTOR x1 = XMLoadFloat4( &v1 );
    XMVECTOR x2 = XMLoadFloat4( &v2 );
    XMVECTOR X = XMVectorLerp( x1, x2, t );
    XMStoreFloat4( &result, X );
}

inline MHVECTOR4 XM_CALLCONV MHVECTOR4::SmoothStep(const MHVECTOR4& v1, const MHVECTOR4& v2, float t)
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

inline void XM_CALLCONV MHVECTOR4::Barycentric(const MHVECTOR4& v1, const MHVECTOR4& v2, const MHVECTOR4& v3, float f, float g, MHVECTOR4& result)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4( &v1 );
    XMVECTOR x2 = XMLoadFloat4( &v2 );
    XMVECTOR x3 = XMLoadFloat4( &v3 );
    XMVECTOR X = XMVectorBaryCentric( x1, x2, x3, f, g );
    XMStoreFloat4( &result, X );
}

inline MHVECTOR4 XM_CALLCONV MHVECTOR4::Barycentric(const MHVECTOR4& v1, const MHVECTOR4& v2, const MHVECTOR4& v3, float f, float g)
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

inline void XM_CALLCONV MHVECTOR4::CatmullRom(const MHVECTOR4& v1, const MHVECTOR4& v2, const MHVECTOR4& v3, const MHVECTOR4& v4, float t, MHVECTOR4& result)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4( &v1 );
    XMVECTOR x2 = XMLoadFloat4( &v2 );
    XMVECTOR x3 = XMLoadFloat4( &v3 );
    XMVECTOR x4 = XMLoadFloat4( &v4 );
    XMVECTOR X = XMVectorCatmullRom( x1, x2, x3, x4, t );
    XMStoreFloat4( &result, X );
}

inline MHVECTOR4 XM_CALLCONV MHVECTOR4::CatmullRom(const MHVECTOR4& v1, const MHVECTOR4& v2, const MHVECTOR4& v3, const MHVECTOR4& v4, float t)
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

inline void XM_CALLCONV MHVECTOR4::Hermite(const MHVECTOR4& v1, const MHVECTOR4& t1, const MHVECTOR4& v2, const MHVECTOR4& t2, float t, MHVECTOR4& result)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4( &v1 );
    XMVECTOR x2 = XMLoadFloat4( &t1 );
    XMVECTOR x3 = XMLoadFloat4( &v2 );
    XMVECTOR x4 = XMLoadFloat4( &t2 );
    XMVECTOR X = XMVectorHermite( x1, x2, x3, x4, t );
    XMStoreFloat4( &result, X );
}

inline MHVECTOR4 XM_CALLCONV MHVECTOR4::Hermite(const MHVECTOR4& v1, const MHVECTOR4& t1, const MHVECTOR4& v2, const MHVECTOR4& t2, float t)
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

inline void XM_CALLCONV MHVECTOR4::Reflect(const MHVECTOR4& ivec, const MHVECTOR4& nvec, MHVECTOR4& result)
{
    using namespace DirectX;
    XMVECTOR i = XMLoadFloat4( &ivec );
    XMVECTOR n = XMLoadFloat4( &nvec );
    XMVECTOR X = XMVector4Reflect( i, n );
    XMStoreFloat4( &result, X );
}

inline MHVECTOR4 XM_CALLCONV MHVECTOR4::Reflect(const MHVECTOR4& ivec, const MHVECTOR4& nvec)
{
    using namespace DirectX;
    XMVECTOR i = XMLoadFloat4( &ivec );
    XMVECTOR n = XMLoadFloat4( &nvec );
    XMVECTOR X = XMVector4Reflect( i, n );

    MHVECTOR4 result;
    XMStoreFloat4( &result, X );
    return result;
}

inline void XM_CALLCONV MHVECTOR4::Refract(const MHVECTOR4& ivec, const MHVECTOR4& nvec, float refractionIndex, MHVECTOR4& result)
{
    using namespace DirectX;
    XMVECTOR i = XMLoadFloat4( &ivec );
    XMVECTOR n = XMLoadFloat4( &nvec );
    XMVECTOR X = XMVector4Refract( i, n, refractionIndex );
    XMStoreFloat4( &result, X );
}

inline MHVECTOR4 XM_CALLCONV MHVECTOR4::Refract(const MHVECTOR4& ivec, const MHVECTOR4& nvec, float refractionIndex)
{
    using namespace DirectX;
    XMVECTOR i = XMLoadFloat4( &ivec );
    XMVECTOR n = XMLoadFloat4( &nvec );
    XMVECTOR X = XMVector4Refract( i, n, refractionIndex );

    MHVECTOR4 result;
    XMStoreFloat4( &result, X );
    return result;
}

inline void XM_CALLCONV MHVECTOR4::Transform(const MHVECTOR2& v, const MHQUATERNION& quat, MHVECTOR4& result)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2( &v );
    XMVECTOR q = XMLoadFloat4( &quat );
    XMVECTOR X = XMVector3Rotate( v1, q );
    X = XMVectorSelect( g_XMIdentityR3, X, g_XMSelect1110 ); // result.w = 1.f
    XMStoreFloat4( &result, X );
}

inline MHVECTOR4 XM_CALLCONV MHVECTOR4::Transform(const MHVECTOR2& v, const MHQUATERNION& quat)
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

inline void XM_CALLCONV MHVECTOR4::Transform(const MHVECTOR3& v, const MHQUATERNION& quat, MHVECTOR4& result)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3( &v );
    XMVECTOR q = XMLoadFloat4( &quat );
    XMVECTOR X = XMVector3Rotate( v1, q );
    X = XMVectorSelect( g_XMIdentityR3, X, g_XMSelect1110 ); // result.w = 1.f
    XMStoreFloat4( &result, X );
}

inline MHVECTOR4 XM_CALLCONV MHVECTOR4::Transform(const MHVECTOR3& v, const MHQUATERNION& quat)
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

inline void XM_CALLCONV MHVECTOR4::Transform(const MHVECTOR4& v, const MHQUATERNION& quat, MHVECTOR4& result)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat4( &v );
    XMVECTOR q = XMLoadFloat4( &quat );
    XMVECTOR X = XMVector3Rotate( v1, q );
    X = XMVectorSelect( v1, X, g_XMSelect1110 ); // result.w = v.w
    XMStoreFloat4( &result, X );
}

inline MHVECTOR4 XM_CALLCONV MHVECTOR4::Transform(const MHVECTOR4& v, const MHQUATERNION& quat)
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

inline void XM_CALLCONV MHVECTOR4::Transform(const MHVECTOR4& v, const MHMATRIX& m, MHVECTOR4& result)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat4( &v );
    XMMATRIX M = XMLoadFloat4x4( &m );
    XMVECTOR X = XMVector4Transform( v1, M );
    XMStoreFloat4( &result, X );
}

inline MHVECTOR4 XM_CALLCONV MHVECTOR4::Transform(const MHVECTOR4& v, const MHMATRIX& m)
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
inline void XM_CALLCONV MHVECTOR4::Transform(const MHVECTOR4* varray, size_t count, const MHMATRIX& m, MHVECTOR4* resultArray)
{
    using namespace DirectX;
    XMMATRIX M = XMLoadFloat4x4( &m );
    XMVector4TransformStream( resultArray, sizeof(XMFLOAT4), varray, sizeof(XMFLOAT4), count, M );
}

#	pragma endregion

/****************************************************************************
 *
 * MHMATRIX
 *
 ****************************************************************************/
#	pragma region MHMATRIX

//------------------------------------------------------------------------------
// Comparision operators
//------------------------------------------------------------------------------

inline bool XM_CALLCONV MHMATRIX::operator == (const MHMATRIX& M) const
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&_11) );
    XMVECTOR x2 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&_21) );
    XMVECTOR x3 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&_31) );
    XMVECTOR x4 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&_41) );

    XMVECTOR y1 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M._11) );
    XMVECTOR y2 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M._21) );
    XMVECTOR y3 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M._31) );
    XMVECTOR y4 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M._41) );

    return ( XMVector4Equal( x1, y1 )
             && XMVector4Equal( x2, y2 )
             && XMVector4Equal( x3, y3 )
             && XMVector4Equal( x4, y4 ) ) != 0;
}

inline bool XM_CALLCONV MHMATRIX::operator != (const MHMATRIX& M) const
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&_11) );
    XMVECTOR x2 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&_21) );
    XMVECTOR x3 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&_31) );
    XMVECTOR x4 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&_41) );

    XMVECTOR y1 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M._11) );
    XMVECTOR y2 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M._21) );
    XMVECTOR y3 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M._31) );
    XMVECTOR y4 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M._41) );

    return ( XMVector4NotEqual( x1, y1 )
             && XMVector4NotEqual( x2, y2 )
             && XMVector4NotEqual( x3, y3 )
             && XMVector4NotEqual( x4, y4 ) ) != 0;
}

//------------------------------------------------------------------------------
// Assignment operators
//------------------------------------------------------------------------------

inline MHMATRIX& XM_CALLCONV MHMATRIX::operator+= (const MHMATRIX& M)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4( reinterpret_cast<XMFLOAT4*>(&_11) );
    XMVECTOR x2 = XMLoadFloat4( reinterpret_cast<XMFLOAT4*>(&_21) );
    XMVECTOR x3 = XMLoadFloat4( reinterpret_cast<XMFLOAT4*>(&_31) );
    XMVECTOR x4 = XMLoadFloat4( reinterpret_cast<XMFLOAT4*>(&_41) );

    XMVECTOR y1 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M._11) );
    XMVECTOR y2 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M._21) );
    XMVECTOR y3 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M._31) );
    XMVECTOR y4 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M._41) );

    x1 = XMVectorAdd( x1, y1 );
    x2 = XMVectorAdd( x2, y2 );
    x3 = XMVectorAdd( x3, y3 );
    x4 = XMVectorAdd( x4, y4 );

    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&_11), x1 );
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&_21), x2 );
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&_31), x3 );
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&_41), x4 );
    return *this;
}

inline MHMATRIX& XM_CALLCONV MHMATRIX::operator+= (float S)
{
	using namespace DirectX;
	XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<XMFLOAT4*>(&_11));
	XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<XMFLOAT4*>(&_21));
	XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<XMFLOAT4*>(&_31));
	XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<XMFLOAT4*>(&_41));

	XMVECTOR y1 = XMLoadFloat(&S);
	XMVECTOR y2 = XMLoadFloat(&S);
	XMVECTOR y3 = XMLoadFloat(&S);
	XMVECTOR y4 = XMLoadFloat(&S);

	x1 = XMVectorAdd(x1, y1);
	x2 = XMVectorAdd(x2, y2);
	x3 = XMVectorAdd(x3, y3);
	x4 = XMVectorAdd(x4, y4);

	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_11), x1);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_21), x2);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_31), x3);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_41), x4);
	return *this;
}

inline MHMATRIX& XM_CALLCONV MHMATRIX::operator-= (const MHMATRIX& M)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4( reinterpret_cast<XMFLOAT4*>(&_11) );
    XMVECTOR x2 = XMLoadFloat4( reinterpret_cast<XMFLOAT4*>(&_21) );
    XMVECTOR x3 = XMLoadFloat4( reinterpret_cast<XMFLOAT4*>(&_31) );
    XMVECTOR x4 = XMLoadFloat4( reinterpret_cast<XMFLOAT4*>(&_41) );

    XMVECTOR y1 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M._11) );
    XMVECTOR y2 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M._21) );
    XMVECTOR y3 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M._31) );
    XMVECTOR y4 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M._41) );

    x1 = XMVectorSubtract( x1, y1 );
    x2 = XMVectorSubtract( x2, y2 );
    x3 = XMVectorSubtract( x3, y3 );
    x4 = XMVectorSubtract( x4, y4 );

    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&_11), x1 );
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&_21), x2 );
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&_31), x3 );
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&_41), x4 );
    return *this;
}

inline MHMATRIX& XM_CALLCONV MHMATRIX::operator-= (float S)
{
	using namespace DirectX;
	XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<XMFLOAT4*>(&_11));
	XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<XMFLOAT4*>(&_21));
	XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<XMFLOAT4*>(&_31));
	XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<XMFLOAT4*>(&_41));

	XMVECTOR y1 = XMLoadFloat(&S);
	XMVECTOR y2 = XMLoadFloat(&S);
	XMVECTOR y3 = XMLoadFloat(&S);
	XMVECTOR y4 = XMLoadFloat(&S);

	x1 = XMVectorSubtract(x1, y1);
	x2 = XMVectorSubtract(x2, y2);
	x3 = XMVectorSubtract(x3, y3);
	x4 = XMVectorSubtract(x4, y4);

	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_11), x1);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_21), x2);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_31), x3);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_41), x4);
	return *this;
}

inline MHMATRIX& XM_CALLCONV MHMATRIX::operator*= (const MHMATRIX& M)
{
    using namespace DirectX;
    XMMATRIX M1 = XMLoadFloat4x4( this );
    XMMATRIX M2 = XMLoadFloat4x4( &M );
    XMMATRIX X = XMMatrixMultiply( M1, M2 );
    XMStoreFloat4x4( this, X );
    return *this;
}

inline MHMATRIX& XM_CALLCONV MHMATRIX::operator*= (float S)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4( reinterpret_cast<XMFLOAT4*>(&_11) );
    XMVECTOR x2 = XMLoadFloat4( reinterpret_cast<XMFLOAT4*>(&_21) );
    XMVECTOR x3 = XMLoadFloat4( reinterpret_cast<XMFLOAT4*>(&_31) );
    XMVECTOR x4 = XMLoadFloat4( reinterpret_cast<XMFLOAT4*>(&_41) );

    x1 = XMVectorScale( x1, S );
    x2 = XMVectorScale( x2, S );
    x3 = XMVectorScale( x3, S );
    x4 = XMVectorScale( x4, S );

    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&_11), x1 );
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&_21), x2 );
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&_31), x3 );
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&_41), x4 );
    return *this;
}

inline MHMATRIX& XM_CALLCONV MHMATRIX::operator/= (const MHMATRIX& M)
{
	using namespace DirectX;
	XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<XMFLOAT4*>(&_11));
	XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<XMFLOAT4*>(&_21));
	XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<XMFLOAT4*>(&_31));
	XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<XMFLOAT4*>(&_41));

	XMVECTOR y1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._11));
	XMVECTOR y2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._21));
	XMVECTOR y3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._31));
	XMVECTOR y4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._41));

	x1 = XMVectorDivide(x1, y1);
	x2 = XMVectorDivide(x2, y2);
	x3 = XMVectorDivide(x3, y3);
	x4 = XMVectorDivide(x4, y4);

	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_11), x1);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_21), x2);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_31), x3);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_41), x4);
	return *this;
}

inline MHMATRIX& XM_CALLCONV MHMATRIX::operator/= (float S)
{
    using namespace DirectX;
    assert( S != 0.f );
    XMVECTOR x1 = XMLoadFloat4( reinterpret_cast<XMFLOAT4*>(&_11) );
    XMVECTOR x2 = XMLoadFloat4( reinterpret_cast<XMFLOAT4*>(&_21) );
    XMVECTOR x3 = XMLoadFloat4( reinterpret_cast<XMFLOAT4*>(&_31) );
    XMVECTOR x4 = XMLoadFloat4( reinterpret_cast<XMFLOAT4*>(&_41) );

    float rs = 1.f / S;

    x1 = XMVectorScale( x1, rs );
    x2 = XMVectorScale( x2, rs );
    x3 = XMVectorScale( x3, rs );
    x4 = XMVectorScale( x4, rs );

    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&_11), x1 );
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&_21), x2 );
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&_31), x3 );
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&_41), x4 );
    return *this;
}

//------------------------------------------------------------------------------
// Urnary operators
//------------------------------------------------------------------------------

/*
inline MHMATRIX XM_CALLCONV MHMATRIX::operator+ () const
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_11));
	XMVECTOR v2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_21));
	XMVECTOR v3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_31));
	XMVECTOR v4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_41));

	v1 = +v1;
	v2 = +v2;
	v3 = +v3;
	v4 = +v4;

	MHMATRIX R;
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._11), v1);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._21), v2);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._31), v3);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._41), v4);
	return R;
}*/

inline MHMATRIX XM_CALLCONV MHMATRIX::operator- () const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&_11) );
    XMVECTOR v2 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&_21) );
    XMVECTOR v3 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&_31) );
    XMVECTOR v4 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&_41) );

    v1 = XMVectorNegate( v1 );
    v2 = XMVectorNegate( v2 );
    v3 = XMVectorNegate( v3 );
    v4 = XMVectorNegate( v4 );

    MHMATRIX R;
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&R._11), v1 );
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&R._21), v2 );
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&R._31), v3 );
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&R._41), v4 );
    return R;
}

//------------------------------------------------------------------------------
// Binary operators
//------------------------------------------------------------------------------

inline MHMATRIX XM_CALLCONV operator+ (const MHMATRIX& M1, const MHMATRIX& M2)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M1._11) );
    XMVECTOR x2 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M1._21) );
    XMVECTOR x3 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M1._31) );
    XMVECTOR x4 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M1._41) );

    XMVECTOR y1 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M2._11) );
    XMVECTOR y2 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M2._21) );
    XMVECTOR y3 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M2._31) );
    XMVECTOR y4 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M2._41) );

    x1 = XMVectorAdd( x1, y1 );
    x2 = XMVectorAdd( x2, y2 );
    x3 = XMVectorAdd( x3, y3 );
    x4 = XMVectorAdd( x4, y4 );

    MHMATRIX R;
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&R._11), x1 );
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&R._21), x2 );
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&R._31), x3 );
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&R._41), x4 );
    return R;
}

inline MHMATRIX XM_CALLCONV operator+ (const MHMATRIX& M, float S)
{
	using namespace DirectX;
	XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._11));
	XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._21));
	XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._31));
	XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._41));

	XMVECTOR v1 = XMLoadFloat(&S);
	XMVECTOR v2 = XMLoadFloat(&S);
	XMVECTOR v3 = XMLoadFloat(&S);
	XMVECTOR v4 = XMLoadFloat(&S);

	x1 = XMVectorAdd(x1, v1);
	x2 = XMVectorAdd(x2, v2);
	x3 = XMVectorAdd(x3, v3);
	x4 = XMVectorAdd(x4, v4);

	MHMATRIX R;
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._11), x1);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._21), x2);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._31), x3);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._41), x4);
	return R;
}

inline MHMATRIX XM_CALLCONV operator+ (float S, const MHMATRIX& M)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._11));
	XMVECTOR v2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._21));
	XMVECTOR v3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._31));
	XMVECTOR v4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._41));

	XMVECTOR x1 = XMLoadFloat(&S);
	XMVECTOR x2 = XMLoadFloat(&S);
	XMVECTOR x3 = XMLoadFloat(&S);
	XMVECTOR x4 = XMLoadFloat(&S);

	x1 = XMVectorAdd(x1, v1);
	x2 = XMVectorAdd(x2, v2);
	x3 = XMVectorAdd(x3, v3);
	x4 = XMVectorAdd(x4, v4);

	MHMATRIX R;
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._11), x1);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._21), x2);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._31), x3);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._41), x4);
	return R;
}

inline MHMATRIX XM_CALLCONV operator- (const MHMATRIX& M1, const MHMATRIX& M2)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M1._11) );
    XMVECTOR x2 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M1._21) );
    XMVECTOR x3 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M1._31) );
    XMVECTOR x4 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M1._41) );

    XMVECTOR y1 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M2._11) );
    XMVECTOR y2 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M2._21) );
    XMVECTOR y3 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M2._31) );
    XMVECTOR y4 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M2._41) );

    x1 = XMVectorSubtract( x1, y1 );
    x2 = XMVectorSubtract( x2, y2 );
    x3 = XMVectorSubtract( x3, y3 );
    x4 = XMVectorSubtract( x4, y4 );

    MHMATRIX R;
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&R._11), x1 );
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&R._21), x2 );
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&R._31), x3 );
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&R._41), x4 );
    return R;
}

inline MHMATRIX XM_CALLCONV operator- (const MHMATRIX& M, float S)
{
	using namespace DirectX;
	XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._11));
	XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._21));
	XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._31));
	XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._41));

	XMVECTOR v1 = XMLoadFloat(&S);
	XMVECTOR v2 = XMLoadFloat(&S);
	XMVECTOR v3 = XMLoadFloat(&S);
	XMVECTOR v4 = XMLoadFloat(&S);

	x1 = XMVectorSubtract(x1, v1);
	x2 = XMVectorSubtract(x2, v2);
	x3 = XMVectorSubtract(x3, v3);
	x4 = XMVectorSubtract(x4, v4);

	MHMATRIX R;
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._11), x1);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._21), x2);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._31), x3);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._41), x4);
	return R;
}

inline MHMATRIX XM_CALLCONV operator- (float S, const MHMATRIX& M)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._11));
	XMVECTOR v2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._21));
	XMVECTOR v3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._31));
	XMVECTOR v4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._41));

	XMVECTOR x1 = XMLoadFloat(&S);
	XMVECTOR x2 = XMLoadFloat(&S);
	XMVECTOR x3 = XMLoadFloat(&S);
	XMVECTOR x4 = XMLoadFloat(&S);

	x1 = XMVectorSubtract(x1, v1);
	x2 = XMVectorSubtract(x2, v2);
	x3 = XMVectorSubtract(x3, v3);
	x4 = XMVectorSubtract(x4, v4);

	MHMATRIX R;
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._11), x1);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._21), x2);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._31), x3);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._41), x4);
	return R;
}

inline MHMATRIX XM_CALLCONV operator* (const MHMATRIX& M1, const MHMATRIX& M2)
{
    using namespace DirectX;
    XMMATRIX m1 = XMLoadFloat4x4( &M1 );
    XMMATRIX m2 = XMLoadFloat4x4( &M2 );
    XMMATRIX X = XMMatrixMultiply( m1, m2 );

    MHMATRIX R;
    XMStoreFloat4x4( &R, X );
    return R;
}

inline MHMATRIX XM_CALLCONV operator* (const MHMATRIX& M, float S)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M._11) );
    XMVECTOR x2 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M._21) );
    XMVECTOR x3 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M._31) );
    XMVECTOR x4 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M._41) );

    x1 = XMVectorScale( x1, S );
    x2 = XMVectorScale( x2, S );
    x3 = XMVectorScale( x3, S );
    x4 = XMVectorScale( x4, S );

    MHMATRIX R;
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&R._11), x1 );
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&R._21), x2 );
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&R._31), x3 );
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&R._41), x4 );
    return R;
}

inline MHMATRIX XM_CALLCONV operator* (float S, const MHMATRIX& M)
{
	using namespace DirectX;

	XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._11));
	XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._21));
	XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._31));
	XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._41));

	x1 = XMVectorScale(x1, S);
	x2 = XMVectorScale(x2, S);
	x3 = XMVectorScale(x3, S);
	x4 = XMVectorScale(x4, S);

	MHMATRIX R;
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._11), x1);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._21), x2);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._31), x3);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._41), x4);
	return R;
}

inline MHMATRIX XM_CALLCONV operator/ (const MHMATRIX& M1, const MHMATRIX& M2)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M1._11) );
    XMVECTOR x2 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M1._21) );
    XMVECTOR x3 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M1._31) );
    XMVECTOR x4 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M1._41) );

    XMVECTOR y1 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M2._11) );
    XMVECTOR y2 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M2._21) );
    XMVECTOR y3 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M2._31) );
    XMVECTOR y4 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M2._41) );

    x1 = XMVectorDivide( x1, y1 );
    x2 = XMVectorDivide( x2, y2 );
    x3 = XMVectorDivide( x3, y3 );
    x4 = XMVectorDivide( x4, y4 );

    MHMATRIX R;
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&R._11), x1 );
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&R._21), x2 );
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&R._31), x3 );
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&R._41), x4 );
    return R;
}

inline MHMATRIX XM_CALLCONV operator/ (const MHMATRIX& M, float S)
{
	using namespace DirectX;
	assert(S != 0.f);

	XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._11));
	XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._21));
	XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._31));
	XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._41));

	float rs = 1.f / S;

	x1 = XMVectorScale(x1, rs);
	x2 = XMVectorScale(x2, rs);
	x3 = XMVectorScale(x3, rs);
	x4 = XMVectorScale(x4, rs);

	MHMATRIX R;
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._11), x1);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._21), x2);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._31), x3);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._41), x4);
	return R;
}

inline MHMATRIX XM_CALLCONV operator/ (float S, const MHMATRIX& M)
{
	using namespace DirectX;
	assert(S != 0.f);

	XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._11));
	XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._21));
	XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._31));
	XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._41));

	float rs = 1.f / S;

	x1 = XMVectorScale(x1, rs);
	x2 = XMVectorScale(x2, rs);
	x3 = XMVectorScale(x3, rs);
	x4 = XMVectorScale(x4, rs);

	MHMATRIX R;
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._11), x1);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._21), x2);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._31), x3);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._41), x4);
	return R;
}


//------------------------------------------------------------------------------
// MHMATRIX operations
//------------------------------------------------------------------------------

inline bool XM_CALLCONV MHMATRIX::MDecompose(MHVECTOR3& scale, MHQUATERNION& rotation, MHVECTOR3& translation)
{
    using namespace DirectX;

    XMVECTOR s, r, t;

    if ( !XMMatrixDecompose( &s, &r, &t, *this ) )
        return false;

    XMStoreFloat3( &scale, s );
    XMStoreFloat4( &rotation, r );
    XMStoreFloat3( &translation, t );

    return true;
}

inline MHMATRIX XM_CALLCONV MHMATRIX::MTranspose() const
{
    using namespace DirectX;
    XMMATRIX M = XMLoadFloat4x4( this );
    MHMATRIX R;
    XMStoreFloat4x4( &R, XMMatrixTranspose( M ) );
    return R;
}

inline void XM_CALLCONV MHMATRIX::MTranspose(MHMATRIX& result) const
{
    using namespace DirectX;
    XMMATRIX M = XMLoadFloat4x4( this );
    XMStoreFloat4x4( &result, XMMatrixTranspose( M ) );
}

inline MHMATRIX XM_CALLCONV MHMATRIX::MInvert() const
{
    using namespace DirectX;
    XMMATRIX M = XMLoadFloat4x4( this );
    MHMATRIX R;
    XMVECTOR det;
    XMStoreFloat4x4( &R, XMMatrixInverse( &det, M ) );
    return R;
}

inline void XM_CALLCONV MHMATRIX::MInvert(MHMATRIX& result) const
{
    using namespace DirectX;
    XMMATRIX M = XMLoadFloat4x4( this );
    XMVECTOR det;
    XMStoreFloat4x4( &result, XMMatrixInverse( &det, M ) );
}

inline float XM_CALLCONV MHMATRIX::MDeterminant() const
{
    using namespace DirectX;
    XMMATRIX M = XMLoadFloat4x4( this );
    return XMVectorGetX( XMMatrixDeterminant( M ) );
}

//------------------------------------------------------------------------------
// Static functions
//------------------------------------------------------------------------------

// Properties
inline MHVECTOR3 XM_CALLCONV Up(const MHMATRIX& M)
{
	using namespace DirectX;
	MHMATRIX floatM;
	XMStoreFloat4x4(&floatM, M);
	MHVECTOR3 RV = (MHVECTOR3)(floatM._21, floatM._22, floatM._23);
	MHVECTOR3 R;
	XMStoreFloat3(&R, RV);
	return R;
}

inline void XM_CALLCONV Up(const MHVECTOR3& V, const MHMATRIX& M, MHVECTOR3& result)
{
	using namespace DirectX;
	MHMATRIX floatM;
	XMStoreFloat4x4(&floatM, M);
	MHVECTOR3 R = (MHVECTOR3)(floatM._21 = V.x, floatM._22 = V.y, floatM._23 = V.z);
	XMStoreFloat3(&result, R);
}

inline MHVECTOR3 XM_CALLCONV Down(const MHMATRIX& M)
{ 
	using namespace DirectX;
	MHMATRIX floatM;
	XMStoreFloat4x4(&floatM, M);
	MHVECTOR3 RV = (MHVECTOR3)(-floatM._21, -floatM._22, -floatM._23);
	MHVECTOR3 R;
	XMStoreFloat3(&R, RV);
	return R;
}

inline void XM_CALLCONV Down(const MHVECTOR3& V, const MHMATRIX& M, MHVECTOR3& result)
{ 
	using namespace DirectX;
	MHMATRIX floatM;
	XMStoreFloat4x4(&floatM, M);
	MHVECTOR3 R = (MHVECTOR3)(floatM._21 = -V.x, floatM._22 = -V.y, floatM._23 = -V.z);
	XMStoreFloat3(&result, R);
}

inline MHVECTOR3 XM_CALLCONV Right(const MHMATRIX& M)
{
	using namespace DirectX;
	MHMATRIX floatM;
	XMStoreFloat4x4(&floatM, M);
	MHVECTOR3 RV = (MHVECTOR3)(floatM._11, floatM._12, floatM._13);
	MHVECTOR3 R;
	XMStoreFloat3(&R, RV);
	return R;
}

inline void XM_CALLCONV Right(const MHVECTOR3& V, const MHMATRIX& M, MHVECTOR3& result)
{
	using namespace DirectX;
	MHMATRIX floatM;
	XMStoreFloat4x4(&floatM, M);
	MHVECTOR3 R = (MHVECTOR3)(floatM._11 = V.x, floatM._12 = V.y, floatM._13 = V.z);
	XMStoreFloat3(&result, R);
}

inline MHVECTOR3 XM_CALLCONV Left(const MHMATRIX& M)
{
	using namespace DirectX;
	MHMATRIX floatM;
	XMStoreFloat4x4(&floatM, M);
	MHVECTOR3 RV = (MHVECTOR3)(-floatM._11, -floatM._12, -floatM._13);
	MHVECTOR3 R;
	XMStoreFloat3(&R, RV);
	return R;
}

inline void XM_CALLCONV Left(const MHVECTOR3& V, const MHMATRIX& M, MHVECTOR3& result)
{
	using namespace DirectX;
	MHMATRIX floatM;
	XMStoreFloat4x4(&floatM, M);
	MHVECTOR3 R = (MHVECTOR3)(floatM._11 = -V.x, floatM._12 = -V.y, floatM._13 = -V.z);
	XMStoreFloat3(&result, R);
}

inline MHVECTOR3 XM_CALLCONV Forward(const MHMATRIX& M)
{
	using namespace DirectX;
	MHMATRIX floatM;
	XMStoreFloat4x4(&floatM, M);
	MHVECTOR3 RV = (MHVECTOR3)(-floatM._31, -floatM._32, -floatM._33);
	MHVECTOR3 R;
	XMStoreFloat3(&R, RV);
	return R;
}

inline void XM_CALLCONV Forward(const MHVECTOR3& V, const MHMATRIX& M, MHVECTOR3& result)
{
	using namespace DirectX;
	MHMATRIX floatM;
	XMStoreFloat4x4(&floatM, M);
	MHVECTOR3 R = (MHVECTOR3)(floatM._31 = -V.x, floatM._32 = -V.y, floatM._33 = -V.z);
	XMStoreFloat3(&result, R);
}

inline MHVECTOR3 XM_CALLCONV Backward(const MHMATRIX& M)
{
	using namespace DirectX;
	MHMATRIX floatM;
	XMStoreFloat4x4(&floatM, M);
	MHVECTOR3 RV = (MHVECTOR3)(floatM._31, floatM._32, floatM._33);
	MHVECTOR3 R;
	XMStoreFloat3(&R, RV);
	return R;
}

inline void XM_CALLCONV Backward(const MHVECTOR3& V, const MHMATRIX& M, MHVECTOR3& result)
{
	using namespace DirectX;
	MHMATRIX floatM;
	XMStoreFloat4x4(&floatM, M);
	MHVECTOR3 R = (MHVECTOR3)(floatM._31 = V.x, floatM._32 = V.y, floatM._33 = V.z);
	XMStoreFloat3(&result, R);
}

inline MHVECTOR3 XM_CALLCONV Translate(const MHMATRIX& M)
{
	using namespace DirectX;
	MHMATRIX floatM;
	XMStoreFloat4x4(&floatM, M);
	MHVECTOR3 RV = (MHVECTOR3)(floatM._41, floatM._42, floatM._43);
	MHVECTOR3 R;
	XMStoreFloat3(&R, RV);
	return R;
}

inline void XM_CALLCONV Translate(const MHVECTOR3& V, const MHMATRIX& M, MHVECTOR3& result)
{
	using namespace DirectX;
	MHMATRIX floatM;
	XMStoreFloat4x4(&floatM, M);
	MHVECTOR3 R = (MHVECTOR3)(floatM._41 = V.x, floatM._42 = V.y, floatM._43 = V.z);
	XMStoreFloat3(&result, R);
}

// Matrix operations
inline bool XM_CALLCONV MHMATRIX::Decompose(const MHMATRIX& M, MHVECTOR3& scale, MHQUATERNION& rotation, MHVECTOR3& translation)
{
	using namespace DirectX;

	XMVECTOR s, r, t;

	if (!XMMatrixDecompose(&s, &r, &t, M))
		return false;

	XMStoreFloat3(&scale, s);
	XMStoreFloat4(&rotation, r);
	XMStoreFloat3(&translation, t);

	return true;
}

inline MHMATRIX XM_CALLCONV MHMATRIX::Transpose(const MHMATRIX& M)
{
	using namespace DirectX;
	XMMATRIX MT = XMLoadFloat4x4(&M);
	MHMATRIX R;
	XMStoreFloat4x4(&R, XMMatrixTranspose(MT));
	return R;
}

inline void XM_CALLCONV MHMATRIX::Transpose(const MHMATRIX& M, MHMATRIX& result)
{
	using namespace DirectX;
	XMMATRIX MT = XMLoadFloat4x4(&M);
	XMStoreFloat4x4(&result, XMMatrixTranspose(MT));
}

inline MHMATRIX XM_CALLCONV MHMATRIX::MultiplyTranspose(const MHMATRIX& M1, const MHMATRIX& M2)
{
	using namespace DirectX;
	XMMATRIX MT1 = XMLoadFloat4x4(&M1);
	XMMATRIX MT2 = XMLoadFloat4x4(&M2);
	MHMATRIX R;
	XMStoreFloat4x4(&R, XMMatrixMultiplyTranspose(MT1, MT2));
	return R;
}

inline void XM_CALLCONV MHMATRIX::MultiplyTranspose(const MHMATRIX& M1, const MHMATRIX& M2, MHMATRIX& result)
{
	using namespace DirectX;
	XMMATRIX MT1 = XMLoadFloat4x4(&M1);
	XMMATRIX MT2 = XMLoadFloat4x4(&M2);
	XMStoreFloat4x4(&result, XMMatrixMultiplyTranspose(MT1, MT2));
}

inline MHMATRIX XM_CALLCONV MHMATRIX::Inverse(const MHMATRIX& M)
{
	using namespace DirectX;
	XMMATRIX MR = XMLoadFloat4x4(&M);
	XMVECTOR det;
	MHMATRIX R;
	XMStoreFloat4x4(&R, XMMatrixInverse(&det, MR));
	return R;
}

inline void XM_CALLCONV MHMATRIX::Inverse(const MHMATRIX& M, MHMATRIX& result)
{
	using namespace DirectX;
	XMMATRIX MR = XMLoadFloat4x4(&M);
	XMVECTOR det;
	XMStoreFloat4x4(&result, XMMatrixInverse(&det, MR));
}

inline float XM_CALLCONV MHMATRIX::Determinant(const MHMATRIX& M)
{
	using namespace DirectX;
	XMMATRIX MR = XMLoadFloat4x4(&M);
	return XMVectorGetX(XMMatrixDeterminant(MR));
}

// Matrix functions
inline MHMATRIX XM_CALLCONV MHMATRIX::MHIdentity()
{
    using namespace DirectX;
    return MHMATRIX(1.f,   0,   0,   0,
					0,   1.f,   0,   0,
					0,     0, 1.f,   0,
					0,     0,   0, 1.f );
}

inline MHMATRIX XM_CALLCONV MHMATRIX::Identity()
{
	using namespace DirectX;
	MHMATRIX Mid = XMMatrixIdentity();
	MHMATRIX R;
	XMStoreFloat4x4(&R, Mid);
	return R;
}

inline bool XM_CALLCONV MHMATRIX::IsIdentity(const MHMATRIX& M)
{
	using namespace DirectX;
	return XMMatrixIsIdentity(M);
}

inline MHMATRIX XM_CALLCONV MHMATRIX::Translation(const MHVECTOR3& position)
{
    using namespace DirectX;
    MHMATRIX R;
    XMStoreFloat4x4( &R, XMMatrixTranslation( position.x, position.y, position.z ) );
    return R;
}

inline MHMATRIX XM_CALLCONV MHMATRIX::Translation(float x, float y, float z)
{
    using namespace DirectX;
    MHMATRIX R;
    XMStoreFloat4x4( &R, XMMatrixTranslation( x, y, z ) );
    return R;
}

inline MHMATRIX XM_CALLCONV MHMATRIX::TranslationFromVector(FXMVECTOR& V)
{
	using namespace DirectX;
	//XMVECTOR v = XMLoadFloat3(&scales);
	MHMATRIX R;
	XMStoreFloat4x4(&R, XMMatrixTranslationFromVector(V));
	return R;
}

inline MHMATRIX XM_CALLCONV MHMATRIX::Scaling(const MHVECTOR3& scales)
{
    using namespace DirectX;
    MHMATRIX R;
    XMStoreFloat4x4( &R, XMMatrixScaling( scales.x, scales.y, scales.z ) );
    return R;
}

inline MHMATRIX XM_CALLCONV MHMATRIX::Scaling(float xs, float ys, float zs)
{
    using namespace DirectX;
    MHMATRIX R;
    XMStoreFloat4x4( &R, XMMatrixScaling( xs, ys, zs ) );
    return R;
}

inline MHMATRIX XM_CALLCONV MHMATRIX::Scaling(float scale)
{
    using namespace DirectX;
    MHMATRIX R;
    XMStoreFloat4x4( &R, XMMatrixScaling( scale, scale, scale ) );
    return R;
}

inline MHMATRIX XM_CALLCONV MHMATRIX::ScalingFromVector(FXMVECTOR& V)
{
	using namespace DirectX;
	//XMVECTOR vscales = XMLoadFloat3(&scales);
	MHMATRIX R;
	XMStoreFloat4x4(&R, XMMatrixScalingFromVector(V));
	return R;
}

inline MHMATRIX XM_CALLCONV MHMATRIX::RotationX(float radians)
{
    using namespace DirectX;
    MHMATRIX R;
    XMStoreFloat4x4( &R, XMMatrixRotationX( radians ) );
    return R;
}

inline MHMATRIX XM_CALLCONV MHMATRIX::RotationY(float radians)
{
    using namespace DirectX;
    MHMATRIX R;
    XMStoreFloat4x4( &R, XMMatrixRotationY( radians ) );
    return R;
}

inline MHMATRIX XM_CALLCONV MHMATRIX::RotationZ(float radians)
{
    using namespace DirectX;
    MHMATRIX R;
    XMStoreFloat4x4( &R, XMMatrixRotationZ( radians ) );
    return R;
}

inline MHMATRIX XM_CALLCONV MHMATRIX::RotationAxisAngle(const MHVECTOR3& axis, float angle)
{
    using namespace DirectX;
    MHMATRIX R;
    XMVECTOR a = XMLoadFloat3( &axis );
    XMStoreFloat4x4( &R, XMMatrixRotationAxis( a, angle ) );
    return R;
}

inline MHMATRIX XM_CALLCONV MHMATRIX::RotationNormal(const MHVECTOR3& axis, float angle)
{
	using namespace DirectX;
	MHMATRIX R;
	XMVECTOR a = XMLoadFloat3(&axis);
	XMStoreFloat4x4(&R, XMMatrixRotationNormal(a, angle));
	return R;
}

inline MHMATRIX XM_CALLCONV MHMATRIX::RotationQuaternion(const MHQUATERNION& quat)
{
	using namespace DirectX;
	MHMATRIX R;
	XMVECTOR quatv = XMLoadFloat4(&quat);
	XMStoreFloat4x4(&R, XMMatrixRotationQuaternion(quatv));
	return R;
}

inline MHMATRIX XM_CALLCONV MHMATRIX::RotationRollPitchYaw(float yaw, float pitch, float roll)
{
	using namespace DirectX;
	MHMATRIX R;
	XMStoreFloat4x4(&R, XMMatrixRotationRollPitchYaw(pitch, yaw, roll));
	return R;
}

inline MHMATRIX XM_CALLCONV MHMATRIX::PerspectiveFov(float fov, float aspectRatio, float nearPlane, float farPlane)
{
    using namespace DirectX;
    MHMATRIX R;
    XMStoreFloat4x4( &R, XMMatrixPerspectiveFovRH( fov, aspectRatio, nearPlane, farPlane ) );
    return R;
}

inline MHMATRIX XM_CALLCONV MHMATRIX::Perspective(float width, float height, float nearPlane, float farPlane)
{
    using namespace DirectX;
    MHMATRIX R;
    XMStoreFloat4x4( &R, XMMatrixPerspectiveRH( width, height, nearPlane, farPlane ) );
    return R;
}

inline MHMATRIX XM_CALLCONV MHMATRIX::PerspectiveOffCenter(float left, float right, float bottom, float top, float nearPlane, float farPlane)
{
    using namespace DirectX;
    MHMATRIX R;
    XMStoreFloat4x4( &R, XMMatrixPerspectiveOffCenterRH( left, right, bottom, top, nearPlane, farPlane ) );
    return R;
}

inline MHMATRIX XM_CALLCONV MHMATRIX::Orthographic(float width, float height, float zNearPlane, float zFarPlane)
{
    using namespace DirectX;
    MHMATRIX R;
    XMStoreFloat4x4( &R, XMMatrixOrthographicRH( width, height, zNearPlane, zFarPlane ) );
    return R;
}

inline MHMATRIX XM_CALLCONV MHMATRIX::OrthographicOffCenter(float left, float right, float bottom, float top, float zNearPlane, float zFarPlane)
{
    using namespace DirectX;
    MHMATRIX R;
    XMStoreFloat4x4( &R, XMMatrixOrthographicOffCenterRH( left, right, bottom, top, zNearPlane, zFarPlane ) );
    return R;
}

inline MHMATRIX XM_CALLCONV MHMATRIX::LookAt(const MHVECTOR3& eye, const MHVECTOR3& target, const MHVECTOR3& up)
{
    using namespace DirectX;
    MHMATRIX R;
    XMVECTOR eyev = XMLoadFloat3( &eye );
    XMVECTOR targetv = XMLoadFloat3( &target );
    XMVECTOR upv = XMLoadFloat3( &up );
    XMStoreFloat4x4( &R, XMMatrixLookAtRH( eyev, targetv, upv ) );
    return R;
}

inline MHMATRIX XM_CALLCONV MHMATRIX::LookTo(const MHVECTOR3& eye, const MHVECTOR3& target, const MHVECTOR3& up)
{
	using namespace DirectX;
	MHMATRIX R;
	XMVECTOR eyev = XMLoadFloat3(&eye);
	XMVECTOR targetv = XMLoadFloat3(&target);
	XMVECTOR upv = XMLoadFloat3(&up);
	XMStoreFloat4x4(&R, XMMatrixLookToRH(eyev, targetv, upv));
	return R;
}

inline MHMATRIX XM_CALLCONV MHMATRIX::CreateWorld(const MHVECTOR3& position, const MHVECTOR3& forward, const MHVECTOR3& up)
{
    using namespace DirectX;
    XMVECTOR zaxis = XMVector3Normalize( XMVectorNegate( XMLoadFloat3( &forward ) ) );
    XMVECTOR yaxis = XMLoadFloat3( &up );
    XMVECTOR xaxis = XMVector3Normalize( XMVector3Cross( yaxis, zaxis ) );
    yaxis = XMVector3Cross( zaxis, xaxis );
    
    MHMATRIX R;
    XMStoreFloat3( reinterpret_cast<XMFLOAT3*>( &R._11 ), xaxis );
    XMStoreFloat3( reinterpret_cast<XMFLOAT3*>( &R._21 ), yaxis );
    XMStoreFloat3( reinterpret_cast<XMFLOAT3*>( &R._31 ), zaxis );
    R._14 = R._24 = R._34 = 0.f;
    R._41 = position.x; R._42 = position.y; R._43 = position.z;
    R._44 = 1.f;
    return R;
}

inline MHMATRIX XM_CALLCONV MHMATRIX::Shadow(const MHVECTOR3& lightDir, const MHPLANE& plane)
{
    using namespace DirectX;
    MHMATRIX R;
    XMVECTOR light = XMLoadFloat3( &lightDir );
    XMVECTOR planev = XMLoadFloat4( &plane );
    XMStoreFloat4x4( &R, XMMatrixShadow( planev, light ) );
    return R;
}

inline MHMATRIX XM_CALLCONV MHMATRIX::Reflect(const MHPLANE& plane)
{
    using namespace DirectX;
    MHMATRIX R;
    XMVECTOR planev = XMLoadFloat4( &plane );
    XMStoreFloat4x4( &R, XMMatrixReflect( planev ) );
    return R;
}

inline void XM_CALLCONV MHMATRIX::Lerp(const MHMATRIX& M1, const MHMATRIX& M2, float t, MHMATRIX& result)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M1._11) );
    XMVECTOR x2 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M1._21) );
    XMVECTOR x3 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M1._31) );
    XMVECTOR x4 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M1._41) );

    XMVECTOR y1 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M2._11) );
    XMVECTOR y2 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M2._21) );
    XMVECTOR y3 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M2._31) );
    XMVECTOR y4 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M2._41) );

    x1 = XMVectorLerp( x1, y1, t );
    x2 = XMVectorLerp( x2, y2, t );
    x3 = XMVectorLerp( x3, y3, t );
    x4 = XMVectorLerp( x4, y4, t );

    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&result._11), x1 );
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&result._21), x2 );
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&result._31), x3 );
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&result._41), x4 );
}

inline MHMATRIX XM_CALLCONV MHMATRIX::Lerp(const MHMATRIX& M1, const MHMATRIX& M2, float t)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M1._11) );
    XMVECTOR x2 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M1._21) );
    XMVECTOR x3 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M1._31) );
    XMVECTOR x4 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M1._41) );

    XMVECTOR y1 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M2._11) );
    XMVECTOR y2 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M2._21) );
    XMVECTOR y3 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M2._31) );
    XMVECTOR y4 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M2._41) );

    x1 = XMVectorLerp( x1, y1, t );
    x2 = XMVectorLerp( x2, y2, t );
    x3 = XMVectorLerp( x3, y3, t );
    x4 = XMVectorLerp( x4, y4, t );

    MHMATRIX result;
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&result._11), x1 );
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&result._21), x2 );
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&result._31), x3 );
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&result._41), x4 );
    return result;
}

inline void XM_CALLCONV MHMATRIX::Transform(const MHMATRIX& M, const MHQUATERNION& rotation, MHMATRIX& result)
{
    using namespace DirectX;
    XMVECTOR quatv = XMLoadFloat4( &rotation );

    XMMATRIX M0 = XMLoadFloat4x4( &M );
    XMMATRIX M1 = XMMatrixRotationQuaternion( quatv );

    XMStoreFloat4x4( &result, XMMatrixMultiply( M0, M1 ) );
}

inline MHMATRIX XM_CALLCONV MHMATRIX::Transform(const MHMATRIX& M, const MHQUATERNION& rotation)
{
    using namespace DirectX;
    XMVECTOR quatv = XMLoadFloat4( &rotation );

    XMMATRIX M0 = XMLoadFloat4x4( &M );
    XMMATRIX M1 = XMMatrixRotationQuaternion( quatv );

    MHMATRIX result;
    XMStoreFloat4x4( &result, XMMatrixMultiply( M0, M1 ) );
    return result;
}

#	pragma endregion

/****************************************************************************
 *
 * MHPLANE
 *
 ****************************************************************************/
#	pragma region MHPLANE

inline MHPLANE::MHPLANE(const MHVECTOR3& point1, const MHVECTOR3& point2, const MHVECTOR3& point3 )
{
    using namespace DirectX;
    XMVECTOR P0 = XMLoadFloat3( &point1 );
    XMVECTOR P1 = XMLoadFloat3( &point2 );
    XMVECTOR P2 = XMLoadFloat3( &point3 );
    XMStoreFloat4( this, XMPlaneFromPoints( P0, P1, P2 ) );
}

inline MHPLANE::MHPLANE(const MHVECTOR3& point, const MHVECTOR3& normal)
{
    using namespace DirectX;
    XMVECTOR P = XMLoadFloat3( &point );
    XMVECTOR N = XMLoadFloat3( &normal );
    XMStoreFloat4( this, XMPlaneFromPointNormal( P, N ) );
}

//------------------------------------------------------------------------------
// Comparision operators
//------------------------------------------------------------------------------

inline bool XM_CALLCONV MHPLANE::operator == (const MHPLANE& p) const
{
    using namespace DirectX;
    XMVECTOR p1 = XMLoadFloat4( this );
    XMVECTOR p2 = XMLoadFloat4( &p );
    return XMPlaneEqual( p1, p2 );
}

inline bool XM_CALLCONV MHPLANE::operator != (const MHPLANE& p) const
{
    using namespace DirectX;
    XMVECTOR p1 = XMLoadFloat4( this );
    XMVECTOR p2 = XMLoadFloat4( &p );
    return XMPlaneNotEqual( p1, p2 );
}

//------------------------------------------------------------------------------
// MHPLANE operations
//------------------------------------------------------------------------------

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

inline float XM_CALLCONV MHPLANE::PDot(const MHVECTOR4& v) const
{
    using namespace DirectX;
    XMVECTOR p = XMLoadFloat4( this );
    XMVECTOR v0 = XMLoadFloat4( &v );
    return XMVectorGetX( XMPlaneDot( p, v0 ) );
}

inline float XM_CALLCONV MHPLANE::PDotCoordinate(const MHVECTOR3& position) const
{
    using namespace DirectX;
    XMVECTOR p = XMLoadFloat4( this );
    XMVECTOR v0 = XMLoadFloat3( &position );
    return XMVectorGetX( XMPlaneDotCoord( p, v0 ) );
}

inline float XM_CALLCONV MHPLANE::PDotNormal(const MHVECTOR3& normal) const
{
    using namespace DirectX;
    XMVECTOR p = XMLoadFloat4( this );
    XMVECTOR n0 = XMLoadFloat3( &normal );
    return XMVectorGetX( XMPlaneDotNormal( p, n0 ) );
}

//------------------------------------------------------------------------------
// Static functions
//------------------------------------------------------------------------------

inline MHPLANE XM_CALLCONV MHPLANE::Normalize(const MHPLANE& plane)
{
	using namespace DirectX;
	XMVECTOR p = XMLoadFloat4(&plane);
	MHPLANE R;
	XMStoreFloat4(&R, XMPlaneNormalize(p));
	return R;
}

inline void XM_CALLCONV MHPLANE::Normalize(const MHPLANE& plane, MHPLANE& result)
{
	using namespace DirectX;
	XMVECTOR p = XMLoadFloat4(&plane);
	XMStoreFloat4(&result, XMPlaneNormalize(p));
}

inline float XM_CALLCONV MHPLANE::Dot(const MHPLANE& plane, const MHVECTOR4& v)
{
	using namespace DirectX;
	XMVECTOR p = XMLoadFloat4(&plane);
	XMVECTOR v0 = XMLoadFloat4(&v);
	return XMVectorGetX(XMPlaneDot(p, v0));
}

inline float XM_CALLCONV MHPLANE::DotCoordinate(const MHPLANE& plane, const MHVECTOR3& position)
{
	using namespace DirectX;
	XMVECTOR p = XMLoadFloat4(&plane);
	XMVECTOR v0 = XMLoadFloat3(&position);
	return XMVectorGetX(XMPlaneDotCoord(p, v0));
}

inline float XM_CALLCONV MHPLANE::DotNormal(const MHPLANE& plane, const MHVECTOR3& normal)
{
	using namespace DirectX;
	XMVECTOR p = XMLoadFloat4(&plane);
	XMVECTOR n0 = XMLoadFloat3(&normal);
	return XMVectorGetX(XMPlaneDotNormal(p, n0));
}

inline void XM_CALLCONV MHPLANE::Transform(const MHPLANE& plane, const MHMATRIX& M, MHPLANE& result)
{
    using namespace DirectX;
    XMVECTOR p = XMLoadFloat4( &plane );
    XMMATRIX m0 = XMLoadFloat4x4( &M );
    XMStoreFloat4( &result, XMPlaneTransform( p, m0 ) );
}

inline MHPLANE XM_CALLCONV MHPLANE::Transform(const MHPLANE& plane, const MHMATRIX& M)
{
    using namespace DirectX;
    XMVECTOR p = XMLoadFloat4( &plane );
    XMMATRIX m0 = XMLoadFloat4x4( &M );

    MHPLANE result;
    XMStoreFloat4( &result, XMPlaneTransform( p, m0 ) );
    return result;
}

inline void XM_CALLCONV MHPLANE::Transform(const MHPLANE& plane, const MHQUATERNION& rotation, MHPLANE& result)
{
    using namespace DirectX;
    XMVECTOR p = XMLoadFloat4( &plane );
    XMVECTOR q = XMLoadFloat4( &rotation );
    XMVECTOR X = XMVector3Rotate( p, q );
    X = XMVectorSelect( p, X, g_XMSelect1110 ); // result.d = plane.d
    XMStoreFloat4( &result, X );
}

inline MHPLANE XM_CALLCONV MHPLANE::Transform(const MHPLANE& plane, const MHQUATERNION& rotation)
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

#	pragma endregion

/****************************************************************************
 *
 * MHQUATERNION
 *
 ****************************************************************************/
#	pragma region MHQUATERNION

//------------------------------------------------------------------------------
// Comparision operators
//------------------------------------------------------------------------------

inline bool XM_CALLCONV MHQUATERNION::operator == (const MHQUATERNION& q) const
{
    using namespace DirectX;
    XMVECTOR q1 = XMLoadFloat4( this );
    XMVECTOR q2 = XMLoadFloat4( &q );
    return XMQuaternionEqual( q1, q2 );
}

inline bool XM_CALLCONV MHQUATERNION::operator != (const MHQUATERNION& q) const
{
    using namespace DirectX;
    XMVECTOR q1 = XMLoadFloat4( this );
    XMVECTOR q2 = XMLoadFloat4( &q );
    return XMQuaternionNotEqual( q1, q2 );
}

//------------------------------------------------------------------------------
// Assignment operators
//------------------------------------------------------------------------------

inline MHQUATERNION& XM_CALLCONV MHQUATERNION::operator+= (const MHQUATERNION& q)
{
    using namespace DirectX;
    XMVECTOR q1 = XMLoadFloat4( this );
    XMVECTOR q2 = XMLoadFloat4( &q );
    XMStoreFloat4( this, XMVectorAdd( q1, q2 ) );
    return *this;
}

inline MHQUATERNION& XM_CALLCONV MHQUATERNION::operator+= (float S)
{
	using namespace DirectX;
	XMVECTOR q1 = XMLoadFloat4(this);
	XMVECTOR q2 = XMLoadFloat(&S);
	XMStoreFloat4(this, XMVectorAdd(q1, q2));
	return *this;
}

inline MHQUATERNION& XM_CALLCONV MHQUATERNION::operator-= (const MHQUATERNION& q)
{
    using namespace DirectX;
    XMVECTOR q1 = XMLoadFloat4( this );
    XMVECTOR q2 = XMLoadFloat4( &q );
    XMStoreFloat4( this, XMVectorSubtract( q1, q2 ) );
    return *this;
}

inline MHQUATERNION& XM_CALLCONV MHQUATERNION::operator-= (float S)
{
	using namespace DirectX;
	XMVECTOR q1 = XMLoadFloat4(this);
	XMVECTOR q2 = XMLoadFloat(&S);
	XMStoreFloat4(this, XMVectorSubtract(q1, q2));
	return *this;
}

inline MHQUATERNION& XM_CALLCONV MHQUATERNION::operator*= (const MHQUATERNION& q)
{
    using namespace DirectX;
    XMVECTOR q1 = XMLoadFloat4( this );
    XMVECTOR q2 = XMLoadFloat4( &q );
    XMStoreFloat4( this, XMQuaternionMultiply( q1, q2 ) );
    return *this;
}

inline MHQUATERNION& XM_CALLCONV MHQUATERNION::operator*= (float S)
{
    using namespace DirectX;
    XMVECTOR q = XMLoadFloat4( this );
    XMStoreFloat4( this, XMVectorScale( q, S ) );
    return *this;
}

inline MHQUATERNION& XM_CALLCONV MHQUATERNION::operator/= (const MHQUATERNION& q)
{
    using namespace DirectX;
    XMVECTOR q1 = XMLoadFloat4( this );
    XMVECTOR q2 = XMLoadFloat4( &q );
    q2 = XMQuaternionInverse( q2 );
    XMStoreFloat4( this, XMQuaternionMultiply( q1, q2 ) );
    return *this;
}

inline MHQUATERNION& XM_CALLCONV MHQUATERNION::operator/= (float S)
{
	using namespace DirectX;
	assert(S != 0.f);

	XMVECTOR q1 = XMLoadFloat4(this);
	XMVECTOR X = XMVectorScale(q1, 1.f/S);
	XMStoreFloat4(this, X);
	return *this;
}

//------------------------------------------------------------------------------
// Urnary operators
//------------------------------------------------------------------------------

/*
inline MHQUATERNION XM_CALLCONV MHQUATERNION::operator+ () const
{
	using namespace DirectX;
	XMVECTOR q = XMLoadFloat4(this);

	MHQUATERNION R;
	XMStoreFloat4(&R, +q);
	return R;
}*/

inline MHQUATERNION XM_CALLCONV MHQUATERNION::operator- () const
{
    using namespace DirectX;
    XMVECTOR q = XMLoadFloat4( this );

    MHQUATERNION R;
    XMStoreFloat4( &R, XMVectorNegate( q ) );
    return R;
}

//------------------------------------------------------------------------------
// Binary operators
//------------------------------------------------------------------------------

inline MHQUATERNION XM_CALLCONV operator+ (const MHQUATERNION& Q1, const MHQUATERNION& Q2)
{
    using namespace DirectX;
    XMVECTOR q1 = XMLoadFloat4( &Q1 );
    XMVECTOR q2 = XMLoadFloat4( &Q2 );

    MHQUATERNION R;
    XMStoreFloat4( &R, XMVectorAdd( q1, q2 ) );
    return R;
}

inline MHQUATERNION XM_CALLCONV operator+ (const MHQUATERNION& Q, float S)
{
	using namespace DirectX;
	XMVECTOR q1 = XMLoadFloat4(&Q);
	XMVECTOR q2 = XMLoadFloat(&S);

	MHQUATERNION R;
	XMStoreFloat4(&R, XMVectorAdd(q1, q2));
	return R;
}

inline MHQUATERNION XM_CALLCONV operator+ (float S, const MHQUATERNION& Q)
{
	using namespace DirectX;
	XMVECTOR q1 = XMLoadFloat(&S);
	XMVECTOR q2 = XMLoadFloat4(&Q);

	MHQUATERNION R;
	XMStoreFloat4(&R, XMVectorAdd(q1, q2));
	return R;
}

inline MHQUATERNION XM_CALLCONV operator- (const MHQUATERNION& Q1, const MHQUATERNION& Q2)
{
    using namespace DirectX;
    XMVECTOR q1 = XMLoadFloat4( &Q1 );
    XMVECTOR q2 = XMLoadFloat4( &Q2 );

    MHQUATERNION R;
    XMStoreFloat4( &R, XMVectorSubtract( q1, q2 ) );
    return R;
}

inline MHQUATERNION XM_CALLCONV operator- (const MHQUATERNION& Q, float S)
{
	using namespace DirectX;
	XMVECTOR q1 = XMLoadFloat4(&Q);
	XMVECTOR q2 = XMLoadFloat(&S);

	MHQUATERNION R;
	XMStoreFloat4(&R, XMVectorSubtract(q1, q2));
	return R;
}

inline MHQUATERNION XM_CALLCONV operator- (float S, const MHQUATERNION& Q)
{
	using namespace DirectX;
	XMVECTOR q1 = XMLoadFloat(&S);
	XMVECTOR q2 = XMLoadFloat4(&Q);

	MHQUATERNION R;
	XMStoreFloat4(&R, XMVectorSubtract(q1, q2));
	return R;
}

inline MHQUATERNION XM_CALLCONV operator* (const MHQUATERNION& Q1, const MHQUATERNION& Q2)
{
    using namespace DirectX;
    XMVECTOR q1 = XMLoadFloat4( &Q1 );
    XMVECTOR q2 = XMLoadFloat4( &Q2 );

    MHQUATERNION R;
    XMStoreFloat4( &R, XMQuaternionMultiply( q1, q2 ) );
    return R;
}

inline MHQUATERNION XM_CALLCONV operator* (const MHQUATERNION& Q, float S)
{
    using namespace DirectX;
    XMVECTOR q = XMLoadFloat4( &Q );

    MHQUATERNION R;
    XMStoreFloat4( &R, XMVectorScale( q, S ) );
    return R;
}

inline MHQUATERNION XM_CALLCONV operator* (float S, const MHQUATERNION& Q)
{
	using namespace DirectX;
	XMVECTOR q1 = XMLoadFloat4(&Q);

	MHQUATERNION R;
	XMStoreFloat4(&R, XMVectorScale(q1, S));
	return R;
}

inline MHQUATERNION XM_CALLCONV operator/ (const MHQUATERNION& Q1, const MHQUATERNION& Q2)
{
    using namespace DirectX;
    XMVECTOR q1 = XMLoadFloat4( &Q1 );
    XMVECTOR q2 = XMLoadFloat4( &Q2 );
    q2 = XMQuaternionInverse( q2 );

    MHQUATERNION R;
    XMStoreFloat4( &R, XMQuaternionMultiply( q1, q2 ) );
    return R;
}

inline MHQUATERNION XM_CALLCONV operator/ (const MHQUATERNION& Q, float S)
{
	using namespace DirectX;
	assert(S != 0.f);

	XMVECTOR q1 = XMLoadFloat4(&Q);
	XMVECTOR X = XMVectorScale(q1, 1.f / S);

	MHQUATERNION R;
	XMStoreFloat4(&R, X);
	return R;
}

inline MHQUATERNION XM_CALLCONV operator/ (float S, const MHQUATERNION& Q)
{
	using namespace DirectX;
	assert(S != 0.f);

	XMVECTOR q1 = XMLoadFloat4(&Q);
	XMVECTOR X = XMVectorScale(q1, 1.f / S);

	MHQUATERNION R;
	XMStoreFloat4(&R, X);
	return R;
}

//------------------------------------------------------------------------------
// MHQUATERNION operations
//------------------------------------------------------------------------------

inline float XM_CALLCONV MHQUATERNION::QLength() const
{
    using namespace DirectX;
    XMVECTOR q = XMLoadFloat4( this );
    return XMVectorGetX( XMQuaternionLength( q ) );
}

inline float XM_CALLCONV MHQUATERNION::QLengthSquared() const
{
    using namespace DirectX;
    XMVECTOR q = XMLoadFloat4( this );
    return XMVectorGetX( XMQuaternionLengthSq( q ) );
}

inline void XM_CALLCONV MHQUATERNION::QNormalize()
{
    using namespace DirectX;
    XMVECTOR q = XMLoadFloat4( this );
    XMStoreFloat4( this, XMQuaternionNormalize( q ) );
}

inline void XM_CALLCONV MHQUATERNION::QNormalize(MHQUATERNION& result) const
{
    using namespace DirectX;
    XMVECTOR q = XMLoadFloat4( this );
    XMStoreFloat4( &result, XMQuaternionNormalize( q ) );
}

inline void XM_CALLCONV MHQUATERNION::QConjugate()
{
    using namespace DirectX;
    XMVECTOR q = XMLoadFloat4( this );
    XMStoreFloat4( this, XMQuaternionConjugate( q ) );
}

inline void XM_CALLCONV MHQUATERNION::QConjugate(MHQUATERNION& result) const
{
    using namespace DirectX;
    XMVECTOR q = XMLoadFloat4( this );
    XMStoreFloat4( &result, XMQuaternionConjugate( q ) );
}

inline void XM_CALLCONV MHQUATERNION::QInverse(MHQUATERNION& result) const
{
    using namespace DirectX;
    XMVECTOR q = XMLoadFloat4( this );
    XMStoreFloat4( &result, XMQuaternionInverse( q ) );
}

inline float XM_CALLCONV MHQUATERNION::QDot(const MHQUATERNION& Q) const
{
    using namespace DirectX;
    XMVECTOR q1 = XMLoadFloat4( this );
    XMVECTOR q2 = XMLoadFloat4( &Q );
    return XMVectorGetX( XMQuaternionDot( q1, q2 ) );
}

//------------------------------------------------------------------------------
// Static functions
//------------------------------------------------------------------------------

inline float XM_CALLCONV MHQUATERNION::Length(const MHQUATERNION& Q)
{
	using namespace DirectX;
	XMVECTOR q = XMLoadFloat4(&Q);
	return XMVectorGetX(XMQuaternionLength(q));
}

inline float XM_CALLCONV MHQUATERNION::LengthSquared(const MHQUATERNION& Q)
{
	using namespace DirectX;
	XMVECTOR q = XMLoadFloat4(&Q);
	return XMVectorGetX(XMQuaternionLengthSq(q));
}

inline MHQUATERNION XM_CALLCONV MHQUATERNION::Identity()
{
	using namespace DirectX;
	MHQUATERNION Qid = XMQuaternionIdentity();
	MHQUATERNION R;
	XMStoreFloat4(&R, Qid);
	return R;
}

inline bool XM_CALLCONV MHQUATERNION::IsIdentity(const MHQUATERNION& Q)
{
	using namespace DirectX;
	return XMQuaternionIsIdentity(Q);
}

inline MHQUATERNION XM_CALLCONV MHQUATERNION::Normalize(const MHQUATERNION& Q)
{
	using namespace DirectX;
	XMVECTOR q = XMLoadFloat4(&Q);
	MHQUATERNION R;
	XMStoreFloat4(&R, XMQuaternionNormalize(q));
	return R;
}

inline void XM_CALLCONV MHQUATERNION::Normalize(const MHQUATERNION& Q, MHQUATERNION& result)
{
	using namespace DirectX;
	XMVECTOR q = XMLoadFloat4(&Q);
	XMStoreFloat4(&result, XMQuaternionNormalize(q));
}

inline MHQUATERNION XM_CALLCONV MHQUATERNION::Conjugate(const MHQUATERNION& Q)
{
	using namespace DirectX;
	XMVECTOR q = XMLoadFloat4(&Q);

	MHQUATERNION R;
	XMStoreFloat4(&R, XMQuaternionConjugate(q));
	return R;
}

inline void XM_CALLCONV MHQUATERNION::Conjugate(const MHQUATERNION& Q, MHQUATERNION& result)
{
	using namespace DirectX;
	XMVECTOR q = XMLoadFloat4(&Q);
	XMStoreFloat4(&result, XMQuaternionConjugate(q));
}

inline MHQUATERNION XM_CALLCONV MHQUATERNION::Inverse(const MHQUATERNION& Q)
{
	using namespace DirectX;
	XMVECTOR q = XMLoadFloat4(&Q);

	MHQUATERNION R;
	XMStoreFloat4(&R, XMQuaternionInverse(q));
	return R;
}

inline void XM_CALLCONV MHQUATERNION::Inverse(const MHQUATERNION& Q, MHQUATERNION& result)
{
	using namespace DirectX;
	XMVECTOR q = XMLoadFloat4(&Q);
	XMStoreFloat4(&result, XMQuaternionInverse(q));
}

inline float XM_CALLCONV MHQUATERNION::Dot(const MHQUATERNION& Q1, const MHQUATERNION& Q2)
{
	using namespace DirectX;
	XMVECTOR q1 = XMLoadFloat4(&Q1);
	XMVECTOR q2 = XMLoadFloat4(&Q2);
	return XMVectorGetX(XMQuaternionDot(q1, q2));
}

inline MHQUATERNION XM_CALLCONV MHQUATERNION::RotationAxis(const MHVECTOR3& axis, float angle)
{
    using namespace DirectX;
    XMVECTOR a = XMLoadFloat3( &axis );

    MHQUATERNION R;
    XMStoreFloat4( &R, XMQuaternionRotationAxis( a, angle ) );
    return R;
}

inline MHQUATERNION XM_CALLCONV MHQUATERNION::RotationRollPitchYaw(float yaw, float pitch, float roll)
{
    using namespace DirectX;
    MHQUATERNION R;
    XMStoreFloat4( &R, XMQuaternionRotationRollPitchYaw( pitch, yaw, roll ) );
    return R;
}

inline MHQUATERNION XM_CALLCONV MHQUATERNION::RotationMatrix(const MHMATRIX& M)
{
    using namespace DirectX;
    XMMATRIX M0 = XMLoadFloat4x4( &M );

    MHQUATERNION R;
    XMStoreFloat4( &R, XMQuaternionRotationMatrix( M0 ) );
    return R;
}

inline void XM_CALLCONV MHQUATERNION::Barycentric(const MHQUATERNION& Q1, const MHQUATERNION& Q2, const MHQUATERNION& Q3, float f, float g, MHQUATERNION& result)
{
	using namespace DirectX;
	XMVECTOR q1 = XMLoadFloat4(&Q1);
	XMVECTOR q2 = XMLoadFloat4(&Q2);
	XMVECTOR q3 = XMLoadFloat4(&Q3);
	XMVECTOR X = XMQuaternionBaryCentric(q1, q2, q3, f, g);
	XMStoreFloat4(&result, X);
}

inline MHQUATERNION XM_CALLCONV MHQUATERNION::Barycentric(const MHQUATERNION& Q1, const MHQUATERNION& Q2, const MHQUATERNION& Q3, float f, float g)
{
	using namespace DirectX;
	XMVECTOR q1 = XMLoadFloat4(&Q1);
	XMVECTOR q2 = XMLoadFloat4(&Q2);
	XMVECTOR q3 = XMLoadFloat4(&Q3);
	XMVECTOR X = XMQuaternionBaryCentric(q1, q2, q3, f, g);

	MHVECTOR2 result;
	XMStoreFloat2(&result, X);
	return result;
}

inline void XM_CALLCONV MHQUATERNION::Barycentric(const MHQUATERNION& Q1, const MHQUATERNION& Q2, const MHQUATERNION& Q3, FXMVECTOR& f, FXMVECTOR& g, MHQUATERNION& result)
{
	using namespace DirectX;
	XMVECTOR q1 = XMLoadFloat4(&Q1);
	XMVECTOR q2 = XMLoadFloat4(&Q2);
	XMVECTOR q3 = XMLoadFloat4(&Q3);
	XMVECTOR X = XMQuaternionBaryCentricV(q1, q2, q3, f, g);
	XMStoreFloat4(&result, X);
}

inline MHQUATERNION XM_CALLCONV MHQUATERNION::Barycentric(const MHQUATERNION& Q1, const MHQUATERNION& Q2, const MHQUATERNION& Q3, FXMVECTOR& f, FXMVECTOR& g)
{
	using namespace DirectX;
	XMVECTOR q1 = XMLoadFloat4(&Q1);
	XMVECTOR q2 = XMLoadFloat4(&Q2);
	XMVECTOR q3 = XMLoadFloat4(&Q3);
	XMVECTOR X = XMQuaternionBaryCentricV(q1, q2, q3, f, g);

	MHVECTOR2 result;
	XMStoreFloat2(&result, X);
	return result;
}

inline void XM_CALLCONV MHQUATERNION::Lerp(const MHQUATERNION& q1, const MHQUATERNION& q2, float t, MHQUATERNION& result)
{
    using namespace DirectX;
    XMVECTOR Q0 = XMLoadFloat4( &q1 );
    XMVECTOR Q1 = XMLoadFloat4( &q2 );

    XMVECTOR dot = XMVector4Dot( Q0, Q1 );

    XMVECTOR R;
    if ( XMVector4GreaterOrEqual( dot, XMVectorZero() ) )
    {
        R = XMVectorLerp( Q0, Q1, t );
    }
    else
    {
        XMVECTOR tv = XMVectorReplicate( t );
        XMVECTOR t1v = XMVectorReplicate( 1.f - t );
        XMVECTOR X0 = XMVectorMultiply( Q0, t1v );
        XMVECTOR X1 = XMVectorMultiply( Q1, tv );
        R = XMVectorSubtract( X0, X1 );
    }

    XMStoreFloat4( &result, XMQuaternionNormalize( R ) );
}

inline MHQUATERNION XM_CALLCONV MHQUATERNION::Lerp(const MHQUATERNION& q1, const MHQUATERNION& q2, float t)
{
    using namespace DirectX;
    XMVECTOR Q0 = XMLoadFloat4( &q1 );
    XMVECTOR Q1 = XMLoadFloat4( &q2 );

    XMVECTOR dot = XMVector4Dot( Q0, Q1 );

    XMVECTOR R;
    if ( XMVector4GreaterOrEqual( dot, XMVectorZero() ) )
    {
        R = XMVectorLerp( Q0, Q1, t );
    }
    else
    {
        XMVECTOR tv = XMVectorReplicate( t );
        XMVECTOR t1v = XMVectorReplicate( 1.f - t );
        XMVECTOR X0 = XMVectorMultiply( Q0, t1v );
        XMVECTOR X1 = XMVectorMultiply( Q1, tv );
        R = XMVectorSubtract( X0, X1 );
    }

    MHQUATERNION result;
    XMStoreFloat4( &result, XMQuaternionNormalize( R ) );
    return result;
}

inline void XM_CALLCONV MHQUATERNION::Slerp(const MHQUATERNION& q1, const MHQUATERNION& q2, float t, MHQUATERNION& result)
{
    using namespace DirectX;
    XMVECTOR Q0 = XMLoadFloat4( &q1 );
    XMVECTOR Q1 = XMLoadFloat4( &q2 );
    XMStoreFloat4( &result, XMQuaternionSlerp( Q0, Q1, t ) );
}

inline MHQUATERNION XM_CALLCONV MHQUATERNION::Slerp(const MHQUATERNION& q1, const MHQUATERNION& q2, float t)
{
    using namespace DirectX;
    XMVECTOR Q0 = XMLoadFloat4( &q1 );
    XMVECTOR Q1 = XMLoadFloat4( &q2 );

    MHQUATERNION result;
    XMStoreFloat4( &result, XMQuaternionSlerp( Q0, Q1, t ) );
    return result;
}

inline void XM_CALLCONV MHQUATERNION::Concatenate(const MHQUATERNION& q1, const MHQUATERNION& q2, MHQUATERNION& result)
{
    using namespace DirectX;
    XMVECTOR Q0 = XMLoadFloat4( &q1 );
    XMVECTOR Q1 = XMLoadFloat4( &q2 );
    XMStoreFloat4( &result, XMQuaternionMultiply( Q1, Q0 ) );
}

inline MHQUATERNION XM_CALLCONV MHQUATERNION::Concatenate(const MHQUATERNION& q1, const MHQUATERNION& q2)
{
    using namespace DirectX;
    XMVECTOR Q0 = XMLoadFloat4( &q1 );
    XMVECTOR Q1 = XMLoadFloat4( &q2 );

    MHQUATERNION result;
    XMStoreFloat4( &result, XMQuaternionMultiply( Q1, Q0 ) );
    return result;
}

#	pragma endregion

/****************************************************************************
 *
 * MHCOLOR
 *
 ****************************************************************************/
#	pragma region MHCOLOR

inline MHCOLOR::MHCOLOR( const PackedVector::XMCOLOR& Packed )
{
    using namespace DirectX;
    XMStoreFloat4( this, PackedVector::XMLoadColor( &Packed ) );
}

inline MHCOLOR::MHCOLOR( const PackedVector::XMUBYTEN4& Packed )
{
    using namespace DirectX;
    XMStoreFloat4( this, PackedVector::XMLoadUByteN4( &Packed ) );
}

//------------------------------------------------------------------------------
// Comparision operators
//------------------------------------------------------------------------------
inline bool XM_CALLCONV MHCOLOR::operator == (const MHCOLOR& c) const
{
    using namespace DirectX;
    XMVECTOR c1 = XMLoadFloat4( this );
    XMVECTOR c2 = XMLoadFloat4( &c );
    return XMColorEqual( c1, c2 );
}

inline bool XM_CALLCONV MHCOLOR::operator != (const MHCOLOR& c) const
{
    using namespace DirectX;
    XMVECTOR c1 = XMLoadFloat4( this );
    XMVECTOR c2 = XMLoadFloat4( &c );
    return XMColorNotEqual( c1, c2 );
}

//------------------------------------------------------------------------------
// Assignment operators
//------------------------------------------------------------------------------

inline MHCOLOR& XM_CALLCONV MHCOLOR::operator+= (const MHCOLOR& c)
{
    using namespace DirectX;
    XMVECTOR c1 = XMLoadFloat4( this );
    XMVECTOR c2 = XMLoadFloat4( &c );
    XMStoreFloat4( this, XMVectorAdd( c1, c2 ) );
    return *this;
}

inline MHCOLOR& XM_CALLCONV MHCOLOR::operator+= (float S)
{
	using namespace DirectX;
	XMVECTOR c1 = XMLoadFloat4(this);
	XMVECTOR c2 = XMLoadFloat(&S);
	XMStoreFloat4(this, XMVectorAdd(c1, c2));
	return *this;
}

inline MHCOLOR& XM_CALLCONV MHCOLOR::operator-= (const MHCOLOR& c)
{
    using namespace DirectX;
    XMVECTOR c1 = XMLoadFloat4( this );
    XMVECTOR c2 = XMLoadFloat4( &c );
    XMStoreFloat4( this, XMVectorSubtract( c1, c2 ) );
    return *this;
}

inline MHCOLOR& XM_CALLCONV MHCOLOR::operator-= (float S)
{
	using namespace DirectX;
	XMVECTOR c1 = XMLoadFloat4(this);
	XMVECTOR c2 = XMLoadFloat(&S);
	XMStoreFloat4(this, XMVectorSubtract(c1, c2));
	return *this;
}

inline MHCOLOR& XM_CALLCONV MHCOLOR::operator*= (const MHCOLOR& c)
{
    using namespace DirectX;
    XMVECTOR c1 = XMLoadFloat4( this );
    XMVECTOR c2 = XMLoadFloat4( &c );
    XMStoreFloat4( this, XMVectorMultiply( c1, c2 ) );
    return *this;
}

inline MHCOLOR& XM_CALLCONV MHCOLOR::operator*= (float S)
{
    using namespace DirectX;
    XMVECTOR c = XMLoadFloat4( this );
    XMStoreFloat4( this, XMVectorScale( c, S ) );
    return *this;
}

inline MHCOLOR& XM_CALLCONV MHCOLOR::operator/= (const MHCOLOR& c)
{
    using namespace DirectX;
    XMVECTOR c1 = XMLoadFloat4( this );
    XMVECTOR c2 = XMLoadFloat4( &c );
    XMStoreFloat4( this, XMVectorDivide( c1, c2 ) );
    return *this;
}

inline MHCOLOR& XM_CALLCONV MHCOLOR::operator/= (float S)
{
	using namespace DirectX;
	assert(S != 0.f);

	XMVECTOR c1 = XMLoadFloat4(this);
	XMVECTOR X = XMVectorScale(c1, 1.f / S);
	XMStoreFloat4(this, X);
	return *this;
}

//------------------------------------------------------------------------------
// Urnary operators
//------------------------------------------------------------------------------

/*
inline MHCOLOR XM_CALLCONV MHCOLOR::operator+ () const
{
	using namespace DirectX;
	XMVECTOR c = XMLoadFloat4(this);
	MHCOLOR R;
	XMStoreFloat4(&R, +c);
	return R;
}*/

inline MHCOLOR XM_CALLCONV MHCOLOR::operator- () const
{
    using namespace DirectX;
    XMVECTOR c = XMLoadFloat4( this );
    MHCOLOR R;
    XMStoreFloat4( &R, XMVectorNegate( c ) );
    return R;
}

//------------------------------------------------------------------------------
// Binary operators
//------------------------------------------------------------------------------

inline MHCOLOR XM_CALLCONV operator+ (const MHCOLOR& C1, const MHCOLOR& C2)
{
    using namespace DirectX;
    XMVECTOR c1 = XMLoadFloat4( &C1 );
    XMVECTOR c2 = XMLoadFloat4( &C2 );
    MHCOLOR R;
    XMStoreFloat4( &R, XMVectorAdd( c1, c2 ) );
    return R;
}

inline MHCOLOR XM_CALLCONV operator+ (const MHCOLOR& C, float S)
{
	using namespace DirectX;
	XMVECTOR c1 = XMLoadFloat4(&C);
	XMVECTOR c2 = XMLoadFloat(&S);
	MHCOLOR R;
	XMStoreFloat4(&R, XMVectorAdd(c1, c2));
	return R;
}

inline MHCOLOR XM_CALLCONV operator+ (float S, const MHCOLOR& C)
{
	using namespace DirectX;
	XMVECTOR c1 = XMLoadFloat(&S);
	XMVECTOR c2 = XMLoadFloat4(&C);
	MHCOLOR R;
	XMStoreFloat4(&R, XMVectorAdd(c1, c2));
	return R;
}

inline MHCOLOR XM_CALLCONV operator- (const MHCOLOR& C1, const MHCOLOR& C2)
{
    using namespace DirectX;
    XMVECTOR c1 = XMLoadFloat4( &C1 );
    XMVECTOR c2 = XMLoadFloat4( &C2 );
    MHCOLOR R;
    XMStoreFloat4( &R, XMVectorSubtract( c1, c2 ) );
    return R;
}

inline MHCOLOR XM_CALLCONV operator- (const MHCOLOR& C, float S)
{
	using namespace DirectX;
	XMVECTOR c1 = XMLoadFloat4(&C);
	XMVECTOR c2 = XMLoadFloat(&S);
	MHCOLOR R;
	XMStoreFloat4(&R, XMVectorSubtract(c1, c2));
	return R;
}

inline MHCOLOR XM_CALLCONV operator- (float S, const MHCOLOR& C)
{
	using namespace DirectX;
	XMVECTOR c1 = XMLoadFloat(&S);
	XMVECTOR c2 = XMLoadFloat4(&C);
	MHCOLOR R;
	XMStoreFloat4(&R, XMVectorSubtract(c1, c2));
	return R;
}

inline MHCOLOR XM_CALLCONV operator* (const MHCOLOR& C1, const MHCOLOR& C2)
{
    using namespace DirectX;
    XMVECTOR c1 = XMLoadFloat4( &C1 );
    XMVECTOR c2 = XMLoadFloat4( &C2 );
    MHCOLOR R;
    XMStoreFloat4( &R, XMVectorMultiply( c1, c2 ) );
    return R;
}

inline MHCOLOR XM_CALLCONV operator* (const MHCOLOR& C, float S)
{
    using namespace DirectX;
    XMVECTOR c = XMLoadFloat4( &C );
    MHCOLOR R;
    XMStoreFloat4( &R, XMVectorScale( c, S ) );
    return R;
}

inline MHCOLOR XM_CALLCONV operator* (float S, const MHCOLOR& C)
{
	using namespace DirectX;
	XMVECTOR c1 = XMLoadFloat4(&C);
	MHCOLOR R;
	XMStoreFloat4(&R, XMVectorScale(c1, S));
	return R;
}

inline MHCOLOR XM_CALLCONV operator/ (const MHCOLOR& C1, const MHCOLOR& C2)
{
    using namespace DirectX;
    XMVECTOR c1 = XMLoadFloat4( &C1 );
    XMVECTOR c2 = XMLoadFloat4( &C2 );
    MHCOLOR R;
    XMStoreFloat4( &R, XMVectorDivide( c1, c2 ) );
    return R;
}

inline MHCOLOR XM_CALLCONV operator/ (const MHCOLOR& C, float S)
{
	using namespace DirectX;
	assert(S != 0.f);

	XMVECTOR q1 = XMLoadFloat4(&C);
	XMVECTOR X = XMVectorScale(q1, 1.f / S);

	MHCOLOR R;
	XMStoreFloat4(&R, X);
	return R;
}

inline MHCOLOR XM_CALLCONV operator/ (float S, const MHCOLOR& C)
{
	using namespace DirectX;
	assert(S != 0.f);

	XMVECTOR q1 = XMLoadFloat4(&C);
	XMVECTOR X = XMVectorScale(q1, 1.f / S);

	MHCOLOR R;
	XMStoreFloat4(&R, X);
	return R;
}

//------------------------------------------------------------------------------
// MHCOLOR operations
//------------------------------------------------------------------------------

inline PackedVector::XMCOLOR XM_CALLCONV MHCOLOR::BGRA() const
{
    using namespace DirectX;
    XMVECTOR clr = XMLoadFloat4( this );
    PackedVector::XMCOLOR Packed;
    PackedVector::XMStoreColor( &Packed, clr );
    return Packed;
}

inline PackedVector::XMUBYTEN4 XM_CALLCONV MHCOLOR::RGBA() const
{
    using namespace DirectX;
    XMVECTOR clr = XMLoadFloat4( this );
    PackedVector::XMUBYTEN4 Packed;
    PackedVector::XMStoreUByteN4( &Packed, clr );
    return Packed;
}

inline MHVECTOR3 XM_CALLCONV MHCOLOR::CToVector3() const
{
    return MHVECTOR3( x, y, z );
}

inline MHVECTOR4 XM_CALLCONV MHCOLOR::CToVector4() const
{
    return MHVECTOR4( x, y, z, w );
}

inline void XM_CALLCONV MHCOLOR::CNegate()
{
    using namespace DirectX;
    XMVECTOR c = XMLoadFloat4( this );
    XMStoreFloat4( this, XMColorNegative( c) );
}

inline void XM_CALLCONV MHCOLOR::CNegate(MHCOLOR& result) const
{
    using namespace DirectX;
    XMVECTOR c = XMLoadFloat4( this );
    XMStoreFloat4( &result, XMColorNegative( c ) );
}

inline void XM_CALLCONV MHCOLOR::CSaturate()
{
    using namespace DirectX;
    XMVECTOR c = XMLoadFloat4( this );
    XMStoreFloat4( this, XMVectorSaturate( c ) );
}

inline void XM_CALLCONV MHCOLOR::CSaturate(MHCOLOR& result) const
{
    using namespace DirectX;
    XMVECTOR c = XMLoadFloat4( this );
    XMStoreFloat4( &result, XMVectorSaturate( c ) );
}

inline void XM_CALLCONV MHCOLOR::CPremultiply()
{
    using namespace DirectX;
    XMVECTOR c = XMLoadFloat4( this );
    XMVECTOR a = XMVectorSplatW( c );
    a = XMVectorSelect( g_XMIdentityR3, a, g_XMSelect1110 );
    XMStoreFloat4( this, XMVectorMultiply( c, a ) );
}

inline void XM_CALLCONV MHCOLOR::CPremultiply(MHCOLOR& result) const
{
    using namespace DirectX;
    XMVECTOR c = XMLoadFloat4( this );
    XMVECTOR a = XMVectorSplatW( c );
    a = XMVectorSelect( g_XMIdentityR3, a, g_XMSelect1110 );
    XMStoreFloat4( &result, XMVectorMultiply( c, a ) );
}

inline void XM_CALLCONV MHCOLOR::CAdjustSaturation(float sat)
{
    using namespace DirectX;
    XMVECTOR c = XMLoadFloat4( this );
    XMStoreFloat4( this, XMColorAdjustSaturation( c, sat ) );
}

inline void XM_CALLCONV MHCOLOR::CAdjustSaturation(float sat, MHCOLOR& result) const
{
    using namespace DirectX;
    XMVECTOR c = XMLoadFloat4( this );
    XMStoreFloat4( &result, XMColorAdjustSaturation( c, sat ) );
}

inline void XM_CALLCONV MHCOLOR::CAdjustContrast(float contrast)
{
    using namespace DirectX;
    XMVECTOR c = XMLoadFloat4( this );
    XMStoreFloat4( this, XMColorAdjustContrast( c, contrast ) );
}

inline void XM_CALLCONV MHCOLOR::CAdjustContrast(float contrast, MHCOLOR& result) const
{
    using namespace DirectX;
    XMVECTOR c = XMLoadFloat4( this );
    XMStoreFloat4( &result, XMColorAdjustContrast( c, contrast ) );
}

//------------------------------------------------------------------------------
// Static functions
//------------------------------------------------------------------------------

inline MHVECTOR3 XM_CALLCONV MHCOLOR::ToVector3(const MHCOLOR& c)
{
	using namespace DirectX;
	MHVECTOR3 VC = (MHVECTOR3)(c.x, c.y, c.z);
	MHVECTOR3 R;
	XMStoreFloat3(&R, VC);
	return R;
}

inline MHVECTOR4 XM_CALLCONV MHCOLOR::ToVector4(const MHCOLOR& c)
{
	using namespace DirectX;
	MHVECTOR4 VC = (MHVECTOR4)(c.x, c.y, c.z, c.w);
	MHVECTOR4 R;
	XMStoreFloat4(&R, VC);
	return R;
}

inline MHVECTOR4 XM_CALLCONV MHCOLOR::HSLToRGB(const MHVECTOR4& c)
{
	using namespace DirectX;
	MHVECTOR4 VC = XMColorHSLToRGB(c);
	MHVECTOR4 R;
	XMStoreFloat4(&R, VC);
	return R;
}

inline MHVECTOR4 XM_CALLCONV MHCOLOR::HSVToRGB(const MHVECTOR4& c)
{
	using namespace DirectX;
	MHVECTOR4 VC = XMColorHSVToRGB(c);
	MHVECTOR4 R;
	XMStoreFloat4(&R, VC);
	return R;
}

inline MHVECTOR4 XM_CALLCONV MHCOLOR::RGBToHSL(const MHVECTOR4& c)
{
	using namespace DirectX;
	MHVECTOR4 VC = XMColorRGBToHSL(c);
	MHVECTOR4 R;
	XMStoreFloat4(&R, VC);
	return R;
}

inline MHVECTOR4 XM_CALLCONV MHCOLOR::RGBToHSV(const MHVECTOR4& c)
{
	using namespace DirectX;
	MHVECTOR4 VC = XMColorRGBToHSV(c);
	MHVECTOR4 R;
	XMStoreFloat4(&R, VC);
	return R;
}

inline MHVECTOR4 XM_CALLCONV MHCOLOR::RGBToXYZ(const MHVECTOR4& c)
{
	using namespace DirectX;
	MHVECTOR4 VC = XMColorRGBToXYZ(c);
	MHVECTOR4 R;
	XMStoreFloat4(&R, VC);
	return R;
}

inline MHVECTOR4 XM_CALLCONV MHCOLOR::RGBToYUV(const MHVECTOR4& c)
{
	using namespace DirectX;
	MHVECTOR4 VC = XMColorRGBToYUV(c);
	MHVECTOR4 R;
	XMStoreFloat4(&R, VC);
	return R;
}

inline MHVECTOR4 XM_CALLCONV MHCOLOR::RGBToYUV_HD(const MHVECTOR4& c)
{
	using namespace DirectX;
	MHVECTOR4 VC = XMColorRGBToYUV_HD(c);
	MHVECTOR4 R;
	XMStoreFloat4(&R, VC);
	return R;
}

inline MHVECTOR4 XM_CALLCONV MHCOLOR::SRGBToXYZ(const MHVECTOR4& c)
{
	using namespace DirectX;
	MHVECTOR4 VC = XMColorSRGBToXYZ(c);
	MHVECTOR4 R;
	XMStoreFloat4(&R, VC);
	return R;
}

inline MHVECTOR4 XM_CALLCONV MHCOLOR::XYZToRGB(const MHVECTOR4& c)
{
	using namespace DirectX;
	MHVECTOR4 VC = XMColorXYZToRGB(c);
	MHVECTOR4 R;
	XMStoreFloat4(&R, VC);
	return R;
}

inline MHVECTOR4 XM_CALLCONV MHCOLOR::XYZToSRGB(const MHVECTOR4& c)
{
	using namespace DirectX;
	MHVECTOR4 VC = XMColorXYZToSRGB(c);
	MHVECTOR4 R;
	XMStoreFloat4(&R, VC);
	return R;
}

inline MHVECTOR4 XM_CALLCONV MHCOLOR::YUVToRGB(const MHVECTOR4& c)
{
	using namespace DirectX;
	MHVECTOR4 VC = XMColorYUVToRGB(c);
	MHVECTOR4 R;
	XMStoreFloat4(&R, VC);
	return R;
}

inline MHVECTOR4 XM_CALLCONV MHCOLOR::YUVToRGB_HD(const MHVECTOR4& c)
{
	using namespace DirectX;
	MHVECTOR4 VC = XMColorYUVToRGB_HD(c);
	MHVECTOR4 R;
	XMStoreFloat4(&R, VC);
	return R;
}

inline MHCOLOR XM_CALLCONV MHCOLOR::Negate(const MHCOLOR& c)
{
	using namespace DirectX;
	XMVECTOR c1 = XMLoadFloat4(&c);
	MHCOLOR R;
	XMStoreFloat4(&R, XMColorNegative(c1));
	return R;
}

inline void XM_CALLCONV MHCOLOR::Negate(const MHCOLOR& c, MHCOLOR& result)
{
	using namespace DirectX;
	XMVECTOR c1 = XMLoadFloat4(&c);
	XMStoreFloat4(&result, XMColorNegative(c1));
}

inline MHCOLOR XM_CALLCONV MHCOLOR::Saturate(const MHCOLOR& c)
{
	using namespace DirectX;
	XMVECTOR c1 = XMLoadFloat4(&c);
	MHCOLOR R;
	XMStoreFloat4(&R, XMVectorSaturate(c1));
	return R;
}

inline void XM_CALLCONV MHCOLOR::Saturate(const MHCOLOR& c, MHCOLOR& result)
{
	using namespace DirectX;
	XMVECTOR c1 = XMLoadFloat4(&c);
	XMStoreFloat4(&result, XMVectorSaturate(c1));
}

inline MHCOLOR XM_CALLCONV MHCOLOR::Premultiply(const MHCOLOR& c)
{
	using namespace DirectX;
	XMVECTOR c1 = XMLoadFloat4(&c);
	XMVECTOR a = XMVectorSplatW(c1);
	a = XMVectorSelect(g_XMIdentityR3, a, g_XMSelect1110);
	MHCOLOR R;
	XMStoreFloat4(&R, XMVectorMultiply(c1, a));
	return R;
}

inline void XM_CALLCONV MHCOLOR::Premultiply(const MHCOLOR& c, MHCOLOR& result)
{
	using namespace DirectX;
	XMVECTOR c1 = XMLoadFloat4(&c);
	XMVECTOR a = XMVectorSplatW(c1);
	a = XMVectorSelect(g_XMIdentityR3, a, g_XMSelect1110);
	XMStoreFloat4(&result, XMVectorMultiply(c1, a));
}

inline MHCOLOR XM_CALLCONV MHCOLOR::AdjustSaturation(const MHCOLOR& c, float sat)
{
	using namespace DirectX;
	XMVECTOR c1 = XMLoadFloat4(&c);
	MHCOLOR R;
	XMStoreFloat4(&R, XMColorAdjustSaturation(c1, sat));
	return R;
}

inline void XM_CALLCONV MHCOLOR::AdjustSaturation(const MHCOLOR& c, float sat, MHCOLOR& result)
{
	using namespace DirectX;
	XMVECTOR c1 = XMLoadFloat4(&c);
	XMStoreFloat4(&result, XMColorAdjustSaturation(c1, sat));
}

inline MHCOLOR XM_CALLCONV MHCOLOR::AdjustContrast(const MHCOLOR& c, float contrast)
{
	using namespace DirectX;
	XMVECTOR c1 = XMLoadFloat4(&c);
	MHCOLOR R;
	XMStoreFloat4(&R, XMColorAdjustContrast(c1, contrast));
	return R;
}

inline void XM_CALLCONV MHCOLOR::AdjustContrast(const MHCOLOR& c, float contrast, MHCOLOR& result)
{
	using namespace DirectX;
	XMVECTOR c1 = XMLoadFloat4(&c);
	XMStoreFloat4(&result, XMColorAdjustContrast(c1, contrast));
}

inline void XM_CALLCONV MHCOLOR::Modulate(const MHCOLOR& c1, const MHCOLOR& c2, MHCOLOR& result)
{
    using namespace DirectX;
    XMVECTOR C0 = XMLoadFloat4( &c1 );
    XMVECTOR C1 = XMLoadFloat4( &c2 );
    XMStoreFloat4( &result, XMColorModulate( C0, C1 ) );
}

inline MHCOLOR XM_CALLCONV MHCOLOR::Modulate(const MHCOLOR& c1, const MHCOLOR& c2)
{
    using namespace DirectX;
    XMVECTOR C0 = XMLoadFloat4( &c1 );
    XMVECTOR C1 = XMLoadFloat4( &c2 );

    MHCOLOR result;
    XMStoreFloat4( &result, XMColorModulate( C0, C1 ) );
    return result;
}

inline void XM_CALLCONV MHCOLOR::Lerp(const MHCOLOR& c1, const MHCOLOR& c2, float t, MHCOLOR& result)
{
    using namespace DirectX;
    XMVECTOR C0 = XMLoadFloat4( &c1 );
    XMVECTOR C1 = XMLoadFloat4( &c2 );
    XMStoreFloat4( &result, XMVectorLerp( C0, C1, t ) );
}

inline MHCOLOR XM_CALLCONV MHCOLOR::Lerp(const MHCOLOR& c1, const MHCOLOR& c2, float t)
{
    using namespace DirectX;
    XMVECTOR C0 = XMLoadFloat4( &c1 );
    XMVECTOR C1 = XMLoadFloat4( &c2 );

    MHCOLOR result;
    XMStoreFloat4( &result, XMVectorLerp( C0, C1, t ) );
    return result;
}

#	pragma endregion

/****************************************************************************
*
* MHLINE
*
****************************************************************************/
#	pragma region MHLINE

//------------------------------------------------------------------------------
// Comparision operators
//------------------------------------------------------------------------------

inline bool XM_CALLCONV MHLINE::operator == (const MHLINE& line) const
{
	using namespace DirectX;
	using DirectX::MHLINE;
	XMVECTOR l1p = XMLoadFloat3(&spoint);
	XMVECTOR l2p = XMLoadFloat3(&line.spoint);
	XMVECTOR l1d = XMLoadFloat3(&dpoint);
	XMVECTOR l2d = XMLoadFloat3(&line.dpoint);
	return XMVector3Equal(l1p, l2p) && XMVector3Equal(l1d, l2d);
}

inline bool XM_CALLCONV MHLINE::operator != (const MHLINE& line) const
{
	using namespace DirectX;
	using DirectX::MHLINE;
	XMVECTOR l1p = XMLoadFloat3(&spoint);
	XMVECTOR l2p = XMLoadFloat3(&line.spoint);
	XMVECTOR l1d = XMLoadFloat3(&dpoint);
	XMVECTOR l2d = XMLoadFloat3(&line.dpoint);
	return XMVector3NotEqual(l1p, l2p) && XMVector3NotEqual(l1d, l2d);
}

//------------------------------------------------------------------------------
// MHLINE operations
//------------------------------------------------------------------------------

inline float XM_CALLCONV MHLINE::Length() const
{
	using namespace DirectX;
	using DirectX::MHLINE;
	XMVECTOR l1 = XMVectorSubtract(dpoint, spoint);
	XMVECTOR L = XMVector3Length(l1);
	return XMVectorGetX(L);
}

inline float XM_CALLCONV MHLINE::LengthSquared() const
{
	using namespace DirectX;
	using DirectX::MHLINE;
	XMVECTOR l1 = XMVectorSubtract(dpoint, spoint);
	XMVECTOR L = XMVector3Length(l1);
	return XMVectorGetX(L);
}

inline MHVECTOR3 XM_CALLCONV MHLINE::Vector() const
{
	using namespace DirectX;
	using DirectX::MHLINE;
	XMVECTOR Lv = XMVectorSubtract(dpoint, spoint);
	return Lv;
}

inline MHVECTOR3 MHLINE::Direction() const
{
	using namespace DirectX;
	using DirectX::MHLINE;
	XMVECTOR Lv = XMVectorSubtract(dpoint, spoint);
	XMVECTOR L = XMVector3Normalize(Lv);

	MHVECTOR3 result;
	XMStoreFloat3(&result, L);
	return result;
}

inline MHVECTOR3 MHLINE::MidPoint() const
{
	using namespace DirectX;
	using DirectX::MHLINE;
	static const float HALF = 0.5f;

	XMVECTOR Lv1 = XMVectorSubtract(dpoint, spoint);
	XMVECTOR Lv2 = XMVectorReplicate(HALF);
	XMVECTOR L = XMVectorMultiply(Lv1, Lv2);

	MHVECTOR3 result;
	XMStoreFloat3(&result, L);
	return result;
}

inline MHVECTOR3 XM_CALLCONV MHLINE::AtPoint(float t) const
{
	using namespace DirectX;
	using DirectX::MHLINE;
	XMVECTOR l = XMLoadFloat(&t);
	XMVECTOR L = MHVECTOR3::Lerp(spoint, dpoint, t);

	MHVECTOR3 result;
	XMStoreFloat3(&result, L);
	return result;
}

inline void MHLINE::Extend(float samount, float eamount)
{
	using namespace DirectX;
	using DirectX::MHLINE;
	XMVECTOR start = XMLoadFloat3(&spoint);
	XMVECTOR end = XMLoadFloat3(&dpoint);
	XMVECTOR dir = XMVector3Normalize(XMVectorSubtract(end, start));
	XMVECTOR sp = XMVectorSubtract(start, XMVectorMultiply(dir, XMVectorReplicate(samount)));
	XMVECTOR sd = XMVectorAdd(end, XMVectorMultiply(dir, XMVectorReplicate(eamount)));
	XMStoreFloat3(&spoint, sp);
	XMStoreFloat3(&dpoint, sd);
}

//------------------------------------------------------------------------------
// Static functions
//------------------------------------------------------------------------------
/*
inline float XM_CALLCONV MHLINE::Length()
{
	using namespace DirectX;
	using DirectX::MHLINE;
	XMVECTOR l1 = XMVectorSubtract(dpoint, spoint);
	XMVECTOR L = XMVector3Length(l1);
	return XMVectorGetX(L);
}

inline float XM_CALLCONV MHLINE::LengthSquared()
{
	using namespace DirectX;
	using DirectX::MHLINE;
	XMVECTOR l1 = XMVectorSubtract(dpoint, spoint);
	XMVECTOR L = XMVector3Length(l1);
	return XMVectorGetX(L);
}

inline MHVECTOR3 XM_CALLCONV MHLINE::Vector()
{
	using namespace DirectX;
	XMVECTOR Lv = XMVectorSubtract(dpoint, spoint);
	return Lv;
}

inline MHVECTOR3 MHLINE::Direction()
{
	using namespace DirectX;
	using DirectX::MHLINE;
	XMVECTOR Lv = XMVectorSubtract(dpoint, spoint);
	XMVECTOR L = XMVector3Normalize(Lv);

	MHVECTOR3 result;
	XMStoreFloat3(&result, L);
	return result;
}

inline MHVECTOR3 MHLINE::MidPoint()
{
	using namespace DirectX;
	using DirectX::MHLINE;
	static const float HALF = 0.5f;

	XMVECTOR Lv1 = XMVectorSubtract(dpoint, spoint);
	XMVECTOR Lv2 = XMVectorReplicate(HALF);
	XMVECTOR L = XMVectorMultiply(Lv1, Lv2);

	MHVECTOR3 result;
	XMStoreFloat3(&result, L);
	return result;
}

inline MHVECTOR3 XM_CALLCONV MHLINE::AtPoint(float t)
{
	using namespace DirectX;
	using DirectX::MHLINE;
	XMVECTOR l = XMLoadFloat(&t);
	XMVECTOR L = XMVectorLerp(spoint, dpoint, t);

	MHVECTOR3 result;
	XMStoreFloat3(&result, L);
	return result;
}

inline void MHLINE::Extend(float samount, float eamount)
{
	using namespace DirectX;
	using DirectX::MHLINE;
	XMVECTOR start = XMLoadFloat3(&spoint);
	XMVECTOR end = XMLoadFloat3(&dpoint);
	XMVECTOR dir = XMVector3Normalize(XMVectorSubtract(end, start));
	XMVECTOR sp = XMVectorSubtract(start, XMVectorMultiply(dir, XMVectorReplicate(samount)));
	XMVECTOR sd = XMVectorAdd(end, XMVectorMultiply(dir, XMVectorReplicate(eamount)));
	XMStoreFloat3(&spoint, sp);
	XMStoreFloat3(&dpoint, sd);
}
*/

#	pragma endregion

/****************************************************************************
 *
 * MHRAY
 *
 ****************************************************************************/
#	pragma region MHRAY

//-----------------------------------------------------------------------------
// Comparision operators
//------------------------------------------------------------------------------
inline bool XM_CALLCONV MHRAY::operator == (const MHRAY& r) const
{
    using namespace DirectX;
    XMVECTOR r1p = XMLoadFloat3( &position );
    XMVECTOR r2p = XMLoadFloat3( &r.position );
    XMVECTOR r1d = XMLoadFloat3( &direction );
    XMVECTOR r2d = XMLoadFloat3( &r.direction );
    return XMVector3Equal( r1p, r2p ) && XMVector3Equal( r1d, r2d );
}

inline bool XM_CALLCONV MHRAY::operator != (const MHRAY& r) const
{
    using namespace DirectX;
    XMVECTOR r1p = XMLoadFloat3( &position );
    XMVECTOR r2p = XMLoadFloat3( &r.position );
    XMVECTOR r1d = XMLoadFloat3( &direction );
    XMVECTOR r2d = XMLoadFloat3( &r.direction );
    return XMVector3NotEqual( r1p, r2p ) && XMVector3NotEqual( r1d, r2d );
}

//-----------------------------------------------------------------------------
// MHRAY operators
//------------------------------------------------------------------------------

inline bool XM_CALLCONV MHRAY::Intersects(const BoundingSphere& sphere, _Out_ float& Dist) const
{
    return sphere.Intersects( position, direction, Dist );
}

inline bool XM_CALLCONV MHRAY::Intersects(const BoundingBox& box, _Out_ float& Dist) const
{
    return box.Intersects( position, direction, Dist );
}

inline bool XM_CALLCONV MHRAY::Intersects(const MHVECTOR3& tri0, const MHVECTOR3& tri1, const MHVECTOR3& tri2, _Out_ float& Dist) const
{
    return TriangleTests::Intersects( position, direction, tri0, tri1, tri2, Dist );
}

inline bool XM_CALLCONV MHRAY::Intersects(const MHPLANE& plane, _Out_ float& Dist) const
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

#	pragma endregion

//  ------------------------------------------------------------------------------
/// XMFLOAT2 operators
//--------------------------------------------------------------------------------
#	pragma region XMFLOAT2 operators

//------------------------------------------------------------------------------
// Comparision operators
//------------------------------------------------------------------------------

inline bool XM_CALLCONV operator== (const XMFLOAT2& V1, const XMFLOAT2& V2)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(&V1);
	XMVECTOR v2 = XMLoadFloat2(&V2);
	return XMVector2Equal(v1, v2);
}

inline bool XM_CALLCONV operator!= (const XMFLOAT2& V1, const XMFLOAT2& V2)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(&V1);
	XMVECTOR v2 = XMLoadFloat2(&V2);
	return XMVector2NotEqual(v1, v2);
}

//------------------------------------------------------------------------------
// Assignment operators
//------------------------------------------------------------------------------

inline XMFLOAT2 XM_CALLCONV operator+= (XMFLOAT2& V1, const XMFLOAT2& V2)
{
	XMVECTOR v1 = XMLoadFloat2(&V1);
	XMVECTOR v2 = XMLoadFloat2(&V2);
	XMVECTOR X = XMVectorAdd(v1, v2);
	XMStoreFloat2(&V1, X);
	return V1;
}

inline XMFLOAT2 XM_CALLCONV operator+= (XMFLOAT2& V, float S)
{
	XMVECTOR v1 = XMLoadFloat2(&V);
	XMVECTOR v2 = XMLoadFloat(&S);
	XMVECTOR X = XMVectorAdd(v1, v2);
	XMStoreFloat2(&V, X);
	return V;
}

inline XMFLOAT2 XM_CALLCONV operator+= (float S, const XMFLOAT2& V)
{
	XMVECTOR v1 = XMLoadFloat(&S);
	XMVECTOR v2 = XMLoadFloat2(&V);
	XMVECTOR X = XMVectorAdd(v1, v2);
	XMFLOAT2 R;
	XMStoreFloat2(&R, X);
	return R;
}

inline XMFLOAT2 XM_CALLCONV operator-= (XMFLOAT2& V1, const XMFLOAT2& V2)
{
	XMVECTOR v1 = XMLoadFloat2(&V1);
	XMVECTOR v2 = XMLoadFloat2(&V2);
	XMVECTOR X = XMVectorSubtract(v1, v2);
	XMStoreFloat2(&V1, X);
	return V1;
}

inline XMFLOAT2 XM_CALLCONV operator-= (XMFLOAT2& V, float S)
{
	XMVECTOR v1 = XMLoadFloat2(&V);
	XMVECTOR v2 = XMLoadFloat(&S);
	XMVECTOR X = XMVectorSubtract(v1, v2);
	XMStoreFloat2(&V, X);
	return V;
}

inline XMFLOAT2 XM_CALLCONV operator-= (float S, const XMFLOAT2& V)
{
	XMVECTOR v1 = XMLoadFloat(&S);
	XMVECTOR v2 = XMLoadFloat2(&V);
	XMVECTOR X = XMVectorSubtract(v1, v2);
	XMFLOAT2 R;
	XMStoreFloat2(&R, X);
	return R;
}

inline XMFLOAT2 XM_CALLCONV operator*= (XMFLOAT2& V1, const XMFLOAT2& V2)
{
	XMVECTOR v1 = XMLoadFloat2(&V1);
	XMVECTOR v2 = XMLoadFloat2(&V2);
	XMVECTOR X = XMVectorMultiply(v1, v2);
	XMStoreFloat2(&V1, X);
	return V1;
}

inline XMFLOAT2 XM_CALLCONV operator*= (XMFLOAT2& V, float S)
{
	XMVECTOR v1 = XMLoadFloat2(&V);
	XMVECTOR X = XMVectorScale(v1, S);
	XMStoreFloat2(&V, X);
	return V;
}

inline XMFLOAT2 XM_CALLCONV operator*= (float S, XMFLOAT2& V)
{
	XMVECTOR v1 = XMLoadFloat2(&V);
	XMVECTOR X = XMVectorScale(v1, S);
	XMStoreFloat2(&V, X);
	return V;
}

inline XMFLOAT2 XM_CALLCONV operator/= (XMFLOAT2& V1, const XMFLOAT2& V2)
{
	XMVECTOR v1 = XMLoadFloat2(&V1);
	XMVECTOR v2 = XMLoadFloat2(&V2);
	XMVECTOR X = XMVectorDivide(v1, v2);
	XMStoreFloat2(&V1, X);
	return V1;
}

inline XMFLOAT2 XM_CALLCONV operator/= (XMFLOAT2& V, float S)
{
	assert(S != 0.0f);
	XMVECTOR v1 = XMLoadFloat2(&V);
	XMVECTOR X = XMVectorScale(v1, 1.f / S);
	XMStoreFloat2(&V, X);
	return V;
}

inline XMFLOAT2 XM_CALLCONV operator/= (float S, XMFLOAT2& V)
{
	assert(S != 0.0f);
	XMVECTOR v1 = XMLoadFloat2(&V);
	XMVECTOR X = XMVectorScale(v1, 1.f / S);
	XMStoreFloat2(&V, X);
	return V;
}

//------------------------------------------------------------------------------
// Urnary operators
//------------------------------------------------------------------------------

inline XMFLOAT2 XM_CALLCONV operator+ (const XMFLOAT2& V)
{
	XMVECTOR v1 = XMLoadFloat2(&V);
	XMVECTOR X = +v1;
	XMFLOAT2 R;
	XMStoreFloat2(&R, X);
	return R;
}

inline XMFLOAT2 XM_CALLCONV operator- (const XMFLOAT2& V)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(&V);
	XMVECTOR X = XMVectorNegate(v1);
	XMFLOAT2 R;
	XMStoreFloat2(&R, X);
	return R;
}

//------------------------------------------------------------------------------
// Binary operators
//------------------------------------------------------------------------------

inline XMFLOAT2 XM_CALLCONV operator+ (const XMFLOAT2& V1, const XMFLOAT2& V2)
{
	XMVECTOR v1 = XMLoadFloat2(&V1);
	XMVECTOR v2 = XMLoadFloat2(&V2);
	XMVECTOR X = XMVectorAdd(v1, v2);
	XMFLOAT2 R;
	XMStoreFloat2(&R, X);
	return R;
}

inline XMFLOAT2 XM_CALLCONV operator+ (const XMFLOAT2& V, float S)
{
	XMVECTOR v1 = XMLoadFloat2(&V);
	XMVECTOR v2 = XMLoadFloat(&S);
	XMVECTOR X = XMVectorAdd(v1, v2);
	XMFLOAT2 R;
	XMStoreFloat2(&R, X);
	return R;
}

inline XMFLOAT2 XM_CALLCONV operator+ (float S, const XMFLOAT2& V)
{
	XMVECTOR v1 = XMLoadFloat(&S);
	XMVECTOR v2 = XMLoadFloat2(&V);
	XMVECTOR X = XMVectorAdd(v1, v2);
	XMFLOAT2 R;
	XMStoreFloat2(&R, X);
	return R;
}

inline XMFLOAT2 XM_CALLCONV operator- (const XMFLOAT2& V1, const XMFLOAT2& V2)
{
	XMVECTOR v1 = XMLoadFloat2(&V1);
	XMVECTOR v2 = XMLoadFloat2(&V2);
	XMVECTOR X = XMVectorSubtract(v1, v2);
	XMFLOAT2 R;
	XMStoreFloat2(&R, X);
	return R;
}

inline XMFLOAT2 XM_CALLCONV operator- (const XMFLOAT2& V, float S)
{
	XMVECTOR v1 = XMLoadFloat2(&V);
	XMVECTOR v2 = XMLoadFloat(&S);
	XMVECTOR X = XMVectorSubtract(v1, v2);
	XMFLOAT2 R;
	XMStoreFloat2(&R, X);
	return R;
}

inline XMFLOAT2 XM_CALLCONV operator- (float S, const XMFLOAT2& V)
{
	XMVECTOR v1 = XMLoadFloat(&S);
	XMVECTOR v2 = XMLoadFloat2(&V);
	XMVECTOR X = XMVectorSubtract(v1, v2);
	XMFLOAT2 R;
	XMStoreFloat2(&R, X);
	return R;
}

inline XMFLOAT2 XM_CALLCONV operator* (const XMFLOAT2& V1, const XMFLOAT2& V2)
{
	XMVECTOR v1 = XMLoadFloat2(&V1);
	XMVECTOR v2 = XMLoadFloat2(&V2);
	XMVECTOR X = XMVectorMultiply(v1, v2);
	XMFLOAT2 R;
	XMStoreFloat2(&R, X);
	return R;
}

inline XMFLOAT2 XM_CALLCONV operator* (const XMFLOAT2& V, float S)
{
	XMVECTOR v1 = XMLoadFloat2(&V);
	XMVECTOR X = XMVectorScale(v1, S);
	XMFLOAT2 R;
	XMStoreFloat2(&R, X);
	return R;
}

inline XMFLOAT2 XM_CALLCONV operator* (float S, const XMFLOAT2&V)
{
	XMVECTOR v1 = XMLoadFloat2(&V);
	XMVECTOR X = XMVectorScale(v1, S);
	XMFLOAT2 R;
	XMStoreFloat2(&R, X);
	return R;
}

inline XMFLOAT2 XM_CALLCONV operator/ (const XMFLOAT2& V1, const XMFLOAT2& V2)
{
	XMVECTOR v1 = XMLoadFloat2(&V1);
	XMVECTOR v2 = XMLoadFloat2(&V2);
	XMVECTOR X = XMVectorDivide(v1, v2);
	XMFLOAT2 R;
	XMStoreFloat2(&R, X);
	return R;
}

inline XMFLOAT2 XM_CALLCONV operator/ (const XMFLOAT2& V, float S)
{
	assert(S != 0.0f);
	XMVECTOR v1 = XMLoadFloat2(&V);
	XMVECTOR X = XMVectorScale(v1, 1.f / S);
	XMFLOAT2 R;
	XMStoreFloat2(&R, X);
	return R;
}

inline XMFLOAT2 XM_CALLCONV operator/ (float S, const XMFLOAT2& V)
{
	assert(S != 0.0f);
	XMVECTOR v1 = XMLoadFloat2(&V);
	XMVECTOR X = XMVectorScale(v1, 1.f / S);
	XMFLOAT2 R;
	XMStoreFloat2(&R, X);
	return R;
}

#	pragma endregion

//  ------------------------------------------------------------------------------
/// XMFLOAT3 operators
//--------------------------------------------------------------------------------
#	pragma region XMFLOAT3 operators

//------------------------------------------------------------------------------
// Comparision operators
//------------------------------------------------------------------------------
inline bool XM_CALLCONV operator== (const XMFLOAT3& V1, const XMFLOAT3& V2)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(&V1);
	XMVECTOR v2 = XMLoadFloat3(&V2);
	return XMVector2Equal(v1, v2);
}

inline bool XM_CALLCONV operator!= (const XMFLOAT3& V1, const XMFLOAT3& V2)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(&V1);
	XMVECTOR v2 = XMLoadFloat3(&V2);
	return XMVector2NotEqual(v1, v2);
}

//------------------------------------------------------------------------------
// Assignment operators
//------------------------------------------------------------------------------

inline XMFLOAT3 XM_CALLCONV operator+= (XMFLOAT3& V1, const XMFLOAT3& V2)
{
	XMVECTOR v1 = XMLoadFloat3(&V1);
	XMVECTOR v2 = XMLoadFloat3(&V2);
	XMVECTOR X = XMVectorAdd(v1, v2);
	XMStoreFloat3(&V1, X);
	return V1;
}

inline XMFLOAT3 XM_CALLCONV operator+= (XMFLOAT3& V, float S)
{
	XMVECTOR v1 = XMLoadFloat3(&V);
	XMVECTOR v2 = XMLoadFloat(&S);
	XMVECTOR X = XMVectorAdd(v1, v2);
	XMStoreFloat3(&V, X);
	return V;
}

inline XMFLOAT3 XM_CALLCONV operator+= (float S, const XMFLOAT3& V)
{
	XMVECTOR v1 = XMLoadFloat(&S);
	XMVECTOR v2 = XMLoadFloat3(&V);
	XMVECTOR X = XMVectorAdd(v1, v2);
	XMFLOAT3 R;
	XMStoreFloat3(&R, X);
	return R;
}

inline XMFLOAT3 XM_CALLCONV operator-= (XMFLOAT3& V1, const XMFLOAT3& V2)
{
	XMVECTOR v1 = XMLoadFloat3(&V1);
	XMVECTOR v2 = XMLoadFloat3(&V2);
	XMVECTOR X = XMVectorSubtract(v1, v2);
	XMStoreFloat3(&V1, X);
	return V1;
}

inline XMFLOAT3 XM_CALLCONV operator-= (XMFLOAT3& V, float S)
{
	XMVECTOR v1 = XMLoadFloat3(&V);
	XMVECTOR v2 = XMLoadFloat(&S);
	XMVECTOR X = XMVectorSubtract(v1, v2);
	XMStoreFloat3(&V, X);
	return V;
}

inline XMFLOAT3 XM_CALLCONV operator-= (float S, const XMFLOAT3& V)
{
	XMVECTOR v1 = XMLoadFloat(&S);
	XMVECTOR v2 = XMLoadFloat3(&V);
	XMVECTOR X = XMVectorSubtract(v1, v2);
	XMFLOAT3 R;
	XMStoreFloat3(&R, X);
	return R;
}

inline XMFLOAT3 XM_CALLCONV operator*= (XMFLOAT3& V1, const XMFLOAT3& V2)
{
	XMVECTOR v1 = XMLoadFloat3(&V1);
	XMVECTOR v2 = XMLoadFloat3(&V2);
	XMVECTOR X = XMVectorMultiply(v1, v2);
	XMStoreFloat3(&V1, X);
	return V1;
}

inline XMFLOAT3 XM_CALLCONV operator*= (XMFLOAT3& V, float S)
{
	XMVECTOR v1 = XMLoadFloat3(&V);
	XMVECTOR X = XMVectorScale(v1, S);
	XMStoreFloat3(&V, X);
	return V;
}

inline XMFLOAT3 XM_CALLCONV operator*= (float S, XMFLOAT3& V)
{
	XMVECTOR v1 = XMLoadFloat3(&V);
	XMVECTOR X = XMVectorScale(v1, S);
	XMStoreFloat3(&V, X);
	return V;
}

inline XMFLOAT3 XM_CALLCONV operator/= (XMFLOAT3& V1, const XMFLOAT3& V2)
{
	XMVECTOR v1 = XMLoadFloat3(&V1);
	XMVECTOR v2 = XMLoadFloat3(&V2);
	XMVECTOR X = XMVectorDivide(v1, v2);
	XMStoreFloat3(&V1, X);
	return V1;
}

inline XMFLOAT3 XM_CALLCONV operator/= (XMFLOAT3& V, float S)
{
	assert(S != 0.0f);
	XMVECTOR v1 = XMLoadFloat3(&V);
	XMVECTOR X = XMVectorScale(v1, 1.f / S);
	XMStoreFloat3(&V, X);
	return V;
}

inline XMFLOAT3 XM_CALLCONV operator/= (float S, XMFLOAT3& V)
{
	assert(S != 0.0f);
	XMVECTOR v1 = XMLoadFloat3(&V);
	XMVECTOR X = XMVectorScale(v1, 1.f / S);
	XMStoreFloat3(&V, X);
	return V;
}

//------------------------------------------------------------------------------
// Urnary operators
//------------------------------------------------------------------------------

inline XMFLOAT3 XM_CALLCONV operator+ (const XMFLOAT3& V)
{
	XMVECTOR v1 = XMLoadFloat3(&V);
	XMVECTOR X = +v1;
	XMFLOAT3 R;
	XMStoreFloat3(&R, X);
	return R;
}

inline XMFLOAT3 XM_CALLCONV operator- (const XMFLOAT3& V)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(&V);
	XMVECTOR X = XMVectorNegate(v1);
	XMFLOAT3 R;
	XMStoreFloat3(&R, X);
	return R;
}

//------------------------------------------------------------------------------
// Binary operators
//------------------------------------------------------------------------------

inline XMFLOAT3 XM_CALLCONV operator+ (const XMFLOAT3& V1, const XMFLOAT3& V2)
{
	XMVECTOR v1 = XMLoadFloat3(&V1);
	XMVECTOR v2 = XMLoadFloat3(&V2);
	XMVECTOR X = XMVectorAdd(v1, v2);
	XMFLOAT3 R;
	XMStoreFloat3(&R, X);
	return R;
}

inline XMFLOAT3 XM_CALLCONV operator+ (const XMFLOAT3& V, float S)
{
	XMVECTOR v1 = XMLoadFloat3(&V);
	XMVECTOR v2 = XMLoadFloat(&S);
	XMVECTOR X = XMVectorAdd(v1, v2);
	XMFLOAT3 R;
	XMStoreFloat3(&R, X);
	return R;
}

inline XMFLOAT3 XM_CALLCONV operator+ (float S, const XMFLOAT3& V)
{
	XMVECTOR v1 = XMLoadFloat(&S);
	XMVECTOR v2 = XMLoadFloat3(&V);
	XMVECTOR X = XMVectorAdd(v1, v2);
	XMFLOAT3 R;
	XMStoreFloat3(&R, X);
	return R;
}

inline XMFLOAT3 XM_CALLCONV operator- (const XMFLOAT3& V1, const XMFLOAT3& V2)
{
	XMVECTOR v1 = XMLoadFloat3(&V1);
	XMVECTOR v2 = XMLoadFloat3(&V2);
	XMVECTOR X = XMVectorSubtract(v1, v2);
	XMFLOAT3 R;
	XMStoreFloat3(&R, X);
	return R;
}

inline XMFLOAT3 XM_CALLCONV operator- (const XMFLOAT3& V, float S)
{
	XMVECTOR v1 = XMLoadFloat3(&V);
	XMVECTOR v2 = XMLoadFloat(&S);
	XMVECTOR X = XMVectorSubtract(v1, v2);
	XMFLOAT3 R;
	XMStoreFloat3(&R, X);
	return R;
}

inline XMFLOAT3 XM_CALLCONV operator- (float S, const XMFLOAT3& V)
{
	XMVECTOR v1 = XMLoadFloat(&S);
	XMVECTOR v2 = XMLoadFloat3(&V);
	XMVECTOR X = XMVectorSubtract(v1, v2);
	XMFLOAT3 R;
	XMStoreFloat3(&R, X);
	return R;
}

inline XMFLOAT3 XM_CALLCONV operator* (const XMFLOAT3& V1, const XMFLOAT3& V2)
{
	XMVECTOR v1 = XMLoadFloat3(&V1);
	XMVECTOR v2 = XMLoadFloat3(&V2);
	XMVECTOR X = XMVectorMultiply(v1, v2);
	XMFLOAT3 R;
	XMStoreFloat3(&R, X);
	return R;
}

inline XMFLOAT3 XM_CALLCONV operator* (const XMFLOAT3& V, float S)
{
	XMVECTOR v1 = XMLoadFloat3(&V);
	XMVECTOR X = XMVectorScale(v1, S);
	XMFLOAT3 R;
	XMStoreFloat3(&R, X);
	return R;
}

inline XMFLOAT3 XM_CALLCONV operator* (float S, const XMFLOAT3&V)
{
	XMVECTOR v1 = XMLoadFloat3(&V);
	XMVECTOR X = XMVectorScale(v1, S);
	XMFLOAT3 R;
	XMStoreFloat3(&R, X);
	return R;
}

inline XMFLOAT3 XM_CALLCONV operator/ (const XMFLOAT3& V1, const XMFLOAT3& V2)
{
	XMVECTOR v1 = XMLoadFloat3(&V1);
	XMVECTOR v2 = XMLoadFloat3(&V2);
	XMVECTOR X = XMVectorDivide(v1, v2);
	XMFLOAT3 R;
	XMStoreFloat3(&R, X);
	return R;
}

inline XMFLOAT3 XM_CALLCONV operator/ (const XMFLOAT3& V, float S)
{
	assert(S != 0.0f);
	XMVECTOR v1 = XMLoadFloat3(&V);
	XMVECTOR X = XMVectorScale(v1, 1.f / S);
	XMFLOAT3 R;
	XMStoreFloat3(&R, X);
	return R;
}

inline XMFLOAT3 XM_CALLCONV operator/ (float S, const XMFLOAT3& V)
{
	assert(S != 0.0f);
	XMVECTOR v1 = XMLoadFloat3(&V);
	XMVECTOR X = XMVectorScale(v1, 1.f / S);
	XMFLOAT3 R;
	XMStoreFloat3(&R, X);
	return R;
}

#	pragma endregion

//  ------------------------------------------------------------------------------
/// XMFLOAT4 operators
//--------------------------------------------------------------------------------
#	pragma region XMFLOAT4 operators

//------------------------------------------------------------------------------
// Comparision operators
//------------------------------------------------------------------------------
inline bool XM_CALLCONV operator== (const XMFLOAT4& V1, const XMFLOAT4& V2)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(&V1);
	XMVECTOR v2 = XMLoadFloat4(&V2);
	return XMVector2Equal(v1, v2);
}

inline bool XM_CALLCONV operator!= (const XMFLOAT4& V1, const XMFLOAT4& V2)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(&V1);
	XMVECTOR v2 = XMLoadFloat4(&V2);
	return XMVector2NotEqual(v1, v2);
}

//------------------------------------------------------------------------------
// Assignment operators
//------------------------------------------------------------------------------

inline XMFLOAT4 XM_CALLCONV operator+= (XMFLOAT4& V1, const XMFLOAT4& V2)
{
	XMVECTOR v1 = XMLoadFloat4(&V1);
	XMVECTOR v2 = XMLoadFloat4(&V2);
	XMVECTOR X = XMVectorAdd(v1, v2);
	XMStoreFloat4(&V1, X);
	return V1;
}

inline XMFLOAT4 XM_CALLCONV operator+= (XMFLOAT4& V, float S)
{
	XMVECTOR v1 = XMLoadFloat4(&V);
	XMVECTOR v2 = XMLoadFloat(&S);
	XMVECTOR X = XMVectorAdd(v1, v2);
	XMStoreFloat4(&V, X);
	return V;
}

inline XMFLOAT4 XM_CALLCONV operator+= (float S, const XMFLOAT4& V)
{
	XMVECTOR v1 = XMLoadFloat(&S);
	XMVECTOR v2 = XMLoadFloat4(&V);
	XMVECTOR X = XMVectorAdd(v1, v2);
	XMFLOAT4 R;
	XMStoreFloat4(&R, X);
	return R;
}

inline XMFLOAT4 XM_CALLCONV operator-= (XMFLOAT4& V1, const XMFLOAT4& V2)
{
	XMVECTOR v1 = XMLoadFloat4(&V1);
	XMVECTOR v2 = XMLoadFloat4(&V2);
	XMVECTOR X = XMVectorSubtract(v1, v2);
	XMStoreFloat4(&V1, X);
	return V1;
}

inline XMFLOAT4 XM_CALLCONV operator-= (XMFLOAT4& V, float S)
{
	XMVECTOR v1 = XMLoadFloat4(&V);
	XMVECTOR v2 = XMLoadFloat(&S);
	XMVECTOR X = XMVectorSubtract(v1, v2);
	XMStoreFloat4(&V, X);
	return V;
}

inline XMFLOAT4 XM_CALLCONV operator-= (float S, const XMFLOAT4& V)
{
	XMVECTOR v1 = XMLoadFloat(&S);
	XMVECTOR v2 = XMLoadFloat4(&V);
	XMVECTOR X = XMVectorSubtract(v1, v2);
	XMFLOAT4 R;
	XMStoreFloat4(&R, X);
	return R;
}

inline XMFLOAT4 XM_CALLCONV operator*= (XMFLOAT4& V1, const XMFLOAT4& V2)
{
	XMVECTOR v1 = XMLoadFloat4(&V1);
	XMVECTOR v2 = XMLoadFloat4(&V2);
	XMVECTOR X = XMVectorMultiply(v1, v2);
	XMStoreFloat4(&V1, X);
	return V1;
}

inline XMFLOAT4 XM_CALLCONV operator*= (XMFLOAT4& V, float S)
{
	XMVECTOR v1 = XMLoadFloat4(&V);
	XMVECTOR X = XMVectorScale(v1, S);
	XMStoreFloat4(&V, X);
	return V;
}

inline XMFLOAT4 XM_CALLCONV operator*= (float S, XMFLOAT4& V)
{
	XMVECTOR v1 = XMLoadFloat4(&V);
	XMVECTOR X = XMVectorScale(v1, S);
	XMStoreFloat4(&V, X);
	return V;
}

inline XMFLOAT4 XM_CALLCONV operator/= (XMFLOAT4& V1, const XMFLOAT4& V2)
{
	XMVECTOR v1 = XMLoadFloat4(&V1);
	XMVECTOR v2 = XMLoadFloat4(&V2);
	XMVECTOR X = XMVectorDivide(v1, v2);
	XMStoreFloat4(&V1, X);
	return V1;
}

inline XMFLOAT4 XM_CALLCONV operator/= (XMFLOAT4& V, float S)
{
	assert(S != 0.0f);
	XMVECTOR v1 = XMLoadFloat4(&V);
	XMVECTOR X = XMVectorScale(v1, 1.f / S);
	XMStoreFloat4(&V, X);
	return V;
}

inline XMFLOAT4 XM_CALLCONV operator/= (float S, XMFLOAT4& V)
{
	assert(S != 0.0f);
	XMVECTOR v1 = XMLoadFloat4(&V);
	XMVECTOR X = XMVectorScale(v1, 1.f / S);
	XMStoreFloat4(&V, X);
	return V;
}

//------------------------------------------------------------------------------
// Urnary operators
//------------------------------------------------------------------------------

inline XMFLOAT4 XM_CALLCONV operator+ (const XMFLOAT4& V)
{
	XMVECTOR v1 = XMLoadFloat4(&V);
	XMVECTOR X = +v1;
	XMFLOAT4 R;
	XMStoreFloat4(&R, X);
	return R;
}

inline XMFLOAT4 XM_CALLCONV operator- (const XMFLOAT4& V)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(&V);
	XMVECTOR X = XMVectorNegate(v1);
	XMFLOAT4 R;
	XMStoreFloat4(&R, X);
	return R;
}

//------------------------------------------------------------------------------
// Binary operators
//------------------------------------------------------------------------------

inline XMFLOAT4 XM_CALLCONV operator+ (const XMFLOAT4& V1, const XMFLOAT4& V2)
{
	XMVECTOR v1 = XMLoadFloat4(&V1);
	XMVECTOR v2 = XMLoadFloat4(&V2);
	XMVECTOR X = XMVectorAdd(v1, v2);
	XMFLOAT4 R;
	XMStoreFloat4(&R, X);
	return R;
}

inline XMFLOAT4 XM_CALLCONV operator+ (const XMFLOAT4& V, float S)
{
	XMVECTOR v1 = XMLoadFloat4(&V);
	XMVECTOR v2 = XMLoadFloat(&S);
	XMVECTOR X = XMVectorAdd(v1, v2);
	XMFLOAT4 R;
	XMStoreFloat4(&R, X);
	return R;
}

inline XMFLOAT4 XM_CALLCONV operator+ (float S, const XMFLOAT4& V)
{
	XMVECTOR v1 = XMLoadFloat(&S);
	XMVECTOR v2 = XMLoadFloat4(&V);
	XMVECTOR X = XMVectorAdd(v1, v2);
	XMFLOAT4 R;
	XMStoreFloat4(&R, X);
	return R;
}

inline XMFLOAT4 XM_CALLCONV operator- (const XMFLOAT4& V1, const XMFLOAT4& V2)
{
	XMVECTOR v1 = XMLoadFloat4(&V1);
	XMVECTOR v2 = XMLoadFloat4(&V2);
	XMVECTOR X = XMVectorSubtract(v1, v2);
	XMFLOAT4 R;
	XMStoreFloat4(&R, X);
	return R;
}

inline XMFLOAT4 XM_CALLCONV operator- (const XMFLOAT4& V, float S)
{
	XMVECTOR v1 = XMLoadFloat4(&V);
	XMVECTOR v2 = XMLoadFloat(&S);
	XMVECTOR X = XMVectorSubtract(v1, v2);
	XMFLOAT4 R;
	XMStoreFloat4(&R, X);
	return R;
}

inline XMFLOAT4 XM_CALLCONV operator- (float S, const XMFLOAT4& V)
{
	XMVECTOR v1 = XMLoadFloat(&S);
	XMVECTOR v2 = XMLoadFloat4(&V);
	XMVECTOR X = XMVectorSubtract(v1, v2);
	XMFLOAT4 R;
	XMStoreFloat4(&R, X);
	return R;
}

inline XMFLOAT4 XM_CALLCONV operator* (const XMFLOAT4& V1, const XMFLOAT4& V2)
{
	XMVECTOR v1 = XMLoadFloat4(&V1);
	XMVECTOR v2 = XMLoadFloat4(&V2);
	XMVECTOR X = XMVectorMultiply(v1, v2);
	XMFLOAT4 R;
	XMStoreFloat4(&R, X);
	return R;
}

inline XMFLOAT4 XM_CALLCONV operator* (const XMFLOAT4& V, float S)
{
	XMVECTOR v1 = XMLoadFloat4(&V);
	XMVECTOR X = XMVectorScale(v1, S);
	XMFLOAT4 R;
	XMStoreFloat4(&R, X);
	return R;
}

inline XMFLOAT4 XM_CALLCONV operator* (float S, const XMFLOAT4&V)
{
	XMVECTOR v1 = XMLoadFloat4(&V);
	XMVECTOR X = XMVectorScale(v1, S);
	XMFLOAT4 R;
	XMStoreFloat4(&R, X);
	return R;
}

inline XMFLOAT4 XM_CALLCONV operator/ (const XMFLOAT4& V1, const XMFLOAT4& V2)
{
	XMVECTOR v1 = XMLoadFloat4(&V1);
	XMVECTOR v2 = XMLoadFloat4(&V2);
	XMVECTOR X = XMVectorDivide(v1, v2);
	XMFLOAT4 R;
	XMStoreFloat4(&R, X);
	return R;
}

inline XMFLOAT4 XM_CALLCONV operator/ (const XMFLOAT4& V, float S)
{
	assert(S != 0.0f);
	XMVECTOR v1 = XMLoadFloat4(&V);
	XMVECTOR X = XMVectorScale(v1, 1.f / S);
	XMFLOAT4 R;
	XMStoreFloat4(&R, X);
	return R;
}

inline XMFLOAT4 XM_CALLCONV operator/ (float S, const XMFLOAT4& V)
{
	assert(S != 0.0f);
	XMVECTOR v1 = XMLoadFloat4(&V);
	XMVECTOR X = XMVectorScale(v1, 1.f / S);
	XMFLOAT4 R;
	XMStoreFloat4(&R, X);
	return R;
}

#	pragma endregion

#ifdef __cplusplus
EXTERN_CC_END
#endif
