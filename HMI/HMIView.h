
// HMIView.h : interface of the CHMIView class
//

#pragma once

#include "resource.h"
#include "MilWnd.h"
#include "gdistatusmain.h"
#include "gdi_ButtonXL.h"
#include "slice_count.h"
#include "afxcmn.h"
#include "gdigagetctrl1.h"
#include "gdimotorstatusctrl1.h"
#include "afxwin.h"
#include "ColorStatic.h"
//#include "ClientEIP.h"
#include "gdiiostatusctrl_slicer.h"
#include "gdiledlightsctrl.h"
#include "Alarms.h"
#include "gdimultireadoutctrl1.h"
#include "statusboxex.h"

#define FAULT_HISTORY_PATH      _T("D:\\BTCDATA\\HISTORY\\BTCERRORS.TXT")

#define DPR_OFFSET_MOTORBITS     112
#define MAX_ALARMS                50

// BTC Status data starts at offset 980
#define DPR_OFFSET_BTCMODE       982
#define DPR_OFFSET_SHEET_COUNT  1084
#define DPR_OFFSET_SHEET_SHIFT  1088
#define DPR_OFFSET_TOTAL_SHEET  1092

#define DPR_OFFSET_PEAK_I1       884
#define DPR_OFFSET_PEAK_I2       888
#define DPR_OFFSET_PEAK_I3       892
#define DPR_OFFSET_PEAK_I4       896
#define DPR_OFFSET_PEAK_I5       900
#define DPR_OFFSET_PEAK_I6       904
#define DPR_OFFSET_PEAK_I7       908
#define DPR_OFFSET_PEAK_I8       912

#define DPR_OFFSET_PEAK_FE1      948
#define DPR_OFFSET_PEAK_FE2      950
#define DPR_OFFSET_PEAK_FE3      952
#define DPR_OFFSET_PEAK_FE4      954
#define DPR_OFFSET_PEAK_FE5      956
#define DPR_OFFSET_PEAK_FE6      958
#define DPR_OFFSET_PEAK_FE7      960
#define DPR_OFFSET_PEAK_FE8      962
#define DPR_OFFSET_PEAK_FE9      964
#define DPR_OFFSET_PEAK_FE10     966
#define DPR_OFFSET_PEAK_FE11     968
#define DPR_OFFSET_PEAK_FE12     970
#define DPR_OFFSET_PEAK_FE13     972
#define DPR_OFFSET_PEAK_FE14     974
#define DPR_OFFSET_PEAK_FE15     976
#define DPR_OFFSET_PEAK_FE16     978

#define DPR_OFFSET_PEAK_I9       1008
#define DPR_OFFSET_PEAK_I10      1012
#define DPR_OFFSET_PEAK_I11      1016
#define DPR_OFFSET_PEAK_I12      1020
#define DPR_OFFSET_PEAK_I13      1024
#define DPR_OFFSET_PEAK_I14      1028
#define DPR_OFFSET_PEAK_I15      1032
#define DPR_OFFSET_PEAK_I16      1036

//#define DPR_OFFSET_BTC_MODE      982
#define GS_DISABLED             0
#define GS_RESET                1
#define GS_ESTOP                2
#define GS_STOPPED              3
#define GS_RUNNING              4
//#define GS_HOMING             5
#define GS_HOMING_ALIGN         5
//#define GS_SETCOUNT           6
#define GS_PLEASE_WAIT          6
#define GS_GAURD_OPEN           7
#define GS_TIMING_TEST          8
#define GS_PARKING_BLADE        9
#define GS_BLADE_PARKED        10
#define GS_DRUM_PROX_FAULT     11
#define GS_KNIFE_FAULT         12
//#define GS_DRUM_FAULT        11
//#define GS_KNIFE_FAULT       12
#define GS_STARTING            13
#define GS_ESTOP_DISABLED      14
#define GS_RESET_FAULT         15
#define GS_KNIFE_PROX_FAULT    16
#define GS_STOPPING            17
//#define GS_VFD_FAULT         18
#define GS_HOMING_MOTORS       18
//#define GS_FAULT             19
#define GS_MACRO_FAULT         19
#define GS_TRAP_KEY_OFF        20
#define GS_DRUM_FAULT          21
//#define GS_KNIFE_FAULT         22

