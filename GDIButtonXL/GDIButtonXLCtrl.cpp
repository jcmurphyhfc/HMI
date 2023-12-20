// GDIButtonXLCtrl.cpp : Implementation of the CGDIButtonXLCtrl ActiveX Control class.

#include "stdafx.h"
#include "GDIButtonXL.h"
#include "GDIButtonXLCtrl.h"
#include "GDIButtonXLPropPage.h"
#include "afxdialogex.h"
#include "InitGDIPlus.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

static InitGDIPlus GDI_Plus_Controler;


IMPLEMENT_DYNCREATE(CGDIButtonXLCtrl, COleControl)

// Message map

BEGIN_MESSAGE_MAP(CGDIButtonXLCtrl, COleControl)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// NOTE: The order of the dispatch map must match the id order. Keep "Text1" and "Text2" in last position
// Dispatch map 

BEGIN_DISPATCH_MAP(CGDIButtonXLCtrl, COleControl)
	DISP_FUNCTION_ID(CGDIButtonXLCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CGDIButtonXLCtrl, "SetLight", dispidSetLight, SetLight, VT_EMPTY, VTS_BOOL)

	DISP_PROPERTY_NOTIFY_ID(CGDIButtonXLCtrl, "TextOffset1", dispidTextOffset1, m_TextOffset1, OnTextOffset1Changed, VT_I4)
	DISP_PROPERTY_NOTIFY_ID(CGDIButtonXLCtrl, "TextOffset2", dispidTextOffset2, m_TextOffset2, OnTextOffset2Changed, VT_I4)
	DISP_PROPERTY_NOTIFY_ID(CGDIButtonXLCtrl, "LightOn", dispidLightOn, m_LightOn, OnLightOnChanged, VT_BOOL)
	DISP_PROPERTY_NOTIFY_ID(CGDIButtonXLCtrl, "TextColor", dispidTextColor, m_TextColor, OnTextColorChanged, VT_COLOR)
	DISP_PROPERTY_NOTIFY_ID(CGDIButtonXLCtrl, "FontSize", dispidFontSize, m_FontSize, OnFontSizeChanged, VT_I4)
	DISP_PROPERTY_NOTIFY_ID(CGDIButtonXLCtrl, "BitMapSelect", dispidBitMapSelect, m_BitMapSelect, OnBitMapSelectChanged, VT_I4)

	//DISP_PROPERTY_NOTIFY(CGDIButtonXLCtrl, "Text1", m_strLabelText1, OnText1Changed, VT_BSTR)
	//DISP_PROPERTY_NOTIFY(CGDIButtonXLCtrl, "Text2", m_strLabelText2, OnText2Changed, VT_BSTR)

	DISP_PROPERTY_NOTIFY_ID(CGDIButtonXLCtrl, "Text1", dispidstrTitle1, m_strLabelText1, OnText1Changed, VT_BSTR)
	DISP_PROPERTY_NOTIFY_ID(CGDIButtonXLCtrl, "Text2", dispidstrTitle2, m_strLabelText2, OnText2Changed, VT_BSTR)


END_DISPATCH_MAP()


//	DISP_PROPERTY_EX_ID(CGDIButtonXLCtrl, "FontSize", dispidFontSize, GetFontSize, SetFontSize, VT_I2)

// Event map

BEGIN_EVENT_MAP(CGDIButtonXLCtrl, COleControl)
	EVENT_STOCK_CLICK()
	EVENT_STOCK_MOUSEDOWN()
	EVENT_STOCK_MOUSEUP()
END_EVENT_MAP()



// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CGDIButtonXLCtrl, 1)
	PROPPAGEID(CGDIButtonXLPropPage::guid)
END_PROPPAGEIDS(CGDIButtonXLCtrl)

//	PROPPAGEID (CLSID_CColorPropPage)


// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CGDIButtonXLCtrl, "GDIBUTTONXL.GDIButtonXLCtrl.1",
	0x7f078f87, 0x2f90, 0x4a93, 0xa0, 0x93, 0xa5, 0x19, 0xf6, 0xc5, 0x45, 0xdc)



// Type library ID and version

IMPLEMENT_OLETYPELIB(CGDIButtonXLCtrl, _tlid, _wVerMajor, _wVerMinor)



