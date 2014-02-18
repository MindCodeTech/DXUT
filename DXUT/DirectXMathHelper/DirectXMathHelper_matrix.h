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
// 4x4 MHMATRIX (assumes right-handed coordinates)
#	pragma region MHMATRIX

#if (defined(_M_IX86) || defined(_M_X64) || defined(_M_ARM)) && defined(_XM_NO_INTRINSICS_)
struct MHMATRIX: public XMFLOAT4X4
#else
__declspec(align(16)) struct MHMATRIX : public XMFLOAT4X4
#endif
{
#ifdef _XM_NO_INTRINSICS_
	union
	{
		XMVECTOR r[4];
		struct
		{
			float _11, _12, _13, _14;
			float _21, _22, _23, _24;
			float _31, _32, _33, _34;
			float _41, _42, _43, _44;
		};
		float m[4][4];
	};
#else
	XMVECTOR r[4];
#endif

/*
struct MHMATRIX : public XMFLOAT4X4
{*/
    MHMATRIX() : XMFLOAT4X4( 1.0f, 0.0f, 0.0f, 0.0f,
                             0.0f, 1.0f, 0.0f, 0.0f,
							 0.0f, 0.0f, 1.0f, 0.0f,
							 0.0f, 0.0f, 0.0f, 1.0f) {}

	MHMATRIX(FXMVECTOR R0, FXMVECTOR R1, FXMVECTOR R2, CXMVECTOR R3) { r[0] = R0; r[1] = R1; r[2] = R2; r[3] = R3; }

    MHMATRIX(float m00, float m01, float m02, float m03,
			 float m10, float m11, float m12, float m13,
			 float m20, float m21, float m22, float m23,
			 float m30, float m31, float m32, float m33) : XMFLOAT4X4(m00, m01, m02, m03,
																	  m10, m11, m12, m13,
                                                                      m20, m21, m22, m23,
                                                                      m30, m31, m32, m33) {}

    explicit MHMATRIX( const MHVECTOR3& r0, const MHVECTOR3& r1, const MHVECTOR3& r2 ) : XMFLOAT4X4( r0.x, r0.y, r0.z, 0.0f,
																									 r1.x, r1.y, r1.z, 0.0f,
																									 r2.x, r2.y, r2.z, 0.0f,
																									 0.0f, 0.0f, 0.0f, 1.0f ) {}

    explicit MHMATRIX( const MHVECTOR4& r0, const MHVECTOR4& r1, const MHVECTOR4& r2, const MHVECTOR4& r3 ) : XMFLOAT4X4( r0.x, r0.y, r0.z, r0.w,
																														  r1.x, r1.y, r1.z, r1.w,
																														  r2.x, r2.y, r2.z, r2.w,
																														  r3.x, r3.y, r3.z, r3.w ) {}
	
	explicit MHMATRIX(_In_reads_(16) const float *pArray) : XMFLOAT4X4(pArray) {}

    MHMATRIX( CXMMATRIX M ) { XMStoreFloat4x4( this, M ); }

    operator XMMATRIX() const { return XMLoadFloat4x4( this ); }

    // Comparison operators
	bool XM_CALLCONV operator == (FMHMATRIX& M) const;
	bool XM_CALLCONV operator != (FMHMATRIX& M) const;

    // Assignment operators
	MHMATRIX& operator= (FMHMATRIX& M) { memcpy_s(this, sizeof(float)* 16, &M, sizeof(float)* 16); return *this; }

	MHMATRIX& XM_CALLCONV operator+= (FMHMATRIX& M);
	MHMATRIX& XM_CALLCONV operator+= (float S);
	MHMATRIX& XM_CALLCONV operator-= (FMHMATRIX& M);
	MHMATRIX& XM_CALLCONV operator-= (float S);
	MHMATRIX& XM_CALLCONV operator*= (FMHMATRIX& M);
	MHMATRIX& XM_CALLCONV operator*= (float S);
	MHMATRIX& XM_CALLCONV operator/= (FMHMATRIX& M);
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
	static MHVECTOR3 XM_CALLCONV Up(FMHMATRIX& M);
	static void XM_CALLCONV Up(const MHVECTOR3& V, FMHMATRIX& M, MHVECTOR3& result);

	static MHVECTOR3 XM_CALLCONV Down(FMHMATRIX& M);
	static void XM_CALLCONV Down(const MHVECTOR3& V, FMHMATRIX& M, MHVECTOR3& result);

	static MHVECTOR3 XM_CALLCONV Right(FMHMATRIX& M);
	static void XM_CALLCONV Right(const MHVECTOR3& V, FMHMATRIX& M, MHVECTOR3& result);

	static MHVECTOR3 XM_CALLCONV Left(FMHMATRIX& M);
	static void XM_CALLCONV Left(const MHVECTOR3& V, FMHMATRIX& M, MHVECTOR3& result);

	static MHVECTOR3 XM_CALLCONV Forward(FMHMATRIX& M);
	static void XM_CALLCONV Forward(const MHVECTOR3& V, FMHMATRIX& M, MHVECTOR3& result);

	static MHVECTOR3 XM_CALLCONV Backward(FMHMATRIX& M);
	static void XM_CALLCONV Backward(const MHVECTOR3& V, FMHMATRIX& M, MHVECTOR3& result);

	static MHVECTOR3 XM_CALLCONV Translate(FMHMATRIX& M);
	static void XM_CALLCONV Translate(const MHVECTOR3& V, FMHMATRIX& M, MHVECTOR3& result);

	// Matrix operations
	static bool XM_CALLCONV Decompose(FMHMATRIX& M, MHVECTOR3& scale, MHQUATERNION& rotation, MHVECTOR3& translation);

	static MHMATRIX XM_CALLCONV Transpose(FMHMATRIX& M);
	static void XM_CALLCONV Transpose(FMHMATRIX& M, MHMATRIX& result);
	static MHMATRIX XM_CALLCONV MultiplyTranspose(FMHMATRIX& M1, FMHMATRIX& M2);
	static void XM_CALLCONV MultiplyTranspose(FMHMATRIX& M1, FMHMATRIX& M2, MHMATRIX& result);

	static MHMATRIX XM_CALLCONV Inverse(FMHMATRIX& M);
	static void XM_CALLCONV Inverse(FMHMATRIX& M, MHMATRIX& result);

	static float XM_CALLCONV Determinant(FMHMATRIX& M);

	// Matrix functions
	static MHMATRIX XM_CALLCONV MIdentity();
	static MHMATRIX XM_CALLCONV Identity();
	static bool XM_CALLCONV IsIdentity( FMHMATRIX& M);

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

	static void XM_CALLCONV Lerp(FMHMATRIX& M1, FMHMATRIX& M2, float t, MHMATRIX& result);
	static MHMATRIX XM_CALLCONV Lerp(FMHMATRIX& M1, FMHMATRIX& M2, float t);

	static void XM_CALLCONV Transform(FMHMATRIX& M, const MHQUATERNION& rotation, MHMATRIX& result);
	static MHMATRIX XM_CALLCONV Transform(FMHMATRIX& M, const MHQUATERNION& rotation);
};

