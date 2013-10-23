//--------------------------------------------------------------------------------------
// File: TressFXSimulation.cpp
//
// Hair physics simulation using DirectCompute
// 
// Copyright © AMD Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#include "TressFXSimulation.h"
#include "..\\DXUT\\Core\\dxut.h"
#include "util.h"
#include "..\\DXUT\\Optional\\SDKmisc.h"
#include "..\\DXUT\\Optional\\DXUTcamera.h"
#include "TressFXMesh.h"
#include "main.h"
#include "SceneParams.h"

// If you change the value below, you must change it in HairSimulateCS_AMD.hlsl as well. 
#define GROUP_SIZE 64

int g_NumLengthConstraintIterations = 2;
int g_NumLocalShapeMatchingIterations = 1;
int g_LocalShapeConstraintMethod = 4; // must be 1, 2, 3 or 4
float g_GravityMagnitude = 9.82f;

bool g_bCollision = true;
int g_HairSimulationFixedFrameRate = 60;

// top back and sides hair
float g_Damping0 = 0.25f;
float g_StiffnessForLocalShapeMatching0 = 1.0f;
float g_StiffnessForGlobalShapeMatching0 = 0.2f;
float g_GlobalShapeMatchingEffectiveRange0 = 0.3f;

// ponytail
float g_Damping2 = 0.02f;
float g_StiffnessForLocalShapeMatching2 = 0.7f;
float g_StiffnessForGlobalShapeMatching2 = 0.0f;
float g_GlobalShapeMatchingEffectiveRange2 = 0.0f;
    
// front long hair
float g_Damping3 = 0.1f;
float g_StiffnessForLocalShapeMatching3 = 1.0f;
float g_StiffnessForGlobalShapeMatching3 = 0.2f;
float g_GlobalShapeMatchingEffectiveRange3 = 0.3f;

struct ConstBufferCS_Per_Frame
{
    D3DXMATRIX ModelTransformForHead;
	D3DXMATRIX ModelPrevInvTransformForHead; // at previous frame

    float4 ModelRotateForHead;

	float4 Wind;
	float4 Wind1;
	float4 Wind2;
	float4 Wind3;

    int NumLengthConstraintIterations;
    int bCollision;

    float GravityMagnitude;
    float timeStep;
    
    // top hair
    float Damping0;
    float StiffnessForLocalShapeMatching0;
    float StiffnessForGlobalShapeMatching0;
    float GlobalShapeMatchingEffectiveRange0;
    
    // back hair
    float Damping1;
    float StiffnessForLocalShapeMatching1;
    float StiffnessForGlobalShapeMatching1;
    float GlobalShapeMatchingEffectiveRange1;

    // ponytail
    float Damping2;
    float StiffnessForLocalShapeMatching2;
    float StiffnessForGlobalShapeMatching2;
    float GlobalShapeMatchingEffectiveRange2;
    
    // front long hair
    float Damping3;
    float StiffnessForLocalShapeMatching3;
    float StiffnessForGlobalShapeMatching3;
    float GlobalShapeMatchingEffectiveRange3;
};

struct CONSTBUFFER_HAIR
{
    D3DXMATRIX	ViewProjection;
    float4 color;
};

CDX11AMDHairMesh::CDX11AMDHairMesh(void) : 
   m_pVertexBuffer(NULL)
  , m_pIndexBuffer(NULL)
  , m_pThicknessCoeffs(NULL)
  , m_pIndexBufferSRV(NULL)
  , m_pThicknessCoeffsSRV(NULL)
{
    m_CSSkipSimulateHair = NULL;
	m_CSSimulateHair_A = NULL;
	m_CSSimulateHair_B = NULL;
	m_CSSimulateHair_C = NULL;
	m_CSSimulateHair_D = NULL;
    m_GuideHairVertexPositionsUAB = NULL;
    m_GuideHairVertexPositionsPrevUAB = NULL;
    m_pCBCSPerFrame = NULL;
    
    m_GuideHairVertexPositionsSRV = NULL;	
    
    m_GuideHairVerticesOffsetsBuffer = NULL;
    m_GuideHairVerticesOffsetsSRV = NULL;

    m_GuideHairStrandTypeBuffer = NULL;
    m_GuideHairStrandTypeSRV = NULL;

    m_GuideHairVertexPositionsUAV = NULL;
    m_GuideHairVertexPositionsPrevUAV = NULL;

    m_GuideHairLengthBuffer = NULL;
    m_GuideHairRestLengthSRV = NULL;
	
    m_InitialGuideHairPositionsSRV = NULL;

    m_GuideHairVertexTangentsUAB = NULL;
    m_GuideHairVertexTangentsSRV = NULL;
    m_GuideHairVertexTangentsUAV = NULL;

    m_GuideHairRefVectorsBuffer = NULL;
    m_GuideHairRefVecsInLocalFrameSRV = NULL;
    
    m_GlobalRotationsUAB = NULL;
    m_GlobalRotationsUAV = NULL;
	
    m_LocalRotationsUAB = NULL;
    m_LocalRotationsUAV = NULL;
	    
	m_MaxNumOfVerticesInStrand = 32;
}

CDX11AMDHairMesh::~CDX11AMDHairMesh(void)
{
    if ( m_pTempVertices )
    {
        delete [] m_pTempVertices;
        m_pTempVertices = NULL;
    }

    if ( m_pTempTangents )
    {
        delete [] m_pTempTangents;
        m_pTempTangents = NULL;
    }

    if ( m_GuideHairVerticesOffsets )
    {
        delete [] m_GuideHairVerticesOffsets;
        m_GuideHairVerticesOffsets = NULL;
    }

    if ( m_GuideHairStrandType )
    {
        delete [] m_GuideHairStrandType;
        m_GuideHairStrandType = NULL;
    }
}

