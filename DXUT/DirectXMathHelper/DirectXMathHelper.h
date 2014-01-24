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

struct MHVECTOR4;
struct MHMATRIX;
struct MHQUATERNION;
struct MHPLANE;

static float MHRand();
static float MHRand(float a, float b);

static float XM_CALLCONV MHFresnelTerm(float CosIAngle, float RefIndex);

static float MHRestrict(float val, float Min, float Max);

static XMFLOAT3 XM_CALLCONV XMMatrixForward(const XMMATRIX& m);
static XMFLOAT3 XM_CALLCONV XMMatrixBackward(const XMMATRIX& m);
static XMFLOAT3 XM_CALLCONV XMMatrixUp(const XMMATRIX& m);
static XMFLOAT3 XM_CALLCONV XMMatrixDown(const XMMATRIX& m);
static XMFLOAT3 XM_CALLCONV XMMatrixRight(const XMMATRIX& m);
static XMFLOAT3 XM_CALLCONV XMMatrixLeft(const XMMATRIX& m);

static float XM_CALLCONV MHDot(XMFLOAT3& a, XMFLOAT3& b);

static float XM_CALLCONV MHLength(XMFLOAT3& a);

static XMFLOAT3 XM_CALLCONV MHCross(XMFLOAT3& a, XMFLOAT3& b);
static XMFLOAT3 XM_CALLCONV MHNormalize(XMFLOAT3& v);

static XMFLOAT3 XM_CALLCONV VectorToFloat3(XMVECTOR& v);
static XMFLOAT4 XM_CALLCONV VectorToFloat4(XMVECTOR& v);

static XMFLOAT3 XM_CALLCONV MHTransform(XMFLOAT3& v, XMMATRIX& m);
static XMFLOAT4 XM_CALLCONV MHTransform(XMFLOAT4& f, XMMATRIX& m);

static XMFLOAT3 XM_CALLCONV MHTransformNormal(XMFLOAT3& v, XMMATRIX& m);
static XMFLOAT4 XM_CALLCONV MHTransformNormal(XMFLOAT4& f, XMMATRIX& m);


//------------------------------------------------------------------------------
// 2D vector
#	pragma region MHVECTOR2

struct MHVECTOR2 : public XMFLOAT2
{
    MHVECTOR2() : XMFLOAT2(0.f, 0.f) {}
    explicit MHVECTOR2(float x) : XMFLOAT2( x, x ) {}
    MHVECTOR2(float _x, float _y) : XMFLOAT2(_x, _y) {}
    explicit MHVECTOR2(_In_reads_(2) const float *pArray) : XMFLOAT2(pArray) {}
    MHVECTOR2(FXMVECTOR& V) { XMStoreFloat2( this, V ); }

    operator XMVECTOR() const { return XMLoadFloat2( this ); }

    // Comparision operators
	bool XM_CALLCONV operator == (const MHVECTOR2& V) const;
	bool XM_CALLCONV operator != (const MHVECTOR2& V) const;

    // Assignment operators
	MHVECTOR2& XM_CALLCONV operator = (const MHVECTOR2& V) { x = V.x; y = V.y; return *this; }
	MHVECTOR2& XM_CALLCONV operator += (const MHVECTOR2& V);
	MHVECTOR2& XM_CALLCONV operator += (float S);
	MHVECTOR2& XM_CALLCONV operator -= (const MHVECTOR2& V);
	MHVECTOR2& XM_CALLCONV operator -= (float S);
	MHVECTOR2& XM_CALLCONV operator *= (const MHVECTOR2& V);
	MHVECTOR2& XM_CALLCONV operator *= (float S);
	MHVECTOR2& XM_CALLCONV operator /= (const MHVECTOR2& V);
	MHVECTOR2& XM_CALLCONV operator /= (float S);

    // Urnary operators
	MHVECTOR2 XM_CALLCONV operator + () const { return *this; }
	MHVECTOR2 XM_CALLCONV operator - () const { return MHVECTOR2(-x, -y); }

    // Vector operations
	bool XM_CALLCONV VInBounds(const MHVECTOR2& Bounds) const;

	float XM_CALLCONV VLength() const;
	float XM_CALLCONV VLengthSquared() const;

	float XM_CALLCONV VDot(const MHVECTOR2& V) const;
	void XM_CALLCONV VCross(const MHVECTOR2& V, MHVECTOR2& result) const;
	MHVECTOR2 XM_CALLCONV VCross(const MHVECTOR2& V) const;
    
	void XM_CALLCONV VNormalize();
	void XM_CALLCONV VNormalize(MHVECTOR2& result) const;

	void XM_CALLCONV VClamp(const MHVECTOR2& vmin, const MHVECTOR2& vmax);
	void XM_CALLCONV VClamp(const MHVECTOR2& vmin, const MHVECTOR2& vmax, MHVECTOR2& result) const;

    // Static functions
	static bool XM_CALLCONV InBounds(const MHVECTOR2& V, const MHVECTOR2& Bounds);

	static float XM_CALLCONV Length(const MHVECTOR2& V);
	static float XM_CALLCONV LengthSquared(const MHVECTOR2& V);

	static float XM_CALLCONV Dot(const MHVECTOR2& V1, const MHVECTOR2& V2);
	static void XM_CALLCONV Cross(const MHVECTOR2& V1, const MHVECTOR2& V2, MHVECTOR2& result);
	static MHVECTOR2 XM_CALLCONV Cross(const MHVECTOR2& V1, const MHVECTOR2& V2);

	static void XM_CALLCONV Normalize(const MHVECTOR2& V, MHVECTOR2& result);
	static MHVECTOR2 XM_CALLCONV Normalize(const MHVECTOR2& V);
	
	static void XM_CALLCONV Clamp(const MHVECTOR2& V, const MHVECTOR2& vmin, const MHVECTOR2& vmax, MHVECTOR2& result);
	static MHVECTOR2 XM_CALLCONV Clamp(MHVECTOR2& V, const MHVECTOR2& vmin, const MHVECTOR2& vmax);

	static void XM_CALLCONV ClampLength(const MHVECTOR2& V, float LengthMin, float LengthMax, MHVECTOR2& result);
	static MHVECTOR2 XM_CALLCONV ClampLength(MHVECTOR2& V, float LengthMin, float LengthMax);

	static float XM_CALLCONV Distance(const MHVECTOR2& v1, const MHVECTOR2& v2);
	static float XM_CALLCONV DistanceSquared(const MHVECTOR2& v1, const MHVECTOR2& v2);

	static void XM_CALLCONV Min(const MHVECTOR2& v1, const MHVECTOR2& v2, MHVECTOR2& result);
	static MHVECTOR2 XM_CALLCONV Min(const MHVECTOR2& v1, const MHVECTOR2& v2);

	static void XM_CALLCONV Max(const MHVECTOR2& v1, const MHVECTOR2& v2, MHVECTOR2& result);
	static MHVECTOR2 XM_CALLCONV Max(const MHVECTOR2& v1, const MHVECTOR2& v2);

	static void XM_CALLCONV Lerp(const MHVECTOR2& v1, const MHVECTOR2& v2, float t, MHVECTOR2& result);
	static MHVECTOR2 XM_CALLCONV Lerp(const MHVECTOR2& v1, const MHVECTOR2& v2, float t);

	static void XM_CALLCONV SmoothStep(const MHVECTOR2& v1, const MHVECTOR2& v2, float t, MHVECTOR2& result);
	static MHVECTOR2 XM_CALLCONV SmoothStep(const MHVECTOR2& v1, const MHVECTOR2& v2, float t);

	static void XM_CALLCONV Barycentric(const MHVECTOR2& v1, const MHVECTOR2& v2, const MHVECTOR2& v3, float f, float g, MHVECTOR2& result);
	static MHVECTOR2 XM_CALLCONV Barycentric(const MHVECTOR2& v1, const MHVECTOR2& v2, const MHVECTOR2& v3, float f, float g);

	static void XM_CALLCONV CatmullRom(const MHVECTOR2& v1, const MHVECTOR2& v2, const MHVECTOR2& v3, const MHVECTOR2& v4, float t, MHVECTOR2& result);
	static MHVECTOR2 XM_CALLCONV CatmullRom(const MHVECTOR2& v1, const MHVECTOR2& v2, const MHVECTOR2& v3, const MHVECTOR2& v4, float t);

