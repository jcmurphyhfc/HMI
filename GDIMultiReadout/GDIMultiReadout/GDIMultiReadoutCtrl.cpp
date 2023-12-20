// GDIMultiReadoutCtrl.cpp : Implementation of the CGDIMultiReadoutCtrl ActiveX Control class.

#include "stdafx.h"
#include "GDIMultiReadout.h"
#include "GDIMultiReadoutCtrl.h"
#include "GDIMultiReadoutPropPage.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CGDIMultiReadoutCtrl, COleControl)



// Message map

BEGIN_MESSAGE_MAP(CGDIMultiReadoutCtrl, COleControl)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()



// Dispatch map

BEGIN_DISPATCH_MAP(CGDIMultiReadoutCtrl, COleControl)
	DISP_FUNCTION_ID(CGDIMultiReadoutCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CGDIMultiReadoutCtrl, "SetValue", dispidSetValue, SetValue, VT_EMPTY, VTS_R8)
	DISP_FUNCTION_ID(CGDIMultiReadoutCtrl, "GetValue", dispidGetValue, GetValue, VT_R8, VTS_NONE)
	DISP_FUNCTION_ID(CGDIMultiReadoutCtrl, "SetPaneNum", dispidSetPaneNum, SetPaneNum, VT_EMPTY, VTS_R8)
	DISP_FUNCTION_ID(CGDIMultiReadoutCtrl, "GetPaneNum", dispidGetPaneNum, GetPaneNum, VT_R8, VTS_NONE)
	DISP_FUNCTION_ID(CGDIMultiReadoutCtrl, "SetTotalPanes", dispidSetTotalPanes, SetTotalPanes, VT_EMPTY, VTS_I2)
	DISP_FUNCTION_ID(CGDIMultiReadoutCtrl, "UpdateReadouts", dispidUpdateReadouts, UpdateReadouts, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CGDIMultiReadoutCtrl, "MultiFunc0", dispidMultiFunc0, MultiFunc0, VT_I2, VTS_I2)
	DISP_FUNCTION_ID(CGDIMultiReadoutCtrl, "MultiFunc1", dispidMultiFunc1, MultiFunc1, VT_R8, VTS_R8)
	DISP_PROPERTY_NOTIFY_ID(CGDIMultiReadoutCtrl, "TextColor", dispidTextColor, m_TextColor, OnTextColorChanged, VT_COLOR)
	DISP_PROPERTY_NOTIFY_ID(CGDIMultiReadoutCtrl, "TextBackColor", dispidTextBackColor, m_TextBackColor, OnTextBackColorChanged, VT_COLOR)
	DISP_PROPERTY_NOTIFY_ID(CGDIMultiReadoutCtrl, "TitleFontSize", dispidTitleFontSize, m_TitleFontSize, OnTitleFontSizeChanged, VT_I2)
	DISP_PROPERTY_NOTIFY_ID(CGDIMultiReadoutCtrl, "TitleTextColor", dispidTitleTextColor, m_TitleTextColor, OnTitleTextColorChanged, VT_COLOR)
	DISP_PROPERTY_NOTIFY_ID(CGDIMultiReadoutCtrl, "TitleBackColor", dispidTitleBackColor, m_TitleBackColor, OnTitleBackColorChanged, VT_COLOR)
	DISP_PROPERTY_NOTIFY_ID(CGDIMultiReadoutCtrl, "TitleDoGradientFill", dispidTitleDoGradientFill, m_TitleDoGradientFill, OnTitleDoGradientFillChanged, VT_I2)
	DISP_PROPERTY_NOTIFY_ID(CGDIMultiReadoutCtrl, "HasTitle", dispidHasTitle, m_HasTitle, OnHasTitleChanged, VT_I2)
	DISP_PROPERTY_NOTIFY_ID(CGDIMultiReadoutCtrl, "TitleText0", dispidTitleText0, m_TitleText0, OnTitleText0Changed, VT_BSTR)
	DISP_PROPERTY_NOTIFY_ID(CGDIMultiReadoutCtrl, "TitleText1", dispidTitleText1, m_TitleText1, OnTitleText1Changed, VT_BSTR)
	DISP_PROPERTY_NOTIFY_ID(CGDIMultiReadoutCtrl, "TitleText2", dispidTitleText2, m_TitleText2, OnTitleText2Changed, VT_BSTR)
	DISP_PROPERTY_NOTIFY_ID(CGDIMultiReadoutCtrl, "TitleText3", dispidTitleText3, m_TitleText3, OnTitleText3Changed, VT_BSTR)
	DISP_PROPERTY_NOTIFY_ID(CGDIMultiReadoutCtrl, "TitleText4", dispidTitleText4, m_TitleText4, OnTitleText4Changed, VT_BSTR)
	DISP_PROPERTY_NOTIFY_ID(CGDIMultiReadoutCtrl, "TitleText5", dispidTitleText5, m_TitleText5, OnTitleText5Changed, VT_BSTR)
	DISP_PROPERTY_NOTIFY_ID(CGDIMultiReadoutCtrl, "TitleText6", dispidTitleText6, m_TitleText6, OnTitleText6Changed, VT_BSTR)
	DISP_PROPERTY_NOTIFY_ID(CGDIMultiReadoutCtrl, "dbValue0", dispiddbValue0, m_dbValue0, OndbValue0Changed, VT_R8)
	DISP_PROPERTY_NOTIFY_ID(CGDIMultiReadoutCtrl, "dbValue1", dispiddbValue1, m_dbValue1, OndbValue1Changed, VT_R8)
	DISP_PROPERTY_NOTIFY_ID(CGDIMultiReadoutCtrl, "dbValue2", dispiddbValue2, m_dbValue2, OndbValue2Changed, VT_R8)
	DISP_PROPERTY_NOTIFY_ID(CGDIMultiReadoutCtrl, "dbValue3", dispiddbValue3, m_dbValue3, OndbValue3Changed, VT_R8)
	DISP_PROPERTY_NOTIFY_ID(CGDIMultiReadoutCtrl, "dbValue4", dispiddbValue4, m_dbValue4, OndbValue4Changed, VT_R8)
	DISP_PROPERTY_NOTIFY_ID(CGDIMultiReadoutCtrl, "dbValue5", dispiddbValue5, m_dbValue5, OndbValue5Changed, VT_R8)
	DISP_PROPERTY_NOTIFY_ID(CGDIMultiReadoutCtrl, "TextFontSize0", dispidTextFontSize0, m_TextFontSize0, OnTextFontSize0Changed, VT_I2)
	DISP_PROPERTY_NOTIFY_ID(CGDIMultiReadoutCtrl, "TextFontSize1", dispidTextFontSize1, m_TextFontSize1, OnTextFontSize1Changed, VT_I2)
	DISP_PROPERTY_NOTIFY_ID(CGDIMultiReadoutCtrl, "TextFontSize2", dispidTextFontSize2, m_TextFontSize2, OnTextFontSize2Changed, VT_I2)
	DISP_PROPERTY_NOTIFY_ID(CGDIMultiReadoutCtrl, "TextFontSize3", dispidTextFontSize3, m_TextFontSize3, OnTextFontSize3Changed, VT_I2)
	DISP_PROPERTY_NOTIFY_ID(CGDIMultiReadoutCtrl, "TextFontSize4", dispidTextFontSize4, m_TextFontSize4, OnTextFontSize4Changed, VT_I2)
	DISP_PROPERTY_NOTIFY_ID(CGDIMultiReadoutCtrl, "TextFontSize5", dispidTextFontSize5, m_TextFontSize5, OnTextFontSize5Changed, VT_I2)
	DISP_PROPERTY_NOTIFY_ID(CGDIMultiReadoutCtrl, "Width0", dispidWidth0, m_Width0, OnWidthChanged0, VT_I2)
	DISP_PROPERTY_NOTIFY_ID(CGDIMultiReadoutCtrl, "Width1", dispidWidth1, m_Width1, OnWidthChanged1, VT_I2)
	DISP_PROPERTY_NOTIFY_ID(CGDIMultiReadoutCtrl, "Width2", dispidWidth2, m_Width2, OnWidthChanged2, VT_I2)
	DISP_PROPERTY_NOTIFY_ID(CGDIMultiReadoutCtrl, "Width3", dispidWidth3, m_Width3, OnWidthChanged3, VT_I2)
	DISP_PROPERTY_NOTIFY_ID(CGDIMultiReadoutCtrl, "Width4", dispidWidth4, m_Width4, OnWidthChanged4, VT_I2)
	DISP_PROPERTY_NOTIFY_ID(CGDIMultiReadoutCtrl, "Width5", dispidWidth5, m_Width5, OnWidthChanged5, VT_I2)
	DISP_PROPERTY_NOTIFY_ID(CGDIMultiReadoutCtrl, "Precision0", dispidPrecision0, m_Precision0, OnPrecision0Changed, VT_I2)
	DISP_PROPERTY_NOTIFY_ID(CGDIMultiReadoutCtrl, "Precision1", dispidPrecision1, m_Precision1, OnPrecision1Changed, VT_I2)
	DISP_PROPERTY_NOTIFY_ID(CGDIMultiReadoutCtrl, "Precision2", dispidPrecision2, m_Precision2, OnPrecision2Changed, VT_I2)
	DISP_PROPERTY_NOTIFY_ID(CGDIMultiReadoutCtrl, "Precision3", dispidPrecision3, m_Precision3, OnPrecision3Changed, VT_I2)
	DISP_PROPERTY_NOTIFY_ID(CGDIMultiReadoutCtrl, "Precision4", dispidPrecision4, m_Precision4, OnPrecision4Changed, VT_I2)
	DISP_PROPERTY_NOTIFY_ID(CGDIMultiReadoutCtrl, "Precision5", dispidPrecision5, m_Precision5, OnPrecision5Changed, VT_I2)
	DISP_PROPERTY_NOTIFY_ID(CGDIMultiReadoutCtrl, "TitleHeight", dispidTitleHeight, m_TitleHeight, OnTitleHeightChanged, VT_I2)
