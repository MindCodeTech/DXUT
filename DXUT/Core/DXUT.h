//--------------------------------------------------------------------------------------
// File: DXUT.h
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

#ifndef UNICODE
#error "DXUT requires a Unicode build."
#endif

// Exclude rarely-used stuff from Windows headers
#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN
#endif
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif
#ifndef STRICT
#define STRICT
#endif

#ifndef _INC_SDKDDKVER
#include <sdkddkver.h>
#endif

// If app hasn't choosen, set to work with Windows 8 and beyond
#ifndef WINVER
#define WINVER         0x0602
#endif
#ifndef _WIN32_WINDOWS
#define _WIN32_WINDOWS 0x0602
#endif
#if _WIN32_WINNT < 0x0602
#define _WIN32_WINNT   0x0602
#endif

#if (_WIN32_WINNT >= _WIN32_WINNT_WIN8) && !defined(DXGI_1_2_FORMATS)
#define DXGI_1_2_FORMATS
#endif

#include "DXUTexp.h"

#if defined(_MSC_VER) && defined(DXUTLIB_EXPORT) || defined(_LIB) || defined(DXUTLIB_IMPORT) || defined(_DLL)
#define DXUT_AUTOLIB 1
#endif


// #define DXUT_AUTOLIB to automatically include the libs needed for DXUT
#ifdef DXUT_AUTOLIB
#pragma comment( lib, "d3d11.lib" )
// #pragma comment( lib, "d3d10_1.lib" )
// #pragma comment( lib, "d3d10.lib" )
#pragma comment( lib, "ComCtl32.lib" )
#pragma comment( lib, "dxgi.lib" )
#pragma comment( lib, "dxguid.lib" )
#pragma comment( lib, "d3dcompiler.lib" )
// #pragma comment( lib, "ole32.lib" ) // included with additional include directories 
// #pragma comment( lib, "uuid.lib" ) // included with additional include directories 
#pragma comment( lib, "usp10.lib" )
#pragma comment( lib, "ddraw.lib" )
#pragma comment( lib, "d2d1.lib" )
#pragma comment( lib, "dwrite.lib" )
#pragma comment( lib, "dsound.lib" )
#ifdef _DEBUG
#pragma comment( lib, "d3dcsxd.lib" )
#else
#pragma comment( lib, "d3dcsx.lib" )
#endif
#pragma comment( lib, "WinMM.Lib" )
#pragma comment( lib, "Imm32.Lib" )
#pragma comment( lib, "Version.Lib" )
#pragma comment( lib, "xapobase.Lib" )
#pragma comment( lib, "xaudio2.Lib" )
#pragma comment( lib, "Xinput.Lib" )

#endif

#ifdef DXUTLIB_IMPORT
#ifdef DXUTLIB_DLL
#ifdef _DEBUG
#pragma comment( lib, "DXUT_d.lib" )
#else
#pragma comment( lib, "DXUT.lib" )
#endif
#elif DXUTLIB_STATIC
#ifdef _DEBUG
#pragma comment( lib, "DXUTs_d.lib" )
#else
#pragma comment( lib, "DXUTs.lib" )
#endif
#else
#pragma warning ("DXUTLIB_IMPORT import librarys aren't defined")
#endif
#endif


#pragma warning(disable : 4067 4102 4127 4201 4251 4324 4481 4505 4616 4706 6326 6993 )

#pragma warning(push)
#pragma warning(disable : 4005)

#pragma pack(push)
#pragma pack(8)

// #ifdef DEFINE_GUID
// #undef DEFINE_GUID
// #endif

// Standard Windows includes
#include <windows.h>
#include <ocidl.h>
#include <initguid.h>
#include <commctrl.h> // for InitCommonControls()
#include <commdlg.h>
#include <shellapi.h> // for ExtractIcon()
#include <shlobj.h>
#include <usp10.h>
#include <dimm.h>
#include <sal.h>
#include <strsafe.h>
#include <msctf.h>
#include <mmsystem.h>
#include <dsound.h>
#include <ks.h>
#include <ole2.h>


// Direct3D11 includes
//#include <d3dcommon.h>
#include <dxgi1_3.h>
#include <d3d11_2.h>
#include <d3d11shader.h>
//#include <d3d10_1.h>
#include <d3dcompiler.h>
#include <d2d1_2.h>
#include <d3dcsx.h>

