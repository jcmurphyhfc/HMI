// GDIGagetPropPage.cpp : Implementation of the CGDIGagetPropPage property page class.

#include "stdafx.h"
#include "GDIGaget.h"
#include "GDIGagetPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CGDIGagetPropPage, COlePropertyPage)



// Message map

BEGIN_MESSAGE_MAP(CGDIGagetPropPage, COlePropertyPage)
END_MESSAGE_MAP()



// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CGDIGagetPropPage, "GDIGAGET.GDIGagetPropPage.1",
	0x10fe3faf, 0xd769, 0x4d9f, 0x8a, 0x68, 0x6e, 0xd0, 0x6a, 0x5e, 0x55, 0x83)



// CGDIGagetPropPage::CGDIGagetPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CGDIGagetPropPage

BOOL CGDIGagetPropPage::CGDIGagetPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_GDIGAGET_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}



// CGDIGagetPropPage::CGDIGagetPropPage - Constructor

CGDIGagetPropPage::CGDIGagetPropPage() :
	COlePropertyPage(IDD, IDS_GDIGAGET_PPG_CAPTION)
{
}



// CGDIGagetPropPage::DoDataExchange - Moves data between page and properties

void CGDIGagetPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}



// CGDIGagetPropPage message handlers
