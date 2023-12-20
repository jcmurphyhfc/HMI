#pragma once

// GDIGagetPropPage.h : Declaration of the CGDIGagetPropPage property page class.


// CGDIGagetPropPage : See GDIGagetPropPage.cpp for implementation.

class CGDIGagetPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CGDIGagetPropPage)
	DECLARE_OLECREATE_EX(CGDIGagetPropPage)

// Constructor
public:
	CGDIGagetPropPage();

// Dialog Data
	enum { IDD = IDD_PROPPAGE_GDIGAGET };

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	DECLARE_MESSAGE_MAP()
};

