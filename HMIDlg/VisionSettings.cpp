// VisionSettings.cpp : implementation file
//

#include "stdafx.h"
#include "HMIDlg.h"
#include "VisionSettings.h"

#define PARAM1_MIN             1
#define PARAM1_MAX           255
#define PARAM1_PRECISION       0

#define PARAM2_MIN             1  
#define PARAM2_MAX        200000
#define PARAM2_PRECISION       0

#define PARAM3_MIN             1
#define PARAM3_MAX          1024
#define PARAM3_PRECISION       0

#define PARAM4_MIN             1
#define PARAM4_MAX           512
#define PARAM4_PRECISION       0

#define PARAM5_MIN            0
#define PARAM5_MAX         20.0
#define PARAM5_PRECISION      0

#define PARAM6_MIN            0
#define PARAM6_MAX            1
#define PARAM6_PRECISION      0

#define PARAM7_MIN              0.0
#define PARAM7_MAX              500000.0
#define PARAM7_PRECISION        0

#define PARAM8_MIN              0
#define PARAM8_MAX              512
#define PARAM8_PRECISION        0

#define PARAM9_MIN              0
#define PARAM9_MAX              1024
#define PARAM9_PRECISION        0

#define PARAM10_MIN              1
#define PARAM10_MAX            200
#define PARAM10_PRECISION        0

#define PARAM11_MIN              0
#define PARAM11_MAX              1
#define PARAM11_PRECISION        0

#define PARAM12_MIN              0
#define PARAM12_MAX            100
#define PARAM12_PRECISION        0

#define PARAM13_MIN              0
#define PARAM13_MAX        1000000
#define PARAM13_PRECISION        0

#define PARAM14_MIN              0
#define PARAM14_MAX        1000000
#define PARAM14_PRECISION        0

//#define PARAM15_MIN              0
//#define PARAM15_MAX             10
//#define PARAM15_PRECISION        0
//#define PARAM15_PVARIABLE       87
#define PARAM15_MIN              0.5
#define PARAM15_MAX               10
#define PARAM15_PRECISION          2
//#define PARAM15_PVARIABLE       87


#define PARAM16_MIN              0
#define PARAM16_MAX             10
#define PARAM16_PRECISION        0
#define PARAM16_PVARIABLE       88

// CVisionSettings dialog

IMPLEMENT_DYNAMIC(CVisionSettings, CPropertyPage)

CVisionSettings::CVisionSettings()
	: CPropertyPage(CVisionSettings::IDD)
{
    m_psp.dwFlags |= PSP_USEHICON;
    m_psp.dwFlags |= PSP_USETITLE;

	HICON hIconTab = AfxGetApp()->LoadIcon (IDI_TOP);
    m_psp.hIcon = hIconTab;
	m_pWndParent = NULL;

}

CVisionSettings::~CVisionSettings()
{
}