#define GS_SLICER_DISABLED         0
#define GS_SLICER_RESET            1
#define GS_SLICER_ESTOP            2
#define GS_SLICER_STOPPED          3
#define GS_SLICER_STARTING         4
#define GS_SLICER_STOPPING         5
#define GS_SLICER_AT_SPEED         6
#define GS_SLICER_HOMING           7
#define GS_SLICER_DISCONECT        8
#define GS_SLICER_FAULT            9
#define GS_SLICER_SPEED_CHANGE    10
#define GS_SLICER_HOME_FAULT      11
#define GS_SLICER_BLADE_FAULT     12
#define GS_SLICER_DISCHARGE_FAULT 13
#define GS_SLICER_INCLINE_FAULT   14
#define GS_SLICER_FEED_FAULT      15
#define GS_SLICER_BELEVATOR_FAULT 16


typedef struct tagHELPERPARAM {
	BOOL bRun;
	int nWaitTime;
} HELPERPARAM;

typedef struct tagOPENPMACDATA{
	int   nDevice;
	CPmac Pmac;
	HWND hWnd;
} OPENPMACDATA;

class CHMIView : public CFormView
{
protected: // create from serialization only
	CHMIView();
	DECLARE_DYNCREATE(CHMIView)

public:
	CString m_strLastfault;
	CWnd* m_pLaserWnd;
	bool m_bOnTimerUpdate;
	//bool m_ParkLatch;
	bool m_bFeedJogReverse;
	PROCESS_INFORMATION m_pi;
	PROCESS_INFORMATION m_piMotorUtil;
	bool m_bPaperOutLatch;
	bool m_bWheelUpLatch;
	bool m_bAirOffLatch;
	bool m_bAlarmLatch[MAX_ALARMS];
	bool m_bShuntTempFaultLatch1;
	bool m_bShuntTempFaultLatch2;
	bool m_bShuntTempFaultLatch3;
	bool m_bPmacBusy;
	bool m_bPmacUtilBusy;
    CWnd* m_pSettings;
    CWnd* m_pAlarm1;
    CWnd* m_pAlarm2;
    CWnd* m_pAlarm3;
    CWnd* m_pAlarm4;
    CWnd* m_pAlarm5;
    CWnd* m_pAlarm6;
    CWnd* m_pAlarm7;
    CWnd* m_pAlarm8;
    CWnd* m_pAlarm9;
    CWnd* m_pAlarm10;
    CWnd* m_pAlarm11;
    CWnd* m_pAlarm12;
	BTCDATA m_BtcData;
	//SLICERDATA m_SlicerData;
	CMilWnd* m_pMilWnd;
	CMilWnd* m_pMilWnd2;
	CMilWnd* m_pMilRejectWnd;
	CMilWnd* m_pMilRejectWnd2;