END_DISPATCH_MAP()



// Event map

BEGIN_EVENT_MAP(CGDIMultiReadoutCtrl, COleControl)
END_EVENT_MAP()



// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CGDIMultiReadoutCtrl, 1)
	PROPPAGEID(CGDIMultiReadoutPropPage::guid)
END_PROPPAGEIDS(CGDIMultiReadoutCtrl)



// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CGDIMultiReadoutCtrl, "GDIMULTIREADOUT.GDIMultiReadoutCtrl.1",
	0x9f01b6e1, 0x2ca6, 0x470b, 0x82, 0x70, 0xf1, 0x3e, 0x8c, 0xec, 0xe6, 0x8f)



// Type library ID and version

IMPLEMENT_OLETYPELIB(CGDIMultiReadoutCtrl, _tlid, _wVerMajor, _wVerMinor)



// Interface IDs

const IID IID_DGDIMultiReadout = { 0xBB7CA3F9, 0x2539, 0x4504, { 0xB4, 0x91, 0x7A, 0x60, 0x48, 0xC9, 0x6, 0x45 } };
const IID IID_DGDIMultiReadoutEvents = { 0x27E66378, 0xB0F9, 0x43D7, { 0xB2, 0x2F, 0xF0, 0xBA, 0x83, 0x66, 0xD7, 0x53 } };


