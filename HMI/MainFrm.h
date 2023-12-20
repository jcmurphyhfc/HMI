
// MainFrm.h : interface of the CMainFrame class
//

#pragma once

class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:
	CToolBar    m_wndSysButtons;

// Operations
public:
	void ToggelToolBar(void);
	BOOL IsToolBarVisable(void);


// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// User messages
	afx_msg LRESULT OnDoPmacSave (WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnDoHmiSave (WPARAM wParam, LPARAM lParam);

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};


