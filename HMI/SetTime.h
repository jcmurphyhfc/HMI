#pragma once
#include "slice_count.h"


// CSetTime dialog

class CSetTime : public CDialog
{
	DECLARE_DYNAMIC(CSetTime)

public:
	CSetTime(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSetTime();
	int m_nPrevSecond;
	long m_nPrevMinute;
	long m_nPrevHour;

// Dialog Data
	enum { IDD = IDD_DIALOG_SETTIME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CGDITedit m_ctlHours;
	CGDITedit m_ctlMinutes;
	DECLARE_EVENTSINK_MAP()
	void ClickGditeditctrlHours();
	void ClickGditeditctrlMinutes();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL OnInitDialog();
	CGDITedit m_ctlSeconds;
	void ClickGditeditctrlSeconds();
	int m_nAmPm;
};
