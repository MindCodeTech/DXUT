//-----------------------------------------------------------------------------
// File: WaveFile.h
//
// Copyright (c) Microsoft Corp. All rights reserved.
//-----------------------------------------------------------------------------

#ifdef _MSC_VER
#pragma once
#endif

#ifdef __DDRAW_INCLUDED__
#define __DDRAW_INCLUDED__
#endif

#include <audioclient.h>

#undef __DDRAW_INCLUDED__

#ifdef __cplusplus
EXTERN_CC_BEGIN
#endif

//-----------------------------------------------------------------------------
// Typing macros
//-----------------------------------------------------------------------------
#define WAVEFILE_READ   1
#define WAVEFILE_WRITE  2

namespace_DXUT

//-----------------------------------------------------------------------------
// Name: class CWaveFile
// Desc: Encapsulates reading or writing sound data to or from a wave file
//-----------------------------------------------------------------------------
class DXUTAPI CWaveFile
{
public:
	WAVEFORMATEX* m_pwfx;        // Pointer to WAVEFORMATEX structure
	HMMIO m_hmmio;       // MM I/O handle for the WAVE
	MMCKINFO m_ck;          // Multimedia RIFF chunk
	MMCKINFO m_ckRiff;      // Use in opening a WAVE file
	DWORD m_dwSize;      // The size of the wave file
	MMIOINFO m_mmioinfoOut;
	DWORD m_dwFlags;
	BOOL m_bIsReadingFromMemory;
	BYTE* m_pbData;
	BYTE* m_pbDataCur;
	ULONG m_ulDataSize;
	CHAR* m_pResourceBuffer;

protected:
	HRESULT WINAPI ReadMMIO();
	HRESULT WINAPI WriteMMIO(_In_z_ WAVEFORMATEX* pwfxDest);

public:
	CWaveFile();
	~CWaveFile();

	HRESULT WINAPI Open(_In_z_ LPWSTR strFileName, _In_ WAVEFORMATEX* pwfx, _In_ DWORD dwFlags);
	HRESULT WINAPI OpenFromMemory(_In_reads_(ulDataSize) BYTE* pbData, _In_ ULONG ulDataSize, _In_ WAVEFORMATEX* pwfx, _In_ DWORD dwFlags);
	HRESULT WINAPI Close();

	HRESULT WINAPI Read(_In_opt_ BYTE* pBuffer, _In_opt_ DWORD dwSizeToRead, _In_opt_ DWORD* pdwSizeRead);
	HRESULT WINAPI Write(_In_opt_ UINT nSizeToWrite, _In_opt_ BYTE* pbData, _In_opt_ UINT* pnSizeWrote);

	DWORD   WINAPI GetSize();
	HRESULT WINAPI ResetFile();
	WAVEFORMATEX* WINAPI GetFormat()
	{
		return m_pwfx;
	};
};

namespace_DXUT_end

#ifdef __cplusplus
EXTERN_CC_END
#endif
