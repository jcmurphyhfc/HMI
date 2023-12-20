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
 *     Module Name: eipc_cpf.h
 *          Author: Jamin D. Wendorf (jwendorf@rtaautomation.com)
 *        Language: Ansi C
 * Compile Options: N/A
 * Compile defines: N/A
 *       Libraries: N/A
 *    Link Options: N/A
 *
 * Description.
 * ====================================================================
 * This file contains definitions for the Common Packet Format (CPF).
 *
 */

#ifndef __EIPC_CPF_H__
#define __EIPC_CPF_H__

#define LINKOBJ_PROD		0x00
#define LINKOBJ_CONS		0x01

#define LINKOBJSTATE_NONEXIST	0x00
#define LINKOBJSTATE_RUNNING	0x01

#define CNXNST_UNCONNECTED	0x00
#define CNXNST_CONNECTED	0x01

#define EIPC_CPF_MAX_ITEM_DATA_LEN  512
#define EIPC_CPF_MAX_RSP_SIZ	    1500

#define LOGSEG_8BITCLASS	0x20
#define LOGSEG_8BITINST 	0x24
#define LOGSEG_8BITCNXNPT	0x2C
#define LOGSEG_8BITATTR 	0x30
#define LOGSEG_ELECKEY		0x34
#define ELECKEY_FORMAT		0x04

/* ---------------------------- */
/* MISCELLANEOUS / MACROS	*/
/* ---------------------------- */
/*
 * TCP sequence numbers are 32 bit integers operated
 * on with modular arithmetric.  These macros can be
 * used to compare such integers.
 */
#define SEQ32_LT(a,b)	(((int32)a - (int32)b) <  0)
#define SEQ32_LEQ(a,b)	(((int32)a - (int32)b) <= 0)
#define SEQ32_GT(a,b)	(((int32)a - (int32)b) >  0)
#define SEQ32_GEQ(a,b)	(((int32)a - (int32)b) >= 0)

#define SEQ16_LT(a,b)	(((int16)a - (int16)b) <  0)
#define SEQ16_LEQ(a,b)	(((int16)a - (int16)b) <= 0)
#define SEQ16_GT(a,b)	(((int16)a - (int16)b) >  0)
#define SEQ16_GEQ(a,b)	(((int16)a - (int16)b) >= 0)

/*
 * The bulk of the information I found was in the ControlNet
 * International Specification, Version 2.0, Errata 2,
 * Part 4 "Network and Transport Layer", Section 8
 * "TCP/IP Encapsulation".
 *
 * I Receive the C.P.F. part of the encapsulated Ethernet/IP
 * message (Part 4, Section 8.9 "Common packet format").
 *
 * (Table 4-62: Common packet format)
 *  --------------------------------------------------------------------
 * |  FIELD NAME  |	   TYPE        |	 DESCRIPTION		|
 * |--------------------------------------------------------------------|
 * | Item Count   | uint16	       | # of items to follow (>1)	|
 * |--------------------------------------------------------------------|
 * | Address Item | Struct (see below) | Address info for encap. packet |
 * |--------------------------------------------------------------------|
 * | Data Item	  | Struct (see below) | The encap. data packet 	|
 * |--------------------------------------------------------------------|
 * | Optional additional items						|
 *  --------------------------------------------------------------------
 *
 * (Table 4-63: Address and data item structure)
 *  -------------------------------------------------------------
 * |  FIELD NAME  |   TYPE   |		DESCRIPTION		 |
 * |-------------------------------------------------------------|
 * | Type ID	  | uint16   | Type of item encapsulated	 |
 * |-------------------------------------------------------------|
 * | Length	  | uint16   | Length in bytes of data to follow |
 * |-------------------------------------------------------------|
 * | Data	  | Variable | The data (if Length > 0) 	 |
 *  -------------------------------------------------------------
 */

/* ***************************************************** */
/* ADDRESS TYPE IDS (From Table 4-64: Address type ID's) */
/* ***************************************************** */
#define ADDR_TYP_ID_NULL	0x0000	/* NULL (used for UCMM messages) */
/* 0x0001 - 0x00A0 -> Allocated for compatiblity with existing protocols) */
#define ADDR_TYP_ID_CNXNBASED	0x00A1	/* Connection-based (used for connected msgs) */
/* 0x00A2 - 0x7FFF -> Allocated for compatiblity with existing protocols) */
/* 0x8000 - 0x8001 -> Area for future expansion */
#define ADDR_TYP_ID_SEQADDRTYP	0x8002	/* Sequenced Address Type */
/* 0x8003 - 0xFFFF -> Area for future expansion */

