#pragma once
#include "afxcmn.h"


// CDlgWait dialog

class CDlgWait : public CDialog
{
	DECLARE_DYNAMIC(CDlgWait)

public:
	CDlgWait(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgWait();
	int m_nTimer;
	int m_nPos;

	afx_msg LRESULT OnWaitUpdateTimer (WPARAM wParam, LPARAM lParam);

// Dialog Data
	enum { IDD = IDD_WAIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CProgressCtrl m_ctlWait;
	virtual BOOL DestroyWindow();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL OnInitDialog();
};
