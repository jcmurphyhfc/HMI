// GDIGagetCtrl.cpp : Implementation of the CGDIGagetCtrl ActiveX Control class.

#include "stdafx.h"
#include "GDIGaget.h"
#include "GDIGagetCtrl.h"
#include "GDIGagetPropPage.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CGDIGagetCtrl, COleControl)



// Message map

BEGIN_MESSAGE_MAP(CGDIGagetCtrl, COleControl)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
	ON_WM_CREATE()
END_MESSAGE_MAP()



// Dispatch map

BEGIN_DISPATCH_MAP(CGDIGagetCtrl, COleControl)
	DISP_FUNCTION_ID(CGDIGagetCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
	DISP_PROPERTY_NOTIFY_ID(CGDIGagetCtrl, "TitleFontSize", dispidTitleFontSize, m_TitleFontSize, OnTitleFontSizeChanged, VT_I2)
	DISP_FUNCTION_ID(CGDIGagetCtrl, "SetPos", dispidSetPos, SetPos, VT_EMPTY, VTS_I4)
	DISP_FUNCTION_ID(CGDIGagetCtrl, "SetRange", dispidSetRange, SetRange, VT_EMPTY, VTS_I4 VTS_I4)
	DISP_PROPERTY_NOTIFY_ID(CGDIGagetCtrl, "DoGradientFill", dispidDoGradientFill, m_DoGradientFill, OnDoGradientFillChanged, VT_I2)
	DISP_PROPERTY_NOTIFY_ID(CGDIGagetCtrl, "TitleTextBackColor", dispidTitleTextBackColor, m_TitleTextBackColor, OnTitleTextBackColorChanged, VT_COLOR)
	DISP_PROPERTY_NOTIFY_ID(CGDIGagetCtrl, "TitleTextColor", dispidTitleTextColor, m_TitleTextColor, OnTitleTextColorChanged, VT_COLOR)
	DISP_PROPERTY_NOTIFY_ID(CGDIGagetCtrl, "Title", dispidTitle, m_Title, OnTitleChanged, VT_BSTR)
	DISP_PROPERTY_NOTIFY_ID(CGDIGagetCtrl, "TickBackColor", dispidTickBackColor, m_TickBackColor, OnTickBackColorChanged, VT_COLOR)
	DISP_PROPERTY_NOTIFY_ID(CGDIGagetCtrl, "TickColor", dispidTickColor, m_TickColor, OnTickColorChanged, VT_COLOR)
	DISP_PROPERTY_NOTIFY_ID(CGDIGagetCtrl, "TickFontSize", dispidTickFontSize, m_TickFontSize, OnTickFontSizeChanged, VT_I2)
	DISP_PROPERTY_NOTIFY_ID(CGDIGagetCtrl, "TickOffset", dispidTickOffset, m_TickOffset, OnTickOffsetChanged, VT_I2)
	DISP_PROPERTY_NOTIFY_ID(CGDIGagetCtrl, "TickCount", dispidTickCount, m_TickCount, OnTickCountChanged, VT_I2)
	DISP_PROPERTY_NOTIFY_ID(CGDIGagetCtrl, "TickUnits", dispidTickUnits, m_TickUnits, OnTickUnitsChanged, VT_BSTR)
END_DISPATCH_MAP()



// Event map

BEGIN_EVENT_MAP(CGDIGagetCtrl, COleControl)
END_EVENT_MAP()



// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CGDIGagetCtrl, 1)
	PROPPAGEID(CGDIGagetPropPage::guid)
END_PROPPAGEIDS(CGDIGagetCtrl)



// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CGDIGagetCtrl, "GDIGAGET.GDIGagetCtrl.1",
	0x2babd821, 0xfc2f, 0x4e9f, 0xae, 0x2e, 0x20, 0xd5, 0x3c, 0x2e, 0xa7, 0x52)



// Type library ID and version

IMPLEMENT_OLETYPELIB(CGDIGagetCtrl, _tlid, _wVerMajor, _wVerMinor)



// Interface IDs

const IID IID_DGDIGaget = { 0x2795B9DA, 0x41A4, 0x496A, { 0xA6, 0x4C, 0x70, 0xC3, 0x5, 0x2F, 0xA2, 0x95 } };
const IID IID_DGDIGagetEvents = { 0x75D53DB2, 0xB40E, 0x472E, { 0x94, 0x1E, 0xD0, 0x4B, 0x6A, 0xF8, 0x87, 0xEA } };


