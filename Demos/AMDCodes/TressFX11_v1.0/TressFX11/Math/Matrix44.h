//--------------------------------------------------------------------------------------
// File: Matrix44.h
// 
// Copyright © AMD Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#ifndef __MATRIX44_H__
#define __MATRIX44_H__

class CVector3D;

class CMatrix44 
{
public:
	CMatrix44();
	CMatrix44(const CMatrix44& other);
	CMatrix44(float r1[4], float r2[4], float r3[4], float r4[4]);
	CMatrix44(float e00, float e01, float e02, float e03,
			  float e10, float e11, float e12, float e13,
			  float e20, float e21, float e22, float e23,
			  float e30, float e31, float e32, float e33);
	virtual ~CMatrix44();

	float Row[4][4];

public:
	void SetIdentity();
	void SetRotation(const CVector3D& axis, float ang);
	void SetTranslate(float x, float y, float z);

	float GetElement(int nRow, int nCol) const;

	CVector3D operator*(const CVector3D& vec) const;
	CMatrix44 operator*(const CMatrix44& other) const;
	CMatrix44& operator=(const CMatrix44& other);

	operator float* () const {return (float*)Row;}
	operator const float* () const {return (const float*)Row;}
};

#endif // __MATRIX44_H__