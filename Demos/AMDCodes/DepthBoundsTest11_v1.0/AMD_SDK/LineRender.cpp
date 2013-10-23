//--------------------------------------------------------------------------------------
// File: LineRender.cpp
//
// Helper to render 3d colored lines
//
// Author: Gareth Thomas
//
// Copyright © AMD Corporation. All rights reserved.
//--------------------------------------------------------------------------------------
#include "..\\DXUT\\Core\\DXUT.h"
#include "..\\DXUT\\Optional\\SDKMesh.h"
#include "Geometry.h"
#include "LineRender.h"
#include "HelperFunctions.h"


AMD::LineRender::LineRender() :
	m_pImmediateContext( 0 ),
	m_pInputLayout( 0 ),
	m_pVertexShader( 0 ),
	m_pPixelShader( 0 ),
	m_pConstantBuffer( 0 ),
	m_pVertexBuffer( 0 ),
	m_pCPUCopy( 0 ),
	m_MaxLines( 0 ),
	m_NumLines( 0 )
{
}


AMD::LineRender::~LineRender()
{
	assert( m_pCPUCopy == 0 );
}


void AMD::LineRender::OnCreateDevice( ID3D11Device* pDevice, ID3D11DeviceContext* pImmediateContext, int nMaxLines )
{
	assert( nMaxLines > 0 );
	assert( pDevice && pImmediateContext );

	m_pImmediateContext = pImmediateContext;
	m_MaxLines = nMaxLines;
	m_NumLines = 0;

	// Create shaders
	ID3DBlob* pBlob = 0;

	HRESULT hr = AMD::CompileShaderFromFile( L"..\\AMD_SDK\\Shaders\\Line.hlsl", "LineVS", "vs_4_0", &pBlob, 0 ); 
	assert( hr == S_OK );
	hr = pDevice->CreateVertexShader( pBlob->GetBufferPointer(), pBlob->GetBufferSize(), 0, &m_pVertexShader );
	assert( hr == S_OK );
	
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",		0, DXGI_FORMAT_R8G8B8A8_UNORM, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	hr = pDevice->CreateInputLayout( layout, ARRAYSIZE( layout ), pBlob->GetBufferPointer(), pBlob->GetBufferSize(), &m_pInputLayout );
	assert( hr == S_OK );
	SAFE_RELEASE( pBlob );

	hr = AMD::CompileShaderFromFile( L"..\\AMD_SDK\\Shaders\\Line.hlsl", "LinePS", "ps_4_0", &pBlob, 0 ); 
	assert( hr == S_OK );
	hr = pDevice->CreatePixelShader( pBlob->GetBufferPointer(), pBlob->GetBufferSize(), 0, &m_pPixelShader );
	assert( hr == S_OK );

	// Create vertex buffer
	D3D11_BUFFER_DESC desc;
	ZeroMemory( &desc, sizeof( desc ) );
	desc.ByteWidth = m_MaxLines * 2 * sizeof( Vertex );
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	pDevice->CreateBuffer( &desc, 0, &m_pVertexBuffer );

	// Create constant buffer
	desc.ByteWidth = sizeof( ConstantBuffer );
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	pDevice->CreateBuffer( &desc, 0, &m_pConstantBuffer );

	// Alloc CPU side vertex buffer
	m_pCPUCopy = new Vertex[ m_MaxLines * 2 ];
}


void AMD::LineRender::OnDestroyDevice()
{
	if ( m_pCPUCopy )
	{
		delete[] m_pCPUCopy;
		m_pCPUCopy = 0;
	}

	SAFE_RELEASE( m_pVertexBuffer );
	SAFE_RELEASE( m_pConstantBuffer );
	SAFE_RELEASE( m_pPixelShader );
	SAFE_RELEASE( m_pVertexShader );
	SAFE_RELEASE( m_pInputLayout );

	m_pImmediateContext = 0;
}

	
void AMD::LineRender::AddLine( const D3DXVECTOR3& p0, const D3DXVECTOR3& p1, const D3DCOLOR& color )
{
	if ( m_NumLines < m_MaxLines )
	{
		Vertex* pVerts = &m_pCPUCopy[ m_NumLines * 2 ];

		pVerts[ 0 ].m_Position = p0;
		pVerts[ 1 ].m_Position = p1;

		pVerts[ 0 ].m_Color = color;
		pVerts[ 1 ].m_Color = color;

		m_NumLines++;
	}
}


