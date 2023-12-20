// GDITeditPropPage.cpp : Implementation of the CGDITeditPropPage property page class.

#include "stdafx.h"
#include "GDITedit.h"
#include "GDITeditPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CGDITeditPropPage, COlePropertyPage)



// Message map

BEGIN_MESSAGE_MAP(CGDITeditPropPage, COlePropertyPage)
END_MESSAGE_MAP()



// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CGDITeditPropPage, "GDITEDIT.GDITeditPropPage.1",
	0xa45cae36, 0xfbac, 0x4294, 0x95, 0x13, 0x2f, 0xb0, 0x51, 0x26, 0x83, 0xde)



// CGDITeditPropPage::CGDITeditPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CGDITeditPropPage

BOOL CGDITeditPropPage::CGDITeditPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_GDITEDIT_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}



// CGDITeditPropPage::CGDITeditPropPage - Constructor

CGDITeditPropPage::CGDITeditPropPage() :
	COlePropertyPage(IDD, IDS_GDITEDIT_PPG_CAPTION)
{
}



// CGDITeditPropPage::DoDataExchange - Moves data between page and properties

void CGDITeditPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}



// CGDITeditPropPage message handlers
