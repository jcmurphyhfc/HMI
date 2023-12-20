#pragma once

// EIPGadgetPropPage.h : Declaration of the CEIPGadgetPropPage property page class.


// CEIPGadgetPropPage : See EIPGadgetPropPage.cpp for implementation.

class CEIPGadgetPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CEIPGadgetPropPage)
	DECLARE_OLECREATE_EX(CEIPGadgetPropPage)

// Constructor
public:
	CEIPGadgetPropPage();

// Dialog Data
	enum { IDD = IDD_PROPPAGE_EIPGADGET };

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	DECLARE_MESSAGE_MAP()
};

