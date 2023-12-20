// GDIStatusBox.cpp : Implementation of CGDIStatusBoxApp and DLL registration.

#include "stdafx.h"
#include "GDIStatusBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CGDIStatusBoxApp theApp;

const GUID CDECL _tlid = { 0x9A5D4DFF, 0x6F3E, 0x4CF7, { 0x92, 0x71, 0x48, 0xE9, 0x91, 0xBC, 0x3A, 0xA } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;



// CGDIStatusBoxApp::InitInstance - DLL initialization

BOOL CGDIStatusBoxApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO: Add your own module initialization code here.
	}

	return bInit;
}



// CGDIStatusBoxApp::ExitInstance - DLL termination

int CGDIStatusBoxApp::ExitInstance()
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
