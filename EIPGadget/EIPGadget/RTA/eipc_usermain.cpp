/* ========================== */
/*      INCLUDE FILES         */
/* ========================== */
#include "eipc_system.h"

WSADATA WSData;
uint16 SampleServerHandle;
uint32 Ticker1;
struct timeb base;

/* ========================= */
/* LOCAL FUNCTION PROTOTYPES */
/* ========================= */
static uint32 local_get_ticks_passed (void);
static void local_process_tag_client (uint32 ticks_passed_since_last_call);
static void local_process_tag_client2 (uint32 ticks_passed_since_last_call);


uint8	struct_num_elements;
uint16  save_handler; 

typedef struct
{
    int16   server_handle;
    uint8   ipaddr_byte[4]; /* store as big endian */
    uint32  ipaddr32;
}EIPC_TAGCLIENT_IP_STRUCT;

#ifdef EIPC_TAG_CLIENT_USED 
EIPC_TAGCLIENT_IP_STRUCT tag_server =  {0,{10,13,4,115},0}; /* store IP as big endian */
EIPC_TAGCLIENT_IP_STRUCT tag_server2 = {0,{10,13,4,118},0}; /* store IP as big endian */
#endif

/* ========================= */
/* MAIN                      */
/* ========================= */
int main (void)
{
    /* local variables */
    int     error;
    uint32  ticks_passed;
	int i;

    // print some information
    eipc_user_dbprint1("RTA 499ETC Version %s\r\n", EIPC_VERSION_STRING);
    eipc_user_dbprint1("EIPC_USER_TICKS_PER_1SEC = %d\r\n", EIPC_USER_TICKS_PER_1SEC);

    /* ---------------------------------------------- */
    /*		   SOCKET INITIALIZATION BEGIN            */
    /* ---------------------------------------------- */
    // initialize WinSock
    error = WSAStartup(0x0020, &WSData);

    /* printf if we received an FAILURE */
    switch(error)
    {
        case WSASYSNOTREADY:     
            eipc_user_dbprint0("WSAStartup: \"WSASYSNOTREADY\"\r\n");    
            exit(1);
        case WSAVERNOTSUPPORTED: 
            eipc_user_dbprint0("WSAStartup: \"WSAVERNOTSUPPORTED\"\r\n"); 
            exit(1);
        case WSAEINPROGRESS:
            eipc_user_dbprint0("WSAStartup: \"WSAEINPROGRESS\"\r\n");
            exit(1);
        case WSAEPROCLIM:
            eipc_user_dbprint0("WSAStartup: \"WSAEPROCLIM\"\r\n");
            exit(1);
        case WSAEFAULT:
            eipc_user_dbprint0("WSAStartup: \"WSAEFAULT\"\r\n");
            exit(1);
    };
    /* ---------------------------------------------- */
    /*		   SOCKET INITIALIZATION END              */
    /* ---------------------------------------------- */
	
    // call the initialization code (RTA's init routines)
    eipc_rtasys_init(0);
   
    // initialize timer code
    local_get_ticks_passed(); // ignore the value the first time, just set the base

    // **********************************************
    // Tag Client Connection Configuration
    // **********************************************

	// store the IP address
    tag_server.ipaddr32 = rta_GetBigEndian32(tag_server.ipaddr_byte);

    // who are we connecting to?
    eipc_user_dbprint4("Tag Client Connecting to %03d.%03d.%03d.%03d\r\n",tag_server.ipaddr_byte[0],tag_server.ipaddr_byte[1],tag_server.ipaddr_byte[2],tag_server.ipaddr_byte[3] );

    // allocate a connection
    tag_server.server_handle = eipc_tagclient_connectToPLC(tag_server.ipaddr32);

	// store the IP address
    tag_server2.ipaddr32 = rta_GetBigEndian32(tag_server2.ipaddr_byte);

    // who are we connecting to?
    eipc_user_dbprint4("Tag Client Connecting to %03d.%03d.%03d.%03d\r\n",tag_server2.ipaddr_byte[0],tag_server2.ipaddr_byte[1],tag_server2.ipaddr_byte[2],tag_server2.ipaddr_byte[3] );

    // allocate a connection
    tag_server2.server_handle = eipc_tagclient_connectToPLC(tag_server2.ipaddr32);

    /* --------------------------------------------- */
    /*               RUN FOREVER                     */
    /* --------------------------------------------- */
    for(i=0;i<100000;i++)
    {
        /* get the time elapsed */
        ticks_passed = local_get_ticks_passed();

        /* process the state */
        eipc_rtasys_process(ticks_passed);

        /* process the tag client */
        local_process_tag_client(ticks_passed);
        local_process_tag_client2(ticks_passed);

    }    
	getchar();
}

