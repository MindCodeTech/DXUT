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

struct XMFLOAT2;
struct XMFLOAT3;
struct XMFLOAT4;

struct MHVECTOR2;
struct MHVECTOR3;
struct MHVECTOR4;
struct MHMATRIX;
struct MHPLANE;
struct MHQUATERNION;
struct MHCOLOR;
class MHLINE;
class MHRAY;


// Fix-up for (1st) XMMATRIX parameter to pass in-register on Xbox 360 and vector call; by reference otherwise
#if ( defined(_XM_VMX128_INTRINSICS )|| _XM_VECTORCALL_ ) && !defined(_XM_NO_INTRINSICS_)
typedef const MHVECTOR2		FMHVECTOR2;
typedef const MHVECTOR3		FMHVECTOR3;
typedef const MHVECTOR4		FMHVECTOR4;
typedef const MHMATRIX		FMHMATRIX;
typedef const MHPLANE		FMHPLANE;
typedef const MHQUATERNION	FMHQUATERNION;
typedef const MHCOLOR		FMHCOLOR;
typedef const MHLINE		FMHLINE;
typedef const MHRAY			FMHRAY;
#else
typedef const MHVECTOR2&	FMHVECTOR2;
typedef const MHVECTOR3&	FMHVECTOR3;
typedef const MHVECTOR4&	FMHVECTOR4;
typedef const MHMATRIX&		FMHMATRIX;
typedef const MHPLANE&		FMHPLANE;
typedef const MHQUATERNION& FMHQUATERNION;
typedef const MHCOLOR&		FMHCOLOR;
typedef const MHLINE&		FMHLINE;
typedef const MHRAY&		FMHRAY;
#endif

// Fix-up for (2nd+) XMMATRIX parameters to pass in-register on Xbox 360, by reference otherwise
#if defined(_XM_VMX128_INTRINSICS_) && !defined(_XM_NO_INTRINSICS_)
typedef const MHVECTOR2		CMHVECTOR2;
typedef const MHVECTOR3		CMHVECTOR3;
typedef const MHVECTOR4		CMHVECTOR4;
typedef const MHMATRIX		CMHMATRIX;
typedef const MHPLANE		CMHPLANE;
typedef const MHQUATERNION	CMHQUATERNION;
typedef const MHCOLOR		CMHCOLOR;
typedef const MHLINE		CMHLINE;
typedef const MHRAY			CMHRAY;
#else
typedef const MHVECTOR2&	CMHVECTOR2;
typedef const MHVECTOR3&	CMHVECTOR3;
typedef const MHVECTOR4&	CMHVECTOR4;
typedef const MHMATRIX&		CMHMATRIX;
typedef const MHPLANE&		CMHPLANE;
typedef const MHQUATERNION& CMHQUATERNION;
typedef const MHCOLOR&		CMHCOLOR;
typedef const MHLINE&		CMHLINE;
typedef const MHRAY&		CMHRAY;
#endif


// common
# pragma region common 

static float MHRand();
static float MHRand(float a, float b);

static float XM_CALLCONV MHFresnelTerm(float CosIAngle, float RefIndex);

static float MHRestrict(float val, float Min, float Max);

# pragma endregion

//  ------------------------------------------------------------------------------
/// XMFLOAT2
//--------------------------------------------------------------------------------
# pragma region XMFLOAT2

//  ------------------------------------------------------------------------------
/// operators
//--------------------------------------------------------------------------------
#	pragma region operators

//------------------------------------------------------------------------------
// Comparision operators
//------------------------------------------------------------------------------
bool XM_CALLCONV operator== (const XMFLOAT2& V1, const XMFLOAT2& V2);
bool XM_CALLCONV operator!= (const XMFLOAT2& V1, const XMFLOAT2& V2);

