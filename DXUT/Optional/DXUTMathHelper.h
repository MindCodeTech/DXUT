//--------------------------------------------------------------------------------------
// File: DXUTMathHelper.h
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

namespace_DXUT
namespace_MathHelper


class DXUTAPI CMathHelper
{
public:

/*
	// Returns random float in [0, 1).
	inline static float SRand()
	{
		return (float)(rand()) / (float)RAND_MAX;
	}

	// Retstatic urns random float in [a, b).
	inline static float SRand(float a, float b)
	{
		return a + SRand()*(b - a);
	}
*/

	// Returns random float in [0, 1).
	inline static float Rand()
	{
		return (float)(rand()) / (float)RAND_MAX;
	}

	// Returns random float in [a, b).
	inline static float Rand(float a, float b)
	{
		return a + Rand()*(b - a);
	}

	inline static float Restrict(float val, float Min, float Max)
	{
		if (val < Min) return Min;
		if (val > Max) return Max;
		return val;
	}

	inline static float XM_CALLCONV Dot(const DirectX::XMFLOAT3& a, const DirectX::XMFLOAT3& b)
	{
		return a.x * b.x + a.y * b.y + a.z * b.z;
	}

	inline static float XM_CALLCONV Length(const DirectX::XMFLOAT3& a)
	{
		return sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
	}

	inline static DirectX::XMFLOAT3 XM_CALLCONV Cross(const DirectX::XMFLOAT3& a, const DirectX::XMFLOAT3& b)
	{
		return DirectX::XMFLOAT3((a.y*b.z) - (a.z*b.y), (a.z*b.x) - (a.x*b.z), (a.x*b.y) - (a.y*b.x));
	}

	inline static DirectX::XMFLOAT3 XM_CALLCONV Normalize(const DirectX::XMFLOAT3& v)
	{
		auto len = Length(v);
		return DirectX::XMFLOAT3(v.x / len, v.y / len, v.z / len);
	}

	inline static DirectX::XMFLOAT2 XM_CALLCONV VectorToFloat2(const DirectX::XMVECTOR& v)
	{
		return DirectX::XMFLOAT2(DirectX::XMVectorGetX(v), DirectX::XMVectorGetY(v));
	}

	inline static DirectX::XMFLOAT3 XM_CALLCONV VectorToFloat3(const DirectX::XMVECTOR& v)
	{
		return DirectX::XMFLOAT3(DirectX::XMVectorGetX(v), DirectX::XMVectorGetY(v), DirectX::XMVectorGetZ(v));
	}

	inline static DirectX::XMFLOAT4 XM_CALLCONV VectorToFloat4(const DirectX::XMVECTOR& v)
	{
		return DirectX::XMFLOAT4(DirectX::XMVectorGetX(v), DirectX::XMVectorGetY(v)
			, DirectX::XMVectorGetZ(v), DirectX::XMVectorGetW(v));
	}

	inline static DirectX::XMFLOAT3 XM_CALLCONV Transform(const DirectX::XMFLOAT3& v, const DirectX::XMMATRIX& m)
	{
		return VectorToFloat3(DirectX::XMVector3Transform(DirectX::XMVectorSet(v.x, v.y, v.z, 1.0f), m));
	}

	inline static DirectX::XMFLOAT4 XM_CALLCONV Transform(const DirectX::XMFLOAT4& f, const DirectX::XMMATRIX& m)
	{
		return VectorToFloat4(DirectX::XMVector3Transform(DirectX::XMVectorSet(f.x, f.y, f.z, f.w), m));
	}

	inline static DirectX::XMFLOAT3 XM_CALLCONV TransformNormal(const DirectX::XMFLOAT3& v, const DirectX::XMMATRIX& m)
	{
		return VectorToFloat3(DirectX::XMVector3TransformNormal(DirectX::XMVectorSet(v.x, v.y, v.z, 1.0f), m));
	}

