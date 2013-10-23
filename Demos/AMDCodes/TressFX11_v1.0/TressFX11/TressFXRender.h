//--------------------------------------------------------------------------------------
// File: TressFXRender.h
//
// Header file for the main hair rendering code 
// 
// Copyright © AMD Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#pragma once
#include "..\\..\\DXUT\\Optional\\DXUTcamera.h"
#include "DX11Mesh.h"
#include "TressFXMesh.h"
#include "sceneparams.h"

enum SM_TECH
{
    NOSHADOW = 0,
    SDSM = 2
};

struct HAIR_PARAMS 
{
    float Ka; // ambient 
    float Kd; // diffuse 
    float Ks1;
    float Ex1;

    float Ks2;
    float Ex2;

    float radius;
    float density; // between [0, 1]

    float alpha;
    float alpha_sm;

    float fiber_spacing;
    bool bThinTip;

    D3DXVECTOR3 color;

    int tech_shadow;
    bool bSimulation;

    float wind_magnitude;
    CVector3D wind_direction;
	
	bool bUseCoverage;
	bool bUseAltCoverage;

	int iStrandCopies;
};

class CHairRenderer
{
private:
    ////////////////////////////////////////////////////////////////////////////
    // Mesh body and hair
    CDX11Mesh					m_MeshHead;
    CDX11TressFXHairMesh		m_MeshHair;
    
    ID3D11Buffer*               m_pScreenQuadVB;

    ////////////////////////////////////////////////////////////////////////////
    // shader

    // VS for rendering hair from the eye camera.
    ID3D11VertexShader*			m_pVSRenderHairNoGS;
	ID3D11VertexShader*			m_pVSRenderHairNoGSAlternativeCoverage;
	
	// VS for performing strand copies, (for transparent and vertex instancing only)
	ID3D11VertexShader*			m_pVSRenderHairNoGSStrandCopies;
	ID3D11VertexShader*			m_pVSRenderHairNoGSAlternativeCoverageStrandCopies;

    // VS for generate hair SM from the light camera.
    ID3D11VertexShader*			m_pVSGenerateHairSM;

    // PS render hair to A buffer
    ID3D11PixelShader*			m_pPSABuffer_Hair;
    // PS composite nearest k hair fragments
    ID3D11PixelShader*			m_pPSDrawTopKEye;

    // VS for rendering scene from eye camera 
    ID3D11VertexShader*			m_pVSRenderScene;
    // VS for generate scene SM from the light camera.
    ID3D11VertexShader*			m_pVSGenerateSceneSM;
    ID3D11PixelShader*			m_pPSRenderScene;
	
    ID3D11VertexShader*			m_pVSScreenQuad;
    
    ////////////////////////////////////////////////////////////////////////////
    // constant buffer
    ID3D11Buffer*				m_pcbPerFrame;
    ID3D11Buffer*				m_pcbPerMaterial;

    ////////////////////////////////////////////////////////////////////////////
    // rendering states
	ID3D11RasterizerState*		m_pRasterizerStateSceneShadowmap;

    ID3D11BlendState*			m_pBlendStateBlendToBg;
    ID3D11BlendState*           m_pColorWritesOff;

    ID3D11DepthStencilState*    m_pDepthTestEnabledDSS;
    ID3D11DepthStencilState*    m_pDepthTestEnabledNoDepthWritesStencilWriteIncrementDSS;
    ID3D11DepthStencilState*    m_pDepthTestDisabledStencilTestLessDSS;

    ID3D11SamplerState*			m_pSamplerStateLinearWrap;
    ID3D11SamplerState*			m_pSamplerStatePointClamp;
    ID3D11SamplerState*			m_pSamplerStateCmpLess;

    ////////////////////////////////////////////////////////////////////////////
    // vertex layout for hair and scene
    ID3D11InputLayout*			m_pLayoutHair_0;
    ID3D11InputLayout*			m_pLayoutHair_1;
    ID3D11InputLayout*			m_pLayoutHair_2;
    ID3D11InputLayout*			m_pLayoutHair_3;
    ID3D11InputLayout*			m_pLayoutHair_4;
    ID3D11InputLayout*			m_pLayoutScene;
    ID3D11InputLayout*			m_pLayoutScene_1;
    ID3D11InputLayout*			m_pLayoutScene_2;

