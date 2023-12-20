// Settings.h : header file
//
#pragma once

#include "HMIDlgApi.h"
#include "VisionSettings.h"
#include "VisionSplit.h"
#include "AlignLUT.h"
#include "TrimLUT.h"
#include "VisSetDelay.h"


/////////////////////////////////////////////////////////////////////////////
// CSettings
#define ID_SAVE_BUTTON		101
#define ID_RESTORE          102
#define ID_NEXT_PAGE		103
#define ID_PREV_PAGE		104

#define ID_LOAD_MASTER      105
#define ID_LOAD_USER		106
#define ID_SAVE_USER		107

class CSettings : public CPropertySheet
{
	DECLARE_DYNAMIC(CSettings)

// Construction
public:
	CSettings(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CSettings(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:
	ALLSETTINGS m_BackUpParams;
	ALLSETTINGS* m_pParams;

	int m_nPage;
	int m_nTotalPage;
	COLORREF m_clrText;
	COLORREF m_clrBack;
	CWnd* m_pWndParent;
	CWnd**	m_ppBackPtr;		// caller's back pointer to me
	CButton m_btnApplyButton;
	CButton m_btnSaveButton;
	CButton m_btnRestoreButton;
	CButton m_btnCloseButton;
	CButton m_btnNextPageButton;
	CButton m_btnPrevPageButton;
	CButton m_btnLoadMaster;
	CButton m_btnLoadUser;
	CButton m_btnSaveUser;
	CFont m_font;	
	CFont m_fontSmall;	
	CVisionSettings m_Page1;
	//CVisSetDelay m_Page2;
	CVisionSplit m_Page2;
	CAlignLUT m_Page3;
	//CTrimLUT m_Page4;

	CFont m_Tabfont;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSettings)
	public:
	virtual BOOL OnInitDialog();
	protected:
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
public:
	void LoadBackUp();
	void SaveBackUp();
	void SetParams();
	void LoadParams();
	virtual ~CSettings();

	// Generated message map functions
protected:
	//{{AFX_MSG(CSettings)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	afx_msg LRESULT OnChange (WPARAM wParam, LPARAM lParam);
	afx_msg void OnApply ();
	afx_msg	void OnSaveButton();
	afx_msg	void OnRestore();
	afx_msg void OnNextPage ();
	afx_msg void OnPrevPage ();
	afx_msg void OnClose ();
	afx_msg void OnLoadMaster ();
	afx_msg void OnLoadUser ();
	afx_msg void OnSaveUser ();
	afx_msg LRESULT OnNcHitTest(CPoint point);

	DECLARE_MESSAGE_MAP()
public:
	void Initialize(CWnd* pParentWnd,ALLSETTINGS* pParams);
public:
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);

};

/////////////////////////////////////////////////////////////////////////////
