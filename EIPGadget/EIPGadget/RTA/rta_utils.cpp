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
 *     Module Name: rta_utils.c
 *          Author: Jamin D. Wendorf (jwendorf@rtaautomation.com)
 *        Language: Ansi C
 * Compile Options: N/A
 * Compile defines: N/A
 *       Libraries: N/A
 *    Link Options: N/A
 *
 * Description.
 * ====================================================================
 * This file contains useful memory manipulation functions.
 *
 */

/*------------------------------*/
/* INCLUDE FILES                */
/*------------------------------*/
#include "eipc_system.h"

/************************************************************************/
/*  GLOBAL FUNCTIONS (all must be re-entrant)                           */
/************************************************************************/
/* ====================================================================
Function:     rta_ByteMove
Parameters:   destination pointer
              source pointer
              length of bytes to move
Returns:      N/A

This function moves n bytes from the src pointer to the destination
pointer.
======================================================================= */
void rta_ByteMove (uint8 *dst, uint8 *src, uint16 len)
{
   uint16 i;

   for(i=0; i<len; i++)
      dst[i] = src[i];
}

/*=======================================================================
Function:   rta_PutBigEndian16
Parameters: 16 bit number to store
            pointer to where to store the Big-Endian data
Returns:    N/A

This function stores the passed value (in Big-Endian) to the location
pointed to by the passed pointer.
=========================================================================*/
void rta_PutBigEndian16 (uint16 value, uint8 *pos)
{
   /* Big-Endian */
   #ifdef RTA_BIG_ENDIAN
      pos[0] = (uint8)((value>>0) & 0x00FF);
      pos[1] = (uint8)((value>>8) & 0x00FF);

   /* Little-Endian */
   #else
      pos[0] = (uint8)((value>>8) & 0x00FF);
      pos[1] = (uint8)((value>>0) & 0x00FF);
   #endif
}

/*=======================================================================
Function:   rta_PutBigEndian32
Parameters: 32 bit number to store
            pointer to where to store the Big-Endian data
Returns:    N/A

This function stores the passed value (in Big-Endian) to the location
pointed to by the passed pointer.
=========================================================================*/
void rta_PutBigEndian32 (uint32 value, uint8 *pos)
{
   /* Big-Endian */
   #ifdef RTA_BIG_ENDIAN
      pos[0] = (uint8)((value>> 0) & 0x000000FFL);
      pos[1] = (uint8)((value>> 8) & 0x000000FFL);
      pos[2] = (uint8)((value>>16) & 0x000000FFL);
      pos[3] = (uint8)((value>>24) & 0x000000FFL);

   /* Little-Endian */
   #else
      pos[3] = (uint8)((value>> 0) & 0x000000FFL);
      pos[2] = (uint8)((value>> 8) & 0x000000FFL);
      pos[1] = (uint8)((value>>16) & 0x000000FFL);
      pos[0] = (uint8)((value>>24) & 0x000000FFL);
   #endif
}

/*=======================================================================
Function:   rta_PutBigEndianFloat
Parameters: floating point value
            pointer to where to store the Big-Endian data
Returns:    N/A

This function stores the passed value (in Big-Endian) to the location
pointed to by the passed pointer.
=========================================================================*/
void rta_PutBigEndianFloat (float value, uint8 *pos)
{
   uint32 longtemp;

   rta_ByteMove (((uint8 *)&longtemp), ((uint8 *)&value), 4);

   /* Big-Endian */
   #ifdef RTA_BIG_ENDIAN
      pos[0] = (uint8)((longtemp>> 0) & 0x000000FFL);
      pos[1] = (uint8)((longtemp>> 8) & 0x000000FFL);
      pos[2] = (uint8)((longtemp>>16) & 0x000000FFL);
      pos[3] = (uint8)((longtemp>>24) & 0x000000FFL);

   /* Little-Endian */
   #else
      pos[3] = (uint8)((longtemp>> 0) & 0x000000FFL);
      pos[2] = (uint8)((longtemp>> 8) & 0x000000FFL);
      pos[1] = (uint8)((longtemp>>16) & 0x000000FFL);
      pos[0] = (uint8)((longtemp>>24) & 0x000000FFL);
   #endif
}

