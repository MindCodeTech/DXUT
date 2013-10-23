//--------------------------------------------------------------------------------------
// File: DXErr.h
//
// DirectX Error Library
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

// This version only supports UNICODE.

#pragma once

#ifdef extern_cplus
extern "C" {
#endif

#ifdef extern_cplusplus
	extern "C++" {
#endif

		namespace DXUT
		{

		//--------------------------------------------------------------------------------------
		// DXGetErrorString
		//--------------------------------------------------------------------------------------
		DXUTAPI const WCHAR* WINAPI DXGetErrorStringW( _In_ HRESULT hr );

#define DXGetErrorString DXGetErrorStringW

		//--------------------------------------------------------------------------------------
		// DXGetErrorDescription has to be modified to return a copy in a buffer rather than
		// the original static string.
		//--------------------------------------------------------------------------------------
		DXUTAPI void WINAPI DXGetErrorDescriptionW( _In_ HRESULT hr, _Out_cap_(count) WCHAR* desc, _In_ size_t count );

#define DXGetErrorDescription DXGetErrorDescriptionW

		//--------------------------------------------------------------------------------------
		//  DXTrace
		//
		//  Desc:  Outputs a formatted error message to the debug stream
		//
		//  Args:  WCHAR* strFile   The current file, typically passed in using the
		//                         __FILEW__ macro.
		//         DWORD dwLine    The current line number, typically passed in using the
		//                         __LINE__ macro.
		//         HRESULT hr      An HRESULT that will be traced to the debug stream.
		//         CHAR* strMsg    A string that will be traced to the debug stream (may be NULL)
		//         BOOL bPopMsgBox If TRUE, then a message box will popup also containing the passed info.
		//
		//  Return: The hr that was passed in.
		//--------------------------------------------------------------------------------------
		DXUTAPI HRESULT WINAPI DXTraceW( _In_z_ const WCHAR* strFile, _In_ DWORD dwLine, _In_ HRESULT hr, _In_opt_ const WCHAR* strMsg, _In_ bool bPopMsgBox );

#define DXTrace DXTraceW

		//--------------------------------------------------------------------------------------
		//
		// Helper macros
		//
		//--------------------------------------------------------------------------------------
#if defined(DEBUG) || defined(_DEBUG)
#define DXTRACE_MSG(str)              DXTrace( __FILEW__, (DWORD)__LINE__, 0, str, false )
#define DXTRACE_ERR(str,hr)           DXTrace( __FILEW__, (DWORD)__LINE__, hr, str, false )
#define DXTRACE_ERR_MSGBOX(str,hr)    DXTrace( __FILEW__, (DWORD)__LINE__, hr, str, true )
#else
#define DXTRACE_MSG(str)              (0L)
#define DXTRACE_ERR(str,hr)           (hr)
#define DXTRACE_ERR_MSGBOX(str,hr)    (hr)
#endif
		}

#if defined(extern_cplus) && defined(extern_cplusplus)
	}
	}
#elif defined(extern_cplus) && !defined(extern_cplusplus)
}
#elif defined(extern_cplusplus) && !defined(extern_cplus)
}
#endif
