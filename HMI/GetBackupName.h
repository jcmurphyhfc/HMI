#pragma once
#include "afxwin.h"


// CGetBackupName dialog

class CGetBackupName : public CDialog
{
	DECLARE_DYNAMIC(CGetBackupName)

public:
	CGetBackupName(CWnd* pParent = NULL);   // standard constructor
	virtual ~CGetBackupName();

// Dialog Data
	enum { IDD = IDD_SET_FILENAME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CFont m_fontLarge;
	int m_NumberOfNames;
	CListBox m_ctlListBox;
	CString m_strName;
	CStringArray m_strNameArray;
	int m_Index;
	virtual BOOL OnInitDialog();
	afx_msg void OnLbnSelchangeList1();
	afx_msg void OnLbnDblclkList1();
	afx_msg void OnBnClickedButtonUp();
	afx_msg void OnBnClickedButtonDn();
};
