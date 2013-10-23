//--------------------------------------------------------------------------------------
// File: AMD_SDK.h
//
// Library include file, to drag in all AMD SDK helper classes and functions.
//
// Author: Jon Story
// 
// Copyright © AMD Corporation. All rights reserved.
//--------------------------------------------------------------------------------------
#ifndef __AMD_SDK_H__
#define __AMD_SDK_H__


#define VENDOR_ID_AMD		(0x1002)
#define VENDOR_ID_NVIDIA	(0x10DE)
#define VENDOR_ID_INTEL		(0x8086)


#include "..\\DXUT\\Core\\DXUT.h"
#include "..\\DXUT\\Core\\DXUTmisc.h"
#include "..\\DXUT\\Optional\\DXUTgui.h"
#include "..\\DXUT\\Optional\\SDKmisc.h"
#include "..\\DXUT\\Optional\\SDKMesh.h"


// AMD helper classes and functions
#include "Timer.h"
#include "ShaderCache.h"
#include "HelperFunctions.h"
#include "Sprite.h" 
#include "Magnify.h"
#include "MagnifyTool.h"
#include "HUD.h"
#include "Geometry.h"
#include "LineRender.h"


// Profile helpers for timing and marking up as D3D perf blocks
#define AMD_PROFILE_RED		D3DCOLOR_XRGB( 255, 0, 0 )
#define AMD_PROFILE_GREEN	D3DCOLOR_XRGB( 0, 255, 0 )
#define AMD_PROFILE_BLUE	D3DCOLOR_XRGB( 0, 0, 255 )


#define AMDProfileBegin( col, name ) DXUT_BeginPerfEvent( col, name ); TIMER_Begin( col, name )
#define AMDProfileEnd() TIMER_End() DXUT_EndPerfEvent();

struct AMDProfileEventClass
{
	AMDProfileEventClass( unsigned int col, LPCWSTR name ) { AMDProfileBegin( col, name ); }
	~AMDProfileEventClass() { AMDProfileEnd() }
};

#define AMDProfileEvent( col, name ) AMDProfileEventClass __amd_profile_event( col, name )



#endif

//--------------------------------------------------------------------------------------
// EOF
//--------------------------------------------------------------------------------------

