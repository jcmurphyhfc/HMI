// MilWnd.cpp : implementation file
//

#include "stdafx.h"
#include "HMI.h"
#include "MilWnd.h"
//#include "TimerMsg.h"

// CMilWnd

IMPLEMENT_DYNCREATE(CMilWnd, CFrameWnd)

CMilWnd::CMilWnd()
{
	m_dbZoomX = 1;
	m_dbZoomY = 1;
	m_dbOffset = 0;
	m_nCameraID = 0;
	m_bGrid = false;
	m_bContinue = false;
}

//CMilWnd::CMilWnd(const RECT& rect,CWnd* pParentWnd,int nToolBarID)
CMilWnd::CMilWnd(const RECT& rect,CWnd* pParentWnd,int nToolBarID,int IndicatorID)
{

	m_dbZoomX = 1;
	m_dbZoomY = 1;
	m_dbOffset = 0;
	m_nToolBarID = nToolBarID;
	ImageBuffer = M_NULL;
	m_nDisplayTime = 0;
	m_nIndicatorID = IndicatorID;

	//
    // Register a WNDCLASS.
    CString strWndClass = AfxRegisterWndClass (
        CS_DBLCLKS,                                     // Class style
        AfxGetApp ()->LoadStandardCursor (IDC_ARROW),   // Class cursor
        (HBRUSH) (COLOR_3DFACE + 1),                    // Background brush
        AfxGetApp ()->LoadStandardIcon (IDI_WINLOGO)    // Class icon
    );

	//
    // Create a window.
    CreateEx (0, strWndClass, _T ("Mil Window"),
		WS_DLGFRAME | WS_CHILD,
		rect, pParentWnd,NULL);


}

CMilWnd::~CMilWnd()
{
}


BEGIN_MESSAGE_MAP(CMilWnd, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_NCHITTEST()
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_POS, &OnUpdateCursorPosition)
END_MESSAGE_MAP()

//ON_UPDATE_COMMAND_UI(, &OnUpdateCursorPosition)
//ON_UPDATE_COMMAND_UI(ID_RESET_SYNC_COUNT, &CMilWnd::OnUpdateResetSyncCount)
//ON_COMMAND(ID_RESET_SYNC_COUNT, &CMilWnd::OnResetSyncCount)

//
static UINT indicators1[] =
{
	ID_INDICATOR_POS,       
	ID_INDICATOR_GRAY_VALUE,
	ID_INDICATOR_PERIOD,
	ID_INDICATOR_PERIOD_MIN,
	ID_INDICATOR_PERIOD_MAX,
	ID_INDICATOR_MAX_PROC,
	ID_INDICATOR_COM_TIME,
	ID_INDICATOR_COM_MAX,
};

//
static UINT indicators2[] =
{
	ID_INDICATOR_POS,       
	ID_INDICATOR_GRAY_VALUE,
	ID_INDICATOR_PERIOD,
	ID_INDICATOR_PERIOD_MIN,
	ID_INDICATOR_PERIOD_MAX,
	ID_INDICATOR_MAX_PROC,
};

// CMilWnd message handlers

BOOL CMilWnd::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style &= ~WS_DLGFRAME;

	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;

    // Position the window
	//cs.x = 0;
	//cs.y = 0;

	return TRUE;

}

int CMilWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{

	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;


	// Status bar
	if (m_nIndicatorID != NULL)
	{
		if (m_nIndicatorID == 1)
		{
			if (!m_wndStatusBar.Create(this) ||	!m_wndStatusBar.SetIndicators(indicators1,sizeof(indicators1)/sizeof(UINT)))
			{
				TRACE0("Failed to create status bar\n");
				return -1;      // fail to create
			}
		}
		else
		{
			if (!m_wndStatusBar.Create(this) ||	!m_wndStatusBar.SetIndicators(indicators2,sizeof(indicators2)/sizeof(UINT)))
			{
				TRACE0("Failed to create status bar\n");
				return -1;      // fail to create
			}
		}
	}

	// Main toolbar
	if (m_nToolBarID != NULL)
	{
		if (!m_wndToolBar.Create(this,WS_CHILD | CBRS_ALIGN_BOTTOM | CBRS_FLYBY | CBRS_SIZE_FIXED) ||
			!m_wndToolBar.LoadToolBar(m_nToolBarID))		
		{
			TRACE0("Failed to create toolbar\n");
			return -1;      // fail to create
		}
	}

	// Docking control
	EnableDocking(CBRS_ALIGN_ANY);
	if (m_nToolBarID != NULL)
	{
		m_wndToolBar.EnableDocking (0);
	}

	// Float position
	CRect rectScreen;
	GetClientRect (&rectScreen);
    ClientToScreen (&rectScreen);
	if (m_nToolBarID != NULL)
	{
		FloatControlBar (&m_wndToolBar,CPoint(rectScreen.left,rectScreen.bottom-18));
	}

	// View Toolbar
	//============================================================================================
	if (!m_wndViewToolBar.Create(this,WS_CHILD | CBRS_ALIGN_BOTTOM | CBRS_FLYBY | CBRS_SIZE_FIXED) ||
		!m_wndViewToolBar.LoadToolBar(IDR_MIL_TOOLBAR2))		
	{
		return -1;      // fail to create
	}
	EnableDocking(CBRS_ALIGN_ANY);
	m_wndViewToolBar.EnableDocking (0);
	GetClientRect (&rectScreen);
    ClientToScreen (&rectScreen);
	FloatControlBar (&m_wndViewToolBar,CPoint(rectScreen.left,rectScreen.bottom-130));
	//============================================================================================

	// Create and position the MIL window
	//============================================================================================
	RecalcLayout(TRUE);
	CRect rect,rectTool,rectStatus;
	GetClientRect(&rect);
	//============================================================================================

	//TRACE("Mil Child window BEFORE resize: rect.x: %d rect.y: %d WIDTH: %d HEIGHT: %d\n",rect.left,rect.top,rect.Width(),rect.Height());

	// Make Room for the Toolbar
	if (m_nToolBarID != NULL)
	{
		m_wndToolBar.GetWindowRect(&rectTool);
		m_wndStatusBar.GetWindowRect(&rectStatus);
		int nHeight = rect.Height() - rectStatus.Height() - 1;
		rect.bottom = rect.top + nHeight;
	}

	TRACE(".............Mil Child window AFTER resize: rect.x: %d rect.y: %d WIDTH: %d HEIGHT: %d\n",rect.left,rect.top,rect.Width(),rect.Height());

	m_pMilWnd = new CMilWndChild(rect,this,false);
	m_pMilWnd->ShowWindow (SW_SHOW);
    m_pMilWnd->UpdateWindow ();

	return 0;
}

