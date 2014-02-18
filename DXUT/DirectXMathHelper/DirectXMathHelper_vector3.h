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
// 3D vector
#	pragma region MHVECTOR3

#if (defined(_M_IX86) || defined(_M_X64) || defined(_M_ARM)) && defined(_XM_NO_INTRINSICS_)
struct MHVECTOR3 : public XMFLOAT3
#else
__declspec(align(16)) struct MHVECTOR3 : public XMFLOAT3
#endif
{
/*
struct MHVECTOR3 : public XMFLOAT3
{*/
    MHVECTOR3() : XMFLOAT3(0.0f, 0.0f, 0.0f) {}
    explicit MHVECTOR3(float x) : XMFLOAT3( x, x, x ) {}
    MHVECTOR3(float _x, float _y, float _z) : XMFLOAT3(_x, _y, _z) {}
    explicit MHVECTOR3(_In_reads_(3) const float *pArray) : XMFLOAT3(pArray) {}
	MHVECTOR3(FXMVECTOR& V) { XMStoreFloat3(this, V); }

    operator XMVECTOR() const { return XMLoadFloat3( this ); }

    // Comparision operators
	bool XM_CALLCONV operator == (FMHVECTOR3& V) const;
	bool XM_CALLCONV operator != (FMHVECTOR3& V) const;

    // Assignment operators
	MHVECTOR3& XM_CALLCONV operator= (FMHVECTOR3& V) { x = V.x; y = V.y; z = V.z; return *this; }
	MHVECTOR3& XM_CALLCONV operator+= (FMHVECTOR3& V);
	MHVECTOR3& XM_CALLCONV operator+= (float S);
	MHVECTOR3& XM_CALLCONV operator-= (FMHVECTOR3& V);
	MHVECTOR3& XM_CALLCONV operator-= (float S);
	MHVECTOR3& XM_CALLCONV operator*= (FMHVECTOR3& V);
	MHVECTOR3& XM_CALLCONV operator*= (float S);
	MHVECTOR3& XM_CALLCONV operator/= (FMHVECTOR3& V);
	MHVECTOR3& XM_CALLCONV operator/= (float S);

    // Urnary operators
	MHVECTOR3 XM_CALLCONV operator+ () const { return *this; }
	MHVECTOR3 XM_CALLCONV operator- () const;

    // Vector operations
	bool XM_CALLCONV VInBounds(FMHVECTOR3& Bounds) const;

	float XM_CALLCONV VLength() const;
	float XM_CALLCONV VLengthSquared() const;

	float XM_CALLCONV VDot(FMHVECTOR3& V) const;
	void XM_CALLCONV VCross(FMHVECTOR3& V, MHVECTOR3& result) const;
	MHVECTOR3 XM_CALLCONV VCross(FMHVECTOR3& V) const;

	void XM_CALLCONV VNormalize();
	void XM_CALLCONV VNormalize(MHVECTOR3& result) const;

	void XM_CALLCONV VClamp(FMHVECTOR3& vmin, FMHVECTOR3& vmax);
	void XM_CALLCONV VClamp(FMHVECTOR3& vmin, FMHVECTOR3& vmax, MHVECTOR3& result) const;

    // Static functions
	static bool XM_CALLCONV InBounds(FMHVECTOR3& V, FMHVECTOR3& Bounds);

	static float XM_CALLCONV Length(FMHVECTOR3& V);
	static float XM_CALLCONV LengthSquared(FMHVECTOR3& V);

	static float XM_CALLCONV Dot(FMHVECTOR3& V1, FMHVECTOR3& V2);
	static void XM_CALLCONV Cross(FMHVECTOR3& V1, FMHVECTOR3& V2, MHVECTOR3& result);
	static MHVECTOR3 XM_CALLCONV Cross(FMHVECTOR3& V1, FMHVECTOR3& V2);

	static void XM_CALLCONV Normalize(FMHVECTOR3& V, MHVECTOR3& result);
	static MHVECTOR3 XM_CALLCONV Normalize(FMHVECTOR3& V);

	static void XM_CALLCONV Clamp(FMHVECTOR3& V, FMHVECTOR3& vmin, FMHVECTOR3& vmax, MHVECTOR3& result);
	static MHVECTOR3 XM_CALLCONV Clamp(FMHVECTOR3& V, FMHVECTOR3& vmin, FMHVECTOR3& vmax);

	static void XM_CALLCONV ClampLength(FMHVECTOR3& V, float LengthMin, float LengthMax, MHVECTOR3& result);
	static MHVECTOR3 XM_CALLCONV ClampLength(FMHVECTOR3& V, float LengthMin, float LengthMax);

	static float XM_CALLCONV Distance(FMHVECTOR3& v1, FMHVECTOR3& v2);
	static float XM_CALLCONV DistanceSquared(FMHVECTOR3& v1, FMHVECTOR3& v2);

	static void XM_CALLCONV Min(FMHVECTOR3& v1, FMHVECTOR3& v2, MHVECTOR3& result);
	static MHVECTOR3 XM_CALLCONV Min(FMHVECTOR3& v1, FMHVECTOR3& v2);

	static void XM_CALLCONV Max(FMHVECTOR3& v1, FMHVECTOR3& v2, MHVECTOR3& result);
	static MHVECTOR3 XM_CALLCONV Max(FMHVECTOR3& v1, FMHVECTOR3& v2);

	static void XM_CALLCONV Lerp(FMHVECTOR3& v1, FMHVECTOR3& v2, float t, MHVECTOR3& result);
	static MHVECTOR3 XM_CALLCONV Lerp(FMHVECTOR3& v1, FMHVECTOR3& v2, float t);

	static void XM_CALLCONV SmoothStep(FMHVECTOR3& v1, FMHVECTOR3& v2, float t, MHVECTOR3& result);
	static MHVECTOR3 XM_CALLCONV SmoothStep(FMHVECTOR3& v1, FMHVECTOR3& v2, float t);

	static void XM_CALLCONV Barycentric(FMHVECTOR3& v1, FMHVECTOR3& v2, FMHVECTOR3& v3, float f, float g, MHVECTOR3& result);
	static MHVECTOR3 XM_CALLCONV Barycentric(FMHVECTOR3& v1, FMHVECTOR3& v2, FMHVECTOR3& v3, float f, float g);

	static void XM_CALLCONV CatmullRom(FMHVECTOR3& v1, FMHVECTOR3& v2, FMHVECTOR3& v3, FMHVECTOR3& v4, float t, MHVECTOR3& result);
	static MHVECTOR3 XM_CALLCONV CatmullRom(FMHVECTOR3& v1, FMHVECTOR3& v2, FMHVECTOR3& v3, FMHVECTOR3& v4, float t);

	static void XM_CALLCONV Hermite(FMHVECTOR3& v1, FMHVECTOR3& t1, FMHVECTOR3& v2, FMHVECTOR3& t2, float t, MHVECTOR3& result);
	static MHVECTOR3 XM_CALLCONV Hermite(FMHVECTOR3& v1, FMHVECTOR3& t1, FMHVECTOR3& v2, FMHVECTOR3& t2, float t);

	static void XM_CALLCONV Reflect(FMHVECTOR3& ivec, FMHVECTOR3& nvec, MHVECTOR3& result);
	static MHVECTOR3 XM_CALLCONV Reflect(FMHVECTOR3& ivec, FMHVECTOR3& nvec);

	static void XM_CALLCONV Refract(FMHVECTOR3& ivec, FMHVECTOR3& nvec, float refractionIndex, MHVECTOR3& result);
	static MHVECTOR3 XM_CALLCONV Refract(FMHVECTOR3& ivec, FMHVECTOR3& nvec, float refractionIndex);

	static void XM_CALLCONV Transform(FMHVECTOR3& v, FMHQUATERNION& quat, MHVECTOR3& result);
	static MHVECTOR3 XM_CALLCONV Transform(FMHVECTOR3& v, FMHQUATERNION& quat);

	static void XM_CALLCONV Transform(FMHVECTOR3& v, FMHMATRIX& m, MHVECTOR3& result);
	static MHVECTOR3 XM_CALLCONV Transform(FMHVECTOR3& v, FMHMATRIX& m);
	static void XM_CALLCONV Transform(_In_reads_(count) FMHVECTOR3* varray, size_t count, FMHMATRIX& m, _Out_writes_(count) MHVECTOR3* resultArray);

	static void XM_CALLCONV Transform(FMHVECTOR3& v, FMHMATRIX& m, MHVECTOR4& result);
	static void XM_CALLCONV Transform(_In_reads_(count) FMHVECTOR3* varray, size_t count, FMHMATRIX& m, _Out_writes_(count) MHVECTOR4* resultArray);

	static void XM_CALLCONV TransformNormal(FMHVECTOR3& v, FMHMATRIX& m, MHVECTOR3& result);
	static MHVECTOR3 XM_CALLCONV TransformNormal(FMHVECTOR3& v, FMHMATRIX& m);
	static void XM_CALLCONV TransformNormal(_In_reads_(count) FMHVECTOR3* varray, size_t count, FMHMATRIX& m, _Out_writes_(count) MHVECTOR3* resultArray);
};