#if defined(DEBUG) || defined(_DEBUG)
#include <dxgidebug.h>
#endif

// DirectXMath includes
#include <DirectXMath.h>
#include <DirectXColors.h>
#include <directxpackedvector.h>
#include <DirectXCollision.h>

// WIC includes
#if !defined(WINAPI_FAMILY) || (WINAPI_FAMILY != WINAPI_FAMILY_PHONE_APP)
#include <wincodec.h>
#endif


// XAudio includes
#include <xapo.h>
#include <xapobase.h>
#include <xapofx.h>
#include <xaudio2.h>
#include <xaudio2fx.h>
#include <x3daudio.h>

// XInput includes
#include <xinput.h>

#include <ddraw.h>
#include <dwrite.h>
#include <dxtmpl.h>

#pragma pack (pop)

// STL includes
#include <assert.h>
#include <wchar.h>
#include <new.h>      // for placement new
#include <math.h>
#include <malloc.h>
#include <limits.h>
#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <intsafe.h>
#include <string>
#include <algorithm>
#include <array>
#include <memory.h>
#include <memory>
#include <map>
#include <float.h>
#include <cmath>
#include <vector>
#include <functional>
#include <set>
#include <search.h>
#include <exception>
#include <type_traits>
#ifdef _OPENMP
#include <omp.h>
#endif

// CRT's memory leak detection
#if defined(DEBUG) || defined(_DEBUG)
#include <crtdbg.h>
#endif

#pragma warning(pop)

// Enable extra D3D debugging in debug builds if using the debug DirectX runtime.
// This makes D3D objects work well in the debugger watch window, but slows down
// performance slightly.
#if defined(DEBUG) | defined(_DEBUG)
#define D3D_DEBUG_INFO
#endif

// HRESULT translation for Direct3D and other APIs
#include "dxerr.h"

#undef min // use __min instead
#undef max // use __max instead

#ifndef UNUSED (-1)
#define UNUSED (-1)
#endif

#ifdef extern_cplus
extern "C" {
#endif

#ifdef extern_cplusplus
extern "C++" {
#endif

// namespace DirectX
// {
// #if (DIRECTXMATH_VERSION < 305) && !defined(XM_CALLCONV)
// #define XM_CALLCONV __fastcall
// 			typedef const XMVECTOR& HXMVECTOR;
// 			typedef const XMMATRIX& FXMMATRIX;
// #endif
// 		}

#if defined(DEBUG) || defined(_DEBUG)
#ifndef V
#define V(x)           { hr = (x); if( FAILED(hr) ) { DXUTTrace( __FILE__, (DWORD)__LINE__, hr, L#x, true ); } }
#endif
#ifndef V_RETURN
#define V_RETURN(x)    { hr = (x); if( FAILED(hr) ) { return DXUTTrace( __FILE__, (DWORD)__LINE__, hr, L#x, true ); } }
#endif
#else
#ifndef V
#define V(x)           { hr = (x); }
#endif
#ifndef V_RETURN
#define V_RETURN(x)    { hr = (x); if( FAILED(hr) ) { return hr; } }
#endif
#endif

#ifndef SAFE_DELETE
#define SAFE_DELETE(p)       { if (p) { delete (p);     (p) = nullptr; } }
#endif
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p) { if (p) { delete[] (p);   (p) = nullptr; } }
#endif
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p)      { if (p) { (p)->Release(); (p) = nullptr; } }
#endif

#ifndef SAFE_ADDREF
#define SAFE_ADDREF(p)        { if (p) { (p)->AddRef(); } }
#endif

#ifndef D3DCOLOR_ARGB
#define D3DCOLOR_ARGB(a,r,g,b) \
	((DWORD)((((a)&0xff)<<24)|(((r)&0xff)<<16)|(((g)&0xff)<<8)|((b)&0xff)))
#endif

