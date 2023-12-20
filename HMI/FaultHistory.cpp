// FaultHistory.cpp : implementation file
//

#include "stdafx.h"
#include "HMI.h"
#include "FaultHistory.h"


// CFaultHistory dialog

IMPLEMENT_DYNAMIC(CFaultHistory, CDialog)

CFaultHistory::CFaultHistory(CWnd* pParent /*=NULL*/)
	: CDialog(CFaultHistory::IDD, pParent)
	, m_strErrors(_T(""))
{
	m_pHistory = NULL;
}

CFaultHistory::~CFaultHistory()
{
}

void CFaultHistory::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_EDIT_ERRORS, m_ctlEditErrors);
	DDX_Text(pDX, IDC_EDIT_ERRORS, m_strErrors);
	DDV_MaxChars(pDX, m_strErrors, 511000);
}


BEGIN_MESSAGE_MAP(CFaultHistory, CDialog)
	ON_BN_CLICKED(IDC_CLEAR, &CFaultHistory::OnBnClickedClear)
END_MESSAGE_MAP()


// CFaultHistory message handlers


void CFaultHistory::OnBnClickedClear()
{	
	if (m_pHistory != NULL)
	{
		m_pHistory->ClearStrings();
		CWnd* pWnd = GetDlgItem(IDC_EDIT_ERRORS);
		pWnd->SetWindowText(_T(""));
	}
}


BOOL CFaultHistory::OnInitDialog()
{
	CDialog::OnInitDialog();
	CWnd* pWnd = GetDlgItem(IDC_EDIT_ERRORS);

	if (m_pHistory != NULL)
	{
		//m_pHistory->ClearStrings();
		//pWnd = GetDlgItem(IDC_EDIT_ERRORS);
		m_pHistory->ShowStrings(pWnd);
		//pWnd->SetWindowText(_T(""));
	}

	//CEdit *edit = static_cast<CEdit*>(pWnd); //dynamic_cast does not work
	//CEdit *edit = (CEdit*)pWnd;                //dynamic_cast does not work
    //UINT limit = edit->GetLimitText();         //The current text limit, in bytes, for this CEdit object.
	//CString str;
	//str.Format(_T("Text limit bytes %d"),limit);
	//AfxMessageBox(str);

 //   UINT limit = edit->GetLimitText(); //The current text limit, in bytes, for this CEdit object.    //value returned: 30000 (0x7530)
//    edit->SetLimitText(0);
//    limit = edit->GetLimitText();
//    //value returned: 2147483646 (0x7FFFFFFE) 


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
