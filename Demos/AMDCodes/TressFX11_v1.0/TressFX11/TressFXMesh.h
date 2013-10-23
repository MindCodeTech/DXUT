//--------------------------------------------------------------------------------------
// File: TressFXMesh.h
//
// Hair mesh code
// 
// Copyright © AMD Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#pragma once
#include "..\\DXUT\\Core\\DXUT.h"
#include "..\\DXUT\\Optional\\DXUTcamera.h"
#include "util.h"
#include "TressFXSimulation.h"

class CDX11TressFXHairMesh
{	
public:
	static void ComputeStrandTangent(vector<StrandVertex>& strand);
	// z value: [0, 1] root:0, tip:1
	static float ComputeStrandTexcoordZ(vector<StrandVertex>& strand);

	CDX11TressFXHairMesh(void);
	~CDX11TressFXHairMesh(void);

	// Create Dx11 Mesh data from file
	void CreateHairMeshFromFile(ID3D11Device* pd3dDevice, 
								float scale = 1, 
								D3DXVECTOR3 rotation = D3DXVECTOR3(0, 0, 0), 
								D3DXVECTOR3 translation = D3DXVECTOR3(0, 0, 0));

	void ScaleRotateTranslate(	float scale = 1, 
								D3DXVECTOR3 rotation = D3DXVECTOR3(0, 0, 0), 
								D3DXVECTOR3 translation = D3DXVECTOR3(0, 0, 0));

	void OnFrameRender(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pd3dContext, CModelViewerCamera* pCamera, float fElapsedTime, const CVector3D & windDir, float windMag);

	void OnDestroy();
	
	// Bounding sphere for the hair mesh
	BSphere				m_bSphere;
	CDX11AMDHairMesh	m_AMDHairSim;
};