void CVisionSettings::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_PARAM1, m_ctlParam1);
	DDX_Control(pDX, IDC_SPIN_PARAM1, m_ctlSpinParam1);
	DDX_Text(pDX, IDC_PARAM1, m_VisSettings.Threshold);
	DDV_MinMaxDouble(pDX, m_VisSettings.Threshold, PARAM1_MIN, PARAM1_MAX);

	DDX_Control(pDX, IDC_PARAM2, m_ctlParam2);
	DDX_Control(pDX, IDC_SPIN_PARAM2, m_ctlSpinParam2);
	DDX_Text(pDX, IDC_PARAM2, m_VisSettings.MinBaconSize);
	DDV_MinMaxDouble(pDX, m_VisSettings.MinBaconSize, PARAM2_MIN, PARAM2_MAX);

	DDX_Control(pDX, IDC_PARAM3, m_ctlParam3);
	DDX_Control(pDX, IDC_SPIN_PARAM3, m_ctlSpinParam3);
	DDX_Text(pDX, IDC_PARAM3, m_VisSettings.MinBaconWidth);
	DDV_MinMaxDouble(pDX, m_VisSettings.MinBaconWidth, PARAM3_MIN, PARAM3_MAX);

	DDX_Control(pDX, IDC_PARAM4, m_ctlParam4);
	DDX_Control(pDX, IDC_SPIN_PARAM4, m_ctlSpinParam4);
	DDX_Text(pDX, IDC_PARAM4, m_VisSettings.MinBaconHeight);
	DDV_MinMaxDouble(pDX, m_VisSettings.MinBaconHeight, PARAM4_MIN, PARAM4_MAX);

	DDX_Control(pDX, IDC_PARAM5, m_ctlParam5);
	DDX_Control(pDX, IDC_SPIN_PARAM5, m_ctlSpinParam5);
	DDX_Text(pDX, IDC_PARAM5, m_VisSettings.MinBlobRadius);
	DDV_MinMaxDouble(pDX, m_VisSettings.MinBlobRadius, PARAM5_MIN, PARAM5_MAX);

	DDX_Control(pDX, IDC_PARAM6, m_ctlParam6);
	DDX_Control(pDX, IDC_SPIN_PARAM6, m_ctlSpinParam6);
	DDX_Text(pDX, IDC_PARAM6, m_VisSettings.Trigger);
	DDV_MinMaxDouble(pDX, m_VisSettings.Trigger, PARAM6_MIN, PARAM6_MAX);

	DDX_Control(pDX, IDC_PARAM7, m_ctlParam7);
	DDX_Control(pDX, IDC_SPIN_PARAM7, m_ctlSpinParam7);
	DDX_Text(pDX, IDC_PARAM7, m_VisSettings.MinBaconRejectSize);
	DDV_MinMaxDouble(pDX, m_VisSettings.MinBaconRejectSize, PARAM7_MIN, PARAM7_MAX);

	DDX_Control(pDX, IDC_PARAM8, m_ctlParam8);
	DDX_Control(pDX, IDC_SPIN_PARAM8, m_ctlSpinParam8);
	DDX_Text(pDX, IDC_PARAM8, m_VisSettings.MinBaconRejectHeight);
	DDV_MinMaxDouble(pDX, m_VisSettings.MinBaconRejectHeight, PARAM8_MIN, PARAM8_MAX);

	DDX_Control(pDX, IDC_PARAM9, m_ctlParam9);
	DDX_Control(pDX, IDC_SPIN_PARAM9, m_ctlSpinParam9);
	DDX_Text(pDX, IDC_PARAM9, m_VisSettings.MinBaconRejectWidth);
	DDV_MinMaxDouble(pDX, m_VisSettings.MinBaconRejectWidth, PARAM9_MIN, PARAM9_MAX);

	DDX_Control(pDX, IDC_PARAM10, m_ctlParam10);
	DDX_Control(pDX, IDC_SPIN_PARAM10, m_ctlSpinParam10);
	DDX_Text(pDX, IDC_PARAM10, m_VisSettings.Exposure_uS);
	DDV_MinMaxDouble(pDX, m_VisSettings.Exposure_uS, PARAM10_MIN, PARAM10_MAX);

	DDX_Control(pDX, IDC_PARAM11, m_ctlParam11);
	DDX_Control(pDX, IDC_SPIN_PARAM11, m_ctlSpinParam11);
	DDX_Text(pDX, IDC_PARAM11, m_VisSettings.SystemEnable);
	DDV_MinMaxDouble(pDX, m_VisSettings.SystemEnable, PARAM11_MIN, PARAM11_MAX);

	DDX_Control(pDX, IDC_PARAM12, m_ctlParam12);
	DDX_Control(pDX, IDC_SPIN_PARAM12, m_ctlSpinParam12);
	DDX_Text(pDX, IDC_PARAM12, m_VisSettings.RejectSuppressionCount);
	DDV_MinMaxDouble(pDX, m_VisSettings.RejectSuppressionCount, PARAM12_MIN, PARAM12_MAX);

	DDX_Control(pDX, IDC_PARAM13, m_ctlParam13);
	DDX_Control(pDX, IDC_SPIN_PARAM13, m_ctlSpinParam13);
	DDX_Text(pDX, IDC_PARAM13, m_VisSettings.RejectDuration);
	DDV_MinMaxDouble(pDX, m_VisSettings.RejectDuration, PARAM13_MIN, PARAM13_MAX);

	DDX_Control(pDX, IDC_PARAM14, m_ctlParam14);
	DDX_Control(pDX, IDC_SPIN_PARAM14, m_ctlSpinParam14);
	DDX_Text(pDX, IDC_PARAM14, m_VisSettings.RejectDelay);
	DDV_MinMaxDouble(pDX, m_VisSettings.RejectDelay, PARAM14_MIN, PARAM14_MAX);

	DDX_Control(pDX, IDC_PARAM15, m_ctlParam15);
	DDX_Control(pDX, IDC_SPIN_PARAM15, m_ctlSpinParam15);
	//DDX_Text(pDX, IDC_PARAM15, m_pSettings->dbPvars[PARAM15_PVARIABLE]);
	//DDV_MinMaxDouble(pDX, m_pSettings->dbPvars[PARAM15_PVARIABLE], PARAM15_MIN, PARAM15_MAX);
	DDX_Text(pDX, IDC_PARAM15, m_VisSettings.dbLineRateScaleFactor);
	DDV_MinMaxDouble(pDX, m_VisSettings.dbLineRateScaleFactor, PARAM15_MIN, PARAM15_MAX);

	//DDX_Control(pDX, IDC_PARAM16, m_ctlParam16);
	//DDX_Control(pDX, IDC_SPIN_PARAM16, m_ctlSpinParam16);
	//DDX_Text(pDX, IDC_PARAM16, m_pSettings->dbPvars[PARAM16_PVARIABLE]);
	//DDV_MinMaxDouble(pDX, m_pSettings->dbPvars[PARAM16_PVARIABLE], PARAM16_MIN, PARAM16_MAX);
}


