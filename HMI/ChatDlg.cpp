// ChatDlg.cpp : implementation file
//

#include "stdafx.h"
//#include "MySocketsServer.h"
#include "HMI.h"
#include "ChatDlg.h"

IMPLEMENT_DYNCREATE (CUIThread, CWinThread)


BOOL CUIThread::InitInstance ()
{
	CChatDlg dlg;
	m_pMainWnd = &dlg;
	m_hWndMessage = NULL;
	//m_pDlg = &dlg;
	dlg.m_pHwnd = &m_hWndMessage;
	dlg.t_sock = t_sock;
	//dlg.m_pDataVal = &m_nDataVal;
	dlg.DoModal();
	TRACE("CUIThread::InitInstance()  \n");
	//m_pMainWnd = new CMyChatWnd;
    //m_pMainWnd->ShowWindow (SW_SHOW);
    //m_pMainWnd->UpdateWindow ();
    return TRUE;

}
void CUIThread::CloseChat(void)
{
	//m_pDlg->DestroyWindow();
	//m_pDlg->PostMessage(WM_CLOSE,0,0);
	//delete m_pDlg;
	TRACE("CUIThread::CloseChat  \n");
}
int CUIThread::ExitInstance()
{
	TRACE("CUIThread::ExitInstance()  \n");
	m_hWndMessage = NULL;
	delete m_pMainWnd;
	return CWinThread::ExitInstance();
}



// CChatDlg dialog

IMPLEMENT_DYNAMIC(CChatDlg, CDialog)

CChatDlg::CChatDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChatDlg::IDD, pParent)
	, m_strSend(_T(""))
{

}

CChatDlg::~CChatDlg()
{
	TRACE("CChatDlg::~CChatDlg()  \n");
}

void CChatDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SEND, m_strSend);
	DDV_MaxChars(pDX, m_strSend, 255);
}


BEGIN_MESSAGE_MAP(CChatDlg, CDialog)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_SEND, &CChatDlg::OnBnClickedSend)
	ON_MESSAGE (WM_DO_DIALOG_UPDATE, OnDoDialogUpdate)
	ON_EN_CHANGE(IDC_EDIT_SEND, &CChatDlg::OnEnChangeEditSend)
	ON_BN_CLICKED(IDOK, &CChatDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_DN, &CChatDlg::OnBnClickedButtonDn)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CChatDlg message handlers

void CChatDlg::OnTimer(UINT_PTR nIDEvent)
{
	//CDialog::OnTimer(nIDEvent);
	//TRACE("\n");
}

BOOL CChatDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	//SetTimer(1,200,NULL);
	*m_pHwnd = m_hWnd;
	m_hOSKWnd = 0;
	//AfxMessageBox(_T("setpos"));
	//SetWindowPos (NULL, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_DRAWFRAME);


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CChatDlg::OnBnClickedSend()
{

	//CWnd* pWnd = GetDlgItem(IDC_EDIT_RECEIVE);
	CEdit* pWnd = (CEdit*)GetDlgItem(IDC_EDIT_RECEIVE);
	UpdateData(1);

	if (m_strSend == _T(""))
		return;

	char buffer[256];
	int len = WideCharToMultiByte(CP_UTF8, 0,
		m_strSend, -1, NULL, 0, 0, 0);
	if (len>1)
	{
		WideCharToMultiByte(CP_UTF8, 0,
			m_strSend, -1, buffer, len, 0, 0);
	}
	TRACE("Length: %d data: %s \n",len,buffer);

	// Send data
	int rc = send (t_sock,buffer,256,0);
	if (rc == SOCKET_ERROR){
		TRACE("Error Connecting \n");
		//closesocket(sock);
	}
	else
	{
		//CString strCurrent;
		//pWnd->GetWindowText(strCurrent);
		//strCurrent += _T("Me: ");
		//strCurrent += m_strSend;
		//strCurrent += _T("\r\n");
		//pWnd->SetWindowText(strCurrent);

		CString strCurrent;
		int length = pWnd->GetWindowTextLength();
		pWnd->SetSel(length,length);
		strCurrent = _T("Me: ");
		strCurrent += m_strSend;
		strCurrent += _T("\r\n");
		pWnd->ReplaceSel(strCurrent);		

		m_strSend =  _T("");
		UpdateData(0);
	}

}

void CChatDlg::PostNcDestroy()
{
	//TRACE("PostNcDestroy \n");
	//CDialog::PostNcDestroy();
	//delete this;
	if (m_hOSKWnd > 0)
	{
		::CloseWindow(m_hOSKWnd);
		m_hOSKWnd = 0;
		return;
	}
}

//	ON_MESSAGE (WM_DO_DIALOG_UPDATE, OnDoDialogUpdate)

// 
LRESULT CChatDlg::OnDoDialogUpdate (WPARAM wParam, LPARAM lParam)
{
	CEdit* pWnd = (CEdit*)GetDlgItem(IDC_EDIT_RECEIVE);
	char* buffer = (char*)wParam;
	//buffer[5] = 0;
	TRACE("OnDoDialogUpdate: %d %s\n",buffer[0],buffer);
	CString str(buffer);
	TRACE(_T("%s\n"),str);


	CString strCurrent;
	int length = pWnd->GetWindowTextLength();
	pWnd->SetSel(length,length);
	strCurrent = _T("You: ");
	strCurrent += str;
	strCurrent += _T("\r\n");
	pWnd->ReplaceSel(strCurrent);		


	return 0;
}


void CChatDlg::OnEnChangeEditSend()
{
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	//TRACE("OnEnChangeEditSend:\n");

}


void CChatDlg::OnBnClickedOk()
{
	TRACE("OnBnClickedOk:\n");
	OnBnClickedSend();
	//CDialog::OnOK();
}


void CChatDlg::OnBnClickedButtonDn()
{
	if (m_hOSKWnd > 0)
	{
		::CloseWindow(m_hOSKWnd);
		m_hOSKWnd = 0;
		return;
	}

	//CString strPath,num;
	//CString strFilename;
	TCHAR szName[256];
	STARTUPINFO si;
	//KEYPADDATA data;
	//CGetName dlg;
	//CHMIApp* pApp = (CHMIApp*)AfxGetApp();

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
		Sleep(100);
	}

	// Position the keyboard
	int TryCount=2000;
	//TRACE("OSK Window %d \n",hWnd);
	m_hOSKWnd = 0;
	while (m_hOSKWnd == 0 && TryCount > 0 )
	{
		m_hOSKWnd = ::FindWindow(NULL,_T("On-Screen Keyboard"));
		if (m_hOSKWnd == 0)
		{
			TRACE("Looking for OSK Window %d \n",TryCount);
			TryCount--;
		}
	}
	if (m_hOSKWnd > 0)
	{
		//DWORD Style = ::GetWindowLong(hWnd,GWL_STYLE);
		//Style = Style & ~WS_CAPTION;
		//Style = Style & ~WS_THICKFRAME;
		//::SetWindowLong(hWnd,GWL_STYLE,Style);
		//::SetWindowPos(hWnd,NULL,WINDOW_POSITION_X,400,1024,768,SWP_NOSIZE | SWP_NOZORDER | SWP_DRAWFRAME);
		::SetWindowPos(m_hOSKWnd,NULL,0,470,1024,300,SWP_NOZORDER | SWP_DRAWFRAME);
		//::CloseWindow(wWnd);
	}

}


int CChatDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	//AfxMessageBox(_T("setpos"));
	SetWindowPos (NULL, 250, 10, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_DRAWFRAME);


	return 0;
}
