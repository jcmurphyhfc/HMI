// MotionSettings5.cpp : implementation file
//
#include "stdafx.h"
#include "HMIDlg.h"
#include "MotionSettings5.h"

#define PARAM1_MIN           12
#define PARAM1_MAX           30
#define PARAM1_PRECISION      2
#define PARAM1_PVARIABLE     10    // P1xxx where xxx = 0 to 100

#define PARAM2_MIN           12
#define PARAM2_MAX           40
#define PARAM2_PRECISION      2
#define PARAM2_PVARIABLE     11    // P1xxx where xxx = 0 to 100

#define PARAM3_MIN           12
#define PARAM3_MAX           55
#define PARAM3_PRECISION      2
#define PARAM3_PVARIABLE     12    // P1xxx where xxx = 0 to 100

#define PARAM4_MIN            0
#define PARAM4_MAX            1
#define PARAM4_PRECISION      0
#define PARAM4_PVARIABLE     98    // P1xxx where xxx = 0 to 100

#define PARAM5_MIN            1
#define PARAM5_MAX          500
#define PARAM5_PRECISION      0
#define PARAM5_PVARIABLE     94    // P1xxx where xxx = 0 to 100

#define PARAM6_MIN         0.01
#define PARAM6_MAX          500
#define PARAM6_PRECISION      2
#define PARAM6_PVARIABLE     29    // P1xxx where xxx = 0 to 100

#define PARAM7_MIN           20
#define PARAM7_MAX          500
#define PARAM7_PRECISION      0
#define PARAM7_PVARIABLE     89    // P1xxx where xxx = 0 to 100

#define PARAM8_MIN           20
#define PARAM8_MAX          500
#define PARAM8_PRECISION      0
#define PARAM8_PVARIABLE     90    // P1xxx where xxx = 0 to 100

#define PARAM9_MIN           20
#define PARAM9_MAX          500
#define PARAM9_PRECISION      0
#define PARAM9_PVARIABLE     91    // P1xxx where xxx = 0 to 100

#define PARAM10_MIN            0
#define PARAM10_MAX            1
#define PARAM10_PRECISION      0
#define PARAM10_PVARIABLE     59    // P1xxx where xxx = 0 to 100

// CMotionSettings5 dialog

IMPLEMENT_DYNAMIC(CMotionSettings5, CPropertyPage)

CMotionSettings5::CMotionSettings5()
	: CPropertyPage(CMotionSettings5::IDD)
{
    m_psp.dwFlags |= PSP_USEHICON;
    m_psp.dwFlags |= PSP_USETITLE;

	HICON hIconTab = AfxGetApp()->LoadIcon (IDI_PAPER_FEED);
    m_psp.hIcon = hIconTab;
	m_pWndParent = NULL;

}

CMotionSettings5::~CMotionSettings5()
{
}

