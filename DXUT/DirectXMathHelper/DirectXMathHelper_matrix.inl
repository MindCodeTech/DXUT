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

# pragma region MHMATRIX

//------------------------------------------------------------------------------
/// MHMATRIX operations
//------------------------------------------------------------------------------
#pragma region operations

inline bool XM_CALLCONV MHMATRIX::MDecompose(MHVECTOR3& scale, MHQUATERNION& rotation, MHVECTOR3& translation)
{
    using namespace DirectX;

    XMVECTOR s, r, t;

    if ( !XMMatrixDecompose( &s, &r, &t, *this ) )
        return false;

    XMStoreFloat3( &scale, s );
    XMStoreFloat4( &rotation, r );
    XMStoreFloat3( &translation, t );

    return true;
}

inline MHMATRIX XM_CALLCONV MHMATRIX::MTranspose() const
{
    using namespace DirectX;
    XMMATRIX M = XMLoadFloat4x4( this );
    MHMATRIX R;
    XMStoreFloat4x4( &R, XMMatrixTranspose( M ) );
    return R;
}

inline void XM_CALLCONV MHMATRIX::MTranspose(MHMATRIX& result) const
{
    using namespace DirectX;
    XMMATRIX M = XMLoadFloat4x4( this );
    XMStoreFloat4x4( &result, XMMatrixTranspose( M ) );
}

inline MHMATRIX XM_CALLCONV MHMATRIX::MInvert() const
{
    using namespace DirectX;
    XMMATRIX M = XMLoadFloat4x4( this );
    MHMATRIX R;
    XMVECTOR det;
    XMStoreFloat4x4( &R, XMMatrixInverse( &det, M ) );
    return R;
}

inline void XM_CALLCONV MHMATRIX::MInvert(MHMATRIX& result) const
{
    using namespace DirectX;
    XMMATRIX M = XMLoadFloat4x4( this );
    XMVECTOR det;
    XMStoreFloat4x4( &result, XMMatrixInverse( &det, M ) );
}

inline float XM_CALLCONV MHMATRIX::MDeterminant() const
{
    using namespace DirectX;
    XMMATRIX M = XMLoadFloat4x4( this );
    return XMVectorGetX( XMMatrixDeterminant( M ) );
}

//------------------------------------------------------------------------------
// Static functions
//------------------------------------------------------------------------------

// Properties
inline MHVECTOR3 XM_CALLCONV MHMATRIX::Up(FMHMATRIX& M)
{
	using namespace DirectX;
	MHMATRIX floatM;
	XMStoreFloat4x4(&floatM, M);
	MHVECTOR3 RV = (MHVECTOR3)(floatM._21, floatM._22, floatM._23);
	MHVECTOR3 R;
	XMStoreFloat3(&R, RV);
	return R;
}

inline void XM_CALLCONV MHMATRIX::Up(const MHVECTOR3& V, FMHMATRIX& M, MHVECTOR3& result)
{
	using namespace DirectX;
	MHMATRIX floatM;
	XMStoreFloat4x4(&floatM, M);
	MHVECTOR3 R = (MHVECTOR3)(floatM._21 = V.x, floatM._22 = V.y, floatM._23 = V.z);
	XMStoreFloat3(&result, R);
}

inline MHVECTOR3 XM_CALLCONV MHMATRIX::Down(FMHMATRIX& M)
{ 
	using namespace DirectX;
	MHMATRIX floatM;
	XMStoreFloat4x4(&floatM, M);
	MHVECTOR3 RV = (MHVECTOR3)(-floatM._21, -floatM._22, -floatM._23);
	MHVECTOR3 R;
	XMStoreFloat3(&R, RV);
	return R;
}

inline void XM_CALLCONV MHMATRIX::Down(const MHVECTOR3& V, FMHMATRIX& M, MHVECTOR3& result)
{ 
	using namespace DirectX;
	MHMATRIX floatM;
	XMStoreFloat4x4(&floatM, M);
	MHVECTOR3 R = (MHVECTOR3)(floatM._21 = -V.x, floatM._22 = -V.y, floatM._23 = -V.z);
	XMStoreFloat3(&result, R);
}

inline MHVECTOR3 XM_CALLCONV MHMATRIX::Right(FMHMATRIX& M)
{
	using namespace DirectX;
	MHMATRIX floatM;
	XMStoreFloat4x4(&floatM, M);
	MHVECTOR3 RV = (MHVECTOR3)(floatM._11, floatM._12, floatM._13);
	MHVECTOR3 R;
	XMStoreFloat3(&R, RV);
	return R;
}

inline void XM_CALLCONV MHMATRIX::Right(const MHVECTOR3& V, FMHMATRIX& M, MHVECTOR3& result)
{
	using namespace DirectX;
	MHMATRIX floatM;
	XMStoreFloat4x4(&floatM, M);
	MHVECTOR3 R = (MHVECTOR3)(floatM._11 = V.x, floatM._12 = V.y, floatM._13 = V.z);
	XMStoreFloat3(&result, R);
}

