// GDIMotorStatusCtrl.cpp : Implementation of the CGDIMotorStatusCtrl ActiveX Control class.

#include "stdafx.h"
#include "GDIMotorStatus.h"
#include "GDIMotorStatusCtrl.h"
#include "GDIMotorStatusPropPage.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CGDIMotorStatusCtrl, COleControl)



// Message map

BEGIN_MESSAGE_MAP(CGDIMotorStatusCtrl, COleControl)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()



// Dispatch map

BEGIN_DISPATCH_MAP(CGDIMotorStatusCtrl, COleControl)
	DISP_FUNCTION_ID(CGDIMotorStatusCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
	DISP_PROPERTY_NOTIFY_ID(CGDIMotorStatusCtrl, "TitleFontSize", dispidTitleFontSize, m_TitleFontSize, OnTitleFontSizeChanged, VT_I2)
	DISP_PROPERTY_NOTIFY_ID(CGDIMotorStatusCtrl, "DoGradientFill", dispidDoGradientFill, m_DoGradientFill, OnDoGradientFillChanged, VT_I2)
	DISP_PROPERTY_NOTIFY_ID(CGDIMotorStatusCtrl, "HasClientBox", dispidHasClientBox, m_HasClientBox, OnHasClientBoxChanged, VT_I2)
	DISP_PROPERTY_NOTIFY_ID(CGDIMotorStatusCtrl, "TitleTextBackColor", dispidTitleTextBackColor, m_TitleTextBackColor, OnTitleTextBackColorChanged, VT_COLOR)
	DISP_PROPERTY_NOTIFY_ID(CGDIMotorStatusCtrl, "TitleTextColor", dispidTitleTextColor, m_TitleTextColor, OnTitleTextColorChanged, VT_COLOR)
	DISP_PROPERTY_NOTIFY_ID(CGDIMotorStatusCtrl, "TitleText", dispidstrTitle, m_strTitle, OnstrTitleChanged, VT_BSTR)
	DISP_PROPERTY_NOTIFY_ID(CGDIMotorStatusCtrl, "MotorFontSize", dispidFontSize, m_MotorFontSize, OnFontSizeChanged, VT_I2)
	DISP_PROPERTY_NOTIFY_ID(CGDIMotorStatusCtrl, "MotorState", dispidMotorState, m_MotorState, OnMotorStateChanged, VT_I2)
	DISP_PROPERTY_NOTIFY_ID(CGDIMotorStatusCtrl, "TotalMotors", dispidTotalMotors, m_TotalMotors, OnTotalMotorsChanged, VT_I2)
	DISP_PROPERTY_NOTIFY_ID(CGDIMotorStatusCtrl, "HasTitle", dispidHasTitle, m_HasTitle, OnHasTitleChanged, VT_I2)
	DISP_PROPERTY_NOTIFY_ID(CGDIMotorStatusCtrl, "MotorTextColor", dispidMotorTextColor, m_MotorTextColor, OnMotorTextColorChanged, VT_COLOR)
	DISP_PROPERTY_NOTIFY_ID(CGDIMotorStatusCtrl, "MotorName", dispidMotorName, m_MotorName, OnMotorNameChanged, VT_BSTR)
	DISP_PROPERTY_NOTIFY_ID(CGDIMotorStatusCtrl, "MotorSelect", dispidMotorSelect, m_MotorSelect, OnMotorSelectChanged, VT_I2)
	DISP_PROPERTY_NOTIFY_ID(CGDIMotorStatusCtrl, "MotorNameWidth", dispidMotorNameWidth, m_MotorNameWidth, OnMotorNameWidthChanged, VT_I2)
	DISP_PROPERTY_NOTIFY_ID(CGDIMotorStatusCtrl, "MotorStateFontSize", dispidMotorStateFontSize, m_MotorStateFontSize, OnMotorStateFontSizeChanged, VT_I2)
	DISP_FUNCTION_ID(CGDIMotorStatusCtrl, "SetMotorState", dispidSetMotorState, SetMotorState, VT_EMPTY, VTS_I2 VTS_I2)
	DISP_FUNCTION_ID(CGDIMotorStatusCtrl, "UpdateMotorStatus", dispidUpdateMotorStatus, UpdateMotorStatus, VT_EMPTY, VTS_I2)
	DISP_FUNCTION_ID(CGDIMotorStatusCtrl, "GetMotorState", dispidGetMotorState, GetMotorState, VT_I2, VTS_I2)
END_DISPATCH_MAP()



// Event map

BEGIN_EVENT_MAP(CGDIMotorStatusCtrl, COleControl)
	EVENT_STOCK_CLICK()
	EVENT_STOCK_MOUSEDOWN()
	EVENT_STOCK_MOUSEUP()
END_EVENT_MAP()



// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CGDIMotorStatusCtrl, 1)
	PROPPAGEID(CGDIMotorStatusPropPage::guid)
END_PROPPAGEIDS(CGDIMotorStatusCtrl)



// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CGDIMotorStatusCtrl, "GDIMOTORSTATUS.GDIMotorStatusCtrl.1",
	0xfa59a8ca, 0xfac8, 0x4a3a, 0x9c, 0xcf, 0x1c, 0xc2, 0x19, 0xc8, 0x40, 0x72)