#define DXUT_VERSION 1104

		//--------------------------------------------------------------------------------------
		// SAL2 fixups for VS 2010
		//--------------------------------------------------------------------------------------

		/*
		#if defined(_MSC_VER) && (_MSC_VER<1610) && !defined(_In_reads_)
		#define _Analysis_assume_(exp)
		#define _In_reads_(exp)
		#define _In_reads_opt_(exp)
		#define _Out_writes_(exp)
		#define _Out_writes_opt_(exp)
		#define _In_reads_bytes_(exp)
		#define _Out_writes_bytes_(exp)
		#define _Out_writes_bytes_to_opt_(a,b)
		#define _Inout_updates_bytes_(exp)
		#define _Inout_updates_all_(exp)
		#define _Inout_updates_all_opt_(exp)
		#define _COM_Outptr_
		#define _Outptr_
		#define _Outptr_opt_
		#define _Outptr_result_z_
		#define _Outptr_opt_result_maybenull_
		#define _When_(a,b)
		#define _Acquires_lock_(exp)
		#define _Releases_lock_(exp)
		#define _Inexpressible_(exp)
		#endif*/

#if defined(_MSC_VER) && (_MSC_VER<1610) && !defined(_In_reads_)
#define _Analysis_assume_(exp) __analysis_assume(exp)
#define _In_reads_(exp) _In_count_x_(exp)
#define _In_reads_opt_(exp) _In_opt_count_x_(exp)
#define _In_reads_bytes_(exp) _In_bytecount_x_(exp)
#define _Inout_updates_(exp) _Inout_cap_x_(exp)
#define _Inout_updates_z_(exp) _Inout_z_cap_x_(exp)
#define _Inout_updates_bytes_(exp) _Inout_bytecap_x_(exp)
#define _Inout_updates_all_(exp) _Inout_z_cap_x_(exp)
#define _Inout_updates_all_opt_(exp) _Inout_opt_z_cap_x_(exp)
#define _Out_writes_(exp) _Out_cap_x_(exp)
#define _Out_writes_opt_(exp) _Out_opt_cap_x_(exp)
#define _Out_writes_bytes_(exp) _Out_bytecap_x_(exp)
#define _Out_writes_bytes_to_opt_(a,b) _Out_opt_bytecap_x_(a,b)
#define _Outptr_ _Deref_out_
#define _Outptr_opt_ _Deref_out_opt_
#define _Outptr_result_z_ _Deref_out_z_
#define _Outptr_opt_result_maybenull_ _Deref_opt_out_opt_
#define _Outptr_result_maybenull_z_ _Deref_opt_out_opt_z_
#define _Outptr_result_buffer_(exp) _Deref_post_cap_x_(exp)
#define _Outptr_result_buffer_all_maybenull_(exp) _Deref_post_opt_cap_x_(exp)
#define _COM_Outptr_ _Deref_out_
#define _When_(test,exp)
#define _Acquires_lock_(exp)
#define _Releases_lock_(exp)
#define _Inexpressible_(exp)
#endif

#ifndef _Use_decl_annotations_
#define _Use_decl_annotations_
#endif

#ifndef offsetof_fx
#define offsetof_fx( a, b ) (uint32_t)offsetof( a, b )
#endif

namespace DXUT
{

		//--------------------------------------------------------------------------------------
		// Structs
		//--------------------------------------------------------------------------------------
		struct DXUTAPI DXUTD3D11DeviceSettings
		{
			UINT AdapterOrdinal;
			D3D_DRIVER_TYPE DriverType;
			UINT Output;
			DXGI_SWAP_CHAIN_DESC sd;
			UINT32 CreateFlags;
			UINT32 SyncInterval;
			DWORD PresentFlags;
			bool AutoCreateDepthStencil; // DXUT will create the depth stencil resource and view if true
			DXGI_FORMAT AutoDepthStencilFormat;
			D3D_FEATURE_LEVEL DeviceFeatureLevel;
		};

		struct DXUTAPI DXUTDeviceSettings
		{
			D3D_FEATURE_LEVEL MinimumFeatureLevel;
			DXUTD3D11DeviceSettings d3d11;
		};

		//--------------------------------------------------------------------------------------
		// Error codes
		//--------------------------------------------------------------------------------------
#define DXUTERR_NODIRECT3D              MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x0901)
#define DXUTERR_NOCOMPATIBLEDEVICES     MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x0902)
#define DXUTERR_MEDIANOTFOUND           MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x0903)
#define DXUTERR_NONZEROREFCOUNT         MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x0904)
#define DXUTERR_CREATINGDEVICE          MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x0905)
#define DXUTERR_RESETTINGDEVICE         MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x0906)
#define DXUTERR_CREATINGDEVICEOBJECTS   MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x0907)
#define DXUTERR_RESETTINGDEVICEOBJECTS  MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x0908)
#define DXUTERR_DEVICEREMOVED           MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x090A)

