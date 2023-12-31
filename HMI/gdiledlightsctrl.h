#pragma once

// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.

/////////////////////////////////////////////////////////////////////////////
// CGdiledlightsctrl wrapper class

class CGdiledlightsctrl : public CWnd
{
protected:
	DECLARE_DYNCREATE(CGdiledlightsctrl)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0x292C0FD4, 0xF89F, 0x4003, { 0xB4, 0xAB, 0x95, 0x31, 0xDE, 0xFC, 0x2B, 0x3B } };
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

// _DGDILedLights

// Functions
//

	void AboutBox()
	{
		InvokeHelper(DISPID_ABOUTBOX, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}

// Properties
//

short GetLedColorSelect()
{
	short result;
	GetProperty(0x1, VT_I2, (void*)&result);
	return result;
}
void SetLedColorSelect(short propVal)
{
	SetProperty(0x1, VT_I2, propVal);
}
short GetTotalIoPoints()
{
	short result;
	GetProperty(0x2, VT_I2, (void*)&result);
	return result;
}
void SetTotalIoPoints(short propVal)
{
	SetProperty(0x2, VT_I2, propVal);
}
long GetIoStatusWord()
{
	long result;
	GetProperty(0x3, VT_I4, (void*)&result);
	return result;
}
void SetIoStatusWord(long propVal)
{
	SetProperty(0x3, VT_I4, propVal);
}


};