/* ================================================ */
/*              LOCAL FUNCTIONS                     */
/* ================================================ */
/* ****************************************************
  Function: local_get_ticks_passed
Parameters: N/A
   Returns: ticks passed

This function returns the number of ticks that have
passed since the last call to this function.
******************************************************* */
static uint32 local_get_ticks_passed (void)
{
    uint32 return_val;
    struct timeb cur;

    ftime(&cur);

   // printf("cur.millitm %d cur.time %d\r\n", cur.millitm, cur.time);

    if(cur.millitm >= base.millitm)
        return_val = (cur.millitm-base.millitm);
    else // handle rollover
        return_val = ((1000-base.millitm)+cur.millitm);

    memcpy(&base, &cur, sizeof(base));
    
    //return the ticks passed
    return(return_val);
}

/* ****************************************************
  Function: local_process_tag_client
Parameters: ticks passed since last call to this func
   Returns: N/A

This function processes the tag client code.

typedef struct
{
    // tag name and offset
    char    tag_name[EIPC_USEROBJ_TAGNAME_SIZE];
    uint8   tag_name_len;
    uint16  tag_offset;

    // number of elements
    uint16  tag_num_elements;

    // message processing
    uint8   service_code;
    uint8   gen_status;
    uint16  ext_status;
 
    uint16  tag_data_type;
    uint16  tag_data_len;
    uint8   tag_data_ptr[EIPC_USEROBJ_TAGDATA_SIZE];    
}EIPC_TAG_STRUCT;
******************************************************* */
#ifdef EIPC_TAG_CLIENT_USED
static void local_process_tag_client (uint32 ticks_passed_since_last_call)
{
    uint8  i, tag_num;
    int16  return_code;

    static uint8 rw_toggle = 0;
    static uint32 tag_ticker = 0;
    static EIPC_TAG_STRUCT tags[EIPC_USEROBJ_MAXTAGS_PER_MSG];
    static uint8 first_time = 1;
    static uint8 string_val=0;

    /* initialize variables */
    if(first_time)
    {
        first_time = 0;

        // zero out the tag configuration
        memset(tags, 0, sizeof(tags));
    }

    /* nothing to do */
    if(ticks_passed_since_last_call == 0)
        return;

    /* advance the ticker */
    tag_ticker += ticks_passed_since_last_call;

    /* send a message every second */
    if(tag_ticker > (EIPC_USER_TICKS_PER_1SEC/10))
    {
        // reset the ticker 
        tag_ticker = 0;

        // alternate between reads and writes for the demo
        rw_toggle++;

        if(rw_toggle > 1)
            rw_toggle = 0;  
         

        // ***************************************
        // Build the Request (1 tags)
        // ***************************************

        // set the tag count to 1
        tag_num = 1;

        // ***************************************
        // Configure 1 Structure
        //
        // Tag 1 : "SingleString" (string UDT)
        // ***************************************
        for(i=0; i<tag_num; i++)
        {            
            // store the tag name and tag name length
            // store the number of elements to read/write
            switch(i)
            {
                case 0: strcpy(tags[i].tag_name, "STEER_VALUE_A");    tags[i].tag_num_elements = 1; break;
                case 1: strcpy(tags[i].tag_name, "STEER_VALUE_A");    tags[i].tag_num_elements = 1; break;
                case 2: strcpy(tags[i].tag_name, "Real1");            tags[i].tag_num_elements = 1; break;
                case 3: strcpy(tags[i].tag_name, "StringApples");     tags[i].tag_num_elements = 1; break;
            }
            tags[i].tag_name_len = (uint8)strlen(tags[i].tag_name);

            // stote the tag offset to read/write
            // usually 0, unless you are acessing an array
            tags[i].tag_offset = 0;

            // update the write data on writes
            if(rw_toggle == 0)
            {
                switch(i)
                {
                    case 0: 
                        // store the data type (String)
                        //memset(tags[i].tag_data_ptr, 0, sizeof(tags[i].tag_data_ptr));
                        //tags[i].tag_data_type = CL_DATATYPE_STRUCTURE;
                        //tags[i].tag_structure_handle = CL_STRUCTHANDLE_STRING;
                        //tags[i].tag_num_elements = 1;
                        //rta_PutLitEndian32(9, tags[i].tag_data_ptr); // store the length
                        //sprintf(tags[i].tag_data_ptr+4, "String_%02x", string_val++);
                        //tags[i].tag_data_len = 4+82+2; // len + string data + 2 bytes padding

						// store the data type REAL
                        memset(tags[i].tag_data_ptr, 0, sizeof(tags[i].tag_data_ptr));
                        tags[i].tag_data_type = CL_DATATYPE_REAL;
                        tags[i].tag_structure_handle = 0;
                        tags[i].tag_num_elements = 1;
                        //rta_PutLitEndian32(123456, tags[i].tag_data_ptr); // store the data
						rta_PutLitEndianFloat ((float)1.23,tags[i].tag_data_ptr);
                        //sprintf(tags[i].tag_data_ptr+4, "Apples_%02x", string_val++);
                        tags[i].tag_data_len = 4+2; // len + string data + 2 bytes padding

                        break;
                    case 1: 
                        // store the data type DINT
                        //memset(tags[i].tag_data_ptr, 0, sizeof(tags[i].tag_data_ptr));
                        //tags[i].tag_data_type = CL_DATATYPE_DINT;
                        //tags[i].tag_structure_handle = 0;
                        //tags[i].tag_num_elements = 1;
                        //rta_PutLitEndian32(1234, tags[i].tag_data_ptr); // store the data
                        ////sprintf(tags[i].tag_data_ptr+4, "Apples_%02x", string_val++);
                        //tags[i].tag_data_len = 4+2; // len + string data + 2 bytes padding
                        break;
                    case 2: 
      //                  // store the data type REAL
      //                  memset(tags[i].tag_data_ptr, 0, sizeof(tags[i].tag_data_ptr));
      //                  tags[i].tag_data_type = CL_DATATYPE_REAL;
      //                  tags[i].tag_structure_handle = 0;
      //                  tags[i].tag_num_elements = 1;
      //                  //rta_PutLitEndian32(123456, tags[i].tag_data_ptr); // store the data
						//rta_PutLitEndianFloat (21.23,tags[i].tag_data_ptr);
      //                  //sprintf(tags[i].tag_data_ptr+4, "Apples_%02x", string_val++);
      //                  tags[i].tag_data_len = 4+2; // len + string data + 2 bytes padding
                        break;
                    case 3: 
                        // store the data type (String)
                        //memset(tags[i].tag_data_ptr, 0, sizeof(tags[i].tag_data_ptr));
                        //tags[i].tag_data_type = CL_DATATYPE_STRUCTURE;
                        //tags[i].tag_structure_handle = CL_STRUCTHANDLE_STRING;
                        //tags[i].tag_num_elements = 1;
                        //rta_PutLitEndian32(9, tags[i].tag_data_ptr); // store the length
                        //sprintf(tags[i].tag_data_ptr+4, "Apples_%02x", string_val++);
                        //tags[i].tag_data_len = 4+82+2; // len + string data + 2 bytes padding
                        break;
               }
            }
        }

        // ***************************************
        // Send Write Request
        // ***************************************
        if(rw_toggle == 0)
        {
            /* server handle, timeout, slot, num tags, tags */
            return_code = eipc_tagclient_sendTagWrite_unconnected(tag_server.server_handle,
				EIPC_USER_TICKS_PER_1SEC, 0, 1, &tags[0]);            

               eipc_user_dbprint0("Write A\r\n");

        }

        // ***************************************
        // Send Read Request
        // ***************************************
        else
        {
            /* server handle, timeout, slot, num tags, tags */
            return_code = eipc_tagclient_sendTagRead_unconnected(tag_server.server_handle, EIPC_USER_TICKS_PER_1SEC, 0, tag_num, &tags[0]);    
        }

        // ***************************************
        // Process the Response (print the errors)
        // ***************************************
        switch(return_code)
        {
            // SUCCESS - Do Nothing
            case EIPC_CLIENT_UCMMERR_SUCCESS:
                break;

            // Server Handle Invalid or Not Connected
            case EIPC_CLIENT_UCMMERR_SERVHAND:
                eipc_user_dbprint0("EIPC_CLIENT_UCMMERR_SERVHAND\r\n");

                // ---------------------------------------------
                // try to reconnect to the server (if necessary)
                // ---------------------------------------------
                tag_server.server_handle = eipc_tagclient_connectToPLC(tag_server.ipaddr32);
                break;

            // Message Already in Progress to the Server Handle
            case EIPC_CLIENT_UCMMERR_BUSY:
                //eipc_user_dbprint0("EIPC_CLIENT_UCMMERR_BUSY\r\n");

                for(i=0; i<tag_num; i++)
                {            
                    // update the write data on writes
                    if(rw_toggle == 1)
                    {
                        // store the data type (DINT)
                        tags[i].tag_data_ptr[0]--;
                    }
                }

                // toggle back, we didn't succeed
                rw_toggle ^=1;

                // try to resend the message later
                break;

            // Tag Count Exceeds Max Allowed
            case EIPC_CLIENT_UCMMERR_TAGCNT:
                eipc_user_dbprint0("EIPC_CLIENT_UCMMERR_TAGCNT\r\n");

                // try to read/write less tags in a single request
                break;

            // Tag Configuration Pointer is Invalid
            case EIPC_CLIENT_UCMMERR_TAGPTR:
                eipc_user_dbprint0("EIPC_CLIENT_UCMMERR_TAGPTR\r\n");
    
                // don't pass a NULL configuration pointer
                break;

            // Tag Format is Invalid or Too Large for a Single Message
            case EIPC_CLIENT_UCMMERR_TAGFMT:
                eipc_user_dbprint0("EIPC_CLIENT_UCMMERR_TAGFMT\r\n");

                // try to read/write less tags in a single request
                break;

            // Timeout is Too Small
            case EIPC_CLIENT_UCMMERR_TMOINVALID:
                eipc_user_dbprint0("EIPC_CLIENT_UCMMERR_TMOINVALID\r\n");

                // increase the timeout value on send requests
                break;
        };
    }
}
#endif