// Binary operators
MHVECTOR3 XM_CALLCONV operator+ (FMHVECTOR3& V1, FMHVECTOR3& V2);
MHVECTOR3 XM_CALLCONV operator+ (FMHVECTOR3& V, float S);
MHVECTOR3 XM_CALLCONV operator+ (float S, FMHVECTOR3& V);
MHVECTOR3 XM_CALLCONV operator- (FMHVECTOR3& V1, FMHVECTOR3& V2);
MHVECTOR3 XM_CALLCONV operator- (FMHVECTOR3& V, float S);
MHVECTOR3 XM_CALLCONV operator- (float S, FMHVECTOR3& V);
MHVECTOR3 XM_CALLCONV operator* (FMHVECTOR3& V1, FMHVECTOR3& V2);
MHVECTOR3 XM_CALLCONV operator* (FMHVECTOR3& V, float S);
MHVECTOR3 XM_CALLCONV operator* (float S, FMHVECTOR3& V);
MHVECTOR3 XM_CALLCONV operator/ (FMHVECTOR3& V1, FMHVECTOR3& V2);
MHVECTOR3 XM_CALLCONV operator/ (FMHVECTOR3& V, float S);
MHVECTOR3 XM_CALLCONV operator/ (float S, FMHVECTOR3& V);

#	pragma endregion

namespace_DirectX_end; // namespace DirectX

#ifdef __cplusplus
EXTERN_CC_END
#endif
