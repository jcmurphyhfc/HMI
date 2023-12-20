#pragma once

// GDIStatusBoxExPropPage.h : Declaration of the CGDIStatusBoxExPropPage property page class.


// CGDIStatusBoxExPropPage : See GDIStatusBoxExPropPage.cpp for implementation.

class CGDIStatusBoxExPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CGDIStatusBoxExPropPage)
	DECLARE_OLECREATE_EX(CGDIStatusBoxExPropPage)

// Constructor
public:
	CGDIStatusBoxExPropPage();

// Dialog Data
	enum { IDD = IDD_PROPPAGE_GDISTATUSBOXEX };

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	DECLARE_MESSAGE_MAP()
};

