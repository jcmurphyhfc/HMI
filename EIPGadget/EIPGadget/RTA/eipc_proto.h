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
 *     Module Name: eipc_proto.h
 *          Author: Jamin D. Wendorf (jwendorf@rtaautomation.com)
 *        Language: Ansi C
 * Compile Options: N/A
 * Compile defines: N/A
 *       Libraries: N/A
 *    Link Options: N/A
 *
 * Description.
 * ====================================================================
 * This file contains definitions for all function prototypes.
 *
 */

#ifndef __EIPC_PROTO_H__
#define __EIPC_PROTO_H__

/* ************************************ */
/* Global Functions in eipc_tagclient.c */
/* ************************************ */
/* rta called functions */
void   eipc_tagclient_init      (uint8 init_type);
void   eipc_tagclient_process   (void);
void   eipc_tagclient_onConnect (EIPC_USERSYS_SOCKTYPE socket_id);
void   eipc_tagclient_onClose   (EIPC_USERSYS_SOCKTYPE socket_id);
uint16 eipc_tagclient_onTCPData (EIPC_USERSYS_SOCKTYPE socket_id, uint8 * socket_data, uint16 socket_data_size);

/* user called functions */
int16   eipc_tagclient_connectToPLC      (uint32 ip_addr); // return the server_handle
int16   eipc_tagclient_disconnectFromPLC (int16 server_handle);

#ifdef EIPC_TAG_CLIENT_USED
    #ifdef EIPC_EM_CLASS3_CNXN_USED
        int16   eipc_tagclient_sendTagRead_connected  (int16 server_handle, uint8 tag_cnt, EIPC_TAG_STRUCT *tags);
        int16   eipc_tagclient_sendTagWrite_connected (int16 server_handle, uint8 tag_cnt, EIPC_TAG_STRUCT *tags);
    #endif

    int16   eipc_tagclient_sendTagRead_unconnected (int16 server_handle, uint32 tmo_in_ticks, uint8 plc_slot, uint8 tag_cnt, EIPC_TAG_STRUCT *tags);
    int16   eipc_tagclient_sendTagWrite_unconnected (int16 server_handle, uint32 tmo_in_ticks, uint8 plc_slot, uint8 tag_cnt, EIPC_TAG_STRUCT *tags);

    #define eipc_tagclient_sendTagRead   eipc_tagclient_sendTagRead_unconnected  /* for backward compatibility */
    #define eipc_tagclient_sendTagWrite  eipc_tagclient_sendTagWrite_unconnected /* for backward compatibility */
#endif

#ifdef EIPC_PCCC_CLIENT_USED
    #ifdef EIPC_EM_CLASS3_CNXN_USED
        int16 eipc_tagclient_sendPcccRead_connected  (uint16 server_handle, EIPC_PCCC_STRUCT *pccc_ptr);
        int16 eipc_tagclient_sendPcccWrite_connected (uint16 server_handle, EIPC_PCCC_STRUCT *pccc_ptr);
    #endif

    int16 eipc_tagclient_sendPcccRead_unconnected  (uint16 server_handle, uint32 tmo_in_ticks, EIPC_PCCC_STRUCT *pccc_ptr);
    int16 eipc_tagclient_sendPcccWrite_unconnected (uint16 server_handle, uint32 tmo_in_ticks, EIPC_PCCC_STRUCT *pccc_ptr);

    #define eipc_tagclient_sendPcccRead  eipc_tagclient_sendPcccRead_unconnected  /* for backward compatibility */
    #define eipc_tagclient_sendPcccWrite eipc_tagclient_sendPcccWrite_unconnected /* for backward compatibility */
#endif

#ifdef EIPC_EM_CLIENT_USED
    #ifdef EIPC_EM_CLASS3_CNXN_USED
        int16 eipc_tagclient_sendExplicitMsg_connected (uint16 server_handle, EIPC_EM_STRUCT *em_ptr);
    #endif
    int16 eipc_tagclient_sendExplicitMsg_unconnected (uint16 server_handle, uint32 tmo_in_ticks, EIPC_EM_STRUCT *em_ptr);
#endif

#ifdef EIPC_EM_CLASS3_CNXN_USED
    int16 eipc_tagclient_openEmCnxn  (uint16 server_handle, uint16 rpi_in_ms, uint8 *port_id);
    int16 eipc_tagclient_closeEmCnxn (uint16 server_handle);
#endif

