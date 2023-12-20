/*
 *            Copyright (c) 2002-2010 by Real Time Automation, Inc.
 *
 *  This software is copyrighted by and is the sole property of
 *  Real Time Automation, Inc. (RTA).  All rights, title, ownership, 
 *  or other interests in the software remain the property of RTA.  
 *  This software may only be used in accordance with the corresponding
 *  license agreement.  Any unauthorized use, duplication, transmission,
 *  distribution, or disclosure of this software is expressly forbidden.
 *
 *  This Copyright notice MAY NOT be removed or modified without prior
 *  written consent of RTA.
 *
 *  RTA reserves the right to modify this software without notice.
 *
 *  Real Time Automation
 *  150 S. Sunny Slope Rd.             USA 262.439.4999
 *  Suite 130                          http://www.rtaautomation.com
 *  Brookfield, WI 53005               software@rtaautomation.com
 *
 *************************************************************************
 *
 *         Version: 1.09
 *    Version Date: 01/09/2012
 *     Module Name: eipc_tagclient.c
 *          Author: Jamin D. Wendorf (jwendorf@rtaautomation.com)
 *        Language: Ansi C
 * Compile Options: N/A
 * Compile defines: N/A
 *       Libraries: N/A
 *    Link Options: N/A
 *
 * Description.
 * ====================================================================
 * This file contains the Tag Client functions.
 *
 */

/* ---------------------------- */
/* INCLUDE FILES                */
/* ---------------------------- */
#include "eipc_system.h"

/* ---------------------------- */
/* LOCAL FUNCTION PROTOTYPES    */
/* ---------------------------- */
/* process encap messages */
static void local_procrsp_reg_session (EIPC_ENCAP_MSG_STRUCT *encap, EIPC_HANDLE_STRUCT *server_handle_ptr);
static void local_procrsp_ucmm        (EIPC_ENCAP_MSG_STRUCT *encap, EIPC_HANDLE_STRUCT *server_handle_ptr);

/* server handle management functions */
static int16 local_find_free_server_handle (uint32 ipaddr); /* 1 handle per server */
static EIPC_HANDLE_STRUCT * local_get_server_struct (int16 server_handle);
static void local_init_server_handle (EIPC_HANDLE_STRUCT *server_handle_ptr);
static int16 local_get_next_server_handle_id (void);

/* timer functions */
static void local_client_timeout (uint16 timer_ix);

#ifdef EIPC_EM_CLASS3_CNXN_USED
    static void local_em_timeout (uint16 timer_ix);
#endif

#ifdef EIPC_TAG_CLIENT_USED
    static int16 local_buildTagRead_common (uint8 *buf, uint16 max_num_buf_bytes, uint8 tag_cnt, EIPC_TAG_STRUCT *tag_ptr);
    static int16 local_buildTagWrite_common (uint8 *buf, uint16 max_num_buf_bytes, uint8 tag_cnt, EIPC_TAG_STRUCT *tag_ptr);
#endif

#ifdef EIPC_PCCC_CLIENT_USED
    static int16 local_buildPcccRead_common (EIPC_HANDLE_STRUCT *server, uint8 *buf, uint16 max_num_buf_bytes, EIPC_PCCC_STRUCT *pccc_ptr);
    static int16 local_buildPcccWrite_common (EIPC_HANDLE_STRUCT *server, uint8 *buf, uint16 max_num_buf_bytes, EIPC_PCCC_STRUCT *pccc_ptr);
#endif

#ifdef EIPC_EM_CLIENT_USED
    static int16 local_buildEm_common (uint8 *buf, uint16 max_num_buf_bytes, EIPC_EM_STRUCT *em_ptr);
#endif

static int16  local_add_tag_name_to_buffer (uint8 *tag_name, uint16 tag_name_len, uint8 *buf, uint16 max_num_buf_bytes);
static uint32 local_getConnectionID (void);

/* ---------------------------- */
/* STATIC VARIABLES             */
/* ---------------------------- */
static EIPC_HANDLE_STRUCT ServerHandles[EIPC_USEROBJ_MAX_NUM_SERVER_HANDLES];
static int16 NextServerHandle;

/* ---------------------------- */
/* EXTERN VARIABLES             */
/* ---------------------------- */

/* ---------------------------- */
/* MISCELLANEOUS                */
/* ---------------------------- */
#define EIPC_SERVERHANDLE_UNUSED -1

#define EIPC_MAXCNXNTMOMULT 7
EIPC_CODESPACE uint16 EIPC_CNXNTMOMULT[(EIPC_MAXCNXNTMOMULT+1)] = {4,8,16,32,64,128,256,512};

#if EIPC_USEROBJ_RPI_CNXNTMO_MULT > EIPC_MAXCNXNTMOMULT
    #error "EIPC_USEROBJ_RPI_CNXNTMO_MULT too large (eipc_userobj.h) "
#endif

/**/
/* ******************************************************************** */
/*                      GLOBAL FUNCTIONS                                */
/* ******************************************************************** */
/* ====================================================================
Function:   eipc_tagclient_init
Parameters: init_type
Returns:    N/A

This function initializes the ServerHandle structures and other local
variables.
======================================================================= */
void eipc_tagclient_init (uint8 init_type)
{
    uint16 i;
    EIPC_TIMER_DATA_STRUCT *TimerStructPtr;

    /* different initialization based on based parameters */
    switch (init_type)
    {
        /* Out of Box Initialization */
        case EIPC_INIT_OUTOFBOX:
            break;

        /* Normal Initialization */
        case EIPC_INIT_NORMAL:
        default:
            break;
    };

    /* Let's make sure we get a uniques server handle on every request */
    NextServerHandle =  0; /* 0 is invalid for use, but a good init value */

    /* initialize the ServerHandle structures */
    for(i=0; i<EIPC_USEROBJ_MAX_NUM_SERVER_HANDLES; i++)
    {
        // 0 is an invalid server handle
        ServerHandles[i].ServerHandle = EIPC_SERVERHANDLE_UNUSED;

        /* General Timer */
        /* NOTE: Timers only need to be allocated once */
        ServerHandles[i].TimerNum = eipc_timer_new(); // allocate timer
        TimerStructPtr = eipc_timer_get_struct (ServerHandles[i].TimerNum);
        if(TimerStructPtr == NULLPTR)
        {
            eipc_usersys_fatalError("eipc_tagclient_init",0);
        }
        TimerStructPtr->current_value = 0;
        TimerStructPtr->reload_value = 0;
        TimerStructPtr->timeout_flag_ptr = NULL;
        TimerStructPtr->timeout_func_ptr = local_client_timeout;
        eipc_timer_stop(ServerHandles[i].TimerNum);   // make sure timer is stopped 

#ifdef EIPC_EM_CLASS3_CNXN_USED
        /* explicit connection handling */
        ServerHandles[i].EM_CnxnState = EIPC_CLIENT_EMCLASS3CNXNSTATE_NONEXIST;

        /* EM Cnxn Allocate Timer */
        /* NOTE: Timers only need to be allocated once */
        ServerHandles[i].EM_TimerNum = eipc_timer_new(); 
        TimerStructPtr = eipc_timer_get_struct (ServerHandles[i].EM_TimerNum);
        if(TimerStructPtr == NULLPTR)
        {
            eipc_usersys_fatalError("eipc_tagclient_init",0);
        }
        TimerStructPtr->current_value = 0;
        TimerStructPtr->reload_value = 0;
        TimerStructPtr->timeout_flag_ptr = NULL;
        TimerStructPtr->timeout_func_ptr = local_em_timeout;
        eipc_timer_stop(ServerHandles[i].EM_TimerNum);   // make sure timer is stopped 
#endif

        /* Initialize user defined variables */
        local_init_server_handle (&ServerHandles[i]);     
    }
}

/* ====================================================================
Function:   eipc_tagclient_process
Parameters: N/A
Returns:    N/A

This function handles any tag client processing.
======================================================================= */
void eipc_tagclient_process (void)
{
    /* nothing to do */
}

/* ====================================================================
Function:     eipc_tagclient_onConnect
Parameters:   socket_id
Returns:      N/A

This function looks through the Server Handles to find which one is now
connected, then send the register session encapsulated command to the
server.
======================================================================= */
void eipc_tagclient_onConnect (EIPC_USERSYS_SOCKTYPE socket_id)
{
    uint16 i;
	uint8 msg[28];
//	int return_code2;
//	char recvbuf[32] = "";

    // find which server we connected to
    for(i=0; i<EIPC_USEROBJ_MAX_NUM_SERVER_HANDLES; i++)
    {
        // 0 is an invalid server handle
        if((ServerHandles[i].SockID == socket_id) && (ServerHandles[i].UCMMState == EIPC_CLIENT_UCMMSERVERSTATE_NONEXIST))
        {
            eipc_user_dbprint1("eipc_tagclient_onConnect(%d)\r\n",ServerHandles[i].ServerHandle);

            /* stop the timer */
            eipc_timer_stop (ServerHandles[i].TimerNum);
 
            /* update the state to look for the Register Session response */
            ServerHandles[i].UCMMState = EIPC_CLIENT_UCMMSERVERSTATE_REGSES; 
            eipc_usersys_UCMMStateChanged (ServerHandles[i].ServerHandle, EIPC_CLIENT_UCMMSERVERSTATE_REGSES);

            /* build the Register Session message */
            memset(msg, 0, 28);
            rta_PutLitEndian16(EIP_ENCAPCMD_REGISTERSESSION, msg+0); // command
            ServerHandles[i].LastEncapCmd = EIP_ENCAPCMD_REGISTERSESSION;
            rta_PutLitEndian32(4,   msg+2); // length
            rta_PutLitEndian16(1,   msg+24); // encap data -> protocol version
            rta_PutLitEndian16(0,   msg+26); // encap data -> option flags

            /* send the Register Session message */
            eipc_usersock_sendData (socket_id, msg, 28);
            return; // we found the ID, stop looking
        }
    }
}

/* ====================================================================
Function:     eipc_tagclient_onClose
Parameters:   socket_id
Returns:      N/A

This function looks through the Server Handles to find which one uses
the passed TCP socket and frees the resources and calls the user to 
inform them the close occurred.
======================================================================= */
void eipc_tagclient_onClose (EIPC_USERSYS_SOCKTYPE socket_id)
{
    uint16 i;
    uint16 server_handle;

    eipc_user_dbprint1("eipc_tagclient_onClose(%d)\r\n",socket_id);

    // find which server we connected to
    for(i=0; i<EIPC_USEROBJ_MAX_NUM_SERVER_HANDLES; i++)
    {
        // 0 is an invalid server handle
        if(ServerHandles[i].SockID == socket_id)
        {
            // we'll need to inform the user this handle was closed
            server_handle = ServerHandles[i].ServerHandle;

            // free the resources
            local_init_server_handle (&ServerHandles[i]);     

            // inform the user of the close
            eipc_usersys_UCMMStateChanged (server_handle, EIPC_CLIENT_UCMMSERVERSTATE_NONEXIST);

            // we found the ID, stop looking
            return; 
        }
    }
}

/* ====================================================================
Function:   eipc_tagclient_onTCPData
Parameters: socket id
            socket data buffer
            socket data size
Returns:    0  - Success
            <0 - Failure

This function is called when TCP data is received.
======================================================================= */
uint16 eipc_tagclient_onTCPData (EIPC_USERSYS_SOCKTYPE socket_id, uint8 * socket_data, uint16 socket_data_size)
{
    EIPC_ENCAP_MSG_STRUCT encap;
    uint16 i;
 
  //  eipc_user_dbprint2("eipc_tagclient_onTCPData(%d) - %d bytes\r\n",socket_id,socket_data_size);

    /* Make sure we have the complete message */
    if(socket_data_size < EIP_ENCAP_HEADER_SIZ)
        return(socket_data_size);  

    /* Parse the Encapsulated message */
    encap.Command       = rta_GetLitEndian16 (socket_data+0);
    encap.Length        = rta_GetLitEndian16 (socket_data+2);
    encap.SessionHandle = rta_GetLitEndian32 (socket_data+4);
    encap.Status        = rta_GetLitEndian32 (socket_data+8);
    for(i=0; i<8; i++)
        encap.SenderContext[i] = *(socket_data+12+i);
    encap.Options = rta_GetLitEndian32(socket_data+20);
    encap.EncapsulatedData = (socket_data + EIP_ENCAP_HEADER_SIZ);
   
    /* if we don't have the complete encapsulated message, return */
    if(socket_data_size < (encap.Length+EIP_ENCAP_HEADER_SIZ))
        return(socket_data_size);  

    // find which server we connected to
    for(i=0; i<EIPC_USEROBJ_MAX_NUM_SERVER_HANDLES && ServerHandles[i].SockID != socket_id; i++);

    // we found the socket
    if(i < EIPC_USEROBJ_MAX_NUM_SERVER_HANDLES)
    {
        /* switch on the encapsulated command */
        switch(encap.Command)
        {
            // Register Session
            case EIP_ENCAPCMD_REGISTERSESSION:
                local_procrsp_reg_session (&encap, &ServerHandles[i]);
                break;

            // we shouldn't get this since we should have the socket closed first
            case EIP_ENCAPCMD_UNREGISTERSESSION:
                // verify the session is for us
                if(encap.SessionHandle == ServerHandles[i].SessionID)
                    eipc_tagclient_onClose(socket_id);
                break;

            case EIP_ENCAPCMD_SENDRRDATA:
            case EIP_ENCAPCMD_SENDUNITDATA:
                local_procrsp_ucmm(&encap, &ServerHandles[i]);
                break;
        };
    }

    // remove the message from the buffer
    return ((socket_data_size - (encap.Length+EIP_ENCAP_HEADER_SIZ))); 
}

/* ====================================================================
Function:   eipc_tagclient_connectToPLC
Parameters: IP Address
Returns:    >0 - Server Handle
            <0 - Failure

This function attempts to connect to the passed PLC IP Address.
======================================================================= */
int16 eipc_tagclient_connectToPLC (uint32 ip_addr)
{
    int16 serv_handle;
    EIPC_HANDLE_STRUCT *server;

    eipc_user_dbprint0("eipc_tagclient_connectToPLC\r\n");

    // make sure the IP address is non-zero
    if(ip_addr == 0)
        return(EIPC_CLIENT_UCMMERR_SUCCESS);
   
    // get a server handle
    serv_handle = local_find_free_server_handle(ip_addr);

    // we didn't get the server handle
    if(serv_handle == EIPC_SERVERHANDLE_UNUSED)
        return(EIPC_CLIENT_UCMMERR_SERVHAND);

    // get the server handle structure
    server = local_get_server_struct(serv_handle);

    // we didn't get the server structure
    if(server == NULLPTR)
        return(EIPC_CLIENT_UCMMERR_SERVHAND);

    /* start a timer to timeout if we don't connect */
    eipc_timer_newval(server->TimerNum, EIPC_USERSYS_TMORATE_CONN_TMO);
    eipc_timer_reset (server->TimerNum);

    // set the state to waiting for connect 
    server->UCMMState = EIPC_CLIENT_UCMMSERVERSTATE_NONEXIST;

    // connect to the server
    server->SockID = eipc_usersock_connect(ip_addr);

    // success
    return(serv_handle);
}

/* ====================================================================
Function:   eipc_tagclient_disconnectFromPLC
Parameters: server handle
Returns:    0  - Success
            <0 - Failure

This function sends the close request to the passed PLC IP Address.
======================================================================= */
int16 eipc_tagclient_disconnectFromPLC (int16 server_handle)
{
    EIPC_HANDLE_STRUCT *server;

    eipc_user_dbprint1("eipc_tagclient_disconnectFromPLC(%d)\r\n",server_handle);

    // get the server pointer
    server = local_get_server_struct(server_handle);

    // validate the server isn't NULL
    if(server == NULL)
        return(EIPC_CLIENT_UCMMERR_SERVHAND);

    // free the resources
    local_init_server_handle (server);  

    // return SUCCESS   
    return(EIPC_CLIENT_UCMMERR_SUCCESS);
}

