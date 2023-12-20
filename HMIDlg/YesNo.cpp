// YesNo.cpp : implementation file
//

#include "stdafx.h"
#include "HMIDlg.h"
#include "YesNo.h"


// CYesNo dialog

IMPLEMENT_DYNAMIC(CYesNo, CDialog)

CYesNo::CYesNo(CWnd* pParent /*=NULL*/)
	: CDialog(CYesNo::IDD, pParent)
{
	m_strMsg = _T("");
}

CYesNo::~CYesNo()
{
}

void CYesNo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CYesNo, CDialog)
END_MESSAGE_MAP()


// CYesNo message handlers

BOOL CYesNo::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Initialization
	m_font.CreatePointFont (140, _T ("Microsoft Sans Serif"));
	CWnd* pWnd = GetDlgItem(IDC_MSG2);
	pWnd->SetFont(&m_font);
	if 	(m_strMsg != _T("")){
		pWnd->SetWindowText(m_strMsg);
	}

	HBITMAP hOkBitmap;
	hOkBitmap = ::LoadBitmap (AfxGetInstanceHandle (), MAKEINTRESOURCE(IDB_YES));
	CButton* pBtn = (CButton*)GetDlgItem(IDOK);
	pBtn->SetIcon (AfxGetApp ()->LoadIcon (IDI_ICON_YES));
	//pBtn->SetBitmap(hOkBitmap);
	hOkBitmap = ::LoadBitmap (AfxGetInstanceHandle (), MAKEINTRESOURCE(IDB_NO));
	pBtn = (CButton*)GetDlgItem(IDCANCEL);
	//pBtn->SetBitmap(hOkBitmap);
	pBtn->SetIcon (AfxGetApp ()->LoadIcon (IDI_ICON_NO));


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
