// MotionSettings2.cpp : implementation file
//

#include "stdafx.h"
#include "HMIDlg.h"
#include "MotionSettings2.h"

#define PARAM1_MIN             0
#define PARAM1_MAX            20
#define PARAM1_PRECISION       2
#define PARAM1_PVARIABLE       5    // P1xxx where xxx = 0 to 100

#define PARAM2_MIN        -50000  
#define PARAM2_MAX         50000
#define PARAM2_PRECISION       0
#define PARAM2_PVARIABLE      31    // P1xxx where xxx = 0 to 100

#define PARAM3_MIN            -4
#define PARAM3_MAX             4
#define PARAM3_PRECISION       2
#define PARAM3_PVARIABLE      23    // P1xxx where xxx = 0 to 100

#define PARAM4_MIN       -100000
#define PARAM4_MAX             0
#define PARAM4_PRECISION       0
#define PARAM4_PVARIABLE      30    // P1xxx where xxx = 0 to 100

#define PARAM5_MIN            0
#define PARAM5_MAX           40
#define PARAM5_PRECISION      1
#define PARAM5_PVARIABLE      6    // P1xxx where xxx = 0 to 100

#define PARAM6_MIN       -500000
#define PARAM6_MAX        500000
#define PARAM6_PRECISION      0
#define PARAM6_PVARIABLE     14      // P1xxx where xxx = 0 to 100

#define PARAM7_MIN      -100000
#define PARAM7_MAX        10000
#define PARAM7_PRECISION      0
#define PARAM7_PVARIABLE     15    // P1xxx where xxx = 0 to 100

#define PARAM8_MIN      -100000
#define PARAM8_MAX            0
#define PARAM8_PRECISION      0
#define PARAM8_PVARIABLE     16    // P1xxx where xxx = 0 to 100

#define PARAM9_MIN             0
#define PARAM9_MAX        100000
#define PARAM9_PRECISION       0
#define PARAM9_PVARIABLE      32    // P1xxx where xxx = 0 to 100

#define PARAM10_MIN            1
#define PARAM10_MAX          300
#define PARAM10_PRECISION      0
#define PARAM10_PVARIABLE     39    // P1xxx where xxx = 0 to 100

#define PARAM11_MIN            1
#define PARAM11_MAX          300
#define PARAM11_PRECISION      0
#define PARAM11_PVARIABLE     40    // P1xxx where xxx = 0 to 100

#define PARAM12_MIN            1
#define PARAM12_MAX          300
#define PARAM12_PRECISION      0
#define PARAM12_PVARIABLE     41    // P1xxx where xxx = 0 to 100

#define PARAM13_MIN            1
#define PARAM13_MAX       500000
#define PARAM13_PRECISION      0
#define PARAM13_PVARIABLE     28    // P1xxx where xxx = 0 to 100

// CMotionSettings2 dialog

IMPLEMENT_DYNAMIC(CMotionSettings2, CPropertyPage)

CMotionSettings2::CMotionSettings2()
	: CPropertyPage(CMotionSettings2::IDD)
{
    m_psp.dwFlags |= PSP_USEHICON;
    m_psp.dwFlags |= PSP_USETITLE;

	HICON hIconTab = AfxGetApp()->LoadIcon (IDI_MOTION_HOMING);
    m_psp.hIcon = hIconTab;
	m_pWndParent = NULL;
	TRACE("..........................m_pWndParent = NULL; \n");
	m_pComWnd = NULL;
}

CMotionSettings2::~CMotionSettings2()
{
}

void CMotionSettings2::DoDataExchange(CDataExchange* pDX)
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

	DDX_Control(pDX, IDC_PARAM11, m_ctlParam11);
	DDX_Control(pDX, IDC_SPIN_PARAM11, m_ctlSpinParam11);
	DDX_Text(pDX, IDC_PARAM11, m_pSettings->dbPvars[PARAM11_PVARIABLE]);
	DDV_MinMaxDouble(pDX, m_pSettings->dbPvars[PARAM11_PVARIABLE], PARAM11_MIN, PARAM11_MAX);

	DDX_Control(pDX, IDC_PARAM12, m_ctlParam12);
	DDX_Control(pDX, IDC_SPIN_PARAM12, m_ctlSpinParam12);
	DDX_Text(pDX, IDC_PARAM12, m_pSettings->dbPvars[PARAM12_PVARIABLE]);
	DDV_MinMaxDouble(pDX, m_pSettings->dbPvars[PARAM12_PVARIABLE], PARAM12_MIN, PARAM12_MAX);

	DDX_Control(pDX, IDC_PARAM13, m_ctlParam13);
	DDX_Control(pDX, IDC_SPIN_PARAM13, m_ctlSpinParam13);
	DDX_Text(pDX, IDC_PARAM13, m_pSettings->dbPvars[PARAM13_PVARIABLE]);
	DDV_MinMaxDouble(pDX, m_pSettings->dbPvars[PARAM13_PVARIABLE], PARAM13_MIN, PARAM13_MAX);
}


