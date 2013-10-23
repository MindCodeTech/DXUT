//--------------------------------------------------------------------------------------
// File: TressFXRender.cpp
//
// Main hair rendering code
// 
// Copyright © AMD Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#include "..\\DXUT\\Core\\DXUT.h"
#include "TressFXRender.h"
#include "main.h"

#define IDSRV_ROOTBUFFER_EYE		       0
#define IDSRV_NODEBUFFER_EYE		       1
#define IDSRV_SCENESM				       2
#define IDSRV_HAIRSM				       3
#define IDSRV_SCENE					       4
#define IDSRV_NOISEMAP				       5
#define IDSRV_HAIR_INDICES                 6
#define IDSRV_HAIR_THICKNESSES             7
#define IDSRV_GUIDE_HAIR_VERTEX_POSITIONS  8
#define IDSRV_GUIDE_HAIR_TANGENTS          9

struct CB_PER_FRAME
{
	D3DXMATRIX	m_mWorld;
    D3DXMATRIX	m_mViewProj;
	D3DXMATRIX  m_mInvViewProj;
    D3DXMATRIX  m_mViewProjLight;
    
    D3DXVECTOR3 m_vEye;
	float		m_fvFOV;

	D3DXVECTOR4 m_AmbientLightColor;
    D3DXVECTOR4 m_PointLightColor;
    D3DXVECTOR4 m_PointLightPos;
    D3DXVECTOR4 m_MatBaseColor;
    D3DXVECTOR4 m_MatKValue;

    float		m_FiberAlpha;
    float		m_HairSMAlpha;
    float		m_bExpandPixels;
	float		m_FiberRadius;

    float		m_fHairKs2;
    float		m_fHairEx2;
	D3DXVECTOR2 m_WinSize;

    float		m_FiberSpacing;
    float		m_bThinTip;
    float		m_fNearLight;
    float		m_fFarLight;
	       
    int			m_iTechSM;
    int			m_bUseCoverage;
    int			m_bUseAltCoverage;
	int			m_iStrandCopies;
};

struct CB_PER_MATERIAL
{
    D3DXVECTOR4		m_MatAmbient	;
    D3DXVECTOR4		m_MatDiffuse	; // alpha value: whether texture is used (yes: 1; no: -1)
    D3DXVECTOR4		m_MatSpecular	; // alpha value: Specular Exponent
    D3DXVECTOR4     m_ScalpColor    ;
};

struct EYE_FRAGMENT_STRUCT
{
    DWORD            vPixelColor;
    DWORD            uDepthAndCoverage;     
    DWORD            dwNext;
};

CHairRenderer::CHairRenderer(void)
{
}


CHairRenderer::~CHairRenderer(void)
{
}

