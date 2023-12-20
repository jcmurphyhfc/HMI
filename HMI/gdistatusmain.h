#pragma once

// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.

/////////////////////////////////////////////////////////////////////////////
// CGdistatusmain wrapper class

class CGdistatusmain : public CWnd
{
protected:
	DECLARE_DYNCREATE(CGdistatusmain)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0x13947960, 0x120F, 0x4559, { 0xAD, 0x1B, 0xFE, 0xD6, 0xE4, 0x57, 0xD7, 0xAA } };
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

// _DGDIStatusBox

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
CString GetStatusText()
{
	CString result;
	GetProperty(0x6, VT_BSTR, (void*)&result);
	return result;
}
void SetStatusText(CString propVal)
{
	SetProperty(0x6, VT_BSTR, propVal);
}
short GetStatusTextFontSize()
{
	short result;
	GetProperty(0x7, VT_I2, (void*)&result);
	return result;
}
void SetStatusTextFontSize(short propVal)
{
	SetProperty(0x7, VT_I2, propVal);
}
unsigned long GetStatusTextColor()
{
	unsigned long result;
	GetProperty(0x8, VT_UI4, (void*)&result);
	return result;
}
void SetStatusTextColor(unsigned long propVal)
{
	SetProperty(0x8, VT_UI4, propVal);
}
unsigned long GetStatusTextBackColor()
{
	unsigned long result;
	GetProperty(0x9, VT_UI4, (void*)&result);
	return result;
}
void SetStatusTextBackColor(unsigned long propVal)
{
	SetProperty(0x9, VT_UI4, propVal);
}
short GetStatusBlink()
{
	short result;
	GetProperty(0xa, VT_I2, (void*)&result);
	return result;
}
void SetStatusBlink(short propVal)
{
	SetProperty(0xa, VT_I2, propVal);
}
short GetStatusState()
{
	short result;
	GetProperty(0xb, VT_I2, (void*)&result);
	return result;
}
void SetStatusState(short propVal)
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
unsigned long GetStatusBlinkOnTime()
{
	unsigned long result;
	GetProperty(0xd, VT_UI4, (void*)&result);
	return result;
}
void SetStatusBlinkOnTime(unsigned long propVal)
{
	SetProperty(0xd, VT_UI4, propVal);
}
unsigned long GetStatusBlinkOffTime()
{
	unsigned long result;
	GetProperty(0xe, VT_UI4, (void*)&result);
	return result;
}
void SetStatusBlinkOffTime(unsigned long propVal)
{
	SetProperty(0xe, VT_UI4, propVal);
}


};