	CIsiLcdDisplay* m_pLedWnd;
	CIsiLcdDisplay* m_pLedWnd2;
	CIsiLcdDisplay* m_pLedWnd3;
	//bool m_bStopLatch;
	int m_nPrevSecond;
	long m_nTotalRunSeconds;
	long m_nPrevTotalRunSeconds;
	long m_nPrevMinute;
	long m_nPrevHour;
	CFont m_fontMed;
	CFont m_fontLarge;
	CFont m_fontExtraLarge;
	int m_nPage;
	int m_nPageHeight;
	//int m_nMinPage;
	//int m_nMaxPage;
	int	m_nScrollPos;
	CStatusboxex m_ctlStatusMainEx;
	CStatusboxex m_ctlStatusMainEx2;
	CStatusboxex m_ctlStatusMainEx3;
	//CGdistatusmain m_ctlMain;
	//CGdistatusmain m_ctlMain2;
	//CGdistatusmain m_ctlMain3;
	CGdistatusmain m_BtcMode;
	CGdistatusmain m_SlicerStatus;
	CGdistatusmain m_SlicerStatus2;
	CGdi_ButtonXL m_ctlStart;
	CGdi_ButtonXL m_ctlStop;
	CGdi_ButtonXL m_ctlStart2;
	CGdi_ButtonXL m_ctlStop2;
	CGdi_ButtonXL m_ctlStart3;
	CGdi_ButtonXL m_ctlStop3;
	CGdi_ButtonXL m_ctlWashMode;
	CGdi_ButtonXL m_ctlRunMode;
	CGdi_ButtonXL m_ctlJogFeedRev;
	CGdi_ButtonXL m_ctlBlower;
	CGdi_ButtonXL m_ctlBelevator;
	CGdi_ButtonXL m_ctlPanic;

	CGdi_ButtonXL m_btnLoadPaper;
	CGdi_ButtonXL m_btnTimingCheck;
	CGdi_ButtonXL m_btnOutputForce;
	CGdi_ButtonXL m_btnOutputForce2;
	CGdi_ButtonXL m_btnOutputForce3;
	CGdi_ButtonXL m_btnFeedUpDn;
	CGdi_ButtonXL m_ctlTTJogFast;
	CGdi_ButtonXL m_ctlTTJogSlow;

	CGdi_ButtonXL m_ctlBladeBrake;

	CGDITedit m_ctlSliceCount;
	//CGDITedit m_ctlSliceCount2;
	CGDITedit m_ctlPaperLenght;
	//CGDITedit m_ctlCountOnPaper;
	//CGDITedit m_ctlCountOnPaper2;
	CHistory     m_FaultHistory;
	bool m_bMotorFaultLatch[16];
	bool m_bMotorWarnLatch[16];
	bool m_bGlobalStatusFaultLatch;
	bool m_bRejectVFDFaultLatch;
	bool m_bExitVFDFaultLatch;
	int m_EIPWriteError;
    static const CString m_HallsBits[16];
	CCriticalSection m_csLatch;
	double m_dbTotalRunSeconds;
	int m_HmiTime;
	bool m_bPmacComLoss;
	//long m_TotalRunSeconds;

public:
	enum{ IDD = IDD_HMI_FORM };

// Attributes
public:
	CHMIDoc* GetDocument() const;

// Operations
public:
	void ScanIO();
	void ScanAlarms();
	void DoClockTimer();
	void DoHMITimer();
	void SetPmacPVariables(CHMIApp* pApp,CPmac* pmac);
	void GetPmacPVariables(CHMIApp* pApp,CPmac* pmac);
	void SetAlignMode(CHMIApp* pApp,BOOL bSave);
	void UpDateHMI();
	void ScrollToPage(int nPage);
	bool CheckPassword();
	bool CheckMasterPassword();
	bool SaveBackUpFile (LPCTSTR lpMsg,ALLSETTINGS* pData);
	bool LoadBackUpFile (LPCTSTR lpMsg,ALLSETTINGS* pData);
	int GetMotorState(LPCTSTR lpName,MOTORDATA* pMtr, unsigned char Halls,bool* pFaultLatch,bool* pWarnLatch);
	LPCTSTR GetHallValue(unsigned char Halls);
	static UINT OpenPmacThreadFunc (LPVOID);


// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
	virtual ~CHMIView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	bool m_bComOn;