// Control type information

static const DWORD _dwGDIGagetOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CGDIGagetCtrl, IDS_GDIGAGET, _dwGDIGagetOleMisc)


// CGDIGagetCtrl::DoPropExchange - Persistence support

void CGDIGagetCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// Call PX_ functions for each persistent custom property.
	PX_Short (pPX, _T ("TitleFontSize"), m_TitleFontSize,12);
	PX_Short (pPX, _T ("DoGradientFill"), m_DoGradientFill,1);
	PX_ULong (pPX, _T ("TitleTextBackColor"), m_TitleTextBackColor,RGB(155,155,155));
	PX_ULong (pPX, _T ("TitleTextColor"), m_TitleTextColor,RGB(255,255,255));
	PX_String (pPX, _T ("Text"), m_Title,_T ("Title"));
	PX_ULong (pPX, _T ("TickBackColor"), m_TickBackColor,RGB(255,255,255));
	PX_ULong (pPX, _T ("TickColor"), m_TickColor,RGB(0,0,0));

	//PX_Short (pPX, _T ("HasStatusBox"), m_HasClientBox,1);
	//PX_Short (pPX, _T ("FontSize"), m_FontSize,16);
	PX_Short (pPX, _T ("TickFontSize"), m_TickFontSize,12);
	PX_Short (pPX, _T ("TickOffset"), m_TickOffset,5);
	PX_Short (pPX, _T ("TickCount"), m_TickCount,4);
	PX_String (pPX, _T ("TickUnits"), m_TickUnits,_T (""));


}


// CGDIGagetCtrl::CGDIGagetCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CGDIGagetCtrl

BOOL CGDIGagetCtrl::CGDIGagetCtrlFactory::UpdateRegistry(BOOL bRegister)
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
			IDS_GDIGAGET,
			IDB_GDIGAGET,
			afxRegApartmentThreading,
			_dwGDIGagetOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}



// CGDIGagetCtrl::CGDIGagetCtrl - Constructor

CGDIGagetCtrl::CGDIGagetCtrl()
{
	InitializeIIDs(&IID_DGDIGaget, &IID_DGDIGagetEvents);
	
	//Initialize
	//m_HasWnd = FALSE;
	m_GreenBar.LoadBitmap(IDB_GREENBAR);
	m_YellowBar.LoadBitmap(IDB_YELLOWBAR);
	m_RedBar.LoadBitmap(IDB_REDBAR);

	m_Pos = 50;
	m_Lower = 0;
	m_Upper = 100;

}



// CGDIGagetCtrl::~CGDIGagetCtrl - Destructor

CGDIGagetCtrl::~CGDIGagetCtrl()
{
	// TODO: Cleanup your control's instance data here.
}



// CGDIGagetCtrl::OnDraw - Drawing function
void CGDIGagetCtrl::OnDraw(	CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
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
	rcBar.left = status.Width()/2;
	DrawBar(&dcMem,rcBar);

	// Position the progress control
	//if (m_HasWnd)
	//{
	//	m_wndProgress.SetWindowPos(&wndTop,(status.Width()/2)+2,status.top,(status.Width()/2)+2,status.Height(),SWP_SHOWWINDOW);
	//	m_HasWnd = FALSE;
	//}

	// Paint the ticks
	status.right = rect.left + status.Width()/2;
	PaintTicks(&dcMem,status);

	// Draw the Title
	DrawTitle(&dcMem,rect);

	// Display to screen
	pdc->BitBlt (rcBounds.left, rcBounds.top, size.x,size.y, &dcMem, org.x, org.y, SRCCOPY);
	
	// Restore the DC
	dcMem.SelectObject (pOldBitmap);
	//dcMem.SelectObject (pOldFont);
}