	static void XM_CALLCONV Hermite(const MHVECTOR2& v1, const MHVECTOR2& t1, const MHVECTOR2& v2, const MHVECTOR2& t2, float t, MHVECTOR2& result);
	static MHVECTOR2 XM_CALLCONV Hermite(const MHVECTOR2& v1, const MHVECTOR2& t1, const MHVECTOR2& v2, const MHVECTOR2& t2, float t);

	static void XM_CALLCONV Reflect(const MHVECTOR2& ivec, const MHVECTOR2& nvec, MHVECTOR2& result);
	static MHVECTOR2 XM_CALLCONV Reflect(const MHVECTOR2& ivec, const MHVECTOR2& nvec);

	static void XM_CALLCONV Refract(const MHVECTOR2& ivec, const MHVECTOR2& nvec, float refractionIndex, MHVECTOR2& result);
	static MHVECTOR2 XM_CALLCONV Refract(const MHVECTOR2& ivec, const MHVECTOR2& nvec, float refractionIndex);

	static void XM_CALLCONV Transform(const MHVECTOR2& v, const MHQUATERNION& quat, MHVECTOR2& result);
	static MHVECTOR2 XM_CALLCONV Transform(const MHVECTOR2& v, const MHQUATERNION& quat);

	static void XM_CALLCONV Transform(const MHVECTOR2& v, const MHMATRIX& m, MHVECTOR2& result);
	static MHVECTOR2 XM_CALLCONV Transform(const MHVECTOR2& v, const MHMATRIX& m);
	static void XM_CALLCONV Transform(_In_reads_(count) const MHVECTOR2* varray, size_t count, const MHMATRIX& m, _Out_writes_(count) MHVECTOR2* resultArray);

	static void XM_CALLCONV Transform(const MHVECTOR2& v, const MHMATRIX& m, MHVECTOR4& result);
	static void XM_CALLCONV Transform(_In_reads_(count) const MHVECTOR2* varray, size_t count, const MHMATRIX& m, _Out_writes_(count) MHVECTOR4* resultArray);

	static void XM_CALLCONV TransformNormal(const MHVECTOR2& v, const MHMATRIX& m, MHVECTOR2& result);
	static MHVECTOR2 XM_CALLCONV TransformNormal(const MHVECTOR2& v, const MHMATRIX& m);
	static void XM_CALLCONV TransformNormal(_In_reads_(count) const MHVECTOR2* varray, size_t count, const MHMATRIX& m, _Out_writes_(count) MHVECTOR2* resultArray);
};

// Binary operators
MHVECTOR2 XM_CALLCONV operator+ (const MHVECTOR2& V1, const MHVECTOR2& V2);
MHVECTOR2 XM_CALLCONV operator+ (const MHVECTOR2& V, float S);
MHVECTOR2 XM_CALLCONV operator+ (float S, const MHVECTOR2& V);
MHVECTOR2 XM_CALLCONV operator- (const MHVECTOR2& V1, const MHVECTOR2& V2);
MHVECTOR2 XM_CALLCONV operator- (const MHVECTOR2& V, float S);
MHVECTOR2 XM_CALLCONV operator- (float S, const MHVECTOR2& V);
MHVECTOR2 XM_CALLCONV operator* (const MHVECTOR2& V1, const MHVECTOR2& V2);
MHVECTOR2 XM_CALLCONV operator* (const MHVECTOR2& V, float S);
MHVECTOR2 XM_CALLCONV operator* (float S, const MHVECTOR2& V);
MHVECTOR2 XM_CALLCONV operator/ (const MHVECTOR2& V1, const MHVECTOR2& V2);
MHVECTOR2 XM_CALLCONV operator/ (const MHVECTOR2& V, float S);
MHVECTOR2 XM_CALLCONV operator/ (float S, const MHVECTOR2& V);

#	pragma endregion

//------------------------------------------------------------------------------
// 3D vector
#	pragma region MHVECTOR3

struct MHVECTOR3 : public XMFLOAT3
{
    MHVECTOR3() : XMFLOAT3(0.f, 0.f, 0.f) {}
    explicit MHVECTOR3(float x) : XMFLOAT3( x, x, x ) {}
    MHVECTOR3(float _x, float _y, float _z) : XMFLOAT3(_x, _y, _z) {}
    explicit MHVECTOR3(_In_reads_(3) const float *pArray) : XMFLOAT3(pArray) {}
	MHVECTOR3(FXMVECTOR& V) { XMStoreFloat3(this, V); }

    operator XMVECTOR() const { return XMLoadFloat3( this ); }

    // Comparision operators
	bool XM_CALLCONV operator == (const MHVECTOR3& V) const;
	bool XM_CALLCONV operator != (const MHVECTOR3& V) const;

    // Assignment operators
	MHVECTOR3& XM_CALLCONV operator= (const MHVECTOR3& V) { x = V.x; y = V.y; z = V.z; return *this; }
	MHVECTOR3& XM_CALLCONV operator+= (const MHVECTOR3& V);
	MHVECTOR3& XM_CALLCONV operator+= (float S);
	MHVECTOR3& XM_CALLCONV operator-= (const MHVECTOR3& V);
	MHVECTOR3& XM_CALLCONV operator-= (float S);
	MHVECTOR3& XM_CALLCONV operator*= (const MHVECTOR3& V);
	MHVECTOR3& XM_CALLCONV operator*= (float S);
	MHVECTOR3& XM_CALLCONV operator/= (const MHVECTOR3& V);
	MHVECTOR3& XM_CALLCONV operator/= (float S);

    // Urnary operators
	MHVECTOR3 XM_CALLCONV operator+ () const { return *this; }
	MHVECTOR3 XM_CALLCONV operator- () const;

    // Vector operations
	bool XM_CALLCONV VInBounds(const MHVECTOR3& Bounds) const;

	float XM_CALLCONV VLength() const;
	float XM_CALLCONV VLengthSquared() const;

	float XM_CALLCONV VDot(const MHVECTOR3& V) const;
	void XM_CALLCONV VCross(const MHVECTOR3& V, MHVECTOR3& result) const;
	MHVECTOR3 XM_CALLCONV VCross(const MHVECTOR3& V) const;

	void XM_CALLCONV VNormalize();
	void XM_CALLCONV VNormalize(MHVECTOR3& result) const;

	void XM_CALLCONV VClamp(const MHVECTOR3& vmin, const MHVECTOR3& vmax);
	void XM_CALLCONV VClamp(const MHVECTOR3& vmin, const MHVECTOR3& vmax, MHVECTOR3& result) const;

    // Static functions
	static bool XM_CALLCONV InBounds(const MHVECTOR3& V, const MHVECTOR3& Bounds);

	static float XM_CALLCONV Length(const MHVECTOR3& V);
	static float XM_CALLCONV LengthSquared(const MHVECTOR3& V);

	static float XM_CALLCONV Dot(const MHVECTOR3& V1, const MHVECTOR3& V2);
	static void XM_CALLCONV Cross(const MHVECTOR3& V1, const MHVECTOR3& V2, MHVECTOR3& result);
	static MHVECTOR3 XM_CALLCONV Cross(const MHVECTOR3& V1, const MHVECTOR3& V2);

	static void XM_CALLCONV Normalize(const MHVECTOR3& V, MHVECTOR3& result);
	static MHVECTOR3 XM_CALLCONV Normalize(const MHVECTOR3& V);

	static void XM_CALLCONV Clamp(const MHVECTOR3& V, const MHVECTOR3& vmin, const MHVECTOR3& vmax, MHVECTOR3& result);
	static MHVECTOR3 XM_CALLCONV Clamp(MHVECTOR3& V, const MHVECTOR3& vmin, const MHVECTOR3& vmax);

	static void XM_CALLCONV ClampLength(const MHVECTOR3& V, float LengthMin, float LengthMax, MHVECTOR3& result);
	static MHVECTOR3 XM_CALLCONV ClampLength(MHVECTOR3& V, float LengthMin, float LengthMax);

	static float XM_CALLCONV Distance(const MHVECTOR3& v1, const MHVECTOR3& v2);
	static float XM_CALLCONV DistanceSquared(const MHVECTOR3& v1, const MHVECTOR3& v2);

	static void XM_CALLCONV Min(const MHVECTOR3& v1, const MHVECTOR3& v2, MHVECTOR3& result);
	static MHVECTOR3 XM_CALLCONV Min(const MHVECTOR3& v1, const MHVECTOR3& v2);

