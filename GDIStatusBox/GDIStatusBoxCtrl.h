#pragma once

// GDIStatusBoxCtrl.h : Declaration of the CGDIStatusBoxCtrl ActiveX Control class.

#define MAX_STATUS_STATES 20

// CGDIStatusBoxCtrl : See GDIStatusBoxCtrl.cpp for implementation.
typedef struct tagSTATUSBOXPARAMS {
	CString  strText;
	COLORREF clrTextColor;
	COLORREF clrBkColor;
	BOOL	 bBlink;
} STATUSBOXPARMS;

class CGDIStatusBoxCtrl : public COleControl
{
	DECLARE_DYNCREATE(CGDIStatusBoxCtrl)

// Constructor
public:
	CGDIStatusBoxCtrl();

// Internal property
public:
	BOOL m_bBlinkOn;
	BOOL m_bTimerRunning;
	SHORT m_nState;
	STATUSBOXPARMS m_StatusData[MAX_STATUS_STATES];
	//CBitmap m_bmpFrame;


// Internal methods
public:
	void DrawTitle(CDC *pDC,const CRect& Rect);
	void DoGradientFill(CDC *pDC,const CRect& Rect);
	void PaintStatusRect(CDC* pDC,const CRect& Rect,COLORREF clrBK,COLORREF clrText,LPCTSTR lpText);
// Overrides
public:

	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();

// Implementation
protected:
	~CGDIStatusBoxCtrl();

	DECLARE_OLECREATE_EX(CGDIStatusBoxCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CGDIStatusBoxCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CGDIStatusBoxCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CGDIStatusBoxCtrl)		// Type name and misc status

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
		dispidStatusBlinkOffTime = 14,
		dispidStatusBlinkOnTime = 13,
		dispidTitleTextBackColor = 12,
		dispidState = 11,
		dispidbBlink = 10,
		dispidcltBkColor = 9,
		dispidclrTextColor = 8, 
		dispidnFontSize = 7,
		dispidstrText = 6,
		dispidstrTitle = 5,
		dispidbDoGradientFill = 4,
		dispidclrTitleTextColor = 3,
		dispidnTitleFontSize = 2,
		dispidbHasClientBox = 1,
	};
protected:
	void OnnFontSizeChanged(void);
	SHORT m_nFontSize;
	void OnstrTitleChanged(void);
	CString m_strTitle;
	void OnbHasClientBoxChanged(void);
	SHORT m_bHasClientBox;
	void OnstrTextChanged(void);
	CString m_strText;
	void OnclrTextColorChanged(void);
	OLE_COLOR m_clrTextColor;
	void OncltBkColorChanged(void);
	OLE_COLOR m_cltBkColor;
	void OnbBlinkChanged(void);
	SHORT m_bBlink;
	SHORT GetState(void);
	void SetState(SHORT newVal);
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
protected:
	void OnnTitleFontSizeChanged(void);
	SHORT m_nTitleFontSize;
	void OnclrTitleTextColorChanged(void);
	OLE_COLOR m_clrTitleTextColor;
	void OnbDoGradientFillChanged(void);
	SHORT m_bDoGradientFill;
	void OnTitleTextBackColorChanged(void);
	OLE_COLOR m_TitleTextBackColor;
	void OnStatusBlinkOnTimeChanged(void);
	ULONG m_StatusBlinkOnTime;
	void OnStatusBlinkOffTimeChanged(void);
	ULONG m_StatusBlinkOffTime;
};

