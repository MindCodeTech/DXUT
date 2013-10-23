//--------------------------------------------------------------------------------------
// File: Quaternion.h
// 
// Copyright © AMD Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#pragma once

#include "Matrix33.h"
#include "Vector3D.h"

class CQuaternion
{
public:
	CQuaternion(float x = 0.0, float y = 0.0, float z = 0.0, float w = 1.0);
	CQuaternion(const CQuaternion& other);	
	CQuaternion(const CMatrix33& rotMat);
	CQuaternion(const CVector3D& axis, float angle_radian);
	~CQuaternion(void);

public:	
	float m_X;
	float m_Y;
	float m_Z; 
	float m_W;

	CQuaternion& Normalize();

	void SetRotation(const CVector3D& axis, float angle_radian);
	void SetRotation(const CMatrix33& rotMat);
	void SetRotation(const CQuaternion& quaternion);
	void GetRotation(CVector3D* pAxis, float* pAngle_radian) const;
	void GetRotation(CMatrix33* pMat33) const;
	CMatrix33 GetMatrix33() const;
	float Length() const;

	void SetIdentity();
	void Inverse();
	CQuaternion InverseOther() const;

	CQuaternion& operator=(const CQuaternion& other);
	CQuaternion operator+(const CQuaternion& other) const;
	CQuaternion operator+(const CVector3D& vec) const;
	CQuaternion operator* (const CQuaternion& other) const;
	CVector3D operator* (const CVector3D& vec) const;

	friend CVector3D operator*(const CVector3D& vec, const CQuaternion& q);
};
