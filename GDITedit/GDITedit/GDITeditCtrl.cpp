// GDITeditCtrl.cpp : Implementation of the CGDITeditCtrl ActiveX Control class.

#include "stdafx.h"
#include "GDITedit.h"
#include "GDITeditCtrl.h"
#include "GDITeditPropPage.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CGDITeditCtrl, COleControl)



// Message map

BEGIN_MESSAGE_MAP(CGDITeditCtrl, COleControl)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()



// Dispatch map

BEGIN_DISPATCH_MAP(CGDITeditCtrl, COleControl)
	DISP_FUNCTION_ID(CGDITeditCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
	DISP_PROPERTY_NOTIFY_ID(CGDITeditCtrl, "TitleFontSize", dispidTitleFontSize, m_TitleFontSize, OnTitleFontSizeChanged, VT_I2)
	DISP_PROPERTY_NOTIFY_ID(CGDITeditCtrl, "TitleTextColor", dispidTitleTextColor, m_TitleTextColor, OnTitleTextColorChanged, VT_COLOR)
	DISP_PROPERTY_NOTIFY_ID(CGDITeditCtrl, "TitleBackColor", dispidTitleBackColor, m_TitleBackColor, OnTitleBackColorChanged, VT_COLOR)
	DISP_PROPERTY_NOTIFY_ID(CGDITeditCtrl, "TitleText", dispidTitleText, m_TitleText, OnTitleTextChanged, VT_BSTR)
	DISP_PROPERTY_NOTIFY_ID(CGDITeditCtrl, "TextFontSize", dispidTextFontSize, m_TextFontSize, OnTextFontSizeChanged, VT_I2)
	DISP_PROPERTY_NOTIFY_ID(CGDITeditCtrl, "TextColor", dispidTextColor, m_TextColor, OnTextColorChanged, VT_COLOR)
	DISP_PROPERTY_NOTIFY_ID(CGDITeditCtrl, "TextBackColor", dispidTextBackColor, m_TextBackColor, OnTextBackColorChanged, VT_COLOR)
	DISP_PROPERTY_NOTIFY_ID(CGDITeditCtrl, "TitleDoGradientFill", dispidTitleDoGradientFill, m_TitleDoGradientFill, OnTitleDoGradientFillChanged, VT_I2)
	DISP_FUNCTION_ID(CGDITeditCtrl, "GetValue", dispidGetValue, GetValue, VT_R8, VTS_NONE)
	DISP_FUNCTION_ID(CGDITeditCtrl, "SetValue", dispidSetValue, SetValue, VT_EMPTY, VTS_R8)
	DISP_PROPERTY_NOTIFY_ID(CGDITeditCtrl, "MinValue", dispidMinValue, m_MinValue, OnMinValueChanged, VT_R8)
	DISP_PROPERTY_NOTIFY_ID(CGDITeditCtrl, "MaxValue", dispidMaxValue, m_MaxValue, OnMaxValueChanged, VT_R8)
	DISP_PROPERTY_NOTIFY_ID(CGDITeditCtrl, "Width", dispidWidth, m_Width, OnWidthChanged, VT_I2)
	DISP_PROPERTY_NOTIFY_ID(CGDITeditCtrl, "Precision", dispidPrecision, m_Precision, OnPrecisionChanged, VT_I2)
	DISP_PROPERTY_NOTIFY_ID(CGDITeditCtrl, "Units", dispidUnits, m_Units, OnUnitsChanged, VT_BSTR)
	DISP_PROPERTY_NOTIFY_ID(CGDITeditCtrl, "HasTitle", dispidHasTitle, m_HasTitle, OnHasTitleChanged, VT_I2)
	DISP_PROPERTY_NOTIFY_ID(CGDITeditCtrl, "EditEnable", dispidEditEnable, m_EditEnable, OnEditEnableChanged, VT_I2)
END_DISPATCH_MAP()


// CGDITeditCtrl::DoPropExchange - Persistence support

void CGDITeditCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// Call PX_ functions for each persistent custom property.
	PX_Short (pPX, _T ("TitleFontSize"), m_TitleFontSize,16);
	PX_ULong (pPX, _T ("TitleTextColor"), m_TitleTextColor,RGB(255,255,255));
	PX_ULong (pPX, _T ("TitleBackColor"), m_TitleBackColor,RGB(155,55,155));
	PX_String (pPX, _T ("TitleText"), m_TitleText,_T ("Title"));
	PX_Short (pPX, _T ("TextFontSize"), m_TextFontSize,16);
	PX_ULong (pPX, _T ("TextColor"), m_TextColor,RGB(0,255,255));
	PX_ULong (pPX, _T ("TextBackColor"), m_TextBackColor,RGB(0,255,255));
	PX_Short (pPX, _T ("TitleDoGradientFill"), m_TitleDoGradientFill,1);
	double dbValue = GetValue();
	PX_Double (pPX, _T ("Value"),dbValue);
	PX_Double (pPX, _T ("MinValue"),m_MinValue,0);
	PX_Double (pPX, _T ("MaxValue"),m_MaxValue,0);
	PX_Short (pPX, _T ("Width"), m_Width,0);
	PX_Short (pPX, _T ("Precision"), m_Precision,0);
	PX_String (pPX, _T ("Units"), m_Units,_T (""));
	PX_Short (pPX, _T ("HasTitle"), m_HasTitle,1);
	PX_Short (pPX, _T ("EditEnable"), m_EditEnable,1);

}


