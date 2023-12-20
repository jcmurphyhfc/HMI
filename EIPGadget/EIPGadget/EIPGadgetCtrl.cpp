// EIPGadgetCtrl.cpp : Implementation of the CEIPGadgetCtrl ActiveX Control class.

#include "stdafx.h"
#include "EIPGadget.h"
#include "EIPGadgetCtrl.h"
#include "EIPGadgetPropPage.h"
#include "afxdialogex.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif



IMPLEMENT_DYNCREATE(CEIPGadgetCtrl, COleControl)



// Message map

BEGIN_MESSAGE_MAP(CEIPGadgetCtrl, COleControl)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()



// Dispatch map

BEGIN_DISPATCH_MAP(CEIPGadgetCtrl, COleControl)
	DISP_FUNCTION_ID(CEIPGadgetCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
	DISP_PROPERTY_NOTIFY_ID(CEIPGadgetCtrl, "DoGradientFill", dispidDoGradientFill, m_DoGradientFill, OnDoGradientFillChanged, VT_I2)
	DISP_PROPERTY_NOTIFY_ID(CEIPGadgetCtrl, "Title", dispidTitle, m_Title, OnTitleChanged, VT_BSTR)
	DISP_PROPERTY_NOTIFY_ID(CEIPGadgetCtrl, "TitleFontSize", dispidTitleFontSize, m_TitleFontSize, OnTitleFontSizeChanged, VT_I2)
	DISP_PROPERTY_NOTIFY_ID(CEIPGadgetCtrl, "TitleBackgroundColor", dispidTitleBackgroundColor, m_TitleBackgroundColor, OnTitleBackgroundColorChanged, VT_COLOR)
	DISP_PROPERTY_NOTIFY_ID(CEIPGadgetCtrl, "TitleTextColor", dispidTitleTextColor, m_TitleTextColor, OnTitleTextColorChanged, VT_COLOR)
	DISP_FUNCTION_ID(CEIPGadgetCtrl, "OpenCom", dispidOpenCom, OpenCom, VT_I2, VTS_BSTR)
END_DISPATCH_MAP()



// Event map

BEGIN_EVENT_MAP(CEIPGadgetCtrl, COleControl)
END_EVENT_MAP()



// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CEIPGadgetCtrl, 1)
	PROPPAGEID(CEIPGadgetPropPage::guid)
END_PROPPAGEIDS(CEIPGadgetCtrl)



// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CEIPGadgetCtrl, "EIPGADGET.EIPGadgetCtrl.1",
	0xf5260866, 0xe6bb, 0x4a2d, 0xa2, 0xd9, 0x33, 0x6b, 0x96, 0xc6, 0xef, 0x1b)



// Type library ID and version

IMPLEMENT_OLETYPELIB(CEIPGadgetCtrl, _tlid, _wVerMajor, _wVerMinor)



// Interface IDs

const IID IID_DEIPGadget = { 0xF0C901EA, 0xE990, 0x41C4, { 0x8F, 0x3C, 0x7B, 0xDB, 0x18, 0x91, 0x98, 0x99 } };
const IID IID_DEIPGadgetEvents = { 0x20C79ABD, 0x247E, 0x4F57, { 0xBF, 0x3C, 0x9C, 0xB9, 0xCB, 0xBE, 0x67, 0x79 } };


// Control type information

static const DWORD _dwEIPGadgetOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CEIPGadgetCtrl, IDS_EIPGADGET, _dwEIPGadgetOleMisc)



// CEIPGadgetCtrl::CEIPGadgetCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CEIPGadgetCtrl

BOOL CEIPGadgetCtrl::CEIPGadgetCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: Verify that your control follows apartment-model threading rules.
	// Refer to MFC TechNote 64 for more information.
	// If your control does not conform to the apartment-model rules, then
	// you must modify the code below, changing the 6th parameter from
	// afxRegApartmentThreading to 0.

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_EIPGADGET,
			IDB_EIPGADGET,
			afxRegApartmentThreading,
			_dwEIPGadgetOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}



// CEIPGadgetCtrl::CEIPGadgetCtrl - Constructor

CEIPGadgetCtrl::CEIPGadgetCtrl()
{
	InitializeIIDs(&IID_DEIPGadget, &IID_DEIPGadgetEvents);
	m_On.LoadBitmap(IDB_DISABLED);
	m_Off.LoadBitmap(IDB_ENABLED);

}



// CEIPGadgetCtrl::~CEIPGadgetCtrl - Destructor