BEGIN_MESSAGE_MAP(CMotionSettings2, CPropertyPage)
	ON_EN_CHANGE(IDC_PARAM1, &CMotionSettings2::OnEnChangeParam1)
	ON_EN_CHANGE(IDC_PARAM2, &CMotionSettings2::OnEnChangeParam)
	ON_EN_CHANGE(IDC_PARAM3, &CMotionSettings2::OnEnChangeParam)
	ON_EN_CHANGE(IDC_PARAM4, &CMotionSettings2::OnEnChangeParam)
	ON_EN_CHANGE(IDC_PARAM5, &CMotionSettings2::OnEnChangeParam)
	ON_EN_CHANGE(IDC_PARAM6, &CMotionSettings2::OnEnChangeParam)
	ON_EN_CHANGE(IDC_PARAM7, &CMotionSettings2::OnEnChangeParam)
	ON_EN_CHANGE(IDC_PARAM8, &CMotionSettings2::OnEnChangeParam)
	ON_EN_CHANGE(IDC_PARAM9, &CMotionSettings2::OnEnChangeParam)
	ON_EN_CHANGE(IDC_PARAM10, &CMotionSettings2::OnEnChangeParam)
	ON_EN_CHANGE(IDC_PARAM11, &CMotionSettings2::OnEnChangeParam)
	ON_EN_CHANGE(IDC_PARAM12, &CMotionSettings2::OnEnChangeParam)
	ON_EN_CHANGE(IDC_PARAM13, &CMotionSettings2::OnEnChangeParam)
	ON_BN_CLICKED(IDC_DRUM_FLAG_WIDTH, &CMotionSettings2::OnBnClickedAlignHomeOffset)
	ON_BN_CLICKED(IDC_ALIGN_NEG_LIM, &CMotionSettings2::OnBnClickedAlignNegLim)
	ON_BN_CLICKED(IDC_ALIGN_POS_LIM, &CMotionSettings2::OnBnClickedAlignPosLim)
	ON_BN_CLICKED(IDC_ALIGN_START_POS, &CMotionSettings2::OnBnClickedAlignStartPos)
	ON_BN_CLICKED(IDC_KNIFE_OFFSET, &CMotionSettings2::OnBnClickedKnifeOffset)
END_MESSAGE_MAP()


// CMotionSettings2 message handlers
BOOL CMotionSettings2::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	m_dbDrumOffset = m_pSettings->dbPvars[PARAM1_PVARIABLE];


	// Param1
	m_ctlParam1.m_nPrecision = PARAM1_PRECISION;
	m_ctlParam1.SetRange(PARAM1_MIN,PARAM1_MAX);
	m_ctlParam1.SetTextColor(m_clrText);
	m_ctlParam1.SetBkColor(m_clrBack);
	m_ctlParam1.SetFont(m_pfont);
	m_ctlParam1.SetValuePtr(&m_pSettings->dbPvars[PARAM1_PVARIABLE]);
	m_ctlSpinParam1.SetDecimalPlaces (PARAM1_PRECISION);
	m_ctlSpinParam1.SetTrimTrailingZeros (FALSE);
	m_ctlSpinParam1.SetRangeAndDelta (PARAM1_MIN, PARAM1_MAX, 0.01);

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
	m_ctlSpinParam3.SetRangeAndDelta (PARAM3_MIN, PARAM3_MAX, 0.1);

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

	//// Param5
	m_ctlParam5.m_nPrecision = PARAM5_PRECISION;
	m_ctlParam5.SetRange(PARAM5_MIN,PARAM5_MAX);
	m_ctlParam5.SetTextColor(m_clrText);
	m_ctlParam5.SetBkColor(m_clrBack);
	m_ctlParam5.SetFont(m_pfont);
	m_ctlParam5.SetValuePtr(&m_pSettings->dbPvars[PARAM5_PVARIABLE]);
	m_ctlSpinParam5.SetDecimalPlaces (PARAM5_PRECISION);
	m_ctlSpinParam5.SetTrimTrailingZeros (FALSE);
	m_ctlSpinParam5.SetRangeAndDelta (PARAM5_MIN, PARAM5_MAX, 0.1);

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

	// Param11
	m_ctlParam11.m_nPrecision = PARAM11_PRECISION;
	m_ctlParam11.SetRange(PARAM11_MIN,PARAM11_MAX);
	m_ctlParam11.SetTextColor(m_clrText);
	m_ctlParam11.SetBkColor(m_clrBack);
	m_ctlParam11.SetFont(m_pfont);
	m_ctlParam11.SetValuePtr(&m_pSettings->dbPvars[PARAM11_PVARIABLE]);
	m_ctlSpinParam11.SetDecimalPlaces (PARAM11_PRECISION);
	m_ctlSpinParam11.SetTrimTrailingZeros (FALSE);
	m_ctlSpinParam11.SetRangeAndDelta (PARAM11_MIN, PARAM11_MAX, 1);

	// Param12
	m_ctlParam12.m_nPrecision = PARAM12_PRECISION;
	m_ctlParam12.SetRange(PARAM12_MIN,PARAM12_MAX);
	m_ctlParam12.SetTextColor(m_clrText);
	m_ctlParam12.SetBkColor(m_clrBack);
	m_ctlParam12.SetFont(m_pfont);
	m_ctlParam12.SetValuePtr(&m_pSettings->dbPvars[PARAM12_PVARIABLE]);
	m_ctlSpinParam12.SetDecimalPlaces (PARAM12_PRECISION);
	m_ctlSpinParam12.SetTrimTrailingZeros (FALSE);
	m_ctlSpinParam12.SetRangeAndDelta (PARAM12_MIN, PARAM12_MAX, 1);

	// Param13
	m_ctlParam13.m_nPrecision = PARAM13_PRECISION;
	m_ctlParam13.SetRange(PARAM13_MIN,PARAM13_MAX);
	m_ctlParam13.SetTextColor(m_clrText);
	m_ctlParam13.SetBkColor(m_clrBack);
	m_ctlParam13.SetFont(m_pfont);
	m_ctlParam13.SetValuePtr(&m_pSettings->dbPvars[PARAM13_PVARIABLE]);
	m_ctlSpinParam13.SetDecimalPlaces (PARAM13_PRECISION);
	m_ctlSpinParam13.SetTrimTrailingZeros (FALSE);
	m_ctlSpinParam13.SetRangeAndDelta (PARAM13_MIN, PARAM13_MAX, 1);

	return TRUE;  // return TRUE unless you set the focus to a control

}

