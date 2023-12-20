#pragma once

// CDlgOk dialog

class CDlgOk : public CDialog
{
	DECLARE_DYNAMIC(CDlgOk)

public:
	CDlgOk(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgOk();

// Members
public:
	bool m_bXOk;
	CString m_strMsg;

// Dialog Data
	enum { IDD = IDD_DLG_OK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
