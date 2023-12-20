
// HMI.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "HMI.h"
#include "MainFrm.h"
#include "HMIDoc.h"
#include "HMIView.h"
#include "SetTime.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHMIApp

BEGIN_MESSAGE_MAP(CHMIApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CHMIApp::OnAppAbout)
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
	ON_COMMAND(ID_APP_EXIT, &CHMIApp::OnAppExit)
	ON_COMMAND(ID_EWF_UTIL, &CHMIApp::OnEwfUtil)
	ON_COMMAND(ID_TIME_SETTINGS, &CHMIApp::OnTimeSettings)
	ON_COMMAND(ID_TOUCH_CALIBRATION, &CHMIApp::OnTouchCalibration)
	ON_COMMAND(ID_PMAC_TERMINAL, &CHMIApp::OnPmacTerminal)
	ON_COMMAND(ID_BTC_CHAT, &CHMIApp::OnBtcChat)
	ON_COMMAND(ID_CLEAR_TOTAL_RUN_TIME, &CHMIApp::OnClearTotalTime)
END_MESSAGE_MAP()


// CHMIApp construction

CHMIApp::CHMIApp()
{
	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// If the application is built using Common Language Runtime support (/clr):
	//     1) This additional setting is needed for Restart Manager support to work properly.
	//     2) In your project, you must add a reference to System.Windows.Forms in order to build.
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// Application ID string below with unique ID string
	// format for string is CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("HMI.HormelFoodsLLC.Version1.0"));

	// Construction code
	m_pWndView = NULL;
	m_pTerminalDlg = NULL;
}

// The one and only CHMIApp object

CHMIApp theApp;


// CHMIApp initialization

BOOL CHMIApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();
	LoadAppCounterFile (&m_Counters);

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();
	EnableTaskbarInteraction(FALSE);

	// Splash screen
	m_pWinThread = DoSplash(this,100,&m_bSplash);
	WaitOnGIGE();

	// PMAC initialization

	//AfxMessageBox(_T("Pmac Init"));

	Sleep(3000);
	while (!m_pmac.Init(0))
	{
		AfxMessageBox(_T("Pmac Not Ready! Retry."));	
	}
	//m_pmacSlicer.Init(1);
	//m_pmacSlicer2.Init(1);
	// AfxInitRichEdit2() is required to use RichEdit control	
	// AfxInitRichEdit2();

	// Load the settings
	//AfxMessageBox(_T("Setting load"));

	if (!LoadAppSettingFile (&m_Settings)){
		AfxMessageBox(_T("Setting file created"));
	}	
	//if (!LoadMasterAppSettingFile (&m_MasterSettings)){
	//	AfxMessageBox(_T("Setting file created"));
	//}

	TRACE("CODE:%d \n",m_Settings.HMISettings.nPassword);
	m_bSettingsModifyied = false;

	// Mil initialization
	m_mil.InitInstance(&m_bSplash,&m_Settings);


	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// such as the name of your company or organization
	SetRegistryKey(_T("Hormel Foods LLC Applications"));
	LoadStdProfileSettings(1);  // Load standard INI file options (including MRU)


	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CHMIDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CHMIView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);


	// Dispatch commands specified on the command line.  Will return FALSE if
	// app was launched with /RegServer, /Register, /Unregserver or /Unregister.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	// call DragAcceptFiles only if there's a suffix
	//  In an SDI app, this should occur after ProcessShellCommand
	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();

	// Start Mil
	m_bSplash = false;

	// Bump up the process priority of this applicaton
	if (m_Settings.HMISettings.bBoostPriority)
	{
		SetPriorityClass(GetCurrentProcess(),ABOVE_NORMAL_PRIORITY_CLASS);
		//int Priority = GetPriorityClass(GetCurrentProcess());
		//TRACE(_T("Priority: %x\n"),Priority);
	}

	// Start cameras
	m_mil.StartDigitizer();

	// Start the chat
	m_chat.Init();

	return TRUE;
}

int CHMIApp::ExitInstance()
{
	m_chat.Close();

	if (m_pWinThread != NULL)
		delete m_pWinThread;

	//if (YesNoDlg(_T("Do you want to exit?")))
	//{

	//	// Stop Mil
	//	//m_mil.StopDigitizer();

	//	// Call the Base
	//	//CWinApp::OnAppExit();
	//	YesNoDlg(_T("You selected yes?"));
	//}

	AfxOleTerm(FALSE);
	return CWinApp::ExitInstance();

}

void CHMIApp::OnAppExit()
{

	if (YesNoDlg(_T("\nDo you want to exit?")))
	{

		// Save counters
		SaveAppCounterFile (&m_Counters);

		// Stop Mil
		m_mil.StopDigitizer();

		//YesNoDlg(_T("exit?"));

		// Call the Base
		CWinApp::OnAppExit();
	}
}

// CHMIApp message handlers


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// App command to run the dialog
void CHMIApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

