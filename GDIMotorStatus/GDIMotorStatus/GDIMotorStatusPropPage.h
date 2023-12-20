#pragma once

// GDIMotorStatusPropPage.h : Declaration of the CGDIMotorStatusPropPage property page class.


// CGDIMotorStatusPropPage : See GDIMotorStatusPropPage.cpp for implementation.

class CGDIMotorStatusPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CGDIMotorStatusPropPage)
	DECLARE_OLECREATE_EX(CGDIMotorStatusPropPage)

// Constructor
public:
	CGDIMotorStatusPropPage();

// Dialog Data
	enum { IDD = IDD_PROPPAGE_GDIMOTORSTATUS };

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	DECLARE_MESSAGE_MAP()
};

