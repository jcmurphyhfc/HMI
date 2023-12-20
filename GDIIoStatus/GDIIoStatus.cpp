// GDIIoStatus.cpp : Implementation of CGDIIoStatusApp and DLL registration.

#include "stdafx.h"
#include "GDIIoStatus.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CGDIIoStatusApp theApp;

const GUID CDECL _tlid = { 0xDBCEDFF5, 0xECA9, 0x4CD1, { 0xA4, 0xA0, 0x55, 0x47, 0xF3, 0x6F, 0x8C, 0xAA } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;



// CGDIIoStatusApp::InitInstance - DLL initialization

BOOL CGDIIoStatusApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO: Add your own module initialization code here.
	}

	return bInit;
}



// CGDIIoStatusApp::ExitInstance - DLL termination

int CGDIIoStatusApp::ExitInstance()
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
