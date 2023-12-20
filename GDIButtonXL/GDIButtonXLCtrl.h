#pragma once

// GDIButtonXLCtrl.h : Declaration of the CGDIButtonXLCtrl ActiveX Control class.
#define FULL_LED_SELECTED  5

// CGDIButtonXLCtrl : See GDIButtonXLCtrl.cpp for implementation.

class CGDIButtonXLCtrl : public COleControl
{
	DECLARE_DYNCREATE(CGDIButtonXLCtrl)

// Constructor
public:
	CGDIButtonXLCtrl();

	CBitmap m_DownOff;
	CBitmap m_DownOn;
	CBitmap m_UpOff;
	CBitmap m_UpOn;
	CBitmap m_bitmapDownOff;
	CBitmap m_bitmapDownOn;
	CBitmap m_bitmapUpOff;
	CBitmap m_bitmapUpOn;
	//CFont m_fontMed;
	//CFont* m_pfont;
	bool m_bBitmapsLoaded;
	bool m_bGenerateBitmap;
	bool m_bBitmapsGenerated;
	bool m_bButtonDown;
	bool m_bButtonDownMessage;
	BOOL m_bLightOn;

	//CString m_strText1;
	//CString m_strText2;
	//CString m_strButtonText1;
	//CString m_strButtonText2;
	//COLORREF m_clrText;
	CString m_strOldButtonText1;
	CString m_strOldButtonText2;

	CString m_strLabelText1;
	CString m_strLabelText2;
	CRect m_rectCurrent;


	//enum { // flags
	//	LightOnly = 0x0001,	
	//	RedLight = 0x0002,	
	//	GreenLight = 0x0004,
	//};

public:
	void GenBitMaps(CDC* pDC,const CRect& rect);
	void DrawLampUp(CDC* pDC,const CRect& rect);
	void DrawLampDown(CDC* pDC,const CRect& rect);
	void DoDrawText(CDC* pDC,const CRect& rect);
	void DoDrawButtonText(CDC* pDC,LPRECT lpRect);
	void SetLightOn(BOOL bLightOn=TRUE);
	//void SetFont(CFont* pFont, BOOL bRedraw = TRUE);
	void SetButtonText(LPCTSTR str1,LPCTSTR str2);
	void ResetSetButtonText();
	void LoadBitMaps(UINT nIDUpOff,UINT nIDUpOn,UINT nIDDownOff,UINT nIDDownOn);


// Overrides
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();

// Implementation
protected:
	~CGDIButtonXLCtrl();

	DECLARE_OLECREATE_EX(CGDIButtonXLCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CGDIButtonXLCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CGDIButtonXLCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CGDIButtonXLCtrl)		// Type name and misc status

// Message maps
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	afx_msg void OnText1Changed();
	afx_msg void OnText2Changed();

	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// Event maps
	DECLARE_EVENT_MAP()


// Dispatch and event IDs
public:
	enum {
		dispidstrTitle2 = 9,
		dispidstrTitle1 = 8,
		dispidTextOffset2 = 7,
		dispidTextOffset1 = 6,
		dispidLightOn = 5,
		dispidTextColor = 4,
		dispidFontSize = 3,
		dispidBitMapSelect = 2,
		dispidSetLight = 1L
	};


//	afx_msg void OnPaint();
//	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
//	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
//	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
//protected:
//	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
//public:
//	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

protected:
	void SetLight(VARIANT_BOOL Light);
	void OnBitMapSelectChanged(void);
	LONG m_BitMapSelect;
	void OnFontSizeChanged(void);
	LONG m_FontSize;
	void OnTextColorChanged(void);
	OLE_COLOR m_TextColor;
	void OnLightOnChanged(void);
	VARIANT_BOOL m_LightOn;
	void OnTextOffset1Changed(void);
	LONG m_TextOffset1;
	void OnTextOffset2Changed(void);
	LONG m_TextOffset2;
};

