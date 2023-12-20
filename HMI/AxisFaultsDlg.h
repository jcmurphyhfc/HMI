#pragma once


// CAxisFaultsDlg dialog

class CAxisFaultsDlg : public CDialog
{
	DECLARE_DYNAMIC(CAxisFaultsDlg)

public:
	CAxisFaultsDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAxisFaultsDlg();

// Dialog Data
	enum { IDD = IDD_AXIS_FAULTS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
