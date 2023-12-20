// KeyPadDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HMIDlg.h"
#include "KeyPadDlg.h"


// CKeyPadDlg dialog

IMPLEMENT_DYNAMIC(CKeyPadDlg, CDialog)

//CKeyPadDlg::CKeyPadDlg(CWnd* pParent /*=NULL*/)
//	: CDialog(CKeyPadDlg::IDD, pParent)
//{
//
//}
//
//CKeyPadDlg::~CKeyPadDlg()
//{
//}
///
//void CKeyPadDlg::DoDataExchange(CDataExchange* pDX)
//{
//	CDialog::DoDataExchange(pDX);
//}
//BEGIN_MESSAGE_MAP(CKeyPadDlg, CDialog)
//END_MESSAGE_MAP()


// CKeyPadDlg message handlers


/////////////////////////////////////////////////////////////////////////////
// CKeyPadDlg dialog

CKeyPadDlg::CKeyPadDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CKeyPadDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CKeyPadDlg)
	//}}AFX_DATA_INIT

	m_strPassWord = _T("");
	m_bPassWord = FALSE;
	m_dblMemory = 0.0;
	m_dbValue = 0.0;
	m_dbIncrement = 1.0;
	m_strFormat = _T ("%0.2f");
	m_nDecimalPlaces = 2;
    m_bDecimalInString = FALSE;
	m_dbMin = 0;
	m_dbMax = 10;
    m_bNewX = TRUE;
	m_bNegPending = FALSE;
	m_hAccel = ::LoadAccelerators (AfxGetInstanceHandle (),
    MAKEINTRESOURCE (IDR_KEYPAD_ACCEL));

}

void CKeyPadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CKeyPadDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CKeyPadDlg, CDialog)
	//{{AFX_MSG_MAP(CKeyPadDlg)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_CLX, OnClear)
	ON_BN_CLICKED(IDC_DECIMAL, OnDecimal)
	ON_BN_CLICKED(IDC_DEL, OnDelete)
	ON_BN_CLICKED(IDC_INCREMENT, OnIncrement)
	ON_BN_CLICKED(IDC_DECREMENT, OnDecrement)
	ON_BN_CLICKED(IDC_NEG_VALUE, OnNegValue)
	//}}AFX_MSG_MAP
	ON_CONTROL_RANGE (BN_CLICKED, IDC_0, IDC_9, OnDigit)
	ON_BN_CLICKED(IDOK, &CKeyPadDlg::OnBnClickedOk)
END_MESSAGE_MAP()

////	ON_BN_CLICKED(IDC_CHGSIGN, OnChangeSign)
/////////////////////////////////////////////////////////////////////////////
// CKeyPadDlg message handlers

BOOL CKeyPadDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CString string;
	CString strMinMax;
	//GetWindowText(string);
	string += m_strLabel;
	if (m_dbMin != m_dbMax)
		strMinMax.Format(_T(" Min: %.0f Max: %.0f"),m_dbMin,m_dbMax);
	string += strMinMax;
	SetWindowText(string);
	//
	// Set the application's icon.
	//
//	SetIcon(m_hIcon, TRUE);
//	SetIcon(m_hIcon, FALSE);
	//
	// Remove the Size and Maximize commands from the system menu.
	//
	CMenu* pMenu = GetSystemMenu (FALSE);
	pMenu->DeleteMenu (SC_SIZE, MF_BYCOMMAND);
	pMenu->DeleteMenu (SC_MAXIMIZE, MF_BYCOMMAND);

	//
	// Initialize m_rect with the coordinates of the control representing
	// the calculator's output window. Then destroy the control.
	//
	CWnd* pWnd = GetDlgItem (IDC_DISPLAYRECT);
	pWnd->GetWindowRect (&m_rect);
	pWnd->DestroyWindow ();
	ScreenToClient (&m_rect);

	//
	// Initialize m_cxChar and m_cyChar with the average character width
	// and height.
	//
    TEXTMETRIC tm;
    CClientDC dc (this);
    dc.GetTextMetrics (&tm);
    m_cxChar = tm.tmAveCharWidth;
    m_cyChar = tm.tmHeight - tm.tmDescent;

	// Set decimal places
	char ch = m_nDecimalPlaces;
    m_strFormat.SetAt (3, ch + 0x30);

	//
	// Initialize the calculator's output window and return.
	//
    DisplayXRegister ();
	return TRUE;
}

