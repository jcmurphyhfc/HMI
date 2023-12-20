// PmacTerminal.cpp : implementation file
//

#include "stdafx.h"
#include "HMI.h"
#include "PmacTerminal.h"
//#include "afxdialogex.h"

BEGIN_MESSAGE_MAP (CMyEdit, CEdit)
    ON_WM_CHAR ()
END_MESSAGE_MAP ()

void CMyEdit::OnChar (UINT nChar, UINT nRepCnt, UINT nFlags)
{
	//if (((nChar >= _T ('0')) && (nChar <= _T ('9'))) || (nChar == VK_BACK))
	//{
	//	TRACE("My Edit \n");
	//}
	//TRACE("nChar %d \n",nChar);
	//if ((nChar == VK_UP) || (nChar == VK_DOWN))
	//{
	//	TRACE("My Edit UP DOWN \n");
	//}
    CEdit::OnChar (nChar, nRepCnt, nFlags);
}
// CPmacTerminal dialog

IMPLEMENT_DYNAMIC(CPmacTerminal, CDialog)

CPmacTerminal::CPmacTerminal(CWnd* pParent /*=NULL*/)
	: CDialog(CPmacTerminal::IDD, pParent)
{
	m_ppBackPtr = NULL;
	m_nVarType = 0;
	m_bUpdateComplete = false;
	m_hOSKWnd = NULL;
}

CPmacTerminal::~CPmacTerminal()
{
	if (m_ppBackPtr)
		*m_ppBackPtr = NULL;

	if (m_hOSKWnd > 0)
	{
		::CloseWindow(m_hOSKWnd);
	}

}

void CPmacTerminal::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_VAR_TYPE1, m_nVarType);
	DDX_Control(pDX, IDC_GDITEDITCTRL_VARNUM, m_ctlVarNum);
	DDX_Control(pDX, IDC_GDITEDITCTRL_VAR_VALUE, m_ctlVarValue);
	DDX_Control(pDX, IDC_GDITEDITCTRL_VAR_PRESISION, m_ctlVarPrecision);
	DDX_Control(pDX, IDC_COMMAND_EDIT, m_ctlEdit);
}


BEGIN_MESSAGE_MAP(CPmacTerminal, CDialog)
	ON_BN_CLICKED(ID_CLOSE, &CPmacTerminal::OnBnClickedClose)
	ON_BN_CLICKED(IDC_SAVE_PMAC_SETTINGS, &CPmacTerminal::OnBnClickedSavePmacSettings)
	ON_WM_TIMER()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_SEND1, &CPmacTerminal::OnBnClickedSend1)
	ON_BN_CLICKED(IDC_SEND2, &CPmacTerminal::OnBnClickedSend2)
	ON_BN_CLICKED(IDC_PMAC_CMD, &CPmacTerminal::OnBnClickedPmacCmd)
	ON_BN_CLICKED(IDC_KEYBOARD, &CPmacTerminal::OnBnClickedKeyboard)
	ON_BN_CLICKED(IDC_SAVE_HMI_SETTINGS, &CPmacTerminal::OnBnClickedSaveHmiSettings)
	ON_WM_CHAR()
END_MESSAGE_MAP()


// CPmacTerminal message handlers


void CPmacTerminal::PostNcDestroy()
{
	CDialog::PostNcDestroy();
	delete this;
}


void CPmacTerminal::OnBnClickedClose()
{
	TRACE("OnClose \n");
	DestroyWindow();
}
char CPmacTerminal::OnGetVarType() 
{

	UpdateData (TRUE);

	char ch = 'P';
	switch (m_nVarType) {

	case 0: // P-Variable
		ch = 'P';
		//TRACE("P READ \n");
		break;
	case 1: // I-variable
		ch = 'I';
		//TRACE("I READ \n");
		break;
	case 2: // Q-variable
		ch = 'Q';
		//TRACE("Q READ \n");
		break;
	case 3: // M-variable
		ch = 'M';
		//TRACE("M READ \n");
		break;
	}
	return ch;
	//if (m_pCom != NULL){
	//	m_wndVarValue.SetValue(m_pCom->GetPmacVariableDouble(ch, (int)m_wndVarNum.GetValue() ));
	//	//TRACE("GetPamcVariableDouble = %f \n",m_pCom->GetPmacVariableDouble('p', 1000));
	//}
	
}

BEGIN_EVENTSINK_MAP(CPmacTerminal, CDialog)
	ON_EVENT(CPmacTerminal, IDC_GDITEDITCTRL_VARNUM, DISPID_CLICK, CPmacTerminal::ClickGditeditctrlVarnum, VTS_NONE)
	ON_EVENT(CPmacTerminal, IDC_GDITEDITCTRL_VAR_VALUE, DISPID_CLICK, CPmacTerminal::ClickGditeditctrlVarValue, VTS_NONE)
	ON_EVENT(CPmacTerminal, IDC_GDITEDITCTRL_VAR_PRESISION, DISPID_CLICK, CPmacTerminal::ClickGditeditctrlVarPresision, VTS_NONE)
