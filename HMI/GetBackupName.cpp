// GetBackupName.cpp : implementation file
//

#include "stdafx.h"
#include "HMI.h"
#include "GetBackupName.h"
//#include "afxdialogex.h"

// CGetBackupName dialog

IMPLEMENT_DYNAMIC(CGetBackupName, CDialog)

CGetBackupName::CGetBackupName(CWnd* pParent /*=NULL*/)
	: CDialog(CGetBackupName::IDD, pParent)
	, m_strName(_T("")), m_NumberOfNames(0)
{
	m_NumberOfNames = 0;
	m_Index = 0;
}

CGetBackupName::~CGetBackupName()
{
}

void CGetBackupName::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ctlListBox);
	//DDX_LBString(pDX, IDC_LIST1, m_strName);
	//DDV_MaxChars(pDX, m_strName, 256);
}


BEGIN_MESSAGE_MAP(CGetBackupName, CDialog)
	ON_LBN_SELCHANGE(IDC_LIST1, &CGetBackupName::OnLbnSelchangeList1)
	ON_LBN_DBLCLK(IDC_LIST1, &CGetBackupName::OnLbnDblclkList1)
	ON_BN_CLICKED(IDC_BUTTON_UP, &CGetBackupName::OnBnClickedButtonUp)
	ON_BN_CLICKED(IDC_BUTTON_DN, &CGetBackupName::OnBnClickedButtonDn)
END_MESSAGE_MAP()


// CGetBackupName message handlers


BOOL CGetBackupName::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_fontLarge.CreatePointFont (270, _T ("Microsoft Sans Serif"));
	m_ctlListBox.SetFont(&m_fontLarge);

	//m_strNameArray.FreeExtra();
	//CString str;
	//str.Format(_T("Size %d"),m_strNameArray.GetSize());

	for (int i=0; i<m_NumberOfNames;i++)
	{
		m_ctlListBox.AddString(m_strNameArray[i]);
	}
	m_ctlListBox.SetCurSel(m_Index);
	m_ctlListBox.GetText(m_Index,	m_strName);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CGetBackupName::OnLbnSelchangeList1()
{

	m_Index = m_ctlListBox.GetCurSel();
	m_ctlListBox.GetText(m_Index,	m_strName);
	TRACE("CHANGE LIST \n");
}

void CGetBackupName::OnLbnDblclkList1()
{
//	int Index = m_ctlListBox.GetCurSel();
//	m_ctlListBox.GetText(Index,	m_strName);
}


void CGetBackupName::OnBnClickedButtonUp()
{
	m_Index--;
	if (m_Index < 0) m_Index=0;
	m_ctlListBox.SetCurSel(m_Index);
	OnLbnSelchangeList1();
}


void CGetBackupName::OnBnClickedButtonDn()
{
	m_Index++;
	if (m_Index >= m_NumberOfNames) m_Index=m_NumberOfNames-1;
	m_ctlListBox.SetCurSel(m_Index);
	OnLbnSelchangeList1();
}
