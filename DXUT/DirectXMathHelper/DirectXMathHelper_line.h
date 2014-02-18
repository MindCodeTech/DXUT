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
// Line
#	pragma region MHLINE

#if (defined(_M_IX86) || defined(_M_X64) || defined(_M_ARM)) && defined(_XM_NO_INTRINSICS_)
class MHLINE
#else
__declspec(align(16)) class MHLINE
#endif
{
/*
class MHLINE
{*/
public:
	MHVECTOR3 spoint;
	MHVECTOR3 dpoint;

	MHLINE(){}

	MHLINE(FMHVECTOR3& start, FMHVECTOR3& end) : spoint(start), dpoint(end){}

	MHLINE(FMHLINE& line) : spoint(line.spoint), dpoint(line.dpoint){}

	// Comparision operators
	bool XM_CALLCONV operator == (FMHLINE& line) const;
	bool XM_CALLCONV operator != (FMHLINE& line) const;

	// Assignment operators
	MHLINE& operator = (FMHLINE& line) { spoint = line.spoint;dpoint = line.dpoint; return *this; }

	// MHLINE operations
	float XM_CALLCONV Length() const;

	float XM_CALLCONV LengthSquared() const;

	MHVECTOR3 XM_CALLCONV Vector() const;

	MHVECTOR3 XM_CALLCONV Direction() const;

	MHVECTOR3 XM_CALLCONV MidPoint() const;

	MHVECTOR3 XM_CALLCONV AtPoint(float t) const;

	void XM_CALLCONV Extend(float s_amount, float e_amount);

	// Static functions
/*
	static float XM_CALLCONV Length();

	static float XM_CALLCONV LengthSquared();

	static MHVECTOR3 XM_CALLCONV Vector();

	static MHVECTOR3 XM_CALLCONV Direction();

	static MHVECTOR3 XM_CALLCONV MidPoint();

	static MHVECTOR3 XM_CALLCONV AtPoint(float t);

	static void XM_CALLCONV Extend(float samount, float eamount);*/
};

#	pragma endregion

namespace_DirectX_end; // namespace DirectX

#ifdef __cplusplus
EXTERN_CC_END
#endif
