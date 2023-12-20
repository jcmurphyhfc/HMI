// TEdit.cpp : implementation file
//

//#include "stdafx.h"
//#include "FMVHMI.h"
//#include "TEdit.h"
//#include "HMIDlg\HMIDlg\HMIDlgApi.h"

#include "stdafx.h"
#include "HMIDlg.h"
#include "TEdit.h"
#include "HMIDlgApi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTEdit

CTEdit::CTEdit()
{
	m_bEnableEdit = TRUE;
	bNoChange = FALSE;
    m_clrText = RGB (0, 0, 0);
    m_clrBack = ::GetSysColor (COLOR_3DFACE);
    m_brBkgnd.CreateSolidBrush (m_clrBack);
	m_dbValue = 0.0;
	m_dbIncrement = 1.0;
	m_strLabel = "";
	m_strUnits = "";
	m_dbMin = -1000000;
	m_dbMax = 1000000;
	m_nWidth = 1;
	m_nPrecision = 0;
	m_pdbValue = NULL;
	m_pnValue = NULL;
}

CTEdit::~CTEdit()
{
}


BEGIN_MESSAGE_MAP(CTEdit, CEdit)
	//{{AFX_MSG_MAP(CTEdit)
	ON_WM_CTLCOLOR_REFLECT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
	ON_WM_CREATE()
	ON_WM_CHAR()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTEdit message handlers

HBRUSH CTEdit::CtlColor(CDC* pDC, UINT nCtlColor) 
{
    pDC->SetTextColor (m_clrText);
    pDC->SetBkColor (m_clrBack);
    return (HBRUSH) m_brBkgnd;
}
void CTEdit::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if (!m_bEnableEdit)
		return;

	// Swap colors
	//bNoChange = TRUE;
  	COLORREF clrText = m_clrBack;
	COLORREF clrBack = m_clrText;
	SetTextColor(clrText);
	SetBkColor(clrBack);
	SetCapture();
	SetFocus();

	CWnd* pWnd = GetParent();
	if (pWnd != NULL){
		pWnd->SendMessage(WM_COMMAND,MAKEWPARAM(GetDlgCtrlID(),BN_CLICKED),(LPARAM)m_hWnd);
	}

	
//	CEdit::OnLButtonDown(nFlags, point);
}

void CTEdit::OnLButtonUp(UINT nFlags, CPoint point) 
{
    if (GetCapture () == this)
	   ::ReleaseCapture ();
	else
		return;

	// Swap colors
  	COLORREF clrText = m_clrBack;
	COLORREF clrBack = m_clrText;
	SetTextColor(clrText);
	SetBkColor(clrBack);

	// Get latest applied data
	if (m_pdbValue != NULL)
		SetValue(*m_pdbValue);
	else if (m_pnValue != NULL)
		SetValue(*m_pnValue);

	KEYPADDATA data;
	data.dbIncrement = m_dbIncrement;
	data.dbMin = m_dbMin;
	data.dbValue = m_dbValue;
	data.dbMax = m_dbMax;
	data.lpTitle = m_strLabel;
	data.nDecimalPlaces = m_nPrecision;
	data.bPassWord = false;
	if (GetNumDlg(&data)){
		SetValue(data.dbValue);
	}
	bNoChange = FALSE;	
//	CEdit::OnLButtonUp(nFlags, point);

}
void CTEdit::SetTextColor(COLORREF clrText)
{
    m_clrText = clrText;
    Invalidate ();
}

void CTEdit::SetBkColor(COLORREF clrBack)
{
    m_clrBack = clrBack;
    m_brBkgnd.DeleteObject ();
    m_brBkgnd.CreateSolidBrush (clrBack);
    Invalidate ();
}
double CTEdit::GetValue()
{
	return m_dbValue;
}
void CTEdit::SetValue(double dbValue)
{
	// Not now
    //if (bNoChange)
	//	return;

	CString str;
	CString strCurrent;

	// Limit range
	if (m_dbMin != m_dbMax){
		if (dbValue < m_dbMin)			
			dbValue = m_dbMin;
		if (dbValue > m_dbMax)			
			dbValue = m_dbMax;
	}
	m_dbValue = dbValue;

	if (m_pdbValue != NULL)
		*m_pdbValue = m_dbValue;

	str.Format(_T("%*.*f"),m_nWidth,m_nPrecision,m_dbValue);
	//TRACE("Tedit m_nWidth:%d m_nPrecision:%d \n",m_nWidth,m_nPrecision);

	str += m_strUnits;

	GetWindowText(strCurrent);
	if (strCurrent != str)
		SetWindowText(str);

}
void CTEdit::SetValuePtr(double* pdbValue)
{
	m_pdbValue = pdbValue;
	SetValue(*m_pdbValue);
}
void CTEdit::SetValuePtr(int* pnValue)
{
	m_pnValue = pnValue;
	SetValue(*m_pnValue);
}

void CTEdit::SetRange(double nMin, double nMax)
{
	m_dbMin = nMin;
	m_dbMax = nMax;
}

BOOL CTEdit::PreCreateWindow(CREATESTRUCT& cs) 
{
	//TRACE("PRECREATE TEDIT...................................\n");
	return CEdit::PreCreateWindow(cs);
}

void CTEdit::PreSubclassWindow() 
{
	
	//TRACE("PRECREATE TEDIT...................................\n");
	CEdit::PreSubclassWindow();
}

int CTEdit::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CEdit::OnCreate(lpCreateStruct) == -1)
		return -1;

//	CRect rect;
//    GetClientRect (&rect);
//	rect.right -= 30;
//	MoveWindow(&rect,TRUE);
//	GetClientRect(
//   LPRECT lpRect 
//) const;

//	// Spin button
//	TRACE("TEDIT ON CREATE .....\n");
//	m_ctlSpin.Create(WS_CHILD | WS_VISIBLE | WS_BORDER,CRect (rect.right,rect.top,rect.right+30,rect.top+30), this, 0);
//	m_ctlSpin.SetBuddy(this);

	return 0;
}

void CTEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (((nChar >= _T ('0')) && (nChar <= _T ('9'))) || 
		(nChar == VK_BACK))
		CEdit::OnChar (nChar, nRepCnt, nFlags);
}