/* ====================================================================
Function:   eipc_tagclient_sendTagRead_unconnected
Parameters: server handle
            message timeout (in ticks)
            tag count 
            tag configuration array[tag count]
Returns:    0  - Success
            <0 - Failure

This function validates the read request as best as possible and
sends the message to the passed PLC. Responses (or timeouts) are 
reported to the user via "eipc_userobj_procTagReadResp()".
======================================================================= */
#ifdef EIPC_TAG_CLIENT_USED
int16 eipc_tagclient_sendTagRead_unconnected (int16 server_handle, uint32 tmo_in_ticks, uint8 plc_slot, uint8 tag_cnt, EIPC_TAG_STRUCT *tag_ptr)
{
    EIPC_HANDLE_STRUCT *server;
    uint8   msg[EIPC_CPF_MAX_ITEM_DATA_LEN];
    uint16  msg_size, i; //path_word_size_ix;
//    uint16  multireq_offsetix, mult_ix, mult_base_ix;
    uint16  exp_msg_size;
    int16   return_code;

//    eipc_user_dbprint1("eipc_tagclient_sendTagRead(%d)\r\n",server_handle);

    // get the server pointer
    server = local_get_server_struct(server_handle);

    // verify the server handle
    if(server == NULL)
        return(EIPC_CLIENT_UCMMERR_SERVHAND);

    /* make sure a message isn't already in progress */
    if(server->UCMMState != EIPC_CLIENT_UCMMSERVERSTATE_READY)
        return(EIPC_CLIENT_UCMMERR_BUSY);

    // verify the timeout is 100ms or larger
    if(tmo_in_ticks < EIPC_USEROBJ_MINTMOVAL)
        return(EIPC_CLIENT_UCMMERR_TMOINVALID);

    // verify the tag count
    if((tag_cnt == 0) || (tag_cnt > EIPC_USEROBJ_MAXTAGS_PER_MSG))
        return(EIPC_CLIENT_UCMMERR_TAGCNT);

    // verify the tag pointer isn't NULL
    if(tag_ptr == NULL)
        return(EIPC_CLIENT_UCMMERR_TAGPTR);

    // verify the tag format (for all tags)
    // copy the request data so we can use it on the response
    server->tag_cnt = tag_cnt;
    exp_msg_size = 75; // default message size (it is actually smaller)
    for(i=0; i<tag_cnt; i++)
    {
        // tag name size error
        if(tag_ptr[i].tag_name_len > EIPC_USEROBJ_TAGNAME_SIZE)
            return(EIPC_CLIENT_UCMMERR_TAGFMT);

        // copy this entry
        memcpy(server->tag_ptr[i].tag_name, tag_ptr[i].tag_name, tag_ptr[i].tag_name_len);
        server->tag_ptr[i].tag_name_len = tag_ptr[i].tag_name_len;
        server->tag_ptr[i].tag_offset = tag_ptr[i].tag_offset;

        // add in the number of characters
        exp_msg_size += tag_ptr[i].tag_name_len + 10;
    }
    
    // verify the message will fit
    if(exp_msg_size > EIPC_CPF_MAX_ITEM_DATA_LEN)
        return(EIPC_CLIENT_UCMMERR_TAGFMT);
    
    // ********************************************************
    //          build and send the message
    // ********************************************************

    /*
        ===========================
        REQUEST/RESPONSE VALIDATION
        ===========================

        FIELD NAME         FIElD VALUE
        ----------         -----------
        Command            SendRRData (0x6F)
        Length             varies
        Session Handle     passed
        Status             shall be 0
        Sender Context     shall be 0
        Options            shall be 0
        Encapsulated Data
24      Interface Handle (4 bytes) shall be 0
28      Timeout          (2 bytes) passed
30      Item Count       (2 bytes) shall be 2
32      Addr Item Code   (2 bytes) shall be 0
34      Addr Item Len    (2 bytes) shall be 0
36      Data Item Code   (2 bytes) shall be 0x00B2
38      Data Item Len    (2 bytes) varies
40      Data Item Data   (varies in length) varies in data
    */

    /* build the fixed part of the message */
    memset(msg, 0, EIPC_CPF_MAX_ITEM_DATA_LEN);

    /* SEND RR DATA - UNCONNECTED */
    server->LastEncapCmd = EIP_ENCAPCMD_SENDRRDATA;

    // Encapsulation Header
    rta_PutLitEndian16(EIP_ENCAPCMD_SENDRRDATA, msg+0); // Encap - Command - Send RR Data (uint16)
    rta_PutLitEndian16(0, msg+2);                       // Encap - Length (uint16) (Filled in later)
    rta_PutLitEndian32(server->SessionID, msg+4);       // Encap - Session handle (uint32)
    rta_PutLitEndian32(0, msg+8);                       // Encap - Status (uint32)
    rta_PutLitEndian32(0, msg+12);                      // Encap - Sender Context HI (uint32)
    rta_PutLitEndian32(0, msg+16);                      // Encap - Sender Context LO (uint32)
    rta_PutLitEndian32(0, msg+20);                      // Encap - Options (uint32) 

    // Command Specific Data
    rta_PutLitEndian32(0, msg+24);                      // Interface Handle (uint32)
    rta_PutLitEndian16(1024, msg+28);                   // Timeout (uint16)
    rta_PutLitEndian16(2, msg+30);                      // Item Count
    rta_PutLitEndian16(ADDR_TYP_ID_NULL, msg+32);       // Item 1 - Address Item
    rta_PutLitEndian16(0, msg+34);                      // Item 1 - Length
    //rta_PutLitEndian16(2, msg+30);                    // Item 1 - No Data
    rta_PutLitEndian16(DATA_TYP_ID_UCMM, msg+36);       // Item 2 - Data Item
    rta_PutLitEndian16(2, msg+38);                      // Item 2 - Length
    msg_size = 40;

    /* build the passed part of the message */
    msg[msg_size++] = 0x52; // UnCnSndCmd: Unconnected Send Command
    msg[msg_size++] = 0x02; // UnCnSndCmd: path size
    msg[msg_size++] = 0x20; // UnCnSndCmd: 8-bit class
    msg[msg_size++] = 0x06; // UnCnSndCmd: Connection Manager
    msg[msg_size++] = 0x24; // UnCnSndCmd: 8-bit instance
    msg[msg_size++] = 0x01; // UnCnSndCmd: Instance 1
    msg[msg_size++] = 0x07; // UnCnSndCmd: Priority/Time
    msg[msg_size++] = 0x80; // UnCnSndCmd: Timeout Ticks
    msg_size+=2;            // UnCnSndCmd: Message Request Size (filled in later)

    // a portion of the message is common for the connected and unconnected version
    return_code = local_buildTagRead_common(&msg[msg_size], (sizeof(msg)-(msg_size+4)), tag_cnt, tag_ptr);

    // was the data sucessfully stored?
    if(return_code < 0)
    {
        return(EIPC_CLIENT_UCMMERR_TAGPTR);
    }

    // advance the pointer based on the amount used
    msg_size+=return_code;    

    // we need to route the message to the Logix controller via the backplane
    msg[msg_size++] = 1;        // UnCnSndCmd: Number of Words in path
    msg[msg_size++] = 0;        // UnCnSndCmd: Reserved
    msg[msg_size++] = 1;        // UnCnSndCmd: Route Path Port 1 (Backplane)
    msg[msg_size++] = plc_slot; // UnCnSndCmd: (Slot with Controller)

    /* store the Encap Length and Data Item Length */
    rta_PutLitEndian16((uint16)(msg_size-EIP_ENCAP_HEADER_SIZ), msg+2); // encap length
    rta_PutLitEndian16((uint16)(msg_size-40),  msg+38); // data item length
    rta_PutLitEndian16((uint16)(msg_size-54),  msg+48); //UnCnSndCmd: Message Request Size

    // send the message to the server
    if(eipc_usersock_sendData (server->SockID, msg, msg_size) == 0)
    {
        // inform the user that the UCMM is busy 
        server->UCMMState = EIPC_CLIENT_UCMMSERVERSTATE_BUSY;
        eipc_usersys_UCMMStateChanged (server->ServerHandle, EIPC_CLIENT_UCMMSERVERSTATE_BUSY);

        // start the timeout
        eipc_timer_newval(server->TimerNum, tmo_in_ticks);
        eipc_timer_reset(server->TimerNum);

        return(EIPC_CLIENT_UCMMERR_SUCCESS);
    }
    
    // send failed
    return(EIPC_CLIENT_UCMMERR_SERVHAND);
}
#endif /* #ifdef EIPC_TAG_CLIENT_USED */

/* ====================================================================
Function:   eipc_tagclient_sendTagWrite_unconnected
Parameters: server handle
            message timeout (in ticks)
            tag count 
            tag configuration array[tag count]
Returns:    0  - Success
            <0 - Failure

This function validates the write request as best as possible and
sends the message to the passed PLC. Responses (or timeouts) are 
reported to the user via "eipc_userobj_procTagWriteResp()".
======================================================================= */
#ifdef EIPC_TAG_CLIENT_USED
int16 eipc_tagclient_sendTagWrite_unconnected (int16 server_handle, uint32 tmo_in_ticks, uint8 plc_slot, uint8 tag_cnt, EIPC_TAG_STRUCT *tag_ptr)
{
    EIPC_HANDLE_STRUCT *server;
    uint8   msg[EIPC_CPF_MAX_ITEM_DATA_LEN];
    uint16  msg_size, i;
    uint16  exp_msg_size;
    int16   return_code;

//    eipc_user_dbprint1("eipc_tagclient_sendTagWrite(%d)\r\n",server_handle);

    // get the server pointer
    server = local_get_server_struct(server_handle);

    // verify the server handle
    if(server == NULL)
        return(EIPC_CLIENT_UCMMERR_SERVHAND);

    /* make sure a message isn't already in progress */
    if(server->UCMMState != EIPC_CLIENT_UCMMSERVERSTATE_READY)
        return(EIPC_CLIENT_UCMMERR_BUSY);

    // verify the timeout is 100ms or larger
    if(tmo_in_ticks < EIPC_USEROBJ_MINTMOVAL)
        return(EIPC_CLIENT_UCMMERR_TMOINVALID);

    // verify the tag count
    if((tag_cnt == 0) || (tag_cnt > EIPC_USEROBJ_MAXTAGS_PER_MSG))
        return(EIPC_CLIENT_UCMMERR_TAGCNT);

    // verify the tag pointer isn't NULL
    if(tag_ptr == NULL)
        return(EIPC_CLIENT_UCMMERR_TAGPTR);

    // verify the tag format (for all tags)
    // copy the request data so we can use it on the response
    server->tag_cnt = tag_cnt;
    exp_msg_size = 75; // default message size (it is actually smaller)
    for(i=0; i<tag_cnt; i++)
    {
        // tag name size error
        if(tag_ptr[i].tag_name_len > EIPC_USEROBJ_TAGNAME_SIZE)
            return(EIPC_CLIENT_UCMMERR_TAGFMT);

        // copy this entry
        memcpy(server->tag_ptr[i].tag_name, tag_ptr[i].tag_name, tag_ptr[i].tag_name_len);
        server->tag_ptr[i].tag_name_len = tag_ptr[i].tag_name_len;
        server->tag_ptr[i].tag_offset = tag_ptr[i].tag_offset;

        // add in the number of characters, data length
        exp_msg_size += tag_ptr[i].tag_name_len + 12 + tag_ptr[i].tag_data_len;
    }
    
    // verify the message will fit
    if(exp_msg_size > EIPC_CPF_MAX_ITEM_DATA_LEN)
        return(EIPC_CLIENT_UCMMERR_TAGFMT);
    
    // ********************************************************
    //          build and send the message
    // ********************************************************

    /*
        ===========================
        REQUEST/RESPONSE VALIDATION
        ===========================

        FIELD NAME         FIElD VALUE
        ----------         -----------
        Command            SendRRData (0x6F)
        Length             varies
        Session Handle     passed
        Status             shall be 0
        Sender Context     shall be 0
        Options            shall be 0
        Encapsulated Data
24      Interface Handle (4 bytes) shall be 0
28      Timeout          (2 bytes) passed
30      Item Count       (2 bytes) shall be 2
32      Addr Item Code   (2 bytes) shall be 0
34      Addr Item Len    (2 bytes) shall be 0
36      Data Item Code   (2 bytes) shall be 0x00B2
38      Data Item Len    (2 bytes) varies
40      Data Item Data   (varies in length) varies in data
    */

    /* SEND RR DATA - UNCONNECTED */
    server->LastEncapCmd = EIP_ENCAPCMD_SENDRRDATA;

    /* build the fixed part of the message */
    memset(msg, 0, EIPC_CPF_MAX_ITEM_DATA_LEN);
    rta_PutLitEndian16(EIP_ENCAPCMD_SENDRRDATA,      msg+0); // command
    rta_PutLitEndian32(server->SessionID, msg+4);   // session handle
    rta_PutLitEndian16(2,        msg+30);           // item count
    rta_PutLitEndian16(178,      msg+36);           // data item code
    msg_size = 40;

    /* build the passed part of the message */
    msg[msg_size++] = 0x52; // UnCnSndCmd: Unconnected Send Command
    msg[msg_size++] = 0x02; // UnCnSndCmd: path size
    msg[msg_size++] = 0x20; // UnCnSndCmd: 8-bit class
    msg[msg_size++] = 0x06; // UnCnSndCmd: Connection Manager
    msg[msg_size++] = 0x24; // UnCnSndCmd: 8-bit instance
    msg[msg_size++] = 0x01; // UnCnSndCmd: Instance 1
    msg[msg_size++] = 0x07; // UnCnSndCmd: Priority/Time
    msg[msg_size++] = 0x80; // UnCnSndCmd: Timeout Ticks
    msg_size+=2;            // UnCnSndCmd: Message Request Size (filled in later)


    // a portion of the message is common for the connected and unconnected version
    return_code = local_buildTagWrite_common(&msg[msg_size], (sizeof(msg)-(msg_size+4)), tag_cnt, tag_ptr);

    // was the data sucessfully stored?
    if(return_code < 0)
    {
        return(EIPC_CLIENT_UCMMERR_TAGPTR);
    }

    // advance the pointer based on the amount used
    msg_size+=return_code;    

    // we need to route the message to the Logix controller via the backplane
    msg[msg_size++] = 1;        // UnCnSndCmd: Number of Words in path
    msg[msg_size++] = 0;        // UnCnSndCmd: Reserved
    msg[msg_size++] = 1;        // UnCnSndCmd: Route Path Port 1 (Backplane)
    msg[msg_size++] = plc_slot; // UnCnSndCmd: (Slot with Controller)

    /* store the Encap Length and Data Item Length */
    rta_PutLitEndian16((uint16)(msg_size-EIP_ENCAP_HEADER_SIZ), msg+2); // encap length
    rta_PutLitEndian16((uint16)(msg_size-40),  msg+38); // data item length
    rta_PutLitEndian16((uint16)(msg_size-54),  msg+48); //UnCnSndCmd: Message Request Size

    // send the message to the server
    if(eipc_usersock_sendData (server->SockID, msg, msg_size) == 0)
    {
        // inform the user that the UCMM is busy 
        server->UCMMState = EIPC_CLIENT_UCMMSERVERSTATE_BUSY;
        eipc_usersys_UCMMStateChanged (server->ServerHandle, EIPC_CLIENT_UCMMSERVERSTATE_BUSY);

        // start the timeout
        eipc_timer_newval(server->TimerNum, tmo_in_ticks);
        eipc_timer_reset(server->TimerNum);

        return(EIPC_CLIENT_UCMMERR_SUCCESS);
    }
    
    // send failed
    return(EIPC_CLIENT_UCMMERR_SERVHAND);
}
#endif /* #ifdef EIPC_TAG_CLIENT_USED */