    ////////////////////////////////////////////////////////////////////////////
    // GPU Buffer
    // Eye camera root buffer(roots of the linked list)
    ID3D11Buffer*               m_pEyeRootBuffer;
    ID3D11UnorderedAccessView*  m_pEyeRootBufferUAV;
    ID3D11ShaderResourceView*   m_pEyeRootBufferSRV;

    // Eye camera node buffer(all linked list data)
    ID3D11Buffer*               m_pEyeNodeBuffer ;
    ID3D11UnorderedAccessView*  m_pEyeNodeBufferUAV;
    ID3D11ShaderResourceView*   m_pEyeNodeBufferSRV;

    ////////////////////////////////////////////////////////////////////////////
    // textures and views
    ID3D11Texture2D*			m_pNoiseTexture2D;
    ID3D11ShaderResourceView*	m_pNoiseSRV;

    // Scene shadow map depth stencil buffer
    ID3D11Texture2D*			m_pSMSceneTx;
    ID3D11DepthStencilView*		m_pSMSceneDSV;
    ID3D11ShaderResourceView*	m_pSMSceneSRV;

    // Hair shadow map depth stencil buffer
    ID3D11Texture2D*			m_pSMHairTx;
    ID3D11DepthStencilView*		m_pSMHairDSV;
    ID3D11ShaderResourceView*	m_pSMHairSRV;

private:
    void CreateShaderAndLayout( ID3D11Device* pd3dDevice );
    void CreateRenderStateObjects(ID3D11Device* pd3dDevice);
    void CreateTextureAndViews(ID3D11Device* pd3dDevice);
    void CreateConstantBuffer(ID3D11Device* pd3dDevice);
    void CreateVertexBuffers(ID3D11Device* pd3dDevice);

    void SetConstantBuffer(ID3D11DeviceContext* pd3dContext, 	
        CModelViewerCamera* pCamera, CModelViewerCamera* pCameraLight, // view camera and light camera
        HAIR_PARAMS& hair_params);

    void SetSamplerStates(ID3D11DeviceContext* pd3dContext);

    void RenderScene(ID3D11DeviceContext* pd3dContext,
                    ID3D11VertexShader* pVS, ID3D11PixelShader* pPS);

    void RenderHair(ID3D11DeviceContext* pd3dContext, 
                        ID3D11VertexShader* pVS, 
                        ID3D11PixelShader* pPS, 
                        float density,
                        bool useVertexInstancing = false,
						int	iStrandCopies = 1);

    void RenderScreenQuad(ID3D11DeviceContext* pd3dContext,
                    ID3D11VertexShader* pVS, ID3D11PixelShader* pPS);
	
    void RenderWith_Shadow_Transparency(ID3D11DeviceContext* pd3dContext, float density, const HAIR_PARAMS & hairParams);

    // Generate different types of shadow maps
    void GenerateSceneSM(ID3D11DeviceContext* pd3dContext);
    void GenerateHairSM(ID3D11DeviceContext* pd3dContext, float density);

    void SetShadowSRVs(ID3D11DeviceContext* pd3dContext, SM_TECH sm_tech);
    void ResetShadowSRVs(ID3D11DeviceContext* pd3dContext, SM_TECH sm_tech);
public:
    CHairRenderer(void);
    ~CHairRenderer(void);

    void OnCreateDevice(ID3D11Device* pd3dDevice, const WCHAR* headFile);
	void OnResizedSwapChain( ID3D11Device* pd3dDevice, IDXGISwapChain* 
							pSwapChain, const DXGI_SURFACE_DESC* 
							pBackBufferSurfaceDesc, void* pUserContext );

    void BeginHairFrame(ID3D11DeviceContext* pd3dContext, CModelViewerCamera* pCamera, CModelViewerCamera* pCameraLight, HAIR_PARAMS& hair_params);
    void GenerateShadows(ID3D11DeviceContext* pd3dContext, HAIR_PARAMS& hair_params);
    void RenderScene(ID3D11DeviceContext* pd3dContext);
    void RenderHair(ID3D11DeviceContext* pd3dContext, HAIR_PARAMS& hair_params);
    void EndHairFrame(ID3D11DeviceContext* pd3dContext, HAIR_PARAMS& hair_params);

    void Simulate(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pd3dContext, CModelViewerCamera* pCamera, float fElapsedTime, const HAIR_PARAMS & hair_params);

    void OnDestroy();
};

