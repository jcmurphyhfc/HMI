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
 *     Module Name: eipc_usersock.c
 *          Author: Jamin D. Wendorf (jwendorf@rtaautomation.com)
 *        Language: Ansi C
 * Compile Options: N/A
 * Compile defines: N/A
 *       Libraries: N/A
 *    Link Options: N/A
 *
 * Description.
 * ====================================================================
 * This file contains the user socket functions. All functions in this
 * file are the responsibility of the user to write.
 *
 */

/* ---------------------------- */
/* INCLUDE FILES                */
/* ---------------------------- */
#include "eipc_system.h"

/* ---------------------------- */
/* LOCAL STRUCTURE DEFINITIONS  */
/* ---------------------------- */
#define USERSOCK_MAX_BUF_SIZ 600
#define USERSOCK_LISTEN_IX   0
#define USERSOCK_UDP_IX      1
#define USERSOCK_TCPSTART_IX 2
#define USERSOCK_SOCKID_UNUSED -1

typedef struct
{
   struct sockaddr_in    socka;
   EIPC_USERSYS_SOCKTYPE sockid;
   uint8 tx_in_prog_flag;
   uint8 connect_in_prog_flag;
}USERSOCK_SOCKSTRUCT;

/* ---------------------------- */
/* STATIC VARIABLES             */
/* ---------------------------- */
static USERSOCK_SOCKSTRUCT usersock_sockets [EIPC_USER_MAX_NUM_SOCKETS];
uint8 macid_string[6];

/* ---------------------------- */
/* LOCAL FUNCTIONS              */
/* ---------------------------- */
static void  local_openUdpSocket      (USERSOCK_SOCKSTRUCT *user_sock);
static void  local_startTcpListen     (USERSOCK_SOCKSTRUCT *user_sock);
static int16 local_findSocketIx       (EIPC_USERSYS_SOCKTYPE socket_id);
static void  local_freeSocketIx       (EIPC_USERSYS_SOCKTYPE socket_id);
static int16 local_findUnusedSocketIx (void);
static uint32 local_swap32 (uint32);

/* ---------------------------- */
/* MISCELLANEOUS                */
/* ---------------------------- */

