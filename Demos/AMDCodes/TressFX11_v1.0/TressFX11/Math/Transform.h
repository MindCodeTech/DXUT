//--------------------------------------------------------------------------------------
// File: Transform.h
// 
// Copyright © AMD Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#pragma once

#include "Vector3D.h"
#include "Quaternion.h"

class CTransform
{
public:
	CTransform(void);
	CTransform(const CTransform& other);
	CTransform(const CVector3D& translation, const CQuaternion& rotation);
	~CTransform(void);

private:
	CVector3D m_Translation;
	CQuaternion m_Rotation;

public:
	const CVector3D& GetTranslation() const { return m_Translation; }
	const CQuaternion& GetRotation() const { return m_Rotation; }
	CVector3D& GetTranslation() { return m_Translation; }
	CQuaternion& GetRotation() { return m_Rotation; }
	void Inverse();
	CTransform InverseOther() const;

	CVector3D operator*(const CVector3D& vector) const;
	CTransform operator*(const CTransform& transform) const;
	CTransform& operator=(const CTransform& other);
};