void CHairRenderer::CreateShaderAndLayout( ID3D11Device* pd3dDevice )
{

    // Ensure all shaders (and input layouts) are released
    SAFE_RELEASE( m_pVSRenderHairNoGS );
    SAFE_RELEASE( m_pLayoutHair_0 );
    SAFE_RELEASE( m_pLayoutHair_1 );
    SAFE_RELEASE( m_pLayoutHair_2 );
    SAFE_RELEASE( m_pLayoutHair_3 );
    SAFE_RELEASE( m_pLayoutHair_4 );
    SAFE_RELEASE( m_pLayoutScene );
    SAFE_RELEASE( m_pLayoutScene_1 );
    SAFE_RELEASE( m_pLayoutScene_2 );
    SAFE_RELEASE( m_pVSRenderHairNoGSAlternativeCoverage );
    SAFE_RELEASE( m_pVSGenerateHairSM );
    SAFE_RELEASE( m_pVSRenderHairNoGSStrandCopies );
    SAFE_RELEASE( m_pVSRenderHairNoGSAlternativeCoverageStrandCopies );
    SAFE_RELEASE( m_pPSABuffer_Hair );
    SAFE_RELEASE( m_pPSDrawTopKEye );
    SAFE_RELEASE( m_pVSRenderScene );
    SAFE_RELEASE( m_pVSGenerateSceneSM );
    SAFE_RELEASE( m_pVSScreenQuad );
	SAFE_RELEASE( m_pPSRenderScene );

	// Hair vertex layout
    const D3D11_INPUT_ELEMENT_DESC layout_hair[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,	0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TANGENT",  0, DXGI_FORMAT_R32G32B32_FLOAT,	0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32B32A32_FLOAT,0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };

    // the vertex layout for the mesh structure
    const D3D11_INPUT_ELEMENT_DESC layout_mesh[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };

    // Add shaders to the cache

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // render hair

	// vertex shaders
	g_ShaderCache.AddShader( (ID3D11DeviceChild**)&m_pVSRenderHairNoGS, AMD::ShaderCache::SHADER_TYPE_VERTEX, 
		L"vs_5_0", L"VS_RenderHairNoGS",L"shaders\\Source\\hairBasic.hlsl", 0, NULL, &m_pLayoutHair_0, 
		(D3D11_INPUT_ELEMENT_DESC*)layout_hair, ARRAYSIZE( layout_hair ) );
	g_ShaderCache.AddShader( (ID3D11DeviceChild**)&m_pVSRenderHairNoGSAlternativeCoverage, AMD::ShaderCache::SHADER_TYPE_VERTEX, 
		L"vs_5_0", L"VS_RenderHairNoGS_AlternativeCoverage",L"shaders\\Source\\hairBasic.hlsl", 0, NULL, &m_pLayoutHair_1, 
		(D3D11_INPUT_ELEMENT_DESC*)layout_hair, ARRAYSIZE( layout_hair ) );
	g_ShaderCache.AddShader( (ID3D11DeviceChild**)&m_pVSGenerateHairSM, AMD::ShaderCache::SHADER_TYPE_VERTEX, 
		L"vs_5_0", L"VS_GenerateHairSM",L"shaders\\Source\\hairBasic.hlsl", 0, NULL, &m_pLayoutHair_2, 
		(D3D11_INPUT_ELEMENT_DESC*)layout_hair, ARRAYSIZE( layout_hair ) );
	g_ShaderCache.AddShader( (ID3D11DeviceChild**)&m_pVSRenderHairNoGSStrandCopies, AMD::ShaderCache::SHADER_TYPE_VERTEX, 
		L"vs_5_0", L"VS_RenderHairNoGS_StrandCopies",L"shaders\\Source\\hairBasic.hlsl", 0, NULL, &m_pLayoutHair_3, 
		(D3D11_INPUT_ELEMENT_DESC*)layout_hair, ARRAYSIZE( layout_hair ) );
	g_ShaderCache.AddShader( (ID3D11DeviceChild**)&m_pVSRenderHairNoGSAlternativeCoverageStrandCopies, AMD::ShaderCache::SHADER_TYPE_VERTEX, 
		L"vs_5_0", L"VS_RenderHairNoGS_AlternativeCoverage_StrandCopies",L"shaders\\Source\\hairBasic.hlsl", 0, NULL, &m_pLayoutHair_4, 
		(D3D11_INPUT_ELEMENT_DESC*)layout_hair, ARRAYSIZE( layout_hair ) );
	
	// pixel shaders
    g_ShaderCache.AddShader( (ID3D11DeviceChild**)&m_pPSABuffer_Hair, AMD::ShaderCache::SHADER_TYPE_PIXEL, L"ps_5_0", L"PS_ABuffer_Hair",
        L"shaders\\Source\\kbuffer.hlsl", 0, NULL, NULL, NULL, 0 );
    g_ShaderCache.AddShader( (ID3D11DeviceChild**)&m_pPSDrawTopKEye, AMD::ShaderCache::SHADER_TYPE_PIXEL, L"ps_5_0", L"PS_DrawTopKEye_SelectBlend",
        L"shaders\\Source\\kbuffer.hlsl", 0, NULL, NULL, NULL, 0 );

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // render scene

	// vertex shaders
	g_ShaderCache.AddShader( (ID3D11DeviceChild**)&m_pVSRenderScene, AMD::ShaderCache::SHADER_TYPE_VERTEX, 
		L"vs_5_0", L"VS_RenderScene",L"shaders\\Source\\renderscene.hlsl", 0, NULL, &m_pLayoutScene, 
		(D3D11_INPUT_ELEMENT_DESC*)layout_mesh, ARRAYSIZE( layout_mesh ) );
	g_ShaderCache.AddShader( (ID3D11DeviceChild**)&m_pVSGenerateSceneSM, AMD::ShaderCache::SHADER_TYPE_VERTEX, 
		L"vs_5_0", L"VS_GenerateSceneSM",L"shaders\\Source\\renderscene.hlsl", 0, NULL, &m_pLayoutScene_1, 
		(D3D11_INPUT_ELEMENT_DESC*)layout_mesh, ARRAYSIZE( layout_mesh ) );
	g_ShaderCache.AddShader( (ID3D11DeviceChild**)&m_pVSScreenQuad, AMD::ShaderCache::SHADER_TYPE_VERTEX, 
		L"vs_5_0", L"VS_ScreenQuad",L"shaders\\Source\\common.hlsl", 0, NULL, &m_pLayoutScene_2, 
		(D3D11_INPUT_ELEMENT_DESC*)layout_mesh, ARRAYSIZE( layout_mesh ) );

	// pixel shaders
    g_ShaderCache.AddShader( (ID3D11DeviceChild**)&m_pPSRenderScene, AMD::ShaderCache::SHADER_TYPE_PIXEL, L"ps_5_0", L"PS_RenderScene",
        L"shaders\\Source\\renderscene.hlsl", 0, NULL, NULL, NULL, 0 );
}

void CHairRenderer::CreateRenderStateObjects( ID3D11Device* pd3dDevice )
{
    HRESULT hr;
    ////////////////////////////////////////////////////////////////////////////////////////
    // Create depth stencil states
    D3D11_DEPTH_STENCIL_DESC DSDesc;
    DSDesc.StencilReadMask              = 0xff;
    DSDesc.StencilWriteMask             = 0xff;
    DSDesc.FrontFace.StencilFailOp      = D3D11_STENCIL_OP_KEEP;
    DSDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
    DSDesc.FrontFace.StencilPassOp      = D3D11_STENCIL_OP_KEEP;
    DSDesc.FrontFace.StencilFunc        = D3D11_COMPARISON_ALWAYS;
    DSDesc.BackFace.StencilFailOp       = D3D11_STENCIL_OP_KEEP;
    DSDesc.BackFace.StencilDepthFailOp  = D3D11_STENCIL_OP_KEEP;
    DSDesc.BackFace.StencilPassOp       = D3D11_STENCIL_OP_KEEP;
    DSDesc.BackFace.StencilFunc         = D3D11_COMPARISON_ALWAYS;
    DSDesc.DepthEnable                  = TRUE;
    DSDesc.StencilEnable                = FALSE;
    DSDesc.DepthFunc                    = D3D11_COMPARISON_LESS_EQUAL;
    DSDesc.DepthWriteMask               = D3D11_DEPTH_WRITE_MASK_ALL;
    hr = pd3dDevice->CreateDepthStencilState(&DSDesc, &m_pDepthTestEnabledDSS);

    DSDesc.DepthEnable                  = TRUE;
    DSDesc.DepthFunc                    = D3D11_COMPARISON_LESS_EQUAL;
    DSDesc.DepthWriteMask               = D3D11_DEPTH_WRITE_MASK_ZERO;
    DSDesc.StencilEnable                = TRUE;
    DSDesc.StencilReadMask              = 0xFF;
    DSDesc.StencilWriteMask             = 0xFF;
    DSDesc.FrontFace.StencilFailOp      = D3D11_STENCIL_OP_KEEP;
    DSDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
    DSDesc.FrontFace.StencilPassOp      = D3D11_STENCIL_OP_INCR_SAT;
    DSDesc.FrontFace.StencilFunc        = D3D11_COMPARISON_ALWAYS;
    DSDesc.BackFace.StencilFailOp       = D3D11_STENCIL_OP_KEEP;
    DSDesc.BackFace.StencilDepthFailOp  = D3D11_STENCIL_OP_KEEP;
    DSDesc.BackFace.StencilPassOp       = D3D11_STENCIL_OP_INCR_SAT;
    DSDesc.BackFace.StencilFunc         = D3D11_COMPARISON_ALWAYS;
    hr = pd3dDevice->CreateDepthStencilState(&DSDesc, &m_pDepthTestEnabledNoDepthWritesStencilWriteIncrementDSS);

    DSDesc.DepthEnable                  = FALSE;
    DSDesc.DepthFunc                    = D3D11_COMPARISON_LESS_EQUAL;
    DSDesc.DepthWriteMask               = D3D11_DEPTH_WRITE_MASK_ZERO;
    DSDesc.StencilEnable                = TRUE;
    DSDesc.StencilReadMask              = 0xFF;
    DSDesc.StencilWriteMask             = 0x00;
    DSDesc.FrontFace.StencilFailOp      = D3D11_STENCIL_OP_KEEP;
    DSDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
    DSDesc.FrontFace.StencilPassOp      = D3D11_STENCIL_OP_KEEP;
    DSDesc.FrontFace.StencilFunc        = D3D11_COMPARISON_LESS;
    DSDesc.BackFace.StencilFailOp       = D3D11_STENCIL_OP_KEEP;
    DSDesc.BackFace.StencilDepthFailOp  = D3D11_STENCIL_OP_KEEP;
    DSDesc.BackFace.StencilPassOp       = D3D11_STENCIL_OP_KEEP;
    DSDesc.BackFace.StencilFunc         = D3D11_COMPARISON_LESS;
    hr = pd3dDevice->CreateDepthStencilState(&DSDesc, &m_pDepthTestDisabledStencilTestLessDSS);

    //////////////////////////////////////////////////////////////////////////////////////////
    // Create sampler state objects
    D3D11_SAMPLER_DESC samDesc;
    ZeroMemory( &samDesc, sizeof(samDesc) );
    samDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR ;//D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    samDesc.AddressU = samDesc.AddressV = samDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    samDesc.MaxAnisotropy = 16;
    samDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    samDesc.MinLOD = 0;
    samDesc.MaxLOD = D3D11_FLOAT32_MAX;
    hr = pd3dDevice->CreateSamplerState( &samDesc, &m_pSamplerStateLinearWrap ) ;
    if(FAILED(hr))
        ::MessageBoxA(0, "Fail to create linear wrap sampler state", "D3D Error", 0);

    samDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
    hr = pd3dDevice->CreateSamplerState( &samDesc, &m_pSamplerStatePointClamp ) ;
    if(FAILED(hr))
        ::MessageBoxA(0, "Fail to create point sampler state", "D3D Error", 0);

    samDesc.Filter = D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR;//D3D11_FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT;
    samDesc.ComparisonFunc = D3D11_COMPARISON_LESS;
    samDesc.BorderColor[0] = samDesc.BorderColor[1] = 
        samDesc.BorderColor[2] = samDesc.BorderColor[3] = 1;
    samDesc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
    samDesc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
    samDesc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
    if(FAILED(pd3dDevice->CreateSamplerState( &samDesc, &m_pSamplerStateCmpLess )))
        ::MessageBoxA(0, "Fail to create compare sampler state", "D3D error", 0);

    /////////////////////////////////////////////////////////////////////////////////////////
    // Create blend state objects
    D3D11_BLEND_DESC blendDesc;
    ZeroMemory(&blendDesc, sizeof(D3D11_BLEND_DESC));
    blendDesc.IndependentBlendEnable = false;
    blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
    blendDesc.AlphaToCoverageEnable = false;
    blendDesc.RenderTarget[0].BlendEnable = true;
    blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE ;
    blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_SRC_ALPHA;
    blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
    blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO;//D3D11_BLEND_SRC_ALPHA  ;
    blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO ;
    blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD ;
    hr = pd3dDevice->CreateBlendState(&blendDesc, &m_pBlendStateBlendToBg);
    if(FAILED(hr))
        ::MessageBoxA(0, "Fail to create blend state: blend to background", "D3D Error", 0);

    // Create a blend state to disable color writes
    blendDesc.RenderTarget[0].SrcBlend  = D3D11_BLEND_ONE;
    blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ZERO;
    blendDesc.RenderTarget[0].RenderTargetWriteMask = 0;
    hr = pd3dDevice->CreateBlendState(&blendDesc, &m_pColorWritesOff);

	/////////////////////////////////////////////////////////////////////////////////////////
    // Create rasterizer state for shadow map rendering
    D3D11_RASTERIZER_DESC drd = {
        D3D11_FILL_SOLID, //D3D11_FILL_MODE FillMode;
        D3D11_CULL_NONE,//D3D11_CULL_MODE CullMode;
        FALSE, //BOOL FrontCounterClockwise;
        256, //INT DepthBias;
        0.0f,//FLOAT DepthBiasClamp;
        2.f,//FLOAT SlopeScaledDepthBias;
        FALSE,//BOOL DepthClipEnable;
        FALSE,//BOOL ScissorEnable;
        FALSE,//BOOL MultisampleEnable;
        FALSE//BOOL AntialiasedLineEnable;        
    };
    hr = pd3dDevice->CreateRasterizerState(&drd, &m_pRasterizerStateSceneShadowmap);
	if(FAILED(hr))
      ::MessageBoxA(0, "Fail to create rasterizer state: sceneShadowmap", "D3D Error", 0);
}

void CHairRenderer::CreateTextureAndViews( ID3D11Device* pd3dDevice )
{
    HRESULT hr;

    ////////////////////////////////////////////////////////////////////////////////////
    // Create SM DSVs for hair and scene	
    D3D11_TEXTURE2D_DESC tex2D_desc;
    tex2D_desc.Width =  SM_SCENE_WIDTH;
    tex2D_desc.Height = SM_SCENE_HEIGHT;
    tex2D_desc.ArraySize = 1;
    tex2D_desc.Format = DXGI_FORMAT_R32_TYPELESS;
    tex2D_desc.Usage = D3D11_USAGE_DEFAULT;//
    tex2D_desc.BindFlags = D3D10_BIND_DEPTH_STENCIL|D3D11_BIND_SHADER_RESOURCE  ;
    tex2D_desc.CPUAccessFlags = 0;
    tex2D_desc.MipLevels = 0;
    tex2D_desc.MiscFlags = 0;
    tex2D_desc.SampleDesc.Count = 1;
    tex2D_desc.SampleDesc.Quality = 0;
	
    hr = pd3dDevice->CreateTexture2D(&tex2D_desc, 0, &m_pSMSceneTx);
    if(FAILED(hr))
        ::MessageBoxW(0, L"fail to create m_pSMSceneTx", L"d3d Error", 0);
    
    D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc;
    dsvDesc.Flags = 0  ;
    dsvDesc.Format = DXGI_FORMAT_D32_FLOAT;
    dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D ;
    dsvDesc.Texture2D.MipSlice = 0;
    if(FAILED(pd3dDevice->CreateDepthStencilView(m_pSMSceneTx, &dsvDesc, &m_pSMSceneDSV)))
        ::MessageBoxW(0, L"fail to create m_pSMSceneDSV", L"d3d Error", 0);
    
    D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
    srvDesc.Format = DXGI_FORMAT_R32_FLOAT;
    srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    srvDesc.Texture2D.MipLevels = 1;
    srvDesc.Texture2D.MostDetailedMip = 0;
    if(FAILED(pd3dDevice->CreateShaderResourceView(m_pSMSceneTx, &srvDesc, &m_pSMSceneSRV)))
        ::MessageBoxW(0, L"fail to create m_pSMSRV", L"d3d Error", 0);
    
    tex2D_desc.Width =  SM_HAIR_WIDTH;
    tex2D_desc.Height = SM_HAIR_HEIGHT;
	
    hr = pd3dDevice->CreateTexture2D(&tex2D_desc, 0, &m_pSMHairTx);
    if(FAILED(hr))
        ::MessageBoxW(0, L"fail to create m_pSMHairTx", L"d3d Error", 0);

    if(FAILED(pd3dDevice->CreateDepthStencilView(m_pSMHairTx, &dsvDesc, &m_pSMHairDSV)))
        ::MessageBoxW(0, L"fail to create m_pSMHairDSV", L"d3d Error", 0);

    if(FAILED(pd3dDevice->CreateShaderResourceView(m_pSMHairTx, &srvDesc, &m_pSMHairSRV)))
        ::MessageBoxW(0, L"fail to create m_pSMSRV", L"d3d Error", 0);
	
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Noise texture
    D3D11_TEXTURE2D_DESC texDesc;
    texDesc.Width = 512;
    texDesc.Height = 512;
    texDesc.MipLevels = 1;
    texDesc.ArraySize = 1;
    texDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
    texDesc.Usage = D3D11_USAGE_DEFAULT;
    texDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE ;
    texDesc.MiscFlags = 0;
    texDesc.CPUAccessFlags = 0;
    texDesc.SampleDesc.Count=1;
    texDesc.SampleDesc.Quality=0;

    D3DXVECTOR4* noiseArray = new D3DXVECTOR4[texDesc.Width*texDesc.Height];
    for(UINT i=0; i<texDesc.Width*texDesc.Height ; i++)
    {
        noiseArray[i].x = rand()/(float)RAND_MAX; 
        noiseArray[i].y = rand()/(float)RAND_MAX;
        noiseArray[i].z = rand()/(float)RAND_MAX;
        noiseArray[i].w = rand()/(float)RAND_MAX;
    }

    D3D11_SUBRESOURCE_DATA initData0;
    initData0.pSysMem = noiseArray;
    initData0.SysMemPitch = texDesc.Width*sizeof(D3DXVECTOR4);
    initData0.SysMemSlicePitch = 0;

    hr = pd3dDevice->CreateTexture2D(&texDesc, &initData0, &m_pNoiseTexture2D);
    if(FAILED(hr))
        ::MessageBoxW(0, L"fail to create random texture", L"Error", 0);
	
    D3D11_SHADER_RESOURCE_VIEW_DESC srDesc;
    srDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
    srDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    srDesc.Texture1D.MipLevels = 0xffffffff;
    srDesc.Texture1D.MostDetailedMip = 0;

    pd3dDevice->CreateShaderResourceView(m_pNoiseTexture2D, &srDesc, &m_pNoiseSRV);
    SAFE_DELETE_ARRAY(noiseArray);
}

void CHairRenderer::CreateConstantBuffer( ID3D11Device* pd3dDevice )
{
    HRESULT hr;
    D3D11_BUFFER_DESC cbDesc;
    ZeroMemory( &cbDesc, sizeof(cbDesc) );
    cbDesc.Usage = D3D11_USAGE_DYNAMIC;
    cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    cbDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

    cbDesc.ByteWidth = sizeof( CB_PER_FRAME );
    hr = pd3dDevice->CreateBuffer( &cbDesc, NULL, &m_pcbPerFrame ) ;
    if (FAILED(hr))
        ::MessageBoxA(0, "Fail to create constant buffer for frame", "d3d error", 0);
	
    cbDesc.ByteWidth = sizeof( CB_PER_MATERIAL );
    hr = pd3dDevice->CreateBuffer( &cbDesc, NULL, &m_pcbPerMaterial ) ;
    if (FAILED(hr))
        ::MessageBoxA(0, "Fail to create constant buffer for material", "d3d error", 0);
}

void CHairRenderer::CreateVertexBuffers(ID3D11Device* pd3dDevice)
{
    HRESULT hr;
    // Create the screen quad vertex buffer(use StandardVertex for simplicity)
    const StandardVertex screenQuad[6] = 
    {
        { D3DXVECTOR3(-1.0f, -1.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(0.0f, 1.0f) },//0
        { D3DXVECTOR3(-1.0f,  1.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f) },//1
        { D3DXVECTOR3( 1.0f, -1.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f) },//2
        { D3DXVECTOR3( 1.0f, -1.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f) },//2
        { D3DXVECTOR3(-1.0f,  1.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f) },//1
        { D3DXVECTOR3( 1.0f,  1.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(1.0f, 0.0f) } //3
    };

    D3D11_BUFFER_DESC bd;
    bd.Usage =          D3D11_USAGE_DEFAULT;
    bd.ByteWidth =      sizeof( StandardVertex ) * 6; 
    bd.BindFlags =      D3D11_BIND_VERTEX_BUFFER;
    bd.CPUAccessFlags = 0;
    bd.MiscFlags =      0;

    D3D11_SUBRESOURCE_DATA initData;
    initData.pSysMem =  screenQuad;
    initData.SysMemPitch = 0;
    initData.SysMemSlicePitch = 0;
    hr = pd3dDevice->CreateBuffer( &bd, &initData, &m_pScreenQuadVB );
    if( FAILED( hr ) )
        ::MessageBoxA(0, "Fail to create screen quad vertex buffer", "d3d error", 0);
}

void CHairRenderer::OnCreateDevice( ID3D11Device* pd3dDevice, const WCHAR* headFile)
{
    if ( headFile )
    {
        m_MeshHead.CreateMeshFromOBJFile(pd3dDevice, headFile, 
            D3DXVECTOR3(g_fScale,g_fScale,g_fScale), g_vRotation, g_vTranslation);
    }

    m_MeshHair.CreateHairMeshFromFile(pd3dDevice, 
        g_fScale, g_vRotation, g_vTranslation);

    CreateShaderAndLayout(pd3dDevice);
    CreateRenderStateObjects(pd3dDevice);
    CreateTextureAndViews(pd3dDevice);
    CreateConstantBuffer(pd3dDevice);
    CreateVertexBuffers(pd3dDevice);
}

void CHairRenderer::OnResizedSwapChain( ID3D11Device* pd3dDevice, IDXGISwapChain* pSwapChain, const DXGI_SURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext )
{
	HRESULT hr;

	// Release any previously allocated buffers
    SAFE_RELEASE(m_pEyeRootBuffer);
    SAFE_RELEASE(m_pEyeRootBufferUAV);
    SAFE_RELEASE(m_pEyeRootBufferSRV);
    SAFE_RELEASE(m_pEyeNodeBuffer);
    SAFE_RELEASE( m_pEyeNodeBufferUAV);
    SAFE_RELEASE(m_pEyeNodeBufferSRV) ;

	int winWidth, winHeight;

	winWidth = pBackBufferSurfaceDesc->Width;
	winHeight = pBackBufferSurfaceDesc->Height;

    // Eye root buffer
    D3D11_BUFFER_DESC eyeRootBufferDesc;
    eyeRootBufferDesc.BindFlags           = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS;
    eyeRootBufferDesc.ByteWidth           = winWidth * winHeight * sizeof(UINT);
    eyeRootBufferDesc.MiscFlags           = D3D11_RESOURCE_MISC_BUFFER_ALLOW_RAW_VIEWS;
    eyeRootBufferDesc.Usage               = D3D11_USAGE_DEFAULT;
    eyeRootBufferDesc.CPUAccessFlags      = 0;
    eyeRootBufferDesc.StructureByteStride = 0;
    hr = ( pd3dDevice->CreateBuffer(&eyeRootBufferDesc, NULL, &this->m_pEyeRootBuffer) );
    if (FAILED(hr))
        ::MessageBoxA(0, "Fail to create eye ref buffer", "d3d error", 0);
	
    // Create UAV view of eye Offset buffer
    D3D11_UNORDERED_ACCESS_VIEW_DESC UAVEyeRootBufferDesc;
    UAVEyeRootBufferDesc.Format              = DXGI_FORMAT_R32_TYPELESS;
    UAVEyeRootBufferDesc.ViewDimension       = D3D11_UAV_DIMENSION_BUFFER;
    UAVEyeRootBufferDesc.Buffer.FirstElement = 0;
    UAVEyeRootBufferDesc.Buffer.NumElements  = winWidth * winHeight;
    UAVEyeRootBufferDesc.Buffer.Flags        = D3D11_BUFFER_UAV_FLAG_RAW;
    hr = pd3dDevice->CreateUnorderedAccessView(m_pEyeRootBuffer, &UAVEyeRootBufferDesc, &m_pEyeRootBufferUAV);
    if (FAILED(hr))
        ::MessageBoxA(0, "Fail to create UAV for eye ref buffer ", "d3d error", 0);

    // Create SRV view of eye Offset buffer
    D3D11_SHADER_RESOURCE_VIEW_DESC SRVEyeRootBufferDesc;
    SRVEyeRootBufferDesc.Format              = DXGI_FORMAT_R32_UINT;
    SRVEyeRootBufferDesc.ViewDimension       = D3D11_SRV_DIMENSION_BUFFER;
    SRVEyeRootBufferDesc.Buffer.ElementOffset= 0;
    SRVEyeRootBufferDesc.Buffer.ElementWidth = (UINT)(winWidth * winHeight);
    hr = pd3dDevice->CreateShaderResourceView(m_pEyeRootBuffer, &SRVEyeRootBufferDesc, &m_pEyeRootBufferSRV);
    if (FAILED(hr))
        ::MessageBoxA(0, "Fail to create SRV for eye ref buffer ", "d3d error", 0);

    ///////////////////////////////////////////////////////////////////////////////////////////
    // Eye node buffer 
    D3D11_BUFFER_DESC BufferDesc;
    BufferDesc.BindFlags               = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS;
    BufferDesc.ByteWidth               = (DWORD)(g_HairTotalLayers * winWidth * winHeight * sizeof(EYE_FRAGMENT_STRUCT) );
    BufferDesc.CPUAccessFlags          = 0;
    BufferDesc.MiscFlags               = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
    BufferDesc.Usage                   = D3D11_USAGE_DEFAULT;
    BufferDesc.StructureByteStride     = sizeof(EYE_FRAGMENT_STRUCT);
    hr = ( pd3dDevice->CreateBuffer(&BufferDesc, NULL, &m_pEyeNodeBuffer) );
    if (FAILED(hr))
        ::MessageBoxA(0, "Fail to create eye camera all fragments linked list buffer ", "d3d error", 0);
	
    // Create UAV view of Fragment and Link Buffer
    D3D11_UNORDERED_ACCESS_VIEW_DESC UAVDesc;
    UAVDesc.Format                = DXGI_FORMAT_UNKNOWN;
    UAVDesc.ViewDimension         = D3D11_UAV_DIMENSION_BUFFER;
    UAVDesc.Buffer.FirstElement   = 0;
    UAVDesc.Buffer.NumElements    = (DWORD)(g_HairTotalLayers * winWidth * winHeight);
    UAVDesc.Buffer.Flags          = D3D11_BUFFER_UAV_FLAG_COUNTER;
    hr = pd3dDevice->CreateUnorderedAccessView(m_pEyeNodeBuffer, &UAVDesc, &m_pEyeNodeBufferUAV);
    if (FAILED(hr))
        ::MessageBoxA(0, "Fail to create UAV for eye camera all fragments linked list buffer ", "d3d error", 0);

    // Create SRV view of Fragment and Link Buffer
    D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc;
    SRVDesc.Format                = DXGI_FORMAT_UNKNOWN;
    SRVDesc.ViewDimension         = D3D11_SRV_DIMENSION_BUFFER;
    SRVDesc.Buffer.ElementOffset  = 0;
    SRVDesc.Buffer.ElementWidth   = (DWORD)(g_HairTotalLayers * winWidth * winHeight);
    hr = pd3dDevice->CreateShaderResourceView(m_pEyeNodeBuffer, &SRVDesc, &m_pEyeNodeBufferSRV);
    if (FAILED(hr))
        ::MessageBoxA(0, "Fail to create SRV for eye camera all fragments linked list buffer ", "d3d error", 0);
}



extern D3DXMATRIX g_ModelTransformForHead;

void CHairRenderer::SetConstantBuffer( ID3D11DeviceContext* pd3dContext, 
                                        CModelViewerCamera* pCamera, CModelViewerCamera* pCameraLight, /* view camera and light camera */ 
                                        HAIR_PARAMS& hair_params )
{
    HRESULT hr;
    /////////////////////////////////////////////////////////////////////////////////////
    // Set up light camera parameters:
    D3DXMATRIX mViewLight, mProjLight, mViewProjLight;

    D3DXVECTOR3 vLightPosition = *(pCameraLight->GetEyePt());
    D3DXVECTOR3 vLightAt = m_MeshHair.m_bSphere.center;
    D3DXVECTOR3 vUp = D3DXVECTOR3(0,1,0);
    D3DXMatrixLookAtLH(&mViewLight, &vLightPosition, &vLightAt, &vUp);

    D3DXVECTOR3 vLightToObject = vLightPosition - m_MeshHair.m_bSphere.center;
    float dis = D3DXVec3Length(&vLightToObject);

    float min_dis = max(0.001f, dis - m_MeshHair.m_bSphere.radius);
    float max_dis = dis + m_MeshHair.m_bSphere.radius;

    float halfAngle = 1.5f*asin(m_MeshHair.m_bSphere.radius/dis);
    float vfov = 2*halfAngle;

    float ratio = 1;

    D3DXMatrixPerspectiveFovLH(&mProjLight, vfov, ratio, min_dis, max_dis );
    mViewProjLight = mViewLight * mProjLight;

    /////////////////////////////////////////////////////////////////////////////////////////
    // constant buffer per frame
    D3D11_MAPPED_SUBRESOURCE MappedResource;
    hr = pd3dContext->Map( m_pcbPerFrame, 0, D3D11_MAP_WRITE_DISCARD, 0, &MappedResource ) ;
    if (FAILED(hr))
        ::MessageBoxA(0, "Fail to map constant buffer", "d3d error", 0);

    CB_PER_FRAME* pcbPerFrame = ( CB_PER_FRAME* )MappedResource.pData;

    // camera parameters
    D3DXMATRIX mWorld = *(pCamera->GetWorldMatrix());
    D3DXMATRIX mView = *(pCamera->GetViewMatrix());
    D3DXMATRIX mProj = *(pCamera->GetProjMatrix());
    D3DXMATRIX mViewProj = /*mWorld * */mView * mProj;

    D3DXMATRIX mInvViewProj;
    D3DXMatrixInverse(&mInvViewProj, 0, &mViewProj);

    D3DXMatrixTranspose( &pcbPerFrame->m_mViewProj, &mViewProj);
    D3DXMatrixTranspose(&pcbPerFrame->m_mInvViewProj, &mInvViewProj);

    D3DXMatrixTranspose( &pcbPerFrame->m_mWorld, &g_ModelTransformForHead);

    pcbPerFrame->m_vEye = *(pCamera->GetEyePt());

    pcbPerFrame->m_fvFOV = D3DX_PI/4;

    // Light camera parameters
    D3DXMATRIX mInvViewProjLight;
    D3DXMatrixInverse(&mInvViewProjLight, 0, &mViewProjLight);

    D3DXMatrixTranspose( &pcbPerFrame->m_mViewProjLight, &mViewProjLight);
    pcbPerFrame->m_fNearLight = min_dis;
    pcbPerFrame->m_fFarLight = max_dis;

    pcbPerFrame->m_PointLightPos = D3DXVECTOR4(vLightPosition, 1);

    // scene light color
    pcbPerFrame->m_AmbientLightColor = D3DXVECTOR4(g_vAmbientLight, 1.0);
    pcbPerFrame->m_PointLightColor = D3DXVECTOR4( g_vPointLight, 1.f );

    // hair material
    pcbPerFrame->m_MatBaseColor =  D3DXVECTOR4(hair_params.color, 1);
    pcbPerFrame->m_MatKValue = D3DXVECTOR4(hair_params.Ka, hair_params.Kd, hair_params.Ks1, hair_params.Ex1);
    pcbPerFrame->m_fHairKs2 = hair_params.Ks2;
    pcbPerFrame->m_fHairEx2 = hair_params.Ex2;
	
    pcbPerFrame->m_FiberAlpha = hair_params.alpha;
    pcbPerFrame->m_HairSMAlpha = hair_params.alpha_sm;
	
    pcbPerFrame->m_FiberRadius = hair_params.radius;

    pcbPerFrame->m_FiberSpacing = hair_params.fiber_spacing;

    pcbPerFrame->m_bThinTip = (hair_params.bThinTip ? 1.f : -1.f);
    pcbPerFrame->m_bExpandPixels = 1; //(hair_params.bExpandPixels? 1: -1);

    pcbPerFrame->m_WinSize = D3DXVECTOR2((float)g_ScreenWidth, (float)g_ScreenHeight);
  
    pcbPerFrame->m_iTechSM = hair_params.tech_shadow;
	pcbPerFrame->m_bUseCoverage = hair_params.bUseCoverage ? 1 : 0;
	pcbPerFrame->m_bUseAltCoverage = hair_params.bUseAltCoverage ? 1 : 0;
	pcbPerFrame->m_iStrandCopies = hair_params.iStrandCopies;

    pd3dContext->Unmap( m_pcbPerFrame, 0 );

    // Set constant buffer to vertex and pixel shader
    pd3dContext->VSSetConstantBuffers( 0, 1, &m_pcbPerFrame );
    pd3dContext->PSSetConstantBuffers( 0, 1, &m_pcbPerFrame );
    pd3dContext->GSSetConstantBuffers( 0, 1, &m_pcbPerFrame );
}

void CHairRenderer::SetSamplerStates( ID3D11DeviceContext* pd3dContext )
{
    // Set texture sampler states
    ID3D11SamplerState* pSS[3];
    pSS[0] = m_pSamplerStateLinearWrap;
    pSS[1] = m_pSamplerStatePointClamp;
    pSS[2] = m_pSamplerStateCmpLess;
    pd3dContext->PSSetSamplers(0, 3, pSS);
}

void CHairRenderer::RenderHair( ID3D11DeviceContext* pd3dContext,
                                ID3D11VertexShader* pVS, 
                                ID3D11PixelShader* pPS,
                                float density,
                                bool useVertexInstancing /*= false*/,
								int	iStrandCopies /*= 1*/) 
{
    //////////////////////////////////////////////////////////////////////////////////////////////
    // Render hair
    pd3dContext->VSSetShader( pVS, NULL, 0 );
    
    pd3dContext->GSSetShader( NULL, NULL, 0 );

	if ( pPS )
        pd3dContext->PSSetShader( pPS, NULL, 0 );

    pd3dContext->PSSetShaderResources(IDSRV_NOISEMAP, 1, &m_pNoiseSRV);
	
	pd3dContext->VSSetShaderResources(IDSRV_NOISEMAP, 1, &m_pNoiseSRV);
    
	pd3dContext->VSSetShaderResources( IDSRV_GUIDE_HAIR_VERTEX_POSITIONS, 1, &m_MeshHair.m_AMDHairSim.m_GuideHairVertexPositionsSRV );
    pd3dContext->VSSetShaderResources( IDSRV_GUIDE_HAIR_TANGENTS, 1, &m_MeshHair.m_AMDHairSim.m_GuideHairVertexTangentsSRV );

    if (useVertexInstancing)
    {
        pd3dContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );

        UINT stride = 0;
        UINT offset = 0;
        pd3dContext->IASetInputLayout( 0 );
        ID3D11Buffer* buf[]={0};
        pd3dContext->IASetVertexBuffers( 0, 1, buf, &stride, &offset );
        pd3dContext->IASetIndexBuffer( 0, DXGI_FORMAT_R32_UINT, 0 );

        pd3dContext->VSSetShaderResources( IDSRV_HAIR_INDICES,     1, &m_MeshHair.m_AMDHairSim.m_pIndexBufferSRV);
        pd3dContext->VSSetShaderResources( IDSRV_HAIR_THICKNESSES, 1, &m_MeshHair.m_AMDHairSim.m_pThicknessCoeffsSRV);

		pd3dContext->Draw(UINT( density * m_MeshHair.m_AMDHairSim.m_TotalIndexCount) * 3 * iStrandCopies, 0 );
    }
    else
    {
        pd3dContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_LINELIST );

        UINT strides = sizeof( StrandVertex );
        UINT offsets = 0;
        pd3dContext->IASetInputLayout( m_pLayoutHair_2 );
        pd3dContext->IASetVertexBuffers( 0, 1, &m_MeshHair.m_AMDHairSim.m_pVertexBuffer, &strides, &offsets );
        pd3dContext->IASetIndexBuffer( m_MeshHair.m_AMDHairSim.m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0 );

        pd3dContext->DrawIndexed(UINT( density * m_MeshHair.m_AMDHairSim.m_TotalIndexCount), 0, 0 );
    }

    ID3D11ShaderResourceView* nullViews[] = { NULL };
    pd3dContext->VSSetShaderResources( IDSRV_GUIDE_HAIR_VERTEX_POSITIONS, 1, nullViews );
    pd3dContext->VSSetShaderResources( IDSRV_GUIDE_HAIR_TANGENTS, 1, nullViews );
    
}

void CHairRenderer::RenderScreenQuad(ID3D11DeviceContext* pd3dContext,
    ID3D11VertexShader* pVS, ID3D11PixelShader* pPS)
{
    // set shader
    pd3dContext->VSSetShader( pVS, NULL, 0 );
    pd3dContext->PSSetShader( pPS, NULL, 0 );

    UINT strides = sizeof( StandardVertex );
    UINT offsets = 0;
    pd3dContext->IASetInputLayout( m_pLayoutScene );
    pd3dContext->IASetVertexBuffers( 0, 1, &m_pScreenQuadVB, &strides, &offsets );
    pd3dContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    // Draw full screen quad
    pd3dContext->Draw( 6, 0);
}

void CHairRenderer::RenderScene( ID3D11DeviceContext* pd3dContext, ID3D11VertexShader* pVS, ID3D11PixelShader* pPS)
{
    HRESULT hr;

    // set shader
    pd3dContext->VSSetShader( pVS, NULL, 0 );

    pd3dContext->PSSetShader( pPS, NULL, 0 );

    UINT strides = sizeof( StandardVertex );
    UINT offsets = 0;

    pd3dContext->IASetInputLayout( m_pLayoutScene );
    pd3dContext->IASetVertexBuffers( 0, 1, &m_MeshHead.m_pVertexBuffer, &strides, &offsets );
    pd3dContext->IASetIndexBuffer( m_MeshHead.m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0 );
    pd3dContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );

    for(UINT i=0; i<m_MeshHead.m_Subsets.size(); i++)
    {
        // Set material value for each subset
        D3D11_MAPPED_SUBRESOURCE MappedResource;
        hr = pd3dContext->Map( m_pcbPerMaterial, 0, D3D11_MAP_WRITE_DISCARD, 0, &MappedResource ) ;
        if (FAILED(hr))
            ::MessageBoxA(0, "Fail to map constant buffer material", "d3d error", 0);

        CB_PER_MATERIAL* pcbPerMaterial = ( CB_PER_MATERIAL* )MappedResource.pData;

        const Material* pMat = &m_MeshHead.m_Materials[m_MeshHead.m_Subsets[i].materialID];
        pcbPerMaterial->m_MatAmbient = D3DXVECTOR4(pMat->vAmbient, 1);
        pcbPerMaterial->m_MatDiffuse = D3DXVECTOR4(pMat->vDiffuse, -1);
        pcbPerMaterial->m_MatSpecular = D3DXVECTOR4(pMat->vSpecular, (float)pMat->nShininess);
        pcbPerMaterial->m_ScalpColor = D3DXVECTOR4(g_HairColor.x, g_HairColor.y, g_HairColor.z, 1.0);

        // Set shader resource view
        if(	pMat->pTextureRV11)
        {
            pcbPerMaterial->m_MatDiffuse.w = 1;
            pd3dContext->PSSetShaderResources(IDSRV_SCENE, 1, &pMat->pTextureRV11);
        }

        pd3dContext->Unmap( m_pcbPerMaterial, 0 );

        pd3dContext->VSSetConstantBuffers( 1, 1, &m_pcbPerMaterial );
        pd3dContext->PSSetConstantBuffers( 1, 1, &m_pcbPerMaterial );

        int indexCount = m_MeshHead.m_Subsets[i].triangleCount*3;
        int startLocation = m_MeshHead.m_Subsets[i].startIndex;
        pd3dContext->DrawIndexed( indexCount, startLocation, 0 );

    }
}

