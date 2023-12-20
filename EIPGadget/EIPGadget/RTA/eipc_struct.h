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
 *     Module Name: eipc_struct.h
 *          Author: Jamin D. Wendorf (jwendorf@rtaautomation.com)
 *        Language: Ansi C
 * Compile Options: N/A
 * Compile defines: N/A
 *       Libraries: N/A
 *    Link Options: N/A
 *
 * Description.
 * ====================================================================
 * This file contains definitions for all structures.
 *
 */

#ifndef __EIPC_STRUCT_H__
#define __EIPC_STRUCT_H__

/* --------------------------------------------------------------- */
/*      STRUCTURE DEFINITIONS                                      */
/* --------------------------------------------------------------- */
/* ====================================================================
SOCKET STRUCTURES

Socket structures are used to simplify TCP/IP processing.
======================================================================= */
typedef struct
{
   uint8 sock_type;
   EIPC_USERSYS_SOCKTYPE sock_id;
}EIPC_SOCKET_STRUCT;

/* ====================================================================
   SESSION STRUCTURE (CLIENT SPECIFIC DATA)
======================================================================= */
typedef struct
{
   uint32 SessionHandle;
   EIPC_USERSYS_SOCKTYPE    sock_id;
}EIPC_SESSION_STRUCT;

/* ====================================================================
   ENCAPSULATED MESSAGE STRUCTURE (USED FOR ENCAPSULATION PROCESSING)
======================================================================= */
typedef struct
{
  /*0x00*/ uint16 Command;
  /*0x02*/ uint16 Length;
  /*0x04*/ uint32 SessionHandle;
  /*0x08*/ uint32 Status;
  /*0x0C*/ uint8  SenderContext[8];
  /*0x0D*/ uint32 Options;
  /* I need a pointer to the rest of the data, this way I don't need to
     define the pointer when I use this structure as a pointer to overlay
     over the passed buffer's memory */
  /*0x11*/ uint8  *EncapsulatedData;
}EIPC_ENCAP_MSG_STRUCT;


typedef struct
{
   uint16 TypeId;
   uint16 Length;
   uint8  Data[EIPC_CPF_MAX_ITEM_DATA_LEN];
}EIPC_CPF_ITEMSTRUCT;

typedef struct
{
   uint8  service;       /* 0 - 0x7F */
   uint8  path_size;     /* 0 - EIPC_USER_MSGRTR_PATH_WORDS */
   uint16 path[EIPC_USER_MSGRTR_PATH_WORDS];
   uint16 req_data_size; /* 0 - EIPC_USER_MSGRTR_DATA_SIZE */
   uint8  req_data[EIPC_USER_MSGRTR_DATA_SIZE];
}EIPC_USER_MSGRTR_REQ_FMT;

typedef struct
{
   uint8  gen_stat;       /* 0 = Success; 1-255 = Error        */
   uint8  ext_stat_size;  /* 0 - EIPC_USER_MSGRTR_EXTSTAT_SIZE */
   uint16 ext_stat[EIPC_USER_MSGRTR_EXTSTAT_SIZE];
   uint16 rsp_data_size;  /* 0 - EIPC_USER_MSGRTR_DATA_SIZE    */
   uint8  rsp_data[EIPC_USER_MSGRTR_DATA_SIZE];
}EIPC_USER_MSGRTR_RSP_FMT;

typedef struct
{
   EIPC_USER_MSGRTR_REQ_FMT	user_struct;
}EXPLICIT_REQUEST_STRUCT;

typedef struct
{
   uint8 service;
   uint8 reserved;
   EIPC_USER_MSGRTR_RSP_FMT	user_struct;
}EXPLICIT_RESPONSE_STRUCT;

typedef struct
{
   EIPC_ENCAP_MSG_STRUCT    *encap;      /* Pointer to encapsulated message */
   uint8                    *encap_data; /* local pointer to encap data */
   int16                    bytes_used;  /* validate enough data for items */
   uint32                   InterfaceHandle; /* should be 0 */
   uint16                   Timeout;         /* Timeout >0 in seconds */
   uint16                   ItemCount;       /* store the number of items */
   uint32                   ConnectionID;    /* Used with connected messages */
   uint16                   SequenceNumber;  /* Used with connected messages */
   EIPC_CPF_ITEMSTRUCT      Items[EIPC_CPF_MAX_ITEM_CNT]; /* store the items */
   EXPLICIT_REQUEST_STRUCT  *emreq; /* EM Request Message Pointer */
   EXPLICIT_RESPONSE_STRUCT *emrsp; /* EM Response Message Pointer */
}CPF_MESSAGE_STRUCT;

/* ====================================================================
   TIMER STRUCTURE (count down)
======================================================================= */
typedef struct
{
   uint32 current_value;
   uint32 reload_value;
   uint16 *timeout_flag_ptr;
   void   (*timeout_func_ptr) (uint16 timer_ix);
}EIPC_TIMER_DATA_STRUCT;

typedef struct
{
   uint8  state;
   uint8  owned;
   EIPC_TIMER_DATA_STRUCT timer_data;
}EIPC_TIMER_STRUCT;

/* ====================================================================
   TAG STRUCTURE (reads and writes)
======================================================================= */
#ifdef EIPC_TAG_CLIENT_USED
typedef struct
{
    // tag name and offset
    char    tag_name[EIPC_USEROBJ_TAGNAME_SIZE];
    uint8   tag_name_len;
    uint16  tag_offset;

    // number of elements
    uint16  tag_num_elements;

    // message processing
    uint8   service_code;
    uint8   gen_status;
    uint16  ext_status;
 
    uint16  tag_data_type;
    uint16  tag_data_len;
    uint16  tag_structure_handle; /* for UDT like strings */
    uint8   tag_data_ptr[EIPC_USEROBJ_TAGDATA_SIZE];    
}EIPC_TAG_STRUCT;
#endif /* #ifdef EIPC_TAG_CLIENT_USED */

#ifdef EIPC_PCCC_CLIENT_USED
/* ****************** */
/* PCCC CONFIGURATION */
/* ****************** */
#define EIPC_PCCC_PLC_TYPE_SLC505       0
#define EIPC_PCCC_PLC_TYPE_PLC5E        1

/* ====================================================================
   PCCC STRUCTURE (reads and writes)
======================================================================= */
typedef struct
{
    /* message processing */
    uint8   service_code;
    uint8   gen_status;
    uint16  ext_status;

    /* request information */
    uint8   pccc_plc_type;
    uint16  pccc_file_num;
    uint16  pccc_file_offset;
    uint8   pccc_data_type;
    char    pccc_file_string[10];
    uint16  pccc_element_size_in_bytes;
    uint16  pccc_num_elements;

    uint16  pccc_data_len;
    uint8   pccc_data_ptr[EIPC_USEROBJ_PCCCDATA_SIZE];
}EIPC_PCCC_STRUCT;
#endif /* #ifdef EIPC_PCCC_CLIENT_USED */

#ifdef EIPC_EM_CLIENT_USED
/* ====================================================================
   EXPLICIT MESSAGE STRUCTURE
======================================================================= */
typedef struct
{
    /* message processing */
    uint8   service_code;
    uint8   gen_status;
    uint16  ext_status;

    /* request information */
    uint16  class_id;
    uint16  inst_id;
    uint16  attr_id;
    uint8   attr_used;

    uint16  data_len;
    uint8   data_ptr[EIPC_USEROBJ_EMDATA_SIZE];
}EIPC_EM_STRUCT;
#endif /* #ifdef EIPC_EM_CLIENT_USED */

#endif /* __EIPC_STRUCT_H__ */
