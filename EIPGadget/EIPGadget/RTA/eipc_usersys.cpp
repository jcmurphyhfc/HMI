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
 *     Module Name: eipc_usersys.c
 *          Author: Jamin D. Wendorf (jwendorf@rtaautomation.com)
 *        Language: Ansi C
 * Compile Options: N/A
 * Compile defines: N/A
 *       Libraries: N/A
 *    Link Options: N/A
 *
 * Description.
 * ====================================================================
 * This file contains the user system functions. All functions in this
 * file are the responsibility of the user to write.
 *
 */

/* ---------------------------- */
/* INCLUDE FILES                */
/* ---------------------------- */
#include "eipc_system.h"

/* ---------------------------- */
/* FUNCTION PROTOTYPES          */
/* ---------------------------- */

/* ---------------------------- */
/* STATIC VARIABLES             */
/* ---------------------------- */

/* ---------------------------- */
/* EXTERN VARIABLES             */
/* ---------------------------- */

/* ---------------------------- */
/* MISCELLANEOUS                */
/* ---------------------------- */

/**/
/* ******************************************************************** */
/*               GLOBAL FUNCTIONS                                       */
/* ******************************************************************** */
/* ====================================================================
Function:    eipc_userobj_init
Parameters:  init type
Returns:     N/A

This function initializes all static variables used in this file.
======================================================================= */
void eipc_usersys_init (uint8 init_type)
{
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
}

/* ====================================================================
Function:    eipc_userobj_init
Parameters:  init type
Returns:     N/A

This function initializes all static variables used in this file.
======================================================================= */
void eipc_usersys_process (void)
{
    /* NOTHING TO DO */
}

/* ====================================================================
Function:    eipc_userobj_init
Parameters:  init type
Returns:     N/A

This function initializes all static variables used in this file.
======================================================================= */
void eipc_usersys_fatalError (char *function_name, int16 error_num)
{
    eipc_user_dbprint2("FATAL ERROR - %s (%d)\r\n", function_name, error_num);
    exit(1);
}

/* ====================================================================
Function:   eipc_usersys_getIncarnationID
Parameters: N/A
Returns:    16-bit number

This function generates the Incarnation ID.
======================================================================= */
uint16 eipc_usersys_getIncarnationID (void)
{
    return((uint16)rand());
}

/* ====================================================================
Function:     eipc_usersys_UCMMStateChanged
Parameters:   Server Handle
              New UCMM State
Returns:      N/A

This function is called when the UCMM state transitions for the passed
server handle.  The default state for the UCMM connection is 
EIPC_CLIENT_UCMMSERVERSTATE_NONEXIST so this function won't be called
until the TCP connection properly allocated and an encapsulated session
is registered.  If the server refuses the TCP connection or the 
RegisterSession command, this function is called with 
EIPC_CLIENT_UCMMSERVERSTATE_NONEXIST to inform the user that there is a 
problem with the server.

Once the state transitions to EIPC_CLIENT_UCMMSERVERSTATE_READY, an
UCMM message can be sent to the user.  Immediately upon sending a UCMM
message to the server, the state transitions to 
EIPC_CLIENT_UCMMSERVERSTATE_BUSY until the message times out or is 
responded to.  There is a pointer to a call back function passed with 
the UCMM request that is called on sucessful responses, error responses
and timeouts with the message.
======================================================================= */
void eipc_usersys_UCMMStateChanged (uint16 server_handle, uint8 ucmm_server_state)
{  
#ifdef EIPC_EM_CLASS3_CNXN_USED
    uint8 port;
#endif

    switch(ucmm_server_state)
    {
        case EIPC_CLIENT_UCMMSERVERSTATE_NONEXIST:
            eipc_user_dbprint2("eipc_usersys_UCMMStateChanged (%d, %d) = NONEXIST\r\n",server_handle, ucmm_server_state);
            break;
        case EIPC_CLIENT_UCMMSERVERSTATE_REGSES:
//            eipc_user_dbprint1("eipc_usersys_UCMMStateChanged (%d) = REGSES\r\n",server_handle);
            break;
        case EIPC_CLIENT_UCMMSERVERSTATE_READY:
//            eipc_user_dbprint1("eipc_usersys_UCMMStateChanged (%d) = READY\r\n",server_handle);
#ifdef EIPC_EM_CLASS3_CNXN_USED
              port = 0;
              eipc_tagclient_openEmCnxn (server_handle, EIPC_USEROBJ_MINTMOVAL*5, &port);
#endif
           break;
        case EIPC_CLIENT_UCMMSERVERSTATE_BUSY:
//            eipc_user_dbprint1("eipc_usersys_UCMMStateChanged (%d) = BUSY\r\n",server_handle);
            break;
        default:
            eipc_user_dbprint2("eipc_usersys_UCMMStateChanged (%d) = UNKNOWN(%d)\r\n",server_handle,ucmm_server_state);
            break;
    };
}

/* ====================================================================
Function:   eipc_usersys_EmCnxnStateChanged
Parameters: server handle
            new connected connection state
Returns:    N/A

This function is called when the connected explicit connection 
transitions.
======================================================================= */
#ifdef EIPC_EM_CLASS3_CNXN_USED
void eipc_usersys_EmCnxnStateChanged (uint16 server_handle, uint8 em_cnxn_state)
{
    RTA_UNUSED_PARAM(server_handle);

    switch(em_cnxn_state)
    {
        case EIPC_CLIENT_EMCLASS3CNXNSTATE_NONEXIST:
            //eipc_user_dbprint1("eipc_usersys_EmCnxnStateChanged (%d) = NONEXIST\r\n",server_handle);
            break;

        case EIPC_CLIENT_EMCLASS3CNXNSTATE_ALLOC:
            //eipc_user_dbprint1("eipc_usersys_EmCnxnStateChanged (%d) = ALLOC\r\n",server_handle);
            break;

        case EIPC_CLIENT_EMCLASS3CNXNSTATE_READY:
            //eipc_user_dbprint1("eipc_usersys_EmCnxnStateChanged (%d) = READY\r\n",server_handle);
            break;

        case EIPC_CLIENT_EMCLASS3CNXNSTATE_BUSY:
            //eipc_user_dbprint1("eipc_usersys_EmCnxnStateChanged (%d) = BUSY\r\n",server_handle);
            break;

        case EIPC_CLIENT_EMCLASS3CNXNSTATE_NEED2SEND:
            //eipc_user_dbprint1("eipc_usersys_EmCnxnStateChanged (%d) = NEED2SEND\r\n",server_handle);
            break;

        default:
            eipc_user_dbprint2("eipc_usersys_EmCnxnStateChanged (%d) = UNKNOWN(%d)\r\n",server_handle,em_cnxn_state);
            break;
    };
}
#endif

/**/
/* ******************************************************************** */
/*                LOCAL FUNCTIONS                                       */
/* ******************************************************************** */

/* *********** */
/* END OF FILE */
/* *********** */
