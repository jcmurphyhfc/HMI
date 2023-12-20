// UploadDownload.cpp : implementation file
//

#include "stdafx.h"
#include "HMI.h"
#include "UploadDownload.h"


// CUploadDownload dialog

IMPLEMENT_DYNAMIC(CUploadDownload, CDialog)

CUploadDownload::CUploadDownload(CWnd* pParent /*=NULL*/)
	: CDialog(CUploadDownload::IDD, pParent)
{

}

CUploadDownload::~CUploadDownload()
{
}

void CUploadDownload::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS1, m_ctlProgress);
	DDX_Control(pDX, IDC_EDIT_RESPONSE, m_ctlEdit);
}


BEGIN_MESSAGE_MAP(CUploadDownload, CDialog)
	ON_MESSAGE (MSG_PMAC_DWONLOAD, OnPmacDownload)
	ON_MESSAGE (MSG_PMAC_PROGRESS, OnPmacProgress)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CUploadDownload::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_UPLOAD_DOWNLOAD, &CUploadDownload::OnBnClickedUploadDownload)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CUploadDownload message handlers


BOOL CUploadDownload::OnInitDialog()
{
	CWnd* pWnd;
	CDialog::OnInitDialog();

	m_ctlProgress.SetRange32(0,99);
	m_ctlProgress.SetPos(0);
	m_pmac->SetDownloadMsgPtr(&m_ctlEdit);
	m_pmac->SetProgressMsgPtr(&m_ctlProgress);

	if (m_Upload)
	{
		pWnd = GetDlgItem(IDC_EDIT_RESPONSE);
		pWnd->SetWindowText(_T("This operaton will backup the entire GeoBrick \r\ndrive and replace the file D:\\BTCDATA\\BACKUP\\FULLBACK.CFG\r\nMake sure the machine is disabled before you continue."));
		pWnd = GetDlgItem(IDC_UPLOAD_DOWNLOAD);
		pWnd->SetWindowText(_T("Upload Full Drive Configuration"));
		pWnd = GetDlgItem(IDC_BUTTON_SAVE);
		pWnd->ModifyStyle (WS_VISIBLE, 0);

	}
	else
	{
		pWnd = GetDlgItem(IDC_EDIT_RESPONSE);
		pWnd->SetWindowText(_T("This operaton will load the GeoBrick \r\ndrive with file D:\\BTCDATA\\BACKUP\\FULLBACK.CFG\r\nMake sure the machine is disabled before you continue."));
		pWnd = GetDlgItem(IDC_UPLOAD_DOWNLOAD);
		pWnd->SetWindowText(_T("Download Full Drive Configuration"));
	}

	return TRUE;  // return TRUE unless you set the focus to a control
}


void CUploadDownload::OnBnClickedButtonSave()
{
}


void CUploadDownload::OnBnClickedUploadDownload()
{
	// Upload Full Drive Configuration
	if (m_Upload)
	{
		//_T ("D:\\BTCDATA\\UpLoadFile.CFG")
		if (YesNoDlg(_T("Upload full drive configuration?")))
		{			
			CWnd* pWnd = GetDlgItem(IDOK);
			pWnd->EnableWindow(0);
			m_pmac->SetVariable(_T('I'),5,(long)0);
			m_params.Upload = true;
			m_params.Complete = false;

			// Start the helper thread
			CWinThread* pThread = AfxBeginThread (UploadThreadFunc, &m_params,THREAD_PRIORITY_NORMAL,CREATE_SUSPENDED);
			pThread->ResumeThread();
			SetTimer(1,250,NULL);

		}


	}
	// Download Full Drive Configuration
	else
	{
		//_T ("D:\\BTCDATA\\UpLoadFile.CFG")
		if (YesNoDlg(_T("Download full drive configuration?")))
		{			
			CWnd* pWnd = GetDlgItem(IDOK);
			pWnd->EnableWindow(0);
			m_pmac->SetVariable(_T('I'),5,(long)0);
			m_params.Upload = false;
			m_params.Complete = false;

			// Start the helper thread
			CWinThread* pThread = AfxBeginThread (UploadThreadFunc, &m_params,THREAD_PRIORITY_NORMAL,CREATE_SUSPENDED);
			pThread->ResumeThread();
			SetTimer(1,250,NULL);

		}
		
	}

}

LRESULT CUploadDownload::OnPmacDownload (WPARAM wParam, LPARAM lParam)
{
	return 0;
}

LRESULT CUploadDownload::OnPmacProgress (WPARAM wParam, LPARAM lParam)
{
	return 0;
}

//======================================================================================================//
// Function Name: UploadThreadFunc (LPVOID pParam)                                                      //
//                                                                                                      //
//======================================================================================================//
UINT UploadThreadFunc (LPVOID pParam)                                                                      
{            
	UPDNHELPER* pData = (UPDNHELPER*)pParam;

	CPmac pmac;
	pmac.Init(0);

	if (pData->Upload)
	{
		TRACE("Upload \n");
		pmac.Upload(_T ("D:\\BTCDATA\\BACKUP\\FULLBACK.CFG"));
	}
	else
	{
		TRACE("Download \n");
		pmac.Download(_T ("D:\\BTCDATA\\BACKUP\\FULLBACK.CFG"));
	}
	pData->Complete = true;

	return 0;                                                                                                       
}

void CUploadDownload::OnTimer(UINT_PTR nIDEvent)
{
	//CDialog::OnTimer(nIDEvent);
	TRACE("OnTimer \n");
	// Wait
	if (m_params.Complete==true)
	{
		m_params.Complete = false;
		CWnd* pWnd = GetDlgItem(IDOK);
		pWnd->EnableWindow(1);
		m_pmac->SetVariable(_T('I'),5,(long)2);
		m_pmac->SendCommand(_T("ENABLE PLC1"));
		TRACE("Complete............. \n");
		m_ctlProgress.SetPos(99);
		KillTimer(1);
	}

}
