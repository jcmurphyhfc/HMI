#pragma once


// CDriveFaults dialog

class CDriveFaults : public CDialog
{
	DECLARE_DYNAMIC(CDriveFaults)

public:
	CDriveFaults(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDriveFaults();

// Dialog Data
	enum { IDD = IDD_DRIVE_FAULTS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
