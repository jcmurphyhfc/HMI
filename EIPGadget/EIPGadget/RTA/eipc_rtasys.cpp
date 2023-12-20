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
 *     Module Name: eipc_rtasys.c
 *          Author: Jamin D. Wendorf (jwendorf@rtaautomation.com)
 *        Language: Ansi C
 * Compile Options: N/A
 * Compile defines: N/A
 *       Libraries: N/A
 *    Link Options: N/A
 *
 * Description.
 * ====================================================================
 * This file contains the functions the user calls to interface to RTA.
 *
 */

/* ---------------------------- */
/* INCLUDE FILES                */
/* ---------------------------- */

/* Application definitions */
#include "eipc_system.h"

/* ---------------------------- */
/* FUNCTION PROTOTYPES          */
/* ---------------------------- */
static uint8 local_getState  (EIPC_USERSYS_SOCKTYPE socket_id);
static void  local_initAll   (uint8 initType);
static void  local_nvramTest (uint8 initType);
static void  local_closeAllSockets (void);
static int16 local_findSocketIx (EIPC_USERSYS_SOCKTYPE socket_id);
static void  local_freeSocketIx (EIPC_USERSYS_SOCKTYPE socket_id);
static int16 local_findFreeSocketIx (void);

/* ---------------------------- */
/* STATIC VARIABLES             */
/* ---------------------------- */
static struct
{
   uint8  buf[EIPC_USER_MAX_ENCAP_BUFFER_SIZ];
   uint16 buf_size;
   EIPC_USERSYS_SOCKTYPE socket_id;
   uint8  state;
   uint8  client_owned;
}struct_data[EIPC_USER_MAX_NUM_SOCKETS];

static uint8 local_state;

/* ---------------------------- */
/* MISCELLANEOUS                */
/* ---------------------------- */

/**/
/* ******************************************************************** */
/*               GLOBAL FUNCTIONS                                       */
/* ******************************************************************** */
/* ====================================================================
Function:   eipc_rtasys_init
Parameters: N/A
Returns:    N/A

This function tests the NVRAM and initializes all variables for the
EtherNet/IP Server stack.
======================================================================= */
void eipc_rtasys_init (uint8 init_type)
{
    /* test the NVRAM */
    local_nvramTest (init_type);

    /* call all init code */
    local_initAll (init_type);
    local_state = EIPC_STATE_RUNNING;
}

/* ====================================================================
Function:   eipc_rtasys_process
Parameters: N/A
Returns:    N/A

This function processes the states of the different sockets.  For now
we only have one state.
======================================================================= */
void eipc_rtasys_process (uint32 time_passed_in_ticks)
{
    switch(local_state)
    {
        /* if the new state is valid, change the state */
        case EIPC_STATE_RESETNORMAL:
        case EIPC_STATE_RESETOUTOFBOX:
            /* close all sockets */
            local_closeAllSockets ();

            /* delay for 15 seconds */
            eipc_user_dbprint0("Reset - All sockets closed\r\n");	  
            local_state = EIPC_STATE_RUNNING; 
            break;

        case EIPC_STATE_RUNNING:
            /* call client process if we are using the client code */
            eipc_tagclient_process();  // DO NOTHING

            /* process the timer */
            eipc_timer_process (time_passed_in_ticks);

            /* process the user code */
            eipc_usersock_process();
            eipc_userobj_process();   // DO NOTHING
            eipc_usersys_process();   // DO NOTHING
            break;
    };
}

