#pragma once


// CGetName dialog

class CGetName : public CDialog
{
	DECLARE_DYNAMIC(CGetName)

public:
	CGetName(CWnd* pParent = NULL);   // standard constructor
	virtual ~CGetName();

// Dialog Data
	enum { IDD = IDD_GETNAME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString m_strName;
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnInitDialog();
};
