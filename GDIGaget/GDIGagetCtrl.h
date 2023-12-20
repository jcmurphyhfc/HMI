#pragma once

//#include <afxcmn.h>

// GDIGagetCtrl.h : Declaration of the CGDIGagetCtrl ActiveX Control class.
#define IDC_PROGRESS    101

// CGDIGagetCtrl : See GDIGagetCtrl.cpp for implementation.

class CGDIGagetCtrl : public COleControl
{
	DECLARE_DYNCREATE(CGDIGagetCtrl)

// Constructor
public:
	CGDIGagetCtrl();

	//BOOL m_HasWnd;
	//CProgressCtrl m_wndProgress;
	CBitmap m_GreenBar;
	CBitmap m_YellowBar;
	CBitmap m_RedBar;
	int m_Pos;
	int m_Lower;
	int m_Upper;

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
	~CGDIGagetCtrl();

	DECLARE_OLECREATE_EX(CGDIGagetCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CGDIGagetCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CGDIGagetCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CGDIGagetCtrl)		// Type name and misc status

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
		dispidTickUnits = 13,
		dispidTickCount = 12,
		dispidTickOffset = 11,
		dispidTickFontSize = 10,
		dispidTickColor = 9,
		dispidTickBackColor = 8,
		dispidTitle = 7,
		dispidTitleTextColor = 6,
		dispidTitleTextBackColor = 5,
		dispidDoGradientFill = 4,
		dispidSetRange = 3L,
		dispidSetPos = 2L,
		dispidTitleFontSize = 1
	};
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
protected:
	void OnTitleFontSizeChanged(void);
	SHORT m_TitleFontSize;
	void SetPos(LONG Pos);
	void SetRange(LONG Lower, LONG Upper);
	void OnDoGradientFillChanged(void);
	SHORT m_DoGradientFill;
	void OnTitleTextBackColorChanged(void);
	OLE_COLOR m_TitleTextBackColor;
	void OnTitleTextColorChanged(void);
	OLE_COLOR m_TitleTextColor;
	void OnTitleChanged(void);
	CString m_Title;
	void OnTickBackColorChanged(void);
	OLE_COLOR m_TickBackColor;
	void OnTickColorChanged(void);
	OLE_COLOR m_TickColor;
	void OnTickFontSizeChanged(void);
	SHORT m_TickFontSize;
	void OnTickOffsetChanged(void);
	SHORT m_TickOffset;
	void OnTickCountChanged(void);
	SHORT m_TickCount;
	void OnTickUnitsChanged(void);
	CString m_TickUnits;
};

