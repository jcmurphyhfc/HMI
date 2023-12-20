// VisionSplit.cpp : implementation file
//

#include "stdafx.h"
#include "HMIDlg.h"
#include "VisionSplit.h"

#define PARAM1_MIN             1
#define PARAM1_MAX           639
#define PARAM1_PRECISION       0

#define PARAM2_MIN             1
#define PARAM2_MAX           639
#define PARAM2_PRECISION       0

#define PARAM3_MIN             1
#define PARAM3_MAX           639
#define PARAM3_PRECISION       0

#define PARAM4_MIN             1
#define PARAM4_MAX           639
#define PARAM4_PRECISION       0

#define PARAM5_MIN             1
#define PARAM5_MAX           639
#define PARAM5_PRECISION       0

#define PARAM6_MIN             1
#define PARAM6_MAX           114
#define PARAM6_PRECISION       0

#define PARAM7_MIN             1
#define PARAM7_MAX           114
#define PARAM7_PRECISION       0

#define PARAM8_MIN             1
#define PARAM8_MAX           114
#define PARAM8_PRECISION       0

#define PARAM9_MIN             1
#define PARAM9_MAX           114
#define PARAM9_PRECISION       0

#define PARAM10_MIN             1
#define PARAM10_MAX           114
#define PARAM10_PRECISION       0

#define PARAM11_MIN             1
#define PARAM11_MAX            20
#define PARAM11_PRECISION       0

#define PARAM12_MIN             1
#define PARAM12_MAX            20
#define PARAM12_PRECISION       0

#define PARAM13_MIN             1
#define PARAM13_MAX           250
#define PARAM13_PRECISION       0

#define PARAM14_MIN             1
#define PARAM14_MAX         72960
#define PARAM14_PRECISION       0

#define PARAM15_MIN             1
#define PARAM15_MAX            50
#define PARAM15_PRECISION       0

#define PARAM16_MIN             0
#define PARAM16_MAX           500
#define PARAM16_PRECISION       0

#define PARAM17_MIN             0
#define PARAM17_MAX           500
#define PARAM17_PRECISION       0
#define PARAM17_PVARIABLE      76    // P1xxx where xxx = 0 to 100

#define PARAM18_MIN             0
#define PARAM18_MAX           400
#define PARAM18_PRECISION       0

#define PARAM19_MIN             0
#define PARAM19_MAX           100
#define PARAM19_PRECISION       0

#define PARAM20_MIN             0
#define PARAM20_MAX           105
#define PARAM20_PRECISION       0

#define PARAM21_MIN             0
#define PARAM21_MAX           480
#define PARAM21_PRECISION       0

#define PARAM22_MIN            10
#define PARAM22_MAX         10000
#define PARAM22_PRECISION       0

#define PARAM23_MIN             0
#define PARAM23_MAX             1
#define PARAM23_PRECISION       0

#define PARAM24_MIN             0
#define PARAM24_MAX             1
#define PARAM24_PRECISION       0
#define PARAM24_PVARIABLE      20    // P1xxx where xxx = 0 to 100

#define PARAM25_MIN             0
#define PARAM25_MAX            20
#define PARAM25_PRECISION       0

// CVisionSplit dialog

IMPLEMENT_DYNAMIC(CVisionSplit, CPropertyPage)

CVisionSplit::CVisionSplit()
	: CPropertyPage(CVisionSplit::IDD)
{
    m_psp.dwFlags |= PSP_USEHICON;
    m_psp.dwFlags |= PSP_USETITLE;

	HICON hIconTab = AfxGetApp()->LoadIcon (IDI_SLICER);
    m_psp.hIcon = hIconTab;
	m_pWndParent = NULL;
}

CVisionSplit::~CVisionSplit()
{
}

