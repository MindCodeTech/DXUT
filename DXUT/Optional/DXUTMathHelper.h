//***************************************************************************************
// DXUTMathHelper.h - Original by Frank Luna (C) 2011 All Rights Reserved.
//
//***************************************************************************************

#ifdef _MSC_VER
#pragma once
#endif

#ifdef __cplusplus
EXTERN_C_BEGIN
#endif

NAMESPACE_DXUT
NAMESPACE_MathHelper


class DXUTAPI CMathHelper
{
public:

	// Returns random float in [0, 1).
	static inline float SRand()
	{
		return (float)(rand()) / (float)RAND_MAX;
	}

	// Retstatic urns random float in [a, b).
	static inline float SRand(float a, float b)
	{
		return a + SRand()*(b - a);
	}

	// Returns random float in [0, 1).
	inline float Rand()
	{
		return (float)(rand()) / (float)RAND_MAX;
	}

	// Retstatic urns random float in [a, b).
	inline float Rand(float a, float b)
	{
		return a + Rand()*(b - a);
	}

	inline float Restrict(float val, float Min, float Max)
	{
		if (val < Min) return Min;
		if (val > Max) return Max;
		return val;
	}

	inline float Dot(DirectX::XMFLOAT3& a, DirectX::XMFLOAT3& b)
	{
		return a.x * b.x + a.y * b.y + a.z * b.z;
	}

	inline float Length(DirectX::XMFLOAT3& a)
	{
		return sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
	}

	inline DirectX::XMFLOAT3 Cross(DirectX::XMFLOAT3& a, DirectX::XMFLOAT3& b)
	{
		return DirectX::XMFLOAT3((a.y*b.z) - (a.z*b.y), (a.z*b.x) - (a.x*b.z), (a.x*b.y) - (a.y*b.x));
	}

	inline DirectX::XMFLOAT3 Normalize(DirectX::XMFLOAT3& v)
	{
		auto len = Length(v);
		return DirectX::XMFLOAT3(v.x / len, v.y / len, v.z / len);
	}

	inline DirectX::XMFLOAT3 VectorToFloat3(DirectX::XMVECTOR& v)
	{
		return DirectX::XMFLOAT3(DirectX::XMVectorGetX(v), DirectX::XMVectorGetY(v), DirectX::XMVectorGetZ(v));
	}

	inline DirectX::XMFLOAT4 VectorToFloat4(DirectX::XMVECTOR& v)
	{
		return DirectX::XMFLOAT4(DirectX::XMVectorGetX(v), DirectX::XMVectorGetY(v)
			, DirectX::XMVectorGetZ(v), DirectX::XMVectorGetW(v));
	}

	inline DirectX::XMFLOAT3 Transform(DirectX::XMFLOAT3& v, DirectX::XMMATRIX& m)
	{
		return VectorToFloat3(DirectX::XMVector3Transform(DirectX::XMVectorSet(v.x, v.y, v.z, 1.0f), m));
	}

	inline DirectX::XMFLOAT4 Transform(DirectX::XMFLOAT4& f, DirectX::XMMATRIX& m)
	{
		return VectorToFloat4(DirectX::XMVector3Transform(DirectX::XMVectorSet(f.x, f.y, f.z, f.w), m));
	}

	inline DirectX::XMFLOAT3 TransformNormal(DirectX::XMFLOAT3& v, DirectX::XMMATRIX& m)
	{
		return VectorToFloat3(DirectX::XMVector3TransformNormal(DirectX::XMVectorSet(v.x, v.y, v.z, 1.0f), m));
	}

	inline DirectX::XMFLOAT4 TransformNormal(DirectX::XMFLOAT4& f, DirectX::XMMATRIX& m)
	{
		return VectorToFloat4(DirectX::XMVector3TransformNormal(DirectX::XMVectorSet(f.x, f.y, f.z, f.w), m));
	}

	inline DirectX::XMFLOAT3 XMMatrixForward(DirectX::XMMATRIX& m)
	{
		DirectX::XMFLOAT4X4 float4x4;
		DirectX::XMStoreFloat4x4(&float4x4, m);
		return DirectX::XMFLOAT3(-float4x4._31, -float4x4._32, -float4x4._33);
	}