		//--------------------------------------------------------------------------------------
		// Callback registration
		//--------------------------------------------------------------------------------------

		// General callbacks
		typedef void    (CALLBACK *LPDXUTCALLBACKFRAMEMOVE)( _In_ double fTime, _In_ float fElapsedTime, _In_opt_ void* pUserContext );
		typedef void    (CALLBACK *LPDXUTCALLBACKKEYBOARD)( _In_ UINT nChar, _In_ bool bKeyDown, _In_ bool bAltDown, _In_opt_ void* pUserContext );
		typedef void    (CALLBACK *LPDXUTCALLBACKMOUSE)( _In_ bool bLeftButtonDown, _In_ bool bRightButtonDown, _In_ bool bMiddleButtonDown,
			_In_ bool bSideButton1Down, _In_ bool bSideButton2Down, _In_ int nMouseWheelDelta,
			_In_ int xPos, _In_ int yPos, _In_opt_ void* pUserContext );
		typedef LRESULT (CALLBACK *LPDXUTCALLBACKMSGPROC)( _In_ HWND hWnd, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam,
			_Out_ bool* pbNoFurtherProcessing, _In_opt_ void* pUserContext );
		typedef void    (CALLBACK *LPDXUTCALLBACKTIMER)( _In_ UINT idEvent, _In_opt_ void* pUserContext );
		typedef bool    (CALLBACK *LPDXUTCALLBACKMODIFYDEVICESETTINGS)( _In_ DXUTDeviceSettings* pDeviceSettings, _In_opt_ void* pUserContext );
		typedef bool    (CALLBACK *LPDXUTCALLBACKDEVICEREMOVED)( _In_opt_ void* pUserContext );

		class CD3D11EnumAdapterInfo;
		class CD3D11EnumDeviceInfo;

		// Direct3D 11 callbacks
		typedef bool    (CALLBACK *LPDXUTCALLBACKISD3D11DEVICEACCEPTABLE)( _In_ const CD3D11EnumAdapterInfo *AdapterInfo, _In_ UINT Output, _In_ const CD3D11EnumDeviceInfo *DeviceInfo,
			_In_ DXGI_FORMAT BackBufferFormat, _In_ bool bWindowed, _In_opt_ void* pUserContext );
		typedef HRESULT (CALLBACK *LPDXUTCALLBACKD3D11DEVICECREATED)( _In_ ID3D11Device* pd3dDevice, _In_ const DXGI_SURFACE_DESC* pBackBufferSurfaceDesc, _In_opt_ void* pUserContext );
		typedef HRESULT (CALLBACK *LPDXUTCALLBACKD3D11SWAPCHAINRESIZED)( _In_ ID3D11Device* pd3dDevice, _In_ IDXGISwapChain *pSwapChain, _In_ const DXGI_SURFACE_DESC* pBackBufferSurfaceDesc, _In_opt_ void* pUserContext );
		typedef void    (CALLBACK *LPDXUTCALLBACKD3D11FRAMERENDER)( _In_ ID3D11Device* pd3dDevice, _In_ ID3D11DeviceContext* pd3dImmediateContext, _In_ double fTime, _In_ float fElapsedTime, _In_opt_ void* pUserContext );
		typedef void    (CALLBACK *LPDXUTCALLBACKD3D11SWAPCHAINRELEASING)( _In_opt_ void* pUserContext );
		typedef void    (CALLBACK *LPDXUTCALLBACKD3D11DEVICEDESTROYED)( _In_opt_ void* pUserContext );

