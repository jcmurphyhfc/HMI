// VisSetDelay.cpp : implementation file
//

#include "stdafx.h"
#include "HMIDlg.h"
#include "VisSetDelay.h"

#define PARAM1_MIN             1
#define PARAM1_MAX          2000
#define PARAM1_PRECISION       0

#define PARAM2_MIN             1
#define PARAM2_MAX          2000
#define PARAM2_PRECISION       0

#define PARAM3_MIN             1
#define PARAM3_MAX          2000
#define PARAM3_PRECISION       0

#define PARAM4_MIN             1
#define PARAM4_MAX          2000
#define PARAM4_PRECISION       0

#define PARAM5_MIN             1
#define PARAM5_MAX          2000
#define PARAM5_PRECISION       0

#define PARAM6_MIN             1
#define PARAM6_MAX          2000
#define PARAM6_PRECISION       0

#define PARAM7_MIN             1
#define PARAM7_MAX          2000
#define PARAM7_PRECISION       0

#define PARAM8_MIN             1
#define PARAM8_MAX          2000
#define PARAM8_PRECISION       0

#define PARAM9_MIN             1
#define PARAM9_MAX          1024
#define PARAM9_PRECISION       0

// CVisSetDelay dialog

IMPLEMENT_DYNAMIC(CVisSetDelay, CPropertyPage)

CVisSetDelay::CVisSetDelay()
	: CPropertyPage(CVisSetDelay::IDD)
{
    m_psp.dwFlags |= PSP_USEHICON;
    m_psp.dwFlags |= PSP_USETITLE;

	HICON hIconTab = AfxGetApp()->LoadIcon (IDI_SPLIT);
    m_psp.hIcon = hIconTab;
	m_pWndParent = NULL;

}

CVisSetDelay::~CVisSetDelay()
{
}

