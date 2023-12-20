// GDIStatusBoxCtrl.cpp : Implementation of the CGDIStatusBoxCtrl ActiveX Control class.

#include "stdafx.h"
#include "GDIStatusBox.h"
#include "GDIStatusBoxCtrl.h"
#include "GDIStatusBoxPropPage.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CGDIStatusBoxCtrl, COleControl)



// Message map

BEGIN_MESSAGE_MAP(CGDIStatusBoxCtrl, COleControl)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
	ON_WM_TIMER()
	ON_WM_CREATE()
END_MESSAGE_MAP()


// Dispatch map

BEGIN_DISPATCH_MAP(CGDIStatusBoxCtrl, COleControl)
	DISP_FUNCTION_ID(CGDIStatusBoxCtrl,        "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
	DISP_PROPERTY_NOTIFY_ID(CGDIStatusBoxCtrl, "HasStatusBox", dispidbHasClientBox, m_bHasClientBox, OnbHasClientBoxChanged, VT_I2)
	DISP_PROPERTY_NOTIFY_ID(CGDIStatusBoxCtrl, "TitleFontSize", dispidnTitleFontSize, m_nTitleFontSize, OnnTitleFontSizeChanged, VT_I2)	DISP_PROPERTY_NOTIFY_ID(CGDIStatusBoxCtrl, "TitleTextColor", dispidclrTitleTextColor, m_clrTitleTextColor, OnclrTitleTextColorChanged, VT_COLOR)
	DISP_PROPERTY_NOTIFY_ID(CGDIStatusBoxCtrl, "TitleDoGradientFill", dispidbDoGradientFill, m_bDoGradientFill, OnbDoGradientFillChanged, VT_I2)
	DISP_PROPERTY_NOTIFY_ID(CGDIStatusBoxCtrl, "TitleText", dispidstrTitle, m_strTitle, OnstrTitleChanged, VT_BSTR)
	DISP_PROPERTY_NOTIFY_ID(CGDIStatusBoxCtrl, "StatusText", dispidstrText, m_strText, OnstrTextChanged, VT_BSTR)
	DISP_PROPERTY_NOTIFY_ID(CGDIStatusBoxCtrl, "StatusTextFontSize", dispidnFontSize, m_nFontSize, OnnFontSizeChanged, VT_I2)
	DISP_PROPERTY_NOTIFY_ID(CGDIStatusBoxCtrl, "StatusTextColor", dispidclrTextColor, m_clrTextColor, OnclrTextColorChanged, VT_COLOR)
	DISP_PROPERTY_NOTIFY_ID(CGDIStatusBoxCtrl, "StatusTextBackColor", dispidcltBkColor, m_cltBkColor, OncltBkColorChanged, VT_COLOR)
	DISP_PROPERTY_NOTIFY_ID(CGDIStatusBoxCtrl, "StatusBlink", dispidbBlink, m_bBlink, OnbBlinkChanged, VT_I2)
	DISP_PROPERTY_EX_ID(CGDIStatusBoxCtrl,     "StatusState", dispidState, GetState, SetState, VT_I2)
	DISP_PROPERTY_NOTIFY_ID(CGDIStatusBoxCtrl, "TitleTextBackColor", dispidTitleTextBackColor, m_TitleTextBackColor, OnTitleTextBackColorChanged, VT_COLOR)
	DISP_PROPERTY_NOTIFY_ID(CGDIStatusBoxCtrl, "StatusBlinkOnTime", dispidStatusBlinkOnTime, m_StatusBlinkOnTime, OnStatusBlinkOnTimeChanged, VT_UI4)
	DISP_PROPERTY_NOTIFY_ID(CGDIStatusBoxCtrl, "StatusBlinkOffTime", dispidStatusBlinkOffTime, m_StatusBlinkOffTime, OnStatusBlinkOffTimeChanged, VT_UI4)
END_DISPATCH_MAP()


// Event map

BEGIN_EVENT_MAP(CGDIStatusBoxCtrl, COleControl)
	EVENT_STOCK_CLICK()
	EVENT_STOCK_MOUSEDOWN()
	EVENT_STOCK_MOUSEUP()
	EVENT_STOCK_DBLCLICK()
	EVENT_STOCK_KEYPRESS()
END_EVENT_MAP()



// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CGDIStatusBoxCtrl, 1)
	PROPPAGEID(CGDIStatusBoxPropPage::guid)
END_PROPPAGEIDS(CGDIStatusBoxCtrl)



// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CGDIStatusBoxCtrl, "GDISTATUSBOX.GDIStatusBoxCtrl.1",
	0x13947960, 0x120f, 0x4559, 0xad, 0x1b, 0xfe, 0xd6, 0xe4, 0x57, 0xd7, 0xaa)