	static void XM_CALLCONV Max(const MHVECTOR3& v1, const MHVECTOR3& v2, MHVECTOR3& result);
	static MHVECTOR3 XM_CALLCONV Max(const MHVECTOR3& v1, const MHVECTOR3& v2);

	static void XM_CALLCONV Lerp(const MHVECTOR3& v1, const MHVECTOR3& v2, float t, MHVECTOR3& result);
	static MHVECTOR3 XM_CALLCONV Lerp(const MHVECTOR3& v1, const MHVECTOR3& v2, float t);

	static void XM_CALLCONV SmoothStep(const MHVECTOR3& v1, const MHVECTOR3& v2, float t, MHVECTOR3& result);
	static MHVECTOR3 XM_CALLCONV SmoothStep(const MHVECTOR3& v1, const MHVECTOR3& v2, float t);

	static void XM_CALLCONV Barycentric(const MHVECTOR3& v1, const MHVECTOR3& v2, const MHVECTOR3& v3, float f, float g, MHVECTOR3& result);
	static MHVECTOR3 XM_CALLCONV Barycentric(const MHVECTOR3& v1, const MHVECTOR3& v2, const MHVECTOR3& v3, float f, float g);

	static void XM_CALLCONV CatmullRom(const MHVECTOR3& v1, const MHVECTOR3& v2, const MHVECTOR3& v3, const MHVECTOR3& v4, float t, MHVECTOR3& result);
	static MHVECTOR3 XM_CALLCONV CatmullRom(const MHVECTOR3& v1, const MHVECTOR3& v2, const MHVECTOR3& v3, const MHVECTOR3& v4, float t);

	static void XM_CALLCONV Hermite(const MHVECTOR3& v1, const MHVECTOR3& t1, const MHVECTOR3& v2, const MHVECTOR3& t2, float t, MHVECTOR3& result);
	static MHVECTOR3 XM_CALLCONV Hermite(const MHVECTOR3& v1, const MHVECTOR3& t1, const MHVECTOR3& v2, const MHVECTOR3& t2, float t);

	static void XM_CALLCONV Reflect(const MHVECTOR3& ivec, const MHVECTOR3& nvec, MHVECTOR3& result);
	static MHVECTOR3 XM_CALLCONV Reflect(const MHVECTOR3& ivec, const MHVECTOR3& nvec);

	static void XM_CALLCONV Refract(const MHVECTOR3& ivec, const MHVECTOR3& nvec, float refractionIndex, MHVECTOR3& result);
	static MHVECTOR3 XM_CALLCONV Refract(const MHVECTOR3& ivec, const MHVECTOR3& nvec, float refractionIndex);

	static void XM_CALLCONV Transform(const MHVECTOR3& v, const MHQUATERNION& quat, MHVECTOR3& result);
	static MHVECTOR3 XM_CALLCONV Transform(const MHVECTOR3& v, const MHQUATERNION& quat);

	static void XM_CALLCONV Transform(const MHVECTOR3& v, const MHMATRIX& m, MHVECTOR3& result);
	static MHVECTOR3 XM_CALLCONV Transform(const MHVECTOR3& v, const MHMATRIX& m);
	static void XM_CALLCONV Transform(_In_reads_(count) const MHVECTOR3* varray, size_t count, const MHMATRIX& m, _Out_writes_(count) MHVECTOR3* resultArray);

	static void XM_CALLCONV Transform(const MHVECTOR3& v, const MHMATRIX& m, MHVECTOR4& result);
	static void XM_CALLCONV Transform(_In_reads_(count) const MHVECTOR3* varray, size_t count, const MHMATRIX& m, _Out_writes_(count) MHVECTOR4* resultArray);

	static void XM_CALLCONV TransformNormal(const MHVECTOR3& v, const MHMATRIX& m, MHVECTOR3& result);
	static MHVECTOR3 XM_CALLCONV TransformNormal(const MHVECTOR3& v, const MHMATRIX& m);
	static void XM_CALLCONV TransformNormal(_In_reads_(count) const MHVECTOR3* varray, size_t count, const MHMATRIX& m, _Out_writes_(count) MHVECTOR3* resultArray);
};

// Binary operators
MHVECTOR3 XM_CALLCONV operator+ (const MHVECTOR3& V1, const MHVECTOR3& V2);
MHVECTOR3 XM_CALLCONV operator+ (const MHVECTOR3& V, float S);
MHVECTOR3 XM_CALLCONV operator+ (float S, const MHVECTOR3& V);
MHVECTOR3 XM_CALLCONV operator- (const MHVECTOR3& V1, const MHVECTOR3& V2);
MHVECTOR3 XM_CALLCONV operator- (const MHVECTOR3& V, float S);
MHVECTOR3 XM_CALLCONV operator- (float S, const MHVECTOR3& V);
MHVECTOR3 XM_CALLCONV operator* (const MHVECTOR3& V1, const MHVECTOR3& V2);
MHVECTOR3 XM_CALLCONV operator* (const MHVECTOR3& V, float S);
MHVECTOR3 XM_CALLCONV operator* (float S, const MHVECTOR3& V);
MHVECTOR3 XM_CALLCONV operator/ (const MHVECTOR3& V1, const MHVECTOR3& V2);
MHVECTOR3 XM_CALLCONV operator/ (const MHVECTOR3& V, float S);
MHVECTOR3 XM_CALLCONV operator/ (float S, const MHVECTOR3& V);

#	pragma endregion

//------------------------------------------------------------------------------
// 4D vector
#	pragma region MHVECTOR4

struct MHVECTOR4 : public XMFLOAT4
{
    MHVECTOR4() : XMFLOAT4(0.f, 0.f, 0.f, 0.f) {}
    explicit MHVECTOR4(float x) : XMFLOAT4( x, x, x, x ) {}
    MHVECTOR4(float _x, float _y, float _z, float _w) : XMFLOAT4(_x, _y, _z, _w) {}
    explicit MHVECTOR4(_In_reads_(4) const float *pArray) : XMFLOAT4(pArray) {}
	MHVECTOR4(FXMVECTOR& V) { XMStoreFloat4(this, V); }

    operator XMVECTOR() const { return XMLoadFloat4( this ); }

    // Comparision operators
	bool XM_CALLCONV operator == (const MHVECTOR4& V) const;
	bool XM_CALLCONV operator != (const MHVECTOR4& V) const;

    // Assignment operators
	MHVECTOR4& XM_CALLCONV operator= (const MHVECTOR4& V) { x = V.x; y = V.y; z = V.z; w = V.w; return *this; }
	MHVECTOR4& XM_CALLCONV operator+= (const MHVECTOR4& V);
	MHVECTOR4& XM_CALLCONV operator+= (float S);
	MHVECTOR4& XM_CALLCONV operator-= (const MHVECTOR4& V);
	MHVECTOR4& XM_CALLCONV operator-= (float S);
	MHVECTOR4& XM_CALLCONV operator*= (const MHVECTOR4& V);
	MHVECTOR4& XM_CALLCONV operator*= (float S);
	MHVECTOR4& XM_CALLCONV operator/= (const MHVECTOR4& V);
	MHVECTOR4& XM_CALLCONV operator/= (float S);

    // Urnary operators
	MHVECTOR4 XM_CALLCONV operator+ () const { return *this; }
	MHVECTOR4 XM_CALLCONV operator- () const;

    // Vector operations
	bool XM_CALLCONV VInBounds(const MHVECTOR4& Bounds) const;

	float XM_CALLCONV VLength() const;
	float XM_CALLCONV VLengthSquared() const;

	float XM_CALLCONV VDot(const MHVECTOR4& V) const;
	void XM_CALLCONV VCross(const MHVECTOR4& v1, const MHVECTOR4& v2, MHVECTOR4& result) const;
	MHVECTOR4 XM_CALLCONV VCross(const MHVECTOR4& v1, const MHVECTOR4& v2) const;

	void XM_CALLCONV VNormalize();
	void XM_CALLCONV VNormalize(MHVECTOR4& result) const;

	void XM_CALLCONV VClamp(const MHVECTOR4& vmin, const MHVECTOR4& vmax);
	void XM_CALLCONV VClamp(const MHVECTOR4& vmin, const MHVECTOR4& vmax, MHVECTOR4& result) const;