//------------------------------------------------------------------------------
// Assignment operators
//------------------------------------------------------------------------------
// XMFLOAT2 XM_CALLCONV operator= (const XMFLOAT2& V) { x = V.x; y = V.y; return *this; };
XMFLOAT2 XM_CALLCONV operator+= (XMFLOAT2& V1, const XMFLOAT2& V2);
XMFLOAT2 XM_CALLCONV operator+= (XMFLOAT2& V, float S);
XMFLOAT2 XM_CALLCONV operator+= (float S, XMFLOAT2& V);
XMFLOAT2 XM_CALLCONV operator-= (XMFLOAT2& V1, const XMFLOAT2& V2);
XMFLOAT2 XM_CALLCONV operator-= (XMFLOAT2& V, float S);
XMFLOAT2 XM_CALLCONV operator-= (float S, XMFLOAT2& V);
XMFLOAT2 XM_CALLCONV operator*= (XMFLOAT2& V1, const XMFLOAT2& V2);
XMFLOAT2 XM_CALLCONV operator*= (XMFLOAT2& V, float S);
XMFLOAT2 XM_CALLCONV operator*= (float S, XMFLOAT2& V);
XMFLOAT2 XM_CALLCONV operator/= (XMFLOAT2& V1, const XMFLOAT2& V2);
XMFLOAT2 XM_CALLCONV operator/= (XMFLOAT2& V, float S);
XMFLOAT2 XM_CALLCONV operator/= (float S, XMFLOAT2& V);

//------------------------------------------------------------------------------
// Urnary operators
//------------------------------------------------------------------------------
XMFLOAT2 XM_CALLCONV operator+ (const XMFLOAT2& V);
XMFLOAT2 XM_CALLCONV operator- (const XMFLOAT2& V);

//------------------------------------------------------------------------------
// Binary operators
//------------------------------------------------------------------------------
XMFLOAT2 XM_CALLCONV operator+ (const XMFLOAT2& V1, const XMFLOAT2& V2);
XMFLOAT2 XM_CALLCONV operator+ (const XMFLOAT2& V, float S);
XMFLOAT2 XM_CALLCONV operator+ (float S, const XMFLOAT2& V);
XMFLOAT2 XM_CALLCONV operator- (const XMFLOAT2& V1, const XMFLOAT2& V2);
XMFLOAT2 XM_CALLCONV operator- (const XMFLOAT2& V, float S);
XMFLOAT2 XM_CALLCONV operator- (float S, const XMFLOAT2& V);
XMFLOAT2 XM_CALLCONV operator* (const XMFLOAT2& V1, const XMFLOAT2& V2);
XMFLOAT2 XM_CALLCONV operator* (const XMFLOAT2& V, float S);
XMFLOAT2 XM_CALLCONV operator* (float S, const XMFLOAT2& V);
XMFLOAT2 XM_CALLCONV operator/ (const XMFLOAT2& V1, const XMFLOAT2& V2);
XMFLOAT2 XM_CALLCONV operator/ (const XMFLOAT2& V, float S);
XMFLOAT2 XM_CALLCONV operator/ (float S, const XMFLOAT2& V);

#	pragma endregion

# pragma endregion

//  ------------------------------------------------------------------------------
/// XMFLOAT3
//--------------------------------------------------------------------------------
#pragma region XMFLOAT3

//  ------------------------------------------------------------------------------
/// operators
//--------------------------------------------------------------------------------
#	pragma region operators

//------------------------------------------------------------------------------
// Comparision operators
//------------------------------------------------------------------------------
bool XM_CALLCONV operator== (const XMFLOAT3& V1, const XMFLOAT3& V2);
bool XM_CALLCONV operator!= (const XMFLOAT3& V1, const XMFLOAT3& V2);

//------------------------------------------------------------------------------
// Assignment operators
//------------------------------------------------------------------------------
// XMFLOAT3 XM_CALLCONV operator= (const XMFLOAT3& V) { x = V.x; y = V.y; z = V.z; return *this; }
XMFLOAT3 XM_CALLCONV operator+= (XMFLOAT3& V1, const XMFLOAT3& V2);
XMFLOAT3 XM_CALLCONV operator+= (XMFLOAT3& V, float S);
XMFLOAT3 XM_CALLCONV operator+= (float S, XMFLOAT3& V);
XMFLOAT3 XM_CALLCONV operator-= (XMFLOAT3& V1, const XMFLOAT3& V2);
XMFLOAT3 XM_CALLCONV operator-= (XMFLOAT3& V, float S);
XMFLOAT3 XM_CALLCONV operator-= (float S, XMFLOAT3& V);
XMFLOAT3 XM_CALLCONV operator*= (XMFLOAT3& V1, const XMFLOAT3& V2);
XMFLOAT3 XM_CALLCONV operator*= (XMFLOAT3& V, float S);
XMFLOAT3 XM_CALLCONV operator*= (float S, XMFLOAT3& V);
XMFLOAT3 XM_CALLCONV operator/= (XMFLOAT3& V1, const XMFLOAT3& V2);
XMFLOAT3 XM_CALLCONV operator/= (XMFLOAT3& V, float S);
XMFLOAT3 XM_CALLCONV operator/= (float S, XMFLOAT3& V);

