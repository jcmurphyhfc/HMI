// CPmac.cpp : implementation file
//
// CPmac.cpp : implementation file
//
#include "StdAfx.h"
#include "Pmac.h"
//#include "PmacServer_i.c"
#include <math.h>

/////////////////////////////////////////////////////////////////////////////
// CPmacDeviceEvents

//IMPLEMENT_DYNCREATE(CPmacDeviceEvents, CCmdTarget)
//
//CPmacDeviceEvents::CPmacDeviceEvents()
//{
//	m_msgDownloadMessage = WM_USER+0x0101;
//	m_msgProgress = WM_USER+0x0102;
//	m_msgError = WM_USER+0x0103;
//	m_msgInterrupt = WM_USER+0x0104;
//	m_msgUnSolicited = WM_USER+0x0105;
//	m_msgDataReady = WM_USER+0x0106;
//	m_hWnd = NULL;
//	m_pProgress = NULL;
//	m_pMessage = NULL;
//
//	EnableAutomation();
//}
//
//CPmacDeviceEvents::~CPmacDeviceEvents()
//{
//}
//
//
//void CPmacDeviceEvents::OnFinalRelease()
//{
//	// When the last reference for an automation object is released
//	// OnFinalRelease is called.  The base class will automatically
//	// deletes the object.  Add additional cleanup required for your
//	// object before calling the base class.
//
//	CCmdTarget::OnFinalRelease();
//}
//
//
//BEGIN_MESSAGE_MAP(CPmacDeviceEvents, CCmdTarget)
//	//{{AFX_MSG_MAP(CPmacDeviceEvents)
//		// NOTE - the ClassWizard will add and remove mapping macros here.
//	//}}AFX_MSG_MAP
//END_MESSAGE_MAP()
//
//BEGIN_DISPATCH_MAP(CPmacDeviceEvents, CCmdTarget)
//	//{{AFX_DISPATCH_MAP(CPmacDeviceEvents)
//		// NOTE - the ClassWizard will add and remove mapping macros here.
//	//}}AFX_DISPATCH_MAP
//    DISP_FUNCTION_ID(CPmacDeviceEvents,"Message",1,OnMessage,VT_EMPTY,VTS_I4 VTS_BSTR VTS_BOOL)
//    DISP_FUNCTION_ID(CPmacDeviceEvents,"Progress",2,OnProgress,VT_EMPTY,VTS_I4 VTS_I4)
//    DISP_FUNCTION_ID(CPmacDeviceEvents,"Error",3,OnError,VT_EMPTY,VTS_I4 VTS_BSTR VTS_I4 VTS_I4 VTS_BSTR)
//    DISP_FUNCTION_ID(CPmacDeviceEvents,"Interrupt",4,OnInterrupt,VT_EMPTY,VTS_I4 VTS_I4)
//    DISP_FUNCTION_ID(CPmacDeviceEvents,"UnSolicited",5,OnUnSolicited,VT_EMPTY,VTS_I4 VTS_BSTR)
//    DISP_FUNCTION_ID(CPmacDeviceEvents, "DataReady",6,OnDataReady,VT_EMPTY,VTS_I4)
//END_DISPATCH_MAP()
//
//// Note: we add support for IID_IPmacDeviceEvents to support typesafe binding
////  from VBA.  This IID must match the GUID that is attached to the 
////  dispinterface in the .ODL file.
//
//// {C0F6E36E-4803-4CFA-9486-73433810371D}
//// Comment out Not Needed --- static const IID IID_IPmacDeviceEvents =
////static const IID IID_IPmacDeviceEvents =
////{ 0xc0f6e36e, 0x4803, 0x4cfa, { 0x94, 0x86, 0x73, 0x43, 0x38, 0x10, 0x37, 0x1d } };
//BEGIN_INTERFACE_MAP(CPmacDeviceEvents, CCmdTarget)
//	INTERFACE_PART(CPmacDeviceEvents, DIID__IPmacDeviceEvents, Dispatch)
//END_INTERFACE_MAP()
//
///////////////////////////////////////////////////////////////////////////////
//// CPmacDeviceEvents message handlers
//
//
//void CPmacDeviceEvents::OnMessage(long lDevice,LPCTSTR Msg,BOOL bNewLine)
//{
//	int length;
//	CString str;
//
////	::PostMessage(MainhWnd,IDDOWNLOADMSG,(WPARAM)MyString,0);
//	if (m_pMessage != NULL)
//	{
//
//		//m_pMessage->GetWindowText(str);
//		//str += Msg;
//		//str += _T("\r\n");
//		//m_pMessage->SetWindowText(str);
//
//		str += Msg;
//		str += _T("\r\n");
//		length = m_pMessage->GetWindowTextLength();
//		m_pMessage->SetSel(length,length);
//		m_pMessage->ReplaceSel(str);
//
//
//		//::PostMessage(m_hWnd,m_msgDownloadMessage,(WPARAM)Msg,(LPARAM )bNewLine);
//		//TRACE(_T("CPmacDeviceEvents::OnMessage %s \n"),Msg);
//	}
//}
//
//void CPmacDeviceEvents::OnProgress(long lDevice,long dwPercent)
//{
////  m_ProgressBar.SetPos(dwPercent);
//	if (m_pProgress != NULL)
//	{
//		m_pProgress->SetPos(dwPercent);
//		//::PostMessage(m_hWnd,m_msgProgress,(WPARAM)lDevice,(LPARAM)dwPercent);
//		TRACE("CPmacDeviceEvents::OnProgress %d \n",dwPercent);
//	}
//}
//
//void CPmacDeviceEvents::OnError(long lDevice,LPCTSTR FileName,long ErrorID,long LineNum,LPCTSTR Line)
//{
////   AfxMessageBox("Event notification handled in client -OnError ");
//	if (m_hWnd != NULL){
//		::PostMessage(m_hWnd,m_msgError,(WPARAM)FileName,(LPARAM)ErrorID);
//	}
//	TRACE("CPmacDeviceEvents::OnError \n");
//
//}
//void CPmacDeviceEvents::OnInterrupt(long lDevice,long dwLevel)
//{
//	LPCTSTR Msg;
//	switch(dwLevel)
//	{
//	case 0: Msg = _T("Interrupt>> In Position"); break;
//	case 1: Msg = _T("Interrupt>> Buffer Request"); break;
//	case 2: Msg = _T("Interrupt>> Fatal Following Error"); break;
//	case 3: Msg = _T("Interrupt>> Warning Following Error"); break;
//	case 4: Msg = _T("Interrupt>> Host Request"); break;
//	case 5: Msg = _T("Interrupt>> Custom IR5"); break;
//	case 6: Msg = _T("Interrupt>> Custom IR6"); break;
//	case 7: Msg = _T("Interrupt>> Custom IR7"); break;
//	default: Msg = _T("Interrupt>> Unknown"); break;
//	}
//
////	*MyString = Msg;
//	if (m_hWnd != NULL){
//		::PostMessage(m_hWnd,m_msgInterrupt,(WPARAM)lDevice,(LPARAM)dwLevel);
//	}
//	TRACE("CPmacDeviceEvents::OnDataReady \n");
//
//}
//
//void CPmacDeviceEvents::OnUnSolicited(long lDevice,LPCTSTR Msg)
//{
////	*MyString = Msg;
////	::PostMessage(MainhWnd,IDDOWNLOADMSG,(WPARAM)MyString,0);
//	if (m_hWnd != NULL){
//		::PostMessage(m_hWnd,m_msgUnSolicited,(WPARAM)lDevice,(LPARAM)Msg);
//	}
//	TRACE(_T("CPmacDeviceEvents::OnUnSolicited %s \n"),Msg);
//
//
//}
//void CPmacDeviceEvents::OnDataReady(long lDevice)
//{
////   AfxMessageBox("Event notification handled in .NET client -OnDataReady ");
//	if (m_hWnd != NULL){
//		::PostMessage(m_hWnd,m_msgDataReady,(WPARAM)lDevice,0);
//	}
//	TRACE("CPmacDeviceEvents::OnDataReady \n");
//}


