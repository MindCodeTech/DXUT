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

// common
# pragma region common 

inline float MHRand()
{
	return (float)(rand()) / (float)RAND_MAX;
}

inline float MHRand(float a, float b)
{
	return a + MHRand() * (b - a);
}

inline float XM_CALLCONV MHFresnelTerm(float CosIAngle, float RefIndex)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat(&CosIAngle);
	XMVECTOR v2 = XMLoadFloat(&RefIndex);
	XMVECTOR RF = (XMFresnelTerm(v1, v2));
	float R;
	XMStoreFloat(&R, RF);
	return R;
}

inline float MHRestrict(float val, float Min, float Max)
{
	if (val < Min) return Min;
	if (val > Max) return Max;
	return val;
}

#pragma endregion

//  ------------------------------------------------------------------------------
/// XMFLOAT2 operators
//--------------------------------------------------------------------------------
#pragma region XMFLOAT2


//  ------------------------------------------------------------------------------
///  operators
//--------------------------------------------------------------------------------
#	pragma region  operators

//------------------------------------------------------------------------------
// Comparision operators
//------------------------------------------------------------------------------

inline bool XM_CALLCONV operator== (const XMFLOAT2& V1, const XMFLOAT2& V2)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(&V1);
	XMVECTOR v2 = XMLoadFloat2(&V2);
	return XMVector2Equal(v1, v2);
}

inline bool XM_CALLCONV operator!= (const XMFLOAT2& V1, const XMFLOAT2& V2)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(&V1);
	XMVECTOR v2 = XMLoadFloat2(&V2);
	return XMVector2NotEqual(v1, v2);
}

//------------------------------------------------------------------------------
// Assignment operators
//------------------------------------------------------------------------------

inline XMFLOAT2 XM_CALLCONV operator+= (XMFLOAT2& V1, const XMFLOAT2& V2)
{
	XMVECTOR v1 = XMLoadFloat2(&V1);
	XMVECTOR v2 = XMLoadFloat2(&V2);
	XMVECTOR X = XMVectorAdd(v1, v2);
	XMStoreFloat2(&V1, X);
	return V1;
}

inline XMFLOAT2 XM_CALLCONV operator+= (XMFLOAT2& V, float S)
{
	XMVECTOR v1 = XMLoadFloat2(&V);
	XMVECTOR v2 = XMLoadFloat(&S);
	XMVECTOR X = XMVectorAdd(v1, v2);
	XMStoreFloat2(&V, X);
	return V;
}

inline XMFLOAT2 XM_CALLCONV operator+= (float S, const XMFLOAT2& V)
{
	XMVECTOR v1 = XMLoadFloat(&S);
	XMVECTOR v2 = XMLoadFloat2(&V);
	XMVECTOR X = XMVectorAdd(v1, v2);
	XMFLOAT2 R;
	XMStoreFloat2(&R, X);
	return R;
}

inline XMFLOAT2 XM_CALLCONV operator-= (XMFLOAT2& V1, const XMFLOAT2& V2)
{
	XMVECTOR v1 = XMLoadFloat2(&V1);
	XMVECTOR v2 = XMLoadFloat2(&V2);
	XMVECTOR X = XMVectorSubtract(v1, v2);
	XMStoreFloat2(&V1, X);
	return V1;
}

inline XMFLOAT2 XM_CALLCONV operator-= (XMFLOAT2& V, float S)
{
	XMVECTOR v1 = XMLoadFloat2(&V);
	XMVECTOR v2 = XMLoadFloat(&S);
	XMVECTOR X = XMVectorSubtract(v1, v2);
	XMStoreFloat2(&V, X);
	return V;
}

inline XMFLOAT2 XM_CALLCONV operator-= (float S, const XMFLOAT2& V)
{
	XMVECTOR v1 = XMLoadFloat(&S);
	XMVECTOR v2 = XMLoadFloat2(&V);
	XMVECTOR X = XMVectorSubtract(v1, v2);
	XMFLOAT2 R;
	XMStoreFloat2(&R, X);
	return R;
}

inline XMFLOAT2 XM_CALLCONV operator*= (XMFLOAT2& V1, const XMFLOAT2& V2)
{
	XMVECTOR v1 = XMLoadFloat2(&V1);
	XMVECTOR v2 = XMLoadFloat2(&V2);
	XMVECTOR X = XMVectorMultiply(v1, v2);
	XMStoreFloat2(&V1, X);
	return V1;
}

inline XMFLOAT2 XM_CALLCONV operator*= (XMFLOAT2& V, float S)
{
	XMVECTOR v1 = XMLoadFloat2(&V);
	XMVECTOR X = XMVectorScale(v1, S);
	XMStoreFloat2(&V, X);
	return V;
}