/* ====================================================================
Function:   eipc_tagclient_sendTagRead_connected
Parameters: server handle
            tag count 
            tag configuration array[tag count]
Returns:    0  - Success
            <0 - Failure

This function validates the read request as best as possible and
sends the message to the passed PLC. Responses (or timeouts) are 
reported to the user via "eipc_userobj_procTagReadResp()".
======================================================================= */
#ifdef EIPC_TAG_CLIENT_USED
#ifdef EIPC_EM_CLASS3_CNXN_USED
int16 eipc_tagclient_sendTagRead_connected  (int16 server_handle, uint8 tag_cnt, EIPC_TAG_STRUCT *tag_ptr)
{
    EIPC_HANDLE_STRUCT *server;
    uint8   msg[EIPC_CPF_MAX_ITEM_DATA_LEN];
    uint16  msg_size, i; //path_word_size_ix;
//    uint16  multireq_offsetix, mult_ix, mult_base_ix;
    uint16  exp_msg_size;
    int16   return_code;

//    eipc_user_dbprint1("eipc_tagclient_sendTagRead(%d)\r\n",server_handle);

    // get the server pointer
    server = local_get_server_struct(server_handle);

    // verify the server handle
    if(server == NULL)
        return(EIPC_CLIENT_UCMMERR_SERVHAND);

    /* make sure a message isn't already in progress */
    if(server->EM_CnxnState != EIPC_CLIENT_EMCLASS3CNXNSTATE_READY)
        return(EIPC_CLIENT_UCMMERR_BUSY);

    // verify the tag count
    if((tag_cnt == 0) || (tag_cnt > EIPC_USEROBJ_MAXTAGS_PER_MSG))
        return(EIPC_CLIENT_UCMMERR_TAGCNT);

    // verify the tag pointer isn't NULL
    if(tag_ptr == NULL)
        return(EIPC_CLIENT_UCMMERR_TAGPTR);

    // verify the tag format (for all tags)
    // copy the request data so we can use it on the response
    server->tag_cnt = tag_cnt;
    exp_msg_size = 75; // default message size (it is actually smaller)
    for(i=0; i<tag_cnt; i++)
    {
        // tag name size error
        if(tag_ptr[i].tag_name_len > EIPC_USEROBJ_TAGNAME_SIZE)
            return(EIPC_CLIENT_UCMMERR_TAGFMT);

        // copy this entry
        memcpy(server->tag_ptr[i].tag_name, tag_ptr[i].tag_name, tag_ptr[i].tag_name_len);
        server->tag_ptr[i].tag_name_len = tag_ptr[i].tag_name_len;
        server->tag_ptr[i].tag_offset = tag_ptr[i].tag_offset;

        // add in the number of characters
        exp_msg_size += tag_ptr[i].tag_name_len + 10;
    }
    
    // verify the message will fit
    if(exp_msg_size > EIPC_CPF_MAX_ITEM_DATA_LEN)
        return(EIPC_CLIENT_UCMMERR_TAGFMT);
    
    // ********************************************************
    //          build and send the message
    // ********************************************************

    /*
        ===========================
        REQUEST/RESPONSE VALIDATION
        ===========================

        FIELD NAME         FIElD VALUE
        ----------         -----------
        Command            SendRRData (0x6F)
        Length             varies
        Session Handle     passed
        Status             shall be 0
        Sender Context     shall be 0
        Options            shall be 0
        Encapsulated Data
24      Interface Handle (4 bytes) shall be 0
28      Timeout          (2 bytes) passed
30      Item Count       (2 bytes) shall be 2
32      Addr Item Code   (2 bytes) shall be 0
34      Addr Item Len    (2 bytes) shall be 0
36      Data Item Code   (2 bytes) shall be 0x00B2
38      Data Item Len    (2 bytes) varies
40      Data Item Data   (varies in length) varies in data
    */

    /* build the fixed part of the message */
    memset(msg, 0, EIPC_CPF_MAX_ITEM_DATA_LEN);

    /* SEND RR DATA - UNCONNECTED */
    server->LastEncapCmd = EIP_ENCAPCMD_SENDUNITDATA;

    // Encapsulation Header
    rta_PutLitEndian16(EIP_ENCAPCMD_SENDUNITDATA, msg+0); // Encap - Command - Send Unit Data (uint16)
    rta_PutLitEndian16(0, msg+2);                         // Encap - Length (uint16) (Filled in later)
    rta_PutLitEndian32(server->SessionID, msg+4);         // Encap - Session handle (uint32)
    rta_PutLitEndian32(0, msg+8);                         // Encap - Status (uint32)
    rta_PutLitEndian32(0, msg+12);                        // Encap - Sender Context HI (uint32)
    rta_PutLitEndian32(0, msg+16);                        // Encap - Sender Context LO (uint32)
    rta_PutLitEndian32(0, msg+20);                        // Encap - Options (uint32) 

    // Command Specific Data
    rta_PutLitEndian32(0, msg+24);                       // Interface Handle (uint32)
    rta_PutLitEndian16(1024, msg+28);                    // Timeout (uint16)
    rta_PutLitEndian16(2, msg+30);                       // Item Count
    rta_PutLitEndian16(ADDR_TYP_ID_CNXNBASED, msg+32);   // Item 1 - Address Item
    rta_PutLitEndian16(4, msg+34);                       // Item 1 - Length = 4
    rta_PutLitEndian32(server->EM_O2T_CnxnID, msg+36);   // Item 1 - Connection ID (uint32) 

    rta_PutLitEndian16(DATA_TYP_ID_PDU, msg+40);         // Item 2 - Data Item
    rta_PutLitEndian16(0, msg+42);                       // Item 2 - Length (later)
    server->EM_O2T_SeqNum++;    // pre-increment so we can compare the response
    rta_PutLitEndian16(server->EM_O2T_SeqNum, msg+44);   // Item 2 - Sequence Count

    msg_size = 46;

#if 0
    /* build the passed part of the message */
    msg[msg_size++] = 0x52; // UnCnSndCmd: Unconnected Send Command
    msg[msg_size++] = 0x02; // UnCnSndCmd: path size
    msg[msg_size++] = 0x20; // UnCnSndCmd: 8-bit class
    msg[msg_size++] = 0x06; // UnCnSndCmd: Connection Manager
    msg[msg_size++] = 0x24; // UnCnSndCmd: 8-bit instance
    msg[msg_size++] = 0x01; // UnCnSndCmd: Instance 1
    msg[msg_size++] = 0x07; // UnCnSndCmd: Priority/Time
    msg[msg_size++] = 0x80; // UnCnSndCmd: Timeout Ticks
    msg_size+=2;            // UnCnSndCmd: Message Request Size (filled in later)
#endif

    // a portion of the message is common for the connected and unconnected version
    return_code = local_buildTagRead_common(&msg[msg_size], (sizeof(msg)-(msg_size+4)), tag_cnt, tag_ptr);

    // was the data sucessfully stored?
    if(return_code < 0)
    {
        return(EIPC_CLIENT_UCMMERR_TAGPTR);
    }

    // advance the pointer based on the amount used
    msg_size+=return_code;    

#if 0
    // we need to route the message to the Logix controller via the backplane
    msg[msg_size++] = 1;        // UnCnSndCmd: Number of Words in path
    msg[msg_size++] = 0;        // UnCnSndCmd: Reserved
    msg[msg_size++] = 1;        // UnCnSndCmd: Route Path Port 1 (Backplane)
    msg[msg_size++] = plc_slot; // UnCnSndCmd: (Slot with Controller)
#endif

    /* store the Encap Length and Data Item Length */
    rta_PutLitEndian16((uint16)(msg_size-EIP_ENCAP_HEADER_SIZ), msg+2); // encap length
    rta_PutLitEndian16((uint16)(msg_size-44),  msg+42); // data item length
//    rta_PutLitEndian16((uint16)(msg_size-54),  msg+48); //UnCnSndCmd: Message Request Size

    // send the message to the server
    if(eipc_usersock_sendData (server->SockID, msg, msg_size) == 0)
    {
        // inform the user that the UCMM is busy 
        server->EM_CnxnState = EIPC_CLIENT_UCMMSERVERSTATE_BUSY;
        eipc_usersys_EmCnxnStateChanged (server->EM_CnxnState, EIPC_CLIENT_EMCLASS3CNXNSTATE_BUSY);

        // reset the timeout
        eipc_timer_reset(server->EM_TimerNum);

        return(EIPC_CLIENT_UCMMERR_SUCCESS);
    }
    
    // send failed
    return(EIPC_CLIENT_UCMMERR_SERVHAND);
}
#endif /* EIPC_EM_CLASS3_CNXN_USED */
#endif /* #ifdef EIPC_TAG_CLIENT_USED */

/* ====================================================================
Function:   eipc_tagclient_sendTagWrite_connected
Parameters: server handle
            tag count 
            tag configuration array[tag count]
Returns:    0  - Success
            <0 - Failure

This function validates the write request as best as possible and
sends the message to the passed PLC. Responses (or timeouts) are 
reported to the user via "eipc_userobj_procTagReadResp()".
======================================================================= */
#ifdef EIPC_TAG_CLIENT_USED
#ifdef EIPC_EM_CLASS3_CNXN_USED
int16 eipc_tagclient_sendTagWrite_connected (int16 server_handle, uint8 tag_cnt, EIPC_TAG_STRUCT *tag_ptr)
{
    EIPC_HANDLE_STRUCT *server;
    uint8   msg[EIPC_CPF_MAX_ITEM_DATA_LEN];
    uint16  msg_size, i;
    uint16  exp_msg_size;
    int16   return_code;

//    eipc_user_dbprint1("eipc_tagclient_sendTagWrite_connected(%d)\r\n",server_handle);

    // get the server pointer
    server = local_get_server_struct(server_handle);

    // verify the server handle
    if(server == NULL)
        return(EIPC_CLIENT_UCMMERR_SERVHAND);

    /* make sure a message isn't already in progress */
    if(server->EM_CnxnState != EIPC_CLIENT_EMCLASS3CNXNSTATE_READY)
        return(EIPC_CLIENT_UCMMERR_BUSY);

    // verify the tag count
    if((tag_cnt == 0) || (tag_cnt > EIPC_USEROBJ_MAXTAGS_PER_MSG))
        return(EIPC_CLIENT_UCMMERR_TAGCNT);

    // verify the tag pointer isn't NULL
    if(tag_ptr == NULL)
        return(EIPC_CLIENT_UCMMERR_TAGPTR);

    // verify the tag format (for all tags)
    // copy the request data so we can use it on the response
    server->tag_cnt = tag_cnt;
    exp_msg_size = 75; // default message size (it is actually smaller)
    for(i=0; i<tag_cnt; i++)
    {
        // tag name size error
        if(tag_ptr[i].tag_name_len > EIPC_USEROBJ_TAGNAME_SIZE)
            return(EIPC_CLIENT_UCMMERR_TAGFMT);

        // copy this entry
        memcpy(server->tag_ptr[i].tag_name, tag_ptr[i].tag_name, tag_ptr[i].tag_name_len);
        server->tag_ptr[i].tag_name_len = tag_ptr[i].tag_name_len;
        server->tag_ptr[i].tag_offset = tag_ptr[i].tag_offset;

        // add in the number of characters, data length
        exp_msg_size += tag_ptr[i].tag_name_len + 12 + tag_ptr[i].tag_data_len;
    }
    
    // verify the message will fit
    if(exp_msg_size > EIPC_CPF_MAX_ITEM_DATA_LEN)
        return(EIPC_CLIENT_UCMMERR_TAGFMT);
    
    // ********************************************************
    //          build and send the message
    // ********************************************************

    /*
        ===========================
        REQUEST/RESPONSE VALIDATION
        ===========================

        FIELD NAME         FIElD VALUE
        ----------         -----------
        Command            SendRRData (0x6F)
        Length             varies
        Session Handle     passed
        Status             shall be 0
        Sender Context     shall be 0
        Options            shall be 0
        Encapsulated Data
24      Interface Handle (4 bytes) shall be 0
28      Timeout          (2 bytes) passed
30      Item Count       (2 bytes) shall be 2
32      Addr Item Code   (2 bytes) shall be 0
34      Addr Item Len    (2 bytes) shall be 0
36      Data Item Code   (2 bytes) shall be 0x00B2
38      Data Item Len    (2 bytes) varies
40      Data Item Data   (varies in length) varies in data
    */

    /* build the fixed part of the message */
    memset(msg, 0, EIPC_CPF_MAX_ITEM_DATA_LEN);

    /* SEND RR DATA - UNCONNECTED */
    server->LastEncapCmd = EIP_ENCAPCMD_SENDUNITDATA;

    // Encapsulation Header
    rta_PutLitEndian16(EIP_ENCAPCMD_SENDUNITDATA, msg+0); // Encap - Command - Send Unit Data (uint16)
    rta_PutLitEndian16(0, msg+2);                         // Encap - Length (uint16) (Filled in later)
    rta_PutLitEndian32(server->SessionID, msg+4);         // Encap - Session handle (uint32)
    rta_PutLitEndian32(0, msg+8);                         // Encap - Status (uint32)
    rta_PutLitEndian32(0, msg+12);                        // Encap - Sender Context HI (uint32)
    rta_PutLitEndian32(0, msg+16);                        // Encap - Sender Context LO (uint32)
    rta_PutLitEndian32(0, msg+20);                        // Encap - Options (uint32) 

    // Command Specific Data
    rta_PutLitEndian32(0, msg+24);                       // Interface Handle (uint32)
    rta_PutLitEndian16(1024, msg+28);                    // Timeout (uint16)
    rta_PutLitEndian16(2, msg+30);                       // Item Count
    rta_PutLitEndian16(ADDR_TYP_ID_CNXNBASED, msg+32);   // Item 1 - Address Item
    rta_PutLitEndian16(4, msg+34);                       // Item 1 - Length = 4
    rta_PutLitEndian32(server->EM_O2T_CnxnID, msg+36);   // Item 1 - Connection ID (uint32) 

    rta_PutLitEndian16(DATA_TYP_ID_PDU, msg+40);         // Item 2 - Data Item
    rta_PutLitEndian16(0, msg+42);                       // Item 2 - Length (later)
    server->EM_O2T_SeqNum++;    // pre-increment so we can compare the response
    rta_PutLitEndian16(server->EM_O2T_SeqNum, msg+44);   // Item 2 - Sequence Count

    msg_size = 46;

    // a portion of the message is common for the connected and unconnected version
    return_code = local_buildTagWrite_common(&msg[msg_size], (sizeof(msg)-(msg_size+4)), tag_cnt, tag_ptr);

    // was the data sucessfully stored?
    if(return_code < 0)
    {
        return(EIPC_CLIENT_UCMMERR_TAGPTR);
    }

    // advance the pointer based on the amount used
    msg_size+=return_code;    

    /* store the Encap Length and Data Item Length */
    rta_PutLitEndian16((uint16)(msg_size-EIP_ENCAP_HEADER_SIZ), msg+2); // encap length
    rta_PutLitEndian16((uint16)(msg_size-44),  msg+42); // data item length

    // send the message to the server
    if(eipc_usersock_sendData (server->SockID, msg, msg_size) == 0)
    {
        // inform the user that the UCMM is busy 
        server->EM_CnxnState = EIPC_CLIENT_UCMMSERVERSTATE_BUSY;
        eipc_usersys_EmCnxnStateChanged (server->EM_CnxnState, EIPC_CLIENT_EMCLASS3CNXNSTATE_BUSY);

        // reset the timeout
        eipc_timer_reset(server->EM_TimerNum);

        return(EIPC_CLIENT_UCMMERR_SUCCESS);
    }
    
    // send failed
    return(EIPC_CLIENT_UCMMERR_SERVHAND);
}
#endif /* EIPC_EM_CLASS3_CNXN_USED */
#endif /* #ifdef EIPC_TAG_CLIENT_USED */

/* ====================================================================
Function:   eipc_tagclient_sendPcccRead_unconnected
Parameters: server handle
            message timeout (in milliseconds)
            pointer to pccc requestion structure
Returns:    0  - Success
            <0 - Failure

This function validates the read request as best as possible and
sends the message to the passed PLC. Responses (or timeouts) are
reported to the user via the passed callback function.
======================================================================= */
#ifdef EIPC_PCCC_CLIENT_USED
int16 eipc_tagclient_sendPcccRead_unconnected (uint16 server_handle, uint32 tmo_in_ticks, EIPC_PCCC_STRUCT *pccc_ptr)
{
    EIPC_HANDLE_STRUCT *server;
    uint8   msg[EIPC_CPF_MAX_ITEM_DATA_LEN];
    uint16  msg_size;
//    uint16  i;
//    char    ascii_addr[51];
    int16   return_code;

    //eipc_user_dbprint1("eipc_tagclient_sendPcccRead(%d)\r\n",server_handle);

    // get the server pointer
    server = local_get_server_struct(server_handle);

    // verify the server handle
    if(server == NULL)
        return(EIPC_CLIENT_UCMMERR_SERVHAND);

    /* make sure a message isn't already in progress */
    if(server->UCMMState != EIPC_CLIENT_UCMMSERVERSTATE_READY)
        return(EIPC_CLIENT_UCMMERR_BUSY);

    // verify the timeout is 100ms or larger
    if(tmo_in_ticks < EIPC_USEROBJ_MINTMOVAL)
        return(EIPC_CLIENT_UCMMERR_TMOINVALID);

    /* verify the pccc pointer isn't NULL */
    if(pccc_ptr == NULL)
        return(EIPC_CLIENT_UCMMERR_TAGPTR);

    /* verify the timeout is 100ms or larger */
    if(tmo_in_ticks < EIPC_USEROBJ_MINTMOVAL)
        return(EIPC_CLIENT_UCMMERR_TMOINVALID);

    /* verify the PLC type */
    if( (pccc_ptr->pccc_plc_type != EIPC_PCCC_PLC_TYPE_SLC505) &&
        (pccc_ptr->pccc_plc_type != EIPC_PCCC_PLC_TYPE_PLC5E) )
        return(EIPC_CLIENT_UCMMERR_PLCTYPEINVALID);

    /* ******************************************************** */
    /*          build and send the message */
    /* ******************************************************** */

    /*
        ===========================
        REQUEST/RESPONSE VALIDATION
        ===========================

        FIELD NAME         FIElD VALUE
        ----------         -----------
        Command            SendRRData (0x6F)
        Length             varies
        Session Handle     passed
        Status             shall be 0
        Sender Context     shall be 0
        Options            shall be 0
        Encapsulated Data
24      Interface Handle (4 bytes) shall be 0
28      Timeout          (2 bytes) passed
30      Item Count       (2 bytes) shall be 2
32      Addr Item Code   (2 bytes) shall be 0
34      Addr Item Len    (2 bytes) shall be 0
36      Data Item Code   (2 bytes) shall be 0x00B2
38      Data Item Len    (2 bytes) varies
40      Data Item Data   (varies in length) varies in data
    */

    /* SEND RR DATA - UNCONNECTED */
    server->LastEncapCmd = EIP_ENCAPCMD_SENDRRDATA;

    // Encapsulation Header
    rta_PutLitEndian16(EIP_ENCAPCMD_SENDRRDATA, msg+0); // Encap - Command - Send RR Data (uint16)
    rta_PutLitEndian16(0, msg+2);                       // Encap - Length (uint16) (Filled in later)
    rta_PutLitEndian32(server->SessionID, msg+4);       // Encap - Session handle (uint32)
    rta_PutLitEndian32(0, msg+8);                       // Encap - Status (uint32)
    rta_PutLitEndian32(0, msg+12);                      // Encap - Sender Context HI (uint32)
    rta_PutLitEndian32(0, msg+16);                      // Encap - Sender Context LO (uint32)
    rta_PutLitEndian32(0, msg+20);                      // Encap - Options (uint32) 

    // Command Specific Data
    rta_PutLitEndian32(0, msg+24);                      // Interface Handle (uint32)
    rta_PutLitEndian16(1024, msg+28);                   // Timeout (uint16)
    rta_PutLitEndian16(2, msg+30);                      // Item Count
    rta_PutLitEndian16(ADDR_TYP_ID_NULL, msg+32);       // Item 1 - Address Item
    rta_PutLitEndian16(0, msg+34);                      // Item 1 - Length
    //rta_PutLitEndian16(2, msg+30);                    // Item 1 - No Data
    rta_PutLitEndian16(DATA_TYP_ID_UCMM, msg+36);       // Item 2 - Data Item
    rta_PutLitEndian16(2, msg+38);                      // Item 2 - Length
    msg_size = 40;

    // a portion of the message is common for the connected and unconnected version
    return_code = local_buildPcccRead_common(server, &msg[msg_size], (sizeof(msg)-(msg_size+4)), pccc_ptr);

    // was the data sucessfully stored?
    if(return_code < 0)
    {
        return(EIPC_CLIENT_UCMMERR_TAGPTR);
    }

    // advance the pointer based on the amount used
    msg_size+=return_code;    

    /* ************** */
    /* Common portion */
    /* ************** */

    /* store the Encap Length and Data Item Length */
    rta_PutLitEndian16((uint16)(msg_size-EIP_ENCAP_HEADER_SIZ), msg+2); /* encap length */
    rta_PutLitEndian16((uint16)(msg_size-40),  msg+38); /* data item length */

    /* send the message to the server */
    eipc_usersock_sendData (server->SockID, msg, msg_size);

    /* inform the user that the UCMM is busy */
    server->UCMMState = EIPC_CLIENT_UCMMSERVERSTATE_BUSY;
    eipc_usersys_UCMMStateChanged (server->ServerHandle, EIPC_CLIENT_UCMMSERVERSTATE_BUSY);

    /* start the timeout */
    eipc_timer_newval(server->TimerNum, tmo_in_ticks);
    eipc_timer_reset(server->TimerNum);

    return(EIPC_CLIENT_UCMMERR_SUCCESS);
}
#endif /* #ifdef EIPC_PCCC_CLIENT_USED */

