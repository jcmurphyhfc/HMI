// TrimLUT.cpp : implementation file
//
#include "stdafx.h"
#include "HMIDlg.h"
#include "TrimLUT.h"

#define PARAM1_MIN             1
#define PARAM1_MAX          1024
#define PARAM1_PRECISION       0

#define PARAM2_MIN             1  
#define PARAM2_MAX          1024
#define PARAM2_PRECISION       0

#define PARAM3_MIN       -100000
#define PARAM3_MAX        100000
#define PARAM3_PRECISION       0

#define PARAM4_MIN       -100000
#define PARAM4_MAX        100000
#define PARAM4_PRECISION       0

#define PARAM5_MIN             0
#define PARAM5_MAX             1
#define PARAM5_PRECISION       0

// CTrimLUT dialog

IMPLEMENT_DYNAMIC(CTrimLUT, CPropertyPage)

CTrimLUT::CTrimLUT()
	: CPropertyPage(CTrimLUT::IDD)
{
    m_psp.dwFlags |= PSP_USEHICON;
    m_psp.dwFlags |= PSP_USETITLE;

	HICON hIconTab = AfxGetApp()->LoadIcon (IDI_ALIGNLUT);
    m_psp.hIcon = hIconTab;
	m_pWndParent = NULL;

}

CTrimLUT::~CTrimLUT()
{
}

void CTrimLUT::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_PARAM1, m_ctlParam1);
	DDX_Control(pDX, IDC_SPIN_PARAM1, m_ctlSpinParam1);
	DDX_Text(pDX, IDC_PARAM1, m_VisSettings.ImagePosX0);
	DDV_MinMaxDouble(pDX, m_VisSettings.ImagePosX0, PARAM1_MIN, PARAM1_MAX);

	DDX_Control(pDX, IDC_PARAM2, m_ctlParam2);
	DDX_Control(pDX, IDC_SPIN_PARAM2, m_ctlSpinParam2);
	DDX_Text(pDX, IDC_PARAM2, m_VisSettings.ImagePosX1);
	DDV_MinMaxDouble(pDX, m_VisSettings.ImagePosX1, PARAM2_MIN, PARAM2_MAX);

	DDX_Control(pDX, IDC_PARAM3, m_ctlParam3);
	DDX_Control(pDX, IDC_SPIN_PARAM3, m_ctlSpinParam3);
	DDX_Text(pDX, IDC_PARAM3, m_VisSettings.MotorPosY0);
	DDV_MinMaxDouble(pDX, m_VisSettings.MotorPosY0, PARAM3_MIN, PARAM3_MAX);

	DDX_Control(pDX, IDC_PARAM4, m_ctlParam4);
	DDX_Control(pDX, IDC_SPIN_PARAM4, m_ctlSpinParam4);
	DDX_Text(pDX, IDC_PARAM4, m_VisSettings.MotorPosY1);
	DDV_MinMaxDouble(pDX, m_VisSettings.MotorPosY1, PARAM4_MIN, PARAM4_MAX);

	DDX_Control(pDX, IDC_PARAM5, m_ctlParam5);
	DDX_Control(pDX, IDC_SPIN_PARAM5, m_ctlSpinParam5);
	DDX_Text(pDX, IDC_PARAM5, m_VisSettings.TrimModeEnable);
	DDV_MinMaxInt(pDX, m_VisSettings.TrimModeEnable, PARAM5_MIN, PARAM5_MAX);
	//DDV_MinMaxDouble(pDX, m_VisSettings.TrimModeEnable, PARAM5_MIN, PARAM5_MAX);
}


BEGIN_MESSAGE_MAP(CTrimLUT, CPropertyPage)
	ON_EN_CHANGE(IDC_PARAM1, &CTrimLUT::OnEnChangeParam)
	ON_EN_CHANGE(IDC_PARAM2, &CTrimLUT::OnEnChangeParam)
	ON_EN_CHANGE(IDC_PARAM3, &CTrimLUT::OnEnChangeParam)
	ON_EN_CHANGE(IDC_PARAM4, &CTrimLUT::OnEnChangeParam)
	ON_EN_CHANGE(IDC_PARAM5, &CTrimLUT::OnEnChangeParam)
	ON_BN_CLICKED(IDC_HELP_BTN, &CTrimLUT::OnBnClickedHelp)
END_MESSAGE_MAP()