/* ====================================================================
Function:   eipc_rtasys_setState
Parameters: socket_id
            new state
Returns:    N/A

This function is called to change the state of the EIP Server.  The
socket_id that wants the state changed is passed to allow a send to
complete prior to causing a reset.
======================================================================= */
void eipc_rtasys_setState (EIPC_USERSYS_SOCKTYPE socket_id, uint8 new_state)
{
    int16 i;

    /* we only use one state for now */
    if( (new_state == EIPC_STATE_RESETNORMAL) ||
        (new_state == EIPC_STATE_RESETOUTOFBOX) ||
        (new_state == EIPC_STATE_RUNNING))
    {
        local_state = new_state;
    }
	 
    /* make sure we have the socket */
    i = local_findSocketIx(socket_id);
    if(i == -1)
        return;

    switch (new_state)
    {
        /* if the new state is valid, change the state */
        case EIPC_STATE_RESETNORMAL:
        case EIPC_STATE_RESETOUTOFBOX:
        case EIPC_STATE_RUNNING:
            struct_data[i].state = new_state;
            break;

        /* if the passed state isn't valid, don't do anything */
        default:
            break;
    };
}

/* ====================================================================
Function:     eipc_rtasys_onTCPAccept
Parameters:   socket_id
Returns:      N/A

This function is called when the listening socket accepts a new
connection.  We need to set up a session structure to match the new
socket so we can receive data from the socket.
======================================================================= */
void eipc_rtasys_onTCPAccept (EIPC_USERSYS_SOCKTYPE socket_id)
{
   int16 i;

   eipc_user_dbprint1("TCP New Connection [Socket %d]\r\n",socket_id);

   /* see if we can accept the new connection */
   i = local_findFreeSocketIx ();

   /* we can't receive the socket, close it */
   if(i == -1)
      eipc_usersock_tcpClose(socket_id);

   /* set up a structure to store messages from the socket */
   else
   {
      struct_data[i].socket_id = socket_id;
      struct_data[i].state = EIPC_STATE_RUNNING;
      struct_data[i].buf_size = 0;
      memset(struct_data[i].buf, 0, sizeof(struct_data[i].buf));
   }
}

/* ====================================================================
Function:     eipc_rtasys_onTCPData
Parameters:   socket_id
              pointer to the data
              size of the data
Returns:      N/A

This function is called when TCP data is received.  This function 
forwards the data to the Encapsulation layer processing.
======================================================================= */
void eipc_rtasys_onTCPData (EIPC_USERSYS_SOCKTYPE socket_id, uint8 * socket_data, uint16 socket_data_size)
{
   EIPC_SOCKET_STRUCT sock;
   int16 i;

   /* see if we have this socket */
   i = local_findSocketIx (socket_id);
   if(i == -1)
   {
      eipc_user_dbprint1("ON TCP Data Error [Socket %d]\r\n",socket_id);
      return;
   }

   #ifdef EIPC_PRINTALL
      eipc_user_dbprint2("TCP Data Received %d bytes [Socket %d]\r\n",socket_data_size,socket_id);
   #endif

   /* add the message to the data buffer */
   memcpy(struct_data[i].buf+struct_data[i].buf_size, socket_data, socket_data_size);
   struct_data[i].buf_size += socket_data_size;

   if(struct_data[i].client_owned == TRUE)
   {
      struct_data[i].buf_size = eipc_tagclient_onTCPData (socket_id, struct_data[i].buf, struct_data[i].buf_size);
   }

   else
   {
      /* process the message */
      sock.sock_id = socket_id;
      sock.sock_type = SOCKTYPE_TCP;
      struct_data[i].buf_size = eipc_encap_process (&sock, struct_data[i].buf, struct_data[i].buf_size);
   }
}

/* ====================================================================
Function:     eipc_rtasys_onUDPData
Parameters:   socket_id
              pointer to the data
              size of the data
Returns:      N/A

This function is called when UDP data is received.  This function
forwards the data to the Encapsulation layer processing.
======================================================================= */
void eipc_rtasys_onUDPData (EIPC_USERSYS_SOCKTYPE socket_id, uint8 * socket_data, uint16 socket_data_size)
{
   EIPC_SOCKET_STRUCT sock;

   #ifdef EIPC_PRINTALL
      eipc_user_dbprint2("UDP Data Received %d bytes [Socket %d]\r\n",socket_data_size,socket_id);
   #endif

   /* process the message */
   sock.sock_id = socket_id;
   sock.sock_type = SOCKTYPE_UDP;
   eipc_encap_process (&sock, socket_data, socket_data_size);
}

