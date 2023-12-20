// GDIButtonXLPropPage.cpp : Implementation of the CGDIButtonXLPropPage property page class.

#include "stdafx.h"
#include "GDIButtonXL.h"
#include "GDIButtonXLPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CGDIButtonXLPropPage, COlePropertyPage)



// Message map

BEGIN_MESSAGE_MAP(CGDIButtonXLPropPage, COlePropertyPage)
END_MESSAGE_MAP()



// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CGDIButtonXLPropPage, "GDIBUTTONXL.GDIButtonXLPropPage.1",
	0x2924e5eb, 0xc261, 0x4bf5, 0xa1, 0xd9, 0xe2, 0x9b, 0x23, 0x85, 0x43, 0x18)



// CGDIButtonXLPropPage::CGDIButtonXLPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CGDIButtonXLPropPage

BOOL CGDIButtonXLPropPage::CGDIButtonXLPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_GDIBUTTONXL_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}



// CGDIButtonXLPropPage::CGDIButtonXLPropPage - Constructor

CGDIButtonXLPropPage::CGDIButtonXLPropPage() :
	COlePropertyPage(IDD, IDS_GDIBUTTONXL_PPG_CAPTION)
		, m_strText1(_T(""))
		, m_strText2(_T(""))
		, m_nFontSize(0)
		, m_nButtonSelect(0)
	{
}



// CGDIButtonXLPropPage::DoDataExchange - Moves data between page and properties

void CGDIButtonXLPropPage::DoDataExchange(CDataExchange* pDX)
{

	DDP_Text(pDX, IDC_FONT_SIZE, m_nFontSize, _T("FontSize") );
	DDX_Text(pDX, IDC_FONT_SIZE, m_nFontSize);
	DDV_MinMaxLong(pDX, m_nFontSize, 0, 72);

	DDP_Text(pDX, IDC_BUTTON_TYPE, m_nButtonSelect, _T("BitMapSelect") );
	DDX_Text(pDX, IDC_BUTTON_TYPE, m_nButtonSelect);
	DDV_MinMaxLong(pDX, m_nButtonSelect, 0, 10);

	DDP_Text(pDX, IDC_TEXT1, m_strText1, _T("Text1") );
	DDX_Text(pDX, IDC_TEXT1, m_strText1);
	DDV_MaxChars(pDX, m_strText1, 64);

	DDP_Text(pDX, IDC_TEXT2, m_strText2, _T("Text2") );
	DDX_Text(pDX, IDC_TEXT2, m_strText2);
	DDV_MaxChars(pDX, m_strText2, 64);

	DDP_PostProcessing(pDX);


	//DDX_Control(pDX, IDC_SPIN_FONT_SIZE, m_ctlSpinFontSize);
	//DDP_Text(pDX, IDC_EDIT_TITLE, m_strTitle, _T("Title") );
	//DDX_Text(pDX, IDC_EDIT_TITLE, m_strTitle);
	//DDV_MaxChars(pDX, m_strTitle, 35);
	//DDP_Text(pDX, IDC_EDIT_FONT_SIZE, m_nFontSize, _T("FontSize") );
	//DDX_Text(pDX, IDC_EDIT_FONT_SIZE, m_nFontSize);
	//DDV_MinMaxInt(pDX, m_nFontSize, 8, 72);
	//DDP_Check(pDX, IDC_TITLE_STATUS, m_bTitleOnly, _T("TitleOnly") );
	//DDX_Check(pDX, IDC_TITLE_STATUS, m_bTitleOnly);
	//DDP_Check(pDX, IDC_AUTO_UPDATE, m_bAutoUpdate, _T("AutoUpdate") );
	//DDX_Check(pDX, IDC_AUTO_UPDATE, m_bAutoUpdate);
	//DDP_Text(pDX, IDC_UPDATE_TIME, m_lnUpDateTime, _T("UpDateTime") );
	//DDX_Text(pDX, IDC_UPDATE_TIME, m_lnUpDateTime);
	//DDV_MinMaxLong(pDX, m_lnUpDateTime, 50, 10000);
	//DDP_PostProcessing(pDX);

}





// CGDIButtonXLPropPage message handlers