void CMotionSettings5::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_PARAM1, m_ctlParam1);
	DDX_Control(pDX, IDC_SPIN_PARAM1, m_ctlSpinParam1);
	DDX_Text(pDX, IDC_PARAM1, m_pSettings->dbPvars[PARAM1_PVARIABLE]);
	DDV_MinMaxDouble(pDX, m_pSettings->dbPvars[PARAM1_PVARIABLE], PARAM1_MIN, PARAM1_MAX);

	DDX_Control(pDX, IDC_PARAM2, m_ctlParam2);
	DDX_Control(pDX, IDC_SPIN_PARAM2, m_ctlSpinParam2);
	DDX_Text(pDX, IDC_PARAM2, m_pSettings->dbPvars[PARAM2_PVARIABLE]);
	DDV_MinMaxDouble(pDX, m_pSettings->dbPvars[PARAM2_PVARIABLE], PARAM2_MIN, PARAM2_MAX);

	DDX_Control(pDX, IDC_PARAM3, m_ctlParam3);
	DDX_Control(pDX, IDC_SPIN_PARAM3, m_ctlSpinParam3);
	DDX_Text(pDX, IDC_PARAM3, m_pSettings->dbPvars[PARAM3_PVARIABLE]);
	DDV_MinMaxDouble(pDX, m_pSettings->dbPvars[PARAM3_PVARIABLE], PARAM3_MIN, PARAM3_MAX);

	DDX_Control(pDX, IDC_PARAM4, m_ctlParam4);
	DDX_Control(pDX, IDC_SPIN_PARAM4, m_ctlSpinParam4);
	DDX_Text(pDX, IDC_PARAM4, m_pSettings->dbPvars[PARAM4_PVARIABLE]);
	DDV_MinMaxDouble(pDX, m_pSettings->dbPvars[PARAM4_PVARIABLE], PARAM4_MIN, PARAM4_MAX);

	DDX_Control(pDX, IDC_PARAM5, m_ctlParam5);
	DDX_Control(pDX, IDC_SPIN_PARAM5, m_ctlSpinParam5);
	DDX_Text(pDX, IDC_PARAM5, m_pSettings->dbPvars[PARAM5_PVARIABLE]);
	DDV_MinMaxDouble(pDX, m_pSettings->dbPvars[PARAM5_PVARIABLE], PARAM5_MIN, PARAM5_MAX);

	DDX_Control(pDX, IDC_PARAM6, m_ctlParam6);
	DDX_Control(pDX, IDC_SPIN_PARAM6, m_ctlSpinParam6);
	DDX_Text(pDX, IDC_PARAM6, m_pSettings->dbPvars[PARAM6_PVARIABLE]);
	DDV_MinMaxDouble(pDX, m_pSettings->dbPvars[PARAM6_PVARIABLE], PARAM6_MIN, PARAM6_MAX);

	DDX_Control(pDX, IDC_PARAM7, m_ctlParam7);
	DDX_Control(pDX, IDC_SPIN_PARAM7, m_ctlSpinParam7);
	DDX_Text(pDX, IDC_PARAM7, m_pSettings->dbPvars[PARAM7_PVARIABLE]);
	DDV_MinMaxDouble(pDX, m_pSettings->dbPvars[PARAM7_PVARIABLE], PARAM7_MIN, PARAM7_MAX);

	DDX_Control(pDX, IDC_PARAM8, m_ctlParam8);
	DDX_Control(pDX, IDC_SPIN_PARAM8, m_ctlSpinParam8);
	DDX_Text(pDX, IDC_PARAM8, m_pSettings->dbPvars[PARAM8_PVARIABLE]);
	DDV_MinMaxDouble(pDX, m_pSettings->dbPvars[PARAM8_PVARIABLE], PARAM8_MIN, PARAM8_MAX);

	DDX_Control(pDX, IDC_PARAM9, m_ctlParam9);
	DDX_Control(pDX, IDC_SPIN_PARAM9, m_ctlSpinParam9);
	DDX_Text(pDX, IDC_PARAM9, m_pSettings->dbPvars[PARAM9_PVARIABLE]);
	DDV_MinMaxDouble(pDX, m_pSettings->dbPvars[PARAM9_PVARIABLE], PARAM9_MIN, PARAM9_MAX);

	DDX_Control(pDX, IDC_PARAM10, m_ctlParam10);
	DDX_Control(pDX, IDC_SPIN_PARAM10, m_ctlSpinParam10);
	DDX_Text(pDX, IDC_PARAM10, m_pSettings->dbPvars[PARAM10_PVARIABLE]);
	DDV_MinMaxDouble(pDX, m_pSettings->dbPvars[PARAM10_PVARIABLE], PARAM10_MIN, PARAM10_MAX);

	//DDX_Control(pDX, IDC_PARAM11, m_ctlParam11);
	//DDX_Control(pDX, IDC_SPIN_PARAM11, m_ctlSpinParam11);
	//DDX_Text(pDX, IDC_PARAM11, m_pSettings->dbPvars[PARAM11_PVARIABLE]);
	//DDV_MinMaxDouble(pDX, m_pSettings->dbPvars[PARAM11_PVARIABLE], PARAM11_MIN, PARAM11_MAX);

	//DDX_Control(pDX, IDC_PARAM12, m_ctlParam12);
	//DDX_Control(pDX, IDC_SPIN_PARAM12, m_ctlSpinParam12);
	//DDX_Text(pDX, IDC_PARAM12, m_pSettings->dbPvars[PARAM12_PVARIABLE]);
	//DDV_MinMaxDouble(pDX, m_pSettings->dbPvars[PARAM12_PVARIABLE], PARAM12_MIN, PARAM12_MAX);

	//DDX_Control(pDX, IDC_PARAM13, m_ctlParam13);
	//DDX_Control(pDX, IDC_SPIN_PARAM13, m_ctlSpinParam13);
	//DDX_Text(pDX, IDC_PARAM13, m_pSettings->dbPvars[PARAM13_PVARIABLE]);
	//DDV_MinMaxDouble(pDX, m_pSettings->dbPvars[PARAM13_PVARIABLE], PARAM13_MIN, PARAM13_MAX);

	//DDX_Control(pDX, IDC_PARAM14, m_ctlParam14);
	//DDX_Control(pDX, IDC_SPIN_PARAM14, m_ctlSpinParam14);
	//DDX_Text(pDX, IDC_PARAM14, m_pSettings->dbPvars[PARAM14_PVARIABLE]);
	//DDV_MinMaxDouble(pDX, m_pSettings->dbPvars[PARAM14_PVARIABLE], PARAM14_MIN, PARAM14_MAX);
}