/* ====================================================================
Function:   eipc_tagclient_sendPcccWrite_unconnected
Parameters: server handle
            message timeout (in milliseconds)
            pointer to pccc requestion structure
Returns:    0  - Success
            <0 - Failure

This function validates the write request as best as possible and
sends the message to the passed PLC. Responses (or timeouts) are
reported to the user via the passed callback function.
======================================================================= */
#ifdef EIPC_PCCC_CLIENT_USED
int16 eipc_tagclient_sendPcccWrite_unconnected (uint16 server_handle, uint32 tmo_in_ticks, EIPC_PCCC_STRUCT *pccc_ptr)
{
    EIPC_HANDLE_STRUCT *server;
    uint8   msg[EIPC_CPF_MAX_ITEM_DATA_LEN];
    uint16  msg_size, i;
//    char    ascii_addr[51];
    int16   return_code;

    //eipc_user_dbprint1("eipc_tagclient_sendPcccWrite(%d)\r\n",server_handle);

    // get the server pointer
    server = local_get_server_struct(server_handle);

    // verify the server handle
    if(server == NULL)
        return(EIPC_CLIENT_UCMMERR_SERVHAND);

    /* make sure a message isn't already in progress */
    if(server->UCMMState != EIPC_CLIENT_UCMMSERVERSTATE_READY)
        return(EIPC_CLIENT_UCMMERR_BUSY);

    // verify the timeout is 100ms or larger
    if(tmo_in_ticks < EIPC_USEROBJ_MINTMOVAL)
        return(EIPC_CLIENT_UCMMERR_TMOINVALID);

    /* verify the pccc pointer isn't NULL */
    if(pccc_ptr == NULL)
        return(EIPC_CLIENT_UCMMERR_TAGPTR);

    /* verify the PLC type */
    if( (pccc_ptr->pccc_plc_type != EIPC_PCCC_PLC_TYPE_SLC505) &&
        (pccc_ptr->pccc_plc_type != EIPC_PCCC_PLC_TYPE_PLC5E) )
        return(EIPC_CLIENT_UCMMERR_PLCTYPEINVALID);
           
    /* ******************************************************** */
    /*          build and send the message */
    /* ******************************************************** */

    /*
        ===========================
        REQUEST/RESPONSE VALIDATION
        ===========================

        FIELD NAME         FIElD VALUE
        ----------         -----------
        Command            SendRRData (0x6F)
        Length             varies
        Session Handle     passed
        Status             shall be 0
        Sender Context     shall be 0
        Options            shall be 0
        Encapsulated Data
24      Interface Handle (4 bytes) shall be 0
28      Timeout          (2 bytes) passed
30      Item Count       (2 bytes) shall be 2
32      Addr Item Code   (2 bytes) shall be 0
34      Addr Item Len    (2 bytes) shall be 0
36      Data Item Code   (2 bytes) shall be 0x00B2
38      Data Item Len    (2 bytes) varies
40      Data Item Data   (varies in length) varies in data
    */

    /* SEND RR DATA - UNCONNECTED */
    server->LastEncapCmd = EIP_ENCAPCMD_SENDRRDATA;

    // Encapsulation Header
    rta_PutLitEndian16(EIP_ENCAPCMD_SENDRRDATA, msg+0); // Encap - Command - Send RR Data (uint16)
    rta_PutLitEndian16(0, msg+2);                       // Encap - Length (uint16) (Filled in later)
    rta_PutLitEndian32(server->SessionID, msg+4);       // Encap - Session handle (uint32)
    rta_PutLitEndian32(0, msg+8);                       // Encap - Status (uint32)
    rta_PutLitEndian32(0, msg+12);                      // Encap - Sender Context HI (uint32)
    rta_PutLitEndian32(0, msg+16);                      // Encap - Sender Context LO (uint32)
    rta_PutLitEndian32(0, msg+20);                      // Encap - Options (uint32) 

    // Command Specific Data
    rta_PutLitEndian32(0, msg+24);                      // Interface Handle (uint32)
    rta_PutLitEndian16(1024, msg+28);                   // Timeout (uint16)
    rta_PutLitEndian16(2, msg+30);                      // Item Count
    rta_PutLitEndian16(ADDR_TYP_ID_NULL, msg+32);       // Item 1 - Address Item
    rta_PutLitEndian16(0, msg+34);                      // Item 1 - Length
    //rta_PutLitEndian16(2, msg+30);                    // Item 1 - No Data
    rta_PutLitEndian16(DATA_TYP_ID_UCMM, msg+36);       // Item 2 - Data Item
    rta_PutLitEndian16(2, msg+38);                      // Item 2 - Length
    msg_size = 40;

    // a portion of the message is common for the connected and unconnected version
    return_code = local_buildPcccWrite_common(server, &msg[msg_size], (sizeof(msg)-(msg_size+4)), pccc_ptr);

    // was the data sucessfully stored?
    if(return_code < 0)
    {
        return(EIPC_CLIENT_UCMMERR_TAGPTR);
    }

    // advance the pointer based on the amount used
    msg_size+=return_code;    

    /* ************** */
    /* Common portion */
    /* ************** */

    /* store the Encap Length and Data Item Length */
    rta_PutLitEndian16((uint16)(msg_size-EIP_ENCAP_HEADER_SIZ), msg+2); /* encap length */
    rta_PutLitEndian16((uint16)(msg_size-40),  msg+38); /* data item length */

    /* send the message to the server */
    eipc_usersock_sendData (server->SockID, msg, msg_size);

    /* inform the user that the UCMM is busy */
    server->UCMMState = EIPC_CLIENT_UCMMSERVERSTATE_BUSY;
    eipc_usersys_UCMMStateChanged (server->ServerHandle, EIPC_CLIENT_UCMMSERVERSTATE_BUSY);

    /* start the timeout */
    eipc_timer_newval(server->TimerNum, tmo_in_ticks);
    eipc_timer_reset(server->TimerNum);

    return(EIPC_CLIENT_UCMMERR_SUCCESS);
}
#endif /* #ifdef EIPC_PCCC_CLIENT_USED */

/* ====================================================================
Function:   eipc_tagclient_sendPcccRead_connected
Parameters: server handle
            pointer to pccc requestion structure
Returns:    0  - Success
            <0 - Failure

This function validates the read request as best as possible and
sends the message to the passed PLC. Responses (or timeouts) are
reported to the user via the passed callback function.
======================================================================= */
#ifdef EIPC_PCCC_CLIENT_USED
#ifdef EIPC_EM_CLASS3_CNXN_USED
int16 eipc_tagclient_sendPcccRead_connected  (uint16 server_handle, EIPC_PCCC_STRUCT *pccc_ptr)
{
    EIPC_HANDLE_STRUCT *server;
    uint8   msg[EIPC_CPF_MAX_ITEM_DATA_LEN];
    uint16  msg_size;
//    uint16  i;
//    char    ascii_addr[51];
    int16   return_code;

    //eipc_user_dbprint1("eipc_tagclient_sendPcccRead(%d)\r\n",server_handle);

    // get the server pointer
    server = local_get_server_struct(server_handle);

    // verify the server handle
    if(server == NULL)
        return(EIPC_CLIENT_UCMMERR_SERVHAND);

    /* make sure a message isn't already in progress */
    if(server->EM_CnxnState != EIPC_CLIENT_EMCLASS3CNXNSTATE_READY)
        return(EIPC_CLIENT_UCMMERR_BUSY);

    /* verify the pccc pointer isn't NULL */
    if(pccc_ptr == NULL)
        return(EIPC_CLIENT_UCMMERR_TAGPTR);

    /* verify the PLC type */
    if( (pccc_ptr->pccc_plc_type != EIPC_PCCC_PLC_TYPE_SLC505) &&
        (pccc_ptr->pccc_plc_type != EIPC_PCCC_PLC_TYPE_PLC5E) )
        return(EIPC_CLIENT_UCMMERR_PLCTYPEINVALID);

    /* ******************************************************** */
    /*          build and send the message */
    /* ******************************************************** */

    /*
        ===========================
        REQUEST/RESPONSE VALIDATION
        ===========================

        FIELD NAME         FIElD VALUE
        ----------         -----------
        Command            SendRRData (0x6F)
        Length             varies
        Session Handle     passed
        Status             shall be 0
        Sender Context     shall be 0
        Options            shall be 0
        Encapsulated Data
24      Interface Handle (4 bytes) shall be 0
28      Timeout          (2 bytes) passed
30      Item Count       (2 bytes) shall be 2
32      Addr Item Code   (2 bytes) shall be 0
34      Addr Item Len    (2 bytes) shall be 0
36      Data Item Code   (2 bytes) shall be 0x00B2
38      Data Item Len    (2 bytes) varies
40      Data Item Data   (varies in length) varies in data
    */

    /* build the fixed part of the message */
    memset(msg, 0, EIPC_CPF_MAX_ITEM_DATA_LEN);

    /* SEND RR DATA - UNCONNECTED */
    server->LastEncapCmd = EIP_ENCAPCMD_SENDUNITDATA;

    // Encapsulation Header
    rta_PutLitEndian16(EIP_ENCAPCMD_SENDUNITDATA, msg+0); // Encap - Command - Send Unit Data (uint16)
    rta_PutLitEndian16(0, msg+2);                         // Encap - Length (uint16) (Filled in later)
    rta_PutLitEndian32(server->SessionID, msg+4);         // Encap - Session handle (uint32)
    rta_PutLitEndian32(0, msg+8);                         // Encap - Status (uint32)
    rta_PutLitEndian32(0, msg+12);                        // Encap - Sender Context HI (uint32)
    rta_PutLitEndian32(0, msg+16);                        // Encap - Sender Context LO (uint32)
    rta_PutLitEndian32(0, msg+20);                        // Encap - Options (uint32) 

    // Command Specific Data
    rta_PutLitEndian32(0, msg+24);                       // Interface Handle (uint32)
    rta_PutLitEndian16(1024, msg+28);                    // Timeout (uint16)
    rta_PutLitEndian16(2, msg+30);                       // Item Count
    rta_PutLitEndian16(ADDR_TYP_ID_CNXNBASED, msg+32);   // Item 1 - Address Item
    rta_PutLitEndian16(4, msg+34);                       // Item 1 - Length = 4
    rta_PutLitEndian32(server->EM_O2T_CnxnID, msg+36);   // Item 1 - Connection ID (uint32) 

    rta_PutLitEndian16(DATA_TYP_ID_PDU, msg+40);         // Item 2 - Data Item
    rta_PutLitEndian16(0, msg+42);                       // Item 2 - Length (later)
    server->EM_O2T_SeqNum++;    // pre-increment so we can compare the response
    rta_PutLitEndian16(server->EM_O2T_SeqNum, msg+44);   // Item 2 - Sequence Count

    msg_size = 46;

    // a portion of the message is common for the connected and unconnected version
    return_code = local_buildPcccRead_common(server, &msg[msg_size], (sizeof(msg)-(msg_size+4)), pccc_ptr);

    // was the data sucessfully stored?
    if(return_code < 0)
    {
        return(EIPC_CLIENT_UCMMERR_TAGPTR);
    }

    // advance the pointer based on the amount used
    msg_size+=return_code;    

    /* ************** */
    /* Common portion */
    /* ************** */

    /* store the Encap Length and Data Item Length */
    rta_PutLitEndian16((uint16)(msg_size-EIP_ENCAP_HEADER_SIZ), msg+2); /* encap length */
    rta_PutLitEndian16((uint16)(msg_size-44),  msg+42); // data item length

    // send the message to the server
    if(eipc_usersock_sendData (server->SockID, msg, msg_size) == 0)
    {
        // inform the user that the UCMM is busy 
        server->EM_CnxnState = EIPC_CLIENT_UCMMSERVERSTATE_BUSY;
        eipc_usersys_EmCnxnStateChanged (server->EM_CnxnState, EIPC_CLIENT_EMCLASS3CNXNSTATE_BUSY);

        // reset the timeout
        eipc_timer_reset(server->EM_TimerNum);

        return(EIPC_CLIENT_UCMMERR_SUCCESS);
    }

    // send failed
    return(EIPC_CLIENT_UCMMERR_SERVHAND);
}
#endif /* #ifdef EIPC_EM_CLASS3_CNXN_USED */
#endif /* #ifdef EIPC_PCCC_CLIENT_USED */

/* ====================================================================
Function:   eipc_tagclient_sendPcccWrite_connected
Parameters: server handle
            pointer to pccc requestion structure
Returns:    0  - Success
            <0 - Failure

This function validates the write request as best as possible and
sends the message to the passed PLC. Responses (or timeouts) are
reported to the user via the passed callback function.
======================================================================= */
#ifdef EIPC_PCCC_CLIENT_USED
#ifdef EIPC_EM_CLASS3_CNXN_USED
int16 eipc_tagclient_sendPcccWrite_connected (uint16 server_handle, EIPC_PCCC_STRUCT *pccc_ptr)
{
    EIPC_HANDLE_STRUCT *server;
    uint8   msg[EIPC_CPF_MAX_ITEM_DATA_LEN];
    uint16  msg_size, i;
//    char    ascii_addr[51];
    int16   return_code;

    //eipc_user_dbprint1("eipc_tagclient_sendPcccWrite(%d)\r\n",server_handle);

    // get the server pointer
    server = local_get_server_struct(server_handle);

    // verify the server handle
    if(server == NULL)
        return(EIPC_CLIENT_UCMMERR_SERVHAND);

    /* make sure a message isn't already in progress */
    if(server->EM_CnxnState != EIPC_CLIENT_EMCLASS3CNXNSTATE_READY)
        return(EIPC_CLIENT_UCMMERR_BUSY);

    /* verify the pccc pointer isn't NULL */
    if(pccc_ptr == NULL)
        return(EIPC_CLIENT_UCMMERR_TAGPTR);

    /* verify the PLC type */
    if( (pccc_ptr->pccc_plc_type != EIPC_PCCC_PLC_TYPE_SLC505) &&
        (pccc_ptr->pccc_plc_type != EIPC_PCCC_PLC_TYPE_PLC5E) )
        return(EIPC_CLIENT_UCMMERR_PLCTYPEINVALID);
           
    /* ******************************************************** */
    /*          build and send the message */
    /* ******************************************************** */

    /*
        ===========================
        REQUEST/RESPONSE VALIDATION
        ===========================

        FIELD NAME         FIElD VALUE
        ----------         -----------
        Command            SendRRData (0x6F)
        Length             varies
        Session Handle     passed
        Status             shall be 0
        Sender Context     shall be 0
        Options            shall be 0
        Encapsulated Data
24      Interface Handle (4 bytes) shall be 0
28      Timeout          (2 bytes) passed
30      Item Count       (2 bytes) shall be 2
32      Addr Item Code   (2 bytes) shall be 0
34      Addr Item Len    (2 bytes) shall be 0
36      Data Item Code   (2 bytes) shall be 0x00B2
38      Data Item Len    (2 bytes) varies
40      Data Item Data   (varies in length) varies in data
    */

    /* build the fixed part of the message */
    memset(msg, 0, EIPC_CPF_MAX_ITEM_DATA_LEN);

    /* SEND RR DATA - UNCONNECTED */
    server->LastEncapCmd = EIP_ENCAPCMD_SENDUNITDATA;

    // Encapsulation Header
    rta_PutLitEndian16(EIP_ENCAPCMD_SENDUNITDATA, msg+0); // Encap - Command - Send Unit Data (uint16)
    rta_PutLitEndian16(0, msg+2);                         // Encap - Length (uint16) (Filled in later)
    rta_PutLitEndian32(server->SessionID, msg+4);         // Encap - Session handle (uint32)
    rta_PutLitEndian32(0, msg+8);                         // Encap - Status (uint32)
    rta_PutLitEndian32(0, msg+12);                        // Encap - Sender Context HI (uint32)
    rta_PutLitEndian32(0, msg+16);                        // Encap - Sender Context LO (uint32)
    rta_PutLitEndian32(0, msg+20);                        // Encap - Options (uint32) 

    // Command Specific Data
    rta_PutLitEndian32(0, msg+24);                       // Interface Handle (uint32)
    rta_PutLitEndian16(1024, msg+28);                    // Timeout (uint16)
    rta_PutLitEndian16(2, msg+30);                       // Item Count
    rta_PutLitEndian16(ADDR_TYP_ID_CNXNBASED, msg+32);   // Item 1 - Address Item
    rta_PutLitEndian16(4, msg+34);                       // Item 1 - Length = 4
    rta_PutLitEndian32(server->EM_O2T_CnxnID, msg+36);   // Item 1 - Connection ID (uint32) 

    rta_PutLitEndian16(DATA_TYP_ID_PDU, msg+40);         // Item 2 - Data Item
    rta_PutLitEndian16(0, msg+42);                       // Item 2 - Length (later)
    server->EM_O2T_SeqNum++;    // pre-increment so we can compare the response
    rta_PutLitEndian16(server->EM_O2T_SeqNum, msg+44);   // Item 2 - Sequence Count

    msg_size = 46;

    // a portion of the message is common for the connected and unconnected version
    return_code = local_buildPcccWrite_common(server, &msg[msg_size], (sizeof(msg)-(msg_size+4)), pccc_ptr);

    // was the data sucessfully stored?
    if(return_code < 0)
    {
        return(EIPC_CLIENT_UCMMERR_TAGPTR);
    }

    // advance the pointer based on the amount used
    msg_size+=return_code;    

    /* ************** */
    /* Common portion */
    /* ************** */

    /* store the Encap Length and Data Item Length */
    rta_PutLitEndian16((uint16)(msg_size-EIP_ENCAP_HEADER_SIZ), msg+2); /* encap length */
    rta_PutLitEndian16((uint16)(msg_size-44),  msg+42); // data item length

    // send the message to the server
    if(eipc_usersock_sendData (server->SockID, msg, msg_size) == 0)
    {
        // inform the user that the UCMM is busy 
        server->EM_CnxnState = EIPC_CLIENT_UCMMSERVERSTATE_BUSY;
        eipc_usersys_EmCnxnStateChanged (server->EM_CnxnState, EIPC_CLIENT_EMCLASS3CNXNSTATE_BUSY);

        // reset the timeout
        eipc_timer_reset(server->EM_TimerNum);

        return(EIPC_CLIENT_UCMMERR_SUCCESS);
    }

    // send failed
    return(EIPC_CLIENT_UCMMERR_SERVHAND);
}
#endif /* #ifdef EIPC_EM_CLASS3_CNXN_USED */
#endif /* #ifdef EIPC_PCCC_CLIENT_USED */

