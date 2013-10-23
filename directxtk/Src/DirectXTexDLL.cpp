//--------------------------------------------------------------------------------------
// File: DXUTDLL.h
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

BOOL WINAPI DllMain(
	_In_  HINSTANCE hinstDLL, 
	_In_  DWORD fdwReason,
	_In_  LPVOID lpvReserved )
{
  hinstDLL = hinstDLL;
  fdwReason = fdwReason;
  lpvReserved = lpvReserved;

  // Perform actions based on the reason for calling.
  switch( fdwReason ) 
  { 
  case DLL_PROCESS_ATTACH:
	  // Initialize once for each new process.
	  // Return FALSE to fail DLL load.
	  {
		  break;
	  }

  case DLL_THREAD_ATTACH:
	  // Do thread-specific initialization.
	  {
		  break;
	  }

  case DLL_THREAD_DETACH:
	  // Do thread-specific cleanup.
	  {
		  break;
	  }

  case DLL_PROCESS_DETACH:
	  // Perform any necessary cleanup.
	  {
		  break;
	  }
  }

  return TRUE;  // Successful DLL_PROCESS_ATTACH.

}

#include "pch.h"