END_EVENTSINK_MAP()


void CPmacTerminal::ClickGditeditctrlVarnum()
{
	if (m_hOSKWnd > 0)
	{
		::CloseWindow(m_hOSKWnd);
		m_hOSKWnd = 0;
	}

	KEYPADDATA data;
	data.dbIncrement = 	1;
	data.dbMin = m_ctlVarNum.GetMinValue();
	data.dbMax = m_ctlVarNum.GetMaxValue();
	data.dbValue = m_ctlVarNum.GetValue();
	data.lpTitle = _T("Enter Variable Number");
	data.nDecimalPlaces = m_ctlVarNum.GetPrecision();
	data.bPassWord = false;
	bool bOk = GetNumDlg(&data);
	if (bOk) 
	{			
		//TRACE(" \n",);
		m_ctlVarNum.SetValue(data.dbValue);

		double data;
		m_pmac->GetVariable(OnGetVarType(),(long)m_ctlVarNum.GetValue(),&data);
		m_ctlVarValue.SetValue(data);

	}

}


void CPmacTerminal::ClickGditeditctrlVarValue()
{
	if (m_hOSKWnd > 0)
	{
		::CloseWindow(m_hOSKWnd);
		m_hOSKWnd = 0;
	}

	KEYPADDATA data;
	data.dbIncrement = 	1;
	data.dbMin = m_ctlVarValue.GetMinValue();
	data.dbMax = m_ctlVarValue.GetMaxValue();
	data.dbValue = m_ctlVarValue.GetValue();
	data.lpTitle = _T("Enter Value");
	m_ctlVarValue.SetPrecision((short)m_ctlVarPrecision.GetValue());
	data.nDecimalPlaces = m_ctlVarValue.GetPrecision();
	data.bPassWord = false;
	bool bOk = GetNumDlg(&data);
	if (bOk) 
	{			
		//TRACE(" \n",);
		m_ctlVarValue.SetValue(data.dbValue);
		m_pmac->SetVariable(OnGetVarType(),(long)m_ctlVarNum.GetValue(),data.dbValue);
		//m_ctlVarValue.SetValue(data);

	}

}

BOOL CPmacTerminal::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_fontLarge.CreatePointFont (120, _T ("Microsoft Sans Serif"));
	CWnd* pWnd = GetDlgItem(IDC_TERMINAL_EDIT);
	pWnd->SetFont(&m_fontLarge);


	//
	m_ctlVarNum.SetValue(0);
	double data;
	m_pmac->GetVariable(OnGetVarType(),(long)m_ctlVarNum.GetValue(),&data);
	m_ctlVarValue.SetValue(data);

	// Set a update timer
	SetTimer(1,2000,NULL);

	m_brBrush.CreateSolidBrush (RGB (0, 0, 0));

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CPmacTerminal::OnBnClickedSavePmacSettings()
{
	//AfxGetMainWnd ()->SendMessage (WM_USER_APPLY, 0, (LPARAM) &rp);
	TRACE("Doing KillTimer terminal update.........\n");
	KillTimer(1);
	AfxGetMainWnd ()->SendMessage (WM_USER_PMAC_SAVE, 0, 0);
	SetTimer(1,2000,NULL);
	TRACE("Doing StartTimer terminal update.........\n");
}


void CPmacTerminal::OnTimer(UINT_PTR nIDEvent)
{
	if (!m_bUpdateComplete)
	{
		KillTimer(1);
		UpdateTerminal();
		SetTimer(1,2000,NULL);
		//TRACE("Doing OnTimer terminal update.........\n");
	}
	m_bUpdateComplete = false;
}

void CPmacTerminal::UpdateTerminal()
{
	double data;
	m_pmac->GetVariable(OnGetVarType(),(long)m_ctlVarNum.GetValue(),&data);
	//TRACE("Data:%f \n",data);
	m_ctlVarValue.SetPrecision((short)m_ctlVarPrecision.GetValue());
	m_ctlVarValue.SetValue(data);
	m_bUpdateComplete = true;
	//CDialog::OnTimer(nIDEvent);
	//TRACE("UPDATE UpdateTerminal\n");
}


