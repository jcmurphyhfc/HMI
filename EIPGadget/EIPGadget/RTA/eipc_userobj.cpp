/*
 *
 * Description.
 * ====================================================================
 * This file contains the user object functions. All functions in this
 * file are the responsibility of the user to write.
 *
 */

/* ---------------------------- */
/* INCLUDE FILES                */
/* ---------------------------- */
#include "eipc_system.h"
#include "EIPCOM.h"

/* ---------------------------- */
/* MISCELLANEOUS                */
/* ---------------------------- */
//#define CL_DATATYPE_STRUCT	0x02A0
/**/
/* ******************************************************************** */
/*                      GLOBAL FUNCTIONS                                */
/* ******************************************************************** */
/* ====================================================================
Function:   eipc_userobj_init
Parameters: init type
Returns:    N/A

This function initializes all static variables used in this file.
======================================================================= */
void eipc_userobj_init (uint8 init_type)
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
Function:   eipc_userobj_process
Parameters: N/A
Returns:    N/A

This function performs any user object processing.
======================================================================= */
void eipc_userobj_process (void)
{
    /* NOTHING TO DO */
}

/* ====================================================================
Function:   eipc_userobj_getSerialNumber
Parameters: N/A
Returns:    32-bit unique serial number

This function returns a unique 32-bit serial number.  The least
significant 4 bytes of the MAC ID can be used since they must be
unique.
======================================================================= */
uint32 eipc_userobj_getSerialNumber (void)
{
   uint32 temp32;
   uint8 temp8_6[6];
   uint8 i;

   /* store the lowest 4 bytes of the MAC as our serial number */
   eipc_usersock_getOurMacAddr(temp8_6);
   for(i=0; i<4; i++)
      ((uint8 *)&temp32)[i] = temp8_6[i];
   return(temp32);
}

