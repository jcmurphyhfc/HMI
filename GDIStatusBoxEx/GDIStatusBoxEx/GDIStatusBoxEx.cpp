// GDIStatusBoxEx.cpp : Implementation of CGDIStatusBoxExApp and DLL registration.

#include "stdafx.h"
#include "GDIStatusBoxEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CGDIStatusBoxExApp theApp;

const GUID CDECL _tlid = { 0x31F23446, 0x4A04, 0x4D58, { 0x97, 0xAD, 0xCA, 0x95, 0x47, 0x2A, 0xEA, 0xBD } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;



// CGDIStatusBoxExApp::InitInstance - DLL initialization

BOOL CGDIStatusBoxExApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO: Add your own module initialization code here.
	}

	return bInit;
}



// CGDIStatusBoxExApp::ExitInstance - DLL termination

int CGDIStatusBoxExApp::ExitInstance()
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
