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
 *     Module Name: eipc_revision.h
 *          Author: Jamin D. Wendorf (jwendorf@rtaautomation.com)
 *        Language: Ansi C
 * Compile Options: N/A
 * Compile defines: N/A
 *       Libraries: N/A
 *    Link Options: N/A
 *
 * Description.
 * ====================================================================
 * This file contains revision information.
 *
 */

#define EIPC_VERSION_STRING "1.09"
#define EIPC_MAJOR_REV       0x01
#define EIPC_MINOR_REV       0x09
#define EIPC_REVISION        0x0109

/* 
===========================================================================
01/09/2012  REVISION 01.09 (Author: Jamin Wendorf)
===========================================================================
1. Better structure support.

===========================================================================
04/21/2010  REVISION 01.08 (Author: Jamin Wendorf)
===========================================================================
1. Added Class 3 connection support (via #define)
2. Added explicit messaging support

===========================================================================
12/07/2009  REVISION 01.07 (Author: Jamin Wendorf)
===========================================================================
1. Changed ticker function to use timeb instead of time (now we have 
    true millisecond resolution)
2. Changed tag read and write to pass the number of ticks for a  timeout,
    not the number of milliseconds
3. Changed revision information to use RTA's new contact information

===========================================================================
07/23/2009  REVISION 01.06 (Author: Jamin Wendorf)
===========================================================================
1.  Add PCCC support
2.  Add conditional compiling for PCCC and Tag client in eipc_usersys.h
        #define EIPC_TAG_CLIENT_USED    #define EIPC_PCCC_CLIENT_USED

===========================================================================
01/23/2009  REVISION 01.05 (Author: Jamin Wendorf)
===========================================================================
1.  Re-certify with Linux
2.  KDevelop 3.4.1 (Using KDE 3.5.7-1.fc6 Fedora)

===========================================================================
10/16/2007  REVISION 01.04 (Author: Jamin Wendorf)
===========================================================================
1.  Changed structure and array parsing to be generic for reads and writes.
        We now should accept any type of tag name.

===========================================================================
03/22/2007  REVISION 01.03 (Author: Emily Palzewicz)
===========================================================================
1. Updated eipc_tagclient.c so that we accept arrays of structures
Now we support the following situations:
SampleTag
SampleTag[array]
Struct.Tag
Struct.Tag[array]
Struct[Array].Tag
Struct[Array].Tag[Array]
===========================================================================
02/27/2007  REVISION 01.02 (Author: Emily Palzewicz)
===========================================================================
1. Updated eipc_userobj.c to actually parse through the tag name and 
find a period if someone is creating their own User-Defined Tag.
===========================================================================
09/16/2005  REVISION 01.01 (Author: Jamin D. Wendorf)
===========================================================================
1.  Initial Release

*/

