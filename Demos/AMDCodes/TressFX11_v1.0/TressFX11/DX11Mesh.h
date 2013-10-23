//--------------------------------------------------------------------------------------
// File: DX11Mesh.h
//
// Basic mesh class for DX11
// mesh contains a single vertex buffer and index buffer
// the m_subsets is grouped according to material information
// all the triangles with the same material are grouped into one subsets
// This mesh can be created using objImpoart class.
// 
// Copyright © AMD Corporation. All rights reserved.
//--------------------------------------------------------------------------------------


#pragma once
#include "util.h"
#include <vector>
using namespace std;

//// the vertex layout for the mesh will be the following:
// This lay out has to match the shader input 
//static const D3D11_INPUT_ELEMENT_DESC layout_mesh[] =
//{
//    { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
//    { "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
//    { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
//};

class CDX11Mesh
{
public:
	CDX11Mesh(void);
	~CDX11Mesh(void);
	void CreateMeshFromOBJFile(ID3D11Device* pd3dDevice, const WCHAR* strFilename, 
								D3DXVECTOR3 scale = D3DXVECTOR3(1,1,1), 
								D3DXVECTOR3 rotation = D3DXVECTOR3(0, 0, 0), 
								D3DXVECTOR3 translation = D3DXVECTOR3(0, 0, 0));

	void OnFrameRender(ID3D11DeviceContext* pd3dContext);

	void OnDestroy();
	
	std::vector<Subset>		m_Subsets;			// all the sub meshes, each with different material property
	std::vector<Material>	m_Materials;
	std::vector<ID3D11ShaderResourceView*> m_TextureSRVs;
	ID3D11Buffer*			m_pVertexBuffer;
	ID3D11Buffer*			m_pIndexBuffer;

	BSphere					m_bSphere;
};