/* *********************************************** */
/* DATA TYPE IDS (From Table 4-65: Data type ID's) */
/* *********************************************** */
/* 0x0000 - 0x00B0 -> Allocated for compatiblity with existing protocols) */
#define DATA_TYP_ID_PDU 	0x00B1	/* Connected Transport PDU */
#define DATA_TYP_ID_UCMM	0x00B2	/* Unconnected Message */
/* 0x00B3 - 0x7FFF -> Allocated for compatiblity with existing protocols) */
#define DATA_TYP_ID_SOCK_OT	0x8000	/* Sockaddr Info. originator-to-target */
#define DATA_TYP_ID_SOCK_TO	0x8001	/* Sockaddr Info. target-to-originator */
/* 0x8002 - 0xFFFF -> Area for future expansion */

/* -------------CLASS DEFINITIONS--------------------------------------- */
#define EIPC_IDENTITY_CLASS_REV  1
#define EIPC_ASSEMBLY_CLASS_REV  1
#define EIPC_TCP_CLASS_REV	 1
#define EIPC_ENETLINK_CLASS_REV  1
#define EIPC_USER_NUM_ASM_INST	 2

/* -------------GENERIC OBJECT CLASSES--------------------------------- */
#define CLASS_IDENTITY			0x01
#define CLASS_MSGROUTER 		0x02
#define CLASS_ASSEMBLY			0x04
#define CLASS_CONNECTMGR		0x06
#define CLASS_TCPIP			0xF5
#define CLASS_ENETLINK			0xF6

/* -------------COMMON SERVICE CODES----------------------------------- */
#define SC_GET_ATTR_ALL        0x01
#define SC_SET_ATTR_ALL        0x02
#define SC_RESET	       0x05
#define SC_APPLY_ATTRIBS       0x0D
#define SC_GET_ATTR_SINGLE     0x0E
#define SC_SET_ATTR_SINGLE     0x10
#define SC_ERROR_RESPONSE      0x94

/* Connection Manager Services (PDU) */
#define SC_FWD_OPEN_REQ        0x54    /* Open	a connection */
#define SC_FWD_OPEN_RSP        0xD4    /* Open	a connection */
#define SC_FWD_CLOSE_REQ       0x4E    /* Close a connection */
#define SC_FWD_CLOSE_RSP       0xCE    /* Close a connection */

/* TCP Object Configuration Capabilities attribute */
#define EIPC_TCPCFG_BOOTPCLIENT_SUPPORTED    0x00000001L
#define EIPC_TCPCFG_DNSCLIENT_SUPPORTED      0x00000002L
#define EIPC_TCPCFG_DHCPCLIENT_SUPPORTED     0x00000004L
#define EIPC_TCPCFG_DHCPDNS_SUPPORTED	     0x00000008L
#define EIPC_TCPCFG_CONFIGSETTABLE_SUPPORTED 0x00000010L

/* -------------ERROR CODES-------------------------------------------- */
#define ERR_SUCCESS			0x00
#define ERR_CNXN_FAILURE		0x01
#define ERR_RESOURCE_UNAVAIL		0x02
#define ERR_PATHSEGMENT 		0x04
#define ERR_PATHDESTUNKNOWN		0x05
#define ERR_CNXNLOST			0x07
#define ERR_SERV_UNSUPP 		0x08
#define ERR_INV_ATTRIBVAL		0x09
#define ERR_IN_REQ_STATE		0x0b
#define ERR_OBJ_STATE_CONFLICT		0x0c
#define ERR_ATTR_READONLY		0x0e
#define ERR_PRIV_VIOLATION		0x0f
#define ERR_DEV_STATE_CONFLICT		0x10
#define ERR_REPLY_SIZE			0x11
#define ERR_INSUFF_DATA 		0x13
#define ERR_ATTR_UNSUPP 		0x14
#define ERR_TOOMUCH_DATA		0x15
#define ERR_UNEXISTANT_OBJ		0x16
#define ERR_NO_ATTR_DATA		0x18
#define ERR_STORE_FAILURE		0x19
#define ERR_VENDOR_SPECIFIC		0x1F
#define ERR_INV_SERVICE_PARM		0x20
#define ERR_NOADD_ERRCODE		0xFF

