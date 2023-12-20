#pragma once

// CDlgHMIOpt dialog

class CDlgHMIOpt : public CDialog
{
	DECLARE_DYNAMIC(CDlgHMIOpt)

public:
	CDlgHMIOpt(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgHMIOpt();

// Dialog Data
	enum { IDD = IDD_HMI_OPTIONS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	int m_nPmacReset;
	int m_nPassword;
	int m_nMasterPassword;
	BOOL m_bBoostPriority;
	BOOL m_bFullReset;
	BOOL m_bEnableUser;
	BOOL m_bEnableMaster;
	afx_msg void OnBnClickedChangeUser();
	afx_msg void OnBnClickedChangeMaster();
	int m_nLaneID;
	//CString m_strIP;
	CString m_strName;
	DWORD m_dwServerIP;
	int m_PmacID;
};