inline MHVECTOR3 XM_CALLCONV MHMATRIX::Left(FMHMATRIX& M)
{
	using namespace DirectX;
	MHMATRIX floatM;
	XMStoreFloat4x4(&floatM, M);
	MHVECTOR3 RV = (MHVECTOR3)(-floatM._11, -floatM._12, -floatM._13);
	MHVECTOR3 R;
	XMStoreFloat3(&R, RV);
	return R;
}

inline void XM_CALLCONV MHMATRIX::Left(const MHVECTOR3& V, FMHMATRIX& M, MHVECTOR3& result)
{
	using namespace DirectX;
	MHMATRIX floatM;
	XMStoreFloat4x4(&floatM, M);
	MHVECTOR3 R = (MHVECTOR3)(floatM._11 = -V.x, floatM._12 = -V.y, floatM._13 = -V.z);
	XMStoreFloat3(&result, R);
}

inline MHVECTOR3 XM_CALLCONV MHMATRIX::Forward(FMHMATRIX& M)
{
	using namespace DirectX;
	MHMATRIX floatM;
	XMStoreFloat4x4(&floatM, M);
	MHVECTOR3 RV = (MHVECTOR3)(-floatM._31, -floatM._32, -floatM._33);
	MHVECTOR3 R;
	XMStoreFloat3(&R, RV);
	return R;
}

inline void XM_CALLCONV MHMATRIX::Forward(const MHVECTOR3& V, FMHMATRIX& M, MHVECTOR3& result)
{
	using namespace DirectX;
	MHMATRIX floatM;
	XMStoreFloat4x4(&floatM, M);
	MHVECTOR3 R = (MHVECTOR3)(floatM._31 = -V.x, floatM._32 = -V.y, floatM._33 = -V.z);
	XMStoreFloat3(&result, R);
}

inline MHVECTOR3 XM_CALLCONV MHMATRIX::Backward(FMHMATRIX& M)
{
	using namespace DirectX;
	MHMATRIX floatM;
	XMStoreFloat4x4(&floatM, M);
	MHVECTOR3 RV = (MHVECTOR3)(floatM._31, floatM._32, floatM._33);
	MHVECTOR3 R;
	XMStoreFloat3(&R, RV);
	return R;
}

inline void XM_CALLCONV MHMATRIX::Backward(const MHVECTOR3& V, FMHMATRIX& M, MHVECTOR3& result)
{
	using namespace DirectX;
	MHMATRIX floatM;
	XMStoreFloat4x4(&floatM, M);
	MHVECTOR3 R = (MHVECTOR3)(floatM._31 = V.x, floatM._32 = V.y, floatM._33 = V.z);
	XMStoreFloat3(&result, R);
}

inline MHVECTOR3 XM_CALLCONV MHMATRIX::Translate(FMHMATRIX& M)
{
	using namespace DirectX;
	MHMATRIX floatM;
	XMStoreFloat4x4(&floatM, M);
	MHVECTOR3 RV = (MHVECTOR3)(floatM._41, floatM._42, floatM._43);
	MHVECTOR3 R;
	XMStoreFloat3(&R, RV);
	return R;
}

inline void XM_CALLCONV MHMATRIX::Translate(const MHVECTOR3& V, FMHMATRIX& M, MHVECTOR3& result)
{
	using namespace DirectX;
	MHMATRIX floatM;
	XMStoreFloat4x4(&floatM, M);
	MHVECTOR3 R = (MHVECTOR3)(floatM._41 = V.x, floatM._42 = V.y, floatM._43 = V.z);
	XMStoreFloat3(&result, R);
}

// Matrix operations
inline bool XM_CALLCONV MHMATRIX::Decompose(FMHMATRIX& M, MHVECTOR3& scale, MHQUATERNION& rotation, MHVECTOR3& translation)
{
	using namespace DirectX;

	XMVECTOR s, r, t;

	if (!XMMatrixDecompose(&s, &r, &t, M))
		return false;

	XMStoreFloat3(&scale, s);
	XMStoreFloat4(&rotation, r);
	XMStoreFloat3(&translation, t);

	return true;
}

inline MHMATRIX XM_CALLCONV MHMATRIX::Transpose(FMHMATRIX& M)
{
	using namespace DirectX;
	XMMATRIX MT = XMLoadFloat4x4(&M);
	MHMATRIX R;
	XMStoreFloat4x4(&R, XMMatrixTranspose(MT));
	return R;
}

inline void XM_CALLCONV MHMATRIX::Transpose(FMHMATRIX& M, MHMATRIX& result)
{
	using namespace DirectX;
	XMMATRIX MT = XMLoadFloat4x4(&M);
	XMStoreFloat4x4(&result, XMMatrixTranspose(MT));
}

inline MHMATRIX XM_CALLCONV MHMATRIX::MultiplyTranspose(FMHMATRIX& M1, FMHMATRIX& M2)
{
	using namespace DirectX;
	XMMATRIX MT1 = XMLoadFloat4x4(&M1);
	XMMATRIX MT2 = XMLoadFloat4x4(&M2);
	MHMATRIX R;
	XMStoreFloat4x4(&R, XMMatrixMultiplyTranspose(MT1, MT2));
	return R;
}