HRESULT CDX11AMDHairMesh::OnCreateDevice(ID3D11Device* pd3dDevice)
{
    HRESULT hr;
	static bool bHairLoaded = false;
    
	if (!bHairLoaded)
	{
		if ( !(
				m_HairAssetLoader.LoadAppend(g_hair_top, 0, true, m_MaxNumOfVerticesInStrand)      &&
				m_HairAssetLoader.LoadAppend(g_hair_back, 1, false, m_MaxNumOfVerticesInStrand)    &&
				m_HairAssetLoader.LoadAppend(g_hair_ponytail, 2, true, m_MaxNumOfVerticesInStrand) &&
				m_HairAssetLoader.LoadAppend(g_hair_front_long, 3, true, m_MaxNumOfVerticesInStrand)
			  )
			)
		{
			char sMsg[200];
			sprintf(sMsg, "Failed to load hair file");
        
			::MessageBoxA(0, sMsg, "file loading error", 0);
			return S_FALSE;
		}
		bHairLoaded = true;
	}
            
	m_NumGuideHairStrands = m_HairAssetLoader.GetHairs().size();
	m_NumGuideHairVertices = m_HairAssetLoader.GetNumTotalVertices();

    m_pTempVertices = new D3DXVECTOR4[m_NumGuideHairVertices];

    m_GuideHairVerticesOffsets = new int[m_HairAssetLoader.GetHairs().size()];
    m_GuideHairStrandType = new int[m_HairAssetLoader.GetHairs().size()];
        
    int index = 0; 

    for(int i=0;i<int(m_HairAssetLoader.GetHairs().size());i++)
    {
        int groupId = 0;

        for(int j=0;j<int(m_HairAssetLoader.GetHairs().at(i)->GetVertexArray().size());j++)
        {
            D3DXVECTOR4 v;
            v.x = m_HairAssetLoader.GetHairs().at(i)->GetVertexArray().at(j).m_Pos.m_X;
            v.y = m_HairAssetLoader.GetHairs().at(i)->GetVertexArray().at(j).m_Pos.m_Y;
            v.z = m_HairAssetLoader.GetHairs().at(i)->GetVertexArray().at(j).m_Pos.m_Z;
            v.w = m_HairAssetLoader.GetHairs().at(i)->GetVertexArray().at(j).m_InvMass;
            
            m_pTempVertices[index++] = v;

            groupId = m_HairAssetLoader.GetHairs().at(i)->GetVertexArray().at(j).m_GroupID;
        }

        m_GuideHairVerticesOffsets[i] = index;
        m_GuideHairStrandType[i] = groupId;
    }
        
    m_HairStrands.clear();
    int numStrands = (int)m_HairAssetLoader.GetHairs().size();
    m_HairStrands.resize(numStrands);

    int indexTang = 0;
    m_pTempTangents = new float4[m_NumGuideHairVertices];
    
    for ( int i=0; i < numStrands; i++ )
    {
        int numVerts = int(m_HairAssetLoader.GetHairs().at(i)->GetVertexArray().size());
        m_HairStrands[i].resize(numVerts);

		for( int v=0; v < numVerts; v++ )
        {
            D3DXVECTOR3 pos;
            pos.x = m_HairAssetLoader.GetHairs().at(i)->GetVertexArray().at(v).m_Pos.m_X;
            pos.y = m_HairAssetLoader.GetHairs().at(i)->GetVertexArray().at(v).m_Pos.m_Y;
            pos.z = m_HairAssetLoader.GetHairs().at(i)->GetVertexArray().at(v).m_Pos.m_Z;

            m_HairStrands[i][v].position = pos;
        }


        CDX11TressFXHairMesh::ComputeStrandTangent(m_HairStrands[i]);
		CDX11TressFXHairMesh::ComputeStrandTexcoordZ(m_HairStrands[i]);

        for( int v=0; v < numVerts; v++ )
        {
            m_pTempTangents[indexTang].x = m_HairStrands[i][v].tangent.x;
            m_pTempTangents[indexTang].y = m_HairStrands[i][v].tangent.y;
            m_pTempTangents[indexTang].z = m_HairStrands[i][v].tangent.z;

            indexTang++;
        }
    }

    //---------------
    // Vertex buffer
    //---------------
    StrandVertex* vertices = new StrandVertex[m_NumGuideHairVertices];
    float * thicknessCoeffs = new float[m_NumGuideHairVertices];

    int indexVert = 0; 
    
    for ( int i=0; i < numStrands; i++ )
    {
        int numVerts = int(m_HairAssetLoader.GetHairs().at(i)->GetVertexArray().size());

        for( int v=0; v < numVerts; v++ )
        {
            vertices[indexVert]        = m_HairStrands[i][v];
            float tVal                 = vertices[indexVert].texcoord.z;
            thicknessCoeffs[indexVert] = sqrt(1.f - tVal * tVal);
            ++indexVert;
        }
    }

    D3D11_BUFFER_DESC bd;
    bd.Usage               = D3D11_USAGE_DEFAULT;
    bd.ByteWidth           = sizeof( StrandVertex ) * m_NumGuideHairVertices;
    bd.BindFlags           = D3D11_BIND_VERTEX_BUFFER;
    bd.CPUAccessFlags      = 0;
    bd.MiscFlags           = 0;

    D3D11_SUBRESOURCE_DATA InitData;
    InitData.pSysMem = vertices;
    V_RETURN( pd3dDevice->CreateBuffer( &bd, &InitData, &m_pVertexBuffer ) );
	
    //thickness coeff buffer
    {
        D3D11_BUFFER_DESC bd;
        ZeroMemory(&bd, sizeof(bd));

        bd.Usage     = D3D11_USAGE_IMMUTABLE;
        bd.ByteWidth = sizeof(float) * m_NumGuideHairVertices;
        bd.BindFlags = D3D11_BIND_SHADER_RESOURCE;
        bd.StructureByteStride = sizeof(float);

        D3D11_SUBRESOURCE_DATA srData;
        ZeroMemory(&srData, sizeof(srData));
        srData.pSysMem = thicknessCoeffs;

        V_RETURN( pd3dDevice->CreateBuffer( &bd, &srData, &m_pThicknessCoeffs) );
    }

    //thickness coeff buffer srv
    {
        D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc;
        ZeroMemory(&SRVDesc, sizeof(SRVDesc));

        SRVDesc.Format                = DXGI_FORMAT_R32_FLOAT;
        SRVDesc.ViewDimension         = D3D11_SRV_DIMENSION_BUFFER;
        SRVDesc.Buffer.FirstElement  = 0;
        SRVDesc.Buffer.NumElements   = m_NumGuideHairVertices;
        
        V_RETURN( pd3dDevice->CreateShaderResourceView(m_pThicknessCoeffs, &SRVDesc, &m_pThicknessCoeffsSRV) );
    }

    delete [] vertices;
    delete [] thicknessCoeffs;

    //--------------
    // Index buffer
    //--------------
    vector<int> indices;
    indices.reserve(m_NumGuideHairVertices * 2);

    int id=0;

    for(int i=0;i<int(m_HairAssetLoader.GetHairs().size());i++)
    {
        int vertCount = (int)m_HairAssetLoader.GetHairs().at(i)->GetVertexArray().size();

        for ( int j = 0; j < vertCount - 1; j++ )
        {
            indices.push_back(id);
            indices.push_back(id+1);
            id++;
        }

        id++;
    }

    m_TotalIndexCount = indices.size();

    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof( unsigned int ) * indices.size();
    bd.BindFlags = D3D11_BIND_INDEX_BUFFER | D3D11_BIND_SHADER_RESOURCE;
    bd.CPUAccessFlags = 0;
    bd.MiscFlags = 0;

    InitData.pSysMem = &(indices[0]);
    hr = pd3dDevice->CreateBuffer( &bd, &InitData, &m_pIndexBuffer );

    if( FAILED(hr) )
        return hr;
    
    //index buffer srv
    {
        D3D11_SHADER_RESOURCE_VIEW_DESC sbSRVDesc;
        sbSRVDesc.Buffer.FirstElement           = 0;
        sbSRVDesc.Buffer.NumElements            = (UINT)indices.size();
        sbSRVDesc.Format                        = DXGI_FORMAT_R32_UINT;
        sbSRVDesc.ViewDimension                 = D3D11_SRV_DIMENSION_BUFFER;
        SAFE_RELEASE(m_pIndexBufferSRV);
        V_RETURN( pd3dDevice->CreateShaderResourceView(m_pIndexBuffer, &sbSRVDesc, &m_pIndexBufferSRV) );
    }

    //--------------
    // Add shaders to cache
    //--------------

    // Ensure all shaders (and input layouts) are released
    SAFE_RELEASE( m_CSSimulateHair_A );
    SAFE_RELEASE( m_CSSimulateHair_B );
    SAFE_RELEASE( m_CSSimulateHair_C );
    SAFE_RELEASE( m_CSSimulateHair_D );

    // Compute Shaders
	g_ShaderCache.AddShader( (ID3D11DeviceChild**)&m_CSSkipSimulateHair, AMD::ShaderCache::SHADER_TYPE_COMPUTE, L"cs_5_0", L"SkipSimulateHair",
        L"shaders\\Source\\HairSimulate.hlsl", 0, NULL, NULL, NULL, 0 );
    g_ShaderCache.AddShader( (ID3D11DeviceChild**)&m_CSSimulateHair_A, AMD::ShaderCache::SHADER_TYPE_COMPUTE, L"cs_5_0", L"SimulateHair_A",
        L"shaders\\Source\\HairSimulate.hlsl", 0, NULL, NULL, NULL, 0 );
    g_ShaderCache.AddShader( (ID3D11DeviceChild**)&m_CSSimulateHair_B, AMD::ShaderCache::SHADER_TYPE_COMPUTE, L"cs_5_0", L"SimulateHair_B",
        L"shaders\\Source\\HairSimulate.hlsl", 0, NULL, NULL, NULL, 0 );
    g_ShaderCache.AddShader( (ID3D11DeviceChild**)&m_CSSimulateHair_C, AMD::ShaderCache::SHADER_TYPE_COMPUTE, L"cs_5_0", L"SimulateHair_C",
        L"shaders\\Source\\HairSimulate.hlsl", 0, NULL, NULL, NULL, 0 );
    g_ShaderCache.AddShader( (ID3D11DeviceChild**)&m_CSSimulateHair_D, AMD::ShaderCache::SHADER_TYPE_COMPUTE, L"cs_5_0", L"SimulateHair_D",
        L"shaders\\Source\\HairSimulate.hlsl", 0, NULL, NULL, NULL, 0 );

    //-------------------------
    // Create constant buffers
    //-------------------------
    D3D11_BUFFER_DESC cbDesc;
    ZeroMemory( &cbDesc, sizeof(cbDesc) );
    cbDesc.Usage = D3D11_USAGE_DYNAMIC;
    cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    cbDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    cbDesc.ByteWidth = sizeof( CONSTBUFFER_HAIR );
    
    if (FAILED(hr))
    {
        ::MessageBoxA(0, "Fail to create constant buffer for plane", "d3d error", 0);
        return hr;
    }

    hr = CreateComputeShaderConstantBuffers(pd3dDevice);
    
    if (FAILED(hr))
    {
        ::MessageBoxA(0, "Fail to create compute shader constant buffers", "d3d error", 0);
        return hr;
    }

    CreateBufferAndViews(pd3dDevice);

    //------------------------------------------
    // Clean up temporarily allocated momories
    //------------------------------------------
    if ( m_pTempVertices )
    {
        delete [] m_pTempVertices;
        m_pTempVertices = NULL;
    }

    if ( m_pTempTangents )
    {
        delete [] m_pTempTangents;
        m_pTempTangents = NULL;
    }

    if ( m_GuideHairVerticesOffsets )
    {
        delete [] m_GuideHairVerticesOffsets;
        m_GuideHairVerticesOffsets = NULL;
    }

    if ( m_GuideHairStrandType )
    {
        delete [] m_GuideHairStrandType;
        m_GuideHairStrandType = NULL;
    }

    return S_OK;
}

