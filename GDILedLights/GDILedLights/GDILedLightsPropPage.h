#pragma once

// GDILedLightsPropPage.h : Declaration of the CGDILedLightsPropPage property page class.


// CGDILedLightsPropPage : See GDILedLightsPropPage.cpp for implementation.

class CGDILedLightsPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CGDILedLightsPropPage)
	DECLARE_OLECREATE_EX(CGDILedLightsPropPage)

// Constructor
public:
	CGDILedLightsPropPage();

// Dialog Data
	enum { IDD = IDD_PROPPAGE_GDILEDLIGHTS };

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	DECLARE_MESSAGE_MAP()
};

