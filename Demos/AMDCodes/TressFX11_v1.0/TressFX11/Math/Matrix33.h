//--------------------------------------------------------------------------------------
// File: Matrix33.h
// 
// Copyright © AMD Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#pragma once

class CVector3D;

class CMatrix33
{
	friend class CVector3D;
	friend class CQuaternion;

public:
	CMatrix33(void);
	CMatrix33(const CMatrix33& other);
	CMatrix33(float e00, float e01, float e02, float e10, float e11, float e12, float e20, float e21, float e22);
	CMatrix33(float a);
	~CMatrix33(void);

private:
	float e[3][3];

public:
	static const CMatrix33 IDENTITY;
	static const CMatrix33 ZERO;

public:
	void SetIdentity();
	void Set(float e00, float e01, float e02, float e10, float e11, float e12, float e20, float e21, float e22);
	float GetElement(int i, int j) const;
	void SetElement(int i, int j, float val);
	void SetRotation(const CVector3D& axis, float ang);
	void Inverse();
	CMatrix33 InverseOther() const;
	void Transpose();
	CMatrix33 TransposeOther() const;

	CVector3D operator*(const CVector3D& vec) const;
	CMatrix33 operator*(const CMatrix33& other) const;
	CMatrix33 operator*(float val) const;
	CMatrix33 operator+(const CMatrix33& other) const;
	CMatrix33 operator-(const CMatrix33& other) const;
	CMatrix33 operator/(float val) const;
	CMatrix33& operator*=(float val);
	CMatrix33& operator-=(const CMatrix33& other);
	CMatrix33& operator+=(const CMatrix33& other);
	CMatrix33& operator=(const CMatrix33& other);
	//CMatrix33& operator=(float a);

	bool operator==(const CMatrix33& other);
	bool operator!=(const CMatrix33& other);

	bool operator==(float a);
	bool operator!=(float a);

	float& operator()(int i, int j);				
	const float& operator()(int i, int j) const;

	friend CMatrix33 operator*(float val, const CMatrix33& other);
	friend CMatrix33 operator-(const CMatrix33& other);
};