bool g_hairReset = false;

HRESULT CDX11AMDHairMesh::Reset(ID3D11Device* pd3dDevice)
{
    OnDestroy();
    return OnCreateDevice(pd3dDevice);
}

HRESULT CDX11AMDHairMesh::Simulate(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pd3dContext, float fElapsedTime, const CVector3D & windDir, float windMag)
{
    //------------------------------------
    // Simulate hair using Compute Shader
    //------------------------------------
	HRESULT hr = S_OK; 

	hr = SimulateDX11(pd3dContext, fElapsedTime, windDir, windMag);
	if ( FAILED(hr) )
		return -1;

	return hr;
}

const float MATH_PI2 = 3.14159265359f;
#define DEG_TO_RAD2(d) (d * MATH_PI2 / 180)

HRESULT CDX11AMDHairMesh::SimulateDX11(ID3D11DeviceContext* pd3dContext, float fElapsedTime, const CVector3D & windDir, float windMag)
{
	float idealElapsedTime = 1.0f/g_HairSimulationFixedFrameRate; //sec/frame
	static float elapsedTimeSinceLastSim = 0;
	
	// If you want to skip simulate, set the following variable true. 
	// It will apply the global head tranform to all hair vertices uniforms. 
	// As a result, hair will move as a rigid motion following head tranform. 
	bool bSkipSimulation = false;

	elapsedTimeSinceLastSim += fElapsedTime;

    if ( !g_bModelTransformUpdated )
        D3DXMatrixIdentity(&g_ModelTransform);

    HRESULT hr = S_OK;

    UINT initCounts = 0;    

    //--------------------
    // CB_CS_TRANSFORMS
    //--------------------
    D3D11_MAPPED_SUBRESOURCE MappedResource;
    
    //--------------------
    // ConstBufferCS_Per_Frame
    //--------------------
    V( pd3dContext->Map(m_pCBCSPerFrame, 0, D3D11_MAP_WRITE_DISCARD, 0, &MappedResource));
        ConstBufferCS_Per_Frame* pCSPerFrame = ( ConstBufferCS_Per_Frame* )MappedResource.pData;
        pCSPerFrame->ModelTransformForHead = g_ModelTransformForHead;

        D3DXMATRIX ModelInvTransformForHead;
        D3DXMatrixInverse(&ModelInvTransformForHead, NULL, &g_ModelTransformForHead);

		pCSPerFrame->ModelPrevInvTransformForHead = g_ModelPrevInvTransformForHead;
		g_ModelPrevInvTransformForHead = ModelInvTransformForHead;

        D3DXQUATERNION quat;
        D3DXQuaternionRotationMatrix(&quat, &g_ModelTransformForHead);
        pCSPerFrame->ModelRotateForHead = float4(quat.x, quat.y, quat.z, quat.w);

        D3DXQuaternionRotationMatrix(&quat, &ModelInvTransformForHead);
       
        pCSPerFrame->NumLengthConstraintIterations = g_NumLengthConstraintIterations;
	    pCSPerFrame->bCollision = (g_bCollision == true) ? 1 : 0;

        pCSPerFrame->GravityMagnitude = g_GravityMagnitude;
        
		pCSPerFrame->timeStep = idealElapsedTime;

        static int frame = 0;

		float wM = windMag * (pow( sin(frame*0.05f), 2.0f ) + 0.5f);

		CVector3D windDirN(windDir);
		windDirN.Normalize();

		CVector3D XAxis(1.0f, 0, 0);
		CVector3D xCrossW = XAxis.Cross(windDirN);

		CQuaternion rotFromXAxisToWindDir;
		rotFromXAxisToWindDir.SetIdentity();

		float angle = asin(xCrossW.Length());

		if ( angle > 0.001 )
		{
			rotFromXAxisToWindDir.SetRotation(xCrossW.Normalize(), angle);
		}

		float angleToWideWindCone = DEG_TO_RAD2(40.f);

		{
			CVector3D rotAxis(0, 1.0f, 0);
			
			CQuaternion rot(rotAxis, angleToWideWindCone);
			CVector3D newWindDir = rotFromXAxisToWindDir * rot * XAxis; 
			pCSPerFrame->Wind = float4(newWindDir.m_X * wM, newWindDir.m_Y * wM, newWindDir.m_Z * wM, (float)frame);
		}

		{
			CVector3D rotAxis(0, -1.0f, 0);
			CQuaternion rot(rotAxis, angleToWideWindCone);
			CVector3D newWindDir = rotFromXAxisToWindDir * rot * XAxis;
			pCSPerFrame->Wind1 = float4(newWindDir.m_X * wM, newWindDir.m_Y * wM, newWindDir.m_Z * wM, (float)frame);
		}

		{
			CVector3D rotAxis(0, 0, 1.0f);
			CQuaternion rot(rotAxis, angleToWideWindCone);
			CVector3D newWindDir = rotFromXAxisToWindDir * rot * XAxis;
			pCSPerFrame->Wind2 = float4(newWindDir.m_X * wM, newWindDir.m_Y * wM, newWindDir.m_Z * wM, (float)frame);
		}

		{
			CVector3D rotAxis(0, 0, -1.0f);
			CQuaternion rot(rotAxis, angleToWideWindCone);
			CVector3D newWindDir = rotFromXAxisToWindDir * rot * XAxis;
			pCSPerFrame->Wind3 = float4(newWindDir.m_X * wM, newWindDir.m_Y * wM, newWindDir.m_Z * wM, (float)frame);
		}

        frame++;

        // top
        pCSPerFrame->Damping0 = g_Damping0;
        pCSPerFrame->StiffnessForLocalShapeMatching0 = g_StiffnessForLocalShapeMatching0;
        pCSPerFrame->StiffnessForGlobalShapeMatching0 = g_StiffnessForGlobalShapeMatching0;
        pCSPerFrame->GlobalShapeMatchingEffectiveRange0 = g_GlobalShapeMatchingEffectiveRange0;

        // back
        pCSPerFrame->Damping1 = g_Damping0;
        pCSPerFrame->StiffnessForLocalShapeMatching1 = g_StiffnessForLocalShapeMatching0;
        pCSPerFrame->StiffnessForGlobalShapeMatching1 = g_StiffnessForGlobalShapeMatching0;
        pCSPerFrame->GlobalShapeMatchingEffectiveRange1 = g_GlobalShapeMatchingEffectiveRange0;

        // ponytail
        pCSPerFrame->Damping2 = g_Damping2;
        pCSPerFrame->StiffnessForLocalShapeMatching2 = g_StiffnessForLocalShapeMatching2;
        pCSPerFrame->StiffnessForGlobalShapeMatching2 = g_StiffnessForGlobalShapeMatching2;
        pCSPerFrame->GlobalShapeMatchingEffectiveRange2 = g_GlobalShapeMatchingEffectiveRange2;
    
        // front long
        pCSPerFrame->Damping3 = g_Damping3;
        pCSPerFrame->StiffnessForLocalShapeMatching3 = g_StiffnessForLocalShapeMatching3;
        pCSPerFrame->StiffnessForGlobalShapeMatching3 = g_StiffnessForGlobalShapeMatching3;
        pCSPerFrame->GlobalShapeMatchingEffectiveRange3 = g_GlobalShapeMatchingEffectiveRange3;
    pd3dContext->Unmap(m_pCBCSPerFrame, 0);

    pd3dContext->CSSetConstantBuffers(0, 1, &m_pCBCSPerFrame);

    //------------------------
    //Set the shader resources
    //------------------------
    ID3D11ShaderResourceView* ppSRV[4] = { m_GuideHairVerticesOffsetsSRV, 
                                           m_GuideHairRestLengthSRV,
                                           m_GuideHairStrandTypeSRV,
                                           m_GuideHairRefVecsInLocalFrameSRV
                                           };

    pd3dContext->CSSetShaderResources( 0, 4, ppSRV);

    //---------------------------
    //Bind unordered access views
    //---------------------------
    ID3D11UnorderedAccessView* ppUAV[8] = { m_GuideHairVertexPositionsUAV,
                                            m_GuideHairVertexPositionsPrevUAV,
                                            m_GuideHairVertexTangentsUAV,
                                            m_InitialGuideHairPositionsUAV, 
                                            m_GlobalRotationsUAV,
                                            m_LocalRotationsUAV };

    pd3dContext->CSSetUnorderedAccessViews( 0, 8, ppUAV, &initCounts );

    //-----------------------
    // Run the compute shader
    //-----------------------
	if ( bSkipSimulation )
	{
		// In this case, we don't simulate hair. Instead, we use the previous vertex positions and 
		// transform them using the head transform as a rigid motion.
		pd3dContext->CSSetShader( m_CSSkipSimulateHair, NULL, 0 );
	}
	else
	{
		int numOfGroupsForCS = 0;

		int numOfStrandsPerThreadGroup = GROUP_SIZE/m_MaxNumOfVerticesInStrand;

		// Integrate and global shape constraints
		// One thread computes one vertex
		numOfGroupsForCS = m_NumGuideHairStrands / numOfStrandsPerThreadGroup;
		pd3dContext->CSSetShader( m_CSSimulateHair_A, NULL, 0 );
		pd3dContext->Dispatch(numOfGroupsForCS, 1, 1);

		// Local shape constraints. If the hair is very curly, increase the iteration so that
		// hair style can be preserved well. 
		// One thread computes one strand
		for ( int iteration = 0; iteration < g_NumLocalShapeMatchingIterations; iteration++)
		{
			int numOfGroupsForCS_B = (int)((float)m_NumGuideHairStrands/(float)GROUP_SIZE);
			pd3dContext->CSSetShader( m_CSSimulateHair_B, NULL, 0 );
			pd3dContext->Dispatch(numOfGroupsForCS_B, 1, 1);
		}

		// Wind and edge length constraints
		// One thread computes one vertex
		pd3dContext->CSSetShader( m_CSSimulateHair_C, NULL, 0 );
		pd3dContext->Dispatch(numOfGroupsForCS, 1, 1);

		// Collision and tangents
		// One thread computes one vertex
		pd3dContext->CSSetShader( m_CSSimulateHair_D, NULL, 0 );
		pd3dContext->Dispatch(numOfGroupsForCS, 1, 1);
	}

    //--------------------------
    // Unbind resources for CS
    //--------------------------
    ID3D11UnorderedAccessView* ppUAViewNULL[8] = { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL };
    pd3dContext->CSSetUnorderedAccessViews( 0, 8, ppUAViewNULL, &initCounts );
    
    ID3D11ShaderResourceView* ppSRVNULL[4] = { NULL, NULL, NULL, NULL};
    pd3dContext->CSSetShaderResources( 0, 4, ppSRVNULL );

	if ( !bSkipSimulation )
	{
		elapsedTimeSinceLastSim = 0;
	}

    return hr;
}