// Interface IDs

const IID IID_DGDIButtonXL = { 0xB28DFE52, 0x8499, 0x4AD4, { 0xAE, 0x4C, 0xDF, 0x4F, 0xC2, 0x92, 0xAB, 0xB8 } };
const IID IID_DGDIButtonXLEvents = { 0x408FF230, 0x3234, 0x46D8, { 0xAE, 0xC6, 0x28, 0x8C, 0xB7, 0xB7, 0x43, 0x37 } };


// Control type information

static const DWORD _dwGDIButtonXLOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CGDIButtonXLCtrl, IDS_GDIBUTTONXL, _dwGDIButtonXLOleMisc)



// CGDIButtonXLCtrl::CGDIButtonXLCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CGDIButtonXLCtrl

BOOL CGDIButtonXLCtrl::CGDIButtonXLCtrlFactory::UpdateRegistry(BOOL bRegister)
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
			IDS_GDIBUTTONXL,
			IDB_GDIBUTTONXL,
			afxRegApartmentThreading,
			_dwGDIButtonXLOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}



// CGDIButtonXLCtrl::CGDIButtonXLCtrl - Constructor

CGDIButtonXLCtrl::CGDIButtonXLCtrl()
{
	InitializeIIDs(&IID_DGDIButtonXL, &IID_DGDIButtonXLEvents);

	// GDI_Plus_Controler is a static global
	GDI_Plus_Controler.Initialize();

	// Initialize control's instance data.
	m_bButtonDown = FALSE;
	m_bBitmapsLoaded = false;
	m_bBitmapsGenerated = false;
	m_bGenerateBitmap = true;
	//m_bLightOn = false;
	m_bButtonDownMessage = true;
	//m_clrText = RGB(0,0,0);
	m_strOldButtonText1 = _T("");
	m_strOldButtonText2 = _T("");
	//LoadBitMaps(IDB_GREEN_OFF_UP,IDB_GREEN_ON_UP,IDB_GREEN_OFF_DN,IDB_GREEN_ON_DN);
	
}

// CGDIButtonXLCtrl::~CGDIButtonXLCtrl - Destructor

CGDIButtonXLCtrl::~CGDIButtonXLCtrl()
{
	 // GDI_Plus_Controler is a static global
	GDI_Plus_Controler.Deinitialize();
}


// CGDIButtonXLCtrl::OnDraw - Drawing function

void CGDIButtonXLCtrl::OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	if (!pdc) return;

	// Size Change
	if (m_rectCurrent != rcBounds)
	{
		m_bGenerateBitmap = true;
	}

	// Save the current size
	m_rectCurrent = rcBounds;

	// Generate bitmaps
	GenBitMaps(pdc,rcBounds);

	// Draw
	if (m_bButtonDown)
	{
		DrawLampDown(pdc,rcBounds);
	}
	else
	{
		DrawLampUp(pdc,rcBounds);
	}

}

// CGDIButtonXLCtrl::DoPropExchange - Persistence support

void CGDIButtonXLCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// Call PX_ functions for each persistent custom property.
	PX_String (pPX, _T ("Text1"), m_strLabelText1,_T("Line 1"));
	PX_String (pPX, _T ("Text2"), m_strLabelText2,_T("Line 2"));
	PX_Long (pPX, _T ("BitMapSelect"), m_BitMapSelect,0);
	PX_Long (pPX, _T ("FontSize"), m_FontSize,14);
	PX_Color(pPX, _T ("TextColor"), m_TextColor,OLE_COLOR (RGB (192, 192, 192)));
	PX_Bool (pPX, _T ("LightOn"), m_bLightOn,FALSE);
	PX_Long (pPX, _T ("TextOffset1"), m_TextOffset1,10);
	PX_Long (pPX, _T ("TextOffset2"), m_TextOffset2,-10);

	//PX_Short (pPX, _T ("FontSize"), m_nFontSize,16);
	//PX_Bool (pPX, _T ("TitleOnly"), m_bTitleOnly,TRUE);
	//PX_Long (pPX, _T ("UpDateTime"),m_lnUpDateTime,500);
	//PX_ULong (pPX, _T ("TextColorState1"), m_textColorState1,RGB(0,255,0));
    //	CBrush brush (TranslateColor (AmbientBackColor ()));
    //pdc->FillRect (rcBounds, &brush);
    //	(OLE_COLOR (RGB (192, 192, 192)));



}



