// GDILedLightsPropPage.cpp : Implementation of the CGDILedLightsPropPage property page class.

#include "stdafx.h"
#include "GDILedLights.h"
#include "GDILedLightsPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CGDILedLightsPropPage, COlePropertyPage)



// Message map

BEGIN_MESSAGE_MAP(CGDILedLightsPropPage, COlePropertyPage)
END_MESSAGE_MAP()



// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CGDILedLightsPropPage, "GDILEDLIGHTS.GDILedLightsPropPage.1",
	0xd01d3b22, 0x4a90, 0x48f3, 0xba, 0x64, 0x67, 0xd0, 0x4c, 0x92, 0x89, 0x8a)



// CGDILedLightsPropPage::CGDILedLightsPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CGDILedLightsPropPage

BOOL CGDILedLightsPropPage::CGDILedLightsPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_GDILEDLIGHTS_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}



// CGDILedLightsPropPage::CGDILedLightsPropPage - Constructor

CGDILedLightsPropPage::CGDILedLightsPropPage() :
	COlePropertyPage(IDD, IDS_GDILEDLIGHTS_PPG_CAPTION)
{
}



// CGDILedLightsPropPage::DoDataExchange - Moves data between page and properties

void CGDILedLightsPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}



// CGDILedLightsPropPage message handlers