// Event map

BEGIN_EVENT_MAP(CGDITeditCtrl, COleControl)
	EVENT_STOCK_CLICK()
	EVENT_STOCK_MOUSEDOWN()
	EVENT_STOCK_MOUSEUP()
END_EVENT_MAP()



// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CGDITeditCtrl, 1)
	PROPPAGEID(CGDITeditPropPage::guid)
END_PROPPAGEIDS(CGDITeditCtrl)



// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CGDITeditCtrl, "GDITEDIT.GDITeditCtrl.1",
	0xfcccba48, 0xbcbf, 0x42f9, 0x9d, 0xa4, 0x7, 0x32, 0x2, 0xaf, 0x82, 0xe8)



// Type library ID and version

IMPLEMENT_OLETYPELIB(CGDITeditCtrl, _tlid, _wVerMajor, _wVerMinor)



// Interface IDs

const IID IID_DGDITedit = { 0x1B573CE3, 0x605E, 0x4247, { 0xB7, 0xC, 0x85, 0x5F, 0xBD, 0x55, 0x73, 0x4D } };
const IID IID_DGDITeditEvents = { 0x42250EBE, 0x117, 0x4674, { 0x9E, 0x5, 0x75, 0x0, 0x7A, 0x9, 0x15, 0xB5 } };


// Control type information

static const DWORD _dwGDITeditOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CGDITeditCtrl, IDS_GDITEDIT, _dwGDITeditOleMisc)



// CGDITeditCtrl::CGDITeditCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CGDITeditCtrl

BOOL CGDITeditCtrl::CGDITeditCtrlFactory::UpdateRegistry(BOOL bRegister)
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
			IDS_GDITEDIT,
			IDB_GDITEDIT,
			afxRegApartmentThreading,
			_dwGDITeditOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}



// CGDITeditCtrl::CGDITeditCtrl - Constructor

CGDITeditCtrl::CGDITeditCtrl()
{
	InitializeIIDs(&IID_DGDITedit, &IID_DGDITeditEvents);
	
	//Initialize your control's data
	m_dbValue = 0.0;
	m_bSwapColors = FALSE;
}



// CGDITeditCtrl::~CGDITeditCtrl - Destructor

CGDITeditCtrl::~CGDITeditCtrl()
{
	// TODO: Cleanup your control's instance data here.
}



// CGDITeditCtrl::OnDraw - Drawing function