void CHairRenderer::GenerateSceneSM(ID3D11DeviceContext* pd3dContext)
{
    ///////////////////////////////////////////////////////////////////////////////////////////	
    // Get original render target and depth stencil view
    ID3D11RenderTargetView* pRTV = DXUTGetD3D11RenderTargetView();
    ID3D11DepthStencilView* pDSV = DXUTGetD3D11DepthStencilView();
	ID3D11RasterizerState* pRSTemp;
	pd3dContext->RSGetState( &pRSTemp );

    // Set viewport value
    D3D11_VIEWPORT viewportSMScene = {0, 0, SM_SCENE_WIDTH, SM_SCENE_HEIGHT, 0.0f, 1.0f};
    pd3dContext->RSSetViewports( 1, &viewportSMScene );
    // clear depth for early z
    pd3dContext->ClearDepthStencilView(m_pSMSceneDSV, D3D11_CLEAR_DEPTH|D3D10_CLEAR_STENCIL, 1.0, 0);
    // set render target to shadow map texture
    pd3dContext->OMSetRenderTargets(0, 0, m_pSMSceneDSV);
	pd3dContext->RSSetState( m_pRasterizerStateSceneShadowmap );

    RenderScene(pd3dContext, m_pVSGenerateSceneSM, NULL);

    // reset view port
    D3D11_VIEWPORT viewportWin = {0, 0, (float)g_ScreenWidth, (float)g_ScreenHeight, 0.0f, 1.0f};
    pd3dContext->RSSetViewports(1, &viewportWin);

    // reset render targets
    pd3dContext->OMSetRenderTargets(1, &pRTV, pDSV);
	pd3dContext->RSSetState( pRSTemp );
	pRSTemp->Release();
}

