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

#	pragma region MHCOLOR

//------------------------------------------------------------------------------
// MHCOLOR methods
//------------------------------------------------------------------------------
#pragma region methods

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

#pragma endregion

//------------------------------------------------------------------------------
// MHCOLOR operations
//------------------------------------------------------------------------------
#pragma region operations

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

inline MHVECTOR3 XM_CALLCONV MHCOLOR::ToVector3(FMHCOLOR& c)
{
	using namespace DirectX;
	MHVECTOR3 VC = (MHVECTOR3)(c.x, c.y, c.z);
	MHVECTOR3 R;
	XMStoreFloat3(&R, VC);
	return R;
}

inline MHVECTOR4 XM_CALLCONV MHCOLOR::ToVector4(FMHCOLOR& c)
{
	using namespace DirectX;
	MHVECTOR4 VC = (MHVECTOR4)(c.x, c.y, c.z, c.w);
	MHVECTOR4 R;
	XMStoreFloat4(&R, VC);
	return R;
}

inline MHVECTOR4 XM_CALLCONV MHCOLOR::HSLToRGB(FMHVECTOR4& c)
{
	using namespace DirectX;
	MHVECTOR4 VC = XMColorHSLToRGB(c);
	MHVECTOR4 R;
	XMStoreFloat4(&R, VC);
	return R;
}

inline MHVECTOR4 XM_CALLCONV MHCOLOR::HSVToRGB(FMHVECTOR4& c)
{
	using namespace DirectX;
	MHVECTOR4 VC = XMColorHSVToRGB(c);
	MHVECTOR4 R;
	XMStoreFloat4(&R, VC);
	return R;
}

inline MHVECTOR4 XM_CALLCONV MHCOLOR::RGBToHSL(FMHVECTOR4& c)
{
	using namespace DirectX;
	MHVECTOR4 VC = XMColorRGBToHSL(c);
	MHVECTOR4 R;
	XMStoreFloat4(&R, VC);
	return R;
}

inline MHVECTOR4 XM_CALLCONV MHCOLOR::RGBToHSV(FMHVECTOR4& c)
{
	using namespace DirectX;
	MHVECTOR4 VC = XMColorRGBToHSV(c);
	MHVECTOR4 R;
	XMStoreFloat4(&R, VC);
	return R;
}

inline MHVECTOR4 XM_CALLCONV MHCOLOR::RGBToXYZ(FMHVECTOR4& c)
{
	using namespace DirectX;
	MHVECTOR4 VC = XMColorRGBToXYZ(c);
	MHVECTOR4 R;
	XMStoreFloat4(&R, VC);
	return R;
}

inline MHVECTOR4 XM_CALLCONV MHCOLOR::RGBToYUV(FMHVECTOR4& c)
{
	using namespace DirectX;
	MHVECTOR4 VC = XMColorRGBToYUV(c);
	MHVECTOR4 R;
	XMStoreFloat4(&R, VC);
	return R;
}

inline MHVECTOR4 XM_CALLCONV MHCOLOR::RGBToYUV_HD(FMHVECTOR4& c)
{
	using namespace DirectX;
	MHVECTOR4 VC = XMColorRGBToYUV_HD(c);
	MHVECTOR4 R;
	XMStoreFloat4(&R, VC);
	return R;
}

inline MHVECTOR4 XM_CALLCONV MHCOLOR::SRGBToXYZ(FMHVECTOR4& c)
{
	using namespace DirectX;
	MHVECTOR4 VC = XMColorSRGBToXYZ(c);
	MHVECTOR4 R;
	XMStoreFloat4(&R, VC);
	return R;
}

inline MHVECTOR4 XM_CALLCONV MHCOLOR::XYZToRGB(FMHVECTOR4& c)
{
	using namespace DirectX;
	MHVECTOR4 VC = XMColorXYZToRGB(c);
	MHVECTOR4 R;
	XMStoreFloat4(&R, VC);
	return R;
}

inline MHVECTOR4 XM_CALLCONV MHCOLOR::XYZToSRGB(FMHVECTOR4& c)
{
	using namespace DirectX;
	MHVECTOR4 VC = XMColorXYZToSRGB(c);
	MHVECTOR4 R;
	XMStoreFloat4(&R, VC);
	return R;
}

inline MHVECTOR4 XM_CALLCONV MHCOLOR::YUVToRGB(FMHVECTOR4& c)
{
	using namespace DirectX;
	MHVECTOR4 VC = XMColorYUVToRGB(c);
	MHVECTOR4 R;
	XMStoreFloat4(&R, VC);
	return R;
}

