//======================================================================
// Header file
//
// Written for the BOV Vision system.
// Copyright (C) 2015 Bill Young
//================================================================
#pragma once
#include "eipc_system.h"
#include <afxmt.h>

#ifdef    EIPCOM_GLOBALS
#define   EIPCOM_EXT 
#else
#define   EIPCOM_EXT extern
#endif

//EIPCOM_EXT CMapStringToPtr ReadTag_map;
//EIPCOM_EXT CMapStringToPtr WriteTag_map;

typedef struct
{
    int16   server_handle;
    uint8   ipaddr_byte[4]; /* store as big endian */
    uint32  ipaddr32;
}EIPC_TAGCLIENT_IP_STRUCT;

// User's thread function hook data structure. 
typedef struct tagEIPRUNTHREADDATASTRUCT{
	bool Running;
    LPCTSTR IpAddr;
	CEvent ExitEvent;
} EIPRUNTHREADDATASTRUCT;

typedef struct tagEIPCOMDATA
{
	bool            WriteDataA;
	bool            WriteDataB;
	int             BTCStatus;
	int             SlicerStatus;
	float           SteeringLaneB;
	float           SpeedLaneB;
} EIPCOMDATA;

//EIPCOM_EXT  uint32  ticks_passed;
EIPCOM_EXT  uint8	                  struct_num_elements;
EIPCOM_EXT	uint16                    save_handler;
EIPCOM_EXT  WSADATA                   WSData;
EIPCOM_EXT  uint16                    SampleServerHandle;
EIPCOM_EXT  uint32                    Ticker1;
EIPCOM_EXT  struct                    timeb base;
EIPCOM_EXT  EIPC_TAGCLIENT_IP_STRUCT  tag_server1;       //  {0,{10,13,4,115},0}; /* store IP as big endian */
EIPCOM_EXT  EIPC_TAGCLIENT_IP_STRUCT  tag_server2;       // {0,{10,13,4,118},0}; /* store IP as big endian */
EIPCOM_EXT  EIPCOMDATA                ReadPLCData;
EIPCOM_EXT  EIPCOMDATA                WritePLCData;

/* FUNCTION PROTOTYPES */
void InitEIPCom(void);
uint32 local_get_ticks_passed (void);
void local_process_tag_client (uint32 ticks_passed_since_last_call);
void local_process_tag_client2 (uint32 ticks_passed_since_last_call);


UINT EIPCOMThreadFunc (LPVOID);

