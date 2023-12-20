// CUserPage3.cpp : implementation file
//

#include "stdafx.h"
#include "HMIDlg.h"
#include "UserPage3.h"

#define PARAM1_MIN        -12000
#define PARAM1_MAX         12000
#define PARAM1_PRECISION       0
#define PARAM1_PVARIABLE      60    // P1xxx where xxx = 0 to 100

#define PARAM2_MIN        -12000  
#define PARAM2_MAX         12000
#define PARAM2_PRECISION       0
#define PARAM2_PVARIABLE      61    // P1xxx where xxx = 0 to 100

//#define PARAM3_MIN             0
//#define PARAM3_MAX           0.5
//#define PARAM3_PRECISION       2
//#define PARAM3_PVARIABLE      47    // P1xxx where xxx = 0 to 100
//
//#define PARAM4_MIN             0
//#define PARAM4_MAX            50
//#define PARAM4_PRECISION       0
//#define PARAM4_PVARIABLE      82    // P1xxx where xxx = 0 to 100

#define PARAM5_MIN           -5
#define PARAM5_MAX            5
#define PARAM5_PRECISION      2
#define PARAM5_PVARIABLE     71    // P1xxx where xxx = 0 to 100

//#define PARAM6_MIN            0
//#define PARAM6_MAX          200
//#define PARAM6_PRECISION      0
//#define PARAM6_PVARIABLE     79    // P1xxx where xxx = 0 to 100

#define PARAM7_MIN            -5
#define PARAM7_MAX             5
#define PARAM7_PRECISION       2
#define PARAM7_PVARIABLE      70    // P1xxx where xxx = 0 to 100

#define PARAM8_MIN            0
#define PARAM8_MAX            1
#define PARAM8_PRECISION      0
#define PARAM8_PVARIABLE     74    // P1xxx where xxx = 0 to 100

#define PARAM15_MIN             0
#define PARAM15_MAX        200000
#define PARAM15_PRECISION       0
#define PARAM15_PVARIABLE      55    // P1xxx where xxx = 0 to 100


// CUserPage3 dialog

IMPLEMENT_DYNAMIC(CUserPage3, CPropertyPage)

CUserPage3::CUserPage3()
	: CPropertyPage(CUserPage3::IDD)
{
    m_psp.dwFlags |= PSP_USEHICON;
    m_psp.dwFlags |= PSP_USETITLE;

	HICON hIconTab = AfxGetApp()->LoadIcon (IDI_MOTION_HOMING);
    m_psp.hIcon = hIconTab;
	m_pWndParent = NULL;

}

CUserPage3::~CUserPage3()
{
}

