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
 *     Module Name: eipc_system.h
 *          Author: Jamin D. Wendorf (jwendorf@rtaautomation.com)
 *        Language: Ansi C
 * Compile Options: N/A
 * Compile defines: N/A
 *       Libraries: N/A
 *    Link Options: N/A
 *
 * Description.
 * ====================================================================
 * This file contains definitions for a general EtherNet/IP system.
 *
 */

#ifndef __EIPC_SYSTEM_H__
#define __EIPC_SYSTEM_H__

#define EIPC_UDP_BIDIR	0
#define EIPC_UDP_RXONLY 1
#define EIPC_UDP_TXONLY 2

#define EIP_CIP_PORT	0xAF12
#define EIPC_UDPIO_PORT 2222

/* NOTE: There are only 5 service codes available to the user, the rest are
   handled by the standard code.  If Set_Attribute_Single is supported, then
   Get_Attribute_Single MUST be supported.  The same is NOT true with
   Set_Attribute_All and Get_Attribute_All. Each entry in the table can only
   have one mask value.  This makes processing easier. */
#define EIPC_SCMASK_GETALL 0x01
#define EIPC_SCMASK_SETALL 0x02
#define EIPC_SCMASK_GETSNG 0x04
#define EIPC_SCMASK_SETSNG 0x08
#define EIPC_SCMASK_RESET  0x10

/* DeviceNet Data Type */
#define EIPC_TYPE_UINT8  0
#define EIPC_TYPE_UINT16 1
#define EIPC_TYPE_UINT32 2
#define EIPC_TYPE_INT8	 3
#define EIPC_TYPE_INT16  4
#define EIPC_TYPE_INT32  5
#define EIPC_TYPE_FLOAT  6
#define EIPC_TYPE_UNUSED 7

#define EIPC_CPF_ADDR_ITEM     0
#define EIPC_CPF_DATA_ITEM     1
#define EIPC_CPF_OPT_ITEM      2 /* CIP doesn't use these (always 2) */
#define EIPC_CPF_SOCKO2T_ITEM  2
#define EIPC_CPF_SOCKT2O_ITEM  3
#define EIPC_CPF_MAX_ITEM_CNT  4

/* List Services Capability Flags (Encap 0x0004)
   ---------------------------------------------
   bits 0 - 4  : reserved
   bit 5       : 1 = CIP over TCP supported, else 0
   bits 6 - 7  : reserved
   bit 8       : 1 = Supports CIP Class 0/1 UDP (I/O)
   bits 9 - 15 : reserved
*/
#define EIP_LIST_SERVICES_CAP_FLAGS 0x0120

#define SOCKTYPE_TCP 0
#define SOCKTYPE_UDP 1

#define EIP_SESSION_STATE_UNUSED 0
#define EIP_SESSION_STATE_USED	 1

/*
   -------------------------------------------------------------------
   NORMAL INITIALIZATION (0)
   -------------------------------------------------------------------
   Emulate as closely as possible cycling power on the item the Object
   represents. This value is the default if this parameter is omitted.

   -------------------------------------------------------------------
   OUT OF BOX INITIALIZATION (1)
   -------------------------------------------------------------------
   Return as closely as possible to the out�of�box configuration, then
   emulate cycling power as closely as possible.
*/
#define EIPC_INIT_NORMAL   0x00
#define EIPC_INIT_OUTOFBOX 0x01

/* Valid EIP Server States */
#define EIPC_STATE_RESETNORMAL	  EIPC_INIT_NORMAL
#define EIPC_STATE_RESETOUTOFBOX  EIPC_INIT_OUTOFBOX
#define EIPC_STATE_RUNNING	  2

#define EIPC_TIMER_NULL   0xFFFF

/* --------------------------------------------------------------- */
/*	EIPS STANDARD INCLUDE FILES				   */
/* --------------------------------------------------------------- */
#include "eipc_usersys.h"
#include "eipc_userobj.h"
#include "eipc_usersock.h"

#include "eipc_cpf.h"
#include "eipc_encap.h"
#include "eipc_struct.h"
#include "eipc_proto.h"
#include "eipc_revision.h"
#include "eipc_tagclient.h"

#include "rta_proto.h"

#endif /* __EIPC_SYSTEM_H__ */
