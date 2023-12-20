#pragma once

#include "TEdit.h"
#include "NumSpinCtrl.h"
#include "HMIDlgApi.h"

// CUserPage3 dialog

class CUserPage3 : public CPropertyPage
{
	DECLARE_DYNAMIC(CUserPage3)

public:
	CUserPage3();   // standard constructor
	virtual ~CUserPage3();
//
public:
	CFont* m_pfont;
	COLORREF m_clrText;
	COLORREF m_clrBack;
	CWnd* m_pWndParent;

	//double m_dbParam1;
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

	ALLSETTINGS* m_pSettings;
	//VISIONSETTINGS1 m_VisSettings;
	//MOTIONSETTINGS* m_pSettings;

// Dialog Data
	enum { IDD = IDD_USER_SETTINGS_PAGE3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnEnChangeParam();

};