void CUserPage3::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_PARAM1, m_ctlParam1);
	DDX_Control(pDX, IDC_SPIN_PARAM1, m_ctlSpinParam1);
	DDX_Text(pDX, IDC_PARAM1, m_pSettings->MotionSettings1.dbPvars[PARAM1_PVARIABLE]);
	DDV_MinMaxDouble(pDX, m_pSettings->MotionSettings1.dbPvars[PARAM1_PVARIABLE], PARAM1_MIN, PARAM1_MAX);

	DDX_Control(pDX, IDC_PARAM2, m_ctlParam2);
	DDX_Control(pDX, IDC_SPIN_PARAM2, m_ctlSpinParam2);
	DDX_Text(pDX, IDC_PARAM2, m_pSettings->MotionSettings1.dbPvars[PARAM2_PVARIABLE]);
	DDV_MinMaxDouble(pDX, m_pSettings->MotionSettings1.dbPvars[PARAM2_PVARIABLE], PARAM2_MIN, PARAM2_MAX);

	//DDX_Control(pDX, IDC_PARAM1, m_ctlParam1);
	//DDX_Control(pDX, IDC_SPIN_PARAM1, m_ctlSpinParam1);
	//DDX_Text(pDX, IDC_PARAM1, m_pSettings->MotionSettings1.dbPvars[PARAM1_PVARIABLE]);
	//DDV_MinMaxDouble(pDX, m_pSettings->MotionSettings1.dbPvars[PARAM1_PVARIABLE], PARAM1_MIN, PARAM1_MAX);

	//DDX_Control(pDX, IDC_PARAM2, m_ctlParam2);
	//DDX_Control(pDX, IDC_SPIN_PARAM2, m_ctlSpinParam2);
	//DDX_Text(pDX, IDC_PARAM2, m_pSettings->MotionSettings1.dbPvars[PARAM2_PVARIABLE]);
	//DDV_MinMaxDouble(pDX, m_pSettings->MotionSettings1.dbPvars[PARAM2_PVARIABLE], PARAM2_MIN, PARAM2_MAX);

	//DDX_Control(pDX, IDC_PARAM3, m_ctlParam3);
	//DDX_Control(pDX, IDC_SPIN_PARAM3, m_ctlSpinParam3);
	//DDX_Text(pDX, IDC_PARAM3, m_pSettings->MotionSettings1.dbPvars[PARAM3_PVARIABLE]);
	//DDV_MinMaxDouble(pDX, m_pSettings->MotionSettings1.dbPvars[PARAM3_PVARIABLE], PARAM3_MIN, PARAM3_MAX);

	//DDX_Control(pDX, IDC_PARAM4, m_ctlParam4);
	//DDX_Control(pDX, IDC_SPIN_PARAM4, m_ctlSpinParam4);
	//DDX_Text(pDX, IDC_PARAM4, m_pSettings->MotionSettings1.dbPvars[PARAM4_PVARIABLE]);
	//DDV_MinMaxDouble(pDX, m_pSettings->MotionSettings1.dbPvars[PARAM4_PVARIABLE], PARAM4_MIN, PARAM4_MAX);

	DDX_Control(pDX, IDC_PARAM5, m_ctlParam5);
	DDX_Control(pDX, IDC_SPIN_PARAM5, m_ctlSpinParam5);
	DDX_Text(pDX, IDC_PARAM5, m_pSettings->MotionSettings1.dbPvars[PARAM5_PVARIABLE]);
	DDV_MinMaxDouble(pDX, m_pSettings->MotionSettings1.dbPvars[PARAM5_PVARIABLE], PARAM5_MIN, PARAM5_MAX);

	//DDX_Control(pDX, IDC_PARAM6, m_ctlParam6);
	//DDX_Control(pDX, IDC_SPIN_PARAM6, m_ctlSpinParam6);
	//DDX_Text(pDX, IDC_PARAM6, m_pSettings->MotionSettings1.dbPvars[PARAM6_PVARIABLE]);
	//DDV_MinMaxDouble(pDX, m_pSettings->MotionSettings1.dbPvars[PARAM6_PVARIABLE], PARAM6_MIN, PARAM6_MAX);

	DDX_Control(pDX, IDC_PARAM7, m_ctlParam7);
	DDX_Control(pDX, IDC_SPIN_PARAM7, m_ctlSpinParam7);
	DDX_Text(pDX, IDC_PARAM7, m_pSettings->MotionSettings1.dbPvars[PARAM7_PVARIABLE]);
	DDV_MinMaxDouble(pDX, m_pSettings->MotionSettings1.dbPvars[PARAM7_PVARIABLE], PARAM7_MIN, PARAM7_MAX);

	DDX_Control(pDX, IDC_PARAM8, m_ctlParam8);
	DDX_Control(pDX, IDC_SPIN_PARAM8, m_ctlSpinParam8);
	DDX_Text(pDX, IDC_PARAM8, m_pSettings->MotionSettings1.dbPvars[PARAM8_PVARIABLE]);
	DDV_MinMaxDouble(pDX, m_pSettings->MotionSettings1.dbPvars[PARAM8_PVARIABLE], PARAM8_MIN, PARAM8_MAX);

	DDX_Control(pDX, IDC_PARAM15, m_ctlParam15);
	DDX_Control(pDX, IDC_SPIN_PARAM15, m_ctlSpinParam15);
	DDX_Text(pDX, IDC_PARAM15, m_pSettings->MotionSettings1.dbPvars[PARAM15_PVARIABLE]);
	DDV_MinMaxDouble(pDX, m_pSettings->MotionSettings1.dbPvars[PARAM15_PVARIABLE], PARAM15_MIN, PARAM15_MAX);

}


