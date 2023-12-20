#pragma once

#include "TEdit.h"
#include "NumSpinCtrl.h"
#include "HMIDlgApi.h"


// CVisionSplit dialog

class CVisionSplit : public CPropertyPage
{
	DECLARE_DYNAMIC(CVisionSplit)

public:
	CVisionSplit();
	virtual ~CVisionSplit();
	//
public:
	CFont* m_pfont;
	COLORREF m_clrText;
	COLORREF m_clrBack;
	CWnd* m_pWndParent;

	CTEdit m_ctlParam1;
	CTEdit m_ctlParam2;
	CTEdit m_ctlParam3;
	CTEdit m_ctlParam4;
	CTEdit m_ctlParam5;

	CTEdit m_ctlParam6;
	CTEdit m_ctlParam7;
	CTEdit m_ctlParam8;
	CTEdit m_ctlParam9;
	CTEdit m_ctlParam10;

	CTEdit m_ctlParam11;
	CTEdit m_ctlParam12;
	CTEdit m_ctlParam13;

	CTEdit m_ctlParam14;
	CTEdit m_ctlParam15;
	CTEdit m_ctlParam16;
	CTEdit m_ctlParam17;
	CTEdit m_ctlParam18;
	CTEdit m_ctlParam19;
	CTEdit m_ctlParam20;
	CTEdit m_ctlParam21;
	CTEdit m_ctlParam22;
	CTEdit m_ctlParam23;
	CTEdit m_ctlParam24;
	CTEdit m_ctlParam25;

	CNumSpinCtrl m_ctlSpinParam1;
	CNumSpinCtrl m_ctlSpinParam2;
	CNumSpinCtrl m_ctlSpinParam3;
	CNumSpinCtrl m_ctlSpinParam4;
	CNumSpinCtrl m_ctlSpinParam5;

	CNumSpinCtrl m_ctlSpinParam6;
	CNumSpinCtrl m_ctlSpinParam7;
	CNumSpinCtrl m_ctlSpinParam8;
	CNumSpinCtrl m_ctlSpinParam9;
	CNumSpinCtrl m_ctlSpinParam10;

	CNumSpinCtrl m_ctlSpinParam11;
	CNumSpinCtrl m_ctlSpinParam12;
	CNumSpinCtrl m_ctlSpinParam13;

	CNumSpinCtrl m_ctlSpinParam14;
	CNumSpinCtrl m_ctlSpinParam15;
	CNumSpinCtrl m_ctlSpinParam16;
	CNumSpinCtrl m_ctlSpinParam17;
	CNumSpinCtrl m_ctlSpinParam18;
	CNumSpinCtrl m_ctlSpinParam19;
	CNumSpinCtrl m_ctlSpinParam20;
	CNumSpinCtrl m_ctlSpinParam21;
	CNumSpinCtrl m_ctlSpinParam22;
	CNumSpinCtrl m_ctlSpinParam23;
	CNumSpinCtrl m_ctlSpinParam24;
	CNumSpinCtrl m_ctlSpinParam25;

	VISIONSETTINGS2 m_VisSettings;
	MOTIONSETTINGS* m_pSettings;

// Dialog Data
	enum { IDD = IDD_VISION_SETTINGS_PAGE2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnEnChangeParam();
};