CEIPGadgetCtrl::~CEIPGadgetCtrl()
{
	m_EIPCOM.Running = false;
	m_EIPCOM.ExitEvent.Lock();
}



// CEIPGadgetCtrl::OnDraw - Drawing function

void CEIPGadgetCtrl::OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	CDC dcMem;
	BITMAP bm;
	CBitmap bitmap;
	CFont font;
	CRect status;
	TEXTMETRIC tm;

	// Drawing rectangle
    CRect rect = rcBounds;

	if (!pdc)return;


	// Bitmap surface for drawing
	bitmap.CreateCompatibleBitmap (pdc, rcBounds.Width(), rcBounds.Height());
    bitmap.GetBitmap (&bm);
	CPoint size (bm.bmWidth, bm.bmHeight);
    pdc->DPtoLP (&size);
	CPoint org (0, 0);
    pdc->DPtoLP (&org);

	// Memory DC for drawing
	dcMem.CreateCompatibleDC (pdc);
	CBitmap* pOldBitmap = dcMem.SelectObject (&bitmap);
    dcMem.SetMapMode (pdc->GetMapMode ());

	// Draw the 3D boarder
	dcMem.Rectangle (rect.left, rect.top,rect.right,rect.bottom);
	rect.DeflateRect(1,1);
	dcMem.Draw3dRect(rect, ::GetSysColor (COLOR_3DHILIGHT), ::GetSysColor (COLOR_3DDKSHADOW));
	rect.DeflateRect(1,1);
	rect.right -=1;
	rect.bottom -=1;
	dcMem.Draw3dRect(rect, ::GetSysColor (COLOR_3DHILIGHT), ::GetSysColor (COLOR_3DSHADOW));

	// Title font
	font.CreatePointFont (m_TitleFontSize*10, _T ("Microsoft Sans Serif"));
	CFont* pOldFont = dcMem.SelectObject (&font);

	// Adjust the title rectangle and draw the status box
	dcMem.GetTextMetrics (&tm);
	int cxChar = tm.tmAveCharWidth;
	int cyChar = tm.tmHeight + tm.tmExternalLeading;
	status.bottom = rect.bottom - 1;
	rect.bottom = rect.top + cyChar;
	status.top = rect.bottom + 1;
	status.right = rect.right - 1;
	status.left = rect.left + 1;

	// Draw the Bar
	CRect rcBar = status;
	//rcBar.left = status.Width()/2;
	DrawBar(&dcMem,rcBar);


	//// Paint the ticks
	//status.right = rect.left + status.Width()/2;
	//PaintTicks(&dcMem,status);

	// Draw the Title
	DrawTitle(&dcMem,rect);

	// Display to screen
	pdc->BitBlt (rcBounds.left, rcBounds.top, size.x,size.y, &dcMem, org.x, org.y, SRCCOPY);
	
	// Restore the DC
	dcMem.SelectObject (pOldBitmap);
	//dcMem.SelectObject (pOldFont);
}