inline XMFLOAT2 XM_CALLCONV operator*= (float S, XMFLOAT2& V)
{
	XMVECTOR v1 = XMLoadFloat2(&V);
	XMVECTOR X = XMVectorScale(v1, S);
	XMStoreFloat2(&V, X);
	return V;
}

inline XMFLOAT2 XM_CALLCONV operator/= (XMFLOAT2& V1, const XMFLOAT2& V2)
{
	XMVECTOR v1 = XMLoadFloat2(&V1);
	XMVECTOR v2 = XMLoadFloat2(&V2);
	XMVECTOR X = XMVectorDivide(v1, v2);
	XMStoreFloat2(&V1, X);
	return V1;
}

inline XMFLOAT2 XM_CALLCONV operator/= (XMFLOAT2& V, float S)
{
	assert(S != 0.0f);
	XMVECTOR v1 = XMLoadFloat2(&V);
	XMVECTOR X = XMVectorScale(v1, 1.f / S);
	XMStoreFloat2(&V, X);
	return V;
}

inline XMFLOAT2 XM_CALLCONV operator/= (float S, XMFLOAT2& V)
{
	assert(S != 0.0f);
	XMVECTOR v1 = XMLoadFloat2(&V);
	XMVECTOR X = XMVectorScale(v1, 1.f / S);
	XMStoreFloat2(&V, X);
	return V;
}

//------------------------------------------------------------------------------
// Urnary operators
//------------------------------------------------------------------------------

inline XMFLOAT2 XM_CALLCONV operator+ (const XMFLOAT2& V)
{
	XMVECTOR v1 = XMLoadFloat2(&V);
	XMVECTOR X = +v1;
	XMFLOAT2 R;
	XMStoreFloat2(&R, X);
	return R;
}

inline XMFLOAT2 XM_CALLCONV operator- (const XMFLOAT2& V)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat2(&V);
	XMVECTOR X = XMVectorNegate(v1);
	XMFLOAT2 R;
	XMStoreFloat2(&R, X);
	return R;
}

//------------------------------------------------------------------------------
// Binary operators
//------------------------------------------------------------------------------

inline XMFLOAT2 XM_CALLCONV operator+ (const XMFLOAT2& V1, const XMFLOAT2& V2)
{
	XMVECTOR v1 = XMLoadFloat2(&V1);
	XMVECTOR v2 = XMLoadFloat2(&V2);
	XMVECTOR X = XMVectorAdd(v1, v2);
	XMFLOAT2 R;
	XMStoreFloat2(&R, X);
	return R;
}

inline XMFLOAT2 XM_CALLCONV operator+ (const XMFLOAT2& V, float S)
{
	XMVECTOR v1 = XMLoadFloat2(&V);
	XMVECTOR v2 = XMLoadFloat(&S);
	XMVECTOR X = XMVectorAdd(v1, v2);
	XMFLOAT2 R;
	XMStoreFloat2(&R, X);
	return R;
}

inline XMFLOAT2 XM_CALLCONV operator+ (float S, const XMFLOAT2& V)
{
	XMVECTOR v1 = XMLoadFloat(&S);
	XMVECTOR v2 = XMLoadFloat2(&V);
	XMVECTOR X = XMVectorAdd(v1, v2);
	XMFLOAT2 R;
	XMStoreFloat2(&R, X);
	return R;
}

inline XMFLOAT2 XM_CALLCONV operator- (const XMFLOAT2& V1, const XMFLOAT2& V2)
{
	XMVECTOR v1 = XMLoadFloat2(&V1);
	XMVECTOR v2 = XMLoadFloat2(&V2);
	XMVECTOR X = XMVectorSubtract(v1, v2);
	XMFLOAT2 R;
	XMStoreFloat2(&R, X);
	return R;
}

inline XMFLOAT2 XM_CALLCONV operator- (const XMFLOAT2& V, float S)
{
	XMVECTOR v1 = XMLoadFloat2(&V);
	XMVECTOR v2 = XMLoadFloat(&S);
	XMVECTOR X = XMVectorSubtract(v1, v2);
	XMFLOAT2 R;
	XMStoreFloat2(&R, X);
	return R;
}

inline XMFLOAT2 XM_CALLCONV operator- (float S, const XMFLOAT2& V)
{
	XMVECTOR v1 = XMLoadFloat(&S);
	XMVECTOR v2 = XMLoadFloat2(&V);
	XMVECTOR X = XMVectorSubtract(v1, v2);
	XMFLOAT2 R;
	XMStoreFloat2(&R, X);
	return R;
}

