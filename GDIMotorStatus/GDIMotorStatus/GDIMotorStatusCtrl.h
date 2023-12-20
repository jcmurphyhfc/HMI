#pragma once

// GDIMotorStatusCtrl.h : Declaration of the CGDIMotorStatusCtrl ActiveX Control class.

#define MAX_MOTORS         32
#define MAX_MOTORS_STATE   12

// CGDIStatusBoxCtrl : See GDIStatusBoxCtrl.cpp for implementation.
typedef struct tagSTATUSBOXPARAMS {
	CString  strText;
	COLORREF clrTextColor;
	short      MotorState;
	BOOL      WarningFE;
} MOTORSTATUSPARMS;

// CGDIMotorStatusCtrl : See GDIMotorStatusCtrl.cpp for implementation.

class CGDIMotorStatusCtrl : public COleControl
{
	DECLARE_DYNCREATE(CGDIMotorStatusCtrl)

// Constructor
public:
	CRect m_rcState[MAX_MOTORS];
	CRect m_rcNames[MAX_MOTORS];
	CGDIMotorStatusCtrl();
	SHORT m_nState;
	MOTORSTATUSPARMS m_StatusData[MAX_MOTORS];
	CBitmap m_NameFrame;
	CBitmap m_DisabledLED;
	CBitmap m_EnabledLED;
	CBitmap m_WarningLED;
	CBitmap m_FaultLED;

// Internal methods
public:
	void DrawTitle(CDC *pDC,const CRect& Rect);
	void DoGradientFill(CDC *pDC,const CRect& Rect);
	void PaintStatusRect(CDC* pDC,const CRect& Rect,COLORREF clrBK,COLORREF clrText,LPCTSTR lpText);
	void DrawMotorName(CDC* pDC,const CRect& rect);
	void DrawMotorStatus(CDC* pDC,const CRect& rect);

// Overrides
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();

// Implementation
protected:
	~CGDIMotorStatusCtrl();

	DECLARE_OLECREATE_EX(CGDIMotorStatusCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CGDIMotorStatusCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CGDIMotorStatusCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CGDIMotorStatusCtrl)		// Type name and misc status

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
		dispidGetMotorState = 18L,
		dispidUpdateMotorStatus = 17L,
		dispidSetMotorState = 16L,
		dispidMotorStateFontSize = 15,
		dispidMotorNameWidth = 14,
		dispidMotorSelect = 13,
		dispidMotorName = 12,
		dispidMotorTextColor = 11,
		dispidHasTitle = 10,
		dispidTotalMotors = 9,
		dispidMotorState = 8,
		dispidFontSize = 7,
		dispidstrTitle = 6,
		dispidTitleTextColor = 5,
		dispidTitleTextBackColor = 4,
		dispidHasClientBox = 3,
		dispidDoGradientFill = 2,
		dispidTitleFontSize = 1
	};
protected:
	void OnTitleFontSizeChanged(void);
	SHORT m_TitleFontSize;
	void OnDoGradientFillChanged(void);
	SHORT m_DoGradientFill;
	void OnHasClientBoxChanged(void);
	SHORT m_HasClientBox;
	void OnTitleTextBackColorChanged(void);
	OLE_COLOR m_TitleTextBackColor;
	void OnTitleTextColorChanged(void);
	OLE_COLOR m_TitleTextColor;
	void OnstrTitleChanged(void);
	CString m_strTitle;
	void OnFontSizeChanged(void);
	SHORT m_MotorFontSize;
	void OnMotorStateChanged(void);
	SHORT m_MotorState;
	void OnTotalMotorsChanged(void);
	SHORT m_TotalMotors;
	void OnHasTitleChanged(void);
	SHORT m_HasTitle;
	void OnMotorTextColorChanged(void);
	OLE_COLOR m_MotorTextColor;
	void OnMotorNameChanged(void);
	CString m_MotorName;
	void OnMotorSelectChanged(void);
	SHORT m_MotorSelect;
	void OnMotorNameWidthChanged(void);
	SHORT m_MotorNameWidth;
	void OnMotorStateFontSizeChanged(void);
	SHORT m_MotorStateFontSize;
	void SetMotorState(SHORT MotorNum, SHORT State);
	void UpdateMotorStatus(SHORT Repaint);
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
protected:
	SHORT GetMotorState(SHORT MotorNum);
};

