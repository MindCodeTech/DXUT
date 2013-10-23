//--------------------------------------------------------------------------------------
// File: pch.h
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//
// http://go.microsoft.com/fwlink/?LinkId=248929
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

// If app hasn't choosen, set to work with Windows Vista and beyond
#ifndef WINVER
#define WINVER         0x0602
#endif
#ifndef _WIN32_WINDOWS
#define _WIN32_WINDOWS 0x0602
#endif
#if (_WIN32_WINNT < 0x0602)
#define _WIN32_WINNT   0x0602
#endif

#if (_WIN32_WINNT >= _WIN32_WINNT_WIN8) && !defined(DXGI_1_2_FORMATS)
#define DXGI_1_2_FORMATS
#endif

#if defined(_MSC_VER) && defined(DXTKLIB_EXPORT) || defined(DXTKLIB_IMPORT)
#define DXTK_AUTOLIB
#endif

// #define DXTK_AUTOLIB to automatically include the libs needed for DXTK
#ifdef DXTK_AUTOLIB
#pragma comment( lib, "d3d11.lib" )
#pragma comment( lib, "d3d10_1.lib" )
#pragma comment( lib, "d3d10.lib" )
#pragma comment( lib, "comctl32.lib" )
#pragma comment( lib, "dxgi.lib" )
#pragma comment( lib, "dxguid.lib" )
#pragma comment( lib, "d3dcompiler.lib" )
// #pragma comment( lib, "ole32.lib" ) // included with additional include directories 
// #pragma comment( lib, "uuid.lib" ) // included with additional include directories 
#pragma comment( lib, "usp10.lib" )
#pragma comment( lib, "ddraw.lib" )
#pragma comment( lib, "d2d1.lib" )
#pragma comment( lib, "dwrite.lib" )
//#pragma comment( lib, "dsound.lib" )
#pragma comment( lib, "d3dcsx.lib" )
#pragma comment( lib, "WinMM.Lib" )
#pragma comment( lib, "Imm32.Lib" )
#pragma comment( lib, "Version.Lib" ) 
#endif

#pragma warning(disable : 4102 4127 4201 4324 4481 4505 4616 4706 6326 6993 )

#pragma warning(push)
#pragma warning(disable : 4005)

#pragma pack(push)
#pragma pack(8)

// Standard Windows includes
#include <windows.h>
#include <ocidl.h>
#include <initguid.h>
#include <commctrl.h> // for InitCommonControls()
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
#include <wrl.h>


// Direct3D11 includes
#include <d3dcommon.h>
#include <dxgi1_2.h>
#include <d3d11_1.h>
#include <d3d11shader.h>
#include <d3d10_1.h>
#include <d3dcompiler.h>
#include <dxgiformat.h>
#if (_WIN32_WINNT >= _WIN32_WINNT_WIN8) || defined(_WIN7_PLATFORM_UPDATE)
#include <d2d1_1.h>
#endif

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

//#undef min // use __min instead
//#undef max // use __max instead

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
// 			typedef DXTKAPI const XMVECTOR& HXMVECTOR;
// 			typedef DXTKAPI const XMMATRIX& FXMMATRIX;
// #endif
// 		}

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

#if FXDEBUG
#define __BREAK_ON_FAIL       { __debugbreak(); }
#else
#define __BREAK_ON_FAIL 
#endif


#define VA(x, action) { hr = (x); if (FAILED(hr)) { action; __BREAK_ON_FAIL;                     return hr;  } }
#define VNA(x,action) {           if (!(x))       { action; __BREAK_ON_FAIL; hr = E_OUTOFMEMORY; goto lExit; } }
#define VBA(x,action) {           if (!(x))       { action; __BREAK_ON_FAIL; hr = E_FAIL;        goto lExit; } }
#define VHA(x,action) { hr = (x); if (FAILED(hr)) { action; __BREAK_ON_FAIL;                     goto lExit; } }

#define V(x)          { VA (x, 0) }
#define VN(x)         { VNA(x, 0) }
#define VB(x)         { VBA(x, 0) }
#define VH(x)         { VHA(x, 0) }

#define VBD(x,str)         { VBA(x, DPF(1,str)) }
#define VHD(x,str)         { VHA(x, DPF(1,str)) }

#define VEASSERT(x)   { hr = (x); if (FAILED(hr)) { __BREAK_ON_FAIL; assert(!#x);                     goto lExit; } }
#define VNASSERT(x)   {           if (!(x))       { __BREAK_ON_FAIL; assert(!#x); hr = E_OUTOFMEMORY; goto lExit; } }

#define D3DX11FLTASSIGN(a,b)    { *reinterpret_cast< UINT32* >(&(a)) = *reinterpret_cast< UINT32* >(&(b)); }


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




///////////////////////////////////////////////////////////////////////////////
// DirectXTK
#include "DirectXTKvers.h"
#include "DirectXTKexp.h"
#include "typesexport.h"
#include "PlatformHelpers.h"
#include "DDS.h"
#include "DDSTextureLoader.h"
#if !defined(WINAPI_FAMILY) || (WINAPI_FAMILY != WINAPI_FAMILY_PHONE_APP)
#include "WICTextureLoader.h"
#endif
#include "ScreenGrab.h"

// #include "GeometricPrimitive.h"
// #include "PrimitiveBatch.h"
// #include "Effects.h"
// #include "SpriteFont.h"
// #include "SpriteBatch.h"
// #include "ConstantBuffer.h"
// #include "Model.h"
// #include "CommonStates.h"
// #include "VertexTypes.h"
// #include "SharedResourcePool.h"
// #include "Bezier.h"
// #include "AlignedNew.h"
// #include "EffectCommon.h"
// #include "DemandCreate.h"
// #include "BinaryReader.h"
// #include "SimpleMath.h"
// #include "SimpleMath.inl"