// Type library ID and version

IMPLEMENT_OLETYPELIB(CGDIStatusBoxCtrl, _tlid, _wVerMajor, _wVerMinor)



// Interface IDs

const IID IID_DGDIStatusBox = { 0xE2D8EAB4, 0xC742, 0x4C2D, { 0x80, 0xB3, 0xAA, 0x21, 0x23, 0xDE, 0x6F, 0x8E } };
const IID IID_DGDIStatusBoxEvents = { 0xEB91B894, 0x9CA1, 0x4CFA, { 0xBF, 0x58, 0x79, 0x13, 0xB9, 0x65, 0x28, 0xA0 } };


// Control type information

static const DWORD _dwGDIStatusBoxOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CGDIStatusBoxCtrl, IDS_GDISTATUSBOX, _dwGDIStatusBoxOleMisc)



// CGDIStatusBoxCtrl::CGDIStatusBoxCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CGDIStatusBoxCtrl

BOOL CGDIStatusBoxCtrl::CGDIStatusBoxCtrlFactory::UpdateRegistry(BOOL bRegister)
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
			IDS_GDISTATUSBOX,
			IDB_GDISTATUSBOX,
			afxRegApartmentThreading,
			_dwGDIStatusBoxOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}



// CGDIStatusBoxCtrl::CGDIStatusBoxCtrl - Constructor

CGDIStatusBoxCtrl::CGDIStatusBoxCtrl()
{
	InitializeIIDs(&IID_DGDIStatusBox, &IID_DGDIStatusBoxEvents);

	// Initialize control's instance data.
	m_bBlinkOn       = FALSE;
	m_bTimerRunning  = FALSE;
	SetState(GetState());
	//m_Button.LoadBitmap(IDB_BLUE_ON_UP);


}



// CGDIStatusBoxCtrl::~CGDIStatusBoxCtrl - Destructor

CGDIStatusBoxCtrl::~CGDIStatusBoxCtrl()
{
	// TODO: Cleanup your control's instance data here.
}

// CGDIStatusBoxCtrl::DoPropExchange - Persistence support

void CGDIStatusBoxCtrl::DoPropExchange(CPropExchange* pPX)
{

	CString strPropName;
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// Call PX_ functions for each persistent custom property.
	PX_Short (pPX, _T ("HasStatusBox"), m_bHasClientBox,TRUE);
	PX_Short (pPX, _T ("TitleFontSize"), m_nTitleFontSize,16);
	PX_ULong (pPX, _T ("TitleTextColor"), m_clrTitleTextColor,RGB(255,255,255));
	PX_Short (pPX, _T ("TitleDoGradientFill"), m_bDoGradientFill,1);
	PX_String (pPX, _T ("TitleText"), m_strTitle,_T ("Title"));
	PX_String (pPX, _T ("StatusText"), m_strText,_T ("Status"));
	PX_Short (pPX, _T ("StatusTextFontSize"), m_nFontSize,16);
	PX_ULong (pPX, _T ("StatusTextColor"), m_clrTextColor,RGB(255,255,255));
	PX_ULong (pPX, _T ("StatusTextBackColor"), m_cltBkColor,RGB(0,255,0));
	PX_Short (pPX, _T ("StatusBlink"), m_bBlink,FALSE);
	PX_Short (pPX, _T ("StatusState"), m_nState,0);
	PX_ULong (pPX, _T ("TitleTextBackColor"), m_TitleTextBackColor,RGB(155,155,155));
	PX_ULong (pPX, _T ("StatusBlinkOnTime"), m_StatusBlinkOnTime,700);
	PX_ULong (pPX, _T ("StatusBlinkOffTime"), m_StatusBlinkOffTime,300);

	for (int i=0; i< MAX_STATUS_STATES;i++)
	{
		strPropName.Format(_T("Text%d"),i);
		PX_String (pPX,strPropName,m_StatusData[i].strText,_T("Status"));
		strPropName.Format(_T("Blink%d"),i);
		PX_Bool (pPX,strPropName,m_StatusData[i].bBlink,FALSE);
		strPropName.Format(_T("TextColor%d"),i);
		PX_ULong (pPX,strPropName,m_StatusData[i].clrTextColor,RGB(255,255,255));
		strPropName.Format(_T("BkColor%d"),i);
		PX_ULong (pPX,strPropName,m_StatusData[i].clrBkColor,RGB(0,255,0));
	}


	//PX_Double (pPX, _T ("TitleRed"),m_nRed,192);
	//PX_Double (pPX, _T ("TitleGreen"),m_nGreen,192);
	//PX_Double (pPX, _T ("TitleBlue"),m_nBlue,192);


}


