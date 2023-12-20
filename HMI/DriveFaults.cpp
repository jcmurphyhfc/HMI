// DriveFaults.cpp : implementation file
//

#include "stdafx.h"
#include "HMI.h"
#include "DriveFaults.h"
#include "afxdialogex.h"


// CDriveFaults dialog

IMPLEMENT_DYNAMIC(CDriveFaults, CDialog)

CDriveFaults::CDriveFaults(CWnd* pParent /*=NULL*/)
	: CDialog(CDriveFaults::IDD, pParent)
{

}

CDriveFaults::~CDriveFaults()
{
}

void CDriveFaults::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDriveFaults, CDialog)
END_MESSAGE_MAP()


// CDriveFaults message handlers
