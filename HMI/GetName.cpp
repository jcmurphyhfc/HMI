// GetName.cpp : implementation file
//

#include "stdafx.h"
#include "HMI.h"
#include "GetName.h"
//#include "afxdialogex.h"


// CGetName dialog

IMPLEMENT_DYNAMIC(CGetName, CDialog)

CGetName::CGetName(CWnd* pParent /*=NULL*/)
	: CDialog(CGetName::IDD, pParent)
	, m_strName(_T(""))
{

}

CGetName::~CGetName()
{
}

void CGetName::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strName);
	DDV_MaxChars(pDX, m_strName, 256);
}


BEGIN_MESSAGE_MAP(CGetName, CDialog)
END_MESSAGE_MAP()


// CGetName message handlers


BOOL CGetName::PreCreateWindow(CREATESTRUCT& cs)
{
	//cs.cx = 0;
	//cs.cy = 0;
	return CDialog::PreCreateWindow(cs);
}


BOOL CGetName::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetWindowPos(NULL,WINDOW_POSITION_X+200,240,0,0,SWP_NOSIZE | SWP_NOZORDER);
	//CenterWindow();
	CWnd* pWnd = GetDlgItem(IDC_EDIT1);
	pWnd->SetFocus();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
