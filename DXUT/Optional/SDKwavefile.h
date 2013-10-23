//-----------------------------------------------------------------------------
// File: WaveFile.h
//
// Copyright (c) Microsoft Corp. All rights reserved.
//-----------------------------------------------------------------------------
#pragma once

#ifdef extern_cplus
extern "C" {
#endif

#ifdef extern_cplusplus
	extern "C++" {
#endif

//-----------------------------------------------------------------------------
// Typing macros 
//-----------------------------------------------------------------------------
#define WAVEFILE_READ   1
#define WAVEFILE_WRITE  2

		namespace DXUT
		{

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
    HRESULT ReadMMIO();
    HRESULT WriteMMIO( _In_z_ WAVEFORMATEX* pwfxDest );

public:
            CWaveFile();
            ~CWaveFile();

    HRESULT Open( _In_z_ LPWSTR strFileName, _In_z_ WAVEFORMATEX* pwfx, _In_ DWORD dwFlags );
    HRESULT OpenFromMemory(  _In_reads_(ulDataSize) BYTE* pbData, _In_ ULONG ulDataSize, _In_z_ WAVEFORMATEX* pwfx, _In_ DWORD dwFlags );
    HRESULT Close();

    HRESULT Read( _In_opt_ BYTE* pBuffer, _In_opt_ DWORD dwSizeToRead, _In_opt_ DWORD* pdwSizeRead );
    HRESULT Write( _In_opt_ UINT nSizeToWrite, _In_opt_ BYTE* pbData, _In_opt_ UINT* pnSizeWrote );

    DWORD   GetSize();
    HRESULT ResetFile();
    WAVEFORMATEX* GetFormat()
    {
        return m_pwfx;
    };
};

		}

#if defined(extern_cplus) && defined(extern_cplusplus)
	}
	}
#elif defined(extern_cplus) && !defined(extern_cplusplus)
}
#elif defined(extern_cplusplus) && !defined(extern_cplus)
}
#endif

