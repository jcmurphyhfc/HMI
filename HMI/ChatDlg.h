#pragma once
//#include "MyChatWnd.h"
#include <winsock.h>                 // Socket includes

#define WM_DO_DIALOG_UPDATE         WM_USER+0x101

// CChatDlg dialog

class CChatDlg : public CDialog
{
	DECLARE_DYNAMIC(CChatDlg)

public:
	CChatDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CChatDlg();
// Dialog Data
	enum { IDD = IDD_CHATDLG };
	SOCKET t_sock;
	HWND* m_pHwnd;
	HWND m_hOSKWnd;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedSend();
	afx_msg LRESULT OnDoDialogUpdate (WPARAM wParam, LPARAM lParam);

protected:
	virtual void PostNcDestroy();
public:
	CString m_strSend;
	afx_msg void OnEnChangeEditSend();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButtonDn();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

// The CUIThread class
class CUIThread : public CWinThread
{
    DECLARE_DYNCREATE (CUIThread)

public:
	//int m_nDataVal;
	SOCKET t_sock;
	HWND m_hWndMessage;
    virtual BOOL InitInstance ();
	void CloseChat(void);
	virtual int ExitInstance();
};