CPmac::CPmac(void)
{
	m_dwDevice = 0;
	m_bDeviceOpen = false;
	m_bSocketOpen = false;
	m_pDisp = 0;
	m_hResult = S_FALSE;
	//pmac = NULL;
	m_pUnkSink = 0;
	m_I10 = 1.0;
	m_strIP[0] = _T("192.6.94.5");
	m_strIP[1] = _T("192.6.94.6");
	m_strIP[2] = _T("192.6.94.7");
	m_strIP[3] = _T("192.6.94.8");
}


CPmac::~CPmac(void)
{

	// Close connection
	//LPUNKNOWN pUnkSink = m_pmacdeviceEvents.GetIDispatch(FALSE);
	//m_pmacdevice.Close(m_dwDevice);
	//int retVal = AfxConnectionUnadvise(m_pDisp,DIID__IPmacDeviceEvents,pUnkSink,FALSE,m_dwCookie);
	//pmac->Close(m_dwDevice);
	////CoUninitialize();
	ClosePmac();
}
void CPmac::ClosePmac(void)
{
	if (m_bSocketOpen)
	{
		m_bSocketOpen = false;
		closesocket(m_sock);
		WSACleanup();
		TRACE(_T("stop talking \n")); 
	}
	m_bDeviceOpen = false;
}