// Binary operators
MHMATRIX XM_CALLCONV operator+ (FMHMATRIX& M1, FMHMATRIX& M2);
MHMATRIX XM_CALLCONV operator+ (FMHMATRIX& M, float S);
MHMATRIX XM_CALLCONV operator+ (float S, FMHMATRIX& M);
MHMATRIX XM_CALLCONV operator- (FMHMATRIX& M1, FMHMATRIX& M2);
MHMATRIX XM_CALLCONV operator- (FMHMATRIX& M, float S);
MHMATRIX XM_CALLCONV operator- (float S, FMHMATRIX& M);
MHMATRIX XM_CALLCONV operator* (FMHMATRIX& M1, FMHMATRIX& M2);
MHMATRIX XM_CALLCONV operator* (FMHMATRIX& M, float S);
MHMATRIX XM_CALLCONV operator* (float S, FMHMATRIX& M);
MHMATRIX XM_CALLCONV operator/ (FMHMATRIX& M1, FMHMATRIX& M2);
MHMATRIX XM_CALLCONV operator/ (FMHMATRIX& M, float S);
MHMATRIX XM_CALLCONV operator/ (float S, FMHMATRIX& M);
    // Element-wise divide

#	pragma endregion

namespace_DirectX_end; // namespace DirectX

#ifdef __cplusplus
EXTERN_CC_END
#endif