		// General callbacks
		DXUTAPI void WINAPI DXUTSetCallbackFrameMove( _In_ LPDXUTCALLBACKFRAMEMOVE pCallback, _In_opt_ void* pUserContext = nullptr );
		DXUTAPI void WINAPI DXUTSetCallbackKeyboard( _In_ LPDXUTCALLBACKKEYBOARD pCallback, _In_opt_ void* pUserContext = nullptr );
		DXUTAPI void WINAPI DXUTSetCallbackMouse( _In_ LPDXUTCALLBACKMOUSE pCallback, bool bIncludeMouseMove = false, _In_opt_ void* pUserContext = nullptr );
		DXUTAPI void WINAPI DXUTSetCallbackMsgProc( _In_ LPDXUTCALLBACKMSGPROC pCallback, _In_opt_ void* pUserContext = nullptr );
		DXUTAPI void WINAPI DXUTSetCallbackDeviceChanging( _In_ LPDXUTCALLBACKMODIFYDEVICESETTINGS pCallback, _In_opt_ void* pUserContext = nullptr );
		DXUTAPI void WINAPI DXUTSetCallbackDeviceRemoved( _In_ LPDXUTCALLBACKDEVICEREMOVED pCallback, _In_opt_ void* pUserContext = nullptr );

		// Direct3D 11 callbacks
		DXUTAPI void WINAPI DXUTSetCallbackD3D11DeviceAcceptable( _In_ LPDXUTCALLBACKISD3D11DEVICEACCEPTABLE pCallback, _In_opt_ void* pUserContext = nullptr );
		DXUTAPI void WINAPI DXUTSetCallbackD3D11DeviceCreated( _In_ LPDXUTCALLBACKD3D11DEVICECREATED pCallback, _In_opt_ void* pUserContext = nullptr );
		DXUTAPI void WINAPI DXUTSetCallbackD3D11SwapChainResized( _In_ LPDXUTCALLBACKD3D11SWAPCHAINRESIZED pCallback, _In_opt_ void* pUserContext = nullptr );
		DXUTAPI void WINAPI DXUTSetCallbackD3D11FrameRender( _In_ LPDXUTCALLBACKD3D11FRAMERENDER pCallback, _In_opt_ void* pUserContext = nullptr );
		DXUTAPI void WINAPI DXUTSetCallbackD3D11SwapChainReleasing( _In_ LPDXUTCALLBACKD3D11SWAPCHAINRELEASING pCallback, _In_opt_ void* pUserContext = nullptr );
		DXUTAPI void WINAPI DXUTSetCallbackD3D11DeviceDestroyed( _In_ LPDXUTCALLBACKD3D11DEVICEDESTROYED pCallback, _In_opt_ void* pUserContext = nullptr );

		//--------------------------------------------------------------------------------------
		// Initialization
		//--------------------------------------------------------------------------------------
		DXUTAPI HRESULT WINAPI DXUTInit( _In_ bool bParseCommandLine = true,
			_In_ bool bShowMsgBoxOnError = true,
			_In_opt_ WCHAR* strExtraCommandLineParams = nullptr,
			_In_ bool bThreadSafeDXUT = false );

		// Choose either DXUTCreateWindow or DXUTSetWindow.  If using DXUTSetWindow, consider using DXUTStaticWndProc
		DXUTAPI HRESULT WINAPI DXUTCreateWindow( _In_z_ const WCHAR* strWindowTitle = L"Direct3D Window",
			_In_opt_ HINSTANCE hInstance = nullptr, _In_opt_ HICON hIcon = nullptr, _In_opt_ HMENU hMenu = nullptr,
			_In_ int x = CW_USEDEFAULT, _In_ int y = CW_USEDEFAULT );
		DXUTAPI HRESULT WINAPI DXUTSetWindow( _In_ HWND hWndFocus, _In_ HWND hWndDeviceFullScreen, _In_ HWND hWndDeviceWindowed, _In_ bool bHandleMessages = true );
		DXUTAPI LRESULT CALLBACK DXUTStaticWndProc( _In_ HWND hWnd, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam );

		// Choose either DXUTCreateDevice or DXUTSetD3D*Device or DXUTCreateD3DDeviceFromSettings

		DXUTAPI HRESULT WINAPI DXUTCreateDevice(_In_ D3D_FEATURE_LEVEL reqFL, _In_ bool bWindowed= true, _In_ int nSuggestedWidth =0,_In_  int nSuggestedHeight =0 );
		DXUTAPI HRESULT WINAPI DXUTCreateDeviceFromSettings( _In_ DXUTDeviceSettings* pDeviceSettings, _In_ bool bClipWindowToSingleAdapter = true );
		DXUTAPI HRESULT WINAPI DXUTSetD3D11Device( _In_ ID3D11Device* pd3dDevice, _In_ IDXGISwapChain* pSwapChain );

