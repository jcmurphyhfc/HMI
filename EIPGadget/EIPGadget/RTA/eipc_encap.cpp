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
 *     Module Name: eipc_encap.c
 *          Author: Jamin D. Wendorf (jwendorf@rtaautomation.com)
 *        Language: Ansi C
 * Compile Options: N/A
 * Compile defines: N/A
 *       Libraries: N/A
 *    Link Options: N/A
 *
 * Description.
 * ====================================================================
 * This file contains the EIP Encapsulation Protocol
 *
 */

/* ---------------------------- */
/* INCLUDE FILES                */
/* ---------------------------- */
#include "eipc_system.h"

/* ---------------------------- */
/* LOCAL FUNCTION PROTOTYPES    */
/* ---------------------------- */

/* supported Encapsulated messages */
void   eipc_encap_Nop               (EIPC_ENCAP_MSG_STRUCT *EncapReq, EIPC_SOCKET_STRUCT *sock);
void   eipc_encap_RegisterSession   (EIPC_ENCAP_MSG_STRUCT *EncapReq, EIPC_SOCKET_STRUCT *sock);
void   eipc_encap_UnregisterSession (EIPC_ENCAP_MSG_STRUCT *EncapReq, EIPC_SOCKET_STRUCT *sock);
void   eipc_encap_ListServices      (EIPC_ENCAP_MSG_STRUCT *EncapReq, EIPC_SOCKET_STRUCT *sock);
void   eipc_encap_ListIdentity      (EIPC_ENCAP_MSG_STRUCT *EncapReq, EIPC_SOCKET_STRUCT *sock);
void   eipc_encap_ListInterfaces    (EIPC_ENCAP_MSG_STRUCT *EncapReq, EIPC_SOCKET_STRUCT *sock);

/* needed for debug tools only */
#define EIPC_ENCAPCMD_LISTTARGETS 0x0001
void   eipc_encap_ListTargets       (EIPC_ENCAP_MSG_STRUCT *EncapReq, EIPC_SOCKET_STRUCT *sock);

/* used to validate and issue/free session ids */
void   eipc_encap_SessionInit       (EIPC_SESSION_STRUCT *session);
int16  eipc_encap_SessionFind       (EIPC_USERSYS_SOCKTYPE sock_id);
int16  eipc_encap_GetSessionIx      (EIPC_USERSYS_SOCKTYPE sock_id);

/* ---------------------------- */
/* MISCELLANEOUS                */
/* ---------------------------- */
EIPC_SESSION_STRUCT EIP_Sessions[EIPC_USER_MAX_NUM_EIP_SESSIONS];
uint32 EIPSessionID = 0x00000001L;

/**/
/* ******************************************************************** */
/*                      GLOBAL FUNCTIONS                                */
/* ******************************************************************** */

/* ====================================================================
Function:    eipc_encap_init
Parameters:  init type
Returns:     N/A

This function initializes all static variables used in this file.
======================================================================= */
void eipc_encap_init(uint8 init_type)
{
   int i;

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

   /* initialize session structures */
   for(i=0; i<EIPC_USER_MAX_NUM_EIP_SESSIONS; i++)
      eipc_encap_SessionInit(&EIP_Sessions[i]);
}

/* ====================================================================
Function:    eipc_encap_SessionInit
Parameters:  session structure pointer
Returns:     N/A

This function closes the passed socket and sets the socket structure
element back to the default state.
======================================================================= */
void eipc_encap_SessionInit(EIPC_SESSION_STRUCT *session)
{
   session->sock_id = EIPC_USER_SOCKET_UNUSED;
   session->SessionHandle = 0;
}

/* ====================================================================
Function:    eipc_encap_SessionFind
Parameters:  socket id
Returns:     session index

This function compares the passed socket id to see if a session exists.
======================================================================= */
int16 eipc_encap_SessionFind (EIPC_USERSYS_SOCKTYPE sock_id)
{
   int16 i;

   for(i=0; i<EIPC_USER_MAX_NUM_EIP_SESSIONS; i++)
      if(EIP_Sessions[i].sock_id == sock_id)
         return(i);
   return(-1);
}

/* ====================================================================
Function:    eipc_encap_getSessionStruct
Parameters:  session ID
Returns:     session structure pointer or NULL

This function looks up the passed session ID and returns the session
structure that matches the session ID, NULL on error.
======================================================================= */
EIPC_SESSION_STRUCT * eipc_encap_getSessionStruct (uint32 sessionID)
{
   uint16 i;

   /* if the session ID is 0, there is an error */
   if(sessionID == 0)
      return(NULL);

   /* look to match the session ID */
   for(i=0; i<EIPC_USER_MAX_NUM_EIP_SESSIONS; i++)
   {
      /* we found the session, return the structure pointer */
      if(EIP_Sessions[i].SessionHandle == sessionID)
      {
         return(&EIP_Sessions[i]);
      }
   }

   /* Error, return NULL */
   return(NULL);
}

