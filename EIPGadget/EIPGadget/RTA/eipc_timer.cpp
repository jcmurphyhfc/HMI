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
 *     Module Name: eipc_timer.c
 *          Author: Jamin D. Wendorf (jwendorf@rtaautomation.com)
 *        Language: Ansi C
 * Compile Options: N/A
 * Compile defines: N/A
 *       Libraries: N/A
 *    Link Options: N/A
 *
 * Description.
 * ====================================================================
 * This file contains the timer subsystem.
 *
 */

/* ---------------------------- */
/* INCLUDE FILES                */
/* ---------------------------- */
#include "eipc_system.h"

/* ---------------------------- */
/* FUNCTION PROTOTYPES          */
/* ---------------------------- */
void EIPC_UpdateTimerIxTable (void);

/* ---------------------------- */
/* STATIC VARIABLES             */
/* ---------------------------- */
EIPC_TIMER_STRUCT EIPC_Timers[EIPC_USER_MAX_NUM_TIMERS];
uint16 EIPC_UsedTimerIx[EIPC_USER_MAX_NUM_TIMERS];
uint16 EIPC_NumTimerIxUsed;

/* ---------------------------- */
/* MISCELLANEOUS                */
/* ---------------------------- */
#define EIPC_TIM_STATE_STOPPED 0
#define EIPC_TIM_STATE_RUNNING 1
#define EIPC_TIM_STATE_TIMEOUT 2

/**/
/* ******************************************************************** */
/*                      GLOBAL FUNCTIONS                                */
/* ******************************************************************** */
/* ====================================================================
Function:    eipc_timer_init
Parameters:  init type
Returns:     N/A

This function initializes static variables used by this file.
======================================================================= */
void eipc_timer_init (uint8 init_type)
{
    uint16 i;

    memset(&EIPC_Timers, 0, sizeof(EIPC_Timers));
    memset(&EIPC_UsedTimerIx, 0, sizeof(EIPC_UsedTimerIx));

    /* initialize all the timers */
    for(i=1; i<EIPC_USER_MAX_NUM_TIMERS; i++)
    {
        eipc_timer_free(i);
    }

    /* keep track of how many timers are used */
    EIPC_NumTimerIxUsed = 0;

    if(init_type) {} // keep the compiler happy
}

/* ====================================================================
Function:    eipc_timer_new
Parameters:  N/A
Returns:     N/A

This function searches for the next unused timer.  If all the timers
are used, EIPC_TIMER_NULL is returned.
======================================================================= */
uint16 eipc_timer_new (void)
{
   uint16 i;

   /* Make sure we have free timers */
   if(EIPC_NumTimerIxUsed == EIPC_USER_MAX_NUM_TIMERS)
      return(EIPC_TIMER_NULL);

   /* search through all timers for a free one */
   for(i=1; i<EIPC_USER_MAX_NUM_TIMERS; i++)
   {
      /* we found a free timer, use it */
      if(EIPC_Timers[i].owned == FALSE)
      {
         /* mark the timer as used */
         EIPC_Timers[i].owned = TRUE;

         /* update the table of used indexes */
         EIPC_UpdateTimerIxTable();

         /* return the timer number */
         return(i);
      }
   }

   /* no timers are free */
   return(EIPC_TIMER_NULL);
}

/* ====================================================================
Function:    eipc_timer_free
Parameters:  timer number
Returns:     N/A

This function validates the timer number, then frees the timer to
unused.
======================================================================= */
void eipc_timer_free (uint16 timer_num)
{
   /* validate timer_num is in range */
   if((timer_num == 0) || (timer_num >= EIPC_USER_MAX_NUM_TIMERS))
      return;

   /* only free the timer if it is owned */
   if(EIPC_Timers[timer_num].owned == TRUE)
   {
      /* free the timer */
      EIPC_Timers[timer_num].owned = FALSE;
      EIPC_Timers[timer_num].state = EIPC_TIM_STATE_STOPPED;
      EIPC_Timers[timer_num].timer_data.current_value = 0;
      EIPC_Timers[timer_num].timer_data.reload_value  = 0;
      EIPC_Timers[timer_num].timer_data.timeout_flag_ptr = NULL;
      EIPC_Timers[timer_num].timer_data.timeout_func_ptr = NULL;
   }
}

/* ====================================================================
Function:    eipc_timer_reset
Parameters:  timer number
Returns:     N/A

This function validates the timer number, then sets the current value
to the reload value.
======================================================================= */
void eipc_timer_reset (uint16 timer_num)
{
   /* validate timer_num is in range */
   if((timer_num == 0) || (timer_num >= EIPC_USER_MAX_NUM_TIMERS))
      return;

   /* only reset the timer if it is owned */
   if(EIPC_Timers[timer_num].owned == TRUE)
   {
      /* set the current value to the reload value */
      EIPC_Timers[timer_num].timer_data.current_value = EIPC_Timers[timer_num].timer_data.reload_value;

      /* set the state back to running */
      EIPC_Timers[timer_num].state = EIPC_TIM_STATE_RUNNING;
   }
}