    // Static functions
	static bool XM_CALLCONV InBounds(const MHVECTOR4& V, const MHVECTOR4& Bounds);

	static float XM_CALLCONV Length(const MHVECTOR4& V);
	static float XM_CALLCONV LengthSquared(const MHVECTOR4& V);

	static float XM_CALLCONV Dot(const MHVECTOR4& V1, const MHVECTOR4& V2);
	static void XM_CALLCONV Cross(const MHVECTOR4& V1, const MHVECTOR4& V2, const MHVECTOR4& V3, MHVECTOR4& result);
	static MHVECTOR4 XM_CALLCONV Cross(const MHVECTOR4& V1, const MHVECTOR4& V2, const MHVECTOR4& V3);

	static void XM_CALLCONV Normalize(const MHVECTOR4& V, MHVECTOR4& result);
	static MHVECTOR4 XM_CALLCONV Normalize(const MHVECTOR4& V);

	static void XM_CALLCONV Clamp(const MHVECTOR4& V, const MHVECTOR4& vmin, const MHVECTOR4& vmax, MHVECTOR4& result);
	static MHVECTOR4 XM_CALLCONV Clamp(MHVECTOR4& V, const MHVECTOR4& vmin, const MHVECTOR4& vmax);

	static void XM_CALLCONV ClampLength(const MHVECTOR4& V, float LengthMin, float LengthMax, MHVECTOR4& result);
	static MHVECTOR4 XM_CALLCONV ClampLength(MHVECTOR4& V, float LengthMin, float LengthMax);

	static float XM_CALLCONV Distance(const MHVECTOR4& v1, const MHVECTOR4& v2);
	static float XM_CALLCONV DistanceSquared(const MHVECTOR4& v1, const MHVECTOR4& v2);

	static void XM_CALLCONV Min(const MHVECTOR4& v1, const MHVECTOR4& v2, MHVECTOR4& result);
	static MHVECTOR4 XM_CALLCONV Min(const MHVECTOR4& v1, const MHVECTOR4& v2);

	static void XM_CALLCONV Max(const MHVECTOR4& v1, const MHVECTOR4& v2, MHVECTOR4& result);
	static MHVECTOR4 XM_CALLCONV Max(const MHVECTOR4& v1, const MHVECTOR4& v2);

	static void XM_CALLCONV Lerp(const MHVECTOR4& v1, const MHVECTOR4& v2, float t, MHVECTOR4& result);
	static MHVECTOR4 XM_CALLCONV Lerp(const MHVECTOR4& v1, const MHVECTOR4& v2, float t);

	static void XM_CALLCONV SmoothStep(const MHVECTOR4& v1, const MHVECTOR4& v2, float t, MHVECTOR4& result);
	static MHVECTOR4 XM_CALLCONV SmoothStep(const MHVECTOR4& v1, const MHVECTOR4& v2, float t);

	static void XM_CALLCONV Barycentric(const MHVECTOR4& v1, const MHVECTOR4& v2, const MHVECTOR4& v3, float f, float g, MHVECTOR4& result);
	static MHVECTOR4 XM_CALLCONV Barycentric(const MHVECTOR4& v1, const MHVECTOR4& v2, const MHVECTOR4& v3, float f, float g);

	static void XM_CALLCONV CatmullRom(const MHVECTOR4& v1, const MHVECTOR4& v2, const MHVECTOR4& v3, const MHVECTOR4& v4, float t, MHVECTOR4& result);
	static MHVECTOR4 XM_CALLCONV CatmullRom(const MHVECTOR4& v1, const MHVECTOR4& v2, const MHVECTOR4& v3, const MHVECTOR4& v4, float t);

	static void XM_CALLCONV Hermite(const MHVECTOR4& v1, const MHVECTOR4& t1, const MHVECTOR4& v2, const MHVECTOR4& t2, float t, MHVECTOR4& result);
	static MHVECTOR4 XM_CALLCONV Hermite(const MHVECTOR4& v1, const MHVECTOR4& t1, const MHVECTOR4& v2, const MHVECTOR4& t2, float t);

	static void XM_CALLCONV Reflect(const MHVECTOR4& ivec, const MHVECTOR4& nvec, MHVECTOR4& result);
	static MHVECTOR4 XM_CALLCONV Reflect(const MHVECTOR4& ivec, const MHVECTOR4& nvec);

	static void XM_CALLCONV Refract(const MHVECTOR4& ivec, const MHVECTOR4& nvec, float refractionIndex, MHVECTOR4& result);
	static MHVECTOR4 XM_CALLCONV Refract(const MHVECTOR4& ivec, const MHVECTOR4& nvec, float refractionIndex);

	static void XM_CALLCONV Transform(const MHVECTOR2& v, const MHQUATERNION& quat, MHVECTOR4& result);
	static MHVECTOR4 XM_CALLCONV Transform(const MHVECTOR2& v, const MHQUATERNION& quat);

	static void XM_CALLCONV Transform(const MHVECTOR3& v, const MHQUATERNION& quat, MHVECTOR4& result);
	static MHVECTOR4 XM_CALLCONV Transform(const MHVECTOR3& v, const MHQUATERNION& quat);

	static void XM_CALLCONV Transform(const MHVECTOR4& v, const MHQUATERNION& quat, MHVECTOR4& result);
	static MHVECTOR4 XM_CALLCONV Transform(const MHVECTOR4& v, const MHQUATERNION& quat);

	static void XM_CALLCONV Transform(const MHVECTOR4& v, const MHMATRIX& m, MHVECTOR4& result);
	static MHVECTOR4 XM_CALLCONV Transform(const MHVECTOR4& v, const MHMATRIX& m);
	static void XM_CALLCONV Transform(_In_reads_(count) const MHVECTOR4* varray, size_t count, const MHMATRIX& m, _Out_writes_(count) MHVECTOR4* resultArray);
};

// Binary operators
MHVECTOR4 XM_CALLCONV operator+ (const MHVECTOR4& V1, const MHVECTOR4& V2);
MHVECTOR4 XM_CALLCONV operator+ (const MHVECTOR4& V, float S);
MHVECTOR4 XM_CALLCONV operator+ (float S, const MHVECTOR4& V);
MHVECTOR4 XM_CALLCONV operator- (const MHVECTOR4& V1, const MHVECTOR4& V2);
MHVECTOR4 XM_CALLCONV operator- (const MHVECTOR4& V, float S);
MHVECTOR4 XM_CALLCONV operator- (float S, const MHVECTOR4& V);
MHVECTOR4 XM_CALLCONV operator* (const MHVECTOR4& V1, const MHVECTOR4& V2);
MHVECTOR4 XM_CALLCONV operator* (const MHVECTOR4& V, float S);
MHVECTOR4 XM_CALLCONV operator* (float S, const MHVECTOR4& V);
MHVECTOR4 XM_CALLCONV operator/ (const MHVECTOR4& V1, const MHVECTOR4& V2);
MHVECTOR4 XM_CALLCONV operator/ (const MHVECTOR4& V, float S);
MHVECTOR4 XM_CALLCONV operator/ (float S, const MHVECTOR4& V);

#	pragma endregion

//------------------------------------------------------------------------------
// 4x4 MHMATRIX (assumes right-handed coordinates)
#	pragma region MHMATRIX

struct MHMATRIX : public XMFLOAT4X4
{
    MHMATRIX() : XMFLOAT4X4( 1.f,   0,   0,   0,
                             0, 1.f,   0,   0,
                             0,   0, 1.f,   0,
                             0,   0,   0, 1.f ) {}
    MHMATRIX(float m00, float m01, float m02, float m03,
           float m10, float m11, float m12, float m13,
           float m20, float m21, float m22, float m23,
           float m30, float m31, float m32, float m33) : XMFLOAT4X4(m00, m01, m02, m03,
                                                                    m10, m11, m12, m13,
                                                                    m20, m21, m22, m23,
                                                                    m30, m31, m32, m33) {}
    explicit MHMATRIX( const MHVECTOR3& r0, const MHVECTOR3& r1, const MHVECTOR3& r2 ) : XMFLOAT4X4( r0.x, r0.y, r0.z, 0,
                                                                                             r1.x, r1.y, r1.z, 0,
                                                                                             r2.x, r2.y, r2.z, 0,
                                                                                             0,       0,    0, 1.f ) {}
    explicit MHMATRIX( const MHVECTOR4& r0, const MHVECTOR4& r1, const MHVECTOR4& r2, const MHVECTOR4& r3 ) : XMFLOAT4X4( r0.x, r0.y, r0.z, r0.w,
                                                                                                                r1.x, r1.y, r1.z, r1.w,
                                                                                                                r2.x, r2.y, r2.z, r2.w,
                                                                                                                r3.x, r3.y, r3.z, r3.w ) {}
    explicit MHMATRIX(_In_reads_(16) const float *pArray) : XMFLOAT4X4(pArray) {}
    MHMATRIX( CXMMATRIX M ) { XMStoreFloat4x4( this, M ); }