inline void XM_CALLCONV MHMATRIX::MultiplyTranspose(FMHMATRIX& M1, FMHMATRIX& M2, MHMATRIX& result)
{
	using namespace DirectX;
	XMMATRIX MT1 = XMLoadFloat4x4(&M1);
	XMMATRIX MT2 = XMLoadFloat4x4(&M2);
	XMStoreFloat4x4(&result, XMMatrixMultiplyTranspose(MT1, MT2));
}

inline MHMATRIX XM_CALLCONV MHMATRIX::Inverse(FMHMATRIX& M)
{
	using namespace DirectX;
	XMMATRIX MR = XMLoadFloat4x4(&M);
	XMVECTOR det;
	MHMATRIX R;
	XMStoreFloat4x4(&R, XMMatrixInverse(&det, MR));
	return R;
}

inline void XM_CALLCONV MHMATRIX::Inverse(FMHMATRIX& M, MHMATRIX& result)
{
	using namespace DirectX;
	XMMATRIX MR = XMLoadFloat4x4(&M);
	XMVECTOR det;
	XMStoreFloat4x4(&result, XMMatrixInverse(&det, MR));
}

inline float XM_CALLCONV MHMATRIX::Determinant(FMHMATRIX& M)
{
	using namespace DirectX;
	XMMATRIX MR = XMLoadFloat4x4(&M);
	return XMVectorGetX(XMMatrixDeterminant(MR));
}

// Matrix functions
inline MHMATRIX XM_CALLCONV MHMATRIX::MIdentity()
{
    using namespace DirectX;
    return MHMATRIX( 1.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 1.0f, 0.0f, 0.0f,
					 0.0f, 0.0f, 1.0f, 0.0f,
					 0.0f, 0.0f, 0.0f, 1.0f);
}

inline MHMATRIX XM_CALLCONV MHMATRIX::Identity()
{
	using namespace DirectX;
	XMMATRIX M = XMMatrixIdentity();
	return M;
}

inline bool XM_CALLCONV MHMATRIX::IsIdentity(FMHMATRIX& M)
{
	using namespace DirectX;
	return XMMatrixIsIdentity(M);
}

inline MHMATRIX XM_CALLCONV MHMATRIX::Translation(const MHVECTOR3& position)
{
    using namespace DirectX;
    MHMATRIX R;
    XMStoreFloat4x4( &R, XMMatrixTranslation( position.x, position.y, position.z ) );
    return R;
}

inline MHMATRIX XM_CALLCONV MHMATRIX::Translation(float x, float y, float z)
{
    using namespace DirectX;
    MHMATRIX R;
    XMStoreFloat4x4( &R, XMMatrixTranslation( x, y, z ) );
    return R;
}

inline MHMATRIX XM_CALLCONV MHMATRIX::TranslationFromVector(FXMVECTOR& V)
{
	using namespace DirectX;
	//XMVECTOR v = XMLoadFloat3(&scales);
	MHMATRIX R;
	XMStoreFloat4x4(&R, XMMatrixTranslationFromVector(V));
	return R;
}

inline MHMATRIX XM_CALLCONV MHMATRIX::Scaling(const MHVECTOR3& scales)
{
    using namespace DirectX;
    MHMATRIX R;
    XMStoreFloat4x4( &R, XMMatrixScaling( scales.x, scales.y, scales.z ) );
    return R;
}

inline MHMATRIX XM_CALLCONV MHMATRIX::Scaling(float xs, float ys, float zs)
{
    using namespace DirectX;
    MHMATRIX R;
    XMStoreFloat4x4( &R, XMMatrixScaling( xs, ys, zs ) );
    return R;
}

inline MHMATRIX XM_CALLCONV MHMATRIX::Scaling(float scale)
{
    using namespace DirectX;
    MHMATRIX R;
    XMStoreFloat4x4( &R, XMMatrixScaling( scale, scale, scale ) );
    return R;
}

inline MHMATRIX XM_CALLCONV MHMATRIX::ScalingFromVector(FXMVECTOR& V)
{
	using namespace DirectX;
	//XMVECTOR vscales = XMLoadFloat3(&scales);
	MHMATRIX R;
	XMStoreFloat4x4(&R, XMMatrixScalingFromVector(V));
	return R;
}

inline MHMATRIX XM_CALLCONV MHMATRIX::RotationX(float radians)
{
    using namespace DirectX;
    MHMATRIX R;
    XMStoreFloat4x4( &R, XMMatrixRotationX( radians ) );
    return R;
}

inline MHMATRIX XM_CALLCONV MHMATRIX::RotationY(float radians)
{
    using namespace DirectX;
    MHMATRIX R;
    XMStoreFloat4x4( &R, XMMatrixRotationY( radians ) );
    return R;
}

inline MHMATRIX XM_CALLCONV MHMATRIX::RotationZ(float radians)
{
    using namespace DirectX;
    MHMATRIX R;
    XMStoreFloat4x4( &R, XMMatrixRotationZ( radians ) );
    return R;
}