//------------------------------------------------------------------------------
// Urnary operators
//------------------------------------------------------------------------------
XMFLOAT3 XM_CALLCONV operator+ (const XMFLOAT3& V);
XMFLOAT3 XM_CALLCONV operator- (const XMFLOAT3& V);

//------------------------------------------------------------------------------
// Binary operators
//------------------------------------------------------------------------------
XMFLOAT3 XM_CALLCONV operator+ (const XMFLOAT3& V1, const XMFLOAT3& V2);
XMFLOAT3 XM_CALLCONV operator+ (const XMFLOAT3& V, float S);
XMFLOAT3 XM_CALLCONV operator+ (float S, const XMFLOAT3& V);
XMFLOAT3 XM_CALLCONV operator- (const XMFLOAT3& V1, const XMFLOAT3& V2);
XMFLOAT3 XM_CALLCONV operator- (const XMFLOAT3& V, float S);
XMFLOAT3 XM_CALLCONV operator- (float S, const XMFLOAT3& V);
XMFLOAT3 XM_CALLCONV operator* (const XMFLOAT3& V1, const XMFLOAT3& V2);
XMFLOAT3 XM_CALLCONV operator* (const XMFLOAT3& V, float S);
XMFLOAT3 XM_CALLCONV operator* (float S, const XMFLOAT3& V);
XMFLOAT3 XM_CALLCONV operator/ (const XMFLOAT3& V1, const XMFLOAT3& V2);
XMFLOAT3 XM_CALLCONV operator/ (const XMFLOAT3& V, float S);
XMFLOAT3 XM_CALLCONV operator/ (float S, const XMFLOAT3& V);

#	pragma endregion

static XMFLOAT3 XM_CALLCONV XMMatrixForward(const XMMATRIX& m);
static XMFLOAT3 XM_CALLCONV XMMatrixBackward(const XMMATRIX& m);
static XMFLOAT3 XM_CALLCONV XMMatrixUp(const XMMATRIX& m);
static XMFLOAT3 XM_CALLCONV XMMatrixDown(const XMMATRIX& m);
static XMFLOAT3 XM_CALLCONV XMMatrixRight(const XMMATRIX& m);
static XMFLOAT3 XM_CALLCONV XMMatrixLeft(const XMMATRIX& m);

static float XM_CALLCONV XMF3Dot(XMFLOAT3& a, XMFLOAT3& b);

static float XM_CALLCONV XMF3Length(XMFLOAT3& a);

static XMFLOAT3 XM_CALLCONV XMF3Cross(XMFLOAT3& a, XMFLOAT3& b);
static XMFLOAT3 XM_CALLCONV XMF3Normalize(XMFLOAT3& v);

static XMFLOAT3 XM_CALLCONV VecToXMF3(XMVECTOR& v);

static XMFLOAT3 XM_CALLCONV XMF3Transform(XMFLOAT3& v, XMMATRIX& m);

static XMFLOAT3 XM_CALLCONV XMF3TransformNormal(XMFLOAT3& v, XMMATRIX& m);

# pragma endregion

//  ------------------------------------------------------------------------------
/// XMFLOAT4
//--------------------------------------------------------------------------------
# pragma region XMFLOAT4

//  ------------------------------------------------------------------------------
/// operators
//--------------------------------------------------------------------------------
#pragma region operators

//------------------------------------------------------------------------------
// Comparision operators
//------------------------------------------------------------------------------
bool XM_CALLCONV operator== (const XMFLOAT4& V1, const XMFLOAT4& V2);
bool XM_CALLCONV operator!= (const XMFLOAT4& V1, const XMFLOAT4& V2);

