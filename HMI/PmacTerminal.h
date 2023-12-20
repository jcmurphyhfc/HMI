#pragma once
#include "slice_count.h"
#include "afxwin.h"


// CPmacTerminal dialog
class CMyEdit : public CEdit
{
protected:
    afx_msg void OnChar (UINT nChar, UINT nRepCnt, UINT nFlags);
    DECLARE_MESSAGE_MAP ()
};

class CPmacTerminal : public CDialog
{
	DECLARE_DYNAMIC(CPmacTerminal)

public:
	CPmacTerminal(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPmacTerminal();
	CWnd**	m_ppBackPtr;		// caller's back pointer to me
	int		m_nVarType;
	char    OnGetVarType();
	CPmac*  m_pmac;
	bool    m_bUpdateComplete;
	CBrush  m_brBrush;
	HWND m_hOSKWnd;
	CFont	m_fontLarge;


	// Methods
	void UpdateTerminal();
	void GetCmd(int nID);

// Dialog Data
	enum { IDD = IDD_TERMINAL_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	virtual void PostNcDestroy();
public:
	afx_msg void OnBnClickedClose();
	DECLARE_EVENTSINK_MAP()
	void ClickGditeditctrlVarnum();
	void ClickGditeditctrlVarValue();
	CGDITedit m_ctlVarNum;
	CGDITedit m_ctlVarValue;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedSavePmacSettings();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CGDITedit m_ctlVarPrecision;
	void ClickGditeditctrlVarPresision();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual void OnOK();
	afx_msg void OnBnClickedSend1();
	afx_msg void OnBnClickedSend2();
	afx_msg void OnBnClickedPmacCmd();
	afx_msg void OnBnClickedKeyboard();
	afx_msg void OnBnClickedSaveHmiSettings();
	CMyEdit m_ctlEdit;
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
};