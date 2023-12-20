/*
*  Description.
 * ====================================================================
 * This file contains user defined definitions for system operations.
 *
 */

#ifndef __EIPC_USERSYS_H__
#define __EIPC_USERSYS_H__

#define _CRT_SECURE_NO_WARNINGS

#include "..\stdafx.h"

/* include files needed for the sample application */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <sys/timeb.h>
#include <winsock2.h>
//#include <afx.h>

#define EIPC_TAG_CLIENT_USED        1   /* define to support talking to Logix processors */
//#define EIPC_PCCC_CLIENT_USED       1   /* define to support talking to SLC, MicroLogix, PLC5E */
//#define EIPC_EM_CLIENT_USED         1   /* define to support talking to devices using generic explicit messaging */
//#define EIPC_EM_CLASS3_CNXN_USED    1   /* define to support Class 3 Connected Explicit Messaging - used by all devices */

/* --------------------------------------------------------------- */
/*      TYPE DEFINITIONS                                           */
/* --------------------------------------------------------------- */
#ifndef int8
  #define int8   signed char
#endif

#ifndef uint8
  #define uint8  unsigned char
#endif

#ifndef int16
  #define int16  short
#endif

#ifndef uint16
  #define uint16 unsigned short
#endif

#ifndef int32
  #define int32  long
#endif

#ifndef uint32
  #define uint32 unsigned long
#endif

#ifndef NULLFNPTR
  #define NULLFNPTR ((void (*)()) 0)
#endif

/* --------------------------------------------------------------- */
/*      GENERIC DEFINITIONS                                        */
/* --------------------------------------------------------------- */
#ifndef SUCCESS
  #define SUCCESS 0
#endif

#ifndef FAILURE
  #define FAILURE 1
#endif

#ifndef FAIL
  #define FAIL 1
#endif

#ifndef TRUE
  #define TRUE 1
#endif

#ifndef FALSE
  #define FALSE 0
#endif

#ifndef YES
  #define YES 1
#endif

#ifndef NO
  #define NO 0
#endif

#ifndef ON
  #define ON 1
#endif

#ifndef OFF
  #define OFF 0
#endif

#ifndef NULL
  #define NULL 0x00
#endif

#ifndef NULLPTR
  #define NULLPTR (void *) NULL
#endif

/* --------------------------------------------------------------- */
/*      MACROS                                                     */
/* --------------------------------------------------------------- */
#define Xmod(v,b) (v - ((v/b)*b))
#define Xmin(a,b) ((a<b)?a:b)
#define Xmax(a,b) ((a>b)?a:b)
#define BYTESWAP(a)  ((uint16)((((unsigned int)a)>>8)&0x00FF)|((((uint16)a)<<8)&0xFF00))
#define RTA_UNUSED_PARAM(a) if(a){}

/* how many servers can we talk to? */
#define EIPC_USEROBJ_MAX_NUM_SERVER_HANDLES 3

/* (UCMM messaging) How many extended response error words do we want? */
#define EIPC_USERSYS_EXT_STAT_SIZE 4

/* (UCMM messaging) How many bytes of resposne data do we want? */
#define EIPC_USERSYS_RSP_DATA_SIZE 512

/* 0 - 4X, 1 - 8X, 2 - 16X, etc */
#define EIPC_USERSYS_CNXNTMOMULT 0

#define EIPC_GET_MUTEX
#define EIPC_PUT_MUTEX

/* we put lookup tables in code space to save RAM */
#define EIPC_CODESPACE const

/* define macros to get the high and low bytes of a word */
#define EIPC_LO(l) (uint8)(l&0x00FF)
#define EIPC_HI(h) (uint8)((h&0xFF00)>>8)

/* Define the amount of data that can sent in a single
   explicit message. */
#define EIPC_USER_MSGRTR_DATA_SIZE     512

/* Define the number of path words included in a single
   explicit message.  This should be at least 10. */
#define EIPC_USER_MSGRTR_PATH_WORDS    16

/* Define the number of extended error words included in
   a single explicit message.  This should be at least 2. */
#define EIPC_USER_MSGRTR_EXTSTAT_SIZE  16

/* Define the max size of the encapsulated message.  This should
   be at least 600, but can go up to 64K based on the needs of
   the customer.  The NOP command is the only command that is
   supported that can be larger than 600 bytes, but the stack
   handles the NOP in a special fashion to save on RAM. */
#define EIPC_USER_MAX_ENCAP_BUFFER_SIZ 512

/* Define the max number of I/O bytes that can be transmitted in
   each direction. */
#define EIPC_USER_IOBUF_SIZ 600

/* Define the max number of I/O connections supported.	This
   can be 0 to (EIPC_USER_MAX_NUM_EM_CNXNS_PER_SESSION *
   EIPC_USER_MAX_NUM_EIP_SESSIONS). */
#define EIPC_USER_MAX_NUM_IO_CNXNS 10