// Type library ID and version

IMPLEMENT_OLETYPELIB(CGDIMotorStatusCtrl, _tlid, _wVerMajor, _wVerMinor)



// Interface IDs

const IID IID_DGDIMotorStatus = { 0x7A6E2211, 0xE84, 0x4774, { 0xB8, 0xDF, 0x2C, 0xDE, 0x77, 0x9C, 0x7E, 0xC7 } };
const IID IID_DGDIMotorStatusEvents = { 0xBAFD3B1F, 0x3D5B, 0x450B, { 0x9A, 0xF9, 0x53, 0xFC, 0x76, 0xCD, 0x7D, 0x5B } };


// Control type information

static const DWORD _dwGDIMotorStatusOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CGDIMotorStatusCtrl, IDS_GDIMOTORSTATUS, _dwGDIMotorStatusOleMisc)



// CGDIMotorStatusCtrl::CGDIMotorStatusCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CGDIMotorStatusCtrl

BOOL CGDIMotorStatusCtrl::CGDIMotorStatusCtrlFactory::UpdateRegistry(BOOL bRegister)
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
			IDS_GDIMOTORSTATUS,
			IDB_GDIMOTORSTATUS,
			afxRegApartmentThreading,
			_dwGDIMotorStatusOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}



// CGDIMotorStatusCtrl::CGDIMotorStatusCtrl - Constructor

CGDIMotorStatusCtrl::CGDIMotorStatusCtrl()
{
	InitializeIIDs(&IID_DGDIMotorStatus, &IID_DGDIMotorStatusEvents);
	m_NameFrame.LoadBitmap(IDB_NAME_FRAME);
	m_DisabledLED.LoadBitmap(IDB_DISABLED);
	m_EnabledLED.LoadBitmap(IDB_ENABLED);
	m_WarningLED.LoadBitmap(IDB_WARNING);
	m_FaultLED.LoadBitmap(IDB_FAULT);
	for (int i=0; i< MAX_MOTORS;i++)
	{
		m_StatusData[i].WarningFE = FALSE;
	}

}



// CGDIMotorStatusCtrl::~CGDIMotorStatusCtrl - Destructor

CGDIMotorStatusCtrl::~CGDIMotorStatusCtrl()
{
}


// CGDIMotorStatusCtrl::DoPropExchange - Persistence support

void CGDIMotorStatusCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// Call PX_ functions for each persistent custom property.
	PX_Short (pPX, _T ("TitleFontSize"), m_TitleFontSize,16);
	PX_Short (pPX, _T ("TitleDoGradientFill"), m_DoGradientFill,1);
	PX_Short (pPX, _T ("HasStatusBox"), m_HasClientBox,1);
	PX_ULong (pPX, _T ("TitleTextColor"), m_TitleTextColor,RGB(255,255,255));
	PX_ULong (pPX, _T ("TitleTextBackColor"), m_TitleTextBackColor,RGB(155,155,155));
	PX_String (pPX, _T ("TitleText"), m_strTitle,_T ("Title"));
	PX_Short (pPX, _T ("MotorFontSize"), m_MotorFontSize,16);

	PX_Short (pPX, _T ("MotorState"), m_MotorState,0);
	PX_Short (pPX, _T ("TotalMotors"), m_TotalMotors,6);
	PX_Short (pPX, _T ("HasTitle"), m_HasTitle,1);

	PX_ULong (pPX, _T ("MotorTextColor"), m_MotorTextColor,RGB(255,255,255));
	PX_String (pPX, _T ("MotorName"), m_MotorName,_T ("Name"));
	PX_Short (pPX, _T ("MotorSelect"), m_MotorSelect,0);
	PX_Short (pPX, _T ("MotorNameWidth"), m_MotorNameWidth,100);

	PX_Short (pPX, _T ("MotorStateFontSize"), m_MotorStateFontSize,12);

	CString strPropName;
	for (int i=0; i< MAX_MOTORS;i++)
	{
		strPropName.Format(_T("MotorTextColor%d"),i);
		PX_ULong (pPX, strPropName, m_StatusData[i].clrTextColor,RGB(255,255,255));

		strPropName.Format(_T("MotorName%d"),i);
		PX_String (pPX, strPropName, m_StatusData[i].strText,_T ("Name"));

		strPropName.Format(_T("MotorState%d"),i);
		PX_Short (pPX,strPropName, m_StatusData[i].MotorState,0);
	}


}

