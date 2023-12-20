// GDITedit.cpp : Implementation of CGDITeditApp and DLL registration.

#include "stdafx.h"
#include "GDITedit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CGDITeditApp theApp;

const GUID CDECL _tlid = { 0x9EE38F38, 0x8436, 0x4106, { 0xA0, 0xC0, 0x4A, 0x4A, 0x0, 0x6F, 0x3C, 0x87 } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;



// CGDITeditApp::InitInstance - DLL initialization

BOOL CGDITeditApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO: Add your own module initialization code here.
	}

	return bInit;
}



// CGDITeditApp::ExitInstance - DLL termination

int CGDITeditApp::ExitInstance()
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
