#pragma once
#include <afxmt.h>
#include <winsock.h>                 // Socket includes


///#pragma comment( lib, "Ws2_32.lib" )    // Winsock lib for desktop

// User's thread function hook data structure. 
typedef struct tagCHATTHREADDATASTRUCT{
	bool Running;
    LPCTSTR IpAddr;
	CEvent ExitEvent;
	SOCKET s_sock;
	char* DataBuffer;
	int   DataSize;
} CHATTHREADDATASTRUCT;

typedef struct tagRECEIVETHEADDATASTRUCT{
	HWND hWnd;
	SOCKET t_sock;
	char* DataBuffer;
	int   DataSize;
} RECEIVETHEADDATASTRUCT;

UINT ServerThreadFunc (LPVOID);
UINT ReceiveThreadFunc (LPVOID);

// CChat command target

class CChat : public CObject
{
public:
	CChat();
	virtual ~CChat();
	void SetDataBuffer(char* pBuff,int Size);

private:
	CHATTHREADDATASTRUCT m_COM;
	static UINT ServerThreadFunc (LPVOID);
	static UINT ReceiveThreadFunc (LPVOID);

public:
	void Init();
	void Close(void);
};


