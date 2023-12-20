// GDIMultiReadout.cpp : Implementation of CGDIMultiReadoutApp and DLL registration.

#include "stdafx.h"
#include "GDIMultiReadout.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CGDIMultiReadoutApp theApp;

const GUID CDECL _tlid = { 0x1E102107, 0xC7AB, 0x4086, { 0xB2, 0xCB, 0xFD, 0xC7, 0x77, 0xB7, 0xE7, 0x4F } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;



// CGDIMultiReadoutApp::InitInstance - DLL initialization

BOOL CGDIMultiReadoutApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO: Add your own module initialization code here.
	}

	return bInit;
}



// CGDIMultiReadoutApp::ExitInstance - DLL termination

int CGDIMultiReadoutApp::ExitInstance()
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
