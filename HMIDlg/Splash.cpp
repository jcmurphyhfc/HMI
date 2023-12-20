////////////////////////////////////////////////////////////////
// Microsoft Systems Journal -- October 1999
// If this code works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
// Compiles with Visual C++ 6.0, runs on Windows 98 and probably NT too.
//
#include "stdafx.h"
#include "Splash.h"
#include "HMIDlg.h"
#include <math.h>

//#include "cmdline.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CSplashWnd, CWnd)
BEGIN_MESSAGE_MAP(CSplashWnd, CWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_TIMER()
END_MESSAGE_MAP()

////////////////////////////////////////////////////////////////
// CSplashWnd : the splash window

CSplashWnd::CSplashWnd()
{
	m_pbSplash = NULL;
}

CSplashWnd::~CSplashWnd()
{
}

//////////////////
// Create splash window: load bitmap and create the window
//
BOOL CSplashWnd::Create(CWinApp* pApp,bool* pbSplash, UINT duration, WORD flags)
{
    //CTime time = CTime::GetCurrentTime ();
    //m_nStartSecond = time.GetSecond();
	//m_nTwelfthSecond = 0;
	m_nPrevSecond = 0;
	m_dwOldTime = GetTickCount();
	m_pApp = pApp;
	m_pbSplash = pbSplash;

	// Code for ordinary bitmap (assumes m_bitmap is a CBitmap)
	if (!m_bitmap.LoadBitmap(IDB_HORMEL_SPLASH))
		return FALSE;
	BITMAP bm;
	m_bitmap.GetBitmap(&bm);
	CSize sz(bm.bmWidth, bm.bmHeight);

	m_bitmapFace[0].LoadBitmap(IDB_CLOCK_FACE);
	m_bitmapFace[1].LoadBitmap(IDB_CLOCK_FACE2);
	m_bitmapFace[2].LoadBitmap(IDB_CLOCK_FACE3);
	m_bitmapFace[3].LoadBitmap(IDB_CLOCK_FACE4);
	m_bitmapFace[4].LoadBitmap(IDB_CLOCK_FACE5);
	m_bitmapFace[5].LoadBitmap(IDB_CLOCK_FACE6);
	m_bitmapFace[6].LoadBitmap(IDB_CLOCK_FACE7);
	m_bitmapFace[7].LoadBitmap(IDB_CLOCK_FACE8);

	m_duration = duration;
	m_flags = flags;
	return CreateEx(0,
		AfxRegisterWndClass(0, AfxGetApp()->LoadStandardCursor(IDC_ARROW)),
		NULL,
		WS_POPUP | WS_VISIBLE,
		0, 0, sz.cx, sz.cy,
		NULL, // parent wnd
		NULL);

}

//////////////////
// Splash window created: center it, move to foreground and set a timer
//
int CSplashWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	CenterWindow();
	UpdateWindow();
	SetForegroundWindow();
	//if (m_duration!=-1)
	//	SetTimer(1, m_duration, NULL);
	SetTimer(1, 100, NULL);

	return 0;
}

//////////////////
// The window has been destroyed: put main app in foreground
// and post a message to quit this thread.
//
void CSplashWnd::PostNcDestroy()
{
	//CWinApp* pApp = AfxGetApp();
	CWnd* pMainWnd = m_pApp->m_pMainWnd;
	if (IsWindow(pMainWnd->GetSafeHwnd()))
		::SetForegroundWindow(pMainWnd->GetSafeHwnd());
	delete this;

}

//////////////////
// Draw the bitmap.
//
void CSplashWnd::OnPaint()
{
	CPaintDC dc(this);

	// Code for ordinary bitmap:
	CDC dcImage;
	if (!dcImage.CreateCompatibleDC(&dc))
		return;
	BITMAP bm;
	m_bitmap.GetBitmap(&bm);

	// Paint the image.
	CBitmap* pOldBitmap = dcImage.SelectObject(&m_bitmap);
	dc.BitBlt(0, 0, bm.bmWidth, bm.bmHeight, &dcImage, 0, 0, SRCCOPY);
	dcImage.SelectObject(pOldBitmap);


}

