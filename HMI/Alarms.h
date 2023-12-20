#pragma once
#include "gdi_buttonxl.h"


// CAlarms dialog

class CAlarms : public CDialog
{
	DECLARE_DYNAMIC(CAlarms)

public:
	CAlarms(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAlarms();
	CWnd**	m_ppBackPtr;		// caller's back pointer to me
	CWnd*	m_pWnd;		        // caller's message target
	int     m_nID;
	CString m_strMsg;

// Dialog Data
	enum { IDD = IDD_ALARMS_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	virtual void PostNcDestroy();
	virtual void OnOK();
	virtual void OnCancel();
public:
	CGdi_ButtonXL m_ctlLight;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();
};
