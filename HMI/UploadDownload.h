#pragma once
#include "afxcmn.h"
#include "afxwin.h"

#define MSG_PMAC_DWONLOAD    WM_USER+0x101
#define MSG_PMAC_PROGRESS    WM_USER+0x102

// User's thread function hook data structure. 
typedef struct tagUPDNHELPER{
	bool Upload;
	bool Complete;
} UPDNHELPER;

// CUploadDownload dialog
static UINT UploadThreadFunc (LPVOID);

class CUploadDownload : public CDialog
{
	DECLARE_DYNAMIC(CUploadDownload)

public:
	CUploadDownload(CWnd* pParent = NULL);   // standard constructor
	virtual ~CUploadDownload();

// Members
public:
	UPDNHELPER m_params;
	CPmac*  m_pmac;
	bool    m_Upload;
	afx_msg LRESULT OnPmacDownload (WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnPmacProgress (WPARAM wParam, LPARAM lParam);



// Dialog Data
	enum { IDD = IDD_UPLOAD_DOWNLOAD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedUploadDownload();
	CProgressCtrl m_ctlProgress;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CEdit m_ctlEdit;
};
