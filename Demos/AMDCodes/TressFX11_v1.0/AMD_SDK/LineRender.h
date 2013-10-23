//--------------------------------------------------------------------------------------
// File: LineRender.h
//
// Helper to render 3d colored lines
//
// Author: Gareth Thomas
//
// Copyright © AMD Corporation. All rights reserved.
//--------------------------------------------------------------------------------------
#ifndef __AMD_LINE_RENDER_H__
#define __AMD_LINE_RENDER_H__



namespace AMD
{

class LineRender
{
public:

	LineRender();
	~LineRender();

	void OnCreateDevice( ID3D11Device* pDevice, ID3D11DeviceContext* pImmediateContext, int nMaxLines );
	void OnDestroyDevice();
	
	void AddLine( const D3DXVECTOR3& p0, const D3DXVECTOR3& p1, const D3DCOLOR& color );
	void AddLines( const D3DXVECTOR3* pPoints, int nNumLines, const D3DCOLOR& color );
	void AddBox( const BoundingBox& box, const D3DCOLOR& color );

	void Render( const D3DXMATRIX& viewProj );

private:

	struct Vertex
	{
		D3DXVECTOR3		m_Position;
		DWORD			m_Color;
	};

	struct ConstantBuffer
	{
		D3DXMATRIX		m_ViewProj;
	};

	ID3D11DeviceContext*		m_pImmediateContext;
	ID3D11InputLayout*			m_pInputLayout;
	ID3D11VertexShader*			m_pVertexShader;
	ID3D11PixelShader*			m_pPixelShader;
	ID3D11Buffer*				m_pConstantBuffer;
	ID3D11Buffer*				m_pVertexBuffer;
	Vertex*						m_pCPUCopy;
	int							m_MaxLines;
	int							m_NumLines;
};

}

#endif