/* ====================================================================
Function:    eipc_encap_GetSessionIx
Parameters:  socket id
Returns:     session index

This function compares the passed socket id to see if a session exists.
If a session exists, return -1, else return the next session index and
store a session number.
======================================================================= */
int16 eipc_encap_GetSessionIx (EIPC_USERSYS_SOCKTYPE sock_id)
{
   int16 i;

   /* the sock_id is already used */
   if(eipc_encap_SessionFind(sock_id) != -1)
      return(-1);

   /* find the next free session */
   for(i=0; i<EIPC_USER_MAX_NUM_EIP_SESSIONS; i++)
      if(EIP_Sessions[i].sock_id == EIPC_USER_SOCKET_UNUSED)
      {
         EIP_Sessions[i].SessionHandle = EIPSessionID;
         EIPSessionID++;
         EIP_Sessions[i].sock_id = sock_id;
         return(i);
      }
   return(-1);
}

/* ====================================================================
Function:    eipc_encap_freeSessionIx
Parameters:  socket id
Returns:     N/A

This function compares the passed socket id to see if a session exists.
If a session exists, re-init the socket id.
======================================================================= */
void eipc_encap_freeSessionIx (EIPC_USERSYS_SOCKTYPE sock_id)
{
   int16 session_ix;

   session_ix = eipc_encap_SessionFind (sock_id);

   /* the session is valid */
   if(session_ix != -1)
   {
     /* free the session */
     eipc_encap_SessionInit(&EIP_Sessions[session_ix]);
   }
}