void CKeyPadDlg::OnPaint() 
{
	CPaintDC dc (this);
	dc.DrawEdge (m_rect, EDGE_SUNKEN, BF_RECT);

	if (m_bPassWord)
		UpdateDisplay (m_strPassWord);
	else 
		UpdateDisplay (m_strDisplay);

}

BOOL CKeyPadDlg::PreTranslateMessage(MSG* pMsg) 
{
    if (m_hAccel != NULL)
        if (::TranslateAccelerator (m_hWnd, m_hAccel, pMsg))
            return TRUE;
    
    return CDialog::PreTranslateMessage (pMsg);
}

BOOL CKeyPadDlg::OnCommand(WPARAM wParam, LPARAM lParam) 
{
/*
    int nID = (int) LOWORD (wParam);

    if (m_bErrorFlag && (nID != IDC_CLX)) {
        ::MessageBeep (MB_ICONASTERISK);
        return TRUE;
    }

    if (m_bFixPending &&
        ((nID < IDC_0) || (nID > IDC_9)) &&
        (nID != IDC_CLX)) {
        ::MessageBeep (MB_ICONASTERISK);
        return TRUE;
    }
	*/
    return CDialog::OnCommand (wParam, lParam);
}

void CKeyPadDlg::OnDigit(UINT nID) 
{
    TCHAR cDigit = (TCHAR) nID;

    if (m_bNewX) {
        m_bNewX = FALSE;
        m_strDisplay.Empty ();
		if (m_nDecimalPlaces > 0)
			m_bDecimalInString = FALSE;
		else
			m_bDecimalInString = TRUE;
    }

	// Add digit
	CString string = m_strDisplay;
	//string += (cDigit - IDC_0 + 0x30);
	cDigit = (cDigit - IDC_0 + 0x30);
	string += cDigit;

    double dbValue = _tcstod (string.GetBuffer (0), NULL);

	if (m_bNegPending){
		dbValue = -dbValue;
		m_bNegPending = FALSE;
	    string = _T ("-") + string;
	}

	// Add new digit to display
	m_strDisplay = string;
	m_strPassWord += _T("*");

	if (m_bPassWord)
		UpdateDisplay (m_strPassWord);
	else 
		UpdateDisplay (m_strDisplay);

//    UpdateDisplay (m_strDisplay);
    m_dbValue = _tcstod (m_strDisplay.GetBuffer (0), NULL);

}


void CKeyPadDlg::OnChangeSign() 
{
}

void CKeyPadDlg::OnClear() 
{
	if (m_nDecimalPlaces > 0)
		m_bDecimalInString = FALSE;
	else
		m_bDecimalInString = TRUE;
    m_dbValue = 0.0;
    DisplayXRegister ();
    m_bStackLiftEnabled = FALSE;
    m_bNewX = TRUE;
}

void CKeyPadDlg::OnDecimal() 
{
//    int nLength = m_strDisplay.GetLength ();
//    if ((nLength == MAXCHARS) || (m_bDecimalInString))
    if (m_bNewX) {
        m_bNewX = FALSE;
        m_strDisplay.Empty ();
		if (m_nDecimalPlaces > 0)
			m_bDecimalInString = FALSE;
		else
			m_bDecimalInString = TRUE;
    }

	// Add decimal to string
    if (m_bDecimalInString)
        ::MessageBeep (MB_ICONASTERISK);
    else {
        m_bDecimalInString = TRUE;
        m_strDisplay += (char) 0x2E;


		if (m_bPassWord)
			UpdateDisplay (m_strPassWord);
		else 
			UpdateDisplay (m_strDisplay);


//        UpdateDisplay (m_strDisplay);
	    //m_dbValue = strtod (m_strDisplay.GetBuffer (0), NULL);
	    m_dbValue = wcstod (m_strDisplay.GetBuffer (0), NULL);		
    }
}

void CKeyPadDlg::OnDelete() 
{
    int nLength = m_strDisplay.GetLength ();

    if (!m_bNewX && (nLength != 0)) {
        if (m_strDisplay[nLength - 1] == _T ('.'))
            m_bDecimalInString = FALSE;
        m_strDisplay = m_strDisplay.Left (nLength - 1);

		int len = m_strPassWord.GetLength();
		if (len > 0){
			//TRACE("Length %d \n",len);
			m_strPassWord.Delete(len-1,1);
		}

		if (m_bPassWord)
			UpdateDisplay (m_strPassWord);
		else 
			UpdateDisplay (m_strDisplay);

//        UpdateDisplay (m_strDisplay);
//        m_dbValue = strtod (m_strDisplay.GetBuffer (0), NULL);
	    m_dbValue = wcstod (m_strDisplay.GetBuffer (0), NULL);		

    }
}


