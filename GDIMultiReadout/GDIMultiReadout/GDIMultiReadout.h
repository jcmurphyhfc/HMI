#pragma once

// GDIMultiReadout.h : main header file for GDIMultiReadout.DLL

#if !defined( __AFXCTL_H__ )
#error "include 'afxctl.h' before including this file"
#endif

#include "resource.h"       // main symbols


// CGDIMultiReadoutApp : See GDIMultiReadout.cpp for implementation.

class CGDIMultiReadoutApp : public COleControlModule
{
public:
	BOOL InitInstance();
	int ExitInstance();
};

extern const GUID CDECL _tlid;
extern const WORD _wVerMajor;
extern const WORD _wVerMinor;

