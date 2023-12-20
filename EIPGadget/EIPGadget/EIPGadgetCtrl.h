#pragma once

//#include "RTA\eipc_system.h"

// C linkage.
//extern "C" {
#include "RTA\EIPCOM.h"
//}

// EIPGadgetCtrl.h : Declaration of the CEIPGadgetCtrl ActiveX Control class.


// CEIPGadgetCtrl : See EIPGadgetCtrl.cpp for implementation.

class CEIPGadgetCtrl : public COleControl
{
	DECLARE_DYNCREATE(CEIPGadgetCtrl)

// Constructor
public:
	CEIPGadgetCtrl();
	EIPRUNTHREADDATASTRUCT m_EIPCOM;
	CBitmap m_On;
	CBitmap m_Off;

// Internal methods
public:
	void DrawTitle(CDC *pDC,const CRect& Rect);
	void DoGradientFill(CDC *pDC,const CRect& Rect);
	void PaintTicks(CDC* pDC,const CRect& Rect);
	void DrawBar(CDC* pDC,const CRect& rect);


// Overrides
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();

// Implementation
protected:
	~CEIPGadgetCtrl();

	DECLARE_OLECREATE_EX(CEIPGadgetCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CEIPGadgetCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CEIPGadgetCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CEIPGadgetCtrl)		// Type name and misc status

// Message maps
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// Event maps
	DECLARE_EVENT_MAP()


// Dispatch and event IDs
public:
	enum {
		dispidOpenCom = 6L,
		dispidTitleTextColor = 5,
		dispidTitleBackgroundColor = 4,
		dispidTitleFontSize = 3,
		dispidTitle = 2,
		dispidDoGradientFill = 1
	};
protected:
	void OnDoGradientFillChanged(void);
	SHORT m_DoGradientFill;
	void OnTitleChanged(void);
	CString m_Title;
	void OnTitleFontSizeChanged(void);
	SHORT m_TitleFontSize;
	void OnTitleBackgroundColorChanged(void);
	OLE_COLOR m_TitleBackgroundColor;
	void OnTitleTextColorChanged(void);
	OLE_COLOR m_TitleTextColor;
	SHORT OpenCom(LPCTSTR IpAddr);
};

