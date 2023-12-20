// DlgHMIOpt.cpp : implementation file
//

#include "stdafx.h"
#include "HMIDlg.h"
#include "DlgHMIOpt.h"
//#include "afxdialogex.h"
#include "HMIDlgApi.h"


// CDlgHMIOpt dialog

IMPLEMENT_DYNAMIC(CDlgHMIOpt, CDialog)

CDlgHMIOpt::CDlgHMIOpt(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgHMIOpt::IDD, pParent)
	, m_bBoostPriority(FALSE)
	, m_bFullReset(FALSE)
	, m_bEnableUser(FALSE)
	, m_bEnableMaster(FALSE)
	, m_nLaneID(1)
	, m_strName(_T(""))
	, m_dwServerIP(0)
	, m_nPmacReset(TRUE)
	, m_PmacID(3)
{

	
}

CDlgHMIOpt::~CDlgHMIOpt()
{
}

void CDlgHMIOpt::DoDataExchange(CDataExchange* pDX)
{
	//m_nPmacReset = m_bFullReset;
	CDialog::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_LOCK_POS, m_bBoostPriority);
	DDX_Check(pDX, IDC_PMAC_RESET, m_nPmacReset);
	DDX_Check(pDX, IDC_LOCK_TOPMOST, m_bFullReset);
	DDX_Check(pDX, IDC_ENABLE_USER, m_bEnableUser);
	DDX_Check(pDX, IDC_ENABLE_MASTER, m_bEnableMaster);
	//DDX_Text(pDX, IDC_EDIT1, m_strIP);
	//DDV_MaxChars(pDX, m_strIP, 15);
	DDX_Text(pDX, IDC_EDIT1, m_nLaneID);
	DDV_MinMaxInt(pDX, m_nLaneID, 1, 4);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	DDV_MaxChars(pDX, m_strName, 256);
	DDX_IPAddress(pDX, IDC_IPADDRESS2, m_dwServerIP);
	DDX_Text(pDX, IDC_EDIT2, m_PmacID);
	DDV_MinMaxInt(pDX, m_PmacID, 0, 3);
}


BEGIN_MESSAGE_MAP(CDlgHMIOpt, CDialog)
	ON_BN_CLICKED(IDC_CHANGE_USER, &CDlgHMIOpt::OnBnClickedChangeUser)
	ON_BN_CLICKED(IDC_CHANGE_MASTER, &CDlgHMIOpt::OnBnClickedChangeMaster)
END_MESSAGE_MAP()


// CDlgHMIOpt message handlers

void CDlgHMIOpt::OnBnClickedChangeUser()
{

	KEYPADDATA data;
	data.dbIncrement = 0;
	data.dbMin = 0;
	data.dbValue = 0;
	data.dbMax = 0;
	data.lpTitle = _T("Enter New User Code");
	data.nDecimalPlaces = 0;
	data.bPassWord = true;
	if (GetNumDlg(&data)) {			
		
		int nNewCode =  (int)data.dbValue;
		data.lpTitle = _T("Verify User Code");
		data.dbValue = 0;
		if (GetNumDlg(&data)) {
			if (nNewCode ==  (int)data.dbValue){
				OkDlg(_T("Password Changed!"),false);
				m_nPassword = nNewCode;
			}
			else{
				OkDlg(_T("Password not Changed!"),true);
			}
		}

	}

}

void CDlgHMIOpt::OnBnClickedChangeMaster()
{
	KEYPADDATA data;
	data.dbIncrement = 0;
	data.dbMin = 0;
	data.dbValue = 0;
	data.dbMax = 0;
	data.lpTitle = _T("Enter New Master Code");
	data.nDecimalPlaces = 0;
	data.bPassWord = true;
	if (GetNumDlg(&data)) {			
		
		int nNewCode =  (int)data.dbValue;
		data.lpTitle = _T("Verify Master Code");
		data.dbValue = 0;
		if (GetNumDlg(&data)) {
			if (nNewCode ==  (int)data.dbValue){
				OkDlg(_T("Password Changed!"),false);
				m_nMasterPassword = nNewCode;
			}
			else{
				OkDlg(_T("Password not Changed!"),true);
			}
		}

	}

}