inline XMFLOAT2 XM_CALLCONV operator* (const XMFLOAT2& V1, const XMFLOAT2& V2)
{
	XMVECTOR v1 = XMLoadFloat2(&V1);
	XMVECTOR v2 = XMLoadFloat2(&V2);
	XMVECTOR X = XMVectorMultiply(v1, v2);
	XMFLOAT2 R;
	XMStoreFloat2(&R, X);
	return R;
}

inline XMFLOAT2 XM_CALLCONV operator* (const XMFLOAT2& V, float S)
{
	XMVECTOR v1 = XMLoadFloat2(&V);
	XMVECTOR X = XMVectorScale(v1, S);
	XMFLOAT2 R;
	XMStoreFloat2(&R, X);
	return R;
}

inline XMFLOAT2 XM_CALLCONV operator* (float S, const XMFLOAT2&V)
{
	XMVECTOR v1 = XMLoadFloat2(&V);
	XMVECTOR X = XMVectorScale(v1, S);
	XMFLOAT2 R;
	XMStoreFloat2(&R, X);
	return R;
}

inline XMFLOAT2 XM_CALLCONV operator/ (const XMFLOAT2& V1, const XMFLOAT2& V2)
{
	XMVECTOR v1 = XMLoadFloat2(&V1);
	XMVECTOR v2 = XMLoadFloat2(&V2);
	XMVECTOR X = XMVectorDivide(v1, v2);
	XMFLOAT2 R;
	XMStoreFloat2(&R, X);
	return R;
}

inline XMFLOAT2 XM_CALLCONV operator/ (const XMFLOAT2& V, float S)
{
	assert(S != 0.0f);
	XMVECTOR v1 = XMLoadFloat2(&V);
	XMVECTOR X = XMVectorScale(v1, 1.f / S);
	XMFLOAT2 R;
	XMStoreFloat2(&R, X);
	return R;
}

inline XMFLOAT2 XM_CALLCONV operator/ (float S, const XMFLOAT2& V)
{
	assert(S != 0.0f);
	XMVECTOR v1 = XMLoadFloat2(&V);
	XMVECTOR X = XMVectorScale(v1, 1.f / S);
	XMFLOAT2 R;
	XMStoreFloat2(&R, X);
	return R;
}

#	pragma endregion

#pragma endregion

//  ------------------------------------------------------------------------------
/// XMFLOAT3
//--------------------------------------------------------------------------------
#pragma region XMFLOAT3

inline XMFLOAT3 XM_CALLCONV XMMatrixForward(const XMMATRIX& m)
{
	using namespace DirectX;
	XMFLOAT4X4 float4x4;
	XMStoreFloat4x4(&float4x4, m);
	return XMFLOAT3(-float4x4._31, -float4x4._32, -float4x4._33);
}

inline XMFLOAT3 XM_CALLCONV XMMatrixBackward(const XMMATRIX& m)
{
	using namespace DirectX;
	XMFLOAT4X4 float4x4;
	XMStoreFloat4x4(&float4x4, m);
	return XMFLOAT3(float4x4._31, float4x4._32, float4x4._33);
}

inline XMFLOAT3 XM_CALLCONV XMMatrixUp(const XMMATRIX& m)
{
	using namespace DirectX;
	XMFLOAT4X4 float4x4;
	XMStoreFloat4x4(&float4x4, m);
	return XMFLOAT3(float4x4._21, float4x4._22, float4x4._23);
}

inline XMFLOAT3 XM_CALLCONV XMMatrixDown(const XMMATRIX& m)
{
	using namespace DirectX;
	XMFLOAT4X4 float4x4;
	XMStoreFloat4x4(&float4x4, m);
	return XMFLOAT3(-float4x4._21, -float4x4._22, -float4x4._23);
}

inline XMFLOAT3 XM_CALLCONV XMMatrixRight(const XMMATRIX& m)
{
	using namespace DirectX;
	XMFLOAT4X4 float4x4;
	XMStoreFloat4x4(&float4x4, m);
	return XMFLOAT3(float4x4._11, float4x4._12, float4x4._13);
}

inline XMFLOAT3 XM_CALLCONV XMMatrixLeft(const XMMATRIX& m)
{
	using namespace DirectX;
	XMFLOAT4X4 float4x4;
	XMStoreFloat4x4(&float4x4, m);
	return XMFLOAT3(-float4x4._11, -float4x4._12, -float4x4._13);
}

