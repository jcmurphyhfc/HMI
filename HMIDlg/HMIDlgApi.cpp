// File: Exports.cpp
// Copyright (c) Hormel Foods LLC.  All rights reserved.
//

#include "stdafx.h"
#include "HMIDlg.h"

//#include <AtlImage.h>
#include "HMIDlgApi.h"
#include "YesNo.h"
#include "Save.h"
#include "DlgOk.h"
#include "DlgHMIOpt.h"
#include "KeyPadDlg.h"
#include "Settings.h"
#include "DlgWait.h"
#include "Splash.h"
#include "PmacSettings.h"
#include "UserSettings.h"

//
// YesNoDlg(LPCTSTR lpMsg)
//
BOOL WINAPI YesNoDlg(LPCTSTR lpMsg)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CYesNo dlg;	
	if (lpMsg != NULL)
		dlg.m_strMsg = lpMsg;
	BOOL bStat = FALSE;
	if (dlg.DoModal() == IDOK) {
		bStat = TRUE;
	}
	return(bStat);
}

//
// CreateIsLCDWnd(CWnd* pParentWnd,const CRect& rcBounds)
//
CIsiLcdDisplay* WINAPI CreateIsLCDWnd(CWnd* pParentWnd,const CRect& rect,int NumDig)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	////========================================================================================//
	//// Led display
	////========================================================================================//
	////m_ledTime.LoadMatrix( IDB_MATRIX5x7 );
	//m_ledTime.SetSegmentStyle( Segment7, FALSE );
	//m_ledTime.SetValueNbDigit( 6,2 ); 
	////m_ledTime.ShowSign( TRUE );
	//m_ledTime.SetColor( RGB(0,150,0) );
	////m_ledTime.SetValue( 2.35 );
	//m_ledTime.StringMode( TRUE, FALSE );
	//m_ledTime.SetWindowText( _T("00:00:00") );
	////m_ledTime.GetBorder()->SetStyle( CGdiBorder::Both );
	////m_ledTime.GetBorder()->SetShape( CGdiBorder::Ellipse, 10 );
	//m_ledTime.ShowGlass(TRUE,TRUE);
	//m_ledTime.GetBorder()->SetStyle( CGdiBorder::Chrome );
	////m_ledTime.GetBorder()->SetStyle( CGdiBorder::None);
	//m_ledTime.GetBorder()->SetShape( CGdiBorder::RoundRect, 10 );
	////m_ledTime.GetBorder()->SetShape( CGdiBorder::Ellipse, 1 );
	//m_ledTime.GetBorder()->SetSize( 8 );
	//m_ledTime.InvalidateBorder();
	////========================================================================================//
    //;IsiCompBase.obj;IsiLcdDisplay.obj;GdiBorder.obj;COLOR.obj


	CIsiLcdDisplay* pWnd = new CIsiLcdDisplay;
	if ( !pWnd->Create(_T(""), WS_CHILD | WS_VISIBLE, rect, pParentWnd, -1 ) ) 
	{ 
		// Something wrong 
		ASSERT( 0 );
	}
	pWnd->SetSegmentStyle( Segment7, FALSE );
	pWnd->SetValueNbDigit( NumDig,2 ); 
	pWnd->SetColor( RGB(0,150,0) );
	pWnd->StringMode( TRUE, FALSE );
	pWnd->SetWindowText( _T("00:00:00") );
	pWnd->ShowGlass(TRUE,TRUE);
	pWnd->GetBorder()->SetStyle( CGdiBorder::Chrome );
	pWnd->GetBorder()->SetShape( CGdiBorder::RoundRect, 10 );
	pWnd->GetBorder()->SetSize( 8 );
	pWnd->InvalidateBorder();
	//========================================================================================//
	return pWnd;

}

// Load settings
bool LoadMasterAppSettingFile (ALLSETTINGS* pData)
{
	return LoadMasterDataFile (pData);
}
// Load settings
bool LoadAppSettingFile (ALLSETTINGS* pData)
{
	return LoadDataFile (pData);
}
// Save settings
bool SaveAppSettingFile (ALLSETTINGS* pData)
{
	return SaveDataFile (pData);
}
// Load settings
bool LoadBackUpAppSettingFile (int nID,ALLSETTINGS* pData)
{
	return LoadBackUpDataFile (nID,pData);
}
// Backup settings
bool SaveBackUpUpAppSettingFile (int nID,ALLSETTINGS* pData)
{
	return SaveBackUpDataFile (nID,pData);
}