/* -------------VENDOR ERROR CONDITIONS-------------------------------- */
#define ERRV_UNDEF_SERV 		0x01

/* -------------LED FLASH RATE----------------------------------------- */
#define LED_FLASH_RATE	TICKS_PER_50MSEC  /* (50 * 10msec) = 500msec */

/* -------------MESSAGE CONTROL BITS----------------------------------- */
#define DNBIT_RR	  0x80
#define DNBIT_FRAG	  0x80
#define DNBIT_XID	  0x40
#define DNBIT_XPORT_DIR   0x80
#define DNBITS_FRAGCNT	  0x3F

/* -------------FRAGMENT PROCESSING------------------------------------ */
#define FRAGTYP_1ST	0
#define FRAGTYP_MID	1
#define FRAGTYP_LAST	2
#define FRAGTYP_ACK	3
#define FRAGCNT_END	0x3F

/* -------------CONNECTION STATES-------------------------------------- */
#define CXST_NONEXIST	  0x00
#define CXST_CONFIGURING  0x01
#define CXST_WAIT4CID	  0x02
#define CXST_ESTABLISHED  0x03
#define CXST_TIMEOUT	  0x04
#define CXST_DEFERDELETE  0x05

/* -------------INSTANCE TYPES----------------------------------------- */
#define INST_TYP_EM	0x00
#define INST_TYP_IO	0x01

/* -------------MESSAGE BODY FORMAT------------------------------------ */
#define BDYFMT_C8I8	0x00		/* Class = 8, Instance = 8	*/
#define BDYFMT_C8I6	0x01		/* Class = 8, Instance = 16	*/
#define BDYFMT_C6I6	0x02		/* Class = 16, Instance = 16	*/
#define BDYFMT_C6I8	0x03		/* Class = 16, Instance = 8	*/

/* -------------INIT PROD CHARS---------------------------------------- */
#define PRODGRP1	0x00
#define PRODGRP2DEST	0x01
#define PRODGRP2SRC	0x02
#define PRODGRP3	0x03
#define PRODDEFAULT	0x0F

/* -------------INIT CONS CHARS---------------------------------------- */
#define CONSGRP1	0x00
#define CONSGRP2DEST	0x01
#define CONSGRP2SRC	0x02
#define CONSGRP3	0x03
#define CONSDEFAULT	0x0F

/* -------------MAX PROD SIZE and MAX CONS SIZE------------------------ */
/*** The values for the Max Prod Size and Max Cons Size are listed in pw.h ***/

/* -------------TRANSPORT DIRECTIONS----------------------------------- */
#define XPORTDIR_CLIENT 	0x00
#define XPORTDIR_SERVER 	0x80

/* -------------TIMEOUT ACTION DEF------------------------------------- */
#define TMOACTION_TMO		0x00
#define TMOACTION_DELETE	0x01
#define TMOACTION_AUTORESET	0x02
#define TMOACTION_DEFERDELETE	0x03

/* ************************************ */
/* IDENTITY STATUS WORD BIT DEFINITIONS */
/* ************************************ */
#define IDSTATWORD_OWNED	0x0001
#define IDSTATWORD_RSVD1	0x0002
#define IDSTATWORD_CONFIGURED	0x0004
#define IDSTATWORD_RSVD2	0x0008
#define IDSTATWORD_VENDOR1	0x0010
#define IDSTATWORD_VENDOR2	0x0020
#define IDSTATWORD_VENDOR3	0x0040
#define IDSTATWORD_VENDOR4	0x0080
#define IDSTATWORD_MINRFLT	0x0100
#define IDSTATWORD_MINNRFLT	0x0200
#define IDSTATWORD_MAJRFLT	0x0400
#define IDSTATWORD_MAJNRFLT	0x0800
#define IDSTATWORD_RSVD3	0x1000
#define IDSTATWORD_RSVD4	0x2000
#define IDSTATWORD_RSVD5	0x4000
#define IDSTATWORD_RSVD6	0x8000

#endif /* __EIPC_CPF_H__ */
