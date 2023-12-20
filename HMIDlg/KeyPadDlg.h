#pragma once

/////////////////////////////////////////////////////////////////////////////
// CKeyPadDlg dialog
/////////////////////////////////////////////////////////////////////////////

class CKeyPadDlg : public CDialog
{
	DECLARE_DYNAMIC(CKeyPadDlg)

//// Construction
public:
	CKeyPadDlg(CWnd* pParent = NULL);	// standard constructor

	// Dialog Data
	//{{AFX_DATA(CKeyPadDlg)
	enum { IDD = IDD_DLG_KEYPAD };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKeyPadDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	void UpdateDisplay (LPCTSTR pszDisplay);
	double SetValue(double dbValue);
	void SetRange(double nMin, double nMax);
	BOOL m_bPassWord;
	CString m_strPassWord;
	double m_dbValue;
	double m_dbIncrement;
	int m_nDecimalPlaces;
	CString m_strLabel;

protected:
	void DisplayXRegister();

    double m_dblMemory;
    CString m_strDisplay;
    CString m_strFormat;
    CRect m_rect;
    int m_cxChar;
    int m_cyChar;
	double m_dbMin;
	double m_dbMax;

//    BOOL m_bFixPending;
    BOOL m_bDecimalInString;
    BOOL m_bStackLiftEnabled;
    BOOL m_bNewX;
	BOOL m_bNegPending;

	HICON m_hIcon;
	HACCEL m_hAccel;

	// Generated message map functions
	//{{AFX_MSG(CKeyPadDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnChangeSign();
	afx_msg void OnClear();
	afx_msg void OnDecimal();
	afx_msg void OnDelete();
	afx_msg void OnIncrement();
	afx_msg void OnDecrement();
	afx_msg void OnNegValue();
	//}}AFX_MSG
	afx_msg void OnDigit(UINT nID);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};

