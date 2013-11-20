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

#if defined(_WINDOWS) || defined(_WIN32)
/* If building or using DXUTlib as a DLL, define DXUTLIB_DLL.
* This is not mandatory, but it offers a little performance increase.
*/

#if defined(LIB_EXPORT) || defined(DXUTLIB_EXPORT)
#ifndef DXUTLIB_IMPORT
#ifndef DXUTLIB_EXPORT
#define DXUTLIB_EXPORT 1
#endif
#endif
#endif

#if defined(LIB_IMPORT) || defined(DXUTLIB_IMPORT)
#if defined(DXUTLIB_EXPORT)
#error ("!!!You are bulding DXUT export and import simultaniously")
#else
#ifndef DXUTLIB_IMPORT
#define DXUTLIB_IMPORT 1
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

//#define extern_cplus

// Defined for Templates functions export
#define extern_cplusplus

#ifdef extern_cplus
#define _EXTERN_C_START extern "C" {
#define _EXTERN_C_END  }
#endif

#ifdef extern_cplusplus
#define _EXTERN_CPP_START extern "C++" {
#define _EXTERN_CPP_END  }
#endif

#define _EXTERN extern

#  ifdef DXUTLIB_DLL
#    if defined(WIN32) && (!defined(__BORLANDC__) || (__BORLANDC__ >= 0x500))
#      if defined(DXUTLIB_EXPORT) && !defined(DXUTLIB_STATIC)
#        define DXUTAPI __declspec(dllexport)
#      elif defined (DXUTLIB_IMPORT) && (defined(_DLL) || defined(_WINDLL) || defined(_USRDLL)) && !defined(DXUTLIB_STATIC)
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