/**/
/* ******************************************************************** */
/*                      GLOBAL FUNCTIONS                                */
/* ******************************************************************** */
/* ====================================================================
Function:     eipc_usersock_process
Parameters:   N/A
Returns:      N/A

This function checks for socket activity and notifies the RTA stack
when certain events occur:

eipc_rtasys_onTCPAccept - called when a client connects to us
eipc_rtasys_onTCPData   - called when TCP data is received
eipc_rtasys_onUDPData   - called when UDP data is received
eipc_rtasys_onTCPSent   - called when a UDP/TCP send is complete
eipc_rtasys_onTCPClose  - called when a socket is closed
eipc_rtasys_onIOData    - called when I/O data is received (opt. support)
======================================================================= */
void eipc_usersock_process (void)
{
   int return_code, sock_size;
   int16 i;
   int buffer_size;
   char buffer[USERSOCK_MAX_BUF_SIZ];
   fd_set readfds;
   fd_set writefds;
   fd_set exceptfds;
   struct timeval timeout;

   /* use the select() call to check multiple sockets with one call */
   timeout.tv_sec = 0;
   timeout.tv_usec = 1; /* wait 1 msec on the call */

   /* we need to zero the socket set every time */
   FD_ZERO(&readfds);
   FD_ZERO(&writefds);
   FD_ZERO(&exceptfds);

   /* add the UDP socket to the read set */
   FD_SET(usersock_sockets[USERSOCK_UDP_IX].sockid, &readfds);

   /* add the TCP listening socket to the read set */
   FD_SET(usersock_sockets[USERSOCK_LISTEN_IX].sockid, &readfds);

   /* add any other sockets that are being used */
   for(i=USERSOCK_TCPSTART_IX; i<EIPC_USER_MAX_NUM_SOCKETS; i++)
   {
      if(usersock_sockets[i].sockid != USERSOCK_SOCKID_UNUSED)
      {
         FD_SET(usersock_sockets[i].sockid, &readfds);
         FD_SET(usersock_sockets[i].sockid, &writefds);
      }
   }

   /* check for activity */
   return_code = select(-1, &readfds, &writefds, &exceptfds, &timeout);
   /* error returned */
   if (return_code < 0)
   {
      eipc_usersys_fatalError("usersock_process", 0);
   }

   /* We have an event */
   else if (return_code > 0)
   {
      /* New TCP Connection Received */
      if (FD_ISSET(usersock_sockets[USERSOCK_LISTEN_IX].sockid, &readfds))
      {
         /* look for unused socket */
         i = local_findUnusedSocketIx();

         /* out of sockets */
         if(i == -1)
         {
            eipc_user_dbprint0("Out of sockets!\r\n");
         }

         /* try to accept the socket */
         else
         {
            sock_size = sizeof(struct sockaddr_in);
            usersock_sockets[i].sockid = (EIPC_USERSYS_SOCKTYPE)accept(usersock_sockets[USERSOCK_LISTEN_IX].sockid,
                                               (struct sockaddr *)&usersock_sockets[i].socka, &sock_size);
            /* accept failed */
            if(usersock_sockets[i].sockid < 0)
               eipc_usersys_fatalError("usersock_process", 1);

            /* inform the RTA source of the new connection */
            else
               eipc_rtasys_onTCPAccept(usersock_sockets[i].sockid);
         }
      } // END-> "New TCP Connection Received"

      /* UDP Data Received */
      if (FD_ISSET(usersock_sockets[USERSOCK_UDP_IX].sockid, &readfds))
      {
         /* read from the socket */
         sock_size =  sizeof(struct sockaddr_in);
         buffer_size = recvfrom(usersock_sockets[USERSOCK_UDP_IX].sockid, buffer, USERSOCK_MAX_BUF_SIZ, 0,
                                (struct sockaddr *)&usersock_sockets[USERSOCK_UDP_IX].socka, &sock_size);

         /* error returned */
         if (buffer_size < 0)
            eipc_usersys_fatalError("usersock_process", 2);

         /* inform the RTA source of the new data */
         else
            eipc_rtasys_onUDPData (usersock_sockets[USERSOCK_UDP_IX].sockid, (uint8 *)buffer, (uint16) buffer_size);
      } // END-> "UDP Data Received"

      /* TCP Data Received or Send Complete */
      for(i=USERSOCK_TCPSTART_IX; i<EIPC_USER_MAX_NUM_SOCKETS; i++)
      {
         /* only check used sockets */
         if (usersock_sockets[i].sockid != USERSOCK_SOCKID_UNUSED)
         {
            /* we received data */
            if (FD_ISSET(usersock_sockets[i].sockid, &readfds))
            {
               buffer_size = recv(usersock_sockets[i].sockid, buffer, USERSOCK_MAX_BUF_SIZ, 0);

               /* error returned, close socket */
               if (buffer_size <= 0 )
                  eipc_usersock_tcpClose(usersock_sockets[i].sockid);

               /* get successful */
               else
                  eipc_rtasys_onTCPData (usersock_sockets[i].sockid, (uint8 *)buffer, (uint16) buffer_size);
            }

            /* send completed */
            if (FD_ISSET(usersock_sockets[i].sockid, &writefds))
            {
               if(usersock_sockets[i].connect_in_prog_flag == TRUE)
               {
                   /* if a tx was in progress, inform the user when done */
                   eipc_rtasys_onTCPConnect(usersock_sockets[i].sockid);
                   usersock_sockets[i].connect_in_prog_flag = FALSE;
               }

               if(usersock_sockets[i].tx_in_prog_flag == TRUE)
               {
                  /* if a tx was in progress, inform the user when done */
                  eipc_rtasys_onTCPSent(usersock_sockets[i].sockid);
                  usersock_sockets[i].tx_in_prog_flag = FALSE;
               }
            }
         } // END-> "only check used sockets */
      } // END-> "TCP or I/O Data Received or Send Complete"
   } // END-> "We have an event"
} // END-> function

