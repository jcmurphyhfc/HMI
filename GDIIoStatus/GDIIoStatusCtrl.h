#pragma once

// GDIIoStatusCtrl.h : Declaration of the CGDIIoStatusCtrl ActiveX Control class.


// CGDIIoStatusCtrl : See GDIIoStatusCtrl.cpp for implementation.
#define MAX_IO_POINTS 48

// CGDIStatusBoxCtrl : See GDIStatusBoxCtrl.cpp for implementation.
typedef struct tagSTATUSBOXPARAMS {
	CString  strText;
	//COLORREF clrTextColor;
	//COLORREF clrBkColor;
	BOOL     bState;
	BOOL	 bInvert;
} IOSTATUSPARMS;

class CGDIIoStatusCtrl : public COleControl
{
	DECLARE_DYNCREATE(CGDIIoStatusCtrl)

// Constructor
public:
	CGDIIoStatusCtrl();

// Internal property
public:
	BOOL m_bTimerRunning;
	SHORT m_nState;
	IOSTATUSPARMS m_StatusData[MAX_IO_POINTS];
	CBitmap m_RedLedOn;
	CBitmap m_RedLedOff;
	CBitmap m_GreenLedOn;
	CBitmap m_GreenLedOff;
	CBitmap m_BlueLedOn;
	CBitmap m_BlueLedOff;
	CBitmap m_AmberLedOn;
	CBitmap m_AmberLedOff;
	//CBitmap* m_pLedOn;
	//CBitmap* m_pLedOff;
	CRect m_rcState[MAX_IO_POINTS];
	CRect m_rcNames[MAX_IO_POINTS];
	BOOL  m_DrawUp[MAX_IO_POINTS];

// Internal methods
public:
	void DrawTitle(CDC *pDC,const CRect& Rect);
	void DoGradientFill(CDC *pDC,const CRect& Rect);
	void DrawLED(CDC* pDC,const CRect& rect);
	void DrawName(CDC* pDC,const CRect& rect);


// Overrides
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();

// Implementation
protected:
	~CGDIIoStatusCtrl();

	DECLARE_OLECREATE_EX(CGDIIoStatusCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CGDIIoStatusCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CGDIIoStatusCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CGDIIoStatusCtrl)		// Type name and misc status

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
		dispidIoStatusWordInvert = 18,
		eventidIoClicked = 1L,
		dispidIoForceEnable = 17,
		dispidIoStatusWord = 16,
		dispidLedColorSelect = 15,
		dispidIoNameWidth = 14,
		dispidTotalIoPoints = 13,
		dispidTitleTextBackColor = 12,
		dispidBit = 11,
		dispidbInvert = 10,
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
	void OnInvertChanged(void);
	SHORT m_bInvert;
	SHORT GetBit(void);
	void SetBit(SHORT newVal);
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
	void OnTotalIoPointsChanged(void);
	SHORT m_TotalIoPoints;
	void OnIoNameWidthChanged(void);
	SHORT m_IoNameWidth;
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
protected:
	void OnLedColorSelectChanged(void);
	SHORT m_LedColorSelect;
	void OnIoStatusWordChanged(void);
	ULONG m_IoStatusWord;
	void OnIoForceEnableChanged(void);
	SHORT m_IoForceEnable;

	void IoClicked(SHORT IoClickedNum)
	{
		FireEvent(eventidIoClicked, EVENT_PARAM(VTS_I2), IoClickedNum);
	}
	void OnIoStatusWordInvertChanged(void);
	ULONG m_IoStatusWordInvert;
};

