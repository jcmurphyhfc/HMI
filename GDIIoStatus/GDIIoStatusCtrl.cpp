// GDIIoStatusCtrl.cpp : Implementation of the CGDIIoStatusCtrl ActiveX Control class.

#include "stdafx.h"
#include "GDIIoStatus.h"
#include "GDIIoStatusCtrl.h"
#include "GDIIoStatusPropPage.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CGDIIoStatusCtrl, COleControl)



// Message map

BEGIN_MESSAGE_MAP(CGDIIoStatusCtrl, COleControl)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()



// Dispatch map

BEGIN_DISPATCH_MAP(CGDIIoStatusCtrl, COleControl)
	DISP_FUNCTION_ID(CGDIIoStatusCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
	DISP_PROPERTY_NOTIFY_ID(CGDIIoStatusCtrl, "HasStatusBox", dispidbHasClientBox, m_bHasClientBox, OnbHasClientBoxChanged, VT_I2)
	DISP_PROPERTY_NOTIFY_ID(CGDIIoStatusCtrl, "TitleFontSize", dispidnTitleFontSize, m_nTitleFontSize, OnnTitleFontSizeChanged, VT_I2)	DISP_PROPERTY_NOTIFY_ID(CGDIIoStatusCtrl, "TitleTextColor", dispidclrTitleTextColor, m_clrTitleTextColor, OnclrTitleTextColorChanged, VT_COLOR)
	DISP_PROPERTY_NOTIFY_ID(CGDIIoStatusCtrl, "TitleDoGradientFill", dispidbDoGradientFill, m_bDoGradientFill, OnbDoGradientFillChanged, VT_I2)
	DISP_PROPERTY_NOTIFY_ID(CGDIIoStatusCtrl, "TitleText", dispidstrTitle, m_strTitle, OnstrTitleChanged, VT_BSTR)
	DISP_PROPERTY_NOTIFY_ID(CGDIIoStatusCtrl, "IOStatusText", dispidstrText, m_strText, OnstrTextChanged, VT_BSTR)
	DISP_PROPERTY_NOTIFY_ID(CGDIIoStatusCtrl, "IOStatusTextFontSize", dispidnFontSize, m_nFontSize, OnnFontSizeChanged, VT_I2)
	DISP_PROPERTY_NOTIFY_ID(CGDIIoStatusCtrl, "IOStatusTextColor", dispidclrTextColor, m_clrTextColor, OnclrTextColorChanged, VT_COLOR)
	DISP_PROPERTY_NOTIFY_ID(CGDIIoStatusCtrl, "IOStatusTextBackColor", dispidcltBkColor, m_cltBkColor, OncltBkColorChanged, VT_COLOR)
	DISP_PROPERTY_NOTIFY_ID(CGDIIoStatusCtrl, "IOStatusInvert", dispidbInvert, m_bInvert, OnInvertChanged, VT_I2)
	DISP_PROPERTY_EX_ID(CGDIIoStatusCtrl,     "StatusState", dispidBit, GetBit, SetBit, VT_I2)
	DISP_PROPERTY_NOTIFY_ID(CGDIIoStatusCtrl, "TitleTextBackColor", dispidTitleTextBackColor, m_TitleTextBackColor, OnTitleTextBackColorChanged, VT_COLOR)
	DISP_PROPERTY_NOTIFY_ID(CGDIIoStatusCtrl, "TotalIoPoints", dispidTotalIoPoints, m_TotalIoPoints, OnTotalIoPointsChanged, VT_I2)
	DISP_PROPERTY_NOTIFY_ID(CGDIIoStatusCtrl, "IoNameWidth", dispidIoNameWidth, m_IoNameWidth, OnIoNameWidthChanged, VT_I2)
	DISP_PROPERTY_NOTIFY_ID(CGDIIoStatusCtrl, "LedColorSelect", dispidLedColorSelect, m_LedColorSelect, OnLedColorSelectChanged, VT_I2)
	DISP_PROPERTY_NOTIFY_ID(CGDIIoStatusCtrl, "IoStatusWord", dispidIoStatusWord, m_IoStatusWord, OnIoStatusWordChanged, VT_UI4)
	DISP_PROPERTY_NOTIFY_ID(CGDIIoStatusCtrl, "IoForceEnable", dispidIoForceEnable, m_IoForceEnable, OnIoForceEnableChanged, VT_I2)
	DISP_PROPERTY_NOTIFY_ID(CGDIIoStatusCtrl, "IoStatusWordInvert", dispidIoStatusWordInvert, m_IoStatusWordInvert, OnIoStatusWordInvertChanged, VT_UI4)
END_DISPATCH_MAP()


// Event map

BEGIN_EVENT_MAP(CGDIIoStatusCtrl, COleControl)
	EVENT_STOCK_CLICK()
	EVENT_STOCK_MOUSEDOWN()
	EVENT_STOCK_MOUSEUP()
	EVENT_STOCK_DBLCLICK()
	EVENT_STOCK_KEYPRESS()
	EVENT_CUSTOM_ID("IoClicked", eventidIoClicked, IoClicked, VTS_I2)
END_EVENT_MAP()


// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CGDIIoStatusCtrl, 1)
	PROPPAGEID(CGDIIoStatusPropPage::guid)
END_PROPPAGEIDS(CGDIIoStatusCtrl)



// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CGDIIoStatusCtrl, "GDIIOSTATUS.GDIIoStatusCtrl.1",
	0xcf5f3df3, 0x3e8e, 0x435a, 0x99, 0xf3, 0x58, 0xe3, 0x68, 0x8, 0x7, 0xbf)