// Control type information

static const DWORD _dwGDIMultiReadoutOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CGDIMultiReadoutCtrl, IDS_GDIMULTIREADOUT, _dwGDIMultiReadoutOleMisc)



// CGDIMultiReadoutCtrl::CGDIMultiReadoutCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CGDIMultiReadoutCtrl

BOOL CGDIMultiReadoutCtrl::CGDIMultiReadoutCtrlFactory::UpdateRegistry(BOOL bRegister)
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
			IDS_GDIMULTIREADOUT,
			IDB_GDIMULTIREADOUT,
			afxRegApartmentThreading,
			_dwGDIMultiReadoutOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}



// CGDIMultiReadoutCtrl::CGDIMultiReadoutCtrl - Constructor

CGDIMultiReadoutCtrl::CGDIMultiReadoutCtrl()
{
	InitializeIIDs(&IID_DGDIMultiReadout, &IID_DGDIMultiReadoutEvents);
	// TODO: Initialize your control's instance data here.
}



// CGDIMultiReadoutCtrl::~CGDIMultiReadoutCtrl - Destructor

CGDIMultiReadoutCtrl::~CGDIMultiReadoutCtrl()
{
	// TODO: Cleanup your control's instance data here.
}



// CGDIMultiReadoutCtrl::OnDraw - Drawing function

