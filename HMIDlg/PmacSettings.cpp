#include "StdAfx.h"
#include "HMIDlg.h"
#include "PmacSettings.h"

// PmacSettings.cpp : implementation file
//

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPmacSettings

IMPLEMENT_DYNAMIC(CPmacSettings, CPropertySheet)

CPmacSettings::CPmacSettings(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	m_ppBackPtr = NULL;
	m_pParams = NULL;
}

CPmacSettings::CPmacSettings(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	m_ppBackPtr = NULL;
	m_pParams = NULL;
}

CPmacSettings::~CPmacSettings()
{
	if (m_ppBackPtr)
		*m_ppBackPtr = NULL;
}

void CPmacSettings::Initialize(CWnd* pParentWnd,MOTIONSETTINGS* pParams)
{
	m_nPage = 0;
	m_nTotalPage = 5;

	// Set the titles
	m_Page1.m_psp.pszTitle = _T("BTC");
	m_Page2.m_psp.pszTitle = _T("Homing");
	m_Page3.m_psp.pszTitle = _T("Slicer");
	m_Page4.m_psp.pszTitle = _T("Two-Tier");
	m_Page5.m_psp.pszTitle = _T("Paper Feed");

	// Set the pointers
	m_pParams = pParams;
	m_Page1.m_pSettings = pParams;
	m_Page2.m_pSettings = pParams;
	m_Page3.m_pSettings = pParams;
	m_Page4.m_pSettings = pParams;
	m_Page5.m_pSettings = pParams;

	// Add the pages
    AddPage (&m_Page1);
    AddPage (&m_Page2);
    AddPage (&m_Page3); 
    AddPage (&m_Page4); 
    AddPage (&m_Page5); 
	m_pWndParent = pParentWnd;

	TRACE(".............................Initialize pmacv settings \n");

}

BEGIN_MESSAGE_MAP(CPmacSettings, CPropertySheet)
	//{{AFX_MSG_MAP(CPmacSettings)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
    ON_BN_CLICKED (ID_APPLY_NOW, OnApply)
	ON_BN_CLICKED (ID_SAVE_BUTTON, OnSaveButton)
	ON_BN_CLICKED (ID_RESTORE, OnRestore)
    ON_BN_CLICKED (ID_NEXT_PAGE, OnNextPage)
    ON_BN_CLICKED (ID_PREV_PAGE, OnPrevPage)
    ON_BN_CLICKED (IDOK, OnClose)
    ON_BN_CLICKED (ID_LOAD_MASTER, OnLoadMaster)
    ON_BN_CLICKED (ID_LOAD_USER, OnLoadUser)
    ON_BN_CLICKED (ID_SAVE_USER, OnSaveUser)
	ON_MESSAGE (WM_VISION_SETTINGS_CHANGED,OnChange)
	ON_WM_NCHITTEST()
	ON_WM_SETFOCUS()
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPmacSettings message handlers

BOOL CPmacSettings::OnInitDialog() 
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

	// Create the Utility buttons
	m_btnLoadMaster.Create (_T("Load \nMaster"), BS_MULTILINE | BS_DEFPUSHBUTTON | WS_CHILD | WS_VISIBLE | WS_TABSTOP,
		CRect (rc.right-151, rc.bottom-60, rc.right-81, rc.bottom-5), this, ID_LOAD_MASTER);
	m_btnLoadUser.Create (_T("Load \nUser"), BS_MULTILINE | BS_DEFPUSHBUTTON | WS_CHILD | WS_VISIBLE | WS_TABSTOP,
		CRect (rc.right-221, rc.bottom-60, rc.right-151, rc.bottom-5), this, ID_LOAD_USER);
	m_btnSaveUser.Create (_T("Save \nUser"), BS_MULTILINE | BS_DEFPUSHBUTTON | WS_CHILD | WS_VISIBLE | WS_TABSTOP,
		CRect (rc.right-291, rc.bottom-60, rc.right-221, rc.bottom-5), this, ID_SAVE_USER);

	// Set parent pointers
	m_Page1.m_pWndParent = this;
	m_Page2.m_pWndParent = this;
	m_Page2.m_pComWnd = m_pWndParent;
	m_Page3.m_pWndParent = this;
	m_Page4.m_pWndParent = this;
	m_Page5.m_pWndParent = this;

	
	return bResult;
}

void CPmacSettings::PostNcDestroy() 
{
	CPropertySheet::PostNcDestroy();
	delete this;
}
void CPmacSettings::OnApply()
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

void CPmacSettings::OnSaveButton()
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

void CPmacSettings::OnRestore()
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