// Type library ID and version

IMPLEMENT_OLETYPELIB(CGDIIoStatusCtrl, _tlid, _wVerMajor, _wVerMinor)



// Interface IDs

const IID IID_DGDIIoStatus = { 0x3CFCA2D7, 0x1644, 0x46D7, { 0x87, 0xD, 0x86, 0x24, 0x7, 0x3A, 0x24, 0x80 } };
const IID IID_DGDIIoStatusEvents = { 0x7ABC9D79, 0x1EF0, 0x4BC7, { 0x9E, 0x4A, 0x6D, 0xEA, 0xF0, 0x96, 0xB8, 0x40 } };


// Control type information

static const DWORD _dwGDIIoStatusOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CGDIIoStatusCtrl, IDS_GDIIOSTATUS, _dwGDIIoStatusOleMisc)



// CGDIIoStatusCtrl::CGDIIoStatusCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CGDIIoStatusCtrl

BOOL CGDIIoStatusCtrl::CGDIIoStatusCtrlFactory::UpdateRegistry(BOOL bRegister)
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
			IDS_GDIIOSTATUS,
			IDB_GDIIOSTATUS,
			afxRegApartmentThreading,
			_dwGDIIoStatusOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}



// CGDIIoStatusCtrl::CGDIIoStatusCtrl - Constructor

CGDIIoStatusCtrl::CGDIIoStatusCtrl()
{
	InitializeIIDs(&IID_DGDIIoStatus, &IID_DGDIIoStatusEvents);

	// Initialize control's instance data.
	m_bInvert       = FALSE;
	m_bTimerRunning  = FALSE;
	SetBit(GetBit());

	m_RedLedOn.LoadBitmap(IDB_RED_LED_ON);
	m_RedLedOff.LoadBitmap(IDB_RED_LED_OFF);
	m_GreenLedOn.LoadBitmap(IDB_GREEN_LED_ON);
	m_GreenLedOff.LoadBitmap(IDB_GREEN_LED_OFF);
	m_BlueLedOn.LoadBitmap(IDB_BLUE_LED_ON);
	m_BlueLedOff.LoadBitmap(IDB_BLUE_LED_OFF);
	m_AmberLedOn.LoadBitmap(IDB_AMBER_LED_ON);
	m_AmberLedOff.LoadBitmap(IDB_AMBER_LED_OFF);
	for (int i=0; i< MAX_IO_POINTS;i++)
	{
		m_DrawUp[i] = TRUE;
	}
}