//------------------------------------------------------------------------------
// Assignment operators
//------------------------------------------------------------------------------
// XMFLOAT4 XM_CALLCONV operator= (const XMFLOAT4& V) { x = V.x; y = V.y; z = V.z; w = V.w; return *this; }
XMFLOAT4 XM_CALLCONV operator+= (XMFLOAT4& V1, const XMFLOAT4& V2);
XMFLOAT4 XM_CALLCONV operator+= (XMFLOAT4& V, float S);
XMFLOAT4 XM_CALLCONV operator+= (float S, XMFLOAT4& V);
XMFLOAT4 XM_CALLCONV operator-= (XMFLOAT4& V1, const XMFLOAT4& V2);
XMFLOAT4 XM_CALLCONV operator-= (XMFLOAT4& V, float S);
XMFLOAT4 XM_CALLCONV operator-= (float S, XMFLOAT4& V);
XMFLOAT4 XM_CALLCONV operator*= (XMFLOAT4& V1, const XMFLOAT4& V2);
XMFLOAT4 XM_CALLCONV operator*= (XMFLOAT4& V, float S);
XMFLOAT4 XM_CALLCONV operator*= (float S, XMFLOAT4& V);
XMFLOAT4 XM_CALLCONV operator/= (XMFLOAT4& V1, const XMFLOAT4& V2);
XMFLOAT4 XM_CALLCONV operator/= (XMFLOAT4& V, float S);
XMFLOAT4 XM_CALLCONV operator/= (float S, XMFLOAT4& V);

//------------------------------------------------------------------------------
// Urnary operators
//------------------------------------------------------------------------------
XMFLOAT4 XM_CALLCONV operator+ (const XMFLOAT4& V);
XMFLOAT4 XM_CALLCONV operator- (const XMFLOAT4& V);

//------------------------------------------------------------------------------
// Binary operators
//------------------------------------------------------------------------------
XMFLOAT4 XM_CALLCONV operator+ (const XMFLOAT4& V1, const XMFLOAT4& V2);
XMFLOAT4 XM_CALLCONV operator+ (const XMFLOAT4& V, float S);
XMFLOAT4 XM_CALLCONV operator+ (float S, const XMFLOAT4& V);
XMFLOAT4 XM_CALLCONV operator- (const XMFLOAT4& V1, const XMFLOAT4& V2);
XMFLOAT4 XM_CALLCONV operator- (const XMFLOAT4& V, float S);
XMFLOAT4 XM_CALLCONV operator- (float S, const XMFLOAT4& V);
XMFLOAT4 XM_CALLCONV operator* (const XMFLOAT4& V1, const XMFLOAT4& V2);
XMFLOAT4 XM_CALLCONV operator* (const XMFLOAT4& V, float S);
XMFLOAT4 XM_CALLCONV operator* (float S, const XMFLOAT4& V);
XMFLOAT4 XM_CALLCONV operator/ (const XMFLOAT4& V1, const XMFLOAT4& V2);
XMFLOAT4 XM_CALLCONV operator/ (const XMFLOAT4& V, float S);
XMFLOAT4 XM_CALLCONV operator/ (float S, const XMFLOAT4& V);

#pragma endregion

static XMFLOAT4 XM_CALLCONV VecToXMF4(XMVECTOR& v);

static XMFLOAT4 XM_CALLCONV XMF4Transform(XMFLOAT4& f, XMMATRIX& m);

static XMFLOAT4 XM_CALLCONV XMF4TransformNormal(XMFLOAT4& f, XMMATRIX& m);

#pragma endregion

namespace_DirectX_end; // namespace DirectX


#include "DirectXMathHelper_vector2.h"
#include "DirectXMathHelper_vector3.h"
#include "DirectXMathHelper_vector4.h"
#include "DirectXMathHelper_matrix.h"
#include "DirectXMathHelper_plane.h"
#include "DirectXMathHelper_quaternion.h"
#include "DirectXMathHelper_color.h"
#include "DirectXMathHelper_line.h"
#include "DirectXMathHelper_ray.h"


namespace_DirectX

#include "DirectXMathHelper.inl"
#include "DirectXMathHelper_vector2.inl"
#include "DirectXMathHelper_vector3.inl"
#include "DirectXMathHelper_vector4.inl"
#include "DirectXMathHelper_matrix.inl"
#include "DirectXMathHelper_plane.inl"
#include "DirectXMathHelper_quaternion.inl"
#include "DirectXMathHelper_color.inl"
#include "DirectXMathHelper_line.inl"
#include "DirectXMathHelper_ray.inl"

namespace_DirectX_end


//------------------------------------------------------------------------------
// Support for DirectXMathHelper and Standard C++ Library containers
namespace std
{
	using namespace DirectX;

    template<> struct less<MHVECTOR2>
    {
		bool operator()(FMHVECTOR2& V1, FMHVECTOR2& V2) const
        {
            return ( (V1.x < V2.x) || ((V1.x == V2.x) && (V1.y < V2.y)) );
        }
    };