inline MHVECTOR4 XM_CALLCONV MHCOLOR::YUVToRGB_HD(FMHVECTOR4& c)
{
	using namespace DirectX;
	MHVECTOR4 VC = XMColorYUVToRGB_HD(c);
	MHVECTOR4 R;
	XMStoreFloat4(&R, VC);
	return R;
}

inline MHCOLOR XM_CALLCONV MHCOLOR::Negate(FMHCOLOR& c)
{
	using namespace DirectX;
	XMVECTOR c1 = XMLoadFloat4(&c);
	MHCOLOR R;
	XMStoreFloat4(&R, XMColorNegative(c1));
	return R;
}

inline void XM_CALLCONV MHCOLOR::Negate(FMHCOLOR& c, MHCOLOR& result)
{
	using namespace DirectX;
	XMVECTOR c1 = XMLoadFloat4(&c);
	XMStoreFloat4(&result, XMColorNegative(c1));
}

inline MHCOLOR XM_CALLCONV MHCOLOR::Saturate(FMHCOLOR& c)
{
	using namespace DirectX;
	XMVECTOR c1 = XMLoadFloat4(&c);
	MHCOLOR R;
	XMStoreFloat4(&R, XMVectorSaturate(c1));
	return R;
}

inline void XM_CALLCONV MHCOLOR::Saturate(FMHCOLOR& c, MHCOLOR& result)
{
	using namespace DirectX;
	XMVECTOR c1 = XMLoadFloat4(&c);
	XMStoreFloat4(&result, XMVectorSaturate(c1));
}

inline MHCOLOR XM_CALLCONV MHCOLOR::Premultiply(FMHCOLOR& c)
{
	using namespace DirectX;
	XMVECTOR c1 = XMLoadFloat4(&c);
	XMVECTOR a = XMVectorSplatW(c1);
	a = XMVectorSelect(g_XMIdentityR3, a, g_XMSelect1110);
	MHCOLOR R;
	XMStoreFloat4(&R, XMVectorMultiply(c1, a));
	return R;
}

inline void XM_CALLCONV MHCOLOR::Premultiply(FMHCOLOR& c, MHCOLOR& result)
{
	using namespace DirectX;
	XMVECTOR c1 = XMLoadFloat4(&c);
	XMVECTOR a = XMVectorSplatW(c1);
	a = XMVectorSelect(g_XMIdentityR3, a, g_XMSelect1110);
	XMStoreFloat4(&result, XMVectorMultiply(c1, a));
}

inline MHCOLOR XM_CALLCONV MHCOLOR::AdjustSaturation(FMHCOLOR& c, float sat)
{
	using namespace DirectX;
	XMVECTOR c1 = XMLoadFloat4(&c);
	MHCOLOR R;
	XMStoreFloat4(&R, XMColorAdjustSaturation(c1, sat));
	return R;
}

inline void XM_CALLCONV MHCOLOR::AdjustSaturation(FMHCOLOR& c, float sat, MHCOLOR& result)
{
	using namespace DirectX;
	XMVECTOR c1 = XMLoadFloat4(&c);
	XMStoreFloat4(&result, XMColorAdjustSaturation(c1, sat));
}

inline MHCOLOR XM_CALLCONV MHCOLOR::AdjustContrast(FMHCOLOR& c, float contrast)
{
	using namespace DirectX;
	XMVECTOR c1 = XMLoadFloat4(&c);
	MHCOLOR R;
	XMStoreFloat4(&R, XMColorAdjustContrast(c1, contrast));
	return R;
}

inline void XM_CALLCONV MHCOLOR::AdjustContrast(FMHCOLOR& c, float contrast, MHCOLOR& result)
{
	using namespace DirectX;
	XMVECTOR c1 = XMLoadFloat4(&c);
	XMStoreFloat4(&result, XMColorAdjustContrast(c1, contrast));
}

inline void XM_CALLCONV MHCOLOR::Modulate(FMHCOLOR& c1, FMHCOLOR& c2, MHCOLOR& result)
{
    using namespace DirectX;
    XMVECTOR C0 = XMLoadFloat4( &c1 );
    XMVECTOR C1 = XMLoadFloat4( &c2 );
    XMStoreFloat4( &result, XMColorModulate( C0, C1 ) );
}