void CVisionSplit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PARAM1, m_ctlParam1);
	DDX_Control(pDX, IDC_SPIN_PARAM1, m_ctlSpinParam1);
	DDX_Text(pDX, IDC_PARAM1, m_VisSettings.x[0]);
	DDV_MinMaxDouble(pDX, m_VisSettings.x[0], PARAM1_MIN, PARAM1_MAX);

	DDX_Control(pDX, IDC_PARAM2, m_ctlParam2);
	DDX_Control(pDX, IDC_SPIN_PARAM2, m_ctlSpinParam2);
	DDX_Text(pDX, IDC_PARAM2, m_VisSettings.x[1]);
	DDV_MinMaxDouble(pDX, m_VisSettings.x[1], PARAM2_MIN, PARAM2_MAX);

	DDX_Control(pDX, IDC_PARAM3, m_ctlParam3);
	DDX_Control(pDX, IDC_SPIN_PARAM3, m_ctlSpinParam3);
	DDX_Text(pDX, IDC_PARAM3, m_VisSettings.x[2]);
	DDV_MinMaxDouble(pDX, m_VisSettings.x[2], PARAM3_MIN, PARAM3_MAX);

	DDX_Control(pDX, IDC_PARAM4, m_ctlParam4);
	DDX_Control(pDX, IDC_SPIN_PARAM4, m_ctlSpinParam4);
	DDX_Text(pDX, IDC_PARAM4, m_VisSettings.x[3]);
	DDV_MinMaxDouble(pDX, m_VisSettings.x[3], PARAM4_MIN, PARAM4_MAX);

	DDX_Control(pDX, IDC_PARAM5, m_ctlParam5);
	DDX_Control(pDX, IDC_SPIN_PARAM5, m_ctlSpinParam5);
	DDX_Text(pDX, IDC_PARAM5, m_VisSettings.x[4]);
	DDV_MinMaxDouble(pDX, m_VisSettings.x[4], PARAM5_MIN, PARAM5_MAX);

	DDX_Control(pDX, IDC_PARAM6, m_ctlParam6);
	DDX_Control(pDX, IDC_SPIN_PARAM6, m_ctlSpinParam6);
	DDX_Text(pDX, IDC_PARAM6, m_VisSettings.y[0]);
	DDV_MinMaxDouble(pDX, m_VisSettings.y[0], PARAM6_MIN, PARAM6_MAX);

	DDX_Control(pDX, IDC_PARAM7, m_ctlParam7);
	DDX_Control(pDX, IDC_SPIN_PARAM7, m_ctlSpinParam7);
	DDX_Text(pDX, IDC_PARAM7, m_VisSettings.y[1]);
	DDV_MinMaxDouble(pDX, m_VisSettings.y[1], PARAM7_MIN, PARAM7_MAX);

	DDX_Control(pDX, IDC_PARAM8, m_ctlParam8);
	DDX_Control(pDX, IDC_SPIN_PARAM8, m_ctlSpinParam8);
	DDX_Text(pDX, IDC_PARAM8, m_VisSettings.y[2]);
	DDV_MinMaxDouble(pDX, m_VisSettings.y[2], PARAM8_MIN, PARAM8_MAX);

	DDX_Control(pDX, IDC_PARAM9, m_ctlParam9);
	DDX_Control(pDX, IDC_SPIN_PARAM9, m_ctlSpinParam9);
	DDX_Text(pDX, IDC_PARAM9, m_VisSettings.y[3]);
	DDV_MinMaxDouble(pDX, m_VisSettings.y[3], PARAM9_MIN, PARAM9_MAX);

	DDX_Control(pDX, IDC_PARAM10, m_ctlParam10);
	DDX_Control(pDX, IDC_SPIN_PARAM10, m_ctlSpinParam10);
	DDX_Text(pDX, IDC_PARAM10, m_VisSettings.y[4]);
	DDV_MinMaxDouble(pDX, m_VisSettings.y[4], PARAM10_MIN, PARAM10_MAX);

	DDX_Control(pDX, IDC_PARAM11, m_ctlParam11);
	DDX_Control(pDX, IDC_SPIN_PARAM11, m_ctlSpinParam11);
	DDX_Text(pDX, IDC_PARAM11, m_VisSettings.NominalLaserWidth);
	DDV_MinMaxDouble(pDX, m_VisSettings.NominalLaserWidth, PARAM11_MIN, PARAM11_MAX);

	DDX_Control(pDX, IDC_PARAM12, m_ctlParam12);
	DDX_Control(pDX, IDC_SPIN_PARAM12, m_ctlSpinParam12);
	DDX_Text(pDX, IDC_PARAM12, m_VisSettings.LaserWidthDelta);
	DDV_MinMaxDouble(pDX, m_VisSettings.LaserWidthDelta, PARAM12_MIN, PARAM12_MAX);

	DDX_Control(pDX, IDC_PARAM13, m_ctlParam13);
	DDX_Control(pDX, IDC_SPIN_PARAM13, m_ctlSpinParam13);
	DDX_Text(pDX, IDC_PARAM13, m_VisSettings.MinLaserIntensity);
	DDV_MinMaxDouble(pDX, m_VisSettings.MinLaserIntensity, PARAM13_MIN, PARAM13_MAX);

	DDX_Control(pDX, IDC_PARAM14, m_ctlParam14);
	DDX_Control(pDX, IDC_SPIN_PARAM14, m_ctlSpinParam14);
	DDX_Text(pDX, IDC_PARAM14, m_VisSettings.MinBaconSize);
	DDV_MinMaxDouble(pDX, m_VisSettings.MinBaconSize, PARAM14_MIN, PARAM14_MAX);

	DDX_Control(pDX, IDC_PARAM15, m_ctlParam15);
	DDX_Control(pDX, IDC_SPIN_PARAM15, m_ctlSpinParam15);
	DDX_Text(pDX, IDC_PARAM15, m_VisSettings.MaxBaconBlobs);
	DDV_MinMaxDouble(pDX, m_VisSettings.MaxBaconBlobs, PARAM15_MIN, PARAM15_MAX);

	DDX_Control(pDX, IDC_PARAM16, m_ctlParam16);
	DDX_Control(pDX, IDC_SPIN_PARAM16, m_ctlSpinParam16);
	DDX_Text(pDX, IDC_PARAM16, m_VisSettings.EndDetectLockCount);
	DDV_MinMaxDouble(pDX, m_VisSettings.EndDetectLockCount, PARAM16_MIN, PARAM16_MAX);

	DDX_Control(pDX, IDC_PARAM17, m_ctlParam17);
	DDX_Control(pDX, IDC_SPIN_PARAM17, m_ctlSpinParam17);
	DDX_Text(pDX, IDC_PARAM17, m_pSettings->dbPvars[PARAM17_PVARIABLE]);
	DDV_MinMaxDouble(pDX, m_pSettings->dbPvars[PARAM17_PVARIABLE], PARAM17_MIN, PARAM17_MAX);

	DDX_Control(pDX, IDC_PARAM18, m_ctlParam18);
	DDX_Control(pDX, IDC_SPIN_PARAM18, m_ctlSpinParam18);
	DDX_Text(pDX, IDC_PARAM18, m_VisSettings.MaxGapFillX);
	DDV_MinMaxDouble(pDX, m_VisSettings.MaxGapFillX, PARAM18_MIN, PARAM18_MAX);

	DDX_Control(pDX, IDC_PARAM19, m_ctlParam19);
	DDX_Control(pDX, IDC_SPIN_PARAM19, m_ctlSpinParam19);
	DDX_Text(pDX, IDC_PARAM19, m_VisSettings.MaxGapFillY);
	DDV_MinMaxDouble(pDX, m_VisSettings.MaxGapFillY, PARAM19_MIN, PARAM19_MAX);

	DDX_Control(pDX, IDC_PARAM20, m_ctlParam20);
	DDX_Control(pDX, IDC_SPIN_PARAM20, m_ctlSpinParam20);
	DDX_Text(pDX, IDC_PARAM20, m_VisSettings.MinPosY);
	DDV_MinMaxDouble(pDX, m_VisSettings.MinPosY, PARAM20_MIN, PARAM20_MAX);

	DDX_Control(pDX, IDC_PARAM21, m_ctlParam21);
	DDX_Control(pDX, IDC_SPIN_PARAM21, m_ctlSpinParam21);
	DDX_Text(pDX, IDC_PARAM21, m_VisSettings.ROIOffsetY);
	DDV_MinMaxDouble(pDX, m_VisSettings.ROIOffsetY, PARAM21_MIN, PARAM21_MAX);

	DDX_Control(pDX, IDC_PARAM22, m_ctlParam22);
	DDX_Control(pDX, IDC_SPIN_PARAM22, m_ctlSpinParam22);
	DDX_Text(pDX, IDC_PARAM22, m_VisSettings.Exposure_uS);
	DDV_MinMaxDouble(pDX, m_VisSettings.Exposure_uS, PARAM22_MIN, PARAM22_MAX);

	DDX_Control(pDX, IDC_PARAM23, m_ctlParam23);
	DDX_Control(pDX, IDC_SPIN_PARAM23, m_ctlSpinParam23);
	DDX_Text(pDX, IDC_PARAM23, m_VisSettings.TriggerOn);
	DDV_MinMaxDouble(pDX, m_VisSettings.TriggerOn, PARAM23_MIN, PARAM23_MAX);

	DDX_Control(pDX, IDC_PARAM24, m_ctlParam24);
	DDX_Control(pDX, IDC_SPIN_PARAM24, m_ctlSpinParam24);
	DDX_Text(pDX, IDC_PARAM24, m_pSettings->dbPvars[PARAM24_PVARIABLE]);
	DDV_MinMaxDouble(pDX, m_pSettings->dbPvars[PARAM24_PVARIABLE], PARAM24_MIN, PARAM24_MAX);

	DDX_Control(pDX, IDC_PARAM25, m_ctlParam25);
	DDX_Control(pDX, IDC_SPIN_PARAM25, m_ctlSpinParam25);
	DDX_Text(pDX, IDC_PARAM25, m_VisSettings.GapDetectLatchCount);
	DDV_MinMaxDouble(pDX, m_VisSettings.GapDetectLatchCount, PARAM25_MIN, PARAM25_MAX);
}