	inline DirectX::XMFLOAT3 XMMatrixUp(DirectX::XMMATRIX& m)
	{
		DirectX::XMFLOAT4X4 float4x4;
		DirectX::XMStoreFloat4x4(&float4x4, m);
		return DirectX::XMFLOAT3(float4x4._21, float4x4._22, float4x4._23);
	}

	inline DirectX::XMFLOAT3 XMMatrixLeft(DirectX::XMMATRIX& m)
	{
		DirectX::XMFLOAT4X4 float4x4;
		DirectX::XMStoreFloat4x4(&float4x4, m);
		return DirectX::XMFLOAT3(-float4x4._11, -float4x4._12, -float4x4._13);
	}

	template<typename T>
	inline T Min(const T& a, const T& b)
	{
		return a < b ? a : b;
	}

	template<typename T>
	inline T Max(const T& a, const T& b)
	{
		return a > b ? a : b;
	}

	template<typename T>
	inline T Lerp(const T& a, const T& b, float t)
	{
		return a + (b - a)*t;
	}

	template<typename T>
	inline T Clamp(const T& x, const T& low, const T& high)
	{
		return x < low ? low : (x > high ? high : x);
	}

	// Returns the polar angle of the point (x,y) in [0, 2*PI).
	inline float AngleFromXY(float x, float y);

	inline DirectX::XMMATRIX InverseTranspose(CXMMATRIX M)
	{
		// Inverse-transpose is just applied to normals.  So zero out
		// translation row so that it doesn't get into our inverse-transpose
		// calculation--we don't want the inverse-transpose of the translation.
		DirectX::XMMATRIX A = M;
		A.r[3] = XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);