void CGDIGagetCtrl::DrawTitle(CDC *pDC,const CRect& Rect)
{
	CRect rect =  Rect;

	if (m_DoGradientFill)
	{
		DoGradientFill(pDC,Rect);
	}
	else
	{
		CBrush Brush;
		Brush.CreateSolidBrush(m_TitleTextBackColor);
		pDC->FillRect(&rect,&Brush);
	}
	pDC->SetBkMode (TRANSPARENT);
	pDC->SetTextColor (m_TitleTextColor);
	pDC->DrawText (m_Title, -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

}
void CGDIGagetCtrl::DoGradientFill(CDC *pDC,const CRect& Rect)
{
	//m_TitleTextBackColor = RGB(255,0,0);
	double dbR = (double)GetRValue(m_TitleTextBackColor)/255.0;
	double dbG = (double)GetGValue(m_TitleTextBackColor)/255.0;
	double dbB = (double)GetBValue(m_TitleTextBackColor)/255.0;
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
void CGDIGagetCtrl::PaintTicks(CDC* pDC,const CRect& Rect)
{
	CRect rcTicks = Rect;

//		PX_ULong (pPX, _T ("TickBackColor"), m_TickBackColor,RGB(255,255,255));
//	PX_ULong (pPX, _T ("TickColor"), m_TickColor,RGB(255,255,255));
	//PX_Short (pPX, _T ("TickFontSize"), m_TickFontSize,12);
	//PX_Short (pPX, _T ("TickOffset"), m_TickOffset,5);
	//PX_Short (pPX, _T ("TickCount"), m_TickCount,4);
	//PX_String (pPX, _T ("TickUnits"), m_TickUnits,_T (""));


	// Create the font and select it
	CFont font;
	font.CreatePointFont (m_TickFontSize*10, _T ("Microsoft Sans Serif"));
	CFont* pOldFont = pDC->SelectObject (&font);

	CBrush Brush;
	Brush.CreateSolidBrush(m_TickBackColor);

	// Draw in memory
	pDC->FillRect(&rcTicks,&Brush);
	pDC->SetBkMode (TRANSPARENT);
	pDC->SetTextColor (m_TickColor);

	int Height = rcTicks.Height()/5;
	rcTicks.bottom = rcTicks.top + Height;
	pDC->DrawText (_T("F   "), -1, &rcTicks, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	int x = rcTicks.right - 18;
	int y = (rcTicks.top + rcTicks.bottom)/2;
	pDC->MoveTo(x,y-1);
	pDC->LineTo(x+8,y-1);
	pDC->MoveTo(x+10,y-1);
	pDC->LineTo(x+18,y-1);
	pDC->MoveTo(x,y);
	pDC->LineTo(x+8,y);
	pDC->MoveTo(x+10,y);
	pDC->LineTo(x+18,y);

	rcTicks.top += Height;
	rcTicks.bottom += Height;
	//pDC->DrawText (_T("     -"), -1, &rcTicks, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	x = rcTicks.right - 8;
	y = (rcTicks.top + rcTicks.bottom)/2;
	pDC->MoveTo(x,y-1);
	pDC->LineTo(x+8,y-1);
	pDC->MoveTo(x,y);
	pDC->LineTo(x+8,y);

	rcTicks.top += Height;
	rcTicks.bottom += Height;
	//pDC->DrawText (_T("1/2 --"), -1, &rcTicks, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	x = rcTicks.right - 18;
	y = (rcTicks.top + rcTicks.bottom)/2;
	pDC->MoveTo(x,y-1);
	pDC->LineTo(x+8,y-1);
	pDC->MoveTo(x+10,y-1);
	pDC->LineTo(x+18,y-1);
	pDC->MoveTo(x,y);
	pDC->LineTo(x+8,y);
	pDC->MoveTo(x+10,y);
	pDC->LineTo(x+18,y);


	rcTicks.top += Height;
	rcTicks.bottom += Height;
	//pDC->DrawText (_T("     -"), -1, &rcTicks, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	x = rcTicks.right - 8;
	y = (rcTicks.top + rcTicks.bottom)/2;
	pDC->MoveTo(x,y-1);
	pDC->LineTo(x+8,y-1);
	pDC->MoveTo(x,y);
	pDC->LineTo(x+8,y);

	rcTicks.top += Height;
	rcTicks.bottom += Height;
	pDC->DrawText (_T("E    "), -1, &rcTicks, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	x = rcTicks.right - 18;
	y = (rcTicks.top + rcTicks.bottom)/2;
	pDC->MoveTo(x,y-1);
	pDC->LineTo(x+8,y-1);
	pDC->MoveTo(x+10,y-1);
	pDC->LineTo(x+18,y-1);
	pDC->MoveTo(x,y);
	pDC->LineTo(x+8,y);
	pDC->MoveTo(x+10,y);
	pDC->LineTo(x+18,y);


	// Restore the DC
	pDC->SelectObject (pOldFont);


}

void CGDIGagetCtrl::DrawBar(CDC* pDC,const CRect& rect)
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

	double Range = m_Upper - m_Lower;
	double Pos = m_Pos - m_Lower;
	double Percent = Pos/Range;
	double Top = rcBar.Height() - rcBar.Height()*Percent;
	//TRACE("Lower %d   Upper: %d  Pos: %d \n",m_Lower,m_Upper,m_Pos);
	//TRACE("Range: %f   Percent: %f   Top: %f \n",Range,Percent,Top);
	rcBar.top += (long)Top;
	if (rcBar.top >= rcBar.bottom)
		rcBar.top = rcBar.bottom - 1;

	// Select the bitmap
	Percent = Percent*100;
	if (Percent > 28.0)
	{
		m_GreenBar.GetBitmap (&bmpInfo);
		pOldBitmap = dcMem.SelectObject (&m_GreenBar);
	}
	else
	{
		if (Percent > 15.0)
		{
			m_YellowBar.GetBitmap (&bmpInfo);
			pOldBitmap = dcMem.SelectObject (&m_YellowBar);		
		}
		else
		{
			m_RedBar.GetBitmap (&bmpInfo);
			pOldBitmap = dcMem.SelectObject (&m_RedBar);				
		}
	}
	
	// Draw background
	pDC->StretchBlt (rcBar.left,rcBar.top, rcBar.Width(),rcBar.Height(), &dcMem, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, SRCCOPY);

	// Restore the DC
    dcMem.SelectObject (pOldBitmap);

}


// CGDIGagetCtrl::OnResetState - Reset control to default state

void CGDIGagetCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}



// CGDIGagetCtrl::AboutBox - Display an "About" box to the user

void CGDIGagetCtrl::AboutBox()
{
	CDialogEx dlgAbout(IDD_ABOUTBOX_GDIGAGET);
	dlgAbout.DoModal();
}



// CGDIGagetCtrl message handlers


int CGDIGagetCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (COleControl::OnCreate(lpCreateStruct) == -1)
		return -1;

	// Add your specialized creation code here
	//m_wndProgress.Create (WS_CHILD | WS_VISIBLE | WS_BORDER | PBS_VERTICAL,
    //CRect (0, 0, 1, 1), this, IDC_PROGRESS);
	//m_wndProgress.SetState(PBST_PAUSED);
	//m_wndProgress.SetState(PBST_NORMAL);
	//m_wndProgress.SetState(PBST_ERROR);
	//m_wndProgress.SetBarColor(RGB(55,55,255));
	//m_wndProgress.SetMarquee(FALSE,0);
	//m_wndProgress.SetRange32(0,100);
	//m_wndProgress.SetPos(50);
	//PBS_MARQUEE
	//m_HasWnd = TRUE;


	return 0;
}

void CGDIGagetCtrl::SetPos(LONG Pos)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	//m_wndProgress.SetPos(Pos);
	m_Pos = Pos;	
	//m_wndProgress.ModifyStyle (0,PBS_MARQUEE);
	//m_wndProgress.SetMarquee(TRUE,0);
	SetModifiedFlag();
	InvalidateControl();
}