void CGDITeditCtrl::OnDraw(	CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
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
	status = rect;
	if (m_HasTitle==1)
	{
		dcMem.GetTextMetrics (&tm);
		int cxChar = tm.tmAveCharWidth;
		int cyChar = tm.tmHeight + tm.tmExternalLeading;
		status.bottom = rect.bottom - 1;
		rect.bottom = rect.top + cyChar;
		status.top = rect.bottom + 1;
		status.right = rect.right - 1;
		status.left = rect.left + 1;
	}

	// Draw the 3D boarder
	dcMem.Draw3dRect(status, ::GetSysColor (COLOR_3DDKSHADOW), ::GetSysColor (COLOR_3DHILIGHT));
	status.DeflateRect(1,1);
	dcMem.Draw3dRect(status, ::GetSysColor (COLOR_3DSHADOW), ::GetSysColor (COLOR_3DHILIGHT));
	status.DeflateRect(1,1);

	// fill the Status rectangle
	m_status = status;
	PaintStatusRect(&dcMem,status,m_TextBackColor,m_TextColor);

	// Draw the Title
	if (m_HasTitle==1)
	{
		DrawTitle(&dcMem,rect);
	}

	// Display to screen
	pdc->BitBlt (rcBounds.left, rcBounds.top, size.x,size.y, &dcMem, org.x, org.y, SRCCOPY);
	
	// Restore the DC
	dcMem.SelectObject (pOldBitmap);
	dcMem.SelectObject (pOldFont);
}

void CGDITeditCtrl::DrawTitle(CDC *pDC,const CRect& Rect)
{
	CRect rect =  Rect;

	if (m_TitleDoGradientFill)
	{
		DoGradientFill(pDC,Rect);
	}
	else
	{
		CBrush Brush;
		Brush.CreateSolidBrush(m_TitleBackColor);
		pDC->FillRect(&rect,&Brush);
	}
	pDC->SetBkMode (TRANSPARENT);
	pDC->SetTextColor (m_TitleTextColor);
	pDC->DrawText (m_TitleText, -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

}
void CGDITeditCtrl::DoGradientFill(CDC *pDC,const CRect& Rect)
{
	//m_TitleTextBackColor = RGB(255,0,0);
	double dbR = (double)GetRValue(m_TitleBackColor)/255.0;
	double dbG = (double)GetGValue(m_TitleBackColor)/255.0;
	double dbB = (double)GetBValue(m_TitleBackColor)/255.0;
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
void CGDITeditCtrl::PaintStatusRect(CDC* pDC,const CRect& Rect,COLORREF clrBK,COLORREF clrText)
{
	CRect rcText = Rect;
	CString str;

	// Format the string
	str.Format(_T("%*.*f"),m_Width,m_Precision,m_dbValue);
	str += m_Units;
	//TRACE("Tedit m_nWidth:%d m_nPrecision:%d \n",m_nWidth,m_nPrecision);

	// Create the font and select it
	CFont font;
	font.CreatePointFont (m_TextFontSize*10, _T ("Microsoft Sans Serif"));
	CFont* pOldFont = pDC->SelectObject (&font);

	CBrush Brush;
	Brush.CreateSolidBrush(clrBK);

	// Draw in memory
	pDC->FillRect(&Rect,&Brush);
    pDC->SetBkMode (TRANSPARENT);
	pDC->SetTextColor (clrText);
	pDC->DrawText (str, -1, &rcText, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

	// Restore the DC
	pDC->SelectObject (pOldFont);

}



// CGDITeditCtrl::OnResetState - Reset control to default state

void CGDITeditCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}



// CGDITeditCtrl::AboutBox - Display an "About" box to the user

void CGDITeditCtrl::AboutBox()
{
	CDialogEx dlgAbout(IDD_ABOUTBOX_GDITEDIT);
	dlgAbout.DoModal();
}



// CGDITeditCtrl message handlers


void CGDITeditCtrl::OnTitleFontSizeChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
	InvalidateControl();
}


void CGDITeditCtrl::OnTitleTextColorChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
	InvalidateControl();
}


