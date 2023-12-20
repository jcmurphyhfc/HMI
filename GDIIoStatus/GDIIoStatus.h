#pragma once

// GDIIoStatus.h : main header file for GDIIoStatus.DLL

#if !defined( __AFXCTL_H__ )
#error "include 'afxctl.h' before including this file"
#endif

#include "resource.h"       // main symbols


// CGDIIoStatusApp : See GDIIoStatus.cpp for implementation.

class CGDIIoStatusApp : public COleControlModule
{
public:
	BOOL InitInstance();
	int ExitInstance();
};

extern const GUID CDECL _tlid;
extern const WORD _wVerMajor;
extern const WORD _wVerMinor;