bool CPmac::Init(long dwDevice)
{
	CString			strIP;
	CString         strError;
	int				rc;
	char			buffer[256];
	WORD			wVersionRequested;
	WSADATA         WSData;
    wVersionRequested = MAKEWORD(2, 2);
    int error = WSAStartup(wVersionRequested, &WSData);
	int nTrys = 0;

	// Com already open
	if (m_bDeviceOpen)
	{
		TRACE(_T("PMAC Already open! \n")); 
		return m_bDeviceOpen;
	}

    // ---------------------------------------------- /
    // Initialize WinSock
    // ---------------------------------------------- /
    switch(error)
    {
        case WSASYSNOTREADY:     
            TRACE("WSAStartup: \"WSASYSNOTREADY\"\r\n");    
			WSACleanup();
			return false;
        case WSAVERNOTSUPPORTED: 
            TRACE("WSAStartup: \"WSAVERNOTSUPPORTED\"\r\n"); 
			WSACleanup();
			return false;
        case WSAEINPROGRESS:
            TRACE("WSAStartup: \"WSAEINPROGRESS\"\r\n");
			WSACleanup();
			return false;
        case WSAEPROCLIM:
            TRACE("WSAStartup: \"WSAEPROCLIM\"\r\n");
			WSACleanup();
			return false;
        case WSAEFAULT:
            TRACE("WSAStartup: \"WSAEFAULT\"\r\n");
			WSACleanup();
			return false;
    };
    // ---------------------------------------------- /

    // Open a socket.
    TRACE("Open a socket...\n");    
    m_sock = socket (PF_INET, SOCK_STREAM, 0);
    if (m_sock == INVALID_SOCKET) {
		TRACE("INVALID_SOCKET.. \n");
		return false;
    }

    // Fill in socket address structure.
	if (dwDevice>3) dwDevice = 0;
	strIP = m_strIP[dwDevice];
	TRACE(_T("Connect to IP: %s \n"),strIP);
	memset(&m_dest_sin,0,sizeof(m_dest_sin));
	m_dest_sin.sin_family = PF_INET;
	m_dest_sin.sin_port = htons(1025);
	int len = WideCharToMultiByte(CP_UTF8, 0,strIP, -1, NULL, 0, 0, 0);
	if (len>1)	{		WideCharToMultiByte(CP_UTF8, 0,	strIP, -1, buffer, len, 0, 0);	}
	TRACE("Connect to Len: %d IP: %s \n",len,buffer);
	m_dest_sin.sin_addr.S_un.S_addr = inet_addr(buffer);

	// Connect to socket.
    TRACE("Connect to socket...\n");    
	rc = connect (m_sock, (struct sockaddr *)&m_dest_sin, sizeof (m_dest_sin));
	if (rc== SOCKET_ERROR){
		TRACE("Error Connecting \n");
		strError = _T("Error Connecting to PMAC IP:");
		strError += strIP;
		//AfxMessageBox(strError);
		closesocket(m_sock);
		return false;
	}

	// Com open
	m_bDeviceOpen = true;
	m_bSocketOpen = true;

	// Get the value of I10
	m_I10 = 0;
	while (nTrys < 10 && m_I10==0)
	{
		nTrys++;
		GetVariable(_T('I'),10,&m_I10);
		TRACE("I10=%f \n",m_I10);
		if (m_I10==0)
		{ 
			Sleep(100);
			TRACE("Error I10=%f \n",m_I10);
		}
	}
	if (m_I10==0)
	{ 
		TRACE("Error Connecting \n");
		//strError = _T("Error Connecting to PMAC IP:");
		//strError += strIP;
		//AfxMessageBox(strError);
		m_bDeviceOpen = true;
		m_bSocketOpen = true;
		closesocket(m_sock);
		return false;
	}

	//GetVariable(_T('I'),10,&m_I10);
	m_ServoFrequency = 8388608.0/m_I10;
	TRACE("I10 %f .................................ServoFreq: %f \n",m_I10,8388608/m_I10);

	// Check for DPRAM
    TRACE("Check for DPRAM...\n");    
	m_DPRamPresent = true;
	unsigned char buff[] = { 0xAA,0xAA,0xAA,0xAA };
	DPRSetMem(0,4,(char*)buff);
	DPRGetMem(0,4,(char*)buff);
	for (int i=0;i<4;i++)
	{
		if (buff[i] != (unsigned char)0xAA){
			m_DPRamPresent = false;
			TRACE("buff[%d]: %x \n",i,buff[i]);
		}
	}
    TRACE("Check for DPRAM complete.\n");    
	if (m_DPRamPresent)
	{
		TRACE("Setup DPRAM for motor data gathering.\n");    
		SetVariable(_T('I'),48,(long)1);       // Enable servo cycle update of motor data
		SetVariable(_T('I'),47,(long)20);	   // cycles
		buff[0] = 0xFF;                        // Enable motors 1-8
		//buff[1] = 0xFF;                      // Enable motors 9-16
		DPRSetMem(DPR_OFFSET_MOTORBITS,1,(char*)buff);
		//pmac->DPRSet(DPR_OFFSET_MOTORBITS,(long)0xFF);
	}

	//pmac->get_DPRAvailable(m_dwDevice,&m_DPRamPresent);
	TRACE("m_DPRamPresent.................................m_DPRamPresent: %d \n",m_DPRamPresent);
	return true;

}
//------------------------------------------------------------------------------------------------------//
//                                BEGINING OF TODO
//------------------------------------------------------------------------------------------------------//
void CPmac::SetPmacMsgWnd(HWND hWnd)
{
	//m_pmacdeviceEvents.m_hWnd = hWnd;
	AfxMessageBox(_T("CODE TO DO"));
}	
void CPmac::SetDownloadMsgPtr(CEdit* pWnd)
{
	//m_pmacdeviceEvents.m_pMessage = pWnd;
	AfxMessageBox(_T("CODE TO DO"));
}
void CPmac::SetProgressMsgPtr(CProgressCtrl* pWnd)
{
	//m_pmacdeviceEvents.m_pProgress = pWnd;
	AfxMessageBox(_T("CODE TO DO"));
}
void CPmac::SelectPmac()
{
	AfxMessageBox(_T("CODE TO DO"));
	//long dwDevice;
	//VARIANT_BOOL bDeviceOpen;

	//pmac->SelectDevice(NULL,&dwDevice,&bDeviceOpen);

	//if (dwDevice >= 0 && dwDevice <= 7)
	//{
	//	if (bDeviceOpen)
	//	{
	//		m_dwDevice = dwDevice;
	//		pmac->Close(m_dwDevice);
	//		pmac->Open(m_dwDevice,&m_bDeviceOpen);
	//		TRACE("Device is open \n");
	//	}
	//}
}
bool CPmac::Download(LPCTSTR lpsz)
{
	AfxMessageBox(_T("CODE TO DO"));
	if (!m_bDeviceOpen) return false;
	//VARIANT_BOOL status;
	//pmac->Download(m_dwDevice,lpsz,FALSE,TRUE,TRUE,TRUE,&status);
	return true;
}
bool CPmac::Upload(LPCTSTR lpsz)
{
	AfxMessageBox(_T("CODE TO DO"));
 // 	// Get the file name
	////CFileDialog fd(	FALSE,_T(".cfg"),NULL, 0,_T("PMAC Configuration File (*.cfg)|*.cfg;*.CFG |All Files(*.*)|*.*|"),NULL);
	////if (fd.DoModal() != IDOK)
	////	return false;

	if (!m_bDeviceOpen) return false;

	//long status;
	//BSTR buffer =  ::SysAllocString(L"");
	//DEVUPLOAD devUpload;
	//devUpload.ivar = 1;
	//devUpload.comp_tables = 0;
	//devUpload.coord_sys = 1;
	//devUpload.important_register = 0;
	//devUpload.macro = 0;
	//devUpload.motion = 1;
	//devUpload.mvar = 1;
	//devUpload.option_16 = 0;
	//devUpload.option_16e = 0;
	//devUpload.plc = 1;
	//devUpload.plcc = 1;
	//devUpload.pvar = 1;
	//devUpload.qvar = 1;
	//devUpload.racro_ring_order = 0;
	//devUpload.user_backup = 0;
	//devUpload.single_backup = 1;
	////AfxMessageBox(_T("Start upload"));

	//// Get the data
	//pmac->Upload(m_dwDevice, devUpload,  &buffer, &status);
	//CString csTest(buffer);

	////AfxMessageBox(_T("upload complete"));
	////TRACE(_T("%s\n"),buffer);
	////fd.GetFileExt();
	////TRACE(_T("Path: %s\n"),fd.GetFolderPath());
	////TRACE(_T("FileName: %s\n"),fd.GetFileName());

	//try {
	//	CString string;
	//	//CStdioFile file (fd.GetFileName(), CFile::modeReadWrite | CFile::modeCreate );
	//	//CStdioFile file (_T ("D:\\BTCDATA\\UpLoadFile.CFG"), CFile::modeReadWrite | CFile::modeCreate );
	//	CStdioFile file (lpsz, CFile::modeReadWrite | CFile::modeCreate );
	//	file.WriteString(csTest);
	//}
	//catch (CFileException* e) {
	//	e->ReportError ();
	//	e->Delete ();
	//}
	return true;
}
int CPmac::Reset(LPCTSTR lpszCmd,BOOL AsciiRingCom)
{
	long status = 0;
	if (!m_bDeviceOpen) return false;
	//pmac->PmacReset(m_dwDevice,lpszCmd,AsciiRingCom,&status);
	AfxMessageBox(_T("CODE TO DO"));
	return COMM_CHARS(status);
}