/*=======================================================================
Function:   rta_rta_GetBigEndian16
Parameters: pointer where the Big-Endian data is stored
Returns:    16 bit number

This function returns the value (in Big-Endian) of the passed pointer.
=========================================================================*/
uint16 rta_GetBigEndian16 (uint8 *pos)
{
   uint16 return_val;

   /* Big-Endian */
   #ifdef RTA_BIG_ENDIAN
      return_val = pos[1];
      return_val = (return_val << 8) | pos[0];

   /* Little-Endian */
   #else
      return_val = pos[0];
      return_val = (return_val << 8) | pos[1];
   #endif

   return(return_val);
}

/*=======================================================================
Function:   rta_GetBigEndian32
Parameters: pointer where the Big-Endian data is stored
Returns:    32 bit number

This function returns the value (in Big-Endian) of the passed pointer.
=========================================================================*/
uint32 rta_GetBigEndian32 (uint8 *pos)
{
   uint32 return_val;

   /* Big-Endian */
   #ifdef RTA_BIG_ENDIAN
      return_val = pos[3];
      return_val = (return_val << 8) | pos[2];
      return_val = (return_val << 8) | pos[1];
      return_val = (return_val << 8) | pos[0];

   /* Little-Endian */
   #else
      return_val = pos[0];
      return_val = (return_val << 8) | pos[1];
      return_val = (return_val << 8) | pos[2];
      return_val = (return_val << 8) | pos[3];
   #endif

   return(return_val);
}

/*=======================================================================
Function:   rta_GetBigEndianFloat
Parameters: pointer where the Big-Endian data is stored
Returns:    floating point number

This function returns the value (in Big-Endian) of the passed pointer.
=========================================================================*/
float rta_GetBigEndianFloat (uint8 *pos)
{
   float return_val;
   uint32 longtemp;

   /* Big-Endian */
   #ifdef RTA_BIG_ENDIAN
      longtemp = pos[3];
      longtemp = (longtemp << 8) | pos[2];
      longtemp = (longtemp << 8) | pos[1];
      longtemp = (longtemp << 8) | pos[0];

   /* Little-Endian */
   #else
      longtemp = pos[0];
      longtemp = (longtemp << 8) | pos[1];
      longtemp = (longtemp << 8) | pos[2];
      longtemp = (longtemp << 8) | pos[3];
   #endif

   rta_ByteMove (((uint8 *)&return_val), ((uint8 *)&longtemp), 4);
   return(return_val);
}

/*=======================================================================
Function:   rta_PutLitEndian16
Parameters: 16 bit number to store
            pointer to where to store the Little-Endian data
Returns:    N/A

This function stores the passed value (in Little-Endian) to the location
pointed to by the passed pointer.
=========================================================================*/
void rta_PutLitEndian16 (uint16 value, uint8 *pos)
{
   /* Big-Endian */
   #ifdef RTA_BIG_ENDIAN
      pos[1] = (uint8)((value>>0) & 0x00FF);
      pos[0] = (uint8)((value>>8) & 0x00FF);

   /* Little-Endian */
   #else
      pos[0] = (uint8)((value>>0) & 0x00FF);
      pos[1] = (uint8)((value>>8) & 0x00FF);
   #endif
}

/*=======================================================================
Function:   rta_PutLitEndian32
Parameters: 32 bit number to store
            pointer to where to store the Little-Endian data
Returns:    N/A

This function stores the passed value (in Little-Endian) to the location
pointed to by the passed pointer.
=========================================================================*/
void rta_PutLitEndian32 (uint32 value, uint8 *pos)
{
   /* Big-Endian */
   #ifdef RTA_BIG_ENDIAN
      pos[3] = (uint8)((value>> 0) & 0x000000FFL);
      pos[2] = (uint8)((value>> 8) & 0x000000FFL);
      pos[1] = (uint8)((value>>16) & 0x000000FFL);
      pos[0] = (uint8)((value>>24) & 0x000000FFL);

   /* Little-Endian */
   #else
      pos[0] = (uint8)((value>> 0) & 0x000000FFL);
      pos[1] = (uint8)((value>> 8) & 0x000000FFL);
      pos[2] = (uint8)((value>>16) & 0x000000FFL);
      pos[3] = (uint8)((value>>24) & 0x000000FFL);
   #endif
}