inline MHCOLOR XM_CALLCONV MHCOLOR::Modulate(FMHCOLOR& c1, FMHCOLOR& c2)
{
    using namespace DirectX;
    XMVECTOR C0 = XMLoadFloat4( &c1 );
    XMVECTOR C1 = XMLoadFloat4( &c2 );

    MHCOLOR result;
    XMStoreFloat4( &result, XMColorModulate( C0, C1 ) );
    return result;
}

inline void XM_CALLCONV MHCOLOR::Lerp(FMHCOLOR& c1, FMHCOLOR& c2, float t, MHCOLOR& result)
{
    using namespace DirectX;
    XMVECTOR C0 = XMLoadFloat4( &c1 );
    XMVECTOR C1 = XMLoadFloat4( &c2 );
    XMStoreFloat4( &result, XMVectorLerp( C0, C1, t ) );
}

inline MHCOLOR XM_CALLCONV MHCOLOR::Lerp(FMHCOLOR& c1, FMHCOLOR& c2, float t)
{
    using namespace DirectX;
    XMVECTOR C0 = XMLoadFloat4( &c1 );
    XMVECTOR C1 = XMLoadFloat4( &c2 );

    MHCOLOR result;
    XMStoreFloat4( &result, XMVectorLerp( C0, C1, t ) );
    return result;
}

#pragma endregion

//------------------------------------------------------------------------------
// MHCOLOR operators
//------------------------------------------------------------------------------
#pragma region operators

//------------------------------------------------------------------------------
// Comparison operators
//------------------------------------------------------------------------------
inline bool XM_CALLCONV MHCOLOR::operator == (FMHCOLOR& c) const
{
	using namespace DirectX;
	XMVECTOR c1 = XMLoadFloat4(this);
	XMVECTOR c2 = XMLoadFloat4(&c);
	return XMColorEqual(c1, c2);
}

inline bool XM_CALLCONV MHCOLOR::operator != (FMHCOLOR& c) const
{
	using namespace DirectX;
	XMVECTOR c1 = XMLoadFloat4(this);
	XMVECTOR c2 = XMLoadFloat4(&c);
	return XMColorNotEqual(c1, c2);
}

//------------------------------------------------------------------------------
// Assignment operators
//------------------------------------------------------------------------------