///////////////////////////////////////////////////////////////////////////////////////////
// Generate shadow map for hair
///////////////////////////////////////////////////////////////////////////////////////////
void CHairRenderer::GenerateHairSM(ID3D11DeviceContext* pd3dContext, float density)
{
    ///////////////////////////////////////////////////////////////////////////////////////////	
    // Get original render target and depth stencil view
    ID3D11RenderTargetView* pRTV = DXUTGetD3D11RenderTargetView();
    ID3D11DepthStencilView* pDSV = DXUTGetD3D11DepthStencilView();

    D3D11_VIEWPORT viewportSMHair = {0, 0, SM_HAIR_WIDTH, SM_HAIR_HEIGHT, 0.0f, 1.0f};
    pd3dContext->RSSetViewports( 1, &viewportSMHair );
    // clear depth for early z
    pd3dContext->ClearDepthStencilView(m_pSMHairDSV, D3D11_CLEAR_DEPTH|D3D10_CLEAR_STENCIL, 1.0, 0);
    // set render target to shadow map texture
    pd3dContext->OMSetRenderTargets(0, 0, m_pSMHairDSV);
    RenderHair(pd3dContext, m_pVSGenerateHairSM, NULL, density);
    
    // reset view port
    D3D11_VIEWPORT viewportWin = {0, 0, (float)g_ScreenWidth, (float)g_ScreenHeight, 0.0f, 1.0f};
    pd3dContext->RSSetViewports(1, &viewportWin);

    // reset render targets
    pd3dContext->OMSetRenderTargets(1, &pRTV, pDSV);
}