/* ******************************** */
/* Global Functions in eipc_encap.c */
/* ******************************** */
void   eipc_encap_init (uint8 init_type);
uint16 eipc_encap_process (EIPC_SOCKET_STRUCT *sock, uint8 *msg, uint16 msg_siz);
void   eipc_encap_freeSessionIx (EIPC_USERSYS_SOCKTYPE socket_id);
void   eipc_encap_unSupEncapMsg (EIPC_ENCAP_MSG_STRUCT *EncapReq, EIPC_SOCKET_STRUCT *sock);
EIPC_SESSION_STRUCT * eipc_encap_getSessionStruct (uint32 sessionID);

/* ********************************* */
/* Global Functions in eipc_rtasys.c */
/* ********************************* */
void eipc_rtasys_init         (uint8 init_type);
void eipc_rtasys_process      (uint32 time_passed_in_ticks);
void eipc_rtasys_onTCPAccept  (EIPC_USERSYS_SOCKTYPE socket_id);
void eipc_rtasys_onTCPData    (EIPC_USERSYS_SOCKTYPE socket_id, uint8 * socket_data, uint16 socket_data_size);
void eipc_rtasys_onUDPData    (EIPC_USERSYS_SOCKTYPE socket_id, uint8 * socket_data, uint16 socket_data_size);
void eipc_rtasys_onTCPSent    (EIPC_USERSYS_SOCKTYPE socket_id);
void eipc_rtasys_onTCPClose   (EIPC_USERSYS_SOCKTYPE socket_id);
void eipc_rtasys_onTCPConnect (EIPC_USERSYS_SOCKTYPE socket_id);

/* ******************************** */
/* Global Functions in eipc_timer.c */
/* ******************************** */
void   eipc_timer_init      (uint8 init_type);
void   eipc_timer_process   (uint32 time_passed_in_ticks);
uint16 eipc_timer_new       (void);
void   eipc_timer_free      (uint16 timer_num);
void   eipc_timer_reset     (uint16 timer_num);
void   eipc_timer_start     (uint16 timer_num);
void   eipc_timer_stop      (uint16 timer_num);
void   eipc_timer_newval    (uint16 timer_num, uint32 newval);
EIPC_TIMER_DATA_STRUCT *    eipc_timer_get_struct (uint16 timer_num);

/* ********************************** */
/* Global Functions in eipc_userobj.c */
/* ********************************** */
void    eipc_userobj_init               (uint8 init_type);
void    eipc_userobj_process            (void);
uint32  eipc_userobj_getSerialNumber    (void);

#ifdef EIPC_TAG_CLIENT_USED
    void eipc_userobj_procTagAccessResp  (int16 server_handle, uint8 status, uint16 tag_cnt, EIPC_TAG_STRUCT *tags);
#endif

#ifdef EIPC_PCCC_CLIENT_USED
    void eipc_userobj_procPcccResp (uint16 server_handle, uint8 status, int8 rta_status, uint16 rsp_size, uint8 *rsp_data);
#endif

#ifdef EIPC_EM_CLIENT_USED
    void eipc_userobj_procEmResp (uint16 server_handle, EIPC_USER_MSGRTR_RSP_FMT * em_rsp);
#endif

/* *********************************** */
/* Global Functions in eipc_usersock.c */
/* *********************************** */
void   eipc_usersock_init          (uint8 init_type);
void   eipc_usersock_process       (void);
int16  eipc_usersock_sendData      (EIPC_USERSYS_SOCKTYPE socket_id, uint8 * socket_data, uint16 socket_data_size);
void   eipc_usersock_tcpClose      (EIPC_USERSYS_SOCKTYPE socket_id);
uint32 eipc_usersock_getOurIPAddr  (void);
uint8  eipc_usersock_getOurMacAddr (uint8 *madid_6byte_string);
EIPC_USERSYS_SOCKTYPE eipc_usersock_connect (uint32 ipaddr);

/* ********************************** */
/* Global Functions in eipc_usersys.c */
/* ********************************** */
void   eipc_usersys_init       (uint8 init_type);
void   eipc_usersys_process    (void);
void   eipc_usersys_fatalError (char *function_name, int16 error_num);
uint16 eipc_usersys_getIncarnationID (void);
void   eipc_usersys_UCMMStateChanged (uint16 server_handle, uint8 ucmm_server_state);

#ifdef EIPC_EM_CLASS3_CNXN_USED
    void   eipc_usersys_EmCnxnStateChanged (uint16 server_handle, uint8 em_cnxn_state);
#endif

#endif /* __EIPC_PROTO_H__ */