inline float XM_CALLCONV XMF3Dot(XMFLOAT3& a, XMFLOAT3& b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

inline float XM_CALLCONV XMF3Length(XMFLOAT3& a)
{
	return sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
}

inline XMFLOAT3 XM_CALLCONV XMF3Cross(XMFLOAT3& a, XMFLOAT3& b)
{
	using namespace DirectX;
	return XMFLOAT3((a.y*b.z) - (a.z*b.y), (a.z*b.x) - (a.x*b.z), (a.x*b.y) - (a.y*b.x));
}

inline XMFLOAT3 XM_CALLCONV XMF3Normalize(XMFLOAT3& v)
{
	using namespace DirectX;
	auto len = XMF3Length(v);
	return XMFLOAT3(v.x / len, v.y / len, v.z / len);
}

inline XMFLOAT3 XM_CALLCONV VecToXMF3(XMVECTOR& v)
{
	using namespace DirectX;
	return XMFLOAT3(XMVectorGetX(v), XMVectorGetY(v), XMVectorGetZ(v));
}

inline XMFLOAT3 XM_CALLCONV XMF3Transform(XMFLOAT3& v, XMMATRIX& m)
{
	using namespace DirectX;
	return VecToXMF3(XMVector3Transform(XMVectorSet(v.x, v.y, v.z, 1.0f), m));
}

inline XMFLOAT3 XM_CALLCONV XMF3TransformNormal(XMFLOAT3& v, XMMATRIX& m)
{
	using namespace DirectX;
	return VecToXMF3(XMVector3TransformNormal(XMVectorSet(v.x, v.y, v.z, 1.0f), m));
}

//  ------------------------------------------------------------------------------
/// operators
//--------------------------------------------------------------------------------
#	pragma region operators

//------------------------------------------------------------------------------
// Comparision operators
//------------------------------------------------------------------------------
inline bool XM_CALLCONV operator== (const XMFLOAT3& V1, const XMFLOAT3& V2)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(&V1);
	XMVECTOR v2 = XMLoadFloat3(&V2);
	return XMVector2Equal(v1, v2);
}

inline bool XM_CALLCONV operator!= (const XMFLOAT3& V1, const XMFLOAT3& V2)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(&V1);
	XMVECTOR v2 = XMLoadFloat3(&V2);
	return XMVector2NotEqual(v1, v2);
}

//------------------------------------------------------------------------------
// Assignment operators
//------------------------------------------------------------------------------

inline XMFLOAT3 XM_CALLCONV operator+= (XMFLOAT3& V1, const XMFLOAT3& V2)
{
	XMVECTOR v1 = XMLoadFloat3(&V1);
	XMVECTOR v2 = XMLoadFloat3(&V2);
	XMVECTOR X = XMVectorAdd(v1, v2);
	XMStoreFloat3(&V1, X);
	return V1;
}

inline XMFLOAT3 XM_CALLCONV operator+= (XMFLOAT3& V, float S)
{
	XMVECTOR v1 = XMLoadFloat3(&V);
	XMVECTOR v2 = XMLoadFloat(&S);
	XMVECTOR X = XMVectorAdd(v1, v2);
	XMStoreFloat3(&V, X);
	return V;
}

inline XMFLOAT3 XM_CALLCONV operator+= (float S, const XMFLOAT3& V)
{
	XMVECTOR v1 = XMLoadFloat(&S);
	XMVECTOR v2 = XMLoadFloat3(&V);
	XMVECTOR X = XMVectorAdd(v1, v2);
	XMFLOAT3 R;
	XMStoreFloat3(&R, X);
	return R;
}

inline XMFLOAT3 XM_CALLCONV operator-= (XMFLOAT3& V1, const XMFLOAT3& V2)
{
	XMVECTOR v1 = XMLoadFloat3(&V1);
	XMVECTOR v2 = XMLoadFloat3(&V2);
	XMVECTOR X = XMVectorSubtract(v1, v2);
	XMStoreFloat3(&V1, X);
	return V1;
}

inline XMFLOAT3 XM_CALLCONV operator-= (XMFLOAT3& V, float S)
{
	XMVECTOR v1 = XMLoadFloat3(&V);
	XMVECTOR v2 = XMLoadFloat(&S);
	XMVECTOR X = XMVectorSubtract(v1, v2);
	XMStoreFloat3(&V, X);
	return V;
}

inline XMFLOAT3 XM_CALLCONV operator-= (float S, const XMFLOAT3& V)
{
	XMVECTOR v1 = XMLoadFloat(&S);
	XMVECTOR v2 = XMLoadFloat3(&V);
	XMVECTOR X = XMVectorSubtract(v1, v2);
	XMFLOAT3 R;
	XMStoreFloat3(&R, X);
	return R;
}

inline XMFLOAT3 XM_CALLCONV operator*= (XMFLOAT3& V1, const XMFLOAT3& V2)
{
	XMVECTOR v1 = XMLoadFloat3(&V1);
	XMVECTOR v2 = XMLoadFloat3(&V2);
	XMVECTOR X = XMVectorMultiply(v1, v2);
	XMStoreFloat3(&V1, X);
	return V1;
}