inline MHMATRIX XM_CALLCONV MHMATRIX::RotationAxisAngle(const MHVECTOR3& axis, float angle)
{
    using namespace DirectX;
    MHMATRIX R;
    XMVECTOR a = XMLoadFloat3( &axis );
    XMStoreFloat4x4( &R, XMMatrixRotationAxis( a, angle ) );
    return R;
}

inline MHMATRIX XM_CALLCONV MHMATRIX::RotationNormal(const MHVECTOR3& axis, float angle)
{
	using namespace DirectX;
	MHMATRIX R;
	XMVECTOR a = XMLoadFloat3(&axis);
	XMStoreFloat4x4(&R, XMMatrixRotationNormal(a, angle));
	return R;
}

inline MHMATRIX XM_CALLCONV MHMATRIX::RotationQuaternion(const MHQUATERNION& quat)
{
	using namespace DirectX;
	MHMATRIX R;
	XMVECTOR quatv = XMLoadFloat4(&quat);
	XMStoreFloat4x4(&R, XMMatrixRotationQuaternion(quatv));
	return R;
}

inline MHMATRIX XM_CALLCONV MHMATRIX::RotationRollPitchYaw(float yaw, float pitch, float roll)
{
	using namespace DirectX;
	MHMATRIX R;
	XMStoreFloat4x4(&R, XMMatrixRotationRollPitchYaw(pitch, yaw, roll));
	return R;
}

inline MHMATRIX XM_CALLCONV MHMATRIX::PerspectiveFov(float fov, float aspectRatio, float nearPlane, float farPlane)
{
    using namespace DirectX;
    MHMATRIX R;
    XMStoreFloat4x4( &R, XMMatrixPerspectiveFovRH( fov, aspectRatio, nearPlane, farPlane ) );
    return R;
}

inline MHMATRIX XM_CALLCONV MHMATRIX::Perspective(float width, float height, float nearPlane, float farPlane)
{
    using namespace DirectX;
    MHMATRIX R;
    XMStoreFloat4x4( &R, XMMatrixPerspectiveRH( width, height, nearPlane, farPlane ) );
    return R;
}

inline MHMATRIX XM_CALLCONV MHMATRIX::PerspectiveOffCenter(float left, float right, float bottom, float top, float nearPlane, float farPlane)
{
    using namespace DirectX;
    MHMATRIX R;
    XMStoreFloat4x4( &R, XMMatrixPerspectiveOffCenterRH( left, right, bottom, top, nearPlane, farPlane ) );
    return R;
}

inline MHMATRIX XM_CALLCONV MHMATRIX::Orthographic(float width, float height, float zNearPlane, float zFarPlane)
{
    using namespace DirectX;
    MHMATRIX R;
    XMStoreFloat4x4( &R, XMMatrixOrthographicRH( width, height, zNearPlane, zFarPlane ) );
    return R;
}

inline MHMATRIX XM_CALLCONV MHMATRIX::OrthographicOffCenter(float left, float right, float bottom, float top, float zNearPlane, float zFarPlane)
{
    using namespace DirectX;
    MHMATRIX R;
    XMStoreFloat4x4( &R, XMMatrixOrthographicOffCenterRH( left, right, bottom, top, zNearPlane, zFarPlane ) );
    return R;
}

inline MHMATRIX XM_CALLCONV MHMATRIX::LookAt(const MHVECTOR3& eye, const MHVECTOR3& target, const MHVECTOR3& up)
{
    using namespace DirectX;
    MHMATRIX R;
    XMVECTOR eyev = XMLoadFloat3( &eye );
    XMVECTOR targetv = XMLoadFloat3( &target );
    XMVECTOR upv = XMLoadFloat3( &up );
    XMStoreFloat4x4( &R, XMMatrixLookAtRH( eyev, targetv, upv ) );
    return R;
}

inline MHMATRIX XM_CALLCONV MHMATRIX::LookTo(const MHVECTOR3& eye, const MHVECTOR3& target, const MHVECTOR3& up)
{
	using namespace DirectX;
	MHMATRIX R;
	XMVECTOR eyev = XMLoadFloat3(&eye);
	XMVECTOR targetv = XMLoadFloat3(&target);
	XMVECTOR upv = XMLoadFloat3(&up);
	XMStoreFloat4x4(&R, XMMatrixLookToRH(eyev, targetv, upv));
	return R;
}

inline MHMATRIX XM_CALLCONV MHMATRIX::CreateWorld(const MHVECTOR3& position, const MHVECTOR3& forward, const MHVECTOR3& up)
{
    using namespace DirectX;
    XMVECTOR zaxis = XMVector3Normalize( XMVectorNegate( XMLoadFloat3( &forward ) ) );
    XMVECTOR yaxis = XMLoadFloat3( &up );
    XMVECTOR xaxis = XMVector3Normalize( XMVector3Cross( yaxis, zaxis ) );
    yaxis = XMVector3Cross( zaxis, xaxis );
    
    MHMATRIX R;
    XMStoreFloat3( reinterpret_cast<XMFLOAT3*>( &R._11 ), xaxis );
    XMStoreFloat3( reinterpret_cast<XMFLOAT3*>( &R._21 ), yaxis );
    XMStoreFloat3( reinterpret_cast<XMFLOAT3*>( &R._31 ), zaxis );
    R._14 = R._24 = R._34 = 0.f;
    R._41 = position.x; R._42 = position.y; R._43 = position.z;
    R._44 = 1.f;
    return R;
}