inline MHCOLOR& XM_CALLCONV MHCOLOR::operator+= (FMHCOLOR& c)
{
	using namespace DirectX;
	XMVECTOR c1 = XMLoadFloat4(this);
	XMVECTOR c2 = XMLoadFloat4(&c);
	XMStoreFloat4(this, XMVectorAdd(c1, c2));
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

inline MHCOLOR& XM_CALLCONV MHCOLOR::operator-= (FMHCOLOR& c)
{
	using namespace DirectX;
	XMVECTOR c1 = XMLoadFloat4(this);
	XMVECTOR c2 = XMLoadFloat4(&c);
	XMStoreFloat4(this, XMVectorSubtract(c1, c2));
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

inline MHCOLOR& XM_CALLCONV MHCOLOR::operator*= (FMHCOLOR& c)
{
	using namespace DirectX;
	XMVECTOR c1 = XMLoadFloat4(this);
	XMVECTOR c2 = XMLoadFloat4(&c);
	XMStoreFloat4(this, XMVectorMultiply(c1, c2));
	return *this;
}

inline MHCOLOR& XM_CALLCONV MHCOLOR::operator*= (float S)
{
	using namespace DirectX;
	XMVECTOR c = XMLoadFloat4(this);
	XMStoreFloat4(this, XMVectorScale(c, S));
	return *this;
}

inline MHCOLOR& XM_CALLCONV MHCOLOR::operator/= (FMHCOLOR& c)
{
	using namespace DirectX;
	XMVECTOR c1 = XMLoadFloat4(this);
	XMVECTOR c2 = XMLoadFloat4(&c);
	XMStoreFloat4(this, XMVectorDivide(c1, c2));
	return *this;
}

inline MHCOLOR& XM_CALLCONV MHCOLOR::operator/= (float S)
{
	using namespace DirectX;
	assert(S != 0.0f);

	XMVECTOR c1 = XMLoadFloat4(this);
	XMVECTOR X = XMVectorScale(c1, 1.0f / S);
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
	XMVECTOR c = XMLoadFloat4(this);
	MHCOLOR R;
	XMStoreFloat4(&R, XMVectorNegate(c));
	return R;
}

//------------------------------------------------------------------------------
// Binary operators
//------------------------------------------------------------------------------

inline MHCOLOR XM_CALLCONV operator+ (FMHCOLOR& C1, FMHCOLOR& C2)
{
	using namespace DirectX;
	XMVECTOR c1 = XMLoadFloat4(&C1);
	XMVECTOR c2 = XMLoadFloat4(&C2);
	MHCOLOR R;
	XMStoreFloat4(&R, XMVectorAdd(c1, c2));
	return R;
}

inline MHCOLOR XM_CALLCONV operator+ (FMHCOLOR& C, float S)
{
	using namespace DirectX;
	XMVECTOR c1 = XMLoadFloat4(&C);
	XMVECTOR c2 = XMLoadFloat(&S);
	MHCOLOR R;
	XMStoreFloat4(&R, XMVectorAdd(c1, c2));
	return R;
}

inline MHCOLOR XM_CALLCONV operator+ (float S, FMHCOLOR& C)
{
	using namespace DirectX;
	XMVECTOR c1 = XMLoadFloat(&S);
	XMVECTOR c2 = XMLoadFloat4(&C);
	MHCOLOR R;
	XMStoreFloat4(&R, XMVectorAdd(c1, c2));
	return R;
}

inline MHCOLOR XM_CALLCONV operator- (FMHCOLOR& C1, FMHCOLOR& C2)
{
	using namespace DirectX;
	XMVECTOR c1 = XMLoadFloat4(&C1);
	XMVECTOR c2 = XMLoadFloat4(&C2);
	MHCOLOR R;
	XMStoreFloat4(&R, XMVectorSubtract(c1, c2));
	return R;
}

inline MHCOLOR XM_CALLCONV operator- (FMHCOLOR& C, float S)
{
	using namespace DirectX;
	XMVECTOR c1 = XMLoadFloat4(&C);
	XMVECTOR c2 = XMLoadFloat(&S);
	MHCOLOR R;
	XMStoreFloat4(&R, XMVectorSubtract(c1, c2));
	return R;
}

inline MHCOLOR XM_CALLCONV operator- (float S, FMHCOLOR& C)
{
	using namespace DirectX;
	XMVECTOR c1 = XMLoadFloat(&S);
	XMVECTOR c2 = XMLoadFloat4(&C);
	MHCOLOR R;
	XMStoreFloat4(&R, XMVectorSubtract(c1, c2));
	return R;
}

inline MHCOLOR XM_CALLCONV operator* (FMHCOLOR& C1, FMHCOLOR& C2)
{
	using namespace DirectX;
	XMVECTOR c1 = XMLoadFloat4(&C1);
	XMVECTOR c2 = XMLoadFloat4(&C2);
	MHCOLOR R;
	XMStoreFloat4(&R, XMVectorMultiply(c1, c2));
	return R;
}

inline MHCOLOR XM_CALLCONV operator* (FMHCOLOR& C, float S)
{
	using namespace DirectX;
	XMVECTOR c = XMLoadFloat4(&C);
	MHCOLOR R;
	XMStoreFloat4(&R, XMVectorScale(c, S));
	return R;
}

inline MHCOLOR XM_CALLCONV operator* (float S, FMHCOLOR& C)
{
	using namespace DirectX;
	XMVECTOR c1 = XMLoadFloat4(&C);
	MHCOLOR R;
	XMStoreFloat4(&R, XMVectorScale(c1, S));
	return R;
}

inline MHCOLOR XM_CALLCONV operator/ (FMHCOLOR& C1, FMHCOLOR& C2)
{
	using namespace DirectX;
	XMVECTOR c1 = XMLoadFloat4(&C1);
	XMVECTOR c2 = XMLoadFloat4(&C2);
	MHCOLOR R;
	XMStoreFloat4(&R, XMVectorDivide(c1, c2));
	return R;
}

inline MHCOLOR XM_CALLCONV operator/ (FMHCOLOR& C, float S)
{
	using namespace DirectX;
	assert(S != 0.0f);

	XMVECTOR q1 = XMLoadFloat4(&C);
	XMVECTOR X = XMVectorScale(q1, 1.0f / S);

	MHCOLOR R;
	XMStoreFloat4(&R, X);
	return R;
}

inline MHCOLOR XM_CALLCONV operator/ (float S, FMHCOLOR& C)
{
	using namespace DirectX;
	assert(S != 0.0f);

	XMVECTOR q1 = XMLoadFloat4(&C);
	XMVECTOR X = XMVectorScale(q1, 1.0f / S);

	MHCOLOR R;
	XMStoreFloat4(&R, X);
	return R;
}

#pragma endregion

#	pragma endregion

#ifdef __cplusplus
EXTERN_CC_END
#endif