inline XMFLOAT3 XM_CALLCONV operator*= (XMFLOAT3& V, float S)
{
	XMVECTOR v1 = XMLoadFloat3(&V);
	XMVECTOR X = XMVectorScale(v1, S);
	XMStoreFloat3(&V, X);
	return V;
}

inline XMFLOAT3 XM_CALLCONV operator*= (float S, XMFLOAT3& V)
{
	XMVECTOR v1 = XMLoadFloat3(&V);
	XMVECTOR X = XMVectorScale(v1, S);
	XMStoreFloat3(&V, X);
	return V;
}

inline XMFLOAT3 XM_CALLCONV operator/= (XMFLOAT3& V1, const XMFLOAT3& V2)
{
	XMVECTOR v1 = XMLoadFloat3(&V1);
	XMVECTOR v2 = XMLoadFloat3(&V2);
	XMVECTOR X = XMVectorDivide(v1, v2);
	XMStoreFloat3(&V1, X);
	return V1;
}

inline XMFLOAT3 XM_CALLCONV operator/= (XMFLOAT3& V, float S)
{
	assert(S != 0.0f);
	XMVECTOR v1 = XMLoadFloat3(&V);
	XMVECTOR X = XMVectorScale(v1, 1.f / S);
	XMStoreFloat3(&V, X);
	return V;
}

inline XMFLOAT3 XM_CALLCONV operator/= (float S, XMFLOAT3& V)
{
	assert(S != 0.0f);
	XMVECTOR v1 = XMLoadFloat3(&V);
	XMVECTOR X = XMVectorScale(v1, 1.f / S);
	XMStoreFloat3(&V, X);
	return V;
}

//------------------------------------------------------------------------------
// Urnary operators
//------------------------------------------------------------------------------

inline XMFLOAT3 XM_CALLCONV operator+ (const XMFLOAT3& V)
{
	XMVECTOR v1 = XMLoadFloat3(&V);
	XMVECTOR X = +v1;
	XMFLOAT3 R;
	XMStoreFloat3(&R, X);
	return R;
}

inline XMFLOAT3 XM_CALLCONV operator- (const XMFLOAT3& V)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat3(&V);
	XMVECTOR X = XMVectorNegate(v1);
	XMFLOAT3 R;
	XMStoreFloat3(&R, X);
	return R;
}

//------------------------------------------------------------------------------
// Binary operators
//------------------------------------------------------------------------------

inline XMFLOAT3 XM_CALLCONV operator+ (const XMFLOAT3& V1, const XMFLOAT3& V2)
{
	XMVECTOR v1 = XMLoadFloat3(&V1);
	XMVECTOR v2 = XMLoadFloat3(&V2);
	XMVECTOR X = XMVectorAdd(v1, v2);
	XMFLOAT3 R;
	XMStoreFloat3(&R, X);
	return R;
}

inline XMFLOAT3 XM_CALLCONV operator+ (const XMFLOAT3& V, float S)
{
	XMVECTOR v1 = XMLoadFloat3(&V);
	XMVECTOR v2 = XMLoadFloat(&S);
	XMVECTOR X = XMVectorAdd(v1, v2);
	XMFLOAT3 R;
	XMStoreFloat3(&R, X);
	return R;
}

inline XMFLOAT3 XM_CALLCONV operator+ (float S, const XMFLOAT3& V)
{
	XMVECTOR v1 = XMLoadFloat(&S);
	XMVECTOR v2 = XMLoadFloat3(&V);
	XMVECTOR X = XMVectorAdd(v1, v2);
	XMFLOAT3 R;
	XMStoreFloat3(&R, X);
	return R;
}

inline XMFLOAT3 XM_CALLCONV operator- (const XMFLOAT3& V1, const XMFLOAT3& V2)
{
	XMVECTOR v1 = XMLoadFloat3(&V1);
	XMVECTOR v2 = XMLoadFloat3(&V2);
	XMVECTOR X = XMVectorSubtract(v1, v2);
	XMFLOAT3 R;
	XMStoreFloat3(&R, X);
	return R;
}

inline XMFLOAT3 XM_CALLCONV operator- (const XMFLOAT3& V, float S)
{
	XMVECTOR v1 = XMLoadFloat3(&V);
	XMVECTOR v2 = XMLoadFloat(&S);
	XMVECTOR X = XMVectorSubtract(v1, v2);
	XMFLOAT3 R;
	XMStoreFloat3(&R, X);
	return R;
}

inline XMFLOAT3 XM_CALLCONV operator- (float S, const XMFLOAT3& V)
{
	XMVECTOR v1 = XMLoadFloat(&S);
	XMVECTOR v2 = XMLoadFloat3(&V);
	XMVECTOR X = XMVectorSubtract(v1, v2);
	XMFLOAT3 R;
	XMStoreFloat3(&R, X);
	return R;
}