//////////////////
// Timer expired: kill myself--unless the app has
// not created a main window yet.
//
void CSplashWnd::OnTimer(UINT nIDEvent)
{
	double dbTwelfSecond;
	DWORD dwTimeElapsed = GetTickCount() - m_dwOldTime;
	dbTwelfSecond = (double)dwTimeElapsed/83.3333;
	//TRACE("Time:%f\n",dbTwelfSecond);

    CClientDC dc (this);

	// 
	// Draw the clock face
	//
	BITMAP bm;
    m_bitmapFace[0].GetBitmap (&bm);
    CPoint org (0, 0);
    CDC dcMem;
    dcMem.CreateCompatibleDC (&dc);
    CBitmap* pOldBitmap = dcMem.SelectObject (&m_bitmapFace[0]);
	::TransparentBlt(dc.m_hDC,322, 22, bm.bmWidth,
		bm.bmHeight,dcMem.m_hDC,org.x, org.y,
		bm.bmWidth, bm.bmHeight,RGB(255,0,255));
    dcMem.SelectObject (pOldBitmap);

	//
	// Draw the twelfth second hand.
	//
	int nTwelfthSecond = (int)(dbTwelfSecond*5);
	dc.SetMapMode (MM_ISOTROPIC);
    dc.SetWindowExt (1000, 1000);
    dc.SetViewportExt (bm.bmWidth, -bm.bmHeight);
    dc.SetViewportOrg (372,72);
    DrawSecondHand (&dc, 400, 8, nTwelfthSecond * 6, RGB (0, 0, 0));

	//
	// Get the number of seconds elapsed
	//
    int nSeconds = dwTimeElapsed/1000;
    DrawSecondHand (&dc, 350, 8, nSeconds*6*5, RGB (255, 0, 0));


	//CWinApp* pApp = AfxGetApp();
	CWnd* pMainWnd = m_pApp->m_pMainWnd;
	if ((m_flags & CSplash::NoWaitForMainWnd) || IsWindow(pMainWnd->GetSafeHwnd())){

		
		// have main window: OK to die
		if ( !(m_flags & CSplash::KeepSplashing) && !*m_pbSplash){
		   SendMessage(WM_CLOSE);
		}
	}
	//else{
		// no main window: keep splashing
		//SetTimer(1,100,NULL);
		//TRACE("No main window!!!!!!\n");
	//}

/****************
    CClientDC dc (this);

	// 
	// Draw the clock face
	//
	BITMAP bm;
    m_bitmapFace[0].GetBitmap (&bm);
    CPoint org (0, 0);
    CDC dcMem;
    CDC dcMem2;
    dcMem.CreateCompatibleDC (&dc);
    dcMem2.CreateCompatibleDC (&dc);
    CBitmap* pOldBitmap = dcMem.SelectObject (&m_bitmapFace[0]);
	::TransparentBlt(dc.m_hDC,322, 22, bm.bmWidth,
		bm.bmHeight,dcMem.m_hDC,org.x, org.y,
		bm.bmWidth, bm.bmHeight,RGB(255,0,255));
    dcMem.SelectObject (pOldBitmap);

	CBitmap bitmapTemp;
    bitmapTemp.CreateCompatibleBitmap (&dcMem, bm.bmWidth, bm.bmHeight);
    CBitmap* pOldBitmapTemp = dcMem2.SelectObject (&bitmapTemp);

	// Copy the blank clock face to a memory dc
	dcMem2.BitBlt(0, 0, bm.bmWidth, bm.bmHeight, &dcMem, 0, 0, SRCCOPY);

	//
	// Draw the twelfth second hand.
	//
	m_nTwelfthSecond+=5;

	int Mode = dc.GetMapMode();
	CPoint point = dc.GetWindowExt();
	TRACE("WindowExt x:%d y:%d\n",point.x,point.y);
	point = dc.GetViewportExt();
	TRACE("ViewportExt x:%d y:%d\n",point.x,point.y);
	point = dc.GetViewportOrg();
	TRACE("x:%d y:%d\n",point.x,point.y);

	dc.SetMapMode (MM_ISOTROPIC);
    dc.SetWindowExt (1000, 1000);
    dc.SetViewportExt (bm.bmWidth, -bm.bmHeight);
    dc.SetViewportOrg (372,72);

	dcMem2.SetMapMode (MM_ISOTROPIC);
    dcMem2.SetWindowExt (1000, 1000);
    dcMem2.SetViewportExt (bm.bmWidth, -bm.bmHeight);
    dcMem2.SetViewportOrg (0,0);

	//point = dcMem2.GetWindowExt();
	//TRACE("WindowExt x:%d y:%d\n",point.x,point.y);
	//point = dcMem2.GetViewportExt();
	//TRACE("ViewportExt x:%d y:%d\n",point.x,point.y);
	//point = dcMem2.GetViewportOrg();
	//TRACE("x:%d y:%d\n",point.x,point.y);
    DrawSecondHand (&dcMem2, 400, 8, m_nTwelfthSecond * 6, RGB (0, 0, 0));

	dc.SetMapMode (Mode);
    dc.SetWindowExt (1, 1);
    dc.SetViewportExt (1,1);
    dc.SetViewportOrg (0,0);
	

	::TransparentBlt(dc.m_hDC,322, 22, bm.bmWidth,
		bm.bmHeight,dcMem2.m_hDC,org.x, org.y,
		bm.bmWidth, bm.bmHeight,RGB(255,0,255));


	dcMem2.SelectObject (pOldBitmapTemp);
    dcMem.SelectObject (pOldBitmap);


****************/
}

