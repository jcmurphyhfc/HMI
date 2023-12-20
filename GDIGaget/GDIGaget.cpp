// GDIGaget.cpp : Implementation of CGDIGagetApp and DLL registration.

#include "stdafx.h"
#include "GDIGaget.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CGDIGagetApp theApp;

const GUID CDECL _tlid = { 0xE8F7FD82, 0xFD29, 0x4B6A, { 0xA6, 0xC4, 0xA7, 0x8A, 0xF, 0x1A, 0xF7, 0x48 } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;



// CGDIGagetApp::InitInstance - DLL initialization

BOOL CGDIGagetApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO: Add your own module initialization code here.
	}

	return bInit;
}



// CGDIGagetApp::ExitInstance - DLL termination

int CGDIGagetApp::ExitInstance()
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