BEGIN_MESSAGE_MAP(CMotionSettings5, CPropertyPage)
	ON_EN_CHANGE(IDC_PARAM1, &CMotionSettings5::OnEnChangeParam)
	ON_EN_CHANGE(IDC_PARAM2, &CMotionSettings5::OnEnChangeParam)
	ON_EN_CHANGE(IDC_PARAM3, &CMotionSettings5::OnEnChangeParam)
	ON_EN_CHANGE(IDC_PARAM4, &CMotionSettings5::OnEnChangeParam)
	ON_EN_CHANGE(IDC_PARAM5, &CMotionSettings5::OnEnChangeParam)
	ON_EN_CHANGE(IDC_PARAM6, &CMotionSettings5::OnEnChangeParam)
	ON_EN_CHANGE(IDC_PARAM7, &CMotionSettings5::OnEnChangeParam)
	ON_EN_CHANGE(IDC_PARAM8, &CMotionSettings5::OnEnChangeParam)
	ON_EN_CHANGE(IDC_PARAM9, &CMotionSettings5::OnEnChangeParam)
	ON_EN_CHANGE(IDC_PARAM10, &CMotionSettings5::OnEnChangeParam)
	//ON_EN_CHANGE(IDC_PARAM11, &CMotionSettings5::OnEnChangeParam)
	//ON_EN_CHANGE(IDC_PARAM12, &CMotionSettings5::OnEnChangeParam)
	//ON_EN_CHANGE(IDC_PARAM13, &CMotionSettings5::OnEnChangeParam)
	//ON_EN_CHANGE(IDC_PARAM14, &CMotionSettings5::OnEnChangeParam)
END_MESSAGE_MAP()


