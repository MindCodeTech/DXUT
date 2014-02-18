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
// Color
#	pragma region MHCOLOR

#if (defined(_M_IX86) || defined(_M_X64) || defined(_M_ARM)) && defined(_XM_NO_INTRINSICS_)
struct MHCOLOR : public XMFLOAT4
#else
__declspec(align(16)) struct MHCOLOR : public XMFLOAT4
#endif
{
/*
struct MHCOLOR : public XMFLOAT4
{*/
	float r, g, b, a;
    MHCOLOR() : XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f) {}
    MHCOLOR( float _r, float _g, float _b ) : XMFLOAT4(_r, _g, _b, 1.f) {}
    MHCOLOR( float _r, float _g, float _b, float _a ) : XMFLOAT4(_r, _g, _b, _a) {}
    explicit MHCOLOR( const MHVECTOR3& clr ) : XMFLOAT4( clr.x, clr.y, clr.z, 1.f ) {}
    explicit MHCOLOR( FMHVECTOR4& clr ) : XMFLOAT4( clr.x, clr.y, clr.z, clr.w ) {}
    explicit MHCOLOR(_In_reads_(4) const float *pArray) : XMFLOAT4(pArray) {}
	MHCOLOR(FXMVECTOR& V) { XMStoreFloat4(this, V); }

    explicit MHCOLOR( const PackedVector::XMCOLOR& Packed );
        // BGRA Direct3D 9 D3DCOLOR packed color
    
    explicit MHCOLOR( const PackedVector::XMUBYTEN4& Packed );
        // RGBA XNA Game Studio packed color

    operator XMVECTOR() const { return XMLoadFloat4( this ); }
    operator const float*() const { return reinterpret_cast<const float*>(this); }

    // Comparison operators
	bool XM_CALLCONV operator == (FMHCOLOR& c) const;
	bool XM_CALLCONV operator != (FMHCOLOR& c) const;

    // Assignment operators
	MHCOLOR& XM_CALLCONV operator= (FMHCOLOR& c) { x = c.x; y = c.y; z = c.z; w = c.w; return *this; }
	MHCOLOR& XM_CALLCONV operator+= (FMHCOLOR& c);
	MHCOLOR& XM_CALLCONV operator+= (float S);
	MHCOLOR& XM_CALLCONV operator-= (FMHCOLOR& c);
	MHCOLOR& XM_CALLCONV operator-= (float S);
	MHCOLOR& XM_CALLCONV operator*= (FMHCOLOR& c);
	MHCOLOR& XM_CALLCONV operator*= (float S);
	MHCOLOR& XM_CALLCONV operator/= (FMHCOLOR& c);
	MHCOLOR& XM_CALLCONV operator/= (float S);

    // Urnary operators
	MHCOLOR XM_CALLCONV operator+ () const { return *this; }
	MHCOLOR XM_CALLCONV operator- () const;

    // Properties
	float XM_CALLCONV R() const { return x; }
	void XM_CALLCONV R(float r) { x = r; }

	float XM_CALLCONV G() const { return y; }
	void XM_CALLCONV G(float g) { y = g; }

	float XM_CALLCONV B() const { return z; }
	void XM_CALLCONV B(float b) { z = b; }

	float XM_CALLCONV A() const { return w; }
	void XM_CALLCONV A(float a) { w = a; }

    // MHCOLOR operations
	PackedVector::XMCOLOR XM_CALLCONV BGRA() const;
	PackedVector::XMUBYTEN4 XM_CALLCONV RGBA() const;

	MHVECTOR3 XM_CALLCONV CToVector3() const;
	MHVECTOR4 XM_CALLCONV CToVector4() const;

	void XM_CALLCONV CNegate();
	void XM_CALLCONV CNegate(MHCOLOR& result) const;

	void XM_CALLCONV CSaturate();
	void XM_CALLCONV CSaturate(MHCOLOR& result) const;

	void XM_CALLCONV CPremultiply();
	void XM_CALLCONV CPremultiply(MHCOLOR& result) const;

	void XM_CALLCONV CAdjustSaturation(float sat);
	void XM_CALLCONV CAdjustSaturation(float sat, MHCOLOR& result) const;

	void XM_CALLCONV CAdjustContrast(float contrast);
	void XM_CALLCONV CAdjustContrast(float contrast, MHCOLOR& result) const;
    
    // Static functions
	static MHVECTOR3 XM_CALLCONV ToVector3(FMHCOLOR& c);
	static MHVECTOR4 XM_CALLCONV ToVector4(FMHCOLOR& c);

	static MHVECTOR4 XM_CALLCONV HSLToRGB(FMHVECTOR4& c);
	static MHVECTOR4 XM_CALLCONV HSVToRGB(FMHVECTOR4& c);

	static MHVECTOR4 XM_CALLCONV RGBToHSL(FMHVECTOR4& c);
	static MHVECTOR4 XM_CALLCONV RGBToHSV(FMHVECTOR4& c);

	static MHVECTOR4 XM_CALLCONV RGBToXYZ(FMHVECTOR4& c);
	static MHVECTOR4 XM_CALLCONV RGBToYUV(FMHVECTOR4& c);

	static MHVECTOR4 XM_CALLCONV RGBToYUV_HD(FMHVECTOR4& c);
	static MHVECTOR4 XM_CALLCONV SRGBToXYZ(FMHVECTOR4& c);

	static MHVECTOR4 XM_CALLCONV XYZToRGB(FMHVECTOR4& c);
	static MHVECTOR4 XM_CALLCONV XYZToSRGB(FMHVECTOR4& c);

	static MHVECTOR4 XM_CALLCONV YUVToRGB(FMHVECTOR4& c);
	static MHVECTOR4 XM_CALLCONV YUVToRGB_HD(FMHVECTOR4& c);

	static MHCOLOR XM_CALLCONV Negate(FMHCOLOR& c);
	static void XM_CALLCONV Negate(FMHCOLOR& c, MHCOLOR& result);

	static MHCOLOR XM_CALLCONV Saturate(FMHCOLOR& c);
	static void XM_CALLCONV Saturate(FMHCOLOR& c, MHCOLOR& result);

	static MHCOLOR XM_CALLCONV Premultiply(FMHCOLOR& c);
	static void XM_CALLCONV Premultiply(FMHCOLOR& c, MHCOLOR& result);

	static MHCOLOR XM_CALLCONV AdjustSaturation(FMHCOLOR& c, float sat);
	static void XM_CALLCONV AdjustSaturation(FMHCOLOR& c, float sat, MHCOLOR& result);

	static MHCOLOR XM_CALLCONV AdjustContrast(FMHCOLOR& c, float contrast);
	static void XM_CALLCONV AdjustContrast(FMHCOLOR& c, float contrast, MHCOLOR& result);

	static void XM_CALLCONV Modulate(FMHCOLOR& c1, FMHCOLOR& c2, MHCOLOR& result);
	static MHCOLOR XM_CALLCONV Modulate(FMHCOLOR& c1, FMHCOLOR& c2);

	static void XM_CALLCONV Lerp(FMHCOLOR& c1, FMHCOLOR& c2, float t, MHCOLOR& result);
	static MHCOLOR XM_CALLCONV Lerp(FMHCOLOR& c1, FMHCOLOR& c2, float t);
};

