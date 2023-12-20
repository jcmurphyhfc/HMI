// EIPGadgetPropPage.cpp : Implementation of the CEIPGadgetPropPage property page class.

#include "stdafx.h"
#include "EIPGadget.h"
#include "EIPGadgetPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CEIPGadgetPropPage, COlePropertyPage)



// Message map

BEGIN_MESSAGE_MAP(CEIPGadgetPropPage, COlePropertyPage)
END_MESSAGE_MAP()



// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CEIPGadgetPropPage, "EIPGADGET.EIPGadgetPropPage.1",
	0x8f7fb158, 0x9d73, 0x4660, 0x87, 0x99, 0xc2, 0xc4, 0x24, 0x63, 0x1c, 0x72)



// CEIPGadgetPropPage::CEIPGadgetPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CEIPGadgetPropPage

BOOL CEIPGadgetPropPage::CEIPGadgetPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_EIPGADGET_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}



// CEIPGadgetPropPage::CEIPGadgetPropPage - Constructor

CEIPGadgetPropPage::CEIPGadgetPropPage() :
	COlePropertyPage(IDD, IDS_EIPGADGET_PPG_CAPTION)
{
}



// CEIPGadgetPropPage::DoDataExchange - Moves data between page and properties

void CEIPGadgetPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}



// CEIPGadgetPropPage message handlers