BEGIN_MESSAGE_MAP(CVisionSettings, CDialog)
	ON_EN_CHANGE(IDC_PARAM1, &CVisionSettings::OnEnChangeParam)
	ON_EN_CHANGE(IDC_PARAM2, &CVisionSettings::OnEnChangeParam)
	ON_EN_CHANGE(IDC_PARAM3, &CVisionSettings::OnEnChangeParam)
	ON_EN_CHANGE(IDC_PARAM4, &CVisionSettings::OnEnChangeParam)
	ON_EN_CHANGE(IDC_PARAM5, &CVisionSettings::OnEnChangeParam)
	ON_EN_CHANGE(IDC_PARAM6, &CVisionSettings::OnEnChangeParam)
	ON_EN_CHANGE(IDC_PARAM7, &CVisionSettings::OnEnChangeParam)
	ON_EN_CHANGE(IDC_PARAM8, &CVisionSettings::OnEnChangeParam)
	ON_EN_CHANGE(IDC_PARAM9, &CVisionSettings::OnEnChangeParam)
	ON_EN_CHANGE(IDC_PARAM10, &CVisionSettings::OnEnChangeParam)
	ON_EN_CHANGE(IDC_PARAM11, &CVisionSettings::OnEnChangeParam)
	ON_EN_CHANGE(IDC_PARAM12, &CVisionSettings::OnEnChangeParam)
	ON_EN_CHANGE(IDC_PARAM13, &CVisionSettings::OnEnChangeParam)
	ON_EN_CHANGE(IDC_PARAM14, &CVisionSettings::OnEnChangeParam)
	ON_EN_CHANGE(IDC_PARAM15, &CVisionSettings::OnEnChangeParam)
	ON_EN_CHANGE(IDC_PARAM16, &CVisionSettings::OnEnChangeParam)
END_MESSAGE_MAP()