// CGDIMotorStatusCtrl::OnDraw - Drawing function

void CGDIMotorStatusCtrl::OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
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

	// Title
	if (m_HasTitle)
	{
		dcMem.GetTextMetrics (&tm);
		int cxChar = tm.tmAveCharWidth;
		int cyChar = tm.tmHeight + tm.tmExternalLeading;
		status.bottom = rect.bottom - 1;
		rect.bottom = rect.top + cyChar;
		status.top = rect.bottom + 1;
		status.right = rect.right - 1;
		status.left = rect.left + 1;

		// Draw the Title
		if (m_HasTitle)
		{
			DrawTitle(&dcMem,rect);
		}

	}
	else
	{
		status = rect;
	}

	// Adjust the title rectangle and draw the status box
	if (m_HasClientBox)
	{

		// Draw the 3D boarder
		dcMem.Draw3dRect(status, ::GetSysColor (COLOR_3DDKSHADOW), ::GetSysColor (COLOR_3DHILIGHT));
		status.DeflateRect(1,1);
		dcMem.Draw3dRect(status, ::GetSysColor (COLOR_3DSHADOW), ::GetSysColor (COLOR_3DHILIGHT));
		status.DeflateRect(1,1);

		// fill the Status rectangle
		int right = status.right;
		status.right = status.left + m_MotorNameWidth;
		DrawMotorName(&dcMem,status);
		status.left = status.right;
		status.right = right;
		DrawMotorStatus(&dcMem,status);

	}


	// Display to screen
	pdc->BitBlt (rcBounds.left, rcBounds.top, size.x,size.y, &dcMem, org.x, org.y, SRCCOPY);
	
	// Restore the DC
	dcMem.SelectObject (pOldBitmap);
	//dcMem.SelectObject (pOldFont);

}