// CGDIIoStatusCtrl::~CGDIIoStatusCtrl - Destructor

CGDIIoStatusCtrl::~CGDIIoStatusCtrl()
{
	// TODO: Cleanup your control's instance data here.
}




// CGDIIoStatusCtrl::DoPropExchange - Persistence support

void CGDIIoStatusCtrl::DoPropExchange(CPropExchange* pPX)
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
	PX_String (pPX, _T ("IOStatusText"), m_strText,_T ("Status"));
	PX_Short (pPX, _T ("IOStatusTextFontSize"), m_nFontSize,16);
	PX_ULong (pPX, _T ("IOStatusTextColor"), m_clrTextColor,RGB(255,255,255));
	PX_ULong (pPX, _T ("IOStatusTextBackColor"), m_cltBkColor,RGB(0,192,192));
	PX_Short (pPX, _T ("IOStatusInvert"), m_bInvert,FALSE);
	PX_Short (pPX, _T ("IOStatusBit"), m_nState,0);
	PX_ULong (pPX, _T ("TitleTextBackColor"), m_TitleTextBackColor,RGB(0,155,155));
	PX_Short (pPX, _T ("TotalIoPoints"), m_TotalIoPoints,8);
	PX_Short (pPX, _T ("IoNameWidth"), m_IoNameWidth,100);
	PX_Short (pPX, _T ("LedColorSelect"), m_LedColorSelect,0);
	PX_ULong (pPX, _T ("IoStatusWord"), m_IoStatusWord,0);
	PX_Short (pPX, _T ("IoForceEnable"), m_IoForceEnable,0);
	PX_ULong (pPX, _T ("IoStatusWordInvert"), m_IoStatusWordInvert,0);

	for (int i=0; i< MAX_IO_POINTS;i++)
	{
		strPropName.Format(_T("IOText%d"),i);
		PX_String (pPX,strPropName,m_StatusData[i].strText,_T("IO Text"));
		strPropName.Format(_T("Invert%d"),i);
		PX_Bool (pPX,strPropName,m_StatusData[i].bInvert,FALSE);
		//strPropName.Format(_T("TextColor%d"),i);
		//PX_ULong (pPX,strPropName,m_StatusData[i].clrTextColor,RGB(255,255,255));
		//strPropName.Format(_T("BkColor%d"),i);
		//PX_ULong (pPX,strPropName,m_StatusData[i].clrBkColor,RGB(0,192,192));
	}


	//PX_Double (pPX, _T ("TitleRed"),m_nRed,192);
	//PX_Double (pPX, _T ("TitleGreen"),m_nGreen,192);
	//PX_Double (pPX, _T ("TitleBlue"),m_nBlue,192);
}



// CGDIIoStatusCtrl::OnResetState - Reset control to default state

void CGDIIoStatusCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}



// CGDIIoStatusCtrl::AboutBox - Display an "About" box to the user

void CGDIIoStatusCtrl::AboutBox()
{
	CDialogEx dlgAbout(IDD_ABOUTBOX_GDIIOSTATUS);
	dlgAbout.DoModal();
}

// CGDIIoStatusCtrl::OnDraw - Drawing function

void CGDIIoStatusCtrl::OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
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

		// Draw the LED names and status
		int right = status.right;

		if (rcBounds==rcInvalid){
			status.right = status.left + m_IoNameWidth;
			DrawName(&dcMem,status);
			status.left = status.right;
			status.right = right;
			DrawLED(&dcMem,status);
		}
		else 
		{
			//TRACE("Partial update \n");
			status.right = status.left + m_IoNameWidth;
			DrawName(&dcMem,status);
			status.left = status.right;
			status.right = right;
			DrawLED(&dcMem,status);
		}


	}

	// Draw the Title
	DrawTitle(&dcMem,rect);

	// Display to screen
	pdc->BitBlt (rcBounds.left, rcBounds.top, size.x,size.y, &dcMem, org.x, org.y, SRCCOPY);
	
	// Restore the DC
	dcMem.SelectObject (pOldBitmap);
	dcMem.SelectObject (pOldFont);

}