void CGDIMultiReadoutCtrl::OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
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
		//status.bottom = rect.bottom - 1;
		//rect.bottom = rect.top + cyChar;
		//status.top = rect.bottom + 1;
		//status.right = rect.right - 1;
		//status.left = rect.left + 1;
		status.bottom = rect.bottom;
		//rect.bottom = rect.top + cyChar;
		rect.bottom = rect.top + m_TitleHeight;
		status.top = rect.bottom;
		status.right = rect.right;
		status.left = rect.left;
	}

	// Set all the pane rectangles
	double TotalChWidth = m_Width0 + m_Width1 + m_Width2 + m_Width3 + m_Width4 + m_Width5;
	double rectWidth = ((double)m_Width0/TotalChWidth)*rect.Width();
	//int rcWidth = rect.Width()/TOTAL_PANES;
	m_rectTitle[0] = rect;
	m_rectTitle[1] = rect;
	m_rectTitle[2] = rect;
	m_rectTitle[3] = rect;
	m_rectTitle[4] = rect;
	m_rectTitle[5] = rect;
	m_rectTitle[0].right = (long)m_rectTitle[0].left + (long)rectWidth;
	m_rectTitle[1].left = (long)m_rectTitle[0].right;
	rectWidth = ((double)m_Width1/TotalChWidth)*(double)rect.Width();
	m_rectTitle[1].right = m_rectTitle[1].left + (long)rectWidth;
	m_rectTitle[2].left = m_rectTitle[1].right;
	rectWidth = ((double)m_Width2/TotalChWidth)*(double)rect.Width();
	m_rectTitle[2].right = m_rectTitle[2].left + (long)rectWidth;	
	m_rectTitle[3].left = m_rectTitle[2].right;
	rectWidth = ((double)m_Width3/TotalChWidth)*(double)rect.Width();
	m_rectTitle[3].right = m_rectTitle[3].left + (long)rectWidth;
	m_rectTitle[4].left = m_rectTitle[3].right;
	rectWidth = ((double)m_Width4/TotalChWidth)*(double)rect.Width();
	m_rectTitle[4].right = m_rectTitle[4].left + (long)rectWidth;
	m_rectTitle[5].left = m_rectTitle[4].right;
	rectWidth = ((double)m_Width5/TotalChWidth)*(double)rect.Width();
	m_rectTitle[5].right = m_rectTitle[5].left + (long)rectWidth;
	m_rectTitle[0].DeflateRect(1,1);
	m_rectTitle[1].DeflateRect(1,1);
	m_rectTitle[2].DeflateRect(1,1);
	m_rectTitle[3].DeflateRect(1,1);
	m_rectTitle[4].DeflateRect(1,1);
	m_rectTitle[5].DeflateRect(1,1);

	//m_rectTitle[1] = m_rectTitle[0];
	//m_rectTitle[1].OffsetRect(CPoint(rcWidth,0));
	//m_rectTitle[2] = m_rectTitle[1];
	//m_rectTitle[2].OffsetRect(CPoint(rcWidth,0));
	//m_rectTitle[3] = m_rectTitle[2];
	//m_rectTitle[3].OffsetRect(CPoint(rcWidth,0));
	//m_rectTitle[4] = m_rectTitle[3];
	//m_rectTitle[4].OffsetRect(CPoint(rcWidth,0));
	//m_rectTitle[5] = m_rectTitle[4];
	//m_rectTitle[5].OffsetRect(CPoint(rcWidth,0));
	//m_rectTitle[0].DeflateRect(1,1);
	//m_rectTitle[1].DeflateRect(1,1);
	//m_rectTitle[2].DeflateRect(1,1);
	//m_rectTitle[3].DeflateRect(1,1);
	//m_rectTitle[4].DeflateRect(1,1);
	//m_rectTitle[5].DeflateRect(1,1);

	//m_rectStatus[0] = status;
	//m_rectStatus[1] = status;
	//m_rectStatus[2] = status;
	//m_rectStatus[3] = status;
	//m_rectStatus[4] = status;
	//m_rectStatus[5] = status;
	//m_rectStatus[0].right = m_rectStatus[0].left + rcWidth;
	//m_rectStatus[1] = m_rectStatus[0];
	//m_rectStatus[1].OffsetRect(CPoint(rcWidth,0));
	//m_rectStatus[2] = m_rectStatus[1];
	//m_rectStatus[2].OffsetRect(CPoint(rcWidth,0));
	//m_rectStatus[3] = m_rectStatus[2];
	//m_rectStatus[3].OffsetRect(CPoint(rcWidth,0));
	//m_rectStatus[4] = m_rectStatus[3];
	//m_rectStatus[4].OffsetRect(CPoint(rcWidth,0));
	//m_rectStatus[5] = m_rectStatus[4];
	//m_rectStatus[5].OffsetRect(CPoint(rcWidth,0));
	//m_rectStatus[0].DeflateRect(3,3);
	//m_rectStatus[1].DeflateRect(3,3);
	//m_rectStatus[2].DeflateRect(3,3);
	//m_rectStatus[3].DeflateRect(3,3);
	//m_rectStatus[4].DeflateRect(3,3);
	//m_rectStatus[5].DeflateRect(3,3);

	m_rectStatus[0] = status;
	m_rectStatus[1] = status;
	m_rectStatus[2] = status;
	m_rectStatus[3] = status;
	m_rectStatus[4] = status;
	m_rectStatus[5] = status;
	rectWidth = ((double)m_Width0/TotalChWidth)*rect.Width();
	m_rectStatus[0].right = m_rectStatus[0].left + (long)rectWidth;
	m_rectStatus[1].left = m_rectStatus[0].right;
	rectWidth = ((double)m_Width1/TotalChWidth)*rect.Width();
	m_rectStatus[1].right = m_rectStatus[1].left + (long)rectWidth;
	m_rectStatus[2].left = m_rectStatus[1].right;
	rectWidth = ((double)m_Width2/TotalChWidth)*rect.Width();
	m_rectStatus[2].right = m_rectStatus[2].left + (long)rectWidth;
	m_rectStatus[3].left = m_rectStatus[2].right;
	rectWidth = ((double)m_Width3/TotalChWidth)*rect.Width();
	m_rectStatus[3].right = m_rectStatus[3].left + (long)rectWidth;
	m_rectStatus[4].left = m_rectStatus[3].right;
	rectWidth = ((double)m_Width4/TotalChWidth)*rect.Width();
	m_rectStatus[4].right = m_rectStatus[4].left + (long)rectWidth;
	m_rectStatus[5].left = m_rectStatus[4].right;
	rectWidth = ((double)m_Width5/TotalChWidth)*rect.Width();
	m_rectStatus[5].right = m_rectStatus[5].left + (long)rectWidth;
	m_rectStatus[0].DeflateRect(3,3);
	m_rectStatus[1].DeflateRect(3,3);
	m_rectStatus[2].DeflateRect(3,3);
	m_rectStatus[3].DeflateRect(3,3);
	m_rectStatus[4].DeflateRect(3,3);
	m_rectStatus[5].DeflateRect(3,3);

	// Draw the 3D boarder
	dcMem.Draw3dRect(status, ::GetSysColor (COLOR_3DDKSHADOW), ::GetSysColor (COLOR_3DHILIGHT));
	status.DeflateRect(1,1);
	dcMem.Draw3dRect(status, ::GetSysColor (COLOR_3DSHADOW), ::GetSysColor (COLOR_3DHILIGHT));
	status.DeflateRect(1,1);

	// fill the Status rectangle
	m_status = status;
	PaintStatusRect(&dcMem,m_rectStatus[0],m_TextBackColor,m_TextColor,m_TextFontSize0,m_Width0,m_Precision0,m_dbValue0);
	PaintStatusRect(&dcMem,m_rectStatus[1],m_TextBackColor,m_TextColor,m_TextFontSize1,m_Width1,m_Precision1,m_dbValue1);
	PaintStatusRect(&dcMem,m_rectStatus[2],m_TextBackColor,m_TextColor,m_TextFontSize2,m_Width2,m_Precision2,m_dbValue2);
	PaintStatusRect(&dcMem,m_rectStatus[3],m_TextBackColor,m_TextColor,m_TextFontSize3,m_Width3,m_Precision3,m_dbValue3);
	PaintStatusRect(&dcMem,m_rectStatus[4],m_TextBackColor,m_TextColor,m_TextFontSize4,m_Width4,m_Precision4,m_dbValue4);
	PaintStatusRect(&dcMem,m_rectStatus[5],m_TextBackColor,m_TextColor,m_TextFontSize5,m_Width5,m_Precision5,m_dbValue5);

	// Draw the Title
	if (m_HasTitle==1)
	{
		DrawTitle(&dcMem,m_rectTitle[0],m_TitleText0);
		DrawTitle(&dcMem,m_rectTitle[1],m_TitleText1);
		DrawTitle(&dcMem,m_rectTitle[2],m_TitleText2);
		DrawTitle(&dcMem,m_rectTitle[3],m_TitleText3);
		DrawTitle(&dcMem,m_rectTitle[4],m_TitleText4);
		DrawTitle(&dcMem,m_rectTitle[5],m_TitleText5);
	}

	// Display to screen
	pdc->BitBlt (rcBounds.left, rcBounds.top, size.x,size.y, &dcMem, org.x, org.y, SRCCOPY);
	
	// Restore the DC
	dcMem.SelectObject (pOldBitmap);
	dcMem.SelectObject (pOldFont);


}
void CGDIMultiReadoutCtrl::PaintStatusRect(CDC* pDC,const CRect& Rect,COLORREF clrBK,COLORREF clrText,int TextFontSize,int Width,int Precision,double dbValue)
{
	CRect rcText = Rect;
	CString str;
	//AfxMessageBox(_T("setpos"));

	// Format the string
	str.Format(_T("%*.*f"),0,Precision,dbValue);
	//str.Format(_T("%*.*f"),Width,Precision,dbValue);
	//str += m_Units;
	//TRACE("Tedit m_nWidth:%d m_nPrecision:%d \n",m_nWidth,m_nPrecision);

	// Create the font and select it
	CFont font;
	font.CreatePointFont (TextFontSize*10, _T ("Microsoft Sans Serif"));
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

void CGDIMultiReadoutCtrl::DrawTitle(CDC *pDC,const CRect& Rect,LPCTSTR lpsz)
{
	CRect rect =  Rect;

	if (m_TitleDoGradientFill)
	{
		DoGradientFill(pDC,rect);
	}
	else
	{
		CBrush Brush;
		Brush.CreateSolidBrush(m_TitleBackColor);
		pDC->FillRect(&rect,&Brush);
	}
	pDC->SetBkMode (TRANSPARENT);
	pDC->SetTextColor (m_TitleTextColor);
	pDC->DrawText (lpsz, -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

}
void CGDIMultiReadoutCtrl::DoGradientFill(CDC *pDC,const CRect& Rect)
{
//	CBrush Brush;
//	Brush.CreateSolidBrush(m_TitleBackColor);
//	pDC->FillRect(&Rect,&Brush);

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

	//const int nNumColors = 1024;
    int nWidth = (Rect.right - Rect.left) + 1;
	//TRACE("Rect Width:%d \n",nWidth);
	int nNumColors = nWidth + 1;
	if (nNumColors > 1024) nNumColors = 1024;
    CBrush* pBrush[1024];
    for (int i=0; i<nNumColors; i++){
        pBrush[i] = new CBrush (RGB(i*dbR+80*dbR,i*dbG+80*dbG,i*dbB+80*dbB));
	}

    //int nHeight = (Rect.bottom - Rect.top) + 1;
	//TRACE("Rect.left:%d  Rect.right: %d  Rect.top:%d Rect.bottom: %d \n",Rect.left,Rect.right,Rect.top,Rect.bottom);
	//TRACE("dbG:%f \n",dbG);
	//TRACE("dbB:%f \n",dbB);
    CRect rect = Rect;
	int ClrIndex = 0;
    for (int i=Rect.left; i<Rect.right; i++) 
	{
		rect.SetRect (i, Rect.top, i + 1, Rect.bottom);
        pDC->FillRect (&rect, pBrush[(ClrIndex*(nNumColors-1))/nWidth]);
		ClrIndex++;
		if (ClrIndex > 1023) ClrIndex = 1023;
    }
    for (int i=0; i<nNumColors; i++)
        delete pBrush[i];

}

// CGDIMultiReadoutCtrl::DoPropExchange - Persistence support

void CGDIMultiReadoutCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// Call PX_ functions for each persistent custom property.
	PX_ULong (pPX, _T ("TextColor"), m_TextColor,RGB(0,255,255));
	PX_ULong (pPX, _T ("TextBackColor"), m_TextBackColor,RGB(0,0,0));
	PX_Short (pPX, _T ("TitleFontSize"), m_TitleFontSize,12);
	PX_ULong (pPX, _T ("TitleTextColor"), m_TitleTextColor,RGB(255,255,255));
	PX_ULong (pPX, _T ("TitleBackColor"), m_TitleBackColor,RGB(55,255,255));
	PX_Short (pPX, _T ("TitleDoGradientFill"), m_TitleDoGradientFill,1);
	PX_Short (pPX, _T ("HasTitle"), m_HasTitle,1);
	PX_String (pPX, _T ("TitleText0"), m_TitleText0,_T ("Position"));
	PX_String (pPX, _T ("TitleText1"), m_TitleText1,_T ("Velocity"));
	PX_String (pPX, _T ("TitleText2"), m_TitleText2,_T ("FE"));
	PX_String (pPX, _T ("TitleText3"), m_TitleText3,_T ("FE Max"));
	PX_String (pPX, _T ("TitleText4"), m_TitleText4,_T ("Amps"));
	PX_String (pPX, _T ("TitleText5"), m_TitleText5,_T ("Amps Max"));
	PX_String (pPX, _T ("TitleText6"), m_TitleText6,_T (""));
	PX_Double (pPX, _T ("dbValue0"),m_dbValue0,0);
	PX_Double (pPX, _T ("dbValue1"),m_dbValue1,0);
	PX_Double (pPX, _T ("dbValue2"),m_dbValue2,0);
	PX_Double (pPX, _T ("dbValue3"),m_dbValue3,0);
	PX_Double (pPX, _T ("dbValue4"),m_dbValue4,0);
	PX_Double (pPX, _T ("dbValue5"),m_dbValue5,0);
	PX_Short (pPX, _T ("TextFontSize0"), m_TextFontSize0,12);
	PX_Short (pPX, _T ("TextFontSize1"), m_TextFontSize1,12);
	PX_Short (pPX, _T ("TextFontSize2"), m_TextFontSize2,12);
	PX_Short (pPX, _T ("TextFontSize3"), m_TextFontSize3,12);
	PX_Short (pPX, _T ("TextFontSize4"), m_TextFontSize4,12);
	PX_Short (pPX, _T ("TextFontSize5"), m_TextFontSize5,12);
	PX_Short (pPX, _T ("Width0"), m_Width0,4);
	PX_Short (pPX, _T ("Width1"), m_Width1,4);
	PX_Short (pPX, _T ("Width2"), m_Width2,4);
	PX_Short (pPX, _T ("Width3"), m_Width3,4);
	PX_Short (pPX, _T ("Width4"), m_Width4,4);
	PX_Short (pPX, _T ("Width5"), m_Width5,4);

	PX_Short (pPX, _T ("Precision0"), m_Precision0,0);
	PX_Short (pPX, _T ("Precision1"), m_Precision1,0);
	PX_Short (pPX, _T ("Precision2"), m_Precision2,0);
	PX_Short (pPX, _T ("Precision3"), m_Precision3,0);
	PX_Short (pPX, _T ("Precision4"), m_Precision4,0);
	PX_Short (pPX, _T ("Precision5"), m_Precision5,0);
	PX_Short (pPX, _T ("TitleHeight"), m_TitleHeight,12);
	

	//for (int i=0; i< MAX_IO_POINTS;i++)
	//{
	//	strPropName.Format(_T("IOText%d"),i);
	//	PX_String (pPX,strPropName,m_StatusData[i].strText,_T("IO Text"));
	//	strPropName.Format(_T("Invert%d"),i);
	//	PX_Bool (pPX,strPropName,m_StatusData[i].bInvert,FALSE);
	//}


}



// CGDIMultiReadoutCtrl::OnResetState - Reset control to default state

void CGDIMultiReadoutCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}



