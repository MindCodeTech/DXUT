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
// 4D vector
#	pragma region MHVECTOR4

#if (defined(_M_IX86) || defined(_M_X64) || defined(_M_ARM)) && defined(_XM_NO_INTRINSICS_)
struct MHVECTOR4 : public XMFLOAT4
#else
__declspec(align(16)) struct MHVECTOR4 : public XMFLOAT4
#endif
{
/*
struct MHVECTOR4 : public XMFLOAT4
{*/
    MHVECTOR4() : XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f) {}
    explicit MHVECTOR4(float x) : XMFLOAT4( x, x, x, x ) {}
    MHVECTOR4(float _x, float _y, float _z, float _w) : XMFLOAT4(_x, _y, _z, _w) {}
    explicit MHVECTOR4(_In_reads_(4) const float *pArray) : XMFLOAT4(pArray) {}
	MHVECTOR4(FXMVECTOR& V) { XMStoreFloat4(this, V); }

    operator XMVECTOR() const { return XMLoadFloat4( this ); }

    // Comparision operators
	bool XM_CALLCONV operator == (FMHVECTOR4& V) const;
	bool XM_CALLCONV operator != (FMHVECTOR4& V) const;

    // Assignment operators
	MHVECTOR4& XM_CALLCONV operator= (FMHVECTOR4& V) { x = V.x; y = V.y; z = V.z; w = V.w; return *this; }
	MHVECTOR4& XM_CALLCONV operator+= (FMHVECTOR4& V);
	MHVECTOR4& XM_CALLCONV operator+= (float S);
	MHVECTOR4& XM_CALLCONV operator-= (FMHVECTOR4& V);
	MHVECTOR4& XM_CALLCONV operator-= (float S);
	MHVECTOR4& XM_CALLCONV operator*= (FMHVECTOR4& V);
	MHVECTOR4& XM_CALLCONV operator*= (float S);
	MHVECTOR4& XM_CALLCONV operator/= (FMHVECTOR4& V);
	MHVECTOR4& XM_CALLCONV operator/= (float S);

    // Urnary operators
	MHVECTOR4 XM_CALLCONV operator+ () const { return *this; }
	MHVECTOR4 XM_CALLCONV operator- () const;

    // Vector operations
	bool XM_CALLCONV VInBounds(FMHVECTOR4& Bounds) const;

	float XM_CALLCONV VLength() const;
	float XM_CALLCONV VLengthSquared() const;

	float XM_CALLCONV VDot(FMHVECTOR4& V) const;
	void XM_CALLCONV VCross(FMHVECTOR4& v1, FMHVECTOR4& v2, MHVECTOR4& result) const;
	MHVECTOR4 XM_CALLCONV VCross(FMHVECTOR4& v1, FMHVECTOR4& v2) const;

	void XM_CALLCONV VNormalize();
	void XM_CALLCONV VNormalize(MHVECTOR4& result) const;

	void XM_CALLCONV VClamp(FMHVECTOR4& vmin, FMHVECTOR4& vmax);
	void XM_CALLCONV VClamp(FMHVECTOR4& vmin, FMHVECTOR4& vmax, MHVECTOR4& result) const;

    // Static functions
	static bool XM_CALLCONV InBounds(FMHVECTOR4& V, FMHVECTOR4& Bounds);

	static float XM_CALLCONV Length(FMHVECTOR4& V);
	static float XM_CALLCONV LengthSquared(FMHVECTOR4& V);

	static float XM_CALLCONV Dot(FMHVECTOR4& V1, FMHVECTOR4& V2);
	static void XM_CALLCONV Cross(FMHVECTOR4& V1, FMHVECTOR4& V2, FMHVECTOR4& V3, MHVECTOR4& result);
	static MHVECTOR4 XM_CALLCONV Cross(FMHVECTOR4& V1, FMHVECTOR4& V2, FMHVECTOR4& V3);

	static void XM_CALLCONV Normalize(FMHVECTOR4& V, MHVECTOR4& result);
	static MHVECTOR4 XM_CALLCONV Normalize(FMHVECTOR4& V);

	static void XM_CALLCONV Clamp(FMHVECTOR4& V, FMHVECTOR4& vmin, FMHVECTOR4& vmax, MHVECTOR4& result);
	static MHVECTOR4 XM_CALLCONV Clamp(FMHVECTOR4& V, FMHVECTOR4& vmin, FMHVECTOR4& vmax);

	static void XM_CALLCONV ClampLength(FMHVECTOR4& V, float LengthMin, float LengthMax, MHVECTOR4& result);
	static MHVECTOR4 XM_CALLCONV ClampLength(FMHVECTOR4& V, float LengthMin, float LengthMax);

	static float XM_CALLCONV Distance(FMHVECTOR4& v1, FMHVECTOR4& v2);
	static float XM_CALLCONV DistanceSquared(FMHVECTOR4& v1, FMHVECTOR4& v2);

	static void XM_CALLCONV Min(FMHVECTOR4& v1, FMHVECTOR4& v2, MHVECTOR4& result);
	static MHVECTOR4 XM_CALLCONV Min(FMHVECTOR4& v1, FMHVECTOR4& v2);

	static void XM_CALLCONV Max(FMHVECTOR4& v1, FMHVECTOR4& v2, MHVECTOR4& result);
	static MHVECTOR4 XM_CALLCONV Max(FMHVECTOR4& v1, FMHVECTOR4& v2);

	static void XM_CALLCONV Lerp(FMHVECTOR4& v1, FMHVECTOR4& v2, float t, MHVECTOR4& result);
	static MHVECTOR4 XM_CALLCONV Lerp(FMHVECTOR4& v1, FMHVECTOR4& v2, float t);

	static void XM_CALLCONV SmoothStep(FMHVECTOR4& v1, FMHVECTOR4& v2, float t, MHVECTOR4& result);
	static MHVECTOR4 XM_CALLCONV SmoothStep(FMHVECTOR4& v1, FMHVECTOR4& v2, float t);

	static void XM_CALLCONV Barycentric(FMHVECTOR4& v1, FMHVECTOR4& v2, FMHVECTOR4& v3, float f, float g, MHVECTOR4& result);
	static MHVECTOR4 XM_CALLCONV Barycentric(FMHVECTOR4& v1, FMHVECTOR4& v2, FMHVECTOR4& v3, float f, float g);

	static void XM_CALLCONV CatmullRom(FMHVECTOR4& v1, FMHVECTOR4& v2, FMHVECTOR4& v3, FMHVECTOR4& v4, float t, MHVECTOR4& result);
	static MHVECTOR4 XM_CALLCONV CatmullRom(FMHVECTOR4& v1, FMHVECTOR4& v2, FMHVECTOR4& v3, FMHVECTOR4& v4, float t);

	static void XM_CALLCONV Hermite(FMHVECTOR4& v1, FMHVECTOR4& t1, FMHVECTOR4& v2, FMHVECTOR4& t2, float t, MHVECTOR4& result);
	static MHVECTOR4 XM_CALLCONV Hermite(FMHVECTOR4& v1, FMHVECTOR4& t1, FMHVECTOR4& v2, FMHVECTOR4& t2, float t);

	static void XM_CALLCONV Reflect(FMHVECTOR4& ivec, FMHVECTOR4& nvec, MHVECTOR4& result);
	static MHVECTOR4 XM_CALLCONV Reflect(FMHVECTOR4& ivec, FMHVECTOR4& nvec);

	static void XM_CALLCONV Refract(FMHVECTOR4& ivec, FMHVECTOR4& nvec, float refractionIndex, MHVECTOR4& result);
	static MHVECTOR4 XM_CALLCONV Refract(FMHVECTOR4& ivec, FMHVECTOR4& nvec, float refractionIndex);

	static void XM_CALLCONV Transform(FMHVECTOR2& v, FMHQUATERNION& quat, MHVECTOR4& result);
	static MHVECTOR4 XM_CALLCONV Transform(FMHVECTOR2& v, FMHQUATERNION& quat);

	static void XM_CALLCONV Transform(FMHVECTOR3& v, FMHQUATERNION& quat, MHVECTOR4& result);
	static MHVECTOR4 XM_CALLCONV Transform(FMHVECTOR3& v, FMHQUATERNION& quat);

	static void XM_CALLCONV Transform(FMHVECTOR4& v, FMHQUATERNION& quat, MHVECTOR4& result);
	static MHVECTOR4 XM_CALLCONV Transform(FMHVECTOR4& v, FMHQUATERNION& quat);

	static void XM_CALLCONV Transform(FMHVECTOR4& v, FMHMATRIX& m, MHVECTOR4& result);
	static MHVECTOR4 XM_CALLCONV Transform(FMHVECTOR4& v, FMHMATRIX& m);
	static void XM_CALLCONV Transform(_In_reads_(count) FMHVECTOR4* varray, size_t count, FMHMATRIX& m, _Out_writes_(count) MHVECTOR4* resultArray);
};

