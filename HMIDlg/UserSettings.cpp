// UserSettings.cpp : implementation file
//

#include "stdafx.h"
#include "HMIDlg.h"
#include "UserSettings.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUserSettings

IMPLEMENT_DYNAMIC(CUserSettings, CPropertySheet)

CUserSettings::CUserSettings(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	m_ppBackPtr = NULL;
	//Initialize(pParentWnd);
}

CUserSettings::CUserSettings(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	//Initialize(pParentWnd);
}

CUserSettings::~CUserSettings()
{
	if (m_ppBackPtr)
		*m_ppBackPtr = NULL;
}

void CUserSettings::Initialize(CWnd* pParentWnd,ALLSETTINGS* pParams)
{
	m_pParams = pParams;
	m_nPage = 0;
	m_nTotalPage = 3;

	// Set the titles
	m_Page1.m_psp.pszTitle = _T("Vision");
	m_Page2.m_psp.pszTitle = _T("BTC/Slicer");
	m_Page3.m_psp.pszTitle = _T("TT Stacker");
    AddPage (&m_Page1);
    AddPage (&m_Page2);
    AddPage (&m_Page3);
	m_pWndParent = pParentWnd;

	// Save the motion settins pointer
	m_Page1.m_pSettings = pParams;
	m_Page2.m_pSettings = pParams;
	m_Page3.m_pSettings = pParams;

}

BEGIN_MESSAGE_MAP(CUserSettings, CPropertySheet)
	//{{AFX_MSG_MAP(CUserSettings)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
    ON_BN_CLICKED (ID_APPLY_NOW, OnApply)
	ON_BN_CLICKED (ID_SAVE_BUTTON, OnSaveButton)
	ON_BN_CLICKED (ID_RESTORE, OnRestore)
    ON_BN_CLICKED (ID_NEXT_PAGE, OnNextPage)
    ON_BN_CLICKED (ID_PREV_PAGE, OnPrevPage)
    ON_BN_CLICKED (IDOK, OnClose)
	ON_MESSAGE (WM_VISION_SETTINGS_CHANGED,OnChange)
	ON_WM_NCHITTEST()
	ON_WM_SETFOCUS()
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUserSettings message handlers

BOOL CUserSettings::OnInitDialog() 
{
	
	BOOL bResult = CPropertySheet::OnInitDialog();
    
	// Increase the height of the CPropertySheet by 30
	CRect rc;
    GetWindowRect (&rc);
	rc.bottom += 60;

	// Resize the CPropertySheet
	MoveWindow (rc.left, rc.top, rc.right-rc.left, rc.bottom-rc.top);
	
	// Convert to client coordinates
	ScreenToClient (&rc);
	
	// Create Apply button
	m_btnApplyButton.Create (_T("Apply"), WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
		CRect (5, rc.bottom-60, 75, rc.bottom-5), this, ID_APPLY_NOW);

	// Create the SAVE button
	m_btnSaveButton.Create (_T("Save"), WS_CHILD | WS_VISIBLE | WS_TABSTOP,
		CRect (79, rc.bottom-60, 149, rc.bottom-5), this, ID_SAVE_BUTTON);

	// Create the Restore button
	m_btnRestoreButton.Create (_T("Restore"), WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED,
		CRect (153, rc.bottom-60, 223, rc.bottom-5), this, ID_RESTORE);

	// Nav buttons
	if (m_nTotalPage > 1)
	{
		// Create the Previous page button
		m_btnPrevPageButton.Create (_T("<- Back"), WS_CHILD | WS_VISIBLE | WS_TABSTOP,
			CRect (238, rc.bottom-60, 308, rc.bottom-5), this, ID_PREV_PAGE);

		// Create the Next page button
		m_btnNextPageButton.Create (_T("Next ->"), WS_CHILD | WS_VISIBLE | WS_TABSTOP,
			CRect (309, rc.bottom-60, 379, rc.bottom-5), this, ID_NEXT_PAGE);
	}

	// Create the CLOSE button
	m_btnCloseButton.Create (_T("Close"), BS_DEFPUSHBUTTON | WS_CHILD | WS_VISIBLE | WS_TABSTOP,
		CRect (rc.right-79, rc.bottom-60, rc.right-9, rc.bottom-5), this, IDOK);

	// Set parent pointers
	m_Page1.m_pWndParent = this;
	m_Page2.m_pWndParent = this;
	m_Page3.m_pWndParent = this;

	return bResult;
}