// CGDIMultiReadoutCtrl::AboutBox - Display an "About" box to the user

void CGDIMultiReadoutCtrl::AboutBox()
{
	CDialogEx dlgAbout(IDD_ABOUTBOX_GDIMULTIREADOUT);
	dlgAbout.DoModal();
}



// CGDIMultiReadoutCtrl message handlers


void CGDIMultiReadoutCtrl::SetValue(DOUBLE Value)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
	InvalidateControl();
}


DOUBLE CGDIMultiReadoutCtrl::GetValue(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	//SetModifiedFlag();
	//InvalidateControl();
	return 0;
}


void CGDIMultiReadoutCtrl::SetPaneNum(DOUBLE PaneNum)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
	InvalidateControl();
}


DOUBLE CGDIMultiReadoutCtrl::GetPaneNum(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
	InvalidateControl();
	return 0;
}


void CGDIMultiReadoutCtrl::SetTotalPanes(SHORT TotalPanes)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
	InvalidateControl();
}

void CGDIMultiReadoutCtrl::UpdateReadouts(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
	InvalidateControl();
}


SHORT CGDIMultiReadoutCtrl::MultiFunc0(SHORT Param)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
	InvalidateControl();

	return 0;
}


DOUBLE CGDIMultiReadoutCtrl::MultiFunc1(DOUBLE Param)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	SetModifiedFlag();
	InvalidateControl();

	return 0;
}


