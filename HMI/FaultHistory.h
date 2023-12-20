#pragma once
#include "afxwin.h"

#include "History.h"


// CFaultHistory dialog

class CFaultHistory : public CDialog
{
	DECLARE_DYNAMIC(CFaultHistory)

public:
	CFaultHistory(CWnd* pParent = NULL);   // standard constructor
	virtual ~CFaultHistory();
	CHistory*     m_pHistory;


// Dialog Data
	enum { IDD = IDD_FAULT_HISTORY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	//CEdit m_ctlEditErrors;
	CString m_strErrors;
	afx_msg void OnBnClickedClear();
	virtual BOOL OnInitDialog();
};