/* ====================================================================
Function:     eipc_rtasys_onTCPSent
Parameters:   socket_id
Returns:      N/A

This function is called once data is successfully sent.  If the state
for the passed socket isn't running, cause the appropriate reset.
======================================================================= */
void eipc_rtasys_onTCPSent  (EIPC_USERSYS_SOCKTYPE socket_id)
{
   uint8 state;

   #ifdef EIPC_PRINTALL
      eipc_user_dbprint1("TCP Send Complete [Socket %d]\r\n",socket_id);
   #endif

   /* get the state for the passed socket_id */
   state = local_getState(socket_id);

   /* if we are running, do nothing */
   if(state == EIPC_STATE_RUNNING)
   {
      return;
   }

   /* we need to reset */
   if((state == EIPC_STATE_RESETOUTOFBOX) ||
      (state == EIPC_INIT_NORMAL))
   {
      /* Close all sockets */
      local_closeAllSockets ();

      /* after we call the init routine, set the state to running */
      eipc_rtasys_setState(socket_id, EIPC_STATE_RUNNING);
   }
}

/* ====================================================================
Function:     eipc_rtasys_onTCPClose
Parameters:   socket_id
Returns:      N/A

This function is called when a socket is closed.  Free all resources
associated with the socket id.
======================================================================= */
void eipc_rtasys_onTCPClose (EIPC_USERSYS_SOCKTYPE socket_id)
{
    int i;
//   eipc_user_dbprint1("TCP Closed [Socket %d]\r\n",socket_id);

    /* make sure we have the socket */
    i = local_findSocketIx(socket_id);
    if(i == -1)
        return;

    /* client connection */
    if(struct_data[i].client_owned == TRUE)
    {
        /* inform the client of the close */
        eipc_tagclient_onClose(socket_id);
    }

    /* server connection */
    else
    {
        /* Free the session info */
        eipc_encap_freeSessionIx(socket_id);
    }

    /* free the local socket structure */
    local_freeSocketIx (socket_id);
}

/* ====================================================================
Function:     eipc_rtasys_onTCPConnect
Parameters:   socket_id
Returns:      N/A

This function is called when a server is connected to.
======================================================================= */
void eipc_rtasys_onTCPConnect (EIPC_USERSYS_SOCKTYPE socket_id)
{
   int16 i;

   /* see if we can accept the new connection */
   i = local_findFreeSocketIx ();

   /* we can't receive the socket, close it */
   if(i == -1)
      eipc_usersock_tcpClose(socket_id);

   /* set up a structure to store messages from the socket */
   else
   {
      struct_data[i].socket_id = socket_id;
      struct_data[i].state = EIPC_STATE_RUNNING;
      struct_data[i].buf_size = 0;
      memset(struct_data[i].buf, 0, sizeof(struct_data[i].buf));
      struct_data[i].client_owned = TRUE;
   }
  
   // inform the client of the connect
   eipc_tagclient_onConnect (socket_id);
}

/**/
/* ******************************************************************** */
/*               LOCAL FUNCTIONS                                        */
/* ******************************************************************** */
/* ====================================================================
Function:     local_getState
Parameters:   socket_id
Returns:      Current State

This function returns the current state of the EIP Server state
machine for the passed socket_id.
======================================================================= */
static uint8 local_getState (EIPC_USERSYS_SOCKTYPE socket_id)
{
   int16 i;

   /* make sure we have the socket */
   i = local_findSocketIx(socket_id);
   if(i == -1)
      return(EIPC_STATE_RUNNING);

   /* we found the socket, return the state */
   return(struct_data[i].state);
}

