// GDIMultiReadoutPropPage.cpp : Implementation of the CGDIMultiReadoutPropPage property page class.

#include "stdafx.h"
#include "GDIMultiReadout.h"
#include "GDIMultiReadoutPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CGDIMultiReadoutPropPage, COlePropertyPage)



// Message map

BEGIN_MESSAGE_MAP(CGDIMultiReadoutPropPage, COlePropertyPage)
END_MESSAGE_MAP()



// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CGDIMultiReadoutPropPage, "GDIMULTIREADOU.GDIMultiReadouPropPage.1",
	0xf3087126, 0x7a85, 0x4d76, 0x91, 0xcd, 0x41, 0xcb, 0xb5, 0x8b, 0xdd, 0x6b)



// CGDIMultiReadoutPropPage::CGDIMultiReadoutPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CGDIMultiReadoutPropPage

BOOL CGDIMultiReadoutPropPage::CGDIMultiReadoutPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_GDIMULTIREADOUT_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}



// CGDIMultiReadoutPropPage::CGDIMultiReadoutPropPage - Constructor

CGDIMultiReadoutPropPage::CGDIMultiReadoutPropPage() :
	COlePropertyPage(IDD, IDS_GDIMULTIREADOUT_PPG_CAPTION)
{
}



// CGDIMultiReadoutPropPage::DoDataExchange - Moves data between page and properties

void CGDIMultiReadoutPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}



// CGDIMultiReadoutPropPage message handlers
