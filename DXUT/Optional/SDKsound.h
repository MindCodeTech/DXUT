//-----------------------------------------------------------------------------
// File: DXUTsound.h
//
// Copyright (c) Microsoft Corp. All rights reserved.
//-----------------------------------------------------------------------------

#ifdef _MSC_VER
#pragma once
#endif

#ifndef NO_DSOUND_API

#ifdef __cplusplus
EXTERN_CC_BEGIN
#endif

namespace_DXUT

//-----------------------------------------------------------------------------
// Classes used by this header
//-----------------------------------------------------------------------------
class CSoundManager;
class CSound;
class CStreamingSound;
class CWaveFile;

//-----------------------------------------------------------------------------
// Typing macros
//-----------------------------------------------------------------------------
#define DXUT_StopSound(s)         { if(s) s->Stop(); }
#define DXUT_PlaySound(s)         { if(s) s->Play( 0, 0 ); }
#define DXUT_PlaySoundLooping(s)  { if(s) s->Play( 0, DSBPLAY_LOOPING ); }

//-----------------------------------------------------------------------------
// Name: class CSoundManager
// Desc:
//-----------------------------------------------------------------------------
class DXUTAPI CSoundManager
{
protected:
	IDirectSound8* m_pDS;

public:
	CSoundManager();
	~CSoundManager();

	HRESULT                 Initialize(_In_ HWND hWnd, _In_ DWORD dwCoopLevel);
	inline  LPDIRECTSOUND8  GetDirectSound()
	{
		return m_pDS;
	}
	HRESULT                 SetPrimaryBufferFormat(_In_ DWORD dwPrimaryChannels, _In_ DWORD dwPrimaryFreq,
		_In_ DWORD dwPrimaryBitRate);
	HRESULT                 Get3DListenerInterface(_In_ LPDIRECTSOUND3DLISTENER* ppDSListener);

	HRESULT                 Create(_In_opt_ CSound** ppSound, _In_z_ LPWSTR strWaveFileName, _In_opt_ DWORD dwCreationFlags = 0,
		_In_opt_ GUID guid3DAlgorithm = GUID_NULL, _In_opt_ DWORD dwNumBuffers = 1);
	HRESULT                 CreateFromMemory(_In_opt_ CSound** ppSound, _In_reads_(ulDataSize) BYTE* pbData, _In_ ULONG ulDataSize, _In_ LPWAVEFORMATEX pwfx,
		_In_opt_ DWORD dwCreationFlags = 0, _In_opt_ GUID guid3DAlgorithm = GUID_NULL,
		_In_opt_ DWORD dwNumBuffers = 1);
	HRESULT                 CreateStreaming(_In_opt_ CStreamingSound** ppStreamingSound, _In_z_ LPWSTR strWaveFileName,
		_In_opt_ DWORD dwCreationFlags, _In_opt_ GUID guid3DAlgorithm, _In_ DWORD dwNotifyCount,
		_In_ DWORD dwNotifySize, _In_ HANDLE hNotifyEvent);
};

//-----------------------------------------------------------------------------
// Name: class CSound
// Desc: Encapsulates functionality of a DirectSound buffer.
//-----------------------------------------------------------------------------
class DXUTAPI CSound
{
protected:
	LPDIRECTSOUNDBUFFER* m_apDSBuffer;
	DWORD m_dwDSBufferSize;
	CWaveFile* m_pWaveFile;
	DWORD m_dwNumBuffers;
	DWORD m_dwCreationFlags;

	HRESULT             RestoreBuffer(_In_ LPDIRECTSOUNDBUFFER pDSB, _In_opt_ BOOL* pbWasRestored);

public:
	CSound(_In_ LPDIRECTSOUNDBUFFER* apDSBuffer, _In_ DWORD dwDSBufferSize, _In_ DWORD dwNumBuffers,
		_In_opt_ CWaveFile* pWaveFile, _In_opt_ DWORD dwCreationFlags);
	virtual ~CSound();

	HRESULT             Get3DBufferInterface(_In_ DWORD dwIndex, _In_ LPDIRECTSOUND3DBUFFER* ppDS3DBuffer);
	HRESULT             FillBufferWithSound(_In_ LPDIRECTSOUNDBUFFER pDSB, _In_ BOOL bRepeatWavIfBufferLarger);
	LPDIRECTSOUNDBUFFER GetFreeBuffer();
	LPDIRECTSOUNDBUFFER GetBuffer(_In_ DWORD dwIndex);

	HRESULT             Play(_In_opt_ DWORD dwPriority = 0, _In_opt_ DWORD dwFlags = 0, _In_opt_ LONG lVolume = 0, _In_opt_ LONG lFrequency = -1,
		LONG lPan = 0);
	HRESULT             Play3D(_In_ LPDS3DBUFFER p3DBuffer, _In_opt_ DWORD dwPriority = 0, _In_opt_ DWORD dwFlags = 0, _In_opt_ LONG lFrequency = 0);
	HRESULT             Stop();
	HRESULT             Reset();
	BOOL                IsSoundPlaying();
};

//-----------------------------------------------------------------------------
// Name: class CStreamingSound
// Desc: Encapsulates functionality to play a wave file with DirectSound.
//       The Create() method loads a chunk of wave file into the buffer,
//       and as sound plays more is written to the buffer by calling
//       HandleWaveStreamNotification() whenever hNotifyEvent is signaled.
//-----------------------------------------------------------------------------
class DXUTAPI CStreamingSound : public CSound
{
protected:
	DWORD m_dwLastPlayPos;
	DWORD m_dwPlayProgress;
	DWORD m_dwNotifySize;
	DWORD m_dwNextWriteOffset;
	BOOL m_bFillNextNotificationWithSilence;

public:
	CStreamingSound(_In_ LPDIRECTSOUNDBUFFER pDSBuffer, _In_ DWORD dwDSBufferSize, _In_opt_ CWaveFile* pWaveFile,
		_In_ DWORD dwNotifySize);
	~CStreamingSound();

	HRESULT HandleWaveStreamNotification(_In_ BOOL bLoopedPlay);
	HRESULT Reset();
};

namespace_DXUT_end

#ifdef __cplusplus
EXTERN_CC_END
#endif

#endif // NO_DSOUND_API