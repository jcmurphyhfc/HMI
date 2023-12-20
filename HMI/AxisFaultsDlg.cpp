// AxisFaultsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HMI.h"
#include "AxisFaultsDlg.h"
#include "afxdialogex.h"


// CAxisFaultsDlg dialog

IMPLEMENT_DYNAMIC(CAxisFaultsDlg, CDialog)

CAxisFaultsDlg::CAxisFaultsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAxisFaultsDlg::IDD, pParent)
{

}

CAxisFaultsDlg::~CAxisFaultsDlg()
{
}

void CAxisFaultsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAxisFaultsDlg, CDialog)
END_MESSAGE_MAP()


// CAxisFaultsDlg message handlers
