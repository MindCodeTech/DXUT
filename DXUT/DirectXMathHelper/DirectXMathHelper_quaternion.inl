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

#	pragma region MHQUATERNION

//------------------------------------------------------------------------------
/// MHQUATERNION operations
//------------------------------------------------------------------------------
#pragma region operations

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

inline float XM_CALLCONV MHQUATERNION::QDot(FMHQUATERNION& Q) const
{
    using namespace DirectX;
    XMVECTOR q1 = XMLoadFloat4( this );
    XMVECTOR q2 = XMLoadFloat4( &Q );
    return XMVectorGetX( XMQuaternionDot( q1, q2 ) );
}

//------------------------------------------------------------------------------
// Static functions
//------------------------------------------------------------------------------

inline float XM_CALLCONV MHQUATERNION::Length(FMHQUATERNION& Q)
{
	using namespace DirectX;
	XMVECTOR q = XMLoadFloat4(&Q);
	return XMVectorGetX(XMQuaternionLength(q));
}

inline float XM_CALLCONV MHQUATERNION::LengthSquared(FMHQUATERNION& Q)
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

inline bool XM_CALLCONV MHQUATERNION::IsIdentity(FMHQUATERNION& Q)
{
	using namespace DirectX;
	return XMQuaternionIsIdentity(Q);
}

inline MHQUATERNION XM_CALLCONV MHQUATERNION::Normalize(FMHQUATERNION& Q)
{
	using namespace DirectX;
	XMVECTOR q = XMLoadFloat4(&Q);
	MHQUATERNION R;
	XMStoreFloat4(&R, XMQuaternionNormalize(q));
	return R;
}

inline void XM_CALLCONV MHQUATERNION::Normalize(FMHQUATERNION& Q, MHQUATERNION& result)
{
	using namespace DirectX;
	XMVECTOR q = XMLoadFloat4(&Q);
	XMStoreFloat4(&result, XMQuaternionNormalize(q));
}

inline MHQUATERNION XM_CALLCONV MHQUATERNION::Conjugate(FMHQUATERNION& Q)
{
	using namespace DirectX;
	XMVECTOR q = XMLoadFloat4(&Q);

	MHQUATERNION R;
	XMStoreFloat4(&R, XMQuaternionConjugate(q));
	return R;
}

inline void XM_CALLCONV MHQUATERNION::Conjugate(FMHQUATERNION& Q, MHQUATERNION& result)
{
	using namespace DirectX;
	XMVECTOR q = XMLoadFloat4(&Q);
	XMStoreFloat4(&result, XMQuaternionConjugate(q));
}

inline MHQUATERNION XM_CALLCONV MHQUATERNION::Inverse(FMHQUATERNION& Q)
{
	using namespace DirectX;
	XMVECTOR q = XMLoadFloat4(&Q);

	MHQUATERNION R;
	XMStoreFloat4(&R, XMQuaternionInverse(q));
	return R;
}

inline void XM_CALLCONV MHQUATERNION::Inverse(FMHQUATERNION& Q, MHQUATERNION& result)
{
	using namespace DirectX;
	XMVECTOR q = XMLoadFloat4(&Q);
	XMStoreFloat4(&result, XMQuaternionInverse(q));
}

inline float XM_CALLCONV MHQUATERNION::Dot(FMHQUATERNION& Q1, FMHQUATERNION& Q2)
{
	using namespace DirectX;
	XMVECTOR q1 = XMLoadFloat4(&Q1);
	XMVECTOR q2 = XMLoadFloat4(&Q2);
	return XMVectorGetX(XMQuaternionDot(q1, q2));
}

inline MHQUATERNION XM_CALLCONV MHQUATERNION::RotationAxis(FMHVECTOR3& axis, float angle)
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

inline MHQUATERNION XM_CALLCONV MHQUATERNION::RotationMatrix(FMHMATRIX& M)
{
    using namespace DirectX;
    XMMATRIX M0 = XMLoadFloat4x4( &M );

    MHQUATERNION R;
    XMStoreFloat4( &R, XMQuaternionRotationMatrix( M0 ) );
    return R;
}

