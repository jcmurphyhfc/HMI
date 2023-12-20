//======================================================================
// Header file
//
// Written for the Hormel.
// Copyright (C) 2015 Bill Young
//================================================================
#pragma once
#include "RTA\eipc_system.h"
#include <afxmt.h>

#ifdef    EIPCOM_GLOBALS
#define   EIPCOM_EXT 
#else
#define   EIPCOM_EXT extern
#endif

#define MAX_SERVERS       10                  // Max number of PLCs to talk to.
#define MAX_TAGS          500                 // Max number of TAGS. To many causes a stack overflow

typedef struct
{
    int16   server_handle;
    uint8   ipaddr_byte[4]; /* store as big endian */
    uint32  ipaddr32;
}EIPC_TAGCLIENT_IP_STRUCT;

// User's thread function hook data structure. 
typedef struct tagEIPRUNTHREADDATASTRUCT{
	bool Running;
	bool ReadWrite;
	int  ServerID;
	int  TimeOut;
	CEvent ExitEvent;
	CEvent ReadWriteExitEvent;
	CEvent DoReadWriteEvent;
	CEvent ReadWriteCompleteEvent;
	CObject* pObj;
} EIPRUNTHREADDATASTRUCT;

EIPCOM_EXT EIPC_TAG_STRUCT_USER_ID g_ResponseTags[EIPC_USEROBJ_MAXTAGS_PER_MSG];
EIPCOM_EXT CEvent  g_eventReadWrite;
EIPCOM_EXT EIPC_TAG_STRUCT_USER m_tagsAll[MAX_TAGS];
EIPCOM_EXT bool  g_userobj_error;

//#pragma once
class CClientEIP : public CObject
{
public:
	CClientEIP(void);
	~CClientEIP(void);

// Member Functions
public:
	void Init(LPCTSTR lpszIpAddr);
	uint32 local_get_ticks_passed (void);
    static UINT ThreadFunc (LPVOID);
    static UINT ReadWriteThreadFunc (LPVOID);
	int ReadTags(int ServerID,int TimeOut);
	int WriteTags(int ServerID,int TimeOut);
	int ReadAllTags(int ServerID,int TimeOut);
	int WriteAllTags(int ServerID,int TimeOut);
	int ThreadReadAllTags(int ServerID);
	int ThreadWriteAllTags(int ServerID);
	void ConnectToServer(int ServerID,LPCTSTR lpszIpAddr);
	void AddTag(int ServerID,char* szTag,int Elements);
	void GetTagData(int ServerID,char* szTag,int Element,float* dbData);
	void GetTagData(int ServerID,char* szTag,int Element,_int32* nData);
	void GetTagData(int ServerID,char* szTag,char* szData);
	void SetTagReadFlag(int ServerID,char* szTag);
	void Reset();
	void SetTagData(int ServerID,char* szTag,int Element,float dbData);
	void SetTagData(int ServerID,char* szTag,int Element,_int32 nData);
	void SetTagData(int ServerID,char* szTag,char* szData);
	int CheckStatus(int ServerID,int return_code);
	int BuildTags(int ServerID,int Index,bool Read,EIPC_TAG_STRUCT_USER *tag_ptr_src,EIPC_TAG_STRUCT *tag_ptr_dst,bool* TagsRemaining);
	
// Members variables
public:
	struct timeb base;
	EIPRUNTHREADDATASTRUCT m_EIPCOM;
	EIPC_TAGCLIENT_IP_STRUCT  tag_servers[MAX_SERVERS];
	EIPC_TAG_STRUCT m_tags[EIPC_USEROBJ_MAXTAGS_PER_MSG];
	CString m_strIPAddr[MAX_SERVERS];
	int m_nServerCount;
	int m_nTagCount;
	double m_dbMaxReadTime;
	bool m_bConnected;
	int m_nConnectRerty;
	bool m_Error;
};