// CGDIStatusBoxCtrl::OnDraw - Drawing function

void CGDIStatusBoxCtrl::OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
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
	font.CreatePointFont (m_nTitleFontSize*10, _T ("Microsoft Sans Serif"));
	CFont* pOldFont = dcMem.SelectObject (&font);

	// Adjust the title rectangle and draw the status box
	if (m_bHasClientBox)
	{
		dcMem.GetTextMetrics (&tm);
		int cxChar = tm.tmAveCharWidth;
		int cyChar = tm.tmHeight + tm.tmExternalLeading;
		status.bottom = rect.bottom - 1;
		rect.bottom = rect.top + cyChar;
		status.top = rect.bottom + 1;
		status.right = rect.right - 1;
		status.left = rect.left + 1;

		// Draw the 3D boarder
		dcMem.Draw3dRect(status, ::GetSysColor (COLOR_3DDKSHADOW), ::GetSysColor (COLOR_3DHILIGHT));
		status.DeflateRect(1,1);
		dcMem.Draw3dRect(status, ::GetSysColor (COLOR_3DSHADOW), ::GetSysColor (COLOR_3DHILIGHT));
		status.DeflateRect(1,1);

		// fill the Status rectangle
		PaintStatusRect(&dcMem,status,m_cltBkColor,m_clrTextColor,m_strText);
	}

	// Draw the Title
	DrawTitle(&dcMem,rect);

	// Display to screen
	pdc->BitBlt (rcBounds.left, rcBounds.top, size.x,size.y, &dcMem, org.x, org.y, SRCCOPY);
	
	// Restore the DC
	dcMem.SelectObject (pOldBitmap);
	dcMem.SelectObject (pOldFont);

	// Blink Timer
	if (m_bBlink==1)
	{
		if (!m_bTimerRunning)
		{
			if (GetSafeHwnd() != 0)
			{
				SetTimer(1,1000,NULL);
				m_bTimerRunning = TRUE;
			}
		}
	}

#if 0
	// Bitmap drawing
	//////////////////////////////////////////////////
	BITMAP bm;
    m_Button.GetBitmap (&bm);
    CPoint size (bm.bmWidth, bm.bmHeight);
    pdc->DPtoLP (&size);
    CPoint org (0, 0);
    pdc->DPtoLP (&org);
    CDC dcMem;
    dcMem.CreateCompatibleDC (pdc);
    CBitmap* pOldBitmap = dcMem.SelectObject (&m_Button);
    dcMem.SetMapMode (pdc->GetMapMode ());
	pdc->StretchBlt (0, 0, rect.Width(),rect.Height(), &dcMem, 0, 0, size.x, size.y, SRCCOPY);
    //pdc->BitBlt (0, 0, size.x, size.y, &dcMem, org.x, org.y, SRCCOPY);
    dcMem.SelectObject (pOldBitmap);
	//////////////////////////////////////////////////
