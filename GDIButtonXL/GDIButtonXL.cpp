// GDIButtonXL.cpp : Implementation of CGDIButtonXLApp and DLL registration.

#include "stdafx.h"
#include "GDIButtonXL.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CGDIButtonXLApp theApp;

const GUID CDECL _tlid = { 0x91D9AAC, 0xDAED, 0x4C28, { 0x96, 0xA, 0x44, 0x6B, 0x85, 0x8E, 0x7D, 0x2A } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;



// CGDIButtonXLApp::InitInstance - DLL initialization

BOOL CGDIButtonXLApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO: Add your own module initialization code here.

		// Initialize GDI+
		//GdiplusStartup(&m_gdiplusToken, &m_gdiplusStartupInput, NULL);

	}

	return bInit;
}



// CGDIButtonXLApp::ExitInstance - DLL termination

int CGDIButtonXLApp::ExitInstance()
{
	// TODO: Add your own module termination code here.
	//GdiplusShutdown(m_gdiplusToken);

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