LRESULT CMilWnd::OnNcHitTest(CPoint point)
{
    LRESULT nHitTest = CFrameWnd::OnNcHitTest (point);
	//if (m_bLockWindowPos)
//		nHitTest = HTCLIENT;
	return nHitTest;

}
void CMilWnd::OnUpdateCursorPosition(CCmdUI *pCmdUI)
{
	// 
	if (m_nToolBarID == NULL)
	{
		return;
	}

	MIL_INT SizeBit;
	unsigned char buff[3];
	CPoint point =  m_pMilWnd->m_ptCursor;
	CString string;

	CHMIApp* pApp = (CHMIApp*)AfxGetApp();
	string.Format (_T ("x:%d y:%d"),point.x,point.y);
    pCmdUI->SetText (string);

	// Buffer valid?
	if (ImageBuffer==NULL)
		return;

	// Get buffer size
	MbufInquire(ImageBuffer, M_SIZE_BIT,&SizeBit);
	if (SizeBit==8)
	{
		GetBuffValue8(point,buff);
		string.Format (_T ("Gray:%d"),buff[0]);
		m_wndStatusBar.SetPaneText(1,string);
	}


	if (m_nIndicatorID == 1)
	{
		// Period
		string.Format (_T ("Period: %d msec"),(int)pApp->m_mil.MilHook1.Period);
		m_wndStatusBar.SetPaneText(2,string);
		string.Format (_T ("Min: %d"),(int)pApp->m_mil.MilHook1.PeriodMin);
		m_wndStatusBar.SetPaneText(3,string);
		string.Format (_T ("Max: %d"),(int)pApp->m_mil.MilHook1.PeriodMax);
		m_wndStatusBar.SetPaneText(4,string);

		// Proc Time
		string.Format (_T ("Max Proc: %3.1f msec"),pApp->m_mil.MilHook1.MaxProcTime);
		m_wndStatusBar.SetPaneText(5,string);

		// COM time
		string.Format (_T ("Com: %d msec"),(int)pApp->m_mil.MilHook1.ComTime);
		m_wndStatusBar.SetPaneText(6,string);
		string.Format (_T ("Com Max: %d msec"),(int)pApp->m_mil.MilHook1.MaxComTime);
		m_wndStatusBar.SetPaneText(7,string);

	}
	else
	{
		// Period
		string.Format (_T ("Period: %d msec"),(int)pApp->m_mil.MilHook2.Period);
		m_wndStatusBar.SetPaneText(2,string);
		string.Format (_T ("Min: %d"),(int)pApp->m_mil.MilHook2.PeriodMin);
		m_wndStatusBar.SetPaneText(3,string);
		string.Format (_T ("Max: %d"),(int)pApp->m_mil.MilHook2.PeriodMax);
		m_wndStatusBar.SetPaneText(4,string);

		// Proc Time
		string.Format (_T ("Max Proc: %3.1f msec"),pApp->m_mil.MilHook2.MaxProcTime);
		m_wndStatusBar.SetPaneText(5,string);

	}

}
void CMilWnd::GetBuffValue8(CPoint point,unsigned char* buff)
{

	if (ImageBuffer==NULL)
	{
		return;	
	}

	MIL_INT SizeX;
	MIL_INT SizeY;
	MIL_INT SizeBit;

	// Get buffer size
	MbufInquire(ImageBuffer, M_SIZE_X,&SizeX);
	MbufInquire(ImageBuffer, M_SIZE_Y,&SizeY);
	MbufInquire(ImageBuffer, M_SIZE_BIT,&SizeBit);

	// Check limits
	if (point.x < 0)
		point.x = 0;
	if (point.x >= SizeX)
		point.x = (int)SizeX-1;
	if (point.y < 0)
		point.y = 0;
	if (point.y >= SizeY)
		point.y = (int)SizeY-1;

	// Get the RGB value or gray level
	//TRACE("X: %d ,y:%d \n",point.x,point.y);
	MbufGet2d(ImageBuffer,point.x,point.y,1,1,buff);

}