/* ====================================================================
Function:     eipc_encap_process
Parameters:   socket structure pointer
              message pointer
              message size
Returns:      bytes used from message pointer

This function processes the encapsulated message.  If more than one
message is available (even partial messages), this function tries
to process the partial message before returning.

We support the following encapsulated messages:
All fields but the encapsulated data content are validated prior to
sending the message to the response building function. The following
is the order of the validation:
  Prior to the command process
  1. Length vs. Encapsulated Data received
  2. Status must equal 0
  3. Options must equal 0
  4. Sender Context - don't care, add to reply
  5. Command

  Within the command process:
  1. Session Handle (if applicable)
  2. Pass the message to the CommandFunction

------ ----------------  ----------------------------------------------
 CODE  NAME              NOTES
------ ----------------  ----------------------------------------------
0x0000 NOP               (May be sent only using TCP)
0x0001 ListTargets       (This is for debug only, remove for production)
0x0004 ListServices      (May be sent using either UDP or TCP)
0x0063 ListIdentity      (May be sent using either UDP or TCP)
0x0065 RegisterSession   (May be sent only using TCP)
0x0066 UnRegisterSession (May be sent only using TCP)
0x006F SendRRData        (May be sent only using TCP)  ** NOT SUPPORTED
0x0070 SendUnitData      (May be sent only using TCP)  ** NOT SUPPORTED
------ ----------------  ----------------------------------------------

An Encapsulation Message has the following format:
  ----------------------------------------------------------------------
 |  FIELD NAME       |        TYPE       |         DESCRIPTION          |
 |----------------------------------------------------------------------|
 | Command           | UINT16            | Encapsulated Command         |
 |----------------------------------------------------------------------|
 | Length            | UINT16            | Len (in bytes) of encap data |
 |----------------------------------------------------------------------|
 | Session Handle    | UINT32            | Session ID (Appl. Dependent) |
 |----------------------------------------------------------------------|
 | Status            | UINT32            | Status Code                  |
 |----------------------------------------------------------------------|
 | Sender Context    | ARRAY[8] OF UINT8 | Info for sender              |
 |----------------------------------------------------------------------|
 | Options           | UINT32            | Options Flags                |
 |----------------------------------------------------------------------|
 | Encapsulated Data | ARRAY OF UINT8    | The encap. data portion      |
  ----------------------------------------------------------------------
======================================================================= */
uint16 eipc_encap_process (EIPC_SOCKET_STRUCT *sock, uint8 *msg, uint16 msg_siz)
{
   EIPC_ENCAP_MSG_STRUCT encap;
   int i;
   uint8 done_flag = FALSE;
   uint16 return_val = msg_siz;
   uint16 encap_length; /* length is sometimes modified along the way */

   /* *************************************************** */
   /* don't leave this function if more data is ready !!! */
   /* *************************************************** */
   while (done_flag == FALSE)
   {
      /* make sure we have enough bytes for the header */
      if(msg_siz < EIP_ENCAP_HEADER_SIZ)
      {
         /* set the done flag */
         done_flag = TRUE;
      }

      /* we have a valid header, continue */
      else
      {
         /* Parse the Encapsulated message */
         encap.Command       = rta_GetLitEndian16 (msg+0);
         encap.Length        = rta_GetLitEndian16 (msg+2);
         encap.SessionHandle = rta_GetLitEndian32 (msg+4);
         encap.Status        = rta_GetLitEndian32 (msg+8);
         for(i=0; i<8; i++)
            encap.SenderContext[i] = *(msg+12+i);
         encap.Options = rta_GetLitEndian32(msg+20);
         encap.EncapsulatedData = (msg + EIP_ENCAP_HEADER_SIZ);

         /* *************************** */
         /* Valid lengths are 0 - 65511 */
         /* *************************** */
         if(encap.Length > 65511L) /* ignore the message if too much data */
         {
            /* store more data after the header */
            return_val = EIP_ENCAP_HEADER_SIZ;

            /* decrement the length based on the number of data bytes */
            encap.Length = encap.Length - (msg_siz-EIP_ENCAP_HEADER_SIZ);

            /* store the new length of the NOP */
            rta_PutLitEndian16(encap.Length, msg+2);

            /* return the header size */
            return(return_val);
         }

         /* Message Size should be EIP_ENCAP_HEADER_SIZ + encap.Length */
         if (((encap.Length + EIP_ENCAP_HEADER_SIZ) > msg_siz) &&
            (sock->sock_type == SOCKTYPE_TCP))
         {
            /* set the done flag */
            done_flag = TRUE;

            /* We need special code to receive NOP messages. The size of the NOP
               data can be 0 to 65511.  This is far more data than any other
               message we receive.  When a NOP message is processed, we receive
               and discard all data until we get the end of the message, then we
               return.  */
            if(encap.Command == EIP_ENCAPCMD_NOP)
            {
               /* store more data after the header */
               return_val = EIP_ENCAP_HEADER_SIZ;

               /* decrement the length based on the number of data bytes */
               encap.Length = encap.Length - (msg_siz-EIP_ENCAP_HEADER_SIZ);

               /* store the new length of the NOP */
               rta_PutLitEndian16(encap.Length, msg+2);

               /* return the header size */
               return(return_val);
            }
         }

         /* UDP length must be exact */
         else if ((sock->sock_type == SOCKTYPE_UDP) &&
                  ((encap.Length + EIP_ENCAP_HEADER_SIZ) != msg_siz))
         {
            /* Always return 0 for UDP messages */
            return(0);
         }

         /* We have a valid message */
         else
         {
            /* save the length of the request for purge purposes */
            encap_length = encap.Length;

            /* *************************************************************** */
            /* *************************************************************** */
            /* Switch on the supported commands if status and options are zero */
            /* *************************************************************** */
            /* *************************************************************** */
            if(encap.Status == 0)
            {
               /* Just return the Sender Context - Don't Care about content */
               switch (encap.Command)
               {
                  /* ********************************** */
                  /* Encapsulated Command 0x0000: "NOP" */
                  /* ********************************** */
                  case EIP_ENCAPCMD_NOP:
                     /* if this is a UDP message send an error message */
                     if(sock->sock_type == SOCKTYPE_UDP)
                     {
                        encap.Status = EIP_ENCAPSTATUSERR_COMMAND;
                        eipc_encap_unSupEncapMsg(&encap, sock);
                     }

                     /* valid for TCP connections only */
                     else
                        eipc_encap_Nop(&encap,sock);
                     break;

                  /* **************************************************** */
                  /* Encapsulated Command 0x0001: "ListTargets" (DB ONLY) */
                  /* **************************************************** */
//                  case EIPC_ENCAPCMD_LISTTARGETS:
//                    eipc_encap_ListTargets(&encap,sock);
//                    break;

                  /* ******************************************* */
                  /* Encapsulated Command 0x0004: "ListServices" */
                  /* ******************************************* */
                  case EIP_ENCAPCMD_LISTSERVICES:
                    eipc_encap_ListServices(&encap,sock);
                    break;

                  /* ******************************************* */
                  /* Encapsulated Command 0x0063: "ListIdentity" */
                  /* ******************************************* */
                  case EIP_ENCAPCMD_LISTIDENTITY:
                     eipc_encap_ListIdentity(&encap,sock);
                     break;

                  /* ********************************************** */
                  /* Encapsulated Command 0x0065: "RegisterSession" */
                  /* ********************************************** */
                  case EIP_ENCAPCMD_REGISTERSESSION:
                     /* if this is a UDP message send an error message */
                     if(sock->sock_type == SOCKTYPE_UDP)
                     {
                        encap.Status = EIP_ENCAPSTATUSERR_COMMAND;
                        eipc_encap_unSupEncapMsg(&encap, sock);
                     }

                     /* valid for TCP connections only */
                     else
                        eipc_encap_RegisterSession(&encap,sock);
                     break;

                  /* ************************************************ */
                  /* Encapsulated Command 0x0066: "UnRegisterSession" */
                  /* ************************************************ */
                  case EIP_ENCAPCMD_UNREGISTERSESSION:
                     /* if this is a UDP message send an error message */
                     if(sock->sock_type == SOCKTYPE_UDP)
                     {
                        encap.Status = EIP_ENCAPSTATUSERR_COMMAND;
                        eipc_encap_unSupEncapMsg(&encap, sock);
                     }

                     /* valid for TCP connections only */
                     else
                        eipc_encap_UnregisterSession(&encap,sock);
                     break;

                  /* ***************************************** */
                  /* Unsupported Command - Send Error Response */       
                  /* ***************************************** */
                  default:
                     encap.Status = EIP_ENCAPSTATUSERR_COMMAND;
                     eipc_encap_unSupEncapMsg(&encap, sock);
            	      break;
               } /* END-> "switch (encap.Command) */
            } /* END-> "if(encap.Status == 0) */

            /* return_val is the number of bytes left in the buffer once the
               message is processed */
            return_val = msg_siz - (encap_length + EIP_ENCAP_HEADER_SIZ);
            msg_siz = return_val;
            
            /* remove the message */
            rta_ByteMove (msg, msg+(encap_length + EIP_ENCAP_HEADER_SIZ), return_val);

            /* we don't have any more messages to process */
            if(return_val == 0)
               done_flag = TRUE;

         } /* END-> "We have a valid message" */
      } /* END-> "Message Size should be EIP_ENCAP_HEADER_SIZ + encap.Length" */
   } /* END-> "while (done_flag == FALSE)" */

   /* UDP messages must be received in one message */
   if(sock->sock_type == SOCKTYPE_UDP)
      return(0);

   /* TCP messages return the offset to store the next block of data */
   return(return_val);

} /* END-> "EIPProcess()" */

