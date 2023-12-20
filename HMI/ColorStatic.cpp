// ColorStatic.cpp : implementation file
//

#include "stdafx.h"
#include "HMI.h"
#include "ColorStatic.h"


// CColorStatic

IMPLEMENT_DYNAMIC(CColorStatic, CStatic)

CColorStatic::CColorStatic()
{
	 m_brRedBrush.CreateSolidBrush (RGB (0, 0, 0));
}

CColorStatic::~CColorStatic()
{
}


BEGIN_MESSAGE_MAP(CColorStatic, CStatic)
	ON_WM_CTLCOLOR_REFLECT ()
END_MESSAGE_MAP()


// CColorStatic message handlers
HBRUSH CColorStatic::CtlColor (CDC* pDC, UINT nCtlColor)
{
    pDC->SetTextColor (RGB (0, 255, 255));
    pDC->SetBkColor (RGB (0, 0, 0));
    return (HBRUSH) m_brRedBrush;
}