void CPmacTerminal::ClickGditeditctrlVarPresision()
{

	if (m_hOSKWnd > 0)
	{
		::CloseWindow(m_hOSKWnd);
		m_hOSKWnd = 0;
	}

	KEYPADDATA data;
	data.dbIncrement = 	1;
	data.dbMin = m_ctlVarPrecision.GetMinValue();
	data.dbMax = m_ctlVarPrecision.GetMaxValue();
	data.dbValue = m_ctlVarPrecision.GetValue();
	data.lpTitle = _T("Enter number of decimal places");
	data.nDecimalPlaces = m_ctlVarPrecision.GetPrecision();
	data.bPassWord = false;
	bool bOk = GetNumDlg(&data);
	if (bOk) 
	{			
		//TRACE(" \n",);
		m_ctlVarPrecision.SetValue(data.dbValue);
		//m_pmac->SetVariable(OnGetVarType(),(long)m_ctlVarNum.GetValue(),data.dbValue);
		//m_ctlVarValue.SetValue(data);

	}
}


HBRUSH CPmacTerminal::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	CWnd* pWndEdit = GetDlgItem(IDC_TERMINAL_EDIT);
	if (pWndEdit->m_hWnd == pWnd->m_hWnd) {
        pDC->SetTextColor (RGB (0, 255, 255));
        pDC->SetBkColor (RGB (0, 0, 0));
        return (HBRUSH) m_brBrush;
    }
	return hbr;
}

void CPmacTerminal::OnOK()
{
	TRACE("OnBnClickedOk ");
	CWnd* pWnd = GetDlgItem(IDC_COMMAND_EDIT);
	GetCmd(IDC_COMMAND_EDIT);
	pWnd->SetWindowText(_T(""));

}

void CPmacTerminal::GetCmd(int nID)
{

	CWnd* pWnd = GetDlgItem(nID);
	int NumChars;
	TCHAR resBuff[4096];
	CString strCmd;
	CString res;
	//CString res2;
	CString ExtractText;
	CString ResText;

	// Get the command
	pWnd->GetWindowText(strCmd);

	// Get the response
	NumChars = m_pmac->GetResponse(strCmd,resBuff);
	res = resBuff;
	//TRACE(_T("First NumChars %d\n"),NumChars);
	//if (NumChars>1400)
	//{
	//	NumChars = m_pmac->GetResponseBuffer(resBuff);
	//	TRACE(_T("Second NumChars %d\n"),NumChars);	
	//	res2 = resBuff;
	//	res += res2;
	//}

	// Show the result
	pWnd = GetDlgItem(IDC_TERMINAL_EDIT);

	int Start = 0;
	int End = 0;
	while (End >=0 )
	{
		End = res.Find(_T('\r'),Start);
		if (End > 0)
		{
			ExtractText = res.Mid(Start,End-Start);
			ResText += ExtractText + _T("\r\n");
			//TRACE(_T("%s  Start:%d End:%d \n"),ExtractText,Start,End);
			Start = End + 1;		
		}
	}
	if (ResText != _T(""))
	{	
		pWnd->SetWindowText(ResText);
	}


}

void CPmacTerminal::OnBnClickedSend1()
{
	GetCmd(IDC_REPEAT_CMD1);
}


void CPmacTerminal::OnBnClickedSend2()
{
	GetCmd(IDC_REPEAT_CMD2);
}


void CPmacTerminal::OnBnClickedPmacCmd()
{
	TCHAR szName[256];
	STARTUPINFO si;
	::ZeroMemory (&si, sizeof (STARTUPINFO));
	si.cb = sizeof (STARTUPINFO);
	PROCESS_INFORMATION pi;

	::ZeroMemory (&si, sizeof (STARTUPINFO));
	si.cb = sizeof (STARTUPINFO);
	::lstrcpy(szName,_T ("C:\\Program Files\\Hormel Foods LLC\\PmacCmd.exe"));

	if (::CreateProcess (NULL,szName ,
		NULL,NULL,FALSE, NORMAL_PRIORITY_CLASS, NULL, NULL, &si, &pi)) {
		::CloseHandle (pi.hThread);
		//::WaitForSingleObject (pi.hProcess, INFINITE);
		::CloseHandle (pi.hProcess);
	}

}


void CPmacTerminal::OnBnClickedKeyboard()
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


void CPmacTerminal::OnBnClickedSaveHmiSettings()
{
	//AfxGetMainWnd ()->SendMessage (WM_USER_APPLY, 0, (LPARAM) &rp);
	//TRACE("Doing KillTimer terminal update.........\n");
	//KillTimer(1);
	AfxGetMainWnd ()->SendMessage (WM_USER_HMI_SAVE, 0, 0);
	//SetTimer(1,2000,NULL);
	//TRACE("Doing StartTimer terminal update.........\n");
}


void CPmacTerminal::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	//if ((nChar == VK_UP) || (nChar == VK_DOWN))
	//{
	//	TRACE("My Edit UP/DOWN \n");
	//}
	CDialog::OnChar(nChar, nRepCnt, nFlags);
}