int CPmac::Save(LPCTSTR lpszCmd)
{
	long status = 0;
	AfxMessageBox(_T("CODE TO DO"));
	if (!m_bDeviceOpen) return false;
	//pmac->PmacSave(m_dwDevice,lpszCmd,&status);
	return COMM_CHARS(status);
}

int CPmac::SendCommand(LPCTSTR lpszCmd)
{
	int status;
	TCHAR resBuff[1401];
	//AfxMessageBox(_T("CODE TO DO"));
	if (!m_bDeviceOpen) return false;
	status = GetResponse(lpszCmd,resBuff);
	TRACE(_T("SendCommand Chars returned: %d \n"),status);
	return status;
	//pmac->SendCommand(m_dwDevice,lpszCmd,&status);
	//return COMM_CHARS(status);
}

//VARIANT_BOOL Success;
//DEVMSTURBO mtrstat;
//pmac->GetTurboMotorStatusEx(0,0,&mtrstat,&Success);
//TRACE(_T("Motor 0 open loop mode: %d \n"),mtrstat.mst_open_loop_mode);
int CPmac::GetResponse(LPCTSTR lpszCmd,LPTSTR response)
{
	int len = 0;
	//char buffer[1400];
	if (!m_bDeviceOpen) return false;
	//TRACE(_T("%s \n"),lpszCmd);	
	if (PmacSockGetResponse(lpszCmd))
	{
		// Count the chars
		len = m_strResponse.GetLength()+1;
		_tcscpy_s(response, len, m_strResponse);
		
		//len = WideCharToMultiByte(CP_UTF8, 0,m_strResponse, -1, NULL, 0, 0, 0);
		//TRACE(_T("%s \n"),m_strResponse);	
		//if (len>1)
		//{
		//	WideCharToMultiByte(CP_UTF8, 0,	m_strResponse, -1, buffer, len, 0, 0);
		//	_tcscpy(response,m_strResponse.GetBuffer(0));
		//}
	}
	// Error
	else
	{
		m_bDeviceOpen = false;
	}
	return len;

//m_dblStack[0] = _tcstod (m_strDisplay.GetBuffer (0), NULL);=
//LPTSTR p = s.GetBuffer( 10 );
//strcpy( p, "Hello" );   // directly access CString buffer
//s.ReleaseBuffer( );

//EthCmd.RequestType = VR_DOWNLOAD;
//EthCmd.Request     = VR_PMAC_GETRESPONSE;
//EthCmd.wValue      = 0; 
//EthCmd.wIndex      = 0;
//EthCmd.wLength     = htons( (WORD)strlen(outstr));
//strncpy((char *)&EthCmd.bData[0],outstr,(WORD)strlen(outstr));
//send(sock,(char*)&EthCmd,ETHERNETCMDSIZE + strlen(outstr),0);
//recv(sock, szPmacData,1400,0); 


//CString theString(_T("This is a test"));
//int sizeOfString = (theString.GetLength() + 1);
//LPTSTR lpsz = new TCHAR[sizeOfString];
//_tcscpy_s(lpsz, sizeOfString, theString);

}

