//--------------------------------------------------------------------------------------
// File: dxutpch.h
//
// Desc: Header file that is the standard includes for the
//		 DXUT for Win32 Desktop
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#ifdef _MSC_VER
#pragma once
#endif

#include "DXUTvers.h"
#include "DXUT.h"
#include "typesexport.h"
#include "PlatformHelpers.h"

#include "dxerr.h"

// Optional
#include "ImeUi.h"
#include "DXUTgui.h"
#include "DXUTsettingsDlg.h"
#include "DXUTcamera.h"
#include "DXUTres.h"
#include "DXUTguiIME.h"
#include "DXUTMathHelper.h"
#include "DXUTLockFreePipe.h"
#include "SDKmisc.h"
#include "DXUTShader.h"
#include "SDKmesh.h"
#ifndef NO_DSOUND_API
#include "SDKsound.h"
#endif
#include "SDKwavefile.h"
// #include "DXUTmesh.h"

#include "DDS.h"
#include "DDSTextureLoader.h"
#if !defined(WINAPI_FAMILY) || (WINAPI_FAMILY != WINAPI_FAMILY_PHONE_APP)
#include "WICTextureLoader.h"
#endif
#include "ScreenGrab.h"