bool WINAPI OkDlg(LPCTSTR lpMsg,bool bXOk)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CDlgOk dlg;

	if (lpMsg != NULL)
		dlg.m_strMsg = lpMsg;
	dlg.m_bXOk = bXOk;
	bool bStat = false;
	if (dlg.DoModal() == IDOK) {
		bStat = true;
	}
	return(bStat);
}
bool WINAPI GetHMIOptDlg(HMIOPT* lpData)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CDlgHMIOpt dlg;
	dlg.m_bBoostPriority = lpData->bBoostPriority;
	dlg.m_bFullReset = lpData->bFullReset;
	dlg.m_bEnableUser = lpData->bEnableUser;
	dlg.m_bEnableMaster = lpData->bEnableMaster;
	dlg.m_nPassword = lpData->nPassword;
	dlg.m_nMasterPassword = lpData->nMasterPassword;
	dlg.m_nPmacReset = lpData->nPmacReset;
	dlg.m_PmacID = lpData->PmacID;

	//dlg.m_strIP = lpData->ServerIP;
	dlg.m_nLaneID = lpData->nLaneID;
	dlg.m_strName = lpData->szLaneName;
	unsigned long addr = inet_addr(lpData->ServerIP);
	dlg.m_dwServerIP = ntohl(addr);

	bool bStat = false;
	if (dlg.DoModal() == IDOK) {
		lpData->bBoostPriority = dlg.m_bBoostPriority;
		lpData->bFullReset = dlg.m_bFullReset;
		lpData->bEnableUser = dlg.m_bEnableUser;
		lpData->bEnableMaster = dlg.m_bEnableMaster;
		lpData->nPassword = dlg.m_nPassword;
		lpData->nMasterPassword = dlg.m_nMasterPassword;
		lpData->nLaneID = dlg.m_nLaneID;
		lpData->nPmacReset = dlg.m_nPmacReset;
		lpData->PmacID = dlg.m_PmacID;
		//TRACE(_T("Name: %s  \n"),dlg.m_strName);
		//TRACE("Length: %d IP: %s \n",len,pszIP);
		//char buff[256];
		//int len =  WideCharToMultiByte(CP_UTF8, 0, dlg.m_strIP, -1, NULL, 0, 0, 0);
		//if (len>1) WideCharToMultiByte(CP_UTF8, 0, dlg.m_strIP, -1, buff, len, 0, 0);
		unsigned char* pIP = (unsigned char*)&dlg.m_dwServerIP;
		char buff[256];
		sprintf_s(buff,"%d.%d.%d.%d",pIP[3],pIP[2],pIP[1],pIP[0]);
		strcpy_s(lpData->ServerIP,buff);
		::lstrcpy (lpData->szLaneName,dlg.m_strName.GetBuffer(0));
		//TRACE(_T("lpData->szLaneName: %s  \n"),lpData->szLaneName);
		bStat = true;
	}
	return bStat;

}

// Load settings
bool LoadAppCounterFile (ALLCOUNTERS* pData)
{
	return LoadCounterFile (pData);
}
// Save settings
bool SaveAppCounterFile (ALLCOUNTERS* pData)
{
	return SaveCounterFile (pData);
}

bool WINAPI GetNumDlg(KEYPADDATA* lpData)
{
	ASSERT(lpData);
	if (!lpData)
		return(FALSE);

	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CKeyPadDlg dlg;	
	dlg.m_dbValue = lpData->dbValue;
	dlg.m_dbIncrement = lpData->dbIncrement;
	dlg.m_nDecimalPlaces = lpData->nDecimalPlaces;
	dlg.m_strLabel = lpData->lpTitle;
	dlg.SetRange(lpData->dbMin,lpData->dbMax);
	dlg.m_bPassWord = lpData->bPassWord;
	bool bStat = false;
	if (dlg.DoModal() == IDOK) {
		bStat = true;
		lpData->dbValue = dlg.m_dbValue;
	}
	return(bStat);
}

CWnd* WINAPI DlgUserSettings(ALLSETTINGS* pData,CWnd* pWndParent,CWnd** ppBackPtr)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CUserSettings* pDlg = new CUserSettings(_T ("User Settings"),pWndParent);
	pDlg->m_ppBackPtr = ppBackPtr;
	pDlg->Initialize(pWndParent,pData);
	pDlg->m_clrBack = RGB(0,0,0);
	pDlg->m_clrText = RGB(0,255,0);
	pDlg->Create (pWndParent);
	pDlg->ShowWindow (SW_SHOW);
	return pDlg;
}