void CEIPGadgetCtrl::DrawTitle(CDC *pDC,const CRect& Rect)
{
	CRect rect =  Rect;

	if (m_DoGradientFill)
	{
		DoGradientFill(pDC,Rect);
	}
	else
	{
		CBrush Brush;
		Brush.CreateSolidBrush(m_TitleBackgroundColor);
		pDC->FillRect(&rect,&Brush);
	}
	pDC->SetBkMode (TRANSPARENT);
	pDC->SetTextColor (m_TitleTextColor);
	pDC->DrawText (m_Title, -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

}
void CEIPGadgetCtrl::DoGradientFill(CDC *pDC,const CRect& Rect)
{
	//m_TitleTextBackColor = RGB(255,0,0);
	double dbR = (double)GetRValue(m_TitleBackgroundColor)/255.0;
	double dbG = (double)GetGValue(m_TitleBackgroundColor)/255.0;
	double dbB = (double)GetBValue(m_TitleBackgroundColor)/255.0;
	//TRACE("R:%d \n",GetRValue(m_TitleTextBackColor));
	//TRACE("G:%d \n",GetGValue(m_TitleTextBackColor));
	//TRACE("B:%d \n",GetBValue(m_TitleTextBackColor));
	//TRACE("dbR:%f \n",dbR);
	//TRACE("dbG:%f \n",dbG);
	//TRACE("dbB:%f \n",dbB);

	const int nNumColors = 128;
    CBrush* pBrush[nNumColors];
    for (int i=0; i<nNumColors; i++){
        pBrush[i] = new CBrush (RGB(i*dbR+80*dbR,i*dbG+80*dbG,i*dbB+80*dbB));
	}

    int nWidth = (Rect.right - Rect.left) + 1;
    int nHeight = (Rect.bottom - Rect.top) + 1;
    CRect rect;

    for (int i=Rect.left; i<=nWidth; i++) {
        rect.SetRect (i, Rect.top, i + 1, nHeight + 1);
        pDC->FillRect (&rect, pBrush[(i*(nNumColors-1))/nWidth]);
    }
    for (int i=0; i<nNumColors; i++)
        delete pBrush[i];
}
void CEIPGadgetCtrl::PaintTicks(CDC* pDC,const CRect& Rect)
{
//	CRect rcTicks = Rect;
//
////		PX_ULong (pPX, _T ("TickBackColor"), m_TickBackColor,RGB(255,255,255));
////	PX_ULong (pPX, _T ("TickColor"), m_TickColor,RGB(255,255,255));
//	//PX_Short (pPX, _T ("TickFontSize"), m_TickFontSize,12);
//	//PX_Short (pPX, _T ("TickOffset"), m_TickOffset,5);
//	//PX_Short (pPX, _T ("TickCount"), m_TickCount,4);
//	//PX_String (pPX, _T ("TickUnits"), m_TickUnits,_T (""));
//
//
//	// Create the font and select it
//	CFont font;
//	font.CreatePointFont (m_TickFontSize*10, _T ("Microsoft Sans Serif"));
//	CFont* pOldFont = pDC->SelectObject (&font);
//
//	CBrush Brush;
//	Brush.CreateSolidBrush(m_TickBackColor);
//
//	// Draw in memory
//	pDC->FillRect(&rcTicks,&Brush);
//	pDC->SetBkMode (TRANSPARENT);
//	pDC->SetTextColor (m_TickColor);
//
//	int Height = rcTicks.Height()/5;
//	rcTicks.bottom = rcTicks.top + Height;
//	pDC->DrawText (_T("F   "), -1, &rcTicks, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
//	int x = rcTicks.right - 18;
//	int y = (rcTicks.top + rcTicks.bottom)/2;
//	pDC->MoveTo(x,y-1);
//	pDC->LineTo(x+8,y-1);
//	pDC->MoveTo(x+10,y-1);
//	pDC->LineTo(x+18,y-1);
//	pDC->MoveTo(x,y);
//	pDC->LineTo(x+8,y);
//	pDC->MoveTo(x+10,y);
//	pDC->LineTo(x+18,y);
//
//	rcTicks.top += Height;
//	rcTicks.bottom += Height;
//	//pDC->DrawText (_T("     -"), -1, &rcTicks, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
//	x = rcTicks.right - 8;
//	y = (rcTicks.top + rcTicks.bottom)/2;
//	pDC->MoveTo(x,y-1);
//	pDC->LineTo(x+8,y-1);
//	pDC->MoveTo(x,y);
//	pDC->LineTo(x+8,y);
//
//	rcTicks.top += Height;
//	rcTicks.bottom += Height;
//	//pDC->DrawText (_T("1/2 --"), -1, &rcTicks, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
//	x = rcTicks.right - 18;
//	y = (rcTicks.top + rcTicks.bottom)/2;
//	pDC->MoveTo(x,y-1);
//	pDC->LineTo(x+8,y-1);
//	pDC->MoveTo(x+10,y-1);
//	pDC->LineTo(x+18,y-1);
//	pDC->MoveTo(x,y);
//	pDC->LineTo(x+8,y);
//	pDC->MoveTo(x+10,y);
//	pDC->LineTo(x+18,y);
//
//
//	rcTicks.top += Height;
//	rcTicks.bottom += Height;
//	//pDC->DrawText (_T("     -"), -1, &rcTicks, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
//	x = rcTicks.right - 8;
//	y = (rcTicks.top + rcTicks.bottom)/2;
//	pDC->MoveTo(x,y-1);
//	pDC->LineTo(x+8,y-1);
//	pDC->MoveTo(x,y);
//	pDC->LineTo(x+8,y);
//
//	rcTicks.top += Height;
//	rcTicks.bottom += Height;
//	pDC->DrawText (_T("E    "), -1, &rcTicks, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
//	x = rcTicks.right - 18;
//	y = (rcTicks.top + rcTicks.bottom)/2;
//	pDC->MoveTo(x,y-1);
//	pDC->LineTo(x+8,y-1);
//	pDC->MoveTo(x+10,y-1);
//	pDC->LineTo(x+18,y-1);
//	pDC->MoveTo(x,y);
//	pDC->LineTo(x+8,y);
//	pDC->MoveTo(x+10,y);
//	pDC->LineTo(x+18,y);
//
//
//	// Restore the DC
//	pDC->SelectObject (pOldFont);


}

void CEIPGadgetCtrl::DrawBar(CDC* pDC,const CRect& rect)
{
    // Get the size of the bitmap
	BITMAP bmpInfo;
    //pBitMap->GetBitmap (&bmpInfo);
    CDC dcMem;
	CBitmap* pOldBitmap;
    dcMem.CreateCompatibleDC (pDC);
	//pOldBitmap = dcMem.SelectObject (pBitMap);

	CBrush Brush;
	Brush.CreateSolidBrush(RGB(84,84,84));
	CRect rcBar = rect;

	pDC->Draw3dRect(rcBar, RGB(164,164,164),RGB(64,64,64));
	rcBar.InflateRect(-1,-1);
	pDC->FillRect(&rcBar,&Brush);

	// Select the bitmap
	m_On.GetBitmap (&bmpInfo);
	pOldBitmap = dcMem.SelectObject (&m_On);
	
	// Draw background
	pDC->StretchBlt (rcBar.left,rcBar.top, rcBar.Width(),rcBar.Height(), &dcMem, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, SRCCOPY);

	// Restore the DC
    dcMem.SelectObject (pOldBitmap);

}



// CEIPGadgetCtrl::DoPropExchange - Persistence support

void CEIPGadgetCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// Call PX_ functions for each persistent custom property.
	PX_Short (pPX, _T ("TitleFontSize"), m_TitleFontSize,12);
	PX_Short (pPX, _T ("DoGradientFill"), m_DoGradientFill,1);
	PX_String (pPX, _T ("Title"), m_Title,_T ("Title"));
	PX_ULong (pPX, _T ("TitleBackgroundColor"), m_TitleBackgroundColor,RGB(155,155,155));
	PX_ULong (pPX, _T ("TitleTextColor"), m_TitleTextColor,RGB(255,255,255));
	//PX_String (pPX, _T ("Text"), m_Title,_T ("Title"));
	//PX_ULong (pPX, _T ("TickBackColor"), m_TickBackColor,RGB(255,255,255));
	//PX_ULong (pPX, _T ("TickColor"), m_TickColor,RGB(0,0,0));
	////PX_Short (pPX, _T ("HasStatusBox"), m_HasClientBox,1);
	////PX_Short (pPX, _T ("FontSize"), m_FontSize,16);
	//PX_Short (pPX, _T ("TickFontSize"), m_TickFontSize,12);
	//PX_Short (pPX, _T ("TickOffset"), m_TickOffset,5);
	//PX_Short (pPX, _T ("TickCount"), m_TickCount,4);
	//PX_String (pPX, _T ("TickUnits"), m_TickUnits,_T (""));

}