void CGDIMotorStatusCtrl::DrawTitle(CDC *pDC,const CRect& Rect)
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
	pDC->DrawText (m_strTitle, -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

}
void CGDIMotorStatusCtrl::DoGradientFill(CDC *pDC,const CRect& Rect)
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
void CGDIMotorStatusCtrl::PaintStatusRect(CDC* pDC,const CRect& Rect,COLORREF clrBK,COLORREF clrText,LPCTSTR lpText)
{
	CRect rcText = Rect;

	// Create the font and select it
	CFont font;
	font.CreatePointFont (m_MotorFontSize*10, _T ("Microsoft Sans Serif"));
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

void CGDIMotorStatusCtrl::DrawMotorName(CDC* pDC,const CRect& rect)
{
    // Get the size of the bitmap
	BITMAP bmpInfo;
    m_NameFrame.GetBitmap (&bmpInfo);
    CDC dcMem;
	CBitmap* pOldBitmap;
    dcMem.CreateCompatibleDC (pDC);
	pOldBitmap = dcMem.SelectObject (&m_NameFrame);

	// Create the font and select it
	CFont font;
	font.CreatePointFont (m_MotorFontSize*10, _T ("Microsoft Sans Serif"));
	CFont* pOldFont = pDC->SelectObject (&font);
	pDC->SetBkMode (TRANSPARENT);

	// Draw each motor name
	double Height = (double)rect.Height()/(double)m_TotalMotors;
	double Top = rect.top;
	double Bottom = Top + Height;
	CRect draw = rect;
	CRect rcText;
	for (int i=0; i< m_TotalMotors;i++)
	{
		draw.top = (long)Top;
		draw.bottom = (long)Bottom;

		// Draw background
		pDC->StretchBlt (draw.left,draw.top, draw.Width(),draw.Height(), &dcMem, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, SRCCOPY);
		m_rcNames[i] = draw;

		// Draw Name
		rcText = draw;
		rcText.left += 20;
		pDC->SetTextColor (m_StatusData[i].clrTextColor);
		pDC->DrawText (m_StatusData[i].strText, -1, &rcText, DT_SINGLELINE | DT_LEFT | DT_VCENTER);

		// Next rect
		Top += Height;
		Bottom += Height;

	}

	// Restore the DC
    dcMem.SelectObject (pOldBitmap);
	pDC->SelectObject (pOldFont);

    // Find a centerpoint for the bitmap in the client area
    //int nX = rect.left + (rect.Width() - bmpInfo.bmWidth) / 2;
    //int nY = rect.top + (rect.Height() - bmpInfo.bmHeight) / 2;

}

void CGDIMotorStatusCtrl::DrawMotorStatus(CDC* pDC,const CRect& rect)
{
	BITMAP bmpInfo;
	m_EnabledLED.GetBitmap (&bmpInfo);

	CDC dcMem;
	CBitmap* pOldBitmap;
    dcMem.CreateCompatibleDC (pDC);
	pOldBitmap = dcMem.SelectObject (&m_EnabledLED);

	CFont font;
	font.CreatePointFont (m_MotorStateFontSize*10, _T ("Microsoft Sans Serif"));
	CFont* pOldFont = pDC->SelectObject (&font);
	pDC->SetBkMode (TRANSPARENT);
	pDC->SetTextColor (RGB(0,0,0));

	// Draw Motor status
	double Height = (double)rect.Height()/(double)m_TotalMotors;
	double Top = rect.top;
	double Bottom = Top + Height;
	CRect draw = rect;
	CString str;
	for (int i=0; i< m_TotalMotors;i++)
	{
		draw.top = (long)Top;
		draw.bottom = (long)Bottom;

		switch (m_StatusData[i].MotorState)
		{
		case 0:
			str = _T("Disabled");
			dcMem.SelectObject (&m_DisabledLED);
			break;
		case 1:
			str = _T("Running");
			dcMem.SelectObject (&m_EnabledLED);
			break;
		case 2:
			str = _T("Warning FE");
			dcMem.SelectObject (&m_WarningLED);
			m_StatusData[i].WarningFE = TRUE;
			break;
		case 3:
			str = _T("Fatal FE");
			dcMem.SelectObject (&m_FaultLED);
			m_StatusData[i].WarningFE = FALSE;
			break;
		case 4:
			str = _T("Amp Fault");
			dcMem.SelectObject (&m_FaultLED);
			m_StatusData[i].WarningFE = FALSE;
			break;
		case 5:
			str = _T("Over Current");
			dcMem.SelectObject (&m_FaultLED);
			m_StatusData[i].WarningFE = FALSE;
			break;
		case 6:
			str = _T("Hall State");
			dcMem.SelectObject (&m_FaultLED);
			m_StatusData[i].WarningFE = FALSE;
			break;
		case 7:
			str = _T("Open Loop");
			dcMem.SelectObject (&m_EnabledLED);
			break;
		case 8:
			str = _T("Over Temp");
			dcMem.SelectObject (&m_WarningLED);
			break;
		case 9:
			str = _T("Encoder Fault");
			dcMem.SelectObject (&m_FaultLED);
			break;
		case 10:
			str = _T("Enc Count Error");
			dcMem.SelectObject (&m_FaultLED);
			break;
		case 11:
			str = _T("Phase Error");
			dcMem.SelectObject (&m_FaultLED);
			break;
		}

		// Check waring latch
		if (m_StatusData[i].WarningFE)
		{		
			str = _T("Warning FE");
			dcMem.SelectObject (&m_WarningLED);
		}
			
		// Draw
		pDC->StretchBlt (draw.left,draw.top, draw.Width(),draw.Height(), &dcMem, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, SRCCOPY);
		pDC->DrawText (str, -1, &draw, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

		// Save the rect
		m_rcState[i] = draw;

		// Next
		Top += Height;
		Bottom += Height;
	}



	//pDC->BitBlt (rect.left,rect.top, rect.Width(),rect.Height(),&dcMem, rect.left,rect.top, SRCCOPY);
    dcMem.SelectObject (pOldBitmap);
}

// CGDIMotorStatusCtrl::OnResetState - Reset control to default state

void CGDIMotorStatusCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}



// CGDIMotorStatusCtrl::AboutBox - Display an "About" box to the user

void CGDIMotorStatusCtrl::AboutBox()
{
	CDialogEx dlgAbout(IDD_ABOUTBOX_GDIMOTORSTATUS);
	dlgAbout.DoModal();
}



// CGDIMotorStatusCtrl message handlers


void CGDIMotorStatusCtrl::OnTitleFontSizeChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
	InvalidateControl();
}