/* ====================================================================
Function:   eipc_tagclient_sendExplicitMsg_connected
Parameters: server handle
            pointer to EM requestion structure
Returns:    0  - Success
            <0 - Failure

This function validates the request as best as possible and sends the 
message to the passed device. Responses (or timeouts) are reported to 
the user via the passed callback function.
======================================================================= */
#ifdef EIPC_EM_CLIENT_USED
#ifdef EIPC_EM_CLASS3_CNXN_USED
int16 eipc_tagclient_sendExplicitMsg_connected (uint16 server_handle, EIPC_EM_STRUCT *em_ptr)
{
    EIPC_HANDLE_STRUCT *server;
    uint8   msg[EIPC_CPF_MAX_ITEM_DATA_LEN];
    uint16  msg_size;
    int16   return_code;

    //eipc_user_dbprint1("eipc_tagclient_sendExplicitMsg_connected(%d)\r\n",server_handle);

    // get the server pointer
    server = local_get_server_struct(server_handle);

    // verify the server handle
    if(server == NULL)
        return(EIPC_CLIENT_UCMMERR_SERVHAND);

    /* make sure a message isn't already in progress */
    if(server->EM_CnxnState != EIPC_CLIENT_EMCLASS3CNXNSTATE_READY)
        return(EIPC_CLIENT_UCMMERR_BUSY);

    /* verify the pccc pointer isn't NULL */
    if(em_ptr == NULL)
        return(EIPC_CLIENT_UCMMERR_TAGPTR);

    /* ******************************************************** */
    /*          build and send the message                      */
    /* ******************************************************** */

    /*
        ===========================
        REQUEST/RESPONSE VALIDATION
        ===========================

        FIELD NAME         FIElD VALUE
        ----------         -----------
        Command            SendRRData (0x6F)
        Length             varies
        Session Handle     passed
        Status             shall be 0
        Sender Context     shall be 0
        Options            shall be 0
        Encapsulated Data
24      Interface Handle (4 bytes) shall be 0
28      Timeout          (2 bytes) passed
30      Item Count       (2 bytes) shall be 2
32      Addr Item Code   (2 bytes) shall be 0
34      Addr Item Len    (2 bytes) shall be 0
36      Data Item Code   (2 bytes) shall be 0x00B2
38      Data Item Len    (2 bytes) varies
40      Data Item Data   (varies in length) varies in data
    */

    /* build the fixed part of the message */
    memset(msg, 0, EIPC_CPF_MAX_ITEM_DATA_LEN);

    /* SEND RR DATA - UNCONNECTED */
    server->LastEncapCmd = EIP_ENCAPCMD_SENDUNITDATA;

    // Encapsulation Header
    rta_PutLitEndian16(EIP_ENCAPCMD_SENDUNITDATA, msg+0); // Encap - Command - Send Unit Data (uint16)
    rta_PutLitEndian16(0, msg+2);                         // Encap - Length (uint16) (Filled in later)
    rta_PutLitEndian32(server->SessionID, msg+4);         // Encap - Session handle (uint32)
    rta_PutLitEndian32(0, msg+8);                         // Encap - Status (uint32)
    rta_PutLitEndian32(0, msg+12);                        // Encap - Sender Context HI (uint32)
    rta_PutLitEndian32(0, msg+16);                        // Encap - Sender Context LO (uint32)
    rta_PutLitEndian32(0, msg+20);                        // Encap - Options (uint32) 

    // Command Specific Data
    rta_PutLitEndian32(0, msg+24);                       // Interface Handle (uint32)
    rta_PutLitEndian16(1024, msg+28);                    // Timeout (uint16)
    rta_PutLitEndian16(2, msg+30);                       // Item Count
    rta_PutLitEndian16(ADDR_TYP_ID_CNXNBASED, msg+32);   // Item 1 - Address Item
    rta_PutLitEndian16(4, msg+34);                       // Item 1 - Length = 4
    rta_PutLitEndian32(server->EM_O2T_CnxnID, msg+36);   // Item 1 - Connection ID (uint32) 

    rta_PutLitEndian16(DATA_TYP_ID_PDU, msg+40);         // Item 2 - Data Item
    rta_PutLitEndian16(0, msg+42);                       // Item 2 - Length (later)
    server->EM_O2T_SeqNum++;    // pre-increment so we can compare the response
    rta_PutLitEndian16(server->EM_O2T_SeqNum, msg+44);   // Item 2 - Sequence Count

    msg_size = 46;

    // a portion of the message is common for the connected and unconnected version
    return_code = local_buildEm_common(&msg[msg_size], (sizeof(msg)-(msg_size+4)), em_ptr);

    // was the data sucessfully stored?
    if(return_code < 0)
    {
        return(EIPC_CLIENT_UCMMERR_TAGPTR);
    }

    // advance the pointer based on the amount used
    msg_size+=return_code;    

    /* ************** */
    /* Common portion */
    /* ************** */

    /* store the Encap Length and Data Item Length */
    rta_PutLitEndian16((uint16)(msg_size-EIP_ENCAP_HEADER_SIZ), msg+2); /* encap length */
    rta_PutLitEndian16((uint16)(msg_size-44),  msg+42); // data item length

    // send the message to the server
    if(eipc_usersock_sendData (server->SockID, msg, msg_size) == 0)
    {
        // inform the user that the UCMM is busy 
        server->EM_CnxnState = EIPC_CLIENT_UCMMSERVERSTATE_BUSY;
        eipc_usersys_EmCnxnStateChanged (server->EM_CnxnState, EIPC_CLIENT_EMCLASS3CNXNSTATE_BUSY);

        // reset the timeout
        eipc_timer_reset(server->EM_TimerNum);

        return(EIPC_CLIENT_UCMMERR_SUCCESS);
    }

    // send failed
    return(EIPC_CLIENT_UCMMERR_SERVHAND);
}
#endif /* #ifdef EIPC_EM_CLASS3_CNXN_USED */
#endif /* #ifdef EIPC_EM_CLIENT_USED */

/* ====================================================================
Function:   eipc_tagclient_sendExplicitMsg_unconnected
Parameters: server handle
            message timeout (in milliseconds)
            pointer to EM requestion structure
Returns:    0  - Success
            <0 - Failure

This function validates the request as best as possible and sends the 
message to the passed device. Responses (or timeouts) are reported to 
the user via the passed callback function.
======================================================================= */
#ifdef EIPC_EM_CLIENT_USED
int16 eipc_tagclient_sendExplicitMsg_unconnected (uint16 server_handle, uint32 tmo_in_ticks, EIPC_EM_STRUCT *em_ptr)
{
    EIPC_HANDLE_STRUCT *server;
    uint8   msg[EIPC_CPF_MAX_ITEM_DATA_LEN];
    uint16  msg_size;
    int16   return_code;

    //eipc_user_dbprint1("eipc_tagclient_sendExplicitMsg_unconnected(%d)\r\n",server_handle);

    // get the server pointer
    server = local_get_server_struct(server_handle);

    // verify the server handle
    if(server == NULL)
        return(EIPC_CLIENT_UCMMERR_SERVHAND);

    /* make sure a message isn't already in progress */
    if(server->UCMMState != EIPC_CLIENT_UCMMSERVERSTATE_READY)
        return(EIPC_CLIENT_UCMMERR_BUSY);

    // verify the timeout is 100ms or larger
    if(tmo_in_ticks < EIPC_USEROBJ_MINTMOVAL)
        return(EIPC_CLIENT_UCMMERR_TMOINVALID);

    /* verify the pointer isn't NULL */
    if(em_ptr == NULL)
        return(EIPC_CLIENT_UCMMERR_TAGPTR);
           
    /* ******************************************************** */
    /*          build and send the message                      */
    /* ******************************************************** */

    /*
        ===========================
        REQUEST/RESPONSE VALIDATION
        ===========================

        FIELD NAME         FIElD VALUE
        ----------         -----------
        Command            SendRRData (0x6F)
        Length             varies
        Session Handle     passed
        Status             shall be 0
        Sender Context     shall be 0
        Options            shall be 0
        Encapsulated Data
24      Interface Handle (4 bytes) shall be 0
28      Timeout          (2 bytes) passed
30      Item Count       (2 bytes) shall be 2
32      Addr Item Code   (2 bytes) shall be 0
34      Addr Item Len    (2 bytes) shall be 0
36      Data Item Code   (2 bytes) shall be 0x00B2
38      Data Item Len    (2 bytes) varies
40      Data Item Data   (varies in length) varies in data
    */

    /* SEND RR DATA - UNCONNECTED */
    server->LastEncapCmd = EIP_ENCAPCMD_SENDRRDATA;

    // Encapsulation Header
    rta_PutLitEndian16(EIP_ENCAPCMD_SENDRRDATA, msg+0); // Encap - Command - Send RR Data (uint16)
    rta_PutLitEndian16(0, msg+2);                       // Encap - Length (uint16) (Filled in later)
    rta_PutLitEndian32(server->SessionID, msg+4);       // Encap - Session handle (uint32)
    rta_PutLitEndian32(0, msg+8);                       // Encap - Status (uint32)
    rta_PutLitEndian32(0, msg+12);                      // Encap - Sender Context HI (uint32)
    rta_PutLitEndian32(0, msg+16);                      // Encap - Sender Context LO (uint32)
    rta_PutLitEndian32(0, msg+20);                      // Encap - Options (uint32) 

    // Command Specific Data
    rta_PutLitEndian32(0, msg+24);                      // Interface Handle (uint32)
    rta_PutLitEndian16(1024, msg+28);                   // Timeout (uint16)
    rta_PutLitEndian16(2, msg+30);                      // Item Count
    rta_PutLitEndian16(ADDR_TYP_ID_NULL, msg+32);       // Item 1 - Address Item
    rta_PutLitEndian16(0, msg+34);                      // Item 1 - Length
    //rta_PutLitEndian16(2, msg+30);                    // Item 1 - No Data
    rta_PutLitEndian16(DATA_TYP_ID_UCMM, msg+36);       // Item 2 - Data Item
    rta_PutLitEndian16(2, msg+38);                      // Item 2 - Length
    msg_size = 40;

    // a portion of the message is common for the connected and unconnected version
    return_code = local_buildEm_common(&msg[msg_size], (sizeof(msg)-(msg_size+4)), em_ptr);

    // was the data sucessfully stored?
    if(return_code < 0)
    {
        return(EIPC_CLIENT_UCMMERR_TAGPTR);
    }

    // advance the pointer based on the amount used
    msg_size+=return_code;    

    /* ************** */
    /* Common portion */
    /* ************** */

    /* store the Encap Length and Data Item Length */
    rta_PutLitEndian16((uint16)(msg_size-EIP_ENCAP_HEADER_SIZ), msg+2); /* encap length */
    rta_PutLitEndian16((uint16)(msg_size-40),  msg+38); /* data item length */

    /* send the message to the server */
    eipc_usersock_sendData (server->SockID, msg, msg_size);

    /* inform the user that the UCMM is busy */
    server->UCMMState = EIPC_CLIENT_UCMMSERVERSTATE_BUSY;
    eipc_usersys_UCMMStateChanged (server->ServerHandle, EIPC_CLIENT_UCMMSERVERSTATE_BUSY);

    /* start the timeout */
    eipc_timer_newval(server->TimerNum, tmo_in_ticks);
    eipc_timer_reset(server->TimerNum);

    return(EIPC_CLIENT_UCMMERR_SUCCESS);
}
#endif /* #ifdef EIPC_EM_CLIENT_USED */

/* ====================================================================
Function:   eipc_tagclient_openEmCnxn
Parameters: server handle
            RPI in milliseconds
Returns:    0  - Success
            <0 - Failure

This function tries to open an Explicit Class 3 connection.
======================================================================= */
#ifdef EIPC_EM_CLASS3_CNXN_USED
#define EIPC_OFFSET_ENCAPLENGTH 2
#define EIPC_OFFSET_CPFLENGTH   38
int16 eipc_tagclient_openEmCnxn  (uint16 server_handle, uint16 rpi_in_ms, uint8 *port_id)
{
    EIPC_HANDLE_STRUCT *server;
    uint8   msg[EIPC_CPF_MAX_ITEM_DATA_LEN];
    uint16  msg_size = 0;

//    eipc_user_dbprint1("eipc_tagclient_openEmCnxn(%d)\r\n",server_handle);

    // get the server pointer
    server = local_get_server_struct(server_handle);

    // verify the server handle
    if(server == NULL)
        return(EIPC_CLIENT_UCMMERR_SERVHAND);

    /* make sure a message isn't already in progress */
    if(server->UCMMState != EIPC_CLIENT_UCMMSERVERSTATE_READY)
        return(EIPC_CLIENT_UCMMERR_BUSY);

    /* make sure a allocation isn't in progress or open */
    if(server->EM_CnxnState != EIPC_CLIENT_EMCLASS3CNXNSTATE_NONEXIST)
        return(EIPC_CLIENT_UCMMERR_CNXN_IN_USE);

    // verify the timeout is 100ms or larger
    if(rpi_in_ms < EIPC_USEROBJ_MINTMOVAL)
        return(EIPC_CLIENT_UCMMERR_TMOINVALID);

    // mark the connection allocation in progress
    server->EM_CnxnState = EIPC_CLIENT_EMCLASS3CNXNSTATE_ALLOC;

    /* initialize message buffer */
    memset(msg, 0, sizeof(msg));  // zero out the buffer
    msg_size = EIP_ENCAP_HEADER_SIZ; // min size of message
           
    /* ************************* */
    /* Build ForwardOpen Message */
    /* ************************* */   
    rta_PutLitEndian16(EIP_ENCAPCMD_SENDRRDATA, msg+0); // Encap Command
    server->LastEncapCmd = EIP_ENCAPCMD_SENDRRDATA;
    rta_PutLitEndian32(server->SessionID, msg+4); // Encap Session Handle
    rta_PutLitEndian32(0,    msg+msg_size); msg_size+=4; // Interface Handle
    rta_PutLitEndian16(0,    msg+msg_size); msg_size+=2; // Timeout
    rta_PutLitEndian16(2,    msg+msg_size); msg_size+=2; // Item Count
    rta_PutLitEndian16(0,    msg+msg_size); msg_size+=2; // Address Item Code
    rta_PutLitEndian16(0,    msg+msg_size); msg_size+=2; // Address Item Length   
    rta_PutLitEndian16(0xb2, msg+msg_size); msg_size+=2; // Data Item Code
    msg_size+=2; // Data Item Length (filled in later)
    msg[msg_size++] = 0x54; // CPF: Forward Open Service Code
    msg[msg_size++] = 0x02; // CPF: Path Size (2)
    msg[msg_size++] = 0x20; // CPF: Path (8-bit Class)
    msg[msg_size++] = 0x06; // CPF: Path (Connection Manager Class)
    msg[msg_size++] = 0x24; // CPF: Path (8-bit Instance)
    msg[msg_size++] = 0x01; // CPF: Path (Instance 1)
    msg[msg_size++] = 0x03; // CPF: Priority/Tick
    msg[msg_size++] = 0xFA; // CPF: Timeout
    rta_PutLitEndian32(local_getConnectionID(), msg+msg_size); msg_size+=4; // O_to_T Connection ID
    rta_PutLitEndian32(local_getConnectionID(), msg+msg_size); msg_size+=4; // T_to_O Connection ID
    rta_PutLitEndian16(server->ServerHandle, msg+msg_size); msg_size+=2; // Connection Serial Number
    rta_PutLitEndian16(EIPC_USER_IDOBJ_VENDORID, msg+msg_size); msg_size+=2; // Our Vendor ID
    rta_PutLitEndian32(eipc_userobj_getSerialNumber(), msg+msg_size); msg_size+=4; // Our Serial Number
    msg[msg_size++] = 0; // Connection Timeout Mult = 4x
    msg_size+=3; // reserved
    rta_PutLitEndian32((1000*rpi_in_ms), msg+msg_size); msg_size+=4; // O_to_T RPI (in microseconds)
    rta_PutLitEndian16((0x4200|(Xmin(EIPC_CPF_MAX_ITEM_DATA_LEN, 500)&0x1FF)), msg+msg_size); msg_size+=2; // O_to_T Cnxn Parameters
    rta_PutLitEndian32((1000*rpi_in_ms), msg+msg_size); msg_size+=4; // T_to_O RPI (in microseconds)
    rta_PutLitEndian16((0x4200|(Xmin(EIPC_CPF_MAX_ITEM_DATA_LEN, 500)&0x1FF)), msg+msg_size); msg_size+=2; // T_to_O Cnxn Parameters
    msg[msg_size++] = 0xA3; // Connection Transport (Class 3)

    /* store the optional port id for modular devices */
    if(port_id)
    {
        msg[msg_size++] = 0x03;      // CPF: Path Size (3)
        msg[msg_size++] = 1;         // CPF: Path (port)
        msg[msg_size++] = *port_id;  // CPF: Path (passed port value (used in Logix))
    }
    /* port isn't passed, just connect to root device */
    else
    {
        msg[msg_size++] = 2; // path: size
    }

    // point to the message router
    msg[msg_size++] = 0x20; // path: 8-bit Class
    msg[msg_size++] = 0x02; // path: Message Router Class        
    msg[msg_size++] = 0x24; // path: 8-bit Instance
    msg[msg_size++] = 0x01; // path: 1        

    // fill in the lengths 
    rta_PutLitEndian16((uint16)(msg_size - EIP_ENCAP_HEADER_SIZ), msg+EIPC_OFFSET_ENCAPLENGTH);
    rta_PutLitEndian16((uint16)(msg_size - EIP_ENCAP_HEADER_SIZ - 16), msg+EIPC_OFFSET_CPFLENGTH);

    /* send the message to the server */
    eipc_usersock_sendData (server->SockID, msg, msg_size);

    /* inform the user that the UCMM is busy */
    server->UCMMState = EIPC_CLIENT_UCMMSERVERSTATE_BUSY;
    eipc_usersys_UCMMStateChanged (server->ServerHandle, EIPC_CLIENT_UCMMSERVERSTATE_BUSY);

    /* start the timeout */
    eipc_timer_newval(server->EM_TimerNum, rpi_in_ms);
    eipc_timer_reset(server->EM_TimerNum);

    return(EIPC_CLIENT_UCMMERR_SUCCESS);
}
#endif /* #ifdef EIPC_EM_CLASS3_CNXN_USED */

