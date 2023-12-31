// EIPGadget.cpp : Implementation of CEIPGadgetApp and DLL registration.

#include "stdafx.h"
#include "EIPGadget.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CEIPGadgetApp theApp;

const GUID CDECL _tlid = { 0xDB417AA8, 0x990A, 0x458A, { 0x8A, 0x58, 0x34, 0x76, 0xE8, 0x67, 0x16, 0xBD } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;



// CEIPGadgetApp::InitInstance - DLL initialization

BOOL CEIPGadgetApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO: Add your own module initialization code here.
	}

	return bInit;
}



// CEIPGadgetApp::ExitInstance - DLL termination

int CEIPGadgetApp::ExitInstance()
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
