// GDILedLights.cpp : Implementation of CGDILedLightsApp and DLL registration.

#include "stdafx.h"
#include "GDILedLights.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CGDILedLightsApp theApp;

const GUID CDECL _tlid = { 0x7237C2F, 0xE7AB, 0x441E, { 0x83, 0x4E, 0xD7, 0xFD, 0x76, 0x31, 0x96, 0x22 } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;



// CGDILedLightsApp::InitInstance - DLL initialization

BOOL CGDILedLightsApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO: Add your own module initialization code here.
	}

	return bInit;
}



// CGDILedLightsApp::ExitInstance - DLL termination

int CGDILedLightsApp::ExitInstance()
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