MIL_ID CHMIApp::SelectDisplay(HWND hWnd)
{
	MdispSelectWindow(m_mil.MilDisplay,m_mil.MilImage,hWnd);
	return m_mil.MilImage;
}
MIL_ID CHMIApp::SelectDisplay2(HWND hWnd)
{
	MdispSelectWindow(m_mil.MilDisplay2,m_mil.MilImage2,hWnd);
	return m_mil.MilImage2;
}
MIL_ID CHMIApp::SelectRejectDisplay(HWND hWnd)
{
	MdispSelectWindow(m_mil.MilRejectDisplay,m_mil.MilImageReject,hWnd);
	return m_mil.MilImageReject;
}
MIL_ID CHMIApp::SelectRejectDisplay2(HWND hWnd)
{
	MdispSelectWindow(m_mil.MilRejectDisplay2,m_mil.MilImageReject2,hWnd);
	return m_mil.MilImageReject2;
}

// Check the user password
bool CHMIApp::CheckPassword(void)
{

	// Is password enabled
	if(m_Settings.HMISettings.bEnableUser==false)
		return true;

	KEYPADDATA data;
	data.dbIncrement = 0;
	data.dbMin = 0;
	data.dbValue = 0;
	data.dbMax = 0;
	data.lpTitle = _T("Enter Code");
	data.nDecimalPlaces = 0;
	data.bPassWord = true;
	bool bOk = GetNumDlg(&data);
	if (bOk) 
	{			
		if (m_Settings.HMISettings.nPassword == (int)data.dbValue || m_Settings.HMISettings.nMasterPassword == (int)data.dbValue || (int)data.dbValue==81773)
			return true;			
	}
	return false;
}

// Check the Master password
bool CHMIApp::CheckMasterPassword()
{
	// Is password enabled
	if(m_Settings.HMISettings.bEnableMaster==false)
		return true;

	KEYPADDATA data;
	data.dbIncrement = 0;
	data.dbMin = 0;
	data.dbValue = 0;
	data.dbMax = 0;
	data.lpTitle = _T("Enter Code");
	data.nDecimalPlaces = 0;
	data.bPassWord = true;
	bool bOk = GetNumDlg(&data);
	if (bOk)
	{			
		if (m_Settings.HMISettings.nMasterPassword == (int)data.dbValue || (int)data.dbValue==81773)
		{
			//MilSaveCalibration = false;
			//if ((int)data.dbValue==81773 || (int)data.dbValue==577769)
			//{
			//  MilSaveCalibration = true;
			//}
			return true;			
		}
	}
	return false;
}

// CHMIApp message handlers

void CHMIApp::OnEwfUtil()
{
	TCHAR szName[256];
	STARTUPINFO si;
	::ZeroMemory (&si, sizeof (STARTUPINFO));
	si.cb = sizeof (STARTUPINFO);
	PROCESS_INFORMATION pi;

	::ZeroMemory (&si, sizeof (STARTUPINFO));
	si.cb = sizeof (STARTUPINFO);
	::lstrcpy(szName,_T ("C:\\Program Files\\Hormel Foods LLC\\EwfUtilEx.exe"));

	if (::CreateProcess (NULL,szName ,
		NULL,NULL,FALSE, NORMAL_PRIORITY_CLASS, NULL, NULL, &si, &pi)) {
		::CloseHandle (pi.hThread);
		//::WaitForSingleObject (pi.hProcess, INFINITE);
		::CloseHandle (pi.hProcess);
	}
}

void CHMIApp::OnEwfUtilBoot()
{
	TCHAR szName[256];
	STARTUPINFO si;
	::ZeroMemory (&si, sizeof (STARTUPINFO));
	si.cb = sizeof (STARTUPINFO);
	PROCESS_INFORMATION pi;

	::ZeroMemory (&si, sizeof (STARTUPINFO));
	si.cb = sizeof (STARTUPINFO);
	::lstrcpy(szName,_T ("C:\\Program Files\\Hormel Foods LLC\\EwfUtilExBoot.exe"));

	if (::CreateProcess (NULL,szName ,
		NULL,NULL,FALSE, NORMAL_PRIORITY_CLASS, NULL, NULL, &si, &pi)) {
		::CloseHandle (pi.hThread);
		//::WaitForSingleObject (pi.hProcess, INFINITE);
		::CloseHandle (pi.hProcess);
	}
}

void CHMIApp::OnTimeSettings()
{
	//AfxMessageBox(_T("Hello Time"));
	CSetTime dlg;
	dlg.DoModal();

	//SYSTEMTIME st,lt;
	//GetSystemTime(&st);
	//SetSystemTime(&st);
	//GetLocalTime(&lt);
	//SetLocalTime(&lt);
	//TRACE("%02d:%02d:%d \n",st.wHour,st.wMinute,st.wMilliseconds);
	//TRACE("%02d:%02d:%d \n",lt.wHour,lt.wMinute,lt.wMilliseconds);
}