void CVisSetDelay::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_PARAM1, m_ctlParam1);
	DDX_Control(pDX, IDC_SPIN_PARAM1, m_ctlSpinParam1);
	DDX_Text(pDX, IDC_PARAM1, m_VisSettings.OffsetLane1);
	DDV_MinMaxDouble(pDX, m_VisSettings.OffsetLane1, PARAM1_MIN, PARAM1_MAX);

	DDX_Control(pDX, IDC_PARAM2, m_ctlParam2);
	DDX_Control(pDX, IDC_SPIN_PARAM2, m_ctlSpinParam2);
	DDX_Text(pDX, IDC_PARAM2, m_VisSettings.OffsetLane2);
	DDV_MinMaxDouble(pDX, m_VisSettings.OffsetLane2, PARAM2_MIN, PARAM2_MAX);

	DDX_Control(pDX, IDC_PARAM3, m_ctlParam3);
	DDX_Control(pDX, IDC_SPIN_PARAM3, m_ctlSpinParam3);
	DDX_Text(pDX, IDC_PARAM3, m_VisSettings.OffsetLane3);
	DDV_MinMaxDouble(pDX, m_VisSettings.OffsetLane3, PARAM3_MIN, PARAM3_MAX);

	DDX_Control(pDX, IDC_PARAM4, m_ctlParam4);
	DDX_Control(pDX, IDC_SPIN_PARAM4, m_ctlSpinParam4);
	DDX_Text(pDX, IDC_PARAM4, m_VisSettings.OffsetLane4);
	DDV_MinMaxDouble(pDX, m_VisSettings.OffsetLane4, PARAM4_MIN, PARAM4_MAX);

	DDX_Control(pDX, IDC_PARAM5, m_ctlParam5);
	DDX_Control(pDX, IDC_SPIN_PARAM5, m_ctlSpinParam5);
	DDX_Text(pDX, IDC_PARAM5, m_VisSettings.OffsetLane5);
	DDV_MinMaxDouble(pDX, m_VisSettings.OffsetLane5, PARAM5_MIN, PARAM5_MAX);

	DDX_Control(pDX, IDC_PARAM6, m_ctlParam6);
	DDX_Control(pDX, IDC_SPIN_PARAM6, m_ctlSpinParam6);
	DDX_Text(pDX, IDC_PARAM6, m_VisSettings.OffsetLane6);
	DDV_MinMaxDouble(pDX, m_VisSettings.OffsetLane6, PARAM6_MIN, PARAM6_MAX);

	DDX_Control(pDX, IDC_PARAM7, m_ctlParam7);
	DDX_Control(pDX, IDC_SPIN_PARAM7, m_ctlSpinParam7);
	DDX_Text(pDX, IDC_PARAM7, m_VisSettings.OffsetLane7);
	DDV_MinMaxDouble(pDX, m_VisSettings.OffsetLane7, PARAM7_MIN, PARAM7_MAX);

	DDX_Control(pDX, IDC_PARAM8, m_ctlParam8);
	DDX_Control(pDX, IDC_SPIN_PARAM8, m_ctlSpinParam8);
	DDX_Text(pDX, IDC_PARAM8, m_VisSettings.OffsetLane8);
	DDV_MinMaxDouble(pDX, m_VisSettings.OffsetLane8, PARAM8_MIN, PARAM8_MAX);

	DDX_Control(pDX, IDC_PARAM9, m_ctlParam9);
	DDX_Control(pDX, IDC_SPIN_PARAM9, m_ctlSpinParam9);
	DDX_Text(pDX, IDC_PARAM9, m_VisSettings.PosLane1);
	DDV_MinMaxDouble(pDX, m_VisSettings.PosLane1, PARAM9_MIN, PARAM9_MAX);

	DDX_Control(pDX, IDC_PARAM10, m_ctlParam10);
	DDX_Control(pDX, IDC_SPIN_PARAM10, m_ctlSpinParam10);
	DDX_Text(pDX, IDC_PARAM10, m_VisSettings.PosLane2);
	DDV_MinMaxDouble(pDX, m_VisSettings.PosLane2, PARAM9_MIN, PARAM9_MAX);

	DDX_Control(pDX, IDC_PARAM11, m_ctlParam11);
	DDX_Control(pDX, IDC_SPIN_PARAM11, m_ctlSpinParam11);
	DDX_Text(pDX, IDC_PARAM11, m_VisSettings.PosLane3);
	DDV_MinMaxDouble(pDX, m_VisSettings.PosLane3, PARAM9_MIN, PARAM9_MAX);

	DDX_Control(pDX, IDC_PARAM12, m_ctlParam12);
	DDX_Control(pDX, IDC_SPIN_PARAM12, m_ctlSpinParam12);
	DDX_Text(pDX, IDC_PARAM12, m_VisSettings.PosLane4);
	DDV_MinMaxDouble(pDX, m_VisSettings.PosLane4, PARAM9_MIN, PARAM9_MAX);

	DDX_Control(pDX, IDC_PARAM13, m_ctlParam13);
	DDX_Control(pDX, IDC_SPIN_PARAM13, m_ctlSpinParam13);
	DDX_Text(pDX, IDC_PARAM13, m_VisSettings.PosLane5);
	DDV_MinMaxDouble(pDX, m_VisSettings.PosLane5, PARAM9_MIN, PARAM9_MAX);

	DDX_Control(pDX, IDC_PARAM14, m_ctlParam14);
	DDX_Control(pDX, IDC_SPIN_PARAM14, m_ctlSpinParam14);
	DDX_Text(pDX, IDC_PARAM14, m_VisSettings.PosLane6);
	DDV_MinMaxDouble(pDX, m_VisSettings.PosLane6, PARAM9_MIN, PARAM9_MAX);

	DDX_Control(pDX, IDC_PARAM15, m_ctlParam15);
	DDX_Control(pDX, IDC_SPIN_PARAM15, m_ctlSpinParam15);
	DDX_Text(pDX, IDC_PARAM15, m_VisSettings.PosLane7);
	DDV_MinMaxDouble(pDX, m_VisSettings.PosLane7, PARAM9_MIN, PARAM9_MAX);
}