		// Choose either DXUTMainLoop or implement your own main loop
		DXUTAPI HRESULT WINAPI DXUTMainLoop( _In_opt_ HACCEL hAccel = nullptr );

		// If not using DXUTMainLoop consider using DXUTRender3DEnvironment
		DXUTAPI void WINAPI DXUTRender3DEnvironment();

		//--------------------------------------------------------------------------------------
		// Common Tasks
		//--------------------------------------------------------------------------------------
		DXUTAPI HRESULT WINAPI DXUTToggleFullScreen();
		DXUTAPI HRESULT WINAPI DXUTToggleREF();
		DXUTAPI HRESULT WINAPI DXUTToggleWARP();
		DXUTAPI void    WINAPI DXUTPause( _In_ bool bPauseTime, _In_ bool bPauseRendering );
		DXUTAPI void    WINAPI DXUTSetConstantFrameTime( _In_ bool bConstantFrameTime, _In_ float fTimePerFrame = 0.0333f );
		DXUTAPI void    WINAPI DXUTSetCursorSettings( _In_ bool bShowCursorWhenFullScreen = false, _In_ bool bClipCursorWhenFullScreen = false );
		DXUTAPI void    WINAPI DXUTSetHotkeyHandling( _In_ bool bAltEnterToToggleFullscreen = true, _In_ bool bEscapeToQuit = true, _In_ bool bPauseToToggleTimePause = true );
		DXUTAPI void    WINAPI DXUTSetMultimonSettings( _In_ bool bAutoChangeAdapter = true );
		DXUTAPI void    WINAPI DXUTSetShortcutKeySettings( _In_ bool bAllowWhenFullscreen = false, _In_ bool bAllowWhenWindowed = true ); // Controls the Windows key, and accessibility shortcut keys
		DXUTAPI void    WINAPI DXUTSetWindowSettings( _In_ bool bCallDefWindowProc = true );
		DXUTAPI HRESULT WINAPI DXUTSetTimer( _In_ LPDXUTCALLBACKTIMER pCallbackTimer, _In_ float fTimeoutInSecs = 1.0f, _Out_opt_ UINT* pnIDEvent = nullptr, _In_opt_ void* pCallbackUserContext = nullptr );
		DXUTAPI HRESULT WINAPI DXUTKillTimer( _In_ UINT nIDEvent );
		DXUTAPI void    WINAPI DXUTResetFrameworkState();
		DXUTAPI void    WINAPI DXUTShutdown( _In_ int nExitCode = 0 );
		DXUTAPI void    WINAPI DXUTSetIsInGammaCorrectMode( _In_ bool bGammaCorrect );
		DXUTAPI bool    WINAPI DXUTGetMSAASwapChainCreated();

		//--------------------------------------------------------------------------------------
		// State Retrieval
		//--------------------------------------------------------------------------------------

		// Direct3D 11
		DXUTAPI IDXGIFactory1*           WINAPI DXUTGetDXGIFactory(); // Does not addref unlike typical Get* APIs
		DXUTAPI IDXGISwapChain*          WINAPI DXUTGetDXGISwapChain(); // Does not addref unlike typical Get* APIs
		DXUTAPI const DXGI_SURFACE_DESC* WINAPI DXUTGetDXGIBackBufferSurfaceDesc();
		DXUTAPI ID3D11Device*            WINAPI DXUTGetD3D11Device(); // Does not addref unlike typical Get* APIs
		DXUTAPI ID3D11DeviceContext*     WINAPI DXUTGetD3D11DeviceContext(); // Does not addref unlike typical Get* APIs
		DXUTAPI ID3D11Device1*           WINAPI DXUTGetD3D11Device1(); // Does not addref unlike typical Get* APIs
		DXUTAPI ID3D11DeviceContext1*	 WINAPI DXUTGetD3D11DeviceContext1(); // Does not addref unlike typical Get* APIs
		DXUTAPI HRESULT                  WINAPI DXUTSetupD3D11Views( _In_ ID3D11DeviceContext* pd3dDeviceContext ); // Supports immediate or deferred context
		DXUTAPI D3D_FEATURE_LEVEL        WINAPI DXUTGetD3D11DeviceFeatureLevel(); // Returns the D3D11 devices current feature level
		DXUTAPI ID3D11RenderTargetView*  WINAPI DXUTGetD3D11RenderTargetView(); // Does not addref unlike typical Get* APIs
		DXUTAPI ID3D11DepthStencilView*  WINAPI DXUTGetD3D11DepthStencilView(); // Does not addref unlike typical Get* APIs

