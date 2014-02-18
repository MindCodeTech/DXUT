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
// Ray
#	pragma region MHRAY

#if (defined(_M_IX86) || defined(_M_X64) || defined(_M_ARM)) && defined(_XM_NO_INTRINSICS_)
class MHRAY
#else
__declspec(align(16)) class MHRAY
#endif
{
/*
class MHRAY
{*/
public:
    MHVECTOR3 position;
    MHVECTOR3 direction;

    MHRAY() : position(0.0f, 0.0f, 0.0f), direction(0.0f, 0.0f, 1.0f) {}
    MHRAY( FMHVECTOR3& pos, FMHVECTOR3& dir ) : position(pos), direction(dir) {}

    // Comparision operators
	bool XM_CALLCONV operator == (FMHRAY& r) const;
	bool XM_CALLCONV operator != (FMHRAY& r) const;

    // MHRAY operations
	bool XM_CALLCONV Intersects(const BoundingSphere& sphere, _Out_ float& Dist) const;
	bool XM_CALLCONV Intersects(const BoundingBox& box, _Out_ float& Dist) const;
	bool XM_CALLCONV Intersects(FMHVECTOR3& tri0, FMHVECTOR3& tri1, FMHVECTOR3& tri2, _Out_ float& Dist) const;
	bool XM_CALLCONV Intersects(FMHPLANE& plane, _Out_ float& Dist) const;
};

#	pragma endregion

namespace_DirectX_end; // namespace DirectX

#ifdef __cplusplus
EXTERN_CC_END
#endif
