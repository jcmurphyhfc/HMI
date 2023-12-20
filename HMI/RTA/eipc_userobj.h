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
 *     Module Name: eipc_userobj.h
 *          Author: Jamin D. Wendorf (jwendorf@rtaautomation.com)
 *        Language: Ansi C
 * Compile Options: N/A
 * Compile defines: N/A
 *       Libraries: N/A
 *    Link Options: N/A
 *
 * Description.
 * ====================================================================
 * This file contains user defined Object Model definitions.
 *
 */

#ifndef __EIPC_USEROBJ_H__
#define __EIPC_USEROBJ_H__

/* *************************** */
/* Identity Object Definitions */
/* *************************** */
/* Vendor ID is "Real Time Automation" 0x0032 */
#define EIPC_USER_IDOBJ_VENDORID   0x0032
/* Device Types is "Communications Adapter" 0x0C */
#define EIPC_USER_IDOBJ_DEVTYPE    0x0000
/* Product Code is unique for each product */
#define EIPC_USER_IDOBJ_PRODCODE   0x0022
/* Product Name is 1-byte length followed by the name string */
#define EIPC_USER_IDOBJ_NAME_SIZE  27
#define EIPC_USER_IDOBJ_NAME "RTA ControlLogix Tag Client"

/* ***************** */
/* TAG CONFIGURATION */
/* ***************** */
#define EIPC_USEROBJ_TAGNAME_SIZE       150  /* in charactes */
#define EIPC_USEROBJ_TAGDATA_SIZE       256 /* in bytes */
#define EIPC_USEROBJ_MAXTAGS_PER_MSG    40  /* number of tags per read/write */
#define EIPC_USEROBJ_MINTMOVAL          100 /* minimum timeout value, should be 100 or larger */
#define EIPC_USEROBJ_RPI_CNXNTMO_MULT   0   /* connection timeout multiplier 0=4x,1=8x,2=16x,3=32x,4=64x,5=128x,6=256x,7=512x*/
#define EIPC_USEROBJ_PCCCDATA_SIZE      256 /* in bytes */
#define EIPC_USEROBJ_EMDATA_SIZE        256 /* in bytes */
#define EIPC_USEROBJ_TAGARRAY_SIZE      80  /* in bytes */

#endif /* __EIPC_USEROBJ_H__ */
