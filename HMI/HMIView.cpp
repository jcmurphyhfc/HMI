
// HMIView.cpp : implementation of the CHMIView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "HMI.h"
#endif

#include "HMIDoc.h"
#include "HMIView.h"
#include "MainFrm.h"
#include <sys/timeb.h>
#include "FaultHistory.h"
#include "GetName.h"
#include "GetBackupName.h"
#include "UploadDownload.h"
//#include <time.h>

HWND hwndLaserView = NULL;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
IMPLEMENT_DYNCREATE (CUIHelperThread, CWinThread)

CUIHelperThread::CUIHelperThread ()
{
	m_nTime = 0;
	TRACE("\nConstructor CUIHelperThread::CUIHelperThread %d \n",m_nTime);
}

BOOL CUIHelperThread::InitInstance ()
{
	TRACE("CUIHelperThread::InitInstance %d \n",m_nTime);
	//m_pProgressWindow = new CProgressWindow;
    m_pMainWnd = new CProgressWindow(m_nTime);
    m_pMainWnd->ShowWindow (SW_SHOW);
    m_pMainWnd->UpdateWindow ();
    return TRUE;
}

void CUIHelperThread::SetDelayTime(int DelayTime)
{
	TRACE("CUIHelperThread::SetTimer %d \n",m_nTime);
	Sleep(200);	
	//CProgressWindow* pWnd = (CProgressWindow*)m_pMainWnd;
	//pWnd->StartTimer(m_nTime);
	CProgressWindow* pWnd = (CProgressWindow*)m_pMainWnd;
	//if (pWnd==NULL) AfxMessageBox(_T("NULL"));
	//Sleep(200);	
	m_nTime = DelayTime;
	pWnd->ResetTimer(m_nTime);
}
void CUIHelperThread::StopTimer()
{
	CProgressWindow* pWnd = (CProgressWindow*)m_pMainWnd;
	pWnd->StopTimer();
}

void CUIHelperThread::ResetTimer()
{
	CProgressWindow* pWnd = (CProgressWindow*)m_pMainWnd;
	pWnd->ResetTimer(m_nTime);
}

void CUIHelperThread::SetMessage(LPCTSTR str)
{
	CProgressWindow* pWnd = (CProgressWindow*)m_pMainWnd;
	//if (m_pMainWnd == NULL)
	//{
	//	AfxMessageBox(_T("How is this possible?"));
	//	return;
	//}
	pWnd->SetMessage(str);
}

void CUIHelperThread::Close()
{
	//(CProgressWindow*)m_pMainWnd->start
	CProgressWindow* pWnd = (CProgressWindow*)m_pMainWnd;
	pWnd->Close();
}

BEGIN_MESSAGE_MAP (CProgressWindow, CFrameWnd)
    ON_WM_LBUTTONDOWN ()
	ON_WM_CREATE()
	ON_WM_TIMER()
END_MESSAGE_MAP ()

CProgressWindow::CProgressWindow ()
{
	m_bReady = false;
	m_nTime = 0;
	lstrcpy(m_buffMsg,_T ("Please Wait..."));
	TRACE("Default constructor... CProgressWindow::CProgressWindow %d \n",m_nTime);
    Create (NULL, _T ("Please Wait..."));
}
CProgressWindow::CProgressWindow (int nTime)
{
	m_bReady = false;
	m_nTime = nTime;
	lstrcpy(m_buffMsg,_T ("Please Wait..."));
	//m_strMessage = _T (""); 
	TRACE("CProgressWindow::CProgressWindow %d \n",m_nTime);
    Create (NULL, _T ("Please Wait..."));
}

void CProgressWindow::SetMessage(LPCTSTR str)
{
	//::InterlockedIncrement (&m_nUpdateMessage);
	lstrcpy(m_buffMsg,str);
	TRACE(_T("\n MessageBuffer= %s \n"),m_buffMsg);
	//m_event.SetEvent();
}

void CProgressWindow::OnLButtonDown (UINT nFlags, CPoint point)
{
    PostMessage (WM_CLOSE, 0, 0);
}
BOOL CProgressWindow::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style = WS_DLGFRAME;
	cs.dwExStyle = WS_EX_TOPMOST;
	cs.x = 0;
	cs.y = 0;
	cs.cx = 300;
	cs.cy =  75;
	TRACE("CProgressWindow::PreCreateWindow %d \n",m_nTime);

	return CFrameWnd::PreCreateWindow(cs);
}

int CProgressWindow::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	CenterWindow();
	//SetWindowPos (&wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

	CRect rect;
	GetClientRect(&rect);
	//rect.InflateRect(0,0,-50,0);
	m_wndProgress.Create (WS_CHILD | WS_VISIBLE | WS_BORDER,rect, this, 1);
	TRACE("CProgressWindow::OnCreate %d \n",m_nTime);
	//m_wndProgress.SetRange(0,m_nTime);
	m_wndProgress.SetRange(0,100);
	m_nPos = 0;
	//SetTimer(1,100,NULL);
	m_bReady = true;


	return 0;
}
void CProgressWindow::OnTimer(UINT_PTR nIDEvent)
{
	//CFrameWnd::OnTimer(nIDEvent);
	//TRACE("CProgressWindow::OnTimer Pos: %d Time: %d \n",m_nPos,m_nTime);
	if (m_nTime==0)
		return;

	// Message Update
	CString strMessage;
	strMessage = m_buffMsg;
	SetWindowText(strMessage);

	//if (::WaitForSingleObject (m_event.m_hObject, 0) == WAIT_OBJECT_0)
	//{
	//	// The event is signaled.
	//	TRACE(_T("The event is signaled. \n"));
	//}
	//else 
	//{
	//	// The event is not signaled.
	//	TRACE(_T("The event is NOT signaled. \n"));
	//}
	m_nPos += 100;	
	m_wndProgress.SetPos(m_nPos);
	if (m_nPos > m_nTime)
	{
		KillTimer(1);
		//PostMessage (WM_CLOSE, 0, 0);
	}

}
void CProgressWindow::ResetTimer(int DelayTime)
{
	//if (!m_bReady) return;

	TRACE("CProgressWindow::ResetTimer %d \n",DelayTime);
	KillTimer(1);
	m_nTime = DelayTime;
	m_nPos = 0;
	m_wndProgress.SetPos(m_nPos);
	m_wndProgress.SetRange(0,m_nTime);
	SetForegroundWindow();
	SetTimer(1,100,NULL);
}
void CProgressWindow::StopTimer()
{
	KillTimer(1);
	m_wndProgress.SetPos(m_nTime);
}
void CProgressWindow::Close()
{
    PostMessage (WM_CLOSE, 0, 0);
}

// CHMIView
IMPLEMENT_DYNCREATE(CHMIView, CFormView)

BEGIN_MESSAGE_MAP(CHMIView, CFormView)
	ON_MESSAGE (WM_DO_PMAC_COMMUNICATONS, OnDoPmacCommunications)
	ON_MESSAGE (WM_VISION_SETTINGS_APPLY, OnApplySettings)
	ON_MESSAGE (WM_CLEAR_ALARM, OnClearAlarm)
	ON_MESSAGE (WM_VISION_SETTINGS_SAVE, OnSaveSettings)
	ON_MESSAGE (WM_VISION_SETTINGS_RESTORE, OnRestoreSettings)	
	ON_MESSAGE (WM_GET_PMAC_VARIABLE, OnGetPmacVariable)
	ON_MESSAGE (WM_GET_PMAC_MOTOR_POS, OnGetPmacMotorPosition)
	ON_MESSAGE (WM_BTC_TIMING_CHECK, OnBtcTimingCheck)
	ON_MESSAGE (WM_USER_PMAC_SAVE, OnDoPmacSave)
	ON_MESSAGE (WM_USER_HMI_SAVE, OnDoHmiSave)
	ON_WM_TIMER()
	ON_WM_SIZE()
	ON_UPDATE_COMMAND_UI(ID_SETTINGS_SAVE, &CHMIView::OnUpdateSettingsSave)	
	ON_COMMAND(ID_WINDOW_OPTIONS, &CHMIView::OnViewHmioptions)
	ON_COMMAND(ID_SETTINGS_SAVE, &CHMIView::OnViewSettingsSave)
	ON_COMMAND(ID_BACKUP_FILE, &CHMIView::OnToolsSave)
	ON_COMMAND(ID_LOAD_FILE, &CHMIView::OnToolsLoad)
	ON_COMMAND(ID_PAGE_HOME, &CHMIView::OnPageHome)
	ON_COMMAND(ID_PAGE_DOWN, &CHMIView::OnPageDown)
	ON_COMMAND(ID_PAGE_UP, &CHMIView::OnPageUp)
	ON_COMMAND(ID_DRIVE_LOAD, &CHMIView::OnDriveLoad)
	ON_BN_CLICKED(IDC_GOTO_VISION, &CHMIView::OnBnClickedGotoVision)
	ON_BN_CLICKED(IDC_SYS_BUTTONS, &CHMIView::OnBnClickedSysButtons)
	ON_BN_CLICKED(IDC_SYS_BUTTONS2, &CHMIView::OnBnClickedSysButtons2)
	ON_BN_CLICKED(IDC_GOTO_HOME, &CHMIView::OnBnClickedGotoHome)
	ON_BN_CLICKED(IDC_CLEAR_PEAKS, &CHMIView::OnBnClickedClearPeaks)
	ON_BN_CLICKED(IDC_HISTORY, &CHMIView::OnBnClickedHistory)	
	ON_BN_CLICKED(IDC_VISION_SETTINGS, &CHMIView::OnBnClickedVisionSettings)
	ON_BN_CLICKED(IDC_VISION_SETTINGS2, &CHMIView::OnBnClickedUserSettings)
	ON_BN_CLICKED(IDC_DISPLAY_SEL1, &CHMIView::OnBnClickedDisplaySel1)
	ON_BN_CLICKED(IDC_DISPLAY_SEL2, &CHMIView::OnBnClickedDisplaySel2)
	ON_BN_CLICKED(IDC_DISPLAY_SEL3, &CHMIView::OnBnClickedDisplaySel3)
	ON_BN_CLICKED(IDC_DISPLAY_SEL4, &CHMIView::OnBnClickedDisplaySel4)
	ON_BN_CLICKED(IDC_GOTO_IOPAGE, &CHMIView::OnBnClickedGotoIopage)
	ON_BN_CLICKED(IDC_GOTO_SERVOS, &CHMIView::OnBnClickedGotoServos)
	ON_BN_CLICKED(IDC_GOTO_CLEAN, &CHMIView::OnBnClickedGotoClean)
	ON_BN_CLICKED(IDC_GOTO_HOME2, &CHMIView::OnBnClickedGotoHome2)
	ON_BN_CLICKED(IDC_GOTO_HOME4, &CHMIView::OnBnClickedGotoHome4)
	ON_BN_CLICKED(IDC_GOTO_HOME3, &CHMIView::OnBnClickedGotoHome3)
	ON_BN_CLICKED(IDC_MOTION_SETTINGS, &CHMIView::OnBnClickedMotionSettings)
	ON_BN_CLICKED(IDC_SHEET_COUNT_INC, &CHMIView::OnBnClickedSheetCountInc)
	ON_BN_CLICKED(IDC_SHEET_COUNT_DEC, &CHMIView::OnBnClickedSheetCountDec)
	ON_BN_CLICKED(IDC_HISTORY2, &CHMIView::OnBnClickedHistory2)	
	ON_BN_CLICKED(IDC_CLEAR_ENDPEAKS, &CHMIView::OnBnClickedClearEndDetectPeaks)
	ON_BN_CLICKED(IDC_SHOW_SHERBAR_POINTS, &CHMIView::OnBnClickedShowSherbarPoints)
	ON_BN_CLICKED(IDC_RECORD_BELLY, &CHMIView::OnBnClickedRecordBelly)
	ON_BN_CLICKED(IDC_PLAY_BELLY, &CHMIView::OnBnClickedPlayBelly)
	ON_BN_CLICKED(IDC_STOP_PLAY, &CHMIView::OnBnClickedStopPlay)
	ON_BN_CLICKED(IDC_CLEAR_PEAKS1, &CHMIView::OnBnClickedClearPeaks1)
	ON_BN_CLICKED(IDC_CLEAR_PEAKS3, &CHMIView::OnBnClickedClearPeaks3)
	ON_BN_CLICKED(IDC_CLEAR_PEAKS2, &CHMIView::OnBnClickedClearPeaks2)
	ON_BN_CLICKED(IDC_CLEAR_PEAKS4, &CHMIView::OnBnClickedClearPeaks4)
	ON_BN_CLICKED(IDC_CLEAR_PEAKS5, &CHMIView::OnBnClickedClearPeaks5)
	ON_BN_CLICKED(IDC_CLEAR_PEAKS6, &CHMIView::OnBnClickedClearPeaks6)
	ON_BN_CLICKED(IDC_CLEAR_PEAKS7, &CHMIView::OnBnClickedClearPeaks7)
	ON_BN_CLICKED(IDC_CLEAR_PEAKS8, &CHMIView::OnBnClickedClearPeaks8)
	ON_BN_CLICKED(IDC_CLEAR_PEAKS9, &CHMIView::OnBnClickedClearPeaks9)
	ON_BN_CLICKED(IDC_CLEAR_PEAKS10, &CHMIView::OnBnClickedClearPeaks10)
	ON_BN_CLICKED(IDC_CLEAR_PEAKS11, &CHMIView::OnBnClickedClearPeaks11)
	ON_BN_CLICKED(IDC_CLEAR_PEAKS12, &CHMIView::OnBnClickedClearPeaks12)
	ON_BN_CLICKED(IDC_CLEAR_PEAKS13, &CHMIView::OnBnClickedClearPeaks13)
	ON_BN_CLICKED(IDC_CLEAR_PEAKS14, &CHMIView::OnBnClickedClearPeaks14)
	ON_BN_CLICKED(IDC_CLEAR_PEAKS15, &CHMIView::OnBnClickedClearPeaks15)
	ON_BN_CLICKED(IDC_CLEAR_PEAKS16, &CHMIView::OnBnClickedClearPeaks16)
	ON_BN_CLICKED(IDC_GOTO_HOME5, &CHMIView::OnBnClickedGotoHome5)
	ON_BN_CLICKED(IDC_CHECK_PHASE, &CHMIView::OnBnClickedCheckPhase)
	ON_BN_CLICKED(IDC_UPDATE_PVARS, &CHMIView::OnBnClickedUpdatePvars)
	ON_BN_CLICKED(IDC_AXIS_FAULT_CODES, &CHMIView::OnBnClickedAxisFaultCodes)
	ON_BN_CLICKED(IDC_DRIVE_FAULT_CODES, &CHMIView::OnBnClickedDriveFaultCodes)
	ON_BN_CLICKED(IDC_MOTOR_TEST_UTIL, &CHMIView::OnBnClickedMotorTestUtil)
	ON_BN_CLICKED(IDC_CHECK_MASTER_SETTINGS, &CHMIView::OnBnClickedCheckMasterSettings)
	ON_MESSAGE (WM_SETTINGS_LOAD_MASTER, OnLoadMaster)
	ON_MESSAGE (WM_SETTINGS_LOAD_USER, OnLoadUser)
	ON_MESSAGE (WM_SETTINGS_SAVE_USER, OnSaveUser)
END_MESSAGE_MAP()

//======================================================================================================//
// Function Name: HelperThreadFunc (LPVOID pParam)                                                      //
//                                                                                                      //
//======================================================================================================//
UINT HelperThreadFunc (LPVOID pParam)                                                                      
{            
	HELPERPARAM* pParm = (HELPERPARAM*) pParam;
	CWnd* pWnd = DlgWait(pParm->nWaitTime);
	while (pParm->bRun)
	{
		Sleep(50);
		pWnd->SendMessage(WM_WAIT_DLG_UPDATE_TIMER,0,0);
	}
	pWnd->DestroyWindow();
	TRACE("Helper Thread Exit\n");
	return 0;                                                                                                       
}

// CHMIView construction/destruction
CHMIView::CHMIView()
	: CFormView(CHMIView::IDD)
{
	//m_bStopLatch = false;
	m_bPmacComLoss = false;
	m_nScrollPos = 0;
	m_pSettings = NULL;
	m_pAlarm1 = NULL;
	m_pAlarm2 = NULL;
	m_pAlarm3 = NULL;
	m_pAlarm4 = NULL;
	m_pAlarm5 = NULL;
	m_pAlarm6 = NULL;
	m_pAlarm7 = NULL;
	m_pAlarm8 = NULL;
	m_pAlarm9 = NULL;
	m_pAlarm10 = NULL;
	m_pAlarm11 = NULL;
	m_pAlarm12 = NULL;
	//m_pDlg = NULL;
	m_bPmacBusy = false;
	m_bPmacUtilBusy = false;
	m_pi.hProcess  = NULL;
	m_piMotorUtil.hProcess  = NULL;
	
	m_EIPWriteError = 0;
	m_bPaperOutLatch = false;
	m_bWheelUpLatch = false;
	m_bFeedJogReverse = false;
	m_bAirOffLatch = false;
	for (int i=0;i<MAX_ALARMS;i++)
	{
		m_bAlarmLatch[i] = false;
	}

	//m_ParkLatch = false;
	m_bOnTimerUpdate = false;
	m_pLaserWnd = NULL;
	m_bShuntTempFaultLatch1 = false;	
	m_bShuntTempFaultLatch2 = false;	
	m_bShuntTempFaultLatch3 = false;	
	m_bComOn = false;

}

CHMIView::~CHMIView()
{
}

void CHMIView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATUSBOXEX, m_ctlStatusMainEx);
	DDX_Control(pDX, IDC_STATUSBOXEX2, m_ctlStatusMainEx2);
	DDX_Control(pDX, IDC_STATUSBOXEX3, m_ctlStatusMainEx3);
	//DDX_Control(pDX, IDC_STATUSBOXMAIN, m_ctlMain);
	//DDX_Control(pDX, IDC_STATUSBOXMAIN2, m_ctlMain2);
	//DDX_Control(pDX, IDC_STATUSBOXMAIN3, m_ctlMain3);
	DDX_Control(pDX, IDC_GDI_START, m_ctlStart);
	DDX_Control(pDX, IDC_GDI_START2, m_ctlStart2);
	DDX_Control(pDX, IDC_GDI_START3, m_ctlStart3);
	DDX_Control(pDX, IDC_GDI_STOP, m_ctlStop);
	DDX_Control(pDX, IDC_GDI_STOP2, m_ctlStop2);
	DDX_Control(pDX, IDC_GDI_STOP3, m_ctlStop3);
	DDX_Control(pDX, IDC_INFEED_DOWN, m_btnFeedUpDn);
	DDX_Control(pDX, IDC_STATUS_BTCMODE, m_BtcMode);
	DDX_Control(pDX, IDC_STATUS_BTCMODE2, m_SlicerStatus);
	DDX_Control(pDX, IDC_STATUS_BTCMODE3, m_SlicerStatus2);
	DDX_Control(pDX, IDC_MODE_WASH, m_ctlWashMode);
	DDX_Control(pDX, IDC_MODE_RUN, m_ctlRunMode);
	DDX_Control(pDX, IDC_INFEED_REVERSE, m_ctlJogFeedRev);
	DDX_Control(pDX, IDC_BLOWER, m_ctlBlower);
	DDX_Control(pDX, IDC_BELEVATOR, m_ctlBelevator);

	DDX_Control(pDX, IDC_GDI_JOG_FAST, m_ctlTTJogFast);
	DDX_Control(pDX, IDC_GDI_BLADE_BRAKE, m_ctlBladeBrake);

	DDX_Control(pDX, IDC_GDI_JOG_SLOW, m_ctlTTJogSlow);

	DDX_Control(pDX, IDC_LOAD_PAPER, m_btnLoadPaper);

	DDX_Control(pDX, IDC_TIMING_CHECK, m_btnTimingCheck);
	DDX_Control(pDX, IDC_OUTPUT_FORCE, m_btnOutputForce);
	DDX_Control(pDX, IDC_OUTPUT_FORCE2, m_btnOutputForce2);
	DDX_Control(pDX, IDC_OUTPUT_FORCE3, m_btnOutputForce3);
	DDX_Control(pDX, IDC_SLICE_COUNT, m_ctlSliceCount);
	//DDX_Control(pDX, IDC_SLICE_COUNT2, m_ctlSliceCount2);
	DDX_Control(pDX, IDC_PAPER_LENGTH, m_ctlPaperLenght);
	DDX_Control(pDX, IDC_GDIGAGETCTRL1, m_PaperRollSize);
	DDX_Control(pDX, IDC_GDIMOTORSTATUSCTRL1, m_ctlMotorStatus1);
	DDX_Control(pDX, IDC_GDIMOTORSTATUSCTRL2, m_ctlMotorStatus2);
	DDX_Control(pDX, IDC_BTC_READY, m_ctlBtcReady);
	DDX_Control(pDX, IDC_BTC_READY2, m_ctlBtcReady2);
	DDX_Control(pDX, IDC_ALIGN_OFFSET, m_ctlAlignOffset);
	DDX_Control(pDX, IDC_SLICE_THICKNESS, m_ctlSliceThickness);
	DDX_Control(pDX, IDC_BLADE_SPEED, m_ctlBladeSpeed);
	DDX_Control(pDX, IDC_BLADE_SPEED2, m_ctlBladeSpeed2);
	DDX_Control(pDX, IDC_BLADE_SPEED3, m_ctlDischargeDistOffset);


	// Position
	//DDX_Control(pDX, IDC_GDITEDITCTRL_POS1, m_ctlMtrPos1);
	//DDX_Control(pDX, IDC_GDITEDITCTRL_POS2, m_ctlMtrPos2);
	//DDX_Control(pDX, IDC_GDITEDITCTRL_POS3, m_ctlMtrPos3);
	//DDX_Control(pDX, IDC_GDITEDITCTRL_POS4, m_ctlMtrPos4);
	//DDX_Control(pDX, IDC_GDITEDITCTRL_POS5, m_ctlMtrPos5);
	//DDX_Control(pDX, IDC_GDITEDITCTRL_POS6, m_ctlMtrPos6);
	//DDX_Control(pDX, IDC_GDITEDITCTRL_POS7, m_ctlMtrPos7);
	//DDX_Control(pDX, IDC_GDITEDITCTRL_POS8, m_ctlMtrPos8);
	//DDX_Control(pDX, IDC_GDITEDITCTRL_POS9, m_ctlMtrPos9);
	//DDX_Control(pDX, IDC_GDITEDITCTRL_POS10, m_ctlMtrPos10);
	//DDX_Control(pDX, IDC_GDITEDITCTRL_POS11, m_ctlMtrPos11);
	//DDX_Control(pDX, IDC_GDITEDITCTRL_POS12, m_ctlMtrPos12);
	//DDX_Control(pDX, IDC_GDITEDITCTRL_POS13, m_ctlMtrPos13);
	//DDX_Control(pDX, IDC_GDITEDITCTRL_POS14, m_ctlMtrPos14);
	//DDX_Control(pDX, IDC_GDITEDITCTRL_POS15, m_ctlMtrPos15);
	//DDX_Control(pDX, IDC_GDITEDITCTRL_POS16, m_ctlMtrPos16);


	DDX_Control(pDX, IDC_GDITEDIT_BUS_VOLTAGE1, m_ctlBusVoltage1);
	DDX_Control(pDX, IDC_GDITEDIT_BUS_VOLTAGE2, m_ctlBusVoltage2);
	DDX_Control(pDX, IDC_GDITEDIT_BUS_VOLTAGE3, m_ctlBusVoltage3);
	DDX_Control(pDX, IDC_GDITEDIT_IGBT_TEMP, m_ctlBladeIGBTTemp);
	DDX_Control(pDX, IDC_GDITEDIT_TOTAL_AMPS, m_ctlTotalCurrent);	


	// Velocity
	//DDX_Control(pDX, IDC_GDITEDITCTRL_VEL1, m_ctlMtrPosVEL1);
	//DDX_Control(pDX, IDC_GDITEDITCTRL_VEL2, m_ctlMtrPosVEL2);
	//DDX_Control(pDX, IDC_GDITEDITCTRL_VEL3, m_ctlMtrPosVEL3);
	//DDX_Control(pDX, IDC_GDITEDITCTRL_VEL4, m_ctlMtrPosVEL4);
	//DDX_Control(pDX, IDC_GDITEDITCTRL_VEL5, m_ctlMtrPosVEL5);
	//DDX_Control(pDX, IDC_GDITEDITCTRL_VEL6, m_ctlMtrPosVEL6);
	//DDX_Control(pDX, IDC_GDITEDITCTRL_VEL7, m_ctlMtrPosVEL7);
	//DDX_Control(pDX, IDC_GDITEDITCTRL_VEL8, m_ctlMtrPosVEL8);
	//DDX_Control(pDX, IDC_GDITEDITCTRL_VEL9, m_ctlMtrPosVEL9);
	//DDX_Control(pDX, IDC_GDITEDITCTRL_VEL10, m_ctlMtrPosVEL10);
	//DDX_Control(pDX, IDC_GDITEDITCTRL_VEL11, m_ctlMtrPosVEL11);
	//DDX_Control(pDX, IDC_GDITEDITCTRL_VEL12, m_ctlMtrPosVEL12);
	//DDX_Control(pDX, IDC_GDITEDITCTRL_VEL13, m_ctlMtrPosVEL13);
	//DDX_Control(pDX, IDC_GDITEDITCTRL_VEL14, m_ctlMtrPosVEL14);

	//// FE
	//DDX_Control(pDX, IDC_GDITEDITCTRL_FE1, m_ctlMtrPosFE1);
	//DDX_Control(pDX, IDC_GDITEDITCTRL_FE2, m_ctlMtrPosFE2);
	//DDX_Control(pDX, IDC_GDITEDITCTRL_FE3, m_ctlMtrPosFE3);
	//DDX_Control(pDX, IDC_GDITEDITCTRL_FE4, m_ctlMtrPosFE4);
	//DDX_Control(pDX, IDC_GDITEDITCTRL_FE5, m_ctlMtrPosFE5);
	//DDX_Control(pDX, IDC_GDITEDITCTRL_FE6, m_ctlMtrPosFE6);
	//DDX_Control(pDX, IDC_GDITEDITCTRL_FE7, m_ctlMtrPosFE7);
	//DDX_Control(pDX, IDC_GDITEDITCTRL_FE8, m_ctlMtrPosFE8);
	//DDX_Control(pDX, IDC_GDITEDITCTRL_FE9, m_ctlMtrPosFE9);
	//DDX_Control(pDX, IDC_GDITEDITCTRL_FE10, m_ctlMtrPosFE10);
	//DDX_Control(pDX, IDC_GDITEDITCTRL_FE11, m_ctlMtrPosFE11);
	//DDX_Control(pDX, IDC_GDITEDITCTRL_FE12, m_ctlMtrPosFE12);
	//DDX_Control(pDX, IDC_GDITEDITCTRL_FE13, m_ctlMtrPosFE13);
	//DDX_Control(pDX, IDC_GDITEDITCTRL_FE14, m_ctlMtrPosFE14);

	//// FE Max
	//DDX_Control(pDX, IDC_GDITEDITCTRL_MAX_FE1, m_ctlMtrPosMaxFE1);
	//DDX_Control(pDX, IDC_GDITEDITCTRL_MAX_FE2, m_ctlMtrPosMaxFE2);
	//DDX_Control(pDX, IDC_GDITEDITCTRL_MAX_FE3, m_ctlMtrPosMaxFE3);
	//DDX_Control(pDX, IDC_GDITEDITCTRL_MAX_FE4, m_ctlMtrPosMaxFE4);
	//DDX_Control(pDX, IDC_GDITEDITCTRL_MAX_FE5, m_ctlMtrPosMaxFE5);
	//DDX_Control(pDX, IDC_GDITEDITCTRL_MAX_FE6, m_ctlMtrPosMaxFE6);
	//DDX_Control(pDX, IDC_GDITEDITCTRL_MAX_FE7, m_ctlMtrPosMaxFE7);
	//DDX_Control(pDX, IDC_GDITEDITCTRL_MAX_FE8, m_ctlMtrPosMaxFE8);
	//DDX_Control(pDX, IDC_GDITEDITCTRL_MAX_FE9, m_ctlMtrPosMaxFE9);
	//DDX_Control(pDX, IDC_GDITEDITCTRL_MAX_FE10, m_ctlMtrPosMaxFE10);
	//DDX_Control(pDX, IDC_GDITEDITCTRL_MAX_FE11, m_ctlMtrPosMaxFE11);
	//DDX_Control(pDX, IDC_GDITEDITCTRL_MAX_FE12, m_ctlMtrPosMaxFE12);
	//DDX_Control(pDX, IDC_GDITEDITCTRL_MAX_FE13, m_ctlMtrPosMaxFE13);
	//DDX_Control(pDX, IDC_GDITEDITCTRL_MAX_FE14, m_ctlMtrPosMaxFE14);

	//// Amps
	//DDX_Control(pDX, IDC_GDITEDITCTRL_CURRENT1, m_ctlMtrAmps1);
	//DDX_Control(pDX, IDC_GDITEDITCTRL_CURRENT2, m_ctlMtrAmps2);
	//DDX_Control(pDX, IDC_GDITEDITCTRL_CURRENT3, m_ctlMtrAmps3);
	//DDX_Control(pDX, IDC_GDITEDITCTRL_CURRENT4, m_ctlMtrAmps4);
	//DDX_Control(pDX, IDC_GDITEDITCTRL_CURRENT5, m_ctlMtrAmps5);
	//DDX_Control(pDX, IDC_GDITEDITCTRL_CURRENT6, m_ctlMtrAmps6);
	//DDX_Control(pDX, IDC_GDITEDITCTRL_CURRENT7, m_ctlMtrAmps7);
	//DDX_Control(pDX, IDC_GDITEDITCTRL_CURRENT8, m_ctlMtrAmps8);
	//DDX_Control(pDX, IDC_GDITEDITCTRL_CURRENT9, m_ctlMtrAmps9);
	//DDX_Control(pDX, IDC_GDITEDITCTRL_CURRENT10, m_ctlMtrAmps10);
	//DDX_Control(pDX, IDC_GDITEDITCTRL_CURRENT11, m_ctlMtrAmps11);
	//DDX_Control(pDX, IDC_GDITEDITCTRL_CURRENT12, m_ctlMtrAmps12);
	//DDX_Control(pDX, IDC_GDITEDITCTRL_CURRENT13, m_ctlMtrAmps13);
	//DDX_Control(pDX, IDC_GDITEDITCTRL_CURRENT14, m_ctlMtrAmps14);

	//// Amps Max
	//DDX_Control(pDX, IDC_GDITEDITCTRL_PEAK_CURRENT1, m_ctlMtrAmpsMax1);
	//DDX_Control(pDX, IDC_GDITEDITCTRL_PEAK_CURRENT2, m_ctlMtrAmpsMax2);
	//DDX_Control(pDX, IDC_GDITEDITCTRL_PEAK_CURRENT3, m_ctlMtrAmpsMax3);
	//DDX_Control(pDX, IDC_GDITEDITCTRL_PEAK_CURRENT4, m_ctlMtrAmpsMax4);
	//DDX_Control(pDX, IDC_GDITEDITCTRL_PEAK_CURRENT5, m_ctlMtrAmpsMax5);
	//DDX_Control(pDX, IDC_GDITEDITCTRL_PEAK_CURRENT6, m_ctlMtrAmpsMax6);
	//DDX_Control(pDX, IDC_GDITEDITCTRL_PEAK_CURRENT7, m_ctlMtrAmpsMax7);
	//DDX_Control(pDX, IDC_GDITEDITCTRL_PEAK_CURRENT8, m_ctlMtrAmpsMax8);
	//DDX_Control(pDX, IDC_GDITEDITCTRL_PEAK_CURRENT9, m_ctlMtrAmpsMax9);
	//DDX_Control(pDX, IDC_GDITEDITCTRL_PEAK_CURRENT10, m_ctlMtrAmpsMax10);

	//DDX_Control(pDX, IDC_GDITEDITCTRL_PEAK_CURRENT11, m_ctlMtrAmpsMax11);
	//DDX_Control(pDX, IDC_GDITEDITCTRL_PEAK_CURRENT12, m_ctlMtrAmpsMax12);
	//DDX_Control(pDX, IDC_GDITEDITCTRL_PEAK_CURRENT13, m_ctlMtrAmpsMax13);
	//DDX_Control(pDX, IDC_GDITEDITCTRL_PEAK_CURRENT14, m_ctlMtrAmpsMax14);

	// Led UVW
	DDX_Control(pDX, IDC_GDILEDLIGHTSCTRL, m_ctlLedTUVW1);
	DDX_Control(pDX, IDC_GDILEDLIGHTSCTRL2, m_ctlLedTUVW2);
	DDX_Control(pDX, IDC_GDILEDLIGHTSCTRL3, m_ctlLedTUVW3);
	DDX_Control(pDX, IDC_GDILEDLIGHTSCTRL4, m_ctlLedTUVW4);
	DDX_Control(pDX, IDC_GDILEDLIGHTSCTRL5, m_ctlLedTUVW5);
	DDX_Control(pDX, IDC_GDILEDLIGHTSCTRL6, m_ctlLedTUVW6);
	DDX_Control(pDX, IDC_GDILEDLIGHTSCTRL7, m_ctlLedTUVW7);
	DDX_Control(pDX, IDC_GDILEDLIGHTSCTRL8, m_ctlLedTUVW8);
	DDX_Control(pDX, IDC_GDILEDLIGHTSCTRL9, m_ctlLedTUVW9);
	DDX_Control(pDX, IDC_GDILEDLIGHTSCTRL10, m_ctlLedTUVW10);

	DDX_Control(pDX, IDC_GDILEDLIGHTSCTRL11, m_ctlLedTUVW11);
	DDX_Control(pDX, IDC_GDILEDLIGHTSCTRL12, m_ctlLedTUVW12);
	DDX_Control(pDX, IDC_GDILEDLIGHTSCTRL13, m_ctlLedTUVW13);
	DDX_Control(pDX, IDC_GDILEDLIGHTSCTRL14, m_ctlLedTUVW14);
	DDX_Control(pDX, IDC_GDILEDLIGHTSCTRL15, m_ctlLedTUVW15);
	DDX_Control(pDX, IDC_GDILEDLIGHTSCTRL16, m_ctlLedTUVW16);

	// UVW State
	DDX_Control(pDX, IDC_GDITEDITCTRL_UVW1, m_ctlMtrUVWT1);
	DDX_Control(pDX, IDC_GDITEDITCTRL_UVW2, m_ctlMtrUVWT2);
	DDX_Control(pDX, IDC_GDITEDITCTRL_UVW3, m_ctlMtrUVWT3);
	DDX_Control(pDX, IDC_GDITEDITCTRL_UVW4, m_ctlMtrUVWT4);
	DDX_Control(pDX, IDC_GDITEDITCTRL_UVW5, m_ctlMtrUVWT5);
	DDX_Control(pDX, IDC_GDITEDITCTRL_UVW6, m_ctlMtrUVWT6);
	DDX_Control(pDX, IDC_GDITEDITCTRL_UVW7, m_ctlMtrUVWT7);
	DDX_Control(pDX, IDC_GDITEDITCTRL_UVW8, m_ctlMtrUVWT8);
	DDX_Control(pDX, IDC_GDITEDITCTRL_UVW9, m_ctlMtrUVWT9);
	DDX_Control(pDX, IDC_GDITEDITCTRL_UVW10, m_ctlMtrUVWT10);

	DDX_Control(pDX, IDC_GDITEDITCTRL_UVW11, m_ctlMtrUVWT11);
	DDX_Control(pDX, IDC_GDITEDITCTRL_UVW12, m_ctlMtrUVWT12);
	DDX_Control(pDX, IDC_GDITEDITCTRL_UVW13, m_ctlMtrUVWT13);
	DDX_Control(pDX, IDC_GDITEDITCTRL_UVW14, m_ctlMtrUVWT14);
	DDX_Control(pDX, IDC_GDITEDITCTRL_UVW15, m_ctlMtrUVWT15);
	DDX_Control(pDX, IDC_GDITEDITCTRL_UVW16, m_ctlMtrUVWT16);

	DDX_Control(pDX, IDC_TOTAL_SHEET_COUNT, m_TotalSheetCount);
	//DDX_Control(pDX, IDC_SHEET_COUNT, m_ctlSheetCount);
	DDX_Control(pDX, IDC_SHEET_COUNT_SHIFT, m_ctlSheetCountShift);
	DDX_Control(pDX, IDC_GDIBUTTONXLCTRL_ESTOP, m_ctlEstopLED);
	DDX_Control(pDX, IDC_GDIBUTTONXLCTRL_ESTOP2, m_ctlEstopLED2);
	DDX_Control(pDX, IDC_GDIBUTTONXLCTRL_FLIPPER_GUARD, m_ctlFlipperGuard);


	DDX_Control(pDX, IDC_GDIBUTTONXLCTRL_DRUM_DOOR, m_ctlDrumDoorLED);
	DDX_Control(pDX, IDC_GDIBUTTONXLCTRL_PAPER_DOOR, m_ctlPaperDoorLED);
	DDX_Control(pDX, IDC_GDIBUTTONXLCTRL_KNIFE_DISCONNECT, m_ctlKnifeDisconnectLED);
	DDX_Control(pDX, IDC_GDIIOSTATUSCTRL_SLICER, m_ctlSlicerStatus);
	DDX_Control(pDX, IDC_GDIIOSTATUSCTRL_INPUTS, m_ctlInputs);
	DDX_Control(pDX, IDC_GDIIOSTATUSCTRL_SLICERINPUTS, m_ctlSlicerInputs);

	DDX_Control(pDX, IDC_GDIIOSTATUSCTRL_FLAG_INPUTS, m_ctlFlagInputs);
	DDX_Control(pDX, IDC_GDIIOSTATUSCTRL_SLICER_FLAG_INPUTS, m_ctlSlicerFlagInputs);

	DDX_Control(pDX, IDC_GDIIOSTATUSCTRL_OUTPUTS, m_ctlOutputs);
	DDX_Control(pDX, IDC_GDIIOSTATUSCTRL_SLICER_OUTPUTS, m_ctlOutputs2);
	DDX_Control(pDX, IDC_GDIIOSTATUSCTRL_REJECT_OUTPUTS, m_ctlOutputs3);
	DDX_Control(pDX, IDC_GDIMULTIREADOUTCTRL1, m_ctlReadOutsMtr1);
	DDX_Control(pDX, IDC_GDIMULTIREADOUTCTRL2, m_ctlReadOutsMtr2);
	DDX_Control(pDX, IDC_GDIMULTIREADOUTCTRL3, m_ctlReadOutsMtr3);
	DDX_Control(pDX, IDC_GDIMULTIREADOUTCTRL4, m_ctlReadOutsMtr4);
	DDX_Control(pDX, IDC_GDIMULTIREADOUTCTRL5, m_ctlReadOutsMtr5);
	DDX_Control(pDX, IDC_GDIMULTIREADOUTCTRL6, m_ctlReadOutsMtr6);
	DDX_Control(pDX, IDC_GDIMULTIREADOUTCTRL7, m_ctlReadOutsMtr7);
	DDX_Control(pDX, IDC_GDIMULTIREADOUTCTRL8, m_ctlReadOutsMtr8);
	DDX_Control(pDX, IDC_GDIMULTIREADOUTCTRL9, m_ctlReadOutsMtr9);
	DDX_Control(pDX, IDC_GDIMULTIREADOUTCTRL10, m_ctlReadOutsMtr10);
	DDX_Control(pDX, IDC_GDIMULTIREADOUTCTRL11, m_ctlReadOutsMtr11);
	DDX_Control(pDX, IDC_GDIMULTIREADOUTCTRL12, m_ctlReadOutsMtr12);
	DDX_Control(pDX, IDC_GDIMULTIREADOUTCTRL13, m_ctlReadOutsMtr13);
	DDX_Control(pDX, IDC_GDIMULTIREADOUTCTRL14, m_ctlReadOutsMtr14);
	DDX_Control(pDX, IDC_GDIMULTIREADOUTCTRL15, m_ctlReadOutsMtr15);
	DDX_Control(pDX, IDC_GDIMULTIREADOUTCTRL16, m_ctlReadOutsMtr16);

	DDX_Control(pDX, IDC_BTC_PANIC, m_ctlPanic);

}

