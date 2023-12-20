// GDIMotorStatusPropPage.cpp : Implementation of the CGDIMotorStatusPropPage property page class.

#include "stdafx.h"
#include "GDIMotorStatus.h"
#include "GDIMotorStatusPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CGDIMotorStatusPropPage, COlePropertyPage)



// Message map

BEGIN_MESSAGE_MAP(CGDIMotorStatusPropPage, COlePropertyPage)
END_MESSAGE_MAP()



// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CGDIMotorStatusPropPage, "GDIMOTORSTATUS.GDIMotorStatusPropPage.1",
	0x2c9a110e, 0x4a34, 0x44b5, 0xb5, 0xc, 0x14, 0xc0, 0x5d, 0xab, 0x2c, 0x8e)



// CGDIMotorStatusPropPage::CGDIMotorStatusPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CGDIMotorStatusPropPage

BOOL CGDIMotorStatusPropPage::CGDIMotorStatusPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_GDIMOTORSTATUS_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}



// CGDIMotorStatusPropPage::CGDIMotorStatusPropPage - Constructor

CGDIMotorStatusPropPage::CGDIMotorStatusPropPage() :
	COlePropertyPage(IDD, IDS_GDIMOTORSTATUS_PPG_CAPTION)
{
}



// CGDIMotorStatusPropPage::DoDataExchange - Moves data between page and properties

void CGDIMotorStatusPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}



// CGDIMotorStatusPropPage message handlers