#endif
}
void CGDIStatusBoxCtrl::DrawTitle(CDC *pDC,const CRect& Rect)
{
	CRect rect =  Rect;

	if (m_bDoGradientFill)
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
	pDC->SetTextColor (m_clrTitleTextColor);
	pDC->DrawText (m_strTitle, -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

}
void CGDIStatusBoxCtrl::DoGradientFill(CDC *pDC,const CRect& Rect)
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
void CGDIStatusBoxCtrl::PaintStatusRect(CDC* pDC,const CRect& Rect,COLORREF clrBK,COLORREF clrText,LPCTSTR lpText)
{
	CRect rcText = Rect;

	// Create the font and select it
	CFont font;
	font.CreatePointFont (m_nFontSize*10, _T ("Microsoft Sans Serif"));
	CFont* pOldFont = pDC->SelectObject (&font);

	CBrush Brush;
	Brush.CreateSolidBrush(clrBK);

	// Draw in memory
	pDC->FillRect(&Rect,&Brush);
    pDC->SetBkMode (TRANSPARENT);
	pDC->SetTextColor (clrText);
	pDC->DrawText (lpText, -1, &rcText, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

	// Restore the DC
	pDC->SelectObject (pOldFont);


}

int CGDIStatusBoxCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (COleControl::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}

void CGDIStatusBoxCtrl::OnTimer(UINT_PTR nIDEvent)
{

	// Blink Timer
	if (!m_bBlink)
	{
		m_bTimerRunning = FALSE;
		KillTimer(1);
		if (!m_bBlinkOn)
			return;
	}

	// Blink is ON
	if (m_bBlinkOn)
	{
		m_bBlinkOn = FALSE;
		m_cltBkColor   = m_StatusData[m_nState].clrBkColor;
		m_clrTextColor = m_StatusData[m_nState].clrTextColor;
		if (m_bBlink)
		{
			SetTimer(1,m_StatusBlinkOnTime,NULL);
		}
	}
	// Blink is OFF
	else
	{
		m_bBlinkOn = TRUE;
		m_cltBkColor   = m_StatusData[m_nState].clrTextColor;
		m_clrTextColor = m_StatusData[m_nState].clrBkColor;
		if (m_bBlink)
		{
			SetTimer(1,m_StatusBlinkOffTime,NULL);
		}
	}

	InvalidateControl();

}


// CGDIStatusBoxCtrl::OnResetState - Reset control to default state

void CGDIStatusBoxCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange
	// Reset any other control state here.
}



// CGDIStatusBoxCtrl::AboutBox - Display an "About" box to the user

void CGDIStatusBoxCtrl::AboutBox()
{
	CDialogEx dlgAbout(IDD_ABOUTBOX_GDISTATUSBOX);
	dlgAbout.DoModal();
}

// CGDIStatusBoxCtrl message handlers

void CGDIStatusBoxCtrl::OnnFontSizeChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
	InvalidateControl();
}

void CGDIStatusBoxCtrl::OnstrTitleChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
	InvalidateControl();
}

void CGDIStatusBoxCtrl::OnbHasClientBoxChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
	InvalidateControl();
}

void CGDIStatusBoxCtrl::OnstrTextChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	m_StatusData[m_nState].strText       = m_strText;
	SetModifiedFlag();
	InvalidateControl();
}

void CGDIStatusBoxCtrl::OnclrTextColorChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	m_StatusData[m_nState].clrTextColor  = m_clrTextColor;
	SetModifiedFlag();
	InvalidateControl();
}


void CGDIStatusBoxCtrl::OncltBkColorChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	m_StatusData[m_nState].clrBkColor    = m_cltBkColor; 
	SetModifiedFlag();
	InvalidateControl();
}


void CGDIStatusBoxCtrl::OnbBlinkChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	m_StatusData[m_nState].bBlink        = m_bBlink;
	//TRACE(_T("Blink changed"));
	SetModifiedFlag();
	InvalidateControl();
}


SHORT CGDIStatusBoxCtrl::GetState(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if (m_nState > MAX_STATUS_STATES-1)
		m_nState = MAX_STATUS_STATES-1;
	if (m_nState < 0)
		m_nState = 0;

	return m_nState;
}


void CGDIStatusBoxCtrl::SetState(SHORT newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	int nState = newVal;
	if (nState < 0)
		nState = 0;
	if (nState > MAX_STATUS_STATES-1)
		nState = MAX_STATUS_STATES-1;

	// Show the state data
	m_cltBkColor   = m_StatusData[nState].clrBkColor;
	m_clrTextColor = m_StatusData[nState].clrTextColor;
	m_strText      = m_StatusData[nState].strText;
	m_bBlink       = m_StatusData[nState].bBlink;

	if (nState == m_nState)
		return;

	m_nState = nState;
	SetModifiedFlag();
	InvalidateControl();
}

void CGDIStatusBoxCtrl::OnnTitleFontSizeChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
	InvalidateControl();
}

void CGDIStatusBoxCtrl::OnclrTitleTextColorChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
	InvalidateControl();
}


void CGDIStatusBoxCtrl::OnbDoGradientFillChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
	InvalidateControl();
}


void CGDIStatusBoxCtrl::OnTitleTextBackColorChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
	InvalidateControl();
}


void CGDIStatusBoxCtrl::OnStatusBlinkOnTimeChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
	InvalidateControl();
}


void CGDIStatusBoxCtrl::OnStatusBlinkOffTimeChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
	InvalidateControl();
}