// CGDIButtonXLCtrl::OnResetState - Reset control to default state

void CGDIButtonXLCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}

// CGDIButtonXLCtrl::AboutBox - Display an "About" box to the user

void CGDIButtonXLCtrl::AboutBox()
{
	CDialogEx dlgAbout(IDD_ABOUTBOX_GDIBUTTONXL);
	dlgAbout.DoModal();
}

void CGDIButtonXLCtrl::GenBitMaps(CDC* pDC,const CRect& rect)
{
	if (!m_bGenerateBitmap)
		return;

	m_bGenerateBitmap = false;

	if (m_bBitmapsGenerated)
	{
		m_DownOff.DeleteObject();
		m_DownOn.DeleteObject();
		m_UpOff.DeleteObject();
		m_UpOn.DeleteObject();
	}

	// Bitmap change
	switch (m_BitMapSelect)
	{
	case 0:
		LoadBitMaps(IDB_GREEN_OFF_UP,IDB_GREEN_ON_UP,IDB_GREEN_OFF_DN,IDB_GREEN_ON_DN);
		break;
	case 1:
		LoadBitMaps(IDB_BLUE_OFF_UP,IDB_BLUE_ON_UP,IDB_BLUE_OFF_DN,IDB_BLUE_ON_DN);
		break;
	case 2:
		LoadBitMaps(IDB_RED_OFF_UP,IDB_RED_ON_UP,IDB_RED_OFF_DN,IDB_RED_ON_DN);
		break;
	case 3:
		LoadBitMaps(IDB_AMBER_OFF_UP,IDB_AMBER_ON_UP,IDB_AMBER_OFF_DN,IDB_AMBER_ON_DN);
		break;
	case 4:
		LoadBitMaps(IDB_REDNOLED_UP,IDB_REDNOLED_UP,IDB_REDNOLED_DN,IDB_REDNOLED_DN);
		break;
	case 5:
		LoadBitMaps(IDB_RECT_BLUE_OFF_UP,IDB_RECT_BLUE_ON_UP,IDB_RECT_BLUE_OFF_DN,IDB_RECT_BLUE_ON_DN);
		break;
	case 6:
		//          OFF UP              ON UP                OFF Down             ON Down
		LoadBitMaps(IDB_RECT_RED_ON_UP, IDB_RECT_GREEN_ON_UP,IDB_RECT_RED_ON_UP  ,IDB_RECT_GREEN_ON_UP);
		break;
	case 7:
		LoadBitMaps(IDB_RECT_BLUE_OFF_UP,IDB_RECT_BLUE_ON_UP,IDB_RECT_BLUE_OFF_DN,IDB_RECT_BLUE_ON_DN);
		break;
	case 8:
		//          OFF UP              ON UP                OFF Down             ON Down
		LoadBitMaps(IDB_RECT_RED_OFF_UP,IDB_RECT_RED_ON_UP, IDB_RECT_RED_OFF_UP,IDB_RECT_RED_OFF_UP);
		break;

	default:
		LoadBitMaps(IDB_RECT_BLUE_OFF_UP,IDB_RECT_BLUE_ON_UP,IDB_RECT_BLUE_OFF_DN,IDB_RECT_BLUE_ON_DN);
		break;
	}

	CRect rcTextUp,rcTextDn;
	rcTextUp = rect;
	rcTextDn = rect;
	rcTextDn.DeflateRect(2,2,0,0);

	CDC dcMem;
	dcMem.CreateCompatibleDC (pDC);

	CPalette palette;
	palette.CreateHalftonePalette (pDC);

	// Create the bitmaps
	m_DownOff.CreateCompatibleBitmap (pDC, rect.Width(),rect.Height());
	m_DownOn.CreateCompatibleBitmap (pDC, rect.Width(),rect.Height());
	m_UpOff.CreateCompatibleBitmap (pDC, rect.Width(),rect.Height());
	m_UpOn.CreateCompatibleBitmap (pDC, rect.Width(),rect.Height());

	// Create the Bitmaps from CBitmaps
	Bitmap UpOff((HBITMAP)m_bitmapUpOff,(HPALETTE)palette);
	Bitmap UpOn((HBITMAP)m_bitmapUpOn,(HPALETTE)palette);
	Bitmap DownOff((HBITMAP)m_bitmapDownOff,(HPALETTE)palette);
	Bitmap DownOn((HBITMAP)m_bitmapDownOn,(HPALETTE)palette);

	// Draw UpOff
	CBitmap* pOldBitmap = dcMem.SelectObject (&m_UpOff);
	Graphics graphics(dcMem.m_hDC);
	graphics.DrawImage(&UpOff,0,0,rect.Width(),rect.Height());				
	if (m_BitMapSelect > FULL_LED_SELECTED)
	{
		DoDrawButtonText(&dcMem,&rcTextUp);
	}
	else
	{
		DoDrawText(&dcMem,rect);
	}

	// Draw UpOn
	dcMem.SelectObject (&m_UpOn);
	graphics.DrawImage(&UpOn,0,0,rect.Width(),rect.Height());				
	if (m_BitMapSelect > FULL_LED_SELECTED)
	{
		DoDrawButtonText(&dcMem,&rcTextUp);
	}
	else
	{
		DoDrawText(&dcMem,rect);
	}

	// Draw DnOff
	dcMem.SelectObject (&m_DownOff);
	graphics.DrawImage(&DownOff,0,0,rect.Width(),rect.Height());				
	if (m_BitMapSelect > FULL_LED_SELECTED)
	{
		DoDrawButtonText(&dcMem,&rcTextDn);
	}
	else
	{
		DoDrawText(&dcMem,rect);
	}

	// Draw DnOn
	dcMem.SelectObject (&m_DownOn);
	graphics.DrawImage(&DownOn,0,0,rect.Width(),rect.Height());				
	if (m_BitMapSelect > FULL_LED_SELECTED)
	{
		DoDrawButtonText(&dcMem,&rcTextDn);
	}
	else
	{
		DoDrawText(&dcMem,rect);
	}

	// Select old
	dcMem.SelectObject (pOldBitmap);
	m_bBitmapsGenerated = true;

}
void CGDIButtonXLCtrl::DrawLampUp(CDC* pDC,const CRect& rect)
{
	//CRect rect;
	//GetClientRect(&rect);

    CBitmap* pOldBitmap;
    CDC dcMem;
    dcMem.CreateCompatibleDC (pDC);

	if (m_bLightOn)
	{
		pOldBitmap = dcMem.SelectObject (&m_UpOn);
	}
	else
	{
		pOldBitmap = dcMem.SelectObject (&m_UpOff);
	}

	pDC->BitBlt (0, 0, rect.Width(),rect.Height(),&dcMem, 0, 0, SRCCOPY);
	dcMem.SelectObject (pOldBitmap);

}
void CGDIButtonXLCtrl::DoDrawButtonText(CDC* pDC,LPRECT lpRect)
{
	CRect rectTop = lpRect;
	CRect rectBot = rectTop;

	rectTop.OffsetRect(0,m_TextOffset1);
	rectBot.OffsetRect(0,m_TextOffset2);

	// Set the top rectangle
	rectTop.bottom = rectTop.top + rectTop.Height()/2;
	rectTop.top = rectTop.bottom - 25;

	// Set the bottom rectangle
	rectBot.top = rectTop.bottom;
	rectBot.bottom = rectBot.top + 25;

	LOGFONT lf;
	::ZeroMemory (&lf, sizeof (lf));
	lf.lfHeight = m_FontSize*10;
	lf.lfWeight = FW_BOLD;
	lf.lfItalic = FALSE;
	::lstrcpy (lf.lfFaceName, _T ("Times New Roman"));
	CFont font;
	font.CreatePointFontIndirect (&lf);

	CFont* pOldFont = pDC->SelectObject (&font);
	pDC->SetBkMode (TRANSPARENT);
	pDC->SetTextColor(TranslateColor(m_TextColor));

	//m_strOldButtonText1 = m_strButtonText1;
	//m_strOldButtonText2 = m_strButtonText2;

	// Text 1
	if (m_strLabelText2 == _T("")){
		pDC->DrawText (m_strLabelText1, -1, lpRect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	}
	// Text 1 and 2
	else{

		pDC->DrawText (m_strLabelText1, -1, &rectTop, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		pDC->DrawText (m_strLabelText2, -1, &rectBot, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	}

	pDC->SelectObject (pOldFont);

}


void CGDIButtonXLCtrl::SetButtonText(LPCTSTR str1,LPCTSTR str2)
{
	//if (str1 == m_strButtonText1 && str2 == m_strButtonText2){
	//	return;
	//}
	//m_DownOff.DeleteObject();
	//m_DownOn.DeleteObject();
	//m_UpOff.DeleteObject();
	//m_UpOn.DeleteObject();
	//m_strOldButtonText1 = m_strButtonText1;
//	m_strOldButtonText2 = m_strButtonText2;
	//m_strButtonText1 = str1;
	//m_strButtonText2 = str2;
	m_bGenerateBitmap = true;
	InvalidateControl();
}

void CGDIButtonXLCtrl::ResetSetButtonText()
{
//	if (m_strOldButtonText1 == m_strButtonText1 && m_strOldButtonText2 == m_strButtonText2){
//		return;
//	}
//	if (m_strOldButtonText1 == _T("") || m_strOldButtonText2 == _T("")){
//		return;
//	}
//	m_strButtonText1 = m_strOldButtonText1;
//	m_strButtonText2 = m_strOldButtonText2;
//	m_bGenerateBitmap = true;
//	InvalidateControl();
}

void CGDIButtonXLCtrl::LoadBitMaps(UINT nIDUpOff,UINT nIDUpOn,UINT nIDDownOff,UINT nIDDownOn)
{

	if (m_bBitmapsLoaded)
	{
		m_bitmapUpOff.DeleteObject();
		m_bitmapUpOn.DeleteObject();
		m_bitmapDownOff.DeleteObject();
		m_bitmapDownOn.DeleteObject();
	}

	m_bitmapUpOff.LoadBitmap(nIDUpOff);
	m_bitmapUpOn.LoadBitmap(nIDUpOn);
	m_bitmapDownOff.LoadBitmap(nIDDownOff);
	m_bitmapDownOn.LoadBitmap(nIDDownOn);
	m_bBitmapsLoaded = true;	

	//========================================================================================//
	// GDI ClearPeaks Button 
	//========================================================================================//
	//m_ClearPeaks.m_strButtonText1 = strBtnTxt1;
	//m_ClearPeaks.m_strButtonText2 = strBtnTxt2;
	//m_ClearPeaks.m_clrText = RGB(255,255,255);
	//m_ClearPeaks.LoadBitMaps(IDB_RECT_BLUE_OFF_UP,IDB_RECT_BLUE_ON_UP,IDB_RECT_BLUE_OFF_DN,IDB_RECT_BLUE_ON_DN);
	//========================================================================================//

}


void CGDIButtonXLCtrl::DrawLampDown(CDC* pDC,const CRect& rect)
{
	//CRect rect;
	//GetClientRect(&rect);

	CBitmap* pOldBitmap;
    CDC dcMem;
    dcMem.CreateCompatibleDC (pDC);

	// Light status
	if (m_bLightOn)
	{
		pOldBitmap = dcMem.SelectObject (&m_DownOn);
	}
	else
	{
		pOldBitmap = dcMem.SelectObject (&m_DownOff);
	}
	//pOldBitmap = dcMem.SelectObject (&m_DownOff);

	// Draw
	pDC->BitBlt (0, 0, rect.Width(),rect.Height(),&dcMem, 0, 0, SRCCOPY);
    dcMem.SelectObject (pOldBitmap);

	//TRACE("Draw button down\n");


}

void CGDIButtonXLCtrl::DoDrawText(CDC* pDC,const CRect& rect)
{
	CRect rectText = rect;

//		rectTop.OffsetRect(0,m_TextOffset1);
	//rectBot.OffsetRect(0,m_TextOffset2);


	LOGFONT lf;
	::ZeroMemory (&lf, sizeof (lf));
	lf.lfHeight = m_FontSize*10;
	//lf.lfHeight = 140;
	lf.lfWeight = FW_BOLD;
	lf.lfItalic = FALSE;
	::lstrcpy (lf.lfFaceName, _T ("Times New Roman"));
	CFont font;
	font.CreatePointFontIndirect (&lf);

	CFont* pOldFont = pDC->SelectObject (&font);
	
	pDC->SetBkMode (TRANSPARENT);
	//pDC->SetTextColor(m_clrText);
	pDC->SetTextColor(TranslateColor(m_TextColor));

	rectText.top += 5;
	rectText.bottom = rectText.top + 30;
	CRect rectText2 = rectText;
	rectText.OffsetRect(0,m_TextOffset1);

	// Text 1
    pDC->DrawText (m_strLabelText1, -1, &rectText, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

	// Text 2
	rectText2.OffsetRect(0,m_TextOffset2);
	rectText2.top = rectText2.bottom;
	rectText2.bottom = rectText2.top + 25;
    pDC->DrawText (m_strLabelText2, -1, &rectText2, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

	pDC->SelectObject (pOldFont);

}


void CGDIButtonXLCtrl::SetLightOn(BOOL bLightOn)
{
	// Save current
	BOOL bCurrent = m_bLightOn;

	// Set new
	m_bLightOn = bLightOn;

	//TRACE("about to INVALIDATE \n");
	//AfxMessageBox(_T("paint time"));

	// Update if needed
	if (bLightOn != bCurrent)
	{
		InvalidateControl();
		//TRACE("INVALIDATE \n");
		//AfxMessageBox(_T("paint time"));
	}
}

// CGDIButtonXLCtrl message handlers

void CGDIButtonXLCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
	COleControl::OnLButtonDown(nFlags, point);
	m_bButtonDown = TRUE;
	InvalidateControl (); // Repaint

}


void CGDIButtonXLCtrl::OnLButtonUp(UINT nFlags, CPoint point)
{
	COleControl::OnLButtonUp(nFlags, point);
	//TRACE("OnLButtonUp...\n");
	m_bButtonDown = FALSE;
	InvalidateControl (); // Repaint

}

void CGDIButtonXLCtrl::OnText1Changed() 
{
	//AfxMessageBox(m_strLabelText1);
	//TRACE(_T("OnText1Changed %s \n"),m_strLabelText1);
	SetButtonText(m_strLabelText1,m_strLabelText2);
	SetModifiedFlag();
}
void CGDIButtonXLCtrl::OnText2Changed() 
{
	//AfxMessageBox(m_strLabelText2);
	//TRACE(_T("OnText2Changed %s \n"),m_strLabelText2);

	SetButtonText(m_strLabelText1,m_strLabelText2);
	SetModifiedFlag();
}

//OnAmbientPropertyChange

void CGDIButtonXLCtrl::SetLight(VARIANT_BOOL Light)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetLightOn(Light);
}


void CGDIButtonXLCtrl::OnBitMapSelectChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	//AfxMessageBox(_T("bitmap select"));
	//m_BitMapSelect
	//CString str;
	//str.Format(_T("Bitmap size %d"),m_BitMapSelect);
	//AfxMessageBox(str);

	m_bGenerateBitmap = true;
	InvalidateControl (); // Repaint
	SetModifiedFlag();
}


void CGDIButtonXLCtrl::OnFontSizeChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	//AfxMessageBox(_T("Font size select"));
	m_bGenerateBitmap = true;
	InvalidateControl (); // Repaint
	SetModifiedFlag();
}


void CGDIButtonXLCtrl::OnTextColorChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	//AfxMessageBox(_T("Color  select"));

	m_bGenerateBitmap = true;
	InvalidateControl (); // Repaint
	SetModifiedFlag();
}


void CGDIButtonXLCtrl::OnLightOnChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	m_bLightOn = m_LightOn;

	//if (m_bLightOn) AfxMessageBox(_T("on "));
	//else AfxMessageBox(_T("off"));
	//TRACE("OnLightOnChanged \n");

	InvalidateControl ();
	SetModifiedFlag();
}


void CGDIButtonXLCtrl::OnTextOffset1Changed(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your property handler code here

	SetModifiedFlag();
}


void CGDIButtonXLCtrl::OnTextOffset2Changed(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your property handler code here

	SetModifiedFlag();
}
