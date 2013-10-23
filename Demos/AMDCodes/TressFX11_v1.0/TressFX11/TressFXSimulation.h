//--------------------------------------------------------------------------------------
// File: TressFXSimulation.h
//
// Hair physics simulation header
// 
// Copyright © AMD Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#pragma once

#include "..\\DXUT\\Core\\DXUT.h"
#include <d3dx11.h>
#include <string>
#include "HairAssetLoader.h"
#include "Util.h"
#include <map>

typedef D3DXVECTOR4 float4;

class CDX11AMDHairMesh
{
public:
    CDX11AMDHairMesh(void);
    ~CDX11AMDHairMesh(void);

    HRESULT OnCreateDevice(ID3D11Device* pd3dDevice);
    HRESULT Reset(ID3D11Device* pd3dDevice);
    HRESULT Simulate(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pd3dContext, float fElapsedTime, const CVector3D & windDir, float windMag);
    void OnDestroy();
    
public:
    CHairAssetLoader m_HairAssetLoader;

    // hair
    ID3D11Buffer* m_pVertexBuffer;

	ID3D11Buffer* m_pIndexBuffer;
    ID3D11ShaderResourceView* m_pIndexBufferSRV;
    
	ID3D11Buffer* m_pThicknessCoeffs;
	ID3D11ShaderResourceView* m_pThicknessCoeffsSRV;

    ID3D11InputLayout* m_pLayout;

    vector< vector<StrandVertex> >	m_HairStrands;
    
    int m_NumGuideHairVertices;
    int m_NumGuideHairStrands;
    int m_MaxNumOfVerticesInStrand;

    int* m_GuideHairVerticesOffsets;
    int* m_GuideHairStrandType;
    int m_TotalIndexCount;

    // Compute Shader
    //data for compute shaders
	ID3D11ComputeShader*    m_CSSkipSimulateHair;
	ID3D11ComputeShader*    m_CSSimulateHair_A;
	ID3D11ComputeShader*    m_CSSimulateHair_B;
	ID3D11ComputeShader*    m_CSSimulateHair_C;
	ID3D11ComputeShader*    m_CSSimulateHair_D;

    float4* m_pTempVertices;
    float4* m_pTempTangents;

    // vertex positions
    ID3D11Buffer* m_GuideHairVertexPositionsUAB;
    ID3D11UnorderedAccessView* m_GuideHairVertexPositionsUAV;
	ID3D11ShaderResourceView* m_GuideHairVertexPositionsSRV;
    
    ID3D11Buffer* m_GuideHairVertexPositionsPrevUAB;
    ID3D11UnorderedAccessView* m_GuideHairVertexPositionsPrevUAV;
	    
    ID3D11ShaderResourceView* m_InitialGuideHairPositionsSRV;
    ID3D11UnorderedAccessView* m_InitialGuideHairPositionsUAV;

    // vertex offsets
    ID3D11Buffer* m_GuideHairVerticesOffsetsBuffer;
    ID3D11ShaderResourceView* m_GuideHairVerticesOffsetsSRV;

    // strand type
    ID3D11Buffer* m_GuideHairStrandTypeBuffer;
    ID3D11ShaderResourceView* m_GuideHairStrandTypeSRV;
    
    // rest length
    ID3D11Buffer* m_GuideHairLengthBuffer;
    ID3D11ShaderResourceView* m_GuideHairRestLengthSRV;

    // reference vectors
    ID3D11Buffer* m_GuideHairRefVectorsBuffer;
    ID3D11ShaderResourceView* m_GuideHairRefVecsInLocalFrameSRV;

    // global and local transforms for each vertex
    ID3D11Buffer* m_GlobalRotationsUAB;
    ID3D11UnorderedAccessView* m_GlobalRotationsUAV;

    ID3D11Buffer* m_LocalRotationsUAB;
    ID3D11UnorderedAccessView* m_LocalRotationsUAV;

    // const buffer for CS
    ID3D11Buffer* m_pCBCSPerFrame;
    
    // vertex tangents
    ID3D11Buffer* m_GuideHairVertexTangentsUAB;
    ID3D11UnorderedAccessView* m_GuideHairVertexTangentsUAV;
    ID3D11ShaderResourceView* m_GuideHairVertexTangentsSRV;

    HRESULT CreateComputeShaderConstantBuffers(ID3D11Device* pd3dDevice);	
    HRESULT SimulateDX11(ID3D11DeviceContext* pd3dContext, float fElapsedTime, const CVector3D & windDir, float windMag);
    HRESULT CreateBufferAndViews(ID3D11Device* pd3dDevice);
};
//---
extern int g_NumLengthConstraintIterations;
extern int g_NumLocalShapeMatchingIterations;
extern int g_LocalShapeConstraintMethod; 
extern float g_GravityMagnitude;
extern int g_HairSimulationFixedFrameRate;
extern bool g_bCollision;

// top back, and sides hair
extern float g_Damping0;
extern float g_StiffnessForLocalShapeMatching0;
extern float g_StiffnessForGlobalShapeMatching0;
extern float g_GlobalShapeMatchingEffectiveRange0;	

// ponytail
extern float g_Damping2;
extern float g_StiffnessForLocalShapeMatching2;
extern float g_StiffnessForGlobalShapeMatching2;
extern float g_GlobalShapeMatchingEffectiveRange2;
    
// front long hair
extern float g_Damping3;
extern float g_StiffnessForLocalShapeMatching3;
extern float g_StiffnessForGlobalShapeMatching3;
extern float g_GlobalShapeMatchingEffectiveRange3;