/* Define the max number of Encapsulation Sessions supported
   by the device.  This should be smaller than the total
   number of sockets supported. */
#define EIPC_USER_MAX_NUM_EIP_SESSIONS 10

/* Define the max number of Explicit connections
   supported by the server. */
#define EIPC_USER_MAX_NUM_EM_CNXNS_PER_SESSION 2

/* define the resolution of the ticker in in microseconds.
	    1L - one microsecond ticker
	 1000L - one millisecond ticker
	10000L - ten millisecond ticker
      1000000L - one second ticker
*/
#define EIPC_USER_TICKS_PER_1SEC    1000       // ticks per second

/* allow the user to change the timeout rates (at compile time) */
#define EIPC_USERSYS_TMORATE_CONN_TMO   EIPC_USER_TICKS_PER_1SEC*5

/* RTA depends on a timer subsystem with at least 2 timers for each
   connection.	This number should be large since the user can use the
   timers too. */
#define EIPC_USER_MAX_NUM_TIMERS    100

/* we need a semaphore to ensure we don't print too fast */
#define EIPC_DEBUG 1 /* define this to 1 to enable debug printing */
//#define EIPC_PRINTALL 1 /* define this for more debug printing */
#if EIPC_DEBUG > 0
  //#define eipc_user_dbprint0(f) printf(f)
  //#define eipc_user_dbprint1(f,a1) printf(f,a1)
  //#define eipc_user_dbprint2(f,a1,a2) printf(f,a1,a2)
  //#define eipc_user_dbprint3(f,a1,a2,a3) printf(f,a1,a2,a3)
  //#define eipc_user_dbprint4(f,a1,a2,a3,a4) printf(f,a1,a2,a3,a4)
  //#define eipc_user_dbprint5(f,a1,a2,a3,a4,a5) printf(f,a1,a2,a3,a4,a5)
  //#define eipc_user_dbprint6(f,a1,a2,a3,a4,a5,a6) printf(f,a1,a2,a3,a4,a5,a6)
  //#define eipc_user_dbprint7(f,a1,a2,a3,a4,a5,a6,a7) printf(f,a1,a2,a3,a4,a5,a6,a7)
  //#define eipc_user_dbprint8(f,a1,a2,a3,a4,a5,a6,a7,a8) printf(f,a1,a2,a3,a4,a5,a6,a7,a8)

  #define eipc_user_dbprint0(f) TRACE(f)
  #define eipc_user_dbprint1(f,a1) TRACE(f,a1)
  #define eipc_user_dbprint2(f,a1,a2) TRACE(f,a1,a2)
  #define eipc_user_dbprint3(f,a1,a2,a3) TRACE(f,a1,a2,a3)
  #define eipc_user_dbprint4(f,a1,a2,a3,a4) TRACE(f,a1,a2,a3,a4)
  #define eipc_user_dbprint5(f,a1,a2,a3,a4,a5) TRACE(f,a1,a2,a3,a4,a5)
  #define eipc_user_dbprint6(f,a1,a2,a3,a4,a5,a6) TRACE(f,a1,a2,a3,a4,a5,a6)
  #define eipc_user_dbprint7(f,a1,a2,a3,a4,a5,a6,a7) TRACE(f,a1,a2,a3,a4,a5,a6,a7)
  #define eipc_user_dbprint8(f,a1,a2,a3,a4,a5,a6,a7,a8) TRACE(f,a1,a2,a3,a4,a5,a6,a7,a8)

  //#define eipc_user_dbprint0(f)
  //#define eipc_user_dbprint1(f,a1)
  //#define eipc_user_dbprint2(f,a1,a2)
  //#define eipc_user_dbprint3(f,a1,a2,a3)
  //#define eipc_user_dbprint4(f,a1,a2,a3,a4)
  //#define eipc_user_dbprint5(f,a1,a2,a3,a4,a5)
  //#define eipc_user_dbprint6(f,a1,a2,a3,a4,a5,a6)
  //#define eipc_user_dbprint7(f,a1,a2,a3,a4,a5,a6,a7)
  //#define eipc_user_dbprint8(f,a1,a2,a3,a4,a5,a6,a7,a8)

#else
  #define eipc_user_dbprint0(f)
  #define eipc_user_dbprint1(f,a1)
  #define eipc_user_dbprint2(f,a1,a2)
  #define eipc_user_dbprint3(f,a1,a2,a3)
  #define eipc_user_dbprint4(f,a1,a2,a3,a4)
  #define eipc_user_dbprint5(f,a1,a2,a3,a4,a5)
  #define eipc_user_dbprint6(f,a1,a2,a3,a4,a5,a6)
  #define eipc_user_dbprint7(f,a1,a2,a3,a4,a5,a6,a7)
  #define eipc_user_dbprint8(f,a1,a2,a3,a4,a5,a6,a7,a8)
#endif

#endif /* __EIPC_USERSYS_H__ */