void CGDIMultiReadoutCtrl::OnTextColorChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	SetModifiedFlag();
	InvalidateControl();
}


void CGDIMultiReadoutCtrl::OnTextBackColorChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
	InvalidateControl();
}


void CGDIMultiReadoutCtrl::OnTitleFontSizeChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
	InvalidateControl();
}


void CGDIMultiReadoutCtrl::OnTitleTextColorChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	SetModifiedFlag();
	InvalidateControl();
}


void CGDIMultiReadoutCtrl::OnTitleBackColorChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	SetModifiedFlag();
	InvalidateControl();
}


void CGDIMultiReadoutCtrl::OnTitleDoGradientFillChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
	InvalidateControl();
}


void CGDIMultiReadoutCtrl::OnHasTitleChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
	InvalidateControl();
}


void CGDIMultiReadoutCtrl::OnTitleText0Changed(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
	InvalidateControl();
}


void CGDIMultiReadoutCtrl::OnTitleText1Changed(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
	InvalidateControl();
}


void CGDIMultiReadoutCtrl::OnTitleText2Changed(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
	InvalidateControl();
}


void CGDIMultiReadoutCtrl::OnTitleText3Changed(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
	InvalidateControl();
}


void CGDIMultiReadoutCtrl::OnTitleText4Changed(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
	InvalidateControl();
}