    operator XMMATRIX() const { return XMLoadFloat4x4( this ); }

    // Comparision operators
	bool XM_CALLCONV operator == (const MHMATRIX& M) const;
	bool XM_CALLCONV operator != (const MHMATRIX& M) const;

    // Assignment operators
	MHMATRIX& XM_CALLCONV operator= (const MHMATRIX& M) { memcpy_s(this, sizeof(float)* 16, &M, sizeof(float)* 16); return *this; }
	MHMATRIX& XM_CALLCONV operator+= (const MHMATRIX& M);
	MHMATRIX& XM_CALLCONV operator+= (float S);
	MHMATRIX& XM_CALLCONV operator-= (const MHMATRIX& M);
	MHMATRIX& XM_CALLCONV operator-= (float S);
	MHMATRIX& XM_CALLCONV operator*= (const MHMATRIX& M);
	MHMATRIX& XM_CALLCONV operator*= (float S);
	MHMATRIX& XM_CALLCONV operator/= (const MHMATRIX& M);
	MHMATRIX& XM_CALLCONV operator/= (float S);
        // Element-wise divide

    // Urnary operators
	MHMATRIX XM_CALLCONV operator+ () const { return *this; }
	MHMATRIX XM_CALLCONV operator- () const;

    // Properties
	MHVECTOR3 XM_CALLCONV MUp() const { return MHVECTOR3(_21, _22, _23); }
	void XM_CALLCONV MUp(const MHVECTOR3& v) { _21 = v.x; _22 = v.y; _23 = v.z; }

	MHVECTOR3 XM_CALLCONV MDown() const { return MHVECTOR3(-_21, -_22, -_23); }
	void XM_CALLCONV MDown(const MHVECTOR3& v) { _21 = -v.x; _22 = -v.y; _23 = -v.z; }

	MHVECTOR3 XM_CALLCONV MRight() const { return MHVECTOR3(_11, _12, _13); }
	void XM_CALLCONV MRight(const MHVECTOR3& v) { _11 = v.x; _12 = v.y; _13 = v.z; }

	MHVECTOR3 XM_CALLCONV MLeft() const { return MHVECTOR3(-_11, -_12, -_13); }
	void XM_CALLCONV MLeft(const MHVECTOR3& v) { _11 = -v.x; _12 = -v.y; _13 = -v.z; }

	MHVECTOR3 XM_CALLCONV MForward() const  { return MHVECTOR3(-_31, -_32, -_33); }
	void XM_CALLCONV MForward(const MHVECTOR3& v) { _31 = -v.x; _32 = -v.y; _33 = -v.z; }

	MHVECTOR3 XM_CALLCONV MBackward() const { return MHVECTOR3(_31, _32, _33); }
	void XM_CALLCONV MBackward(const MHVECTOR3& v) { _31 = v.x; _32 = v.y; _33 = v.z; }

	MHVECTOR3 XM_CALLCONV MTranslation() const { return MHVECTOR3(_41, _42, _43); }
	void XM_CALLCONV MTranslation(const MHVECTOR3& v) { _41 = v.x; _42 = v.y; _43 = v.z; }

    // Matrix operations
	bool XM_CALLCONV MDecompose(MHVECTOR3& scale, MHQUATERNION& rotation, MHVECTOR3& translation);

	MHMATRIX XM_CALLCONV MTranspose() const;
	void XM_CALLCONV MTranspose(MHMATRIX& result) const;

	MHMATRIX XM_CALLCONV MInvert() const;
	void XM_CALLCONV MInvert(MHMATRIX& result) const;

	float XM_CALLCONV MDeterminant() const;

	//-------------------------------------------------------
    // Static functions

	// Properties
	static MHVECTOR3 XM_CALLCONV Up(const MHMATRIX& M);
	static void XM_CALLCONV Up(const MHVECTOR3& V, const MHMATRIX& M, MHVECTOR3& result);

	static MHVECTOR3 XM_CALLCONV Down(const MHMATRIX& M);
	static void XM_CALLCONV Down(const MHVECTOR3& V, const MHMATRIX& M, MHVECTOR3& result);

	static MHVECTOR3 XM_CALLCONV Right(const MHMATRIX& M);
	static void XM_CALLCONV Right(const MHVECTOR3& V, const MHMATRIX& M, MHVECTOR3& result);

	static MHVECTOR3 XM_CALLCONV Left(const MHMATRIX& M);
	static void XM_CALLCONV Left(const MHVECTOR3& V, const MHMATRIX& M, MHVECTOR3& result);

	static MHVECTOR3 XM_CALLCONV Forward(const MHMATRIX& M);
	static void XM_CALLCONV Forward(const MHVECTOR3& V, const MHMATRIX& M, MHVECTOR3& result);

	static MHVECTOR3 XM_CALLCONV Backward(const MHMATRIX& M);
	static void XM_CALLCONV Backward(const MHVECTOR3& V, const MHMATRIX& M, MHVECTOR3& result);

	static MHVECTOR3 XM_CALLCONV Translate(const MHMATRIX& M);
	static void XM_CALLCONV Translate(const MHVECTOR3& V, const MHMATRIX& M, MHVECTOR3& result);

	// Matrix operations
	static bool XM_CALLCONV Decompose(const MHMATRIX& M, MHVECTOR3& scale, MHQUATERNION& rotation, MHVECTOR3& translation);

	static MHMATRIX XM_CALLCONV Transpose(const MHMATRIX& M);
	static void XM_CALLCONV Transpose(const MHMATRIX& M, MHMATRIX& result);
	static MHMATRIX XM_CALLCONV MultiplyTranspose(const MHMATRIX& M1, const MHMATRIX& M2);
	static void XM_CALLCONV MultiplyTranspose(const MHMATRIX& M1, const MHMATRIX& M2, MHMATRIX& result);

	static MHMATRIX XM_CALLCONV Inverse(const MHMATRIX& M);
	static void XM_CALLCONV Inverse(const MHMATRIX& M, MHMATRIX& result);

	static float XM_CALLCONV Determinant(const MHMATRIX& M);

	// Matrix functions
	static MHMATRIX XM_CALLCONV MHIdentity();
	static MHMATRIX XM_CALLCONV Identity();
	static bool XM_CALLCONV IsIdentity(const MHMATRIX& M);

	static MHMATRIX XM_CALLCONV Translation(const MHVECTOR3& position);
	static MHMATRIX XM_CALLCONV Translation(float x, float y, float z);
	static MHMATRIX XM_CALLCONV TranslationFromVector(FXMVECTOR& V);

	static MHMATRIX XM_CALLCONV Scaling(const MHVECTOR3& scales);
	static MHMATRIX XM_CALLCONV Scaling(float xs, float ys, float zs);
	static MHMATRIX XM_CALLCONV Scaling(float scale);
	static MHMATRIX XM_CALLCONV ScalingFromVector(FXMVECTOR& V);

	static MHMATRIX XM_CALLCONV RotationX(float radians);
	static MHMATRIX XM_CALLCONV RotationY(float radians);
	static MHMATRIX XM_CALLCONV RotationZ(float radians);
	static MHMATRIX XM_CALLCONV RotationAxisAngle(const MHVECTOR3& axis, float angle);
	static MHMATRIX XM_CALLCONV RotationNormal(const MHVECTOR3& axis, float angle);
	static MHMATRIX XM_CALLCONV RotationQuaternion(const MHQUATERNION& quat);
	static MHMATRIX XM_CALLCONV RotationRollPitchYaw(float yaw, float pitch, float roll);