// CEIPGadgetCtrl::OnResetState - Reset control to default state

void CEIPGadgetCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}



// CEIPGadgetCtrl::AboutBox - Display an "About" box to the user

void CEIPGadgetCtrl::AboutBox()
{
	CDialogEx dlgAbout(IDD_ABOUTBOX_EIPGADGET);
	dlgAbout.DoModal();
}



// CEIPGadgetCtrl message handlers


void CEIPGadgetCtrl::OnDoGradientFillChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
	InvalidateControl();
}


void CEIPGadgetCtrl::OnTitleChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
	InvalidateControl();
}


void CEIPGadgetCtrl::OnTitleFontSizeChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
	InvalidateControl();
}


void CEIPGadgetCtrl::OnTitleBackgroundColorChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
	InvalidateControl();
}


void CEIPGadgetCtrl::OnTitleTextColorChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
	InvalidateControl();
}


SHORT CEIPGadgetCtrl::OpenCom(LPCTSTR IpAddr)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// Initialize
	m_EIPCOM.Running = true;
	m_EIPCOM.IpAddr = IpAddr;
	CWinThread* pThread = AfxBeginThread (EIPCOMThreadFunc, &m_EIPCOM,THREAD_PRIORITY_NORMAL,CREATE_SUSPENDED);
	pThread->ResumeThread();

	return 0;
}