	inline static DirectX::XMFLOAT4 XM_CALLCONV TransformNormal(const DirectX::XMFLOAT4& f, const DirectX::XMMATRIX& m)
	{
		return VectorToFloat4(DirectX::XMVector3TransformNormal(DirectX::XMVectorSet(f.x, f.y, f.z, f.w), m));
	}

	inline static DirectX::XMFLOAT3 XM_CALLCONV XMMatrixForward(const DirectX::XMMATRIX& m)
	{
		DirectX::XMFLOAT4X4 float4x4;
		DirectX::XMStoreFloat4x4(&float4x4, m);
		return DirectX::XMFLOAT3(-float4x4._31, -float4x4._32, -float4x4._33);
	}
	
	inline static DirectX::XMFLOAT3 XM_CALLCONV XMMatrixBackward(const DirectX::XMMATRIX& m)
	{
		DirectX::XMFLOAT4X4 float4x4;
		DirectX::XMStoreFloat4x4(&float4x4, m);
		return DirectX::XMFLOAT3(float4x4._31, float4x4._32, float4x4._33);
	}

	inline static DirectX::XMFLOAT3 XM_CALLCONV XMMatrixUp(const DirectX::XMMATRIX& m)
	{
		DirectX::XMFLOAT4X4 float4x4;
		DirectX::XMStoreFloat4x4(&float4x4, m);
		return DirectX::XMFLOAT3(float4x4._21, float4x4._22, float4x4._23);
	}

	inline static DirectX::XMFLOAT3 XM_CALLCONV XMMatrixDown(const DirectX::XMMATRIX& m)
	{
		DirectX::XMFLOAT4X4 float4x4;
		DirectX::XMStoreFloat4x4(&float4x4, m);
		return DirectX::XMFLOAT3(-float4x4._21, -float4x4._22, -float4x4._23);
	}

	inline static DirectX::XMFLOAT3 XM_CALLCONV XMMatrixRight(const DirectX::XMMATRIX& m)
	{
		DirectX::XMFLOAT4X4 float4x4;
		DirectX::XMStoreFloat4x4(&float4x4, m);
		return DirectX::XMFLOAT3(float4x4._11, float4x4._12, float4x4._13);
	}

	inline static DirectX::XMFLOAT3 XM_CALLCONV XMMatrixLeft(const DirectX::XMMATRIX& m)
	{
		DirectX::XMFLOAT4X4 float4x4;
		DirectX::XMStoreFloat4x4(&float4x4, m);
		return DirectX::XMFLOAT3(-float4x4._11, -float4x4._12, -float4x4._13);
	}

	template<typename T>
	inline static T Min(const T& a, const T& b)
	{
		return a < b ? a : b;
	}

	template<typename T>
	inline static T Max(const T& a, const T& b)
	{
		return a > b ? a : b;
	}

	template<typename T>
	inline static T Lerp(const T& a, const T& b, float t)
	{
		return a + (b - a)*t;
	}

	template<typename T>
	inline static T Clamp(const T& x, const T& low, const T& high)
	{
		return x < low ? low : (x > high ? high : x);
	}

	// Returns the polar angle of the point (x,y) in [0, 2*PI).
	static float AngleFromXY(float x, float y);

	inline static DirectX::XMMATRIX InverseTranspose(const CXMMATRIX M)
	{
		// Inverse-transpose is just applied to normals.  So zero out
		// translation row so that it doesn't get into our inverse-transpose
		// calculation--we don't want the inverse-transpose of the translation.
		DirectX::XMMATRIX A = M;
		A.r[3] = XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);

		DirectX::XMVECTOR det = XMMatrixDeterminant(A);
		return XMMatrixTranspose(XMMatrixInverse(&det, A));
	}

	inline static DirectX::XMVECTOR RandUnitVec3();
	inline static DirectX::XMVECTOR RandHemisphereUnitVec3(const XMVECTOR n);

	/*
	static const float Infinity;
	static const float Pi;*/

	}; // !CMathHelper

namespace_MathHelper_end
namespace_DXUT_end

#ifdef __cplusplus
EXTERN_CC_END
#endif