void CMilWnd::GetBuffValue16(MIL_ID nID,CPoint point,unsigned __int16* buff)
{
	////CALPApp* pApp = (CALPApp*)AfxGetApp();
	//if (nID==NULL)
	//{
	//	TRACE(" 16 bit nULL \n");
	//	return;	
	//}

	//MIL_INT SizeX;
	//MIL_INT SizeY;
	//MIL_INT SizeBit;

	//// Get buffer size
	//MbufInquire(nID, M_SIZE_X,&SizeX);
	//MbufInquire(nID, M_SIZE_Y,&SizeY);
	//MbufInquire(nID, M_SIZE_BIT,&SizeBit);

	//// Check limits
	//if (point.x < 0)
	//	point.x = 0;
	//if (point.x >= SizeX)
	//	point.x = (int)SizeX-1;
	//if (point.y < 0)
	//	point.y = 0;
	//if (point.y >= SizeY)
	//	point.y = (int)SizeY-1;

	//// Get the RGB value or gray level
	////TRACE("X: %d ,y:%d \n",point.x,point.y);
	//MbufGet2d(nID,point.x,point.y,1,1,buff);
	////TRACE("X:%d Y:%d Pixel:%d \n",point.x,point.y,buff[0]);

}


//---------------------------------------------------------------------------------------------------//
// CLaserWnd
//---------------------------------------------------------------------------------------------------//

IMPLEMENT_DYNCREATE(CLaserWnd, CFrameWnd)

CLaserWnd::CLaserWnd()
{
}

CLaserWnd::CLaserWnd(const RECT& rect,CWnd* pParentWnd)
{
	m_hwndChild = NULL;
	//
    // Register a WNDCLASS.
    CString strWndClass = AfxRegisterWndClass (
        CS_DBLCLKS,                                     // Class style
        AfxGetApp ()->LoadStandardCursor (IDC_ARROW),   // Class cursor
        (HBRUSH) (COLOR_3DFACE + 1),                    // Background brush
        AfxGetApp ()->LoadStandardIcon (IDI_WINLOGO)    // Class icon
    );

	//
    // Create a window.
    CreateEx (0, strWndClass, _T ("Laser Window"),
		WS_DLGFRAME | WS_CHILD,
		rect, pParentWnd,NULL);


}

CLaserWnd::~CLaserWnd()
{
}


BEGIN_MESSAGE_MAP(CLaserWnd, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_NCHITTEST()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_SETFOCUS()
END_MESSAGE_MAP()

//ON_UPDATE_COMMAND_UI(, &OnUpdateCursorPosition)
//ON_UPDATE_COMMAND_UI(ID_RESET_SYNC_COUNT, &CLaserWnd::OnUpdateResetSyncCount)
//ON_COMMAND(ID_RESET_SYNC_COUNT, &CLaserWnd::OnResetSyncCount)


// CLaserWnd message handlers

BOOL CLaserWnd::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style &= ~WS_DLGFRAME;

	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;

    // Position the window
	//cs.x = 0;
	//cs.y = 0;

	return TRUE;

}

int CLaserWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	::SetFocus(m_hwndChild);
	return 0;
}

LRESULT CLaserWnd::OnNcHitTest(CPoint point)
{
    LRESULT nHitTest = CFrameWnd::OnNcHitTest (point);
	//if (m_bLockWindowPos)
//		nHitTest = HTCLIENT;
	return nHitTest;
}
//

void CLaserWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	if (m_hwndChild)
	{
		//::SetFocus(m_hwndChild);
		TRACE("Painting the laser window \n");
	}
}
BOOL CLaserWnd::OnEraseBkgnd(CDC* pDC)
{
	//CWnd::OnEraseBkgnd(pDC);
	TRACE("OnEraseBkgnd the laser window \n");
	if (m_hwndChild)
	{
		//::SetFocus(m_hwndChild);
		TRACE("OnEraseBkgnd the laser window \n");
		::SetWindowPos(m_hwndChild,NULL,0,0,0,0,SWP_NOSIZE | SWP_DRAWFRAME | SWP_FRAMECHANGED | SWP_SHOWWINDOW);
	}
    return TRUE;
}


void CLaserWnd::OnSetFocus(CWnd* pOldWnd)
{
	CFrameWnd::OnSetFocus(pOldWnd);

	if (m_hwndChild)
	{
		//::SetFocus(m_hwndChild);
		//::SetWindowPos(m_hwndChild,NULL,0,0,800,600,SWP_DRAWFRAME);
		TRACE("Focus the laser window \n");
	}
}
