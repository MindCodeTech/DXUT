//--------------------------------------------------------------------------------------
// File: HUD.h
//
// Class definition for the AMD standard HUD interface.
//
// Author: Jon Story
// 
// Copyright © AMD Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#pragma once

namespace AMD
{

class HUD
{
public:

    // AMD standard HUD defines for GUI spacing
    static const int iElementDelta = 25;
    static const int iGroupDelta = ( iElementDelta * 2 );
    static const int iDialogWidth = 250;
    static const int iElementHeight = 24;
    static const int iElementWidth = 170;
    static const int iElementOffset = ( iDialogWidth - iElementWidth ) / 2;
    static const int iElementDropHeight = 35;

    // Public access to the CDXUTDialog is allowed for ease of use in the sample
    CDXUTDialog m_GUI;

    // Constructor / destructor
    HUD();
    ~HUD();

    // Various hook functions
    HRESULT OnCreateDevice( ID3D11Device* pd3dDevice );
    void OnDestroyDevice();
    void OnResizedSwapChain( const DXGI_SURFACE_DESC* pBackBufferSurfaceDesc );
    void OnRender( float fElapsedTime );

private:

    // The private AMD logo texture, and sprite object
    Sprite                      m_Sprite;
    ID3D11ShaderResourceView*   m_pLogoSRV;
};


class Slider : public CDXUTControl
{
public:

	Slider( CDXUTDialog& dialog, int id, int& y, const wchar_t* label, int min, int max, int& value );
	virtual ~Slider() {}

	void OnGuiEvent();
	void SetEnabled( bool enable );
	void SetVisible( bool visible );
	void SetValue( int value );

private:

	Slider& operator=( const Slider& );

	int&			m_Value;
	const wchar_t*	m_szLabel;
	CDXUTSlider*	m_pSlider;
	CDXUTStatic*	m_pLabel;
};



} // namespace AMD

//--------------------------------------------------------------------------------------
// EOF
//--------------------------------------------------------------------------------------
