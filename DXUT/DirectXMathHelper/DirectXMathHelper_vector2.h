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
// 2D vector
#	pragma region MHVECTOR2

#if (defined(_M_IX86) || defined(_M_X64) || defined(_M_ARM)) && defined(_XM_NO_INTRINSICS_)
struct MHVECTOR2 : public XMFLOAT2
#else
__declspec(align(16)) struct MHVECTOR2 : public XMFLOAT2
#endif
{
/*
struct MHVECTOR2 : public XMFLOAT2
{*/
    MHVECTOR2() : XMFLOAT2(0.0f, 0.0f) {}
    explicit MHVECTOR2(float x) : XMFLOAT2( x, x ) {}
    MHVECTOR2(float _x, float _y) : XMFLOAT2(_x, _y) {}
    explicit MHVECTOR2(_In_reads_(2) const float *pArray) : XMFLOAT2(pArray) {}
    MHVECTOR2(FXMVECTOR& V) { XMStoreFloat2( this, V ); }

    operator XMVECTOR() const { return XMLoadFloat2( this ); }

    // Comparision operators
	bool XM_CALLCONV operator == (FMHVECTOR2& V) const;
	bool XM_CALLCONV operator != (FMHVECTOR2& V) const;

    // Assignment operators
	MHVECTOR2& XM_CALLCONV operator = (FMHVECTOR2& V) { x = V.x; y = V.y; return *this; }
	MHVECTOR2& XM_CALLCONV operator += (FMHVECTOR2& V);
	MHVECTOR2& XM_CALLCONV operator += (float S);
	MHVECTOR2& XM_CALLCONV operator -= (FMHVECTOR2& V);
	MHVECTOR2& XM_CALLCONV operator -= (float S);
	MHVECTOR2& XM_CALLCONV operator *= (FMHVECTOR2& V);
	MHVECTOR2& XM_CALLCONV operator *= (float S);
	MHVECTOR2& XM_CALLCONV operator /= (FMHVECTOR2& V);
	MHVECTOR2& XM_CALLCONV operator /= (float S);

    // Urnary operators
	MHVECTOR2 XM_CALLCONV operator + () const { return *this; }
	MHVECTOR2 XM_CALLCONV operator - () const { return MHVECTOR2(-x, -y); }

    // Vector operations
	bool XM_CALLCONV VInBounds(FMHVECTOR2& Bounds) const;

	float XM_CALLCONV VLength() const;
	float XM_CALLCONV VLengthSquared() const;

	float XM_CALLCONV VDot(FMHVECTOR2& V) const;
	void XM_CALLCONV VCross(FMHVECTOR2& V, MHVECTOR2& result) const;
	MHVECTOR2 XM_CALLCONV VCross(FMHVECTOR2& V) const;
    
	void XM_CALLCONV VNormalize();
	void XM_CALLCONV VNormalize(MHVECTOR2& result) const;

	void XM_CALLCONV VClamp(FMHVECTOR2& vmin, FMHVECTOR2& vmax);
	void XM_CALLCONV VClamp(FMHVECTOR2& vmin, FMHVECTOR2& vmax, MHVECTOR2& result) const;

    // Static functions
	static bool XM_CALLCONV InBounds(FMHVECTOR2& V, FMHVECTOR2& Bounds);

	static float XM_CALLCONV Length(FMHVECTOR2& V);
	static float XM_CALLCONV LengthSquared(FMHVECTOR2& V);

	static float XM_CALLCONV Dot(FMHVECTOR2& V1, FMHVECTOR2& V2);
	static void XM_CALLCONV Cross(FMHVECTOR2& V1, FMHVECTOR2& V2, MHVECTOR2& result);
	static MHVECTOR2 XM_CALLCONV Cross(FMHVECTOR2& V1, FMHVECTOR2& V2);

	static void XM_CALLCONV Normalize(FMHVECTOR2& V, MHVECTOR2& result);
	static MHVECTOR2 XM_CALLCONV Normalize(FMHVECTOR2& V);
	
	static void XM_CALLCONV Clamp(FMHVECTOR2& V, FMHVECTOR2& vmin, FMHVECTOR2& vmax, MHVECTOR2& result);
	static MHVECTOR2 XM_CALLCONV Clamp(FMHVECTOR2& V, FMHVECTOR2& vmin, FMHVECTOR2& vmax);

	static void XM_CALLCONV ClampLength(FMHVECTOR2& V, float LengthMin, float LengthMax, MHVECTOR2& result);
	static MHVECTOR2 XM_CALLCONV ClampLength(FMHVECTOR2& V, float LengthMin, float LengthMax);

	static float XM_CALLCONV Distance(FMHVECTOR2& v1, FMHVECTOR2& v2);
	static float XM_CALLCONV DistanceSquared(FMHVECTOR2& v1, FMHVECTOR2& v2);

	static void XM_CALLCONV Min(FMHVECTOR2& v1, FMHVECTOR2& v2, MHVECTOR2& result);
	static MHVECTOR2 XM_CALLCONV Min(FMHVECTOR2& v1, FMHVECTOR2& v2);

	static void XM_CALLCONV Max(FMHVECTOR2& v1, FMHVECTOR2& v2, MHVECTOR2& result);
	static MHVECTOR2 XM_CALLCONV Max(FMHVECTOR2& v1, FMHVECTOR2& v2);

	static void XM_CALLCONV Lerp(FMHVECTOR2& v1, FMHVECTOR2& v2, float t, MHVECTOR2& result);
	static MHVECTOR2 XM_CALLCONV Lerp(FMHVECTOR2& v1, FMHVECTOR2& v2, float t);

	static void XM_CALLCONV SmoothStep(FMHVECTOR2& v1, FMHVECTOR2& v2, float t, MHVECTOR2& result);
	static MHVECTOR2 XM_CALLCONV SmoothStep(FMHVECTOR2& v1, FMHVECTOR2& v2, float t);

	static void XM_CALLCONV Barycentric(FMHVECTOR2& v1, FMHVECTOR2& v2, FMHVECTOR2& v3, float f, float g, MHVECTOR2& result);
	static MHVECTOR2 XM_CALLCONV Barycentric(FMHVECTOR2& v1, FMHVECTOR2& v2, FMHVECTOR2& v3, float f, float g);

	static void XM_CALLCONV CatmullRom(FMHVECTOR2& v1, FMHVECTOR2& v2, FMHVECTOR2& v3, FMHVECTOR2& v4, float t, MHVECTOR2& result);
	static MHVECTOR2 XM_CALLCONV CatmullRom(FMHVECTOR2& v1, FMHVECTOR2& v2, FMHVECTOR2& v3, FMHVECTOR2& v4, float t);

	static void XM_CALLCONV Hermite(FMHVECTOR2& v1, FMHVECTOR2& t1, FMHVECTOR2& v2, FMHVECTOR2& t2, float t, MHVECTOR2& result);
	static MHVECTOR2 XM_CALLCONV Hermite(FMHVECTOR2& v1, FMHVECTOR2& t1, FMHVECTOR2& v2, FMHVECTOR2& t2, float t);

	static void XM_CALLCONV Reflect(FMHVECTOR2& ivec, FMHVECTOR2& nvec, MHVECTOR2& result);
	static MHVECTOR2 XM_CALLCONV Reflect(FMHVECTOR2& ivec, FMHVECTOR2& nvec);

	static void XM_CALLCONV Refract(FMHVECTOR2& ivec, FMHVECTOR2& nvec, float refractionIndex, MHVECTOR2& result);
	static MHVECTOR2 XM_CALLCONV Refract(FMHVECTOR2& ivec, FMHVECTOR2& nvec, float refractionIndex);

	static void XM_CALLCONV Transform(FMHVECTOR2& v, FMHQUATERNION& quat, MHVECTOR2& result);
	static MHVECTOR2 XM_CALLCONV Transform(FMHVECTOR2& v, FMHQUATERNION& quat);

	static void XM_CALLCONV Transform(FMHVECTOR2& v, FMHMATRIX& m, MHVECTOR2& result);
	static MHVECTOR2 XM_CALLCONV Transform(FMHVECTOR2& v, FMHMATRIX& m);
	static void XM_CALLCONV Transform(_In_reads_(count) FMHVECTOR2* varray, size_t count, FMHMATRIX& m, _Out_writes_(count) MHVECTOR2* resultArray);

	static void XM_CALLCONV Transform(FMHVECTOR2& v, FMHMATRIX& m, MHVECTOR4& result);
	static void XM_CALLCONV Transform(_In_reads_(count) FMHVECTOR2* varray, size_t count, FMHMATRIX& m, _Out_writes_(count) MHVECTOR4* resultArray);

	static void XM_CALLCONV TransformNormal(FMHVECTOR2& v, FMHMATRIX& m, MHVECTOR2& result);
	static MHVECTOR2 XM_CALLCONV TransformNormal(FMHVECTOR2& v, FMHMATRIX& m);
	static void XM_CALLCONV TransformNormal(_In_reads_(count) FMHVECTOR2* varray, size_t count, FMHMATRIX& m, _Out_writes_(count) MHVECTOR2* resultArray);
};

