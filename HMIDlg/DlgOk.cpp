// DlgOk.cpp : implementation file
//
#include "stdafx.h"
#include "HMIDlg.h"
#include "DlgOk.h"

// CDlgOk dialog

IMPLEMENT_DYNAMIC(CDlgOk, CDialog)

CDlgOk::CDlgOk(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgOk::IDD, pParent)
{
	m_bXOk = false;
	m_strMsg = _T("");

}

CDlgOk::~CDlgOk()
{
}

void CDlgOk::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgOk, CDialog)
END_MESSAGE_MAP()


// CDlgOk message handlers

BOOL CDlgOk::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Initialization
	if 	(m_strMsg != _T("")){
		CWnd* pWnd = GetDlgItem(IDC_MSG);
		pWnd->SetWindowText(m_strMsg);
	}
	
	//HBITMAP hOkBitmap;
	CButton* pBtn = (CButton*)GetDlgItem(IDOK);
	if (m_bXOk){
		pBtn->SetIcon (AfxGetApp ()->LoadIcon (IDI_NOT_OK));
		//hOkBitmap = ::LoadBitmap (AfxGetInstanceHandle (), MAKEINTRESOURCE(IDB_X_OK));
		//SetWindowText(_T("Error"));
	}
	else{
		pBtn->SetIcon (AfxGetApp ()->LoadIcon (IDI_OK));
		//hOkBitmap = ::LoadBitmap (AfxGetInstanceHandle (), MAKEINTRESOURCE(IDB_OK));
	}
	//CButton* pBtn = (CButton*)GetDlgItem(IDOK);
	//pBtn->SetBitmap(hOkBitmap);



	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}