void CGDIMultiReadoutCtrl::OnTitleText5Changed(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
	InvalidateControl();
}


void CGDIMultiReadoutCtrl::OnTitleText6Changed(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
	InvalidateControl();
}

void CGDIMultiReadoutCtrl::OndbValue0Changed(void)
{

	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag(); 

	TRACE("m_dbValue0: %f \n",m_dbValue0);
	//m_dbValue0;
	//DOUBLE m_dbValue1;
	//DOUBLE m_dbValue2;
	//DOUBLE m_dbValue3;
	//DOUBLE m_dbValue4;
	//DOUBLE m_dbValue5;

}
void CGDIMultiReadoutCtrl::OndbValue1Changed(void){	AFX_MANAGE_STATE(AfxGetStaticModuleState());	SetModifiedFlag(); }
void CGDIMultiReadoutCtrl::OndbValue2Changed(void){	AFX_MANAGE_STATE(AfxGetStaticModuleState());	SetModifiedFlag(); }
void CGDIMultiReadoutCtrl::OndbValue3Changed(void){	AFX_MANAGE_STATE(AfxGetStaticModuleState());	SetModifiedFlag(); }
void CGDIMultiReadoutCtrl::OndbValue4Changed(void){	AFX_MANAGE_STATE(AfxGetStaticModuleState());	SetModifiedFlag(); }
void CGDIMultiReadoutCtrl::OndbValue5Changed(void){	AFX_MANAGE_STATE(AfxGetStaticModuleState());	SetModifiedFlag(); }
void CGDIMultiReadoutCtrl::OnTextFontSize0Changed(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
	InvalidateControl();
}
void CGDIMultiReadoutCtrl::OnTextFontSize1Changed(void)
{ 
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag(); 
	InvalidateControl();
}
void CGDIMultiReadoutCtrl::OnTextFontSize2Changed(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag(); 
	InvalidateControl();
}
void CGDIMultiReadoutCtrl::OnTextFontSize3Changed(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag(); 
	InvalidateControl();
}
void CGDIMultiReadoutCtrl::OnTextFontSize4Changed(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag(); 
	InvalidateControl();
}
void CGDIMultiReadoutCtrl::OnTextFontSize5Changed(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());	
	SetModifiedFlag(); 
	InvalidateControl();
}
void CGDIMultiReadoutCtrl::OnWidthChanged0(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());	SetModifiedFlag();	InvalidateControl();
}
void CGDIMultiReadoutCtrl::OnWidthChanged1(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());	SetModifiedFlag();	InvalidateControl();
}
void CGDIMultiReadoutCtrl::OnWidthChanged2(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());	SetModifiedFlag();	InvalidateControl();
}
void CGDIMultiReadoutCtrl::OnWidthChanged3(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());	SetModifiedFlag();	InvalidateControl();
}
void CGDIMultiReadoutCtrl::OnWidthChanged4(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());	SetModifiedFlag();	InvalidateControl();
}
void CGDIMultiReadoutCtrl::OnWidthChanged5(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());	SetModifiedFlag();	InvalidateControl();
}
void CGDIMultiReadoutCtrl::OnPrecision0Changed(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
	InvalidateControl();
}
void CGDIMultiReadoutCtrl::OnPrecision1Changed(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
	InvalidateControl();
}
void CGDIMultiReadoutCtrl::OnPrecision2Changed(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
	InvalidateControl();
}


void CGDIMultiReadoutCtrl::OnPrecision3Changed(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
	InvalidateControl();
}


void CGDIMultiReadoutCtrl::OnPrecision4Changed(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
	InvalidateControl();
}

void CGDIMultiReadoutCtrl::OnPrecision5Changed(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
	InvalidateControl();
}

void CGDIMultiReadoutCtrl::OnTitleHeightChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
	InvalidateControl();
}