inline MHMATRIX XM_CALLCONV MHMATRIX::Shadow(const MHVECTOR3& lightDir, const MHPLANE& plane)
{
    using namespace DirectX;
    MHMATRIX R;
    XMVECTOR light = XMLoadFloat3( &lightDir );
    XMVECTOR planev = XMLoadFloat4( &plane );
    XMStoreFloat4x4( &R, XMMatrixShadow( planev, light ) );
    return R;
}

inline MHMATRIX XM_CALLCONV MHMATRIX::Reflect(const MHPLANE& plane)
{
    using namespace DirectX;
    MHMATRIX R;
    XMVECTOR planev = XMLoadFloat4( &plane );
    XMStoreFloat4x4( &R, XMMatrixReflect( planev ) );
    return R;
}

inline void XM_CALLCONV MHMATRIX::Lerp(FMHMATRIX& M1, FMHMATRIX& M2, float t, MHMATRIX& result)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M1._11) );
    XMVECTOR x2 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M1._21) );
    XMVECTOR x3 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M1._31) );
    XMVECTOR x4 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M1._41) );

    XMVECTOR y1 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M2._11) );
    XMVECTOR y2 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M2._21) );
    XMVECTOR y3 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M2._31) );
    XMVECTOR y4 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M2._41) );

    x1 = XMVectorLerp( x1, y1, t );
    x2 = XMVectorLerp( x2, y2, t );
    x3 = XMVectorLerp( x3, y3, t );
    x4 = XMVectorLerp( x4, y4, t );

    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&result._11), x1 );
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&result._21), x2 );
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&result._31), x3 );
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&result._41), x4 );
}

inline MHMATRIX XM_CALLCONV MHMATRIX::Lerp(FMHMATRIX& M1, FMHMATRIX& M2, float t)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M1._11) );
    XMVECTOR x2 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M1._21) );
    XMVECTOR x3 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M1._31) );
    XMVECTOR x4 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M1._41) );

    XMVECTOR y1 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M2._11) );
    XMVECTOR y2 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M2._21) );
    XMVECTOR y3 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M2._31) );
    XMVECTOR y4 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M2._41) );

    x1 = XMVectorLerp( x1, y1, t );
    x2 = XMVectorLerp( x2, y2, t );
    x3 = XMVectorLerp( x3, y3, t );
    x4 = XMVectorLerp( x4, y4, t );

    MHMATRIX result;
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&result._11), x1 );
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&result._21), x2 );
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&result._31), x3 );
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&result._41), x4 );
    return result;
}

inline void XM_CALLCONV MHMATRIX::Transform(FMHMATRIX& M, const MHQUATERNION& rotation, MHMATRIX& result)
{
    using namespace DirectX;
    XMVECTOR quatv = XMLoadFloat4( &rotation );

    XMMATRIX M0 = XMLoadFloat4x4( &M );
    XMMATRIX M1 = XMMatrixRotationQuaternion( quatv );

    XMStoreFloat4x4( &result, XMMatrixMultiply( M0, M1 ) );
}

inline MHMATRIX XM_CALLCONV MHMATRIX::Transform(FMHMATRIX& M, const MHQUATERNION& rotation)
{
    using namespace DirectX;
    XMVECTOR quatv = XMLoadFloat4( &rotation );

    XMMATRIX M0 = XMLoadFloat4x4( &M );
    XMMATRIX M1 = XMMatrixRotationQuaternion( quatv );

    MHMATRIX result;
    XMStoreFloat4x4( &result, XMMatrixMultiply( M0, M1 ) );
    return result;
}

#pragma endregion

//------------------------------------------------------------------------------
/// MHMATRIX operators
//------------------------------------------------------------------------------
# pragma region operators

//------------------------------------------------------------------------------
// Comparision operators
//------------------------------------------------------------------------------

inline bool XM_CALLCONV MHMATRIX::operator == (FMHMATRIX& M) const
{
	using namespace DirectX;
	XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_11));
	XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_21));
	XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_31));
	XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_41));

	XMVECTOR y1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._11));
	XMVECTOR y2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._21));
	XMVECTOR y3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._31));
	XMVECTOR y4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._41));

	return (XMVector4Equal(x1, y1)
		&& XMVector4Equal(x2, y2)
		&& XMVector4Equal(x3, y3)
		&& XMVector4Equal(x4, y4)) != 0;
}

inline bool XM_CALLCONV MHMATRIX::operator != (FMHMATRIX& M) const
{
	using namespace DirectX;
	XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_11));
	XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_21));
	XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_31));
	XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_41));

	XMVECTOR y1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._11));
	XMVECTOR y2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._21));
	XMVECTOR y3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._31));
	XMVECTOR y4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._41));

	return (XMVector4NotEqual(x1, y1)
		&& XMVector4NotEqual(x2, y2)
		&& XMVector4NotEqual(x3, y3)
		&& XMVector4NotEqual(x4, y4)) != 0;
}

