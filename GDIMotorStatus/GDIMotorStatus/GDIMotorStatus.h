#pragma once

// GDIMotorStatus.h : main header file for GDIMotorStatus.DLL

#if !defined( __AFXCTL_H__ )
#error "include 'afxctl.h' before including this file"
#endif

#include "resource.h"       // main symbols


// CGDIMotorStatusApp : See GDIMotorStatus.cpp for implementation.

class CGDIMotorStatusApp : public COleControlModule
{
public:
	BOOL InitInstance();
	int ExitInstance();
};

extern const GUID CDECL _tlid;
extern const WORD _wVerMajor;
extern const WORD _wVerMinor;

