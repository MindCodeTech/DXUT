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

#	pragma region MHLINE

//------------------------------------------------------------------------------
// MHLINE operators
//------------------------------------------------------------------------------
#pragma region operators

//------------------------------------------------------------------------------
// Comparision operators
//------------------------------------------------------------------------------

inline bool XM_CALLCONV MHLINE::operator == (FMHLINE& line) const
{
	using namespace DirectX;
	using DirectX::MHLINE;
	XMVECTOR l1p = XMLoadFloat3(&spoint);
	XMVECTOR l2p = XMLoadFloat3(&line.spoint);
	XMVECTOR l1d = XMLoadFloat3(&dpoint);
	XMVECTOR l2d = XMLoadFloat3(&line.dpoint);
	return XMVector3Equal(l1p, l2p) && XMVector3Equal(l1d, l2d);
}

inline bool XM_CALLCONV MHLINE::operator != (FMHLINE& line) const
{
	using namespace DirectX;
	using DirectX::MHLINE;
	XMVECTOR l1p = XMLoadFloat3(&spoint);
	XMVECTOR l2p = XMLoadFloat3(&line.spoint);
	XMVECTOR l1d = XMLoadFloat3(&dpoint);
	XMVECTOR l2d = XMLoadFloat3(&line.dpoint);
	return XMVector3NotEqual(l1p, l2p) && XMVector3NotEqual(l1d, l2d);
}

#pragma endregion

//------------------------------------------------------------------------------
// MHLINE operations
//------------------------------------------------------------------------------
#pragma region operations

inline float XM_CALLCONV MHLINE::Length() const
{
	using namespace DirectX;
	using DirectX::MHLINE;
	XMVECTOR l1 = XMVectorSubtract(dpoint, spoint);
	XMVECTOR L = XMVector3Length(l1);
	return XMVectorGetX(L);
}

inline float XM_CALLCONV MHLINE::LengthSquared() const
{
	using namespace DirectX;
	using DirectX::MHLINE;
	XMVECTOR l1 = XMVectorSubtract(dpoint, spoint);
	XMVECTOR L = XMVector3Length(l1);
	return XMVectorGetX(L);
}

inline MHVECTOR3 XM_CALLCONV MHLINE::Vector() const
{
	using namespace DirectX;
	using DirectX::MHLINE;
	XMVECTOR Lv = XMVectorSubtract(dpoint, spoint);
	return Lv;
}

inline MHVECTOR3 XM_CALLCONV MHLINE::Direction() const
{
	using namespace DirectX;
	using DirectX::MHLINE;
	XMVECTOR Lv = XMVectorSubtract(dpoint, spoint);
	XMVECTOR L = XMVector3Normalize(Lv);

	MHVECTOR3 result;
	XMStoreFloat3(&result, L);
	return result;
}

inline MHVECTOR3 XM_CALLCONV MHLINE::MidPoint() const
{
	using namespace DirectX;
	using DirectX::MHLINE;
	static const float HALF = 0.5f;

	XMVECTOR Lv1 = XMVectorSubtract(dpoint, spoint);
	XMVECTOR Lv2 = XMVectorReplicate(HALF);
	XMVECTOR L = XMVectorMultiply(Lv1, Lv2);

	MHVECTOR3 result;
	XMStoreFloat3(&result, L);
	return result;
}

inline MHVECTOR3 XM_CALLCONV MHLINE::AtPoint(float t) const
{
	using namespace DirectX;
	using DirectX::MHLINE;
	XMVECTOR l = XMLoadFloat(&t);
	XMVECTOR L = MHVECTOR3::Lerp(spoint, dpoint, t);

	MHVECTOR3 result;
	XMStoreFloat3(&result, L);
	return result;
}

inline void XM_CALLCONV MHLINE::Extend(float samount, float eamount)
{
	using namespace DirectX;
	using DirectX::MHLINE;
	XMVECTOR start = XMLoadFloat3(&spoint);
	XMVECTOR end = XMLoadFloat3(&dpoint);
	XMVECTOR dir = XMVector3Normalize(XMVectorSubtract(end, start));
	XMVECTOR sp = XMVectorSubtract(start, XMVectorMultiply(dir, XMVectorReplicate(samount)));
	XMVECTOR sd = XMVectorAdd(end, XMVectorMultiply(dir, XMVectorReplicate(eamount)));
	XMStoreFloat3(&spoint, sp);
	XMStoreFloat3(&dpoint, sd);
}

//------------------------------------------------------------------------------
// Static functions
//------------------------------------------------------------------------------
/*
inline float XM_CALLCONV MHLINE::Length()
{
	using namespace DirectX;
	using DirectX::MHLINE;
	XMVECTOR l1 = XMVectorSubtract(dpoint, spoint);
	XMVECTOR L = XMVector3Length(l1);
	return XMVectorGetX(L);
}

inline float XM_CALLCONV MHLINE::LengthSquared()
{
	using namespace DirectX;
	using DirectX::MHLINE;
	XMVECTOR l1 = XMVectorSubtract(dpoint, spoint);
	XMVECTOR L = XMVector3Length(l1);
	return XMVectorGetX(L);
}

inline MHVECTOR3 XM_CALLCONV MHLINE::Vector()
{
	using namespace DirectX;
	XMVECTOR Lv = XMVectorSubtract(dpoint, spoint);
	return Lv;
}

inline MHVECTOR3 MHLINE::Direction()
{
	using namespace DirectX;
	using DirectX::MHLINE;
	XMVECTOR Lv = XMVectorSubtract(dpoint, spoint);
	XMVECTOR L = XMVector3Normalize(Lv);

	MHVECTOR3 result;
	XMStoreFloat3(&result, L);
	return result;
}

inline MHVECTOR3 MHLINE::MidPoint()
{
	using namespace DirectX;
	using DirectX::MHLINE;
	static const float HALF = 0.5f;

	XMVECTOR Lv1 = XMVectorSubtract(dpoint, spoint);
	XMVECTOR Lv2 = XMVectorReplicate(HALF);
	XMVECTOR L = XMVectorMultiply(Lv1, Lv2);

	MHVECTOR3 result;
	XMStoreFloat3(&result, L);
	return result;
}

inline MHVECTOR3 XM_CALLCONV MHLINE::AtPoint(float t)
{
	using namespace DirectX;
	using DirectX::MHLINE;
	XMVECTOR l = XMLoadFloat(&t);
	XMVECTOR L = XMVectorLerp(spoint, dpoint, t);

	MHVECTOR3 result;
	XMStoreFloat3(&result, L);
	return result;
}

inline void MHLINE::Extend(float samount, float eamount)
{
	using namespace DirectX;
	using DirectX::MHLINE;
	XMVECTOR start = XMLoadFloat3(&spoint);
	XMVECTOR end = XMLoadFloat3(&dpoint);
	XMVECTOR dir = XMVector3Normalize(XMVectorSubtract(end, start));
	XMVECTOR sp = XMVectorSubtract(start, XMVectorMultiply(dir, XMVectorReplicate(samount)));
	XMVECTOR sd = XMVectorAdd(end, XMVectorMultiply(dir, XMVectorReplicate(eamount)));
	XMStoreFloat3(&spoint, sp);
	XMStoreFloat3(&dpoint, sd);
}
*/

#pragma endregion

#	pragma endregion

#ifdef __cplusplus
EXTERN_CC_END
#endif