inline XMFLOAT3 XM_CALLCONV operator* (const XMFLOAT3& V1, const XMFLOAT3& V2)
{
	XMVECTOR v1 = XMLoadFloat3(&V1);
	XMVECTOR v2 = XMLoadFloat3(&V2);
	XMVECTOR X = XMVectorMultiply(v1, v2);
	XMFLOAT3 R;
	XMStoreFloat3(&R, X);
	return R;
}

inline XMFLOAT3 XM_CALLCONV operator* (const XMFLOAT3& V, float S)
{
	XMVECTOR v1 = XMLoadFloat3(&V);
	XMVECTOR X = XMVectorScale(v1, S);
	XMFLOAT3 R;
	XMStoreFloat3(&R, X);
	return R;
}

inline XMFLOAT3 XM_CALLCONV operator* (float S, const XMFLOAT3&V)
{
	XMVECTOR v1 = XMLoadFloat3(&V);
	XMVECTOR X = XMVectorScale(v1, S);
	XMFLOAT3 R;
	XMStoreFloat3(&R, X);
	return R;
}

inline XMFLOAT3 XM_CALLCONV operator/ (const XMFLOAT3& V1, const XMFLOAT3& V2)
{
	XMVECTOR v1 = XMLoadFloat3(&V1);
	XMVECTOR v2 = XMLoadFloat3(&V2);
	XMVECTOR X = XMVectorDivide(v1, v2);
	XMFLOAT3 R;
	XMStoreFloat3(&R, X);
	return R;
}

inline XMFLOAT3 XM_CALLCONV operator/ (const XMFLOAT3& V, float S)
{
	assert(S != 0.0f);
	XMVECTOR v1 = XMLoadFloat3(&V);
	XMVECTOR X = XMVectorScale(v1, 1.f / S);
	XMFLOAT3 R;
	XMStoreFloat3(&R, X);
	return R;
}

inline XMFLOAT3 XM_CALLCONV operator/ (float S, const XMFLOAT3& V)
{
	assert(S != 0.0f);
	XMVECTOR v1 = XMLoadFloat3(&V);
	XMVECTOR X = XMVectorScale(v1, 1.f / S);
	XMFLOAT3 R;
	XMStoreFloat3(&R, X);
	return R;
}

#	pragma endregion

#pragma endregion

//  ------------------------------------------------------------------------------
/// XMFLOAT4
//--------------------------------------------------------------------------------
# pragma region XMFLOAT4

inline XMFLOAT4 XM_CALLCONV VecToXMF4(XMVECTOR& v)
{
	using namespace DirectX;
	return XMFLOAT4(XMVectorGetX(v), XMVectorGetY(v)
		, XMVectorGetZ(v), XMVectorGetW(v));
}

inline XMFLOAT4 XM_CALLCONV XMF3Transform(XMFLOAT4& f, XMMATRIX& m)
{
	return VecToXMF4(XMVector3Transform(XMVectorSet(f.x, f.y, f.z, f.w), m));
}

inline XMFLOAT4 XM_CALLCONV XMF3TransformNormal(XMFLOAT4& f, XMMATRIX& m)
{
	using namespace DirectX;
	return VecToXMF4(XMVector3TransformNormal(XMVectorSet(f.x, f.y, f.z, f.w), m));
}

//  ------------------------------------------------------------------------------
/// operators
//--------------------------------------------------------------------------------
#	pragma region operators

//------------------------------------------------------------------------------
// Comparision operators
//------------------------------------------------------------------------------
inline bool XM_CALLCONV operator== (const XMFLOAT4& V1, const XMFLOAT4& V2)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(&V1);
	XMVECTOR v2 = XMLoadFloat4(&V2);
	return XMVector2Equal(v1, v2);
}

inline bool XM_CALLCONV operator!= (const XMFLOAT4& V1, const XMFLOAT4& V2)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(&V1);
	XMVECTOR v2 = XMLoadFloat4(&V2);
	return XMVector2NotEqual(v1, v2);
}

//------------------------------------------------------------------------------
// Assignment operators
//------------------------------------------------------------------------------

inline XMFLOAT4 XM_CALLCONV operator+= (XMFLOAT4& V1, const XMFLOAT4& V2)
{
	XMVECTOR v1 = XMLoadFloat4(&V1);
	XMVECTOR v2 = XMLoadFloat4(&V2);
	XMVECTOR X = XMVectorAdd(v1, v2);
	XMStoreFloat4(&V1, X);
	return V1;
}