void CKeyPadDlg::DisplayXRegister()
{
    double dblVal = m_dbValue;

    if ((dblVal >= 1000000000000.0) || (dblVal <= -1000000000000.0)) {
        UpdateDisplay (CString (_T ("Overflow error")));
        MessageBeep (MB_ICONASTERISK);
    }
    else {
        m_strDisplay.Format (m_strFormat, dblVal);

		if (m_bPassWord)
			UpdateDisplay (m_strPassWord);
		else 
			UpdateDisplay (m_strDisplay);

        //UpdateDisplay (m_strDisplay);
    }
}

void CKeyPadDlg::UpdateDisplay(LPCTSTR pszDisplay)
{
    CClientDC dc (this);
    CFont* pOldFont = dc.SelectObject (GetFont ());
    CSize size = dc.GetTextExtent (pszDisplay);

    CRect rect = m_rect;
    rect.InflateRect (-2, -2);
    int x = rect.right - size.cx - m_cxChar;
    int y = rect.top + ((rect.Height () - m_cyChar) / 2);
	dc.ExtTextOut (x, y, ETO_OPAQUE, rect, pszDisplay, NULL);

    dc.SelectObject (pOldFont);

}


/////////////////////////////////////////////////////////////////////////////
// CKeyPadDlg message handlers

void CKeyPadDlg::OnIncrement() 
{
    m_bNewX = FALSE;
	double dbValue = m_dbValue;    
	dbValue += m_dbIncrement;

	if (m_dbMin == m_dbMax)
	{
		m_dbValue = dbValue;
	}
	else
	{
		if (dbValue <= m_dbMax)
			m_dbValue = dbValue;
		else
		   ::MessageBeep (MB_ICONASTERISK);
	}

    DisplayXRegister ();

}

void CKeyPadDlg::OnDecrement() 
{
    m_bNewX = FALSE;
	double dbValue = m_dbValue;    
	dbValue -= m_dbIncrement;

	if (m_dbMin == m_dbMax)
	{
		m_dbValue = dbValue;
	}
	else
	{
		if (dbValue >= m_dbMin)
			m_dbValue = dbValue;
		else
		   ::MessageBeep (MB_ICONASTERISK);
	}

    DisplayXRegister ();
}

///////////////////////////////////////////////////////////////////////////////
// CKeyPadDlg message handlers


void CKeyPadDlg::SetRange(double nMin, double nMax)
{
	if (nMin < nMax){
		m_dbMin = nMin;
		m_dbMax = nMax;
	}
	else{
		m_dbMin = nMax;
		m_dbMax = nMin;
	}

}

void CKeyPadDlg::OnNegValue() 
{
	//TRACE("NegValue \n");
	if (!m_bNewX){
		m_dbValue = -m_dbValue;    
		DisplayXRegister ();
	}
	else{
		if (!m_bNegPending){
			m_bNegPending = TRUE;
			if (m_strDisplay[0] != _T ('-')) {
				m_strDisplay = _T ("-") + m_strDisplay;
				if (m_bPassWord)
					UpdateDisplay (m_strPassWord);
				else 
					UpdateDisplay (m_strDisplay);
				//UpdateDisplay (m_strDisplay);
			}
		}
	}
}

double CKeyPadDlg::SetValue(double dbValue)
{
	double dbOldValue = m_dbValue;
	m_strPassWord = _T("");
	m_dbValue = 0.0;
    m_bNewX = TRUE;
	if (dbValue < m_dbMin){
		m_dbValue = m_dbMin;
	}
	if (dbValue > m_dbMax){
		m_dbValue = m_dbMax;
	}
	return dbOldValue;
}



void CKeyPadDlg::OnBnClickedOk()
{
	if (m_dbMin != m_dbMax)
	{
		if (m_dbValue > m_dbMax)  m_dbValue = m_dbMax;
		if (m_dbValue < m_dbMin)  m_dbValue = m_dbMin;
	}

	CDialog::OnOK();
}
