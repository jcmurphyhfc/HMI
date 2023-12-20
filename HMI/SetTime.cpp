// SetTime.cpp : implementation file
//

#include "stdafx.h"
#include "HMI.h"
#include "SetTime.h"

// CSetTime dialog

IMPLEMENT_DYNAMIC(CSetTime, CDialog)

CSetTime::CSetTime(CWnd* pParent /*=NULL*/)
	: CDialog(CSetTime::IDD, pParent)
	, m_nAmPm(0)
{

}

CSetTime::~CSetTime()
{
}

void CSetTime::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GDITEDITCTRL_HOURS, m_ctlHours);
	DDX_Control(pDX, IDC_GDITEDITCTRL_MINUTES, m_ctlMinutes);
	DDX_Control(pDX, IDC_GDITEDITCTRL_MINUTES2, m_ctlSeconds);
	DDX_Radio(pDX, IDC_RADIO1, m_nAmPm);

}


BEGIN_MESSAGE_MAP(CSetTime, CDialog)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CSetTime message handlers
BEGIN_EVENTSINK_MAP(CSetTime, CDialog)
	ON_EVENT(CSetTime, IDC_GDITEDITCTRL_HOURS, DISPID_CLICK, CSetTime::ClickGditeditctrlHours, VTS_NONE)
	ON_EVENT(CSetTime, IDC_GDITEDITCTRL_MINUTES, DISPID_CLICK, CSetTime::ClickGditeditctrlMinutes, VTS_NONE)
	ON_EVENT(CSetTime, IDC_GDITEDITCTRL_MINUTES2, DISPID_CLICK, CSetTime::ClickGditeditctrlSeconds, VTS_NONE)
END_EVENTSINK_MAP()


void CSetTime::ClickGditeditctrlHours()
{
	//SYSTEMTIME st,lt;
	//GetSystemTime(&st);
	//SetSystemTime(&st);
	//GetLocalTime(&lt);
	//SetLocalTime(&lt);
	//TRACE("%02d:%02d:%d \n",st.wHour,st.wMinute,st.wMilliseconds);
	//TRACE("%02d:%02d:%d \n",lt.wHour,lt.wMinute,lt.wSecond);
	UpdateData(1);
	TRACE("Hour %d \n",m_nAmPm);

	SYSTEMTIME lt;
	KEYPADDATA data;
	data.dbIncrement = 	1;
	data.dbMin = m_ctlHours.GetMinValue();
	data.dbMax = m_ctlHours.GetMaxValue();
	data.dbValue = m_ctlHours.GetValue();
	data.lpTitle = _T("Enter Hour");
	data.nDecimalPlaces = m_ctlHours.GetPrecision();
	data.bPassWord = false;
	bool bOk = GetNumDlg(&data);
	if (bOk) 
	{			
		GetLocalTime(&lt);
		lt.wHour = (WORD)data.dbValue;
		if (m_nAmPm==1)
		{
			if (lt.wHour < 12)
				lt.wHour += 12; 
		}
		SetLocalTime(&lt);
		TRACE("%02d:%02d:%d \n",lt.wHour,lt.wMinute,lt.wSecond);
	}

}

void CSetTime::ClickGditeditctrlMinutes()
{
	SYSTEMTIME lt;
	KEYPADDATA data;
	data.dbIncrement = 	1;
	data.dbMin = m_ctlMinutes.GetMinValue();
	data.dbMax = m_ctlMinutes.GetMaxValue();
	data.dbValue = m_ctlMinutes.GetValue();
	data.lpTitle = _T("Enter Minutes");
	data.nDecimalPlaces = m_ctlMinutes.GetPrecision();
	data.bPassWord = false;
	bool bOk = GetNumDlg(&data);
	if (bOk) 
	{			
		GetLocalTime(&lt);
		lt.wMinute = (WORD)data.dbValue;
		SetLocalTime(&lt);
		TRACE("%02d:%02d:%d \n",lt.wHour,lt.wMinute,lt.wSecond);
	}

}

void CSetTime::ClickGditeditctrlSeconds()
{
	//if (nHour > 12) nHour = nHour%12;
	//m_ctlHours.SetValue(nHour);
	//m_ctlMinutes.SetValue(nMinute);
	//m_ctlSeconds.SetValue(nSecond);

	SYSTEMTIME lt;
	KEYPADDATA data;
	data.dbIncrement = 	1;
	data.dbMin = m_ctlSeconds.GetMinValue();
	data.dbMax = m_ctlSeconds.GetMaxValue();
	data.dbValue = m_ctlSeconds.GetValue();
	data.lpTitle = _T("Enter Seconds");
	data.nDecimalPlaces = m_ctlSeconds.GetPrecision();
	data.bPassWord = false;
	bool bOk = GetNumDlg(&data);
	if (bOk) 
	{			
		GetLocalTime(&lt);
		lt.wSecond = (WORD)data.dbValue;
		SetLocalTime(&lt);
		TRACE("%02d:%02d:%d \n",lt.wHour,lt.wMinute,lt.wSecond);
	}


}


void CSetTime::OnTimer(UINT_PTR nIDEvent)
{
	CDialog::OnTimer(nIDEvent);

	CTime time;
    int nSecond;
	int nMinute;
    int nHour;

    time = CTime::GetCurrentTime ();
    nSecond = time.GetSecond ();
	nMinute = time.GetMinute ();
    nHour = time.GetHour ();

	// Return when clock has not changed
	if ((nSecond == m_nPrevSecond) && (nMinute == m_nPrevMinute) && (nHour == m_nPrevHour))
	{
		//TRACE("every 100 msec \n");
		SetTimer(1,100,NULL);  // Check again in 100 msec
		return;
	}

	// Dont check clock for another second
	//TRACE("every second\n");
	SetTimer(1,1010,NULL);

	// Save
	m_nPrevSecond = nSecond;
    m_nPrevMinute = nMinute;
    m_nPrevHour = nHour;

	if (nHour > 12) nHour = nHour%12;
	m_ctlHours.SetValue(nHour);
	m_ctlMinutes.SetValue(nMinute);
	m_ctlSeconds.SetValue(nSecond);

}


BOOL CSetTime::OnInitDialog()
{
	CDialog::OnInitDialog();

	CTime time;
    int nHour;
    time = CTime::GetCurrentTime ();
    nHour = time.GetHour ();

	SetTimer(1,250,NULL);
	m_nAmPm = 0;
	if (nHour >= 12)
	{
		m_nAmPm = 1;	
	}
	UpdateData(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
