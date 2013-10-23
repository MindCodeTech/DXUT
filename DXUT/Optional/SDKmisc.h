//--------------------------------------------------------------------------------------
// File: SDKMisc.h
//
// Various helper functionality that is shared between SDK samples
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//
// http://go.microsoft.com/fwlink/?LinkId=320437
//--------------------------------------------------------------------------------------
#pragma once

#ifdef extern_cplus
extern "C" {
#endif

#ifdef extern_cplusplus
	extern "C++" {
#endif

//-----------------------------------------------------------------------------
// Resource cache for textures, fonts, meshs, and effects.  
// Use DXUTGetGlobalResourceCache() to access the global cache
//-----------------------------------------------------------------------------

namespace DXUT
	{

struct DXUTAPI DXUTCache_Texture
{
    WCHAR   wszSource[MAX_PATH];
    bool    bSRGB;
    ID3D11ShaderResourceView* pSRV11;

    DXUTCache_Texture() :
        pSRV11(nullptr)
    {
    }
};


class DXUTAPI CDXUTResourceCache
{
public:
    ~CDXUTResourceCache();

    HRESULT CreateTextureFromFile( _In_ ID3D11Device* pDevice, _In_ ID3D11DeviceContext *pContext, _In_z_ LPCWSTR pSrcFile,
                                   _Outptr_ ID3D11ShaderResourceView** ppOutputRV, _In_ bool bSRGB=false );
    HRESULT CreateTextureFromFile( _In_ ID3D11Device* pDevice, _In_ ID3D11DeviceContext *pContext, _In_z_ LPCSTR pSrcFile,
                                   _Outptr_ ID3D11ShaderResourceView** ppOutputRV, _In_ bool bSRGB=false );
public:
    HRESULT OnDestroyDevice();

protected:
    friend DXUTAPI CDXUTResourceCache& WINAPI DXUTGetGlobalResourceCache();
    friend DXUTAPI HRESULT WINAPI   DXUTInitialize3DEnvironment();
    friend DXUTAPI HRESULT WINAPI   DXUTReset3DEnvironment();
    friend DXUTAPI void WINAPI      DXUTCleanup3DEnvironment( _In_ bool bReleaseSettings );

    CDXUTResourceCache() { }

    std::vector<DXUTCache_Texture> m_TextureCache;
};
   
DXUTAPI CDXUTResourceCache& WINAPI DXUTGetGlobalResourceCache();


//--------------------------------------------------------------------------------------
// Manages the insertion point when drawing text
//--------------------------------------------------------------------------------------
class CDXUTDialogResourceManager;
class DXUTAPI CDXUTTextHelper
{
public:
    CDXUTTextHelper( _In_ ID3D11Device* pd3d11Device, _In_ ID3D11DeviceContext* pd3dDeviceContext, _In_ CDXUTDialogResourceManager* pManager, _In_ int nLineHeight );
    ~CDXUTTextHelper();

    void Init( _In_ int nLineHeight = 15 );

    void SetInsertionPos( _In_ int x, _In_ int y )
    {
        m_pt.x = x;
        m_pt.y = y;
    }
    void SetForegroundColor( _In_ DirectX::XMFLOAT4 clr ) { m_clr = clr; }
    void SetForegroundColor( _In_ DirectX::FXMVECTOR clr ) { XMStoreFloat4( &m_clr, clr ); }

    void    Begin();
    HRESULT DrawFormattedTextLine( _In_z_ const WCHAR* strMsg, ... );
    HRESULT DrawTextLine( _In_z_ const WCHAR* strMsg );
    HRESULT DrawFormattedTextLine( _In_ const RECT& rc, _In_z_ const WCHAR* strMsg, ... );
    HRESULT DrawTextLine( _In_ const RECT& rc, _In_z_ const WCHAR* strMsg );
    void    End();

protected:
    DirectX::XMFLOAT4 m_clr;
    POINT m_pt;
    int m_nLineHeight;

    // D3D11 font 
    ID3D11Device* m_pd3d11Device;
    ID3D11DeviceContext* m_pd3d11DeviceContext;
    CDXUTDialogResourceManager* m_pManager;
};


//--------------------------------------------------------------------------------------
// Shared code for samples to ask user if they want to use a REF device or quit
//--------------------------------------------------------------------------------------
DXUTAPI void WINAPI DXUTDisplaySwitchingToREFWarning();

//--------------------------------------------------------------------------------------
// Tries to finds a media file by searching in common locations
//--------------------------------------------------------------------------------------
DXUTAPI HRESULT WINAPI DXUTFindDXSDKMediaFileCch( _Out_writes_(cchDest) WCHAR* strDestPath,
                                          _In_ int cchDest, 
                                          _In_z_ LPCWSTR strFilename );
DXUTAPI HRESULT WINAPI DXUTSetMediaSearchPath( _In_z_ LPCWSTR strPath );
DXUTAPI LPCWSTR WINAPI DXUTGetMediaSearchPath();


//--------------------------------------------------------------------------------------
// Compiles HLSL shaders
//--------------------------------------------------------------------------------------
DXUTAPI HRESULT WINAPI DXUTCompileFromFile( _In_z_ LPCWSTR pFileName,
                                    _In_reads_opt_(_Inexpressible_(pDefines->Name != NULL)) const D3D_SHADER_MACRO* pDefines,
                                    _In_z_ LPCSTR pEntrypoint, _In_z_ LPCSTR pTarget,
                                    _In_ UINT Flags1, _In_ UINT Flags2,
                                    _Outptr_ ID3DBlob** ppCode );

//--------------------------------------------------------------------------------------
// Texture utilities
//--------------------------------------------------------------------------------------
DXUTAPI HRESULT WINAPI DXUTCreateShaderResourceViewFromFile( _In_ ID3D11Device* d3dDevice, _In_z_ const wchar_t* szFileName, _Outptr_ ID3D11ShaderResourceView** textureView );
DXUTAPI HRESULT WINAPI DXUTCreateTextureFromFile( _In_ ID3D11Device* d3dDevice, _In_z_ const wchar_t* szFileName, _Outptr_ ID3D11Resource** texture );
DXUTAPI HRESULT WINAPI DXUTSaveTextureToFile( _In_ ID3D11DeviceContext* pContext, _In_ ID3D11Resource* pSource, _In_ bool usedds, _In_z_ const wchar_t* szFileName );

//--------------------------------------------------------------------------------------
// Returns a view matrix for rendering to a face of a cubemap.
//--------------------------------------------------------------------------------------
DXUTAPI DirectX::XMMATRIX WINAPI DXUTGetCubeMapViewMatrix( _In_ DWORD dwFace );

}

#if defined(extern_cplus) && defined(extern_cplusplus)
	}
	}
#elif defined(extern_cplus) && !defined(extern_cplusplus)
}
#elif defined(extern_cplusplus) && !defined(extern_cplus)
}
#endif