inline XMFLOAT4 XM_CALLCONV operator+= (XMFLOAT4& V, float S)
{
	XMVECTOR v1 = XMLoadFloat4(&V);
	XMVECTOR v2 = XMLoadFloat(&S);
	XMVECTOR X = XMVectorAdd(v1, v2);
	XMStoreFloat4(&V, X);
	return V;
}

inline XMFLOAT4 XM_CALLCONV operator+= (float S, const XMFLOAT4& V)
{
	XMVECTOR v1 = XMLoadFloat(&S);
	XMVECTOR v2 = XMLoadFloat4(&V);
	XMVECTOR X = XMVectorAdd(v1, v2);
	XMFLOAT4 R;
	XMStoreFloat4(&R, X);
	return R;
}

inline XMFLOAT4 XM_CALLCONV operator-= (XMFLOAT4& V1, const XMFLOAT4& V2)
{
	XMVECTOR v1 = XMLoadFloat4(&V1);
	XMVECTOR v2 = XMLoadFloat4(&V2);
	XMVECTOR X = XMVectorSubtract(v1, v2);
	XMStoreFloat4(&V1, X);
	return V1;
}

inline XMFLOAT4 XM_CALLCONV operator-= (XMFLOAT4& V, float S)
{
	XMVECTOR v1 = XMLoadFloat4(&V);
	XMVECTOR v2 = XMLoadFloat(&S);
	XMVECTOR X = XMVectorSubtract(v1, v2);
	XMStoreFloat4(&V, X);
	return V;
}

inline XMFLOAT4 XM_CALLCONV operator-= (float S, const XMFLOAT4& V)
{
	XMVECTOR v1 = XMLoadFloat(&S);
	XMVECTOR v2 = XMLoadFloat4(&V);
	XMVECTOR X = XMVectorSubtract(v1, v2);
	XMFLOAT4 R;
	XMStoreFloat4(&R, X);
	return R;
}

inline XMFLOAT4 XM_CALLCONV operator*= (XMFLOAT4& V1, const XMFLOAT4& V2)
{
	XMVECTOR v1 = XMLoadFloat4(&V1);
	XMVECTOR v2 = XMLoadFloat4(&V2);
	XMVECTOR X = XMVectorMultiply(v1, v2);
	XMStoreFloat4(&V1, X);
	return V1;
}

inline XMFLOAT4 XM_CALLCONV operator*= (XMFLOAT4& V, float S)
{
	XMVECTOR v1 = XMLoadFloat4(&V);
	XMVECTOR X = XMVectorScale(v1, S);
	XMStoreFloat4(&V, X);
	return V;
}

inline XMFLOAT4 XM_CALLCONV operator*= (float S, XMFLOAT4& V)
{
	XMVECTOR v1 = XMLoadFloat4(&V);
	XMVECTOR X = XMVectorScale(v1, S);
	XMStoreFloat4(&V, X);
	return V;
}

inline XMFLOAT4 XM_CALLCONV operator/= (XMFLOAT4& V1, const XMFLOAT4& V2)
{
	XMVECTOR v1 = XMLoadFloat4(&V1);
	XMVECTOR v2 = XMLoadFloat4(&V2);
	XMVECTOR X = XMVectorDivide(v1, v2);
	XMStoreFloat4(&V1, X);
	return V1;
}

inline XMFLOAT4 XM_CALLCONV operator/= (XMFLOAT4& V, float S)
{
	assert(S != 0.0f);
	XMVECTOR v1 = XMLoadFloat4(&V);
	XMVECTOR X = XMVectorScale(v1, 1.f / S);
	XMStoreFloat4(&V, X);
	return V;
}

inline XMFLOAT4 XM_CALLCONV operator/= (float S, XMFLOAT4& V)
{
	assert(S != 0.0f);
	XMVECTOR v1 = XMLoadFloat4(&V);
	XMVECTOR X = XMVectorScale(v1, 1.f / S);
	XMStoreFloat4(&V, X);
	return V;
}

//------------------------------------------------------------------------------
// Urnary operators
//------------------------------------------------------------------------------

inline XMFLOAT4 XM_CALLCONV operator+ (const XMFLOAT4& V)
{
	XMVECTOR v1 = XMLoadFloat4(&V);
	XMVECTOR X = +v1;
	XMFLOAT4 R;
	XMStoreFloat4(&R, X);
	return R;
}

inline XMFLOAT4 XM_CALLCONV operator- (const XMFLOAT4& V)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(&V);
	XMVECTOR X = XMVectorNegate(v1);
	XMFLOAT4 R;
	XMStoreFloat4(&R, X);
	return R;
}

//------------------------------------------------------------------------------
// Binary operators
//------------------------------------------------------------------------------