//------------------------------------------------------------------------------
// Assignment operators
//------------------------------------------------------------------------------

inline MHMATRIX& XM_CALLCONV MHMATRIX::operator+= (FMHMATRIX& M)
{
	using namespace DirectX;
	XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<XMFLOAT4*>(&_11));
	XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<XMFLOAT4*>(&_21));
	XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<XMFLOAT4*>(&_31));
	XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<XMFLOAT4*>(&_41));

	XMVECTOR y1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._11));
	XMVECTOR y2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._21));
	XMVECTOR y3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._31));
	XMVECTOR y4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._41));

	x1 = XMVectorAdd(x1, y1);
	x2 = XMVectorAdd(x2, y2);
	x3 = XMVectorAdd(x3, y3);
	x4 = XMVectorAdd(x4, y4);

	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_11), x1);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_21), x2);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_31), x3);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_41), x4);
	return *this;
}

inline MHMATRIX& XM_CALLCONV MHMATRIX::operator+= (float S)
{
	using namespace DirectX;
	XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<XMFLOAT4*>(&_11));
	XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<XMFLOAT4*>(&_21));
	XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<XMFLOAT4*>(&_31));
	XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<XMFLOAT4*>(&_41));

	XMVECTOR y1 = XMLoadFloat(&S);
	XMVECTOR y2 = XMLoadFloat(&S);
	XMVECTOR y3 = XMLoadFloat(&S);
	XMVECTOR y4 = XMLoadFloat(&S);

	x1 = XMVectorAdd(x1, y1);
	x2 = XMVectorAdd(x2, y2);
	x3 = XMVectorAdd(x3, y3);
	x4 = XMVectorAdd(x4, y4);

	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_11), x1);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_21), x2);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_31), x3);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_41), x4);
	return *this;
}

inline MHMATRIX& XM_CALLCONV MHMATRIX::operator-= (FMHMATRIX& M)
{
	using namespace DirectX;
	XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<XMFLOAT4*>(&_11));
	XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<XMFLOAT4*>(&_21));
	XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<XMFLOAT4*>(&_31));
	XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<XMFLOAT4*>(&_41));

	XMVECTOR y1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._11));
	XMVECTOR y2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._21));
	XMVECTOR y3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._31));
	XMVECTOR y4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._41));

	x1 = XMVectorSubtract(x1, y1);
	x2 = XMVectorSubtract(x2, y2);
	x3 = XMVectorSubtract(x3, y3);
	x4 = XMVectorSubtract(x4, y4);

	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_11), x1);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_21), x2);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_31), x3);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_41), x4);
	return *this;
}

inline MHMATRIX& XM_CALLCONV MHMATRIX::operator-= (float S)
{
	using namespace DirectX;
	XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<XMFLOAT4*>(&_11));
	XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<XMFLOAT4*>(&_21));
	XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<XMFLOAT4*>(&_31));
	XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<XMFLOAT4*>(&_41));

	XMVECTOR y1 = XMLoadFloat(&S);
	XMVECTOR y2 = XMLoadFloat(&S);
	XMVECTOR y3 = XMLoadFloat(&S);
	XMVECTOR y4 = XMLoadFloat(&S);

	x1 = XMVectorSubtract(x1, y1);
	x2 = XMVectorSubtract(x2, y2);
	x3 = XMVectorSubtract(x3, y3);
	x4 = XMVectorSubtract(x4, y4);

	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_11), x1);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_21), x2);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_31), x3);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_41), x4);
	return *this;
}

inline MHMATRIX& XM_CALLCONV MHMATRIX::operator*= (FMHMATRIX& M)
{
	using namespace DirectX;
	XMMATRIX M1 = XMLoadFloat4x4(this);
	XMMATRIX M2 = XMLoadFloat4x4(&M);
	XMMATRIX X = XMMatrixMultiply(M1, M2);
	XMStoreFloat4x4(this, X);
	return *this;
}

inline MHMATRIX& XM_CALLCONV MHMATRIX::operator*= (float S)
{
	using namespace DirectX;
	XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<XMFLOAT4*>(&_11));
	XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<XMFLOAT4*>(&_21));
	XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<XMFLOAT4*>(&_31));
	XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<XMFLOAT4*>(&_41));

	x1 = XMVectorScale(x1, S);
	x2 = XMVectorScale(x2, S);
	x3 = XMVectorScale(x3, S);
	x4 = XMVectorScale(x4, S);

	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_11), x1);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_21), x2);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_31), x3);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_41), x4);
	return *this;
}

inline MHMATRIX& XM_CALLCONV MHMATRIX::operator/= (FMHMATRIX& M)
{
	using namespace DirectX;
	XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<XMFLOAT4*>(&_11));
	XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<XMFLOAT4*>(&_21));
	XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<XMFLOAT4*>(&_31));
	XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<XMFLOAT4*>(&_41));

	XMVECTOR y1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._11));
	XMVECTOR y2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._21));
	XMVECTOR y3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._31));
	XMVECTOR y4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._41));

	x1 = XMVectorDivide(x1, y1);
	x2 = XMVectorDivide(x2, y2);
	x3 = XMVectorDivide(x3, y3);
	x4 = XMVectorDivide(x4, y4);

	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_11), x1);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_21), x2);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_31), x3);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_41), x4);
	return *this;
}

