#pragma once

// GDITeditCtrl.h : Declaration of the CGDITeditCtrl ActiveX Control class.


// CGDITeditCtrl : See GDITeditCtrl.cpp for implementation.
// CGDIIoStatusCtrl : See GDIIoStatusCtrl.cpp for implementation.
//#define MAX_IO_POINTS 48

// CGDIStatusBoxCtrl : See GDIStatusBoxCtrl.cpp for implementation.
//typedef struct tagSTATUSBOXPARAMS {
//	CString  strText;
//	COLORREF clrTextColor;
//	COLORREF clrBkColor;
//	BOOL	 bInvert;
//} IOSTATUSPARMS;

class CGDITeditCtrl : public COleControl
{
	DECLARE_DYNCREATE(CGDITeditCtrl)

// Constructor
public:
	CGDITeditCtrl();

// Overrides
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();

// Internal property
public:
	BOOL m_bSwapColors;
	BOOL m_bTimerRunning;
	SHORT m_nState;
	CRect m_status;

	//IOSTATUSPARMS m_StatusData[MAX_IO_POINTS];

// Internal methods
public:
	void DrawTitle(CDC *pDC,const CRect& Rect);
	void DoGradientFill(CDC *pDC,const CRect& Rect);
	void PaintStatusRect(CDC* pDC,const CRect& Rect,COLORREF clrBK,COLORREF clrText);
	void SwapColors();

// Implementation
protected:
	~CGDITeditCtrl();

	DECLARE_OLECREATE_EX(CGDITeditCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CGDITeditCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CGDITeditCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CGDITeditCtrl)		// Type name and misc status

// Message maps
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// Event maps
	DECLARE_EVENT_MAP()

	//double m_dbValue;
	//double m_dbIncrement;
	//CString m_strLabel;
	//CString m_strUnits;
	//double m_dbMin;
	//double m_dbMax;
	//int m_nWidth;
	//int m_nPrecision;
	//double* m_pdbValue;
	//int* m_pnValue;
	double m_dbValue;


// Dispatch and event IDs
public:
	enum {
		dispidEditEnable = 17,
		dispidHasTitle = 16,
		dispidUnits = 15,
		dispidPrecision = 14,
		dispidWidth = 13,
		dispidMaxValue = 12,
		dispidMinValue = 11,
		dispidSetValue = 10L,
		dispidGetValue = 9L,
		dispidTitleDoGradientFill = 8,
		dispidTextBackColor = 7,
		dispidTextColor = 6,
		dispidTextFontSize = 5,
		dispidTitleText = 4,
		dispidTitleBackColor = 3,
		dispidTitleTextColor = 2,
		dispidTitleFontSize = 1,
	};

	void OnTitleFontSizeChanged(void);
	SHORT m_TitleFontSize;
	void OnTitleTextColorChanged(void);
	OLE_COLOR m_TitleTextColor;
	void OnTitleBackColorChanged(void);
	OLE_COLOR m_TitleBackColor;
	void OnTitleTextChanged(void);
	CString m_TitleText;
protected:
	void OnTextFontSizeChanged(void);
	SHORT m_TextFontSize;
	void OnTextColorChanged(void);
	OLE_COLOR m_TextColor;
	void OnTextBackColorChanged(void);
	OLE_COLOR m_TextBackColor;
	void OnTitleDoGradientFillChanged(void);
	SHORT m_TitleDoGradientFill;
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
protected:
	DOUBLE GetValue(void);
	void SetValue(DOUBLE dbValue);
	void OnMinValueChanged(void);
	DOUBLE m_MinValue;
	void OnMaxValueChanged(void);
	DOUBLE m_MaxValue;
	void OnWidthChanged(void);
	SHORT m_Width;
	void OnPrecisionChanged(void);
	SHORT m_Precision;
	void OnUnitsChanged(void);
	CString m_Units;
	void OnHasTitleChanged(void);
	SHORT m_HasTitle;
	void OnEditEnableChanged(void);
	SHORT m_EditEnable;
};