	static MHMATRIX XM_CALLCONV PerspectiveFov(float fov, float aspectRatio, float nearPlane, float farPlane);
	static MHMATRIX XM_CALLCONV Perspective(float width, float height, float nearPlane, float farPlane);
	static MHMATRIX XM_CALLCONV PerspectiveOffCenter(float left, float right, float bottom, float top, float nearPlane, float farPlane);
	
	static MHMATRIX XM_CALLCONV Orthographic(float width, float height, float zNearPlane, float zFarPlane);
	static MHMATRIX XM_CALLCONV OrthographicOffCenter(float left, float right, float bottom, float top, float zNearPlane, float zFarPlane);

	static MHMATRIX XM_CALLCONV LookAt(const MHVECTOR3& eye, const MHVECTOR3& target, const MHVECTOR3& up);
	static MHMATRIX XM_CALLCONV LookTo(const MHVECTOR3& eye, const MHVECTOR3& target, const MHVECTOR3& up);
	
	static MHMATRIX XM_CALLCONV CreateWorld(const MHVECTOR3& position, const MHVECTOR3& forward, const MHVECTOR3& up);
	
	static MHMATRIX XM_CALLCONV Shadow(const MHVECTOR3& lightDir, const MHPLANE& plane);

	static MHMATRIX XM_CALLCONV Reflect(const MHPLANE& plane);

	static void XM_CALLCONV Lerp(const MHMATRIX& M1, const MHMATRIX& M2, float t, MHMATRIX& result);
	static MHMATRIX XM_CALLCONV Lerp(const MHMATRIX& M1, const MHMATRIX& M2, float t);

	static void XM_CALLCONV Transform(const MHMATRIX& M, const MHQUATERNION& rotation, MHMATRIX& result);
	static MHMATRIX XM_CALLCONV Transform(const MHMATRIX& M, const MHQUATERNION& rotation);
};

// Binary operators
MHMATRIX XM_CALLCONV operator+ (const MHMATRIX& M1, const MHMATRIX& M2);
MHMATRIX XM_CALLCONV operator+ (const MHMATRIX& M, float S);
MHMATRIX XM_CALLCONV operator+ (float S, const MHMATRIX& M);
MHMATRIX XM_CALLCONV operator- (const MHMATRIX& M1, const MHMATRIX& M2);
MHMATRIX XM_CALLCONV operator- (const MHMATRIX& M, float S);
MHMATRIX XM_CALLCONV operator- (float S, const MHMATRIX& M);
MHMATRIX XM_CALLCONV operator* (const MHMATRIX& M1, const MHMATRIX& M2);
MHMATRIX XM_CALLCONV operator* (const MHMATRIX& M, float S);
MHMATRIX XM_CALLCONV operator* (float S, const MHMATRIX& M);
MHMATRIX XM_CALLCONV operator/ (const MHMATRIX& M1, const MHMATRIX& M2);
MHMATRIX XM_CALLCONV operator/ (const MHMATRIX& M, float S);
MHMATRIX XM_CALLCONV operator/ (float S, const MHMATRIX& M);
    // Element-wise divide

#	pragma endregion

//-----------------------------------------------------------------------------
// Plane
#	pragma region MHPLANE

struct MHPLANE : public XMFLOAT4
{
    MHPLANE() : XMFLOAT4(0.f, 1.f, 0.f, 0.f) {}
    MHPLANE(float _x, float _y, float _z, float _w) : XMFLOAT4(_x, _y, _z, _w) {}
    MHPLANE(const MHVECTOR3& normal, float d) : XMFLOAT4(normal.x, normal.y, normal.z, d) {}
    MHPLANE(const MHVECTOR3& point1, const MHVECTOR3& point2, const MHVECTOR3& point3 );
    MHPLANE(const MHVECTOR3& point, const MHVECTOR3& normal);
    explicit MHPLANE(const MHVECTOR4& v) : XMFLOAT4(v.x, v.y, v.z, v.w) {}
    explicit MHPLANE(_In_reads_(4) const float *pArray) : XMFLOAT4(pArray) {}
	MHPLANE(FXMVECTOR& V) { XMStoreFloat4(this, V); }

    operator XMVECTOR() const { return XMLoadFloat4( this ); }

    // Comparision operators
	bool XM_CALLCONV operator == (const MHPLANE& p) const;
	bool XM_CALLCONV operator != (const MHPLANE& p) const;

    // Assignment operators
	MHPLANE& XM_CALLCONV operator= (const MHPLANE& p) { x = p.x; y = p.y; z = p.z; w = p.w; return *this; }

    // Properties
	MHVECTOR3 XM_CALLCONV Normal() const { return MHVECTOR3(x, y, z); }
	void XM_CALLCONV Normal(const MHVECTOR3& normal) { x = normal.x; y = normal.y; z = normal.z; }

	float XM_CALLCONV D() const { return w; }
	void XM_CALLCONV D(float d) { w = d; }

    // MHPLANE operations
	void XM_CALLCONV PNormalize();
	void XM_CALLCONV PNormalize(MHPLANE& result) const;

	float XM_CALLCONV PDot(const MHVECTOR4& v) const;
	float XM_CALLCONV PDotCoordinate(const MHVECTOR3& position) const;
	float XM_CALLCONV PDotNormal(const MHVECTOR3& normal) const;

    // Static functions
	static MHPLANE XM_CALLCONV Normalize(const MHPLANE& plane);
	static void XM_CALLCONV Normalize(const MHPLANE& plane, MHPLANE& result);

	static float XM_CALLCONV Dot(const MHPLANE& plane, const MHVECTOR4& v);
	static float XM_CALLCONV DotCoordinate(const MHPLANE& plane, const MHVECTOR3& position);
	static float XM_CALLCONV DotNormal(const MHPLANE& plane, const MHVECTOR3& normal);

	static void XM_CALLCONV Transform(const MHPLANE& plane, const MHMATRIX& M, MHPLANE& result);
	static MHPLANE XM_CALLCONV Transform(const MHPLANE& plane, const MHMATRIX& M);

	static void XM_CALLCONV Transform(const MHPLANE& plane, const MHQUATERNION& rotation, MHPLANE& result);
	static MHPLANE XM_CALLCONV Transform(const MHPLANE& plane, const MHQUATERNION& rotation);
        // Input quaternion must be the inverse transpose of the transformation
};

#	pragma endregion

//------------------------------------------------------------------------------
// Quaternion
#	pragma region MHQUATERNION

struct MHQUATERNION : public XMFLOAT4
{
    MHQUATERNION() : XMFLOAT4(0, 0, 0, 1.f) {}
    MHQUATERNION( float _x, float _y, float _z, float _w ) : XMFLOAT4(_x, _y, _z, _w) {}
    MHQUATERNION( const MHVECTOR3& v, float scalar ) : XMFLOAT4( v.x, v.y, v.z, scalar ) {}
    explicit MHQUATERNION( const MHVECTOR4& v ) : XMFLOAT4( v.x, v.y, v.z, v.w ) {}
    explicit MHQUATERNION(_In_reads_(4) const float *pArray) : XMFLOAT4(pArray) {}
	MHQUATERNION(FXMVECTOR& V) { XMStoreFloat4(this, V); }

    operator XMVECTOR() const { return XMLoadFloat4( this ); }

    // Comparision operators
	bool XM_CALLCONV operator == (const MHQUATERNION& q) const;
	bool XM_CALLCONV operator != (const MHQUATERNION& q) const;

    // Assignment operators
	MHQUATERNION& XM_CALLCONV operator= (const MHQUATERNION& q) { x = q.x; y = q.y; z = q.z; w = q.w; return *this; }
	MHQUATERNION& XM_CALLCONV operator+= (const MHQUATERNION& q);
	MHQUATERNION& XM_CALLCONV operator+= (float S);
	MHQUATERNION& XM_CALLCONV operator-= (const MHQUATERNION& q);
	MHQUATERNION& XM_CALLCONV operator-= (float S);
	MHQUATERNION& XM_CALLCONV operator*= (const MHQUATERNION& q);
	MHQUATERNION& XM_CALLCONV operator*= (float S);
	MHQUATERNION& XM_CALLCONV operator/= (const MHQUATERNION& q);
	MHQUATERNION& XM_CALLCONV operator/= (float S);

    // Urnary operators
	MHQUATERNION XM_CALLCONV operator+ () const { return *this; }
	MHQUATERNION XM_CALLCONV operator- () const;

    // MHQUATERNION operations
	float XM_CALLCONV QLength() const;
	float XM_CALLCONV QLengthSquared() const;