void CHairRenderer::SetShadowSRVs(ID3D11DeviceContext* pd3dContext, SM_TECH sm_tech)
{
    // set shader resource according to shadow techniques
    if( sm_tech == SDSM )
    {
        pd3dContext->PSSetShaderResources(IDSRV_SCENESM, 1, &m_pSMSceneSRV);
        pd3dContext->PSSetShaderResources(IDSRV_HAIRSM, 1, &m_pSMHairSRV);
    }
}

void CHairRenderer::ResetShadowSRVs(ID3D11DeviceContext* pd3dContext, SM_TECH sm_tech)
{
    ID3D11ShaderResourceView* pNull = 0;
    if( sm_tech == SDSM )
    {
        pd3dContext->PSSetShaderResources(IDSRV_SCENESM, 1, &pNull);
        pd3dContext->PSSetShaderResources(IDSRV_HAIRSM, 1, &pNull);
    }
}
///////////////////////////////////////////////////////////////////////////////////////////
// render hair with shadow effect
///////////////////////////////////////////////////////////////////////////////////////////
void CHairRenderer::RenderWith_Shadow_Transparency(ID3D11DeviceContext* pd3dContext, float density, const HAIR_PARAMS & hairParams)
{
    /////////////////////////////////////////////////////////////////////////////////////////////	
    // Get original render target and depth stencil view
	TIMER_Begin( 0, L"KBufferFill" );
    ID3D11RenderTargetView* pRTV = DXUTGetD3D11RenderTargetView();
    ID3D11DepthStencilView* pDSV = DXUTGetD3D11DepthStencilView();

    // render hair
    const UINT dwClearDataMinusOne[1] = {0xFFFFFFFF};
    
	pd3dContext->ClearUnorderedAccessViewUint(m_pEyeRootBufferUAV, dwClearDataMinusOne);

    // Clear stencil buffer to mask the rendering area
    // Keep depth buffer for correct depth and early z
    pd3dContext->ClearDepthStencilView(pDSV, D3D10_CLEAR_STENCIL, 1.0, 0); 

	ID3D11UnorderedAccessView*  pUAV[] = {m_pEyeRootBufferUAV, m_pEyeNodeBufferUAV, NULL, NULL, NULL, NULL, NULL};
    UINT    pUAVCounters[] = { 0, 0, 0, 0, 0, 0, 0 };
    pd3dContext->OMSetRenderTargetsAndUnorderedAccessViews(1, &pRTV, pDSV, 1, 7, pUAV, pUAVCounters);
    // disable color write if there is no need for fragments counting
    pd3dContext->OMSetBlendState(m_pColorWritesOff, 0, 0xffffffff);

    // Enable depth test to use early z, disable depth write to make sure required layers won't be clipped out in early z
    pd3dContext->OMSetDepthStencilState(m_pDepthTestEnabledNoDepthWritesStencilWriteIncrementDSS, 0x00);

	// Select the specific pixel shader for the chosen transparency implementation
	ID3D11PixelShader* pPSAbuffer = m_pPSABuffer_Hair;
	ID3D11PixelShader* pPSDrawTopKEye = m_pPSDrawTopKEye;

	if(hairParams.bUseCoverage && hairParams.bUseAltCoverage)
	{
		// Can only choose alt coverage if using "original" packing scheme or "Version A"
		if(hairParams.iStrandCopies > 1)
			RenderHair(pd3dContext, m_pVSRenderHairNoGSAlternativeCoverageStrandCopies, pPSAbuffer, density, true, hairParams.iStrandCopies);
		else
			RenderHair(pd3dContext, m_pVSRenderHairNoGSAlternativeCoverage, pPSAbuffer, density, true, 1);
	}
	else
	{
		if(hairParams.iStrandCopies > 1)
			RenderHair(pd3dContext, m_pVSRenderHairNoGSStrandCopies, pPSAbuffer, density, true, hairParams.iStrandCopies);
		else
			RenderHair(pd3dContext, m_pVSRenderHairNoGS, pPSAbuffer, density, true, 1);
	}
	TIMER_End();

    /////////////////////////////////////////////////////////////////////////////////////////
    // Composite nearest k fragments
	TIMER_Begin( 0, L"KBufferSortAndDraw" );
    pd3dContext->OMSetBlendState(m_pBlendStateBlendToBg, 0, 0xffffffff);
    pd3dContext->OMSetDepthStencilState(m_pDepthTestDisabledStencilTestLessDSS, 0x00);

	pUAV[0] = pUAV[1] = pUAV[2] = pUAV[3] = pUAV[4] = pUAV[5] = pUAV[6] = 0; 
    pd3dContext->OMSetRenderTargetsAndUnorderedAccessViews(1, &pRTV, pDSV, 1, 7, pUAV, pUAVCounters);

    pd3dContext->PSSetShaderResources(IDSRV_ROOTBUFFER_EYE, 1, &m_pEyeRootBufferSRV);
    pd3dContext->PSSetShaderResources(IDSRV_NODEBUFFER_EYE, 1, &m_pEyeNodeBufferSRV);

	RenderScreenQuad(pd3dContext, m_pVSScreenQuad, pPSDrawTopKEye);
	TIMER_End();

    ID3D11ShaderResourceView* pNULL = NULL;
    pd3dContext->PSSetShaderResources(IDSRV_ROOTBUFFER_EYE, 1, &pNULL);
    pd3dContext->PSSetShaderResources(IDSRV_NODEBUFFER_EYE, 1, &pNULL);

    pd3dContext->OMSetDepthStencilState(m_pDepthTestEnabledDSS, 0x00);
    pd3dContext->OMSetRenderTargets(1, &pRTV, pDSV);
    pd3dContext->OMSetBlendState(NULL, 0, 0xffffffff);
}