#ifdef EIPC_EM_CLASS3_CNXN_USED
int16 eipc_tagclient_closeEmCnxn (uint16 server_handle)
{
    RTA_UNUSED_PARAM(server_handle);
    return(-1);
}
#endif /* #ifdef EIPC_EM_CLASS3_CNXN_USED */

/**/
/* ******************************************************************** */
/*	   	 	            LOCAL FUNCTIONS	    	                        */
/* ******************************************************************** */
/* ====================================================================
Function:   local_add_tag_name_to_buffer
Parameters: tag name to add
            length of tag name in bytes
            pointer to buffer to add tag name
            maximum number of bytes available in buffer
Returns:    Number of bytes added (<0 on error)

This function adds the tag name to the buffer
======================================================================= */
static int16 local_add_tag_name_to_buffer (uint8 *tag_name, uint16 tag_name_len, uint8 *buf, uint16 max_num_buf_bytes)
{
    uint16  tag_name_parse_ix;
    uint8   temp_buf[256];          /* temp buffer to avoid buffer overflow */
    uint16  temp_buf_ix;        
    uint8   array_ix_buf[10];
    uint16  array_ix_buf_ix;
    uint8   wait4bracket;
    uint16  offset;
    uint16  ioi_size_ix_local;
    uint8   ioi_size;
    uint8   last_char;

    /* make sure the pointers aren't NULL */
    if(!tag_name || !buf)
        return(-1);

    /* make sure the tagname stands a chance of fitting */
    if(tag_name_len > sizeof(temp_buf))
        return(-2);

    /* 0x91 0x01 0xnn 0x00 is the minimum tag string - so 4 characters */
    if(max_num_buf_bytes < 4)
        return(-3);

    /* we need to have a character to store */
    if(tag_name_len < 1)
        return(-4);
        
    /* first character must not be '.' '[' ']' or '\0' */
    if( (tag_name[0] == '.') || (tag_name[0] == '[') || (tag_name[0] == ']') || (tag_name[0] == '\0'))
        return(-5);

    /* set initial states */
    memset(temp_buf, 0, sizeof(temp_buf));
    temp_buf_ix = 0;
    memset(array_ix_buf, 0, sizeof(array_ix_buf));
    array_ix_buf_ix = 0;
    tag_name_parse_ix = 0;
    wait4bracket = 0;
    offset = 0;
    ioi_size_ix_local = 0;
    ioi_size = 0;
    last_char = 0;

    /* process the string until we are done */
    while ((temp_buf_ix < max_num_buf_bytes) && (tag_name_parse_ix < tag_name_len))    
    {
        switch(tag_name[tag_name_parse_ix])
        {
            case '.':
                /* Waiting for matching bracket */
                if(wait4bracket)
                {
                    /* tag error */
                    return(-6);
                }
                /* IOI String (normal processing) */
                else
                {
                    /* store the previous size (pad if necesary) */
                    if(ioi_size)
                    {
                        /* store the previous string size */
                        temp_buf[ioi_size_ix_local] = ioi_size;
                        if((ioi_size%2) == 1) /* odd # chars */
                            temp_buf[temp_buf_ix++] = 0; /* add a padding 0 */
                        ioi_size = 0; /* set size back to 0 to prep for next string */
                    }
                }
                break;
            case '[':
                /* Waiting for matching bracket */
                if(wait4bracket)
                {
                    /* tag error */
                    return(-7);
                }
                /* IOI String (normal processing) */
                else
                {
                    /* store the previous size (pad if necesary) */
                    if(ioi_size)
                    {
                        /* store the previous string size */
                        temp_buf[ioi_size_ix_local] = ioi_size;
                        if((ioi_size%2) == 1) /* odd # chars */
                            temp_buf[temp_buf_ix++] = 0; /* add a padding 0 */
                        ioi_size = 0; /* set size back to 0 to prep for next string */
                    }

                    /* flag we are looking for an offset */
                    wait4bracket = 1;
                }                
                break;
            case ']':
                /* Waiting for matching bracket */
                if(wait4bracket)
                {
                    /* store the offset from the ASCII buffer */
                    offset = (uint8)atoi((const char *)array_ix_buf);

                    /* offset < 256 */
                    if(offset < 256)
                    {
                        temp_buf[temp_buf_ix++] = 0x28;
                        temp_buf[temp_buf_ix++] = (uint8)offset;
                    }
                    else
                    {
                        temp_buf[temp_buf_ix++] = 0x29;
                        temp_buf[temp_buf_ix++] = 0;
                        rta_PutLitEndian16(offset, &temp_buf[temp_buf_ix]);
                        temp_buf_ix+=2;
                    }

                    /* clear flag and temp buffers, we found the offset */
                    wait4bracket = 0;
                    memset(array_ix_buf, 0, sizeof(array_ix_buf));
                    array_ix_buf_ix = 0;
                }
                /* IOI String (normal processing) */
                else
                {
                    /* tag error */
                    return(-8);
                }                
                break;
            default:
                /* Waiting for matching bracket */
                if(wait4bracket)
                {
                    array_ix_buf[array_ix_buf_ix++] = tag_name[tag_name_parse_ix];
                }
                /* IOI String (normal processing) */
                else
                {
                    /* first character, send the IOI header */
                    if(ioi_size == 0)
                    {
                        /* store the start of the IOI */
                        temp_buf[temp_buf_ix++] = 0x91;
                        ioi_size_ix_local = temp_buf_ix;
                        temp_buf_ix++; /* fill in later */
                    }
    
                    /* store the character */
                    temp_buf[temp_buf_ix++] = tag_name[tag_name_parse_ix];
                    ioi_size++;
                }
                break;
        };

        /* advance the parsing index */
        tag_name_parse_ix++;
    }

    /* store the previous size (pad if necesary) */
    if(ioi_size)
    {
        /* store the previous string size */
        temp_buf[ioi_size_ix_local] = ioi_size;
        if((ioi_size%2) == 1) /* odd # chars */
            temp_buf[temp_buf_ix++] = 0; /* add a padding 0 */
    }
    
    /* validate we have room */
    if(temp_buf_ix > max_num_buf_bytes)
        return(-9);
            
    /* store the string */
    rta_ByteMove(buf, temp_buf, temp_buf_ix);

    /* return the number of used bytes */
    return(temp_buf_ix);
}

/* ====================================================================
Function:     local_find_free_server_handle
Parameters:   ipadd
Returns:      N/A

This function returns the next available server handle (0 on error).
======================================================================= */
static int16 local_find_free_server_handle (uint32 ipaddr)
{
    uint16 i;
    int16 serv_handle;

    // make sure the IP Addres is non-zero
    if(ipaddr == 0)
        return(EIPC_SERVERHANDLE_UNUSED);

    // search for a free server_handle (IP Address = 0)
    for(i=0; i<EIPC_USEROBJ_MAX_NUM_SERVER_HANDLES; i++)
    {
        // if the IP Address matches a used entry, reuse
        // the server handle
        if( (ServerHandles[i].IPAddr == ipaddr) && 
            (ServerHandles[i].ServerHandle != EIPC_SERVERHANDLE_UNUSED))
        {
            return(ServerHandles[i].ServerHandle);
        }
    
        // if the handle isn't used 
        if(ServerHandles[i].ServerHandle == EIPC_SERVERHANDLE_UNUSED)
        {
            // get the next unused handle
            serv_handle = local_get_next_server_handle_id();

            // store the IP address and server handle
            ServerHandles[i].IPAddr = ipaddr;
            ServerHandles[i].ServerHandle = serv_handle;

            // success!! return the server handle
            return(serv_handle);
        }
    }
   
    // no free server handles
    return(EIPC_SERVERHANDLE_UNUSED);
}

/* ====================================================================
Function:     local_get_server_struct
Parameters:   Server Handle
Returns:      pointer to Server Handle structure (NULL on ERROR)

This function returns the server handle structure for the passed
server handle (NULL on error).
======================================================================= */
static EIPC_HANDLE_STRUCT * local_get_server_struct (int16 server_handle)
{
    uint16 i;

    // find the server handle structure based on the handle
    for(i=0; i<EIPC_USEROBJ_MAX_NUM_SERVER_HANDLES; i++)
    {
        // the server handle matches, return the structure
        if(ServerHandles[i].ServerHandle == server_handle)
        {
            return(&ServerHandles[i]);
        }
    
    }

    // server handle not found
    return(NULL);
}

/* ====================================================================
Function:     local_init_server_handle
Parameters:   pointer to server handle structure
Returns:      N/A

This function initializes the server handle structure.
======================================================================= */
static void local_init_server_handle (EIPC_HANDLE_STRUCT *server_handle_ptr)
{
    /* free any sockets */
    eipc_usersock_tcpClose(server_handle_ptr->SockID);

    /* make sure all the timers are stopped */
    eipc_timer_stop(server_handle_ptr->TimerNum);

    /* general server control variables */
    server_handle_ptr->IPAddr       = 0;
    server_handle_ptr->ServerHandle = EIPC_SERVERHANDLE_UNUSED;
    server_handle_ptr->SessionID    = 0;
    server_handle_ptr->UCMMState    = EIPC_CLIENT_UCMMSERVERSTATE_NONEXIST;
    server_handle_ptr->SockID       = EIPC_USER_SOCKET_UNUSED;
    server_handle_ptr->LastEncapCmd = 0;

#ifdef EIPC_EM_CLASS3_CNXN_USED
    /* explicit connection handling */
    server_handle_ptr->EM_CnxnState = EIPC_CLIENT_EMCLASS3CNXNSTATE_NONEXIST;
    eipc_timer_stop(server_handle_ptr->EM_TimerNum);
    server_handle_ptr->EM_CnxnTmoCnt = 0;
    server_handle_ptr->EM_O2T_CnxnID = 0;
    server_handle_ptr->EM_O2T_SeqNum = 0;
    server_handle_ptr->EM_T2O_CnxnID = 0;
    server_handle_ptr->EM_T2O_SeqNum = 0;
#endif
}

/* ====================================================================
Function:     local_get_next_server_handle_id
Parameters:   N/A
Returns:      next server handle id

This function returns the next server handle id. Thd id must be > 0 and
not in use by any other server.
======================================================================= */
static int16 local_get_next_server_handle_id (void)
{
    int16 return_code;
    uint16 i;

    // default to an error
    return_code = EIPC_SERVERHANDLE_UNUSED;

    //keep going until we find an unused server handle id
    while(return_code == EIPC_SERVERHANDLE_UNUSED)
    {
        // find the next free server handle
        NextServerHandle++;

        // roll over if needed (0 is invalid)
        if(NextServerHandle <=0)
            NextServerHandle = 1;

        // store the new return code
        return_code = NextServerHandle;

        // validate this server handle isn't used
        for(i=0; i<EIPC_USEROBJ_MAX_NUM_SERVER_HANDLES; i++)
        {
            // server handle is already used, mark as invalid
            if(ServerHandles[i].ServerHandle == NextServerHandle)
                return_code = EIPC_SERVERHANDLE_UNUSED;
        }
    }

    // we found a valid server handle
    return(return_code);
}

/* ====================================================================
Function:     local_client_timeout
Parameters:   Timer Index
Returns:      N/A

This function handles client timeouts (this is a timeout, close the
connection to the server and start over).
======================================================================= */
static void local_client_timeout (uint16 timer_ix)
{
   uint16 i, server_handle;

   // find which server timed out
   for(i=0; i<EIPC_USEROBJ_MAX_NUM_SERVER_HANDLES && ServerHandles[i].TimerNum!=timer_ix; i++);
   if(i==EIPC_USEROBJ_MAX_NUM_SERVER_HANDLES)
      return;
  
   // save the server_handle to alert the user and free the resources  
   server_handle = ServerHandles[i].ServerHandle;
   local_init_server_handle (&ServerHandles[i]);       

   // inform the user application of the new states
   eipc_usersys_UCMMStateChanged (server_handle, EIPC_CLIENT_UCMMSERVERSTATE_NONEXIST);
}

/* ====================================================================
Function:     local_em_timeout
Parameters:   Timer Index
Returns:      N/A

This function handles explicit connection timeouts. On a timeout inform
the customer they may want to send an explicit message.
======================================================================= */
#ifdef EIPC_EM_CLASS3_CNXN_USED
static void local_em_timeout (uint16 timer_ix)
{
    uint16 i, server_handle;

    // find which server timed out
    for(i=0; i<EIPC_USEROBJ_MAX_NUM_SERVER_HANDLES && ServerHandles[i].EM_TimerNum!=timer_ix; i++);
    if(i==EIPC_USEROBJ_MAX_NUM_SERVER_HANDLES)
        return;
  
    // keep track of the number of consecutive timeouts
    ServerHandles[i].EM_CnxnTmoCnt++;

    if(ServerHandles[i].EM_CnxnTmoCnt >= (EIPC_CNXNTMOMULT[EIPC_USEROBJ_RPI_CNXNTMO_MULT]))
    {
        // save the server_handle to alert the user and free the resources  
        server_handle = ServerHandles[i].ServerHandle;
        local_init_server_handle (&ServerHandles[i]);       

        // inform the user application of the new states
        eipc_usersys_UCMMStateChanged (server_handle, EIPC_CLIENT_UCMMSERVERSTATE_NONEXIST);
    }
    else
    {
        // inform the user application of the need to send a message, 
        // BUT DON'T CHANGE THE STATE... we need to stay in the READY state to allow 
        // the message to send
        eipc_usersys_EmCnxnStateChanged (ServerHandles[i].ServerHandle, EIPC_CLIENT_EMCLASS3CNXNSTATE_NEED2SEND);

        // reset the timer
        eipc_timer_reset(timer_ix);
    }
}
#endif

/* ====================================================================
Function:     local_procrsp_reg_session
Parameters:   pointer to server handle structure
Returns:      N/A

This function initializes the server handle structure.
======================================================================= */
static void local_procrsp_reg_session (EIPC_ENCAP_MSG_STRUCT *encap, EIPC_HANDLE_STRUCT *server_handle_ptr)
{
   /* make sure the response is succesful and the server handle is waiting 
      for this message */
    if(encap->Status != EIP_ENCAPSTATUSERR_SUCCESS)
    {
        eipc_tagclient_onClose(server_handle_ptr->SockID);
        return;
    }

    /* store the session handle and inform the user of the state change */
    server_handle_ptr->SessionID = encap->SessionHandle;

    /* inform the user of the open */
    server_handle_ptr->UCMMState = EIPC_CLIENT_UCMMSERVERSTATE_READY;
    eipc_usersys_UCMMStateChanged (server_handle_ptr->ServerHandle, EIPC_CLIENT_UCMMSERVERSTATE_READY);
}