void CGDIIoStatusCtrl::DrawTitle(CDC *pDC,const CRect& Rect)
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

	//if (m_IoForceEnable==1)
	//{
	//	CString str = m_strTitle;
	//	str += _T("   Force ON");
	//	pDC->DrawText (str, -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	//}
	//else
	//{
	//	pDC->DrawText (m_strTitle, -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	//}

}
void CGDIIoStatusCtrl::DoGradientFill(CDC *pDC,const CRect& Rect)
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

void CGDIIoStatusCtrl::DrawName(CDC* pDC,const CRect& rect)
{
	CFont* pOldFont;
	CPen* pOldPen;
	CBrush Brush;
	CBrush BrushInvert;
	CPen pen;
	CFont font;


	// Create drawing objects
	font.CreatePointFont (m_nFontSize*10, _T ("Microsoft Sans Serif"));
	Brush.CreateSolidBrush(m_cltBkColor);
	BrushInvert.CreateSolidBrush(m_clrTextColor);
	pen.CreatePen (PS_SOLID, 1, RGB (255, 255, 255));

	// Select drawing objects
	pOldFont = pDC->SelectObject (&font);
	pOldPen = pDC->SelectObject (&pen);
	pDC->SetBkMode (TRANSPARENT);

	// Draw each I/O name
	double Height = (double)rect.Height()/(double)m_TotalIoPoints;
	double Top = rect.top;
	double Bottom = Top + Height;
	CRect draw = rect;
	CRect rcText;
	for (int i=0; i< m_TotalIoPoints;i++)
	{
		// Set the rect
		draw.top = (long)Top;
		draw.bottom = (long)Bottom;
		m_rcNames[i] = draw;
		//TRACE("Save m_rcNames[i].top:%d left:%d right:%d\n",m_rcNames[i].top,m_rcNames[i].left,m_rcNames[i].right);

		if (m_DrawUp[i]== TRUE)
		{
			// Background
			pDC->FillRect(&m_rcNames[i],&Brush);
			pDC->MoveTo (m_rcNames[i].left,m_rcNames[i].bottom-1);
			pDC->LineTo (m_rcNames[i].right,m_rcNames[i].bottom-1);

			// Draw Name
			rcText = m_rcNames[i];
			rcText.left += 4;
			pDC->SetTextColor (m_clrTextColor);
			pDC->DrawText (m_StatusData[i].strText, -1, &rcText, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
		}
		else
		{
			// Background
			pDC->FillRect(&m_rcNames[i],&BrushInvert);
			pDC->MoveTo (m_rcNames[i].left,m_rcNames[i].bottom-1);
			pDC->LineTo (m_rcNames[i].right,m_rcNames[i].bottom-1);

			// Draw Name
			rcText = m_rcNames[i];
			rcText.left += 4;
			pDC->SetTextColor (m_cltBkColor);
			pDC->DrawText (m_StatusData[i].strText, -1, &rcText, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
		
		}

		// Next rect
		Top += Height;
		Bottom += Height;
	}

	// Restore the DC
	pDC->SelectObject (pOldFont);
	pDC->SelectObject (pOldPen);


}

//void CGDIIoStatusCtrl::DrawNameRect(CDC* pDC,const CRect& rect)
//{
//		// Background
//		pDC->FillRect(&m_rcNames[i],&Brush);
//		pDC->MoveTo (m_rcNames[i].left,m_rcNames[i].bottom-1);
//		pDC->LineTo (m_rcNames[i].right,m_rcNames[i].bottom-1);
//
//		// Draw Name
//		rcText = m_rcNames[i];
//		rcText.left += 4;
//		pDC->SetTextColor (m_clrTextColor);
//		pDC->DrawText (m_StatusData[i].strText, -1, &rcText, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
//
//}

void CGDIIoStatusCtrl::DrawLED(CDC* pDC,const CRect& rect)
{
    //Get the size of the bitmap
	BITMAP bmpInfo;
    m_RedLedOn.GetBitmap (&bmpInfo);
    CDC dcMemOn;
    CDC dcMemOff;
	CBitmap* pOldBitmapOn;
	CBitmap* pOldBitmapOff;

    dcMemOn.CreateCompatibleDC (pDC);
	//pOldBitmapOn = dcMemOn.SelectObject (&m_RedLedOn);
    dcMemOff.CreateCompatibleDC (pDC);
	//pOldBitmapOff = dcMemOff.SelectObject (&m_RedLedOn);


	switch (m_LedColorSelect)
	{
	case 0:
		pOldBitmapOn = dcMemOn.SelectObject (&m_RedLedOn);
		pOldBitmapOff = dcMemOff.SelectObject (&m_RedLedOff);
		break;
	case 1:
		pOldBitmapOn = dcMemOn.SelectObject (&m_GreenLedOn);
		pOldBitmapOff = dcMemOff.SelectObject (&m_GreenLedOff);
		break;
	case 2:
		pOldBitmapOn = dcMemOn.SelectObject (&m_BlueLedOn);
		pOldBitmapOff = dcMemOff.SelectObject (&m_BlueLedOff);
		break;
	case 3:
		pOldBitmapOn = dcMemOn.SelectObject (&m_AmberLedOn);
		pOldBitmapOff = dcMemOff.SelectObject (&m_AmberLedOff);
		break;
	default:
		pOldBitmapOn = dcMemOn.SelectObject (&m_RedLedOn);
		pOldBitmapOff = dcMemOff.SelectObject (&m_RedLedOff);
		break;	
	}

	// Draw each I/O name
	double Height = (double)rect.Height()/(double)m_TotalIoPoints;
	double Top = rect.top;
	double Bottom = Top + Height;
	CRect draw = rect;
	CRect rcText;
	ULONG CurrentBit = 1;

	for (int i=0; i< m_TotalIoPoints;i++)
	{
		draw.top = (long)Top;
		draw.bottom = (long)Bottom;
		if (m_StatusData[i].bInvert == 1)
		//if (m_IoStatusWordInvert & CurrentBit)
		{
			if (m_IoStatusWord & CurrentBit)
			{
				pDC->StretchBlt (draw.left,draw.top,draw.Width(),draw.Height(), &dcMemOff, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, SRCCOPY);		
			}
			else
			{
				pDC->StretchBlt (draw.left,draw.top,draw.Width(),draw.Height(), &dcMemOn, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, SRCCOPY);
			}
		}
		else
		{
			if (m_IoStatusWord & CurrentBit)
			{
				pDC->StretchBlt (draw.left,draw.top,draw.Width(),draw.Height(), &dcMemOn, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, SRCCOPY);
			}
			else
			{
				pDC->StretchBlt (draw.left,draw.top,draw.Width(),draw.Height(), &dcMemOff, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, SRCCOPY);		
			}
		}

		// Next bit
		CurrentBit = CurrentBit << 1;
		
		// Next rect
		Top += Height;
		Bottom += Height;
	}

	// Restore the DC
    dcMemOn.SelectObject (pOldBitmapOn);
    dcMemOff.SelectObject (pOldBitmapOff);

}

// CGDIIoStatusCtrl message handlers

int CGDIIoStatusCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (COleControl::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}

void CGDIIoStatusCtrl::OnTimer(UINT_PTR nIDEvent)
{


}

// CGDIIoStatusCtrl message handlers

void CGDIIoStatusCtrl::OnnFontSizeChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
	InvalidateControl();
}

void CGDIIoStatusCtrl::OnstrTitleChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
	InvalidateControl();
}