int CPmac::GetResponseBuffer(LPTSTR response)
{
	int len = 0;
	if (!m_bDeviceOpen) return false;
	if (PmacSockGetResponseBuffer())
	{
		// Count the chars
		len = m_strResponse.GetLength()+1;
		_tcscpy_s(response, len, m_strResponse);
		
		//len = WideCharToMultiByte(CP_UTF8, 0,m_strResponse, -1, NULL, 0, 0, 0);
		//TRACE(_T("%s \n"),m_strResponse);	
		//if (len>1)
		//{
		//	WideCharToMultiByte(CP_UTF8, 0,	m_strResponse, -1, buffer, len, 0, 0);
		//	_tcscpy(response,m_strResponse.GetBuffer(0));
		//}
	}
	// Error
	else
	{
		m_bDeviceOpen = false;
	}
	return len;

}
int CPmac::IsPmacOpen()
{
	return m_bDeviceOpen;
}

bool CPmac::DPRGet(int Offset, short *Data)
{
	bool      bSuccess=0;
	AfxMessageBox(_T("CODE TO DO"));
	if (!m_bDeviceOpen) return false;
	//pmac->DPRGetShort(m_dwDevice,Offset,Data,&bSuccess);
	//TRACE("%c%d=%f \n",ch,num,*Data);
	return bSuccess;
}

bool CPmac::DPRGet(int Offset, long *Data)
{
	bool      bSuccess=0;
	AfxMessageBox(_T("CODE TO DO"));
	if (!m_bDeviceOpen) return false;
	//pmac->DPRGetLong(m_dwDevice,Offset,Data,&bSuccess);
	return bSuccess;
}
bool CPmac::DPRSet(int Offset, short Data)
{
	char* ptrData = (char*)&Data;
	char buffer[16];
	int rc;
	ETHERNETCMD EthCmd;
	if (!m_bDeviceOpen) return false;
	if (!m_DPRamPresent) return false;
	EthCmd.RequestType = VR_UPLOAD;
	EthCmd.Request = VR_PMAC_SETMEM;
	EthCmd.wValue = htons(Offset);
	EthCmd.wIndex = 0;
	EthCmd.wLength = htons(2);
	EthCmd.bData[0]= ptrData[0];
	EthCmd.bData[1]= ptrData[1];
	rc = send(m_sock,(char *)&EthCmd,ETHERNETCMDSIZE+2 ,0);
	if (rc == SOCKET_ERROR) 
	{
		rc = WSAGetLastError();
		TRACE("Send Error Code%d \n",rc);
		m_bDeviceOpen = false;
		return false;
	}
	rc = recv(m_sock,buffer,1,0);
	if (rc == SOCKET_ERROR) 
	{
		rc = WSAGetLastError();
		TRACE("recv Error Code%d \n",rc);
		m_bDeviceOpen = false;
		return false;
	}
	return true;
}

