// GDIStatusBoxExPropPage.cpp : Implementation of the CGDIStatusBoxExPropPage property page class.

#include "stdafx.h"
#include "GDIStatusBoxEx.h"
#include "GDIStatusBoxExPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CGDIStatusBoxExPropPage, COlePropertyPage)



// Message map

BEGIN_MESSAGE_MAP(CGDIStatusBoxExPropPage, COlePropertyPage)
END_MESSAGE_MAP()



// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CGDIStatusBoxExPropPage, "GDISTATUSBOXEX.GDIStatusBoxExPropPage.1",
	0x796d7ebe, 0xb35a, 0x4671, 0xb5, 0x40, 0x33, 0x3b, 0x8c, 0xc1, 0x30, 0xb2)



// CGDIStatusBoxExPropPage::CGDIStatusBoxExPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CGDIStatusBoxExPropPage

BOOL CGDIStatusBoxExPropPage::CGDIStatusBoxExPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_GDISTATUSBOXEX_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}



// CGDIStatusBoxExPropPage::CGDIStatusBoxExPropPage - Constructor

CGDIStatusBoxExPropPage::CGDIStatusBoxExPropPage() :
	COlePropertyPage(IDD, IDS_GDISTATUSBOXEX_PPG_CAPTION)
{
}



// CGDIStatusBoxExPropPage::DoDataExchange - Moves data between page and properties

void CGDIStatusBoxExPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}



// CGDIStatusBoxExPropPage message handlers
