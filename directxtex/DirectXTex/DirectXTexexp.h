/* DXTEXLibExports.c -- DXTEX library export types definitions  Entry point
2008-10-04 : Igor Pavlov : Public domain */
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
/* If building or using DXTEXlib as a DLL, define DXTEXLIB_DLL.
* This is not mandatory, but it offers a little performance increase.
*/

#if defined(_DLL) || defined(_USRDLL) || defined(_WINDLL)
#ifndef DXTEXLIB_DLL
#define DXTEXLIB_DLL
#endif
#endif

//#define extern_cplus
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

#  ifdef DXTEXLIB_DLL
#    if defined(WIN32) && (!defined(__BORLANDC__) || (__BORLANDC__ >= 0x500))
#      ifdef DXTEXLIB_EXPORT
#        define DXTEXAPI __declspec(dllexport)
#      else  // DXTEXLIB_IMPORT
#        define DXTEXAPI __declspec(dllimport)
#      endif
#    endif
#  else  // DXTEXLIB_LIB
#      define DXTEXAPI
#  endif  /* ! DXTEXLIB_DLL */

#else
#	define DXTEXAPI
#endif // _WINDOWS



#define DXSTDAPI                  EXTERN_C DXTEXAPI HRESULT STDAPICALLTYPE
#define DXSTDAPI_(type)           EXTERN_C DXTEXAPI type STDAPICALLTYPE


