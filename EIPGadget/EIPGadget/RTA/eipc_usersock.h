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
 *     Module Name: eipc_usersock.h
 *          Author: Jamin D. Wendorf (jwendorf@rtaautomation.com)
 *        Language: Ansi C
 * Compile Options: N/A
 * Compile defines: N/A
 *       Libraries: N/A
 *    Link Options: N/A
 *
 * Description.
 * ====================================================================
 * This file contains user defined Socket definitions.
 *
 */

#ifndef __EIPC_USERSOCK_H__
#define __EIPC_USERSOCK_H__

/* define what the socket type is (usually int) */
#define EIPC_USERSYS_SOCKTYPE SOCKET

//#define EIPC_USER_SOCKIX_LISTENING  0
#define EIPC_USER_MAX_NUM_SOCKETS   100
#define EIPC_USER_MAX_NUM_SOCK_ID   FD_SETSIZE
#define EIPC_USER_SOCKET_UNUSED     0

#endif /* __EIPC_USERSOCK_H__ */