// CTrimLUT message handlers
// CTrimLUT message handlers
BOOL CTrimLUT::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// Param1
	m_ctlParam1.m_nPrecision = PARAM1_PRECISION;
	m_ctlParam1.SetRange(PARAM1_MIN,PARAM1_MAX);
	m_ctlParam1.SetTextColor(m_clrText);
	m_ctlParam1.SetBkColor(m_clrBack);
	m_ctlParam1.SetFont(m_pfont);
	m_ctlParam1.SetValuePtr(&m_VisSettings.ImagePosX0);
	m_ctlSpinParam1.SetDecimalPlaces (PARAM1_PRECISION);
	m_ctlSpinParam1.SetTrimTrailingZeros (FALSE);
	m_ctlSpinParam1.SetRangeAndDelta (PARAM1_MIN, PARAM1_MAX, 1);

	// Param2
	m_ctlParam2.m_nPrecision = PARAM2_PRECISION;
	m_ctlParam2.SetRange(PARAM2_MIN,PARAM2_MAX);
	m_ctlParam2.SetTextColor(m_clrText);
	m_ctlParam2.SetBkColor(m_clrBack);
	m_ctlParam2.SetFont(m_pfont);
	m_ctlParam2.SetValuePtr(&m_VisSettings.ImagePosX1);
	m_ctlSpinParam2.SetDecimalPlaces (PARAM2_PRECISION);
	m_ctlSpinParam2.SetTrimTrailingZeros (FALSE);
	m_ctlSpinParam2.SetRangeAndDelta (PARAM2_MIN, PARAM2_MAX, 1);

	// Param3
	m_ctlParam3.m_nPrecision = PARAM3_PRECISION;
	m_ctlParam3.SetRange(PARAM3_MIN,PARAM3_MAX);
	m_ctlParam3.SetTextColor(m_clrText);
	m_ctlParam3.SetBkColor(m_clrBack);
	m_ctlParam3.SetFont(m_pfont);
	m_ctlParam3.SetValuePtr(&m_VisSettings.MotorPosY0);
	m_ctlSpinParam3.SetDecimalPlaces (PARAM3_PRECISION);
	m_ctlSpinParam3.SetTrimTrailingZeros (FALSE);
	m_ctlSpinParam3.SetRangeAndDelta (PARAM3_MIN, PARAM3_MAX, 1);
	// Param4
	m_ctlParam4.m_nPrecision = PARAM4_PRECISION;
	m_ctlParam4.SetRange(PARAM4_MIN,PARAM4_MAX);
	m_ctlParam4.SetTextColor(m_clrText);
	m_ctlParam4.SetBkColor(m_clrBack);
	m_ctlParam4.SetFont(m_pfont);
	m_ctlParam4.SetValuePtr(&m_VisSettings.MotorPosY1);
	m_ctlSpinParam4.SetDecimalPlaces (PARAM4_PRECISION);
	m_ctlSpinParam4.SetTrimTrailingZeros (FALSE);
	m_ctlSpinParam4.SetRangeAndDelta (PARAM4_MIN, PARAM4_MAX, 1);

	// Param5
	m_ctlParam5.m_nPrecision = PARAM5_PRECISION;
	m_ctlParam5.SetRange(PARAM5_MIN,PARAM5_MAX);
	m_ctlParam5.SetTextColor(m_clrText);
	m_ctlParam5.SetBkColor(m_clrBack);
	m_ctlParam5.SetFont(m_pfont);
	m_ctlParam5.SetValuePtr(&m_VisSettings.TrimModeEnable);
	m_ctlSpinParam5.SetDecimalPlaces (PARAM5_PRECISION);
	m_ctlSpinParam5.SetTrimTrailingZeros (FALSE);
	m_ctlSpinParam5.SetRangeAndDelta (PARAM5_MIN, PARAM5_MAX, 1);

	return TRUE;  // return TRUE unless you set the focus to a control

}


void CTrimLUT::OnEnChangeParam()
{
	// Send change message
	if (m_pWndParent != NULL){
		m_pWndParent->SendMessage (WM_VISION_SETTINGS_CHANGED, 0, 0);		
	}
}


void CTrimLUT::OnBnClickedHelp()
{
	// TODO: Add your control notification handler code here
	//
	MessageBox(_T("This table is used calibrate the Trim Mode alignment by mapping images positions to motor positions. Image position X0 will produce motor position Y0. Image positions between X0 and X1 are interpolated between motor positions Y0 and Y1. This table must be setup to align the bacon with Cut-To-Lenght On."),_T("LUT Help"));
}
