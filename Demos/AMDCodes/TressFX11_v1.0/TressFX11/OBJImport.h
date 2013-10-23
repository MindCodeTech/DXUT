//--------------------------------------------------------------------------------------
// File: OBJImport.h
// 
// Copyright © AMD Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#pragma once
#include "util.h"
#include <vector>
#include <map>
#include <fstream>

using namespace std;

class COBJImport
{
private:
	// Vertex format
	struct VERTEX
	{
		D3DXVECTOR3 position;
		D3DXVECTOR3 normal;
		D3DXVECTOR2 texcoord;
	};

	// Used for a hashtable vertex cache when creating the mesh from a .obj file
	struct CacheEntry
	{
		UINT index;
		CacheEntry* pNext;
	};

    HRESULT LoadMaterialsFromMTL( const WCHAR* strFileName );
    UINT   AddVertex( UINT hash, StandardVertex* pVertex );

	void GenerateNormal();
	void UpdateBoundingSphere();
public:
	COBJImport(void);
	~COBJImport(void);

	void BuildMesh();
    HRESULT LoadModelFromOBJ( const WCHAR* strFilename );
	void ScaleRotateTranslate(D3DXVECTOR3 scale, D3DXVECTOR3 rotation, D3DXVECTOR3 translation);

	void	Destroy();

    UINT  GetNumMaterials() const				{	return m_Materials.size();	}
    Material* GetMaterial( UINT iMaterial )		{	return &m_Materials[iMaterial];	}
    WCHAR* GetMediaDirectory()					{	return m_strMediaDir;	}

	std::vector<Subset>				m_Subsets;			// all the sub meshes, each with different material property
	std::vector<Material>			m_Materials;
	std::vector<UINT>				m_IndexBuffer;
	std::vector<StandardVertex>		m_VertexBuffer;
	std::vector<UINT>				m_AttributeBuffer;

	std::map<UINT, std::vector<UINT>> m_VertexCache;

	UINT	m_NumSubMeshes;
	bool	m_bHasNormal;
    WCHAR   m_strMediaDir[ MAX_PATH ];               // Directory where the mesh was found
	// Bounding sphere for the mesh
	BSphere					m_bSphere;
};