CWnd* WINAPI DlgSettings(ALLSETTINGS* pData,CWnd* pWndParent,CWnd** ppBackPtr)
{

	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CSettings* pDlg = new CSettings(_T ("Settings"),pWndParent);
	pDlg->m_ppBackPtr = ppBackPtr;
	//pDlg->m_pParams = pData;
	pDlg->Initialize(pWndParent,pData);
	pDlg->m_clrBack = RGB(0,0,0);
	pDlg->m_clrText = RGB(0,255,0);
	pDlg->Create (pWndParent);
	pDlg->ShowWindow (SW_SHOW);
	return pDlg;
}



CWnd* WINAPI DlgMotionSettings(MOTIONSETTINGS* pData,CWnd* pWndParent,CWnd** ppBackPtr)
{

	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CPmacSettings* pDlg = new CPmacSettings(_T ("Motion Settings"),pWndParent);
	pDlg->m_ppBackPtr = ppBackPtr;
	//pDlg->m_pParams = pData;
	pDlg->m_clrBack = RGB(0,0,0);
	pDlg->m_clrText = RGB(0,255,0);
	pDlg->Initialize(pWndParent,pData);
	pDlg->Create (pWndParent);
	pDlg->ShowWindow (SW_SHOW);
	return pDlg;
}

CWnd* WINAPI DlgWait(int Timer)
{

	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CDlgWait* pDlg = new CDlgWait();
	pDlg->m_nTimer = Timer;
	pDlg->Create (IDD_WAIT);
	pDlg->ShowWindow (SW_SHOW);
	return pDlg;
}

CWinThread* WINAPI DoSplash(CWinApp* pApp,int nTime,bool* pbSplash)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	//CWinThread* pThread = AfxBeginThread (RUNTIME_CLASS (CSplash));
	//CSplash* pSplash = new CSplash(pbSplash, 1000, CSplash::KillOnClick, &g_pSplash);
	CSplash* pSplash = new CSplash(pApp,1000, CSplash::KillOnClick, pbSplash);
	//return (CWinThread*)pSplash;
	return pSplash;

}

#if 0

bool WINAPI DoCalDlg(CWnd* pWndParent,bool bRun,bool* pbContinue)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CCalibration dlg(pWndParent);
	dlg.m_bRun = bRun;
	dlg.m_pbContinue = pbContinue; 

	//if (lpMsg != NULL)
	//	dlg.m_strMsg = lpMsg;
	bool bStat = false;
	if (dlg.DoModal() == IDOK) {
		bStat = true;
	}

	return(bStat);
}



CWinThread* WINAPI DoSplash(CWinApp* pApp,int nTime,bool* pbSplash)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CSplash* pSplash = new CSplash(pApp,1000, 0, pbSplash);
	return pSplash;
}



CWnd* WINAPI DlgSettings2(ALLSETTINGS* pData,CWnd* pWndParent,CWnd** ppBackPtr)
{

	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	//CSettings2* pDlg = new CSettings2(_T ("Settings"),pWndParent);
	//pDlg->m_ppBackPtr = ppBackPtr;
	//pDlg->m_pParams = pData;
	//pDlg->m_clrBack = RGB(0,0,0);
	//pDlg->m_clrText = RGB(0,255,0);
	//pDlg->Create (pWndParent);
	//pDlg->ShowWindow (SW_SHOW);

	//return pDlg;

	return NULL;
}

int WINAPI PlaneSelectDlg()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CDlgSelPlane dlg;
	dlg.DoModal();
	return dlg.m_nPlane;
}


CWnd* WINAPI MsgDlg(LPCTSTR lpMsg,int Time)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState());	
	//CMSGUIThread* pCMSGUIThread = new CMSGUIThread(lpMsg,Time);

	//m_pThread = AfxBeginThread (RUNTIME_CLASS (CMSGUIThread));
	CStatusMsg* pDlg = new CStatusMsg();
	pDlg->m_pBackPtr = pDlg;
	pDlg->m_msg = lpMsg;
	pDlg->m_Time = Time;
	pDlg->Create (IDD_DLG_MSG);
	pDlg->ShowWindow (SW_SHOW);
	return (CWnd*)pDlg;

}


/////////////////////////////////////////////////////////////////////////
// CMainWindow message map and member functions

