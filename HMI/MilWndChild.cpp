// MilWndChild.cpp : implementation file
//

#include "stdafx.h"
#include "HMI.h"
#include "MilWndChild.h"


// CMilWndChild

IMPLEMENT_DYNAMIC(CMilWndChild, CWnd)

CMilWndChild::CMilWndChild()
{
	m_ptCursor.x = 0;
	m_ptCursor.y = 0;
	m_bShowGradient = false;
}
CMilWndChild::CMilWndChild(const RECT& rect,CWnd* pParentWnd,bool ShowGradient)
{
	m_ptCursor.x = 0;
	m_ptCursor.y = 0;
	m_bShowGradient = ShowGradient;

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
    CreateEx (0, strWndClass, _T ("Mil Window"),WS_CHILD,
		rect, pParentWnd,NULL);

}


CMilWndChild::~CMilWndChild()
{
}


BEGIN_MESSAGE_MAP(CMilWndChild, CWnd)
	ON_WM_MOUSEMOVE()
	ON_WM_ERASEBKGND()
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CMilWndChild message handlers

void CMilWndChild::PostNcDestroy()
{
	//CWnd::PostNcDestroy();
	delete this;
}

void CMilWndChild::OnMouseMove(UINT nFlags, CPoint point)
{
	CWnd::OnMouseMove(nFlags, point);
	m_ptCursor = point;

	//GetParent()->PostMessageW(WM_MOUSEMOVE,0,0);
	//CFrameWnd* pWnd = GetParentFrame();
	//pWnd->OnMouseMove(nFlags,point);
	//GetParentFrame())->PostMessage(WM_MOUSEMOVE,point.x,point.y);
	//MAKEWPARAM()
	//TRACE("CMilWnd Rect, point X:%d Y:%d \n",point.x,point.y);
	//if (m_pParentWnd != NULL){
	//	m_pParentWnd->PostMessage(WM_MIL_WND_MOUSEMOVE,point.x,point.y);
	//}

}
BOOL CMilWndChild::OnEraseBkgnd(CDC* pDC)
{
	//return CWnd::OnEraseBkgnd(pDC);
	if (m_bShowGradient)
	{
		CRect rect;
		GetClientRect (&rect);
		DoGradientFill (pDC, &rect);
	}
    return TRUE;

}
void CMilWndChild::DoGradientFill(CDC *pDC, LPRECT pRect)
{
    CBrush* pBrush[64];
    for (int i=0; i<64; i++)
        pBrush[i] = new CBrush (RGB (0, 0, 255 - (i * 4)));

    int nWidth = pRect->right - pRect->left;
    int nHeight = pRect->bottom - pRect->top;
    CRect rect;

    for (int i=0; i<nHeight; i++) {
        rect.SetRect (0, i, nWidth, i + 1);
        pDC->FillRect (&rect, pBrush[(i * 63) / nHeight]);
    }

    for (int i=0; i<64; i++)
        delete pBrush[i];
}

int CMilWndChild::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rect;
	GetClientRect(&rect);

	if (m_bShowGradient)
		TRACE("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! Show gradient!!!!!!!!!!!!!!Client size: rect.x: %d rect.y: %d \n",rect.Width(),rect.Height());
	else
		TRACE("Mil Child window client size: rect.x: %d rect.y: %d \n",rect.Width(),rect.Height());

	return 0;
}

void CMilWndChild::OnLButtonDown(UINT nFlags, CPoint point)
{
	//CWnd::OnLButtonDown(nFlags, point);
	///TRACE("Click ... \n");
	//GetParent()->PostMessageW(WM_MOUSEMOVE,0,0);
	//CFrameWnd* pWnd = GetParentFrame();
	//pWnd->OnMouseMove(nFlags,point);
	//GetParentFrame())->PostMessage(WM_MOUSEMOVE,point.x,point.y);

	////CFrameWnd::OnLButtonDown(nFlags, point);
	//if (!g_bClipEnable)
	//{
	//	return;
	//}

	//switch (g_nClipImage)
	//{
	//case 1:
	//	MimClip(MilImage,MilImage, M_EQUAL,g_CurrentPixel, M_NULL, 250, M_NULL);
	//	break;
	//case 2:
	//	MimClip(MilImage,MilImage, M_EQUAL,g_CurrentPixel, M_NULL, 0, M_NULL);
	//	break;
	//case 3:
	//	MimBinarize(MilImage, MilImage, M_FIXED+M_LESS_OR_EQUAL, 128, M_NULL);
	//	break;
	//}

	//// Do the clip
	////g_nClipImage = 0;

}
