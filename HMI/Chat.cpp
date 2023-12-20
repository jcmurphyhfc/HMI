// Chat.cpp : implementation file
//

#include "stdafx.h"
//#include "MySocketsServer.h"
#include "HMI.h"
#include "Chat.h"
#include "ChatDlg.h"

	//ReceiveData.hWnd = pRunData->hWnd;
	//int len = WideCharToMultiByte(CP_UTF8, 0, pRunData->IpAddr, -1, NULL, 0, 0, 0);
	//if (len>1)
	//{ 
	//   //char *ptr = utf8.GetBuffer(len-1);
	//   WideCharToMultiByte(CP_UTF8, 0, pRunData->IpAddr, -1, pszIP, len, 0, 0);
	//   //utf8.ReleaseBuffer();
	//}
	//TRACE("Length: %d IP: %s \n",len,pszIP);

// CChat

CChat::CChat()
{
	m_COM.Running = false;
	WSADATA WSData;
	int error;

    // ---------------------------------------------- //
    // Initialize WinSock
    // ---------------------------------------------- //
    error = WSAStartup(0x0020, &WSData);
    switch(error)
    {
        case WSASYSNOTREADY:     
            TRACE("WSAStartup: \"WSASYSNOTREADY\"\r\n");    
			WSACleanup();
			return;
        case WSAVERNOTSUPPORTED: 
            TRACE("WSAStartup: \"WSAVERNOTSUPPORTED\"\r\n"); 
			WSACleanup();
			return;
        case WSAEINPROGRESS:
            TRACE("WSAStartup: \"WSAEINPROGRESS\"\r\n");
			WSACleanup();
			return;
        case WSAEPROCLIM:
            TRACE("WSAStartup: \"WSAEPROCLIM\"\r\n");
			WSACleanup();
			return;
        case WSAEFAULT:
            TRACE("WSAStartup: \"WSAEFAULT\"\r\n");
			WSACleanup();
			return;
    };
    // ---------------------------------------------- /

}

void CChat::SetDataBuffer(char* pBuff,int Size)
{
	m_COM.DataBuffer = pBuff;
	m_COM.DataSize = Size;
}

CChat::~CChat()
{
}

void CChat::Init()
{
	// Initialize
	TRACE("................................................CChat::CChat \n");
	m_COM.Running = true;
	m_COM.DataBuffer = NULL;
	CWinThread* pThread = AfxBeginThread (ServerThreadFunc, &m_COM,THREAD_PRIORITY_NORMAL,CREATE_SUSPENDED);
	pThread->ResumeThread();


	//pThread = (CUIThread*)AfxBeginThread (RUNTIME_CLASS (CUIThread));

}
void CChat::Close(void)
{
	if (m_COM.Running)
	{
		// Exit 
		TRACE("CChat::~CChat \n");
		m_COM.Running = false;
		closesocket(m_COM.s_sock);
		//AfxMessageBox(_T("close"));
		m_COM.ExitEvent.Lock(5000);	
		TRACE("CChat::~CChat \n");
		TRACE("CChat::~CChat \n");
	}
	WSACleanup();
}