//
// Draw the second hand
////////////////////////////////////////////////////////////
void CSplashWnd::DrawSecondHand (CDC* pDC, int nLength, int nScale,    int nDegrees, COLORREF clrColor)
{
    CPoint point[2];
    double nRadians = (double) nDegrees * 0.017453292;

    point[0].x = (int) (nLength * sin (nRadians));
    point[0].y = (int) (nLength * cos (nRadians));

    point[1].x = -point[0].x / nScale;
    point[1].y = -point[0].y / nScale;

	//TRACE("Point[0].x:%d Point[0].y:%d \nPoint[1].x:%d Point[1].y:%d \n",point[0].x,point[0].y,point[1].x,point[1].y);

    CPen pen (PS_SOLID, 0, clrColor);
    CPen* pOldPen = pDC->SelectObject (&pen);

    pDC->MoveTo (point[0]);
    pDC->LineTo (point[1]);

    pDC->SelectObject (pOldPen);
}

//////////////////
// Before translating keystroke or mouse: die
//
BOOL CSplashWnd::PreTranslateMessage(MSG* pMsg)
{
	if (m_flags & CSplash::KillOnClick) {
		UINT msg = pMsg->message;
		if (msg == WM_KEYDOWN ||
			 msg == WM_SYSKEYDOWN ||
			 msg == WM_LBUTTONDOWN ||
			 msg == WM_RBUTTONDOWN ||
			 msg == WM_MBUTTONDOWN)
		{
			PostMessage(WM_CLOSE); // post don't send, to let current msg process
			return TRUE;			  // (eat current message)
		}
	}
	return CWnd::PreTranslateMessage(pMsg);
}

////////////////////////////////////////////////////////////////
// CSplash, a thread object

IMPLEMENT_DYNAMIC(CSplash, CWinThread)

//////////////////
// Create a new splash thread
//
CSplash::CSplash(CWinApp* pApp,UINT duration, WORD flags,bool* pbSplash)
{
	//m_ppBackPtr = ppBackPtr;
	//m_nIDRes = nIDRes;
	m_pApp = pApp;
	m_pbSplash = pbSplash;
	m_duration = duration;
	m_flags = flags;
	CreateThread();
}

/////////////////
// Destruction: Set caller's pointer to NULL, so he knows I'm gone.
//
CSplash::~CSplash()
{
//	if (m_ppBackPtr)
//		*m_ppBackPtr = NULL;
}

//////////////////
// Thread initialization.
// Returns TRUE to keep running, otherwise FALSE
// if I determine I'm not supposed to run the splash
//
BOOL CSplash::InitInstance()
{
	// Check for -nologo switch
	CWinApp* pApp = AfxGetApp();
	ASSERT(pApp);

	// Look for -nologo switch, or any others that MFC thinks should
	// prohibit a splash screen (such as OLE embedding, etc.)
	//
	//if (!(m_flags & IgnoreCmdLine)) {
	//	CCommandLineInfoEx cmdinfo;
	//	pApp->ParseCommandLine(cmdinfo);
	//	if (!cmdinfo.m_bShowSplash || cmdinfo.GetOption(_T("nologo")))
	//		return FALSE;
	//}

	if (!AfxOleGetUserCtrl())  // running without UI: to be safe
		return FALSE;

	// Create the splash window
	m_pMainWnd = OnCreateSplashWnd(m_pApp,m_pbSplash, m_duration, m_flags);
	return m_pMainWnd != NULL;
}

//////////////////
// Create the splash window. This is virtual so you can override to create
// somet other kind of window if you like. 
//
CWnd* CSplash::OnCreateSplashWnd(CWinApp* pApp,bool* pbSplash, UINT duration, WORD flags)
{
	CSplashWnd *pSplashWnd = new CSplashWnd;
	if (pSplashWnd)
		pSplashWnd->Create(pApp,pbSplash, duration, flags);
	return pSplashWnd;
}


//////////////////
// Kill the splash window. Could set a CEvent to
// terminate thread, but easier to post a close message.
//
void CSplash::Kill()
{
	if (m_pMainWnd)
		m_pMainWnd->PostMessage(WM_CLOSE);
}
