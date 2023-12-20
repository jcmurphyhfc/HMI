#pragma once

// GDIMultiReadoutPropPage.h : Declaration of the CGDIMultiReadoutPropPage property page class.


// CGDIMultiReadoutPropPage : See GDIMultiReadoutPropPage.cpp for implementation.

class CGDIMultiReadoutPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CGDIMultiReadoutPropPage)
	DECLARE_OLECREATE_EX(CGDIMultiReadoutPropPage)

// Constructor
public:
	CGDIMultiReadoutPropPage();

// Dialog Data
	enum { IDD = IDD_PROPPAGE_GDIMULTIREADOUT };

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	DECLARE_MESSAGE_MAP()
};