void CHairRenderer::Simulate(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pd3dContext, CModelViewerCamera* pCamera, float fElapsedTime, const HAIR_PARAMS & hair_params)
{
    m_MeshHair.OnFrameRender(pd3dDevice, pd3dContext, pCamera, fElapsedTime, hair_params.wind_direction, hair_params.wind_magnitude);
}

void CHairRenderer::BeginHairFrame(ID3D11DeviceContext* pd3dContext, CModelViewerCamera* pCamera, CModelViewerCamera* pCameraLight, HAIR_PARAMS& hair_params)
{
    SetSamplerStates(pd3dContext);
    SetConstantBuffer(pd3dContext, pCamera, pCameraLight, hair_params);
}

void CHairRenderer::GenerateShadows(ID3D11DeviceContext* pd3dContext, HAIR_PARAMS& hair_params)
{
    ////////////////////////////////////////////////////////////////////
    // render shadow map
    if( hair_params.tech_shadow == SDSM )
    {
        GenerateSceneSM(pd3dContext);
        GenerateHairSM(pd3dContext, hair_params.density);
    }
    
    SetShadowSRVs(pd3dContext, (SM_TECH)hair_params.tech_shadow);

}

void CHairRenderer::RenderScene(ID3D11DeviceContext* pd3dContext)
{
    // set viewport
    D3D11_VIEWPORT viewport = {0, 0, (float)g_ScreenWidth, (float)g_ScreenHeight, 0.0f, 1.0f};
    pd3dContext->RSSetViewports(1, &viewport);

    // render scene
    RenderScene(pd3dContext, m_pVSRenderScene, m_pPSRenderScene);
}

