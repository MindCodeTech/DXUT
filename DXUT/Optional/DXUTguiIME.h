//--------------------------------------------------------------------------------------
// File: DXUTguiIME.h
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
#pragma once

#ifdef __cplusplus
EXTERN_C_BEGIN
#endif

NAMESPACE_DXUT

//--------------------------------------------------------------------------------------
// Forward declarations
//--------------------------------------------------------------------------------------
class CDXUTIMEEditBox;

//-----------------------------------------------------------------------------
// IME-enabled EditBox control
//-----------------------------------------------------------------------------
#define MAX_COMPSTRING_SIZE 256

class CDXUTIMEEditBox : public CDXUTEditBox
{
public:

	DXUTAPI static HRESULT CreateIMEEditBox(_In_ CDXUTDialog* pDialog, _In_ int ID, _In_z_ LPCWSTR strText, _In_ int x, _In_ int y, _In_ int width,
		_In_ int height, _In_ bool bIsDefault = false, _Outptr_opt_ CDXUTIMEEditBox** ppCreated = nullptr);

	CDXUTIMEEditBox(_In_opt_ CDXUTDialog* pDialog = nullptr);
	virtual ~CDXUTIMEEditBox();

	DXUTAPI static void InitDefaultElements(_In_ CDXUTDialog* pDialog);

	DXUTAPI static void WINAPI Initialize(_In_ HWND hWnd);
	DXUTAPI static void WINAPI Uninitialize();

	DXUTAPI static  HRESULT WINAPI  StaticOnCreateDevice();
	DXUTAPI static  bool WINAPI     StaticMsgProc(_In_ HWND hWnd, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam);

	DXUTAPI static  void WINAPI     SetImeEnableFlag(_In_ bool bFlag);

	virtual DXUTAPI void Render(_In_ float fElapsedTime) override;
	virtual DXUTAPI bool MsgProc(_In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam) override;
	virtual DXUTAPI bool HandleMouse(_In_ UINT uMsg, _In_ const POINT& pt, _In_ WPARAM wParam, _In_ LPARAM lParam) override;
	virtual DXUTAPI void UpdateRects() override;
	virtual DXUTAPI void OnFocusIn() override;
	virtual DXUTAPI void OnFocusOut() override;

	DXUTAPI void PumpMessage();

	virtual DXUTAPI void RenderCandidateReadingWindow(_In_ bool bReading);
	virtual DXUTAPI void RenderComposition();
	virtual DXUTAPI void RenderIndicator(_In_ float fElapsedTime);

protected:
	DXUTAPI static void WINAPI      EnableImeSystem(_In_ bool bEnable);

	DXUTAPI static WORD WINAPI      GetLanguage()
	{
		return ImeUi_GetLanguage();
	}
	DXUTAPI static WORD WINAPI      GetPrimaryLanguage()
	{
		return ImeUi_GetPrimaryLanguage();
	}
	DXUTAPI static void WINAPI      SendKey(_In_ BYTE nVirtKey);
	DXUTAPI static DWORD WINAPI     GetImeId(_In_ UINT uIndex = 0)
	{
		return ImeUi_GetImeId(uIndex);
	};
	DXUTAPI static void WINAPI      CheckInputLocale();
	DXUTAPI static void WINAPI      CheckToggleState();
	DXUTAPI static void WINAPI      SetupImeApi();
	DXUTAPI static void WINAPI      ResetCompositionString();

	DXUTAPI static void             SetupImeUiCallback();

protected:
	enum
	{
		INDICATOR_NON_IME,
		INDICATOR_CHS,
		INDICATOR_CHT,
		INDICATOR_KOREAN,
		INDICATOR_JAPANESE
	};

	struct CCandList
	{
		CUniBuffer HoriCand; // Candidate list string (for horizontal candidate window)
		int nFirstSelected; // First character position of the selected string in HoriCand
		int nHoriSelectedLen; // Length of the selected string in HoriCand
		RECT rcCandidate;   // Candidate rectangle computed and filled each time before rendered
	};

	static POINT s_ptCompString;        // Composition string position. Updated every frame.
	static int s_nFirstTargetConv;    // Index of the first target converted char in comp string.  If none, -1.
	static CUniBuffer s_CompString;       // Buffer to hold the composition string (we fix its length)
	static DWORD            s_adwCompStringClause[MAX_COMPSTRING_SIZE];
	static CCandList s_CandList;          // Data relevant to the candidate list
	static WCHAR            s_wszReadingString[32];// Used only with horizontal reading window (why?)
	static bool s_bImeFlag;			  // Is ime enabled

	// Color of various IME elements
	DWORD m_ReadingColor;        // Reading string color
	DWORD m_ReadingWinColor;     // Reading window color
	DWORD m_ReadingSelColor;     // Selected character in reading string
	DWORD m_ReadingSelBkColor;   // Background color for selected char in reading str
	DWORD m_CandidateColor;      // Candidate string color
	DWORD m_CandidateWinColor;   // Candidate window color
	DWORD m_CandidateSelColor;   // Selected candidate string color
	DWORD m_CandidateSelBkColor; // Selected candidate background color
	DWORD m_CompColor;           // Composition string color
	DWORD m_CompWinColor;        // Composition string window color
	DWORD m_CompCaretColor;      // Composition string caret color
	DWORD m_CompTargetColor;     // Composition string target converted color
	DWORD m_CompTargetBkColor;   // Composition string target converted background
	DWORD m_CompTargetNonColor;  // Composition string target non-converted color
	DWORD m_CompTargetNonBkColor;// Composition string target non-converted background
	DWORD m_IndicatorImeColor;   // Indicator text color for IME
	DWORD m_IndicatorEngColor;   // Indicator text color for English
	DWORD m_IndicatorBkColor;    // Indicator text background color

	// Edit-control-specific data
	int m_nIndicatorWidth;     // Width of the indicator symbol
	RECT m_rcIndicator;         // Rectangle for drawing the indicator button

#if defined(DEBUG) || defined(_DEBUG)
	static bool    m_bIMEStaticMsgProcCalled;
#endif
};

NAMESPACE_DXUT_END

#ifdef __cplusplus
EXTERN_C_END
#endif