/* ====================================================================
Function:       eipc_encap_unSupEncapMsg
Parameters:     Encapsulated message structure
                socket structure pointer
Returns:        N/A

This function builds an error message to transmit over the encapsulated
layer.
======================================================================= */
void eipc_encap_unSupEncapMsg(EIPC_ENCAP_MSG_STRUCT *EncapReq, EIPC_SOCKET_STRUCT *sock)
{
   uint8 resp_msg[EIP_ENCAP_HEADER_SIZ], i;
   int16 resp_msg_siz;

   /* Error response size is fixed */
   EncapReq->Length = 0;
   resp_msg_siz = EIP_ENCAP_HEADER_SIZ;

   /* build the response message */
   rta_PutLitEndian16(EncapReq->Command,       resp_msg+0);
   rta_PutLitEndian16(EncapReq->Length,        resp_msg+2);
   rta_PutLitEndian32(EncapReq->SessionHandle, resp_msg+4);
   rta_PutLitEndian32(EncapReq->Status,        resp_msg+8);
   for(i=0; i<8; i++)
      resp_msg[12+i] = EncapReq->SenderContext[i];
   rta_PutLitEndian32(EncapReq->Options,       resp_msg+20);

   eipc_usersock_sendData (sock->sock_id, resp_msg, resp_msg_siz);
}

/**/
/* ====================================================================
Function:       eipc_encap_Nop
Parameters:     Encapsulated message structure
                socket structure pointer
Returns:        N/A

This function processes the Nop command code.

The Nop command code response: No Response
======================================================================= */
void eipc_encap_Nop(EIPC_ENCAP_MSG_STRUCT *EncapReq, EIPC_SOCKET_STRUCT *sock)
{
   /*
   ==================
   REQUEST VALIDATION
   ==================

   FIELD NAME         FIElD VALUE
   ----------         -----------
   Command            NOP (0x00)
   Length             0 to 65511
   Session Handle     Don't Care
   Status             shall be 0
   Sender Context     Ignored (since no reply)
   Options            shall be 0
   Encapsulated Data  No Data
   */

   /* use EncapReq to keep compiler happy */
   if(EncapReq) {}

   /* use sock to keep compiler happy */
   if(sock) {}
}