// Binary operators
MHVECTOR4 XM_CALLCONV operator+ (FMHVECTOR4& V1, FMHVECTOR4& V2);
MHVECTOR4 XM_CALLCONV operator+ (FMHVECTOR4& V, float S);
MHVECTOR4 XM_CALLCONV operator+ (float S, FMHVECTOR4& V);
MHVECTOR4 XM_CALLCONV operator- (FMHVECTOR4& V1, FMHVECTOR4& V2);
MHVECTOR4 XM_CALLCONV operator- (FMHVECTOR4& V, float S);
MHVECTOR4 XM_CALLCONV operator- (float S, FMHVECTOR4& V);
MHVECTOR4 XM_CALLCONV operator* (FMHVECTOR4& V1, FMHVECTOR4& V2);
MHVECTOR4 XM_CALLCONV operator* (FMHVECTOR4& V, float S);
MHVECTOR4 XM_CALLCONV operator* (float S, FMHVECTOR4& V);
MHVECTOR4 XM_CALLCONV operator/ (FMHVECTOR4& V1, FMHVECTOR4& V2);
MHVECTOR4 XM_CALLCONV operator/ (FMHVECTOR4& V, float S);
MHVECTOR4 XM_CALLCONV operator/ (float S, FMHVECTOR4& V);

#	pragma endregion

namespace_DirectX_end; // namespace DirectX

#ifdef __cplusplus
EXTERN_CC_END
#endif