BOOL CHMIView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CFormView::PreCreateWindow(cs);
}

void CHMIView::SetPmacPVariables(CHMIApp* pApp,CPmac* pmac)
{
		
	//AfxMessageBox(_T("Set pmac variables "));
	//if (pApp->m_Settings.VisSettings1.SystemEnable == 1)
	//{
	//   pApp->m_Settings.MotionSettings1.dbPvars[1] = 1;
	//}
	//else
	//{
	//   pApp->m_Settings.MotionSettings1.dbPvars[1] = 0;	
	//}

	// Get p-variables
	for (int i=0;i<100;i++)
	{
		pmac->SetVariable(_T('P'),i+1000,pApp->m_Settings.MotionSettings1.dbPvars[i]);
		//TRACE("Set P%d %f \n",i+1000,pApp->m_Settings.MotionSettings1.dbPvars[i]);
	}

}


void CHMIView::SetAlignMode(CHMIApp* pApp,BOOL bSave)
{
	//if (bSave)
	//{
	//	if (pApp->m_Settings.VisSettings4.TrimModeEnable == 0)
	//	{
	//		m_ctlAlignOffset.SetTitleText(_T("Align Offset"));
	//		pApp->m_Settings.VisSettings3.dbAlignOffset = m_ctlAlignOffset.GetValue();
	//		//AfxMessageBox(_T("Save Align offset "));
	//	}
	//	else
	//	{
	//		m_ctlAlignOffset.SetTitleText(_T("Trim Length"));
	//		pApp->m_Settings.VisSettings4.dbTrimLength = m_ctlAlignOffset.GetValue();
	//		//AfxMessageBox(_T("Save  TRIM length"));
	//	}
	//}
	//else
	//{
	//	if (pApp->m_Settings.VisSettings4.TrimModeEnable == 0)
	//	{
	//		m_ctlAlignOffset.SetTitleText(_T("Align Offset"));
	//		m_ctlAlignOffset.SetValue(pApp->m_Settings.VisSettings3.dbAlignOffset);
	//		//AfxMessageBox(_T("Load Align mode to center "));
	//	}
	//	else
	//	{
	//		m_ctlAlignOffset.SetTitleText(_T("Trim Length"));
	//		m_ctlAlignOffset.SetValue(pApp->m_Settings.VisSettings4.dbTrimLength);
	//		//AfxMessageBox(_T("Load Align mode to TRIM "));
	//	}
	//
	//}

	//pmac->SetVariable(_T('P'),i+1000,pApp->m_Settings.MotionSettings1.dbPvars[i]);
	//TRACE("Set P%d %f \n",i+1000,pApp->m_Settings.MotionSettings1.dbPvars[i]);

}

void CHMIView::GetPmacPVariables(CHMIApp* pApp,CPmac* pmac)
{
	// Get p-variables
	double pvar;
	for (int i=0;i<100;i++)
	{
		pmac->GetVariable(_T('P'),i+1000,&pvar);
		pApp->m_Settings.MotionSettings1.dbPvars[i] = pvar;
		TRACE("Get P%d %f \n",i+1000,pApp->m_Settings.MotionSettings1.dbPvars[i]);
	}

}
void CHMIView::OnInitialUpdate()
{
	double dbHours;
	int nMinute;
    int nHour;
	double remaining;
	double dbMin;
	CString str;
	CButton* pBtn;
	CWnd* pWnd;
	CRect rect;
	CHMIApp* pApp = (CHMIApp*)AfxGetApp();
	CPmac* pmac = &pApp->m_pmac;

	// Call the base class
	CFormView::OnInitialUpdate();
	m_strLastfault = _T("NoFault");

	// Set the server buffer
	pApp->m_chat.SetDataBuffer((char*)&m_BtcData,sizeof(BTCDATA));

#ifdef OSCEOLA_LAYOUT
	// IDC_GDIMOTORSTATUSCTRL1
	//m_ctlMotorStatus1.SetTotalMotors(14);
	m_ctlMotorStatus1.SetMotorSelect(3);
	m_ctlMotorStatus1.SetMotorName(_T("4: Flipper"));
	m_ctlMotorStatus1.SetMotorSelect(14);
	m_ctlMotorStatus1.SetMotorName(_T("14: Exit Belt VFD"));
	m_ctlMotorStatus1.SetMotorSelect(15);
	m_ctlMotorStatus1.SetMotorName(_T("15: Reject Belt VFD"));

	m_ctlMotorStatus2.SetMotorSelect(3);
	m_ctlMotorStatus2.SetMotorName(_T("4: Flipper"));
	m_ctlMotorStatus2.SetMotorSelect(14);
	m_ctlMotorStatus2.SetMotorName(_T("14: Exit Belt VFD"));
	m_ctlMotorStatus2.SetMotorSelect(15);
	m_ctlMotorStatus2.SetMotorName(_T("15: Reject Belt VFD"));

	//m_ctlMotorStatus2.SetMotorSelect(14);
	//m_ctlMotorStatus2.SetMotorName(_T(""));
	//m_ctlMotorStatus2.SetMotorSelect(15);
	//m_ctlMotorStatus2.SetMotorName(_T(""));
	//m_ctlMotorStatus2.SetTotalMotors(14);
#else
	m_ctlMotorStatus1.SetTotalMotors(16);
	m_ctlMotorStatus1.SetMotorSelect(3);
	m_ctlMotorStatus1.SetMotorName(_T("4: Exit Belt"));
	m_ctlMotorStatus2.SetMotorSelect(3);
	m_ctlMotorStatus2.SetMotorName(_T("4: Exit Belt"));
	m_ctlMotorStatus2.SetMotorSelect(14);
	m_ctlMotorStatus2.SetMotorName(_T("15: Flipper Up/Dn"));
	m_ctlMotorStatus2.SetMotorSelect(15);
	m_ctlMotorStatus2.SetMotorName(_T("16: Flipper Belt"));
#endif

	// New camera
	//pWnd = GetDlgItem(IDC_STATIC_NEW_CAMERA);
	//if (pApp->m_mil.m_NewCamera) 
	//	pWnd->SetWindowText(_T("New Camera"));
	//else 
	//	pWnd->SetWindowText(_T(""));

	// Save a pointer in the app member
	pApp->m_pWndView = this;

	// Remove the scroll bars
	SetScrollSizes(MM_TEXT,CSize (0,0),CSize (0,0));

	// Is PMAC open
	//TRACE("................................IsPmacOpen %x \n",pmac->IsPmacOpen());
	
	TRACE("................................BTCDATA %d \n",sizeof(BTCDATA));
	if (pmac->IsPmacOpen() )
	{
		//AfxMessageBox(_T("Set PMAC variables"));	
		// Set the P-Varibles
		SetPmacPVariables(pApp,pmac);

		// Set the Counters
		pmac->DPRSet(DPR_OFFSET_MOTORBITS,(long)0xFFFF);
		pmac->DPRSet(DPR_OFFSET_TOTAL_SHEET,pApp->m_Counters.TotalSheetCount);
		pmac->DPRSet(DPR_OFFSET_SHEET_COUNT,pApp->m_Counters.SheetCount);
		pmac->DPRSet(DPR_OFFSET_SHEET_SHIFT,pApp->m_Counters.SheetCountShift);
		//AfxMessageBox(_T("OnInitialUpdate ... PMAC IS open"));	
	}
	else
	{
		AfxMessageBox(_T("OnInitialUpdate ... PMAC not open"));	
	}


	// Set Main screen values
	m_ctlSliceCount.SetValue(pApp->m_Settings.MotionSettings1.dbPvars[24]);
	m_ctlPaperLenght.SetValue(pApp->m_Settings.MotionSettings1.dbPvars[19]);
	m_ctlBladeSpeed.SetValue(pApp->m_Settings.MotionSettings1.dbPvars[7]);
	m_ctlBladeSpeed2.SetValue(pApp->m_Settings.MotionSettings1.dbPvars[7]);
	m_ctlDischargeDistOffset.SetValue(pApp->m_Settings.MotionSettings1.dbPvars[52]);

	//MIL_DOUBLE AcquisitionLineRateAbsInHz = pApp->m_Settings.MotionSettings1.dbPvars[7];
	//if (AcquisitionLineRateAbsInHz < 200) AcquisitionLineRateAbsInHz = 200;
	//pApp->m_mil.RunThreadData.pHook1->AcquisitionLineRateAbsInHz = AcquisitionLineRateAbsInHz;
	//MdigControlFeature(pApp->m_mil.MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("AcquisitionLineRateAbs"), M_TYPE_DOUBLE, &AcquisitionLineRateAbsInHz);

	// Set Alignment mode
	m_ctlAlignOffset.SetValue(pApp->m_Settings.VisSettings3.dbAlignOffset);

	//========================================================================================//
	// Set the font
	//========================================================================================//
	m_fontMed.CreatePointFont (90, _T ("Microsoft Sans Serif"));
	m_fontLarge.CreatePointFont (90, _T ("Microsoft Sans Serif"));
	m_fontExtraLarge.CreatePointFont (420, _T ("Microsoft Sans Serif"));
	//========================================================================================//

	// Main status
	m_ctlStatusMainEx.SetTitleText(pApp->m_Settings.HMISettings.szLaneName);
	m_ctlStatusMainEx2.SetTitleText(pApp->m_Settings.HMISettings.szLaneName);
	m_ctlStatusMainEx3.SetTitleText(pApp->m_Settings.HMISettings.szLaneName);
	//m_ctlMain.SetTitleText(pApp->m_Settings.HMISettings.szLaneName);
	//m_ctlMain2.SetTitleText(pApp->m_Settings.HMISettings.szLaneName);
	//m_ctlMain3.SetTitleText(pApp->m_Settings.HMISettings.szLaneName);

	// Clock
	pWnd = GetDlgItem(IDC_CLOCK);
	pWnd->GetWindowRect(&rect);
	pWnd->DestroyWindow();
	ScreenToClient(&rect);
	m_pLedWnd = CreateIsLCDWnd(this,rect,6);
		
	// RunTime
	pWnd = GetDlgItem(IDC_RUNTIME_CLOCK);
	pWnd->GetWindowRect(&rect);
	pWnd->DestroyWindow();
	ScreenToClient(&rect);
	m_pLedWnd2 = CreateIsLCDWnd(this,rect,7);

	// Show time
	dbHours = pApp->m_Counters.TotalRunSeconds/3600.0;
	nHour = (int)dbHours;
	remaining = dbHours - nHour;
	dbMin = remaining*60;
	nMinute = (int)dbMin;
	remaining = dbMin - nMinute;
	str.Format (_T ("%0.5d:%0.2d"),nHour,nMinute);
	m_pLedWnd2->SetWindowText(str);

	// Total RunTime
	pWnd = GetDlgItem(IDC_RUNTIME_CLOCK2);
	pWnd->GetWindowRect(&rect);
	pWnd->DestroyWindow();
	ScreenToClient(&rect);
	m_pLedWnd3 = CreateIsLCDWnd(this,rect,7);

	// Show time
	dbHours = pApp->m_Counters.LifeTimeRunSeconds/3600.0;
	nHour = (int)dbHours;
	remaining = dbHours - nHour;
	dbMin = remaining*60;
	nMinute = (int)dbMin;
	remaining = dbMin - nMinute;
	str.Format (_T ("%0.5d:%0.2d"),nHour,nMinute);
	m_pLedWnd3->SetWindowText(str);

	// Start the clock timer
	SetTimer(1,1000,NULL);
	m_HmiTime=200;
	SetTimer(2,m_HmiTime,NULL);
	//SetTimer(2,200,NULL);

	// Create the MilWindow
	pWnd = GetDlgItem(IDC_MIL_DISPLAY);
	pWnd->GetWindowRect(&rect);
	pWnd->DestroyWindow();
	ScreenToClient(&rect);
	m_pMilWnd = new CMilWnd(rect,this,IDR_MIL_TOOLBAR1,1);
	m_pMilWnd->ShowWindow (SW_SHOW);
	m_pMilWnd->UpdateWindow ();
	m_pMilWnd->ImageBuffer = pApp->SelectDisplay(m_pMilWnd->m_hWnd);
	pApp->m_mil.RunThreadData.pMilWnd = m_pMilWnd;

	// Create the MilWindow2
	pWnd = GetDlgItem(IDC_MIL_DISPLAY2);
	pWnd->GetWindowRect(&rect);
	pWnd->DestroyWindow();
	ScreenToClient(&rect);
	m_pMilWnd2 = new CMilWnd(rect,this,NULL,NULL);
	m_pMilWnd2->ShowWindow (SW_SHOW);
	m_pMilWnd2->UpdateWindow ();
	m_pMilWnd2->ImageBuffer = pApp->SelectDisplay2(m_pMilWnd2->m_hWnd);
	pApp->m_mil.RunThreadData.pMilWnd2 = m_pMilWnd2;

	// Create the RejectMilWindow
	pWnd = GetDlgItem(IDC_MIL_REJ_DISPLAY1);
	pWnd->GetWindowRect(&rect);
	pWnd->DestroyWindow();
	ScreenToClient(&rect);
	m_pMilRejectWnd = new CMilWnd(rect,this,IDR_MIL_TOOLBAR1,2);
	m_pMilRejectWnd->ShowWindow (SW_SHOW);
	m_pMilRejectWnd->UpdateWindow ();
	m_pMilRejectWnd->ImageBuffer = pApp->SelectRejectDisplay(m_pMilRejectWnd->m_hWnd);

	// Create the RejectMilWindow2
	pWnd = GetDlgItem(IDC_MIL_REJ_DISPLAY2);
	pWnd->GetWindowRect(&rect);
	pWnd->DestroyWindow();
	ScreenToClient(&rect);
	m_pMilRejectWnd2 = new CMilWnd(rect,this,NULL,NULL);
	m_pMilRejectWnd2->ShowWindow (SW_SHOW);
	m_pMilRejectWnd2->UpdateWindow ();
	m_pMilRejectWnd2->ImageBuffer = pApp->SelectRejectDisplay2(m_pMilRejectWnd2->m_hWnd);

	// Vision Page
	pWnd = GetDlgItem(IDC_BACON_POS);
	pWnd->SetFont(&m_fontMed);
	pWnd = GetDlgItem(IDC_BACON_POS2);
	pWnd->SetFont(&m_fontMed);
	pWnd = GetDlgItem(IDC_DPR_ROLL_SIZE);
	pWnd->SetFont(&m_fontMed);
	pWnd = GetDlgItem(IDC_MIN_ROLL_SIZE);
	pWnd->SetFont(&m_fontMed);
	pWnd = GetDlgItem(IDC_MAX_ROLL_SIZE);
	pWnd->SetFont(&m_fontMed);
	pWnd = GetDlgItem(IDC_DRUM_REVS);
	pWnd->SetFont(&m_fontMed);
	pWnd = GetDlgItem(IDC_P183);
	pWnd->SetFont(&m_fontMed);
	pWnd = GetDlgItem(IDC_P357);
	pWnd->SetFont(&m_fontMed);
	pWnd = GetDlgItem(IDC_P316);
	pWnd->SetFont(&m_fontMed);
	pWnd = GetDlgItem(IDC_P319);
	pWnd->SetFont(&m_fontMed);
	pWnd = GetDlgItem(IDC_P334);
	pWnd->SetFont(&m_fontMed);
	pWnd = GetDlgItem(IDC_P400);
	pWnd->SetFont(&m_fontMed);
	pWnd = GetDlgItem(IDC_P404);
	pWnd->SetFont(&m_fontMed);
	pWnd = GetDlgItem(IDC_P405);
	pWnd->SetFont(&m_fontMed);

	pWnd = GetDlgItem(IDC_P419);
	pWnd->SetFont(&m_fontMed);

	// Page Change buttons
	pBtn = (CButton*)GetDlgItem(IDC_GOTO_VISION);
	pBtn->SetFont(&m_fontLarge);
	pBtn->SetIcon (AfxGetApp ()->LoadIcon (IDI_VISION));

	pBtn = (CButton*)GetDlgItem(IDC_GOTO_HOME);
	pBtn->SetFont(&m_fontLarge);
	pBtn->SetIcon (AfxGetApp ()->LoadIcon (IDI_HOME));

	pBtn = (CButton*)GetDlgItem(IDC_GOTO_HOME2);
	pBtn->SetFont(&m_fontLarge);
	pBtn->SetIcon (AfxGetApp ()->LoadIcon (IDI_HOME));

	pBtn = (CButton*)GetDlgItem(IDC_GOTO_HOME3);
	pBtn->SetFont(&m_fontLarge);
	pBtn->SetIcon (AfxGetApp ()->LoadIcon (IDI_HOME));

	pBtn = (CButton*)GetDlgItem(IDC_GOTO_HOME4);
	pBtn->SetFont(&m_fontLarge);
	pBtn->SetIcon (AfxGetApp ()->LoadIcon (IDI_HOME));

	pBtn = (CButton*)GetDlgItem(IDC_GOTO_HOME5);
	pBtn->SetFont(&m_fontLarge);
	pBtn->SetIcon (AfxGetApp ()->LoadIcon (IDI_HOME));

	pBtn = (CButton*)GetDlgItem(IDC_GOTO_IOPAGE);
	pBtn->SetFont(&m_fontLarge);
	pBtn->SetIcon (AfxGetApp ()->LoadIcon (IDI_IOPAGE));

	pBtn = (CButton*)GetDlgItem(IDC_GOTO_SERVOS);
	pBtn->SetFont(&m_fontLarge);
	pBtn->SetIcon (AfxGetApp ()->LoadIcon (IDI_SERVOS));

	//pBtn = (CButton*)GetDlgItem(IDC_GOTO_LASER);
	//pBtn->SetFont(&m_fontLarge);
	//pBtn->SetIcon (AfxGetApp ()->LoadIcon (IDI_LASER));

	pBtn = (CButton*)GetDlgItem(IDC_GOTO_CLEAN);
	pBtn->SetFont(&m_fontLarge);
	pBtn->SetIcon (AfxGetApp ()->LoadIcon (IDI_CLEAN));

	pBtn = (CButton*)GetDlgItem(IDC_SYS_BUTTONS);
	pBtn->SetFont(&m_fontLarge);
	pBtn->SetIcon (AfxGetApp ()->LoadIcon (IDI_SYSTEM));

	pBtn = (CButton*)GetDlgItem(IDC_SYS_BUTTONS2);
	pBtn->SetFont(&m_fontLarge);
	pBtn->SetIcon (AfxGetApp ()->LoadIcon (IDI_SYSTEM));

	// Counter Buttons
	pBtn = (CButton*)GetDlgItem(IDC_SHEET_COUNT_INC);
	pBtn->SetFont(&m_fontExtraLarge);
	pBtn = (CButton*)GetDlgItem(IDC_SHEET_COUNT_DEC);
	pBtn->SetFont(&m_fontExtraLarge);
	//pBtn->SetIcon (AfxGetApp ()->LoadIcon (IDI_SYSTEM));

	// Settings
	pBtn = (CButton*)GetDlgItem(IDC_VISION_SETTINGS);
	pBtn->SetFont(&m_fontLarge);
	pBtn->SetIcon (AfxGetApp ()->LoadIcon (IDI_VIS_SETTINGS));

	// Settings
	//pBtn = (CButton*)GetDlgItem(IDC_VISION_SETTINGS2);
	//pBtn->SetFont(&m_fontLarge);
	//pBtn->SetIcon (AfxGetApp ()->LoadIcon (IDI_VIS_SETTINGS));
	pBtn = (CButton*)GetDlgItem(IDC_VISION_SETTINGS2);
	pBtn->SetFont(&m_fontLarge);
	pBtn->SetIcon (AfxGetApp ()->LoadIcon (IDI_MOTION_SETTINGS));

	// Settings
	pBtn = (CButton*)GetDlgItem(IDC_MOTION_SETTINGS);
	pBtn->SetFont(&m_fontLarge);
	pBtn->SetIcon (AfxGetApp ()->LoadIcon (IDI_MOTION_SETTINGS));

	//pBtn = (CButton*)GetDlgItem(IDC_MOTION_SETTINGS2);
	//pBtn->SetFont(&m_fontLarge);
	//pBtn->SetIcon (AfxGetApp ()->LoadIcon (IDI_MOTION_SETTINGS));

	pBtn = (CButton*)GetDlgItem(IDC_DISPLAY_SEL1);
	pBtn->SetFont(&m_fontLarge);
	pBtn->SetIcon (AfxGetApp ()->LoadIcon (IDI_LIVE));

	pBtn = (CButton*)GetDlgItem(IDC_DISPLAY_SEL4);
	pBtn->SetFont(&m_fontLarge);
	pBtn->SetIcon (AfxGetApp ()->LoadIcon (IDI_FREEZE_CAPTURE));

	pBtn = (CButton*)GetDlgItem(IDC_DISPLAY_SEL2);
	pBtn->SetFont(&m_fontLarge);
	pBtn->SetIcon (AfxGetApp ()->LoadIcon (IDI_BIN));

	pBtn = (CButton*)GetDlgItem(IDC_DISPLAY_SEL3);
	pBtn->SetFont(&m_fontLarge);
	pBtn->SetIcon (AfxGetApp ()->LoadIcon (IDI_RESULT));

	pBtn = (CButton*)GetDlgItem(IDC_SHOW_SHERBAR_POINTS);
	pBtn->SetFont(&m_fontLarge);
	pBtn->SetIcon (AfxGetApp ()->LoadIcon (IDI_HIDE_OVERLAY));

	pBtn = (CButton*)GetDlgItem(IDC_RECORD_BELLY);
	pBtn->SetFont(&m_fontLarge);
	pBtn->SetIcon (AfxGetApp ()->LoadIcon (IDI_RECORD));

	pBtn = (CButton*)GetDlgItem(IDC_PLAY_BELLY);
	pBtn->SetFont(&m_fontLarge);
	pBtn->SetIcon (AfxGetApp ()->LoadIcon (IDI_PLAY));

	pBtn = (CButton*)GetDlgItem(IDC_STOP_PLAY);
	pBtn->SetFont(&m_fontLarge);
	pBtn->SetIcon (AfxGetApp ()->LoadIcon (IDI_STOP));
	pBtn->EnableWindow(0);

	// Set the buttons
	switch (pApp->m_mil.RunThreadData.pHook1->DisplaySelect)
	{
		case 0:
			OnBnClickedDisplaySel1();
			break;
		case 1:
			OnBnClickedDisplaySel2();
			break;
		case 2:
			OnBnClickedDisplaySel3();
			break;	
		case 3:
			OnBnClickedDisplaySel4();
			break;	
	}

	// Off
	m_btnTimingCheck.SetLightOn(0);
	m_ctlBtcReady.SetLightOn(0);
	m_ctlBtcReady2.SetLightOn(0);
	m_btnLoadPaper.SetLightOn(0);

	// Roll diameter range
	m_PaperRollSize.SetRange(11,55);	
	m_FaultHistory.SetFileName(FAULT_HISTORY_PATH);
	//m_FaultHistory.AddString(_T("MOTOR 1 FAULT"));
	//m_FaultHistory.AddString(_T("MOTOR 21 FAULT"));
	//m_FaultHistory.AddString(_T("MOTOR 12 FAULT"));
	//// m_FaultHistory.SaveStrings();

	// Clear the latches
	::ZeroMemory (&m_bMotorFaultLatch[0], sizeof (m_bMotorFaultLatch));
	::ZeroMemory (&m_bMotorWarnLatch[0], sizeof (m_bMotorWarnLatch));	

	TRACE("\n\n sizeof (m_bMotorFaultLatch) %d \n",sizeof (m_bMotorFaultLatch));
	TRACE("m_bMotorFaultLatch[15]= %d \n",m_bMotorFaultLatch[15]);

	m_bGlobalStatusFaultLatch = false;
	m_bShuntTempFaultLatch1 = false;	
	m_bShuntTempFaultLatch2 = false;	
	m_bShuntTempFaultLatch3 = false;	
	m_bRejectVFDFaultLatch = false;
	m_bExitVFDFaultLatch = false;

	CString strIp(pApp->m_Settings.HMISettings.ServerIP);
	//AfxMessageBox(strIp);

	// Initialization of ETHERNET/IP
	//m_EIPClient.Init(strIp);        //_T("192.168.1.121") //m_EIPClient.ConnectToServer(1,_T("192.168.1.122"));

	// Add tags
	//m_EIPClient.AddTag(0,"BTC1_Status",1);
	//m_EIPClient.AddTag(0,"BTC2_Status",1);
	//m_EIPClient.AddTag(0,"BTC3_Status",1);
	//m_EIPClient.AddTag(0,"BTC4_Status",1);
	//m_EIPClient.AddTag(0,"Slicer_A_Status",1);
	//m_EIPClient.AddTag(0,"Slicer_B_Status",1);

	// Set the tag names
	switch (pApp->m_Settings.HMISettings.nLaneID)
	{
	case 0:
	case 1:
		strcpy_s(m_TagNameBTCStatus,"BTC1_Status");
		strcpy_s(m_TagNameSlicerStatus,"Slicer_A_Status");
		break;
	case 2:
		strcpy_s(m_TagNameBTCStatus,"BTC2_Status");
		strcpy_s(m_TagNameSlicerStatus,"Slicer_A_Status");
		break;
	case 3:
		strcpy_s(m_TagNameBTCStatus,"BTC3_Status");
		strcpy_s(m_TagNameSlicerStatus,"Slicer_B_Status");
		break;
	case 4:
		strcpy_s(m_TagNameBTCStatus,"BTC4_Status");
		strcpy_s(m_TagNameSlicerStatus,"Slicer_B_Status");
		break;
	default:
		strcpy_s(m_TagNameBTCStatus,"BTC4_Status");
		strcpy_s(m_TagNameSlicerStatus,"Slicer_B_Status");
		break;
	}

	// Show the slice thinkness
	m_ctlSliceThickness.SetValue(pApp->m_Settings.MotionSettings1.dbPvars[45]);

	// Shear bar and Camera settings
	pApp->m_mil.ApplySettings();

	// Lights off
	m_btnOutputForce.SetLightOn(0);
	m_btnOutputForce2.SetLightOn(0);
	m_btnOutputForce3.SetLightOn(0);

	//AfxMessageBox(_T("Here"));

}

// CHMIView diagnostics

#ifdef _DEBUG
void CHMIView::AssertValid() const
{
	CFormView::AssertValid();
}

void CHMIView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CHMIDoc* CHMIView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHMIDoc)));
	return (CHMIDoc*)m_pDocument;
}
#endif //_DEBUG


// CHMIView message handlers



void CHMIView::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent==1)DoClockTimer();
	if (nIDEvent==2)DoHMITimer();
}
void CHMIView::DoClockTimer()
{
	CHMIApp* pApp = (CHMIApp*)AfxGetApp();
	CPmac* pmac = &pApp->m_pmac;

	CTime time;
    int nSecond;
	int nMinute;
    int nHour;
	static bool LatchStart = false;
	static clock_t start, finish;
	double  duration;
	double remaining;

    time = CTime::GetCurrentTime ();
    nSecond = time.GetSecond ();
	nMinute = time.GetMinute ();
    nHour = time.GetHour ();

	// Return when clock has not changed
	if ((nSecond == m_nPrevSecond) && (nMinute == m_nPrevMinute) && (nHour == m_nPrevHour))
	{
		TRACE("every 100 msec \n");
		SetTimer(1,100,NULL);  // Check again in 100 msec
		return;
	}

	// Dont check clock for another second
	//TRACE("every second\n");
	SetTimer(1,1010,NULL);

	// Save
	m_nPrevSecond = nSecond;
    m_nPrevMinute = nMinute;
    m_nPrevHour = nHour;

	// Update the time display
	CString str;
	if (nHour > 12) nHour = nHour%12;
	str.Format (_T ("%0.2d:%0.2d:%0.2d"), nHour, nMinute, nSecond);
	//TRACE("every second \n");
	m_pLedWnd->SetWindowText(str);

	// Feed Button
	if (m_BtcData.StatusBits.FeedStartStop==1 && m_BtcData.GlobalStatus==GS_RUNNING)
	{
		if (!LatchStart)
		{
			LatchStart = true;
			start = clock();
		}
		finish = clock();
		duration = (double)(finish - start) / CLOCKS_PER_SEC;
		duration += pApp->m_Counters.TotalRunSeconds;
		double dbHours = duration/3600.0;
		nHour = (int)dbHours;
		remaining = dbHours - nHour;
		double dbMin = remaining*60;
		nMinute = (int)dbMin;
		//remaining = dbMin - nMinute;
		//double dbSec = remaining*60;
		//nSecond = (int)dbSec;
		str.Format (_T ("%0.5d:%0.2d"),nHour,nMinute);
		m_pLedWnd2->SetWindowText(str);
	
		duration = (double)(finish - start) / CLOCKS_PER_SEC;
		duration += pApp->m_Counters.LifeTimeRunSeconds;
		dbHours = duration/3600.0;
		nHour = (int)dbHours;
		remaining = dbHours - nHour;
		dbMin = remaining*60;
		nMinute = (int)dbMin;
		str.Format (_T ("%0.5d:%0.2d"),nHour,nMinute);
		m_pLedWnd3->SetWindowText(str);
	}
	else
	{
		if (LatchStart)
		{
			finish = clock();
			duration = (double)(finish - start) / CLOCKS_PER_SEC;
			pApp->m_Counters.TotalRunSeconds +=(long)duration;
			pApp->m_Counters.LifeTimeRunSeconds +=(long)duration;
			SaveAppCounterFile (&pApp->m_Counters);
		}
		LatchStart = false;	
	}
	//-------------------------------------------------------------------------------//


	return;

}
void CHMIView::DoHMITimer()
{
	//TRACE("DoHMITimer \n");
	// PMAC communications when the camera is not sending data.
	//-------------------------------------------------------------------------------//
	if (m_bOnTimerUpdate)
	{
		//TRACE("DoHMITimer PMAC communications \n");
		OnDoPmacCommunications (0,0);
		if (m_HmiTime !=200)
		{
			m_HmiTime=200;
			TRACE("Speed up HMI TIMER \n");
			SetTimer(2,m_HmiTime,NULL);
		}
	}
	else
	{
		m_bOnTimerUpdate = true;
	}
}

// Page change helper
//////////////////////////////////////////////////////////////////////////////////////////////////
void CHMIView::ScrollToPage(int nPage)
{
	//CBTCHMIApp* pApp = (CBTCHMIApp*)AfxGetApp();
	//pApp->dbPageTime = 0;
	CHMIApp* pApp = (CHMIApp*)AfxGetApp();

	if (nPage == 0)
	{
		pApp->m_mil.RunThreadData.pHook1->MainPage = true;
		pApp->m_mil.MilHook2.MainPage = true;
	}
	else
	{
		pApp->m_mil.RunThreadData.pHook1->MainPage = false;
		pApp->m_mil.MilHook2.MainPage = false;
	}
	int nScrollDist = (nPage*m_nPageHeight) - m_nScrollPos;
	m_nScrollPos += nScrollDist;
	ScrollWindow(0,-nScrollDist);
	m_nPage = nPage;
	//TRACE("Scroll Position: %d \n",m_nScrollPos);
}