/* ====================================================================
Function:       eipc_encap_ListServices
Parameters:     Encapsulated message structure
                socket structure pointer
Returns:        N/A

This function processes the ListServices command code.

The ListServices command code response:
  ----------------------------------------------------------------------
 |  FIELD NAME       |        TYPE          |      DESCRIPTION          |
 |----------------------------------------------------------------------|
 | Item Count        | UINT16               | Always 0x0001             |
 |----------------------------------------------------------------------|
 | Item Code         | UINT16               | Always 0x0100             |
 |----------------------------------------------------------------------|
 | Item Length       | UINT16               | Always 0x0014             |
 |----------------------------------------------------------------------|
 | Item Data         | ARRAY[20] OF UINT8   |                           |
 | ==================  =====================  ========================= |
 | Protocol Version  | ItemData[0] -  [1]   | Always 0x0001             |
 | Capability Flags  | ItemData[2] -  [3]   | Always 0x0120             |
 | Name              | ItemData[4] - [19]   | Name String (NULL TERM)   |
  ----------------------------------------------------------------------
======================================================================= */
void eipc_encap_ListServices(EIPC_ENCAP_MSG_STRUCT *EncapReq, EIPC_SOCKET_STRUCT *sock)
{
   uint8 resp_msg[(EIP_ENCAP_HEADER_SIZ+26)];
   int16 resp_msg_siz, i;

   /*
   ==================
   REQUEST VALIDATION
   ==================

   FIELD NAME         FIElD VALUE
   ----------         -----------
   Command            ListServices (0x0004)
   Length             shall be 0
   Session Handle     Don't Care
   Status             shall be 0
   Sender Context     Don't Care
   Options            shall be 0
   Encapsulated Data  No Data
   */

   /* Session Handle Don't Care */

   /* Valid Length = 0 */
   if (EncapReq->Length != 0)
   {
      EncapReq->Status = EIP_ENCAPSTATUSERR_LENGTH;
      eipc_encap_unSupEncapMsg(EncapReq, sock);
      return; /* Stop this function on an error */
   }

   /* Response size is fixed */
   EncapReq->Length = 26;
   resp_msg_siz = EIP_ENCAP_HEADER_SIZ; /* incremented as response is built */

   /* build the response message */
   rta_PutLitEndian16(EncapReq->Command,       resp_msg+0);
   rta_PutLitEndian16(EncapReq->Length,        resp_msg+2);
   rta_PutLitEndian32(EncapReq->SessionHandle, resp_msg+4);
   rta_PutLitEndian32(EncapReq->Status,        resp_msg+8);
   for(i=0; i<8; i++)
      resp_msg[12+i] = EncapReq->SenderContext[i];
   rta_PutLitEndian32(EncapReq->Options,       resp_msg+20);

   /* ****************************** */
   /* Build the rest of the response */
   /* ****************************** */

   /* CPF Data - Item Count (always 0x0001) */
   rta_PutLitEndian16(0x0001, resp_msg + resp_msg_siz);
   resp_msg_siz += 2; /* advance the count by the 2 bytes added */

   /* CPF Data - Item Type Code (always 0x0100) */
   rta_PutLitEndian16(0x0100, resp_msg + resp_msg_siz);
   resp_msg_siz += 2; /* advance the count by the 2 bytes added */

   /* CPF Data - Item Length (always 0x0014) */
   rta_PutLitEndian16(0x0014, resp_msg + resp_msg_siz);
   resp_msg_siz += 2; /* advance the count by the 2 bytes added */

   /* CPF Data - Item Data - Protocol Version (always 0x0001) */
   rta_PutLitEndian16(0x0001, resp_msg + resp_msg_siz);
   resp_msg_siz += 2; /* advance the count by the 2 bytes added */

   /* CPF Data - Item Data - Capablities Flags */
   rta_PutLitEndian16(EIP_LIST_SERVICES_CAP_FLAGS, resp_msg + resp_msg_siz);
   resp_msg_siz += 2; /* advance the count by the 2 bytes added */

   /* CPF Data - Item Data - Socket Address - Name (always "Communications " */
   resp_msg[resp_msg_siz++] = 'C';
   resp_msg[resp_msg_siz++] = 'o';
   resp_msg[resp_msg_siz++] = 'm';
   resp_msg[resp_msg_siz++] = 'm';
   resp_msg[resp_msg_siz++] = 'u';
   resp_msg[resp_msg_siz++] = 'n';
   resp_msg[resp_msg_siz++] = 'i';
   resp_msg[resp_msg_siz++] = 'c';
   resp_msg[resp_msg_siz++] = 'a';
   resp_msg[resp_msg_siz++] = 't';
   resp_msg[resp_msg_siz++] = 'i';
   resp_msg[resp_msg_siz++] = 'o';
   resp_msg[resp_msg_siz++] = 'n';
   resp_msg[resp_msg_siz++] = 's';
   resp_msg[resp_msg_siz++] = ' ';
   resp_msg[resp_msg_siz++] = 0x00;

   /* send message */
   eipc_usersock_sendData (sock->sock_id, resp_msg, resp_msg_siz);
}