//======================================================================================================//
// Function Name: ServerThreadFunc (LPVOID pParam)                                                     //
//                                                                                                      //
//======================================================================================================//
UINT CChat::ServerThreadFunc (LPVOID pParam)                                                                      
{            
	CHATTHREADDATASTRUCT* pRunData = (CHATTHREADDATASTRUCT*) pParam;
	RECEIVETHEADDATASTRUCT ReceiveData;
    INT rc, nSize;
    SOCKET t_sock, s_sock;
    SOCKADDR_IN sadr, t_sadr;

	//	TRACE("................................................CChat::CChat \n");
	//m_COM.Running = true;
	//m_COM.DataBuffer = NULL;
	//CWinThread* pThread = AfxBeginThread (ServerThreadFunc, &m_COM,THREAD_PRIORITY_NORMAL,CREATE_SUSPENDED);
	//pThread->ResumeThread();


    // Open a socket.
    s_sock = socket (AF_INET, SOCK_STREAM, 0);
    if (s_sock == INVALID_SOCKET) {
		TRACE("INVALID_SOCKET.. \n");
        return 0;
    }

    // Fill in socket address structure.
	memset(&sadr,0,sizeof(sadr));
	sadr.sin_family = AF_INET;
	sadr.sin_port = 1701;

	_try	{
		// Bind address to socket.
		rc = bind (s_sock, (struct sockaddr *)&sadr, sizeof (sadr));
		if (rc== SOCKET_ERROR){
			TRACE("Error binding \n");
			_leave;
		}

		// Set socket into listen mode.
		rc = listen (s_sock, SOMAXCONN);
		if (rc== SOCKET_ERROR){
			TRACE("Error listening \n");
			_leave;
		}

		pRunData->s_sock = s_sock;

		// Run
		//============================================================================================================//
		while (pRunData->Running)
		{
			// Block on accept.
			nSize = sizeof(t_sadr);
			TRACE("Blocking on accept............... \n");
			t_sock = accept (s_sock, (struct sockaddr *)&t_sadr, &nSize);
			if (t_sock == INVALID_SOCKET) {
				TRACE("INVALID_SOCKET on accept....\n");
				break;
			}

			// Create the receive thread 
			TRACE("Create ReceiveThreadFunc............ \n");

			//int z;                       /* Status return code */
			//struct sockaddr_in adr_inet; /* AF_INET */
			//int len_inet;                /* length */
			//len_inet = sizeof( adr_inet);
			//z = getpeername(s_sock, (struct sockaddr *)&adr_inet, &len_inet);
			//TRACE("getpeername ...........................%s z:%d\n",inet_ntoa(adr_inet.sin_addr),z);
			//if ( z == -1) {
			//	TRACE("getpeername Failed...........................%s \n",inet_ntoa(adr_inet.sin_addr));
			//}
			//z = getsockname(s_sock, (struct sockaddr *)&adr_inet, &len_inet);
			//TRACE("getsockname ...........................%s z:%d\n",inet_ntoa(adr_inet.sin_addr),z);
			//if ( z == -1) {
			//	TRACE("getpeername Failed...........................%s %d \n",inet_ntoa(adr_inet.sin_addr),z);
			//}
			////z = snprintf(buf,bufsiz, "%s:%u",inet_ntoa(adr_inet.sin_addr), (unsigned)ntohs(adr_inet.sin_port));


			//SOCKET t_sock = (SOCKET)pParam;
			ReceiveData.t_sock = t_sock;
			ReceiveData.DataBuffer = pRunData->DataBuffer;
			ReceiveData.DataSize = pRunData->DataSize;
			CWinThread* pThread = AfxBeginThread (ReceiveThreadFunc,(PVOID)&ReceiveData,THREAD_PRIORITY_NORMAL,CREATE_SUSPENDED);
			pThread->ResumeThread();

		}


	}
	_finally
	{
		closesocket(s_sock);
	}
	TRACE("...................................................ServerThreadFunc Exit \n");
	pRunData->ExitEvent.SetEvent();

	// Exit 
	//WSACleanup();
	return 0;                                                                                                       
}
//======================================================================================================//
// Function Name: ReceiveThreadFunc (LPVOID pParam)                                                     //
//                                                                                                      //
//======================================================================================================//
UINT CChat::ReceiveThreadFunc (LPVOID pParam)                                                                      
{          
	char buffer[256];
	bool bGo = true;
    INT rc;
	RECEIVETHEADDATASTRUCT* pReceiveData = (RECEIVETHEADDATASTRUCT*)pParam;
	SOCKET t_sock = pReceiveData->t_sock;
	char* DataBuffer = pReceiveData->DataBuffer;
	int   DataSize = pReceiveData->DataSize;
	bool DataSession = false;
	CUIThread* pThread = NULL;

	// Read the session type
	//----------------------------------------------//
	TRACE("Calling ReceiveThreadFunc \n");
	rc = recv(t_sock,buffer,256,0);
	if (rc == SOCKET_ERROR) 
	{
		rc = WSAGetLastError();
		TRACE("Error Code%d \n",rc);
		bGo = false;
	}
	if (bGo)
	{
		if (buffer[0]=='D' &&
			buffer[1]=='A' &&
			buffer[2]=='T' &&
			buffer[3]=='A')
		{
			DataSession = true;
		}
	}

	// Data Session
	//----------------------------------------------------------------------------------
	if (DataSession)
	{
		//------------------------------------------------------------------------------//
		while (bGo)
		{
			// Read from socket
			TRACE("Calling ReceiveThreadFunc \n");
			rc = recv(t_sock,buffer,256,0);
			if (rc == SOCKET_ERROR) 
			{
				rc = WSAGetLastError();
				TRACE("Error Code%d \n",rc);
				bGo = false;
			}

			// Send the data
			if (DataBuffer != NULL)
				rc = send(t_sock,DataBuffer,DataSize,0);

		}
		//------------------------------------------------------------------------------//
	
	}
	// CHAT Session
	//----------------------------------------------------------------------------------//
	else
	{
		// Create the chat window
		pThread = (CUIThread*)AfxBeginThread (RUNTIME_CLASS (CUIThread));
		pThread->t_sock = t_sock;
		HWND hWnd = pThread->m_hWndMessage;

		//------------------------------------------------------------------------------//
		while (bGo)
		{
			// Read from socket
			TRACE("Calling ReceiveThreadFunc \n");
			rc = recv(t_sock,buffer,256,0);
			if (rc == SOCKET_ERROR) 
			{
				rc = WSAGetLastError();
				TRACE("Error Code%d \n",rc);
				bGo = false;
			}
			//bGo = false;
			TRACE("ReceiveThreadFunc %d \n",buffer[0]);

			hWnd = pThread->m_hWndMessage;
			if ((hWnd != NULL) && bGo){
				//if (::IsWindow(hWnd)){
					TRACE("PostMessage %d \n",buffer[0]);
					::PostMessage(hWnd,WM_DO_DIALOG_UPDATE,(WPARAM)&buffer[0],0);
				//}
			}
		}
		//------------------------------------------------------------------------------//
		pThread->m_pMainWnd->PostMessage(WM_CLOSE,0,0);

	}

	// Exit
	closesocket(t_sock);
	TRACE("ReceiveThreadFunc Exit \n");
	return 0;
}