#pragma once

// GDITeditPropPage.h : Declaration of the CGDITeditPropPage property page class.


// CGDITeditPropPage : See GDITeditPropPage.cpp for implementation.

class CGDITeditPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CGDITeditPropPage)
	DECLARE_OLECREATE_EX(CGDITeditPropPage)

// Constructor
public:
	CGDITeditPropPage();

// Dialog Data
	enum { IDD = IDD_PROPPAGE_GDITEDIT };

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	DECLARE_MESSAGE_MAP()
};

