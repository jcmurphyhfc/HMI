
// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "HMI.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_MESSAGE (WM_USER_PMAC_SAVE, OnDoPmacSave)
	ON_MESSAGE (WM_USER_HMI_SAVE, OnDoHmiSave)
END_MESSAGE_MAP()

// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
}

CMainFrame::~CMainFrame()
{
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;

	// Window style
	//cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE		 | WS_THICKFRAME;
	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE;
		 
    // Size the window
#ifndef _DEBUG
	//cs.x = -1280;
	//cs.y = -1024;
	cs.x = 0;
	cs.y = 0;
	cs.cx = 1280;
	cs.cy = 1024;
#else
	//cs.x = -1280;
	//cs.y = -1024;
	cs.x = 0;
	cs.y = 0;
	cs.cx = 1280;
	cs.cy = 1024;
#endif


	return TRUE;
}

// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG

void CMainFrame::ToggelToolBar(void)
{
	ShowControlBar(&m_wndSysButtons,(m_wndSysButtons.GetStyle() & WS_VISIBLE)==0,FALSE);
}


BOOL CMainFrame::IsToolBarVisable(void)
{
	if ((m_wndSysButtons.GetStyle() & WS_VISIBLE) == 0) 
		return FALSE;
	else
		return TRUE;
}


// CMainFrame message handlers


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// Supervisor toolbar
	if (!m_wndSysButtons.Create(this,WS_CHILD | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_FIXED) ||
		!m_wndSysButtons.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	// Docking control
	EnableDocking(CBRS_ALIGN_ANY);

	// Format System tools
	//m_wndSysButtons.SetButtonStyle(2,m_wndSysButtons.GetButtonStyle(0) | TBBS_WRAPPED);
	//m_wndSysButtons.SetButtonStyle(5,m_wndSysButtons.GetButtonStyle(0) | TBBS_WRAPPED);
	//m_wndSysButtons.SetButtonStyle(8,m_wndSysButtons.GetButtonStyle(0) | TBBS_WRAPPED);
	//m_wndSysButtons.EnableDocking(0);

	// Format the Toolbar
	m_wndSysButtons.SetBarStyle(m_wndSysButtons.GetBarStyle() |CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_FIXED);
	m_wndSysButtons.SetButtonStyle(3,m_wndSysButtons.GetButtonStyle(0) | TBBS_WRAPPED);
	m_wndSysButtons.SetButtonStyle(7,m_wndSysButtons.GetButtonStyle(0) | TBBS_WRAPPED);
	m_wndSysButtons.SetButtonStyle(11,m_wndSysButtons.GetButtonStyle(0) | TBBS_WRAPPED);
	//m_wndSysButtons.SetButtonStyle(15,m_wndSysButtons.GetButtonStyle(0) | TBBS_WRAPPED);
	//m_wndSysButtons.SetButtonStyle(19,m_wndSysButtons.GetButtonStyle(0) | TBBS_WRAPPED);
	m_wndSysButtons.EnableDocking(0);


	CRect rectScreen;
	GetClientRect (&rectScreen);
    ClientToScreen (&rectScreen);
	FloatControlBar (&m_wndSysButtons,CPoint(rectScreen.right-240,rectScreen.bottom-420));

	// Remove the main menu
	SetMenu(NULL);

	// Remove the title bar
	ModifyStyle (WS_CAPTION, 0);
	
	// Display
	SetWindowPos (NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_DRAWFRAME);

	return 0;
}

LRESULT CMainFrame::OnDoPmacSave (WPARAM wParam, LPARAM lParam)
{
	//TRACE("CMainFrame::OnDoPmacSave\n");
	GetActiveView ()->SendMessage (WM_USER_PMAC_SAVE, 0, 0);
	return 0;
}	
LRESULT CMainFrame::OnDoHmiSave (WPARAM wParam, LPARAM lParam)
{
	GetActiveView ()->SendMessage (WM_USER_HMI_SAVE, 0, 0);
	return 0;
}	