/* ====================================================================
Function:     local_procrsp_ucmm
Parameters:   pointer to encap message structure
              pointer to server handle structure
Returns:      N/A

This function processes the UCMM response from the server.
======================================================================= */
static void local_procrsp_ucmm (EIPC_ENCAP_MSG_STRUCT *encap, EIPC_HANDLE_STRUCT *server_handle_ptr)
{
    uint16 i, bytes_used;
    CPF_MESSAGE_STRUCT eipc_cpf;
    EXPLICIT_RESPONSE_STRUCT  eipc_emrsp;
#if defined(EIPC_EM_CLASS3_CNXN_USED) || defined(EIPC_TAG_CLIENT_USED)
    uint16 offset_ix;
#endif

#ifdef EIPC_TAG_CLIENT_USED
    uint16 j, k;
    uint16 count, offset, next_offset, bytes_left, data_len;
#endif
   
    // stop the timer
    eipc_timer_stop(server_handle_ptr->TimerNum);

    // make sure the Session Handle is ours
    if(server_handle_ptr->SessionID != encap->SessionHandle)
        return;

    // make sure the status is success
    if(encap->Status != EIP_ENCAPSTATUSERR_SUCCESS)
    {
        eipc_tagclient_onClose(server_handle_ptr->SockID);
        return;
    }

    // zero fill the message structure
    memset(&eipc_cpf,   0, sizeof(CPF_MESSAGE_STRUCT));
    memset(&eipc_emrsp, 0, sizeof(eipc_emrsp));

    /* store the Encapsulated data length and data pointer */
    eipc_cpf.bytes_used = 0;
    eipc_cpf.encap_data = encap->EncapsulatedData; 

    /* Get Interface Handle */
    eipc_cpf.InterfaceHandle = rta_GetLitEndian32(eipc_cpf.encap_data);
    eipc_cpf.encap_data+=4;   /* move data pointer by data copied length */
    eipc_cpf.bytes_used += 4; /* incr the count (validate data prior to use) */

    /* Get Timeout */
    eipc_cpf.Timeout = rta_GetLitEndian16(eipc_cpf.encap_data);
    eipc_cpf.encap_data+=2;   /* move data pointer by data copied length */
    eipc_cpf.bytes_used += 2; /* incr the count (validate data prior to use) */

    /* Validate the number of items */
    eipc_cpf.ItemCount = rta_GetLitEndian16(eipc_cpf.encap_data);
    eipc_cpf.encap_data+=2;   /* move data pointer by data copied length */
    eipc_cpf.bytes_used += 2; /* incr the count (validate data prior to use) */

    /* Error: Too Many Items */
    if(eipc_cpf.ItemCount > EIPC_CPF_MAX_ITEM_CNT)
    {
        eipc_tagclient_onClose(server_handle_ptr->SockID);
        return; /* Stop this function on an error */
    }

    /* Parse the CPF message into items */
    for(i=0; i<eipc_cpf.ItemCount; i++)
    {
        /* store the type */
        eipc_cpf.Items[i].TypeId = rta_GetLitEndian16(eipc_cpf.encap_data);
        eipc_cpf.encap_data+=2;   /* move data pointer by data copied length */
        eipc_cpf.bytes_used += 2; /* incr the count (validate data prior to use) */

        /* store the length */
        eipc_cpf.Items[i].Length = rta_GetLitEndian16(eipc_cpf.encap_data);
        eipc_cpf.encap_data+=2;   /* move data pointer by data copied length */
        eipc_cpf.bytes_used += 2; /* incr the count (validate data prior to use) */

        /* validate there is enough room for data */
        if(eipc_cpf.Items[i].Length > EIPC_CPF_MAX_ITEM_DATA_LEN)
        {
            eipc_tagclient_onClose(server_handle_ptr->SockID);
            return; /* Stop this function on an error */
        }

        /* store the data */
        rta_ByteMove(eipc_cpf.Items[i].Data, eipc_cpf.encap_data, eipc_cpf.Items[i].Length);
        eipc_cpf.encap_data += eipc_cpf.Items[i].Length; /* move data pointer by data copied length */
        eipc_cpf.bytes_used += eipc_cpf.Items[i].Length; /* incr the count (validate data prior to use) */
    }

    /* validate the buffer had the exact message prior to use */
    if(eipc_cpf.bytes_used != encap->Length)
    {
        eipc_tagclient_onClose(server_handle_ptr->SockID);
        return; /* Stop this function on an error */
    }

    /* all messages should have at least 2 items */
    if(eipc_cpf.ItemCount < 2)
    {
        eipc_tagclient_onClose(server_handle_ptr->SockID);
        return; /* Stop this function on an error */
    }

    switch(server_handle_ptr->LastEncapCmd)
    {
        case EIP_ENCAPCMD_SENDRRDATA:
            /* Item 0 should be NULL (Address Item) with no data */
            if((eipc_cpf.Items[0].Length != 0) || (eipc_cpf.Items[0].TypeId != ADDR_TYP_ID_NULL))
            {
                eipc_tagclient_onClose(server_handle_ptr->SockID);
                return; /* Stop this function on an error */
            }

            /* Item 1 should be UCMM (Data Item) with some data */
            if((eipc_cpf.Items[1].Length == 0) || (eipc_cpf.Items[1].TypeId != DATA_TYP_ID_UCMM))
            {
                eipc_tagclient_onClose(server_handle_ptr->SockID);
                return; /* Stop this function on an error */
            }

            /* parse the response message */
            bytes_used = 0;
            break;

#ifdef EIPC_EM_CLASS3_CNXN_USED
        case EIP_ENCAPCMD_SENDUNITDATA:
            /* Item 0 should be NULL (Address Item) with no data */
            if((eipc_cpf.Items[0].Length != 4) || (eipc_cpf.Items[0].TypeId != ADDR_TYP_ID_CNXNBASED)
                || (server_handle_ptr->EM_T2O_CnxnID != rta_GetLitEndian32(eipc_cpf.Items[0].Data)))
            {
                eipc_tagclient_onClose(server_handle_ptr->SockID);
                return; /* Stop this function on an error */
            }

            /* Item 1 should be PDU (Data Item) with some data */
            if((eipc_cpf.Items[1].Length < 2) || (eipc_cpf.Items[1].TypeId != DATA_TYP_ID_PDU))
            {
                eipc_tagclient_onClose(server_handle_ptr->SockID);
                return; /* Stop this function on an error */
            }

            /* check sequence number */
            if(server_handle_ptr->EM_O2T_SeqNum != rta_GetLitEndian16(eipc_cpf.Items[1].Data))
            {
                eipc_tagclient_onClose(server_handle_ptr->SockID);
                return; /* Stop this function on an error */
            }

            /* zero out the consecutive timeout */
            server_handle_ptr->EM_CnxnTmoCnt = 0;

            /* parse the response message */
            bytes_used = 2;
            break;
#endif

        default:
            eipc_tagclient_onClose(server_handle_ptr->SockID);
            return; /* Stop this function on an error */
    };

    // service code
    eipc_emrsp.service = eipc_cpf.Items[1].Data[bytes_used++];   

    // reserved byte
    bytes_used++;
    // general status
    eipc_emrsp.user_struct.gen_stat = eipc_cpf.Items[1].Data[bytes_used++];

    // extended status size
    eipc_emrsp.user_struct.ext_stat_size = eipc_cpf.Items[1].Data[bytes_used++];

    // extended status (if any)
    for(i=0; i<eipc_emrsp.user_struct.ext_stat_size; i++)
    {
        eipc_emrsp.user_struct.ext_stat[i] =  rta_GetLitEndian16(eipc_cpf.Items[1].Data + bytes_used);
        bytes_used+=2;
    }

    // Not Enough Data Error
    if(bytes_used > eipc_cpf.Items[1].Length)
    {
        eipc_tagclient_onClose(server_handle_ptr->SockID);
        return; /* Stop this function on an error */
    }

    // store the data (if any)
    eipc_emrsp.user_struct.rsp_data_size = 0;
    for(i=bytes_used; i<eipc_cpf.Items[1].Length; i++)
    {
        eipc_emrsp.user_struct.rsp_data[eipc_emrsp.user_struct.rsp_data_size++] = eipc_cpf.Items[1].Data[i];      
    }

    // switch on the service code
    switch (eipc_emrsp.service)
    {		
#ifdef EIPC_EM_CLASS3_CNXN_USED
        // Forward Open Response
        case 0xD4:
            // make sure there is enough data in the response
            if(eipc_emrsp.user_struct.rsp_data_size < 26)
            {
                return;
            }

            // parse the message
            offset_ix = 0;

            // store the O->T Network Connection ID
            server_handle_ptr->EM_O2T_CnxnID = rta_GetLitEndian32(&eipc_emrsp.user_struct.rsp_data[offset_ix]);
            offset_ix+=4;

            // store the T->O Network Connection ID
            server_handle_ptr->EM_T2O_CnxnID = rta_GetLitEndian32(&eipc_emrsp.user_struct.rsp_data[offset_ix]);
            offset_ix+=4;

            // verify the Connection Serial Number is ours
            if(server_handle_ptr->ServerHandle != rta_GetLitEndian16(&eipc_emrsp.user_struct.rsp_data[offset_ix]))
            {
                return;
            }
            offset_ix+=2;

            // verify the Vendor ID is ours
            if(EIPC_USER_IDOBJ_VENDORID != rta_GetLitEndian16(&eipc_emrsp.user_struct.rsp_data[offset_ix]))
            {
                return;
            }
            offset_ix+=2;
    
            // verify the Originator Serial Number is ours
            if(eipc_userobj_getSerialNumber() != rta_GetLitEndian32(&eipc_emrsp.user_struct.rsp_data[offset_ix]))
            {
                return;
            }
            offset_ix+=4;

            // transition the state 
            server_handle_ptr->EM_CnxnState = EIPC_CLIENT_EMCLASS3CNXNSTATE_READY;

            // store the O->T API

            // store the T->O API
            break;
#endif

#ifdef EIPC_TAG_CLIENT_USED
        // multi-request response
        case 0x8A:
            // store the count (number or responses)
            count = rta_GetLitEndian16(&eipc_emrsp.user_struct.rsp_data[0]);
            server_handle_ptr->tag_cnt = count;

            // store the bytes left (so we can calulate the last data length)
            bytes_left = eipc_emrsp.user_struct.rsp_data_size-2; // subtract 2 for the count

            // store the offset count
            offset_ix = 2;

            // store all the responses
            for(i=0; i<count; i++)
            {
                // calculate the offset
                offset = rta_GetLitEndian16(&eipc_emrsp.user_struct.rsp_data[offset_ix]);
                k = 0;
                offset_ix+=2;
                
                // calculate the data length
                if(i+1 < count)
                {
                    next_offset = rta_GetLitEndian16(&eipc_emrsp.user_struct.rsp_data[offset_ix]);
                    data_len = (next_offset - offset - 4);
                }
                else
                {
                    data_len = (bytes_left - 6); // offset (2 bytes), serv code (2 bytes), status (2 bytes)
                }

                // calculate the number of bytes left
                bytes_left = (bytes_left - data_len - 6); // offset (2 bytes), serv code (2 bytes), status (2 bytes)

                // store the service code (8-bit)
				server_handle_ptr->tag_ptr[i].service_code = eipc_emrsp.user_struct.rsp_data[offset+k];
                k+=2;

                // store the general status (8-bit)
                server_handle_ptr->tag_ptr[i].gen_status = eipc_emrsp.user_struct.rsp_data[(offset+k)];
                k++;

                // if the ext status size is 1, store the extended status
                if(eipc_emrsp.user_struct.rsp_data[(offset+k)] > 0)
                {
                    k++;
                    server_handle_ptr->tag_ptr[i].ext_status = rta_GetLitEndian16(&eipc_emrsp.user_struct.rsp_data[(offset+k)]);
                    k+=2;
                }
                
                else
                    k++;

                // READ RESPONSES ONLY!!!! (service code = 0xCC)
                if((server_handle_ptr->tag_ptr[i].service_code == 0xCC) && (server_handle_ptr->tag_ptr[i].gen_status == ERR_SUCCESS))
                {
                    // store the data type (if present)
                    server_handle_ptr->tag_ptr[i].tag_data_type = rta_GetLitEndian16(&eipc_emrsp.user_struct.rsp_data[(offset+k)]);
                    k+=2;

                    // store the data
                    data_len = (data_len - 2);
                    server_handle_ptr->tag_ptr[i].tag_data_len = data_len;
                    for(j=0; j<server_handle_ptr->tag_ptr[i].tag_data_len; j++)       
                    {
                        server_handle_ptr->tag_ptr[i].tag_data_ptr[j] = eipc_emrsp.user_struct.rsp_data[(offset+k+j)];
                    }                    
                }
                // WRITE RESPONSE!!! (service code = CD)
                else
                {
                    server_handle_ptr->tag_ptr[i].tag_data_len = 0;
                }
            }
            
			// inform the user of the response
            eipc_userobj_procTagAccessResp  (server_handle_ptr->ServerHandle, eipc_emrsp.user_struct.gen_stat, server_handle_ptr->tag_cnt, server_handle_ptr->tag_ptr);
            break;
#endif

#ifdef EIPC_PCCC_CLIENT_USED
            case 0xCB:
                /* make sure we have at least 11 bytes */
                if(eipc_emrsp.user_struct.rsp_data_size < 11)
                    eipc_userobj_procPcccResp(server_handle_ptr->ServerHandle, eipc_emrsp.user_struct.gen_stat, -1, 0, NULL);

                /* size must be 7 */
                else if(eipc_emrsp.user_struct.rsp_data[0] != 7)
                    eipc_userobj_procPcccResp(server_handle_ptr->ServerHandle, eipc_emrsp.user_struct.gen_stat, -2, 0, NULL);

                /* Vendor ID = 50, 0 */
                else if((eipc_emrsp.user_struct.rsp_data[1] != 50) || (eipc_emrsp.user_struct.rsp_data[2] != 0))
                    eipc_userobj_procPcccResp(server_handle_ptr->ServerHandle, eipc_emrsp.user_struct.gen_stat, -3, 0, NULL);

                /* serial number must match ([3-6] */
                else if(eipc_userobj_getSerialNumber() != rta_GetLitEndian32(&eipc_emrsp.user_struct.rsp_data[3]))
                    eipc_userobj_procPcccResp(server_handle_ptr->ServerHandle, eipc_emrsp.user_struct.gen_stat, -4, 0, NULL);

                /* Command must be 0x4F */
                else if(eipc_emrsp.user_struct.rsp_data[7] != 0x4F)
                    eipc_userobj_procPcccResp(server_handle_ptr->ServerHandle, eipc_emrsp.user_struct.gen_stat, -5, 0, NULL);

                /* STS must be 0 */
                else if(eipc_emrsp.user_struct.rsp_data[8] != 0)
                    eipc_userobj_procPcccResp(server_handle_ptr->ServerHandle, eipc_emrsp.user_struct.rsp_data[8], -6, 0, NULL);

                /* TNS must match sent value */
                else if(rta_GetLitEndian16(&eipc_emrsp.user_struct.rsp_data[9]) != server_handle_ptr->tns)
                    eipc_userobj_procPcccResp(server_handle_ptr->ServerHandle, eipc_emrsp.user_struct.gen_stat, -7, 0, NULL);

                /* pass the data to the user */
                else
                    eipc_userobj_procPcccResp(server_handle_ptr->ServerHandle, eipc_emrsp.user_struct.gen_stat, 0, (uint16)(eipc_emrsp.user_struct.rsp_data_size-11), &eipc_emrsp.user_struct.rsp_data[11]);

		        /* inform the user that UCMM is free again */
        		server_handle_ptr->UCMMState = EIPC_CLIENT_UCMMSERVERSTATE_READY;
	    	    eipc_usersys_UCMMStateChanged (server_handle_ptr->ServerHandle, EIPC_CLIENT_UCMMSERVERSTATE_READY);               
                break;
#endif

        // unknown response (generic UCMM)
        default:
#ifdef EIPC_EM_CLIENT_USED
            eipc_userobj_procEmResp (server_handle_ptr->ServerHandle, &eipc_emrsp.user_struct);
#endif
            break;
    };

    switch(server_handle_ptr->LastEncapCmd)
    {
        case EIP_ENCAPCMD_SENDRRDATA:
            // inform the user that the UCMM is READY
            server_handle_ptr->UCMMState = EIPC_CLIENT_UCMMSERVERSTATE_READY;
            eipc_usersys_UCMMStateChanged (server_handle_ptr->ServerHandle, EIPC_CLIENT_UCMMSERVERSTATE_READY);
            break;

#ifdef EIPC_EM_CLASS3_CNXN_USED
        case EIP_ENCAPCMD_SENDUNITDATA:
            /* transition the state */
            server_handle_ptr->EM_CnxnState = EIPC_CLIENT_EMCLASS3CNXNSTATE_READY;
            eipc_usersys_EmCnxnStateChanged(server_handle_ptr->ServerHandle, server_handle_ptr->EM_CnxnState);
            break;
#endif

        default:
            eipc_tagclient_onClose(server_handle_ptr->SockID);
            return; /* Stop this function on an error */
    };
}

/* ====================================================================
Function:   local_buildTagRead_common
Parameters: pointer to buffer to add data
            maximum number of bytes available in buffer
            pointer to Tag message structure
Returns:    number of bytes added (<0 on error)

This function adds the Tag Read message common portion (both connected
and unconnected).
======================================================================= */
#ifdef EIPC_TAG_CLIENT_USED
static int16 local_buildTagRead_common (uint8 *buf, uint16 max_num_buf_bytes, uint8 tag_cnt, EIPC_TAG_STRUCT *tag_ptr)
{
    uint16  path_word_size_ix;
    uint16  multireq_offsetix, mult_ix, mult_base_ix;
    uint16  msg_size;
    int16   return_code;
    uint8   msg[500];          /* temp buffer to avoid buffer overflow */

    // Use the Multi-Request Service
    msg_size = 0;
    msg[msg_size++] = 0x0A; // UnCnSndCmd: MultiReqServ (CMD)
    msg[msg_size++] = 0x02; // UnCnSndCmd: MultiReqServ (2 Path Elements)
    msg[msg_size++] = 0x20; // UnCnSndCmd: MultiReqServ (8-bit Class)
    msg[msg_size++] = 0x02; // UnCnSndCmd: MultiReqServ (Message Router)
    msg[msg_size++] = 0x24; // UnCnSndCmd: MultiReqServ (8-bit Instance)
    msg[msg_size++] = 0x01; // UnCnSndCmd: MultiReqServ (Instance 1)

    // store the number of requests
    mult_base_ix = msg_size;
    rta_PutLitEndian16(tag_cnt, msg+msg_size); // item count
    msg_size +=2;

    // advance the index based on the number of requests
    multireq_offsetix = msg_size;
    msg_size += (2*tag_cnt);

    // store the request services
    for(mult_ix = 0; mult_ix < tag_cnt; mult_ix++)
    {
        // store the Offset for this command
        rta_PutLitEndian16(((uint16)(msg_size - mult_base_ix)), msg+multireq_offsetix); // item count
        multireq_offsetix += 2;

        // CIP Service: CIP Rd Data Service Code
        msg[msg_size++] = 0x4C; 

        // Store the overall size later
        path_word_size_ix = msg_size;    
        msg[msg_size++] = 0; // write over later

        // Add the tag name to the buffer        
        return_code = local_add_tag_name_to_buffer((uint8 *)tag_ptr[mult_ix].tag_name, tag_ptr[mult_ix].tag_name_len, &msg[msg_size], (uint16)(sizeof(msg)-msg_size));

        // function return the number of bytes stored
        if(return_code >= 0)
            msg_size += return_code;
        else
            return(EIPC_CLIENT_UCMMERR_TAGFMT);

        // store the word length (overall size)
        msg[path_word_size_ix] = (uint8)((return_code+1)/2);

        // add the number of elements to read (uint16)
        rta_PutLitEndian16(tag_ptr[mult_ix].tag_num_elements, msg+msg_size);
        msg_size += 2;
    } // END of Multi-Request Service

    // will the message fit?
    if(msg_size > max_num_buf_bytes)
        return(EIPC_CLIENT_UCMMERR_TAGPTR);

    // store the response
    memcpy(buf, msg, msg_size);

    // return the amount of data copied
    return(msg_size);
}
#endif /* #ifdef EIPC_TAG_CLIENT_USED */