BEGIN_MESSAGE_MAP(CVisSetDelay, CPropertyPage)
	ON_EN_CHANGE(IDC_PARAM1, &CVisSetDelay::OnEnChangeParam)
	ON_EN_CHANGE(IDC_PARAM2, &CVisSetDelay::OnEnChangeParam)
	ON_EN_CHANGE(IDC_PARAM3, &CVisSetDelay::OnEnChangeParam)
	ON_EN_CHANGE(IDC_PARAM4, &CVisSetDelay::OnEnChangeParam)
	ON_EN_CHANGE(IDC_PARAM5, &CVisSetDelay::OnEnChangeParam)
	ON_EN_CHANGE(IDC_PARAM6, &CVisSetDelay::OnEnChangeParam)
	ON_EN_CHANGE(IDC_PARAM7, &CVisSetDelay::OnEnChangeParam)
	ON_EN_CHANGE(IDC_PARAM8, &CVisSetDelay::OnEnChangeParam)
	ON_EN_CHANGE(IDC_PARAM9, &CVisSetDelay::OnEnChangeParam)
	ON_EN_CHANGE(IDC_PARAM10, &CVisSetDelay::OnEnChangeParam)
	ON_EN_CHANGE(IDC_PARAM11, &CVisSetDelay::OnEnChangeParam)
	ON_EN_CHANGE(IDC_PARAM12, &CVisSetDelay::OnEnChangeParam)
	ON_EN_CHANGE(IDC_PARAM13, &CVisSetDelay::OnEnChangeParam)
	ON_EN_CHANGE(IDC_PARAM14, &CVisSetDelay::OnEnChangeParam)
	ON_EN_CHANGE(IDC_PARAM15, &CVisSetDelay::OnEnChangeParam)
END_MESSAGE_MAP()

