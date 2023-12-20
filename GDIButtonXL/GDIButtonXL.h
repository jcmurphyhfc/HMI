#pragma once

// GDIButtonXL.h : main header file for GDIButtonXL.DLL

#if !defined( __AFXCTL_H__ )
#error "include 'afxctl.h' before including this file"
#endif

#include "resource.h"       // main symbols


// CGDIButtonXLApp : See GDIButtonXL.cpp for implementation.

class CGDIButtonXLApp : public COleControlModule
{
public:
	BOOL InitInstance();
	int ExitInstance();

	//GdiplusStartupInput m_gdiplusStartupInput;
	//ULONG_PTR m_gdiplusToken;

};

extern const GUID CDECL _tlid;
extern const WORD _wVerMajor;
extern const WORD _wVerMinor;