BEGIN_MESSAGE_MAP (CParentWindow, CWnd)
    ON_WM_PAINT ()
	ON_WM_CREATE()
END_MESSAGE_MAP ()

CParentWindow::CParentWindow ()
{
    //Create (NULL, _T ("The Hello Application"));
	m_bInit = FALSE;
	Init ();
}

CParentWindow::CParentWindow (CWnd* pWndParent,CWnd* pWnd)
{
	CRect rect;
	pWnd->GetWindowRect(&rect);
	pWnd->DestroyWindow();

//		AfxMessageBox(_T("create"));
			//
		// Register a WNDCLASS.
		CString strWndClass = AfxRegisterWndClass (
			CS_DBLCLKS,                                     // Class style
			AfxGetApp ()->LoadStandardCursor (IDC_ARROW),   // Class cursor
			(HBRUSH) (COLOR_3DFACE + 1),                    // Background brush
			AfxGetApp ()->LoadStandardIcon (IDI_WINLOGO)    // Class icon
		);

		// Create a window.
		//CreateEx (0, strWndClass, _T ("Mil Window"),WS_CHILD,rect, pParentWnd,NULL);
		CreateEx (0, strWndClass, _T ("this is a test"),WS_CHILD | WS_VISIBLE,rect,pWndParent,NULL);
		//TRACE("Init \n");

}
CParentWindow::~CParentWindow()
{
	//AfxMessageBox(_T("delete"));
	//delete this;
}

void CParentWindow::PostNcDestroy()
{
	// TODO: Add your specialized code here and/or call the base class
	CWnd::PostNcDestroy();
	//AfxMessageBox(_T("delete"));

	delete this;
}

void CParentWindow::Init ()
{
	if (!m_bInit)
	{
		//Create (NULL, _T ("The Hello Application"),WS_BORDER | WS_VISIBLE,CRect(0,0,100,100),NULL,NULL,WS_EX_TOPMOST);
		//Create (NULL, _T ("The Hello Application"),WS_VISIBLE,CRect(0,0,100,100));
		//CreateEx(0,AfxRegisterWndClass(0),_T(""),0,CRect(0,0,100,100),NULL,0,0);

		//
		// Register a WNDCLASS.
		//CString strWndClass = AfxRegisterWndClass (
		//	CS_DBLCLKS,                                     // Class style
		//	AfxGetApp ()->LoadStandardCursor (IDC_ARROW),   // Class cursor
		//	(HBRUSH) (COLOR_3DFACE + 1),                    // Background brush
		//	AfxGetApp ()->LoadStandardIcon (IDI_WINLOGO)    // Class icon
		//);


	}
	m_bInit = TRUE;

}

int CParentWindow::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// Remove the title bar
	//ModifyStyle (WS_CAPTION, 0);
	
	// Display
	//SetWindowPos (&wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_DRAWFRAME);

	   // if (m_bStayOnTop) {
    //    SetWindowPos (&wndTopMost, 0, 0, 0, 0, SWP_NOMOVE œ SWP_NOSIZE);
    //    pMenu->CheckMenuItem (IDM_SYSMENU_STAY_ON_TOP, MF_CHECKED);
    //}       
    //else {
    //    SetWindowPos (&wndNoTopMost, 0, 0, 0, 0, SWP_NOMOVE œ SWP_NOSIZE);
    //    pMenu->CheckMenuItem (IDM_SYSMENU_STAY_ON_TOP, MF_UNCHECKED);
    //}


	AfxMessageBox(_T("hello create"));

	return 0;
}

BOOL CParentWindow::PreCreateWindow(CREATESTRUCT& cs)
{

    if (!CWnd::PreCreateWindow(cs))
        return FALSE;
	//cs.dwExStyle ¦= WS_EX_CLIENTEDGE;
	//cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
    //cs.style &= ~WS_CAPTION;
    //cs.style &= ~WS_BORDER;
    //cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW |CS_VREDRAW |CS_DBLCLKS, ::LoadCursor(NULL, IDC_ARROW), HBRUSH(COLOR_WINDOW+1), NULL);
    return TRUE;
}

void CParentWindow::OnPaint ()
{
    CPaintDC dc (this);
    CRect rect;
    GetClientRect (&rect);

//		AfxMessageBox(_T("Paint "));
		CBrush brush (RGB(255,0,0));
        dc.FillRect (rect, &brush);

}
#endif