void CUserSettings::PostNcDestroy() 
{
	CPropertySheet::PostNcDestroy();
	delete this;
}
void CUserSettings::OnApply()
{

	// Get data from active page
	GetActivePage ()->UpdateData (TRUE);

	// Set Parameters
	SetParams();

	// Send message
	if (m_pWndParent != NULL){
		m_pWndParent->SendMessage (WM_VISION_SETTINGS_APPLY, 0, 0);
		//TRACE("Send apply message to parent \n");
	}

	// Disable the Apply button
	m_btnApplyButton.EnableWindow(FALSE);

	// Enable the Restore button
	m_btnRestoreButton.EnableWindow();
	//TRACE("OnApply \n");

}

void CUserSettings::OnSaveButton()
{

	// Disable the Apply button
	m_btnApplyButton.EnableWindow(FALSE);

	// Get data from active page
	GetActivePage ()->UpdateData (TRUE);

	// Set Parameters
	SetParams();

	// Send save message
	if (m_pWndParent != NULL){
		m_pWndParent->SendMessage (WM_VISION_SETTINGS_SAVE, 0, 0);
		TRACE("Send Save message to parent \n");
	}

	// Enable the Restore button
	m_btnRestoreButton.EnableWindow();
	m_btnSaveButton.EnableWindow(FALSE);
	//TRACE("OnSaveButton \n");


}

void CUserSettings::OnRestore()
{
	// Restore settings
	LoadBackUp();

	// Load Dialog members with Document data
	LoadParams();

	// Set data in active page
	GetActivePage ()->UpdateData (FALSE);
	m_btnRestoreButton.EnableWindow(FALSE);

	// Send restore message
	if (m_pWndParent != NULL){
		m_pWndParent->SendMessage (WM_VISION_SETTINGS_RESTORE, 0, 0);
		//TRACE("Send Save message to parent \n");
	}

	//TRACE("OnRestore \n");
}

void CUserSettings::OnNextPage()
{
	m_nPage++;
	if (m_nPage >= m_nTotalPage)
		m_nPage = 0;

	SetActivePage(m_nPage);
	TRACE(".............................OnNextPage %d \n",m_nPage);
}
void CUserSettings::OnPrevPage()
{
	m_nPage--;
	if (m_nPage < 0)
		m_nPage = m_nTotalPage - 1;
		
	SetActivePage(m_nPage);
	TRACE("OnPrevPage.....Page %d \n",m_nPage);
}
void CUserSettings::OnClose()
{
	TRACE("OnClose \n");
	DestroyWindow();
}

LRESULT CUserSettings::OnChange(WPARAM wParam, LPARAM lParam)
{
	TRACE("CUserSettings::OnChange........... \n");
	//SetModified (TRUE);
	m_btnApplyButton.EnableWindow();
	//m_btnApplyButton.EnableWindow();

	m_btnSaveButton.EnableWindow();


	return 0;
}

LRESULT CUserSettings::OnNcHitTest(CPoint point)
{
    LRESULT nHitTest = CPropertySheet::OnNcHitTest (point);
    if ((nHitTest == HTCLIENT) && (::GetAsyncKeyState (MK_LBUTTON) < 0))
        nHitTest = HTCAPTION;
    return nHitTest;

}

