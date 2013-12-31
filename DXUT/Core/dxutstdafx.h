//--------------------------------------------------------------------------------------
// File: DxStdAfx.h
//
// Desc: Header file that is the standard includes for the DirectX SDK samples
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------
#pragma once

#include "DXUTvers.h"
#include "DXUTvers.h"
#include "DXUT.h"
//#include "typesexport.h"
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
#include "SDKsound.h"
#include "SDKwavefile.h"
//#include "DXUTmesh.h"

// DirectXTex
#include "DDS.h"
// #include "DirectXTex.h"
// #include "DirectXTexp.h"
#include "DDSTextureLoader.h"
#if !defined(WINAPI_FAMILY) || (WINAPI_FAMILY != WINAPI_FAMILY_PHONE_APP)
#include "WICTextureLoader.h"
#endif
#include "ScreenGrab.h"

//#include <d3d9.h>

// #include "BC.h"
//#include "scoped.h" ported to PlatformHelpers.h
// #include "BCDirectCompute.h"
// #include "filters.h"

///////////////////////////////////////////////////////////////////////////////
// DirectXTK
//#include "PlatformHelpers.h"
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

////////////////////////////////////////////////////////////////////////////////
// Effects11

// #include "Effects11exp.h"
// #include "PlatformHelpers.h"
//
// // Effects11
// #include "d3dx11effect.h"
// #include "d3dxGlobal.h"
//
// #include "Effect.h"
// #include "EffectStateBase11.h"
//
// #include "EffectLoad.h"
//
//
// #define _PCH_BUILD
// #ifdef _PCH_BUILD
// #include "EffectStates11.h"
// #include "SOParser.h"
// #endif
// #undef _PCH_BUILD

// #include "d3dx11effect.h"
// #include "d3dxGlobal.h"
// #include "EffectBinaryFormat.h"
// #include "IUnknownImp.h"
// #include "Effect.h"
// #include "EffectStateBase11.h"
// #include "EffectStates11.h"
// #include "EffectLoad.h"
// #include "SOParser.h"
