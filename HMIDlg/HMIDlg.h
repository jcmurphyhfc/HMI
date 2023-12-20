// HMIDlg.h : main header file for the HMIDlg DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CHMIDlgApp
// See HMIDlg.cpp for the implementation of this class
//

class CHMIDlgApp : public CWinApp
{
public:
	//DECLARE_GDI_PLUS;

	CHMIDlgApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
