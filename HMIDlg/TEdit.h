#if !defined(AFX_TEDIT_H__B9550587_8B06_4E6B_AAA6_E940B183F06B__INCLUDED_)
#define AFX_TEDIT_H__B9550587_8B06_4E6B_AAA6_E940B183F06B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTEdit window
//#include "KeyPad.h"

class CTEdit : public CEdit
{
// Construction
public:
	CTEdit();

// Attributes
public:
	BOOL bNoChange;
	COLORREF m_clrText;
	COLORREF m_clrBack;
    CBrush m_brBkgnd;
	double m_dbValue;
	double m_dbIncrement;
	CString m_strLabel;
	CString m_strUnits;
	double m_dbMin;
	double m_dbMax;
	int m_nWidth;
	int m_nPrecision;
	double* m_pdbValue;
	int* m_pnValue;

// Operations
public:
	void SetBkColor(COLORREF);
	void SetTextColor(COLORREF);
	double GetValue();
	void SetValue(double dbValue);
	void SetValuePtr(double* pdbValue);
	void SetValuePtr(int* pnValue);
	void SetRange(double dbMin,double dbMax);


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTEdit)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL m_bEnableEdit;
	virtual ~CTEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CTEdit)
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
public:
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEDIT_H__B9550587_8B06_4E6B_AAA6_E940B183F06B__INCLUDED_)
