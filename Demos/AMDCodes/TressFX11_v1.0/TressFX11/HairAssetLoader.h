//--------------------------------------------------------------------------------------
// File: HairAssetLoader.h
//
// Hair asset loading classes declared here.
// 
// Copyright © AMD Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#pragma once

#include <vector>
#include <list>
#include <assert.h>

#include <iostream>
#include <fstream>

#include "Math\\Vector3D.h"
#include "Math\\Transform.h"

struct CHairVertex
{
	CVector3D m_Pos;	
	float m_InvMass; // In case mass is infinite, m_InvMass is zero

	int m_GroupID;

	CTransform m_GlobalTransform;
	CTransform m_LocalTransform;

	CVector3D m_XVec;
	CVector3D m_ZVec; 
	
	CVector3D m_RefVecInLocalFrame;
	CVector3D m_OrgPosInLocalFrame_i_minus_1;
};

class CHairAsset
{
friend class CHairAssetLoader;

public:
	CHairAsset(void);
	~CHairAsset(void);

private:
	std::vector<CHairVertex> m_VertexArray;

public:
	std::vector<CHairVertex>& GetVertexArray() { return m_VertexArray; }
	const std::vector<CHairVertex>& GetVertexArray() const { return m_VertexArray; }
	
	void Clear();
	void ConstructAsset();
	void InitGlobalLocalFrame();
};

class CHairAssetLoader
{
public:
	CHairAssetLoader(void);
	~CHairAssetLoader(void);

private:
	int m_NumTotalVertices;
	std::vector<CHairAsset*> m_Hairs;

public:
	bool LoadAppend(const char* filename, int groupId, bool bMovable, int maxNumOfVerticesInStrand = 32);
	void Clear();
		
	int GetNumTotalVertices() const { return m_NumTotalVertices; }
	std::vector<CHairAsset*>& GetHairs() { return m_Hairs; }
	const std::vector<CHairAsset*>& GetHairs() const { return m_Hairs; }
};
