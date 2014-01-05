/* DXUTLibExports.c -- DXUT library export types definitions  Entry point
 : Public domain */
#pragma once

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

#define NAMESPACE_DirectX namespace DirectX {
#define NAMESPACE_DirectX_END }

#define NAMESPACE_DXUT namespace DXUT {
#define NAMESPACE_DXUT_END }

#define NAMESPACE_DDSTextureLoader namespace DDSTextureLoader {
#define NAMESPACE_DDSTextureLoader_END }

#define NAMESPACE_ScreenGrab namespace ScreenGrab {
#define NAMESPACE_ScreenGrab_END }

#define NAMESPACE_WICTextureLoader namespace WICTextureLoader {
#define NAMESPACE_WICTextureLoader_END }

//#define extern_cplus

// Defined for Templates functions export
#define extern_cplusplus

#ifndef EXTERN_C_BEGIN
#ifdef __cplusplus
#ifdef extern_cplus
#define EXTERN_C_BEGIN extern "C" {
#define EXTERN_C_END }
#endif
#ifdef extern_cplusplus
#define EXTERN_C_BEGIN extern "C++" {
#define EXTERN_C_END }
#endif
#else
#define EXTERN_C_BEGIN
#define EXTERN_C_END
#endif
#endif

#ifdef __cplusplus
EXTERN_C_BEGIN
#endif

#ifdef __cplusplus
EXTERN_C_END
#endif

#ifdef __cplusplus
#if defined(extern_cplus)
#define _EXTERN extern "C"
#elif defined(extern_cplusplus)
#define _EXTERN extern "C++"
#endif
#else
#define _EXTERN extern
#endif

#ifdef __cplusplus
#if defined(extern_cplus)
#define _EXTERN_C extern "C"
#elif defined(extern_cplusplus)
#define _EXTERN_C extern "C++"
#endif
#else
#define _EXTERN extern
#endif

#ifdef __cplusplus
#if defined(extern_cplus)
#define DXUTEXTERN extern "C"
#elif defined(extern_cplusplus)
#define DXUTEXTERN extern "C++"
#endif
#else
#define DXUTEXTERN extern
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