// Page size
//////////////////////////////////////////////////////////////////////////////////////////////////
void CHMIView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);
	m_nPageHeight = cy;
	//TRACE("OnSize X size: %d Y size: %d\n",cx,cy);	
}
void CHMIView::OnBnClickedGotoVision()
{
	ScrollToPage(1);
	//m_EIPClient.SetTagReadFlag(0,"BTC1_Status");
	//m_EIPClient.SetTagReadFlag(0,"BTC2_Status");
	//m_EIPClient.SetTagReadFlag(0,"BTC3_Status");
	//m_EIPClient.SetTagReadFlag(0,"BTC4_Status");
	//m_EIPClient.SetTagReadFlag(0,"Slicer_A_Status");
	//m_EIPClient.SetTagReadFlag(0,"Slicer_B_Status");
	//m_EIPClient.ReadTags(0,0);

}
void CHMIView::OnBnClickedGotoLaser()
{
	ScrollToPage(5);			

	//TCHAR szName[256];
	//STARTUPINFO si;
	//::ZeroMemory (&si, sizeof (STARTUPINFO));
	//si.cb = sizeof (STARTUPINFO);
	//PROCESS_INFORMATION pi;
	//::ZeroMemory (&si, sizeof (STARTUPINFO));
	//si.cb = sizeof (STARTUPINFO);
	//::lstrcpy(szName,_T ("C:\\Program Files\\Hormel Foods LLC\\LaserView.exe"));

	//// Find LASERVIEW.EXE
	//if (m_pLaserWnd==NULL)
	//{
	//	CRect rect;

	//	// Create the Laser window
	//	CWnd* pWnd = GetDlgItem(IDC_LASER_WND);
	//	pWnd->GetWindowRect(&rect);
	//	pWnd->DestroyWindow();
	//	ScreenToClient(&rect);
	//	m_pLaserWnd = new CLaserWnd(rect,this);
	//	m_pLaserWnd->ShowWindow (SW_SHOW);
	//	m_pLaserWnd->UpdateWindow ();
	//
	//	if (::CreateProcess (NULL,szName ,NULL,NULL,FALSE, NORMAL_PRIORITY_CLASS, NULL, NULL, &si, &pi))
	//	{
	//		::CloseHandle (pi.hThread);
	//		::WaitForInputIdle (pi.hProcess, INFINITE);
	//		::EnumWindows(EnumWindowsProc,(LPARAM) m_pLaserWnd);
	//		::CloseHandle (pi.hProcess);
	//	}
	//}

}
// CLaserViewView message handlers
BOOL CALLBACK CHMIView::EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
	TCHAR buff[256];
	CString str;
	CLaserWnd* pLaserWnd = (CLaserWnd*) lParam;
	::GetWindowText(hwnd,buff,256);
	TRACE(_T("NAME: %s \n"),buff);
	str = buff;
	if (str.Find(_T("LaserView")) == 0){
		TRACE(_T("\n\nFound LASERVIEW.EXE window... %s !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n"),str);
		if (pLaserWnd)
		{
			pLaserWnd->m_hwndChild = hwnd;
			hwndLaserView = hwnd;
			::SetParent(hwnd,pLaserWnd->m_hWnd);
			//::SetWindowPos(hwndLaserView,NULL,0,0,800,600,SWP_DRAWFRAME);
			//pLaserWnd->SetFocus();
		}
		return FALSE;
	}
	return TRUE;

	//TCHAR buff[256];
	//CString str;
	//::GetWindowText(hwnd,buff,256);
	//TRACE(_T("NAME: %s \n"),buff);
	//DWORD pID;
	//DWORD TpID = GetWindowThreadProcessId(hwnd, &pID);
	//if (TpID == lParam)
	//{
	//	TRACE(_T("!!!! Found NAME: %s \n"),buff);
	//	hwndLaserView =hwnd;
	//	return false;
	//}
	//return true;
}

void CHMIView::OnBnClickedGotoHome()
{
	ScrollToPage(0);			
}
void CHMIView::OnBnClickedGotoHome2()
{
	ScrollToPage(0);			
}
void CHMIView::OnBnClickedGotoHome3()
{
	ScrollToPage(0);			
}
void CHMIView::OnBnClickedGotoHome4()
{
	ScrollToPage(0);			
}
void CHMIView::OnBnClickedGotoHome5()
{
	ScrollToPage(0);			
}
void CHMIView::OnBnClickedGotoIopage()
{
	ScrollToPage(2);
}
void CHMIView::OnBnClickedGotoServos()
{
	ScrollToPage(3);
}
void CHMIView::OnBnClickedGotoClean()
{
	ScrollToPage(4);
}
void CHMIView::OnBnClickedSysButtons()
{
	CMainFrame* pWnd = (CMainFrame*)GetParentFrame();

	// Hide the tools if visable
	if (pWnd->IsToolBarVisable())
	{
		pWnd->ToggelToolBar();
		return;
	}

	// Password
	if (CheckMasterPassword()==false)
		return;

	// Show the tools
	pWnd->ToggelToolBar();
}
void CHMIView::OnBnClickedSysButtons2()
{
	OnBnClickedSysButtons();
}
void CHMIView::OnBnClickedClearPeaks()
{
	CHMIApp* pApp = (CHMIApp*)AfxGetApp();
	CPmac* pmac = &pApp->m_pmac;
	pApp->m_mil.MilHook1.MaxComTime = 0;
	pApp->m_mil.MilHook1.PeriodMin = 0;
	pApp->m_mil.MilHook1.PeriodMax = 0;
	pApp->m_mil.MilHook1.TotalBlobCount = 0;
	pApp->m_mil.MilHook1.LockSize = 0;
	pApp->m_mil.MilHook1.MaxProcTime = 0;
	pApp->m_mil.MilHook1.BaconSpeed = 0;
	pApp->m_mil.MilHook1.MaxComPeriod = 0;
	pApp->m_mil.MilHook1.MaxTimeStampRes = 0;
	pApp->m_mil.MilHook1.TotalRejectCount = 0;
	//pApp->m_mil.MilHook1.ResyncCount = 0;
	//pApp->m_mil.MilHook1.TimeStampErrorCount = 0;
	//pApp->m_mil.MilHook1.DoubleBufferCount = 0;
	//pmac->SetVariable(_T('M'),1785,(long)0);
	//pmac->SetVariable(_T('M'),1786,(long)0);
	pmac->SetVariable(_T('P'),334,(long)0);

}
// Check the user password
bool CHMIView::CheckPassword(void)
{
	CHMIApp* pApp = (CHMIApp*)AfxGetApp();
	return pApp->CheckPassword();
}

// Check the Master password
bool CHMIView::CheckMasterPassword(void)
{
	CHMIApp* pApp = (CHMIApp*)AfxGetApp();
	return pApp->CheckMasterPassword();
}
LRESULT CHMIView::OnDoPmacSave (WPARAM wParam, LPARAM lParam)
{
	TRACE("CHMIView::OnDoPmacSave\n");
	CHMIApp* pApp = (CHMIApp*)AfxGetApp();
	CPmac* pmac = &pApp->m_pmac;
	int Count = 0;
	HELPERPARAM Wait;
	Wait.bRun = TRUE;
	Wait.nWaitTime = 3000;

	m_bPmacBusy = true;
	if (YesNoDlg(_T("Do you want to save?")))
	{
		CWaitCursor wait;

		// Get latest copy of pvars and save
		GetPmacPVariables(pApp,pmac);
		OnSaveSettings (0,0);

		// Start the helper thread
		//CWinThread* pThread = AfxBeginThread (RUNTIME_CLASS (CUIHelperThread));
		CUIHelperThread* pThread = (CUIHelperThread*)AfxBeginThread (RUNTIME_CLASS (CUIHelperThread));
		pThread->SetDelayTime(3500);

		//TRACE("Character count: Before save %d \n",Count);
		//Count = pmac->Save(_T ("save"));
		pmac->SendCommand(_T("save"));
		Sleep(3500);
		//pThread->GetMainWnd()->SendMessage (WM_CLOSE,0,0); 		
		//DWORD dwExitCode;
		//::GetExitCodeThread (pThread->m_hThread, &dwExitCode);
		//if (dwExitCode == STILL_ACTIVE)
		//{
		////pThread->GetMainWnd()->SendMessage (WM_CLOSE,0,0); 		
		//}
		pThread->Close();


		Wait.bRun = FALSE;
	}
	m_bPmacBusy = false;

	return 0;
}	
//
LRESULT CHMIView::OnDoHmiSave (WPARAM wParam, LPARAM lParam)
{
	TRACE("CHMIView::OnDoHmiSave\n");
	CHMIApp* pApp = (CHMIApp*)AfxGetApp();
	CPmac* pmac = &pApp->m_pmac;
	//int Count = 0;
	//HELPERPARAM Wait;
	//Wait.bRun = TRUE;
	//Wait.nWaitTime = 3000;

	//_T ("D:\\BTCDATA\\UpLoadFile.CFG")
	if (YesNoDlg(_T("Do you want to save HMI settings?")))
	{
		CWaitCursor wait;

		// Get latest copy of pvars and save
		GetPmacPVariables(pApp,pmac);
		OnSaveSettings (0,0);


	}

	return 0;
}	

LRESULT CHMIView::OnDoPmacCommunications (WPARAM wParam, LPARAM lParam)
{
	CHMIApp* pApp = (CHMIApp*)AfxGetApp();
	//int NumChars;
	//BSTR resBuff;
	//long Ub;
	//HRESULT hres;
	//VARIANT DPRAMData;
	//VARIANT vardata;
	//SAFEARRAYBOUND bound;
	CPmac* pmac = &pApp->m_pmac;
	//CPmac* pmac2 = &pApp->m_pmacSlicer;
	//char* BaconBuff = (char*)&pApp->m_mil.RunThreadData.pHook1->BaconBuff[0];
	unsigned _int16* BaconBuff = &pApp->m_mil.RunThreadData.pHook1->BaconBuff[0];
	int count = PMAC_SEND_SIZE;
	//BTCDATA* pData;
	double dbTimeStart;
	double dbTimeEnd;

	// Read the com start time
	MappTimer(M_TIMER_READ, &dbTimeStart);

	// Com loss
	if (m_bPmacComLoss)
	{
		return 3;	
	}

	// HMI timer adjustment
	if (wParam==1 && m_HmiTime!=2000) 
	{
		m_HmiTime=2000;
		TRACE("SlowDown HMI TIMER \n");
		SetTimer(2,m_HmiTime,NULL);
	}

	// Is PMAC busy?
	if (m_bPmacBusy || m_bPmacUtilBusy)
	{
		//AfxMessageBox(_T("PMAC Busy"));
		//TRACE("OnDoPmacCommunications Pmac Busy... \n");
		//::WaitForSingleObject (m_pi.hProcess, 0);
		if (m_pi.hProcess != NULL && m_bPmacUtilBusy)
		{
			TRACE("Check PMAC utility... \n");
			if (::WaitForSingleObject (m_pi.hProcess, 0) == WAIT_OBJECT_0) {
				::CloseHandle (m_pi.hProcess);
				m_pi.hProcess  = NULL;
				m_bPmacUtilBusy = false;
				TRACE("Close PMAC utility... \n");
			}     //WAIT_TIMEOUT 
		}
		return 0;
	}

    //TRACE("PMAC communications... \n");
	m_bOnTimerUpdate = false;

	// Is PMAC open
	if (pmac->IsPmacOpen() == 0)
	{
		//AfxMessageBox(_T("OnDoPmacCommunications... PMAC not open"));
		return 1;
	}

	// Send PMAC data
	//------------------------------------------------//
	BaconBuff[0]                = 0xFFFF;             // Data Ready
	// BaconBuff[1]                = 0;               // Always zero
	// BaconBuff[2]                = pPos[0];         // Position X Low byte
	// BaconBuff[3]                = pPos[1];         // Position X High byte
	// BaconBuff[4]                = PosY;            // Position Y
	// BaconBuff[5]                = BlobCount;       // Count
	// BaconBuff[6]                = 0;               // Always zero
	// BaconBuff[7]                = 0;               // Always zero
	// BaconBuff[8]                = 0;               // Always zero
	// BaconBuff[9]                = 0;               // Always zero
	// BaconBuff[10]               = 0;               // Always zero
	BaconBuff[11]                  = 0xFFFF;          // Data ready
	//------------------------------------------------//
	if (!pmac->DPRSetMem(4416,count,(char*)BaconBuff))
	{
		if (!m_bPmacComLoss)
		{
			m_bPmacComLoss = true;				
			pmac->ClosePmac();
			MessageBox(_T("Communications Lost!"),_T("DPRSetMem Error!"));
			m_FaultHistory.AddString(_T("PMAC SetMem Communications Fault"));
			if (pmac->Init(0))
			{
				m_bPmacComLoss = false;
				long pvar;
				pmac->GetVariable(_T('P'),105,&pvar);
				if (pvar == 0)
				{
					m_FaultHistory.AddString(_T("Unexpected PMAC Reset"));
				}
			}
			//if (pmac->Init(0)) m_bPmacComLoss = false;
			return 3;
		}			
	}
	pApp->m_mil.RunThreadData.pHook1->BaconBuff[0]=0;
	MappTimer(M_TIMER_READ, &dbTimeEnd);
	//TRACE("DPR Set Time: %f \n",(dbTimeEnd-dbTimeStart)*1000);	
	//------------------------------------------------//

	// Read DPRAM memory locations from BTC drive
	//-------------------------------------------------------//
	if (!pmac->DPRGetMem(DPRAM_OFFSET,sizeof(BTCDATA),(char*)&m_BtcData))
	{
		TRACE(_T("DPRGetMem Error \n "));	
		m_bPmacComLoss = true;				
		pmac->ClosePmac();
		MessageBox(_T("Communications Lost!"),_T("DPRSetMem Error!"));
		m_FaultHistory.AddString(_T("PMAC SetMem Communications Fault"));
		if (pmac->Init(0))
		{
			m_bPmacComLoss = false;
			long pvar;
			pmac->GetVariable(_T('P'),105,&pvar);
			if (pvar == 0)
			{
				m_FaultHistory.AddString(_T("Unexpected PMAC Reset"));
			}
		}
		return 3;
	}

	//if (pmac->DPRGetMem(DPRAM_OFFSET,sizeof(BTCDATA),&DPRAMData))	
	//{
	//	// Get the Data
	//	hres = SafeArrayGetUBound(DPRAMData.parray,1,&Ub);
	//	//TRACE(_T("Ubounds %d \n"),Ub);	
	//	
	//	// Copy the data
	//	hres = SafeArrayAccessData(DPRAMData.parray,(void**)&pData);
	//	memcpy( &m_BtcData, pData, sizeof(BTCDATA) );
	//	SafeArrayUnaccessData(DPRAMData.parray);
	//	SafeArrayDestroy(DPRAMData.parray);
	//}
	//else
	//{
	//	if (!m_bPmacComLoss)
	//	{
	//		m_bPmacComLoss = true;				
	//		MessageBox(_T("Communications Lost!"),_T("DPRSetMem Error!"));
	//		m_FaultHistory.AddString(_T("PMAC Communications Fault"));
	//	}
	//}
	//-------------------------------------------------------//

	// Update the HMI
	UpDateHMI();

	// Com time
	MappTimer(M_TIMER_READ, &dbTimeEnd);
	pApp->m_mil.MilHook1.ComTime = ((dbTimeEnd-dbTimeStart)*1000);
	if (pApp->m_mil.MilHook1.ComTime > pApp->m_mil.MilHook1.MaxComTime)
	{
		pApp->m_mil.MilHook1.MaxComTime = pApp->m_mil.MilHook1.ComTime;
	}
	//TRACE(_T("Time to read/write DPRAM: %4.2f msec Max %4.2f msec\n"),pApp->m_mil.MilHook1.ComTime,pApp->m_mil.MilHook1.MaxComTime);
	//TRACE(_T("PeakCurrentMotor9 %f \n"),m_BtcData.PeakCurrentMotor9);
	//TRACE(_T("PeakCurrentMotor1 %d \n"),m_BtcData.MaxFE1);
	//TRACE(_T("VoltTempChannelSelect %d \n"),m_BtcData.VoltTempChannelSelect);
	//TRACE(_T("Btc Data Size %d \n"),sizeof(BTCDATA));
	pApp->m_mil.RunThreadData.pHook1->PmacComComplete = true;

	//m_BtcData.Mtr1to4.Byte0

	return 0;

}

void CHMIView::OnBnClickedHistory()
{
	CFaultHistory dlg;
	CHMIApp* pApp = (CHMIApp*)AfxGetApp();
	dlg.m_pHistory = &pApp->m_mil.m_History;
	dlg.DoModal();
}
void CHMIView::OnViewHmioptions()
{
	//TCHAR szLaneName[256];
	HMIOPT Data;
	CHMIApp* pApp = (CHMIApp*)AfxGetApp();
	Data.bBoostPriority = pApp->m_Settings.HMISettings.bBoostPriority;
	Data.bFullReset = pApp->m_Settings.HMISettings.bFullReset;
	Data.bEnableUser = pApp->m_Settings.HMISettings.bEnableUser;
	Data.bEnableMaster = pApp->m_Settings.HMISettings.bEnableMaster;
	Data.nPassword = pApp->m_Settings.HMISettings.nPassword;
	Data.nMasterPassword = pApp->m_Settings.HMISettings.nMasterPassword;
	Data.nLaneID = pApp->m_Settings.HMISettings.nLaneID;
	Data.nPmacReset = pApp->m_Settings.HMISettings.nPmacReset;
	Data.PmacID = pApp->m_Settings.HMISettings.PmacID;

	strcpy_s(Data.ServerIP,pApp->m_Settings.HMISettings.ServerIP);
	::lstrcpy (Data.szLaneName,pApp->m_Settings.HMISettings.szLaneName);

	// Display the HMI Options dialog
	if (GetHMIOptDlg(&Data))
	{
		pApp->m_Settings.HMISettings.bBoostPriority = Data.bBoostPriority;
		pApp->m_Settings.HMISettings.bFullReset = Data.bFullReset;
		pApp->m_Settings.HMISettings.bEnableUser = Data.bEnableUser;
		pApp->m_Settings.HMISettings.bEnableMaster = Data.bEnableMaster;
		pApp->m_Settings.HMISettings.nPassword = Data.nPassword;
		pApp->m_Settings.HMISettings.nMasterPassword = Data.nMasterPassword;
		pApp->m_Settings.HMISettings.nLaneID = Data.nLaneID;
		pApp->m_Settings.HMISettings.nPmacReset = Data.nPmacReset;
		pApp->m_Settings.HMISettings.PmacID = Data.PmacID;

		strcpy_s(pApp->m_Settings.HMISettings.ServerIP,Data.ServerIP);
		::lstrcpy (pApp->m_Settings.HMISettings.szLaneName,Data.szLaneName);

		m_ctlStatusMainEx.SetTitleText(pApp->m_Settings.HMISettings.szLaneName);
		m_ctlStatusMainEx2.SetTitleText(pApp->m_Settings.HMISettings.szLaneName);
		m_ctlStatusMainEx3.SetTitleText(pApp->m_Settings.HMISettings.szLaneName);
		//m_ctlMain.SetTitleText(pApp->m_Settings.HMISettings.szLaneName);
		//m_ctlMain2.SetTitleText(pApp->m_Settings.HMISettings.szLaneName);
		//m_ctlMain3.SetTitleText(pApp->m_Settings.HMISettings.szLaneName);
		
		TRACE("Lane ID %d \n",pApp->m_Settings.HMISettings.nLaneID);
		TRACE(_T("Name: %s  \n"),Data.szLaneName);

		//TRACE(_T("lpData->szLaneName: %s  \n"),lpData->szLaneName);

		// Do silent save if password changed
		if ((pApp->m_Settings.HMISettings.nPassword != Data.nPassword) 
			|| (pApp->m_Settings.HMISettings.nMasterPassword != Data.nMasterPassword) )
		{

			SaveAppSettingFile (&pApp->m_Settings);
			TRACE("Password User%d Master %d ",pApp->m_Settings.HMISettings.nPassword,pApp->m_Settings.HMISettings.nMasterPassword);
		}

		// Bump up the process priority of this applicaton
		if (pApp->m_Settings.HMISettings.bBoostPriority)
		{
			SetPriorityClass(GetCurrentProcess(),ABOVE_NORMAL_PRIORITY_CLASS);
			//int Priority = GetPriorityClass(GetCurrentProcess());
			//TRACE(_T("Priority: %x\n"),Priority);
		}
		else
		{
			SetPriorityClass(GetCurrentProcess(),NORMAL_PRIORITY_CLASS);
		}


	}
	pApp->m_bSettingsModifyied = true;


}
// Save settings
void CHMIView::OnViewSettingsSave(void)
{
	CHMIApp* pApp = (CHMIApp*)AfxGetApp();
	SaveAppSettingFile (&pApp->m_Settings);
	pApp->m_bSettingsModifyied = false;
}
void CHMIView::OnUpdateSettingsSave(CCmdUI *pCmdUI)
{
	CHMIApp* pApp = (CHMIApp*)AfxGetApp();
	pCmdUI->Enable(pApp->m_bSettingsModifyied);

	//TRACE("IDC_RECORD .....IDC_RECORD .....IDC_RECORD ..... \n");

}


void CHMIView::OnToolsSave()
{
	CString strPath,num;
	CString strFilename;
	TCHAR szName[256];
	STARTUPINFO si;
	KEYPADDATA data;
	CGetName dlg;
	CHMIApp* pApp = (CHMIApp*)AfxGetApp();

	// Get path number
	data.dbIncrement = 0;
	data.dbMin = 0;
	data.dbValue = 0;
	data.dbMax = 0;
	data.lpTitle = _T("Enter User Pin number");
	data.nDecimalPlaces = 0;
	data.bPassWord = false;
	if (!GetNumDlg(&data)){
		return;			
	}

	// Get the path
	strPath = BACKUP_PATH;
	num.Format(_T("SET%d"),(int)data.dbValue);
	strPath+=num;
	if (!CreateDirectory(strPath,NULL))
	{
		if (GetLastError() == ERROR_ALREADY_EXISTS)
		{
			TRACE(_T("Code in use....create.... %s \n"),strPath);
		}
		//OkDlg(_T("Code Already used !     Select a different code."),true);
	}
	
	// Get the File Name
	::ZeroMemory (&si, sizeof (STARTUPINFO));
	si.cb = sizeof (STARTUPINFO);
	PROCESS_INFORMATION pi;
	::lstrcpy(szName,_T ("OSK.EXE"));
	if (::CreateProcess (NULL,szName ,NULL,NULL,FALSE, NORMAL_PRIORITY_CLASS, NULL, NULL, &si, &pi))
	{
		::CloseHandle (pi.hThread);
		//::WaitForSingleObject (pi.hProcess, INFINITE);
		::WaitForInputIdle(pi.hProcess,INFINITE);
		::CloseHandle (pi.hProcess);
	}

	// Position the keyboard
	int TryCount=2000;
	HWND hWnd = 0;
	//TRACE("OSK Window %d \n",hWnd);
	while (hWnd == 0 && TryCount > 0 )
	{
		hWnd = ::FindWindow(NULL,_T("On-Screen Keyboard"));
		Sleep(1);
		TryCount--;
	}
	if (hWnd > 0)
	{
		//DWORD Style = ::GetWindowLong(hWnd,GWL_STYLE);
		//Style = Style & ~WS_CAPTION;
		//Style = Style & ~WS_THICKFRAME;
		//::SetWindowLong(hWnd,GWL_STYLE,Style);
		//::SetWindowPos(hWnd,NULL,WINDOW_POSITION_X,400,1024,768,SWP_NOSIZE | SWP_NOZORDER | SWP_DRAWFRAME);
		::SetWindowPos(hWnd,NULL,WINDOW_POSITION_X,400,1024,768,SWP_NOSIZE | SWP_NOZORDER | SWP_DRAWFRAME);
	}

	if (dlg.DoModal() == IDOK)
	{
		TRACE(_T("name %s \n"),dlg.m_strName);
		if (dlg.m_strName == _T("MASTER")) dlg.m_strName = _T("MASTERSETTINGS");
		strPath += _T("\\");
		strPath += dlg.m_strName;
		strPath += _T(".BTC");
		SaveBackUpFile (strPath,&pApp->m_Settings);
		//SaveBackUpUpAppSettingFile(m_strName,&pApp->m_Settings);
	}

	// Close the keyboard
	hWnd = ::FindWindow(NULL,_T("On-Screen Keyboard"));
	if (hWnd > 0)
	{
		::SendMessage(hWnd,WM_SYSCOMMAND,SC_CLOSE,0);
	}

	// Display
	dlg.m_strName += _T(" file Saved!");
	OkDlg(dlg.m_strName,false);

}


void CHMIView::OnToolsLoad()
{
	CString strPath,num;
	CString strFilename;
	//STARTUPINFO si;
	KEYPADDATA data;
	CGetName dlg;
	CHMIApp* pApp = (CHMIApp*)AfxGetApp();

	// Get path number
	data.dbIncrement = 0;
	data.dbMin = 0;
	data.dbValue = 0;
	data.dbMax = 0;
	data.lpTitle = _T("Enter User Pin number");
	data.nDecimalPlaces = 0;
	data.bPassWord = false;
	if (!GetNumDlg(&data)){
		return;			
	}

	// Get the path
	bool CodeValid = false;
	strPath = BACKUP_PATH;
	num.Format(_T("SET%d"),(int)data.dbValue);
	strPath+=num;
	if (!CreateDirectory(strPath,NULL))
	{
		if (GetLastError() == ERROR_ALREADY_EXISTS)
		{
			CodeValid = true;
			TRACE(_T("Code in use....create.... %s \n"),strPath);
		}
		//OkDlg(_T("Code Already used !     Select a different code."),true);
	}

	// 
	if (!CodeValid)
	{
		OkDlg(_T("Invalid Code!"),true);
		return;
	}

	CGetBackupName dlgGetName;
	dlgGetName.m_strNameArray.SetSize(2000);
	WIN32_FIND_DATA fd;
	::SetCurrentDirectory(strPath);
	HANDLE hFind = ::FindFirstFile (_T ("*.*"), &fd);
	dlgGetName.m_NumberOfNames=0;
	if (hFind != INVALID_HANDLE_VALUE)
	{
		do{
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)){
				TRACE (_T ("%s\n"), fd.cFileName);
				dlgGetName.m_strNameArray[dlgGetName.m_NumberOfNames++] = fd.cFileName;
				//dlgGetName.m_ctlListBox.AddString(fd.cFileName);
			}
		} while (::FindNextFile (hFind, &fd));
		::FindClose (hFind);
	}

	//Load file
	if (dlgGetName.DoModal() == IDOK)
	{
		//TRACE(_T("name %s \n"),dlg.m_strName);	
		strPath += _T("\\");
		strPath += dlgGetName.m_strName;
		if (LoadBackUpFile (strPath,&pApp->m_Settings))
		{
			dlgGetName.m_strName += _T(" Loaded!");
			OkDlg(dlgGetName.m_strName,false);
			OnApplySettings(0,0);
		}
		else
		{
			OkDlg(_T("Error Loading file!"),false);						
		}
	}
}