	void XM_CALLCONV QNormalize();
	void XM_CALLCONV QNormalize(MHQUATERNION& result) const;

	void XM_CALLCONV QConjugate();
	void XM_CALLCONV QConjugate(MHQUATERNION& result) const;

	void XM_CALLCONV QInverse(MHQUATERNION& result) const;

	float XM_CALLCONV QDot(const MHQUATERNION& Q) const;

    // Static functions
	static float XM_CALLCONV Length(const MHQUATERNION& Q);
	static float XM_CALLCONV LengthSquared(const MHQUATERNION& Q);

	static MHQUATERNION XM_CALLCONV Identity();
	static bool XM_CALLCONV IsIdentity(const MHQUATERNION& Q);

	static MHQUATERNION XM_CALLCONV Normalize(const MHQUATERNION& Q);
	static void XM_CALLCONV Normalize(const MHQUATERNION& Q, MHQUATERNION& result);

	static MHQUATERNION XM_CALLCONV Conjugate(const MHQUATERNION& Q);
	static void XM_CALLCONV Conjugate(const MHQUATERNION& Q, MHQUATERNION& result);

	static MHQUATERNION XM_CALLCONV Inverse(const MHQUATERNION& Q);
	static void XM_CALLCONV Inverse(const MHQUATERNION& Q, MHQUATERNION& result);

	static float XM_CALLCONV Dot(const MHQUATERNION& Q1, const MHQUATERNION& Q2);

	static MHQUATERNION XM_CALLCONV RotationAxis(const MHVECTOR3& axis, float angle);
	static MHQUATERNION XM_CALLCONV RotationRollPitchYaw(float yaw, float pitch, float roll);
	static MHQUATERNION XM_CALLCONV RotationMatrix(const MHMATRIX& M);

	static void XM_CALLCONV Barycentric(const MHQUATERNION& Q1, const MHQUATERNION& Q2, const MHQUATERNION& Q3, float f, float g, MHQUATERNION& result);
	static MHQUATERNION XM_CALLCONV Barycentric(const MHQUATERNION& Q1, const MHQUATERNION& Q2, const MHQUATERNION& Q3, float f, float g);

	static void XM_CALLCONV Barycentric(const MHQUATERNION& Q1, const MHQUATERNION& Q2, const MHQUATERNION& Q3, FXMVECTOR& f, FXMVECTOR& g, MHQUATERNION& result);
	static MHQUATERNION XM_CALLCONV Barycentric(const MHQUATERNION& Q1, const MHQUATERNION& Q2, const MHQUATERNION& Q3, FXMVECTOR& f, FXMVECTOR& g);

	static void XM_CALLCONV Lerp(const MHQUATERNION& q1, const MHQUATERNION& q2, float t, MHQUATERNION& result);
	static MHQUATERNION XM_CALLCONV Lerp(const MHQUATERNION& q1, const MHQUATERNION& q2, float t);

	static void XM_CALLCONV Slerp(const MHQUATERNION& q1, const MHQUATERNION& q2, float t, MHQUATERNION& result);
	static MHQUATERNION XM_CALLCONV Slerp(const MHQUATERNION& q1, const MHQUATERNION& q2, float t);

	static void XM_CALLCONV Concatenate(const MHQUATERNION& q1, const MHQUATERNION& q2, MHQUATERNION& result);
	static MHQUATERNION XM_CALLCONV Concatenate(const MHQUATERNION& q1, const MHQUATERNION& q2);
};

// Binary operators
MHQUATERNION XM_CALLCONV operator+ (const MHQUATERNION& Q1, const MHQUATERNION& Q2);
MHQUATERNION XM_CALLCONV operator+ (const MHQUATERNION& Q, float S);
MHQUATERNION XM_CALLCONV operator+ (float S, const MHQUATERNION& Q);
MHQUATERNION XM_CALLCONV operator- (const MHQUATERNION& Q1, const MHQUATERNION& Q2);
MHQUATERNION XM_CALLCONV operator- (const MHQUATERNION& Q, float S);
MHQUATERNION XM_CALLCONV operator- (float S, const MHQUATERNION& Q);
MHQUATERNION XM_CALLCONV operator* (const MHQUATERNION& Q1, const MHQUATERNION& Q2);
MHQUATERNION XM_CALLCONV operator* (const MHQUATERNION& Q, float S);
MHQUATERNION XM_CALLCONV operator* (float S, const MHQUATERNION& Q);
MHQUATERNION XM_CALLCONV operator/ (const MHQUATERNION& Q1, const MHQUATERNION& Q2);
MHQUATERNION XM_CALLCONV operator/ (const MHQUATERNION& Q, float S);
MHQUATERNION XM_CALLCONV operator/ (float S, const MHQUATERNION& Q);

#	pragma endregion

//------------------------------------------------------------------------------
// Color
#	pragma region MHCOLOR

struct MHCOLOR : public XMFLOAT4
{
    MHCOLOR() : XMFLOAT4(0, 0, 0, 1.f) {}
    MHCOLOR( float _r, float _g, float _b ) : XMFLOAT4(_r, _g, _b, 1.f) {}
    MHCOLOR( float _r, float _g, float _b, float _a ) : XMFLOAT4(_r, _g, _b, _a) {}
    explicit MHCOLOR( const MHVECTOR3& clr ) : XMFLOAT4( clr.x, clr.y, clr.z, 1.f ) {}
    explicit MHCOLOR( const MHVECTOR4& clr ) : XMFLOAT4( clr.x, clr.y, clr.z, clr.w ) {}
    explicit MHCOLOR(_In_reads_(4) const float *pArray) : XMFLOAT4(pArray) {}
	MHCOLOR(FXMVECTOR& V) { XMStoreFloat4(this, V); }

    explicit MHCOLOR( const PackedVector::XMCOLOR& Packed );
        // BGRA Direct3D 9 D3DCOLOR packed color
    
    explicit MHCOLOR( const PackedVector::XMUBYTEN4& Packed );
        // RGBA XNA Game Studio packed color

    operator XMVECTOR() const { return XMLoadFloat4( this ); }
    operator const float*() const { return reinterpret_cast<const float*>(this); }

    // Comparision operators
	bool XM_CALLCONV operator == (const MHCOLOR& c) const;
	bool XM_CALLCONV operator != (const MHCOLOR& c) const;

    // Assignment operators
	MHCOLOR& XM_CALLCONV operator= (const MHCOLOR& c) { x = c.x; y = c.y; z = c.z; w = c.w; return *this; }
	MHCOLOR& XM_CALLCONV operator+= (const MHCOLOR& c);
	MHCOLOR& XM_CALLCONV operator+= (float S);
	MHCOLOR& XM_CALLCONV operator-= (const MHCOLOR& c);
	MHCOLOR& XM_CALLCONV operator-= (float S);
	MHCOLOR& XM_CALLCONV operator*= (const MHCOLOR& c);
	MHCOLOR& XM_CALLCONV operator*= (float S);
	MHCOLOR& XM_CALLCONV operator/= (const MHCOLOR& c);
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
	static MHVECTOR3 XM_CALLCONV ToVector3(const MHCOLOR& c);
	static MHVECTOR4 XM_CALLCONV ToVector4(const MHCOLOR& c);

	static MHVECTOR4 XM_CALLCONV HSLToRGB(const MHVECTOR4& c);
	static MHVECTOR4 XM_CALLCONV HSVToRGB(const MHVECTOR4& c);

	static MHVECTOR4 XM_CALLCONV RGBToHSL(const MHVECTOR4& c);
	static MHVECTOR4 XM_CALLCONV RGBToHSV(const MHVECTOR4& c);

	static MHVECTOR4 XM_CALLCONV RGBToXYZ(const MHVECTOR4& c);
	static MHVECTOR4 XM_CALLCONV RGBToYUV(const MHVECTOR4& c);

	static MHVECTOR4 XM_CALLCONV RGBToYUV_HD(const MHVECTOR4& c);
	static MHVECTOR4 XM_CALLCONV SRGBToXYZ(const MHVECTOR4& c);

	static MHVECTOR4 XM_CALLCONV XYZToRGB(const MHVECTOR4& c);
	static MHVECTOR4 XM_CALLCONV XYZToSRGB(const MHVECTOR4& c);