		DirectX::XMVECTOR det = XMMatrixDeterminant(A);
		return XMMatrixTranspose(XMMatrixInverse(&det, A));
	}

	inline DirectX::XMVECTOR RandUnitVec3();
	inline DirectX::XMVECTOR RandHemisphereUnitVec3(XMVECTOR n);

	/*
	static const float Infinity;
	static const float Pi;*/

	}; // !CMathHelper


	inline bool operator == (DirectX::XMFLOAT2 a, DirectX::XMFLOAT2 b)
	{
		return a.x == b.x && a.y;
	}

	inline bool operator != (DirectX::XMFLOAT2 a, DirectX::XMFLOAT2 b)
	{
		return a.x != b.x || a.y != b.y;
	}

	inline DirectX::XMFLOAT2 operator + (DirectX::XMFLOAT2 a, DirectX::XMFLOAT2 b)
	{
		return DirectX::XMFLOAT2(a.x + b.x, a.y + b.y);
	}

	inline DirectX::XMFLOAT2 operator - (DirectX::XMFLOAT2 a, DirectX::XMFLOAT2 b)
	{
		return DirectX::XMFLOAT2(a.x - b.x, a.y - b.y);
	}

	inline DirectX::XMFLOAT2 operator * (DirectX::XMFLOAT2 a, DirectX::XMFLOAT2 b)
	{
		return DirectX::XMFLOAT2(a.x * b.x, a.y * b.y);
	}

	inline DirectX::XMFLOAT2 operator * (float a, DirectX::XMFLOAT2 b)
	{
		return DirectX::XMFLOAT2(a * b.x, a * b.y);
	}

	inline DirectX::XMFLOAT2 operator * (DirectX::XMFLOAT2 a, float b)
	{
		return DirectX::XMFLOAT2(a.x * b, a.y * b);
	}

	inline DirectX::XMFLOAT2 operator / (DirectX::XMFLOAT2 a, DirectX::XMFLOAT2 b)
	{
		try
		{
			return DirectX::XMFLOAT2(a.x / b.x, a.y / b.y);
		}
		catch (...)
		{
			throw "Logical error : Divide by zero";
		}
	}

	inline DirectX::XMFLOAT2 operator / (DirectX::XMFLOAT2 a, float b)
	{
		try
		{
			return DirectX::XMFLOAT2(a.x / b, a.y);
		}
		catch (...)
		{
			throw "Logical error : Divide by zero";
		}
	}


	inline bool operator == (DirectX::XMFLOAT3 a, DirectX::XMFLOAT3 b)
	{
		return a.x == b.x && a.y == b.y && a.z == b.z;
	}

	inline bool operator != (DirectX::XMFLOAT3 a, DirectX::XMFLOAT3 b)
	{
		return a.x != b.x || a.y != b.y || a.z != b.z;
	}

	inline DirectX::XMFLOAT3 operator + (DirectX::XMFLOAT3 a, DirectX::XMFLOAT3 b)
	{
		return DirectX::XMFLOAT3(a.x + b.x, a.y + b.y, a.z + b.z);
	}

	inline DirectX::XMFLOAT3 operator - (DirectX::XMFLOAT3 a, DirectX::XMFLOAT3 b)
	{
		return DirectX::XMFLOAT3(a.x - b.x, a.y - b.y, a.z - b.z);
	}

	inline DirectX::XMFLOAT3 operator * (DirectX::XMFLOAT3 a, DirectX::XMFLOAT3 b)
	{
		return DirectX::XMFLOAT3(a.x * b.x, a.y * b.y, a.z * b.z);
	}

	inline DirectX::XMFLOAT3 operator * (float a, DirectX::XMFLOAT3 b)
	{
		return DirectX::XMFLOAT3(a * b.x, a * b.y, a * b.z);
	}

	inline DirectX::XMFLOAT3 operator * (DirectX::XMFLOAT3 a, float b)
	{
		return DirectX::XMFLOAT3(a.x * b, a.y * b, a.z * b);
	}

	inline DirectX::XMFLOAT3 operator / (DirectX::XMFLOAT3 a, DirectX::XMFLOAT3 b)
	{
		try
		{
			return DirectX::XMFLOAT3(a.x / b.x, a.y / b.y, a.z / b.z);
		}
		catch (...)
		{
			throw "Logical error : Divide by zero";
		}
	}

	inline DirectX::XMFLOAT3 operator / (DirectX::XMFLOAT3 a, float b)
	{
		try
		{
			return DirectX::XMFLOAT3(a.x / b, a.y / b, a.z / b);
		}
		catch (...)
		{
			throw "Logical error : Divide by zero";
		}
	}


	inline bool operator == (DirectX::XMFLOAT4 a, DirectX::XMFLOAT4 b)
	{
		return a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w;
	}

	inline bool operator != (DirectX::XMFLOAT4 a, DirectX::XMFLOAT4 b)
	{
		return a.x != b.x || a.y != b.y || a.z != b.z || a.w != b.w;
	}

	inline DirectX::XMFLOAT4 operator + (DirectX::XMFLOAT4 a, DirectX::XMFLOAT4 b)
	{
		return DirectX::XMFLOAT4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
	}

	inline DirectX::XMFLOAT4 operator - (DirectX::XMFLOAT4 a, DirectX::XMFLOAT4 b)
	{
		return DirectX::XMFLOAT4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
	}

	inline DirectX::XMFLOAT4 operator * (DirectX::XMFLOAT4 a, DirectX::XMFLOAT4 b)
	{
		return DirectX::XMFLOAT4(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
	}

	inline DirectX::XMFLOAT4 operator * (float a, DirectX::XMFLOAT4 b)
	{
		return DirectX::XMFLOAT4(a * b.x, a * b.y, a * b.z, a * b.w);
	}

	inline DirectX::XMFLOAT4 operator * (DirectX::XMFLOAT4 a, float b)
	{
		return DirectX::XMFLOAT4(a.x * b, a.y * b, a.z * b, a.w * b);
	}

	inline DirectX::XMFLOAT4 operator / (DirectX::XMFLOAT4 a, DirectX::XMFLOAT4 b)
	{
		try
		{
			return DirectX::XMFLOAT4(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w);
		}
		catch (...)
		{
			throw "Logical error : Divide by zero";
		}
	}

	inline DirectX::XMFLOAT4 operator / (DirectX::XMFLOAT4 a, float b)
	{
		try
		{
			return DirectX::XMFLOAT4(a.x / b, a.y / b, a.z / b, a.w / b);
		}
		catch (...)
		{
			throw "Logical error : Divide by zero";
		}
	}


NAMESPACE_MathHelper_END
NAMESPACE_DXUT_END

#ifdef __cplusplus
EXTERN_C_END
#endif
