// DlgWait.cpp : implementation file
//

#include "stdafx.h"
#include "HMIDlg.h"
#include "DlgWait.h"
#include "HMIDlgApi.h"


// CDlgWait dialog

IMPLEMENT_DYNAMIC(CDlgWait, CDialog)

CDlgWait::CDlgWait(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgWait::IDD, pParent)
{
	m_nTimer = 100;
	m_nPos = 0;
}

CDlgWait::~CDlgWait()
{
}

void CDlgWait::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS_WAIT, m_ctlWait);
}


BEGIN_MESSAGE_MAP(CDlgWait, CDialog)
	ON_WM_TIMER()
	ON_MESSAGE (WM_WAIT_DLG_UPDATE_TIMER, OnWaitUpdateTimer)

END_MESSAGE_MAP()


// CDlgWait message handlers


BOOL CDlgWait::DestroyWindow()
{
	// TODO: Add your specialized code here and/or call the base class

	return CDialog::DestroyWindow();
}

LRESULT CDlgWait::OnWaitUpdateTimer (WPARAM wParam, LPARAM lParam)
{
	//TRACE("TIMER HELPER\n");
	OnTimer(1);
	return 0;
}


void CDlgWait::OnTimer(UINT_PTR nIDEvent)
{
	m_nPos += 1;
	m_ctlWait.SetPos(m_nPos);
	//TRACE("TIMER \n");
}


BOOL CDlgWait::OnInitDialog()
{
	CDialog::OnInitDialog();
	int Upper = m_nTimer/50;
	m_ctlWait.SetRange32(0,Upper);
	//TRACE("TIMER %d  Step:%d \n",m_nTimer,Upper);

	SetTimer(1,50,NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