/* ====================================================================
Function:       eipc_encap_ListIdentity
Parameters:     Encapsulated message structure
                socket structure pointer
Returns:        N/A

This function processes the ListServices command code.

The ListIdentity command code response:
  ----------------------------------------------------------------------
 |  FIELD NAME       |        TYPE          |      DESCRIPTION          |
 |----------------------------------------------------------------------|
 | Item Count        | UINT16               | Always 0x0001             |
 |----------------------------------------------------------------------|
 | Item Code         | UINT16               | Always 0x000C             |
 |----------------------------------------------------------------------|
 | Item Length       | UINT16               | Varies                    |
 |----------------------------------------------------------------------|
 | Item Data         | Varies               | Varies                    |
  ----------------------------------------------------------------------
======================================================================= */
void eipc_encap_ListIdentity(EIPC_ENCAP_MSG_STRUCT *EncapReq, EIPC_SOCKET_STRUCT *sock)
{
   uint8 resp_msg[(EIP_ENCAP_HEADER_SIZ + 40 + EIPC_USER_IDOBJ_NAME_SIZE)];
   int16 resp_msg_siz, i;

   /*
   ==================
   REQUEST VALIDATION
   ==================

   FIELD NAME         FIElD VALUE
   ----------         -----------
   Command            ListIdentity (0x63)
   Length             shall be 0
   Session Handle     Don't Care
   Status             shall be 0
   Sender Context     Don't Care
   Options            shall be 0
   Encapsulated Data  No Data
   */

   /* Session Handle Don't Care */

   /* Valid Length = 0 */
   if (EncapReq->Length != 0)
   {
      EncapReq->Status = EIP_ENCAPSTATUSERR_LENGTH;
      eipc_encap_unSupEncapMsg(EncapReq, sock);
      return; /* Stop this function on an error */
   }

   /* Response size is fixed */
   EncapReq->Length = (40 + EIPC_USER_IDOBJ_NAME_SIZE);
   resp_msg_siz = EIP_ENCAP_HEADER_SIZ; /* incremented as response is built */

   /* build the response message */
   rta_PutLitEndian16(EncapReq->Command,       resp_msg+0);
   rta_PutLitEndian16(EncapReq->Length,        resp_msg+2);
   rta_PutLitEndian32(EncapReq->SessionHandle, resp_msg+4);
   rta_PutLitEndian32(EncapReq->Status,        resp_msg+8);
   for(i=0; i<8; i++)
      resp_msg[12+i] = EncapReq->SenderContext[i];
   rta_PutLitEndian32(EncapReq->Options,       resp_msg+20);

   /* ****************************** */
   /* Build the rest of the response */
   /* ****************************** */

   /* CPF Data - Item Count (always 0x0001) */
   rta_PutLitEndian16(0x0001, resp_msg + resp_msg_siz);
   resp_msg_siz += 2; /* advance the count by the 2 bytes added */

   /* CPF Data - Item Type Code (always 0x000C) */
   rta_PutLitEndian16(0x000C, resp_msg + resp_msg_siz);
   resp_msg_siz += 2; /* advance the count by the 2 bytes added */

   /* CPF Data - Item Length */
   rta_PutLitEndian16((uint16)(34 + EIPC_USER_IDOBJ_NAME_SIZE), resp_msg + resp_msg_siz);
   resp_msg_siz += 2; /* advance the count by the 2 bytes added */

   /* CPF Data - Item Data - Protocol Version */
   rta_PutLitEndian16(0x0001, resp_msg + resp_msg_siz);
   resp_msg_siz += 2; /* advance the count by the 2 bytes added */

   /* CPF Data - Item Data - Socket Address - sin_family (big-endian) (always 0x0002)*/
   resp_msg[resp_msg_siz++] = 0x00;
   resp_msg[resp_msg_siz++] = 0x02;   

   /* CPF Data - Item Data - Socket Address - sin_port (big-endian) (always 0xAF12) */
   resp_msg[resp_msg_siz++] = 0xaf;
   resp_msg[resp_msg_siz++] = 0x12;      

   /* CPF Data - Item Data - Socket Address - sin_addr (big-endian) (our IP address) */
   rta_PutBigEndian32(eipc_usersock_getOurIPAddr (), resp_msg + resp_msg_siz);   
   resp_msg_siz += 4; /* advance the count by the 4 bytes added */

   /* CPF Data - Item Data - Socket Address - sin_zero (len 8) (big-endian) */
   for(i=0; i<8; i++)
      resp_msg[resp_msg_siz++] = 0;

   /* CPF Data - Item Data - Vendor ID */
   rta_PutLitEndian16(EIPC_USER_IDOBJ_VENDORID, resp_msg + resp_msg_siz);
   resp_msg_siz += 2; /* advance the count by the 2 bytes added */

   /* CPF Data - Item Data - Device Type */
   rta_PutLitEndian16(EIPC_USER_IDOBJ_DEVTYPE, resp_msg + resp_msg_siz);
   resp_msg_siz += 2; /* advance the count by the 2 bytes added */

   /* CPF Data - Item Data - Product Code */
   rta_PutLitEndian16(EIPC_USER_IDOBJ_PRODCODE, resp_msg + resp_msg_siz);
   resp_msg_siz += 2; /* advance the count by the 2 bytes added */

   /* CPF Data - Item Data - Revision */
   rta_PutLitEndian16(EIPC_REVISION, resp_msg + resp_msg_siz);
   resp_msg_siz += 2; /* advance the count by the 2 bytes added */

   /* CPF Data - Item Data - Status */
   rta_PutLitEndian16(0, resp_msg + resp_msg_siz);
   resp_msg_siz += 2; /* advance the count by the 2 bytes added */

   /* CPF Data - Item Data - Serial Number */
   rta_PutLitEndian32(eipc_userobj_getSerialNumber(), resp_msg + resp_msg_siz);
   resp_msg_siz += 4; /* advance the count by the 4 bytes added */

   /* CPF Data - Item Data - Product Name Size */
   resp_msg[resp_msg_siz++] = EIPC_USER_IDOBJ_NAME_SIZE;

   /* CPF Data - Item Data - Product Name */
   for(i=0; i<EIPC_USER_IDOBJ_NAME_SIZE; i++)
     resp_msg[resp_msg_siz++] = EIPC_USER_IDOBJ_NAME[i];

   /* CPF Data - Item Data - State */
   resp_msg[resp_msg_siz++] = 0xFF;

   /* send message */
   eipc_usersock_sendData (sock->sock_id, resp_msg, resp_msg_siz);
}