void AMD::LineRender::AddLines( const D3DXVECTOR3* pPoints, int nNumLines, const D3DCOLOR& color )
{
	if ( m_NumLines + nNumLines <= m_MaxLines )
	{
		Vertex* pVerts = &m_pCPUCopy[ m_NumLines * 2 ];

		for ( int i = 0; i < nNumLines; i++ )
		{
			pVerts[ 0 ].m_Position = pPoints[ 0 ];
			pVerts[ 1 ].m_Position = pPoints[ 1 ];

			pVerts[ 0 ].m_Color = color;
			pVerts[ 1 ].m_Color = color;

			pVerts += 2;
			pPoints += 2;
		}

		m_NumLines += nNumLines;
	}
}


void AMD::LineRender::AddBox( const BoundingBox& box, const D3DCOLOR& color )
{
	D3DXVECTOR3 points[ 24 ];

	D3DXVECTOR3 corners[ 8 ];
	for ( int i = 0; i < 8; i++ )
	{
		corners[ i ] = D3DXVECTOR3( box.GetPoint( i ) );
	}

	const int indices[ 24 ] = 
	{
		0, 1, 1, 3, 3, 2, 2, 0,
		4, 5, 5, 7, 7, 6, 6, 4,
		0, 4, 1, 5, 2, 6, 3, 7
	};

	for ( int i = 0; i < 24; i++ )
	{
		points[ i ] = corners[ indices[ i ] ];
	}

	AddLines( points, 12, color );
}


void AMD::LineRender::Render( const D3DXMATRIX& viewProj )
{
	if ( m_NumLines > 0 )
	{
		// Copy the CPU buffer into the GPU one
		D3D11_MAPPED_SUBRESOURCE res;
		m_pImmediateContext->Map( m_pVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &res );
		memcpy( res.pData, m_pCPUCopy, sizeof( Vertex ) * m_NumLines * 2 );
		m_pImmediateContext->Unmap( m_pVertexBuffer, 0 );

		// Update the constant buffer
		m_pImmediateContext->Map( m_pConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &res );
		ConstantBuffer* constants = (ConstantBuffer*)res.pData;
		D3DXMatrixTranspose( &constants->m_ViewProj, &viewProj );
		m_pImmediateContext->Unmap( m_pConstantBuffer, 0 );

		// Set up states
		m_pImmediateContext->IASetInputLayout( m_pInputLayout );
		m_pImmediateContext->VSSetShader( m_pVertexShader, 0, 0 );
		m_pImmediateContext->HSSetShader( 0, 0, 0 );
		m_pImmediateContext->DSSetShader( 0, 0, 0 );
		m_pImmediateContext->GSSetShader( 0, 0, 0 );
		m_pImmediateContext->PSSetShader( m_pPixelShader, 0, 0 );
		m_pImmediateContext->VSSetConstantBuffers( 0, 1, &m_pConstantBuffer );

		UINT stride = sizeof( Vertex );
		UINT offset = 0;
		m_pImmediateContext->IASetVertexBuffers( 0, 1, &m_pVertexBuffer, &stride, &offset );
		m_pImmediateContext->IASetPrimitiveTopology( D3D_PRIMITIVE_TOPOLOGY_LINELIST );
		
		// Draw
		m_pImmediateContext->Draw( m_NumLines * 2, 0 );

		// Reset the number of lines
		m_NumLines = 0;
	}
}