void CHairRenderer::RenderHair(ID3D11DeviceContext* pd3dContext, HAIR_PARAMS& hair_params)
{
    ////////////////////////////////////////////////////////////////////
    // render the hair and scene
    RenderWith_Shadow_Transparency(pd3dContext, hair_params.density, hair_params);
}

void CHairRenderer::EndHairFrame(ID3D11DeviceContext* pd3dContext, HAIR_PARAMS& hair_params)
{
    ResetShadowSRVs(pd3dContext,(SM_TECH)hair_params.tech_shadow);
}

void CHairRenderer::OnDestroy()
{	////////////////////////////////////////////////////////////////////////////
    // Mesh body and hair
    m_MeshHead.OnDestroy();
    m_MeshHair.OnDestroy();
    
    SAFE_RELEASE(m_pScreenQuadVB);
    ////////////////////////////////////////////////////////////////////////////
    // shader

    // vs for rendering hair from the eye camera.
    SAFE_RELEASE(m_pVSRenderHairNoGS);
	SAFE_RELEASE(m_pVSRenderHairNoGSAlternativeCoverage);

	SAFE_RELEASE(m_pVSRenderHairNoGSStrandCopies);
	SAFE_RELEASE(m_pVSRenderHairNoGSAlternativeCoverageStrandCopies);

    // vs for generate hair SM from the light camera.
    SAFE_RELEASE(m_pVSGenerateHairSM);

    // k-buffer
    SAFE_RELEASE(m_pPSABuffer_Hair);
    // PS composite nearest k hair fragments
    SAFE_RELEASE(m_pPSDrawTopKEye)	;

    // vs for rendering scene from eye camera 
    SAFE_RELEASE(m_pVSRenderScene);
    // vs for generate hair SM from the light camera.
    SAFE_RELEASE(m_pVSGenerateSceneSM);
    SAFE_RELEASE(m_pPSRenderScene);


    // PS generate shadow map
    SAFE_RELEASE(m_pVSScreenQuad);

    ////////////////////////////////////////////////////////////////////////////
    // constant buffer
    SAFE_RELEASE(m_pcbPerFrame);
    SAFE_RELEASE(m_pcbPerMaterial);

    ////////////////////////////////////////////////////////////////////////////
    // rendering states
	SAFE_RELEASE(m_pRasterizerStateSceneShadowmap);

    SAFE_RELEASE(m_pBlendStateBlendToBg);
    SAFE_RELEASE(m_pColorWritesOff );

    SAFE_RELEASE( m_pDepthTestEnabledDSS );
    SAFE_RELEASE( m_pDepthTestEnabledNoDepthWritesStencilWriteIncrementDSS );
    SAFE_RELEASE( m_pDepthTestDisabledStencilTestLessDSS );

    SAFE_RELEASE(m_pSamplerStateLinearWrap );
    SAFE_RELEASE(m_pSamplerStatePointClamp );
    SAFE_RELEASE(m_pSamplerStateCmpLess);

    ////////////////////////////////////////////////////////////////////////////
    // vertex layout for hair and scene
    SAFE_RELEASE(m_pLayoutScene);
    SAFE_RELEASE( m_pLayoutHair_0 );
    SAFE_RELEASE( m_pLayoutHair_1 );
    SAFE_RELEASE( m_pLayoutHair_2 );
    SAFE_RELEASE( m_pLayoutHair_3 );
    SAFE_RELEASE( m_pLayoutHair_4 );
    SAFE_RELEASE( m_pLayoutScene_1 );
    SAFE_RELEASE( m_pLayoutScene_2 );

    ////////////////////////////////////////////////////////////////////////////
    // GPU buffer
    // Eye camera root buffer(roots of the linked list)
    SAFE_RELEASE(m_pEyeRootBuffer);
    SAFE_RELEASE(m_pEyeRootBufferUAV);
    SAFE_RELEASE(m_pEyeRootBufferSRV);

    // Eye camera node buffer(all linked list data)
    SAFE_RELEASE(m_pEyeNodeBuffer);
    SAFE_RELEASE( m_pEyeNodeBufferUAV);
    SAFE_RELEASE(m_pEyeNodeBufferSRV) ;

    ////////////////////////////////////////////////////////////////////////////
    // textures and views
    SAFE_RELEASE(m_pNoiseTexture2D);
    SAFE_RELEASE(m_pNoiseSRV);

    // Scene shadow map depth stencil buffer
    SAFE_RELEASE(m_pSMSceneTx);
    SAFE_RELEASE(m_pSMSceneDSV);
    SAFE_RELEASE(m_pSMSceneSRV);

    // Hair shadow map depth stencil buffer
    SAFE_RELEASE(m_pSMHairTx);
    SAFE_RELEASE(m_pSMHairDSV);
    SAFE_RELEASE(m_pSMHairSRV);
}



