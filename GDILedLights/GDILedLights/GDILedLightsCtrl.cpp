// GDILedLightsCtrl.cpp : Implementation of the CGDILedLightsCtrl ActiveX Control class.

#include "stdafx.h"
#include "GDILedLights.h"
#include "GDILedLightsCtrl.h"
#include "GDILedLightsPropPage.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CGDILedLightsCtrl, COleControl)



// Message map

BEGIN_MESSAGE_MAP(CGDILedLightsCtrl, COleControl)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()



// Dispatch map

BEGIN_DISPATCH_MAP(CGDILedLightsCtrl, COleControl)
	DISP_FUNCTION_ID(CGDILedLightsCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
	DISP_PROPERTY_NOTIFY_ID(CGDILedLightsCtrl, "LedColorSelect", dispidLedColorSelect, m_LedColorSelect, OnLedColorSelectChanged, VT_I2)
	DISP_PROPERTY_NOTIFY_ID(CGDILedLightsCtrl, "TotalIoPoints", dispidTotalIoPoints, m_TotalIoPoints, OnTotalIoPointsChanged, VT_I2)
	DISP_PROPERTY_NOTIFY_ID(CGDILedLightsCtrl, "IoStatusWord", dispidIoStatusWord, m_IoStatusWord, OnIoStatusWordChanged, VT_I4)
END_DISPATCH_MAP()



// Event map

BEGIN_EVENT_MAP(CGDILedLightsCtrl, COleControl)
END_EVENT_MAP()



// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CGDILedLightsCtrl, 1)
	PROPPAGEID(CGDILedLightsPropPage::guid)
END_PROPPAGEIDS(CGDILedLightsCtrl)



// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CGDILedLightsCtrl, "GDILEDLIGHTS.GDILedLightsCtrl.1",
	0x292c0fd4, 0xf89f, 0x4003, 0xb4, 0xab, 0x95, 0x31, 0xde, 0xfc, 0x2b, 0x3b)



// Type library ID and version

IMPLEMENT_OLETYPELIB(CGDILedLightsCtrl, _tlid, _wVerMajor, _wVerMinor)



// Interface IDs

const IID IID_DGDILedLights = { 0xDFCD43C, 0x3A3B, 0x4D7C, { 0x90, 0x12, 0x45, 0x8F, 0x88, 0x30, 0x58, 0xA9 } };
const IID IID_DGDILedLightsEvents = { 0xBFEDD14E, 0x53A6, 0x460D, { 0x85, 0xB3, 0x7C, 0xAC, 0xD, 0x55, 0x74, 0x5A } };


// Control type information

static const DWORD _dwGDILedLightsOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CGDILedLightsCtrl, IDS_GDILEDLIGHTS, _dwGDILedLightsOleMisc)



// CGDILedLightsCtrl::CGDILedLightsCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CGDILedLightsCtrl

BOOL CGDILedLightsCtrl::CGDILedLightsCtrlFactory::UpdateRegistry(BOOL bRegister)
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
			IDS_GDILEDLIGHTS,
			IDB_GDILEDLIGHTS,
			afxRegApartmentThreading,
			_dwGDILedLightsOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}



// CGDILedLightsCtrl::CGDILedLightsCtrl - Constructor

CGDILedLightsCtrl::CGDILedLightsCtrl()
{
	InitializeIIDs(&IID_DGDILedLights, &IID_DGDILedLightsEvents);

	// Initialize control's instance data
	m_RedLedOn.LoadBitmap(IDB_RED_LED_ON);
	m_RedLedOff.LoadBitmap(IDB_RED_LED_OFF);
	m_GreenLedOn.LoadBitmap(IDB_GREEN_LED_ON);
	m_GreenLedOff.LoadBitmap(IDB_GREEN_LED_OFF);
	m_BlueLedOn.LoadBitmap(IDB_BLUE_LED_ON);
	m_BlueLedOff.LoadBitmap(IDB_BLUE_LED_OFF);
	m_AmberLedOn.LoadBitmap(IDB_AMBER_LED_ON);
	m_AmberLedOff.LoadBitmap(IDB_AMBER_LED_OFF);

}



// CGDILedLightsCtrl::~CGDILedLightsCtrl - Destructor

CGDILedLightsCtrl::~CGDILedLightsCtrl()
{
	// TODO: Cleanup your control's instance data here.
}



// CGDILedLightsCtrl::OnDraw - Drawing function

void CGDILedLightsCtrl::OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	CDC dcMem;
	BITMAP bm;
	CBitmap bitmap;
	CFont font;
	CRect status;
	//TEXTMETRIC tm;

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


	DrawLED(&dcMem,rect);

	//// Title font
	//font.CreatePointFont (m_nTitleFontSize*10, _T ("Microsoft Sans Serif"));
	//CFont* pOldFont = dcMem.SelectObject (&font);

	//// Adjust the title rectangle and draw the status box
	//if (m_bHasClientBox)
	//{
	//	dcMem.GetTextMetrics (&tm);
	//	int cxChar = tm.tmAveCharWidth;
	//	int cyChar = tm.tmHeight + tm.tmExternalLeading;
	//	status.bottom = rect.bottom - 1;
	//	rect.bottom = rect.top + cyChar;
	//	status.top = rect.bottom + 1;
	//	status.right = rect.right - 1;
	//	status.left = rect.left + 1;

	//	// Draw the 3D boarder
	//	dcMem.Draw3dRect(status, ::GetSysColor (COLOR_3DDKSHADOW), ::GetSysColor (COLOR_3DHILIGHT));
	//	status.DeflateRect(1,1);
	//	dcMem.Draw3dRect(status, ::GetSysColor (COLOR_3DSHADOW), ::GetSysColor (COLOR_3DHILIGHT));
	//	status.DeflateRect(1,1);

	//	// Draw the LED names and status
	//	int right = status.right;

	//	if (rcBounds==rcInvalid){
	//		status.right = status.left + m_IoNameWidth;
	//		DrawName(&dcMem,status);
	//		status.left = status.right;
	//		status.right = right;
	//		DrawLED(&dcMem,status);
	//	}
	//	else 
	//	{
	//		//TRACE("Partial update \n");
	//		status.right = status.left + m_IoNameWidth;
	//		DrawName(&dcMem,status);
	//		status.left = status.right;
	//		status.right = right;
	//		DrawLED(&dcMem,status);
	//	}


	//}

	//// Draw the Title
	//DrawTitle(&dcMem,rect);

	// Display to screen
	pdc->BitBlt (rcBounds.left, rcBounds.top, size.x,size.y, &dcMem, org.x, org.y, SRCCOPY);
	
	// Restore the DC
	dcMem.SelectObject (pOldBitmap);
	//dcMem.SelectObject (pOldFont);
}

