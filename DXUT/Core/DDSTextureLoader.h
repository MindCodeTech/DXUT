//--------------------------------------------------------------------------------------
// File: DDSTextureLoader.h
//
// Functions for loading a DDS texture and creating a Direct3D 11 runtime resource for it
//
// Note these functions are useful as a light-weight runtime loader for DDS files. For
// a full-featured DDS file reader, writer, and texture processing pipeline see
// the 'Texconv' sample and the 'DirectXTex' library.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//
// http://go.microsoft.com/fwlink/?LinkId=248926
//--------------------------------------------------------------------------------------

#ifdef _MSC_VER
#pragma once
#endif

#ifdef __cplusplus
EXTERN_C_BEGIN
#endif

NAMESPACE_DXUT
NAMESPACE_DDSTextureLoader

DXUTAPI HRESULT CreateDDSTextureFromMemory(_In_ ID3D11Device* d3dDevice,
_In_reads_bytes_(ddsDataSize) const uint8_t* ddsData,
_In_ size_t ddsDataSize,
_Outptr_opt_ ID3D11Resource** texture,
_Outptr_opt_ ID3D11ShaderResourceView** textureView,
_In_ size_t maxsize = 0,
_Out_opt_ DDS_ALPHA_MODE* alphaMode = nullptr
);

DXUTAPI HRESULT CreateDDSTextureFromFile(_In_ ID3D11Device* d3dDevice,
	_In_z_ const wchar_t* szFileName,
	_Outptr_opt_ ID3D11Resource** texture,
	_Outptr_opt_ ID3D11ShaderResourceView** textureView,
	_In_ size_t maxsize = 0,
	_Out_opt_ DDS_ALPHA_MODE* alphaMode = nullptr
	);

DXUTAPI HRESULT CreateDDSTextureFromMemoryEx(_In_ ID3D11Device* d3dDevice,
	_In_reads_bytes_(ddsDataSize) const uint8_t* ddsData,
	_In_ size_t ddsDataSize,
	_In_ size_t maxsize,
	_In_ D3D11_USAGE usage,
	_In_ unsigned int bindFlags,
	_In_ unsigned int cpuAccessFlags,
	_In_ unsigned int miscFlags,
	_In_ bool forceSRGB,
	_Outptr_opt_ ID3D11Resource** texture,
	_Outptr_opt_ ID3D11ShaderResourceView** textureView,
	_Out_opt_ DDS_ALPHA_MODE* alphaMode = nullptr
	);

DXUTAPI HRESULT CreateDDSTextureFromFileEx(_In_ ID3D11Device* d3dDevice,
	_In_z_ const wchar_t* szFileName,
	_In_ size_t maxsize,
	_In_ D3D11_USAGE usage,
	_In_ unsigned int bindFlags,
	_In_ unsigned int cpuAccessFlags,
	_In_ unsigned int miscFlags,
	_In_ bool forceSRGB,
	_Outptr_opt_ ID3D11Resource** texture,
	_Outptr_opt_ ID3D11ShaderResourceView** textureView,
	_Out_opt_ DDS_ALPHA_MODE* alphaMode = nullptr
	);

NAMESPACE_DDSTextureLoader_END
NAMESPACE_DXUT_END

#ifdef __cplusplus
EXTERN_C_END
#endif
