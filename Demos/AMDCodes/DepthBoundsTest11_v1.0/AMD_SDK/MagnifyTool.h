//--------------------------------------------------------------------------------------
// File: AMD_HUD.h
//
// MagnifyTool class definition. This class implements a user interface based upon the DXUT framework,
// for the Magnify class. 
//
// Author: Jon Story
// 
// Copyright © AMD Corporation. All rights reserved.
//--------------------------------------------------------------------------------------


#ifndef _MAGNIFYTOOL_H_
#define _MAGNIFYTOOL_H_

namespace AMD
{

// GUI defines
enum 
{
	IDC_MAGNIFY_STATIC_CAPTION   =  19 + 1024,
	IDC_MAGNIFY_CHECKBOX_ENABLE,
	IDC_MAGNIFY_CHECKBOX_STICKY,
	IDC_MAGNIFY_STATIC_PIXEL_REGION,
	IDC_MAGNIFY_SLIDER_PIXEL_REGION,
	IDC_MAGNIFY_STATIC_SCALE,
	IDC_MAGNIFY_SLIDER_SCALE
};


class MagnifyTool
{
public:

    // Constructor / destructor
    MagnifyTool();
    ~MagnifyTool();

    // Set methods
    void SetSourceResources( ID3D11Resource* pSourceRTResource, DXGI_FORMAT RTFormat, 
        int nWidth, int nHeight, int nSamples );
    void SetPixelRegion( int nPixelRegion ) { m_Magnify.SetPixelRegion( nPixelRegion ); }
    void SetScale( int nScale ) { m_Magnify.SetScale( nScale ); }
        
    // Hooks for the DX SDK Framework
    void InitApp( CDXUTDialog* pUI, int& iStartHeight, bool bSupportStickyMode = false );
    HRESULT OnCreateDevice( ID3D11Device* pd3dDevice );
    void OnResizedSwapChain( ID3D11Device* pd3dDevice, IDXGISwapChain *pSwapChain, 
        const DXGI_SURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext, 
        int nPositionX, int nPositionY );
    void OnDestroyDevice();
    void OnGUIEvent( UINT nEvent, int nControlID, CDXUTControl* pControl, void* pUserContext );
	
    // Render
    void Render();

private:

    // UI helper methods
    void EnableTool( bool bEnable );
    void EnableUI( bool bEnable );

private:

    // The DXUT dialog
    CDXUTDialog* m_pMagnifyUI;

    // Pointer to the Magnify class
    AMD::Magnify m_Magnify;

    // The source resources
    ID3D11Resource* m_pSourceRTResource;
    DXGI_FORMAT     m_RTFormat;
    int             m_nWidth;
    int             m_nHeight;
    int             m_nSamples;
    bool            m_bReleaseRTOnResize;
	bool			m_bMouseDownLastFrame;
	bool			m_bStickyShowing;
	POINT			m_StickyPoint;
};

} // namespace AMD

#endif // _MAGNIFYTOOL_H_


//--------------------------------------------------------------------------------------
// EOF
//--------------------------------------------------------------------------------------