/*=======================================================================
Function:   rta_PutLitEndianFloat
Parameters: floating point value
            pointer to where to store the Little-Endian data
Returns:    N/A

This function stores the passed value (in Little-Endian) to the location
pointed to by the passed pointer.
=========================================================================*/
void rta_PutLitEndianFloat (float value, uint8 *pos)
{
   uint32 longtemp;

   rta_ByteMove (((uint8 *)&longtemp), ((uint8 *)&value), 4);

   /* Big-Endian */
   #ifdef RTA_BIG_ENDIAN
      pos[3] = (uint8)((longtemp>> 0) & 0x000000FFL);
      pos[2] = (uint8)((longtemp>> 8) & 0x000000FFL);
      pos[1] = (uint8)((longtemp>>16) & 0x000000FFL);
      pos[0] = (uint8)((longtemp>>24) & 0x000000FFL);

   /* Little-Endian */
   #else
      pos[0] = (uint8)((longtemp>> 0) & 0x000000FFL);
      pos[1] = (uint8)((longtemp>> 8) & 0x000000FFL);
      pos[2] = (uint8)((longtemp>>16) & 0x000000FFL);
      pos[3] = (uint8)((longtemp>>24) & 0x000000FFL);
   #endif
}

/*=======================================================================
Function:   rta_GetLitEndian16
Parameters: pointer where the Little-Endian data is stored
Returns:    16 bit number

This function returns the value (in Little-Endian) of the passed pointer.
=========================================================================*/
uint16 rta_GetLitEndian16 (uint8 *pos)
{
   uint16 return_val;

   /* Big-Endian */
   #ifdef RTA_BIG_ENDIAN
      return_val = pos[0];
      return_val = (return_val << 8) | pos[1];

   /* Little-Endian */
   #else
      return_val = pos[1];
      return_val = (return_val << 8) | pos[0];
   #endif

   return(return_val);
}

/*=======================================================================
Function:   rta_GetLitEndian32
Parameters: pointer where the Little-Endian data is stored
Returns:    32 bit number

This function returns the value (in Little-Endian) of the passed pointer.
=========================================================================*/
uint32 rta_GetLitEndian32 (uint8 *pos)
{
   uint32 return_val;

   /* Big-Endian */
   #ifdef RTA_BIG_ENDIAN
      return_val = pos[0];
      return_val = (return_val << 8) | pos[1];
      return_val = (return_val << 8) | pos[2];
      return_val = (return_val << 8) | pos[3];

   /* Little-Endian */
   #else
      return_val = pos[3];
      return_val = (return_val << 8) | pos[2];
      return_val = (return_val << 8) | pos[1];
      return_val = (return_val << 8) | pos[0];
   #endif

   return(return_val);
}

/*=======================================================================
Function:   rta_GetLitEndianFloat
Parameters: pointer where the Little-Endian data is stored
Returns:    floating point number

This function returns the value (in Little-Endian) of the passed pointer.
=========================================================================*/
float rta_GetLitEndianFloat (uint8 *pos)
{
   float return_val;
   uint32 longtemp;

   /* Big-Endian */
   #ifdef RTA_BIG_ENDIAN
      longtemp = pos[0];
      longtemp = (longtemp << 8) | pos[1];
      longtemp = (longtemp << 8) | pos[2];
      longtemp = (longtemp << 8) | pos[3];

   /* Little-Endian */
   #else
      longtemp = pos[3];
      longtemp = (longtemp << 8) | pos[2];
      longtemp = (longtemp << 8) | pos[1];
      longtemp = (longtemp << 8) | pos[0];
   #endif

   rta_ByteMove (((uint8 *)&return_val), ((uint8 *)&longtemp), 4);
   return(return_val);
}

/* *********** */
/* END OF FILE */
/* *********** */
