#pragma once

// GDIStatusBoxExCtrl.h : Declaration of the CGDIStatusBoxExCtrl ActiveX Control class.
#define MAX_STATUS_STATES 40

// CGDIStatusBoxExCtrl : See GDIStatusBoxCtrl.cpp for implementation.
typedef struct tagSTATUSBOXPARAMS {
	CString  strText;
	COLORREF clrTextColor;
	COLORREF clrBkColor;
	BOOL	 bBlink;
} STATUSBOXPARMS;


// CGDIStatusBoxExCtrl : See GDIStatusBoxExCtrl.cpp for implementation.

class CGDIStatusBoxExCtrl : public COleControl
{
	DECLARE_DYNCREATE(CGDIStatusBoxExCtrl)

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

// Constructor
public:
	CGDIStatusBoxExCtrl();

// Overrides
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	virtual DWORD GetControlFlags();

// Internal 
protected:
	SHORT m_bBlink;
	OLE_COLOR m_cltBkColor;
	OLE_COLOR m_clrTextColor;
	CString m_strText;
	SHORT m_bHasClientBox;
	SHORT m_nFontSize;
	CString m_strTitle;
	SHORT m_nTitleFontSize;
	OLE_COLOR m_clrTitleTextColor;
	SHORT m_bDoGradientFill;
	OLE_COLOR m_TitleTextBackColor;
	ULONG m_StatusBlinkOnTime;
	ULONG m_StatusBlinkOffTime;
	void OnnFontSizeChanged(void);
	void OnstrTitleChanged(void);
	void OnbHasClientBoxChanged(void);
	void OnstrTextChanged(void);
	void OnclrTextColorChanged(void);
	void OncltBkColorChanged(void);
	void OnbBlinkChanged(void);
	SHORT GetState(void);
	void SetState(SHORT newVal);
	void OnnTitleFontSizeChanged(void);
	void OnclrTitleTextColorChanged(void);
	void OnbDoGradientFillChanged(void);
	void OnTitleTextBackColorChanged(void);
	void OnStatusBlinkOnTimeChanged(void);
	void OnStatusBlinkOffTimeChanged(void);
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);


// Implementation
protected:
	~CGDIStatusBoxExCtrl();

	DECLARE_OLECREATE_EX(CGDIStatusBoxExCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CGDIStatusBoxExCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CGDIStatusBoxExCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CGDIStatusBoxExCtrl)		// Type name and misc status

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
};

