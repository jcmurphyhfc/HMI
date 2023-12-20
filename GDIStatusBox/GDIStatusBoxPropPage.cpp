// GDIStatusBoxPropPage.cpp : Implementation of the CGDIStatusBoxPropPage property page class.

#include "stdafx.h"
#include "GDIStatusBox.h"
#include "GDIStatusBoxPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CGDIStatusBoxPropPage, COlePropertyPage)



// Message map

BEGIN_MESSAGE_MAP(CGDIStatusBoxPropPage, COlePropertyPage)
END_MESSAGE_MAP()



// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CGDIStatusBoxPropPage, "GDISTATUSBOX.GDIStatusBoxPropPage.1",
	0x4b9b61, 0xbf6b, 0x45ab, 0x8e, 0xdd, 0x71, 0xff, 0xd3, 0x60, 0x63, 0x81)



// CGDIStatusBoxPropPage::CGDIStatusBoxPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CGDIStatusBoxPropPage

BOOL CGDIStatusBoxPropPage::CGDIStatusBoxPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_GDISTATUSBOX_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}



// CGDIStatusBoxPropPage::CGDIStatusBoxPropPage - Constructor

CGDIStatusBoxPropPage::CGDIStatusBoxPropPage() :
	COlePropertyPage(IDD, IDS_GDISTATUSBOX_PPG_CAPTION)
{
}



// CGDIStatusBoxPropPage::DoDataExchange - Moves data between page and properties

void CGDIStatusBoxPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}



// CGDIStatusBoxPropPage message handlers