BEGIN_MESSAGE_MAP(CUserPage3, CDialog)
	ON_EN_CHANGE(IDC_PARAM1, &CUserPage3::OnEnChangeParam)
	ON_EN_CHANGE(IDC_PARAM2, &CUserPage3::OnEnChangeParam)
	//ON_EN_CHANGE(IDC_PARAM3, &CUserPage3::OnEnChangeParam)
	//ON_EN_CHANGE(IDC_PARAM4, &CUserPage3::OnEnChangeParam)
	ON_EN_CHANGE(IDC_PARAM5, &CUserPage3::OnEnChangeParam)
	//ON_EN_CHANGE(IDC_PARAM6, &CUserPage3::OnEnChangeParam)
	ON_EN_CHANGE(IDC_PARAM7, &CUserPage3::OnEnChangeParam)
	ON_EN_CHANGE(IDC_PARAM8, &CUserPage3::OnEnChangeParam)
	ON_EN_CHANGE(IDC_PARAM15, &CUserPage3::OnEnChangeParam)
END_MESSAGE_MAP()


// CUserPage3 message handlers
BOOL CUserPage3::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// Param1
	m_ctlParam1.m_nPrecision = PARAM1_PRECISION;
	m_ctlParam1.SetRange(PARAM1_MIN,PARAM1_MAX);
	m_ctlParam1.SetTextColor(m_clrText);
	m_ctlParam1.SetBkColor(m_clrBack);
	m_ctlParam1.SetFont(m_pfont);
	m_ctlParam1.SetValuePtr(&m_pSettings->MotionSettings1.dbPvars[PARAM1_PVARIABLE]);
	m_ctlSpinParam1.SetDecimalPlaces (PARAM1_PRECISION);
	m_ctlSpinParam1.SetTrimTrailingZeros (FALSE);
	m_ctlSpinParam1.SetRangeAndDelta (PARAM1_MIN, PARAM1_MAX, 1);

	// Param2
	m_ctlParam2.m_nPrecision = PARAM2_PRECISION;
	m_ctlParam2.SetRange(PARAM2_MIN,PARAM2_MAX);
	m_ctlParam2.SetTextColor(m_clrText);
	m_ctlParam2.SetBkColor(m_clrBack);
	m_ctlParam2.SetFont(m_pfont);
	m_ctlParam2.SetValuePtr(&m_pSettings->MotionSettings1.dbPvars[PARAM2_PVARIABLE]);
	m_ctlSpinParam2.SetDecimalPlaces (PARAM2_PRECISION);
	m_ctlSpinParam2.SetTrimTrailingZeros (FALSE);
	m_ctlSpinParam2.SetRangeAndDelta (PARAM2_MIN, PARAM2_MAX, 1);

	//// Param3
	//m_ctlParam3.m_nPrecision = PARAM3_PRECISION;
	//m_ctlParam3.SetRange(PARAM3_MIN,PARAM3_MAX);
	//m_ctlParam3.SetTextColor(m_clrText);
	//m_ctlParam3.SetBkColor(m_clrBack);
	//m_ctlParam3.SetFont(m_pfont);
	//m_ctlParam3.SetValuePtr(&m_pSettings->MotionSettings1.dbPvars[PARAM3_PVARIABLE]);
	//m_ctlSpinParam3.SetDecimalPlaces (PARAM3_PRECISION);
	//m_ctlSpinParam3.SetTrimTrailingZeros (FALSE);
	//m_ctlSpinParam3.SetRangeAndDelta (PARAM3_MIN, PARAM3_MAX, 1);

	//// Param4
	//m_ctlParam4.m_nPrecision = PARAM4_PRECISION;
	//m_ctlParam4.SetRange(PARAM4_MIN,PARAM4_MAX);
	//m_ctlParam4.SetTextColor(m_clrText);
	//m_ctlParam4.SetBkColor(m_clrBack);
	//m_ctlParam4.SetFont(m_pfont);
	//m_ctlParam4.SetValuePtr(&m_pSettings->MotionSettings1.dbPvars[PARAM4_PVARIABLE]);
	//m_ctlSpinParam4.SetDecimalPlaces (PARAM4_PRECISION);
	//m_ctlSpinParam4.SetTrimTrailingZeros (FALSE);
	//m_ctlSpinParam4.SetRangeAndDelta (PARAM4_MIN, PARAM4_MAX, 1);

	// Param5
	m_ctlParam5.m_nPrecision = PARAM5_PRECISION;
	m_ctlParam5.SetRange(PARAM5_MIN,PARAM5_MAX);
	m_ctlParam5.SetTextColor(m_clrText);
	m_ctlParam5.SetBkColor(m_clrBack);
	m_ctlParam5.SetFont(m_pfont);
	m_ctlParam5.SetValuePtr(&m_pSettings->MotionSettings1.dbPvars[PARAM5_PVARIABLE]);
	m_ctlSpinParam5.SetDecimalPlaces (PARAM5_PRECISION);
	m_ctlSpinParam5.SetTrimTrailingZeros (FALSE);
	m_ctlSpinParam5.SetRangeAndDelta (PARAM5_MIN, PARAM5_MAX, 1);

	//// Param6
	//m_ctlParam6.m_nPrecision = PARAM6_PRECISION;
	//m_ctlParam6.SetRange(PARAM6_MIN,PARAM6_MAX);
	//m_ctlParam6.SetTextColor(m_clrText);
	//m_ctlParam6.SetBkColor(m_clrBack);
	//m_ctlParam6.SetFont(m_pfont);
	//m_ctlParam6.SetValuePtr(&m_pSettings->MotionSettings1.dbPvars[PARAM6_PVARIABLE]);
	//m_ctlSpinParam6.SetDecimalPlaces (PARAM6_PRECISION);
	//m_ctlSpinParam6.SetTrimTrailingZeros (FALSE);
	//m_ctlSpinParam6.SetRangeAndDelta (PARAM6_MIN, PARAM6_MAX, 1);

	// Param7
	m_ctlParam7.m_nPrecision = PARAM7_PRECISION;
	m_ctlParam7.SetRange(PARAM7_MIN,PARAM7_MAX);
	m_ctlParam7.SetTextColor(m_clrText);
	m_ctlParam7.SetBkColor(m_clrBack);
	m_ctlParam7.SetFont(m_pfont);
	//m_ctlParam7.SetValuePtr(&m_pSettings->VisSettings2.MinBaconSize);
	m_ctlParam7.SetValuePtr(&m_pSettings->MotionSettings1.dbPvars[PARAM7_PVARIABLE]);
	m_ctlSpinParam7.SetDecimalPlaces (PARAM7_PRECISION);
	m_ctlSpinParam7.SetTrimTrailingZeros (FALSE);
	m_ctlSpinParam7.SetRangeAndDelta (PARAM7_MIN, PARAM7_MAX, 1);

	// Param8
	m_ctlParam8.m_nPrecision = PARAM8_PRECISION;
	m_ctlParam8.SetRange(PARAM8_MIN,PARAM8_MAX);
	m_ctlParam8.SetTextColor(m_clrText);
	m_ctlParam8.SetBkColor(m_clrBack);
	m_ctlParam8.SetFont(m_pfont);
	//m_ctlParam8.SetValuePtr(&m_pSettings->VisSettings2.MinBaconSize);
	m_ctlParam8.SetValuePtr(&m_pSettings->MotionSettings1.dbPvars[PARAM8_PVARIABLE]);
	m_ctlSpinParam8.SetDecimalPlaces (PARAM8_PRECISION);
	m_ctlSpinParam8.SetTrimTrailingZeros (FALSE);
	m_ctlSpinParam8.SetRangeAndDelta (PARAM8_MIN, PARAM8_MAX, 1);

	// Param15
	m_ctlParam15.m_nPrecision = PARAM15_PRECISION;
	m_ctlParam15.SetRange(PARAM15_MIN,PARAM15_MAX);
	m_ctlParam15.SetTextColor(m_clrText);
	m_ctlParam15.SetBkColor(m_clrBack);
	m_ctlParam15.SetFont(m_pfont);
	//m_ctlParam15.SetValuePtr(&m_pSettings->dbPvars[PARAM15_PVARIABLE]);
	m_ctlParam15.SetValuePtr(&m_pSettings->MotionSettings1.dbPvars[PARAM15_PVARIABLE]);
	m_ctlSpinParam15.SetDecimalPlaces (PARAM15_PRECISION);
	m_ctlSpinParam15.SetTrimTrailingZeros (FALSE);
	m_ctlSpinParam15.SetRangeAndDelta (PARAM15_MIN, PARAM15_MAX, 1);

    return TRUE;  // return TRUE unless you set the focus to a control
}


void CUserPage3::OnEnChangeParam()
{
	// Send change message
	if (m_pWndParent != NULL){
		m_pWndParent->SendMessage (WM_VISION_SETTINGS_CHANGED, 0, 0);		
	}
}

