#pragma once


// CColorStatic

class CColorStatic : public CStatic
{
	DECLARE_DYNAMIC(CColorStatic)

public:
	CColorStatic();
	virtual ~CColorStatic();

protected:
    CBrush m_brRedBrush;
    afx_msg HBRUSH CtlColor (CDC* pDC, UINT nCtlColor);
	DECLARE_MESSAGE_MAP()
};