// Binary operators
MHVECTOR2 XM_CALLCONV operator+ (FMHVECTOR2& V1, FMHVECTOR2& V2);
MHVECTOR2 XM_CALLCONV operator+ (FMHVECTOR2& V, float S);
MHVECTOR2 XM_CALLCONV operator+ (float S, FMHVECTOR2& V);
MHVECTOR2 XM_CALLCONV operator- (FMHVECTOR2& V1, FMHVECTOR2& V2);
MHVECTOR2 XM_CALLCONV operator- (FMHVECTOR2& V, float S);
MHVECTOR2 XM_CALLCONV operator- (float S, FMHVECTOR2& V);
MHVECTOR2 XM_CALLCONV operator* (FMHVECTOR2& V1, FMHVECTOR2& V2);
MHVECTOR2 XM_CALLCONV operator* (FMHVECTOR2& V, float S);
MHVECTOR2 XM_CALLCONV operator* (float S, FMHVECTOR2& V);
MHVECTOR2 XM_CALLCONV operator/ (FMHVECTOR2& V1, FMHVECTOR2& V2);
MHVECTOR2 XM_CALLCONV operator/ (FMHVECTOR2& V, float S);
MHVECTOR2 XM_CALLCONV operator/ (float S, FMHVECTOR2& V);

#	pragma endregion

namespace_DirectX_end; // namespace DirectX

#ifdef __cplusplus
EXTERN_CC_END
#endif