int CUserSettings::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CPropertySheet::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	//lpCreateStruct->dwExStyle &= ~WS_SYSMENU;
	lpCreateStruct->style &= ~WS_SYSMENU;

	// Make a backup copy of current settings
	SaveBackUp();

	// Create font
	m_font.CreatePointFont (220, _T ("Microsoft Sans Serif"));
	m_fontSmall.CreatePointFont (140, _T ("Microsoft Sans Serif"));
	m_Tabfont.CreatePointFont (140, _T ("Microsoft Sans Serif"));

	// Specialized creation code
	m_Page1.m_pfont = &m_fontSmall;
	m_Page1.m_clrText = m_clrText;
	m_Page1.m_clrBack = m_clrBack;

	m_Page2.m_pfont = &m_fontSmall;
	m_Page2.m_clrText = m_clrText;
	m_Page2.m_clrBack = m_clrBack;

	m_Page3.m_pfont = &m_fontSmall;
	m_Page3.m_clrText = m_clrText;
	m_Page3.m_clrBack = m_clrBack;

	//m_Page4.m_pfont = &m_fontSmall;
	//m_Page4.m_clrText = m_clrText;
	//m_Page4.m_clrBack = m_clrBack;

	// Load Dialog members with Document data
	LoadParams();
	//GetActivePage ()->UpdateData (FALSE);

	
	return 0;
}
void CUserSettings::OnSetFocus(CWnd* pOldWnd)
{
	CPropertySheet::OnSetFocus(pOldWnd);
	TRACE("CUserSettings:SetFocus......\n");
}

void CUserSettings::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CPropertySheet::OnShowWindow(bShow, nStatus);
	GetTabControl()->SetFont(&m_Tabfont);
	SetActivePage(m_nPage);

	CPropertyPage* page = GetActivePage( );
	page->SetWindowText(_T("123"));

	TRACE("OnNextPage %d \n",m_nPage);
	//Invalidate();

}
// Modify all the following functions to add variables to be saved
///////////////////////////////////////////////////////////////////////////
void CUserSettings::SaveBackUp()
{
	if (m_pParams != NULL){
		memcpy(&m_BackUpParams,m_pParams,sizeof(ALLSETTINGS));
	}	
}
void CUserSettings::LoadBackUp()
{
	if (m_pParams != NULL){
		memcpy(m_pParams,&m_BackUpParams,sizeof(ALLSETTINGS));
	}	
}
void CUserSettings::LoadParams()
{
	if (m_pParams != NULL){
		// Copy to page
		//memcpy(&m_Page1.m_VisSettings,&m_pParams->VisSettings1,sizeof(VISIONSETTINGS1));
		//memcpy(&m_Page3.m_VisSettings,&m_pParams->VisSettings3,sizeof(VISIONSETTINGS3));
		//memcpy(&m_Page2.m_VisSettings,&m_pParams->VisSettings2,sizeof(VISIONSETTINGS2));
		//TRACE("Load page data... m_pParams->VisSettings4=%d \n",m_pParams->VisSettings4.TrimModeEnable);
		//TRACE("Load page data m_Page1.MinBaconSize = %d \n",m_Page1.m_VisSettings.MinBaconSize);
	}
}
void CUserSettings::SetParams()
{
	if (m_pParams != NULL){
		// Copy from page
		//memcpy(&m_pParams->VisSettings1,&m_Page1.m_VisSettings,sizeof(VISIONSETTINGS1));
		//memcpy(&m_pParams->VisSettings3,&m_Page3.m_VisSettings,sizeof(VISIONSETTINGS3));
		//memcpy(&m_pParams->VisSettings2,&m_Page2.m_VisSettings,sizeof(VISIONSETTINGS2));
		//TRACE("Save page data m_Page1.MinBaconSize = %d \n",m_Page1.m_VisSettings.MinBaconSize);
	}
}

BOOL CUserSettings::PreCreateWindow(CREATESTRUCT& cs)
{
	TRACE("PreCreateWindow......................................................... PreCreateWindow\n");
    if (!CPropertySheet::PreCreateWindow (cs))
        return FALSE;

    cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
    return TRUE;

	//return CPropertySheet::PreCreateWindow(cs);
}
