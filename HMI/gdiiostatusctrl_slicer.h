#pragma once

// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.

/////////////////////////////////////////////////////////////////////////////
// CGdiiostatusctrl wrapper class

class CGdiiostatusctrl : public CWnd
{
protected:
	DECLARE_DYNCREATE(CGdiiostatusctrl)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0xCF5F3DF3, 0x3E8E, 0x435A, { 0x99, 0xF3, 0x58, 0xE3, 0x68, 0x8, 0x7, 0xBF } };
		return clsid;
	}
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle,
						const RECT& rect, CWnd* pParentWnd, UINT nID, 
						CCreateContext* pContext = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID); 
	}

    BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, 
				UINT nID, CFile* pPersist = NULL, BOOL bStorage = FALSE,
				BSTR bstrLicKey = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
		pPersist, bStorage, bstrLicKey); 
	}

// Attributes
public:


// Operations
public:

// _DGDIIoStatus

// Functions
//

	void AboutBox()
	{
		InvokeHelper(DISPID_ABOUTBOX, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}

// Properties
//

short GetHasStatusBox()
{
	short result;
	GetProperty(0x1, VT_I2, (void*)&result);
	return result;
}
void SetHasStatusBox(short propVal)
{
	SetProperty(0x1, VT_I2, propVal);
}
short GetTitleFontSize()
{
	short result;
	GetProperty(0x2, VT_I2, (void*)&result);
	return result;
}
void SetTitleFontSize(short propVal)
{
	SetProperty(0x2, VT_I2, propVal);
}
unsigned long GetTitleTextColor()
{
	unsigned long result;
	GetProperty(0x3, VT_UI4, (void*)&result);
	return result;
}
void SetTitleTextColor(unsigned long propVal)
{
	SetProperty(0x3, VT_UI4, propVal);
}
short GetTitleDoGradientFill()
{
	short result;
	GetProperty(0x4, VT_I2, (void*)&result);
	return result;
}
void SetTitleDoGradientFill(short propVal)
{
	SetProperty(0x4, VT_I2, propVal);
}
CString GetTitleText()
{
	CString result;
	GetProperty(0x5, VT_BSTR, (void*)&result);
	return result;
}
void SetTitleText(CString propVal)
{
	SetProperty(0x5, VT_BSTR, propVal);
}
CString GetIOStatusText()
{
	CString result;
	GetProperty(0x6, VT_BSTR, (void*)&result);
	return result;
}
void SetIOStatusText(CString propVal)
{
	SetProperty(0x6, VT_BSTR, propVal);
}
short GetIOStatusTextFontSize()
{
	short result;
	GetProperty(0x7, VT_I2, (void*)&result);
	return result;
}
void SetIOStatusTextFontSize(short propVal)
{
	SetProperty(0x7, VT_I2, propVal);
}
unsigned long GetIOStatusTextColor()
{
	unsigned long result;
	GetProperty(0x8, VT_UI4, (void*)&result);
	return result;
}
void SetIOStatusTextColor(unsigned long propVal)
{
	SetProperty(0x8, VT_UI4, propVal);
}
unsigned long GetIOStatusTextBackColor()
{
	unsigned long result;
	GetProperty(0x9, VT_UI4, (void*)&result);
	return result;
}
void SetIOStatusTextBackColor(unsigned long propVal)
{
	SetProperty(0x9, VT_UI4, propVal);
}
short GetIOStatusInvert()
{
	short result;
	GetProperty(0xa, VT_I2, (void*)&result);
	return result;
}
void SetIOStatusInvert(short propVal)
{
	SetProperty(0xa, VT_I2, propVal);
}
short GetIOStatusBit()
{
	short result;
	GetProperty(0xb, VT_I2, (void*)&result);
	return result;
}
void SetIOStatusBit(short propVal)
{
	SetProperty(0xb, VT_I2, propVal);
}
unsigned long GetTitleTextBackColor()
{
	unsigned long result;
	GetProperty(0xc, VT_UI4, (void*)&result);
	return result;
}
void SetTitleTextBackColor(unsigned long propVal)
{
	SetProperty(0xc, VT_UI4, propVal);
}
short GetTotalIoPoints()
{
	short result;
	GetProperty(0xd, VT_I2, (void*)&result);
	return result;
}
void SetTotalIoPoints(short propVal)
{
	SetProperty(0xd, VT_I2, propVal);
}
short GetIoNameWidth()
{
	short result;
	GetProperty(0xe, VT_I2, (void*)&result);
	return result;
}
void SetIoNameWidth(short propVal)
{
	SetProperty(0xe, VT_I2, propVal);
}
short GetLedColorSelect()
{
	short result;
	GetProperty(0xf, VT_I2, (void*)&result);
	return result;
}
void SetLedColorSelect(short propVal)
{
	SetProperty(0xf, VT_I2, propVal);
}
unsigned long GetIoStatusWord()
{
	unsigned long result;
	GetProperty(0x10, VT_UI4, (void*)&result);
	return result;
}
void SetIoStatusWord(unsigned long propVal)
{
	SetProperty(0x10, VT_UI4, propVal);
}
short GetIoForceEnable()
{
	short result;
	GetProperty(0x11, VT_I2, (void*)&result);
	return result;
}
void SetIoForceEnable(short propVal)
{
	SetProperty(0x11, VT_I2, propVal);
}
unsigned long GetIoStatusWordInvert()
{
	unsigned long result;
	GetProperty(0x12, VT_UI4, (void*)&result);
	return result;
}
void SetIoStatusWordInvert(unsigned long propVal)
{
	SetProperty(0x12, VT_UI4, propVal);
}


};