/* ****************************************************
  Function: local_process_tag_client
Parameters: ticks passed since last call to this func
   Returns: N/A

This function processes the tag client code.

typedef struct
{
    // tag name and offset
    char    tag_name[EIPC_USEROBJ_TAGNAME_SIZE];
    uint8   tag_name_len;
    uint16  tag_offset;

    // number of elements
    uint16  tag_num_elements;

    // message processing
    uint8   service_code;
    uint8   gen_status;
    uint16  ext_status;
 
    uint16  tag_data_type;
    uint16  tag_data_len;
    uint8   tag_data_ptr[EIPC_USEROBJ_TAGDATA_SIZE];    
}EIPC_TAG_STRUCT;
******************************************************* */
#ifdef EIPC_TAG_CLIENT_USED
static void local_process_tag_client2 (uint32 ticks_passed_since_last_call)
{
	uint8  i, tag_num;
    int16  return_code;

    static uint8 rw_toggle = 0;
    static uint32 tag_ticker = 0;
    static EIPC_TAG_STRUCT tags[EIPC_USEROBJ_MAXTAGS_PER_MSG];
    static uint8 first_time = 1;
    static uint8 string_val=0;

    /* initialize variables */
    if(first_time)
    {
        first_time = 0;

        // zero out the tag configuration
        memset(tags, 0, sizeof(tags));
    }

    /* nothing to do */
    if(ticks_passed_since_last_call == 0)
        return;

    /* advance the ticker */
    tag_ticker += ticks_passed_since_last_call;

    /* send a message every second */
    if(tag_ticker > (EIPC_USER_TICKS_PER_1SEC/10))
    {
        // reset the ticker 
        tag_ticker = 0;

        // alternate between reads and writes for the demo
        rw_toggle++;

        if(rw_toggle > 1)
            rw_toggle = 0;  
         
		// TEST
		//rw_toggle = 1;  

        // ***************************************
        // Build the Request (1 tags)
        // ***************************************

        // set the tag count to 1
        tag_num = 1;

        // ***************************************
        // Configure 1 Structure
        //
        // Tag 1 : "SingleString" (string UDT)
        // ***************************************
        for(i=0; i<tag_num; i++)
        {            
            // store the tag name and tag name length
            // store the number of elements to read/write
            switch(i)
            {
                case 0: strcpy(tags[i].tag_name, "STEER_VALUE_B");    tags[i].tag_num_elements = 1; break;
                case 1: strcpy(tags[i].tag_name, "STEER_VALUE_A");    tags[i].tag_num_elements = 1; break;
                case 2: strcpy(tags[i].tag_name, "Real1");            tags[i].tag_num_elements = 1; break;
                case 3: strcpy(tags[i].tag_name, "StringApples");     tags[i].tag_num_elements = 1; break;
            }
            tags[i].tag_name_len = (uint8)strlen(tags[i].tag_name);

            // stote the tag offset to read/write
            // usually 0, unless you are acessing an array
            tags[i].tag_offset = 0;

            // update the write data on writes
            if(rw_toggle == 0)
            {
                switch(i)
                {
                    case 0: 
                        // store the data type (String)
                        //memset(tags[i].tag_data_ptr, 0, sizeof(tags[i].tag_data_ptr));
                        //tags[i].tag_data_type = CL_DATATYPE_STRUCTURE;
                        //tags[i].tag_structure_handle = CL_STRUCTHANDLE_STRING;
                        //tags[i].tag_num_elements = 1;
                        //rta_PutLitEndian32(9, tags[i].tag_data_ptr); // store the length
                        //sprintf(tags[i].tag_data_ptr+4, "String_%02x", string_val++);
                        //tags[i].tag_data_len = 4+82+2; // len + string data + 2 bytes padding

						// store the data type REAL
                        memset(tags[i].tag_data_ptr, 0, sizeof(tags[i].tag_data_ptr));
                        tags[i].tag_data_type = CL_DATATYPE_REAL;
                        tags[i].tag_structure_handle = 0;
                        tags[i].tag_num_elements = 1;
                        //rta_PutLitEndian32(123456, tags[i].tag_data_ptr); // store the data
						rta_PutLitEndianFloat ((float)3.23,tags[i].tag_data_ptr);
                        //sprintf(tags[i].tag_data_ptr+4, "Apples_%02x", string_val++);
                        tags[i].tag_data_len = 4+2; // len + string data + 2 bytes padding

                        break;
                    case 1: 
                        // store the data type DINT
                        //memset(tags[i].tag_data_ptr, 0, sizeof(tags[i].tag_data_ptr));
                        //tags[i].tag_data_type = CL_DATATYPE_DINT;
                        //tags[i].tag_structure_handle = 0;
                        //tags[i].tag_num_elements = 1;
                        //rta_PutLitEndian32(1234, tags[i].tag_data_ptr); // store the data
                        ////sprintf(tags[i].tag_data_ptr+4, "Apples_%02x", string_val++);
                        //tags[i].tag_data_len = 4+2; // len + string data + 2 bytes padding
                        break;
                    case 2: 
      //                  // store the data type REAL
      //                  memset(tags[i].tag_data_ptr, 0, sizeof(tags[i].tag_data_ptr));
      //                  tags[i].tag_data_type = CL_DATATYPE_REAL;
      //                  tags[i].tag_structure_handle = 0;
      //                  tags[i].tag_num_elements = 1;
      //                  //rta_PutLitEndian32(123456, tags[i].tag_data_ptr); // store the data
						//rta_PutLitEndianFloat (21.23,tags[i].tag_data_ptr);
      //                  //sprintf(tags[i].tag_data_ptr+4, "Apples_%02x", string_val++);
      //                  tags[i].tag_data_len = 4+2; // len + string data + 2 bytes padding
                        break;
                    case 3: 
                        // store the data type (String)
                        //memset(tags[i].tag_data_ptr, 0, sizeof(tags[i].tag_data_ptr));
                        //tags[i].tag_data_type = CL_DATATYPE_STRUCTURE;
                        //tags[i].tag_structure_handle = CL_STRUCTHANDLE_STRING;
                        //tags[i].tag_num_elements = 1;
                        //rta_PutLitEndian32(9, tags[i].tag_data_ptr); // store the length
                        //sprintf(tags[i].tag_data_ptr+4, "Apples_%02x", string_val++);
                        //tags[i].tag_data_len = 4+82+2; // len + string data + 2 bytes padding
                        break;
               }
            }
        }

        // ***************************************
        // Send Write Request
        // ***************************************
        if(rw_toggle == 0)
        {
            /* server handle, timeout, slot, num tags, tags */
            return_code = eipc_tagclient_sendTagWrite_unconnected(tag_server2.server_handle,
				EIPC_USER_TICKS_PER_1SEC, 0, 1, &tags[0]);            

               eipc_user_dbprint0("Write  B\r\n");

        }

        // ***************************************
        // Send Read Request
        // ***************************************
        else
        {
            /* server handle, timeout, slot, num tags, tags */
            return_code = eipc_tagclient_sendTagRead_unconnected(tag_server2.server_handle, EIPC_USER_TICKS_PER_1SEC, 0, tag_num, &tags[0]);    
        }

        // ***************************************
        // Process the Response (print the errors)
        // ***************************************
        switch(return_code)
        {
            // SUCCESS - Do Nothing
            case EIPC_CLIENT_UCMMERR_SUCCESS:
                break;

            // Server Handle Invalid or Not Connected
            case EIPC_CLIENT_UCMMERR_SERVHAND:
                eipc_user_dbprint0("EIPC_CLIENT_UCMMERR_SERVHAND\r\n");

                // ---------------------------------------------
                // try to reconnect to the server (if necessary)
                // ---------------------------------------------
                tag_server2.server_handle = eipc_tagclient_connectToPLC(tag_server2.ipaddr32);
                break;

            // Message Already in Progress to the Server Handle
            case EIPC_CLIENT_UCMMERR_BUSY:
                //eipc_user_dbprint0("EIPC_CLIENT_UCMMERR_BUSY\r\n");

                for(i=0; i<tag_num; i++)
                {            
                    // update the write data on writes
                    if(rw_toggle == 1)
                    {
                        // store the data type (DINT)
                        tags[i].tag_data_ptr[0]--;
                    }
                }

                // toggle back, we didn't succeed
                rw_toggle ^=1;

                // try to resend the message later
                break;

            // Tag Count Exceeds Max Allowed
            case EIPC_CLIENT_UCMMERR_TAGCNT:
                eipc_user_dbprint0("EIPC_CLIENT_UCMMERR_TAGCNT\r\n");

                // try to read/write less tags in a single request
                break;

            // Tag Configuration Pointer is Invalid
            case EIPC_CLIENT_UCMMERR_TAGPTR:
                eipc_user_dbprint0("EIPC_CLIENT_UCMMERR_TAGPTR\r\n");
    
                // don't pass a NULL configuration pointer
                break;

            // Tag Format is Invalid or Too Large for a Single Message
            case EIPC_CLIENT_UCMMERR_TAGFMT:
                eipc_user_dbprint0("EIPC_CLIENT_UCMMERR_TAGFMT\r\n");

                // try to read/write less tags in a single request
                break;

            // Timeout is Too Small
            case EIPC_CLIENT_UCMMERR_TMOINVALID:
                eipc_user_dbprint0("EIPC_CLIENT_UCMMERR_TMOINVALID\r\n");

                // increase the timeout value on send requests
                break;
        };
    }

}
#endif


/* *********** */
/* END OF FILE */
/* *********** */
