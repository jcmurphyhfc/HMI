// Alarms.cpp : implementation file
//

#include "stdafx.h"
#include "HMI.h"
#include "Alarms.h"
//#include "afxdialogex.h"


// CAlarms dialog

IMPLEMENT_DYNAMIC(CAlarms, CDialog)

CAlarms::CAlarms(CWnd* pParent /*=NULL*/)
	: CDialog(CAlarms::IDD, pParent)
{
	m_ppBackPtr = NULL;
	m_pWnd = pParent;
	m_nID = 0;
}

CAlarms::~CAlarms()
{
	TRACE("CAlarms::~CAlarms() \n");
	if (m_ppBackPtr)
		*m_ppBackPtr = NULL;
}

void CAlarms::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GDIBUTTONXLCTRL_ESTOP, m_ctlLight);
}


BEGIN_MESSAGE_MAP(CAlarms, CDialog)
	ON_WM_TIMER()
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CAlarms message handlers


void CAlarms::PostNcDestroy()
{
	CDialog::PostNcDestroy();
	TRACE("CAlarms::PostNcDestroy() \n");
    //AfxGetMainWnd ()->SendMessage (WM_USER_DIALOG_DESTROYED, 0, 0);
    delete this;
}


void CAlarms::OnOK()
{
	//CDialog::OnOK();
	m_pWnd->SendMessage (WM_CLEAR_ALARM,m_nID,0);
	DestroyWindow ();

	//if (m_ppBackPtr)
	//	*m_ppBackPtr = NULL;

}


void CAlarms::OnCancel()
{
	//CDialog::OnCancel();
	//DestroyWindow ();
}


void CAlarms::OnTimer(UINT_PTR nIDEvent)
{
	//CDialog::OnTimer(nIDEvent);
	if (m_ctlLight.GetLightOn() == 1)
		m_ctlLight.SetLightOn(0);
	else
		m_ctlLight.SetLightOn(1);
}


int CAlarms::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}

BOOL CAlarms::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetTimer(1,600,NULL);
	CWnd* pWnd = GetDlgItem(IDC_MSG);
	if (pWnd) pWnd->SetWindowText(m_strMsg);

	return TRUE;  // return TRUE unless you set the focus to a control
}
