// GDIIoStatusPropPage.cpp : Implementation of the CGDIIoStatusPropPage property page class.

#include "stdafx.h"
#include "GDIIoStatus.h"
#include "GDIIoStatusPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CGDIIoStatusPropPage, COlePropertyPage)



// Message map

BEGIN_MESSAGE_MAP(CGDIIoStatusPropPage, COlePropertyPage)
END_MESSAGE_MAP()



// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CGDIIoStatusPropPage, "GDIIOSTATUS.GDIIoStatusPropPage.1",
	0x1b3a350a, 0x36c0, 0x4149, 0x8d, 0x96, 0x53, 0x31, 0xc9, 0x8d, 0x55, 0x9f)



// CGDIIoStatusPropPage::CGDIIoStatusPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CGDIIoStatusPropPage

BOOL CGDIIoStatusPropPage::CGDIIoStatusPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_GDIIOSTATUS_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}



// CGDIIoStatusPropPage::CGDIIoStatusPropPage - Constructor

CGDIIoStatusPropPage::CGDIIoStatusPropPage() :
	COlePropertyPage(IDD, IDS_GDIIOSTATUS_PPG_CAPTION)
{
}



// CGDIIoStatusPropPage::DoDataExchange - Moves data between page and properties

void CGDIIoStatusPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}



// CGDIIoStatusPropPage message handlers
