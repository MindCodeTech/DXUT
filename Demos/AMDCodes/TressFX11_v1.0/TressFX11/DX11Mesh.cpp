//--------------------------------------------------------------------------------------
// File: DX11Mesh.cpp
//
// Mesh model loading 
// 
// Copyright © AMD Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#include "..\\DXUT\\Core\\dxut.h"
#include "DX11Mesh.h"
#include "objimport.h"
#include "..\\DXUT\\Optional\\SDKmisc.h"
#include "..\\DXUT\\Optional\\sdkmesh.h"

CDX11Mesh::CDX11Mesh(void)
{
	this->m_pIndexBuffer = NULL;
	this->m_pVertexBuffer = NULL;
}

CDX11Mesh::~CDX11Mesh(void)
{
}

void CDX11Mesh::CreateMeshFromOBJFile(ID3D11Device* pd3dDevice, const WCHAR* strFilename, 
									  D3DXVECTOR3 scale, D3DXVECTOR3 rotation, D3DXVECTOR3 translation)
{
	this->OnDestroy();

	COBJImport objImport;
	objImport.LoadModelFromOBJ(strFilename);
	objImport.ScaleRotateTranslate(scale, rotation, translation);

	// sort triangles according to material and setup all subsets
	objImport.BuildMesh();
	// get bounding sphere information
	this->m_bSphere.center = objImport.m_bSphere.center;
	this->m_bSphere.radius = objImport.m_bSphere.radius;

	///////////////////////////////////////////////////////////////////////////////////////////
	// copy the subsets and material from objImport
	for(UINT i=0; i<objImport.m_Subsets.size(); i++)
		this->m_Subsets.push_back(objImport.m_Subsets[i]);

	for(UINT i=0; i<objImport.m_Materials.size(); i++)
		this->m_Materials.push_back(objImport.m_Materials[i]);

	HRESULT hr;
	/////////////////////////////////////////////////////////////////////////////////////////////
	// Create vertex buffer from objImport
	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(bufferDesc));
	bufferDesc.BindFlags        = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.ByteWidth        = sizeof( StandardVertex ) * objImport.m_VertexBuffer.size();
	bufferDesc.Usage            = D3D11_USAGE_DEFAULT;
	bufferDesc.CPUAccessFlags   = 0;
	bufferDesc.MiscFlags        = 0;

	// Fill in the subresource data.
	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = &(objImport.m_VertexBuffer[0]);
	InitData.SysMemPitch = 0;
	InitData.SysMemSlicePitch = 0;

	// Create the vertex buffer.
	hr = pd3dDevice->CreateBuffer( &bufferDesc, &InitData, &(this->m_pVertexBuffer) );
	if( FAILED( hr ) )
		::MessageBoxA(0,"fail to create vb for obj", "d3dError", 0);

	// Create indices.
	// Fill in a buffer description.
	bufferDesc.Usage           = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth       = sizeof( unsigned int ) * objImport.m_IndexBuffer.size();
	bufferDesc.BindFlags       = D3D11_BIND_INDEX_BUFFER;
	bufferDesc.CPUAccessFlags  = 0;
	bufferDesc.MiscFlags       = 0;

	// Define the resource data.
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = &(objImport.m_IndexBuffer[0]);
	InitData.SysMemPitch = 0;
	InitData.SysMemSlicePitch = 0;

	// Create the buffer with the device.
	hr = pd3dDevice->CreateBuffer( &bufferDesc, &InitData, &(this->m_pIndexBuffer) );
	if( FAILED( hr ) )
		::MessageBoxA(0,"fail to create vb for obj", "d3dError", 0);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	// set directory for loading textures
    WCHAR wstrOldDir[MAX_PATH] = {0};
    GetCurrentDirectory( MAX_PATH, wstrOldDir );
    SetCurrentDirectory( objImport.m_strMediaDir );
	
	// load textures required in .mtl file
	for ( UINT iMaterial = 0; iMaterial < m_Materials.size(); ++iMaterial )
    {
        Material *pMaterial = &m_Materials[ iMaterial ];

		if ( pMaterial->strTexture[0] )
        {    
			// Avoid loading the same texture twice
			bool bFound = false;

			// loop through previous materials to see if texture is already loaded.
            for( int x = 0; x < (int)iMaterial; x++ )
            {
                Material* pCur = &m_Materials[x];
				if( 0 == wcscmp( pCur->strTexture, pMaterial->strTexture ) )
                {
					pMaterial->pTextureRV11 = pCur->pTextureRV11;
					bFound = true;
					break;
				}
			}

			// Not found, load the texture
			if(!bFound)
			{
				WCHAR wstr[ MAX_PATH ] = {0};
				if ( SUCCEEDED(DXUTFindDXSDKMediaFileCch( wstr, MAX_PATH, pMaterial->strTexture) ) )
				{
					D3DX11_IMAGE_INFO srcInfo;
					D3DX11GetImageInfoFromFile(wstr, NULL, &srcInfo, NULL);

					D3DX11_IMAGE_LOAD_INFO loadInfo;
					loadInfo.BindFlags = D3D11_BIND_SHADER_RESOURCE ;
					loadInfo.CpuAccessFlags = 0;
					loadInfo.MiscFlags = 0;
					loadInfo.FirstMipLevel = 0;
					loadInfo.MipLevels = srcInfo.MipLevels;
					loadInfo.pSrcInfo = &srcInfo;
					loadInfo.Format = srcInfo.Format;
					loadInfo.Width = srcInfo.Width;
					loadInfo.Height = srcInfo.Height;
					loadInfo.Depth = srcInfo.Depth;
					loadInfo.Filter = D3DX11_FILTER_NONE  ;               

					hr = D3DX11CreateShaderResourceViewFromFile( pd3dDevice, wstr, &loadInfo, NULL, &pMaterial->pTextureRV11, NULL );
					m_TextureSRVs.push_back(pMaterial->pTextureRV11);
					if(FAILED(hr)) ::MessageBoxW(0, L"fail to load material texture", L"D3D11 Error", 0);

				}
			}
        }
    }

    // Restore the original current directory
    SetCurrentDirectory( wstrOldDir );
}
////////////////////////////////////////////////////////////////////
// Draw all subsets of the mesh
// Including:
// - Setting vertex buffer
// - Setting index buffer
// - Set primitive Topology : triangleList
// Not including:
// - Set viewport
// - Set Shader
// - Set input layout (as it require shader signiture)
void CDX11Mesh::OnFrameRender(ID3D11DeviceContext* pd3dContext)
{
	UINT strides = sizeof( StandardVertex );
	UINT offsets = 0;
	pd3dContext->IASetVertexBuffers( 0, 1, &m_pVertexBuffer, &strides, &offsets );
    pd3dContext->IASetIndexBuffer( m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0 );
	pd3dContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
	
	// loop through all subsets
	int numSubsets = m_Subsets.size();		
	for(int i=0; i<numSubsets; i++)
	{
		int indexCount = m_Subsets[i].triangleCount*3;
		int startLocation = m_Subsets[i].startIndex;
		pd3dContext->DrawIndexed( indexCount, startLocation, 0 );
	}
}

void CDX11Mesh::OnDestroy()
{
	SAFE_RELEASE(m_pVertexBuffer);
	SAFE_RELEASE(m_pIndexBuffer);

	////////////////////////////////////////////////////////////////////////////
	for(UINT i=0; i<m_TextureSRVs.size(); i++)
	{
        ID3D11Resource* pRes = NULL;
        if(m_TextureSRVs[i])
		{
			m_TextureSRVs[i]->GetResource( &pRes );
			SAFE_RELEASE( pRes );
			SAFE_RELEASE( pRes );   // do this twice, because GetResource adds a ref

			SAFE_RELEASE( m_TextureSRVs[i] );
		}
	}

	std::vector<Subset>().swap(m_Subsets);			// all the sub meshes, each with different material property
	std::vector<Material>().swap(m_Materials);
	std::vector<ID3D11ShaderResourceView*>().swap( m_TextureSRVs);

	m_bSphere.center = D3DXVECTOR3(0,0,0);
	m_bSphere.radius = 0;
}
