#pragma once

// GDIIoStatusPropPage.h : Declaration of the CGDIIoStatusPropPage property page class.


// CGDIIoStatusPropPage : See GDIIoStatusPropPage.cpp for implementation.

class CGDIIoStatusPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CGDIIoStatusPropPage)
	DECLARE_OLECREATE_EX(CGDIIoStatusPropPage)

// Constructor
public:
	CGDIIoStatusPropPage();

// Dialog Data
	enum { IDD = IDD_PROPPAGE_GDIIOSTATUS };

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	DECLARE_MESSAGE_MAP()
};