BEGIN_MESSAGE_MAP(CVisionSplit, CPropertyPage)
	ON_EN_CHANGE(IDC_PARAM1, &CVisionSplit::OnEnChangeParam)
	ON_EN_CHANGE(IDC_PARAM2, &CVisionSplit::OnEnChangeParam)
	ON_EN_CHANGE(IDC_PARAM3, &CVisionSplit::OnEnChangeParam)
	ON_EN_CHANGE(IDC_PARAM4, &CVisionSplit::OnEnChangeParam)
	ON_EN_CHANGE(IDC_PARAM5, &CVisionSplit::OnEnChangeParam)
	ON_EN_CHANGE(IDC_PARAM6, &CVisionSplit::OnEnChangeParam)
	ON_EN_CHANGE(IDC_PARAM7, &CVisionSplit::OnEnChangeParam)
	ON_EN_CHANGE(IDC_PARAM8, &CVisionSplit::OnEnChangeParam)
	ON_EN_CHANGE(IDC_PARAM9, &CVisionSplit::OnEnChangeParam)
	ON_EN_CHANGE(IDC_PARAM10, &CVisionSplit::OnEnChangeParam)
	ON_EN_CHANGE(IDC_PARAM11, &CVisionSplit::OnEnChangeParam)
	ON_EN_CHANGE(IDC_PARAM12, &CVisionSplit::OnEnChangeParam)
	ON_EN_CHANGE(IDC_PARAM13, &CVisionSplit::OnEnChangeParam)
	ON_EN_CHANGE(IDC_PARAM14, &CVisionSplit::OnEnChangeParam)
	ON_EN_CHANGE(IDC_PARAM15, &CVisionSplit::OnEnChangeParam)
	ON_EN_CHANGE(IDC_PARAM16, &CVisionSplit::OnEnChangeParam)
	ON_EN_CHANGE(IDC_PARAM17, &CVisionSplit::OnEnChangeParam)
	ON_EN_CHANGE(IDC_PARAM18, &CVisionSplit::OnEnChangeParam)
	ON_EN_CHANGE(IDC_PARAM19, &CVisionSplit::OnEnChangeParam)
	ON_EN_CHANGE(IDC_PARAM20, &CVisionSplit::OnEnChangeParam)
	ON_EN_CHANGE(IDC_PARAM21, &CVisionSplit::OnEnChangeParam)
	ON_EN_CHANGE(IDC_PARAM22, &CVisionSplit::OnEnChangeParam)
	ON_EN_CHANGE(IDC_PARAM23, &CVisionSplit::OnEnChangeParam)
	ON_EN_CHANGE(IDC_PARAM24, &CVisionSplit::OnEnChangeParam)
	ON_EN_CHANGE(IDC_PARAM25, &CVisionSplit::OnEnChangeParam)