void CGDIIoStatusCtrl::OnbHasClientBoxChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
	InvalidateControl();
}


void CGDIIoStatusCtrl::OnstrTextChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	m_StatusData[m_nState].strText       = m_strText;
	SetModifiedFlag();
	InvalidateControl();
}

void CGDIIoStatusCtrl::OnclrTextColorChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	//m_StatusData[m_nState].clrTextColor  = m_clrTextColor;
	SetModifiedFlag();
	InvalidateControl();
}


void CGDIIoStatusCtrl::OncltBkColorChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	//m_StatusData[m_nState].clrBkColor    = m_cltBkColor; 
	SetModifiedFlag();
	InvalidateControl();
}


void CGDIIoStatusCtrl::OnInvertChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	m_StatusData[m_nState].bInvert      = m_bInvert;
	//TRACE(_T("Blink changed"));
	SetModifiedFlag();
	InvalidateControl();
}


SHORT CGDIIoStatusCtrl::GetBit(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if (m_nState > MAX_IO_POINTS-1)
		m_nState = MAX_IO_POINTS-1;
	if (m_nState < 0)
		m_nState = 0;

	return m_nState;
}


void CGDIIoStatusCtrl::SetBit(SHORT newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	int nState = newVal;
	if (nState < 0)
		nState = 0;
	if (nState > MAX_IO_POINTS-1)
		nState = MAX_IO_POINTS-1;

	// Show the state data
	//m_cltBkColor   = m_StatusData[nState].clrBkColor;
	//m_clrTextColor = m_StatusData[nState].clrTextColor;
	m_strText      = m_StatusData[nState].strText;
	m_bInvert       = m_StatusData[nState].bInvert;

	if (nState == m_nState)
		return;

	m_nState = nState;
	SetModifiedFlag();
	InvalidateControl();
}