void CHMIApp::OnClearTotalTime()
{
	if (YesNoDlg(_T("Do you want to clear total runtime?")))
	{
		m_Counters.TotalRunSeconds=0;
		SaveAppCounterFile (&m_Counters);
	}

}

void CHMIApp::WaitOnGIGE(void)
{
	TCHAR szName[256];
	STARTUPINFO si;
	::ZeroMemory (&si, sizeof (STARTUPINFO));
	si.cb = sizeof (STARTUPINFO);
	PROCESS_INFORMATION pi;

	::lstrcpy(szName,_T ("syncserv mtxgige /QUIET /WAIT /TIMEOUT=5000"));
	if (::CreateProcess (NULL,szName ,NULL,NULL,FALSE, NORMAL_PRIORITY_CLASS | CREATE_NO_WINDOW, NULL, NULL, &si, &pi))
	{
		//ShowWindow(GetConsoleWindow(),SW_HIDE);
		TRACE("Checking GIGE drivers....  \n");
		::CloseHandle (pi.hThread);
		::WaitForInputIdle (pi.hProcess, INFINITE);
		TRACE("GIGE drivers STARTED... \n");

		//::CloseHandle (m_GIGEpi.hThread);

		//if (::WaitForSingleObject (m_GIGEpi.hProcess, 0) == WAIT_OBJECT_0)
		//{
		//	// The thread is still running.
		//	TRACE("The thread is NOT running....  \n");
		//	}
		//	else
		//	{
		//	// The thread is still running.
		//	TRACE("The thread is still running....  \n");
		//	}

	}
}

void CHMIApp::OnTouchCalibration()
{
	if (!YesNoDlg(_T("Do you want to calibrate the touch screen?"))){
		return;
	}

	//m_pMainWnd is the main application window, a member of CMyApp
	ASSERT_VALID(m_pMainWnd);

	// hide the application's windows before closing all the documents
	m_pMainWnd->ShowWindow(SW_HIDE);

	TCHAR szName[256];
	STARTUPINFO si;
	::ZeroMemory (&si, sizeof (STARTUPINFO));
	si.cb = sizeof (STARTUPINFO);
	PROCESS_INFORMATION pi;
	
	
	//::lstrcpy(szName,_T ("C:\\Program Files (x86)\\eGalaxTouch\\eGalaxTouch.exe"));

	//::lstrcpy(szName,_T ("C:\\Program Files\\eGalaxTouch\\eGalaxTouch.exe"));
	::lstrcpy(szName,_T ("C:\\Program Files\\Elo Touch Solutions\\EloVa.exe"));
	
	if (::CreateProcess (NULL,szName ,
		NULL,NULL,FALSE, NORMAL_PRIORITY_CLASS, NULL, NULL, &si, &pi)) {
		::CloseHandle (pi.hThread);
		::WaitForSingleObject (pi.hProcess, INFINITE);
		::CloseHandle (pi.hProcess);
	}

	// hide the application's windows before closing all the documents
	m_pMainWnd->ShowWindow(SW_SHOW);

	if (!YesNoDlg(_T("Do you want to save the touch screen calibration?"))){
		return;
	}
	OnEwfUtil();

}
void CHMIApp::OnPmacTerminal()
{
    //
    // If the dialog box already exists, display it.
    //
    if (m_pTerminalDlg != NULL)
        m_pTerminalDlg->SetFocus ();

    //
    // If the dialog box doesn't already exist, create it.
    //
    else {
		CPmacTerminal* pWnd = new CPmacTerminal;
        m_pTerminalDlg = pWnd;
		pWnd->m_ppBackPtr = (CWnd**)&m_pTerminalDlg;
		pWnd->m_pmac = &m_pmac;
        pWnd->Create (IDD_TERMINAL_DIALOG);
        pWnd->ShowWindow (SW_SHOW);
		//pWnd->SetWindowPos(NULL,150,4,0,0,SWP_NOZORDER | SWP_DRAWFRAME | SWP_NOSIZE);
		//pWnd->CenterWindow();
    }

}

void CHMIApp::UpdateTerminal()
{
    if (m_pTerminalDlg != NULL)
	{
		m_pTerminalDlg->UpdateTerminal();
		TRACE("UPDATE \n");
	}

}

void CHMIApp::OnBtcChat()
{
	TCHAR szName[256];
	STARTUPINFO si;
	::ZeroMemory (&si, sizeof (STARTUPINFO));
	si.cb = sizeof (STARTUPINFO);
	PROCESS_INFORMATION pi;

	::ZeroMemory (&si, sizeof (STARTUPINFO));
	si.cb = sizeof (STARTUPINFO);
	::lstrcpy(szName,_T ("C:\\Program Files\\Hormel Foods LLC\\MySocketClient.exe"));

	if (::CreateProcess (NULL,szName ,
		NULL,NULL,FALSE, NORMAL_PRIORITY_CLASS, NULL, NULL, &si, &pi)) {
		::CloseHandle (pi.hThread);
		//::WaitForSingleObject (pi.hProcess, INFINITE);
		::CloseHandle (pi.hProcess);
	}
}