/* ====================================================================
Function:     eipc_usersock_init
Parameters:   init type
Returns:      N/A

This function initialize all user socket variables.
======================================================================= */
void eipc_usersock_init (uint8 init_type)
{
   int16 i;

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

   macid_string[0] = 1;
   macid_string[1] = 2;
   macid_string[2] = 3;
   macid_string[3] = 4;
   macid_string[4] = 5;
   macid_string[5] = 6;

   /* initialize all static variables */
   for(i=0; i<EIPC_USER_MAX_NUM_SOCKETS; i++)
   {
      usersock_sockets[i].sockid = (EIPC_USERSYS_SOCKTYPE)USERSOCK_SOCKID_UNUSED;
      memset(&usersock_sockets[i].socka,0,sizeof(struct sockaddr_in));
      usersock_sockets[i].tx_in_prog_flag = FALSE;
      usersock_sockets[i].connect_in_prog_flag = FALSE;
   }

   /* open a UDP socket for UCMM Messages */
   local_openUdpSocket (&usersock_sockets[USERSOCK_UDP_IX]);

   /* start a listening socket */
   local_startTcpListen (&usersock_sockets[USERSOCK_LISTEN_IX]);
}

/* ====================================================================
Function:     eipc_usersock_sendData
Parameters:   socket id
              pointer to socket data
              socket data size
Returns:      N/A

This function sends the passed data to the network client.
======================================================================= */
int16 eipc_usersock_sendData (EIPC_USERSYS_SOCKTYPE socket_id, uint8 * socket_data, uint16 socket_data_size)
{
   int16 return_code, ix;

   /* successful send (keep track to inform the user on success */
   ix = local_findSocketIx(socket_id);

   if(ix == EIPC_USER_MAX_NUM_SOCKETS)
   {
      eipc_usersock_tcpClose(socket_id);
      return(-1);
   }

   return_code = (int16)sendto (socket_id, (char *) socket_data, socket_data_size, 0, (struct sockaddr *)&usersock_sockets[ix].socka ,sizeof(struct sockaddr_in));
   
   /* there is an error with the send, close the socket */
   if(return_code < 0)
   {
      eipc_usersock_tcpClose(socket_id);
      return(-1);
   }

   usersock_sockets[ix].tx_in_prog_flag = TRUE;
   #ifdef EIPC_PRINTALL
      eipc_user_dbprint2("Sent %d bytes [Socket %d]\r\n", socket_data_size, socket_id);
   #endif

   return(0);
}

/* ====================================================================
Function:     eipc_usersock_tcpClose
Parameters:   socket id
Returns:      N/A

This function closes the passed socket.
======================================================================= */
void eipc_usersock_tcpClose (EIPC_USERSYS_SOCKTYPE socket_id)
{
   int16 return_code;

   /* try to close the socket */
   return_code = (int16)closesocket (socket_id);

   /* close was successful, inform RTA source */
   if(return_code == 0)
   {
      eipc_rtasys_onTCPClose(socket_id);
   }
  
   /* Free the socket to be used */
   local_freeSocketIx(socket_id);
}

/* ====================================================================
Function:     eipc_usersock_getSockInfo_sin_addr
Parameters:   socket id
Returns:      sin_addr for the passed socket.

This function returns the sin_addr for the passed socket (0 on error).
======================================================================= */
uint32 eipc_usersock_getSockInfo_sin_addr (EIPC_USERSYS_SOCKTYPE socket_id)
{
   uint16 ix;

   /* find which socket instance they are interested in */
   ix = local_findSocketIx (socket_id);

   /* the socket does not exist */
   if(ix == EIPC_USER_MAX_NUM_SOCKETS)
   {
      eipc_user_dbprint1("eipc_usersock_getSockInfo_sin_addr not found %d\r\n", socket_id);
      return(0);
   }

   /* return the sin_family for the passed socket */
   return(local_swap32(usersock_sockets[ix].socka.sin_addr.s_addr));
}

/* ====================================================================
Function:     eipc_usersock_getOurIPAddr
Parameters:   N/A
Returns:      32-bit IP Address

This function returns the current IP address of the device.
======================================================================= */
uint32 eipc_usersock_getOurIPAddr (void)
{  
   char ac[80];
   struct hostent *phe;
   struct in_addr addr;

   if (gethostname(ac, sizeof(ac)) == SOCKET_ERROR) 
   {
      eipc_usersys_fatalError("eipc_usersock_getOurIPAddr",0);
	  return(0);
   }

   phe = gethostbyname(ac);

   if (phe == 0) 
   {
      eipc_usersys_fatalError("eipc_usersock_getOurIPAddr",1);
	  return(0);
   }

   memcpy(&addr, phe->h_addr_list[0], sizeof(struct in_addr));   
   return(local_swap32(addr.S_un.S_addr));
}