void CGDITeditCtrl::OnTitleBackColorChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
	InvalidateControl();
}


void CGDITeditCtrl::OnTitleTextChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	SetModifiedFlag();
	InvalidateControl();
}


void CGDITeditCtrl::OnTextFontSizeChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
	InvalidateControl();
}


void CGDITeditCtrl::OnTextColorChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
	InvalidateControl();
}


void CGDITeditCtrl::OnTextBackColorChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
	InvalidateControl();
}

void CGDITeditCtrl::OnTitleDoGradientFillChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
	InvalidateControl();
}

void CGDITeditCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
//	if (!m_status.PtInRect(point))
//		return;
	COleControl::OnLButtonDown(nFlags, point);
	if (m_EditEnable==0)
		return;

	// Swap colors
	SetCapture();
	m_bSwapColors = TRUE;
	SwapColors();
	InvalidateControl();
	//	pWnd->SendMessage(WM_COMMAND,MAKEWPARAM(GetDlgCtrlID(),BN_CLICKED),(LPARAM)m_hWnd);
}
void CGDITeditCtrl::OnLButtonUp(UINT nFlags, CPoint point)
{
 //   if (GetCapture () == this)
	//   ::ReleaseCapture ();
	//if (!m_status.PtInRect(point))
	//	return;
	COleControl::OnLButtonUp(nFlags, point);
	if (m_bSwapColors==FALSE)
	{
		//TRACE("m_bSwapColors==FALSE \n");
		return;
	}

	//TRACE("OnLButtonUp \n");
	m_bSwapColors = FALSE;
	SwapColors();
	InvalidateControl();
//    if (GetCapture () == this)
//	   ::ReleaseCapture ();
//	else
//		return;
}

void CGDITeditCtrl::SwapColors()
{
	COLORREF clrSwap = m_TextColor;
	m_TextColor = m_TextBackColor;
	m_TextBackColor = clrSwap;
}

DOUBLE CGDITeditCtrl::GetValue(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return m_dbValue;
}

void CGDITeditCtrl::SetValue(DOUBLE dbValue)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	//TRACE("CGDITeditCtrl::SetValue %f \n",dbValue);
    if (GetCapture () == this)
		return;

	// Limit range
	if (m_MinValue != m_MaxValue)
	{
		if (dbValue < m_MinValue)			
			dbValue = m_MinValue;
		if (dbValue > m_MaxValue)			
			dbValue = m_MaxValue;
	}
	m_dbValue = dbValue;

	//TRACE("CGDITeditCtrl::m_MinValue %f \n",m_MinValue);
	//TRACE("CGDITeditCtrl::m_MaxValue %f \n",m_MaxValue);
	//TRACE("CGDITeditCtrl::SetValue %f \n",dbValue);

	SetModifiedFlag();
	//TRACE("Setvalue \n\n");
	if (m_bSwapColors==TRUE){
		//TRACE("m_bSwapColors==TRUE \n");
		m_bSwapColors = FALSE;
		SwapColors();
	}

	//if (m_dbValue != dbValue){
	//	m_dbValue = dbValue;
	InvalidateControl();
	//}
	//m_dbValue = dbValue;

}

void CGDITeditCtrl::OnMinValueChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
	InvalidateControl();
}

void CGDITeditCtrl::OnMaxValueChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
	InvalidateControl();
}

void CGDITeditCtrl::OnWidthChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
	InvalidateControl();
}

void CGDITeditCtrl::OnPrecisionChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
	InvalidateControl();
}

void CGDITeditCtrl::OnUnitsChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
	InvalidateControl();
}

void CGDITeditCtrl::OnHasTitleChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
	InvalidateControl();
}

void CGDITeditCtrl::OnEditEnableChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
	InvalidateControl();
}