	char m_TagNameBTCStatus[256];
	char m_TagNameSlicerStatus[256];
	//CClientEIP m_EIPClient;
	static BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam);


	afx_msg LRESULT OnClearAlarm (WPARAM wParam, LPARAM lParam);
	afx_msg void OnViewHmioptions();
	afx_msg void OnViewSettingsSave();
	afx_msg void OnUpdateSettingsSave(CCmdUI *pCmdUI);
	afx_msg LRESULT OnApplySettings (WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSaveSettings (WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnRestoreSettings (WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnGetPmacVariable (WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnGetPmacMotorPosition (WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnBtcTimingCheck (WPARAM wParam, LPARAM lParam);

	afx_msg LRESULT OnDoPmacCommunications (WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnDoPmacSave (WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnDoHmiSave (WPARAM wParam, LPARAM lParam);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedGotoVision();
	afx_msg void OnBnClickedSysButtons();
	afx_msg void OnBnClickedSysButtons2();
	afx_msg void OnBnClickedGotoHome();
	afx_msg void OnBnClickedHistory();
	afx_msg void OnBnClickedClearPeaks();
	afx_msg void OnToolsSave();
	afx_msg void OnToolsLoad();
	afx_msg void OnBnClickedVisionSettings();
	afx_msg void OnBnClickedUserSettings();
	afx_msg void OnBnClickedDisplaySel1();
	afx_msg void OnBnClickedDisplaySel2();
	afx_msg void OnBnClickedDisplaySel3();
	afx_msg LRESULT OnLoadMaster (WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnLoadUser (WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSaveUser (WPARAM wParam, LPARAM lParam);
	DECLARE_EVENTSINK_MAP()
	void ClickGdiStart();
	void ClickGdiFeedDown();
	void ClickGdiStop();
	void ClickModeWash();
	void ClickModeRun();
	void ClickBlower();
	void ClickBelevator();
	void ClickBtcReset();
	void ClickTimingCheck();
	void ClickLoadPaper();
	afx_msg void OnBnClickedGotoIopage();
	afx_msg void OnBnClickedGotoServos();
	afx_msg void OnBnClickedGotoClean();
	afx_msg void OnBnClickedGotoHome2();
	afx_msg void OnBnClickedGotoHome4();
	afx_msg void OnBnClickedGotoHome3();
	void ClickSliceCount();
	void ClickPaperLength();
	afx_msg void OnBnClickedMotionSettings();
	CGdigagetctrl1 m_PaperRollSize;
	CGdimotorstatusctrl1 m_ctlMotorStatus1;
	CGdimotorstatusctrl1 m_ctlMotorStatus2;
	CGdi_ButtonXL m_ctlBtcReady;
	CGdi_ButtonXL m_ctlBtcReady2;
	void ClickBtcReady();
	void ClickBladeSpeed();
	void ClickAlignOffset();
	void SlicerDischargeSpeed();
	void ClickSliceThickness();
	CGDITedit m_ctlAlignOffset;
	CGDITedit m_ctlSliceThickness;
	CGDITedit m_ctlBladeSpeed;
	CGDITedit m_ctlBladeSpeed2;
	CGDITedit m_ctlDischargeDistOffset;

	CGDITedit m_ctlBusVoltage1;
	CGDITedit m_ctlBusVoltage2;
	CGDITedit m_ctlBusVoltage3;
	CGDITedit m_ctlBladeIGBTTemp;
	CGDITedit m_ctlTotalCurrent;

	CGDITedit m_ctlMtrUVWT1;
	CGDITedit m_ctlMtrUVWT2;
	CGDITedit m_ctlMtrUVWT3;
	CGDITedit m_ctlMtrUVWT4;
	CGDITedit m_ctlMtrUVWT5;
	CGDITedit m_ctlMtrUVWT6;
	CGDITedit m_ctlMtrUVWT7;
	CGDITedit m_ctlMtrUVWT8;

	CGDITedit m_ctlMtrUVWT9;
	CGDITedit m_ctlMtrUVWT10;
	CGDITedit m_ctlMtrUVWT11;
	CGDITedit m_ctlMtrUVWT12;
	CGDITedit m_ctlMtrUVWT13;
	CGDITedit m_ctlMtrUVWT14;
	CGDITedit m_ctlMtrUVWT15;
	CGDITedit m_ctlMtrUVWT16;


	CGDITedit m_TotalSheetCount;
	afx_msg void OnBnClickedSheetCountInc();
	afx_msg void OnBnClickedSheetCountDec();
	//CGDITedit m_ctlSheetCount;
	CGDITedit m_ctlSheetCountShift;
	void ClickSheetCount();
	void ClickSheetCountShift();
	CGdi_ButtonXL m_ctlEstopLED;
	CGdi_ButtonXL m_ctlEstopLED2;
	CGdi_ButtonXL m_ctlFlipperGuard;
	CGdi_ButtonXL m_ctlDrumDoorLED;
	CGdi_ButtonXL m_ctlPaperDoorLED;
	CGdi_ButtonXL m_ctlKnifeDisconnectLED;
	afx_msg void OnBnClickedDisplaySel4();
	afx_msg void OnBnClickedMotionSettings2();
	afx_msg void OnPageHome();
	afx_msg void OnPageDown();
	afx_msg void OnPageUp();
	afx_msg void OnDriveLoad();
	afx_msg void OnBnClickedClearPeaks1();
	afx_msg void OnBnClickedClearPeaks3();
	afx_msg void OnBnClickedClearPeaks2();
	afx_msg void OnBnClickedClearPeaks4();
	afx_msg void OnBnClickedClearPeaks5();
	afx_msg void OnBnClickedClearPeaks6();
	afx_msg void OnBnClickedHistory2();
	CGdiiostatusctrl m_ctlSlicerStatus;
	CGdiiostatusctrl m_ctlInputs;
	CGdiiostatusctrl m_ctlSlicerInputs;

	CGdiiostatusctrl m_ctlFlagInputs;
	CGdiiostatusctrl m_ctlSlicerFlagInputs;

	CGdiiostatusctrl m_ctlOutputs;
	CGdiiostatusctrl m_ctlOutputs2;
	CGdiiostatusctrl m_ctlOutputs3;
	void IoClickedGdiiostatusctrlOutputs(short IoClickedNum);
	void IoClickedGdiiostatusctrlOutputs2(short IoClickedNum);
	void IoClickedGdiiostatusctrlOutputs3(short IoClickedNum);
	void ClickOutputForce();
	void ClickOutputForce2();
	void ClickOutputForce3();
	//afx_msg void OnBnClickedClearFaultLatch();
	afx_msg void OnBnClickedClearPeaks7();
	afx_msg void OnBnClickedClearPeaks8();
	afx_msg void OnBnClickedClearPeaks9();
	afx_msg void OnBnClickedClearEndDetectPeaks();
	CGdiledlightsctrl m_ctlLedTUVW1;
	CGdiledlightsctrl m_ctlLedTUVW2;
	CGdiledlightsctrl m_ctlLedTUVW3;
	CGdiledlightsctrl m_ctlLedTUVW4;
	CGdiledlightsctrl m_ctlLedTUVW5;
	CGdiledlightsctrl m_ctlLedTUVW6;
	CGdiledlightsctrl m_ctlLedTUVW7;
	CGdiledlightsctrl m_ctlLedTUVW8;
	CGdiledlightsctrl m_ctlLedTUVW9;
	CGdiledlightsctrl m_ctlLedTUVW10;
	CGdiledlightsctrl m_ctlLedTUVW11;
	CGdiledlightsctrl m_ctlLedTUVW12;
	CGdiledlightsctrl m_ctlLedTUVW13;
	CGdiledlightsctrl m_ctlLedTUVW14;
	CGdiledlightsctrl m_ctlLedTUVW15;
	CGdiledlightsctrl m_ctlLedTUVW16;
	afx_msg void OnBnClickedShowSherbarPoints();
	afx_msg void OnBnClickedRecordBelly();
	afx_msg void OnBnClickedPlayBelly();
	afx_msg void OnBnClickedStopPlay();
	void MouseDownInfeedReverse(short Button, short Shift, long x, long y);
	void MouseUpInfeedReverse(short Button, short Shift, long x, long y);
	afx_msg void OnBnClickedClearPeaks11();
	afx_msg void OnBnClickedClearPeaks10();
	afx_msg void OnBnClickedClearPeaks12();
	afx_msg void OnBnClickedClearPeaks13();
	afx_msg void OnBnClickedClearPeaks14();
	afx_msg void OnBnClickedClearPeaks15();
	afx_msg void OnBnClickedClearPeaks16();
	void MouseDownGdiJogFast(short Button, short Shift, long x, long y);	
	void BladeBrake(short Button, short Shift, long x, long y);
	void MouseUpGdiJogFast(short Button, short Shift, long x, long y);
	void MouseDownGdiJogSlow(short Button, short Shift, long x, long y);
	void MouseUpGdiJogSlow(short Button, short Shift, long x, long y);
	//afx_msg void OnBnClickedReadPvars();
	afx_msg void OnBnClickedGotoLaser();
	afx_msg void OnBnClickedGotoHome5();
	CGdimultireadoutctrl1 m_ctlReadOutsMtr1;
	CGdimultireadoutctrl1 m_ctlReadOutsMtr2;
	CGdimultireadoutctrl1 m_ctlReadOutsMtr3;
	CGdimultireadoutctrl1 m_ctlReadOutsMtr4;
	CGdimultireadoutctrl1 m_ctlReadOutsMtr5;
	CGdimultireadoutctrl1 m_ctlReadOutsMtr6;
	CGdimultireadoutctrl1 m_ctlReadOutsMtr7;
	CGdimultireadoutctrl1 m_ctlReadOutsMtr8;
	CGdimultireadoutctrl1 m_ctlReadOutsMtr9;
	CGdimultireadoutctrl1 m_ctlReadOutsMtr10;
	CGdimultireadoutctrl1 m_ctlReadOutsMtr11;
	CGdimultireadoutctrl1 m_ctlReadOutsMtr12;
	CGdimultireadoutctrl1 m_ctlReadOutsMtr13;
	CGdimultireadoutctrl1 m_ctlReadOutsMtr14;
	CGdimultireadoutctrl1 m_ctlReadOutsMtr15;
	CGdimultireadoutctrl1 m_ctlReadOutsMtr16;
	void ClickBtcPanic();
	afx_msg void OnBnClickedCheckPhase();
	afx_msg void OnBnClickedUpdatePvars();
	afx_msg void OnBnClickedAxisFaultCodes();
	afx_msg void OnBnClickedDriveFaultCodes();
	afx_msg void OnBnClickedMotorTestUtil();
	afx_msg void OnBnClickedCheckMasterSettings();
};

static UINT HelperThreadFunc (LPVOID);
// The CUIHelperThread class
class CUIHelperThread : public CWinThread
{
    DECLARE_DYNCREATE (CUIHelperThread)
public:
	CUIHelperThread();
	int m_nTime;
    virtual BOOL InitInstance ();
	void SetDelayTime(int DelayTime);
	void ResetTimer();
	void SetMessage(LPCTSTR str);
	void StopTimer();
	void Close(void);
};

// The CMainWindow class
class CProgressWindow : public CFrameWnd
{
public:
	TCHAR m_buffMsg[1024];
	int m_nPos;
	int m_nTime;
	bool m_bReady;
	//CString m_strMessageOld;
	//long m_nUpdateMessage;
	//CEvent m_event;
	//CString m_strMessage;
	CProgressCtrl m_wndProgress;
    CProgressWindow ();
	CProgressWindow (int nTime);
	void ResetTimer(int DelayTime);
	void StopTimer();
	void Close(void);
	void SetMessage(LPCTSTR str);

protected:
    afx_msg void OnLButtonDown (UINT, CPoint);
    DECLARE_MESSAGE_MAP ()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};


#ifndef _DEBUG  // debug version in HMIView.cpp
inline CHMIDoc* CHMIView::GetDocument() const
   { return reinterpret_cast<CHMIDoc*>(m_pDocument); }
#endif