bool CPmac::DPRSet(int Offset, int Data)
{
	char* ptrData = (char*)&Data;
	char buffer[16];
	int rc;
	ETHERNETCMD EthCmd;
	if (!m_bDeviceOpen) return false;
	if (!m_DPRamPresent) return false;
	EthCmd.RequestType = VR_UPLOAD;
	EthCmd.Request = VR_PMAC_SETMEM;
	EthCmd.wValue = htons(Offset);
	EthCmd.wIndex = 0;
	EthCmd.wLength = htons(4);
	EthCmd.bData[0]= ptrData[0];
	EthCmd.bData[1]= ptrData[1];
	EthCmd.bData[2]= ptrData[2];
	EthCmd.bData[3]= ptrData[3];
	rc = send(m_sock,(char *)&EthCmd,ETHERNETCMDSIZE+4 ,0);
	if (rc == SOCKET_ERROR) 
	{
		rc = WSAGetLastError();
		m_bDeviceOpen = false;
		TRACE("Send Error Code%d \n",rc);
		return false;
	}
	rc = recv(m_sock,buffer,1,0);
	if (rc == SOCKET_ERROR) 
	{
		rc = WSAGetLastError();
		m_bDeviceOpen = false;
		TRACE("recv Error Code%d \n",rc);
		return false;
	}
	return true;
}
double CPmac::GetCommandedPos(int MtrNum,double scale)
{
	double data=0;
	AfxMessageBox(_T("CODE TO DO"));
	if (!m_bDeviceOpen) return false;
	//pmac->GetCommandedPos(m_dwDevice,MtrNum,scale,&data);
	return data;
}
double CPmac::GetFollowError(int MtrNum,double scale)
{
	double data=0;
	AfxMessageBox(_T("CODE TO DO"));
	if (!m_bDeviceOpen) return false;
	//pmac->GetFollowError(m_dwDevice,MtrNum,scale,&data);
	return data;
}
double CPmac::GetVelocity(int MtrNum,double scale)
{
	double data=0;
	AfxMessageBox(_T("CODE TO DO"));
	if (!m_bDeviceOpen) return false;
	//pmac->GetVelocity(m_dwDevice,MtrNum,scale,&data);
	return data;
}
double CPmac::DPRFloat(long long d,double scale)
{
	double data=0;
	AfxMessageBox(_T("CODE TO DO"));
	if (!m_bDeviceOpen) return false;
	//TRACE("%I64x \n",(_int64)0x00059A000000FFFF);
	//TRACE("%I64x \n",d);
	//pmac->DPRFloat(d,scale,&data);
	return data;
}

//------------------------------------------------------------------------------------------------------//
//                               END OF TODO
//------------------------------------------------------------------------------------------------------//

bool CPmac::GetVariable(char ch,long num, long* Data)
{
	int len;
	char buffer[256];
	CString str;
	bool      bSuccess=0;
	if (!m_bDeviceOpen) return false;
	str.Format(_T("%c%d"),ch,num);
	//TRACE(_T("%s \n"),str);	
	if (PmacSockGetResponse(str))
	{
		// Convert to long
		len = WideCharToMultiByte(CP_UTF8, 0,m_strResponse, -1, NULL, 0, 0, 0);
		if (len>1)
		{
			WideCharToMultiByte(CP_UTF8, 0,	m_strResponse, -1, buffer, len, 0, 0);
		}
		//	TRACE("Length: %d data: %s \n",len,buffer);
		*Data = atol(buffer);
		//TRACE (_T ("Data: %d\n"), *Data);
		bSuccess = 1;
	}
	else 
	{
		m_bDeviceOpen = false;
	}
	return bSuccess;
}
bool CPmac::GetVariable(char ch,long num, double* Data)
{
	int len;
	char buffer[256];
	CString str;
	bool      bSuccess=0;
	if (!m_bDeviceOpen) return false;
	//pmac->GetVariableLong(m_dwDevice,ch,num,0,Data,&bSuccess);
	str.Format(_T("%c%d"),ch,num);
	//TRACE(_T("%s \n"),str);	
	if (PmacSockGetResponse(str))
	{
		// Convert to long
		len = WideCharToMultiByte(CP_UTF8, 0,m_strResponse, -1, NULL, 0, 0, 0);
		if (len>1)
		{
			WideCharToMultiByte(CP_UTF8, 0,	m_strResponse, -1, buffer, len, 0, 0);
		}
		//	TRACE("Length: %d data: %s \n",len,buffer);
		*Data = atof(buffer);
		//TRACE (_T ("Data: %f\n"), *Data);
		bSuccess = 1;
	}
	else 
	{
		m_bDeviceOpen = false;
	}
	return bSuccess;

	//bool      bSuccess=0;
	//if (!m_bDeviceOpen) return false;
	//pmac->GetVariableDouble(m_dwDevice,ch,num,0,Data,&bSuccess);
	//TRACE("%c%d=%f \n",ch,num,*Data);
	//return bSuccess;
}

bool CPmac::SetVariable(char ch,long num, long Data)
{
	//int len;
	//char buffer[256];
	CString str;
	bool      bSuccess=0;
	if (!m_bDeviceOpen) return false;
	str.Format(_T("%c%d=%ld"),ch,num,Data);
	if (PmacSockGetResponse(str))
	{
		// Convert to long
		//len = WideCharToMultiByte(CP_UTF8, 0,m_strResponse, -1, NULL, 0, 0, 0);
		//if (len>1)
		//{
		//	WideCharToMultiByte(CP_UTF8, 0,	m_strResponse, -1, buffer, len, 0, 0);
		//}
		////	TRACE("Length: %d data: %s \n",len,buffer);
		//*Data = atof(buffer);
		//TRACE (_T ("Data: %f\n"), *Data);
		bSuccess = 1;
	}
	else 
	{
		m_bDeviceOpen = false;
	}
	return bSuccess;

	//bool      bSuccess=0;
	//if (!m_bDeviceOpen) return false;
	//pmac->SetVariableLong(m_dwDevice,ch,num,Data,&bSuccess);
	//TRACE("%c%d=%d \n",ch,num,*Data);
	//return bSuccess;
}
bool CPmac::SetVariable(char ch,long num, double Data)
{
	//int len;
	//char buffer[256];
	CString str;
	bool      bSuccess=0;
	if (!m_bDeviceOpen) return false;
	str.Format(_T("%c%d=%f"),ch,num,Data);
	if (PmacSockGetResponse(str))
	{
		// Convert to long
		//len = WideCharToMultiByte(CP_UTF8, 0,m_strResponse, -1, NULL, 0, 0, 0);
		//if (len>1)
		//{
		//	WideCharToMultiByte(CP_UTF8, 0,	m_strResponse, -1, buffer, len, 0, 0);
		//}
		////	TRACE("Length: %d data: %s \n",len,buffer);
		//*Data = atof(buffer);
		//TRACE (_T ("Data: %f\n"), *Data);
		bSuccess = 1;
	}
	else 
	{
		m_bDeviceOpen = false;
	}
	return bSuccess;
	//bool      bSuccess=0;
	//if (!m_bDeviceOpen) return false;
	//pmac->SetVariableDouble(m_dwDevice,ch,num,Data,&bSuccess);
	//TRACE("%c%d=%f \n",ch,num,*Data);
	//return bSuccess;
}

