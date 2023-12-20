// GDIMotorStatus.cpp : Implementation of CGDIMotorStatusApp and DLL registration.

#include "stdafx.h"
#include "GDIMotorStatus.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CGDIMotorStatusApp theApp;

const GUID CDECL _tlid = { 0x8F88BE82, 0xB38D, 0x46D0, { 0x8C, 0x56, 0x7E, 0x39, 0x2C, 0x3C, 0xAC, 0xC5 } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;



// CGDIMotorStatusApp::InitInstance - DLL initialization

BOOL CGDIMotorStatusApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO: Add your own module initialization code here.
	}

	return bInit;
}



// CGDIMotorStatusApp::ExitInstance - DLL termination

int CGDIMotorStatusApp::ExitInstance()
{
	// TODO: Add your own module termination code here.

	return COleControlModule::ExitInstance();
}



// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}



// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}