inline void XM_CALLCONV MHQUATERNION::Barycentric(FMHQUATERNION& Q1, FMHQUATERNION& Q2, FMHQUATERNION& Q3, float f, float g, MHQUATERNION& result)
{
	using namespace DirectX;
	XMVECTOR q1 = XMLoadFloat4(&Q1);
	XMVECTOR q2 = XMLoadFloat4(&Q2);
	XMVECTOR q3 = XMLoadFloat4(&Q3);
	XMVECTOR X = XMQuaternionBaryCentric(q1, q2, q3, f, g);
	XMStoreFloat4(&result, X);
}

inline MHQUATERNION XM_CALLCONV MHQUATERNION::Barycentric(FMHQUATERNION& Q1, FMHQUATERNION& Q2, FMHQUATERNION& Q3, float f, float g)
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

inline void XM_CALLCONV MHQUATERNION::Barycentric(FMHQUATERNION& Q1, FMHQUATERNION& Q2, FMHQUATERNION& Q3, FXMVECTOR& f, FXMVECTOR& g, MHQUATERNION& result)
{
	using namespace DirectX;
	XMVECTOR q1 = XMLoadFloat4(&Q1);
	XMVECTOR q2 = XMLoadFloat4(&Q2);
	XMVECTOR q3 = XMLoadFloat4(&Q3);
	XMVECTOR X = XMQuaternionBaryCentricV(q1, q2, q3, f, g);
	XMStoreFloat4(&result, X);
}

inline MHQUATERNION XM_CALLCONV MHQUATERNION::Barycentric(FMHQUATERNION& Q1, FMHQUATERNION& Q2, FMHQUATERNION& Q3, FXMVECTOR& f, FXMVECTOR& g)
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

inline void XM_CALLCONV MHQUATERNION::Lerp(FMHQUATERNION& q1, FMHQUATERNION& q2, float t, MHQUATERNION& result)
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

inline MHQUATERNION XM_CALLCONV MHQUATERNION::Lerp(FMHQUATERNION& q1, FMHQUATERNION& q2, float t)
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

inline void XM_CALLCONV MHQUATERNION::Slerp(FMHQUATERNION& q1, FMHQUATERNION& q2, float t, MHQUATERNION& result)
{
    using namespace DirectX;
    XMVECTOR Q0 = XMLoadFloat4( &q1 );
    XMVECTOR Q1 = XMLoadFloat4( &q2 );
    XMStoreFloat4( &result, XMQuaternionSlerp( Q0, Q1, t ) );
}

inline MHQUATERNION XM_CALLCONV MHQUATERNION::Slerp(FMHQUATERNION& q1, FMHQUATERNION& q2, float t)
{
    using namespace DirectX;
    XMVECTOR Q0 = XMLoadFloat4( &q1 );
    XMVECTOR Q1 = XMLoadFloat4( &q2 );

    MHQUATERNION result;
    XMStoreFloat4( &result, XMQuaternionSlerp( Q0, Q1, t ) );
    return result;
}

inline void XM_CALLCONV MHQUATERNION::Concatenate(FMHQUATERNION& q1, FMHQUATERNION& q2, MHQUATERNION& result)
{
    using namespace DirectX;
    XMVECTOR Q0 = XMLoadFloat4( &q1 );
    XMVECTOR Q1 = XMLoadFloat4( &q2 );
    XMStoreFloat4( &result, XMQuaternionMultiply( Q1, Q0 ) );
}

inline MHQUATERNION XM_CALLCONV MHQUATERNION::Concatenate(FMHQUATERNION& q1, FMHQUATERNION& q2)
{
    using namespace DirectX;
    XMVECTOR Q0 = XMLoadFloat4( &q1 );
    XMVECTOR Q1 = XMLoadFloat4( &q2 );

    MHQUATERNION result;
    XMStoreFloat4( &result, XMQuaternionMultiply( Q1, Q0 ) );
    return result;
}

#pragma endregion

//------------------------------------------------------------------------------
/// MHQUATERNION operators
//------------------------------------------------------------------------------
#	pragma region operators