void CGDIGagetCtrl::SetRange(LONG Lower, LONG Upper)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	//m_wndProgress.SetRange32(Lower,Upper);

	m_Lower = Lower;
	m_Upper = Upper;

	//SetModifiedFlag();
	//InvalidateControl();
}

void CGDIGagetCtrl::OnTitleFontSizeChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
	InvalidateControl();
}


void CGDIGagetCtrl::OnDoGradientFillChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
	InvalidateControl();
}


void CGDIGagetCtrl::OnTitleTextBackColorChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
	InvalidateControl();
}


void CGDIGagetCtrl::OnTitleTextColorChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
	InvalidateControl();
}


void CGDIGagetCtrl::OnTitleChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
	InvalidateControl();
}


void CGDIGagetCtrl::OnTickBackColorChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
	InvalidateControl();
}


void CGDIGagetCtrl::OnTickColorChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
	InvalidateControl();
}


void CGDIGagetCtrl::OnTickFontSizeChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
	InvalidateControl();
}


void CGDIGagetCtrl::OnTickOffsetChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
	InvalidateControl();
}


void CGDIGagetCtrl::OnTickCountChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
	InvalidateControl();
}


void CGDIGagetCtrl::OnTickUnitsChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
	InvalidateControl();
}