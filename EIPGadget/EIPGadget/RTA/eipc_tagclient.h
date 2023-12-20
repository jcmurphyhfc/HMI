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
 *     Module Name: eipc_tagclient.h
 *          Author: Jamin D. Wendorf (jwendorf@rtaautomation.com)
 *        Language: Ansi C
 * Compile Options: N/A
 * Compile defines: N/A
 *       Libraries: N/A
 *    Link Options: N/A
 *
 * Description.
 * ====================================================================
 * This file contains definitions for the Tag Client.
 *
 */

#ifndef __EIPC_TAGCLIENT_H__
#define __EIPC_TAGCLIENT_H__

// all user defines for the client code are in this file
#include "eipc_usersys.h"

/* *************** */
/*     DEFINES     */
/* *************** */

/* UCMM Server States */
#define EIPC_CLIENT_UCMMSERVERSTATE_NONEXIST  0x00  /* no session in use */
#define EIPC_CLIENT_UCMMSERVERSTATE_REGSES    0x01  /* register session sent */
#define EIPC_CLIENT_UCMMSERVERSTATE_READY     0x02  /* idle wire... ready to send message */
#define EIPC_CLIENT_UCMMSERVERSTATE_BUSY      0x03  /* message in progress */

#ifdef EIPC_EM_CLASS3_CNXN_USED
    /* Class 3 Connection States */
    #define EIPC_CLIENT_EMCLASS3CNXNSTATE_NONEXIST  0x00    /* connection isn't used */
    #define EIPC_CLIENT_EMCLASS3CNXNSTATE_ALLOC     0x01    /* forward open sent */
    #define EIPC_CLIENT_EMCLASS3CNXNSTATE_READY     0x02    /* ready to send message */
    #define EIPC_CLIENT_EMCLASS3CNXNSTATE_BUSY      0x03    /* message in progress */
    #define EIPC_CLIENT_EMCLASS3CNXNSTATE_NEED2SEND 0x04    /* need to send a packet to avoid timeout */
#endif

/* UCMM Error Codes - General */
#define EIPC_CLIENT_UCMMERR_SUCCESS         0
#define EIPC_CLIENT_UCMMERR_SERVHAND        -1
#define EIPC_CLIENT_UCMMERR_BUSY            -2
#define EIPC_CLIENT_UCMMERR_TAGCNT          -3
#define EIPC_CLIENT_UCMMERR_TAGPTR          -4
#define EIPC_CLIENT_UCMMERR_TAGFMT          -5
#define EIPC_CLIENT_UCMMERR_TMOINVALID      -6
#define EIPC_CLIENT_UCMMERR_PLCTYPEINVALID  -7
#define EIPC_CLIENT_UCMMERR_CNXN_IN_USE     -8

/* ************************* */
/* CONTROL LOGIX DEFINITIONS */
/* ************************* */
#define CL_DATATYPE_BOOL        0x00C1
#define CL_DATATYPE_SINT        0x00C2
#define CL_DATATYPE_INT         0x00C3
#define CL_DATATYPE_DINT        0x00C4
#define CL_DATATYPE_REAL        0x00CA
#define CL_DATATYPE_BITARRAY    0x00D3
#define CL_DATATYPE_STRUCTURE   0x02A0
#define CL_STRUCTHANDLE_STRING  0x0FCE

#define CL_RSPCODE_READ     0xCC
#define CL_RSPCODE_WRITE    0xCD

/* **************** */
/* PCCC DEFINITIONS */
/* **************** */
#define PCCC_DATATYPE_INT   0x89
#define PCCC_DATATYPE_REAL  0x8A

/* ****************** */
/*     STRUCTURES     */
/* ****************** */

/* structure definitions */
typedef struct
{
    /* general variables needed for all clients */
    int16  ServerHandle; // internal reference for the server (1-65535 valid)
    uint16 TimerNum;     // used for connecting, ucmm and retry delay timeouts
    uint32 IPAddr;       // IP Address of the server (Big-endian)
    uint32 SessionID;    // 32-bit session handle returned by the server
    uint8  UCMMState;    // UCMM State (Non-exist, Ready or Busy)
    EIPC_USERSYS_SOCKTYPE SockID; // main socket for TCP traffic

#ifdef EIPC_TAG_CLIENT_USED
    /* store the last tag request so processing the response is easier */
    uint16   tag_cnt;
    EIPC_TAG_STRUCT tag_ptr[EIPC_USEROBJ_MAXTAGS_PER_MSG];
#endif

#ifdef EIPC_PCCC_CLIENT_USED
    /* store the last TNS for PCCC */
    uint16 tns;
#endif

    /* store the last encapsulation command sent */
    uint16 LastEncapCmd;

#ifdef EIPC_EM_CLASS3_CNXN_USED
    /* explicit connection handling */
    uint8  EM_CnxnState;
    uint16 EM_CnxnTmoCnt;
    uint16 EM_TimerNum;

    uint32 EM_O2T_CnxnID;
    uint16 EM_O2T_SeqNum;

    uint32 EM_T2O_CnxnID;
    uint16 EM_T2O_SeqNum;
#endif
}EIPC_HANDLE_STRUCT;

#endif /* __EIPC_TAGCLIENT_H__ */