void CGDILedLightsCtrl::DrawLED(CDC* pDC,const CRect& rect)
{
    //Get the size of the bitmap
	BITMAP bmpInfo;
    m_RedLedOn.GetBitmap (&bmpInfo);
    CDC dcMemOn;
    CDC dcMemOff;
	CBitmap* pOldBitmapOn;
	CBitmap* pOldBitmapOff;

    dcMemOn.CreateCompatibleDC (pDC);
    dcMemOff.CreateCompatibleDC (pDC);


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

	
	// Draw each I/O point
	double Width = (double)rect.Width()/(double)m_TotalIoPoints;
	double Left = rect.left;
	double Right = Left + Width;
	CRect draw = rect;
	//ULONG CurrentBit = 1;
	ULONG CurrentBit = 0x8;
	ULONG StatusWord = (ULONG)m_IoStatusWord;

	for (int i=0; i< m_TotalIoPoints;i++)
	{
		draw.left = (long)Left;
		draw.right = (long)Right;
		if (m_IoStatusWord & CurrentBit)
		{
			pDC->StretchBlt (draw.left,draw.top,draw.Width(),draw.Height(), &dcMemOn, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, SRCCOPY);
		}
		else
		{
			pDC->StretchBlt (draw.left,draw.top,draw.Width(),draw.Height(), &dcMemOff, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, SRCCOPY);		
		}

		// Next bit
		//CurrentBit = CurrentBit << 1;
		CurrentBit = CurrentBit >> 1;
		
		// Next rect
		Left += Width;
		Right += Width;
	}

	// Restore the DC
    dcMemOn.SelectObject (pOldBitmapOn);
    dcMemOff.SelectObject (pOldBitmapOff);

}


// CGDILedLightsCtrl::DoPropExchange - Persistence support

void CGDILedLightsCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.

	//CString strPropName;
	//ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	//COleControl::DoPropExchange(pPX);

	// Call PX_ functions for each persistent custom property.
	//PX_Short (pPX, _T ("HasStatusBox"), m_bHasClientBox,TRUE);
	//PX_Short (pPX, _T ("TitleFontSize"), m_nTitleFontSize,16);
	//PX_ULong (pPX, _T ("TitleTextColor"), m_clrTitleTextColor,RGB(255,255,255));
	//PX_Short (pPX, _T ("TitleDoGradientFill"), m_bDoGradientFill,1);
	//PX_String (pPX, _T ("TitleText"), m_strTitle,_T ("Title"));
	//PX_String (pPX, _T ("IOStatusText"), m_strText,_T ("Status"));
	//PX_Short (pPX, _T ("IOStatusTextFontSize"), m_nFontSize,16);
	//PX_ULong (pPX, _T ("IOStatusTextColor"), m_clrTextColor,RGB(255,255,255));
	//PX_ULong (pPX, _T ("IOStatusTextBackColor"), m_cltBkColor,RGB(0,192,192));
	//PX_Short (pPX, _T ("IOStatusInvert"), m_bInvert,FALSE);
	//PX_Short (pPX, _T ("IOStatusBit"), m_nState,0);
	//PX_ULong (pPX, _T ("TitleTextBackColor"), m_TitleTextBackColor,RGB(0,155,155));
	//PX_Short (pPX, _T ("IoNameWidth"), m_IoNameWidth,100);
	PX_Short (pPX, _T ("LedColorSelect"), m_LedColorSelect,0);
	PX_Short (pPX, _T ("TotalIoPoints"), m_TotalIoPoints,4);
	PX_Long (pPX, _T ("IoStatusWord"), m_IoStatusWord,0);
	//PX_Short (pPX, _T ("IoForceEnable"), m_IoForceEnable,0);
	//PX_ULong (pPX, _T ("IoStatusWordInvert"), m_IoStatusWordInvert,0);

}



// CGDILedLightsCtrl::OnResetState - Reset control to default state

void CGDILedLightsCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}



// CGDILedLightsCtrl::AboutBox - Display an "About" box to the user

void CGDILedLightsCtrl::AboutBox()
{
	CDialogEx dlgAbout(IDD_ABOUTBOX_GDILEDLIGHTS);
	dlgAbout.DoModal();
}



// CGDILedLightsCtrl message handlers


void CGDILedLightsCtrl::OnLedColorSelectChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
	InvalidateControl();
}


void CGDILedLightsCtrl::OnTotalIoPointsChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
	InvalidateControl();
}

void CGDILedLightsCtrl::OnIoStatusWordChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
	InvalidateControl();
}