// CVisSetDelay message handlers
// CVisionSplit message handlers
// CVisionSplit message handlers
BOOL CVisSetDelay::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// Param1
	m_ctlParam1.m_nPrecision = PARAM1_PRECISION;
	m_ctlParam1.SetRange(PARAM1_MIN,PARAM1_MAX);
	m_ctlParam1.SetTextColor(m_clrText);
	m_ctlParam1.SetBkColor(m_clrBack);
	m_ctlParam1.SetFont(m_pfont);
	m_ctlParam1.SetValuePtr(&m_VisSettings.OffsetLane1);
	m_ctlSpinParam1.SetDecimalPlaces (PARAM1_PRECISION);
	m_ctlSpinParam1.SetTrimTrailingZeros (FALSE);
	m_ctlSpinParam1.SetRangeAndDelta (PARAM1_MIN, PARAM1_MAX, 1);

	// Param2
	m_ctlParam2.m_nPrecision = PARAM2_PRECISION;
	m_ctlParam2.SetRange(PARAM2_MIN,PARAM2_MAX);
	m_ctlParam2.SetTextColor(m_clrText);
	m_ctlParam2.SetBkColor(m_clrBack);
	m_ctlParam2.SetFont(m_pfont);
	m_ctlParam2.SetValuePtr(&m_VisSettings.OffsetLane2);
	m_ctlSpinParam2.SetDecimalPlaces (PARAM2_PRECISION);
	m_ctlSpinParam2.SetTrimTrailingZeros (FALSE);
	m_ctlSpinParam2.SetRangeAndDelta (PARAM2_MIN, PARAM2_MAX, 1);

	// Param3
	m_ctlParam3.m_nPrecision = PARAM3_PRECISION;
	m_ctlParam3.SetRange(PARAM3_MIN,PARAM3_MAX);
	m_ctlParam3.SetTextColor(m_clrText);
	m_ctlParam3.SetBkColor(m_clrBack);
	m_ctlParam3.SetFont(m_pfont);
	m_ctlParam3.SetValuePtr(&m_VisSettings.OffsetLane3);
	m_ctlSpinParam3.SetDecimalPlaces (PARAM3_PRECISION);
	m_ctlSpinParam3.SetTrimTrailingZeros (FALSE);
	m_ctlSpinParam3.SetRangeAndDelta (PARAM3_MIN, PARAM3_MAX, 1);
	// Param4
	m_ctlParam4.m_nPrecision = PARAM4_PRECISION;
	m_ctlParam4.SetRange(PARAM4_MIN,PARAM4_MAX);
	m_ctlParam4.SetTextColor(m_clrText);
	m_ctlParam4.SetBkColor(m_clrBack);
	m_ctlParam4.SetFont(m_pfont);
	m_ctlParam4.SetValuePtr(&m_VisSettings.OffsetLane4);
	m_ctlSpinParam4.SetDecimalPlaces (PARAM4_PRECISION);
	m_ctlSpinParam4.SetTrimTrailingZeros (FALSE);
	m_ctlSpinParam4.SetRangeAndDelta (PARAM4_MIN, PARAM4_MAX, 1);

	// Param5
	m_ctlParam5.m_nPrecision = PARAM5_PRECISION;
	m_ctlParam5.SetRange(PARAM5_MIN,PARAM5_MAX);
	m_ctlParam5.SetTextColor(m_clrText);
	m_ctlParam5.SetBkColor(m_clrBack);
	m_ctlParam5.SetFont(m_pfont);
	m_ctlParam5.SetValuePtr(&m_VisSettings.OffsetLane5);
	m_ctlSpinParam5.SetDecimalPlaces (PARAM5_PRECISION);
	m_ctlSpinParam5.SetTrimTrailingZeros (FALSE);
	m_ctlSpinParam5.SetRangeAndDelta (PARAM5_MIN, PARAM5_MAX, 1);

	// Param6
	m_ctlParam6.m_nPrecision = PARAM6_PRECISION;
	m_ctlParam6.SetRange(PARAM6_MIN,PARAM6_MAX);
	m_ctlParam6.SetTextColor(m_clrText);
	m_ctlParam6.SetBkColor(m_clrBack);
	m_ctlParam6.SetFont(m_pfont);
	m_ctlParam6.SetValuePtr(&m_VisSettings.OffsetLane6);
	m_ctlSpinParam6.SetDecimalPlaces (PARAM6_PRECISION);
	m_ctlSpinParam6.SetTrimTrailingZeros (FALSE);
	m_ctlSpinParam6.SetRangeAndDelta (PARAM6_MIN, PARAM6_MAX, 1);

	// Param7
	m_ctlParam7.m_nPrecision = PARAM7_PRECISION;
	m_ctlParam7.SetRange(PARAM7_MIN,PARAM7_MAX);
	m_ctlParam7.SetTextColor(m_clrText);
	m_ctlParam7.SetBkColor(m_clrBack);
	m_ctlParam7.SetFont(m_pfont);
	m_ctlParam7.SetValuePtr(&m_VisSettings.OffsetLane7);
	m_ctlSpinParam7.SetDecimalPlaces (PARAM7_PRECISION);
	m_ctlSpinParam7.SetTrimTrailingZeros (FALSE);
	m_ctlSpinParam7.SetRangeAndDelta (PARAM7_MIN, PARAM7_MAX, 1);

	// Param8
	m_ctlParam8.m_nPrecision = PARAM8_PRECISION;
	m_ctlParam8.SetRange(PARAM8_MIN,PARAM8_MAX);
	m_ctlParam8.SetTextColor(m_clrText);
	m_ctlParam8.SetBkColor(m_clrBack);
	m_ctlParam8.SetFont(m_pfont);
	m_ctlParam8.SetValuePtr(&m_VisSettings.OffsetLane8);
	m_ctlSpinParam8.SetDecimalPlaces (PARAM8_PRECISION);
	m_ctlSpinParam8.SetTrimTrailingZeros (FALSE);
	m_ctlSpinParam8.SetRangeAndDelta (PARAM8_MIN, PARAM8_MAX, 1);

	// Param9
	m_ctlParam9.m_nPrecision = PARAM9_PRECISION;
	m_ctlParam9.SetRange(PARAM9_MIN,PARAM9_MAX);
	m_ctlParam9.SetTextColor(m_clrText);
	m_ctlParam9.SetBkColor(m_clrBack);
	m_ctlParam9.SetFont(m_pfont);
	m_ctlParam9.SetValuePtr(&m_VisSettings.PosLane1);
	m_ctlSpinParam9.SetDecimalPlaces (PARAM9_PRECISION);
	m_ctlSpinParam9.SetTrimTrailingZeros (FALSE);
	m_ctlSpinParam9.SetRangeAndDelta (PARAM9_MIN, PARAM9_MAX, 1);

	// Param10
	m_ctlParam10.m_nPrecision = PARAM9_PRECISION;
	m_ctlParam10.SetRange(PARAM9_MIN,PARAM9_MAX);
	m_ctlParam10.SetTextColor(m_clrText);
	m_ctlParam10.SetBkColor(m_clrBack);
	m_ctlParam10.SetFont(m_pfont);
	m_ctlParam10.SetValuePtr(&m_VisSettings.PosLane2);
	m_ctlSpinParam10.SetDecimalPlaces (PARAM9_PRECISION);
	m_ctlSpinParam10.SetTrimTrailingZeros (FALSE);
	m_ctlSpinParam10.SetRangeAndDelta (PARAM9_MIN, PARAM9_MAX, 1);

	// Param11
	m_ctlParam11.m_nPrecision = PARAM9_PRECISION;
	m_ctlParam11.SetRange(PARAM9_MIN,PARAM9_MAX);
	m_ctlParam11.SetTextColor(m_clrText);
	m_ctlParam11.SetBkColor(m_clrBack);
	m_ctlParam11.SetFont(m_pfont);
	m_ctlParam11.SetValuePtr(&m_VisSettings.PosLane3);
	m_ctlSpinParam11.SetDecimalPlaces (PARAM9_PRECISION);
	m_ctlSpinParam11.SetTrimTrailingZeros (FALSE);
	m_ctlSpinParam11.SetRangeAndDelta (PARAM9_MIN, PARAM9_MAX, 1);

	// Param12
	m_ctlParam12.m_nPrecision = PARAM9_PRECISION;
	m_ctlParam12.SetRange(PARAM9_MIN,PARAM9_MAX);
	m_ctlParam12.SetTextColor(m_clrText);
	m_ctlParam12.SetBkColor(m_clrBack);
	m_ctlParam12.SetFont(m_pfont);
	m_ctlParam12.SetValuePtr(&m_VisSettings.PosLane4);
	m_ctlSpinParam12.SetDecimalPlaces (PARAM9_PRECISION);
	m_ctlSpinParam12.SetTrimTrailingZeros (FALSE);
	m_ctlSpinParam12.SetRangeAndDelta (PARAM9_MIN, PARAM9_MAX, 1);

	// Param13
	m_ctlParam13.m_nPrecision = PARAM9_PRECISION;
	m_ctlParam13.SetRange(PARAM9_MIN,PARAM9_MAX);
	m_ctlParam13.SetTextColor(m_clrText);
	m_ctlParam13.SetBkColor(m_clrBack);
	m_ctlParam13.SetFont(m_pfont);
	m_ctlParam13.SetValuePtr(&m_VisSettings.PosLane5);
	m_ctlSpinParam13.SetDecimalPlaces (PARAM9_PRECISION);
	m_ctlSpinParam13.SetTrimTrailingZeros (FALSE);
	m_ctlSpinParam13.SetRangeAndDelta (PARAM9_MIN, PARAM9_MAX, 1);

	// Param14
	m_ctlParam14.m_nPrecision = PARAM9_PRECISION;
	m_ctlParam14.SetRange(PARAM9_MIN,PARAM9_MAX);
	m_ctlParam14.SetTextColor(m_clrText);
	m_ctlParam14.SetBkColor(m_clrBack);
	m_ctlParam14.SetFont(m_pfont);
	m_ctlParam14.SetValuePtr(&m_VisSettings.PosLane6);
	m_ctlSpinParam14.SetDecimalPlaces (PARAM9_PRECISION);
	m_ctlSpinParam14.SetTrimTrailingZeros (FALSE);
	m_ctlSpinParam14.SetRangeAndDelta (PARAM9_MIN, PARAM9_MAX, 1);

	// Param15
	m_ctlParam15.m_nPrecision = PARAM9_PRECISION;
	m_ctlParam15.SetRange(PARAM9_MIN,PARAM9_MAX);
	m_ctlParam15.SetTextColor(m_clrText);
	m_ctlParam15.SetBkColor(m_clrBack);
	m_ctlParam15.SetFont(m_pfont);
	m_ctlParam15.SetValuePtr(&m_VisSettings.PosLane7);
	m_ctlSpinParam15.SetDecimalPlaces (PARAM9_PRECISION);
	m_ctlSpinParam15.SetTrimTrailingZeros (FALSE);
	m_ctlSpinParam15.SetRangeAndDelta (PARAM9_MIN, PARAM9_MAX, 1);

	return TRUE;  // return TRUE unless you set the focus to a control

}


void CVisSetDelay::OnEnChangeParam()
{
	// Send change message
	if (m_pWndParent != NULL){
		m_pWndParent->SendMessage (WM_VISION_SETTINGS_CHANGED, 0, 0);		
	}
}
