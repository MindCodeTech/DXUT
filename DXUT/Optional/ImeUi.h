//--------------------------------------------------------------------------------------
// File: ImeUi.h
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

#ifdef _MSC_VER
#pragma once
#endif

#ifdef __cplusplus
EXTERN_CC_BEGIN
#endif

namespace_DXUT

class DXUTAPI CImeUiFont_Base
{
public:
	virtual void    SetHeight(_In_ UINT uHeight)
	{
		uHeight;
	}; // for backward compatibility
	virtual void    SetColor(_In_ DWORD color) = 0;
	virtual void    SetPosition(_In_ int x, _In_ int y) = 0;
	virtual void    GetTextExtent(_In_z_ LPCTSTR szText, _Out_ DWORD* puWidth, _Out_ DWORD* puHeight) = 0;
	virtual void    DrawText(_In_z_ LPCTSTR pszText) = 0;
};

typedef struct
{
	// symbol (Henkan-kyu)
	DWORD symbolColor;
	DWORD symbolColorOff;
	DWORD symbolColorText;
	BYTE symbolHeight;
	BYTE symbolTranslucence;
	BYTE symbolPlacement;
	CImeUiFont_Base* symbolFont;

	// candidate list
	DWORD candColorBase;
	DWORD candColorBorder;
	DWORD candColorText;

	// composition string
	DWORD compColorInput;
	DWORD compColorTargetConv;
	DWORD compColorConverted;
	DWORD compColorTargetNotConv;
	DWORD compColorInputErr;
	BYTE compTranslucence;
	DWORD compColorText;

	// caret
	BYTE caretWidth;
	BYTE caretYMargin;
}               DXUTAPI IMEUI_APPEARANCE;

typedef struct	// D3DTLVERTEX compatible
{
	float sx;
	float sy;
	float sz;
	float rhw;
	DWORD color;
	DWORD specular;
	float tu;
	float tv;
}               DXUTAPI IMEUI_VERTEX;

// IME States
#define IMEUI_STATE_OFF		0
#define IMEUI_STATE_ON		1
#define IMEUI_STATE_ENGLISH	2

// IME const
#define MAX_CANDLIST 10

// IME Flags
#define IMEUI_FLAG_SUPPORT_CARET	0x00000001

DXUTAPI bool ImeUi_Initialize(_In_ HWND hwnd, _In_ bool bDisable = false);
DXUTAPI void ImeUi_Uninitialize();
DXUTAPI void ImeUi_SetAppearance(_In_opt_ const IMEUI_APPEARANCE* pia);
DXUTAPI void ImeUi_GetAppearance(_Out_opt_ IMEUI_APPEARANCE* pia);
DXUTAPI bool ImeUi_IgnoreHotKey(_In_ const MSG* pmsg);
DXUTAPI LPARAM ImeUi_ProcessMessage(_In_ HWND hWnd, _In_ UINT uMsg, _In_ WPARAM wParam, _Inout_ LPARAM& lParam, _Out_ bool* trapped);
DXUTAPI void ImeUi_SetScreenDimension(_In_ UINT width, _In_ UINT height);
DXUTAPI void ImeUi_RenderUI(_In_ bool bDrawCompAttr = true, _In_ bool bDrawOtherUi = true);
DXUTAPI void ImeUi_SetCaretPosition(_In_ UINT x, _In_ UINT y);
DXUTAPI void ImeUi_SetCompStringAppearance(_In_ CImeUiFont_Base* pFont, _In_ DWORD color, _In_ const RECT* prc);
DXUTAPI bool ImeUi_GetCaretStatus();
DXUTAPI void ImeUi_SetInsertMode(_In_ bool bInsert);
DXUTAPI void ImeUi_SetState(_In_ DWORD dwState);
DXUTAPI DWORD ImeUi_GetState();
DXUTAPI void ImeUi_EnableIme(_In_ bool bEnable);
DXUTAPI bool ImeUi_IsEnabled();
DXUTAPI void ImeUi_FinalizeString(_In_ bool bSend = false);
DXUTAPI void ImeUi_ToggleLanguageBar(_In_ BOOL bRestore);
DXUTAPI bool ImeUi_IsSendingKeyMessage();
DXUTAPI void ImeUi_SetWindow(_In_ HWND hwnd);
DXUTAPI UINT ImeUi_GetInputCodePage();
DXUTAPI DWORD ImeUi_GetFlags();
DXUTAPI void ImeUi_SetFlags(_In_ DWORD dwFlags, _In_ bool bSet);

DXUTAPI WORD ImeUi_GetPrimaryLanguage();
DXUTAPI DWORD ImeUi_GetImeId(_In_ UINT uIndex);
DXUTAPI WORD ImeUi_GetLanguage();
DXUTAPI LPTSTR ImeUi_GetIndicatior();
DXUTAPI bool ImeUi_IsShowReadingWindow();
DXUTAPI bool ImeUi_IsShowCandListWindow();
DXUTAPI bool ImeUi_IsVerticalCand();
DXUTAPI bool ImeUi_IsHorizontalReading();
DXUTAPI TCHAR*          ImeUi_GetCandidate(_In_ UINT idx);
DXUTAPI TCHAR*          ImeUi_GetCompositionString();
DXUTAPI DWORD ImeUi_GetCandidateSelection();
DXUTAPI DWORD ImeUi_GetCandidateCount();
DXUTAPI BYTE*           ImeUi_GetCompStringAttr();
DXUTAPI DWORD ImeUi_GetImeCursorChars();

DXUTEXTERNCC DXUTAPI void (CALLBACK*ImeUiCallback_DrawRect)(_In_ int x1, _In_ int y1, _In_ int x2, _In_ int y2, _In_ DWORD color);
DXUTEXTERNCC DXUTAPI void*    (__cdecl*ImeUiCallback_Malloc)(_In_ size_t bytes);
DXUTEXTERNCC DXUTAPI void(__cdecl*ImeUiCallback_Free)(_In_ void* ptr);
DXUTEXTERNCC DXUTAPI void (CALLBACK*ImeUiCallback_DrawFans)(_In_ const IMEUI_VERTEX* paVertex, _In_ UINT uNum);
DXUTEXTERNCC DXUTAPI void (CALLBACK*ImeUiCallback_OnChar)(_In_ WCHAR wc);

namespace_DXUT_end

#ifdef __cplusplus
EXTERN_CC_END
#endif
