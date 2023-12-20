#pragma once

// GDILedLightsCtrl.h : Declaration of the CGDILedLightsCtrl ActiveX Control class.


// CGDILedLightsCtrl : See GDILedLightsCtrl.cpp for implementation.

class CGDILedLightsCtrl : public COleControl
{
	DECLARE_DYNCREATE(CGDILedLightsCtrl)

// Constructor
public:
	CGDILedLightsCtrl();

	CBitmap m_RedLedOn;
	CBitmap m_RedLedOff;
	CBitmap m_GreenLedOn;
	CBitmap m_GreenLedOff;
	CBitmap m_BlueLedOn;
	CBitmap m_BlueLedOff;
	CBitmap m_AmberLedOn;
	CBitmap m_AmberLedOff;

// Members
public:
	void DrawLED(CDC* pDC,const CRect& rect);

// Overrides
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();

// Implementation
protected:
	~CGDILedLightsCtrl();

	DECLARE_OLECREATE_EX(CGDILedLightsCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CGDILedLightsCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CGDILedLightsCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CGDILedLightsCtrl)		// Type name and misc status

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
		dispidIoStatusWord = 3,
		dispidTotalIoPoints = 2,
		dispidLedColorSelect = 1
	};
protected:
	void OnLedColorSelectChanged(void);
	SHORT m_LedColorSelect;
	void OnTotalIoPointsChanged(void);
	SHORT m_TotalIoPoints;
	void OnIoStatusWordChanged(void);
	LONG m_IoStatusWord;
};

