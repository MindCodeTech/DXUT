//--------------------------------------------------------------------------------------
// File: DXUTexp.h
//
// Desc: Header file that is the standard exports definitions for the
//		 DXUT for Win32 Desktop
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#ifdef _MSC_VER
#pragma once
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

#ifndef _WINDOWS_
#include <windows.h>
#endif

#define namespace_DirectX namespace DirectX {
#define namespace_DirectX_end }

#define namespace_DXUT namespace DXUT {
#define namespace_DXUT_end }

#define namespace_MathHelper namespace MathHelper {
#define namespace_MathHelper_end }

#define namespace_DDSTextureLoader namespace DDSTextureLoader {
#define namespace_DDSTextureLoader_end }

#define namespace_ScreenGrab namespace ScreenGrab {
#define namespace_ScreenGrab_end }

#define namespace_WICTextureLoader namespace WICTextureLoader {
#define namespace_WICTextureLoader_end }


#ifdef __cplusplus
#define EXTERN_C_BEGIN extern "C" {
#define EXTERN_C_END }
#define EXTERN_CC_BEGIN extern "C++" {
#define EXTERN_CC_END }
#else
#define EXTERN_C_BEGIN
#define EXTERN_C_END
#define EXTERN_CC_BEGIN
#define EXTERN_CC_END
#endif

#ifdef __cplusplus
EXTERN_CC_BEGIN
#endif

#ifdef __cplusplus
EXTERN_CC_END
#endif

#ifdef __cplusplus
#ifndef _EXTERNC
#define _EXTERNC extern "C"
#endif
#ifndef _EXTERNCC
#define _EXTERNCC extern "C++"
#endif
#ifndef _EXTERN
#define _EXTERN extern
#endif
#else
#ifndef _EXTERNC
#define _EXTERNC
#endif
#ifndef _EXTERNCC
#define _EXTERNCC
#endif
#ifndef _EXTERN
#define _EXTERN
#endif
#endif

#ifdef __cplusplus
#define DXUTEXTERNC extern "C"
#define DXUTEXTERNCC extern "C++"
#define DXUTEXTERN extern
#else
#define DXUTEXTERNC
#define DXUTEXTERNCC
#define DXUTEXTERN
#endif

#if defined(_WINDOWS) || defined(_WIN32)
/* If building or using DXUTlib as a DLL, define DXUTLIB_DLL.
* This is not mandatory, but it offers a little performance increase.
*/

#if defined(LIB_EXPORTS) || defined(DXUTLIB_EXPORTS)
#ifndef DXUTLIB_IMPORTS
#ifndef DXUTLIB_EXPORTS
#define DXUTLIB_EXPORTS 1
#endif
#endif
#endif

#if defined(LIB_IMPORTS) || defined(DXUTLIB_IMPORTS)
#if defined(DXUTLIB_EXPORTS)
#error ("!!!You are bulding DXUT export and import simultaniously")
#else
#ifndef DXUTLIB_IMPORTS
#define DXUTLIB_IMPORTS 1
#endif
#endif
#endif

#if defined(LIB_STATIC) || defined(DXUTLIB_STATIC)
#ifndef DXUTLIB_DLL
#ifndef DXUTLIB_STATIC
#define DXUTLIB_STATIC 1
#endif
#endif
#endif

#if (defined(_DLL) || defined(_USRDLL) || defined(_WINDLL) || defined(LIB_DYNAMIC) || defined(DXUTLIB_DLL)) && !defined(_LIB) && !defined(DXUTLIB_STATIC)
#ifndef DXUTLIB_STATIC
#ifndef DXUTLIB_DLL
#define DXUTLIB_DLL 1
#endif
#endif
#endif

#if !defined(DXUTLIB_DLL) && !defined(DXUTLIB_STATIC)
#error ("!!!Your DXUT lib type static or dll aren't defined")
#endif

#  ifdef DXUTLIB_DLL
#    if defined(WIN32) && (!defined(__BORLANDC__) || (__BORLANDC__ >= 0x500))
#      if defined(DXUTLIB_EXPORTS) && !defined(DXUTLIB_STATIC)
#        define DXUTAPI __declspec(dllexport)
#      elif defined (DXUTLIB_IMPORTS) && (defined(_DLL) || defined(_WINDLL) || defined(_USRDLL)) && !defined(DXUTLIB_STATIC)
#        define DXUTAPI __declspec(dllimport)
#      else // DXUTLIB_STATIC  _LIB
#        define DXUTAPI
#      endif
#    endif
#  else  // DXUTLIB_STATIC
#      define DXUTAPI
#  endif  /* ! DXUTLIB_DLL */

#else
#	define DXUTAPI
#endif // _WINDOWS

#define DXSTDAPI                  EXTERN_C DXUTAPI HRESULT STDAPICALLTYPE

#define DXSTDAPI_(type)           EXTERN_C DXUTAPI type STDAPICALLTYPE
