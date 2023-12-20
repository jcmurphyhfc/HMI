#pragma once

#include "TEdit.h"
#include "NumSpinCtrl.h"
#include "HMIDlgApi.h"

// CAlignLUT dialog

class CAlignLUT : public CPropertyPage
{
	DECLARE_DYNAMIC(CAlignLUT)

public:
	CAlignLUT();
	virtual ~CAlignLUT();

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
	CNumSpinCtrl m_ctlSpinParam1;
	CNumSpinCtrl m_ctlSpinParam2;
	CNumSpinCtrl m_ctlSpinParam3;
	CNumSpinCtrl m_ctlSpinParam4;
	CNumSpinCtrl m_ctlSpinParam5;
	CNumSpinCtrl m_ctlSpinParam6;
	CNumSpinCtrl m_ctlSpinParam7;
	CNumSpinCtrl m_ctlSpinParam8;
	CNumSpinCtrl m_ctlSpinParam9;

	VISIONSETTINGS3 m_VisSettings;


// Dialog Data
	enum { IDD = IDD_VISION_SETTINGS_PAGE3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnEnChangeParam();
	afx_msg void OnBnClickedHelp();
};