HRESULT CDX11AMDHairMesh::CreateComputeShaderConstantBuffers(ID3D11Device* pd3dDevice)
{
    HRESULT hr = S_OK;

    D3D11_BUFFER_DESC Desc;
    Desc.Usage = D3D11_USAGE_DYNAMIC;
    Desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    Desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    Desc.MiscFlags = 0;
    Desc.ByteWidth = sizeof( ConstBufferCS_Per_Frame );
    SAFE_RELEASE(m_pCBCSPerFrame);
    V_RETURN( pd3dDevice->CreateBuffer(&Desc, NULL, &m_pCBCSPerFrame));
       
    return S_OK;
}

static float vec3Length(D3DXVECTOR3 vec)
{
    return sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}


HRESULT CDX11AMDHairMesh::CreateBufferAndViews(ID3D11Device* pd3dDevice)
{
    HRESULT hr;

    //--------------------------------
    // m_GuideHairVerticesOffsetsSRV
    //--------------------------------
    {
        D3D11_SUBRESOURCE_DATA initialData;
        initialData.pSysMem = m_GuideHairVerticesOffsets;

        HRESULT hr;
        D3D11_BUFFER_DESC bufferDesc;
        bufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
        bufferDesc.CPUAccessFlags = 0;
        bufferDesc.MiscFlags = 0;
        bufferDesc.ByteWidth = m_NumGuideHairStrands*sizeof(int);
        bufferDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    
        SAFE_RELEASE(m_GuideHairVerticesOffsetsBuffer);
        V_RETURN(pd3dDevice->CreateBuffer(&bufferDesc, &initialData, &m_GuideHairVerticesOffsetsBuffer));
    
        D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc;
        SRVDesc.Format = DXGI_FORMAT_R32_SINT;
        SRVDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
        SRVDesc.Buffer.FirstElement = 0;
        SRVDesc.Buffer.NumElements = m_NumGuideHairStrands;
        SAFE_RELEASE(m_GuideHairVerticesOffsetsSRV);
        V_RETURN(pd3dDevice->CreateShaderResourceView(m_GuideHairVerticesOffsetsBuffer, &SRVDesc, &m_GuideHairVerticesOffsetsSRV));
    }

    //--------------------------------
    // m_GuideHairStrandTypeSRV
    //--------------------------------
    {
        D3D11_SUBRESOURCE_DATA initialData;
        initialData.pSysMem = m_GuideHairStrandType;

        HRESULT hr;
        D3D11_BUFFER_DESC bufferDesc;
        bufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
        bufferDesc.CPUAccessFlags = 0;
        bufferDesc.MiscFlags = 0;
        bufferDesc.ByteWidth = m_NumGuideHairStrands*sizeof(int);
        bufferDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    
        SAFE_RELEASE(m_GuideHairStrandTypeBuffer);
        V_RETURN(pd3dDevice->CreateBuffer(&bufferDesc, &initialData, &m_GuideHairStrandTypeBuffer));
    
        D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc;
        SRVDesc.Format = DXGI_FORMAT_R32_SINT;
        SRVDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
        SRVDesc.Buffer.FirstElement = 0;
        SRVDesc.Buffer.NumElements = m_NumGuideHairStrands;
        SAFE_RELEASE(m_GuideHairStrandTypeSRV);
        V_RETURN(pd3dDevice->CreateShaderResourceView(m_GuideHairStrandTypeBuffer, &SRVDesc, &m_GuideHairStrandTypeSRV));
    }

    //---------------------------------
    // m_InitialGuideHairPositionsSRV
    // m_InitialGuideHairPositionsUAV
    //---------------------------------
    {
        ID3D11Buffer* pInitialGuideHairPositionsBuffer = NULL;

        D3D11_SUBRESOURCE_DATA initialData;
        initialData.pSysMem = m_pTempVertices;

        D3D11_BUFFER_DESC bufferDesc;
        bufferDesc.ByteWidth = m_NumGuideHairVertices * sizeof(D3DXVECTOR4);
        bufferDesc.CPUAccessFlags = 0;
        bufferDesc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
        bufferDesc.Usage = D3D11_USAGE_DEFAULT; //D3D11_USAGE_IMMUTABLE;
        bufferDesc.StructureByteStride  = sizeof(D3DXVECTOR4);
        bufferDesc.BindFlags = D3D11_BIND_UNORDERED_ACCESS | D3D11_BIND_SHADER_RESOURCE;

        SAFE_RELEASE(pInitialGuideHairPositionsBuffer);
        SAFE_RELEASE(m_InitialGuideHairPositionsSRV);
        V_RETURN(pd3dDevice->CreateBuffer(&bufferDesc, &initialData, &pInitialGuideHairPositionsBuffer));

        D3D11_SHADER_RESOURCE_VIEW_DESC desc;
        desc.Buffer.FirstElement = 0;
        desc.Buffer.NumElements = m_NumGuideHairVertices;
        desc.Format = DXGI_FORMAT_UNKNOWN;
        desc.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
        SAFE_RELEASE(m_InitialGuideHairPositionsSRV);
        V_RETURN(pd3dDevice->CreateShaderResourceView(pInitialGuideHairPositionsBuffer, &desc, &m_InitialGuideHairPositionsSRV));
        
        D3D11_UNORDERED_ACCESS_VIEW_DESC sbUAVDesc;
        sbUAVDesc.Buffer.FirstElement       = 0;
        sbUAVDesc.Buffer.Flags              = 0;
        sbUAVDesc.Buffer.NumElements        = m_NumGuideHairVertices;
        sbUAVDesc.Format                    = DXGI_FORMAT_UNKNOWN; 
        sbUAVDesc.ViewDimension             = D3D11_UAV_DIMENSION_BUFFER;
        SAFE_RELEASE(m_InitialGuideHairPositionsUAV);
        V_RETURN( pd3dDevice->CreateUnorderedAccessView(pInitialGuideHairPositionsBuffer, &sbUAVDesc, &m_InitialGuideHairPositionsUAV) );

        SAFE_RELEASE(pInitialGuideHairPositionsBuffer);
    }
    
    // ------------------------
    // m_GuideHairVertexPositionsUAB
    //-------------------------
    {
        D3D11_SUBRESOURCE_DATA initialData;
        initialData.pSysMem = m_pTempVertices;
        
        D3D11_BUFFER_DESC bufferDescUA;
        bufferDescUA.ByteWidth = m_NumGuideHairVertices * sizeof(D3DXVECTOR4);
        bufferDescUA.Usage = D3D11_USAGE_DEFAULT;
        bufferDescUA.BindFlags =  D3D11_BIND_UNORDERED_ACCESS | D3D11_BIND_SHADER_RESOURCE;
        bufferDescUA.CPUAccessFlags = 0;
        bufferDescUA.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
        bufferDescUA.StructureByteStride  = sizeof(D3DXVECTOR4);
        SAFE_RELEASE(m_GuideHairVertexPositionsUAB);
        SAFE_RELEASE(m_GuideHairVertexPositionsPrevUAB);
        V_RETURN(pd3dDevice->CreateBuffer(&bufferDescUA, &initialData, &m_GuideHairVertexPositionsUAB));
        V_RETURN(pd3dDevice->CreateBuffer(&bufferDescUA, &initialData, &m_GuideHairVertexPositionsPrevUAB));
    }

    // -----------------------------
    // m_GuideHairVertexTangentsUAB
    //------------------------------
    {		
        D3D11_SUBRESOURCE_DATA initialData;
        initialData.pSysMem = m_pTempTangents;

        D3D11_BUFFER_DESC bufferDescUA;
        bufferDescUA.ByteWidth = m_NumGuideHairVertices * sizeof(D3DXVECTOR4);
        bufferDescUA.Usage = D3D11_USAGE_DEFAULT;
        bufferDescUA.BindFlags =  D3D11_BIND_UNORDERED_ACCESS | D3D11_BIND_SHADER_RESOURCE;
        bufferDescUA.CPUAccessFlags = 0;
        bufferDescUA.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
        bufferDescUA.StructureByteStride  = sizeof(D3DXVECTOR4);
        SAFE_RELEASE(m_GuideHairVertexTangentsUAB);
        V_RETURN(pd3dDevice->CreateBuffer(&bufferDescUA, &initialData, &m_GuideHairVertexTangentsUAB));	
    }

    //-----------------------
    // m_GuideHairVertexPositionsSRV
    //-----------------------
    {
        D3D11_SHADER_RESOURCE_VIEW_DESC sbSRVDesc;
        sbSRVDesc.Buffer.FirstElement           = 0;
        sbSRVDesc.Buffer.NumElements            = m_NumGuideHairVertices;
        sbSRVDesc.Format                        = DXGI_FORMAT_UNKNOWN; //DXGI_FORMAT_R32G32B32A32_FLOAT
        sbSRVDesc.ViewDimension                 = D3D11_SRV_DIMENSION_BUFFER;
        SAFE_RELEASE(m_GuideHairVertexPositionsSRV);
        V_RETURN( pd3dDevice->CreateShaderResourceView(m_GuideHairVertexPositionsUAB, &sbSRVDesc, &m_GuideHairVertexPositionsSRV) );
    }

    //-----------------------
    // m_GuideHairVertexTangentsSRV
    //-----------------------
    {
        D3D11_SHADER_RESOURCE_VIEW_DESC sbSRVDesc;
        sbSRVDesc.Buffer.FirstElement           = 0;
        sbSRVDesc.Buffer.NumElements            = m_NumGuideHairVertices;
        sbSRVDesc.Format                        = DXGI_FORMAT_UNKNOWN; //DXGI_FORMAT_R32G32B32A32_FLOAT
        sbSRVDesc.ViewDimension                 = D3D11_SRV_DIMENSION_BUFFER;
        SAFE_RELEASE(m_GuideHairVertexTangentsSRV);
        V_RETURN( pd3dDevice->CreateShaderResourceView(m_GuideHairVertexTangentsUAB, &sbSRVDesc, &m_GuideHairVertexTangentsSRV) );
    }

    //-----------------------
    // m_GuideHairVertexPositionsUAV
    //-----------------------
    {
        D3D11_UNORDERED_ACCESS_VIEW_DESC sbUAVDesc;
        sbUAVDesc.Buffer.FirstElement       = 0;
        sbUAVDesc.Buffer.Flags              = 0;
        sbUAVDesc.Buffer.NumElements        = m_NumGuideHairVertices;
        sbUAVDesc.Format                    = DXGI_FORMAT_UNKNOWN; //DXGI_FORMAT_R32G32B32A32_FLOAT
        sbUAVDesc.ViewDimension             = D3D11_UAV_DIMENSION_BUFFER;
        SAFE_RELEASE(m_GuideHairVertexPositionsUAV);
        SAFE_RELEASE(m_GuideHairVertexPositionsPrevUAV);
        V_RETURN( pd3dDevice->CreateUnorderedAccessView(m_GuideHairVertexPositionsUAB, &sbUAVDesc, &m_GuideHairVertexPositionsUAV) );
        V_RETURN( pd3dDevice->CreateUnorderedAccessView(m_GuideHairVertexPositionsPrevUAB, &sbUAVDesc, &m_GuideHairVertexPositionsPrevUAV) );
    }	

    //------------------------------
    // m_GuideHairVertexTangentsUAV
    //------------------------------
    {
        D3D11_UNORDERED_ACCESS_VIEW_DESC sbUAVDesc;
        sbUAVDesc.Buffer.FirstElement       = 0;
        sbUAVDesc.Buffer.Flags              = 0;
        sbUAVDesc.Buffer.NumElements        = m_NumGuideHairVertices;
        sbUAVDesc.Format                    = DXGI_FORMAT_UNKNOWN; 
        sbUAVDesc.ViewDimension             = D3D11_UAV_DIMENSION_BUFFER;
        SAFE_RELEASE(m_GuideHairVertexTangentsUAV);
        V_RETURN( pd3dDevice->CreateUnorderedAccessView(m_GuideHairVertexTangentsUAB, &sbUAVDesc, &m_GuideHairVertexTangentsUAV) );
    }	

    //---------------------------
    // m_GuideHairRestLengthSRV
    //---------------------------
    {
        float* restLengths = new float[m_NumGuideHairVertices];

		int index = 0;

		for ( int i = 0; i < m_NumGuideHairStrands; i++ )
		{
			float sumOfRestLengthsInOneStrand = 0;

			for ( int j = 0; j < (int)m_HairStrands[i].size()-1; j++ )
			{
				float restLen = vec3Length(m_HairStrands[i][j].position - m_HairStrands[i][j+1].position);

				if ( j > 0 )
					sumOfRestLengthsInOneStrand += restLen;

				restLengths[index] = restLen;
				index++;
			}

			restLengths[index] = sumOfRestLengthsInOneStrand;
			index++;
		}
		
        HRESULT hr;
        D3D11_BUFFER_DESC bufferDesc;
        bufferDesc.ByteWidth = m_NumGuideHairVertices * sizeof(float);
        bufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
        bufferDesc.BindFlags =  D3D11_BIND_SHADER_RESOURCE;
        bufferDesc.CPUAccessFlags = 0;
        bufferDesc.MiscFlags = 0;

        D3D11_SUBRESOURCE_DATA initialData;
        initialData.pSysMem = restLengths;
        
        SAFE_RELEASE(m_GuideHairLengthBuffer);
        V_RETURN(pd3dDevice->CreateBuffer(&bufferDesc, &initialData, &m_GuideHairLengthBuffer));
        delete[] restLengths;

        D3D11_SHADER_RESOURCE_VIEW_DESC desc;
        desc.Format = DXGI_FORMAT_R32_FLOAT;
        desc.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
        desc.Buffer.FirstElement = 0;
        desc.Buffer.NumElements = m_NumGuideHairVertices;
        SAFE_RELEASE(m_GuideHairRestLengthSRV);
        V_RETURN(pd3dDevice->CreateShaderResourceView(m_GuideHairLengthBuffer, &desc, &m_GuideHairRestLengthSRV));
    }
	  
    //-----------------------------------
    // m_GuideHairRefVecsInLocalFrameSRV
    //-----------------------------------
    {
        D3DXVECTOR3* pTempRefVectors = new D3DXVECTOR3[m_NumGuideHairVertices];

        int index = 0;

        for ( int i = 0; i < int(m_HairAssetLoader.GetHairs().size()); i++ )
        {
            for ( int j = 0; j < int(m_HairAssetLoader.GetHairs().at(i)->GetVertexArray().size()); j++ )
            {
                D3DXVECTOR3 v;
                                
                v.x = m_HairAssetLoader.GetHairs().at(i)->GetVertexArray().at(j).m_OrgPosInLocalFrame_i_minus_1.m_X;
                v.y = m_HairAssetLoader.GetHairs().at(i)->GetVertexArray().at(j).m_OrgPosInLocalFrame_i_minus_1.m_Y;
                v.z = m_HairAssetLoader.GetHairs().at(i)->GetVertexArray().at(j).m_OrgPosInLocalFrame_i_minus_1.m_Z;
                

                pTempRefVectors[index++] = v;
            }
        }

        HRESULT hr;
        D3D11_BUFFER_DESC bufferDesc;
        bufferDesc.ByteWidth = m_NumGuideHairVertices * sizeof(D3DXVECTOR3);
        bufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
        bufferDesc.BindFlags =  D3D11_BIND_SHADER_RESOURCE;
        bufferDesc.CPUAccessFlags = 0;
        bufferDesc.MiscFlags = 0;

        D3D11_SUBRESOURCE_DATA initialData;
        initialData.pSysMem = pTempRefVectors;
        
        SAFE_RELEASE(m_GuideHairRefVectorsBuffer);
        V_RETURN(pd3dDevice->CreateBuffer(&bufferDesc, &initialData, &m_GuideHairRefVectorsBuffer));
        delete[] pTempRefVectors;

        D3D11_SHADER_RESOURCE_VIEW_DESC desc;
        desc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
        desc.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
        desc.Buffer.FirstElement = 0;
        desc.Buffer.NumElements = m_NumGuideHairVertices;
        SAFE_RELEASE(m_GuideHairRefVecsInLocalFrameSRV);
        V_RETURN(pd3dDevice->CreateShaderResourceView(m_GuideHairRefVectorsBuffer, &desc, &m_GuideHairRefVecsInLocalFrameSRV));
    }

    // --------------------------------------------
    // m_GlobalRotationsUAB & m_GlobalRotationsUAV
    //---------------------------------------------
    {
        D3DXVECTOR4* pTempGlobalRotations = new D3DXVECTOR4[m_NumGuideHairVertices];

        int index = 0;

        for ( int i = 0; i < int(m_HairAssetLoader.GetHairs().size()); i++ )
        {
            for ( int j = 0; j < int(m_HairAssetLoader.GetHairs().at(i)->GetVertexArray().size()); j++ )
            {
                D3DXVECTOR4 v;
                v.x = m_HairAssetLoader.GetHairs().at(i)->GetVertexArray().at(j).m_GlobalTransform.GetRotation().m_X;
                v.y = m_HairAssetLoader.GetHairs().at(i)->GetVertexArray().at(j).m_GlobalTransform.GetRotation().m_Y;
                v.z = m_HairAssetLoader.GetHairs().at(i)->GetVertexArray().at(j).m_GlobalTransform.GetRotation().m_Z;
                v.w = m_HairAssetLoader.GetHairs().at(i)->GetVertexArray().at(j).m_GlobalTransform.GetRotation().m_W;
            
                pTempGlobalRotations[index++] = v;
            }
        }

        D3D11_SUBRESOURCE_DATA initialData;
        initialData.pSysMem = pTempGlobalRotations;

        D3D11_BUFFER_DESC bufferDescUA;
        bufferDescUA.ByteWidth = m_NumGuideHairVertices * sizeof(D3DXVECTOR4);
        bufferDescUA.Usage = D3D11_USAGE_DEFAULT;
        bufferDescUA.BindFlags =  D3D11_BIND_UNORDERED_ACCESS | D3D11_BIND_SHADER_RESOURCE;
        bufferDescUA.CPUAccessFlags = 0;
        bufferDescUA.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
        bufferDescUA.StructureByteStride  = sizeof(D3DXVECTOR4);
        SAFE_RELEASE(m_GlobalRotationsUAB);
        V_RETURN(pd3dDevice->CreateBuffer(&bufferDescUA, &initialData, &m_GlobalRotationsUAB));

        D3D11_UNORDERED_ACCESS_VIEW_DESC sbUAVDesc;
        sbUAVDesc.Buffer.FirstElement       = 0;
        sbUAVDesc.Buffer.Flags              = 0;
        sbUAVDesc.Buffer.NumElements        = m_NumGuideHairVertices;
        sbUAVDesc.Format                    = DXGI_FORMAT_UNKNOWN; 
        sbUAVDesc.ViewDimension             = D3D11_UAV_DIMENSION_BUFFER;
        SAFE_RELEASE(m_GlobalRotationsUAV);
        V_RETURN( pd3dDevice->CreateUnorderedAccessView(m_GlobalRotationsUAB, &sbUAVDesc, &m_GlobalRotationsUAV) );

        delete [] pTempGlobalRotations;
    }

    // --------------------------------------------
    // m_LocalRotationsUAB & m_LocalRotationsUAV
    //---------------------------------------------
    {
        D3DXVECTOR4* pTempLocalRotations = new D3DXVECTOR4[m_NumGuideHairVertices];

        int index = 0;

        for ( int i = 0; i < int(m_HairAssetLoader.GetHairs().size()); i++ )
        {
            for ( int j = 0; j < int(m_HairAssetLoader.GetHairs().at(i)->GetVertexArray().size()); j++ )
            {
                D3DXVECTOR4 v;
                v.x = m_HairAssetLoader.GetHairs().at(i)->GetVertexArray().at(j).m_LocalTransform.GetRotation().m_X;
                v.y = m_HairAssetLoader.GetHairs().at(i)->GetVertexArray().at(j).m_LocalTransform.GetRotation().m_Y;
                v.z = m_HairAssetLoader.GetHairs().at(i)->GetVertexArray().at(j).m_LocalTransform.GetRotation().m_Z;
                v.w = m_HairAssetLoader.GetHairs().at(i)->GetVertexArray().at(j).m_LocalTransform.GetRotation().m_W;
            
                pTempLocalRotations[index++] = v;
            }
        }

        D3D11_SUBRESOURCE_DATA initialData;
        initialData.pSysMem = pTempLocalRotations;

        D3D11_BUFFER_DESC bufferDescUA;
        bufferDescUA.ByteWidth = m_NumGuideHairVertices * sizeof(D3DXVECTOR4);
        bufferDescUA.Usage = D3D11_USAGE_DEFAULT;
        bufferDescUA.BindFlags =  D3D11_BIND_UNORDERED_ACCESS | D3D11_BIND_SHADER_RESOURCE;
        bufferDescUA.CPUAccessFlags = 0;
        bufferDescUA.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
        bufferDescUA.StructureByteStride  = sizeof(D3DXVECTOR4);
        SAFE_RELEASE(m_LocalRotationsUAB);
        V_RETURN(pd3dDevice->CreateBuffer(&bufferDescUA, &initialData, &m_LocalRotationsUAB));

        D3D11_UNORDERED_ACCESS_VIEW_DESC sbUAVDesc;
        sbUAVDesc.Buffer.FirstElement       = 0;
        sbUAVDesc.Buffer.Flags              = 0;
        sbUAVDesc.Buffer.NumElements        = m_NumGuideHairVertices;
        sbUAVDesc.Format                    = DXGI_FORMAT_UNKNOWN; 
        sbUAVDesc.ViewDimension             = D3D11_UAV_DIMENSION_BUFFER;
        SAFE_RELEASE(m_LocalRotationsUAV);
        V_RETURN( pd3dDevice->CreateUnorderedAccessView(m_LocalRotationsUAB, &sbUAVDesc, &m_LocalRotationsUAV) );

        delete [] pTempLocalRotations;
    }

    return S_OK;
}

