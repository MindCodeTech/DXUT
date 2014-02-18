//--------------------------------------------------------------------------------------
// File: DirectXMathHelper.h
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

namespace_DirectX

//------------------------------------------------------------------------------
// Quaternion
#	pragma region MHQUATERNION

#if (defined(_M_IX86) || defined(_M_X64) || defined(_M_ARM)) && defined(_XM_NO_INTRINSICS_)
struct MHQUATERNION : public XMFLOAT4
#else
__declspec(align(16)) struct MHQUATERNION : public XMFLOAT4
#endif
{
/*
struct MHQUATERNION : public XMFLOAT4
{*/
    MHQUATERNION() : XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f) {}
    MHQUATERNION( float _x, float _y, float _z, float _w ) : XMFLOAT4(_x, _y, _z, _w) {}
    MHQUATERNION( FMHVECTOR3& v, float scalar ) : XMFLOAT4( v.x, v.y, v.z, scalar ) {}
    explicit MHQUATERNION( FMHVECTOR4& v ) : XMFLOAT4( v.x, v.y, v.z, v.w ) {}
    explicit MHQUATERNION(_In_reads_(4) const float *pArray) : XMFLOAT4(pArray) {}
	MHQUATERNION(FXMVECTOR& V) { XMStoreFloat4(this, V); }

    operator XMVECTOR() const { return XMLoadFloat4( this ); }

    // Comparision operators
	bool XM_CALLCONV operator == (FMHQUATERNION& q) const;
	bool XM_CALLCONV operator != (FMHQUATERNION& q) const;

    // Assignment operators
	MHQUATERNION& XM_CALLCONV operator= (FMHQUATERNION& q) { x = q.x; y = q.y; z = q.z; w = q.w; return *this; }
	MHQUATERNION& XM_CALLCONV operator+= (FMHQUATERNION& q);
	MHQUATERNION& XM_CALLCONV operator+= (float S);
	MHQUATERNION& XM_CALLCONV operator-= (FMHQUATERNION& q);
	MHQUATERNION& XM_CALLCONV operator-= (float S);
	MHQUATERNION& XM_CALLCONV operator*= (FMHQUATERNION& q);
	MHQUATERNION& XM_CALLCONV operator*= (float S);
	MHQUATERNION& XM_CALLCONV operator/= (FMHQUATERNION& q);
	MHQUATERNION& XM_CALLCONV operator/= (float S);

    // Urnary operators
	MHQUATERNION XM_CALLCONV operator+ () const { return *this; }
	MHQUATERNION XM_CALLCONV operator- () const;

    // MHQUATERNION operations
	float XM_CALLCONV QLength() const;
	float XM_CALLCONV QLengthSquared() const;

	void XM_CALLCONV QNormalize();
	void XM_CALLCONV QNormalize(MHQUATERNION& result) const;

	void XM_CALLCONV QConjugate();
	void XM_CALLCONV QConjugate(MHQUATERNION& result) const;

	void XM_CALLCONV QInverse(MHQUATERNION& result) const;

	float XM_CALLCONV QDot(FMHQUATERNION& Q) const;

    // Static functions
	static float XM_CALLCONV Length(FMHQUATERNION& Q);
	static float XM_CALLCONV LengthSquared(FMHQUATERNION& Q);

	static MHQUATERNION XM_CALLCONV Identity();
	static bool XM_CALLCONV IsIdentity(FMHQUATERNION& Q);

	static MHQUATERNION XM_CALLCONV Normalize(FMHQUATERNION& Q);
	static void XM_CALLCONV Normalize(FMHQUATERNION& Q, MHQUATERNION& result);

	static MHQUATERNION XM_CALLCONV Conjugate(FMHQUATERNION& Q);
	static void XM_CALLCONV Conjugate(FMHQUATERNION& Q, MHQUATERNION& result);

	static MHQUATERNION XM_CALLCONV Inverse(FMHQUATERNION& Q);
	static void XM_CALLCONV Inverse(FMHQUATERNION& Q, MHQUATERNION& result);

	static float XM_CALLCONV Dot(FMHQUATERNION& Q1, FMHQUATERNION& Q2);

	static MHQUATERNION XM_CALLCONV RotationAxis(FMHVECTOR3& axis, float angle);
	static MHQUATERNION XM_CALLCONV RotationRollPitchYaw(float yaw, float pitch, float roll);
	static MHQUATERNION XM_CALLCONV RotationMatrix(FMHMATRIX& M);

	static void XM_CALLCONV Barycentric(FMHQUATERNION& Q1, FMHQUATERNION& Q2, FMHQUATERNION& Q3, float f, float g, MHQUATERNION& result);
	static MHQUATERNION XM_CALLCONV Barycentric(FMHQUATERNION& Q1, FMHQUATERNION& Q2, FMHQUATERNION& Q3, float f, float g);

	static void XM_CALLCONV Barycentric(FMHQUATERNION& Q1, FMHQUATERNION& Q2, FMHQUATERNION& Q3, FXMVECTOR& f, FXMVECTOR& g, MHQUATERNION& result);
	static MHQUATERNION XM_CALLCONV Barycentric(FMHQUATERNION& Q1, FMHQUATERNION& Q2, FMHQUATERNION& Q3, FXMVECTOR& f, FXMVECTOR& g);

	static void XM_CALLCONV Lerp(FMHQUATERNION& q1, FMHQUATERNION& q2, float t, MHQUATERNION& result);
	static MHQUATERNION XM_CALLCONV Lerp(FMHQUATERNION& q1, FMHQUATERNION& q2, float t);

	static void XM_CALLCONV Slerp(FMHQUATERNION& q1, FMHQUATERNION& q2, float t, MHQUATERNION& result);
	static MHQUATERNION XM_CALLCONV Slerp(FMHQUATERNION& q1, FMHQUATERNION& q2, float t);

	static void XM_CALLCONV Concatenate(FMHQUATERNION& q1, FMHQUATERNION& q2, MHQUATERNION& result);
	static MHQUATERNION XM_CALLCONV Concatenate(FMHQUATERNION& q1, FMHQUATERNION& q2);
};

// Binary operators
MHQUATERNION XM_CALLCONV operator+ (FMHQUATERNION& Q1, FMHQUATERNION& Q2);
MHQUATERNION XM_CALLCONV operator+ (FMHQUATERNION& Q, float S);
MHQUATERNION XM_CALLCONV operator+ (float S, FMHQUATERNION& Q);
MHQUATERNION XM_CALLCONV operator- (FMHQUATERNION& Q1, FMHQUATERNION& Q2);
MHQUATERNION XM_CALLCONV operator- (FMHQUATERNION& Q, float S);
MHQUATERNION XM_CALLCONV operator- (float S, FMHQUATERNION& Q);
MHQUATERNION XM_CALLCONV operator* (FMHQUATERNION& Q1, FMHQUATERNION& Q2);
MHQUATERNION XM_CALLCONV operator* (FMHQUATERNION& Q, float S);
MHQUATERNION XM_CALLCONV operator* (float S, FMHQUATERNION& Q);
MHQUATERNION XM_CALLCONV operator/ (FMHQUATERNION& Q1, FMHQUATERNION& Q2);
MHQUATERNION XM_CALLCONV operator/ (FMHQUATERNION& Q, float S);
MHQUATERNION XM_CALLCONV operator/ (float S, FMHQUATERNION& Q);

#	pragma endregion

namespace_DirectX_end; // namespace DirectX

#ifdef __cplusplus
EXTERN_CC_END
#endif
