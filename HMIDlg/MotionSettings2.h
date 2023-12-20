#pragma once
#include "TEdit.h"
#include "NumSpinCtrl.h"
#include "HMIDlgApi.h"

// CMotionSettings1 dialog

class CMotionSettings2 : public CPropertyPage
{
	DECLARE_DYNAMIC(CMotionSettings2)

public:
	CMotionSettings2();
	virtual ~CMotionSettings2();

	CFont* m_pfont;
	COLORREF m_clrText;
	COLORREF m_clrBack;
	CWnd* m_pWndParent;
	CWnd* m_pComWnd;
	double m_dbDrumOffset;

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

	MOTIONSETTINGS* m_pSettings;

// Dialog Data
	enum { IDD = IDD_MOTION_SETTINGS_PAGE2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnEnChangeParam();
	afx_msg void OnEnChangeParam1();
	afx_msg void OnBnClickedAlignHomeOffset();
	afx_msg void OnBnClickedAlignNegLim();
	afx_msg void OnBnClickedAlignPosLim();
	afx_msg void OnBnClickedAlignStartPos();
	afx_msg void OnBnClickedKnifeOffset();
};