void CPmacSettings::OnLoadUser()
{
	// Send restore message
	if (m_pWndParent != NULL){
		m_pWndParent->SendMessage (WM_SETTINGS_LOAD_USER, 0, 0);
		//TRACE("Send Save message to parent \n");
	}

	// Load Dialog members with Document data
	LoadParams();

	// Set data in active page
	GetActivePage ()->UpdateData (FALSE);
	m_btnRestoreButton.EnableWindow(FALSE);

}
void CPmacSettings::OnSaveUser()
{
	// Get data from active page
	GetActivePage ()->UpdateData (TRUE);

	// Send restore message
	if (m_pWndParent != NULL){
		m_pWndParent->SendMessage (WM_SETTINGS_SAVE_USER, 0, 0);
		//TRACE("Send Save message to parent \n");
	}
}
void CPmacSettings::OnLoadMaster()
{
	// Send restore message
	if (m_pWndParent != NULL){
		m_pWndParent->SendMessage (WM_SETTINGS_LOAD_MASTER, 0, 0);
		//TRACE("Send Save message to parent \n");
	}

	// Load Dialog members with Document data
	LoadParams();

	// Set data in active page
	GetActivePage ()->UpdateData (FALSE);
	m_btnRestoreButton.EnableWindow(FALSE);

}

void CPmacSettings::OnNextPage()
{
	m_nPage++;
	if (m_nPage >= m_nTotalPage)
		m_nPage = 0;

	SetActivePage(m_nPage);
	TRACE(".............................OnNextPage %d \n",m_nPage);
}
void CPmacSettings::OnPrevPage()
{
	m_nPage--;
	if (m_nPage < 0)
		m_nPage = m_nTotalPage - 1;
		
	SetActivePage(m_nPage);
	TRACE("OnPrevPage.....Page %d \n",m_nPage);
}
void CPmacSettings::OnClose()
{
	TRACE("OnClose \n");
	DestroyWindow();
}

LRESULT CPmacSettings::OnChange(WPARAM wParam, LPARAM lParam)
{
	TRACE("CPmacSettings::OnChange........... \n");
	//SetModified (TRUE);
	m_btnApplyButton.EnableWindow();
	//m_btnApplyButton.EnableWindow();

	m_btnSaveButton.EnableWindow();


	return 0;
}

LRESULT CPmacSettings::OnNcHitTest(CPoint point)
{
    LRESULT nHitTest = CPropertySheet::OnNcHitTest (point);
    if ((nHitTest == HTCLIENT) && (::GetAsyncKeyState (MK_LBUTTON) < 0))
        nHitTest = HTCAPTION;
    return nHitTest;

}

int CPmacSettings::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CPropertySheet::OnCreate(lpCreateStruct) == -1)
		return -1;
	
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

	m_Page4.m_pfont = &m_fontSmall;
	m_Page4.m_clrText = m_clrText;
	m_Page4.m_clrBack = m_clrBack;

	m_Page5.m_pfont = &m_fontSmall;
	m_Page5.m_clrText = m_clrText;
	m_Page5.m_clrBack = m_clrBack;

	// Load Dialog members with Document data
	LoadParams();
	//GetActivePage ()->UpdateData (FALSE);

	return 0;
}
void CPmacSettings::OnSetFocus(CWnd* pOldWnd)
{
	//		AfxMessageBox(_T("pmac settimngs"));
	CPropertySheet::OnSetFocus(pOldWnd);
	TRACE("CPmacSettings:SetFocus......\n");
}

void CPmacSettings::OnShowWindow(BOOL bShow, UINT nStatus)
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
void CPmacSettings::SaveBackUp()
{
	if (m_pParams != NULL){
		memcpy(&m_BackUpParams,m_pParams,sizeof(MOTIONSETTINGS));
	}	
}
void CPmacSettings::LoadBackUp()
{
	if (m_pParams != NULL){
		memcpy(m_pParams,&m_BackUpParams,sizeof(MOTIONSETTINGS));
	}	
}
void CPmacSettings::LoadParams()
{
	//if (m_pParams != NULL){

	//	// Copy to page
	//	//memcpy(&m_Page1.m_VisSettings,&m_pParams->VisSettings1,sizeof(VISIONSETTINGS1));
	//	//memcpy(&m_Page2.m_VisSettings,&m_pParams->VisSettings2,sizeof(VISIONSETTINGS2));
	//	//memcpy(&m_Page3.m_VisSettings,&m_pParams->VisSettings3,sizeof(VISIONSETTINGS3));
	//}
}
void CPmacSettings::SetParams()
{
	//if (m_pParams != NULL){

	//	// Copy from page
	//	//memcpy(&m_pParams->VisSettings1,&m_Page1.m_VisSettings,sizeof(VISIONSETTINGS1));
	//	//memcpy(&m_pParams->VisSettings2,&m_Page2.m_VisSettings,sizeof(VISIONSETTINGS2));
	//	//memcpy(&m_pParams->VisSettings3,&m_Page3.m_VisSettings,sizeof(VISIONSETTINGS3));
	//}
}