void CMotionSettings2::OnEnChangeParam()
{
	// Send change message
	if (m_pWndParent != NULL){
		m_pWndParent->SendMessage (WM_VISION_SETTINGS_CHANGED, 0, 0);		
	}
}

//	
void CMotionSettings2::OnEnChangeParam1()
{
	if (m_pComWnd == NULL)
		return;
	//TRACE("m_pSettings->dbPvars[PARAM1_PVARIABLE]: %f \n",m_pSettings->dbPvars[PARAM1_PVARIABLE]);	
	if (m_dbDrumOffset != m_pSettings->dbPvars[PARAM1_PVARIABLE])
	{
		m_pComWnd->SendMessage (WM_BTC_TIMING_CHECK,0,0);	
	}
	m_dbDrumOffset = m_pSettings->dbPvars[PARAM1_PVARIABLE];
	OnEnChangeParam();
}

void CMotionSettings2::OnBnClickedAlignHomeOffset()
{
	if (m_pComWnd == NULL)
		return;
	long Pos = m_pComWnd->SendMessage (WM_GET_PMAC_MOTOR_POS,1, 0);
	m_pSettings->dbPvars[PARAM2_PVARIABLE] = Pos;
	UpdateData(0);
	OnEnChangeParam();
}


void CMotionSettings2::OnBnClickedAlignNegLim()
{
	if (m_pComWnd == NULL)
		return;
	long Pos = m_pComWnd->SendMessage (WM_GET_PMAC_MOTOR_POS,1, 0);
	m_pSettings->dbPvars[PARAM8_PVARIABLE] = Pos;
	UpdateData(0);
	OnEnChangeParam();
//	TRACE("Get position: %d \n",Pos);	
}

void CMotionSettings2::OnBnClickedAlignPosLim()
{
	if (m_pComWnd == NULL)
		return;
	long Pos = m_pComWnd->SendMessage (WM_GET_PMAC_MOTOR_POS,1, 0);
	m_pSettings->dbPvars[PARAM7_PVARIABLE] = Pos;
	UpdateData(0);
	OnEnChangeParam();
}


void CMotionSettings2::OnBnClickedAlignStartPos()
{
	if (m_pComWnd == NULL)
		return;
	long Pos = m_pComWnd->SendMessage (WM_GET_PMAC_MOTOR_POS,1, 0);
	m_pSettings->dbPvars[PARAM4_PVARIABLE] = Pos;
	UpdateData(0);
	OnEnChangeParam();
}

void CMotionSettings2::OnBnClickedKnifeOffset()
{
	if (m_pComWnd == NULL)
		return;
	long Pos = m_pComWnd->SendMessage (WM_GET_PMAC_MOTOR_POS,3, 0);
	m_pSettings->dbPvars[PARAM6_PVARIABLE] = Pos;
	UpdateData(0);
	OnEnChangeParam();
}