END_MESSAGE_MAP()


// CVisionSplit message handlers
// CVisionSplit message handlers
BOOL CVisionSplit::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// Param1
	m_ctlParam1.m_nPrecision = PARAM1_PRECISION;
	m_ctlParam1.SetRange(PARAM1_MIN,PARAM1_MAX);
	m_ctlParam1.SetTextColor(m_clrText);
	m_ctlParam1.SetBkColor(m_clrBack);
	m_ctlParam1.SetFont(m_pfont);
	m_ctlParam1.SetValuePtr(&m_VisSettings.x[0]);
	m_ctlSpinParam1.SetDecimalPlaces (PARAM1_PRECISION);
	m_ctlSpinParam1.SetTrimTrailingZeros (FALSE);
	m_ctlSpinParam1.SetRangeAndDelta (PARAM1_MIN, PARAM1_MAX, 1);

	// Param2
	m_ctlParam2.m_nPrecision = PARAM2_PRECISION;
	m_ctlParam2.SetRange(PARAM2_MIN,PARAM2_MAX);
	m_ctlParam2.SetTextColor(m_clrText);
	m_ctlParam2.SetBkColor(m_clrBack);
	m_ctlParam2.SetFont(m_pfont);
	m_ctlParam2.SetValuePtr(&m_VisSettings.x[1]);
	m_ctlSpinParam2.SetDecimalPlaces (PARAM2_PRECISION);
	m_ctlSpinParam2.SetTrimTrailingZeros (FALSE);
	m_ctlSpinParam2.SetRangeAndDelta (PARAM2_MIN, PARAM2_MAX, 1);

	// Param3
	m_ctlParam3.m_nPrecision = PARAM3_PRECISION;
	m_ctlParam3.SetRange(PARAM3_MIN,PARAM3_MAX);
	m_ctlParam3.SetTextColor(m_clrText);
	m_ctlParam3.SetBkColor(m_clrBack);
	m_ctlParam3.SetFont(m_pfont);
	m_ctlParam3.SetValuePtr(&m_VisSettings.x[2]);
	m_ctlSpinParam3.SetDecimalPlaces (PARAM3_PRECISION);
	m_ctlSpinParam3.SetTrimTrailingZeros (FALSE);
	m_ctlSpinParam3.SetRangeAndDelta (PARAM3_MIN, PARAM3_MAX, 1);
	// Param4
	m_ctlParam4.m_nPrecision = PARAM4_PRECISION;
	m_ctlParam4.SetRange(PARAM4_MIN,PARAM4_MAX);
	m_ctlParam4.SetTextColor(m_clrText);
	m_ctlParam4.SetBkColor(m_clrBack);
	m_ctlParam4.SetFont(m_pfont);
	m_ctlParam4.SetValuePtr(&m_VisSettings.x[3]);
	m_ctlSpinParam4.SetDecimalPlaces (PARAM4_PRECISION);
	m_ctlSpinParam4.SetTrimTrailingZeros (FALSE);
	m_ctlSpinParam4.SetRangeAndDelta (PARAM4_MIN, PARAM4_MAX, 1);

	// Param5
	m_ctlParam5.m_nPrecision = PARAM5_PRECISION;
	m_ctlParam5.SetRange(PARAM5_MIN,PARAM5_MAX);
	m_ctlParam5.SetTextColor(m_clrText);
	m_ctlParam5.SetBkColor(m_clrBack);
	m_ctlParam5.SetFont(m_pfont);
	m_ctlParam5.SetValuePtr(&m_VisSettings.x[4]);
	m_ctlSpinParam5.SetDecimalPlaces (PARAM5_PRECISION);
	m_ctlSpinParam5.SetTrimTrailingZeros (FALSE);
	m_ctlSpinParam5.SetRangeAndDelta (PARAM5_MIN, PARAM5_MAX, 1);

	// Param6
	m_ctlParam6.m_nPrecision = PARAM6_PRECISION;
	m_ctlParam6.SetRange(PARAM6_MIN,PARAM6_MAX);
	m_ctlParam6.SetTextColor(m_clrText);
	m_ctlParam6.SetBkColor(m_clrBack);
	m_ctlParam6.SetFont(m_pfont);
	m_ctlParam6.SetValuePtr(&m_VisSettings.y[0]);
	m_ctlSpinParam6.SetDecimalPlaces (PARAM6_PRECISION);
	m_ctlSpinParam6.SetTrimTrailingZeros (FALSE);
	m_ctlSpinParam6.SetRangeAndDelta (PARAM6_MIN, PARAM6_MAX, 1);

	// Param7
	m_ctlParam7.m_nPrecision = PARAM7_PRECISION;
	m_ctlParam7.SetRange(PARAM7_MIN,PARAM7_MAX);
	m_ctlParam7.SetTextColor(m_clrText);
	m_ctlParam7.SetBkColor(m_clrBack);
	m_ctlParam7.SetFont(m_pfont);
	m_ctlParam7.SetValuePtr(&m_VisSettings.y[1]);
	m_ctlSpinParam7.SetDecimalPlaces (PARAM7_PRECISION);
	m_ctlSpinParam7.SetTrimTrailingZeros (FALSE);
	m_ctlSpinParam7.SetRangeAndDelta (PARAM7_MIN, PARAM7_MAX, 1);

	// Param8
	m_ctlParam8.m_nPrecision = PARAM8_PRECISION;
	m_ctlParam8.SetRange(PARAM8_MIN,PARAM8_MAX);
	m_ctlParam8.SetTextColor(m_clrText);
	m_ctlParam8.SetBkColor(m_clrBack);
	m_ctlParam8.SetFont(m_pfont);
	m_ctlParam8.SetValuePtr(&m_VisSettings.y[2]);
	m_ctlSpinParam8.SetDecimalPlaces (PARAM8_PRECISION);
	m_ctlSpinParam8.SetTrimTrailingZeros (FALSE);
	m_ctlSpinParam8.SetRangeAndDelta (PARAM8_MIN, PARAM8_MAX, 1);

	// Param9
	m_ctlParam9.m_nPrecision = PARAM9_PRECISION;
	m_ctlParam9.SetRange(PARAM9_MIN,PARAM9_MAX);
	m_ctlParam9.SetTextColor(m_clrText);
	m_ctlParam9.SetBkColor(m_clrBack);
	m_ctlParam9.SetFont(m_pfont);
	m_ctlParam9.SetValuePtr(&m_VisSettings.y[3]);
	m_ctlSpinParam9.SetDecimalPlaces (PARAM9_PRECISION);
	m_ctlSpinParam9.SetTrimTrailingZeros (FALSE);
	m_ctlSpinParam9.SetRangeAndDelta (PARAM9_MIN, PARAM9_MAX, 1);

	// Param10
	m_ctlParam10.m_nPrecision = PARAM10_PRECISION;
	m_ctlParam10.SetRange(PARAM10_MIN,PARAM10_MAX);
	m_ctlParam10.SetTextColor(m_clrText);
	m_ctlParam10.SetBkColor(m_clrBack);
	m_ctlParam10.SetFont(m_pfont);
	m_ctlParam10.SetValuePtr(&m_VisSettings.y[4]);
	m_ctlSpinParam10.SetDecimalPlaces (PARAM10_PRECISION);
	m_ctlSpinParam10.SetTrimTrailingZeros (FALSE);
	m_ctlSpinParam10.SetRangeAndDelta (PARAM10_MIN, PARAM10_MAX, 1);

	// Param11
	m_ctlParam11.m_nPrecision = PARAM11_PRECISION;
	m_ctlParam11.SetRange(PARAM11_MIN,PARAM11_MAX);
	m_ctlParam11.SetTextColor(m_clrText);
	m_ctlParam11.SetBkColor(m_clrBack);
	m_ctlParam11.SetFont(m_pfont);
	m_ctlParam11.SetValuePtr(&m_VisSettings.NominalLaserWidth);
	m_ctlSpinParam11.SetDecimalPlaces (PARAM11_PRECISION);
	m_ctlSpinParam11.SetTrimTrailingZeros (FALSE);
	m_ctlSpinParam11.SetRangeAndDelta (PARAM11_MIN, PARAM11_MAX, 1);

	// Param12
	m_ctlParam12.m_nPrecision = PARAM12_PRECISION;
	m_ctlParam12.SetRange(PARAM12_MIN,PARAM12_MAX);
	m_ctlParam12.SetTextColor(m_clrText);
	m_ctlParam12.SetBkColor(m_clrBack);
	m_ctlParam12.SetFont(m_pfont);
	m_ctlParam12.SetValuePtr(&m_VisSettings.LaserWidthDelta);
	m_ctlSpinParam12.SetDecimalPlaces (PARAM12_PRECISION);
	m_ctlSpinParam12.SetTrimTrailingZeros (FALSE);
	m_ctlSpinParam12.SetRangeAndDelta (PARAM12_MIN, PARAM12_MAX, 1);

	// Param13
	m_ctlParam13.m_nPrecision = PARAM13_PRECISION;
	m_ctlParam13.SetRange(PARAM13_MIN,PARAM13_MAX);
	m_ctlParam13.SetTextColor(m_clrText);
	m_ctlParam13.SetBkColor(m_clrBack);
	m_ctlParam13.SetFont(m_pfont);
	m_ctlParam13.SetValuePtr(&m_VisSettings.MinLaserIntensity);
	m_ctlSpinParam13.SetDecimalPlaces (PARAM13_PRECISION);
	m_ctlSpinParam13.SetTrimTrailingZeros (FALSE);
	m_ctlSpinParam13.SetRangeAndDelta (PARAM13_MIN, PARAM13_MAX, 1);

	// Param14
	m_ctlParam14.m_nPrecision = PARAM14_PRECISION;
	m_ctlParam14.SetRange(PARAM14_MIN,PARAM14_MAX);
	m_ctlParam14.SetTextColor(m_clrText);
	m_ctlParam14.SetBkColor(m_clrBack);
	m_ctlParam14.SetFont(m_pfont);
	m_ctlParam14.SetValuePtr(&m_VisSettings.MinBaconSize);
	m_ctlSpinParam14.SetDecimalPlaces (PARAM14_PRECISION);
	m_ctlSpinParam14.SetTrimTrailingZeros (FALSE);
	m_ctlSpinParam14.SetRangeAndDelta (PARAM14_MIN, PARAM14_MAX, 1);

	// Param15
	m_ctlParam15.m_nPrecision = PARAM15_PRECISION;
	m_ctlParam15.SetRange(PARAM15_MIN,PARAM15_MAX);
	m_ctlParam15.SetTextColor(m_clrText);
	m_ctlParam15.SetBkColor(m_clrBack);
	m_ctlParam15.SetFont(m_pfont);
	m_ctlParam15.SetValuePtr(&m_VisSettings.MaxBaconBlobs);
	m_ctlSpinParam15.SetDecimalPlaces (PARAM15_PRECISION);
	m_ctlSpinParam15.SetTrimTrailingZeros (FALSE);
	m_ctlSpinParam15.SetRangeAndDelta (PARAM15_MIN, PARAM15_MAX, 1);

	// Param16
	m_ctlParam16.m_nPrecision = PARAM16_PRECISION;
	m_ctlParam16.SetRange(PARAM16_MIN,PARAM16_MAX);
	m_ctlParam16.SetTextColor(m_clrText);
	m_ctlParam16.SetBkColor(m_clrBack);
	m_ctlParam16.SetFont(m_pfont);
	m_ctlParam16.SetValuePtr(&m_VisSettings.EndDetectLockCount);
	m_ctlSpinParam16.SetDecimalPlaces (PARAM16_PRECISION);
	m_ctlSpinParam16.SetTrimTrailingZeros (FALSE);
	m_ctlSpinParam16.SetRangeAndDelta (PARAM16_MIN, PARAM16_MAX, 1);

	// Param17
	m_ctlParam17.m_nPrecision = PARAM17_PRECISION;
	m_ctlParam17.SetRange(PARAM17_MIN,PARAM17_MAX);
	m_ctlParam17.SetTextColor(m_clrText);
	m_ctlParam17.SetBkColor(m_clrBack);
	m_ctlParam17.SetFont(m_pfont);
	m_ctlParam17.SetValuePtr(&m_pSettings->dbPvars[PARAM17_PVARIABLE]);
	m_ctlSpinParam17.SetDecimalPlaces (PARAM17_PRECISION);
	m_ctlSpinParam17.SetTrimTrailingZeros (FALSE);
	m_ctlSpinParam17.SetRangeAndDelta (PARAM17_MIN, PARAM17_MAX, 1);
	
	// Param18
	m_ctlParam18.m_nPrecision = PARAM18_PRECISION;
	m_ctlParam18.SetRange(PARAM18_MIN,PARAM18_MAX);
	m_ctlParam18.SetTextColor(m_clrText);
	m_ctlParam18.SetBkColor(m_clrBack);
	m_ctlParam18.SetFont(m_pfont);
	m_ctlParam18.SetValuePtr(&m_VisSettings.MaxGapFillX);
	m_ctlSpinParam18.SetDecimalPlaces (PARAM18_PRECISION);
	m_ctlSpinParam18.SetTrimTrailingZeros (FALSE);
	m_ctlSpinParam18.SetRangeAndDelta (PARAM18_MIN, PARAM18_MAX, 1);

	// Param19
	m_ctlParam19.m_nPrecision = PARAM19_PRECISION;
	m_ctlParam19.SetRange(PARAM19_MIN,PARAM19_MAX);
	m_ctlParam19.SetTextColor(m_clrText);
	m_ctlParam19.SetBkColor(m_clrBack);
	m_ctlParam19.SetFont(m_pfont);
	m_ctlParam19.SetValuePtr(&m_VisSettings.MaxGapFillY);
	m_ctlSpinParam19.SetDecimalPlaces (PARAM19_PRECISION);
	m_ctlSpinParam19.SetTrimTrailingZeros (FALSE);
	m_ctlSpinParam19.SetRangeAndDelta (PARAM19_MIN, PARAM19_MAX, 1);

	// Param20
	m_ctlParam20.m_nPrecision = PARAM20_PRECISION;
	m_ctlParam20.SetRange(PARAM20_MIN,PARAM20_MAX);
	m_ctlParam20.SetTextColor(m_clrText);
	m_ctlParam20.SetBkColor(m_clrBack);
	m_ctlParam20.SetFont(m_pfont);
	m_ctlParam20.SetValuePtr(&m_VisSettings.MinPosY);
	m_ctlSpinParam20.SetDecimalPlaces (PARAM20_PRECISION);
	m_ctlSpinParam20.SetTrimTrailingZeros (FALSE);
	m_ctlSpinParam20.SetRangeAndDelta (PARAM20_MIN, PARAM20_MAX, 1);

	// Param21
	m_ctlParam21.m_nPrecision = PARAM21_PRECISION;
	m_ctlParam21.SetRange(PARAM21_MIN,PARAM21_MAX);
	m_ctlParam21.SetTextColor(m_clrText);
	m_ctlParam21.SetBkColor(m_clrBack);
	m_ctlParam21.SetFont(m_pfont);
	m_ctlParam21.SetValuePtr(&m_VisSettings.ROIOffsetY);
	m_ctlSpinParam21.SetDecimalPlaces (PARAM21_PRECISION);
	m_ctlSpinParam21.SetTrimTrailingZeros (FALSE);
	m_ctlSpinParam21.SetRangeAndDelta (PARAM21_MIN, PARAM21_MAX, 1);

	// Param22
	m_ctlParam22.m_nPrecision = PARAM22_PRECISION;
	m_ctlParam22.SetRange(PARAM22_MIN,PARAM22_MAX);
	m_ctlParam22.SetTextColor(m_clrText);
	m_ctlParam22.SetBkColor(m_clrBack);
	m_ctlParam22.SetFont(m_pfont);
	m_ctlParam22.SetValuePtr(&m_VisSettings.Exposure_uS);
	m_ctlSpinParam22.SetDecimalPlaces (PARAM22_PRECISION);
	m_ctlSpinParam22.SetTrimTrailingZeros (FALSE);
	m_ctlSpinParam22.SetRangeAndDelta (PARAM22_MIN, PARAM22_MAX, 1);

	// Param23
	m_ctlParam23.m_nPrecision = PARAM23_PRECISION;
	m_ctlParam23.SetRange(PARAM23_MIN,PARAM23_MAX);
	m_ctlParam23.SetTextColor(m_clrText);
	m_ctlParam23.SetBkColor(m_clrBack);
	m_ctlParam23.SetFont(m_pfont);
	m_ctlParam23.SetValuePtr(&m_VisSettings.TriggerOn);
	m_ctlSpinParam23.SetDecimalPlaces (PARAM23_PRECISION);
	m_ctlSpinParam23.SetTrimTrailingZeros (FALSE);
	m_ctlSpinParam23.SetRangeAndDelta (PARAM23_MIN, PARAM23_MAX, 1);

	// Param24
	m_ctlParam24.m_nPrecision = PARAM24_PRECISION;
	m_ctlParam24.SetRange(PARAM24_MIN,PARAM24_MAX);
	m_ctlParam24.SetTextColor(m_clrText);
	m_ctlParam24.SetBkColor(m_clrBack);
	m_ctlParam24.SetFont(m_pfont);
	m_ctlParam24.SetValuePtr(&m_pSettings->dbPvars[PARAM24_PVARIABLE]);
	m_ctlSpinParam24.SetDecimalPlaces (PARAM24_PRECISION);
	m_ctlSpinParam24.SetTrimTrailingZeros (FALSE);
	m_ctlSpinParam24.SetRangeAndDelta (PARAM24_MIN, PARAM24_MAX, 1);

	// Param25
	m_ctlParam25.m_nPrecision = PARAM25_PRECISION;
	m_ctlParam25.SetRange(PARAM25_MIN,PARAM25_MAX);
	m_ctlParam25.SetTextColor(m_clrText);
	m_ctlParam25.SetBkColor(m_clrBack);
	m_ctlParam25.SetFont(m_pfont);
	m_ctlParam25.SetValuePtr(&m_VisSettings.GapDetectLatchCount);
	m_ctlSpinParam25.SetDecimalPlaces (PARAM25_PRECISION);
	m_ctlSpinParam25.SetTrimTrailingZeros (FALSE);
	m_ctlSpinParam25.SetRangeAndDelta (PARAM25_MIN, PARAM25_MAX, 1);
	
	return TRUE;  // return TRUE unless you set the focus to a control

}


void CVisionSplit::OnEnChangeParam()
{
	// Send change message
	if (m_pWndParent != NULL){
		m_pWndParent->SendMessage (WM_VISION_SETTINGS_CHANGED, 0, 0);		
	}
}