/* Ethernet Link Object */
/* ====================================================================
Function:     eipc_usersock_getOurMacAddr
Parameters:   Pointer to the buffer to store the 6-byte mac address
Returns:      SUCCESS/FAILURE

This function returns the 6-byte MAC ID of server device. See the
Ethernet Link Object definition in the EtherNet/IP volume of the ODVA
specification for more information.
======================================================================= */
uint8  eipc_usersock_getOurMacAddr (uint8 *macid_6byte_string)
{
   uint8 i;

   for(i=0; i<6; i++)
      macid_6byte_string[i] = macid_string[i];

   return(SUCCESS);
}

/* ====================================================================
Function:     eipc_usersock_connect
Parameters:   IP Address
Returns:      socket identifier for the new connection 
              (EIPC_USER_SOCKET_UNUSED on error)

This function tries allocate a socket then connect to the passed IP 
address.
======================================================================= */
EIPC_USERSYS_SOCKTYPE eipc_usersock_connect(uint32 ipaddr)
{
   int16 ix;
   uint32 argp;
   int    return_code;
   int    error_code;

   // if the IP Address is zero, return EIPC_USER_SOCKET_UNUSED
   if(ipaddr == 0)
      return(EIPC_USER_SOCKET_UNUSED);

   // get a socket
   ix = local_findUnusedSocketIx();

   // no free sockets
   if(ix == -1)
      return(EIPC_USER_SOCKET_UNUSED);

   // try to get a socket
   usersock_sockets[ix].sockid = socket(AF_INET, SOCK_STREAM, 0);

   // we couldn't get the socket
   if(usersock_sockets[ix].sockid < 0)
      return(EIPC_USER_SOCKET_UNUSED);

   /* make the socket non-blocking */
   argp = 1L;
   return_code = ioctlsocket(usersock_sockets[ix].sockid, FIONBIO, (uint32 *) &argp);
   if(return_code < 0)
      eipc_usersys_fatalError("eipc_usersock_connect (non_block failed)",0);

   /* initialize the sockaddr_in structure */
   usersock_sockets[ix].socka.sin_family           = AF_INET;
   usersock_sockets[ix].socka.sin_port             = htons(0xAF12);
   usersock_sockets[ix].socka.sin_addr.S_un.S_addr = htonl(ipaddr);
   memset(usersock_sockets[ix].socka.sin_zero, 0, 8);

   /* We need to notify the client when the connection occurs */
   usersock_sockets[ix].connect_in_prog_flag = TRUE;

   /* connect to the server */
   return_code = connect(usersock_sockets[ix].sockid, (struct sockaddr *)&usersock_sockets[ix].socka, sizeof(struct sockaddr_in));
   if(return_code < 0)
   {
      /* The only error we like is WSAEWOULDBLOCK */
      error_code = WSAGetLastError();
      if(error_code != WSAEWOULDBLOCK)
      {
         return(EIPC_USER_SOCKET_UNUSED);
      }
   }

   /* return the sockid */
   return(usersock_sockets[ix].sockid);
}

/**/
/* ******************************************************************** */
/*                      LOCAL FUNCTIONS                                 */
/* ******************************************************************** */
/* ====================================================================
Function:     local_openUdpSocket
Parameters:   user socket structure pointer
Returns:      N/A

This function attemps to open and bind a UDP socket based on the
parameters stored in the socket structure.
======================================================================= */
static void local_openUdpSocket (USERSOCK_SOCKSTRUCT *user_sock)
{
   int16 return_code;

   /* initialize udp socket */
   memset(&user_sock->socka, 0, sizeof(user_sock->socka));
   user_sock->socka.sin_addr.s_addr = htonl(0);
   user_sock->socka.sin_family = AF_INET;
   user_sock->socka.sin_port = htons(EIP_CIP_PORT);
   memset(&user_sock->socka.sin_zero, 0, sizeof(user_sock->socka.sin_zero));

   /* get UDP socket */
   user_sock->sockid = socket(AF_INET, SOCK_DGRAM, 0);

   /* we didn't get the socket */
   if(user_sock->sockid < 0)
   {
      eipc_usersys_fatalError("local_openUdpSocket", 0);
      return;
   }

   /* bind UDP socket */
   return_code = (int16)bind(user_sock->sockid, (struct sockaddr *)&user_sock->socka, sizeof(struct sockaddr));

   /* bind failed */
   if(return_code < 0)
   {
      eipc_usersys_fatalError("local_openUdpSocket", 1);
      return;
   }
}