// Binary operators
MHCOLOR XM_CALLCONV operator+ (FMHCOLOR& C1, FMHCOLOR& C2);
MHCOLOR XM_CALLCONV operator+ (FMHCOLOR& C, float S);
MHCOLOR XM_CALLCONV operator+ (float S, FMHCOLOR& C);
MHCOLOR XM_CALLCONV operator- (FMHCOLOR& C1, FMHCOLOR& C2);
MHCOLOR XM_CALLCONV operator- (FMHCOLOR& C1, float S);
MHCOLOR XM_CALLCONV operator- (float S, FMHCOLOR& C);
MHCOLOR XM_CALLCONV operator* (FMHCOLOR& C1, FMHCOLOR& C2);
MHCOLOR XM_CALLCONV operator* (FMHCOLOR& C, float S);
MHCOLOR XM_CALLCONV operator* (float S, FMHCOLOR& C);
MHCOLOR XM_CALLCONV operator/ (FMHCOLOR& C1, FMHCOLOR& C2);
MHCOLOR XM_CALLCONV operator/ (FMHCOLOR& C, float S);
MHCOLOR XM_CALLCONV operator/ (float S, FMHCOLOR& C);

#	pragma endregion

namespace_DirectX_end; // namespace DirectX

#ifdef __cplusplus
EXTERN_CC_END
#endif
