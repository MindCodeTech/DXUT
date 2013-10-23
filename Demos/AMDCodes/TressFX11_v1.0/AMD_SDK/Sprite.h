//--------------------------------------------------------------------------------------
// File: Sprite.h
//
// Sprite class definition. This class provides functionality to render sprites, at a 
// given position and scale. 
// 
// Author: Jon Story
// 
// Copyright © AMD Corporation. All rights reserved.
//--------------------------------------------------------------------------------------


#ifndef _SPRITE_H_
#define _SPRITE_H_

namespace AMD
{

class Sprite
{
public:

    Sprite();
    ~Sprite();

    HRESULT OnCreateDevice( ID3D11Device* pd3dDevice );
    void OnDestroyDevice();
    void OnResizedSwapChain( const DXGI_SURFACE_DESC* pBackBufferSurfaceDesc );

    HRESULT RenderSprite( ID3D11ShaderResourceView* pTextureView, int nStartPosX,
        int nStartPosY, int nWidth, int nHeight, bool bAlpha, bool bBordered );

    HRESULT RenderSpriteMS( ID3D11ShaderResourceView* pTextureView, int nStartPosX,
        int nStartPosY, int nWidth, int nHeight, int nTextureWidth, int nTextureHeight, 
        bool bAlpha, bool bBordered, int nSampleIndex );

    HRESULT RenderSpriteAsDepth( ID3D11ShaderResourceView* pTextureView, int nStartPosX,
        int nStartPosY, int nWidth, int nHeight, bool bBordered, float fDepthRangeMin, 
        float fDepthRangeMax );
	
    HRESULT RenderSpriteAsDepthMS( ID3D11ShaderResourceView* pTextureView, int nStartPosX,
        int nStartPosY, int nWidth, int nHeight, int nTextureWidth, int nTextureHeight, 
        bool bBordered, float fDepthRangeMin, float fDepthRangeMax, int nSampleIndex );

	HRESULT RenderSpriteVolume( ID3D11ShaderResourceView* pTextureView, int nStartPosX, int nStartPosY, int nMaxWidth, int nSliceSize, bool bBordered );

	void SetSpriteColor( D3DXCOLOR Color );
    void SetBorderColor( D3DXCOLOR Color );
    void SetUVs( float fU1, float fV1, float fU2, float fV2 );
	void EnableScissorTest( bool enable ) { m_EnableScissorTest = enable; }
	void SetPointSample( bool pointSample ) { m_PointSampleMode = pointSample; }

private:

	void RenderBorder();
	void Render();

	// VBs
	ID3D11InputLayout*  m_pVertexLayout;
	ID3D11Buffer*       m_pVertexBuffer;
	ID3D11InputLayout*  m_pBorderVertexLayout;
	ID3D11Buffer*       m_pBorderVertexBuffer;

    // CB
    ID3D11Buffer*		m_pcbSprite;

    // Shaders
    ID3D11VertexShader* m_pSpriteVS;
    ID3D11VertexShader* m_pSpriteBorderVS;
    ID3D11PixelShader*  m_pSpritePS;
    ID3D11PixelShader*  m_pSpriteMSPS;
    ID3D11PixelShader*  m_pSpriteAsDepthPS;
    ID3D11PixelShader*  m_pSpriteAsDepthMSPS;
    ID3D11PixelShader*  m_pSpriteBorderPS;
	ID3D11PixelShader*  m_pSpriteUntexturedPS;
	ID3D11PixelShader*	m_pSpriteVolumePS;

    // States
	bool						m_EnableScissorTest;
	bool						m_PointSampleMode;
    ID3D11SamplerState*         m_pSamplePoint;
    ID3D11SamplerState*         m_pSampleLinear;
    ID3D11RasterizerState*      m_pRasterState;
	ID3D11RasterizerState*      m_pRasterStateWithScissor;
    ID3D11RasterizerState*      m_pEnableCulling;
    ID3D11BlendState*           m_pNoBlending;
    ID3D11BlendState*           m_pSrcAlphaBlending;
    ID3D11DepthStencilState*    m_pDisableDepthTestWrite;
    ID3D11DepthStencilState*    m_pEnableDepthTestWrite;
};

}; // namespace AMD

#endif // _SPRITE_H_


//--------------------------------------------------------------------------------------
// EOF
//--------------------------------------------------------------------------------------