/* ====================================================================
Function:     local_startTcpListen
Parameters:   listen socket structure pointer
Returns:      N/A

This function attemps to open and bind a TCP socket based on the
parameters stored in the socket structure.  This socket is used to
listen for other socket connect requests.
======================================================================= */
static void local_startTcpListen (USERSOCK_SOCKSTRUCT *user_sock)
{
   int16 return_code;

   /* initialize listen socket */
   memset(&user_sock->socka, 0, sizeof(user_sock->socka));
   user_sock->socka.sin_family = AF_INET;
   user_sock->socka.sin_port = htons(EIP_CIP_PORT);
   memset(&user_sock->socka.sin_zero, 0, sizeof(user_sock->socka.sin_zero));

   /* get socket */
   user_sock->sockid = socket(AF_INET, SOCK_STREAM, 0);

   /* get failed */
   if(user_sock->sockid < 0)
   {
      eipc_usersys_fatalError("local_startTcpListen", 0);
      return;
   }

   /* bind socket */
   return_code = (int16)bind(user_sock->sockid, (struct sockaddr *)&user_sock->socka, sizeof(struct sockaddr));

   /* bind failed */
   if(return_code < 0)
   {
      eipc_usersys_fatalError("local_startTcpListen", 1);
      return;
   }

   /* listen for connection */
   return_code = (int16)listen(user_sock->sockid, 1);

   /* listen failed */
   if(return_code < 0)
   {
      eipc_usersys_fatalError("local_startTcpListen", 2);
      return;
   }
}

/* ====================================================================
Function:     local_findSocketIx
Parameters:   socket id
Returns:      ix (-1 on error)

This function searches through the array of socket ids and returns the
index for the matching element.
======================================================================= */
static int16 local_findSocketIx (EIPC_USERSYS_SOCKTYPE socket_id)
{
   int16 i;

   /* search through the list of sockets for the passed socket id */
   for(i=0; i<EIPC_USER_MAX_NUM_SOCKETS; i++)
      if (usersock_sockets[i].sockid == socket_id)
         return(i);
   /* no match was found */
   return(-1);
}

/* ====================================================================
Function:     local_freeSocketIx
Parameters:   socket id
Returns:      N/A

This function searches through the array of socket ids for the passed
socket id and frees the socket ix.
======================================================================= */
static void local_freeSocketIx (EIPC_USERSYS_SOCKTYPE socket_id)
{
   int16 i;

   /* search through the list of sockets for the passed socket id */
   for(i=0; i<EIPC_USER_MAX_NUM_SOCKETS; i++)
   {
      if (usersock_sockets[i].sockid == socket_id)
      {
         usersock_sockets[i].sockid = (EIPC_USERSYS_SOCKTYPE)USERSOCK_SOCKID_UNUSED;
         memset(&usersock_sockets[i].socka,0,sizeof(struct sockaddr_in));
         usersock_sockets[i].tx_in_prog_flag = FALSE;
         return;
      }
   }
}

/* ====================================================================
Function:     local_findUnusedSocketIx
Parameters:   N/A
Returns:      ix (-1 on error)

This function returns the first free index or -1 if all sockets are
used.
======================================================================= */
static int16 local_findUnusedSocketIx (void)
{
   int16 i;

   /* search through the list of sockets for a free socket */
   for(i=USERSOCK_TCPSTART_IX; i<EIPC_USER_MAX_NUM_SOCKETS; i++)
      if (usersock_sockets[i].sockid == USERSOCK_SOCKID_UNUSED)
         return(i);
   /* no free sockets */
   return(-1);
}

/* ====================================================================
Function:     local_swap32
Parameters:   32-bit number
Returns:      32-bit number

This function swaps the byte order of the passed number.
======================================================================= */
static uint32 local_swap32 (uint32 passed_val)
{
   uint32 return_val;

   return_val  = (passed_val & 0xFF000000)>>24;
   return_val |= (passed_val & 0x00FF0000)>>8;
   return_val |= (passed_val & 0x0000FF00)<<8;
   return_val |= (passed_val & 0x000000FF)<<24;

   return(return_val);
}

/* *********** */
/* END OF FILE */
/* *********** */