inline MHMATRIX& XM_CALLCONV MHMATRIX::operator/= (float S)
{
	using namespace DirectX;
	assert(S != 0.f);
	XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<XMFLOAT4*>(&_11));
	XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<XMFLOAT4*>(&_21));
	XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<XMFLOAT4*>(&_31));
	XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<XMFLOAT4*>(&_41));

	float rs = 1.f / S;

	x1 = XMVectorScale(x1, rs);
	x2 = XMVectorScale(x2, rs);
	x3 = XMVectorScale(x3, rs);
	x4 = XMVectorScale(x4, rs);

	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_11), x1);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_21), x2);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_31), x3);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_41), x4);
	return *this;
}

//------------------------------------------------------------------------------
// Urnary operators
//------------------------------------------------------------------------------

/*
inline MHMATRIX XM_CALLCONV MHMATRIX::operator+ () const
{
using namespace DirectX;
XMVECTOR v1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_11));
XMVECTOR v2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_21));
XMVECTOR v3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_31));
XMVECTOR v4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_41));

v1 = +v1;
v2 = +v2;
v3 = +v3;
v4 = +v4;

MHMATRIX R;
XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._11), v1);
XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._21), v2);
XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._31), v3);
XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._41), v4);
return R;
}*/

inline MHMATRIX XM_CALLCONV MHMATRIX::operator- () const
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_11));
	XMVECTOR v2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_21));
	XMVECTOR v3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_31));
	XMVECTOR v4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_41));

	v1 = XMVectorNegate(v1);
	v2 = XMVectorNegate(v2);
	v3 = XMVectorNegate(v3);
	v4 = XMVectorNegate(v4);

	MHMATRIX R;
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._11), v1);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._21), v2);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._31), v3);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._41), v4);
	return R;
}

//------------------------------------------------------------------------------
// Binary operators
//------------------------------------------------------------------------------

inline MHMATRIX XM_CALLCONV operator+ (FMHMATRIX& M1, FMHMATRIX& M2)
{
	using namespace DirectX;
	XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._11));
	XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._21));
	XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._31));
	XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._41));

	XMVECTOR y1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._11));
	XMVECTOR y2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._21));
	XMVECTOR y3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._31));
	XMVECTOR y4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._41));

	x1 = XMVectorAdd(x1, y1);
	x2 = XMVectorAdd(x2, y2);
	x3 = XMVectorAdd(x3, y3);
	x4 = XMVectorAdd(x4, y4);

	MHMATRIX R;
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._11), x1);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._21), x2);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._31), x3);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._41), x4);
	return R;
}

inline MHMATRIX XM_CALLCONV operator+ (FMHMATRIX& M, float S)
{
	using namespace DirectX;
	XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._11));
	XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._21));
	XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._31));
	XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._41));

	XMVECTOR v1 = XMLoadFloat(&S);
	XMVECTOR v2 = XMLoadFloat(&S);
	XMVECTOR v3 = XMLoadFloat(&S);
	XMVECTOR v4 = XMLoadFloat(&S);

	x1 = XMVectorAdd(x1, v1);
	x2 = XMVectorAdd(x2, v2);
	x3 = XMVectorAdd(x3, v3);
	x4 = XMVectorAdd(x4, v4);

	MHMATRIX R;
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._11), x1);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._21), x2);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._31), x3);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._41), x4);
	return R;
}

inline MHMATRIX XM_CALLCONV operator+ (float S, FMHMATRIX& M)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._11));
	XMVECTOR v2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._21));
	XMVECTOR v3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._31));
	XMVECTOR v4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._41));

	XMVECTOR x1 = XMLoadFloat(&S);
	XMVECTOR x2 = XMLoadFloat(&S);
	XMVECTOR x3 = XMLoadFloat(&S);
	XMVECTOR x4 = XMLoadFloat(&S);

	x1 = XMVectorAdd(x1, v1);
	x2 = XMVectorAdd(x2, v2);
	x3 = XMVectorAdd(x3, v3);
	x4 = XMVectorAdd(x4, v4);

	MHMATRIX R;
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._11), x1);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._21), x2);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._31), x3);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._41), x4);
	return R;
}

inline MHMATRIX XM_CALLCONV operator- (FMHMATRIX& M1, FMHMATRIX& M2)
{
	using namespace DirectX;
	XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._11));
	XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._21));
	XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._31));
	XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._41));

	XMVECTOR y1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._11));
	XMVECTOR y2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._21));
	XMVECTOR y3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._31));
	XMVECTOR y4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._41));

	x1 = XMVectorSubtract(x1, y1);
	x2 = XMVectorSubtract(x2, y2);
	x3 = XMVectorSubtract(x3, y3);
	x4 = XMVectorSubtract(x4, y4);

	MHMATRIX R;
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._11), x1);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._21), x2);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._31), x3);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._41), x4);
	return R;
}