		// General
		DXUTAPI DXUTDeviceSettings WINAPI DXUTGetDeviceSettings();
		DXUTAPI HINSTANCE WINAPI DXUTGetHINSTANCE();
		DXUTAPI HWND      WINAPI DXUTGetHWND();
		DXUTAPI HWND      WINAPI DXUTGetHWNDFocus();
		DXUTAPI HWND      WINAPI DXUTGetHWNDDeviceFullScreen();
		DXUTAPI HWND      WINAPI DXUTGetHWNDDeviceWindowed();
		DXUTAPI RECT      WINAPI DXUTGetWindowClientRect();
		DXUTAPI LONG      WINAPI DXUTGetWindowWidth();
		DXUTAPI LONG      WINAPI DXUTGetWindowHeight();
		DXUTAPI RECT      WINAPI DXUTGetWindowClientRectAtModeChange(); // Useful for returning to windowed mode with the same resolution as before toggle to full screen mode
		DXUTAPI RECT      WINAPI DXUTGetFullsceenClientRectAtModeChange(); // Useful for returning to full screen mode with the same resolution as before toggle to windowed mode
		DXUTAPI double    WINAPI DXUTGetTime();
		DXUTAPI float     WINAPI DXUTGetElapsedTime();
		DXUTAPI bool      WINAPI DXUTIsWindowed();
		DXUTAPI bool	  WINAPI DXUTIsInGammaCorrectMode();
		DXUTAPI float     WINAPI DXUTGetFPS();
		DXUTAPI LPCWSTR   WINAPI DXUTGetWindowTitle();
		DXUTAPI LPCWSTR   WINAPI DXUTGetFrameStats( _In_ bool bIncludeFPS = false );
		DXUTAPI LPCWSTR   WINAPI DXUTGetDeviceStats();

		DXUTAPI bool      WINAPI DXUTIsVsyncEnabled();
		DXUTAPI bool      WINAPI DXUTIsRenderingPaused();
		DXUTAPI bool      WINAPI DXUTIsTimePaused();
		DXUTAPI bool      WINAPI DXUTIsActive();
		DXUTAPI int       WINAPI DXUTGetExitCode();
		DXUTAPI bool      WINAPI DXUTGetShowMsgBoxOnError();
		DXUTAPI bool      WINAPI DXUTGetAutomation();  // Returns true if -automation parameter is used to launch the app
		DXUTAPI bool      WINAPI DXUTIsKeyDown( _In_ BYTE vKey ); // Pass a virtual-key code, ex. VK_F1, 'A', VK_RETURN, VK_LSHIFT, etc
		DXUTAPI bool      WINAPI DXUTWasKeyPressed( _In_ BYTE vKey );  // Like DXUTIsKeyDown() but return true only if the key was just pressed
		DXUTAPI bool      WINAPI DXUTIsMouseButtonDown( _In_ BYTE vButton ); // Pass a virtual-key code: VK_LBUTTON, VK_RBUTTON, VK_MBUTTON, VK_XBUTTON1, VK_XBUTTON2
		DXUTAPI HRESULT   WINAPI DXUTCreateState(); // Optional method to create DXUT's memory.  If its not called by the application it will be automatically called when needed
		DXUTAPI void      WINAPI DXUTDestroyState(); // Optional method to destroy DXUT's memory.  If its not called by the application it will be automatically called after the application exits WinMain

		}

#if defined(extern_cplus) && defined(extern_cplusplus)
	}
	}
#elif defined(extern_cplus) && !defined(extern_cplusplus)
}
#elif defined(extern_cplusplus) && !defined(extern_cplus)
}
#endif

	//--------------------------------------------------------------------------------------
	// DXUT core layer includes
	//--------------------------------------------------------------------------------------
#include "DXUTmisc.h"
#include "DXUTDevice11.h"