//------------------------------------------------------------------------------
/// Comparision operators
//------------------------------------------------------------------------------
inline bool XM_CALLCONV MHQUATERNION::operator == (FMHQUATERNION& q) const
{
	using namespace DirectX;
	XMVECTOR q1 = XMLoadFloat4(this);
	XMVECTOR q2 = XMLoadFloat4(&q);
	return XMQuaternionEqual(q1, q2);
}

inline bool XM_CALLCONV MHQUATERNION::operator != (FMHQUATERNION& q) const
{
	using namespace DirectX;
	XMVECTOR q1 = XMLoadFloat4(this);
	XMVECTOR q2 = XMLoadFloat4(&q);
	return XMQuaternionNotEqual(q1, q2);
}

//------------------------------------------------------------------------------
// Assignment operators
//------------------------------------------------------------------------------

inline MHQUATERNION& XM_CALLCONV MHQUATERNION::operator+= (FMHQUATERNION& q)
{
	using namespace DirectX;
	XMVECTOR q1 = XMLoadFloat4(this);
	XMVECTOR q2 = XMLoadFloat4(&q);
	XMStoreFloat4(this, XMVectorAdd(q1, q2));
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

inline MHQUATERNION& XM_CALLCONV MHQUATERNION::operator-= (FMHQUATERNION& q)
{
	using namespace DirectX;
	XMVECTOR q1 = XMLoadFloat4(this);
	XMVECTOR q2 = XMLoadFloat4(&q);
	XMStoreFloat4(this, XMVectorSubtract(q1, q2));
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

inline MHQUATERNION& XM_CALLCONV MHQUATERNION::operator*= (FMHQUATERNION& q)
{
	using namespace DirectX;
	XMVECTOR q1 = XMLoadFloat4(this);
	XMVECTOR q2 = XMLoadFloat4(&q);
	XMStoreFloat4(this, XMQuaternionMultiply(q1, q2));
	return *this;
}

inline MHQUATERNION& XM_CALLCONV MHQUATERNION::operator*= (float S)
{
	using namespace DirectX;
	XMVECTOR q = XMLoadFloat4(this);
	XMStoreFloat4(this, XMVectorScale(q, S));
	return *this;
}

inline MHQUATERNION& XM_CALLCONV MHQUATERNION::operator/= (FMHQUATERNION& q)
{
	using namespace DirectX;
	XMVECTOR q1 = XMLoadFloat4(this);
	XMVECTOR q2 = XMLoadFloat4(&q);
	q2 = XMQuaternionInverse(q2);
	XMStoreFloat4(this, XMQuaternionMultiply(q1, q2));
	return *this;
}

inline MHQUATERNION& XM_CALLCONV MHQUATERNION::operator/= (float S)
{
	using namespace DirectX;
	assert(S != 0.f);

	XMVECTOR q1 = XMLoadFloat4(this);
	XMVECTOR X = XMVectorScale(q1, 1.f / S);
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
	XMVECTOR q = XMLoadFloat4(this);

	MHQUATERNION R;
	XMStoreFloat4(&R, XMVectorNegate(q));
	return R;
}

//------------------------------------------------------------------------------
// Binary operators
//------------------------------------------------------------------------------

inline MHQUATERNION XM_CALLCONV operator+ (FMHQUATERNION& Q1, FMHQUATERNION& Q2)
{
	using namespace DirectX;
	XMVECTOR q1 = XMLoadFloat4(&Q1);
	XMVECTOR q2 = XMLoadFloat4(&Q2);

	MHQUATERNION R;
	XMStoreFloat4(&R, XMVectorAdd(q1, q2));
	return R;
}

inline MHQUATERNION XM_CALLCONV operator+ (FMHQUATERNION& Q, float S)
{
	using namespace DirectX;
	XMVECTOR q1 = XMLoadFloat4(&Q);
	XMVECTOR q2 = XMLoadFloat(&S);

	MHQUATERNION R;
	XMStoreFloat4(&R, XMVectorAdd(q1, q2));
	return R;
}

inline MHQUATERNION XM_CALLCONV operator+ (float S, FMHQUATERNION& Q)
{
	using namespace DirectX;
	XMVECTOR q1 = XMLoadFloat(&S);
	XMVECTOR q2 = XMLoadFloat4(&Q);

	MHQUATERNION R;
	XMStoreFloat4(&R, XMVectorAdd(q1, q2));
	return R;
}

inline MHQUATERNION XM_CALLCONV operator- (FMHQUATERNION& Q1, FMHQUATERNION& Q2)
{
	using namespace DirectX;
	XMVECTOR q1 = XMLoadFloat4(&Q1);
	XMVECTOR q2 = XMLoadFloat4(&Q2);

	MHQUATERNION R;
	XMStoreFloat4(&R, XMVectorSubtract(q1, q2));
	return R;
}

inline MHQUATERNION XM_CALLCONV operator- (FMHQUATERNION& Q, float S)
{
	using namespace DirectX;
	XMVECTOR q1 = XMLoadFloat4(&Q);
	XMVECTOR q2 = XMLoadFloat(&S);

	MHQUATERNION R;
	XMStoreFloat4(&R, XMVectorSubtract(q1, q2));
	return R;
}

inline MHQUATERNION XM_CALLCONV operator- (float S, FMHQUATERNION& Q)
{
	using namespace DirectX;
	XMVECTOR q1 = XMLoadFloat(&S);
	XMVECTOR q2 = XMLoadFloat4(&Q);

	MHQUATERNION R;
	XMStoreFloat4(&R, XMVectorSubtract(q1, q2));
	return R;
}

inline MHQUATERNION XM_CALLCONV operator* (FMHQUATERNION& Q1, FMHQUATERNION& Q2)
{
	using namespace DirectX;
	XMVECTOR q1 = XMLoadFloat4(&Q1);
	XMVECTOR q2 = XMLoadFloat4(&Q2);

	MHQUATERNION R;
	XMStoreFloat4(&R, XMQuaternionMultiply(q1, q2));
	return R;
}

inline MHQUATERNION XM_CALLCONV operator* (FMHQUATERNION& Q, float S)
{
	using namespace DirectX;
	XMVECTOR q = XMLoadFloat4(&Q);

	MHQUATERNION R;
	XMStoreFloat4(&R, XMVectorScale(q, S));
	return R;
}

inline MHQUATERNION XM_CALLCONV operator* (float S, FMHQUATERNION& Q)
{
	using namespace DirectX;
	XMVECTOR q1 = XMLoadFloat4(&Q);

	MHQUATERNION R;
	XMStoreFloat4(&R, XMVectorScale(q1, S));
	return R;
}

inline MHQUATERNION XM_CALLCONV operator/ (FMHQUATERNION& Q1, FMHQUATERNION& Q2)
{
	using namespace DirectX;
	XMVECTOR q1 = XMLoadFloat4(&Q1);
	XMVECTOR q2 = XMLoadFloat4(&Q2);
	q2 = XMQuaternionInverse(q2);

	MHQUATERNION R;
	XMStoreFloat4(&R, XMQuaternionMultiply(q1, q2));
	return R;
}

inline MHQUATERNION XM_CALLCONV operator/ (FMHQUATERNION& Q, float S)
{
	using namespace DirectX;
	assert(S != 0.f);

	XMVECTOR q1 = XMLoadFloat4(&Q);
	XMVECTOR X = XMVectorScale(q1, 1.f / S);

	MHQUATERNION R;
	XMStoreFloat4(&R, X);
	return R;
}

inline MHQUATERNION XM_CALLCONV operator/ (float S, FMHQUATERNION& Q)
{
	using namespace DirectX;
	assert(S != 0.f);

	XMVECTOR q1 = XMLoadFloat4(&Q);
	XMVECTOR X = XMVectorScale(q1, 1.f / S);

	MHQUATERNION R;
	XMStoreFloat4(&R, X);
	return R;
}

#pragma endregion

#	pragma endregion

#ifdef __cplusplus
EXTERN_CC_END
#endif