void CGDIIoStatusCtrl::OnnTitleFontSizeChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
	InvalidateControl();
}

void CGDIIoStatusCtrl::OnclrTitleTextColorChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
	InvalidateControl();
}


void CGDIIoStatusCtrl::OnbDoGradientFillChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
	InvalidateControl();
}


void CGDIIoStatusCtrl::OnTitleTextBackColorChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
	InvalidateControl();
}

void CGDIIoStatusCtrl::OnTotalIoPointsChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
	InvalidateControl();
}

void CGDIIoStatusCtrl::OnIoNameWidthChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
	InvalidateControl();
}


void CGDIIoStatusCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
	//TRACE("OnLButtonDown \n");
	CRect rect;
	COleControl::OnLButtonDown(nFlags, point);
	//TRACE("Point x %d y %d\n",point.x,point.y);
	for (int i=0; i< m_TotalIoPoints;i++)
	{
		//TRACE("m_rcNames[i].top:%d left:%d right:%d\n",m_rcNames[i].top,m_rcNames[i].left,m_rcNames[i].right);
		if (m_rcNames[i].PtInRect(point))
		{
			m_DrawUp[i] = FALSE;
			rect = m_rcNames[i];
			//TRACE("Point in rect... OnLButtonDown %d\n",i);
			InvalidateControl(rect);
			return;
		}
	}
	//InvalidateControl(rect);

}


void CGDIIoStatusCtrl::OnLButtonUp(UINT nFlags, CPoint point)
{
	//TRACE("OnLButtonUp... \n");

	CRect rect;
	COleControl::OnLButtonUp(nFlags, point);
	for (int i=0; i< m_TotalIoPoints;i++)
	{
		if (m_DrawUp[i] == FALSE)
		{
			IoClicked(i);
			m_DrawUp[i] = TRUE;
			rect = m_rcNames[i];
			InvalidateControl(rect);
			return;
		}
	}
	//InvalidateControl(rect);

}


void CGDIIoStatusCtrl::OnLedColorSelectChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
	InvalidateControl();
}


void CGDIIoStatusCtrl::OnIoStatusWordChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
	InvalidateControl();
}

void CGDIIoStatusCtrl::OnIoForceEnableChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
	InvalidateControl();
}

void CGDIIoStatusCtrl::OnIoStatusWordInvertChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
	InvalidateControl();
}