	static MHVECTOR4 XM_CALLCONV YUVToRGB(const MHVECTOR4& c);
	static MHVECTOR4 XM_CALLCONV YUVToRGB_HD(const MHVECTOR4& c);

	static MHCOLOR XM_CALLCONV Negate(const MHCOLOR& c);
	static void XM_CALLCONV Negate(const MHCOLOR& c, MHCOLOR& result);

	static MHCOLOR XM_CALLCONV Saturate(const MHCOLOR& c);
	static void XM_CALLCONV Saturate(const MHCOLOR& c, MHCOLOR& result);

	static MHCOLOR XM_CALLCONV Premultiply(const MHCOLOR& c);
	static void XM_CALLCONV Premultiply(const MHCOLOR& c, MHCOLOR& result);

	static MHCOLOR XM_CALLCONV AdjustSaturation(const MHCOLOR& c, float sat);
	static void XM_CALLCONV AdjustSaturation(const MHCOLOR& c, float sat, MHCOLOR& result);

	static MHCOLOR XM_CALLCONV AdjustContrast(const MHCOLOR& c, float contrast);
	static void XM_CALLCONV AdjustContrast(const MHCOLOR& c, float contrast, MHCOLOR& result);

	static void XM_CALLCONV Modulate(const MHCOLOR& c1, const MHCOLOR& c2, MHCOLOR& result);
	static MHCOLOR XM_CALLCONV Modulate(const MHCOLOR& c1, const MHCOLOR& c2);

	static void XM_CALLCONV Lerp(const MHCOLOR& c1, const MHCOLOR& c2, float t, MHCOLOR& result);
	static MHCOLOR XM_CALLCONV Lerp(const MHCOLOR& c1, const MHCOLOR& c2, float t);
};

// Binary operators
MHCOLOR XM_CALLCONV operator+ (const MHCOLOR& C1, const MHCOLOR& C2);
MHCOLOR XM_CALLCONV operator+ (const MHCOLOR& C, float S);
MHCOLOR XM_CALLCONV operator+ (float S, const MHCOLOR& C);
MHCOLOR XM_CALLCONV operator- (const MHCOLOR& C1, const MHCOLOR& C2);
MHCOLOR XM_CALLCONV operator- (const MHCOLOR& C1, float S);
MHCOLOR XM_CALLCONV operator- (float S, const MHCOLOR& C);
MHCOLOR XM_CALLCONV operator* (const MHCOLOR& C1, const MHCOLOR& C2);
MHCOLOR XM_CALLCONV operator* (const MHCOLOR& C, float S);
MHCOLOR XM_CALLCONV operator* (float S, const MHCOLOR& C);
MHCOLOR XM_CALLCONV operator/ (const MHCOLOR& C1, const MHCOLOR& C2);
MHCOLOR XM_CALLCONV operator/ (const MHCOLOR& C, float S);
MHCOLOR XM_CALLCONV operator/ (float S, const MHCOLOR& C);

#	pragma endregion

//------------------------------------------------------------------------------
// Line
#	pragma region MHLINE

class MHLINE
{
public:
	MHVECTOR3 spoint;
	MHVECTOR3 dpoint;

	MHLINE(){}

	MHLINE(const MHVECTOR3& start, const MHVECTOR3& end) : spoint(start), dpoint(end){}

	MHLINE(const MHLINE& line) : spoint(line.spoint), dpoint(line.dpoint){}

	// Comparision operators
	bool XM_CALLCONV operator == (const MHLINE& line) const;
	bool XM_CALLCONV operator != (const MHLINE& line) const;

	// Assignment operators
	MHLINE& operator = (const MHLINE& line) { spoint = line.spoint;dpoint = line.dpoint; return *this; }

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

//------------------------------------------------------------------------------
// Ray
#	pragma region MHRAY

class MHRAY
{
public:
    MHVECTOR3 position;
    MHVECTOR3 direction;

    MHRAY() : position(0,0,0), direction(0,0,1) {}
    MHRAY( const MHVECTOR3& pos, const MHVECTOR3& dir ) : position(pos), direction(dir) {}

    // Comparision operators
	bool XM_CALLCONV operator == (const MHRAY& r) const;
	bool XM_CALLCONV operator != (const MHRAY& r) const;

    // MHRAY operations
	bool XM_CALLCONV Intersects(const BoundingSphere& sphere, _Out_ float& Dist) const;
	bool XM_CALLCONV Intersects(const BoundingBox& box, _Out_ float& Dist) const;
	bool XM_CALLCONV Intersects(const MHVECTOR3& tri0, const MHVECTOR3& tri1, const MHVECTOR3& tri2, _Out_ float& Dist) const;
	bool XM_CALLCONV Intersects(const MHPLANE& plane, _Out_ float& Dist) const;
};

#	pragma endregion

//  ------------------------------------------------------------------------------
/// XMFLOAT2 operators
//--------------------------------------------------------------------------------
#	pragma region XMFLOAT2 operators

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

//  ------------------------------------------------------------------------------
/// XMFLOAT3 operators
//--------------------------------------------------------------------------------
#	pragma region XMFLOAT3 operators

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

//  ------------------------------------------------------------------------------
/// XMFLOAT4 operators
//--------------------------------------------------------------------------------
#pragma region XMFLOAT4 operators

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

#include "DirectXMathHelper.inl"

namespace_DirectX_end; // namespace DirectX

//------------------------------------------------------------------------------
// Support for DirectXMathHelper and Standard C++ Library containers
namespace std
{
	using namespace DirectX;

    template<> struct less<MHVECTOR2>
    {
		bool operator()(const MHVECTOR2& V1, const MHVECTOR2& V2) const
        {
            return ( (V1.x < V2.x) || ((V1.x == V2.x) && (V1.y < V2.y)) );
        }
    };

    template<> struct less<MHVECTOR3>
    {
		bool operator()(const MHVECTOR3& V1, const MHVECTOR3& V2) const
        {
            return ( (V1.x < V2.x)
                     || ((V1.x == V2.x) && (V1.y < V2.y))
                     || ((V1.x == V2.x) && (V1.y == V2.y) && (V1.z < V2.z)) );
        }
    };

    template<> struct less<MHVECTOR4>
    {
		bool operator()(const MHVECTOR4& V1, const MHVECTOR4& V2) const
        {
            return ( (V1.x < V2.x)
                     || ((V1.x == V2.x) && (V1.y < V2.y))
                     || ((V1.x == V2.x) && (V1.y == V2.y) && (V1.z < V2.z))
                     || ((V1.x == V2.x) && (V1.y == V2.y) && (V1.z == V2.z) && (V1.w < V2.w)) );
        }
    };

    template<> struct less<MHMATRIX>
    {
		bool operator()(const MHMATRIX& M1, const MHMATRIX& M2) const
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
		bool operator()(const MHPLANE& P1, const MHPLANE& P2) const
        {
            return ( (P1.x < P2.x)
                     || ((P1.x == P2.x) && (P1.y < P2.y))
                     || ((P1.x == P2.x) && (P1.y == P2.y) && (P1.z < P2.z))
                     || ((P1.x == P2.x) && (P1.y == P2.y) && (P1.z == P2.z) && (P1.w < P2.w)) );
        }
    };

    template<> struct less<MHQUATERNION>
    {
		bool operator()(const MHQUATERNION& Q1, const MHQUATERNION& Q2) const
        {
            return ( (Q1.x < Q2.x)
                     || ((Q1.x == Q2.x) && (Q1.y < Q2.y))
                     || ((Q1.x == Q2.x) && (Q1.y == Q2.y) && (Q1.z < Q2.z))
                     || ((Q1.x == Q2.x) && (Q1.y == Q2.y) && (Q1.z == Q2.z) && (Q1.w < Q2.w)) );
        }
    };

    template<> struct less<MHCOLOR>
    {
		bool operator()(const MHCOLOR& C1, const MHCOLOR& C2) const
        {
            return ( (C1.x < C2.x)
                     || ((C1.x == C2.x) && (C1.y < C2.y))
                     || ((C1.x == C2.x) && (C1.y == C2.y) && (C1.z < C2.z))
                     || ((C1.x == C2.x) && (C1.y == C2.y) && (C1.z == C2.z) && (C1.w < C2.w)) );
        }
    };

    template<> struct less<MHRAY>
    {
		bool operator()(const MHRAY& R1, const MHRAY& R2) const
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