    template<> struct less<MHVECTOR3>
    {
		bool operator()(FMHVECTOR3& V1, FMHVECTOR3& V2) const
        {
            return ( (V1.x < V2.x)
                     || ((V1.x == V2.x) && (V1.y < V2.y))
                     || ((V1.x == V2.x) && (V1.y == V2.y) && (V1.z < V2.z)) );
        }
    };

    template<> struct less<MHVECTOR4>
    {
		bool operator()(FMHVECTOR4& V1, FMHVECTOR4& V2) const
        {
            return ( (V1.x < V2.x)
                     || ((V1.x == V2.x) && (V1.y < V2.y))
                     || ((V1.x == V2.x) && (V1.y == V2.y) && (V1.z < V2.z))
                     || ((V1.x == V2.x) && (V1.y == V2.y) && (V1.z == V2.z) && (V1.w < V2.w)) );
        }
    };

    template<> struct less<MHMATRIX>
    {
		bool operator()(FMHMATRIX& M1, FMHMATRIX& M2) const
        {
            if (M1._11 != M2._11) return M1._11 < M2._11;
            if (M1._12 != M2._12) return M1._12 < M2._12;
            if (M1._13 != M2._13) return M1._13 < M2._13;
            if (M1._14 != M2._14) return M1._14 < M2._14;
            if (M1._21 != M2._21) return M1._21 < M2._21;
            if (M1._22 != M2._22) return M1._22 < M2._22;
            if (M1._23 != M2._23) return M1._23 < M2._23;
            if (M1._24 != M2._24) return M1._24 < M2._24;
            if (M1._31 != M2._31) return M1._31 < M2._31;
            if (M1._32 != M2._32) return M1._32 < M2._32;
            if (M1._33 != M2._33) return M1._33 < M2._33;
            if (M1._34 != M2._34) return M1._34 < M2._34;
            if (M1._41 != M2._41) return M1._41 < M2._41;
            if (M1._42 != M2._42) return M1._42 < M2._42;
            if (M1._43 != M2._43) return M1._43 < M2._43;
            if (M1._44 != M2._44) return M1._44 < M2._44;

            return false;
        }
    };

    template<> struct less<MHPLANE>
    {
		bool operator()(FMHPLANE& P1, FMHPLANE& P2) const
        {
            return ( (P1.x < P2.x)
                     || ((P1.x == P2.x) && (P1.y < P2.y))
                     || ((P1.x == P2.x) && (P1.y == P2.y) && (P1.z < P2.z))
                     || ((P1.x == P2.x) && (P1.y == P2.y) && (P1.z == P2.z) && (P1.w < P2.w)) );
        }
    };

    template<> struct less<MHQUATERNION>
    {
		bool operator()(FMHQUATERNION& Q1, FMHQUATERNION& Q2) const
        {
            return ( (Q1.x < Q2.x)
                     || ((Q1.x == Q2.x) && (Q1.y < Q2.y))
                     || ((Q1.x == Q2.x) && (Q1.y == Q2.y) && (Q1.z < Q2.z))
                     || ((Q1.x == Q2.x) && (Q1.y == Q2.y) && (Q1.z == Q2.z) && (Q1.w < Q2.w)) );
        }
    };

    template<> struct less<MHCOLOR>
    {
		bool operator()(FMHCOLOR& C1, FMHCOLOR& C2) const
        {
            return ( (C1.x < C2.x)
                     || ((C1.x == C2.x) && (C1.y < C2.y))
                     || ((C1.x == C2.x) && (C1.y == C2.y) && (C1.z < C2.z))
                     || ((C1.x == C2.x) && (C1.y == C2.y) && (C1.z == C2.z) && (C1.w < C2.w)) );
        }
    };

    template<> struct less<MHRAY>
    {
		bool operator()(FMHRAY& R1, FMHRAY& R2) const
        {
            if (R1.position.x != R2.position.x) return R1.position.x < R2.position.x;
            if (R1.position.y != R2.position.y) return R1.position.y < R2.position.y;
            if (R1.position.z != R2.position.z) return R1.position.z < R2.position.z;

            if (R1.direction.x != R2.direction.x) return R1.direction.x < R2.direction.x;
            if (R1.direction.y != R2.direction.y) return R1.direction.y < R2.direction.y;
            if (R1.direction.z != R2.direction.z) return R1.direction.z < R2.direction.z;

            return false;
        }
    };
} // namespace std end

#ifdef __cplusplus
EXTERN_CC_END
#endif
