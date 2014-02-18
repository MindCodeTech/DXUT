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

//-----------------------------------------------------------------------------
// Plane
#	pragma region MHPLANE

#if (defined(_M_IX86) || defined(_M_X64) || defined(_M_ARM)) && defined(_XM_NO_INTRINSICS_)
struct MHPLANE : public XMFLOAT4
#else
__declspec(align(16)) struct MHPLANE : public XMFLOAT4
#endif
{
/*
struct MHPLANE : public XMFLOAT4
{*/
    MHPLANE() : XMFLOAT4(0.0f, 1.0f, 0.0f, 0.0f) {}
    MHPLANE(float _x, float _y, float _z, float _w) : XMFLOAT4(_x, _y, _z, _w) {}
    MHPLANE(FMHVECTOR3& normal, float d) : XMFLOAT4(normal.x, normal.y, normal.z, d) {}
    MHPLANE(FMHVECTOR3& point1, FMHVECTOR3& point2, FMHVECTOR3& point3 );
    MHPLANE(FMHVECTOR3& point, FMHVECTOR3& normal);
    explicit MHPLANE(FMHVECTOR4& v) : XMFLOAT4(v.x, v.y, v.z, v.w) {}
    explicit MHPLANE(_In_reads_(4) const float *pArray) : XMFLOAT4(pArray) {}
	MHPLANE(FXMVECTOR& V) { XMStoreFloat4(this, V); }

    operator XMVECTOR() const { return XMLoadFloat4( this ); }

    // Comparision operators
	bool XM_CALLCONV operator == (FMHPLANE& p) const;
	bool XM_CALLCONV operator != (FMHPLANE& p) const;

    // Assignment operators
	MHPLANE& XM_CALLCONV operator= (FMHPLANE& p) { x = p.x; y = p.y; z = p.z; w = p.w; return *this; }

    // Properties
	MHVECTOR3 XM_CALLCONV Normal() const { return MHVECTOR3(x, y, z); }
	void XM_CALLCONV Normal(FMHVECTOR3& normal) { x = normal.x; y = normal.y; z = normal.z; }

	float XM_CALLCONV D() const { return w; }
	void XM_CALLCONV D(float d) { w = d; }

    // MHPLANE operations
	void XM_CALLCONV PNormalize();
	void XM_CALLCONV PNormalize(MHPLANE& result) const;

	float XM_CALLCONV PDot(FMHVECTOR4& v) const;
	float XM_CALLCONV PDotCoordinate(FMHVECTOR3& position) const;
	float XM_CALLCONV PDotNormal(FMHVECTOR3& normal) const;

    // Static functions
	static MHPLANE XM_CALLCONV Normalize(FMHPLANE& plane);
	static void XM_CALLCONV Normalize(FMHPLANE& plane, MHPLANE& result);

	static float XM_CALLCONV Dot(FMHPLANE& plane, FMHVECTOR4& v);
	static float XM_CALLCONV DotCoordinate(FMHPLANE& plane, FMHVECTOR3& position);
	static float XM_CALLCONV DotNormal(FMHPLANE& plane, FMHVECTOR3& normal);

	static void XM_CALLCONV Transform(FMHPLANE& plane, FMHMATRIX& M, MHPLANE& result);
	static MHPLANE XM_CALLCONV Transform(FMHPLANE& plane, FMHMATRIX& M);

	static void XM_CALLCONV Transform(FMHPLANE& plane, FMHQUATERNION& rotation, MHPLANE& result);
	static MHPLANE XM_CALLCONV Transform(FMHPLANE& plane, FMHQUATERNION& rotation);
        // Input quaternion must be the inverse transpose of the transformation
};

#	pragma endregion

namespace_DirectX_end; // namespace DirectX

#ifdef __cplusplus
EXTERN_CC_END
#endif