/* ====================================================================
Function:       eipc_encap_RegisterSession
Parameters:     Encapsulated message structure
                socket structure pointer
Returns:        N/A

This function processes the RegisterSession command code.

The RegisterSession command code response: See Below
======================================================================= */
void eipc_encap_RegisterSession(EIPC_ENCAP_MSG_STRUCT *EncapReq, EIPC_SOCKET_STRUCT *sock)
{
   uint8 resp_msg[EIP_ENCAP_HEADER_SIZ+4], i;
   int16 resp_msg_siz;
   int16 session_ix;
   uint16 prot_ver, opt_flags;

   /*
   ==================
   REQUEST VALIDATION
   ==================

   FIELD NAME         FIElD VALUE
   ----------         -----------
   Command            RegisterSession (0x65)
   Length             4 Bytes of Data
   Session Handle     shall be 0
   Status             shall be 0
   Sender Context     Don't Care
   Options            shall be 0
   Encapsulated Data  Protocol Version (2 bytes)
                      Options flags (2 bytes)
   */

   /*
   ===============
   RESPONSE FORMAT
   ===============

   FIELD NAME         FIElD VALUE
   ----------         -----------
   Command            RegisterSession (0x65)
   Length             4 Bytes of Data
   Session Handle     SET BY US
   Status             shall be 0
   Sender Context     all 0's
   Options            shall be 0
   Encapsulated Data  0x0100 Protocol Version (2 bytes LSB MSB)
                      0x0000 Options flags (2 bytes LSB MSB)
   */

   /* Session Handle Don't Care */

   /* Valid Length = 4 */
   if (EncapReq->Length != 4)
   {
      EncapReq->Status = EIP_ENCAPSTATUSERR_LENGTH;
      eipc_encap_unSupEncapMsg(EncapReq, sock);
      return;
   }

   /* Validate Protocol Version should be the current version, options should be 0 */
   prot_ver = rta_GetLitEndian16(EncapReq->EncapsulatedData);
   opt_flags = rta_GetLitEndian16(EncapReq->EncapsulatedData+2);
   if( (prot_ver != EIP_ENCAP_PROT_VER) || (opt_flags != 0))
   {
      EncapReq->Status = EIP_ENCAPSTATUSERR_PROTREV;
      eipc_encap_unSupEncapMsg(EncapReq, sock);
      return; /* Stop this function on an error */
   }

   /* Validate we don't already have a Session Handle */
   session_ix = eipc_encap_GetSessionIx(sock->sock_id);
   if(session_ix == -1)
   {
      EncapReq->Status = EIP_ENCAPSTATUSERR_MEMORY;
      eipc_encap_unSupEncapMsg(EncapReq, sock);
      return; /* Stop this function on an error */
   }

   /* Valid Protocol Version */
   EncapReq->SessionHandle = EIP_Sessions[session_ix].SessionHandle;

   /* Error response size is fixed */
   EncapReq->Length = 4;
   resp_msg_siz = (EIP_ENCAP_HEADER_SIZ + EncapReq->Length);

   /* build the response message */
   rta_PutLitEndian16(EncapReq->Command,       resp_msg+0);
   rta_PutLitEndian16(EncapReq->Length,        resp_msg+2);
   rta_PutLitEndian32(EncapReq->SessionHandle, resp_msg+4);
   rta_PutLitEndian32(EncapReq->Status,        resp_msg+8);
   for(i=0; i<8; i++)
      resp_msg[12+i] = EncapReq->SenderContext[i];
   rta_PutLitEndian32(EncapReq->Options,       resp_msg+20);
   for(i=0; i<4; i++)
      resp_msg[24+i] = EncapReq->EncapsulatedData[i];

   eipc_usersock_sendData (sock->sock_id, resp_msg, resp_msg_siz);
}

