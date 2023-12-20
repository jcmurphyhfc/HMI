#pragma once

// GDIStatusBoxPropPage.h : Declaration of the CGDIStatusBoxPropPage property page class.


// CGDIStatusBoxPropPage : See GDIStatusBoxPropPage.cpp for implementation.

class CGDIStatusBoxPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CGDIStatusBoxPropPage)
	DECLARE_OLECREATE_EX(CGDIStatusBoxPropPage)

// Constructor
public:
	CGDIStatusBoxPropPage();

// Dialog Data
	enum { IDD = IDD_PROPPAGE_GDISTATUSBOX };

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	DECLARE_MESSAGE_MAP()
};

