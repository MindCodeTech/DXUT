//----------------------------------------------------------------------------
// File: dxutres.h
//
// Functions to create DXUT media from arrays in memory 
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//
// http://go.microsoft.com/fwlink/?LinkId=320437
//-----------------------------------------------------------------------------
#pragma once

#ifdef extern_cplus
extern "C" {
#endif

#ifdef extern_cplusplus
	extern "C++" {
#endif

		namespace DXUT
		{

DXUTAPI HRESULT WINAPI DXUTCreateGUITextureFromInternalArray( _In_ ID3D11Device* pd3dDevice, _Outptr_ ID3D11Texture2D** ppTexture );

		}

#if defined(extern_cplus) && defined(extern_cplusplus)
	}
	}
#elif defined(extern_cplus) && !defined(extern_cplusplus)
}
#elif defined(extern_cplusplus) && !defined(extern_cplus)
}
#endif