bool CPmac::DPRGetMem(int Offset,int NumBytes, char* Data)
{
	int rc;
	ETHERNETCMD EthCmd;
	if (!m_bDeviceOpen) return false;
	if (!m_DPRamPresent) return false;
	EthCmd.RequestType = VR_UPLOAD;
	EthCmd.Request = VR_PMAC_GETMEM;
	EthCmd.wValue = htons(Offset);
	EthCmd.wIndex = 0;
	EthCmd.wLength = htons(NumBytes);
	rc = send(m_sock,(char *)&EthCmd,ETHERNETCMDSIZE ,0);
	if (rc == SOCKET_ERROR) 
	{
		rc = WSAGetLastError();
		TRACE("Send Error Code%d \n",rc);
		m_bDeviceOpen = false;
		return false;
	}
	rc = recv(m_sock,Data,NumBytes,0);
	if (rc == SOCKET_ERROR) 
	{
		rc = WSAGetLastError();
		TRACE("recv Error Code%d \n",rc);
		m_bDeviceOpen = false;
		return false;
	}
	return true;

}
bool CPmac::DPRSetMem(int Offset,int NumBytes, char* Data)
{
	//bool      bSuccess=0;
	//if (!m_bDeviceOpen) return false;
	//if (!m_DPRamPresent) return false;
	//pmac->DPRSetMem(m_dwDevice,Offset,NumBytes,Data,&bSuccess);

	//EthCmd.RequestType = VR_UPLOAD;
	//EthCmd.Request = VR_PMAC_SETMEM;
	//EthCmd.wValue = htons(offset);
	//EthCmd.wIndex = 0;
	//EthCmd.wLength = htons(length);

	int rc;
	ETHERNETCMD EthCmd;
	if (!m_bDeviceOpen) return false;
	if (!m_DPRamPresent) return false;
	EthCmd.RequestType = VR_UPLOAD;
	EthCmd.Request = VR_PMAC_SETMEM;
	EthCmd.wValue = htons(Offset);
	EthCmd.wIndex = 0;
	EthCmd.wLength = htons(NumBytes);
	memcpy(EthCmd.bData,Data,NumBytes);
	rc = send(m_sock,(char *)&EthCmd,ETHERNETCMDSIZE+NumBytes ,0);
	if (rc == SOCKET_ERROR) 
	{
		rc = WSAGetLastError();
		TRACE("Send Error Code%d \n",rc);
		m_bDeviceOpen = false;
		return false;
	}
	rc = recv(m_sock,Data,NumBytes,0);
	if (rc == SOCKET_ERROR) 
	{
		rc = WSAGetLastError();
		TRACE("recv Error Code%d \n",rc);
		m_bDeviceOpen = false;
		return false;
	}
	return true;

}
double CPmac::DPRFixed( long d[], double scale )
{
	if (!m_bDeviceOpen) return false;
	//TRACE(_T("first_word %x \n"),d[0]);
	//TRACE(_T("second_word %x \n"),d[1]);

	//	double CPmac::DPRLFixed( long d[], double scale )
	// 48-bit fixed point word:
	// 2 32 bit words holding 24 bits each of the 48 bit words.
	double result;
	result = ( double ) ( d[0] & 0x00FFFFFFL ) + (( double ) ( d[1] )) * 16777216.0;
	return result * scale;

//	long exp = second_word & 0x00FFF000L;              // Select 12 bits for exponent
//	long low_mantissa =  first_word  & 0x00FFFFFFL;
//	long high_mantissa = second_word & 0x00000FFFL;
//	double mantissa = second_word*16777216 + low_mantissa;
//	return mantissa;
//	//return (mantissa * pow (2.0, exp - 2047 - 35));
//
//#if 0
//	long int exp = first_word & 0x00000FFFL;  // Select low 12 bits for exponent
//	long low_mantissa = (first_word >> 12) & 0x00FFFL;
//
//	// Select next 12 bits for mantissa
//	// shift right and mask
//	long high_mantissa = second_word;
//	
//	//The floating point value can then be reconstructed with:
//	long mantissa = high_mantissa * 4096.0 + low_mantissa;
//	double value = mantissa * pow (2.0, exp - 2047 - 35);
//	return value;
//
//#endif
//	// return mantissa/2^35 * 2^(exp-2047)
//	//double mantissa;
//	//long int exp;
//	//mantissa = (double)(second_word) * 4096.0 + (double)((first_word>>12) & 0x00FFFL);
//	//if (mantissa == 0.0) return (0.0);
//	//exp = (first_word & 0x00000FFFL) - 2082;  // 2082=2047+35
//	//return (mantissa * pow(2.0 * (double) exp));	
}