// CVisionSettings message handlers
BOOL CVisionSettings::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// Param1
	m_ctlParam1.m_nPrecision = PARAM1_PRECISION;
	m_ctlParam1.SetRange(PARAM1_MIN,PARAM1_MAX);
	m_ctlParam1.SetTextColor(m_clrText);
	m_ctlParam1.SetBkColor(m_clrBack);
	m_ctlParam1.SetFont(m_pfont);
	m_ctlParam1.SetValuePtr(&m_VisSettings.Threshold);
	m_ctlSpinParam1.SetDecimalPlaces (PARAM1_PRECISION);
	m_ctlSpinParam1.SetTrimTrailingZeros (FALSE);
	m_ctlSpinParam1.SetRangeAndDelta (PARAM1_MIN, PARAM1_MAX, 1);

	// Param2
	m_ctlParam2.m_nPrecision = PARAM2_PRECISION;
	m_ctlParam2.SetRange(PARAM2_MIN,PARAM2_MAX);
	m_ctlParam2.SetTextColor(m_clrText);
	m_ctlParam2.SetBkColor(m_clrBack);
	m_ctlParam2.SetFont(m_pfont);
	m_ctlParam2.SetValuePtr(&m_VisSettings.MinBaconSize);
	m_ctlSpinParam2.SetDecimalPlaces (PARAM2_PRECISION);
	m_ctlSpinParam2.SetTrimTrailingZeros (FALSE);
	m_ctlSpinParam2.SetRangeAndDelta (PARAM2_MIN, PARAM2_MAX, 1);

	// Param3
	m_ctlParam3.m_nPrecision = PARAM3_PRECISION;
	m_ctlParam3.SetRange(PARAM3_MIN,PARAM3_MAX);
	m_ctlParam3.SetTextColor(m_clrText);
	m_ctlParam3.SetBkColor(m_clrBack);
	m_ctlParam3.SetFont(m_pfont);
	m_ctlParam3.SetValuePtr(&m_VisSettings.MinBaconWidth);
	m_ctlSpinParam3.SetDecimalPlaces (PARAM3_PRECISION);
	m_ctlSpinParam3.SetTrimTrailingZeros (FALSE);
	m_ctlSpinParam3.SetRangeAndDelta (PARAM3_MIN, PARAM3_MAX, 1);
	// Param4
	m_ctlParam4.m_nPrecision = PARAM4_PRECISION;
	m_ctlParam4.SetRange(PARAM4_MIN,PARAM4_MAX);
	m_ctlParam4.SetTextColor(m_clrText);
	m_ctlParam4.SetBkColor(m_clrBack);
	m_ctlParam4.SetFont(m_pfont);
	m_ctlParam4.SetValuePtr(&m_VisSettings.MinBaconHeight);
	m_ctlSpinParam4.SetDecimalPlaces (PARAM4_PRECISION);
	m_ctlSpinParam4.SetTrimTrailingZeros (FALSE);
	m_ctlSpinParam4.SetRangeAndDelta (PARAM4_MIN, PARAM4_MAX, 1);

	// Param5
	m_ctlParam5.m_nPrecision = PARAM5_PRECISION;
	m_ctlParam5.SetRange(PARAM5_MIN,PARAM5_MAX);
	m_ctlParam5.SetTextColor(m_clrText);
	m_ctlParam5.SetBkColor(m_clrBack);
	m_ctlParam5.SetFont(m_pfont);
	m_ctlParam5.SetValuePtr(&m_VisSettings.MinBlobRadius);
	m_ctlSpinParam5.SetDecimalPlaces (PARAM5_PRECISION);
	m_ctlSpinParam5.SetTrimTrailingZeros (FALSE);
	m_ctlSpinParam5.SetRangeAndDelta (PARAM5_MIN, PARAM5_MAX, 1);

	// Param6
	m_ctlParam6.m_nPrecision = PARAM6_PRECISION;
	m_ctlParam6.SetRange(PARAM6_MIN,PARAM6_MAX);
	m_ctlParam6.SetTextColor(m_clrText);
	m_ctlParam6.SetBkColor(m_clrBack);
	m_ctlParam6.SetFont(m_pfont);
	m_ctlParam6.SetValuePtr(&m_VisSettings.Trigger);
	m_ctlSpinParam6.SetDecimalPlaces (PARAM6_PRECISION);
	m_ctlSpinParam6.SetTrimTrailingZeros (FALSE);
	m_ctlSpinParam6.SetRangeAndDelta (PARAM6_MIN, PARAM6_MAX, 1);

	// Param7
	m_ctlParam7.m_nPrecision = PARAM7_PRECISION;
	m_ctlParam7.SetRange(PARAM7_MIN,PARAM7_MAX);
	m_ctlParam7.SetTextColor(m_clrText);
	m_ctlParam7.SetBkColor(m_clrBack);
	m_ctlParam7.SetFont(m_pfont);
	m_ctlParam7.SetValuePtr(&m_VisSettings.MinBaconRejectSize);
	m_ctlSpinParam7.SetDecimalPlaces (PARAM7_PRECISION);
	m_ctlSpinParam7.SetTrimTrailingZeros (FALSE);
	m_ctlSpinParam7.SetRangeAndDelta (PARAM7_MIN, PARAM7_MAX, 1);

	// Param8
	m_ctlParam8.m_nPrecision = PARAM8_PRECISION;
	m_ctlParam8.SetRange(PARAM8_MIN,PARAM8_MAX);
	m_ctlParam8.SetTextColor(m_clrText);
	m_ctlParam8.SetBkColor(m_clrBack);
	m_ctlParam8.SetFont(m_pfont);
	m_ctlParam8.SetValuePtr(&m_VisSettings.MinBaconRejectHeight);
	m_ctlSpinParam8.SetDecimalPlaces (PARAM8_PRECISION);
	m_ctlSpinParam8.SetTrimTrailingZeros (FALSE);
	m_ctlSpinParam8.SetRangeAndDelta (PARAM8_MIN, PARAM8_MAX, 1);

	// Param9
	m_ctlParam9.m_nPrecision = PARAM9_PRECISION;
	m_ctlParam9.SetRange(PARAM9_MIN,PARAM9_MAX);
	m_ctlParam9.SetTextColor(m_clrText);
	m_ctlParam9.SetBkColor(m_clrBack);
	m_ctlParam9.SetFont(m_pfont);
	m_ctlParam9.SetValuePtr(&m_VisSettings.MinBaconRejectWidth);
	m_ctlSpinParam9.SetDecimalPlaces (PARAM9_PRECISION);
	m_ctlSpinParam9.SetTrimTrailingZeros (FALSE);
	m_ctlSpinParam9.SetRangeAndDelta (PARAM9_MIN, PARAM9_MAX, 1);

	// Param10
	m_ctlParam10.m_nPrecision = PARAM10_PRECISION;
	m_ctlParam10.SetRange(PARAM10_MIN,PARAM10_MAX);
	m_ctlParam10.SetTextColor(m_clrText);
	m_ctlParam10.SetBkColor(m_clrBack);
	m_ctlParam10.SetFont(m_pfont);
	m_ctlParam10.SetValuePtr(&m_VisSettings.Exposure_uS);
	m_ctlSpinParam10.SetDecimalPlaces (PARAM10_PRECISION);
	m_ctlSpinParam10.SetTrimTrailingZeros (FALSE);
	m_ctlSpinParam10.SetRangeAndDelta (PARAM10_MIN, PARAM10_MAX, 1);

	// Param11
	m_ctlParam11.m_nPrecision = PARAM11_PRECISION;
	m_ctlParam11.SetRange(PARAM11_MIN,PARAM11_MAX);
	m_ctlParam11.SetTextColor(m_clrText);
	m_ctlParam11.SetBkColor(m_clrBack);
	m_ctlParam11.SetFont(m_pfont);
	m_ctlParam11.SetValuePtr(&m_VisSettings.SystemEnable);
	m_ctlSpinParam11.SetDecimalPlaces (PARAM11_PRECISION);
	m_ctlSpinParam11.SetTrimTrailingZeros (FALSE);
	m_ctlSpinParam11.SetRangeAndDelta (PARAM11_MIN, PARAM11_MAX, 1);
	

	// Param12
	m_ctlParam12.m_nPrecision = PARAM12_PRECISION;
	m_ctlParam12.SetRange(PARAM12_MIN,PARAM12_MAX);
	m_ctlParam12.SetTextColor(m_clrText);
	m_ctlParam12.SetBkColor(m_clrBack);
	m_ctlParam12.SetFont(m_pfont);
	m_ctlParam12.SetValuePtr(&m_VisSettings.RejectSuppressionCount);
	m_ctlSpinParam12.SetDecimalPlaces (PARAM12_PRECISION);
	m_ctlSpinParam12.SetTrimTrailingZeros (FALSE);
	m_ctlSpinParam12.SetRangeAndDelta (PARAM12_MIN, PARAM12_MAX, 1);

	// Param13
	m_ctlParam13.m_nPrecision = PARAM13_PRECISION;
	m_ctlParam13.SetRange(PARAM13_MIN,PARAM13_MAX);
	m_ctlParam13.SetTextColor(m_clrText);
	m_ctlParam13.SetBkColor(m_clrBack);
	m_ctlParam13.SetFont(m_pfont);
	m_ctlParam13.SetValuePtr(&m_VisSettings.RejectDuration);
	m_ctlSpinParam13.SetDecimalPlaces (PARAM13_PRECISION);
	m_ctlSpinParam13.SetTrimTrailingZeros (FALSE);
	m_ctlSpinParam13.SetRangeAndDelta (PARAM13_MIN, PARAM13_MAX, 1);

	// Param14
	m_ctlParam14.m_nPrecision = PARAM14_PRECISION;
	m_ctlParam14.SetRange(PARAM14_MIN,PARAM14_MAX);
	m_ctlParam14.SetTextColor(m_clrText);
	m_ctlParam14.SetBkColor(m_clrBack);
	m_ctlParam14.SetFont(m_pfont);
	m_ctlParam14.SetValuePtr(&m_VisSettings.RejectDelay);
	m_ctlSpinParam14.SetDecimalPlaces (PARAM14_PRECISION);
	m_ctlSpinParam14.SetTrimTrailingZeros (FALSE);
	m_ctlSpinParam14.SetRangeAndDelta (PARAM14_MIN, PARAM14_MAX, 1);

	// Param15 
	m_ctlParam15.m_nPrecision = PARAM15_PRECISION;
	m_ctlParam15.SetRange(PARAM15_MIN,PARAM15_MAX);
	m_ctlParam15.SetTextColor(m_clrText);
	m_ctlParam15.SetBkColor(m_clrBack);
	m_ctlParam15.SetFont(m_pfont);
	//m_ctlParam15.SetValuePtr(&m_pSettings->dbPvars[PARAM15_PVARIABLE]);
	m_ctlParam15.SetValuePtr(&m_VisSettings.dbLineRateScaleFactor);
	m_ctlSpinParam15.SetDecimalPlaces (PARAM15_PRECISION);
	m_ctlSpinParam15.SetTrimTrailingZeros (FALSE);
	m_ctlSpinParam15.SetRangeAndDelta (PARAM15_MIN, PARAM15_MAX, 1);

	// Param16
	//m_ctlParam16.m_nPrecision = PARAM16_PRECISION;
	//m_ctlParam16.SetRange(PARAM16_MIN,PARAM16_MAX);
	//m_ctlParam16.SetTextColor(m_clrText);
	//m_ctlParam16.SetBkColor(m_clrBack);
	//m_ctlParam16.SetFont(m_pfont);
	//m_ctlParam16.SetValuePtr(&m_pSettings->dbPvars[PARAM16_PVARIABLE]);
	//m_ctlSpinParam16.SetDecimalPlaces (PARAM16_PRECISION);
	//m_ctlSpinParam16.SetTrimTrailingZeros (FALSE);
	//m_ctlSpinParam16.SetRangeAndDelta (PARAM16_MIN, PARAM16_MAX, 1);
	return TRUE;  // return TRUE unless you set the focus to a control
}


void CVisionSettings::OnEnChangeParam()
{
	// Send change message
	if (m_pWndParent != NULL){
		m_pWndParent->SendMessage (WM_VISION_SETTINGS_CHANGED, 0, 0);		
	}
}