/* ====================================================================
Function:    eipc_timer_start
Parameters:  timer number
Returns:     N/A

This function validates the timer number, then starts the timer.
======================================================================= */
void eipc_timer_start (uint16 timer_num)
{
   /* validate timer_num is in range */
   if((timer_num == 0) || (timer_num >= EIPC_USER_MAX_NUM_TIMERS))
      return;

   /* only start the timer if it is owned */
   if(EIPC_Timers[timer_num].owned == TRUE)
   {
      /* set the state back to running */
      EIPC_Timers[timer_num].state = EIPC_TIM_STATE_RUNNING;
   }
}

/* ====================================================================
Function:    eipc_timer_stop
Parameters:  timer number
Returns:     N/A

This function validates the timer number, then stops the timer.
======================================================================= */
void eipc_timer_stop (uint16 timer_num)
{
   /* validate timer_num is in range */
   if((timer_num == 0) || (timer_num >= EIPC_USER_MAX_NUM_TIMERS))
      return;

   /* only start the timer if it is owned */
   if(EIPC_Timers[timer_num].owned == TRUE)
   {
      /* set the state back to running */
      EIPC_Timers[timer_num].state = EIPC_TIM_STATE_STOPPED;
   }
}

/* ====================================================================
Function:    eipc_timer_newval
Parameters:  timer number
             new timeout value
Returns:     N/A

This function sets the timeout value to the passed value.
======================================================================= */
void eipc_timer_newval (uint16 timer_num, uint32 newval)
{
   /* validate timer_num is in range */
   if((timer_num == 0) || (timer_num >= EIPC_USER_MAX_NUM_TIMERS))
      return;

   /* only start the timer if it is owned */
   if(EIPC_Timers[timer_num].owned == TRUE)
   {
      /* set the current value to the reload value */
      EIPC_Timers[timer_num].timer_data.current_value = newval;
      EIPC_Timers[timer_num].timer_data.reload_value  = newval;
   }
}

/* ====================================================================
Function:    eipc_timer_get_struct
Parameters:  timer number
Returns:     pointer to the timer data element, NULL on error

This function validates the timer number is valid and owned, then
returns the timer structure.
======================================================================= */
EIPC_TIMER_DATA_STRUCT * eipc_timer_get_struct (uint16 timer_num)
{
   /* validate timer_num is in range */
   if((timer_num == 0) || (timer_num >= EIPC_USER_MAX_NUM_TIMERS))
      return(NULL);

   /* only start the timer if it is owned */
   if(EIPC_Timers[timer_num].owned == TRUE)
   {
      /* set the state back to running */
      return(&EIPC_Timers[timer_num].timer_data);
   }

   /* if the timer isn't owned, return NULL */
   return(NULL);
}

/* ====================================================================
Function:    eipc_timer_process
Parameters:  N/A
Returns:     N/A

This function processes all timers.  Flags are incremented on timeout.
Function pointers are called on timeouts.
======================================================================= */
void eipc_timer_process (uint32 ticks_passed)
{
   uint16 i, timer_ix;

   /* if ticks_passed is 0, return */
   if(ticks_passed == 0)
      return;

   /* only process timers in our lookup table */
   for(i=1; i<EIPC_NumTimerIxUsed; i++)
   {
      /* get the next timer index to access */
      timer_ix = EIPC_UsedTimerIx[i];

      /* only check the timer if it is running */
      if(EIPC_Timers[timer_ix].state == EIPC_TIM_STATE_RUNNING)
      {
         /* see if ticks_passed causes us to transition to timed out */
         if(ticks_passed >= EIPC_Timers[timer_ix].timer_data.current_value)
         {
            /* transition to timed out */
            EIPC_Timers[timer_ix].state = EIPC_TIM_STATE_TIMEOUT;

            /* set the current value to 0 */
            EIPC_Timers[timer_ix].timer_data.current_value = 0;

            /* if available, increment the timeout counter */
            if(EIPC_Timers[timer_ix].timer_data.timeout_flag_ptr != NULL)
            {
               (*EIPC_Timers[timer_ix].timer_data.timeout_flag_ptr)++;
            }

            /* if available call the timeout function pointer */
            if(EIPC_Timers[timer_ix].timer_data.timeout_func_ptr != NULL)
            {
               (*EIPC_Timers[timer_ix].timer_data.timeout_func_ptr)(timer_ix);
            }
         }                                   

         /* we didn't timeout, decrement our current count */
         else
         {
            EIPC_Timers[EIPC_UsedTimerIx[i]].timer_data.current_value -= ticks_passed;
         }
      }
   }
}

/**/
/* ******************************************************************** */
/*                      LOCAL FUNCTIONS                                 */
/* ******************************************************************** */
/* ====================================================================
Function:    EIPC_UpdateTimerIxTable
Parameters:  N/A
Returns:     N/A

A table of used indexes is implemented to shorten the process time for
timers.  Only used indexes are updated in the timer process.
======================================================================= */
void EIPC_UpdateTimerIxTable (void)
{
   uint16 i;

   /* if a timer is used, add it to the table of used indexes */
   for(i=1, EIPC_NumTimerIxUsed = 0; i<EIPC_USER_MAX_NUM_TIMERS; i++)
   {
      /* if a timer is owned, add the index to the table */
      if(EIPC_Timers[i].owned == TRUE)
      {
         /* add the index to the lookup table */
         EIPC_UsedTimerIx[EIPC_NumTimerIxUsed] = i;

         /* increment the number of used indexes */
         EIPC_NumTimerIxUsed++;
      }
   }
}

/* *********** */
/* END OF FILE */
/* *********** */
