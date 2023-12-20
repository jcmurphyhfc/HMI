#pragma once

// GDIButtonXLPropPage.h : Declaration of the CGDIButtonXLPropPage property page class.


// CGDIButtonXLPropPage : See GDIButtonXLPropPage.cpp for implementation.

class CGDIButtonXLPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CGDIButtonXLPropPage)
	DECLARE_OLECREATE_EX(CGDIButtonXLPropPage)

// Constructor
public:
	CGDIButtonXLPropPage();

// Dialog Data
	enum { IDD = IDD_PROPPAGE_GDIBUTTONXL };

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	DECLARE_MESSAGE_MAP()
public:
	CString m_strText1;
	CString m_strText2;
	long m_nFontSize;
	long m_nButtonSelect;
};