void CGDIMotorStatusCtrl::OnDoGradientFillChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
	InvalidateControl();
}


void CGDIMotorStatusCtrl::OnHasClientBoxChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
	InvalidateControl();
}


void CGDIMotorStatusCtrl::OnTitleTextBackColorChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
	InvalidateControl();
}


void CGDIMotorStatusCtrl::OnTitleTextColorChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
	InvalidateControl();
}


void CGDIMotorStatusCtrl::OnstrTitleChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
	InvalidateControl();
}

void CGDIMotorStatusCtrl::OnFontSizeChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
	InvalidateControl();
}


void CGDIMotorStatusCtrl::OnMotorStateChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if (m_MotorState >= MAX_MOTORS_STATE)
	{
		m_MotorState = MAX_MOTORS_STATE - 1;
	}

	m_StatusData[m_MotorSelect].clrTextColor = m_MotorTextColor;
	m_StatusData[m_MotorSelect].strText = m_MotorName;
	m_StatusData[m_MotorSelect].MotorState = m_MotorState;

	SetModifiedFlag();
	InvalidateControl();
}


void CGDIMotorStatusCtrl::OnTotalMotorsChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
	InvalidateControl();
	if (m_TotalMotors >= MAX_MOTORS)
	{
		m_TotalMotors = MAX_MOTORS - 1;
	}

}


void CGDIMotorStatusCtrl::OnHasTitleChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
	InvalidateControl();
}


void CGDIMotorStatusCtrl::OnMotorTextColorChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	m_StatusData[m_MotorSelect].clrTextColor = m_MotorTextColor;
	m_StatusData[m_MotorSelect].strText = m_MotorName;
	m_StatusData[m_MotorSelect].MotorState = m_MotorState;

	SetModifiedFlag();
	InvalidateControl();

}

void CGDIMotorStatusCtrl::OnMotorNameChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	m_StatusData[m_MotorSelect].clrTextColor = m_MotorTextColor;
	m_StatusData[m_MotorSelect].strText = m_MotorName;
	m_StatusData[m_MotorSelect].MotorState = m_MotorState;

	SetModifiedFlag();
	InvalidateControl();
}


void CGDIMotorStatusCtrl::OnMotorSelectChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	m_MotorTextColor = m_StatusData[m_MotorSelect].clrTextColor;
	m_MotorName = m_StatusData[m_MotorSelect].strText;
	m_MotorState = m_StatusData[m_MotorSelect].MotorState;

	SetModifiedFlag();
	InvalidateControl();
}


void CGDIMotorStatusCtrl::OnMotorNameWidthChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
	InvalidateControl();
}


void CGDIMotorStatusCtrl::OnMotorStateFontSizeChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	SetModifiedFlag();
	InvalidateControl();
}


void CGDIMotorStatusCtrl::SetMotorState(SHORT MotorNum, SHORT State)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	//m_StatusData[m_MotorSelect].clrTextColor = m_MotorTextColor;
	//m_StatusData[m_MotorSelect].strText = m_MotorName;

	if (State < 0) State = 0;
	if (State >= MAX_MOTORS_STATE) State = MAX_MOTORS_STATE - 1;

	m_StatusData[MotorNum].MotorState = State;
}


void CGDIMotorStatusCtrl::UpdateMotorStatus(SHORT Repaint)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if (Repaint)
	{
		InvalidateControl();
	}
}


void CGDIMotorStatusCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
	COleControl::OnLButtonDown(nFlags, point);

	// Clear Warning latch
	for (int i=0; i< MAX_MOTORS;i++)
	{
		if (m_rcState[i].PtInRect(point))
		{
			if (m_StatusData[i].WarningFE)
			{
				m_StatusData[i].WarningFE = FALSE;
				InvalidateControl();
			}
		}
	}
	//CWnd* pWnd = GetParent();
	//if (pWnd != NULL)
	//	pWnd->SendMessage(WM_COMMAND,MAKEWPARAM(GetDlgCtrlID(),BN_CLICKED),(LPARAM)m_hWnd);
}


SHORT CGDIMotorStatusCtrl::GetMotorState(SHORT MotorNum)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return m_StatusData[MotorNum].MotorState;
}