/**/
/* ====================================================================
Function:       eipc_encap_UnregisterSession
Parameters:     Encapsulated message structure
                socket structure pointer
Returns:        N/A

This function processes the UnRegisterSession command code.

The eipc_encap_UnregisterSession command code response: No Response
======================================================================= */
void eipc_encap_UnregisterSession(EIPC_ENCAP_MSG_STRUCT *EncapReq, EIPC_SOCKET_STRUCT *sock)
{
   int16 session_ix;

   /*
   ==================
   REQUEST VALIDATION
   ==================

   FIELD NAME         FIElD VALUE
   ----------         -----------
   Command            UnRegisterSession (0x66)
   Length             shall be 0
   Session Handle     match ours
   Status             shall be 0
   Sender Context     Don't Care
   Options            shall be 0
   Encapsulated Data  No Data
   */

   /* Validate the Session Handle (-1 on Error) */
   session_ix = eipc_encap_SessionFind(sock->sock_id);
   if(session_ix == -1)
   {
      eipc_user_dbprint1("Invalid Session Close %08lx \r\n", EncapReq->SessionHandle);
      return; /* Stop this function on an error */
   }

   /* No Response */
   eipc_usersock_tcpClose(sock->sock_id);

   if(EncapReq){} /* keep compiler happy */
}

/* ====================================================================
Function:       eipc_encap_ListTargets
Parameters:     Encapsulated message structure
                socket structure pointer
Returns:        N/A

This function processes the ListTargets command code.  This function is
only for testing purposes.
======================================================================= */
void eipc_encap_ListTargets (EIPC_ENCAP_MSG_STRUCT *EncapReq, EIPC_SOCKET_STRUCT *sock)
{
   uint8 resp_msg[100], i;
   int16 resp_msg_siz;

   /* Error response size is fixed */
   EncapReq->Length = 0x2A;
   resp_msg_siz = (EIP_ENCAP_HEADER_SIZ + EncapReq->Length);

   /* build the response message */
   rta_PutLitEndian16(EncapReq->Command,       resp_msg+0);
   rta_PutLitEndian16(EncapReq->Length,        resp_msg+2);
   rta_PutLitEndian32(EncapReq->SessionHandle, resp_msg+4);
   rta_PutLitEndian32(EncapReq->Status,        resp_msg+8);
   for(i=0; i<8; i++)
      resp_msg[12+i] = EncapReq->SenderContext[i];
   rta_PutLitEndian32(EncapReq->Options,       resp_msg+20);
   for(i=0; i<4; i++)
      resp_msg[24+i] = EncapReq->EncapsulatedData[i];

   /* Build the rest of the response */
   resp_msg_siz = EIP_ENCAP_HEADER_SIZ;

   /* CPF Data - Item Count (always 1) */
   rta_PutLitEndian16(1, resp_msg+resp_msg_siz);
   resp_msg_siz+=2;

   /* CPF Data - Item Code (always 1) */
   rta_PutLitEndian16(1, resp_msg+resp_msg_siz);
   resp_msg_siz+=2;

   /* CPF Data - Item Length (always 0x24) */
   rta_PutLitEndian16(0x24, resp_msg+resp_msg_siz);
   resp_msg_siz+=2;

   /* CPF Data - Item Data - Protocol Version (always 1) */
   rta_PutLitEndian16(1, resp_msg+resp_msg_siz);
   resp_msg_siz+=2;

   /* CPF Data - Item Data - Capablities Flags (always 0) */
   rta_PutLitEndian16(0, resp_msg+resp_msg_siz);
   resp_msg_siz+=2;

   /* 16 bytes of 0 */
   for(i=0; i<16; i++)
      resp_msg[resp_msg_siz++] = 0;

   /* IP Address "000.000.000.000" */
   resp_msg[resp_msg_siz++] = '0';
   resp_msg[resp_msg_siz++] = '0';
   resp_msg[resp_msg_siz++] = '0';
   resp_msg[resp_msg_siz++] = '.';
   resp_msg[resp_msg_siz++] = '0';
   resp_msg[resp_msg_siz++] = '0';
   resp_msg[resp_msg_siz++] = '0';
   resp_msg[resp_msg_siz++] = '.';
   resp_msg[resp_msg_siz++] = '0';
   resp_msg[resp_msg_siz++] = '0';
   resp_msg[resp_msg_siz++] = '0';
   resp_msg[resp_msg_siz++] = '.';
   resp_msg[resp_msg_siz++] = '0';
   resp_msg[resp_msg_siz++] = '0';
   resp_msg[resp_msg_siz++] = '0';
   resp_msg[resp_msg_siz++] = 0;

   /* send the response */
   eipc_usersock_sendData (sock->sock_id, resp_msg, resp_msg_siz);
}

/* *********** */
/* END OF FILE */
/* *********** */