inline MHMATRIX XM_CALLCONV operator- (FMHMATRIX& M, float S)
{
	using namespace DirectX;
	XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._11));
	XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._21));
	XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._31));
	XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._41));

	XMVECTOR v1 = XMLoadFloat(&S);
	XMVECTOR v2 = XMLoadFloat(&S);
	XMVECTOR v3 = XMLoadFloat(&S);
	XMVECTOR v4 = XMLoadFloat(&S);

	x1 = XMVectorSubtract(x1, v1);
	x2 = XMVectorSubtract(x2, v2);
	x3 = XMVectorSubtract(x3, v3);
	x4 = XMVectorSubtract(x4, v4);

	MHMATRIX R;
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._11), x1);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._21), x2);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._31), x3);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._41), x4);
	return R;
}

inline MHMATRIX XM_CALLCONV operator- (float S, FMHMATRIX& M)
{
	using namespace DirectX;
	XMVECTOR v1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._11));
	XMVECTOR v2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._21));
	XMVECTOR v3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._31));
	XMVECTOR v4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._41));

	XMVECTOR x1 = XMLoadFloat(&S);
	XMVECTOR x2 = XMLoadFloat(&S);
	XMVECTOR x3 = XMLoadFloat(&S);
	XMVECTOR x4 = XMLoadFloat(&S);

	x1 = XMVectorSubtract(x1, v1);
	x2 = XMVectorSubtract(x2, v2);
	x3 = XMVectorSubtract(x3, v3);
	x4 = XMVectorSubtract(x4, v4);

	MHMATRIX R;
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._11), x1);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._21), x2);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._31), x3);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._41), x4);
	return R;
}

inline MHMATRIX XM_CALLCONV operator* (FMHMATRIX& M1, FMHMATRIX& M2)
{
	using namespace DirectX;
	XMMATRIX m1 = XMLoadFloat4x4(&M1);
	XMMATRIX m2 = XMLoadFloat4x4(&M2);
	XMMATRIX X = XMMatrixMultiply(m1, m2);

	MHMATRIX R;
	XMStoreFloat4x4(&R, X);
	return R;
}

inline MHMATRIX XM_CALLCONV operator* (FMHMATRIX& M, float S)
{
	using namespace DirectX;
	XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._11));
	XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._21));
	XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._31));
	XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._41));

	x1 = XMVectorScale(x1, S);
	x2 = XMVectorScale(x2, S);
	x3 = XMVectorScale(x3, S);
	x4 = XMVectorScale(x4, S);

	MHMATRIX R;
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._11), x1);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._21), x2);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._31), x3);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._41), x4);
	return R;
}

inline MHMATRIX XM_CALLCONV operator* (float S, FMHMATRIX& M)
{
	using namespace DirectX;

	XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._11));
	XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._21));
	XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._31));
	XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._41));

	x1 = XMVectorScale(x1, S);
	x2 = XMVectorScale(x2, S);
	x3 = XMVectorScale(x3, S);
	x4 = XMVectorScale(x4, S);

	MHMATRIX R;
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._11), x1);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._21), x2);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._31), x3);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._41), x4);
	return R;
}

inline MHMATRIX XM_CALLCONV operator/ (FMHMATRIX& M1, FMHMATRIX& M2)
{
	using namespace DirectX;
	XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._11));
	XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._21));
	XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._31));
	XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._41));

	XMVECTOR y1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._11));
	XMVECTOR y2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._21));
	XMVECTOR y3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._31));
	XMVECTOR y4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._41));

	x1 = XMVectorDivide(x1, y1);
	x2 = XMVectorDivide(x2, y2);
	x3 = XMVectorDivide(x3, y3);
	x4 = XMVectorDivide(x4, y4);

	MHMATRIX R;
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._11), x1);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._21), x2);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._31), x3);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._41), x4);
	return R;
}

inline MHMATRIX XM_CALLCONV operator/ (FMHMATRIX& M, float S)
{
	using namespace DirectX;
	assert(S != 0.f);

	XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._11));
	XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._21));
	XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._31));
	XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._41));

	float rs = 1.f / S;

	x1 = XMVectorScale(x1, rs);
	x2 = XMVectorScale(x2, rs);
	x3 = XMVectorScale(x3, rs);
	x4 = XMVectorScale(x4, rs);

	MHMATRIX R;
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._11), x1);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._21), x2);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._31), x3);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._41), x4);
	return R;
}

inline MHMATRIX XM_CALLCONV operator/ (float S, FMHMATRIX& M)
{
	using namespace DirectX;
	assert(S != 0.f);

	XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._11));
	XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._21));
	XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._31));
	XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._41));

	float rs = 1.f / S;

	x1 = XMVectorScale(x1, rs);
	x2 = XMVectorScale(x2, rs);
	x3 = XMVectorScale(x3, rs);
	x4 = XMVectorScale(x4, rs);

	MHMATRIX R;
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._11), x1);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._21), x2);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._31), x3);
	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._41), x4);
	return R;
}

#pragma endregion

#	pragma endregion

#ifdef __cplusplus
EXTERN_CC_END
#endif