void CDX11AMDHairMesh::OnDestroy()
{
    SAFE_RELEASE(m_pIndexBuffer);
    SAFE_RELEASE(m_pIndexBufferSRV);

    SAFE_RELEASE(m_pVertexBuffer);

    SAFE_RELEASE(m_pThicknessCoeffs);
    SAFE_RELEASE(m_pThicknessCoeffsSRV);

    //compute shader variables
    SAFE_RELEASE(m_GuideHairVertexPositionsUAB);
    SAFE_RELEASE(m_GuideHairVertexPositionsPrevUAB);
    SAFE_RELEASE(m_GuideHairVertexPositionsSRV);
    SAFE_RELEASE(m_GuideHairVertexTangentsSRV);
    SAFE_RELEASE(m_GuideHairVertexPositionsUAV);
    SAFE_RELEASE(m_GuideHairVertexTangentsUAV);
    SAFE_RELEASE(m_GuideHairVertexPositionsPrevUAV);
    SAFE_RELEASE(m_CSSkipSimulateHair);
    SAFE_RELEASE(m_CSSimulateHair_A);
    SAFE_RELEASE(m_CSSimulateHair_B);
    SAFE_RELEASE(m_CSSimulateHair_C);
	SAFE_RELEASE(m_CSSimulateHair_D);
    SAFE_RELEASE(m_GuideHairVertexTangentsUAB);
    
    SAFE_RELEASE(m_GuideHairVerticesOffsetsBuffer);
    SAFE_RELEASE(m_GuideHairVerticesOffsetsSRV);

    SAFE_RELEASE(m_GuideHairStrandTypeBuffer);
    SAFE_RELEASE(m_GuideHairStrandTypeSRV);

    SAFE_RELEASE(m_pCBCSPerFrame);

    //vertex buffers
    SAFE_RELEASE(m_GuideHairLengthBuffer);
    SAFE_RELEASE(m_GuideHairRestLengthSRV);

    SAFE_RELEASE(m_InitialGuideHairPositionsSRV);
    SAFE_RELEASE(m_InitialGuideHairPositionsUAV);

    SAFE_RELEASE(m_GuideHairRefVectorsBuffer);
    SAFE_RELEASE(m_GuideHairRefVecsInLocalFrameSRV);

    SAFE_RELEASE(m_GlobalRotationsUAB);
    SAFE_RELEASE(m_GlobalRotationsUAV);

    SAFE_RELEASE(m_LocalRotationsUAB);
    SAFE_RELEASE(m_LocalRotationsUAV);
}