inline XMFLOAT4 XM_CALLCONV operator+ (const XMFLOAT4& V1, const XMFLOAT4& V2)
{
	XMVECTOR v1 = XMLoadFloat4(&V1);
	XMVECTOR v2 = XMLoadFloat4(&V2);
	XMVECTOR X = XMVectorAdd(v1, v2);
	XMFLOAT4 R;
	XMStoreFloat4(&R, X);
	return R;
}

inline XMFLOAT4 XM_CALLCONV operator+ (const XMFLOAT4& V, float S)
{
	XMVECTOR v1 = XMLoadFloat4(&V);
	XMVECTOR v2 = XMLoadFloat(&S);
	XMVECTOR X = XMVectorAdd(v1, v2);
	XMFLOAT4 R;
	XMStoreFloat4(&R, X);
	return R;
}

inline XMFLOAT4 XM_CALLCONV operator+ (float S, const XMFLOAT4& V)
{
	XMVECTOR v1 = XMLoadFloat(&S);
	XMVECTOR v2 = XMLoadFloat4(&V);
	XMVECTOR X = XMVectorAdd(v1, v2);
	XMFLOAT4 R;
	XMStoreFloat4(&R, X);
	return R;
}

inline XMFLOAT4 XM_CALLCONV operator- (const XMFLOAT4& V1, const XMFLOAT4& V2)
{
	XMVECTOR v1 = XMLoadFloat4(&V1);
	XMVECTOR v2 = XMLoadFloat4(&V2);
	XMVECTOR X = XMVectorSubtract(v1, v2);
	XMFLOAT4 R;
	XMStoreFloat4(&R, X);
	return R;
}

inline XMFLOAT4 XM_CALLCONV operator- (const XMFLOAT4& V, float S)
{
	XMVECTOR v1 = XMLoadFloat4(&V);
	XMVECTOR v2 = XMLoadFloat(&S);
	XMVECTOR X = XMVectorSubtract(v1, v2);
	XMFLOAT4 R;
	XMStoreFloat4(&R, X);
	return R;
}

inline XMFLOAT4 XM_CALLCONV operator- (float S, const XMFLOAT4& V)
{
	XMVECTOR v1 = XMLoadFloat(&S);
	XMVECTOR v2 = XMLoadFloat4(&V);
	XMVECTOR X = XMVectorSubtract(v1, v2);
	XMFLOAT4 R;
	XMStoreFloat4(&R, X);
	return R;
}

inline XMFLOAT4 XM_CALLCONV operator* (const XMFLOAT4& V1, const XMFLOAT4& V2)
{
	XMVECTOR v1 = XMLoadFloat4(&V1);
	XMVECTOR v2 = XMLoadFloat4(&V2);
	XMVECTOR X = XMVectorMultiply(v1, v2);
	XMFLOAT4 R;
	XMStoreFloat4(&R, X);
	return R;
}

inline XMFLOAT4 XM_CALLCONV operator* (const XMFLOAT4& V, float S)
{
	XMVECTOR v1 = XMLoadFloat4(&V);
	XMVECTOR X = XMVectorScale(v1, S);
	XMFLOAT4 R;
	XMStoreFloat4(&R, X);
	return R;
}

inline XMFLOAT4 XM_CALLCONV operator* (float S, const XMFLOAT4&V)
{
	XMVECTOR v1 = XMLoadFloat4(&V);
	XMVECTOR X = XMVectorScale(v1, S);
	XMFLOAT4 R;
	XMStoreFloat4(&R, X);
	return R;
}

inline XMFLOAT4 XM_CALLCONV operator/ (const XMFLOAT4& V1, const XMFLOAT4& V2)
{
	XMVECTOR v1 = XMLoadFloat4(&V1);
	XMVECTOR v2 = XMLoadFloat4(&V2);
	XMVECTOR X = XMVectorDivide(v1, v2);
	XMFLOAT4 R;
	XMStoreFloat4(&R, X);
	return R;
}

inline XMFLOAT4 XM_CALLCONV operator/ (const XMFLOAT4& V, float S)
{
	assert(S != 0.0f);
	XMVECTOR v1 = XMLoadFloat4(&V);
	XMVECTOR X = XMVectorScale(v1, 1.f / S);
	XMFLOAT4 R;
	XMStoreFloat4(&R, X);
	return R;
}

inline XMFLOAT4 XM_CALLCONV operator/ (float S, const XMFLOAT4& V)
{
	assert(S != 0.0f);
	XMVECTOR v1 = XMLoadFloat4(&V);
	XMVECTOR X = XMVectorScale(v1, 1.f / S);
	XMFLOAT4 R;
	XMStoreFloat4(&R, X);
	return R;
}

#	pragma endregion

# pragma endregion

#ifdef __cplusplus
EXTERN_CC_END
#endif
