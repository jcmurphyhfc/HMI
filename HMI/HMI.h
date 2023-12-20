
// HMI.h : main header file for the HMI application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols
#include "MilObj.h"
#include "..\HMIDlg\HMIDlgApi.h"
#include "Pmac.h"
#include "PmacTerminal.h"
#include "Chat.h"
#include "AxisFaultsDlg.h"
#include "DriveFaults.h"

#ifndef _DEBUG
#define WINDOW_POSITION_X 0
#else
#define WINDOW_POSITION_X 0 //1680
#endif

#define OSCEOLA_LAYOUT


// CHMIApp:
// See HMI.cpp for the implementation of this class
//

class CHMIApp : public CWinApp
{
public:
	CHMIApp();

private:
	DECLARE_GDI_PLUS;

// Members
public:
	CChat m_chat;
	CWinThread* m_pWinThread;
	bool m_bSettingsModifyied;
	CWnd* m_pWndView;
	CPmac m_pmac;
	//CPmac m_pmacSlicer;
	//CPmac m_pmacSlicer2;
	bool m_bSplash;
	CMil m_mil;
	MIL_ID SelectDisplay(HWND hWnd);
	MIL_ID SelectDisplay2(HWND hWnd);
	MIL_ID SelectRejectDisplay(HWND hWnd);
	MIL_ID SelectRejectDisplay2(HWND hWnd);
	ALLSETTINGS m_Settings;
	ALLSETTINGS m_MasterSettings;
	ALLCOUNTERS m_Counters;
	CPmacTerminal* m_pTerminalDlg;

// Operations
public:
	bool CheckPassword();
	bool  CheckMasterPassword();
	void WaitOnGIGE(void);
	void UpdateTerminal();

// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	afx_msg void OnEwfUtilBoot();

// Implementation
	afx_msg void OnAppAbout();
	afx_msg void OnAppExit();

	DECLARE_MESSAGE_MAP()
	afx_msg void OnEwfUtil();
	afx_msg void OnTimeSettings();
	afx_msg void OnTouchCalibration();
	afx_msg void OnPmacTerminal();
	afx_msg void OnBtcChat();
	afx_msg void OnClearTotalTime();
};

extern CHMIApp theApp;
