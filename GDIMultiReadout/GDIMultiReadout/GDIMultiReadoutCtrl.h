#pragma once

#define TOTAL_PANES 6

// GDIMultiReadoutCtrl.h : Declaration of the CGDIMultiReadoutCtrl ActiveX Control class.
// CGDIStatusBoxCtrl : See GDIStatusBoxCtrl.cpp for implementation.
typedef struct tagMULTIREADOUT {
	BOOL     bState;
	BOOL	 bInvert;
} IOSTATUSPARMS;


// CGDIMultiReadoutCtrl : See GDIMultiReadoutCtrl.cpp for implementation.

class CGDIMultiReadoutCtrl : public COleControl
{
	DECLARE_DYNCREATE(CGDIMultiReadoutCtrl)

// Constructor
public:
	CGDIMultiReadoutCtrl();

// Internal property
public:
	CRect m_rectTitle[TOTAL_PANES];
	CRect m_rectStatus[TOTAL_PANES];
	CRect m_status;
// Internal methods
public:
    void PaintStatusRect(CDC* pDC,const CRect& Rect,COLORREF clrBK,COLORREF clrText,int TextFontSize,int Width,int Precision,double dbValue);
	void DrawTitle(CDC *pDC,const CRect& Rect,LPCTSTR lpsz);
	void DoGradientFill(CDC *pDC,const CRect& Rect);

// Overrides
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();

// Implementation
protected:
	~CGDIMultiReadoutCtrl();

	DECLARE_OLECREATE_EX(CGDIMultiReadoutCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CGDIMultiReadoutCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CGDIMultiReadoutCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CGDIMultiReadoutCtrl)		// Type name and misc status

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
		dispidTitleHeight = 47,
		dispidPrecision5 = 46,
		dispidPrecision4 = 45,
		dispidPrecision3 = 44,
		dispidPrecision2 = 43,
		dispidPrecision1 = 42,
		dispidPrecision0 = 41,
		dispidWidth5 = 40,
		dispidWidth4 = 39,
		dispidWidth3 = 38,
		dispidWidth2 = 37,
		dispidWidth1 = 36,
		dispidWidth0 = 35,
		dispidTextFontSize5 = 34,
		dispidTextFontSize4 = 33,
		dispidTextFontSize3 = 32,
		dispidTextFontSize2 = 31,
		dispidTextFontSize1 = 30,
		dispidTextFontSize0 = 29,
		dispiddbValue5 = 28,
		dispiddbValue4 = 27,
		dispiddbValue3 = 26,
		dispiddbValue2 = 25,
		dispiddbValue1 = 24,
		dispiddbValue0 = 23,
		dispidTitleText6 = 22,
		dispidTitleText5 = 21,
		dispidTitleText4 = 20,
		dispidTitleText3 = 19,
		dispidTitleText2 = 18,
		dispidTitleText1 = 17,
		dispidTitleText0 = 16,
		dispidHasTitle = 15,
		dispidTitleDoGradientFill = 14,
		dispidTitleBackColor = 13,
		dispidTitleTextColor = 12,
		dispidTitleFontSize = 11,
		dispidTextBackColor = 10,
		dispidTextColor = 9,
		dispidMultiFunc1 = 8L,
		dispidMultiFunc0 = 7L,
		dispidUpdateReadouts = 6L,
		dispidSetTotalPanes = 5L,
		dispidGetPaneNum = 4L,
		dispidSetPaneNum = 3L,
		dispidGetValue = 2L,
		dispidSetValue = 1L
	};
protected:
	void SetValue(DOUBLE Value);
	DOUBLE GetValue(void);
	void SetPaneNum(DOUBLE PaneNum);
	DOUBLE GetPaneNum(void);
	void SetTotalPanes(SHORT TotalPanes);
	void UpdateReadouts(void);
	SHORT MultiFunc0(SHORT Param);
	DOUBLE MultiFunc1(DOUBLE Param);
	void OnTextColorChanged(void);
	OLE_COLOR m_TextColor;
	void OnTextBackColorChanged(void);
	OLE_COLOR m_TextBackColor;
	void OnTitleFontSizeChanged(void);
	SHORT m_TitleFontSize;
	void OnTitleTextColorChanged(void);
	OLE_COLOR m_TitleTextColor;
	void OnTitleBackColorChanged(void);
	OLE_COLOR m_TitleBackColor;
	void OnTitleDoGradientFillChanged(void);
	SHORT m_TitleDoGradientFill;
	void OnHasTitleChanged(void);
	SHORT m_HasTitle;
	void OnTitleText0Changed(void);
	CString m_TitleText0;
	void OnTitleText1Changed(void);
	CString m_TitleText1;
	void OnTitleText2Changed(void);
	CString m_TitleText2;
	void OnTitleText3Changed(void);
	CString m_TitleText3;
	void OnTitleText4Changed(void);
	CString m_TitleText4;
	void OnTitleText5Changed(void);
	CString m_TitleText5;
	void OnTitleText6Changed(void);
	CString m_TitleText6;
	void OndbValue0Changed(void);
	void OndbValue1Changed(void);
	void OndbValue2Changed(void);
	void OndbValue3Changed(void);
	void OndbValue4Changed(void);
	void OndbValue5Changed(void);
	DOUBLE m_dbValue0;
	DOUBLE m_dbValue1;
	DOUBLE m_dbValue2;
	DOUBLE m_dbValue3;
	DOUBLE m_dbValue4;
	DOUBLE m_dbValue5;
	void OnTextFontSize0Changed(void);
	void OnTextFontSize1Changed(void);
	void OnTextFontSize2Changed(void);
	void OnTextFontSize3Changed(void);
	void OnTextFontSize4Changed(void);
	void OnTextFontSize5Changed(void);
	SHORT m_TextFontSize0;
	SHORT m_TextFontSize1;
	SHORT m_TextFontSize2;
	SHORT m_TextFontSize3;
	SHORT m_TextFontSize4;
	SHORT m_TextFontSize5;
	void OnWidthChanged0(void);
	void OnWidthChanged1(void);
	void OnWidthChanged2(void);
	void OnWidthChanged3(void);
	void OnWidthChanged4(void);
	void OnWidthChanged5(void);
	void OnWidthChanged6(void);
	SHORT m_Width0;
	SHORT m_Width1;
	SHORT m_Width2;
	SHORT m_Width3;
	SHORT m_Width4;
	SHORT m_Width5;
	void OnPrecision0Changed(void);
	SHORT m_Precision0;
	void OnPrecision1Changed(void);
	SHORT m_Precision1;
	void OnPrecision2Changed(void);
	SHORT m_Precision2;
	void OnPrecision3Changed(void);
	SHORT m_Precision3;
	void OnPrecision4Changed(void);
	SHORT m_Precision4;
	void OnPrecision5Changed(void);
	SHORT m_Precision5;
	void OnTitleHeightChanged(void);
	SHORT m_TitleHeight;
};