double CPmac::GetMotorPosition(int MtrNum,double scale)
{
	double data=0;
	int len;
	char buffer[256];
	CString str;
	if (!m_bDeviceOpen)
	{
		TRACE("GetMotorPosition Device not open \n");
		return data;
	}
	str.Format(_T("#%dP"),MtrNum);
	//TRACE(_T("%s \n"),str);	
	if (PmacSockGetResponse(str))
	{
		// Convert to long
		len = WideCharToMultiByte(CP_UTF8, 0,m_strResponse, -1, NULL, 0, 0, 0);
		if (len>1)
		{
			WideCharToMultiByte(CP_UTF8, 0,	m_strResponse, -1, buffer, len, 0, 0);
		}
		//TRACE("Length: %d data: %s \n",len,buffer);
		data = atof(buffer)*scale;
		//TRACE (_T ("Data: %f\n"), data);
	}
	else 
	{
		m_bDeviceOpen = false;
		TRACE("PmacSockGetResponse error closing device... \n");
	}
	return data;
}
bool CPmac::PmacSockGetResponse(LPCTSTR lpsz)
{
	int length;
	int rc;
	char Buffer[2048];
	ETHERNETCMD EthCmd;
	EthCmd.RequestType = VR_DOWNLOAD;
	EthCmd.Request = VR_PMAC_GETRESPONSE;
	EthCmd.wValue = 0;
	EthCmd.wIndex = 0;

	CString strCmd(lpsz);
	//TRACE(_T("String %s \n"),str);
	length = WideCharToMultiByte(CP_UTF8, 0,strCmd, -1, NULL, 0, 0, 0);
	if (length>1) WideCharToMultiByte(CP_UTF8, 0,strCmd, -1, Buffer, length, 0, 0);
	//TRACE(_T("Length:%d \n"),length);
	length = (WORD)strlen(Buffer);
	//TRACE(_T("Length:%d \n"),length);
	EthCmd.wLength = htons(length);
	strcpy_s((char *)&EthCmd.bData[0],1400,Buffer);

	// Send the data
	rc = send(m_sock,(char*)&EthCmd,ETHERNETCMDSIZE + length,0);
	if (rc == SOCKET_ERROR) 
	{
		rc = WSAGetLastError();
		m_bDeviceOpen = false;
		TRACE("Send Error Code%d \n",rc);
		return false;
	}
    rc = recv(m_sock,Buffer,1400,0);
	//recv(m_sock, szPmacData,1400,0);
	if (rc == SOCKET_ERROR) 
	{
		rc = WSAGetLastError();
		m_bDeviceOpen = false;
		TRACE("Error Code%d \n",rc);
		return false;
	}
	else
	{
		Buffer[rc] = '\0';
		m_strResponse = Buffer;
		//TRACE(_T("Response..\n%s\n"),m_strResponse);
		//TRACE("rc:%d ",rc);
		//for (int i=0;i<rc;i++)
		//{
		//	TRACE("%c",Buffer[i]);
		//}
		//TRACE("\n");
	}
	return true;
}

bool CPmac::PmacSockGetResponseBuffer()
{
	int rc;
	char Buffer[2048];
	ETHERNETCMD EthCmd;
    EthCmd.RequestType = VR_UPLOAD;
    EthCmd.Request     = VR_PMAC_GETBUFFER;
	EthCmd.wValue = 0;
	EthCmd.wIndex = 0;
    // EthCmd.wLength     = htons( (WORD)strlen(outstr));
	EthCmd.wLength     = 0;

	// Send the data
	rc = send(m_sock,(char*)&EthCmd,ETHERNETCMDSIZE,0);
    //	 send(sock,(char *)&EthCmd,ETHERNETCMDSIZE,0);
	if (rc == SOCKET_ERROR) 
	{
		rc = WSAGetLastError();
		m_bDeviceOpen = false;
		TRACE("Send Error Code%d \n",rc);
		return false;
	}
    rc = recv(m_sock,Buffer,1400,0);
    //	 recv(sock,(char *)&instr,1400,0);
	if (rc == SOCKET_ERROR) 
	{
		rc = WSAGetLastError();
		m_bDeviceOpen = false;
		TRACE("Error Code%d \n",rc);
		return false;
	}
	else
	{
		Buffer[rc] = '\0';
		m_strResponse = Buffer;
		TRACE(_T("m_strResponse=%s count:%d\n"),m_strResponse,rc);	

		//TRACE(_T("Response..\n%s\n"),m_strResponse);
		//TRACE("rc:%d ",rc);
		//for (int i=0;i<rc;i++)
		//{
		//	TRACE("%c",Buffer[i]);
		//}
		//TRACE("\n");
	}
	return true;
}