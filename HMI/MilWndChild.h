#pragma once


// CMilWndChild

class CMilWndChild : public CWnd
{
	DECLARE_DYNAMIC(CMilWndChild)

public:
	CMilWndChild();
	CMilWndChild(const RECT& rect,CWnd* pParentWnd,bool ShowGradient);
	virtual ~CMilWndChild();
public:
	CPoint m_ptCursor;
	bool m_bShowGradient;

protected:
	DECLARE_MESSAGE_MAP()
	virtual void PostNcDestroy();

public:
	void DoGradientFill(CDC *pDC, LPRECT pRect);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};