/* ====================================================================
Function:   local_buildTagWrite_common
Parameters: pointer to buffer to add data
            maximum number of bytes available in buffer
            pointer to Tag message structure
Returns:    number of bytes added (<0 on error)

This function adds the Tag Write message common portion (both connected
and unconnected).
======================================================================= */
#ifdef EIPC_TAG_CLIENT_USED
static int16 local_buildTagWrite_common (uint8 *buf, uint16 max_num_buf_bytes, uint8 tag_cnt, EIPC_TAG_STRUCT *tag_ptr)
{
    uint16  path_word_size_ix;
    uint16  multireq_offsetix, mult_ix, mult_base_ix;
    uint16  msg_size, i;
    int16   return_code;
    uint8   msg[500];          /* temp buffer to avoid buffer overflow */

    // Use the Multi-Request Service
    msg_size = 0;

    // Use the Multi-Request Service
    msg[msg_size++] = 0x0A; // UnCnSndCmd: MultiReqServ (CMD)
    msg[msg_size++] = 0x02; // UnCnSndCmd: MultiReqServ (2 Path Elements)
    msg[msg_size++] = 0x20; // UnCnSndCmd: MultiReqServ (8-bit Class)
    msg[msg_size++] = 0x02; // UnCnSndCmd: MultiReqServ (Message Router)
    msg[msg_size++] = 0x24; // UnCnSndCmd: MultiReqServ (8-bit Instance)
    msg[msg_size++] = 0x01; // UnCnSndCmd: MultiReqServ (Instance 1)

    // store the number of requests
    mult_base_ix = msg_size;
    rta_PutLitEndian16(tag_cnt, msg+msg_size); // item count
    msg_size +=2;

    // advance the index based on the number of requests
    multireq_offsetix = msg_size;
    msg_size += (2*tag_cnt);

    // store the request services
    for(mult_ix = 0; mult_ix < tag_cnt; mult_ix++)
    {
        // store the Offset for this command
        rta_PutLitEndian16(((uint16)(msg_size - mult_base_ix)), msg+multireq_offsetix); // item count
        multireq_offsetix += 2;

        msg[msg_size++] = 0x4D; // CIP Service: CIP Write Data Service Code

        // Store the overall size later
        path_word_size_ix = msg_size;    
        msg[msg_size++] = 0; // write over later

        // Add the tag name to the buffer        
        return_code = local_add_tag_name_to_buffer((uint8 *)tag_ptr[mult_ix].tag_name, tag_ptr[mult_ix].tag_name_len, &msg[msg_size], (uint16)(sizeof(msg)-msg_size));

        // function return the number of bytes stored
        if(return_code >= 0)
            msg_size += return_code;
        else
            return(EIPC_CLIENT_UCMMERR_TAGFMT);

        // store the word length (overall size)
        msg[path_word_size_ix] = (uint8)((return_code+1)/2);

		// add the data type
		rta_PutLitEndian16(tag_ptr[mult_ix].tag_data_type, msg+msg_size);
        msg_size += 2;

        /* set the structure handle if needed */
        if(tag_ptr[mult_ix].tag_data_type == CL_DATATYPE_STRUCTURE)
        {
            rta_PutLitEndian16(tag_ptr[mult_ix].tag_structure_handle, msg+msg_size);
            msg_size += 2;
        }

        // add the size (in elements)
        rta_PutLitEndian16(tag_ptr[mult_ix].tag_num_elements, msg+msg_size);
        msg_size += 2;

        // add the data (in bytes)
        for(i=0; i<tag_ptr[mult_ix].tag_data_len; i++)
            msg[msg_size++] = tag_ptr[mult_ix].tag_data_ptr[i];

        // pad a zero byte (if odd number of bytes)
        if((tag_ptr[mult_ix].tag_data_len%2)==1)
            msg[msg_size++] = 0;
    } // END of Multi-Request Service

    // will the message fit?
    if(msg_size > max_num_buf_bytes)
        return(EIPC_CLIENT_UCMMERR_TAGPTR);

    // store the response
    memcpy(buf, msg, msg_size);

    // return the amount of data copied
    return(msg_size);
}
#endif /* #ifdef EIPC_TAG_CLIENT_USED */

/* ====================================================================
Function:   local_buildPcccRead_common
Parameters: pointer to server structure (so we know SLC/PLC)
            pointer to buffer to add data
            maximum number of bytes available in buffer
            pointer to PCCC message structure
Returns:    number of bytes added (<0 on error)

This function adds the PCCC Read message common portion (both connected
and unconnected).
======================================================================= */
#ifdef EIPC_PCCC_CLIENT_USED
static int16 local_buildPcccRead_common (EIPC_HANDLE_STRUCT *server, uint8 *buf, uint16 max_num_buf_bytes, EIPC_PCCC_STRUCT *pccc_ptr)
{
    uint8   msg[500];          /* temp buffer to avoid buffer overflow */
    uint16  msg_size, i;
    char    ascii_addr[51];

    /* build the passed part of the message */
    msg_size = 0;
    msg[msg_size++] = 0x4B; /* Execute PCCC  */
    msg[msg_size++] = 0x02; /* Execute PCCC: path size */
    msg[msg_size++] = 0x20; /* Execute PCCC: 8-bit class */
    msg[msg_size++] = 0x67; /* Execute PCCC: PCCC Object */
    msg[msg_size++] = 0x24; /* Execute PCCC: 8-bit instance */
    msg[msg_size++] = 0x01; /* Execute PCCC: Instance 1 */
    msg[msg_size++] = 0x07; /* Execute PCCC: Req ID Length (vid + s/n + other + 1) */
    msg[msg_size++] = 0x32; /* Execute PCCC: Vendor ID (we are 50) */
    msg[msg_size++] = 0x00; /* Execute PCCC: Vendor ID (we are 50) */

    /* store the serial number */
    rta_PutLitEndian32(eipc_userobj_getSerialNumber(),msg+msg_size);
    msg_size = msg_size + 4;
    
    msg[msg_size++] = 0x0F; /* store the command  */
    msg[msg_size++] = 0x00; /* store the status */

    /* store the TNS */
    server->tns++;
    rta_PutLitEndian16(server->tns, msg+msg_size); 
    msg_size += 2;

    /* PLC */
    if(pccc_ptr->pccc_plc_type == EIPC_PCCC_PLC_TYPE_PLC5E)
    {
        /* store FNC "Typed Read" */
        msg[msg_size++] = 0x68; /* store the command      */

        /* store the Packet Offset */
        rta_PutLitEndian16(0 , msg+msg_size); 
        msg_size += 2;

        /* store the Total Trans (number of units to read) */
        rta_PutLitEndian16(pccc_ptr->pccc_num_elements, msg+msg_size); 
        msg_size += 2;

        /* store a NULL to start the string */
        msg[msg_size++] = 0x00;

        /* store the PLC-5 sys. address */
        sprintf(ascii_addr, "$%s:%d", pccc_ptr->pccc_file_string, pccc_ptr->pccc_file_offset);

        /* copy the address */
        for(i=0; i<strlen(ascii_addr); i++)
            msg[msg_size++] = ascii_addr[i];

        /* add a NULL terminator */
        msg[msg_size++] = 0x00; 

        /* store the size */
        rta_PutLitEndian16(pccc_ptr->pccc_num_elements, msg+msg_size); 
        msg_size += 2;        
    }

    /* SLC */
    else
    {
        /* store FNC "Protected Typed Logical Read w/3 addr fields" */
        msg[msg_size++] = 0xA2; /* store the command   */

        /* store the byte size */
        msg[msg_size++] = (uint8)(pccc_ptr->pccc_element_size_in_bytes*pccc_ptr->pccc_num_elements); 
        
        /* store the file number */
        if(pccc_ptr->pccc_file_num > 254)
        {
            msg[msg_size++] = 0xFF; /* expand to 3 field address */
            rta_PutLitEndian16(pccc_ptr->pccc_file_num, msg+msg_size); 
            msg_size += 2;        
        }
        else
            msg[msg_size++] = (uint8)pccc_ptr->pccc_file_num; /* store the file number */

        /* store the file type (output logical by slot) */
        msg[msg_size++] = pccc_ptr->pccc_data_type;

        /* store the element number */
        if(pccc_ptr->pccc_file_offset > 254)
        {
            msg[msg_size++] = 0xFF; /* expand to 3 field address */
            rta_PutLitEndian16(pccc_ptr->pccc_file_offset, msg+msg_size); 
            msg_size += 2;        
        }
        else
            msg[msg_size++] = (uint8)pccc_ptr->pccc_file_offset; /* store the file number */

        /* store the sub-element number */
        msg[msg_size++] = 0x00; 
    }

    // will the message fit?
    if(msg_size > max_num_buf_bytes)
        return(EIPC_CLIENT_UCMMERR_TAGPTR);

    // store the response
    memcpy(buf, msg, msg_size);

    // return the amount of data copied
    return(msg_size);
}
#endif /* #ifdef EIPC_PCCC_CLIENT_USED */

/* ====================================================================
Function:   local_buildPcccWrite_common
Parameters: pointer to server structure (so we know SLC/PLC)
            pointer to buffer to add data
            maximum number of bytes available in buffer
            pointer to PCCC message structure
Returns:    number of bytes added (<0 on error)

This function adds the PCCC Write message common portion (both connected
and unconnected).
======================================================================= */
#ifdef EIPC_PCCC_CLIENT_USED
static int16 local_buildPcccWrite_common (EIPC_HANDLE_STRUCT *server, uint8 *buf, uint16 max_num_buf_bytes, EIPC_PCCC_STRUCT *pccc_ptr)
{
    uint8   msg[500];          /* temp buffer to avoid buffer overflow */
    uint16  msg_size, i;
    char    ascii_addr[51];

    /* build the passed part of the message */
    msg_size = 0;

    /* build the passed part of the message */
    msg[msg_size++] = 0x4B; /* Execute PCCC  */
    msg[msg_size++] = 0x02; /* Execute PCCC: path size */
    msg[msg_size++] = 0x20; /* Execute PCCC: 8-bit class */
    msg[msg_size++] = 0x67; /* Execute PCCC: PCCC Object */
    msg[msg_size++] = 0x24; /* Execute PCCC: 8-bit instance */
    msg[msg_size++] = 0x01; /* Execute PCCC: Instance 1 */
    msg[msg_size++] = 0x07; /* Execute PCCC: Req ID Length (vid + s/n + other + 1) */
    msg[msg_size++] = 0x32; /* Execute PCCC: Vendor ID (we are 50) */
    msg[msg_size++] = 0x00; /* Execute PCCC: Vendor ID (we are 50) */

    /* store the serial number */
    rta_PutLitEndian32(eipc_userobj_getSerialNumber(),msg+msg_size);
    msg_size = msg_size + 4;
    
    msg[msg_size++] = 0x0F; /* store the command  */
    msg[msg_size++] = 0x00; /* store the status */

    /* store the TNS */
    server->tns++;
    rta_PutLitEndian16(server->tns, msg+msg_size); 
    msg_size += 2;

    /* PLC */
    if(pccc_ptr->pccc_plc_type == EIPC_PCCC_PLC_TYPE_PLC5E)
    {
        /* store FNC "Typed Write" */
        msg[msg_size++] = 0x67; /* store the command      */

        /* store the Packet Offset */
        rta_PutLitEndian16(0 , msg+msg_size); 
        msg_size += 2;

        /* store the Total Trans (number of units to read) */
        rta_PutLitEndian16(pccc_ptr->pccc_num_elements, msg+msg_size); 
        msg_size += 2;

        /* store a NULL to start the string */
        msg[msg_size++] = 0x00;

        /* store the PLC-5 sys. address */
        sprintf(ascii_addr, "$%s:%d", pccc_ptr->pccc_file_string, pccc_ptr->pccc_file_offset);

        /* copy the address */
        for(i=0; i<strlen(ascii_addr); i++)
            msg[msg_size++] = ascii_addr[i];

        /* add a NULL terminator */
        msg[msg_size++] = 0x00; 
    }

    /* SLC */
    else
    {
        /* store FNC "Protected Write w/3 addr fields" */
        msg[msg_size++] = 0xAA; /* store the command   */

        /* store the byte size */
        msg[msg_size++] = (uint8)(pccc_ptr->pccc_element_size_in_bytes*pccc_ptr->pccc_num_elements); 
        
        /* store the file number */
        if(pccc_ptr->pccc_file_num > 254)
        {
            msg[msg_size++] = 0xFF; /* expand to 3 field address */
            rta_PutLitEndian16(pccc_ptr->pccc_file_num, msg+msg_size); 
            msg_size += 2;        
        }
        else
            msg[msg_size++] = (uint8)pccc_ptr->pccc_file_num; /* store the file number */

        /* store the file type (output logical by slot) */
        msg[msg_size++] = pccc_ptr->pccc_data_type;

        /* store the element number */
        if(pccc_ptr->pccc_file_offset > 254)
        {
            msg[msg_size++] = 0xFF; /* expand to 3 field address */
            rta_PutLitEndian16(pccc_ptr->pccc_file_offset, msg+msg_size); 
            msg_size += 2;        
        }
        else
            msg[msg_size++] = (uint8)pccc_ptr->pccc_file_offset; /* store the file number */

        /* store the sub-element number */
        msg[msg_size++] = 0x00; 
    }

    /* store the data */
    for(i=0; i<pccc_ptr->pccc_data_len; i++)
        msg[msg_size++] = pccc_ptr->pccc_data_ptr[i];   

    /* pad the data is size is odd */
    if((pccc_ptr->pccc_data_len % 2) == 1) 
        msg[msg_size++] = 0x00; 

    // will the message fit?
    if(msg_size > max_num_buf_bytes)
        return(EIPC_CLIENT_UCMMERR_TAGPTR);

    // store the response
    memcpy(buf, msg, msg_size);

    // return the amount of data copied
    return(msg_size);
}
#endif /* #ifdef EIPC_PCCC_CLIENT_USED */

/* ====================================================================
Function:   local_buildEm_common
Parameters: pointer to buffer to add data
            maximum number of bytes available in buffer
            pointer to explicit message structure
Returns:    number of bytes added (<0 on error)

This function adds the explicit message common portion (both connected
and unconnected).
======================================================================= */
#ifdef EIPC_EM_CLIENT_USED
static int16 local_buildEm_common (uint8 *buf, uint16 max_num_buf_bytes, EIPC_EM_STRUCT *em_ptr)
{
    uint8   msg[500];          /* temp buffer to avoid buffer overflow */
    uint16  msg_size, i;

    /* build the passed part of the message */
    msg_size = 0;
    msg[msg_size++] = em_ptr->service_code; // CPF: Service Code
    msg[msg_size++] = 0x00;                 // CPF: Path Size (filled in later)

    // store the Class id    
    if(em_ptr->class_id > 0x00FF)
    {
        msg[msg_size++] = 0x21;             // CPF: Path (16-bit Class)
        msg[msg_size++] = 0x00;             // CPF: Path (pad byte)
        rta_PutLitEndian16(em_ptr->class_id, &msg[msg_size]); // CPF: (Class)
        msg_size+=2;
    }
    else
    {
        msg[msg_size++] = 0x20;             // CPF: Path (8-bit Class)
        msg[msg_size++] = (uint8)em_ptr->class_id; // CPF: (Class)
    }

    // store the Instance id    
    if(em_ptr->inst_id > 0x00FF)
    {
        msg[msg_size++] = 0x25;             // CPF: Path (16-bit Instance)
        msg[msg_size++] = 0x00;             // CPF: Path (pad byte)
        rta_PutLitEndian16(em_ptr->inst_id, &msg[msg_size]); // CPF: (Instance)
        msg_size+=2;
    }
    else
    {
        msg[msg_size++] = 0x24;             // CPF: Path (8-bit Instance)
        msg[msg_size++] = (uint8)em_ptr->inst_id; // CPF: (Instance)
    }

    /* Attribute is used */   
    if(em_ptr->attr_used)
    {
        // store the Attribute id    
        if(em_ptr->attr_id > 0x00FF)
        {
            msg[msg_size++] = 0x31;             // CPF: Path (16-bit Attribute)
            msg[msg_size++] = 0x00;             // CPF: Path (pad byte)
            rta_PutLitEndian16(em_ptr->attr_id, &msg[msg_size]); // CPF: (Attribute)
            msg_size+=2;
        }
        else
        {
            msg[msg_size++] = 0x30;             // CPF: Path (8-bit Attribute)
            msg[msg_size++] = (uint8)em_ptr->attr_id; // CPF: (Attribute)
        }
    }

    // store the path size
    msg[1] = (uint8)((msg_size-2)/2); // size in words

    /* Store Data */
    for(i=0; i<em_ptr->data_len; i++)
        msg[msg_size++] = em_ptr->data_ptr[i];  // CPF: Data

    // will the message fit?
    if(msg_size > max_num_buf_bytes)
        return(EIPC_CLIENT_UCMMERR_TAGPTR);

    // store the response
    memcpy(buf, msg, msg_size);

    // return the amount of data copied
    return(msg_size);
}
#endif

/* ====================================================================
Function:   local_getConnectionID
Parameters: N/A
Returns:    unique connection ID

This function returns the next available connection id.
======================================================================= */
static uint32 local_getConnectionID (void)
{
    static uint8  first_time = TRUE;
    static uint32 connection_id = 0;

    // on the first time, set the base connection id 
    // this needs to be uniques on every power up
    if(first_time == TRUE)
    {
        first_time = FALSE;
        connection_id = (eipc_usersys_getIncarnationID() << 16);
    }

    // get the next connection id and return it
    connection_id++;
    return(connection_id);
}

/* ******** */
/* END FILE */
/* ******** */