//----------------------------------------------------------------------
// SaveBackUpDataFile - Save backup application settings.
//
//----------------------------------------------------------------------
bool CHMIView::SaveBackUpFile (LPCTSTR lpMsg,ALLSETTINGS* pData)
{
	DWORD nBytes;
	BOOL bResult;
	unsigned char* buffer = (unsigned char*)pData;
	CString strFile;
	strFile = lpMsg;
	TRACE(_T("Backup File: %s \n"),strFile);

	// Open the file.
	HANDLE hFile = CreateFile (strFile, GENERIC_WRITE,FILE_SHARE_WRITE, NULL, CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
		TRACE("Error File not found!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
        return false;
    }

	// Save the parameter file
	bResult = WriteFile(hFile, buffer, sizeof(ALLSETTINGS), &nBytes, NULL) ; 
	TRACE("Save the data file... Bytes Written: %d \n",nBytes);
	CloseHandle(hFile);

	return true;
}
//----------------------------------------------------------------------
// LoadBackUpFile - Load backup application settings.
//
//----------------------------------------------------------------------
bool CHMIView::LoadBackUpFile (LPCTSTR lpMsg,ALLSETTINGS* pData)
{
	DWORD nBytes;
	BOOL bResult;
	unsigned char* buffer = (unsigned char*)pData;
	CString strFile = lpMsg;

	// Open the file.
    HANDLE hFile = CreateFile (strFile, GENERIC_READ,FILE_SHARE_READ, NULL, OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) 
	{
        //MessageBox (hWnd, TEXT("Couldn't open file"), szAppName, MB_OK);
		//TRACE("No data file exists! Creat the file...\n");
		OkDlg(_T("Data file does not exist!"),true);
		CloseHandle(hFile);
		return false;
    }

	// Load the parameter file
	bResult = ReadFile(hFile, buffer, sizeof(ALLSETTINGS), &nBytes, NULL) ; 
	TRACE("Bytes Read %d\n",nBytes);
	CloseHandle(hFile);
	return true;

}
// 
LRESULT CHMIView::OnLoadMaster (WPARAM wParam, LPARAM lParam)
{
	CHMIApp* pApp = (CHMIApp*)AfxGetApp();
	if (YesNoDlg(_T("Do you want to load the MASTER setting file?")))
	{
		if (LoadBackUpFile (MASTERDATAFILE,&pApp->m_Settings))
		{
			OkDlg(_T("Master Settings Loaded!"),false);
			OnApplySettings(0,0);
		}
		else
		{
			OkDlg(_T("Error Loading file!"),false);						
		}
	}

	return 0;
}
LRESULT CHMIView::OnLoadUser (WPARAM wParam, LPARAM lParam)
{
	CHMIApp* pApp = (CHMIApp*)AfxGetApp();
	OnToolsLoad();
	OnApplySettings(0,0);
	OnViewSettingsSave();
	SaveAppCounterFile (&pApp->m_Counters);
	return 0;
}
LRESULT CHMIView::OnSaveUser (WPARAM wParam, LPARAM lParam)
{
	OnToolsSave();
	return 0;
}

void CHMIView::OnBnClickedUserSettings()
{
	//
	// If the dialog box already exists, display it.
	if (m_pSettings != NULL){
		m_pSettings->SetFocus ();
		return;
	}

	// Password
	//if (CheckPassword()==false)
		//return;

	//
	// If the dialog box doesn't already exist, create it.
	// Change Settings
	CHMIApp* pApp = (CHMIApp*)AfxGetApp();
	m_pSettings = DlgUserSettings(&pApp->m_Settings,this,&m_pSettings);
}

void CHMIView::OnBnClickedVisionSettings()
{
	//
	// If the dialog box already exists, display it.
	if (m_pSettings != NULL){
		m_pSettings->SetFocus ();
		return;
	}

	// Password
	if (CheckPassword()==false)
		return;

	//
	// If the dialog box doesn't already exist, create it.
	// Change Settings
	CHMIApp* pApp = (CHMIApp*)AfxGetApp();
	m_pSettings = DlgSettings(&pApp->m_Settings,this,&m_pSettings);
}
void CHMIView::OnBnClickedMotionSettings()
{
	//
	// If the dialog box already exists, display it.
	if (m_pSettings != NULL){
		//AfxMessageBox(_T(""));
		m_pSettings->SetFocus ();
		return;
	}

	// Password
	if (CheckPassword()==false)
		return;

	//
	// If the dialog box doesn't already exist, create it.
	// Change Settings
	CHMIApp* pApp = (CHMIApp*)AfxGetApp();
	m_pSettings = DlgMotionSettings(&pApp->m_Settings.MotionSettings1,this,&m_pSettings);
}

LRESULT CHMIView::OnClearAlarm (WPARAM wParam, LPARAM lParam)
{
	CHMIApp* pApp = (CHMIApp*)AfxGetApp();
	CPmac* pmac = &pApp->m_pmac;

	switch (wParam)
	{
	case 0:
		TRACE("CCVISView::OnClearAlarm 1\n");
		pmac->SetVariable(_T('M'),26,(long)0);
		m_bAlarmLatch[0] = false;
		break;
	case 1:
		TRACE("CCVISView::OnClearAlarm 2\n");
		pmac->SetVariable(_T('M'),27,(long)0);
		m_bAlarmLatch[1] = false;
		break;
	case 2:
		TRACE("CCVISView::OnClearAlarm 3\n");
		pmac->SetVariable(_T('M'),28,(long)0);
		m_bAlarmLatch[2] = false;
		break;
	case 3:
		TRACE("CCVISView::OnClearAlarm 3\n");
		pmac->SetVariable(_T('M'),29,(long)0);
		m_bAlarmLatch[3] = false;
		break;
	case 4:
		TRACE("CCVISView::OnClearAlarm 4\n");
		pmac->SetVariable(_T('M'),30,(long)0);
		m_bAlarmLatch[4] = false;
		break;
	case 5:
		TRACE("CCVISView::OnClearAlarm 5\n");
		m_bAlarmLatch[5] = false;
		pmac->SetVariable(_T('M'),31,(long)0);
		break;
	case 6:
		TRACE("CCVISView::OnClearAlarm 6\n");
		//m_bShuntTempFaultLatch = false;
		//pmac->SetVariable(_T('M'),103,(long)0);
		//m_bAlarmLatch = false;
		break;
	case 7:
		TRACE("CCVISView::OnClearAlarm 7 \n");
		m_bAlarmLatch[7] = false;
		pmac->SetVariable(_T('M'),4317,(long)0);
		break;
	case 8:
		TRACE("CCVISView::OnClearAlarm 8 \n");
		m_bAlarmLatch[8] = false;
		pmac->SetVariable(_T('M'),4318,(long)0);
		break;
	case 9:
		TRACE("CCVISView::OnClearAlarm 9 \n");
		m_bAlarmLatch[9] = false;
		pmac->SetVariable(_T('M'),4319,(long)0);
		break;
	case 10:
		TRACE("CCVISView::OnClearAlarm 10 \n");
		m_bAlarmLatch[10] = false;
		pmac->SetVariable(_T('M'),4320,(long)0);
		break;
	case 11:
		TRACE("CCVISView::OnClearAlarm 11 \n");
		m_bAlarmLatch[11] = false;
		pmac->SetVariable(_T('M'),4321,(long)0);
		break;
	case 12:
		TRACE("CCVISView::OnClearAlarm 12 \n");
		m_bAlarmLatch[12] = false;
		pmac->SetVariable(_T('M'),4322,(long)0);
		break;
	}
	return 0;
}


// OnApplySettings
LRESULT CHMIView::OnApplySettings (WPARAM wParam, LPARAM lParam)
{
	TRACE("CCVISView::OnApplySettings \n");
	CHMIApp* pApp = (CHMIApp*)AfxGetApp();
	CPmac* pmac = &pApp->m_pmac;
	SetPmacPVariables(pApp,pmac);

	//pApp->ApplySettings();
	//AfxMessageBox(_T("Apply Settings "));
	//SetAlignMode(pApp,TRUE);
	pApp->m_bSettingsModifyied = true;

	// Shear bar
	//pApp->m_mil.m_X[0] = pApp->m_Settings.VisSettings2.x[0];
	//pApp->m_mil.m_X[1] = pApp->m_Settings.VisSettings2.x[1];
	//pApp->m_mil.m_X[2] = pApp->m_Settings.VisSettings2.x[2];
	//pApp->m_mil.m_X[3] = pApp->m_Settings.VisSettings2.x[3];
	//pApp->m_mil.m_X[4] = pApp->m_Settings.VisSettings2.x[4];

	//pApp->m_mil.m_Y[0] = pApp->m_Settings.VisSettings2.y[0];
	//pApp->m_mil.m_Y[1] = pApp->m_Settings.VisSettings2.y[1];
	//pApp->m_mil.m_Y[2] = pApp->m_Settings.VisSettings2.y[2];
	//pApp->m_mil.m_Y[3] = pApp->m_Settings.VisSettings2.y[3];
	//pApp->m_mil.m_Y[4] = pApp->m_Settings.VisSettings2.y[4];

	pApp->m_mil.ApplySettings();


	return 0;
}

//
/////////////////////////////////////////////////
LRESULT CHMIView::OnBtcTimingCheck (WPARAM wParam, LPARAM lParam)
{
	m_btnTimingCheck.SetLightOn(1);
	CHMIApp* pApp = (CHMIApp*)AfxGetApp();
	CPmac* pmac = &pApp->m_pmac;
	pmac->DPRSet(DPR_OFFSET_BTCMODE,(short)2);
	return 0;
}

// 
/////////////////////////////////////////////////
LRESULT CHMIView::OnGetPmacMotorPosition (WPARAM wParam, LPARAM lParam)
{
	//LPCTSTR lpsz = (LPCTSTR)wParam;
	//TRACE(_T("%s \n"),lpsz);
	CHMIApp* pApp = (CHMIApp*)AfxGetApp();
	CPmac* pmac = &pApp->m_pmac;
	double pos = pmac->GetMotorPosition((int)wParam,1);
	return (LRESULT)pos;
	//int NumChars;
	//BSTR resBuff;
	//CString strCmd = lpsz;
	// Get the response
	//NumChars = pmac->GetResponse(strCmd,&resBuff);
}
// 
/////////////////////////////////////////////////
LRESULT CHMIView::OnGetPmacVariable (WPARAM wParam, LPARAM lParam)
{
	TRACE("OnGetPmacVariable \n");
	//return 0;

	CHMIApp* pApp = (CHMIApp*)AfxGetApp();
	CPmac* pmac = &pApp->m_pmac;
	char ch = wParam;
	long num = lParam;
	long data;
	pmac->GetVariable(ch,num,&data);
	return data;
}

// 
/////////////////////////////////////////////////
LRESULT CHMIView::OnRestoreSettings (WPARAM wParam, LPARAM lParam)
{
	TRACE("OnRestoreSettings...On Restore settings \n");
	OnApplySettings(0,0);
	return 0;
}

// 
/////////////////////////////////////////////////
LRESULT CHMIView::OnSaveSettings (WPARAM wParam, LPARAM lParam)
{
	CHMIApp* pApp = (CHMIApp*)AfxGetApp();
	//SetAlignMode(pApp,TRUE);
	TRACE("OnSaveSettings...On save settings wParam %d   lParam %d \n",wParam,lParam);
	OnApplySettings(0,0);
	OnViewSettingsSave();
	SaveAppCounterFile (&pApp->m_Counters);

	return 0;
}

void CHMIView::OnBnClickedDisplaySel1()
{
	CButton* pBtn;
	CHMIApp* pApp = (CHMIApp*)AfxGetApp();
	pApp->m_mil.RunThreadData.pHook1->DisplaySelect = 0;
	pBtn = (CButton*)GetDlgItem(IDC_DISPLAY_SEL1);
	pBtn->EnableWindow(0);
	pBtn = (CButton*)GetDlgItem(IDC_DISPLAY_SEL2);
	pBtn->EnableWindow(1);
	pBtn = (CButton*)GetDlgItem(IDC_DISPLAY_SEL3);
	pBtn->EnableWindow(1);
	pBtn = (CButton*)GetDlgItem(IDC_DISPLAY_SEL4);
	pBtn->EnableWindow(1);
}


void CHMIView::OnBnClickedDisplaySel2()
{
	CButton* pBtn;
	CHMIApp* pApp = (CHMIApp*)AfxGetApp();
	pApp->m_mil.RunThreadData.pHook1->DisplaySelect = 1;
	pBtn = (CButton*)GetDlgItem(IDC_DISPLAY_SEL1);
	pBtn->EnableWindow(1);
	pBtn = (CButton*)GetDlgItem(IDC_DISPLAY_SEL2);
	pBtn->EnableWindow(0);
	pBtn = (CButton*)GetDlgItem(IDC_DISPLAY_SEL3);
	pBtn->EnableWindow(1);
	pBtn = (CButton*)GetDlgItem(IDC_DISPLAY_SEL4);
	pBtn->EnableWindow(1);

}

void CHMIView::OnBnClickedDisplaySel3()
{
	CButton* pBtn;
	CHMIApp* pApp = (CHMIApp*)AfxGetApp();
	pApp->m_mil.RunThreadData.pHook1->DisplaySelect = 2;
	pBtn = (CButton*)GetDlgItem(IDC_DISPLAY_SEL1);
	pBtn->EnableWindow(1);
	pBtn = (CButton*)GetDlgItem(IDC_DISPLAY_SEL2);
	pBtn->EnableWindow(1);
	pBtn = (CButton*)GetDlgItem(IDC_DISPLAY_SEL3);
	pBtn->EnableWindow(0);
	pBtn = (CButton*)GetDlgItem(IDC_DISPLAY_SEL4);
	pBtn->EnableWindow(1);
}
void CHMIView::OnBnClickedDisplaySel4()
{
	CButton* pBtn;
	CHMIApp* pApp = (CHMIApp*)AfxGetApp();
	pApp->m_mil.RunThreadData.pHook1->DisplaySelect = 3;
	pBtn = (CButton*)GetDlgItem(IDC_DISPLAY_SEL1);
	pBtn->EnableWindow(1);
	pBtn = (CButton*)GetDlgItem(IDC_DISPLAY_SEL2);
	pBtn->EnableWindow(1);
	pBtn = (CButton*)GetDlgItem(IDC_DISPLAY_SEL3);
	pBtn->EnableWindow(1);
	pBtn = (CButton*)GetDlgItem(IDC_DISPLAY_SEL4);
	pBtn->EnableWindow(0);
}
void CHMIView::OnBnClickedShowSherbarPoints()
{
	CButton* pBtn;
	CHMIApp* pApp = (CHMIApp*)AfxGetApp();
	if (pApp->m_mil.m_OverlayOn)
	{
		pApp->m_mil.HideShearBarPoints();
		pBtn = (CButton*)GetDlgItem(IDC_SHOW_SHERBAR_POINTS);
		pBtn->SetIcon (AfxGetApp ()->LoadIcon (IDI_HIDE_OVERLAY));
	}
	else
	{
		pApp->m_mil.ShowShearBarPoints();
		pBtn = (CButton*)GetDlgItem(IDC_SHOW_SHERBAR_POINTS);
		pBtn->SetIcon (AfxGetApp ()->LoadIcon (IDI_SHOW_OVERLAY));
	}

	//CButton* pBtn;
	//CHMIApp* pApp = (CHMIApp*)AfxGetApp();
	//if (!pApp->m_mil.m_OverlayOn)
	//{
	//	pApp->m_mil.ShowLanes();
	//	pBtn = (CButton*)GetDlgItem(IDC_SHOW_SHERBAR_POINTS);
	//	pBtn->SetIcon (AfxGetApp ()->LoadIcon (IDI_SHOW_OVERLAY));
	//}
	//else
	//{
	//	pApp->m_mil.HideLanes();
	//	pBtn = (CButton*)GetDlgItem(IDC_SHOW_SHERBAR_POINTS);
	//	pBtn->SetIcon (AfxGetApp ()->LoadIcon (IDI_HIDE_OVERLAY));
	//}

}

BEGIN_EVENTSINK_MAP(CHMIView, CFormView)
	ON_EVENT(CHMIView, IDC_GDI_START, DISPID_CLICK, CHMIView::ClickGdiStart, VTS_NONE)
	ON_EVENT(CHMIView, IDC_GDI_START2, DISPID_CLICK, CHMIView::ClickGdiStart, VTS_NONE)
	ON_EVENT(CHMIView, IDC_GDI_START3, DISPID_CLICK, CHMIView::ClickGdiStart, VTS_NONE)
	ON_EVENT(CHMIView, IDC_INFEED_DOWN, DISPID_CLICK, CHMIView::ClickGdiFeedDown, VTS_NONE)
	ON_EVENT(CHMIView, IDC_GDI_STOP, DISPID_CLICK, CHMIView::ClickGdiStop, VTS_NONE)
	ON_EVENT(CHMIView, IDC_GDI_STOP2, DISPID_CLICK, CHMIView::ClickGdiStop, VTS_NONE)
	ON_EVENT(CHMIView, IDC_GDI_STOP3, DISPID_CLICK, CHMIView::ClickGdiStop, VTS_NONE)
	ON_EVENT(CHMIView, IDC_MODE_WASH, DISPID_CLICK, CHMIView::ClickModeWash, VTS_NONE)
	ON_EVENT(CHMIView, IDC_MODE_RUN, DISPID_CLICK, CHMIView::ClickModeRun, VTS_NONE)
	ON_EVENT(CHMIView, IDC_BLOWER, DISPID_CLICK, CHMIView::ClickBlower, VTS_NONE)
	ON_EVENT(CHMIView, IDC_BELEVATOR, DISPID_CLICK, CHMIView::ClickBelevator, VTS_NONE)
	ON_EVENT(CHMIView, IDC_BTC_RESET, DISPID_CLICK, CHMIView::ClickBtcReset, VTS_NONE)
	ON_EVENT(CHMIView, IDC_LOAD_PAPER, DISPID_CLICK, CHMIView::ClickLoadPaper, VTS_NONE)
	ON_EVENT(CHMIView, IDC_TIMING_CHECK, DISPID_CLICK, CHMIView::ClickTimingCheck, VTS_NONE)
	ON_EVENT(CHMIView, IDC_SLICE_COUNT, DISPID_CLICK, CHMIView::ClickSliceCount, VTS_NONE)
	ON_EVENT(CHMIView, IDC_PAPER_LENGTH, DISPID_CLICK, CHMIView::ClickPaperLength, VTS_NONE)
	ON_EVENT(CHMIView, IDC_BTC_READY, DISPID_CLICK, CHMIView::ClickBtcReady, VTS_NONE)
	ON_EVENT(CHMIView, IDC_BTC_READY2, DISPID_CLICK, CHMIView::ClickBtcReady, VTS_NONE)
	ON_EVENT(CHMIView, IDC_BLADE_SPEED, DISPID_CLICK, CHMIView::ClickBladeSpeed, VTS_NONE)
	ON_EVENT(CHMIView, IDC_BLADE_SPEED2, DISPID_CLICK, CHMIView::ClickBladeSpeed, VTS_NONE)
	ON_EVENT(CHMIView, IDC_ALIGN_OFFSET, DISPID_CLICK, CHMIView::ClickAlignOffset, VTS_NONE)
	ON_EVENT(CHMIView, IDC_SLICE_THICKNESS, DISPID_CLICK, CHMIView::ClickSliceThickness, VTS_NONE)
	ON_EVENT(CHMIView, IDC_BLADE_SPEED3, DISPID_CLICK, CHMIView::SlicerDischargeSpeed, VTS_NONE)
	ON_EVENT(CHMIView, IDC_SHEET_COUNT, DISPID_CLICK, CHMIView::ClickSheetCount, VTS_NONE)
	ON_EVENT(CHMIView, IDC_SHEET_COUNT_SHIFT, DISPID_CLICK, CHMIView::ClickSheetCountShift, VTS_NONE)
	ON_EVENT(CHMIView, IDC_GDIIOSTATUSCTRL_OUTPUTS, 1, CHMIView::IoClickedGdiiostatusctrlOutputs, VTS_I2)
	ON_EVENT(CHMIView, IDC_GDIIOSTATUSCTRL_SLICER_OUTPUTS, 1, CHMIView::IoClickedGdiiostatusctrlOutputs2, VTS_I2)
	ON_EVENT(CHMIView, IDC_GDIIOSTATUSCTRL_REJECT_OUTPUTS, 1, CHMIView::IoClickedGdiiostatusctrlOutputs3, VTS_I2)
	ON_EVENT(CHMIView, IDC_OUTPUT_FORCE, DISPID_CLICK, CHMIView::ClickOutputForce, VTS_NONE)
	ON_EVENT(CHMIView, IDC_OUTPUT_FORCE2, DISPID_CLICK, CHMIView::ClickOutputForce2, VTS_NONE)
	ON_EVENT(CHMIView, IDC_OUTPUT_FORCE3, DISPID_CLICK, CHMIView::ClickOutputForce3, VTS_NONE)
	ON_EVENT(CHMIView, IDC_INFEED_REVERSE, DISPID_MOUSEDOWN, CHMIView::MouseDownInfeedReverse, VTS_I2 VTS_I2 VTS_I4 VTS_I4)
	ON_EVENT(CHMIView, IDC_INFEED_REVERSE, DISPID_MOUSEUP, CHMIView::MouseUpInfeedReverse, VTS_I2 VTS_I2 VTS_I4 VTS_I4)
	ON_EVENT(CHMIView, IDC_GDI_JOG_FAST, DISPID_MOUSEDOWN, CHMIView::MouseDownGdiJogFast, VTS_I2 VTS_I2 VTS_I4 VTS_I4)
	ON_EVENT(CHMIView, IDC_GDI_JOG_FAST, DISPID_MOUSEUP, CHMIView::MouseUpGdiJogFast, VTS_I2 VTS_I2 VTS_I4 VTS_I4)
	ON_EVENT(CHMIView, IDC_GDI_JOG_SLOW, DISPID_MOUSEDOWN, CHMIView::MouseDownGdiJogSlow, VTS_I2 VTS_I2 VTS_I4 VTS_I4)
	ON_EVENT(CHMIView, IDC_GDI_JOG_SLOW, DISPID_MOUSEUP, CHMIView::MouseUpGdiJogSlow, VTS_I2 VTS_I2 VTS_I4 VTS_I4)
	ON_EVENT(CHMIView, IDC_BTC_PANIC, DISPID_CLICK, CHMIView::ClickBtcPanic, VTS_NONE)	
	ON_EVENT(CHMIView, IDC_GDI_BLADE_BRAKE, DISPID_MOUSEDOWN, CHMIView::BladeBrake, VTS_I2 VTS_I2 VTS_I4 VTS_I4)

END_EVENTSINK_MAP()


void CHMIView::ClickGdiStart()
{
	CHMIApp* pApp = (CHMIApp*)AfxGetApp();
	CPmac* pmac = &pApp->m_pmac;
	//pmac->SendCommand(_T("#8j+"));
	pmac->SetVariable(_T('P'),710,(long)1);
	m_ctlStart.SetLight(1);
	m_ctlStart2.SetLight(1);
	m_ctlStart3.SetLight(1);
	m_ctlStop.SetLight(0);
	m_ctlStop2.SetLight(0);
	m_ctlStop3.SetLight(0);
	SaveAppCounterFile (&pApp->m_Counters);

	//m_ctlStop.SetTitleText1(_T("BTC"));
	m_ctlStop.SetTitleText2(_T("Stop"));
	m_ctlStop2.SetTitleText2(_T("Stop"));
	m_ctlStop3.SetTitleText2(_T("Stop"));
	//m_ctlStop.SetTitleText1(_T("Machine"));
	//m_ctlStop2.SetTitleText1(_T("Machine"));
	//m_ctlStop3.SetTitleText1(_T("Machine"));

	//m_ctlStop.SetTitleText2(_T("Stop"));
	//m_ctlStop2.SetTitleText2(_T("Stop"));
	//m_ctlStop3.SetTitleText2(_T("Stop"));

	// Clear the Fault latches
	if (m_bMotorFaultLatch[0]==true 
	 || m_bMotorFaultLatch[1]==true
	 || m_bMotorFaultLatch[2]==true
	 || m_bMotorFaultLatch[3]==true
	 || m_bMotorFaultLatch[4]==true
	 || m_bMotorFaultLatch[5]==true
	 || m_bMotorFaultLatch[6]==true
	 || m_bMotorFaultLatch[7]==true
	 || m_bMotorFaultLatch[8]==true
	 || m_bMotorFaultLatch[9]==true
	 || m_bMotorFaultLatch[10]==true
	 || m_bMotorFaultLatch[11]==true
	 || m_bMotorFaultLatch[12]==true
	 || m_bMotorFaultLatch[13]==true
	 || m_bMotorFaultLatch[14]==true
	 || m_bMotorFaultLatch[15]==true)
	{
		//m_csLatch.Lock();
		TRACE(_T("On Start....................fault latch set \n"));
	    ::ZeroMemory (&m_bMotorFaultLatch[0], sizeof (m_bMotorFaultLatch));
	    ::ZeroMemory (&m_bMotorWarnLatch[0], sizeof (m_bMotorWarnLatch));
	    TRACE("Clear the fault latches Size %d\n",sizeof(m_bMotorWarnLatch));
		//m_csLatch.Unlock();
	}

	// Que Start
	pApp->m_mil.HookQue();

}

void CHMIView::ClickGdiStop()
{
	CHMIApp* pApp = (CHMIApp*)AfxGetApp();
	CPmac* pmac = &pApp->m_pmac;

	// Ignore double clicks
	if (m_BtcData.GlobalStatus == GS_STOPPING)
	{
		return;
	}

	// Stop the Feed
	if (m_BtcData.StatusBits.FeedStartStop)
	{
		if (YesNoDlg(_T("Do you want to stop the Belly Feed?")))
		{
			pmac->SetVariable(_T('M'),23,(long)0);
		}
		return;
	}

	// Cycle stop
	//m_bStopLatch = true;
	pmac->SetVariable(_T('P'),711,(long)1);
	m_ctlStart.SetLight(0);
	m_ctlStart2.SetLight(0);
	m_ctlStart3.SetLight(0);
	m_ctlStop.SetLight(1);
	m_ctlStop2.SetLight(1);
	m_ctlStop3.SetLight(1);
	//if (m_BtcData.GlobalStatus == GS_RUNNING)
	//{
	//	m_ParkLatch = true;
	//}

	// Save counters
	SaveAppCounterFile (&pApp->m_Counters);

	// Que stop
	pApp->m_mil.UnHookQue();

	//m_ctlBtcReady.SetLightOn(m_BtcData.StatusBits.FeedStartStop);
	//m_ctlBtcReady2.SetLightOn(m_BtcData.StatusBits.FeedStartStop);
	//OkDlg(_T("Belly Feed Stopped"),false);

}
void CHMIView::ClickModeWash()
{
	CHMIApp* pApp = (CHMIApp*)AfxGetApp();
	CPmac* pmac = &pApp->m_pmac;
	pmac->DPRSet(DPR_OFFSET_BTCMODE,(short)1);
	m_ctlRunMode.SetLight(0);
	m_ctlWashMode.SetLight(1);

}
void CHMIView::ClickModeRun()
{
	CHMIApp* pApp = (CHMIApp*)AfxGetApp();
	CPmac* pmac = &pApp->m_pmac;
	pmac->DPRSet(DPR_OFFSET_BTCMODE,(short)0);
	m_ctlRunMode.SetLight(1);
	m_ctlWashMode.SetLight(0);
}

void CHMIView::ClickBlower()
{
	CHMIApp* pApp = (CHMIApp*)AfxGetApp();
	CPmac* pmac = &pApp->m_pmac;
	if (m_BtcData.BtcOutputs.Blower == 0)
	{
		pmac->SetVariable(_T('M'),36,(long)1);
		m_ctlBlower.SetLight(1);
	}
	else
	{
		pmac->SetVariable(_T('M'),36,(long)0);
		m_ctlBlower.SetLight(0);
	}

}

void CHMIView::ClickBelevator()
{
	CHMIApp* pApp = (CHMIApp*)AfxGetApp();
	CPmac* pmac = &pApp->m_pmac;
	if (m_BtcData.BtcOutputs.BelevatorLight == 0)
	{
		pmac->SetVariable(_T('M'),39,(long)1);
		m_ctlBelevator.SetLight(1);
	}
	else
	{
		pmac->SetVariable(_T('M'),39,(long)0);
		m_ctlBelevator.SetLight(0);
	}

}

void CHMIView::ClickGdiFeedDown()
{
	CHMIApp* pApp = (CHMIApp*)AfxGetApp();
	CPmac* pmac = &pApp->m_pmac;

	if (m_BtcData.SlicerOutputs.FeedNoseDown == 0 || m_BtcData.SlicerOutputs.FeedRollersDown == 1)
	{
		pmac->SetVariable(_T('M'),48,(long)0);
		pmac->SetVariable(_T('M'),51,(long)1);
		m_btnFeedUpDn.SetLight(1);
	}
	else
	{
		if (m_BtcData.GlobalStatus != 4)
		{
			pmac->SetVariable(_T('M'),48,(long)1);
			pmac->SetVariable(_T('M'),51,(long)0);
			m_btnFeedUpDn.SetLight(0);
		}
	}

}

////////////////////////////////////////////////////////////////////////////////////////////
void CHMIView::ClickBtcReset()
{
	//CPmac Pmac1;
	//Pmac1.Init(0);
	//CPmac* pmac = &Pmac1; pApp->m_pmac
	CHMIApp* pApp = (CHMIApp*)AfxGetApp();
	OPENPMACDATA pmacData1;
	OPENPMACDATA pmacData2;
	CPmac* pmac = &pApp->m_pmac;
	int Count = 0;
	HELPERPARAM Wait;
	Wait.bRun = TRUE;
	Wait.nWaitTime = 5000;
	m_bPmacBusy = true;
	CString str;
	CString strResetCommand;
	int SlaveErrors = 0;
	bool GetStatus;

	if (m_BtcData.GlobalStatus != GS_ESTOP)
	{
		if (!YesNoDlg(_T("Machine is not E-STOPPED. Do you want to continue anyway?")))
		{
			m_bPmacBusy = false;
			return;
		}	
	}

	// Set the string
	if (pApp->m_Settings.HMISettings.bFullReset)
	{
		str = _T("\nDo you want to reset all drives?");	
	}
	else
	{
		str = _T("\nDo you want to reset?");
	}

	//_T ("D:\\BTCDATA\\UpLoadFile.CFG")
	if (YesNoDlg(str))
	{
		CUIHelperThread* pThread = (CUIHelperThread*)AfxBeginThread (RUNTIME_CLASS (CUIHelperThread));
		Sleep(100);
		if (::WaitForSingleObject (pThread->m_hThread, 500) == WAIT_OBJECT_0)
		{
			TRACE("\n Error! The thread is not running!!! \n");
			Sleep(200);
		}
		//else
		//{
		//	TRACE("\n The thread IS Running!!! \n");
		//}

		// Disable and turn off master and slave high voltage
		//----------------------------------------------//
		if (pApp->m_Settings.HMISettings.nPmacReset)
		{
			//AfxMessageBox(_T("Using $$$"));
			strResetCommand = _T("$$$");
			if (m_BtcData.GlobalStatus == GS_ESTOP)
			{
				pThread->SetMessage(_T("Bus Power is Off..."));
				pThread->SetDelayTime(4500);
				pmac->SendCommand(_T("P143=0M37=0M49=0"));
				Sleep(1000);
			}
			else
			{
				// Wait for bus power to bleed off.
				pThread->SetMessage(_T("Turning Off Bus Power..."));
				pThread->SetDelayTime(5000);
				pmac->SendCommand(_T("P143=0M37=0M49=0"));
				Sleep(5000);
				pThread->SetDelayTime(4500);
			}
		}
		else
		{
			pThread->SetMessage(_T("Sending ENABLE PLC1..."));
			strResetCommand = _T("ENABLE PLC1");		
			pThread->SetDelayTime(2000);
			Sleep(1000);
		}
		TRACE("\n PMAC RESET COMMAND %S \n",strResetCommand);
		//----------------------------------------------//

		// Reset slave PMACs
		//----------------------------------------------//
		if (pApp->m_Settings.HMISettings.bFullReset)
		{
			// Reset Slave 6-Axis
			//------------------------------------------//
#ifdef OSCEOLA_LAYOUT
			pmacData1.nDevice = pApp->m_Settings.HMISettings.PmacID;
#else
			pmacData1.nDevice = 1;
#endif
			pThread->SetMessage(_T("Reset Slave 6-Axis"));
			CWinThread* pThreadOpen = AfxBeginThread (OpenPmacThreadFunc, &pmacData1,THREAD_PRIORITY_NORMAL,CREATE_SUSPENDED);
			pThreadOpen->ResumeThread();
			HANDLE hThread = pThreadOpen->m_hThread;     // Save the thread handle
			if (::WaitForSingleObject (hThread, 1000) == WAIT_OBJECT_0)
			{
				TRACE("\n PMAC 6-AXIS is open!!!The thread no longer exists. %d \n",pmacData1.Pmac.IsPmacOpen());
				//pmacData1.Pmac.SendCommand(_T("ENABLE PLC1"));
				pmacData1.Pmac.SendCommand(strResetCommand);
			}
			else
			{
				TRACE("Error! The thread is still running... PMAC not open!\n");
				TRACE("Error %d \n",pmacData1.Pmac.IsPmacOpen());
				SlaveErrors++;
				pThread->SetMessage(_T("Slave 6-Axis Reset Error!"));
				pThread->SetDelayTime(20000);
				pThread->ResetTimer();
				::WaitForSingleObject (hThread, 20000);
			}
			//------------------------------------------//

			// Reset Slave 8-Axis
			//------------------------------------------//
#ifndef OSCEOLA_LAYOUT
			if (pmacData1.Pmac.IsPmacOpen())
			{
				pmacData2.nDevice = 2;
				pThread->SetMessage(_T("Reset Slave 8-Axis"));
				CWinThread* pThreadOpen2 = AfxBeginThread (OpenPmacThreadFunc, &pmacData2,THREAD_PRIORITY_NORMAL,CREATE_SUSPENDED);
				pThreadOpen2->ResumeThread();
				HANDLE hThread2 = pThreadOpen2->m_hThread;     // Save the thread handle
				if (::WaitForSingleObject (hThread2, 1000) == WAIT_OBJECT_0)
				{
					TRACE("\n PMAC 8-AXIS is open!!!The thread no longer exists. %d \n",pmacData2.Pmac.IsPmacOpen());
					//pmacData2.Pmac.SendCommand(_T("ENABLE PLC1"));
					pmacData2.Pmac.SendCommand(strResetCommand);
				}
				else
				{
					TRACE("Error! The thread is still running... PMAC not open!\n");
					TRACE("Error %d \n",pmacData2.Pmac.IsPmacOpen());
					SlaveErrors++;
					pThread->SetMessage(_T("Slave 8-Axis Reset Error!"));
					pThread->SetDelayTime(20000);
					pThread->ResetTimer();
					::WaitForSingleObject (hThread2, 20000);
				}
			}
#endif
			//------------------------------------------//
			Sleep(500);
		}
		//----------------------------------------------//

		// Reset MASTER PMAC
		//----------------------------------------------//
		pThread->SetMessage(_T("Reset Master Drive"));
		pmac->SendCommand(strResetCommand);
		if (pApp->m_Settings.HMISettings.nPmacReset)
		{
			//AfxMessageBox(_T("Using $$$"));
			Sleep(1000);
			pmac->ClosePmac();
			Sleep(2500);
			pmac->Init(0);
		}
		else
		{
			Sleep(1000);
		}
		pThread->Close();
		//----------------------------------------------//

		// Finish the reset
		//----------------------------------------------//
		long pvar=1;
		int count=0;
		GetStatus = pmac->GetVariable(_T('P'),105,&pvar);
		if (!GetStatus)
		{
			TRACE("GetVariable error! \n");
			//AfxMessageBox(_T("GetVariable error 1"));

		}
		//else
		//{
		//	AfxMessageBox(_T("Reset OK"));		
		//}
		while (pvar==1 && count < 20)
		{
			count++;
			Sleep(100);
			GetStatus = pmac->GetVariable(_T('P'),105,&pvar);
			if (!GetStatus)
			{
				TRACE("GetVariable error! \n");
				//AfxMessageBox(_T("GetVariable error 2"));
			}
		}

		if (pvar==0 && SlaveErrors==0)
		{
			OkDlg(_T("Reset Complete!"),false);
		}
		else
		{
			OkDlg(_T("Reset Failed!"),false);
		}
		//----------------------------------------------//

		// Set the P-Varibles
		SetPmacPVariables(pApp,pmac);

		// Set the DPRAM memory
		pmac->DPRSet(DPR_OFFSET_MOTORBITS,(long)0xFFFF);
		pmac->DPRSet(DPR_OFFSET_TOTAL_SHEET,pApp->m_Counters.TotalSheetCount);
		pmac->DPRSet(DPR_OFFSET_SHEET_COUNT,pApp->m_Counters.SheetCount);
		GetStatus = pmac->DPRSet(DPR_OFFSET_SHEET_SHIFT,pApp->m_Counters.SheetCountShift);
		if (!GetStatus)
		{
			AfxMessageBox(_T("SetMem error"));
		}

		// Set Main screen values
		m_ctlSliceCount.SetValue(pApp->m_Settings.MotionSettings1.dbPvars[24]);
		m_ctlPaperLenght.SetValue(pApp->m_Settings.MotionSettings1.dbPvars[19]);
		m_ctlBladeSpeed.SetValue(pApp->m_Settings.MotionSettings1.dbPvars[7]);
		m_ctlBladeSpeed2.SetValue(pApp->m_Settings.MotionSettings1.dbPvars[7]);
		m_ctlDischargeDistOffset.SetValue(pApp->m_Settings.MotionSettings1.dbPvars[52]);

		// Save the history
		m_FaultHistory.AddString(_T("BTC Reset"));
		// // m_FaultHistory.SaveStrings();

	}
	m_bPmacBusy = false;

	//_T ("D:\\BTCDATA\\UpLoadFile.CFG")
	//CHMIApp* pApp = (CHMIApp*)AfxGetApp();
	//if (YesNoDlg(_T("Do you want to reboot?")))
	//{
	//	pApp->OnEwfUtilBoot();
	//}
}

void CHMIView::ClickLoadPaper()
{
	CHMIApp* pApp = (CHMIApp*)AfxGetApp();
	CPmac* pmac = &pApp->m_pmac;

	if (m_btnLoadPaper.GetLightOn())
	{
		m_btnLoadPaper.SetLightOn(0);
		pmac->DPRSet(DPR_OFFSET_BTCMODE,(short)0);
		//pmac->SetVariable(_T('M'),32,(long)0);
		return;
	}

	if (YesNoDlg(_T("Do you want to load paper?")))
	{
		m_btnLoadPaper.SetLightOn(1);
		pmac->DPRSet(DPR_OFFSET_BTCMODE,(short)3);
		//pmac->SetVariable(_T('M'),32,(long)1);
	}
	else
	{
		m_btnLoadPaper.SetLightOn(0);
		pmac->DPRSet(DPR_OFFSET_BTCMODE,(short)0);
		//pmac->SetVariable(_T('M'),32,(long)0);
	}

}

void CHMIView::ClickTimingCheck()
{
	CHMIApp* pApp = (CHMIApp*)AfxGetApp();
	CPmac* pmac = &pApp->m_pmac;


	if (m_btnTimingCheck.GetLightOn())
	{
		m_btnTimingCheck.SetLightOn(0);
		pmac->DPRSet(DPR_OFFSET_BTCMODE,(short)0);
		return;
	}

	if (YesNoDlg(_T("Do you want to check Knife timing?")))
	{
		m_btnTimingCheck.SetLightOn(1);
		pmac->DPRSet(DPR_OFFSET_BTCMODE,(short)2);
	}
	else
	{
		m_btnTimingCheck.SetLightOn(0);
		pmac->DPRSet(DPR_OFFSET_BTCMODE,(short)0);
	}

}
void CHMIView::ClickSliceCount()
{
	CHMIApp* pApp = (CHMIApp*)AfxGetApp();
	if (m_BtcData.GlobalStatus == GS_RUNNING)  // Running
	{
		return;
	}

	KEYPADDATA data;
	data.dbIncrement = 	1;
	data.dbMin = m_ctlSliceCount.GetMinValue();
	data.dbMax = m_ctlSliceCount.GetMaxValue();
	data.dbValue = m_ctlSliceCount.GetValue();
	data.lpTitle = _T("Enter Slice Count");
	data.nDecimalPlaces = m_ctlSliceCount.GetPrecision();
	data.bPassWord = false;
	bool bOk = GetNumDlg(&data);
	if (bOk) 
	{			
		//TRACE("slice cont: %f \n",data.dbValue);
		m_ctlSliceCount.SetValue(data.dbValue);
		pApp->m_Settings.MotionSettings1.dbPvars[24] = data.dbValue;
		OnSaveSettings (0,0);
		//pmac->SetVariable(_T('P'),1024,data.dbValue);
	}

}
void CHMIView::ClickPaperLength()
{

	//CWaitCursor wait;

	CHMIApp* pApp = (CHMIApp*)AfxGetApp();
	if (m_BtcData.GlobalStatus == GS_RUNNING)  // Running
	{
		return;
	}

	KEYPADDATA data;
	data.dbIncrement = 	1;
	data.dbMin = m_ctlPaperLenght.GetMinValue();
	data.dbMax = m_ctlPaperLenght.GetMaxValue();
	data.dbValue = m_ctlPaperLenght.GetValue();
	data.lpTitle = _T("Enter Paper Lenght");
	data.nDecimalPlaces = m_ctlPaperLenght.GetPrecision();
	data.bPassWord = false;
	bool bOk = GetNumDlg(&data);
	if (bOk) 
	{			
		m_ctlPaperLenght.SetValue(data.dbValue);
		pApp->m_Settings.MotionSettings1.dbPvars[19] = data.dbValue;

		//pApp->m_Settings.MotionSettings1.dbPvars[56] = 5;     // Sheet Count Preset
		//pApp->m_Settings.MotionSettings1.dbPvars[57] = 150;     // First Slice move time
		//pApp->m_Settings.MotionSettings1.dbPvars[21] = 26000;   // FirstSliceDist
		//pApp->m_Settings.MotionSettings1.dbPvars[4] = 1450;     // Exit Belt delay
		//pApp->m_Settings.MotionSettings1.dbPvars[6] = 13.75;    // Paper Offset
		//pApp->m_Settings.MotionSettings1.dbPvars[13] = 128;     // SetCountVelocity
		//pApp->m_Settings.MotionSettings1.dbPvars[5] = 1.15;     // Drum Offset
		//pApp->m_Settings.MotionSettings1.dbPvars[48] = 100;     // Drum accel time
		//pApp->m_Settings.MotionSettings1.dbPvars[49] = 2;       // Drum accel rate
		//pApp->m_Settings.MotionSettings1.dbPvars[58] = 100;     // Min move time
		//pApp->m_Settings.MotionSettings1.dbPvars[59] = 500;     // Max move time
		//pApp->m_Settings.MotionSettings1.dbPvars[10] = 1400;    // Drum delay
		//pApp->m_Settings.MotionSettings1.dbPvars[18] = 1000;    // Align delay
		//pApp->m_Settings.MotionSettings1.dbPvars[34] = 64;      // vel
		//pApp->m_Settings.MotionSettings1.dbPvars[15] =  1;      //
		//pApp->m_Settings.MotionSettings1.dbPvars[16] = -63000;  //

		OnSaveSettings (0,0);


	}

}
void CHMIView::ClickBtcReady()
{
	CHMIApp* pApp = (CHMIApp*)AfxGetApp();
	CPmac* pmac = &pApp->m_pmac;

	if (m_ctlBtcReady.GetLightOn())
	{
		m_ctlBtcReady.SetLightOn(0);
		m_ctlBtcReady2.SetLightOn(0);
		pmac->SetVariable(_T('M'),23,(long)0);
	}
	else
	{
		if (m_BtcData.GlobalStatus == GS_RUNNING && m_BtcData.SlicerGlobalStatus==GS_SLICER_AT_SPEED)
		{
			m_ctlBtcReady.SetLightOn(1);	
			m_ctlBtcReady2.SetLightOn(1);	
			pmac->SetVariable(_T('m'),23,(long)1);		
		}
	}
}
void CHMIView::ClickBladeSpeed()
{
	CHMIApp* pApp = (CHMIApp*)AfxGetApp();
	KEYPADDATA data;
	data.dbIncrement = 	10;
	data.dbMin = m_ctlBladeSpeed.GetMinValue();
	data.dbMax = m_ctlBladeSpeed.GetMaxValue();
	data.dbValue = m_ctlBladeSpeed.GetValue();
	data.lpTitle = _T("Enter Blade Speed");
	data.nDecimalPlaces = m_ctlBladeSpeed.GetPrecision();
	data.bPassWord = false;
	bool bOk = GetNumDlg(&data);
	if (bOk) 
	{			
		TRACE("Blade Speed %f \n",data.dbValue);
		if (data.dbValue > 1200) data.dbValue = 1200;

		m_ctlBladeSpeed.SetValue(data.dbValue);
		m_ctlBladeSpeed2.SetValue(data.dbValue);
		pApp->m_Settings.MotionSettings1.dbPvars[7] = data.dbValue;
		OnSaveSettings (0,0);

		//TRACE("Blade Speed %f \n",data.dbValue);
		//if (data.dbValue > 1200) data.dbValue = 1200;

		//MIL_DOUBLE AcquisitionLineRateAbsInHz = data.dbValue;
		//if (AcquisitionLineRateAbsInHz < 200) AcquisitionLineRateAbsInHz = 200;
		//pApp->m_mil.RunThreadData.pHook1->AcquisitionLineRateAbsInHz = AcquisitionLineRateAbsInHz;
		//MdigControlFeature(pApp->m_mil.MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("AcquisitionLineRateAbs"), M_TYPE_DOUBLE, &AcquisitionLineRateAbsInHz);

	}
}
//	m_ctlDischargeDistOffset.SetValue(pApp->m_Settings.MotionSettings1.dbPvars[52]);
void CHMIView::SlicerDischargeSpeed()
{
	SYSTEMTIME st,lt;
	GetSystemTime(&st);
	//SetSystemTime(&st);
	GetLocalTime(&lt);
	//SetLocalTime(&lt);
	TRACE("%02d:%02d:%d \n",st.wHour,st.wMinute,st.wMilliseconds);
	TRACE("%02d:%02d:%d \n",lt.wHour,lt.wMinute,lt.wMilliseconds);

	CHMIApp* pApp = (CHMIApp*)AfxGetApp();
	KEYPADDATA data;
	data.dbIncrement = 	0.1;
	data.dbMin = m_ctlDischargeDistOffset.GetMinValue();
	data.dbMax = m_ctlDischargeDistOffset.GetMaxValue();
	data.dbValue = m_ctlDischargeDistOffset.GetValue();

	//if (pApp->m_Settings.VisSettings4.TrimModeEnable==0)	data.lpTitle = _T("Enter Offset");
	//else 	data.lpTitle = _T("Enter Trim Length");
	data.lpTitle = _T("Bacon Placement X offset (inch) ");
	data.nDecimalPlaces = m_ctlDischargeDistOffset.GetPrecision();
	data.bPassWord = false;
	bool bOk = GetNumDlg(&data);
	if (bOk) 
	{			
		m_ctlDischargeDistOffset.SetValue(data.dbValue);
		pApp->m_Settings.MotionSettings1.dbPvars[52] = data.dbValue;
		//pApp->m_Settings.VisSettings3.dbAlignOffset = data.dbValue;
		//m_ctlAlignOffset.SetValue(pApp->m_Settings.VisSettings3.dbAlignOffset);
		OnSaveSettings (0,0);
	}

}

void CHMIView::ClickAlignOffset()
{
	SYSTEMTIME st,lt;
	GetSystemTime(&st);
	//SetSystemTime(&st);
	GetLocalTime(&lt);
	//SetLocalTime(&lt);
	TRACE("%02d:%02d:%d \n",st.wHour,st.wMinute,st.wMilliseconds);
	TRACE("%02d:%02d:%d \n",lt.wHour,lt.wMinute,lt.wMilliseconds);

	CHMIApp* pApp = (CHMIApp*)AfxGetApp();
	KEYPADDATA data;
	data.dbIncrement = 	0.1;
	data.dbMin = m_ctlAlignOffset.GetMinValue();
	data.dbMax = m_ctlAlignOffset.GetMaxValue();
	data.dbValue = m_ctlAlignOffset.GetValue();


	//if (pApp->m_Settings.VisSettings4.TrimModeEnable==0)	data.lpTitle = _T("Enter Offset");
	//else 	data.lpTitle = _T("Enter Trim Length");
	data.lpTitle = _T("Enter Offset");
	data.nDecimalPlaces = m_ctlAlignOffset.GetPrecision();
	data.bPassWord = false;
	bool bOk = GetNumDlg(&data);
	if (bOk) 
	{			
		m_ctlAlignOffset.SetValue(data.dbValue);
		pApp->m_Settings.VisSettings3.dbAlignOffset = data.dbValue;
		//m_ctlAlignOffset.SetValue(pApp->m_Settings.VisSettings3.dbAlignOffset);
		OnSaveSettings (0,0);
	}

}
//ClickSliceThickness
void CHMIView::ClickSliceThickness()
{
	CHMIApp* pApp = (CHMIApp*)AfxGetApp();
	KEYPADDATA data;
	data.dbIncrement = 	0.1;
	data.dbMin = m_ctlSliceThickness.GetMinValue();
	data.dbMax = m_ctlSliceThickness.GetMaxValue();
	data.dbValue = m_ctlSliceThickness.GetValue();
	data.lpTitle = _T("Enter Slice Thickness");
	data.nDecimalPlaces = m_ctlSliceThickness.GetPrecision();
	data.bPassWord = false;
	bool bOk = GetNumDlg(&data);
	if (bOk) 
	{			
		m_ctlSliceThickness.SetValue(data.dbValue);
		pApp->m_Settings.MotionSettings1.dbPvars[45] = data.dbValue;
		OnSaveSettings (0,0);
	}
}


void CHMIView::OnBnClickedSheetCountInc()
{
	CHMIApp* pApp = (CHMIApp*)AfxGetApp();
	//CPmac* pmac = &pApp->m_pmac;
	//pmac->DPRSet(DPR_OFFSET_SHEET_COUNT,(long)m_BtcData.SheetCount);
	m_ctlSliceThickness.SetValue(m_ctlSliceThickness.GetValue()+0.001);
	pApp->m_Settings.MotionSettings1.dbPvars[45] = m_ctlSliceThickness.GetValue();
	OnSaveSettings (0,0);


	//CHMIApp* pApp = (CHMIApp*)AfxGetApp();
	//m_ctlSliceThickness.SetValue(pApp->m_Settings.MotionSettings1.dbPvars[45]);

}
void CHMIView::OnBnClickedSheetCountDec()
{
	CHMIApp* pApp = (CHMIApp*)AfxGetApp();
	//CPmac* pmac = &pApp->m_pmac;
	//pmac->DPRSet(DPR_OFFSET_SHEET_COUNT,(long)m_BtcData.SheetCount);
	m_ctlSliceThickness.SetValue(m_ctlSliceThickness.GetValue()-0.001);
	pApp->m_Settings.MotionSettings1.dbPvars[45] = m_ctlSliceThickness.GetValue();
	OnSaveSettings (0,0);
}
void CHMIView::ClickSheetCount()
{
	CHMIApp* pApp = (CHMIApp*)AfxGetApp();
	KEYPADDATA data;
	data.dbIncrement = 	1;
	data.dbMin = 0;
	data.dbMax = 1000;
	data.dbValue = pApp->m_Settings.MotionSettings1.dbPvars[56];
	data.lpTitle = _T("Enter Sheet Count Preset");
	data.nDecimalPlaces = 0;
	data.bPassWord = false;
	bool bOk = GetNumDlg(&data);
	if (bOk) 
	{			
		pApp->m_Settings.MotionSettings1.dbPvars[56] = data.dbValue;
		OnSaveSettings (0,0);
	}

}
void CHMIView::ClickSheetCountShift()
{
	CHMIApp* pApp = (CHMIApp*)AfxGetApp();
	CPmac* pmac = &pApp->m_pmac;
	KEYPADDATA data;
	data.dbIncrement = 	1;
	data.dbMin = m_ctlSheetCountShift.GetMinValue();
	data.dbMax = m_ctlSheetCountShift.GetMaxValue();
	data.dbValue = m_ctlSheetCountShift.GetValue();
	data.lpTitle = _T("Enter Value");
	data.nDecimalPlaces = m_ctlSheetCountShift.GetPrecision();
	data.bPassWord = false;
	bool bOk = GetNumDlg(&data);
	if (bOk) 
	{			
		//m_ctlSheetCountShift.SetValue(data.dbValue);
		pmac->DPRSet(DPR_OFFSET_SHEET_SHIFT,(long)data.dbValue);
		pApp->m_Counters.SheetCountShift = (long)data.dbValue; //m_BtcData.SheetCountShift;
		SaveAppCounterFile (&pApp->m_Counters);
	}

}
void CHMIView::OnBnClickedMotionSettings2()
{
	OnBnClickedMotionSettings();
}
void CHMIView::OnPageHome()
{
	ScrollToPage(0);
}
void CHMIView::OnPageDown()
{
	int page = 	m_nPage;
	page++;
	if (page>4) page=4;
	ScrollToPage(page);
}
void CHMIView::OnPageUp()
{
	int page = 	m_nPage;
	page--;
	if (page<0) page=0;
	ScrollToPage(page);
}

void CHMIView::OnDriveLoad()
{

	TCHAR szName[256];
	STARTUPINFO si;
	::ZeroMemory (&si, sizeof (STARTUPINFO));
	si.cb = sizeof (STARTUPINFO);
	//PROCESS_INFORMATION m_pi;

	::ZeroMemory (&si, sizeof (STARTUPINFO));
	si.cb = sizeof (STARTUPINFO);
	::lstrcpy(szName,_T ("C:\\Program Files\\Hormel Foods LLC\\PmacUtil.exe"));

	m_bPmacUtilBusy = true;
	if (::CreateProcess (NULL,szName ,
		NULL,NULL,FALSE, NORMAL_PRIORITY_CLASS, NULL,
		NULL, &si, &m_pi)) {
		::CloseHandle (m_pi.hThread);
		//::WaitForSingleObject (pi.hProcess, INFINITE);
		//::CloseHandle (pi.hProcess);
	}
	CUIHelperThread* pThread = (CUIHelperThread*)AfxBeginThread (RUNTIME_CLASS (CUIHelperThread));
	//Sleep(1000);
	pThread->SetDelayTime(6000);
	Sleep(6000);
	pThread->Close();

}

void CHMIView::UpDateHMI()
{
	static bool WriteTags = false;
	unsigned char EncData[16];
	double TotalCurrent;
	//BTCINPUTS IOStatusWord;

	// Is PMAC busy?
	if (m_bPmacBusy || m_bPmacUtilBusy)
	{
		//AfxMessageBox(_T("PMAC busy"));
		return;
	}

	// Call the base class
	CString str;
	CWnd* pWnd;
	CHMIApp* pApp = (CHMIApp*)AfxGetApp();
	CPmac* pmac = &pApp->m_pmac;
	//CPmac* pmacSlicer = &pApp->m_pmacSlicer;

	// Is PMAC open
	if (pmac->IsPmacOpen() == 0)
	{
		//AfxMessageBox(_T("UpDateHMI ... PMAC not open"));
		return;			
	}

	// Is PMAC open
	//if (pmacSlicer->IsPmacOpen() != 0)
	//{
		//double p12 = 0;
	    //pmacSlicer->GetVariable(_T('p'),12,&p12);
	    //TRACE(_T("UpDateHMI ... p12:%f \n"),p12);
	//}

	double dbTimeStart,dbTimeEnd;
	MappTimer(M_TIMER_READ, &dbTimeStart);

	// Global Status faults
	if (m_BtcData.GlobalStatus == GS_DRUM_FAULT && !m_bGlobalStatusFaultLatch)
	{
		m_bGlobalStatusFaultLatch = true;
		m_FaultHistory.AddString(_T("Drum Fault"));
		//// // m_FaultHistory.SaveStrings();
	}
	if (m_BtcData.GlobalStatus == GS_KNIFE_FAULT && !m_bGlobalStatusFaultLatch)
	{
		m_bGlobalStatusFaultLatch = true;
		m_FaultHistory.AddString(_T("Knife Fault"));
		// m_FaultHistory.SaveStrings();
	}
	if (m_BtcData.GlobalStatus == GS_KNIFE_PROX_FAULT && !m_bGlobalStatusFaultLatch) 
	{
		m_bGlobalStatusFaultLatch = true;
		m_FaultHistory.AddString(_T("Knife Prox Fault"));
		// m_FaultHistory.SaveStrings();
	}
	if (m_BtcData.GlobalStatus == GS_DRUM_PROX_FAULT && !m_bGlobalStatusFaultLatch) 
	{
		m_bGlobalStatusFaultLatch = true;
		m_FaultHistory.AddString(_T("Drum Prox Fault"));
		// m_FaultHistory.SaveStrings();
	}
	
	// Global Status
	//------------------------------------------------------------------//
	m_ctlStatusMainEx.SetStatusState(m_BtcData.GlobalStatus);
	m_ctlStatusMainEx2.SetStatusState(m_BtcData.GlobalStatus);
	m_ctlStatusMainEx3.SetStatusState(m_BtcData.GlobalStatus);
	//m_ctlMain.SetStatusState(m_BtcData.GlobalStatus);
	//m_ctlMain2.SetStatusState(m_BtcData.GlobalStatus);
	//m_ctlMain3.SetStatusState(m_BtcData.GlobalStatus);
	if (m_BtcData.GlobalStatus == GS_RUNNING)  // Running
	{
		m_ctlStart.SetLight(1);
		m_ctlStart2.SetLight(1);
		m_ctlStart3.SetLight(1);
		m_ctlStop.SetLight(0);
		m_ctlStop2.SetLight(0);
		m_ctlStop3.SetLight(0);
		m_bGlobalStatusFaultLatch = false;
	}
	else
	{
		m_ctlStart.SetLight(0);
		m_ctlStart2.SetLight(0);
		m_ctlStart3.SetLight(0);
		m_ctlStop.SetLight(1);
		m_ctlStop2.SetLight(1);
		m_ctlStop3.SetLight(1);
		if (m_BtcData.GlobalStatus == GS_STOPPED || m_BtcData.GlobalStatus==GS_BLADE_PARKED)
		{
			m_ctlStop.SetTitleText2(_T("Park Blades"));
			m_ctlStop2.SetTitleText2(_T("Park Blades"));
			m_ctlStop3.SetTitleText2(_T("Park Blades"));
		}
	}

	// Slicer Status
	m_SlicerStatus.SetStatusState(m_BtcData.SlicerGlobalStatus);
	m_SlicerStatus2.SetStatusState(m_BtcData.SlicerGlobalStatus);
	
	//IDC_GDIBUTTONXLCTRL_DRUM_DOOR

	// Safety contacts
	m_ctlEstopLED.SetLightOn(!m_BtcData.BtcInputs.Bits.In6);
	m_ctlDrumDoorLED.SetLightOn(m_BtcData.Mtr1Mtr2FlagsHalls.USER2); 
	m_ctlFlipperGuard.SetLightOn(m_BtcData.Mtr1Mtr2FlagsHalls.PLIM2);
	m_ctlEstopLED2.SetLightOn(!m_BtcData.SlicerInputs.BelevatorEstop);
	m_ctlPaperDoorLED.SetLightOn(!m_BtcData.SlicerInputs.SlicerDisconnect);
	m_ctlKnifeDisconnectLED.SetLightOn(!m_BtcData.BtcInputs.Bits.In1);

	// Feed Button
	m_ctlBtcReady.SetLightOn(m_BtcData.StatusBits.FeedStartStop);
	m_ctlBtcReady2.SetLightOn(m_BtcData.StatusBits.FeedStartStop);

	// Count
	//m_ctlSliceCount2.SetValue(m_BtcData.CountOnPaper);

	// Feed Rollers Up/Dn
	//TRACE(_T("M1920= %d M1923= %d \n"),m_BtcData.SlicerOutputs.Bits.FeedNoseDown,m_BtcData.SlicerOutputs.Bits.FeedRollersDown);
	if (m_BtcData.SlicerOutputs.FeedNoseDown == 1 && m_BtcData.SlicerOutputs.FeedRollersDown == 0)
	{
		m_btnFeedUpDn.SetLight(1);
	}
	else
	{
		m_btnFeedUpDn.SetLight(0);
	}

	// Blower
	//TRACE(_T("Blower= %d \n"),m_BtcData.BtcOutputs.Blower);
	m_ctlBlower.SetLight(m_BtcData.BtcOutputs.Blower); 
	m_ctlBelevator.SetLight(m_BtcData.BtcOutputs.BelevatorLight);

	// Paper Roll
	m_PaperRollSize.SetPos((int)m_BtcData.PaperRollSize);
	str.Format(_T("%4.2f"),m_BtcData.PaperRollSize);
	pWnd = GetDlgItem(IDC_DPR_ROLL_SIZE);
	pWnd->SetWindowText(str);
	//TRACE(_T("RollSize %f \n"),m_BtcData.PaperRollSize);

	// Shunt temp	
	if (m_BtcData.BtcInputs.Bits.In8 == 0 && !m_bShuntTempFaultLatch1)  // Running
	{
		m_FaultHistory.AddString(_T("BTC Shunt Resistor Over Temp"));
		m_bShuntTempFaultLatch1 = true;
		if (m_pAlarm6 != NULL)
		{
			m_pAlarm6->SetFocus ();
		}
		else
		{
			CAlarms* pDlg = new CAlarms(this);
			pDlg->m_ppBackPtr = &m_pAlarm6;
			pDlg->m_nID = 6;
			pDlg->m_strMsg =_T("BTC Shunt Resistor Over Temp");
			pDlg->Create (IDD_ALARMS_DIALOG);
			pDlg->ShowWindow (SW_SHOW);
			m_pAlarm6 = pDlg;
		}
	}
	// Shunt temp2	
	if (m_BtcData.SlicerInputs.ShuntOverTemp1 == 0 && !m_bShuntTempFaultLatch2)
	{
		m_FaultHistory.AddString(_T("Slicer Shunt Resistor 1 Over Temp"));
		m_bShuntTempFaultLatch2 = true;
		if (m_pAlarm6 != NULL)
		{
			m_pAlarm6->SetFocus ();
		}
		else
		{
			CAlarms* pDlg = new CAlarms(this);
			pDlg->m_ppBackPtr = &m_pAlarm6;
			pDlg->m_nID = 6;
			pDlg->m_strMsg =_T("Slicer Shunt Resistor 1 Over Temp");
			pDlg->Create (IDD_ALARMS_DIALOG);
			pDlg->ShowWindow (SW_SHOW);
			m_pAlarm6 = pDlg;
		}
	}

#ifndef OSCEOLA_LAYOUT
	// IDC_GDIMOTORSTATUSCTRL1
	// Shunt temp3
	if (m_BtcData.SlicerInputs.ShuntOverTemp2 == 0 && !m_bShuntTempFaultLatch3)
	{
		m_FaultHistory.AddString(_T("Slicer Shunt Resistor 2 Over Temp"));
		// m_FaultHistory.SaveStrings();
		m_bShuntTempFaultLatch3 = true;
		if (m_pAlarm6 != NULL)
		{
			m_pAlarm6->SetFocus ();
		}
		else
		{
			CAlarms* pDlg = new CAlarms(this);
			pDlg->m_ppBackPtr = &m_pAlarm6;
			pDlg->m_nID = 6;
			pDlg->m_strMsg =_T("Slicer Shunt Resistor 2 Over Temp");
			pDlg->Create (IDD_ALARMS_DIALOG);
			pDlg->ShowWindow (SW_SHOW);
			m_pAlarm6 = pDlg;
		}
	}
#endif

	// Motor Status 
	//m_csLatch.Lock();
	
	// Update HALL STATES
	EncData[0] = m_BtcData.Mtr1Mtr2FlagsHalls.HallWVUT1;
	EncData[1] = m_BtcData.Mtr1Mtr2FlagsHalls.HallWVUT2;
	EncData[2] = m_BtcData.Mtr3Mtr4FlagsHalls.HallWVUT1;
	EncData[3] = m_BtcData.Mtr3Mtr4FlagsHalls.HallWVUT2;
	EncData[4] = m_BtcData.Mtr5Mtr6FlagsHalls.HallWVUT1;
	EncData[5] = m_BtcData.Mtr5Mtr6FlagsHalls.HallWVUT2;
	EncData[6] = m_BtcData.Mtr7Mtr8FlagsHalls.HallWVUT1;
	EncData[7] = m_BtcData.Mtr7Mtr8FlagsHalls.HallWVUT2;
	EncData[8] = m_BtcData.Mtr9Mtr10FlagsHalls.HallWVUT1;
	EncData[9] = m_BtcData.Mtr9Mtr10FlagsHalls.HallWVUT2;
	EncData[10] = m_BtcData.Mtr11Mtr12FlagsHalls.HallWVUT1;
	EncData[11] = m_BtcData.Mtr11Mtr12FlagsHalls.HallWVUT2;
	EncData[12] = 2;
	EncData[13] = m_BtcData.Mtr13Mtr14FlagsHalls.HallWVUT2;
	EncData[14] = m_BtcData.Mtr15Mtr16FlagsHalls.HallWVUT1;
	EncData[15] = m_BtcData.Mtr15Mtr16FlagsHalls.HallWVUT2;
	//TRACE("m_BtcData.EncCntErrorsMtr1to4.Byte0 %d",m_BtcData.EncCntErrorsMtr1to4.Byte0);

	// Update encoder count errors
	if (m_BtcData.EncCntErrorsMtr1to4.Byte0)   m_BtcData.Mtr1.MotorStatus.Bits.encoder_count_error = 1;	else m_BtcData.Mtr1.MotorStatus.Bits.encoder_count_error = 0;
	if (m_BtcData.EncCntErrorsMtr1to4.Byte1)   m_BtcData.Mtr2.MotorStatus.Bits.encoder_count_error = 1;	else m_BtcData.Mtr2.MotorStatus.Bits.encoder_count_error = 0;
	if (m_BtcData.EncCntErrorsMtr1to4.Byte2)   m_BtcData.Mtr3.MotorStatus.Bits.encoder_count_error = 1;	else m_BtcData.Mtr3.MotorStatus.Bits.encoder_count_error = 0;
	if (m_BtcData.EncCntErrorsMtr1to4.Byte3)   m_BtcData.Mtr4.MotorStatus.Bits.encoder_count_error = 1;	else m_BtcData.Mtr4.MotorStatus.Bits.encoder_count_error = 0;
	if (m_BtcData.EncCntErrorsMtr5to8.Byte0)   m_BtcData.Mtr5.MotorStatus.Bits.encoder_count_error = 1;	else m_BtcData.Mtr5.MotorStatus.Bits.encoder_count_error = 0;
	if (m_BtcData.EncCntErrorsMtr5to8.Byte1)   m_BtcData.Mtr6.MotorStatus.Bits.encoder_count_error = 1;	else m_BtcData.Mtr6.MotorStatus.Bits.encoder_count_error = 0;
	if (m_BtcData.EncCntErrorsMtr5to8.Byte2)   m_BtcData.Mtr7.MotorStatus.Bits.encoder_count_error = 1;	else m_BtcData.Mtr7.MotorStatus.Bits.encoder_count_error = 0;
	if (m_BtcData.EncCntErrorsMtr5to8.Byte3)   m_BtcData.Mtr8.MotorStatus.Bits.encoder_count_error = 1;	else m_BtcData.Mtr8.MotorStatus.Bits.encoder_count_error = 0;
	if (m_BtcData.EncCntErrorsMtr9to12.Byte0)  m_BtcData.Mtr9.MotorStatus.Bits.encoder_count_error = 1;	else m_BtcData.Mtr9.MotorStatus.Bits.encoder_count_error = 0;
	if (m_BtcData.EncCntErrorsMtr9to12.Byte1)  m_BtcData.Mtr10.MotorStatus.Bits.encoder_count_error = 1;	else m_BtcData.Mtr10.MotorStatus.Bits.encoder_count_error = 0;
	if (m_BtcData.EncCntErrorsMtr9to12.Byte2)  m_BtcData.Mtr11.MotorStatus.Bits.encoder_count_error = 1;	else m_BtcData.Mtr11.MotorStatus.Bits.encoder_count_error = 0;
	if (m_BtcData.EncCntErrorsMtr9to12.Byte3)  m_BtcData.Mtr12.MotorStatus.Bits.encoder_count_error = 1;	else m_BtcData.Mtr12.MotorStatus.Bits.encoder_count_error = 0;
	if (m_BtcData.EncCntErrorsMtr13to16.Byte0) m_BtcData.Mtr13.MotorStatus.Bits.encoder_count_error = 1;	else m_BtcData.Mtr13.MotorStatus.Bits.encoder_count_error = 0;
	if (m_BtcData.EncCntErrorsMtr13to16.Byte1) m_BtcData.Mtr14.MotorStatus.Bits.encoder_count_error = 1;	else m_BtcData.Mtr14.MotorStatus.Bits.encoder_count_error = 0;
	if (m_BtcData.EncCntErrorsMtr13to16.Byte2) m_BtcData.Mtr15.MotorStatus.Bits.encoder_count_error = 1;	else m_BtcData.Mtr15.MotorStatus.Bits.encoder_count_error = 0;
	if (m_BtcData.EncCntErrorsMtr13to16.Byte3) m_BtcData.Mtr16.MotorStatus.Bits.encoder_count_error = 1;	else m_BtcData.Mtr16.MotorStatus.Bits.encoder_count_error = 0;

	// Update phase errors
	m_BtcData.Mtr1.MotorStatus.Bits.reset_phase_error = m_BtcData.MtrPhaseStatus.Mtr1;
	m_BtcData.Mtr2.MotorStatus.Bits.reset_phase_error = m_BtcData.MtrPhaseStatus.Mtr2;
	m_BtcData.Mtr3.MotorStatus.Bits.reset_phase_error = m_BtcData.MtrPhaseStatus.Mtr3;
	m_BtcData.Mtr4.MotorStatus.Bits.reset_phase_error = m_BtcData.MtrPhaseStatus.Mtr4;
	m_BtcData.Mtr5.MotorStatus.Bits.reset_phase_error = m_BtcData.MtrPhaseStatus.Mtr5;
	m_BtcData.Mtr6.MotorStatus.Bits.reset_phase_error = m_BtcData.MtrPhaseStatus.Mtr6;
	m_BtcData.Mtr7.MotorStatus.Bits.reset_phase_error = m_BtcData.MtrPhaseStatus.Mtr7;
	m_BtcData.Mtr8.MotorStatus.Bits.reset_phase_error = m_BtcData.MtrPhaseStatus.Mtr8;
	m_BtcData.Mtr9.MotorStatus.Bits.reset_phase_error = m_BtcData.MtrPhaseStatus.Mtr9;
	m_BtcData.Mtr10.MotorStatus.Bits.reset_phase_error = m_BtcData.MtrPhaseStatus.Mtr10;
	m_BtcData.Mtr11.MotorStatus.Bits.reset_phase_error = m_BtcData.MtrPhaseStatus.Mtr11;
	m_BtcData.Mtr12.MotorStatus.Bits.reset_phase_error = m_BtcData.MtrPhaseStatus.Mtr12;
	m_BtcData.Mtr13.MotorStatus.Bits.reset_phase_error = m_BtcData.MtrPhaseStatus.Mtr13;
	m_BtcData.Mtr14.MotorStatus.Bits.reset_phase_error = m_BtcData.MtrPhaseStatus.Mtr14;
	m_BtcData.Mtr15.MotorStatus.Bits.reset_phase_error = m_BtcData.MtrPhaseStatus.Mtr15;
	m_BtcData.Mtr16.MotorStatus.Bits.reset_phase_error = m_BtcData.MtrPhaseStatus.Mtr16;

	// Update motor status
	m_ctlMotorStatus1.SetMotorState(0,GetMotorState(_T("Motor 1"),&m_BtcData.Mtr1,EncData[0],&m_bMotorFaultLatch[0],&m_bMotorWarnLatch[0]));
	m_ctlMotorStatus1.SetMotorState(1,GetMotorState(_T("Motor 2"),&m_BtcData.Mtr2,EncData[1],&m_bMotorFaultLatch[1],&m_bMotorWarnLatch[1]));
	m_ctlMotorStatus1.SetMotorState(2,GetMotorState(_T("Motor 3"),&m_BtcData.Mtr3,EncData[2],&m_bMotorFaultLatch[2],&m_bMotorWarnLatch[2]));
	m_ctlMotorStatus1.SetMotorState(3,GetMotorState(_T("Motor 4"),&m_BtcData.Mtr4,EncData[3],&m_bMotorFaultLatch[3],&m_bMotorWarnLatch[3]));
	m_ctlMotorStatus1.SetMotorState(4,GetMotorState(_T("Motor 5"),&m_BtcData.Mtr5,EncData[4],&m_bMotorFaultLatch[4],&m_bMotorWarnLatch[4]));
	m_ctlMotorStatus1.SetMotorState(5,GetMotorState(_T("Motor 6"),&m_BtcData.Mtr6,EncData[5],&m_bMotorFaultLatch[5],&m_bMotorWarnLatch[5]));
	m_ctlMotorStatus1.SetMotorState(6,GetMotorState(_T("Motor 7"),&m_BtcData.Mtr7,EncData[6],&m_bMotorFaultLatch[6],&m_bMotorWarnLatch[6]));
	m_ctlMotorStatus1.SetMotorState(7,GetMotorState(_T("Motor 8"),&m_BtcData.Mtr8,EncData[7],&m_bMotorFaultLatch[7],&m_bMotorWarnLatch[7]));
	m_ctlMotorStatus1.SetMotorState(8,GetMotorState(_T("Motor 9"),&m_BtcData.Mtr9,EncData[8],&m_bMotorFaultLatch[8],&m_bMotorWarnLatch[8]));
	m_ctlMotorStatus1.SetMotorState(9,GetMotorState(_T("Motor 10"),&m_BtcData.Mtr10,EncData[9],&m_bMotorFaultLatch[9],&m_bMotorWarnLatch[9]));
	m_ctlMotorStatus1.SetMotorState(10,GetMotorState(_T("Motor 11"),&m_BtcData.Mtr11,EncData[10],&m_bMotorFaultLatch[10],&m_bMotorWarnLatch[10]));
	m_ctlMotorStatus1.SetMotorState(11,GetMotorState(_T("Motor 12"),&m_BtcData.Mtr12,EncData[11],&m_bMotorFaultLatch[11],&m_bMotorWarnLatch[11]));	
	m_ctlMotorStatus1.SetMotorState(12,GetMotorState(_T("Motor 13"),&m_BtcData.Mtr13,EncData[12],&m_bMotorFaultLatch[12],&m_bMotorWarnLatch[12]));	
	m_ctlMotorStatus1.SetMotorState(13,GetMotorState(_T("Motor 14"),&m_BtcData.Mtr14,EncData[13],&m_bMotorFaultLatch[13],&m_bMotorWarnLatch[13]));	
#ifndef OSCEOLA_LAYOUT
	m_ctlMotorStatus1.SetMotorState(14,GetMotorState(_T("Motor 15"),&m_BtcData.Mtr15,EncData[14],&m_bMotorFaultLatch[14],&m_bMotorWarnLatch[14]));	
	m_ctlMotorStatus1.SetMotorState(15,GetMotorState(_T("Motor 16"),&m_BtcData.Mtr16,EncData[15],&m_bMotorFaultLatch[15],&m_bMotorWarnLatch[15]));	
#else

	// Exit VFD
	if (pApp->m_mil.m_ReadData.VfdRunning==1)
	{
		m_ctlMotorStatus1.SetMotorState(14,1);
	}
	else 
	{
		if (pApp->m_mil.m_ReadData.VfdFaulted)
			m_ctlMotorStatus1.SetMotorState(14,3);
		else
			m_ctlMotorStatus1.SetMotorState(14,0);
	}

	// Reject VFD
	if (m_BtcData.BtcOutputs.RejectVFDRun==1)
	{
		m_ctlMotorStatus1.SetMotorState(15,1);
	}
	else 
	{
		if (m_BtcData.BtcInputs.Bits.RejectVFDFault==1)
			m_ctlMotorStatus1.SetMotorState(15,3);
		else
			m_ctlMotorStatus1.SetMotorState(15,0);
	}
#endif
	m_ctlMotorStatus1.UpdateMotorStatus(1);

	////TRACE(_T("Motor 13 ffE BIT %d \n"),m_BtcData.Mtr13.MotorStatus.Bits.fatal_ferr);
	////TRACE(_T("Motor 3 open loop  %d \n"),m_BtcData.Mtr3.ServoStatus.Bits.open_loop);
	////TRACE(_T("Motor 4 open loop  %d \n"),m_BtcData.Mtr4.ServoStatus.Bits.open_loop);
	m_ctlMotorStatus2.SetMotorState(0,GetMotorState(_T("Motor 1"),&m_BtcData.Mtr1,EncData[0],&m_bMotorFaultLatch[0],&m_bMotorWarnLatch[0]));
	m_ctlMotorStatus2.SetMotorState(1,GetMotorState(_T("Motor 2"),&m_BtcData.Mtr2,EncData[1],&m_bMotorFaultLatch[1],&m_bMotorWarnLatch[1]));
	m_ctlMotorStatus2.SetMotorState(2,GetMotorState(_T("Motor 3"),&m_BtcData.Mtr3,EncData[2],&m_bMotorFaultLatch[2],&m_bMotorWarnLatch[2]));
	m_ctlMotorStatus2.SetMotorState(3,GetMotorState(_T("Motor 4"),&m_BtcData.Mtr4,EncData[3],&m_bMotorFaultLatch[3],&m_bMotorWarnLatch[3]));
	m_ctlMotorStatus2.SetMotorState(4,GetMotorState(_T("Motor 5"),&m_BtcData.Mtr5,EncData[4],&m_bMotorFaultLatch[4],&m_bMotorWarnLatch[4]));
	m_ctlMotorStatus2.SetMotorState(5,GetMotorState(_T("Motor 6"),&m_BtcData.Mtr6,EncData[5],&m_bMotorFaultLatch[5],&m_bMotorWarnLatch[5]));
	m_ctlMotorStatus2.SetMotorState(6,GetMotorState(_T("Motor 7"),&m_BtcData.Mtr7,EncData[6],&m_bMotorFaultLatch[6],&m_bMotorWarnLatch[6]));
	m_ctlMotorStatus2.SetMotorState(7,GetMotorState(_T("Motor 8"),&m_BtcData.Mtr8,EncData[7],&m_bMotorFaultLatch[7],&m_bMotorWarnLatch[7]));
	m_ctlMotorStatus2.SetMotorState(8,GetMotorState(_T("Motor 9"),&m_BtcData.Mtr9,EncData[8],&m_bMotorFaultLatch[8],&m_bMotorWarnLatch[8]));
	m_ctlMotorStatus2.SetMotorState(9,GetMotorState(_T("Motor 10"),&m_BtcData.Mtr10,EncData[9],&m_bMotorFaultLatch[9],&m_bMotorWarnLatch[9]));
	m_ctlMotorStatus2.SetMotorState(10,GetMotorState(_T("Motor 11"),&m_BtcData.Mtr11,EncData[10],&m_bMotorFaultLatch[10],&m_bMotorWarnLatch[10]));
	m_ctlMotorStatus2.SetMotorState(11,GetMotorState(_T("Motor 12"),&m_BtcData.Mtr12,EncData[11],&m_bMotorFaultLatch[11],&m_bMotorWarnLatch[11]));	
	m_ctlMotorStatus2.SetMotorState(12,GetMotorState(_T("Motor 13"),&m_BtcData.Mtr13,EncData[12],&m_bMotorFaultLatch[12],&m_bMotorWarnLatch[12]));	
	m_ctlMotorStatus2.SetMotorState(13,GetMotorState(_T("Motor 14"),&m_BtcData.Mtr14,EncData[13],&m_bMotorFaultLatch[13],&m_bMotorWarnLatch[13]));	
#ifndef OSCEOLA_LAYOUT
	m_ctlMotorStatus2.SetMotorState(14,GetMotorState(_T("Motor 15"),&m_BtcData.Mtr15,EncData[14],&m_bMotorFaultLatch[14],&m_bMotorWarnLatch[14]));	
	m_ctlMotorStatus2.SetMotorState(15,GetMotorState(_T("Motor 16"),&m_BtcData.Mtr16,EncData[15],&m_bMotorFaultLatch[15],&m_bMotorWarnLatch[15]));	
#else

	// Exit VFD
	if (pApp->m_mil.m_ReadData.VfdRunning==1)
	{
		m_ctlMotorStatus2.SetMotorState(14,1);
	}
	else 
	{
		if (pApp->m_mil.m_ReadData.VfdFaulted)
			m_ctlMotorStatus2.SetMotorState(14,3);
		else
			m_ctlMotorStatus2.SetMotorState(14,0);
	}

	// Reject VFD
	if (m_BtcData.BtcOutputs.RejectVFDRun==1)
	{
		m_ctlMotorStatus2.SetMotorState(15,1);
	}
	else 
	{
		if (m_BtcData.BtcInputs.Bits.RejectVFDFault==1)
			m_ctlMotorStatus2.SetMotorState(15,3);
		else
			m_ctlMotorStatus2.SetMotorState(15,0);
	}
#endif
	m_ctlMotorStatus2.UpdateMotorStatus(1);
	//m_csLatch.Unlock();
	
	// Sheet Counters
	pApp->m_Counters.TotalSheetCount = m_BtcData.TotalSheetCount;
	m_TotalSheetCount.SetValue(m_BtcData.TotalSheetCount);
	pApp->m_Counters.SheetCount = m_BtcData.SheetCount;
	pApp->m_Counters.SheetCountShift = m_BtcData.SheetCountShift;
	m_ctlSheetCountShift.SetValue(m_BtcData.SheetCountShift);

	// Wash/Run Mode
	m_BtcMode.SetStatusState(m_BtcData.BtcMode);
	//if (m_BtcData.BtcMode == 0)
	//{
	//	m_ctlRunMode.SetLight(1);
	//	m_ctlWashMode.SetLight(0);
	//}
	//else
	//{
	//	m_ctlRunMode.SetLight(0);
	//	m_ctlWashMode.SetLight(1);	
	//}
	switch (m_BtcData.BtcMode)
	{
	case 0:
		m_ctlRunMode.SetLight(1);
		m_ctlWashMode.SetLight(0);
		m_btnTimingCheck.SetLightOn(0);	
		m_btnLoadPaper.SetLightOn(0);
		break;
	case 1:
		m_ctlRunMode.SetLight(0);
		m_ctlWashMode.SetLight(1);	
		m_btnTimingCheck.SetLightOn(0);	
		m_btnLoadPaper.SetLightOn(0);
		break;
	case 2:
		m_ctlRunMode.SetLight(0);
		m_ctlWashMode.SetLight(0);
		m_btnTimingCheck.SetLightOn(1);
		m_btnLoadPaper.SetLightOn(0);
		if (!m_ctlTTJogFast.GetLightOn())
			m_ctlTTJogSlow.SetLightOn(m_BtcData.StatusBits.TimingTestActive);
		break;
	case 3:
		m_btnLoadPaper.SetLightOn(1);
		break;
	}

	//=====================================================================================================//
	// Servo Page
	//=====================================================================================================//

	// Motor positions
	m_ctlReadOutsMtr1.SetdbValue0(pmac->DPRFixed((long*)&m_BtcData.Mtr1.PositionWord0,1.0/3072.0));
	m_ctlReadOutsMtr2.SetdbValue0(pmac->DPRFixed((long*)&m_BtcData.Mtr2.PositionWord0,1.0/3072.0));
	m_ctlReadOutsMtr3.SetdbValue0(pmac->DPRFixed((long*)&m_BtcData.Mtr3.PositionWord0,1.0/3072.0));
	m_ctlReadOutsMtr4.SetdbValue0(pmac->DPRFixed((long*)&m_BtcData.Mtr4.PositionWord0,1.0/3072.0));
	m_ctlReadOutsMtr5.SetdbValue0(pmac->DPRFixed((long*)&m_BtcData.Mtr5.PositionWord0,1.0/3072.0));
	m_ctlReadOutsMtr6.SetdbValue0(pmac->DPRFixed((long*)&m_BtcData.Mtr6.PositionWord0,1.0/3072.0));
	m_ctlReadOutsMtr7.SetdbValue0(pmac->DPRFixed((long*)&m_BtcData.Mtr7.PositionWord0,1.0/3072.0));
	m_ctlReadOutsMtr8.SetdbValue0(pmac->DPRFixed((long*)&m_BtcData.Mtr8.PositionWord0,1.0/3072.0));
	m_ctlReadOutsMtr9.SetdbValue0(pmac->DPRFixed((long*)&m_BtcData.Mtr9.PositionWord0,1.0/3072.0));
	m_ctlReadOutsMtr10.SetdbValue0(pmac->DPRFixed((long*)&m_BtcData.Mtr10.PositionWord0,1.0/3072.0));
	m_ctlReadOutsMtr11.SetdbValue0(pmac->DPRFixed((long*)&m_BtcData.Mtr11.PositionWord0,1.0/3072.0));
	m_ctlReadOutsMtr12.SetdbValue0(pmac->DPRFixed((long*)&m_BtcData.Mtr12.PositionWord0,1.0/3072.0));
	m_ctlReadOutsMtr13.SetdbValue0(pmac->DPRFixed((long*)&m_BtcData.Mtr13.PositionWord0,1.0/3072.0));
	m_ctlReadOutsMtr14.SetdbValue0(pmac->DPRFixed((long*)&m_BtcData.Mtr14.PositionWord0,1.0/3072.0));
	m_ctlReadOutsMtr15.SetdbValue0(pmac->DPRFixed((long*)&m_BtcData.Mtr15.PositionWord0,1.0/3072.0));
	m_ctlReadOutsMtr16.SetdbValue0(pmac->DPRFixed((long*)&m_BtcData.Mtr16.PositionWord0,1.0/3072.0));

	// Velocity
	m_ctlReadOutsMtr1.SetdbValue1(pmac->m_ServoFrequency*(m_BtcData.Mtr1.Velocity/3072.0));
	m_ctlReadOutsMtr2.SetdbValue1(pmac->m_ServoFrequency*(m_BtcData.Mtr2.Velocity/3072.0));
	m_ctlReadOutsMtr3.SetdbValue1(pmac->m_ServoFrequency*(m_BtcData.Mtr3.Velocity/3072.0));
	m_ctlReadOutsMtr4.SetdbValue1(pmac->m_ServoFrequency*(m_BtcData.Mtr4.Velocity/3072.0));
	m_ctlReadOutsMtr5.SetdbValue1(pmac->m_ServoFrequency*(m_BtcData.Mtr5.Velocity/3072.0));
	m_ctlReadOutsMtr6.SetdbValue1(pmac->m_ServoFrequency*(m_BtcData.Mtr6.Velocity/3072.0));
	m_ctlReadOutsMtr7.SetdbValue1(pmac->m_ServoFrequency*(m_BtcData.Mtr7.Velocity/3072.0));
	m_ctlReadOutsMtr8.SetdbValue1(pmac->m_ServoFrequency*(m_BtcData.Mtr8.Velocity/3072.0));
	m_ctlReadOutsMtr9.SetdbValue1(pmac->m_ServoFrequency*(m_BtcData.Mtr9.Velocity/3072.0));
	m_ctlReadOutsMtr10.SetdbValue1(pmac->m_ServoFrequency*(m_BtcData.Mtr10.Velocity/3072.0));
	m_ctlReadOutsMtr11.SetdbValue1(pmac->m_ServoFrequency*(m_BtcData.Mtr11.Velocity/3072.0));
	m_ctlReadOutsMtr12.SetdbValue1(pmac->m_ServoFrequency*(m_BtcData.Mtr12.Velocity/3072.0));
	m_ctlReadOutsMtr13.SetdbValue1(pmac->m_ServoFrequency*(m_BtcData.Mtr13.Velocity/3072.0));
	m_ctlReadOutsMtr14.SetdbValue1(pmac->m_ServoFrequency*(m_BtcData.Mtr14.Velocity/3072.0));
	m_ctlReadOutsMtr15.SetdbValue1(pmac->m_ServoFrequency*(m_BtcData.Mtr15.Velocity/3072.0));
	m_ctlReadOutsMtr16.SetdbValue1(pmac->m_ServoFrequency*(m_BtcData.Mtr16.Velocity/3072.0));

	// Motor following error
	m_ctlReadOutsMtr1.SetdbValue2(pmac->DPRFixed((long*)&m_BtcData.Mtr1.FollowingErrorWord0,1.0/3072.0));
	m_ctlReadOutsMtr2.SetdbValue2(pmac->DPRFixed((long*)&m_BtcData.Mtr2.FollowingErrorWord0,1.0/3072.0));
	m_ctlReadOutsMtr3.SetdbValue2(pmac->DPRFixed((long*)&m_BtcData.Mtr3.FollowingErrorWord0,1.0/3072.0));
	m_ctlReadOutsMtr4.SetdbValue2(pmac->DPRFixed((long*)&m_BtcData.Mtr4.FollowingErrorWord0,1.0/3072.0));
	m_ctlReadOutsMtr5.SetdbValue2(pmac->DPRFixed((long*)&m_BtcData.Mtr5.FollowingErrorWord0,1.0/3072.0));
	m_ctlReadOutsMtr6.SetdbValue2(pmac->DPRFixed((long*)&m_BtcData.Mtr6.FollowingErrorWord0,1.0/3072.0));
	m_ctlReadOutsMtr7.SetdbValue2(pmac->DPRFixed((long*)&m_BtcData.Mtr7.FollowingErrorWord0,1.0/3072.0));
	m_ctlReadOutsMtr8.SetdbValue2(pmac->DPRFixed((long*)&m_BtcData.Mtr8.FollowingErrorWord0,1.0/3072.0));
	m_ctlReadOutsMtr9.SetdbValue2(pmac->DPRFixed((long*)&m_BtcData.Mtr9.FollowingErrorWord0,1.0/3072.0));
	m_ctlReadOutsMtr10.SetdbValue2(pmac->DPRFixed((long*)&m_BtcData.Mtr10.FollowingErrorWord0,1.0/3072.0));
	m_ctlReadOutsMtr11.SetdbValue2(pmac->DPRFixed((long*)&m_BtcData.Mtr11.FollowingErrorWord0,1.0/3072.0));
	m_ctlReadOutsMtr12.SetdbValue2(pmac->DPRFixed((long*)&m_BtcData.Mtr12.FollowingErrorWord0,1.0/3072.0));
	if (m_BtcData.GlobalStatus== GS_RUNNING)
		m_ctlReadOutsMtr13.SetdbValue2(0);
	else
		m_ctlReadOutsMtr13.SetdbValue2(pmac->DPRFixed((long*)&m_BtcData.Mtr13.FollowingErrorWord0,1.0/3072.0));	
	m_ctlReadOutsMtr14.SetdbValue2(pmac->DPRFixed((long*)&m_BtcData.Mtr14.FollowingErrorWord0,1.0/3072.0));
	m_ctlReadOutsMtr15.SetdbValue2(pmac->DPRFixed((long*)&m_BtcData.Mtr15.FollowingErrorWord0,1.0/3072.0));
	m_ctlReadOutsMtr16.SetdbValue2(pmac->DPRFixed((long*)&m_BtcData.Mtr16.FollowingErrorWord0,1.0/3072.0));

	// Max FE
	m_ctlReadOutsMtr1.SetdbValue3(m_BtcData.MaxFE1);
	m_ctlReadOutsMtr2.SetdbValue3(m_BtcData.MaxFE2);
	m_ctlReadOutsMtr3.SetdbValue3(m_BtcData.MaxFE3);
	m_ctlReadOutsMtr4.SetdbValue3(m_BtcData.MaxFE4);
	m_ctlReadOutsMtr5.SetdbValue3(m_BtcData.MaxFE5);
	m_ctlReadOutsMtr6.SetdbValue3(m_BtcData.MaxFE6);
	m_ctlReadOutsMtr7.SetdbValue3(m_BtcData.MaxFE7);
	m_ctlReadOutsMtr8.SetdbValue3(m_BtcData.MaxFE8);
	m_ctlReadOutsMtr9.SetdbValue3(m_BtcData.MaxFE9);
	m_ctlReadOutsMtr10.SetdbValue3(m_BtcData.MaxFE10);
	m_ctlReadOutsMtr11.SetdbValue3(m_BtcData.MaxFE11);
	m_ctlReadOutsMtr12.SetdbValue3(m_BtcData.MaxFE12);
	m_ctlReadOutsMtr13.SetdbValue3(m_BtcData.MaxFE13);
	m_ctlReadOutsMtr14.SetdbValue3(m_BtcData.MaxFE14);
	m_ctlReadOutsMtr15.SetdbValue3(m_BtcData.MaxFE15);
	m_ctlReadOutsMtr16.SetdbValue3(m_BtcData.MaxFE16);

	// Motor Current
	m_ctlReadOutsMtr1.SetdbValue4(m_BtcData.CurrentMotor1);
	m_ctlReadOutsMtr2.SetdbValue4(m_BtcData.CurrentMotor2);
	m_ctlReadOutsMtr3.SetdbValue4(m_BtcData.CurrentMotor3);
	m_ctlReadOutsMtr4.SetdbValue4(m_BtcData.CurrentMotor4);
	m_ctlReadOutsMtr5.SetdbValue4(m_BtcData.CurrentMotor5);
	m_ctlReadOutsMtr6.SetdbValue4(m_BtcData.CurrentMotor6);
	m_ctlReadOutsMtr7.SetdbValue4(m_BtcData.CurrentMotor7);
	m_ctlReadOutsMtr8.SetdbValue4(m_BtcData.CurrentMotor8);
	m_ctlReadOutsMtr9.SetdbValue4(m_BtcData.CurrentMotor9);
	m_ctlReadOutsMtr10.SetdbValue4(m_BtcData.CurrentMotor10);
	m_ctlReadOutsMtr11.SetdbValue4(m_BtcData.CurrentMotor11);
	m_ctlReadOutsMtr12.SetdbValue4(m_BtcData.CurrentMotor12);
	m_ctlReadOutsMtr13.SetdbValue4(m_BtcData.CurrentMotor13);
	m_ctlReadOutsMtr14.SetdbValue4(m_BtcData.CurrentMotor14);
#ifndef OSCEOLA_LAYOUT
	m_ctlReadOutsMtr15.SetdbValue4(m_BtcData.CurrentMotor15);
#else
	// Exit VFD
	m_ctlReadOutsMtr15.SetdbValue4(((double)pApp->m_mil.m_ReadData.Current/100.0));
#endif
	m_ctlReadOutsMtr16.SetdbValue4(m_BtcData.CurrentMotor16);
	TotalCurrent = m_BtcData.CurrentMotor1 +
		m_BtcData.CurrentMotor2 +
		m_BtcData.CurrentMotor3 +
		m_BtcData.CurrentMotor4 +
		m_BtcData.CurrentMotor5 +
		m_BtcData.CurrentMotor6 +
		m_BtcData.CurrentMotor7 +
		m_BtcData.CurrentMotor8 +
		m_BtcData.CurrentMotor9 +
		m_BtcData.CurrentMotor10 +
		m_BtcData.CurrentMotor11 +
		m_BtcData.CurrentMotor12 +
		m_BtcData.CurrentMotor13 +
		m_BtcData.CurrentMotor14 +
		m_BtcData.CurrentMotor15 +
		m_BtcData.CurrentMotor16;
	m_ctlTotalCurrent.SetValue(TotalCurrent);

	// Peak Motor Current
	m_ctlReadOutsMtr1.SetdbValue5(m_BtcData.PeakCurrentMotor1);
	m_ctlReadOutsMtr2.SetdbValue5(m_BtcData.PeakCurrentMotor2);
	m_ctlReadOutsMtr3.SetdbValue5(m_BtcData.PeakCurrentMotor3);
	m_ctlReadOutsMtr4.SetdbValue5(m_BtcData.PeakCurrentMotor4);
	m_ctlReadOutsMtr5.SetdbValue5(m_BtcData.PeakCurrentMotor5);
	m_ctlReadOutsMtr6.SetdbValue5(m_BtcData.PeakCurrentMotor6);
	m_ctlReadOutsMtr7.SetdbValue5(m_BtcData.PeakCurrentMotor7);
	m_ctlReadOutsMtr8.SetdbValue5(m_BtcData.PeakCurrentMotor8);
	m_ctlReadOutsMtr9.SetdbValue5(m_BtcData.PeakCurrentMotor9);
	m_ctlReadOutsMtr10.SetdbValue5(m_BtcData.PeakCurrentMotor10);
	m_ctlReadOutsMtr11.SetdbValue5(m_BtcData.PeakCurrentMotor11);
	m_ctlReadOutsMtr12.SetdbValue5(m_BtcData.PeakCurrentMotor12);
	m_ctlReadOutsMtr13.SetdbValue5(m_BtcData.PeakCurrentMotor13);
	m_ctlReadOutsMtr14.SetdbValue5(m_BtcData.PeakCurrentMotor14);
	m_ctlReadOutsMtr15.SetdbValue5(m_BtcData.PeakCurrentMotor15);
	m_ctlReadOutsMtr16.SetdbValue5(m_BtcData.PeakCurrentMotor16);
	m_ctlReadOutsMtr1.UpdateReadouts();
	m_ctlReadOutsMtr2.UpdateReadouts();
	m_ctlReadOutsMtr3.UpdateReadouts();
	m_ctlReadOutsMtr4.UpdateReadouts();
	m_ctlReadOutsMtr5.UpdateReadouts();
	m_ctlReadOutsMtr6.UpdateReadouts();
	m_ctlReadOutsMtr7.UpdateReadouts();
	m_ctlReadOutsMtr8.UpdateReadouts();
	m_ctlReadOutsMtr9.UpdateReadouts();
	m_ctlReadOutsMtr10.UpdateReadouts();
	m_ctlReadOutsMtr11.UpdateReadouts();
	m_ctlReadOutsMtr12.UpdateReadouts();
	m_ctlReadOutsMtr13.UpdateReadouts();
	m_ctlReadOutsMtr14.UpdateReadouts();
	m_ctlReadOutsMtr15.UpdateReadouts();
	m_ctlReadOutsMtr16.UpdateReadouts();

	// Hall State
	m_ctlMtrUVWT1.SetValue(m_BtcData.Mtr1Mtr2FlagsHalls.HallWVUT1);
	m_ctlMtrUVWT2.SetValue(m_BtcData.Mtr1Mtr2FlagsHalls.HallWVUT2);
	m_ctlMtrUVWT3.SetValue(m_BtcData.Mtr3Mtr4FlagsHalls.HallWVUT1);
	m_ctlMtrUVWT4.SetValue(m_BtcData.Mtr3Mtr4FlagsHalls.HallWVUT2);
	m_ctlMtrUVWT5.SetValue(m_BtcData.Mtr5Mtr6FlagsHalls.HallWVUT1);
	m_ctlMtrUVWT6.SetValue(m_BtcData.Mtr5Mtr6FlagsHalls.HallWVUT2);
	m_ctlMtrUVWT7.SetValue(m_BtcData.Mtr7Mtr8FlagsHalls.HallWVUT1);
	m_ctlMtrUVWT8.SetValue(m_BtcData.Mtr7Mtr8FlagsHalls.HallWVUT2);
	m_ctlMtrUVWT9.SetValue(m_BtcData.Mtr9Mtr10FlagsHalls.HallWVUT1);
	m_ctlMtrUVWT10.SetValue(m_BtcData.Mtr9Mtr10FlagsHalls.HallWVUT2);
	m_ctlMtrUVWT11.SetValue(m_BtcData.Mtr11Mtr12FlagsHalls.HallWVUT1);
	m_ctlMtrUVWT12.SetValue(m_BtcData.Mtr11Mtr12FlagsHalls.HallWVUT2);
	m_ctlMtrUVWT13.SetValue(m_BtcData.Mtr13Mtr14FlagsHalls.HallWVUT1);
	m_ctlMtrUVWT14.SetValue(m_BtcData.Mtr13Mtr14FlagsHalls.HallWVUT2);
#ifndef OSCEOLA_LAYOUT
	m_ctlMtrUVWT15.SetValue(m_BtcData.Mtr15Mtr16FlagsHalls.HallWVUT1);
#else
	// Exit VFD
	m_ctlMtrUVWT15.SetValue((int)pApp->m_mil.m_ReadData.FaultCode);
	//TRACE("Fault Code: %x \n",(int)pApp->m_mil.m_ReadData.FaultCode);
#endif
	m_ctlMtrUVWT16.SetValue(m_BtcData.Mtr15Mtr16FlagsHalls.HallWVUT2);


	m_ctlLedTUVW1.SetIoStatusWord(m_BtcData.Mtr1Mtr2FlagsHalls.HallWVUT1);
	m_ctlLedTUVW2.SetIoStatusWord(m_BtcData.Mtr1Mtr2FlagsHalls.HallWVUT2);
	m_ctlLedTUVW3.SetIoStatusWord(m_BtcData.Mtr3Mtr4FlagsHalls.HallWVUT1);	
	m_ctlLedTUVW4.SetIoStatusWord(m_BtcData.Mtr3Mtr4FlagsHalls.HallWVUT2);
	m_ctlLedTUVW5.SetIoStatusWord(m_BtcData.Mtr5Mtr6FlagsHalls.HallWVUT1);
	m_ctlLedTUVW6.SetIoStatusWord(m_BtcData.Mtr5Mtr6FlagsHalls.HallWVUT2);
	m_ctlLedTUVW7.SetIoStatusWord(m_BtcData.Mtr7Mtr8FlagsHalls.HallWVUT1);
	m_ctlLedTUVW8.SetIoStatusWord(m_BtcData.Mtr7Mtr8FlagsHalls.HallWVUT2);
	m_ctlLedTUVW9.SetIoStatusWord(m_BtcData.Mtr9Mtr10FlagsHalls.HallWVUT1);
	m_ctlLedTUVW10.SetIoStatusWord(m_BtcData.Mtr9Mtr10FlagsHalls.HallWVUT2);
	m_ctlLedTUVW11.SetIoStatusWord(m_BtcData.Mtr11Mtr12FlagsHalls.HallWVUT1);
	m_ctlLedTUVW12.SetIoStatusWord(m_BtcData.Mtr11Mtr12FlagsHalls.HallWVUT2);
	m_ctlLedTUVW13.SetIoStatusWord(m_BtcData.Mtr13Mtr14FlagsHalls.HallWVUT1);
	m_ctlLedTUVW14.SetIoStatusWord(m_BtcData.Mtr13Mtr14FlagsHalls.HallWVUT2);
	m_ctlLedTUVW15.SetIoStatusWord(m_BtcData.Mtr15Mtr16FlagsHalls.HallWVUT1);
	m_ctlLedTUVW16.SetIoStatusWord(m_BtcData.Mtr15Mtr16FlagsHalls.HallWVUT2);

	// Drive bus voltage
	m_ctlBusVoltage1.SetValue(m_BtcData.BusVoltage1);
	m_ctlBusVoltage2.SetValue(m_BtcData.BusVoltage2);
#ifdef OSCEOLA_LAYOUT
	m_ctlBusVoltage3.ShowWindow(SW_HIDE);
#endif
	m_ctlBusVoltage3.SetValue(m_BtcData.BusVoltage3);

	//switch (m_BtcData.VoltTempDriveSelect)
	//{
	//case 1:
	//	m_ctlBusVoltage1.SetValue(m_BtcData.BusVoltage);
	//	break;
	//case 2:
	//	m_ctlBusVoltage2.SetValue(m_BtcData.BusVoltage);
	//	break;
	//case 3:
	//	m_ctlBusVoltage3.SetValue(m_BtcData.BusVoltage);
	//	break;
	//}

	// Blade IGBT temp
	m_ctlBladeIGBTTemp.SetValue(m_BtcData.IGBTTemp);
	//=====================================================================================================//


	// Time Stamp response
	pWnd = GetDlgItem(IDC_TIME_STAMP_RES);
	str.Format(_T("%d"),m_BtcData.ComTicks);
	pWnd->SetWindowText(str);
	pWnd = GetDlgItem(IDC_TIME_STAMP_PERIOD);
	str.Format(_T("%d"),m_BtcData.DataPeriod);
	pWnd->SetWindowText(str);

	// Queue size
	pWnd = GetDlgItem(IDC_QUEUE);
	str.Format(_T("%d"),pApp->m_mil.MilHook1.QueueSize);
	pWnd->SetWindowText(str);

	//// ResyncCount 
	//pWnd = GetDlgItem(IDC_RESYNC);
	//str.Format(_T("%d"),pApp->m_mil.MilHook1.ResyncCount);
	//pWnd->SetWindowText(str);

	// Latch Diff 
	pWnd = GetDlgItem(IDC_LAG);
	str.Format(_T("%d"),pApp->m_mil.MilHook1.LatchDiff);
	pWnd->SetWindowText(str);

	// Vision Page
	pWnd = GetDlgItem(IDC_BACON_POS);
	str.Format(_T("%d"),pApp->m_mil.MilHook1.Position);
	pWnd->SetWindowText(str);

	// Vision Page Align motor Position
	pWnd = GetDlgItem(IDC_BACON_POS2);
	str.Format(_T("%d"),(long)pmac->DPRFixed((long*)&m_BtcData.Mtr1.PositionWord0,1.0/3072.0));
	pWnd->SetWindowText(str);

	pWnd = GetDlgItem(IDC_BACON_COUNT);
	str.Format(_T("%d"),pApp->m_mil.MilHook1.TotalBlobCount);
	pWnd->SetWindowText(str);

	// Total Rejects	
	pWnd = GetDlgItem(IDC_TOTAL_REJECTS);
	str.Format(_T("%d"),(int)pApp->m_mil.MilHook1.TotalRejectCount);
	pWnd->SetWindowText(str);

	// Time stamp peaks
	if (m_BtcData.DataPeriod > pApp->m_mil.MilHook1.MaxComPeriod)
	{
		pApp->m_mil.MilHook1.MaxComPeriod = m_BtcData.DataPeriod;
	}
	if (m_BtcData.ComTicks > pApp->m_mil.MilHook1.MaxTimeStampRes)
	{
		pApp->m_mil.MilHook1.MaxTimeStampRes = m_BtcData.ComTicks;
	}

	//// Bacon Speed	  IDC_SLICES_PER_MINUTE
	//double SlicePerMin = m_ctlSliceCount.GetValue();
	//if (m_BtcData.BaconSpeed < 500)
	//{
	//	m_BtcData.BaconSpeed  = 500;
	//}
	//if (m_BtcData.BaconSpeed > 6000)
	//{
	//	m_BtcData.BaconSpeed  = 6000;
	//}
	//SlicePerMin = (SlicePerMin / ((double)m_BtcData.BaconSpeed/1000.0)) *60;
	//str.Format(_T("%d"),(int)SlicePerMin);
	//pApp->m_mil.MilHook1.BaconSpeed = SlicePerMin;	


	//// Show com status
	//if (m_EIPWriteError > 0)
	//{
	//	m_ctlSlicerStatus.SetLedColorSelect(0);
	//	m_ctlSlicerStatus.SetIoStatusWord(1);
	//	m_ctlSlicerStatus.SetIOStatusBit(0);
	//	m_ctlSlicerStatus.SetIOStatusText(_T("Com Error"));
	//}
	//else
	//{
	//	m_ctlSlicerStatus.SetLedColorSelect(1);	
	//	m_ctlSlicerStatus.SetIOStatusBit(0);
	//	m_ctlSlicerStatus.SetIOStatusText(_T("Running"));
	//}

    //=====================================================================================================//
	// I/O Page
	//=====================================================================================================//
	ScanIO();

	// Alarm Messages
	///////////////////////////////////////////////;
	ScanAlarms();

	//pWnd->SetWindowText(str);
	if (pApp->m_mil.MilHook2.RecordIndex == MAX_RECORD)
	{
		CWnd* pBtn = (CButton*)GetDlgItem(IDC_RECORD_BELLY);
		pBtn->EnableWindow(1);	
	    //pBtn = (CButton*)GetDlgItem(IDC_PLAY_BELLY);
	    //pBtn->EnableWindow(1);
	}
	//pBtn = (CButton*)GetDlgItem(IDC_STOP_PLAY);

	// Update the PMAC terminal window
	pApp->UpdateTerminal();

#ifdef OSCEOLA_LAYOUT

	// Clear the reset bit
	if (pApp->m_mil.m_WriteData.VfdReset == 1)
	{
		pApp->m_mil.m_WriteData.VfdReset = 0;
		TRACE(_T("Clear the reset bit...\n"));
	}

	// Update VFD data
	pApp->m_mil.m_WriteData.VfdSpeedInPerSec = m_BtcData.ExitVfdSpeedInPerSec;
	pApp->m_mil.m_WriteData.VfdRun = m_BtcData.StatusBits.ExitVfdRun;

	// Com is Off
	if (pApp->m_mil.ReadWriteComData() > 0)
	{
		//m_ctlSlicerStatus.SetLedColorSelect(0);
		//m_ctlSlicerStatus.SetIoStatusWord(1);
		//m_ctlSlicerStatus.SetIOStatusBit(0);
		//m_ctlSlicerStatus.SetIOStatusText(_T("Com Off"));
		//TRACE(_T("Com Off \n"));
		m_bComOn = false;
	}
	// Com is On
	else
	{
		m_bComOn = true;
		//m_ctlSlicerStatus.SetLedColorSelect(1);	
		//m_ctlSlicerStatus.SetIOStatusBit(0);
		//if (pApp->m_mil.m_ReadData.SlicerStatus)
		//	m_ctlSlicerStatus.SetIOStatusText(_T("Slicing"));
		//else
		//	m_ctlSlicerStatus.SetIOStatusText(_T("Stopped"));	
		//pApp->m_mil.m_WriteData.VfdSpeedInPerSec = m_BtcData.ExitVfdSpeedInPerSec;
		//pApp->m_mil.m_WriteData.VfdRun = m_BtcData.StatusBits.ExitVfdRun;

		//m_ReadData
		//m_WriteData
		//if (pApp->m_mil.m_ReadData.VfdFaulted==1)
		//{
		//	pApp->m_mil.m_WriteData.VfdReset = 1;
		//}
		//TRACE(_T("Com ON HeartBeat %d VFD Faulted %d  Code: %d\n"),pApp->m_mil.m_ReadData.HeartBeat,pApp->m_mil.m_ReadData.VfdFaulted,pApp->m_mil.m_ReadData.FaultCode);
		//TRACE(_T("Speed %d \n"),m_BtcData.ExitVfdSpeedInPerSec);
	}
#endif

	// Time measurement
	MappTimer(M_TIMER_READ, &dbTimeEnd);
	//TRACE("Update time: %f \n",(dbTimeEnd-dbTimeStart)*1000);


}

// ScanIO 
//////////////////////////////////////////////;
void CHMIView::ScanIO()
{
	CHMIApp* pApp = (CHMIApp*)AfxGetApp();

	//BTCINPUTS IOStatusWord;
	BTCWORD IOStatusWord;

	// BTC Input Status update
	m_ctlInputs.SetIoStatusWord(m_BtcData.BtcInputs.IOWord);

	// Output Status update
	//TRACE(_T("m_BtcData.BtcOutputs.IOWord %d \n"),m_BtcData.BtcOutputs.IOWord);
	m_ctlOutputs.SetIoStatusWord(m_BtcData.BtcOutputs.IOWord);
	m_ctlBladeBrake.SetLightOn(m_BtcData.SlicerOutputs.BladeBreak);

	// Slicer Output Status update
	m_ctlOutputs2.SetIoStatusWord(m_BtcData.SlicerOutputs.IOWord);

	// Slicer Input Status update
	//IOStatusWord.Bits.In0 =  m_BtcData.SlicerInputs.SafetyEStop;
	//IOStatusWord.Bits.In1 =  m_BtcData.SlicerInputs.SlicerDisconnect;
	//IOStatusWord.Bits.In2 =  m_BtcData.SlicerInputs.In3;
	//IOStatusWord.Bits.In3 =  m_BtcData.SlicerInputs.TrapKeyStatus;
	//IOStatusWord.Bits.In4 =  m_BtcData.SlicerInputs.SlicerBellyEye;
	//IOStatusWord.Bits.In5 =  m_BtcData.SlicerInputs.In6;
	//IOStatusWord.Bits.In6 =  m_BtcData.SlicerInputs.BelevatorEstop;
	//IOStatusWord.Bits.In7 =  m_BtcData.SlicerInputs.In8;
	//IOStatusWord.Bits.In8 =  m_BtcData.SlicerInputs.ShuntOverTemp1;
	//IOStatusWord.Bits.In9 =  m_BtcData.SlicerInputs.BelevartoPusherBack;
	//IOStatusWord.Bits.In10 = m_BtcData.SlicerInputs.ShuntOverTemp2;
	//IOStatusWord.Bits.In11 =  m_BtcData.SlicerInputs.BelevatorStart;
	//IOStatusWord.Bits.In12 =  m_BtcData.SlicerInputs.BelevatorStop;
	//m_ctlSlicerInputs.SetIoStatusWord(IOStatusWord.IOWord);
	m_ctlSlicerInputs.SetIoStatusWord(m_BtcData.SlicerInputs.IOWord);
	
	// BTC Servo Input Status update
	IOStatusWord.Bits.In0 = m_BtcData.Mtr1Mtr2FlagsHalls.USER1;
	IOStatusWord.Bits.In1 = m_BtcData.Mtr1Mtr2FlagsHalls.PLIM1;
	IOStatusWord.Bits.In2 = m_BtcData.Mtr1Mtr2FlagsHalls.MLIM1;
	IOStatusWord.Bits.In3 = m_BtcData.Mtr1Mtr2FlagsHalls.HMFL1;
	IOStatusWord.Bits.In4 = m_BtcData.Mtr1Mtr2FlagsHalls.USER2;
	IOStatusWord.Bits.In5 = m_BtcData.Mtr1Mtr2FlagsHalls.PLIM2;
	IOStatusWord.Bits.In6 = m_BtcData.Mtr1Mtr2FlagsHalls.MLIM2;
	IOStatusWord.Bits.In7 = m_BtcData.Mtr1Mtr2FlagsHalls.HMFL2;
	IOStatusWord.Bits.In8 = m_BtcData.Mtr3Mtr4FlagsHalls.USER1;
	IOStatusWord.Bits.In9 = m_BtcData.Mtr3Mtr4FlagsHalls.PLIM1;
	IOStatusWord.Bits.In10 = m_BtcData.Mtr3Mtr4FlagsHalls.MLIM1;
	IOStatusWord.Bits.In11 = m_BtcData.Mtr3Mtr4FlagsHalls.HMFL1;
	IOStatusWord.Bits.In12 = m_BtcData.Mtr3Mtr4FlagsHalls.USER2;
	IOStatusWord.Bits.In13 = m_BtcData.Mtr3Mtr4FlagsHalls.PLIM2;
	IOStatusWord.Bits.In14 = m_BtcData.Mtr3Mtr4FlagsHalls.MLIM2;
	IOStatusWord.Bits.In15 = m_BtcData.Mtr3Mtr4FlagsHalls.HMFL2;
	m_ctlFlagInputs.SetIoStatusWord(IOStatusWord.IOWord);

	// Slicer Servo Input Status update
	IOStatusWord.Bits.In0 = m_BtcData.Mtr9Mtr10FlagsHalls.USER1;
	IOStatusWord.Bits.In1 = m_BtcData.Mtr9Mtr10FlagsHalls.MLIM1;
	IOStatusWord.Bits.In2 = m_BtcData.Mtr9Mtr10FlagsHalls.PLIM1;
	IOStatusWord.Bits.In3 = m_BtcData.Mtr9Mtr10FlagsHalls.HMFL1;
	IOStatusWord.Bits.In4 = m_BtcData.Mtr13Mtr14FlagsHalls.USER2;
	IOStatusWord.Bits.In5 = m_BtcData.Mtr13Mtr14FlagsHalls.PLIM2; // Belly Detect eye
	IOStatusWord.Bits.In6 = m_BtcData.Mtr13Mtr14FlagsHalls.MLIM2; // Chute eye
	IOStatusWord.Bits.In7 = m_BtcData.Mtr13Mtr14FlagsHalls.HMFL2; //


	IOStatusWord.Bits.In8 = m_bComOn; 
	IOStatusWord.Bits.In9 = pApp->m_mil.m_ReadData.VfdRunning;
	IOStatusWord.Bits.In10 = pApp->m_mil.m_ReadData.VfdFaulted;
	IOStatusWord.Bits.In11 = 1;
	IOStatusWord.Bits.In12 = 1;
	IOStatusWord.Bits.In13 = 1;
	IOStatusWord.Bits.In14 = 1;
	IOStatusWord.Bits.In15 = 1;
	m_ctlSlicerFlagInputs.SetIoStatusWord(IOStatusWord.IOWord);

	// Reject Outputs
	MIL_INT64 OutputStatus;
	MsysInquire(M_DEFAULT_HOST, M_USER_BIT_STATE_ALL, &OutputStatus);	
	IOStatusWord.IOWord = (short)OutputStatus;
	m_ctlOutputs3.SetIoStatusWord(IOStatusWord.IOWord);

}
// Alarm Messages
//////////////////////////////////////////////;
void CHMIView::ScanAlarms()
{
	if (m_BtcData.StatusBits.BellyChuteEyeBlocked==1 && !m_bAlarmLatch[0])
	{
		m_bAlarmLatch[0] = true;
		if (m_pAlarm1 != NULL)
		{
			m_pAlarm1->SetFocus ();		
		}
		else
		{
			CAlarms* pDlg = new CAlarms(this);
			pDlg->m_ppBackPtr = &m_pAlarm1;
			pDlg->m_nID = 0;
			pDlg->m_strMsg =_T(" Belly Chute Eye is blocked!");
			pDlg->Create (IDD_ALARMS_DIALOG);
			pDlg->ShowWindow (SW_SHOW);
			m_pAlarm1 = pDlg;
			m_FaultHistory.AddString(_T("Belly Chute is blocked"));
			// m_FaultHistory.SaveStrings();
		}
	}
	// Slicer Eye
	if (m_BtcData.StatusBits.BellyJamInSlicer==1 && !m_bAlarmLatch[1])
	{
		m_bAlarmLatch[1] = true;
		if (m_pAlarm2 != NULL)
		{
			m_pAlarm2->SetFocus ();
		}
		else
		{
			CAlarms* pDlg = new CAlarms(this);
			pDlg->m_ppBackPtr = &m_pAlarm2;
			pDlg->m_nID = 1;
			pDlg->m_strMsg =_T(" Belly jam detected in slicer!");
			pDlg->Create (IDD_ALARMS_DIALOG);
			pDlg->ShowWindow (SW_SHOW);
			m_pAlarm2 = pDlg;
			m_FaultHistory.AddString(_T("Belly jam detected in slicer"));
			// m_FaultHistory.SaveStrings();
		}
	}
	// Belly Chute Eye
	if (m_BtcData.StatusBits.BellyJamInLoader==1 && !m_bAlarmLatch[2])
	{
		m_bAlarmLatch[2] = true;
		if (m_pAlarm3 != NULL)
		{
			m_pAlarm3->SetFocus ();
		}
		else
		{
			CAlarms* pDlg = new CAlarms(this);
			pDlg->m_ppBackPtr = &m_pAlarm3;
			pDlg->m_nID = 2;
			pDlg->m_strMsg =_T(" No belly detected in chute!");
			pDlg->Create (IDD_ALARMS_DIALOG);
			pDlg->ShowWindow (SW_SHOW);
			m_pAlarm3 = pDlg;
			m_FaultHistory.AddString(_T("No belly detected in chute! (Chute Eye not made)"));
			// m_FaultHistory.SaveStrings();
		}
	}
	// Belly Pusher
	if (m_BtcData.StatusBits.BellyPusherStuck==1 && !m_bAlarmLatch[3])
	{
		m_bAlarmLatch[3] = true;
		if (m_pAlarm4 != NULL)
		{
			m_pAlarm4->SetFocus ();
		}
		else
		{
			CAlarms* pDlg = new CAlarms(this);
			pDlg->m_ppBackPtr = &m_pAlarm4;
			pDlg->m_nID = 3;
			pDlg->m_strMsg =_T(" Belly Pusher Jam Detected!");
			pDlg->Create (IDD_ALARMS_DIALOG);
			pDlg->ShowWindow (SW_SHOW);
			m_pAlarm4 = pDlg;
			m_FaultHistory.AddString(_T("Belly Pusher Jam Detected"));
			// m_FaultHistory.SaveStrings();
		}
	}
	
	// Paper Eyes
	if (m_BtcData.StatusBits.PaperEyeError==1 && !m_bAlarmLatch[4] && m_BtcData.StatusBits.PaperOut==0)
	{
		m_bAlarmLatch[4] = true;
		if (m_pAlarm5 != NULL)
		{
			m_pAlarm5->SetFocus ();
		}
		else
		{
			CAlarms* pDlg = new CAlarms(this);
			pDlg->m_ppBackPtr = &m_pAlarm5;
			pDlg->m_nID = 4;
			pDlg->m_strMsg =_T(" Paper Eye Error!");
			pDlg->Create (IDD_ALARMS_DIALOG);
			pDlg->ShowWindow (SW_SHOW);
			m_pAlarm5 = pDlg;
			m_FaultHistory.AddString(_T("Paper Eye Error"));
			// m_FaultHistory.SaveStrings();
		}
	}
	// Paper Out
	if (m_BtcData.StatusBits.PaperOut==1 && !m_bAlarmLatch[5])
	{
		m_bAlarmLatch[5] = true;
		if (m_pAlarm5 != NULL)
		{
			m_pAlarm5->SetFocus ();
		}
		else
		{
			CAlarms* pDlg = new CAlarms(this);
			pDlg->m_ppBackPtr = &m_pAlarm5;
			pDlg->m_nID = 5;
			pDlg->m_strMsg =_T(" Paper Empty!");
			pDlg->Create (IDD_ALARMS_DIALOG);
			pDlg->ShowWindow (SW_SHOW);
			m_pAlarm5 = pDlg;
			//m_FaultHistory.AddString(_T("Paper Empty"));
			//// m_FaultHistory.SaveStrings();
		}
	}

	// Align Home fault
	//---------------------------------------------------------------------//
	if (m_BtcData.StatusBits.AlignHomeFault==1 && !m_bAlarmLatch[7])
	{
		m_bAlarmLatch[7] = true;
		if (m_pAlarm7 != NULL)
		{
			m_pAlarm7->SetFocus ();		
		}
		else
		{
			CAlarms* pDlg = new CAlarms(this);
			pDlg->m_ppBackPtr = &m_pAlarm7;
			pDlg->m_nID = 7;
			pDlg->m_strMsg =_T(" Align Home Fault!");
			pDlg->Create (IDD_ALARMS_DIALOG);
			pDlg->ShowWindow (SW_SHOW);
			m_pAlarm7 = pDlg;
			m_FaultHistory.AddString(_T("Align Home Fault!"));
		}
	}
	//---------------------------------------------------------------------//

	// Flipper Home fault
	//---------------------------------------------------------------------//
	if (m_BtcData.StatusBits.FlipperHomeFault==1 && !m_bAlarmLatch[8])
	{
		m_bAlarmLatch[8] = true;
		if (m_pAlarm8 != NULL)
		{
			m_pAlarm8->SetFocus ();		
		}
		else
		{
			CAlarms* pDlg = new CAlarms(this);
			pDlg->m_ppBackPtr = &m_pAlarm8;
			pDlg->m_nID = 8;
			pDlg->m_strMsg =_T(" Flipper Home Fault!");
			pDlg->Create (IDD_ALARMS_DIALOG);
			pDlg->ShowWindow (SW_SHOW);
			m_pAlarm8 = pDlg;
			m_FaultHistory.AddString(_T("Flipper Home Fault!"));
		}
	}
	//---------------------------------------------------------------------//

	// SlicerBladeHomeFault fault
	//---------------------------------------------------------------------//
	if (m_BtcData.StatusBits.SlicerBladeHomeFault==1 && !m_bAlarmLatch[9])
	{
		m_bAlarmLatch[9] = true;
		if (m_pAlarm9 != NULL)
		{
			m_pAlarm9->SetFocus ();		
		}
		else
		{
			CAlarms* pDlg = new CAlarms(this);
			pDlg->m_ppBackPtr = &m_pAlarm9;
			pDlg->m_nID = 9;
			pDlg->m_strMsg =_T(" Slicer Blade Home Fault!");
			pDlg->Create (IDD_ALARMS_DIALOG);
			pDlg->ShowWindow (SW_SHOW);
			m_pAlarm9 = pDlg;
			m_FaultHistory.AddString(_T("Slicer Blade Home Fault!"));
		}
	}
	//---------------------------------------------------------------------//

	// KnifeHomeFault fault
	//---------------------------------------------------------------------//
	if (m_BtcData.StatusBits.KnifeHomeFault==1 && !m_bAlarmLatch[10])
	{
		m_bAlarmLatch[10] = true;
		if (m_pAlarm10 != NULL)
		{
			m_pAlarm10->SetFocus ();		
		}
		else
		{
			CAlarms* pDlg = new CAlarms(this);
			pDlg->m_ppBackPtr = &m_pAlarm10;
			pDlg->m_nID = 10;
			pDlg->m_strMsg =_T(" Align Home Fault!");
			pDlg->Create (IDD_ALARMS_DIALOG);
			pDlg->ShowWindow (SW_SHOW);
			m_pAlarm10 = pDlg;
			m_FaultHistory.AddString(_T("Align Home Fault!"));
		}
	}
	//---------------------------------------------------------------------//

	// DrumHomeFault fault
	//---------------------------------------------------------------------//
	if (m_BtcData.StatusBits.DrumHomeFault==1 && !m_bAlarmLatch[11])
	{
		m_bAlarmLatch[11] = true;
		if (m_pAlarm11 != NULL)
		{
			m_pAlarm11->SetFocus ();		
		}
		else
		{
			CAlarms* pDlg = new CAlarms(this);
			pDlg->m_ppBackPtr = &m_pAlarm11;
			pDlg->m_nID = 11;
			pDlg->m_strMsg =_T(" Flipper Home Fault!");
			pDlg->Create (IDD_ALARMS_DIALOG);
			pDlg->ShowWindow (SW_SHOW);
			m_pAlarm11 = pDlg;
			m_FaultHistory.AddString(_T("Flipper Home Fault!"));
		}
	}
	//---------------------------------------------------------------------//

	// TTFault fault
	//---------------------------------------------------------------------//
	if (m_BtcData.StatusBits.TTFault==1 && !m_bAlarmLatch[12])
	{
		m_bAlarmLatch[12] = true;
		if (m_pAlarm12 != NULL)
		{
			m_pAlarm12->SetFocus ();		
		}
		else
		{
			CAlarms* pDlg = new CAlarms(this);
			pDlg->m_ppBackPtr = &m_pAlarm12;
			pDlg->m_nID = 12;
			pDlg->m_strMsg =_T(" Two-Tier Fault!");
			pDlg->Create (IDD_ALARMS_DIALOG);
			pDlg->ShowWindow (SW_SHOW);
			m_pAlarm12 = pDlg;
			m_FaultHistory.AddString(_T("Two-Tier Fault!"));
		}
	}
	//---------------------------------------------------------------------//
}

// 
// GetMotorState(MOTORDATA* pMtr)
int CHMIView::GetMotorState(LPCTSTR lpName,MOTORDATA* pMtr,unsigned char Halls,bool* pFaultLatch,bool* pWarnLatch)
{
	CString fault = lpName;

	// Over current
	if (pMtr->MotorStatus.Bits.amp_i2t_err)
	{
		if (*pFaultLatch==false)
		{
			*pFaultLatch = true;
			fault += _T(" Over Current");
			if (m_strLastfault != fault)
			{
			   m_FaultHistory.AddString(fault);
			   // m_FaultHistory.SaveStrings();
			   m_strLastfault = fault;
			}
		}
		return 5;
	}
	if (pMtr->MotorStatus.Bits.amp_fault)
	{
		if (*pFaultLatch==false)
		{
			*pFaultLatch = true;
			if (pMtr->MotorStatus.Bits.amp_i2t_err)
			{
			   fault += _T(" Amp Fault i2t");
			}
			else
			{
			   fault += _T(" Amp Fault");
			}
			if (m_strLastfault != fault)
			{
			   m_FaultHistory.AddString(fault);
			   // m_FaultHistory.SaveStrings();
			   m_strLastfault = fault;
			}
		}
		return 4;
	}
	if (pMtr->MotorStatus.Bits.fatal_ferr)
	{
		if (*pFaultLatch==false)
		{
			*pFaultLatch = true;
			fault += _T(" Fatal Following Error");
			if (m_strLastfault != fault)
			{
			   m_FaultHistory.AddString(fault);
			   // m_FaultHistory.SaveStrings();
			   m_strLastfault = fault;
			}
			TRACE(_T("Setting %s fault latch...\n"),fault);
		}
		//else 
		//{
		//TRACE("FFE *pFaultLatch==true not string saved... \n");		
		//}
		return 3;
	}
	if (pMtr->MotorStatus.Bits.warn_ferr)
	{
		if (*pWarnLatch==false)
		{
			*pWarnLatch = true;
			fault += _T(" Warning Following Error");
			if (m_strLastfault != fault)
			{
			   m_FaultHistory.AddString(fault);
			   // m_FaultHistory.SaveStrings();
			   m_strLastfault = fault;
			}
		}
		return 2;
	}
	else
	{
		*pWarnLatch = false;	
	}

	// Encoder
	if (Halls ==15)
	{
		if (*pFaultLatch==false)
		{
			*pFaultLatch = true;
			fault += _T(" Encoder Fault");
			if (m_strLastfault != fault)
			{
			   m_FaultHistory.AddString(fault);
			   // m_FaultHistory.SaveStrings();
			   m_strLastfault = fault;
			}
		}
		return 9;
	}
	// Encoder count error
	if (pMtr->MotorStatus.Bits.encoder_count_error)
	{
		if (*pFaultLatch==false)
		{
			*pFaultLatch = true;
			fault += _T(" Encoder Count error");
			if (m_strLastfault != fault)
			{
			   m_FaultHistory.AddString(fault);
			   // m_FaultHistory.SaveStrings();
			   m_strLastfault = fault;
			}
		}
		return 10;
	}
	// Phase Error
	if (pMtr->MotorStatus.Bits.reset_phase_error)
	{
		if (*pFaultLatch==false)
		{
			*pFaultLatch = true;
			fault += _T(" Reset Phase error");
			if (m_strLastfault != fault)
			{
			   m_FaultHistory.AddString(fault);
			   // m_FaultHistory.SaveStrings();
			   m_strLastfault = fault;
			}
		}
		return 11;
	}

	// Hall state error
	if (Halls==0 || Halls==7)
	{
		if (*pFaultLatch==false)
		{
			*pFaultLatch = true;
			fault += _T(" Hall State Error");
			if (m_strLastfault != fault)
			{
			   m_FaultHistory.AddString(fault);
			   // m_FaultHistory.SaveStrings();
			   m_strLastfault = fault;
			}
		}
		return 6;
	}
	// Thermal switch
	//if (Halls & 0x8)
	//{
	//	if (*pFaultLatch==false)
	//	{
	//		*pFaultLatch = true;
	//		fault += _T(" Motor Overtemp");
	//		m_FaultHistory.AddString(fault);
	//		// m_FaultHistory.SaveStrings();
	//	}
	//	return 8;
	//}
	if (pMtr->ServoStatus.Bits.amp_enabled && pMtr->ServoStatus.Bits.open_loop)
	{
		if (*pFaultLatch==true)
		{
		   TRACE(_T("%s Clear fault latch \n"),fault);
		   *pFaultLatch = false;
		}
		return 7;		
	}
	if (pMtr->ServoStatus.Bits.amp_enabled && pMtr->ServoStatus.Bits.open_loop==0)
	{
		if (*pFaultLatch==true)
		{
			TRACE(_T("%s Clear fault latch motor closed loop\n"),fault);
		   *pFaultLatch = false;
		}
		return 1;		
	}

	return 0;
}

const CString CHMIView::m_HallsBits[16] = {
		_T("0 0 0 0"),
		_T("0 0 0 1"),
		_T("0 0 1 0"),
		_T("0 0 1 1"),
		_T("0 1 0 0"),
		_T("0 1 0 1"),
		_T("0 1 1 0"),
		_T("0 1 1 1"),
		_T("1 0 0 0"),
		_T("1 0 0 1"),
		_T("1 0 1 0"),
		_T("1 0 1 1"),
		_T("1 1 0 0"),
		_T("1 1 0 1"),
		_T("1 1 1 0"),
		_T("1 1 1 1")
};


LPCTSTR CHMIView::GetHallValue(unsigned char Halls)
{
	unsigned char Index = Halls & 0x0F;
	//const static CString HallsBits[] = {
	//	_T("0 0 0 0"),
	//	_T("0 0 0 1"),
	//	_T("0 0 1 0"),
	//	_T("0 0 1 1"),
	//	_T("0 1 0 0"),
	//	_T("0 1 0 1"),
	//	_T("0 1 1 0"),
	//	_T("0 1 1 1"),
	//	_T("1 0 0 0"),
	//	_T("1 0 0 1"),
	//	_T("1 0 1 0"),
	//	_T("1 0 1 1"),
	//	_T("1 1 0 0"),
	//	_T("1 1 0 1"),
	//	_T("1 1 1 0"),
	//	_T("1 1 1 1"),
	//};
	//TRACE(_T("Index %d %s\n"),Index,HallsBits[Index]);

	return m_HallsBits[Index];
}

void CHMIView::OnBnClickedClearPeaks1()
{
	CString fault;
	fault.Format(_T("Clear Peaks Motor 1: I=%4.2f amps FE=%d cts"),m_BtcData.PeakCurrentMotor1,m_BtcData.PeakCurrentMotor1);
	m_FaultHistory.AddString(fault);
	// m_FaultHistory.SaveStrings();

	CHMIApp* pApp = (CHMIApp*)AfxGetApp();
	CPmac* pmac = &pApp->m_pmac;
	pmac->DPRSet(DPR_OFFSET_PEAK_I1,(long)0);
	pmac->DPRSet(DPR_OFFSET_PEAK_FE1,(short)0);
}


void CHMIView::OnBnClickedClearPeaks2()
{
	CString fault;
	fault.Format(_T("Clear Peaks Motor 2: I=%4.2f amps FE=%d cts"),m_BtcData.PeakCurrentMotor2,m_BtcData.PeakCurrentMotor2);
	m_FaultHistory.AddString(fault);
	// m_FaultHistory.SaveStrings();

	CHMIApp* pApp = (CHMIApp*)AfxGetApp();
	CPmac* pmac = &pApp->m_pmac;
	pmac->DPRSet(DPR_OFFSET_PEAK_I2,(long)0);
	pmac->DPRSet(DPR_OFFSET_PEAK_FE2,(short)0);
}

void CHMIView::OnBnClickedClearPeaks3()
{
	CString fault;
	fault.Format(_T("Clear Peaks Motor 3: I=%4.2f amps FE=%d cts"),m_BtcData.PeakCurrentMotor3,m_BtcData.PeakCurrentMotor3);
	m_FaultHistory.AddString(fault);
	// m_FaultHistory.SaveStrings();

	CHMIApp* pApp = (CHMIApp*)AfxGetApp();
	CPmac* pmac = &pApp->m_pmac;
	pmac->DPRSet(DPR_OFFSET_PEAK_I3,(long)0);
	pmac->DPRSet(DPR_OFFSET_PEAK_FE3,(short)0);
}

void CHMIView::OnBnClickedClearPeaks4()
{
	CString fault;
	fault.Format(_T("Clear Peaks Motor 4: I=%4.2f amps FE=%d cts"),m_BtcData.PeakCurrentMotor4,m_BtcData.PeakCurrentMotor4);
	m_FaultHistory.AddString(fault);
	// m_FaultHistory.SaveStrings();

	CHMIApp* pApp = (CHMIApp*)AfxGetApp();
	CPmac* pmac = &pApp->m_pmac;
	pmac->DPRSet(DPR_OFFSET_PEAK_I4,(long)0);
	pmac->DPRSet(DPR_OFFSET_PEAK_FE4,(short)0);
}


void CHMIView::OnBnClickedClearPeaks5()
{
	CString fault;
	fault.Format(_T("Clear Peaks Motor 5: I=%4.2f amps FE=%d cts"),m_BtcData.PeakCurrentMotor5,m_BtcData.PeakCurrentMotor5);
	m_FaultHistory.AddString(fault);
	// m_FaultHistory.SaveStrings();

	CHMIApp* pApp = (CHMIApp*)AfxGetApp();
	CPmac* pmac = &pApp->m_pmac;
	pmac->DPRSet(DPR_OFFSET_PEAK_I5,(long)0);
	pmac->DPRSet(DPR_OFFSET_PEAK_FE5,(short)0);
}

void CHMIView::OnBnClickedClearPeaks6()
{
	CString fault;
	fault.Format(_T("Clear Peaks Motor 6: I=%4.2f amps FE=%d cts"),m_BtcData.PeakCurrentMotor6,m_BtcData.PeakCurrentMotor6);
	m_FaultHistory.AddString(fault);
	// m_FaultHistory.SaveStrings();

	CHMIApp* pApp = (CHMIApp*)AfxGetApp();
	CPmac* pmac = &pApp->m_pmac;
	pmac->DPRSet(DPR_OFFSET_PEAK_I6,(long)0);
	pmac->DPRSet(DPR_OFFSET_PEAK_FE6,(short)0);
}
void CHMIView::OnBnClickedClearPeaks7()
{
	CString fault;
	fault.Format(_T("Clear Peaks Motor 7: I=%4.2f amps FE=%d cts"),m_BtcData.PeakCurrentMotor7,m_BtcData.PeakCurrentMotor7);
	m_FaultHistory.AddString(fault);
	// m_FaultHistory.SaveStrings();

	CHMIApp* pApp = (CHMIApp*)AfxGetApp();
	CPmac* pmac = &pApp->m_pmac;
	pmac->DPRSet(DPR_OFFSET_PEAK_I7,(long)0);
	pmac->DPRSet(DPR_OFFSET_PEAK_FE7,(short)0);
}

void CHMIView::OnBnClickedClearPeaks8()
{
	CString fault;
	fault.Format(_T("Clear Peaks Motor 8: I=%4.2f amps FE=%d cts"),m_BtcData.PeakCurrentMotor8,m_BtcData.PeakCurrentMotor8);
	m_FaultHistory.AddString(fault);
	// m_FaultHistory.SaveStrings();

	CHMIApp* pApp = (CHMIApp*)AfxGetApp();
	CPmac* pmac = &pApp->m_pmac;
	pmac->DPRSet(DPR_OFFSET_PEAK_I8,(long)0);
	pmac->DPRSet(DPR_OFFSET_PEAK_FE8,(short)0);
}
void CHMIView::OnBnClickedClearPeaks9()
{
	CString fault;
	fault.Format(_T("Clear Peaks Motor 9: I=%4.2f amps FE=%d cts"),m_BtcData.PeakCurrentMotor9,m_BtcData.PeakCurrentMotor9);
	m_FaultHistory.AddString(fault);
	// m_FaultHistory.SaveStrings();

	CHMIApp* pApp = (CHMIApp*)AfxGetApp();
	CPmac* pmac = &pApp->m_pmac;
	pmac->DPRSet(DPR_OFFSET_PEAK_I9,(long)0);
	pmac->DPRSet(DPR_OFFSET_PEAK_FE9,(short)0);
	pmac->SetVariable(_T('P'),227,(long)1);

}
void CHMIView::OnBnClickedClearPeaks10()
{
	CString fault;
	fault.Format(_T("Clear Peaks Motor 10: I=%4.2f amps FE=%d cts"),m_BtcData.PeakCurrentMotor10,m_BtcData.PeakCurrentMotor10);
	m_FaultHistory.AddString(fault);
	// m_FaultHistory.SaveStrings();

	CHMIApp* pApp = (CHMIApp*)AfxGetApp();
	CPmac* pmac = &pApp->m_pmac;
	pmac->DPRSet(DPR_OFFSET_PEAK_I10,(long)0);
	pmac->DPRSet(DPR_OFFSET_PEAK_FE10,(short)0);
	pmac->SetVariable(_T('P'),228,(long)1);
}
void CHMIView::OnBnClickedClearPeaks11()
{
	CString fault;
	fault.Format(_T("Clear Peaks Motor 11: I=%4.2f amps FE=%d cts"),m_BtcData.PeakCurrentMotor11,m_BtcData.PeakCurrentMotor11);
	m_FaultHistory.AddString(fault);
	// m_FaultHistory.SaveStrings();

	CHMIApp* pApp = (CHMIApp*)AfxGetApp();
	CPmac* pmac = &pApp->m_pmac;
	pmac->DPRSet(DPR_OFFSET_PEAK_I11,(long)0);
	pmac->DPRSet(DPR_OFFSET_PEAK_FE11,(short)0);
	pmac->SetVariable(_T('P'),229,(long)1);
}
void CHMIView::OnBnClickedClearPeaks12()
{
	CString fault;
	fault.Format(_T("Clear Peaks Motor 12: I=%4.2f amps FE=%d cts"),m_BtcData.PeakCurrentMotor12,m_BtcData.PeakCurrentMotor12);
	m_FaultHistory.AddString(fault);
	// m_FaultHistory.SaveStrings();

	CHMIApp* pApp = (CHMIApp*)AfxGetApp();
	CPmac* pmac = &pApp->m_pmac;
	pmac->DPRSet(DPR_OFFSET_PEAK_I12,(long)0);
	pmac->DPRSet(DPR_OFFSET_PEAK_FE12,(short)0);
	pmac->SetVariable(_T('P'),230,(long)1);
}
void CHMIView::OnBnClickedClearPeaks13()
{
	CString fault;
	fault.Format(_T("Clear Peaks Motor 13: I=%4.2f amps FE=%d cts"),m_BtcData.PeakCurrentMotor13,m_BtcData.PeakCurrentMotor13);
	m_FaultHistory.AddString(fault);
	// m_FaultHistory.SaveStrings();

	CHMIApp* pApp = (CHMIApp*)AfxGetApp();
	CPmac* pmac = &pApp->m_pmac;
	pmac->DPRSet(DPR_OFFSET_PEAK_I13,(long)0);
	pmac->DPRSet(DPR_OFFSET_PEAK_FE13,(short)0);
	pmac->SetVariable(_T('P'),231,(long)1);
}
void CHMIView::OnBnClickedClearPeaks14()
{
	CString fault;
	fault.Format(_T("Clear Peaks Motor 14: I=%4.2f amps FE=%d cts"),m_BtcData.PeakCurrentMotor14,m_BtcData.PeakCurrentMotor14);
	m_FaultHistory.AddString(fault);
	// m_FaultHistory.SaveStrings();

	CHMIApp* pApp = (CHMIApp*)AfxGetApp();
	CPmac* pmac = &pApp->m_pmac;
	pmac->DPRSet(DPR_OFFSET_PEAK_I14,(long)0);
	pmac->DPRSet(DPR_OFFSET_PEAK_FE14,(short)0);
	pmac->SetVariable(_T('P'),232,(long)1);
}
void CHMIView::OnBnClickedClearPeaks15()
{
	CString fault;
	fault.Format(_T("Clear Peaks Motor 15: I=%4.2f amps FE=%d cts"),m_BtcData.PeakCurrentMotor15,m_BtcData.PeakCurrentMotor15);
	m_FaultHistory.AddString(fault);
	// m_FaultHistory.SaveStrings();

	CHMIApp* pApp = (CHMIApp*)AfxGetApp();
	CPmac* pmac = &pApp->m_pmac;
	pmac->DPRSet(DPR_OFFSET_PEAK_I15,(long)0);
	pmac->DPRSet(DPR_OFFSET_PEAK_FE15,(short)0);
	pmac->SetVariable(_T('P'),233,(long)1);
}
void CHMIView::OnBnClickedClearPeaks16()
{
	CString fault;
	fault.Format(_T("Clear Peaks Motor 16: I=%4.2f amps FE=%d cts"),m_BtcData.PeakCurrentMotor16,m_BtcData.PeakCurrentMotor16);
	m_FaultHistory.AddString(fault);
	// m_FaultHistory.SaveStrings();

	CHMIApp* pApp = (CHMIApp*)AfxGetApp();
	CPmac* pmac = &pApp->m_pmac;
	pmac->DPRSet(DPR_OFFSET_PEAK_I16,(long)0);
	pmac->DPRSet(DPR_OFFSET_PEAK_FE16,(short)0);
	pmac->SetVariable(_T('P'),234,(long)1);
	
}


void CHMIView::OnBnClickedHistory2()
{
	CFaultHistory dlg;
	//CHMIApp* pApp = (CHMIApp*)AfxGetApp();
	dlg.m_pHistory = &m_FaultHistory;
	dlg.DoModal();
}

void CHMIView::IoClickedGdiiostatusctrlOutputs(short IoClickedNum)
{
	CHMIApp* pApp = (CHMIApp*)AfxGetApp();
	CPmac* pmac = &pApp->m_pmac;
	long  BitValue;
	long  IoStatusWord = m_ctlOutputs.GetIoStatusWord();
	long  BitToTest = 1<<IoClickedNum;
	long  MvarNum = 33 + IoClickedNum;
	TRACE("Bit Value: %d MvarNum: %d \n",IoClickedNum,MvarNum);

	// EQU control
	if (MvarNum > 40)
	{
	//	AfxMessageBox(_T("EQU "));
		return;
	}

	// Test the bit and set or clear
	if (IoStatusWord & BitToTest)
	{
		BitValue = 0;    // Clear
	}
	else
	{
		BitValue = 1;    // Set	
	}

	// Force one
	if (m_btnOutputForce.GetLightOn())
		pmac->SetVariable(_T('M'),MvarNum,BitValue);

	//switch (IoClickedNum)
	//{
	//case 0:
	//	IoStatusWord = IoStatusWord & 0x0001;
	//	if (IoStatusWord){	
	//		pmac->SetVariable(_T('M'),11,(long)0);
	//	}
	//	else{
	//		pmac->SetVariable(_T('M'),11,(long)1);
	//	}
	//	break;
	//case 1:
	//	IoStatusWord = IoStatusWord & 0x0002;
	//	if (IoStatusWord){	
	//		pmac->SetVariable(_T('M'),12,(long)0);
	//	}
	//	else{
	//		pmac->SetVariable(_T('M'),12,(long)1);
	//	}
	//	break;
	//case 2:
	//	IoStatusWord = IoStatusWord & 0x0004;
	//	if (IoStatusWord){	
	//		pmac->SetVariable(_T('M'),13,(long)0);
	//	}
	//	else{
	//		pmac->SetVariable(_T('M'),13,(long)1);
	//	}
	//	break;
	//// Blower
	//case 3:
	//	IoStatusWord = IoStatusWord & 0x0008;
	//	if (IoStatusWord){	
	//		pmac->SetVariable(_T('M'),14,(long)0);
	//	}
	//	else{
	//		//AfxMessageBox(_T("Set M14=1"));
	//		pmac->SetVariable(_T('M'),14,(long)1);
	//	}
	//	break;
	//case 4:
	//	break;
	//case 5:
	//	break;
	//case 6:
	//	break;
	//case 7:
	//	break;
	//case 8:
	//	break;
	//case 9:
	//	break;

	//}
}

void CHMIView::IoClickedGdiiostatusctrlOutputs2(short IoClickedNum)
{
	CHMIApp* pApp = (CHMIApp*)AfxGetApp();
	CPmac* pmac = &pApp->m_pmac;
	long  BitValue;
	long  IoStatusWord = m_ctlOutputs2.GetIoStatusWord();
	long  BitToTest = 1<<IoClickedNum;
	long  MvarNum = 45 + IoClickedNum;
	if (MvarNum > 52)
	{
		return;
	}

	// Test the bit and set or clear
	if (IoStatusWord & BitToTest)
	{
		BitValue = 0;    // Clear
	}
	else
	{
		BitValue = 1;    // Set	
	}

	// Force one
	if (m_btnOutputForce2.GetLightOn())
		pmac->SetVariable(_T('M'),MvarNum,BitValue);
}

void CHMIView::IoClickedGdiiostatusctrlOutputs3(short IoClickedNum)
{
	CHMIApp* pApp = (CHMIApp*)AfxGetApp();
	long  IoStatusWord = m_ctlOutputs3.GetIoStatusWord();
	long  BitToTest = 1 << IoClickedNum;

	TRACE("IO Status %d \n",IoStatusWord);
	MIL_INT EdgeStatus;

	//// Test the bit and set or clear
	if (IoStatusWord & BitToTest)
	{
		EdgeStatus = M_OFF;
		TRACE("Clear bit \n");
	}
	else
	{
		EdgeStatus = M_ON;
		TRACE("Set bit \n");
	}

	// Force one
	if (m_btnOutputForce3.GetLightOn())
	{
		switch (IoClickedNum)
		{
		case 0:
			TRACE("Change bit 0...\n");
			MsysControl(M_DEFAULT_HOST,M_USER_BIT_STATE+M_USER_BIT0, EdgeStatus);
			break;
		case 1:
			MsysControl(M_DEFAULT_HOST,M_USER_BIT_STATE+M_USER_BIT1, EdgeStatus);
			break;
		case 2:
			MsysControl(M_DEFAULT_HOST,M_USER_BIT_STATE+M_USER_BIT2, EdgeStatus);
			break;
		case 3:
			MsysControl(M_DEFAULT_HOST,M_USER_BIT_STATE+M_USER_BIT3, EdgeStatus);
			break;
		case 4:
			MsysControl(M_DEFAULT_HOST,M_USER_BIT_STATE+M_USER_BIT4, EdgeStatus);
			break;
		case 5:
			MsysControl(M_DEFAULT_HOST,M_USER_BIT_STATE+M_USER_BIT5, EdgeStatus);
			break;
		case 6:
			MsysControl(M_DEFAULT_HOST,M_USER_BIT_STATE+M_USER_BIT6, EdgeStatus);
			break;
		case 7:
			MsysControl(M_DEFAULT_HOST,M_USER_BIT_STATE+M_USER_BIT7, EdgeStatus);
			break;
		}

	}

}

void CHMIView::ClickOutputForce()
{
	
	if (!m_btnOutputForce.GetLightOn())
	{
		// Password
		if (CheckPassword()==false)
			return;

		if (YesNoDlg(_T("Do you want to enable output force control?")))
		{
			m_btnOutputForce.SetLightOn(1);
			//CHMIApp* pApp = (CHMIApp*)AfxGetApp();
			//CPmac* pmac = &pApp->m_pmac;
			//pmac->SetVariable(_T('P'),138,(long)1);
		}	
	}
	else
	{
		m_btnOutputForce.SetLightOn(0);	
	}
}
void CHMIView::ClickOutputForce2()
{

	if (!m_btnOutputForce2.GetLightOn())
	{
		// Password
		if (CheckPassword()==false)
			return;

		if (YesNoDlg(_T("Do you want to enable output force control?")))
		{
			m_btnOutputForce2.SetLightOn(1);
			//CHMIApp* pApp = (CHMIApp*)AfxGetApp();
			//CPmac* pmac = &pApp->m_pmac;
			//pmac->SetVariable(_T('P'),138,(long)1);
		}	
	}
	else
	{
		m_btnOutputForce2.SetLightOn(0);	
	}
}

void CHMIView::ClickOutputForce3()
{

	if (!m_btnOutputForce3.GetLightOn())
	{
		// Password
		if (CheckPassword()==false)
			return;

		if (YesNoDlg(_T("Do you want to enable output force control?")))
		{
			m_btnOutputForce3.SetLightOn(1);
			//CHMIApp* pApp = (CHMIApp*)AfxGetApp();
			//CPmac* pmac = &pApp->m_pmac;
			//pmac->SetVariable(_T('P'),138,(long)1);
			MsysControl(M_DEFAULT_HOST, M_IO_SOURCE + M_AUX_IO0, M_USER_BIT0); /* Connector's Output 1. */
			MsysControl(M_DEFAULT_HOST, M_IO_SOURCE + M_AUX_IO1, M_USER_BIT1); /* Connector's Output 1. */
			MsysControl(M_DEFAULT_HOST, M_IO_SOURCE + M_AUX_IO2, M_USER_BIT2); /* Connector's Output 1. */
			MsysControl(M_DEFAULT_HOST, M_IO_SOURCE + M_AUX_IO3, M_USER_BIT3); /* Connector's Output 1. */
			MsysControl(M_DEFAULT_HOST, M_IO_SOURCE + M_AUX_IO4, M_USER_BIT4); /* Connector's Output 1. */
			MsysControl(M_DEFAULT_HOST, M_IO_SOURCE + M_AUX_IO5, M_USER_BIT5); /* Connector's Output 1. */
			MsysControl(M_DEFAULT_HOST, M_IO_SOURCE + M_AUX_IO6, M_USER_BIT6); /* Connector's Output 1. */
			MsysControl(M_DEFAULT_HOST, M_IO_SOURCE + M_AUX_IO7, M_USER_BIT7); /* Connector's Output 1. */
		}	
	}
	else
	{
		m_btnOutputForce3.SetLightOn(0);	
		MsysControl(M_DEFAULT_HOST, M_IO_SOURCE + M_AUX_IO0, M_IO_COMMAND_LIST1 + M_IO_COMMAND_BIT0); /* Connector's Output 1. */
		//MsysControl(M_DEFAULT_HOST, M_IO_SOURCE + M_AUX_IO1, M_IO_COMMAND_LIST1 + M_IO_COMMAND_BIT1); /* Connector's Output 2. */
		MsysControl(M_DEFAULT_HOST, M_IO_SOURCE + M_AUX_IO2, M_IO_COMMAND_LIST1 + M_IO_COMMAND_BIT2); /* Connector's Output 3. */
		//MsysControl(M_DEFAULT_HOST, M_IO_SOURCE + M_AUX_IO3, M_IO_COMMAND_LIST1 + M_IO_COMMAND_BIT3); /* Connector's Output 4. */
		//MsysControl(M_DEFAULT_HOST, M_IO_SOURCE + M_AUX_IO4, M_IO_COMMAND_LIST1 + M_IO_COMMAND_BIT4); /* Connector's Output 5. */
		//MsysControl(M_DEFAULT_HOST, M_IO_SOURCE + M_AUX_IO5, M_IO_COMMAND_LIST1 + M_IO_COMMAND_BIT5); /* Connector's Output 6. */
		//MsysControl(M_DEFAULT_HOST, M_IO_SOURCE + M_AUX_IO6, M_IO_COMMAND_LIST1 + M_IO_COMMAND_BIT6); /* Connector's Output 7. */
		//MsysControl(M_DEFAULT_HOST, M_IO_SOURCE + M_AUX_IO7, M_IO_COMMAND_LIST1 + M_IO_COMMAND_BIT7); /* Connector's Output 8. */
	}
}

//void CHMIView::OnBnClickedClearFaultLatch()
//{
//	m_csLatch.Lock();
//    ::ZeroMemory (&m_bMotorFaultLatch[0], sizeof (m_bMotorFaultLatch));
//    ::ZeroMemory (&m_bMotorWarnLatch[0], sizeof (m_bMotorWarnLatch));
//    TRACE("Clear the fault latches Size %d\n",sizeof(m_bMotorWarnLatch));
//	m_csLatch.Unlock();
//}


void CHMIView::OnBnClickedClearEndDetectPeaks()
{
	CHMIApp* pApp = (CHMIApp*)AfxGetApp();
	pApp->m_mil.MilHook2.PeriodMin = 0;
	pApp->m_mil.MilHook2.PeriodMax = 0;
	pApp->m_mil.MilHook2.MaxProcTime = 0;
}

void CHMIView::OnBnClickedRecordBelly()
{
	CButton* pBtn;
	CHMIApp* pApp = (CHMIApp*)AfxGetApp();
	pBtn = (CButton*)GetDlgItem(IDC_RECORD_BELLY);
	pBtn->EnableWindow(0);
	pBtn = (CButton*)GetDlgItem(IDC_PLAY_BELLY);
	pBtn->EnableWindow(0);
	pApp->m_mil.MilHook2.ImagesRecorded = 0;
	pApp->m_mil.MilHook2.RecordIndex = 0;
	pApp->m_mil.MilHook2.RecordEndCount = 0;
	pApp->m_mil.MilHook2.PlayImages = false;
	pBtn = (CButton*)GetDlgItem(IDC_STOP_PLAY);
	pBtn->EnableWindow(1);

}


void CHMIView::OnBnClickedPlayBelly()
{
	CHMIApp* pApp = (CHMIApp*)AfxGetApp();
	CButton* pBtn;
	pBtn = (CButton*)GetDlgItem(IDC_PLAY_BELLY);
	pBtn->EnableWindow(0);
	pBtn = (CButton*)GetDlgItem(IDC_STOP_PLAY);
	pBtn->EnableWindow(1);
	pApp->m_mil.MilHook2.PlayIndex = 0;
	pApp->m_mil.MilHook2.PlayImages = true;
}


void CHMIView::OnBnClickedStopPlay()
{
	CHMIApp* pApp = (CHMIApp*)AfxGetApp();
	CButton* pBtn;
	pBtn = (CButton*)GetDlgItem(IDC_STOP_PLAY);
	pBtn->EnableWindow(0);
	pBtn = (CButton*)GetDlgItem(IDC_PLAY_BELLY);
	pBtn->EnableWindow(1);
	pApp->m_mil.MilHook2.PlayIndex = 0;
	pApp->m_mil.MilHook2.PlayImages = false;
	pApp->m_mil.MilHook2.RecordIndex = MAX_RECORD;
	pBtn = (CButton*)GetDlgItem(IDC_RECORD_BELLY);
	pBtn->EnableWindow(0);

}


void CHMIView::MouseDownInfeedReverse(short Button, short Shift, long x, long y)
{
	CHMIApp* pApp = (CHMIApp*)AfxGetApp();
	CPmac* pmac = &pApp->m_pmac;
	if ( (m_BtcData.GlobalStatus == GS_ESTOP_DISABLED || m_BtcData.GlobalStatus == GS_BLADE_PARKED) && !m_bFeedJogReverse)
	{
		m_ctlJogFeedRev.SetLight(1);
		pmac->SendCommand(_T("#12j:-200000"));
		m_bFeedJogReverse = true;
	}
}


void CHMIView::MouseUpInfeedReverse(short Button, short Shift, long x, long y)
{
	CHMIApp* pApp = (CHMIApp*)AfxGetApp();
	CPmac* pmac = &pApp->m_pmac;
	if (m_bFeedJogReverse)
	{
		m_ctlJogFeedRev.SetLight(0);
		pmac->SendCommand(_T("#12j/"));
		m_bFeedJogReverse = false;
	}
}


void CHMIView::MouseDownGdiJogFast(short Button, short Shift, long x, long y)
{
	CHMIApp* pApp = (CHMIApp*)AfxGetApp();
	CPmac* pmac = &pApp->m_pmac;
	pmac->SetVariable(_T('P'),713,(long)1);
	m_ctlTTJogFast.SetLightOn(1);
	m_ctlTTJogSlow.SetLightOn(0);
}

void CHMIView::BladeBrake(short Button, short Shift, long x, long y)
{
	CHMIApp* pApp = (CHMIApp*)AfxGetApp();
	CPmac* pmac = &pApp->m_pmac;	
	if (m_BtcData.GlobalStatus == GS_ESTOP || m_BtcData.GlobalStatus == GS_DISABLED)
	{
		if (m_ctlBladeBrake.GetLightOn())
		{
			pmac->SetVariable(_T('M'),50,(long)0);	
		}
		else
		{
			pmac->SetVariable(_T('M'),50,(long)1);		
		}	
	}
}

void CHMIView::MouseUpGdiJogFast(short Button, short Shift, long x, long y)
{
	//CHMIApp* pApp = (CHMIApp*)AfxGetApp();
	//CPmac* pmac = &pApp->m_pmac;
	//pmac->SetVariable(_T('P'),714,(long)0);
	//m_ctlTTJogFast.SetLightOn(0);
}


void CHMIView::MouseDownGdiJogSlow(short Button, short Shift, long x, long y)
{
	CHMIApp* pApp = (CHMIApp*)AfxGetApp();
	CPmac* pmac = &pApp->m_pmac;
	pmac->SetVariable(_T('P'),713,(long)0);
	pmac->SetVariable(_T('P'),714,(long)1);
	m_ctlTTJogSlow.SetLightOn(1);
	m_ctlTTJogFast.SetLightOn(0);
}


void CHMIView::MouseUpGdiJogSlow(short Button, short Shift, long x, long y)
{
	//CHMIApp* pApp = (CHMIApp*)AfxGetApp();
	//CPmac* pmac = &pApp->m_pmac;
	//pmac->SetVariable(_T('P'),715,(long)0);
	//m_ctlTTJogSlow.SetLightOn(0);
}

//void CHMIView::OnBnClickedReadPvars()
//{
	//CString str;
	//CWnd* pWnd;
	//double p292,p530;
	//double p406,p407;
	//CHMIApp* pApp = (CHMIApp*)AfxGetApp();
	//CPmac* pmac = &pApp->m_pmac;
	////pmac->GetVariable(_T('P'),715,(long)0);
	////m_ctlTTJogSlow.SetLightOn(0);
	//pmac->GetVariable(_T('P'),292,&p292);
	////pmac->GetVariable(_T('P'),293,&p293);
	//pmac->GetVariable(_T('P'),530,&p530);
	//pmac->GetVariable(_T('P'),406,&p406);
	//pmac->GetVariable(_T('P'),407,&p407);

	//// Prox
	//pWnd = GetDlgItem(IDC_P292);
	//str.Format (_T ("%4.2f"),p292);
	//pWnd->SetWindowText(str);

	//pWnd = GetDlgItem(IDC_P530);
	//str.Format (_T ("%4.2f"),p530);
	//pWnd->SetWindowText(str);

	//pWnd = GetDlgItem(IDC_P406);
	//str.Format (_T ("%4.2f"),p406);
	//pWnd->SetWindowText(str);

	//pWnd = GetDlgItem(IDC_P407);
	//str.Format (_T ("%4.2f"),p407);
	//pWnd->SetWindowText(str);
//}

void CHMIView::ClickBtcPanic()
{
	//m_ctlPanic.SetBitMapSelect(5);
}


void CHMIView::OnBnClickedCheckPhase()
{
	long pvar;
	CHMIApp* pApp = (CHMIApp*)AfxGetApp();
	CPmac* pmac = &pApp->m_pmac;
	pmac->GetVariable(_T('P'),201,&pvar);
	if (pvar==0) AfxMessageBox(_T("Motor 1 Not Phased"));
	pmac->GetVariable(_T('P'),202,&pvar);
	if (pvar==0) AfxMessageBox(_T("Motor 2 Not Phased"));
	pmac->GetVariable(_T('P'),203,&pvar);
	if (pvar==0) AfxMessageBox(_T("Motor 3 Not Phased"));
	pmac->GetVariable(_T('P'),204,&pvar);
	if (pvar==0) AfxMessageBox(_T("Motor 4 Not Phased"));
	pmac->GetVariable(_T('P'),205,&pvar);
	if (pvar==0) AfxMessageBox(_T("Motor 5 Not Phased"));
	pmac->GetVariable(_T('P'),206,&pvar);
	if (pvar==0) AfxMessageBox(_T("Motor 6 Not Phased"));
	pmac->GetVariable(_T('P'),207,&pvar);
	if (pvar==0) AfxMessageBox(_T("Motor 7 Not Phased"));
	pmac->GetVariable(_T('P'),208,&pvar);
	if (pvar==0) AfxMessageBox(_T("Motor 8 Not Phased"));
	pmac->GetVariable(_T('P'),219,&pvar);
	if (pvar==0) AfxMessageBox(_T("Motor 9 Not Phased"));
	pmac->GetVariable(_T('P'),220,&pvar);
	if (pvar==0) AfxMessageBox(_T("Motor 10 Not Phased"));
	pmac->GetVariable(_T('P'),221,&pvar);
	if (pvar==0) AfxMessageBox(_T("Motor 11 Not Phased"));
	pmac->GetVariable(_T('P'),222,&pvar);
	if (pvar==0) AfxMessageBox(_T("Motor 12 Not Phased"));
	pmac->GetVariable(_T('P'),223,&pvar);
	if (pvar==0) AfxMessageBox(_T("Motor 13 Not Phased"));
	pmac->GetVariable(_T('P'),224,&pvar);
	if (pvar==0) AfxMessageBox(_T("Motor 14 Not Phased"));
	pmac->GetVariable(_T('P'),225,&pvar);
	if (pvar==0) AfxMessageBox(_T("Motor 15 Not Phased"));
	pmac->GetVariable(_T('P'),226,&pvar);
	if (pvar==0) AfxMessageBox(_T("Motor 16 Not Phased"));
}


void CHMIView::OnBnClickedUpdatePvars()
{
	CHMIApp* pApp = (CHMIApp*)AfxGetApp();
	CPmac* pmac = &pApp->m_pmac;
	CWnd* pWnd;
	CString str;
	double pvar;
	long lpvar;

	// DRP ROLL SIZE
	str.Format(_T("%4.2f"),m_BtcData.PaperRollSize);
	pWnd = GetDlgItem(IDC_DPR_ROLL_SIZE);
	pWnd->SetWindowText(str);

	// Min ROLL SIZE
	pWnd = GetDlgItem(IDC_MIN_ROLL_SIZE);
	pmac->GetVariable(_T('P'),323,&pvar);
	str.Format(_T("%4.2f"),pvar);
	pWnd->SetWindowText(str);

	// Max ROLL SIZE
	pWnd = GetDlgItem(IDC_MAX_ROLL_SIZE);
	pmac->GetVariable(_T('P'),324,&pvar);
	str.Format(_T("%4.2f"),pvar);
	pWnd->SetWindowText(str);

	// Drum Revs
	pWnd = GetDlgItem(IDC_DRUM_REVS);
	pmac->GetVariable(_T('P'),420,&pvar);
	str.Format(_T("%4.2f"),pvar);
	pWnd->SetWindowText(str);
	
	// Paper gap
	pWnd = GetDlgItem(IDC_P183);
	pmac->GetVariable(_T('P'),183,&pvar);
	str.Format(_T("%4.2f"),pvar);
	pWnd->SetWindowText(str);

	// Paper length
	pWnd = GetDlgItem(IDC_P357);
	pmac->GetVariable(_T('P'),357,&pvar);
	str.Format(_T("%4.2f"),pvar);
	pWnd->SetWindowText(str);

	// Arm prox state
	pWnd = GetDlgItem(IDC_P316);
	pmac->GetVariable(_T('P'),316,&pvar);
	str.Format(_T("%4.2f"),pvar);
	pWnd->SetWindowText(str);

	// Eye state
	pWnd = GetDlgItem(IDC_P319);
	pmac->GetVariable(_T('P'),319,&pvar);
	str.Format(_T("%4.2f"),pvar);
	pWnd->SetWindowText(str);

	// No Sheet Count
	pWnd = GetDlgItem(IDC_P334);
	pmac->GetVariable(_T('P'),334,&lpvar);
	str.Format(_T("%d"),lpvar);
	pWnd->SetWindowText(str);

	// Correction distance
	pWnd = GetDlgItem(IDC_P400);
	pmac->GetVariable(_T('P'),416,&pvar);
	str.Format(_T("%4.2f"),pvar);
	pWnd->SetWindowText(str);

	// S2 revs
	pWnd = GetDlgItem(IDC_P404);
	pmac->GetVariable(_T('P'),417,&pvar);
	str.Format(_T("%4.2f"),pvar);
	pWnd->SetWindowText(str);

	// S3 revs
	pWnd = GetDlgItem(IDC_P405);
	pmac->GetVariable(_T('P'),418,&pvar);
	//pmac->GetVariable(_T('P'),389,&pvar);
	str.Format(_T("%4.2f"),pvar);
	pWnd->SetWindowText(str);

	// S4 revs
	pWnd = GetDlgItem(IDC_P419);
	//pmac->GetVariable(_T('P'),419,&pvar);
	pmac->GetVariable(_T('P'),390,&pvar);
	str.Format(_T("%4.2f"),pvar);
	pWnd->SetWindowText(str);

}


void CHMIView::OnBnClickedAxisFaultCodes()
{
	//ScrollToPage(4);
	CAxisFaultsDlg dlg;
	dlg.DoModal();
}

void CHMIView::OnBnClickedDriveFaultCodes()
{
	//ScrollToPage(5);
	CDriveFaults dlg;
	dlg.DoModal();
}


void CHMIView::OnBnClickedMotorTestUtil()
{
	TCHAR szName[256];
	STARTUPINFO si;
	::ZeroMemory (&si, sizeof (STARTUPINFO));
	si.cb = sizeof (STARTUPINFO);
	//PROCESS_INFORMATION pi;

	if (m_BtcData.GlobalStatus == GS_RUNNING)
	{
	   MessageBox(_T("The machine must be in a E-Stop state to start this utility."),_T("Push E-Stop"));
	   return;
	}

	// Motor Utility
	if (m_piMotorUtil.hProcess != NULL)
	{
		TRACE("Check PMAC Motor utility... \n");
		if (::WaitForSingleObject (m_piMotorUtil.hProcess, 0)
			== WAIT_OBJECT_0)
		{
			::CloseHandle (m_piMotorUtil.hProcess);
			m_piMotorUtil.hProcess  = NULL;
			TRACE("PMAC utility closed \n");
		}
		else
		{
			return;
		}
	}

	// Start process
	CUIHelperThread* pThread = (CUIHelperThread*)AfxBeginThread (RUNTIME_CLASS (CUIHelperThread));
	pThread->SetDelayTime(6000);
	::ZeroMemory (&si, sizeof (STARTUPINFO));
	si.cb = sizeof (STARTUPINFO);
	::lstrcpy(szName,_T ("C:\\Program Files\\Hormel Foods LLC\\PmacMotorUtil.exe"));
	if (::CreateProcess (NULL,szName ,
		NULL,NULL,FALSE, NORMAL_PRIORITY_CLASS,
		NULL, NULL, &si, &m_piMotorUtil)) {
		::CloseHandle (m_piMotorUtil.hThread);
		//::WaitForSingleObject (pi.hProcess, INFINITE);
		//::WaitForInputIdle (pi.hProcess, INFINITE);
		//::CloseHandle (pi.hProcess);
	}
	Sleep(6000);
	pThread->Close();

	//MessageBox(_T("Starting utility... Press Ok to continue."),_T("Push E-Stop"));

}

void CHMIView::OnBnClickedCheckMasterSettings()
{
    CString str;
	CString strVars[100];
	strVars[0] = _T("DeadSwings p1000");
	strVars[1] = _T("Not used P1001");
	strVars[2] = _T("RejectIndexStartPos p1002");
	strVars[3] = _T("WashVelocity p1003");
	strVars[4] = _T("DrumIndexStartPos p1004");    
	strVars[5] = _T("DrumOffset p1005");
	strVars[6] = _T("PaperOffset p1006");
	strVars[7] = _T("BladeSpeed p1007");
	strVars[8] = _T("MinRollAdc p1008");        
	strVars[9] = _T("MaxRollAdc p1009");
	strVars[10] = _T("EYE1_ROLL_CIRC p1010");          
	strVars[11] = _T("EYE2_ROLL_CIRC p1011");
	strVars[12] = _T("EYE3_ROLL_CIRC p1012"); 
	strVars[13] = _T("ParkVelocity p1013");
	strVars[14] = _T("KnifeHomeOffset p1014");
	strVars[15] = _T("AlignPosSoftLimit p1015");
	strVars[16] = _T("AlignNegSoftLimit p1016");
	strVars[17] = _T("Not used P1017");
	strVars[18] = _T("AlignDelayOffset p1018");
	strVars[19] = _T("PaperLengthRequest p1019  ");
	strVars[20] = _T("EndDetectEnable p1020");
	strVars[22] = _T("ParkAccel p1021");
	strVars[23] = _T("BelevatorHomeOffset p1023 ");
	strVars[24] = _T("SliceCountRequest p1024 ");
	strVars[25] = _T("BackLashPercent p1025");
	strVars[26] = _T("TrimSpeedBoostPercent p1026");
	strVars[27] = _T("SlicerStopAccel p1027");
	strVars[28] = _T("TimingTestPosition p1028");
	strVars[29] = _T("LowProxMeasureDist p1029");
	strVars[30] = _T("AlignStartPos p1030");
	strVars[31] = _T("AlignHomeOffset p1031");
	strVars[32] = _T("SlicerHomeOffset p1032");
	strVars[33] = _T("SlicerRunAccel p1033");
	strVars[34] = _T("AlignVelocity p1034 ");
	strVars[35] = _T("TamperOnTime p1035");
	strVars[36] = _T("TamperOffTime p1036");
	strVars[37] = _T("BoostTriggerEn p1037");
	strVars[38] = _T("AlignAccelTime p1038 ");
	strVars[39] = _T("KnifeVel1 p1039");
	strVars[40] = _T("KnifeVel2 p1040");
	strVars[41] = _T("KnifeVel3 p1041");
	strVars[42] = _T("MaxBladeSpeed p1042");
	strVars[43] = _T("BoostTrigger p1043");
	strVars[44] = _T("BoostDistance p1044");
	strVars[45] = _T("SliceThickness p1045");
	strVars[46] = _T("Not used p1046");
	strVars[47] = _T("TrimThickness p1047  ");
	strVars[48] = _T("Not used p1048");
	strVars[49] = _T("Not used p1049");
	strVars[50] = _T("DischargeDist p1050");
	strVars[51] = _T("InclineDist p1051");
	strVars[52] = _T("InfeedDistDistOffset p1052");
	strVars[53] = _T("Not used p1053");
	strVars[54] = _T("ExitBeltPaperGap p1054");
	strVars[55] = _T("FlipperDelay p1055");
	strVars[56] = _T("Not used p1056");
	strVars[57] = _T("Mtr2AutoInc p1057");
	strVars[58] = _T("Mtr4AutoInc p1058");
	strVars[59] = _T("EyeStateStop p1059");
	strVars[60] = _T("GateUpPosition p1060");
	strVars[61] = _T("GateDownPosition p1061");
	strVars[62] = _T("FlipperMoveTime p1062");
	strVars[63] = _T("PaperLenDelayAdj p1063");
	strVars[64] = _T("CountDelayAdj    p1064");
	strVars[65] = _T("FlipperMonitorDelay p1065");
	strVars[66] = _T("Not used p1066");
	strVars[67] = _T("Not used p1067");
	strVars[68] = _T("TTBotDelay p1068");
	strVars[69] = _T("Not used  p1069");
	strVars[70] = _T("WaitModePosBias p1070");
	strVars[71] = _T("ContinousModePosBias p1071");
	strVars[72] = _T("RejectDistChange p1072");
	strVars[73] = _T("Not used P1073");
	strVars[74] = _T("ModifyTTBuffer p1074");
	strVars[75] = _T("BellyStopOpenDelay p1075");
	strVars[76] = _T("MinGapDetectCount p1076");
	strVars[77] = _T("BellyStopCloseDist p1077");
	strVars[78] = _T("BelevatorPushDwell p1078");
	strVars[79] = _T("BelevatorEyeCheck p1079");
	strVars[80] = _T("BelevatorLoadTimeout p1080");
	strVars[81] = _T("BelevatorMoveTime p1081");
	strVars[82] = _T("EndTrimCount p1082");
	strVars[83] = _T("PartialDraftReject p1083");
	strVars[84] = _T("Not used p1084");
	strVars[85] = _T("BotommAccelTime p1085");
	strVars[86] = _T("BotommMaxVel p1086");
	strVars[87] = _T("Not used p1087");
	strVars[88] = _T("Not used p1088");
	strVars[89] = _T("LowProxAccel p1089");
	strVars[90] = _T("MidProxAccel p1090");
	strVars[91] = _T("UpperProxAccel p1091");
	strVars[92] = _T("Not used p1092");
	strVars[93] = _T("TTTopBeltAxisScale p1093");
	strVars[94] = _T("RollSizeLockDist p1094");
	strVars[95] = _T("BellyLoadDistance p1095");
	strVars[96] = _T("RejectDistance p1096");
	strVars[97] = _T("RejectDistanceNeg p1097");
	strVars[98] = _T("EnableLowerProx p1098");
	strVars[99] = _T("TTBottomBeltAxisScale p1099");

	CHMIApp* pApp = (CHMIApp*)AfxGetApp();
	if (!LoadMasterAppSettingFile (&pApp->m_MasterSettings))
	{
		AfxMessageBox(_T("MasterSetting file created"));
	}

	// Check servo parameters
	for (int i=0; i<100; i++)
	{
		if (pApp->m_MasterSettings.MotionSettings1.dbPvars[i] != 
			pApp->m_Settings.MotionSettings1.dbPvars[i])
		{
			str.Format(_T(" Does not match master file! \nMaster=%4.2f  Current=%4.2f"),pApp->m_MasterSettings.MotionSettings1.dbPvars[i],pApp->m_Settings.MotionSettings1.dbPvars[i]);
			strVars[i] += str;
			AfxMessageBox(strVars[i]);		
		}
	}

	// Check vision parameters
	if (pApp->m_MasterSettings.VisSettings1.Exposure_uS != pApp->m_Settings.VisSettings1.Exposure_uS)
	{
		str.Format(_T("Master Exposure_uS=%4.2f \nCurrent Exposure_uS=%4.2f"),(double)pApp->m_MasterSettings.VisSettings1.Exposure_uS,(double)pApp->m_Settings.VisSettings1.Exposure_uS);
		AfxMessageBox(str);		
	}
	if ((double)pApp->m_MasterSettings.VisSettings1.MinBaconHeight != (double)pApp->m_Settings.VisSettings1.MinBaconHeight)
	{
		str.Format(_T("Master MinBaconHeight=%4.2f \nCurrent MinBaconHeight=%4.2f"),(double)pApp->m_MasterSettings.VisSettings1.MinBaconHeight,(double)pApp->m_Settings.VisSettings1.MinBaconHeight);
		AfxMessageBox(str);		
	}
	if ((double)pApp->m_MasterSettings.VisSettings1.MinBaconRejectHeight != (double)pApp->m_Settings.VisSettings1.MinBaconRejectHeight)
	{
		str.Format(_T("Master MinBaconRejectHeight=%4.2f \nCurrent MinBaconRejectHeight=%4.2f"),(double)pApp->m_MasterSettings.VisSettings1.MinBaconRejectHeight,(double)pApp->m_Settings.VisSettings1.MinBaconRejectHeight);
		AfxMessageBox(str);		
	}
	if ((double)pApp->m_MasterSettings.VisSettings1.MinBaconRejectSize != (double)pApp->m_Settings.VisSettings1.MinBaconRejectSize)
	{
		str.Format(_T("Master MinBaconRejectSize=%4.2f \nCurrent MinBaconRejectSize=%4.2f"),(double)pApp->m_MasterSettings.VisSettings1.MinBaconRejectSize,(double)pApp->m_Settings.VisSettings1.MinBaconRejectSize);
		AfxMessageBox(str);		
	}
	if ((double)pApp->m_MasterSettings.VisSettings1.MinBaconRejectWidth != (double)pApp->m_Settings.VisSettings1.MinBaconRejectWidth)
	{
		str.Format(_T("Master MinBaconRejectWidth=%4.2f \nCurrent MinBaconRejectWidth=%4.2f"),(double)pApp->m_MasterSettings.VisSettings1.MinBaconRejectWidth,(double)pApp->m_Settings.VisSettings1.MinBaconRejectWidth);
		AfxMessageBox(str);		
	}

	if ((double)pApp->m_MasterSettings.VisSettings1.MinBaconSize != (double)pApp->m_Settings.VisSettings1.MinBaconSize)
	{
		str.Format(_T("Master MinBaconSize=%4.2f \nCurrent MinBaconSize=%4.2f"),(double)pApp->m_MasterSettings.VisSettings1.MinBaconSize,(double)pApp->m_Settings.VisSettings1.MinBaconSize);
		AfxMessageBox(str);		
	}
	if ((double)pApp->m_MasterSettings.VisSettings1.MinBaconWidth != (double)pApp->m_Settings.VisSettings1.MinBaconWidth)
	{
		str.Format(_T("Master MinBaconWidth=%4.2f \nCurrent MinBaconWidth=%4.2f"),(double)pApp->m_MasterSettings.VisSettings1.MinBaconWidth,(double)pApp->m_Settings.VisSettings1.MinBaconWidth);
		AfxMessageBox(str);		
	}
	if ((double)pApp->m_MasterSettings.VisSettings1.MinBlobRadius != (double)pApp->m_Settings.VisSettings1.MinBlobRadius)
	{
		str.Format(_T("Master MinBlobRadius=%4.2f \nCurrent MinBlobRadius=%4.2f"),(double)pApp->m_MasterSettings.VisSettings1.MinBlobRadius,
			(double)pApp->m_Settings.VisSettings1.MinBlobRadius);
		AfxMessageBox(str);		
	}
	if ((double)pApp->m_MasterSettings.VisSettings1.RejectDelay != (double)pApp->m_Settings.VisSettings1.RejectDelay)
	{
		str.Format(_T("Master RejectDelay=%4.2f \nCurrent RejectDelay=%4.2f"),
			(double)pApp->m_MasterSettings.VisSettings1.RejectDelay,
			(double)pApp->m_Settings.VisSettings1.RejectDelay);
		AfxMessageBox(str);		
	}
	if ((double)pApp->m_MasterSettings.VisSettings1.RejectDuration != 
		(double)pApp->m_Settings.VisSettings1.RejectDuration)
	{
		str.Format(_T("Master RejectDuration=%4.2f \nCurrent RejectDuration=%4.2f"),
			(double)pApp->m_MasterSettings.VisSettings1.RejectDuration,
			(double)pApp->m_Settings.VisSettings1.RejectDuration);
		AfxMessageBox(str);		
	}

	if ((double)pApp->m_MasterSettings.VisSettings1.RejectSuppressionCount != 
		(double)pApp->m_Settings.VisSettings1.RejectSuppressionCount)
	{
		str.Format(_T("Master RejectSuppressionCount=%4.2f \nCurrent RejectSuppressionCount=%4.2f"),
			(double)pApp->m_MasterSettings.VisSettings1.RejectSuppressionCount,
			(double)pApp->m_Settings.VisSettings1.RejectSuppressionCount);
		AfxMessageBox(str);		
	}
	if ((double)pApp->m_MasterSettings.VisSettings1.SystemEnable != 
		(double)pApp->m_Settings.VisSettings1.SystemEnable)
	{
		str.Format(_T("Master SystemEnable=%4.2f \nCurrent SystemEnable=%4.2f"),
			(double)pApp->m_MasterSettings.VisSettings1.SystemEnable,
			(double)pApp->m_Settings.VisSettings1.SystemEnable);
		AfxMessageBox(str);		
	}
	if ((double)pApp->m_MasterSettings.VisSettings1.Threshold != 
		(double)pApp->m_Settings.VisSettings1.Threshold)
	{
		str.Format(_T("Master Threshold=%4.2f \nCurrent Threshold=%4.2f"),
			(double)pApp->m_MasterSettings.VisSettings1.Threshold,
			(double)pApp->m_Settings.VisSettings1.Threshold);
		AfxMessageBox(str);		
	}
	// VisionSettings2
	if ((double)pApp->m_MasterSettings.VisSettings2.EndDetectEnable != 
		(double)pApp->m_Settings.VisSettings2.EndDetectEnable)
	{
		str.Format(_T("Master EndDetectEnable=%4.2f \nCurrent EndDetectEnable=%4.2f"),
			(double)pApp->m_MasterSettings.VisSettings2.EndDetectEnable,
			(double)pApp->m_Settings.VisSettings2.EndDetectEnable);
		AfxMessageBox(str);		
	}
	if ((double)pApp->m_MasterSettings.VisSettings2.EndDetectLockCount != 
		(double)pApp->m_Settings.VisSettings2.EndDetectLockCount)
	{
		str.Format(_T("Master EndDetectLockCount=%4.2f \nCurrent EndDetectLockCount=%4.2f"),
			(double)pApp->m_MasterSettings.VisSettings2.EndDetectLockCount,
			(double)pApp->m_Settings.VisSettings2.EndDetectLockCount);
		AfxMessageBox(str);		
	}
	if ((double)pApp->m_MasterSettings.VisSettings2.Exposure_uS != 
		(double)pApp->m_Settings.VisSettings2.Exposure_uS)
	{
		str.Format(_T("V2 Master Exposure_uS=%4.2f \nCurrent Exposure_uS=%4.2f"),
			(double)pApp->m_MasterSettings.VisSettings2.Exposure_uS,
			(double)pApp->m_Settings.VisSettings2.Exposure_uS);
		AfxMessageBox(str);		
	}
	if ((double)pApp->m_MasterSettings.VisSettings2.GapDetectCount != 
		(double)pApp->m_Settings.VisSettings2.GapDetectCount)
	{
		str.Format(_T("Master GapDetectCount=%4.2f \nCurrent GapDetectCount=%4.2f"),
			(double)pApp->m_MasterSettings.VisSettings2.GapDetectCount,
			(double)pApp->m_Settings.VisSettings2.GapDetectCount);
		AfxMessageBox(str);		
	}
	if ((double)pApp->m_MasterSettings.VisSettings2.GapDetectLatchCount != 
		(double)pApp->m_Settings.VisSettings2.GapDetectLatchCount)
	{
		str.Format(_T("Master GapDetectLatchCount=%4.2f \nCurrent GapDetectLatchCount=%4.2f"),
			(double)pApp->m_MasterSettings.VisSettings2.GapDetectLatchCount,
			(double)pApp->m_Settings.VisSettings2.GapDetectLatchCount);
		AfxMessageBox(str);		
	}
	if ((double)pApp->m_MasterSettings.VisSettings2.LaserWidthDelta != 
		(double)pApp->m_Settings.VisSettings2.LaserWidthDelta)
	{
		str.Format(_T("Master LaserWidthDelta=%4.2f \nCurrent LaserWidthDelta=%4.2f"),
			(double)pApp->m_MasterSettings.VisSettings2.LaserWidthDelta,
			(double)pApp->m_Settings.VisSettings2.LaserWidthDelta);
		AfxMessageBox(str);		
	}
	if ((double)pApp->m_MasterSettings.VisSettings2.MaxBaconBlobs != 
		(double)pApp->m_Settings.VisSettings2.MaxBaconBlobs)
	{
		str.Format(_T("Master MaxBaconBlobs=%4.2f \nCurrent MaxBaconBlobs=%4.2f"),
			(double)pApp->m_MasterSettings.VisSettings2.MaxBaconBlobs,
			(double)pApp->m_Settings.VisSettings2.MaxBaconBlobs);
		AfxMessageBox(str);		
	}
	if ((double)pApp->m_MasterSettings.VisSettings2.MaxGapFillX != 
		(double)pApp->m_Settings.VisSettings2.MaxGapFillX)
	{
		str.Format(_T("Master MaxGapFillX=%4.2f \nCurrent MaxGapFillX=%4.2f"),
			(double)pApp->m_MasterSettings.VisSettings2.MaxGapFillX,
			(double)pApp->m_Settings.VisSettings2.MaxGapFillX);
		AfxMessageBox(str);		
	}

	if ((double)pApp->m_MasterSettings.VisSettings2.MaxGapFillY != 
		(double)pApp->m_Settings.VisSettings2.MaxGapFillY)
	{
		str.Format(_T("Master MaxGapFillY=%4.2f \nCurrent MaxGapFillY=%4.2f"),
			(double)pApp->m_MasterSettings.VisSettings2.MaxGapFillY,
			(double)pApp->m_Settings.VisSettings2.MaxGapFillY);
		AfxMessageBox(str);		
	}
	if ((double)pApp->m_MasterSettings.VisSettings2.MinBaconSize != 
		(double)pApp->m_Settings.VisSettings2.MinBaconSize)
	{
		str.Format(_T("Master MinBaconSize=%4.2f \nCurrent MinBaconSize=%4.2f"),
			(double)pApp->m_MasterSettings.VisSettings2.MinBaconSize,
			(double)pApp->m_Settings.VisSettings2.MinBaconSize);
		AfxMessageBox(str);		
	}
	if ((double)pApp->m_MasterSettings.VisSettings2.MinLaserIntensity != 
		(double)pApp->m_Settings.VisSettings2.MinLaserIntensity)
	{
		str.Format(_T("Master MinLaserIntensity=%4.2f \nCurrent MinLaserIntensity=%4.2f"),
			(double)pApp->m_MasterSettings.VisSettings2.MinLaserIntensity,
			(double)pApp->m_Settings.VisSettings2.MinLaserIntensity);
		AfxMessageBox(str);		
	}
	if ((double)pApp->m_MasterSettings.VisSettings2.MinPosY != 
		(double)pApp->m_Settings.VisSettings2.MinPosY)
	{
		str.Format(_T("Master MinPosY=%4.2f \nCurrent MinPosY=%4.2f"),
			(double)pApp->m_MasterSettings.VisSettings2.MinPosY,
			(double)pApp->m_Settings.VisSettings2.MinPosY);
		AfxMessageBox(str);		
	}
	if ((double)pApp->m_MasterSettings.VisSettings2.NominalLaserWidth != 
		(double)pApp->m_Settings.VisSettings2.NominalLaserWidth)
	{
		str.Format(_T("Master NominalLaserWidth=%4.2f \nCurrent NominalLaserWidth=%4.2f"),
			(double)pApp->m_MasterSettings.VisSettings2.NominalLaserWidth,
			(double)pApp->m_Settings.VisSettings2.NominalLaserWidth);
		AfxMessageBox(str);		
	}

}

//======================================================================================================//
// Function Name: ServerThreadFunc (LPVOID pParam)                                                     //
//                                                                                                      //
//======================================================================================================//
UINT CHMIView::OpenPmacThreadFunc (LPVOID pParam)                                                                      
{            
	OPENPMACDATA* pRunData = (OPENPMACDATA*) pParam;
	TRACE("OpenPmacThreadFunc................................................OpenPmacThreadFunc \n");
	pRunData->Pmac.Init(pRunData->nDevice);
	TRACE("OpenPmacThreadFunc................................................OpenPmacThreadFunc \n");
	return 0;                                                                                                       
}