/* ====================================================================
Function:   eipc_userobj_procTagAccessResp
Parameters: server handle
            status
            tag configuration array count 
            tag configuration array
Returns:    N/A

This function is called when the PLC Response is received or timed out.

All data is returned as bytes in Litlle Endian

DATA TYPE           BYTES (0..3)                RTA FUNCTION TO CALL
================    ==========================  ====================
CL_DATATYPE_BOOL    data                        N/A
CL_DATATYPE_SINT    data                        N/A
CL_DATATYPE_INT     low     high                rta_GetLitEndian16()
CL_DATATYPE_DINT    lowest  low  high  highest  rta_GetLitEndian32()
CL_DATATYPE_REAL    lowest  low  high  highest  rta_GetLitEndianFloat() 

If a data function rta_GetLitEndianN needs to be called, the parameter
passed is the offset to the start of the data in the resonse buffer.
Make sure to advance the pointer by n bytes based on the data type.
======================================================================= */
void eipc_userobj_procTagAccessResp (int16 server_handle, uint8 status, uint16 tag_cnt, EIPC_TAG_STRUCT *tags)
{
    uint16  i, j;
	//uint16 test_len;

	//void* TagDst;
	CString str;
 	//EIPCUSERDATA* ptrTag;


    RTA_UNUSED_PARAM(status);

    // make sure the tag pointer isn't NULL
    if(tags == NULL)
        return;

    // process all tags based on the tag count
    for(i=0; i<tag_cnt; i++)
    {
        // check for an error response
        if(tags[i].gen_status)
        {
            // display the error message (if known)
            
            // READ ERROR 
            if(tags[i].service_code == CL_RSPCODE_READ)
            {
                TRACE("eipc_userobj_procTagAccessResp(%d) (%d)%s[%d] READ ERROR (GenStatus %02x, ExtStatus %04x)\r\n",server_handle, i,tags[i].tag_name, tags[i].tag_offset,tags[i].gen_status,tags[i].ext_status);
            }

            // WRITE ERROR
            else if(tags[i].service_code == CL_RSPCODE_WRITE)
            {
                TRACE("eipc_userobj_procTagAccessResp(%d) (%d)%s[%d] WRITE ERROR (GenStatus %02x, ExtStatus %04x)\r\n",server_handle, i,tags[i].tag_name, tags[i].tag_offset,tags[i].gen_status,tags[i].ext_status);
            }
        }

        // Get the read data
        else if((tags[i].service_code == CL_RSPCODE_READ) && (tags[i].tag_data_len > 0))
        {
            //TRACE("eipc_userobj_procTagAccessResp(%d) Read Data (tag[%d]) ",server_handle, i);

			tags[i].tag_name[tags[i].tag_name_len]='\0';
			str = tags[i].tag_name;
			//TRACE (_T ("Read lookup Tag1 name: %s \n"), str);
			//if (ReadTag_map.Lookup (str, (void*)TagDst))
			//{
			//	ptrTag = (EIPCUSERDATA*)TagDst;
			//	//str = ptrTag->tag_name;
			//	//TRACE (_T ("Index[%d]  Struct name: %s \n"), ptrTag->tag_index,str);
			//}
			//else{
			//	TRACE (_T ("Name NOT FOUND!!: %s ...\n"), str);			
			//	break;
			//}


            // only print up to the first 10 data items (for display purposes)
            //for(j=0; j<40 && j<tags[i].tag_data_len;)
            j=0;
            {
                // switch on the data type
                switch(tags[i].tag_data_type)
                {
                    // BOOL / SINT
                    case CL_DATATYPE_BOOL:
                    case CL_DATATYPE_SINT:
                        // print the data as hexadecimal
                        //eipc_user_dbprint1("%02x ", tags[i].tag_data_ptr[j]);
                    
                        // each data element is 1 byte
                        j++;
                        break;

                    // INT
                    case CL_DATATYPE_INT:
                        // print the data as hexadecimal
                        //eipc_user_dbprint1("%04x ", rta_GetLitEndian16(&tags[i].tag_data_ptr[j]));

                        // each data element is 2 bytes
                        j+=2;
                        break;

                    // DINT
                    case CL_DATATYPE_DINT:
                    case CL_DATATYPE_BITARRAY:        
                        // print the data as hexadecimal
                        //eipc_user_dbprint1("%08lx ", rta_GetLitEndian32(&tags[i].tag_data_ptr[j]));
                        //eipc_user_dbprint1("%ld ", rta_GetLitEndian32(&tags[i].tag_data_ptr[j]));

						// Save the data as floating point
						if (str == "BTC_Status_From_BTC1")
						{
							//TRACE("A DATA.... %5.2f \n", rta_GetLitEndianFloat(&tags[i].tag_data_ptr[j]));
							ReadPLCData.BTCStatus = rta_GetLitEndian32(&tags[i].tag_data_ptr[j]);
						}
						if (str == "BTC_Status_To_BTC1")
						{
							//TRACE("B DATA.... %5.2f \n", rta_GetLitEndianFloat(&tags[i].tag_data_ptr[j]));
							ReadPLCData.SlicerStatus = rta_GetLitEndian32(&tags[i].tag_data_ptr[j]);
						}						


                        // each data element is 4 bytes
                        j+=4;
                        break;

                    // FLOAT
                    case CL_DATATYPE_REAL:

						//// Save the data as floating point
						//if (str == "BTC_Status_From_BTC1")
						//{
						//	//TRACE("A DATA.... %5.2f \n", rta_GetLitEndianFloat(&tags[i].tag_data_ptr[j]));
						//	ReadPLCData.SteeringLaneA = rta_GetLitEndianFloat(&tags[i].tag_data_ptr[j]);
						//}
						//if (str == "BTC_Status_To_BTC1")
						//{
						//	//TRACE("B DATA.... %5.2f \n", rta_GetLitEndianFloat(&tags[i].tag_data_ptr[j]));
						//	ReadPLCData.SteeringLaneB = rta_GetLitEndianFloat(&tags[i].tag_data_ptr[j]);
						//}						

                        // each data element is 4 bytes
                        j+=4;
                        break;

					case CL_DATATYPE_STRUCTURE:
						// print the data as hexadecimal
						//eipc_user_dbprint1("%04x ", rta_GetLitEndian16(&tags[i].tag_data_ptr[j]));

						// Must store Struct Handler in the struct
						if (j==0) 
							save_handler= rta_GetLitEndian16(&tags[i].tag_data_ptr[j]);
						
						// each data element is 2 bytes since we are reading a structure of INTS
						switch(save_handler)
                        {
                            case CL_STRUCTHANDLE_STRING:
                                //test_len = (unsigned short)rta_GetLitEndian32(&tags[i].tag_data_ptr[j+2]);
                                //eipc_user_dbprint1("Len: %d ", test_len);
                                //tags[i].tag_data_ptr[j+6+test_len] = 0;
                                //eipc_user_dbprint1("%s", &tags[i].tag_data_ptr[j+6]);                                
                                break;
                        };
						break;
                }
            }

            // print a newline
            //eipc_user_dbprint0("\r\n");
        }
		else if(tags[i].service_code == CL_RSPCODE_WRITE)
		{
			tags[i].tag_name[tags[i].tag_name_len]='\0';
			str = tags[i].tag_name;
			//TRACE (_T ("Write lookup Tag1 name: %s \n"), str);
			//tags[i].tag_name[tags[i].tag_name_len]='\0';
			//str = tags[i].tag_name;
			////TRACE (_T ("lookup Tag1 Write name: %s "), str);
			//if (WriteTag_map.Lookup (str, (void*)TagDst))
			//{
			//	ptrTag = (EIPCUSERDATA*)TagDst;
			//}
			//else{
			//	TRACE (_T ("Name NOT FOUND!!: %s ...\n"), str);			
			//	break;
			//}
			////TRACE (_T ("Write tag data good.... tag[%d] update:%d \n"),i,ptrTag->tag_update_data);
		 //   ptrTag->tag_update_data = 0;

		}
		//======================================================================================================//

    }

}
