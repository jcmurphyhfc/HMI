#pragma once


// CYesNo dialog

class CYesNo : public CDialog
{
	DECLARE_DYNAMIC(CYesNo)

public:
	CYesNo(CWnd* pParent = NULL);   // standard constructor
	virtual ~CYesNo();

// Dialog Data
	enum { IDD = IDD_DLG_YESNO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CString m_strMsg;

private:
	CFont m_font;

};