/* ====================================================================
Function:     local_initAll
Parameters:   initType
Returns:      N/A

This function initializes all variables based on the passed initType.
======================================================================= */
static void local_initAll (uint8 initType)
{
   int16 i;

   /* Force to Out-of-Box on errors */
   if(initType != EIPC_INIT_NORMAL)
   {
      initType = EIPC_INIT_OUTOFBOX;
   }

   eipc_encap_init    (initType);
   eipc_timer_init    (initType);
   eipc_usersys_init  (initType);
   eipc_userobj_init  (initType);
   eipc_usersock_init (initType);

   /* call if Client is supported */
   eipc_tagclient_init (initType);

   /* initialize local structures */
   for(i=0; i<EIPC_USER_MAX_NUM_SOCKETS; i++)
   {
      struct_data[i].socket_id = EIPC_USER_SOCKET_UNUSED;
      struct_data[i].state = EIPC_STATE_RUNNING;
      struct_data[i].buf_size = 0;
      memset(struct_data[i].buf, 0, sizeof(struct_data[i].buf));
      struct_data[i].client_owned = FALSE;
   }
}

/* ====================================================================
Function:     local_nvramTest
Parameters:   initType
Returns:      N/A

This function tests all locations of the NVRAM on the first power-up
then validates the checksum on all other power-ups.
======================================================================= */
static void local_nvramTest (uint8 initType)
{
   if(initType){} //keep the compiler happy
   /* if the test fails, we have a fatal error */
   //jdw add me
}

/* ====================================================================
Function:     local_closeAllSockets
Parameters:   N/A
Returns:      N/A

This function closes all open sockets prior to a reset.
======================================================================= */
static void local_closeAllSockets (void)
{
    int16 i;

    for(i=0; i<EIPC_USER_MAX_NUM_SOCKETS; i++)
    {
	   if(struct_data[i].socket_id != EIPC_USER_SOCKET_UNUSED)
          eipc_usersock_tcpClose(struct_data[i].socket_id);
	
	   local_freeSocketIx(struct_data[i].socket_id);
   }
}

/* ====================================================================
Function:     local_findSocketIx
Parameters:   Socket ID
Returns:      Index where socket info is stored (-1 on error)

This function finds which index stores the socket information.
======================================================================= */
static int16 local_findSocketIx (EIPC_USERSYS_SOCKTYPE socket_id)
{
   int16 i;

   /* search for a free element */
   for(i=0; i<EIPC_USER_MAX_NUM_SOCKETS; i++)
   {
      /* the socket element is free */
      if(struct_data[i].socket_id == socket_id)
      {
         return(i);
      }
   }

   /* socket index not found */
   return (-1);
}

/* ====================================================================
Function:     local_freeSocketIx
Parameters:   Socket ID
Returns:      N/A

This function finds which index stores the passed socket id and frees
the resources.
======================================================================= */
static void local_freeSocketIx (EIPC_USERSYS_SOCKTYPE socket_id)
{
   int16 i;

   for(i=0; i<EIPC_USER_MAX_NUM_SOCKETS; i++)
   {
      if(struct_data[i].socket_id == socket_id)
      {
         struct_data[i].socket_id = EIPC_USER_SOCKET_UNUSED;
         struct_data[i].state = EIPC_STATE_RUNNING;
         struct_data[i].buf_size = 0;
         memset(struct_data[i].buf, 0, sizeof(struct_data[i].buf));
         struct_data[i].client_owned = FALSE;		 	
      }
   }
}

/* ====================================================================
Function:     local_findFreeSocketIx
Parameters:   N/A
Returns:      Index to store the socket info (-1 on error)

This function finds the next free index to store the socket info.
======================================================================= */
static int16 local_findFreeSocketIx (void)
{
   int16 i;

   /* search for a free element */
   for(i=0; i<EIPC_USER_MAX_NUM_SOCKETS; i++)
   {
      /* the socket element is free */
      if(struct_data[i].socket_id == EIPC_USER_SOCKET_UNUSED)
      {
         return(i);
      }
   }

   /* no free socket indexes */
   return (-1);
}

/* *********** */
/* END OF FILE */
/* *********** */