// CMotionSettings5 message handlers
BOOL CMotionSettings5::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// Param1
	m_ctlParam1.m_nPrecision = PARAM1_PRECISION;
	m_ctlParam1.SetRange(PARAM1_MIN,PARAM1_MAX);
	m_ctlParam1.SetTextColor(m_clrText);
	m_ctlParam1.SetBkColor(m_clrBack);
	m_ctlParam1.SetFont(m_pfont);
	m_ctlParam1.SetValuePtr(&m_pSettings->dbPvars[PARAM1_PVARIABLE]);
	m_ctlSpinParam1.SetDecimalPlaces (PARAM1_PRECISION);
	m_ctlSpinParam1.SetTrimTrailingZeros (FALSE);
	m_ctlSpinParam1.SetRangeAndDelta (PARAM1_MIN, PARAM1_MAX, 1);

	// Param2
	m_ctlParam2.m_nPrecision = PARAM2_PRECISION;
	m_ctlParam2.SetRange(PARAM2_MIN,PARAM2_MAX);
	m_ctlParam2.SetTextColor(m_clrText);
	m_ctlParam2.SetBkColor(m_clrBack);
	m_ctlParam2.SetFont(m_pfont);
	m_ctlParam2.SetValuePtr(&m_pSettings->dbPvars[PARAM2_PVARIABLE]);
	m_ctlSpinParam2.SetDecimalPlaces (PARAM2_PRECISION);
	m_ctlSpinParam2.SetTrimTrailingZeros (FALSE);
	m_ctlSpinParam2.SetRangeAndDelta (PARAM2_MIN, PARAM2_MAX, 1);

	// Param3
	m_ctlParam3.m_nPrecision = PARAM3_PRECISION;
	m_ctlParam3.SetRange(PARAM3_MIN,PARAM3_MAX);
	m_ctlParam3.SetTextColor(m_clrText);
	m_ctlParam3.SetBkColor(m_clrBack);
	m_ctlParam3.SetFont(m_pfont);
	m_ctlParam3.SetValuePtr(&m_pSettings->dbPvars[PARAM3_PVARIABLE]);
	m_ctlSpinParam3.SetDecimalPlaces (PARAM3_PRECISION);
	m_ctlSpinParam3.SetTrimTrailingZeros (FALSE);
	m_ctlSpinParam3.SetRangeAndDelta (PARAM3_MIN, PARAM3_MAX, 1);

	// Param4
	m_ctlParam4.m_nPrecision = PARAM4_PRECISION;
	m_ctlParam4.SetRange(PARAM4_MIN,PARAM4_MAX);
	m_ctlParam4.SetTextColor(m_clrText);
	m_ctlParam4.SetBkColor(m_clrBack);
	m_ctlParam4.SetFont(m_pfont);
	m_ctlParam4.SetValuePtr(&m_pSettings->dbPvars[PARAM4_PVARIABLE]);
	m_ctlSpinParam4.SetDecimalPlaces (PARAM4_PRECISION);
	m_ctlSpinParam4.SetTrimTrailingZeros (FALSE);
	m_ctlSpinParam4.SetRangeAndDelta (PARAM4_MIN, PARAM4_MAX, 1);

	// Param5
	m_ctlParam5.m_nPrecision = PARAM5_PRECISION;
	m_ctlParam5.SetRange(PARAM5_MIN,PARAM5_MAX);
	m_ctlParam5.SetTextColor(m_clrText);
	m_ctlParam5.SetBkColor(m_clrBack);
	m_ctlParam5.SetFont(m_pfont);
	m_ctlParam5.SetValuePtr(&m_pSettings->dbPvars[PARAM5_PVARIABLE]);
	m_ctlSpinParam5.SetDecimalPlaces (PARAM5_PRECISION);
	m_ctlSpinParam5.SetTrimTrailingZeros (FALSE);
	m_ctlSpinParam5.SetRangeAndDelta (PARAM5_MIN, PARAM5_MAX, 1);

	// Param6
	m_ctlParam6.m_nPrecision = PARAM6_PRECISION;
	m_ctlParam6.SetRange(PARAM6_MIN,PARAM6_MAX);
	m_ctlParam6.SetTextColor(m_clrText);
	m_ctlParam6.SetBkColor(m_clrBack);
	m_ctlParam6.SetFont(m_pfont);
	m_ctlParam6.SetValuePtr(&m_pSettings->dbPvars[PARAM6_PVARIABLE]);
	m_ctlSpinParam6.SetDecimalPlaces (PARAM6_PRECISION);
	m_ctlSpinParam6.SetTrimTrailingZeros (FALSE);
	m_ctlSpinParam6.SetRangeAndDelta (PARAM6_MIN, PARAM6_MAX, 1);

	// Param7
	m_ctlParam7.m_nPrecision = PARAM7_PRECISION;
	m_ctlParam7.SetRange(PARAM7_MIN,PARAM7_MAX);
	m_ctlParam7.SetTextColor(m_clrText);
	m_ctlParam7.SetBkColor(m_clrBack);
	m_ctlParam7.SetFont(m_pfont);
	m_ctlParam7.SetValuePtr(&m_pSettings->dbPvars[PARAM7_PVARIABLE]);
	m_ctlSpinParam7.SetDecimalPlaces (PARAM7_PRECISION);
	m_ctlSpinParam7.SetTrimTrailingZeros (FALSE);
	m_ctlSpinParam7.SetRangeAndDelta (PARAM7_MIN, PARAM7_MAX, 1);

	// Param8
	m_ctlParam8.m_nPrecision = PARAM8_PRECISION;
	m_ctlParam8.SetRange(PARAM8_MIN,PARAM8_MAX);
	m_ctlParam8.SetTextColor(m_clrText);
	m_ctlParam8.SetBkColor(m_clrBack);
	m_ctlParam8.SetFont(m_pfont);
	m_ctlParam8.SetValuePtr(&m_pSettings->dbPvars[PARAM8_PVARIABLE]);
	m_ctlSpinParam8.SetDecimalPlaces (PARAM8_PRECISION);
	m_ctlSpinParam8.SetTrimTrailingZeros (FALSE);
	m_ctlSpinParam8.SetRangeAndDelta (PARAM8_MIN, PARAM8_MAX, 1);

	// Param9
	m_ctlParam9.m_nPrecision = PARAM9_PRECISION;
	m_ctlParam9.SetRange(PARAM9_MIN,PARAM9_MAX);
	m_ctlParam9.SetTextColor(m_clrText);
	m_ctlParam9.SetBkColor(m_clrBack);
	m_ctlParam9.SetFont(m_pfont);
	m_ctlParam9.SetValuePtr(&m_pSettings->dbPvars[PARAM9_PVARIABLE]);
	m_ctlSpinParam9.SetDecimalPlaces (PARAM9_PRECISION);
	m_ctlSpinParam9.SetTrimTrailingZeros (FALSE);
	m_ctlSpinParam9.SetRangeAndDelta (PARAM9_MIN, PARAM9_MAX, 1);

	// Param10
	m_ctlParam10.m_nPrecision = PARAM10_PRECISION;
	m_ctlParam10.SetRange(PARAM10_MIN,PARAM10_MAX);
	m_ctlParam10.SetTextColor(m_clrText);
	m_ctlParam10.SetBkColor(m_clrBack);
	m_ctlParam10.SetFont(m_pfont);
	m_ctlParam10.SetValuePtr(&m_pSettings->dbPvars[PARAM10_PVARIABLE]);
	m_ctlSpinParam10.SetDecimalPlaces (PARAM10_PRECISION);
	m_ctlSpinParam10.SetTrimTrailingZeros (FALSE);
	m_ctlSpinParam10.SetRangeAndDelta (PARAM10_MIN, PARAM10_MAX, 1);

	//m_ctlParam11.m_nPrecision = PARAM11_PRECISION;
	//m_ctlParam11.SetRange(PARAM11_MIN,PARAM11_MAX);
	//m_ctlParam11.SetTextColor(m_clrText);
	//m_ctlParam11.SetBkColor(m_clrBack);
	//m_ctlParam11.SetFont(m_pfont);
	//m_ctlParam11.SetValuePtr(&m_pSettings->dbPvars[PARAM11_PVARIABLE]);
	//m_ctlSpinParam11.SetDecimalPlaces (PARAM11_PRECISION);
	//m_ctlSpinParam11.SetTrimTrailingZeros (FALSE);
	//m_ctlSpinParam11.SetRangeAndDelta (PARAM11_MIN, PARAM11_MAX, 1);

	//m_ctlParam12.m_nPrecision = PARAM12_PRECISION;
	//m_ctlParam12.SetRange(PARAM12_MIN,PARAM12_MAX);
	//m_ctlParam12.SetTextColor(m_clrText);
	//m_ctlParam12.SetBkColor(m_clrBack);
	//m_ctlParam12.SetFont(m_pfont);
	//m_ctlParam12.SetValuePtr(&m_pSettings->dbPvars[PARAM12_PVARIABLE]);
	//m_ctlSpinParam12.SetDecimalPlaces (PARAM12_PRECISION);
	//m_ctlSpinParam12.SetTrimTrailingZeros (FALSE);
	//m_ctlSpinParam12.SetRangeAndDelta (PARAM12_MIN, PARAM12_MAX, 1);

	//m_ctlParam13.m_nPrecision = PARAM13_PRECISION;
	//m_ctlParam13.SetRange(PARAM13_MIN,PARAM13_MAX);
	//m_ctlParam13.SetTextColor(m_clrText);
	//m_ctlParam13.SetBkColor(m_clrBack);
	//m_ctlParam13.SetFont(m_pfont);
	//m_ctlParam13.SetValuePtr(&m_pSettings->dbPvars[PARAM13_PVARIABLE]);
	//m_ctlSpinParam13.SetDecimalPlaces (PARAM13_PRECISION);
	//m_ctlSpinParam13.SetTrimTrailingZeros (FALSE);
	//m_ctlSpinParam13.SetRangeAndDelta (PARAM13_MIN, PARAM13_MAX, 1);

	//m_ctlParam14.m_nPrecision = PARAM14_PRECISION;
	//m_ctlParam14.SetRange(PARAM14_MIN,PARAM14_MAX);
	//m_ctlParam14.SetTextColor(m_clrText);
	//m_ctlParam14.SetBkColor(m_clrBack);
	//m_ctlParam14.SetFont(m_pfont);
	//m_ctlParam14.SetValuePtr(&m_pSettings->dbPvars[PARAM14_PVARIABLE]);
	//m_ctlSpinParam14.SetDecimalPlaces (PARAM14_PRECISION);
	//m_ctlSpinParam14.SetTrimTrailingZeros (FALSE);
	//m_ctlSpinParam14.SetRangeAndDelta (PARAM14_MIN, PARAM14_MAX, 1);

	return TRUE;  // return TRUE unless you set the focus to a control

}


void CMotionSettings5::OnEnChangeParam()
{
	// Send change message
	if (m_pWndParent != NULL){
		m_pWndParent->SendMessage (WM_VISION_SETTINGS_CHANGED, 0, 0);		
	}
}
