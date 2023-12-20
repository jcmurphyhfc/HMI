#include "StdAfx.h"
#include "MilObj.h"
#include "HookFunctions.h"

#ifndef SHARED_HANDLERS
#include "HMI.h"
#endif
/////////////////////////////////////////////////////////////////////////////////
// Functon: FillMissingData()
//
// Description: This function fills in missing laser line data.
// 
//
/////////////////////////////////////////////////////////////////////////////////.
bool FillMissingData(int MaxGapFill,int GapElavation,MIL_INT* pLaserPos,int xStart,int xEnd)
{
	double y;
	double y0;
	double y1;
	int x0;
	int x1;
	bool Point1 = false;
	bool Gap = false;
	int GapSize;
	int ElavationSize;

	for (int i=xStart;i<xEnd;i++)
	{
		// Data Found
		if (pLaserPos[i] > 0 && !Gap)
		{
			Point1 = true;
			x0 = i;
			y0 = pLaserPos[i];
		}

		// Gap found
		if (pLaserPos[i] < 0 && Point1)
		{
			Gap = true;
		}

		// End of gap Found
		if (pLaserPos[i] > 0 && Gap)
		{
			Point1 = false;
			Gap = false;
			x1 = i;
			y1 = pLaserPos[i];
			GapSize = x1 - x0;
			ElavationSize = (int)abs(y0-y1);

			//TRACE("Fill gap Gap x0 %d x1 %d  Gap Size: %d    y(-1): %d  y1: %d \n",(int)x0,(int)x1,GapSize,pLaserPos[i-1],pLaserPos[i]);
			//int indexI = (int)x0;
			//TRACE("Fill gap Gap x0 %d x1 %d  Gap Size: %d    y(+1): %d  y1: %d \n",(int)x0,(int)x1,GapSize,pLaserPos[indexI+1],pLaserPos[indexI]);

			// Fill the gaps in the data.
			if (GapSize <= MaxGapFill && ElavationSize <= GapElavation)
			{
				for (int x=x0; x<x1; x++)
				{
					y = y0 + (x-x0)*((y1-y0)/(x1-x0));
					pLaserPos[x] = (MIL_INT)y;
				}
			}

			Point1 = true;
			x0 = i;
			y0 = pLaserPos[i];
		}

	}
	return true;
}

//======================================================================================================//
// Function Name: CreateBaconBlob(MIL_ID SrcID,MIL_ID DstID)                                           //
//                                                                                                      //
//======================================================================================================//
long CreateBaconBlob(int MinX,MIL_INT* LaserPos,int* SBarPos,MIL_ID DstID)
{            
	MIL_UINT8* DstImageDataPtr;
	MIL_INT   DstImageSizeX, DstImageSizeY, DstImageType, DstImagePitchByte;
	MIL_INT   x, y;
	long BlobSize = 0;

	// Lock buffer for direct access.
	MbufControl(DstID, M_LOCK, M_DEFAULT);

	// Read image information. 
	MbufInquire(DstID, M_HOST_ADDRESS, &DstImageDataPtr);
	MbufInquire(DstID, M_SIZE_X,       &DstImageSizeX);           //TRACE("DstSize X: %d \n",DstImageSizeX);
	MbufInquire(DstID, M_SIZE_Y,       &DstImageSizeY);           //TRACE("DstSize Y: %d \n",DstImageSizeY);
	MbufInquire(DstID, M_TYPE,         &DstImageType);            //TRACE("DstType: %d \n",DstImageType);
	MbufInquire(DstID, M_PITCH_BYTE,   &DstImagePitchByte); 	   //TRACE("DstPitchByte: %d \n",DstImagePitchByte);

	//TRACE("SizeX:%d \n",DstImageSizeX);
	//TRACE("SizeY:%d \n",DstImageSizeY);

	// Check pointers
	if (DstImageDataPtr == M_NULL)
	{
	 return 0;
	}
	//TRACE("SrcPtr %x \n",SrcImageDataPtr); TRACE("DstPtr %x \n",DstImageDataPtr);

	// Y
	//-----------------------------------------------------------------------------------------------//
	for (y= 0; y < DstImageSizeY; y++) 
	{
		// X
		//--------------------------------------------------------------------------------------------//
		for (x= 0; x < DstImageSizeX; x++)
		{	
			// Is data point at or below the laser point and above the SBar point?
			if (y >= LaserPos[x] && y < SBarPos[x])
			{
				// SBar starting point
				if (x > MinX)
				{
					if (LaserPos[x] > 0 && (LaserPos[x] < SBarPos[x]))
					{
						BlobSize++;
						DstImageDataPtr[x] = 0xFF;
					}
					else
					{
						DstImageDataPtr[x] = 0x00;
					}
				}
				else
				{
					DstImageDataPtr[x] = 0x00;
				}
			}
			else
			{
				DstImageDataPtr[x] = 0x00;
			}
		}
		//-------------------------------------- End x -----------------------------------------------//
		
		// Move pointer to the next line taking into account the image's pitch.
		DstImageDataPtr += DstImagePitchByte;
	}
	//------------------------------------------- End y  ---------------------------------------------//

	//DstAreaSqCm = (double)TotalHeightPoints*dbSqCmScale;
	//TRACE("Dst Size: %d %4.2f \n",TotalHeightPoints,DstAreaSqCm);

	// Unlock buffers. 
	MbufControl(DstID, M_UNLOCK, M_DEFAULT);

	return BlobSize;
}
//======================================================================================================//

CMil::CMil(void)
{
	//MilHook1.FirstImage = true;
	m_bInitOK = false;
	MilCom = M_NULL;
	m_dbComAllocTimeST = 0;
	MilHook1.DisplaySelect = 2;
	MilHook1.MainPage = true;
	MILShowError = false;
	MilApplication = M_NULL;
	MilSystem = M_NULL;
	CmdListId = M_NULL;
	MilDisplay = M_NULL;
	MilDisplay2 = M_NULL;
	MilOverlayImage = M_NULL;
	MilRejectDisplay = M_NULL;
	MilRejectDisplay2 = M_NULL;
	MilDigitizer[0] = M_NULL;
	MilDigitizer[1] = M_NULL;
	MilDigitizer[2] = M_NULL;
	MilDigitizer[3] = M_NULL;
	MilHook1.MilRawImage = M_NULL;
	MilHook1.MilRawImageTop = M_NULL;
	MilHook1.MilRawImageBot = M_NULL;
	MilHook1.MilBinImage = M_NULL;
	MilHook1.MilBinImageTop = M_NULL;
	MilHook1.MilBinImageBot = M_NULL;
	MilHook1.MilBinImageBotSeperation = M_NULL;
	MilHook1.PmacComComplete = true;

	MilContext[0]  = M_NULL;
	MilContext[1]  = M_NULL;
	MilLocatePeak[0]= M_NULL;
	MilLocatePeak[1]= M_NULL;
	MilBaconBlobImage = M_NULL;

	
	for (int i=0; i<GRAB_LIST_SIZE2; i++)
	{
		MilGrabBuff1[i] = M_NULL;
	}
	for (int i=0; i<GRAB_LIST_SIZE; i++)
	{
		MilGrabBuff0[i] = M_NULL;
	}

	MilImage = M_NULL;
	MilImageFull = M_NULL;
	MilImage2 = M_NULL;
	MilWorkImage2 = NULL;
	MilRejectBlobImage = NULL;
	for (int i=0; i<MAX_RECORD; i++)
	{
		MilRecordImages[i] = NULL;
	}
	RunThreadData.Running = false;

	//m_strErrors.SetSize (MAX_MIL_ERRORS);
	m_nErrorCount = 0;
	CameraTrigSel = 0;
	m_History.SetFileName(HISTORY_PATH);
	m_OverlayOn = false;
	MilHook1.IoFunctionHooked = false;	
	MilHook1.StartQue = false;	
	MilHook1.StartQueCount = 0;
	
}


CMil::~CMil(void)
{
	//MsysControl(M_DEFAULT_HOST,TIME_STAMP_OUTPUT, M_OFF);

	// Unhook
	MsysHookFunction(MilSystem, M_CAMERA_PRESENT + M_UNHOOK, CamPresentFunction,&SysUserHookData);

	/* Unhook the callback function. */
    //MsysHookFunction(M_DEFAULT_HOST, M_IO_CHANGE+M_UNHOOK, IoHookFunction, &IoHookData);
	MsysControl(M_DEFAULT_HOST, M_IO_INTERRUPT_STATE + M_AUX_IO9, M_DISABLE);

	if (MilHook1.IoFunctionHooked) MsysHookFunction(M_DEFAULT_HOST, M_IO_CHANGE+M_UNHOOK, IoHookFunction, &MilHook1);
	MilHook1.IoFunctionHooked = false;	
	if (MilBaconBlobImage) MbufFree(MilBaconBlobImage);
	if (MilLocatePeak[1]) MimFree(MilLocatePeak[1]);
	if (MilLocatePeak[0]) MimFree(MilLocatePeak[0]);
	if (MilContext[1]) MimFree(MilContext[1]);
	if (MilContext[0]) MimFree(MilContext[0]);

	m_EndBlob.Free();
	m_Blob.Free();

	for (int i=0; i<GRAB_LIST_SIZE2; i++)
	{
		if (MilGrabBuff1[i]) MbufFree(MilGrabBuff1[i]);
	}
	for (int i=0; i<GRAB_LIST_SIZE; i++)
	{
		if (MilGrabBuff0[i]) MbufFree(MilGrabBuff0[i]);
	}

	for (int i=0; i<MAX_RECORD; i++)
	{
		if (MilRecordImages[i]) MbufFree(MilRecordImages[i]);
	}


	if (MilHook1.MilRawImageBot)        MbufFree(MilHook1.MilRawImageBot);
	if (MilHook1.MilRawImageTop)        MbufFree(MilHook1.MilRawImageTop);
	if (MilHook1.MilRawImage)        MbufFree(MilHook1.MilRawImage);

	if (MilHook1.MilBinImageBotSeperation)        MbufFree(MilHook1.MilBinImageBotSeperation);
	if (MilHook1.MilBinImageBot)        MbufFree(MilHook1.MilBinImageBot);
	if (MilHook1.MilBinImageTop)        MbufFree(MilHook1.MilBinImageTop);
	if (MilHook1.MilBinImage)        MbufFree(MilHook1.MilBinImage);

	if (MilImageRejectWork2)        MbufFree(MilImageRejectWork2);
	if (MilImageRejectWorkBlueBand)        MbufFree(MilImageRejectWorkBlueBand);
	if (MilImageRejectWorkGreenBand)        MbufFree(MilImageRejectWorkGreenBand);
	if (MilImageRejectWorkRedBand)        MbufFree(MilImageRejectWorkRedBand);
	if (MilImageRejectWork)        MbufFree(MilImageRejectWork);
	if (MilImageReject2)        MbufFree(MilImageReject2);
	if (MilImageReject)        MbufFree(MilImageReject);

	if (MilWorkImage)        MbufFree(MilWorkImage);
	if (MilWorkImage2)       MbufFree(MilWorkImage2);
	if (MilRejectBlobImage)  MbufFree(MilRejectBlobImage);

	if (MilImage2)       MbufFree(MilImage2);
	if (MilImage)        MbufFree(MilImage);
	if (MilImageFull)    MbufFree(MilImageFull);
	if (MilDigitizer[1]) MdigFree(MilDigitizer[1]);
    if (MilDigitizer[0]) MdigFree(MilDigitizer[0]);

	
	if (MilRejectDisplay2)      MdispFree(MilRejectDisplay2);
    if (MilRejectDisplay)      MdispFree(MilRejectDisplay);
    //if (MilOverlayImage)      MdispFree(MilOverlayImage);

    if (MilDisplay2)      MdispFree(MilDisplay2);
    if (MilDisplay)      MdispFree(MilDisplay);
	if (CmdListId)       MsysIoFree(CmdListId);
    if (MilSystem)       MsysFree(MilSystem);
	if (MilCom)          McomFree(MilCom);
    if (MilApplication)  MappFree(MilApplication);
	TRACE("Free mill \n");

}

BOOL CMil::InitInstance(bool* pbSplash,ALLSETTINGS* pSettings)
{
	m_bInitOK = false;
	m_pbSplash = pbSplash;
	MilHook1.pSettings = pSettings;
	MilHook2.pSettings = pSettings;
	RunThreadData.pHook1 = &MilHook1;
	MilHook1.pRunning = &RunThreadData.Running;
	RunThreadData.pHook1->pBlob = &m_Blob;
    MIL_BOOL ChunkModeActive = M_FALSE;
	MIL_INT LicenseModules;
	TCHAR szText[1024];
	MIL_INT BoardType,BufSizeX,BufSizeY,BufSizeBand,NumCameras;

	// Wait on runtime license
	do 
	{
		// Allocate a MIL application.
		MappAlloc(M_DEFAULT, &MilApplication);

		// Check the modules
	    MappInquire(MilApplication, M_LICENSE_MODULES, &LicenseModules);    
		if ( !(LicenseModules & M_LICENSE_IM) || !(LicenseModules & M_LICENSE_BLOB))
		{
			if (MilApplication)  MappFree(MilApplication);
			Sleep(1000);
		}
	}
	while( !(LicenseModules & M_LICENSE_IM) || !(LicenseModules & M_LICENSE_BLOB));


	// Hook MIL error on function DisplayError() [CALL TO MIL]
	MappHookFunction(M_DEFAULT, M_ERROR_CURRENT,DisplayErrorExt,this);
	MilErrorMessageCount = 0;

	// Disable the typical MIL error message display [CALL TO MIL]
	MappControl(M_DEFAULT, M_ERROR,M_PRINT_DISABLE);

	// I/O
	//MsysControl(M_DEFAULT_HOST,BACON_DETECT_OUTPUT_A, M_OFF);
	//MsysControl(M_DEFAULT_HOST,BACON_DETECT_OUTPUT_B, M_OFF);
	//MsysControl(M_DEFAULT_HOST,TIME_STAMP_OUTPUT, M_OFF);

    // Allocate a MIL system.
    MsysAlloc(M_SYSTEM_GIGE_VISION, M_DEFAULT, M_DEFAULT, &MilSystem);

	// Allocate a command list based on the internal clock
	//MsysIoAlloc(M_DEFAULT_HOST, M_IO_COMMAND_LIST1, M_IO_COMMAND_LIST, M_CLOCK, &CmdListId);
	// Setup timer controlled pulse on (Output 8)
	//MsysControl(M_DEFAULT_HOST, M_IO_SOURCE + M_AUX_IO7, M_TIMER1);
	//MsysControl(M_DEFAULT_HOST, M_TIMER_DELAY + M_TIMER1, 0);
	//MsysControl(M_DEFAULT_HOST, M_TIMER_DURATION + M_TIMER1, PULSE_WIDTH_5MSEC);
	//MsysControl(M_DEFAULT_HOST, M_TIMER_TRIGGER_SOURCE + M_TIMER1, M_IO_COMMAND_LIST1 + M_IO_COMMAND_BIT0);
	//MsysControl(M_DEFAULT_HOST, M_TIMER_STATE + M_TIMER1, M_ENABLE);
	//MsysControl(M_DEFAULT_HOST, M_IO_SOURCE + M_AUX_IO7, M_IO_COMMAND_LIST1 + M_IO_COMMAND_BIT1); /* Connector's Output 8. */
	//MsysIoCommandRegister(CmdListId, M_PULSE_HIGH, M_REFERENCE_VALUE_CURRENT,0, 1400, M_IO_COMMAND_BIT0, M_NULL);
	//MsysIoCommandRegister(CmdListId, M_PULSE_HIGH, M_REFERENCE_VALUE_CURRENT,3000, 1400, M_IO_COMMAND_BIT0, M_NULL);
	//MsysIoCommandRegister(CmdListId, M_EDGE_FALLING, M_REFERENCE_VALUE_CURRENT,0, M_DEFAULT, M_IO_COMMAND_BIT6, M_NULL);
	//MsysIoCommandRegister(CmdListId, M_PULSE_HIGH, M_REFERENCE_VALUE_CURRENT,0, 4000, M_IO_COMMAND_BIT7, M_NULL);

	// All outputs off
	MsysControl(M_DEFAULT_HOST,M_USER_BIT_STATE+M_USER_BIT0, M_OFF);
	MsysControl(M_DEFAULT_HOST,M_USER_BIT_STATE+M_USER_BIT1, M_OFF);
	MsysControl(M_DEFAULT_HOST,M_USER_BIT_STATE+M_USER_BIT2, M_OFF);
	MsysControl(M_DEFAULT_HOST,M_USER_BIT_STATE+M_USER_BIT3, M_OFF);
	MsysControl(M_DEFAULT_HOST,M_USER_BIT_STATE+M_USER_BIT4, M_OFF);
	MsysControl(M_DEFAULT_HOST,M_USER_BIT_STATE+M_USER_BIT5, M_OFF);
	MsysControl(M_DEFAULT_HOST,M_USER_BIT_STATE+M_USER_BIT6, M_OFF);
	MsysControl(M_DEFAULT_HOST,M_USER_BIT_STATE+M_USER_BIT7, M_OFF);

	// Setup pulse	
	//MsysControl(M_DEFAULT_HOST, M_IO_SOURCE + M_AUX_IO0, M_IO_COMMAND_LIST1 + M_IO_COMMAND_BIT0); /* Connector's Output 1. */
	//MsysControl(M_DEFAULT_HOST, M_IO_SOURCE + M_AUX_IO1, M_IO_COMMAND_LIST1 + M_IO_COMMAND_BIT1); /* Connector's Output 2. */
	MsysControl(M_DEFAULT_HOST, M_IO_SOURCE + M_AUX_IO2, M_IO_COMMAND_LIST1 + M_IO_COMMAND_BIT2); /* Connector's Output 3. */
	//MsysControl(M_DEFAULT_HOST, M_IO_SOURCE + M_AUX_IO3, M_IO_COMMAND_LIST1 + M_IO_COMMAND_BIT3); /* Connector's Output 4. */
	//MsysControl(M_DEFAULT_HOST, M_IO_SOURCE + M_AUX_IO4, M_IO_COMMAND_LIST1 + M_IO_COMMAND_BIT4); /* Connector's Output 5. */
	//MsysControl(M_DEFAULT_HOST, M_IO_SOURCE + M_AUX_IO5, M_IO_COMMAND_LIST1 + M_IO_COMMAND_BIT5); /* Connector's Output 6. */
	//MsysControl(M_DEFAULT_HOST, M_IO_SOURCE + M_AUX_IO6, M_IO_COMMAND_LIST1 + M_IO_COMMAND_BIT6); /* Connector's Output 7. */
	//MsysControl(M_DEFAULT_HOST, M_IO_SOURCE + M_AUX_IO7, M_IO_COMMAND_LIST1 + M_IO_COMMAND_BIT7); /* Connector's Output 8. */
	
	// Allocate a command list based on M_AUX_IO input 1
	MsysIoAlloc(M_DEFAULT_HOST, M_IO_COMMAND_LIST1, M_IO_COMMAND_LIST, M_AUX_IO8, &CmdListId);
	if (CmdListId != M_NULL)
	{
	   TRACE("Command List registered.....................................................\n");
	   // Count on Rising edges
	   MsysIoControl(CmdListId, M_IO_COMMAND_COUNTER_ACTIVATION, M_EDGE_RISING);

	   // Latch counter upon detection of part on (Input 2)
	   MsysIoControl(CmdListId, M_REFERENCE_LATCH_TRIGGER_SOURCE + M_LATCH1, M_AUX_IO9);
	   MsysIoControl(CmdListId, M_REFERENCE_LATCH_ACTIVATION + M_LATCH1, M_EDGE_RISING);
	   MsysIoControl(CmdListId, M_REFERENCE_LATCH_STATE + M_LATCH1, M_ENABLE);
   	   // Debounce Input during 25 ms
	   MsysControl(M_DEFAULT_HOST, M_IO_DEBOUNCE_TIME+M_AUX_IO9, 25000000);
	   //MsysControl(M_DEFAULT_HOST, M_IO_GLITCH_FILTER_STATE+M_AUX_IO9, M_ENABLE); 

	   // Hook a function to sensor's signal (Input 2);
	   // hook-handler function reads and queues latched value.
	   MilHook1.CmdListId = CmdListId;
	   MsysControl(M_DEFAULT_HOST, M_IO_INTERRUPT_ACTIVATION + M_AUX_IO9, M_EDGE_RISING);
	   //MsysHookFunction(M_DEFAULT_HOST, M_IO_CHANGE, IoHookFunction, &MilHook1);
	   //MsysControl(M_DEFAULT_HOST, M_IO_INTERRUPT_STATE + M_AUX_IO9, M_ENABLE);

   	   //MsysIoCommandRegister(CmdListId, M_IMPULSE,0,0.001, M_DEFAULT, M_IO_COMMAND_BIT1, M_NULL);
	   //MsysIoCommandRegister(CmdListId, M_IMPULSE,M_REFERENCE_VALUE_CURRENT,0, M_DEFAULT, M_IO_COMMAND_BIT0, M_NULL);
	   //MsysIoCommandRegister(CmdListId, M_IMPULSE,M_REFERENCE_VALUE_CURRENT,0.1, M_DEFAULT, M_IO_COMMAND_BIT0, M_NULL);

	   // Add a command to the I/O command list.Click to summarizeClick for more details  
	   //MsysIoCommandRegister(CmdListId, M_EDGE_FALLING, M_REFERENCE_VALUE_CURRENT, 0.0, M_DEFAULT,  M_IO_COMMAND_BIT0, M_NULL);
	   //MsysIoCommandRegister(CmdListId, M_EDGE_FALLING, M_REFERENCE_VALUE_CURRENT, 0.0, M_DEFAULT,  M_IO_COMMAND_BIT7, M_NULL);
	}

    // Allocate a MIL displays 
    MdispAlloc(MilSystem, M_DEFAULT, MIL_TEXT("M_DEFAULT"), M_WINDOWED, &MilDisplay);
    MdispAlloc(MilSystem, M_DEFAULT, MIL_TEXT("M_DEFAULT"), M_WINDOWED, &MilDisplay2);
    MdispAlloc(MilSystem, M_DEFAULT, MIL_TEXT("M_DEFAULT"), M_WINDOWED, &MilRejectDisplay);
    MdispAlloc(MilSystem, M_DEFAULT, MIL_TEXT("M_DEFAULT"), M_WINDOWED, &MilRejectDisplay2);

	// Get information on the system we are using and print a welcome message to the console. 
	MsysInquire(MilSystem, M_BOARD_TYPE, &BoardType);
	MsysInquire(MilSystem, M_NUM_CAMERA_PRESENT, &NumCameras);
	TRACE(TEXT("Total Camerars present..........................................: %d \n"),NumCameras);

	/* Register a hook function to the system's camera present event. */
    /* Used to:                                                        */
    /* 1- Allocate and start acquisition on a newly attached camera.   */
    /* 2- Stop acquisition on a camera that has been removed.          */
    /* 3- Resume acquisition on a camera that has been re-connected.   */
    MsysHookFunction(MilSystem, M_CAMERA_PRESENT, CamPresentFunction, &SysUserHookData);

	//_T ("D:\\BTCDATA\\UpLoadFile.CFG")
	//CHMIApp* pApp = (CHMIApp*)AfxGetApp();
	//if (YesNoDlg(_T("Do you want to reboot?")))
	//{
	//	pApp->OnEwfUtilBoot();
	//}

	m_NewCamera = false;
	if (NumCameras < 2)
	{
		*m_pbSplash = false;
		Sleep(2000);
		if (NumCameras == 1)
		{		
			if (AfxMessageBox(_T("One Cameara Detected. Setup IP?"),MB_YESNO) == IDYES)
			{

				MdigAlloc(MilSystem,M_DEV0, MIL_TEXT("M_DEFAULT"),M_DEFAULT,	&MilDigitizer[0]);

				if (AfxMessageBox(_T("Is this camera 1 (End-Detect)?"),MB_YESNO) == IDYES)
				{
					SetupCameraIP(0xa9fefe01);			
				}
				else
				{
					SetupCameraIP(0xa9fefe02);
				}			
				AfxMessageBox(_T("Cycle Power to complete setup."),MB_OK);
				m_bInitOK = false;
				return m_bInitOK;
			}				
		}
		else
		{
			AfxMessageBox(_T("No cameras detected!"),MB_ICONSTOP);		
		}
	}

	// Allocate all GIGE digitizers
	if(((BoardType & M_BOARD_TYPE_MASK) == M_GIGE_VISION))
    {
		MdigAlloc(MilSystem,M_GC_CAMERA_ID(STEER_CAMERA_IP), MIL_TEXT("M_DEFAULT"),M_GC_DEVICE_IP_ADDRESS,	&MilDigitizer[0]);
		MdigAlloc(MilSystem,M_GC_CAMERA_ID(END_CAMERA_IP), MIL_TEXT("M_DEFAULT"),M_GC_DEVICE_IP_ADDRESS,	&MilDigitizer[1]);
		if (MilDigitizer[0]==NULL) AfxMessageBox(_T("Steering Camera Error!"));
		if (MilDigitizer[1]==NULL) AfxMessageBox(_T("End-Detect Camera Error!"));
	}
	// Allocate all default digitizers
	else
	{
		MdigAlloc(MilSystem, M_DEFAULT, MIL_TEXT("M_DEFAULT"), M_DEFAULT, &MilDigitizer[0]);
		MdigAlloc(MilSystem, M_DEFAULT, MIL_TEXT("M_DEFAULT"), M_DEFAULT, &MilDigitizer[1]);
	}
	TRACE(TEXT("Total Camerars present..........................................: %d \n"),NumCameras);

	// Set Steering camera parameters
	//--------------------------------------------------------------------------------------------------------------//
	MIL_DOUBLE ExposureTimeAbsInus        = pSettings->VisSettings1.Exposure_uS;
    MIL_DOUBLE LineDebouncerTimeAbsInus   = 10;
	MIL_BOOL LineInverter                 = M_FALSE;
	MIL_BOOL LineTermination              = M_TRUE;
	MIL_DOUBLE TriggerDelayAbsInus        = 0;
	//MIL_BOOL ChunkModeActive            = M_TRUE;
	//MIL_BOOL ChunkEnable                = M_TRUE;
	MIL_BOOL PartialClosingFrame          = M_FALSE;
	MIL_INT64 Width                       = IMAGE_SIZE_X;
	MIL_INT64 Height                      = IMAGE_SIZE_Y/2;
	MIL_DOUBLE AcquisitionLineRateAbsInHz = 6000;
	MIL_INT64 XOffset                     = 0;
	MIL_INT64 BinningHorizontal           = 2;
	//ApplySettings();

	// Setup Steering camera
	if (MilDigitizer[0])
	{
#ifdef OSCEOLA_LAYOUT

		// Acquisition Controls
		AcquisitionLineRateAbsInHz = 1000;
		MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("AcquisitionLineRateAbs"), M_TYPE_DOUBLE, &AcquisitionLineRateAbsInHz);
		MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("ExposureMode"), M_TYPE_STRING, MIL_TEXT("Timed"));
		MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("ExposureTimeAbs"), M_TYPE_DOUBLE, &ExposureTimeAbsInus);
		MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("BinningHorizontal"), M_TYPE_INT64, &BinningHorizontal);
		MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE_AS_STRING, MIL_TEXT("AcquisitionMode"), M_TYPE_ENUMERATION, MIL_TEXT("Continuous"));
		MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("Height"), M_TYPE_INT64, &Height);
		MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("Width"), M_TYPE_INT64, &Width);
		MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("OffsetX"), M_TYPE_INT64, &XOffset);
		MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE_AS_STRING, MIL_TEXT("TestImageSelector"), M_TYPE_ENUMERATION, MIL_TEXT("Off"));

		// AcquisitionStart
		MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("TriggerSelector"), M_TYPE_STRING, MIL_TEXT("AcquisitionStart"));
		MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("TriggerMode"), M_TYPE_STRING, MIL_TEXT("Off"));

		// FrameStart
		MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("TriggerSelector"), M_TYPE_STRING, MIL_TEXT("FrameStart"));
		//MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("TriggerMode"), M_TYPE_STRING, MIL_TEXT("On"));
		MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("TriggerMode"), M_TYPE_STRING, MIL_TEXT("Off"));
		//MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("TriggerSource"), M_TYPE_STRING, MIL_TEXT("Line2"));
		//MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("TriggerActivation"), M_TYPE_STRING, MIL_TEXT("LevelLow"));
		//MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("TriggerActivation"), M_TYPE_STRING, MIL_TEXT("RisingEdge"));
		//MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("TriggerActivation"), M_TYPE_STRING, MIL_TEXT("LevelHigh"));
		//MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("TriggerPartialClosingFrame"), M_TYPE_BOOLEAN, &PartialClosingFrame);

		MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("TriggerDelaySource"), M_TYPE_STRING, MIL_TEXT("Time_us"));
		MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("TriggerDelayAbs"), M_TYPE_DOUBLE, &TriggerDelayAbsInus);

		// LineStart
		MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("TriggerSelector"), M_TYPE_STRING, MIL_TEXT("LineStart"));
		//MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("TriggerMode"), M_TYPE_STRING, MIL_TEXT("On"));
		MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("TriggerMode"), M_TYPE_STRING, MIL_TEXT("Off"));
		//MdigControlFeature(MilDigitizer[0], M_FEATURE_EXECUTE, MIL_TEXT("TriggerSoftware"), M_DEFAULT, M_NULL);
		//MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("TriggerSource"), M_TYPE_STRING, MIL_TEXT("Line1"));
		//MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("TriggerActivation"), M_TYPE_STRING, MIL_TEXT("RisingEdge"));
		//MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("TriggerDelayAbs"), M_TYPE_DOUBLE, &TriggerDelayAbsInus);
		//MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("TriggerDelaySource"), M_TYPE_STRING, MIL_TEXT("Time_us"));

		// LineSelector 1
		//MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("LineSelector"), M_TYPE_STRING, MIL_TEXT("Line1"));
		//MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("LineMode"), M_TYPE_STRING, MIL_TEXT("Input"));
		//MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("LineDebouncerTimeAbs"), M_TYPE_DOUBLE, &LineDebouncerTimeAbsInus);
		//MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("LineInverter"), M_TYPE_BOOLEAN, &LineInverter);
		//MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("LineTermination"), M_TYPE_BOOLEAN, &LineTermination);
		//MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("LineFormat"), M_TYPE_STRING, MIL_TEXT("RS422"));

		// LineSelector 2
		//MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("LineSelector"), M_TYPE_STRING, MIL_TEXT("Line2"));
		//MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("LineMode"), M_TYPE_STRING, MIL_TEXT("Input"));
		//MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("LineDebouncerTimeAbs"), M_TYPE_DOUBLE, &LineDebouncerTimeAbsInus);
		//MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("LineInverter"), M_TYPE_BOOLEAN, &LineInverter);
		//MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("LineTermination"), M_TYPE_BOOLEAN, &LineTermination);
		//MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("LineFormat"), M_TYPE_STRING, MIL_TEXT("RS422"));

		//MIL_DOUBLE AcquisitionLineRateAbsInHz = 2000;
		//MdigControlFeature(MilDigitizer, M_FEATURE_VALUE, MIL_TEXT("AcquisitionLineRateAbs"), M_TYPE_DOUBLE, &AcquisitionLineRate(Abs)InHz);
#else
		// Acquisition Controls
		MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("AcquisitionLineRateAbs"), M_TYPE_DOUBLE, &AcquisitionLineRateAbsInHz);
		MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("ExposureMode"), M_TYPE_STRING, MIL_TEXT("Timed"));
		MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("ExposureTimeAbs"), M_TYPE_DOUBLE, &ExposureTimeAbsInus);
		MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("BinningHorizontal"), M_TYPE_INT64, &BinningHorizontal);
		MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE_AS_STRING, MIL_TEXT("AcquisitionMode"), M_TYPE_ENUMERATION, MIL_TEXT("Continuous"));
		MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("Height"), M_TYPE_INT64, &Height);
		MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("Width"), M_TYPE_INT64, &Width);
		MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("OffsetX"), M_TYPE_INT64, &XOffset);
		MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE_AS_STRING, MIL_TEXT("TestImageSelector"), M_TYPE_ENUMERATION, MIL_TEXT("Off"));

		// AcquisitionStart
		MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("TriggerSelector"), M_TYPE_STRING, MIL_TEXT("AcquisitionStart"));
		MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("TriggerMode"), M_TYPE_STRING, MIL_TEXT("Off"));

		// FrameStart
		MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("TriggerSelector"), M_TYPE_STRING, MIL_TEXT("FrameStart"));
		MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("TriggerMode"), M_TYPE_STRING, MIL_TEXT("On"));
		//MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("TriggerMode"), M_TYPE_STRING, MIL_TEXT("Off"));
		MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("TriggerSource"), M_TYPE_STRING, MIL_TEXT("Line2"));
		//MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("TriggerActivation"), M_TYPE_STRING, MIL_TEXT("LevelLow"));
		MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("TriggerActivation"), M_TYPE_STRING, MIL_TEXT("RisingEdge"));

		// New
		//MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("TriggerActivation"), M_TYPE_STRING, MIL_TEXT("LevelHigh"));
		//MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("TriggerPartialClosingFrame"), M_TYPE_BOOLEAN, &PartialClosingFrame);
		// New

		MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("TriggerDelaySource"), M_TYPE_STRING, MIL_TEXT("Time_us"));
		MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("TriggerDelayAbs"), M_TYPE_DOUBLE, &TriggerDelayAbsInus);

		// LineStart
		MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("TriggerSelector"), M_TYPE_STRING, MIL_TEXT("LineStart"));
		MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("TriggerMode"), M_TYPE_STRING, MIL_TEXT("On"));
		//MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("TriggerMode"), M_TYPE_STRING, MIL_TEXT("Off"));
		MdigControlFeature(MilDigitizer[0], M_FEATURE_EXECUTE, MIL_TEXT("TriggerSoftware"), M_DEFAULT, M_NULL);
		MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("TriggerSource"), M_TYPE_STRING, MIL_TEXT("Line1"));
		MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("TriggerActivation"), M_TYPE_STRING, MIL_TEXT("RisingEdge"));
		//MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("TriggerDelayAbs"), M_TYPE_DOUBLE, &TriggerDelayAbsInus);
		//MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("TriggerDelaySource"), M_TYPE_STRING, MIL_TEXT("Time_us"));

		// LineSelector 1
		MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("LineSelector"), M_TYPE_STRING, MIL_TEXT("Line1"));
		MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("LineMode"), M_TYPE_STRING, MIL_TEXT("Input"));
		MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("LineDebouncerTimeAbs"), M_TYPE_DOUBLE, &LineDebouncerTimeAbsInus);
		MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("LineInverter"), M_TYPE_BOOLEAN, &LineInverter);
		MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("LineTermination"), M_TYPE_BOOLEAN, &LineTermination);
		MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("LineFormat"), M_TYPE_STRING, MIL_TEXT("RS422"));

		// LineSelector 2
		MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("LineSelector"), M_TYPE_STRING, MIL_TEXT("Line2"));
		MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("LineMode"), M_TYPE_STRING, MIL_TEXT("Input"));
		MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("LineDebouncerTimeAbs"), M_TYPE_DOUBLE, &LineDebouncerTimeAbsInus);
		MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("LineInverter"), M_TYPE_BOOLEAN, &LineInverter);
		MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("LineTermination"), M_TYPE_BOOLEAN, &LineTermination);
		MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("LineFormat"), M_TYPE_STRING, MIL_TEXT("RS422"));

		//MIL_DOUBLE AcquisitionLineRateAbsInHz = 2000;
		//MdigControlFeature(MilDigitizer, M_FEATURE_VALUE, MIL_TEXT("AcquisitionLineRateAbs"), M_TYPE_DOUBLE, &AcquisitionLineRate(Abs)InHz);

#endif

		// Final setup
		MdigControl(MilDigitizer[0], M_GRAB_TIMEOUT, M_INFINITE);
		MdigInquire(MilDigitizer[0], M_SIZE_X,    &BufSizeX);
		MdigInquire(MilDigitizer[0], M_SIZE_Y,    &BufSizeY);
		MdigInquire(MilDigitizer[0], M_SIZE_BAND, &BufSizeBand);
		RunThreadData.pHook1->ImageSizeY = BufSizeY;
	}

	// Enable chunk mode. 
	//MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE_AS_STRING, MIL_TEXT("ChunkModeActive"), M_DEFAULT, MIL_TEXT("1"));
	//MdigControlFeature(MilDigitizer[0],  M_FEATURE_VALUE_AS_STRING, MIL_TEXT("ChunkSelector"), M_DEFAULT, MIL_TEXT("Timestamp"));
	//MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE_AS_STRING, MIL_TEXT("ChunkEnable"), M_DEFAULT, MIL_TEXT("1"));

	// Setup End-Detect camera
	if (MilDigitizer[1])
	{
		// Set End-Detect camera parameters
		//--------------------------------------------------------------------------------------------------------------//
		MIL_INT64 YOffset = pSettings->VisSettings2.ROIOffsetY;
		ExposureTimeAbsInus = 600;
		MIL_INT64 EndHeight = 114;
		MIL_DOUBLE AcquisitionFrameRateAbsInHz = 16;
		MdigControlFeature(MilDigitizer[1], M_FEATURE_VALUE, MIL_TEXT("AcquisitionFrameRateAbs"), M_TYPE_DOUBLE, &AcquisitionFrameRateAbsInHz);
		MdigControlFeature(MilDigitizer[1], M_FEATURE_VALUE, MIL_TEXT("TriggerSelector"), M_TYPE_STRING, MIL_TEXT("FrameStart"));
		MdigControlFeature(MilDigitizer[1], M_FEATURE_VALUE, MIL_TEXT("TriggerMode"), M_TYPE_STRING, MIL_TEXT("On"));
		MdigControlFeature(MilDigitizer[1], M_FEATURE_VALUE, MIL_TEXT("Height"), M_TYPE_INT64, &EndHeight);
		MdigControlFeature(MilDigitizer[1], M_FEATURE_VALUE, MIL_TEXT("OffsetY"), M_TYPE_INT64, &YOffset);
		MdigControlFeature(MilDigitizer[1], M_FEATURE_VALUE, MIL_TEXT("ExposureTimeAbs"), M_TYPE_DOUBLE, &ExposureTimeAbsInus);
		MdigControl(MilDigitizer[1], M_GRAB_TIMEOUT, M_INFINITE );
	}

	//// New Camera
	//if (m_NewCamera)
	//{

	//	*pbSplash = FALSE;

	//	// Get Current IP
	//	MIL_INT64 CurrentIPAddress = 0;
	//	MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE_AS_STRING, MIL_TEXT("GevInterfaceSelector"), M_TYPE_ENUMERATION, MIL_TEXT("NetworkInterface0"));
	//	MdigInquireFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("GevCurrentIPAddress"), M_TYPE_INT64, &CurrentIPAddress);

	//	// Get subnet mask
	//	MIL_INT64 CurrentSubnetMask = 0;
	//	MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE_AS_STRING, MIL_TEXT("GevInterfaceSelector"), M_TYPE_ENUMERATION, MIL_TEXT("NetworkInterface0"));
	//	MdigInquireFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("GevCurrentSubnetMask"), M_TYPE_INT64, &CurrentSubnetMask);

	//	// Get Gateway
	//	MIL_INT64 CurrentDefaultGateway = 0;
	//	MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE_AS_STRING, MIL_TEXT("GevInterfaceSelector"), M_TYPE_ENUMERATION, MIL_TEXT("NetworkInterface0"));
	//	MdigInquireFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("GevCurrentDefaultGateway"), M_TYPE_INT64, &CurrentDefaultGateway);

	//	// Set IP
	//	MIL_INT64 FixedIPAddress = CurrentIPAddress; //0xa9fe1acc;
	//	MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE_AS_STRING, MIL_TEXT("GevInterfaceSelector"), M_TYPE_ENUMERATION, MIL_TEXT("NetworkInterface0"));
	//	MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("GevPersistentIPAddress"), M_TYPE_INT64, &FixedIPAddress);

	//	// Set subnet mask
	//	MIL_INT64 FixedSubnetMask = CurrentSubnetMask;  //0xffff0000;
	//	MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE_AS_STRING, MIL_TEXT("GevInterfaceSelector"), M_TYPE_ENUMERATION, MIL_TEXT("NetworkInterface0"));
	//	MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("GevPersistentSubnetMask"), M_TYPE_INT64, &FixedSubnetMask);

	//	// Use  fixed IP,
	//	MIL_INT64 CurrentIPConfiguration = 0x5;
	//	MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE_AS_STRING, MIL_TEXT("GevInterfaceSelector"), M_TYPE_ENUMERATION, MIL_TEXT("NetworkInterface0"));
	//	MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("GevCurrentIPConfiguration"), M_TYPE_INT64, &CurrentIPConfiguration);

	//	// Select User set 1
	//	MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE_AS_STRING, MIL_TEXT("UserSetDefaultSelector"), M_TYPE_ENUMERATION, MIL_TEXT("UserSet1"));
	//	// Save Settings
	//	MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE_AS_STRING, MIL_TEXT("UserSetSelector"), M_TYPE_ENUMERATION, MIL_TEXT("UserSet1"));
	//	MdigControlFeature(MilDigitizer[0], M_FEATURE_EXECUTE, MIL_TEXT("UserSetSave"), M_TYPE_COMMAND, M_NULL);

	//}

	// Show errors
	MILShowError = true;

	// Allocate MIL display buffers	
	MbufAllocColor(MilSystem, 3,IMAGE_SIZE_X+46,IMAGE_SIZE_Y+5,8L+M_UNSIGNED,M_IMAGE+M_PROC+M_DISP,&MilImageFull);
	MbufClear(MilImageFull,0);
	//MbufAllocColor(MilSystem, 3,IMAGE_SIZE_X,IMAGE_SIZE_Y,8L+M_UNSIGNED,M_IMAGE+M_PROC+M_DISP,&MilImage);
	MbufChildColor(MilImageFull, M_ALL_BANDS, &MilImage);
	MbufAllocColor(MilSystem, 3,IMAGE2_SIZE_X,IMAGE2_SIZE_Y,8L+M_UNSIGNED,M_IMAGE+M_PROC+M_DISP,&MilImage2);
	MbufClear(MilImage2,M_RGB888(64,64,64));

	// Work buffers for MilImage and MilImage2
	MbufAllocColor(MilSystem, 3,IMAGE_SIZE_X,IMAGE_SIZE_Y,8L+M_UNSIGNED,M_IMAGE+M_PROC,&MilWorkImage);	
	MbufAllocColor(MilSystem, 3,IMAGE2_SIZE_X,IMAGE2_SIZE_Y,8L+M_UNSIGNED,M_IMAGE+M_PROC,&MilWorkImage2);
	MbufAllocColor(MilSystem, 1,IMAGE_SIZE_X,IMAGE_SIZE_Y,8L+M_UNSIGNED,M_IMAGE+M_PROC,&MilRejectBlobImage);
	m_Blob.MilRejectBlobImage = MilRejectBlobImage;
	MbufClear(MilWorkImage,M_RGB888(64,64,64));

	// End-Detect display buffers
	MbufAllocColor(MilSystem, 3,REJ_IMAGE_SIZE_X,REJ_IMAGE_SIZE_Y,8L+M_UNSIGNED,M_IMAGE+M_PROC+M_DISP,&MilImageReject);
	MbufAllocColor(MilSystem, 3,REJ_IMAGE2_SIZE_X,REJ_IMAGE2_SIZE_Y,8L+M_UNSIGNED,M_IMAGE+M_PROC+M_DISP,&MilImageReject2);
	MbufClear(MilImageReject2,M_RGB888(64,64,64));
	MbufClear(MilImageReject,0);

	// End-Detect work buffers
	MbufAllocColor(MilSystem, 3,REJ_IMAGE_SIZE_X,REJ_IMAGE_SIZE_Y,8L+M_UNSIGNED,M_IMAGE+M_PROC+M_DISP,&MilImageRejectWork);
	MbufChildColor(MilImageRejectWork, M_RED, &MilImageRejectWorkRedBand);
	MbufChildColor(MilImageRejectWork, M_GREEN, &MilImageRejectWorkGreenBand);
	MbufChildColor(MilImageRejectWork, M_BLUE, &MilImageRejectWorkBlueBand);
	MbufAllocColor(MilSystem, 3,REJ_IMAGE2_SIZE_X,REJ_IMAGE2_SIZE_Y,8L+M_UNSIGNED,M_IMAGE+M_PROC+M_DISP,&MilImageRejectWork2);

	// Work buffers
	MbufAlloc2d(MilSystem, IMAGE_SIZE_X,IMAGE_SIZE_Y,8L+M_UNSIGNED,M_IMAGE+M_PROC,&MilHook1.MilRawImage);	
	MbufChild2d(MilHook1.MilRawImage,0,0,IMAGE_SIZE_X,IMAGE_SIZE_Y/2,&MilHook1.MilRawImageTop);
	MbufChild2d(MilHook1.MilRawImage,0,IMAGE_SIZE_Y/2,IMAGE_SIZE_X,IMAGE_SIZE_Y/2,&MilHook1.MilRawImageBot);
	MbufAlloc2d(MilSystem, IMAGE_SIZE_X,IMAGE_SIZE_Y,8L+M_UNSIGNED,M_IMAGE+M_PROC,&MilHook1.MilBinImage);	
	MbufChild2d(MilHook1.MilBinImage,0,0,IMAGE_SIZE_X,IMAGE_SIZE_Y/2,&MilHook1.MilBinImageTop);
	MbufChild2d(MilHook1.MilBinImage,0,IMAGE_SIZE_Y/2,IMAGE_SIZE_X,IMAGE_SIZE_Y/2,&MilHook1.MilBinImageBot);
	MbufAlloc2d(MilSystem, IMAGE_SIZE_X,IMAGE_SIZE_Y/2,8L+M_UNSIGNED,M_IMAGE+M_PROC,&MilHook1.MilBinImageBotSeperation);	

	for (int i=0; i<MAX_RECORD; i++)
	{
		MbufAllocColor(MilSystem, 3,REJ_IMAGE_SIZE_X,REJ_IMAGE_SIZE_Y,8L+M_UNSIGNED,M_IMAGE+M_PROC+M_DISP,&MilRecordImages[i]);
		//MbufClear(MilRecordImages[i],i);
	}

	// Camera 1
	if (MilDigitizer[0])
	{
		MdigInquire(MilDigitizer[0], M_SIZE_X,    &BufSizeX);
		MdigInquire(MilDigitizer[0], M_SIZE_Y,    &BufSizeY);
		MdigInquire(MilDigitizer[0], M_SIZE_BAND, &BufSizeBand);
		TRACE(TEXT("Dig 0 BuffSize X: %d \n"),BufSizeX);
		TRACE(TEXT("Dig 0 BuffSize Y: %d \n"),BufSizeY);
		for (int i=0; i<GRAB_LIST_SIZE; i++)
		{
			MbufAllocColor(MilSystem, BufSizeBand,BufSizeX,BufSizeY,8L+M_UNSIGNED,
				M_IMAGE+M_PROC+M_GRAB,&MilGrabBuff0[i]);
		}	
		//MbufClear(MilImage2,M_RGB888(0,0,0));
	}
	else
	{
		MbufClear(MilImage,M_RGB888(0,0,0));
		MgraFontScale(M_DEFAULT,2.0,2.0);
		MgraColor(M_DEFAULT, M_RGB888(255,0,0));
		MgraBackColor(M_DEFAULT,0);
		_stprintf_s(szText,64,_T("Camera Error!"));
		MgraText(M_DEFAULT, MilImage, 40, 75, szText);	
		MbufClear(MilImage2,M_RGB888(0,0,0));
		MgraFontScale(M_DEFAULT,1.0,1.0);
		MgraColor(M_DEFAULT, M_RGB888(255,0,0));
		MgraBackColor(M_DEFAULT,0);
		_stprintf_s(szText,64,_T("Camera Error!"));
		MgraText(M_DEFAULT, MilImage2, 1, 1, szText);
	}

	// Camera 2 End-Detect
	if (MilDigitizer[1])
	{
		MdigInquire(MilDigitizer[1], M_SIZE_X,    &BufSizeX);
		MdigInquire(MilDigitizer[1], M_SIZE_Y,    &BufSizeY);
		MdigInquire(MilDigitizer[1], M_SIZE_BAND, &BufSizeBand);
		TRACE(TEXT("Dig 1 BuffSize X: %d \n"),BufSizeX);
		TRACE(TEXT("Dig 1 BuffSize Y: %d \n"),BufSizeY);
		TRACE(TEXT("Dig 1 BuffSize BufSizeBand: %d \n"),BufSizeBand);
		for (int i=0; i<GRAB_LIST_SIZE2; i++)
		{
			MbufAllocColor(MilSystem, BufSizeBand,BufSizeX,BufSizeY,8L+M_UNSIGNED,
				M_IMAGE+M_PROC+M_GRAB,&MilGrabBuff1[i]);
		}
		MbufAlloc2d(MilSystem, BufSizeX, BufSizeY, 8+M_UNSIGNED, M_IMAGE+M_PROC, &MilBaconBlobImage);
		MbufClear(MilBaconBlobImage,0);
	}
	else
	{
		MbufClear(MilImageReject,M_RGB888(0,0,0));
		MgraFontScale(M_DEFAULT,2.0,2.0);
		MgraColor(M_DEFAULT, M_RGB888(255,0,0));
		MgraBackColor(M_DEFAULT,0);
		_stprintf_s(szText,64,_T("Camera Error!"));
		MgraText(M_DEFAULT, MilImageReject, 40, 75, szText);	
		MbufClear(MilImageReject2,M_RGB888(0,0,0));
		MgraFontScale(M_DEFAULT,1.0,1.0);
		MgraColor(M_DEFAULT, M_RGB888(255,0,0));
		MgraBackColor(M_DEFAULT,0);
		_stprintf_s(szText,64,_T("Camera Error!"));
		MgraText(M_DEFAULT, MilImageReject2, 1, 1, szText);
	}

	// Linescan Blobs
	m_Blob.Alloc(MilSystem,MilHook1.MilBinImageBot);

	// End-Detect Blobs
	m_EndBlob.Alloc(MilSystem,MilBaconBlobImage);

	// Allocate context for MimLocatePeak1D 
	MimAlloc(MilSystem,M_LOCATE_PEAK_1D_CONTEXT, M_DEFAULT, &MilContext[0]);
	MimAlloc(MilSystem,M_LOCATE_PEAK_1D_CONTEXT, M_DEFAULT, &MilContext[1]);

	// Allocate result for MimLocatePeak1D
	MimAllocResult(MilSystem,M_DEFAULT, M_LOCATE_PEAK_1D_RESULT, &MilLocatePeak[0]);
	MimAllocResult(MilSystem,M_DEFAULT, M_LOCATE_PEAK_1D_RESULT, &MilLocatePeak[1]);
	MimControl(MilLocatePeak[0],M_SORT_CRITERION,HMI_SORT_CRITERION);
	MimControl(MilLocatePeak[1],M_SORT_CRITERION,HMI_SORT_CRITERION);	 

	// Preprocess the context.
	MimControl(MilContext[0],M_NUMBER_OF_PEAKS,MAX_PEAKS);
	MimLocatePeak1d(MilContext[0],MilGrabBuff1[0],MilLocatePeak[0],M_NULL, M_NULL,M_NULL,M_PREPROCESS, M_DEFAULT);

	m_bInitOK = true;
	return m_bInitOK;
}


long MFTYPE CMil::DisplayError(MIL_INT HookType,MIL_ID EventId,void* UserDataPtr)
{
	*m_pbSplash = false;

   MIL_TEXT_CHAR ErrorMessageFunction[M_ERROR_MESSAGE_SIZE] = MIL_TEXT("");
   MIL_TEXT_CHAR ErrorMessage[M_ERROR_MESSAGE_SIZE]         = MIL_TEXT("");
   MIL_TEXT_CHAR ErrorSubMessage1[M_ERROR_MESSAGE_SIZE]     = MIL_TEXT("");
   MIL_TEXT_CHAR ErrorSubMessage2[M_ERROR_MESSAGE_SIZE]     = MIL_TEXT("");
   MIL_TEXT_CHAR ErrorSubMessage3[M_ERROR_MESSAGE_SIZE]     = MIL_TEXT("");
   MIL_INT NbSubCode;
   //CString   CErrorMessage;

   //Retrieve error message [CALL TO MIL]
   MappGetHookInfo(EventId,M_MESSAGE+M_CURRENT_FCT,ErrorMessageFunction);
   MappGetHookInfo(EventId,M_MESSAGE+M_CURRENT,ErrorMessage);
   MappGetHookInfo(EventId,M_CURRENT_SUB_NB,&NbSubCode);   
   
   if (NbSubCode > 2)
      MappGetHookInfo(EventId,M_MESSAGE+M_CURRENT_SUB_3,ErrorSubMessage3);   
   if (NbSubCode > 1)   
      MappGetHookInfo(EventId,M_MESSAGE+M_CURRENT_SUB_2,ErrorSubMessage2);
   if (NbSubCode > 0)
      MappGetHookInfo(EventId,M_MESSAGE+M_CURRENT_SUB_1,ErrorSubMessage1);

   CErrorMessage = ErrorMessageFunction;
   CErrorMessage = CErrorMessage + MIL_TEXT("\r\n"); //"\n";
   CErrorMessage = CErrorMessage + ErrorMessage;
   
   if(NbSubCode > 0)
   {
      CErrorMessage = CErrorMessage + MIL_TEXT("\r\n");
      CErrorMessage = CErrorMessage + ErrorSubMessage1;
   }
   
   if(NbSubCode > 1)
   {
      CErrorMessage = CErrorMessage + MIL_TEXT("\r\n");
      CErrorMessage = CErrorMessage + ErrorSubMessage2;
   }
   
   if(NbSubCode > 2)
   {
      CErrorMessage = CErrorMessage + MIL_TEXT("\r\n");
      CErrorMessage = CErrorMessage + ErrorSubMessage3;
   }
   
   CErrorMessage = CErrorMessage + MIL_TEXT("\r\n\n");
   MilErrorMessageCount++;
   TRACE(_T("%s\n"),CErrorMessage);

#ifdef _DEBUG
   if (MILShowError) AfxMessageBox(CErrorMessage);
#endif

   	//m_strErrors.SetSize (MAX_MIL_ERRORS);
	//if (m_nErrorCount < MAX_MIL_ERRORS)
	//{
	//	m_strErrors[m_nErrorCount++] = CErrorMessage;
	//}

	// Save the fault to a file 
	m_History.AddString(CErrorMessage);
	//m_History.SaveStrings();

   return 0;

   //CErrorMessage = CErrorMessage + MIL_TEXT("Do you want to continue error print?");
   //return (AfxMessageBox(CErrorMessage,MB_YESNO,0) == IDYES)?M_YES:M_NO;
}

//----------------------------------------------------------------------
// StartDigitizer - Start grabbing.
//
//-----------------------------------------------------------------------
void CMil::StartDigitizer(void)
{	
	if (!m_bInitOK)
		return;
	if (MilDigitizer[0] == M_NULL)
	{
		TRACE("Steering Digitizer not found! ............................................................\n");
		return;
	} 
	if (MilDigitizer[1] == M_NULL)
	{
		TRACE("End-Detect Digitizer not found! ............................................................\n");
		return;
	} 
	TRACE("Start the digitizer.............................................................\n");

	//AfxMessageBox(_T("Start... I am here!!!!"));
	//RunThreadData.dbMaxProcSide = 0;
	//MsysControl(M_DEFAULT_HOST,TRIGGER_SELECT, M_ON);
	//CHMIApp* pApp = (CHMIApp*)AfxGetApp();
	
	// Start Digitizer 1 (Steering)
	//MilHook1.FirstImage           = true;
	MilHook1.MainPage             = true;
	MilHook1.nID                  = 1;
	MilHook1.dbTimePrev           = 0;
	MilHook1.PeriodMax            = 0;
	MilHook1.PeriodMin            = 0;
	MilHook1.Period               = 0;
	MilHook1.MaxProcTime          = 0;		
	MilHook1.MaxComTime			  = 0;
	//MilHook1.ResyncCount          = 0;
	MilHook1.ComTime              = 0;
	MilHook1.TotalBlobCount       = 0;
	//MilHook1.TotalBaconCount      = 0;
	MilHook1.SuppressionCount     = 0;
	//MilHook1.BaconSpeedFrameCount = 0;
	MilHook1.LockSize             = 0;
	MilHook1.Position             = 0;
	MilHook1.BaconSpeed           = 0;
	MilHook1.MaxComPeriod         = 0;
	MilHook1.MaxTimeStampRes      = 0;
	//MilHook1.TimeStampErrorCount  = 0;
	MilHook1.ImageCount           = 0;
	MilHook1.nModifyedBuffID      = M_NULL;
	MilHook1.MilWorkImage		  = MilWorkImage;
	MilHook1.MilWorkImage2	      = MilWorkImage2;
	MilHook1.MilRejectBlobImage   = MilRejectBlobImage;	
	MilHook1.MilDigitizer         = MilDigitizer[0];
	MilHook1.MilImage             = MilImage;
	MilHook1.MilImage2            = MilImage2;
	//MilHook1.pBaconBuff           = NULL;
	//MilHook1.BufferSelect         = 0;
	MilHook1.CmdListId            = CmdListId;
	MilHook1.LastReferenceStamp   = 0;
	//MilHook1.SteerTriggerOn            = true;
	MilHook1.MilSystem            = MilSystem;
	MilHook1.StopDigitizer        = false;
	MilHook1.EndDetected          = false;
	MilHook1.EndDetectedLatch     = false;
	
	// Steering
	if (MilDigitizer[0])
	{
		MdigProcess(MilDigitizer[0], MilGrabBuff0, GRAB_LIST_SIZE, M_START,M_DEFAULT, GrabHookHandlerCount, (void*)&MilHook1);
	}

	// Create a worker thread and dublicate the thread handle for later use
	RunThreadData.Running = true;
	RunThreadData.MilImage = MilImage;
	RunThreadData.MilImage2 = MilImage2;
	RunThreadData.MilWorkImage = MilWorkImage;
	RunThreadData.MilWorkImage2 = MilWorkImage2;
	RunThreadData.MilRejectBlobImage   = MilRejectBlobImage;
	CWinThread* pThread = AfxBeginThread (ComRelayThreadFunc, &RunThreadData,THREAD_PRIORITY_NORMAL,CREATE_SUSPENDED);
	//CWinThread* pThread = AfxBeginThread (ComRelayThreadFunc, &RunThreadData,THREAD_PRIORITY_ABOVE_NORMAL,CREATE_SUSPENDED);
	pThread->ResumeThread();
    //::DuplicateHandle (GetCurrentProcess(), pThread->m_hThread,GetCurrentProcess(), &m_hThread0, 0, FALSE, DUPLICATE_SAME_ACCESS);

	// Enable the interrupts
	MsysControl(M_DEFAULT_HOST, M_IO_INTERRUPT_STATE + M_AUX_IO9, M_ENABLE);

	// Start Digitizer 2 (End-Detect)
	MilHook2.pHook1               = &MilHook1;
	MilHook2.MainPage             = true;
	MilHook2.nID                  = 2;
	MilHook2.dbTimePrev           = 0;
	MilHook2.PeriodMax            = 0;
	MilHook2.PeriodMin            = 0;
	MilHook2.Period               = 0;
	MilHook2.MaxProcTime          = 0;	
	MilHook2.MilImage             = MilImageReject;
	MilHook2.MilImage2            = MilImageReject2;
	MilHook2.Context              = MilContext[0];
	MilHook2.LocatePeak           = MilLocatePeak[0];
	MilHook2.MilBaconBlobImage    = MilBaconBlobImage;
	MilHook2.pShearBarData        = &m_ShearBarData[0];
	MilHook2.pBlob                = &m_EndBlob;
	MilHook2.EndDetectLockCount   = 0;
	MilHook2.GapDetectLatchCount  = 0;
	MilHook2.EndDetectLockCountReset     = true;
	MilHook2.RecordIndex          = MAX_RECORD;
	MilHook2.PlayIndex            = 0;
	MilHook2.RecordEndCount       = 0;
	MilHook2.PlayImages           = false;
	MilHook2.ImagesRecorded       = 0;
	MilHook2.MilImageRejectWork          = MilImageRejectWork;
	MilHook2.MilImageRejectWork2          = MilImageRejectWork2;
	MilHook2.MilImageRejectWorkRedBand   = MilImageRejectWorkRedBand;
	MilHook2.MilImageRejectWorkGreenBand = MilImageRejectWorkGreenBand;
	MilHook2.MilImageRejectWorkBlueBand  = MilImageRejectWorkBlueBand;
	MilHook2.MilRecordImages             = MilRecordImages;

	if (MilDigitizer[1])
	{
		MdigProcess(MilDigitizer[1], MilGrabBuff1, GRAB_LIST_SIZE2, M_START,M_DEFAULT, GrabHookHandlerEndDetect, (void*)&MilHook2);
	}

}
//----------------------------------------------------------------------
// StopDigitizer - Stop grabbing.
//
//-----------------------------------------------------------------------
void CMil::StopDigitizer(void)
{
	if (!RunThreadData.Running)
		return;

	// Disable the interrupts
	MsysControl(M_DEFAULT_HOST, M_IO_INTERRUPT_STATE + M_AUX_IO9, M_DISABLE);

	if (MilHook1.IoFunctionHooked) MsysHookFunction(M_DEFAULT_HOST, M_IO_CHANGE+M_UNHOOK, IoHookFunction, &MilHook1);
	MilHook1.IoFunctionHooked = false;	

	TRACE("Stop the digitizer.............................................................\n");
	MilHook1.StopDigitizer = true;
	MilHook1.CritSect.Lock();

	// Stop Digitizer 2
	if (MilDigitizer[1]) MdigProcess(MilDigitizer[1], MilGrabBuff1, GRAB_LIST_SIZE2, M_STOP, M_DEFAULT, GrabHookHandlerEndDetect, (void*)&MilHook2);
	//AfxMessageBox(_T("Stop the dig.. I am here!!!!"));

	// Stop Digitizer 1
	RunThreadData.Running = false;
	MilHook1.GrabEvent.SetEvent();
	if (MilDigitizer[0]) MdigProcess(MilDigitizer[0], MilGrabBuff0, GRAB_LIST_SIZE, M_STOP, M_DEFAULT, GrabHookHandlerCount, (void*)&MilHook1);
	//AfxMessageBox(_T("Stop the dig.. I am here!!!!"));
	RunThreadData.EventExit.Lock();

	MilHook1.CritSect.Lock();

}
//----------------------------------------------------------------------
// UnHookQue - Stop que.
//
//-----------------------------------------------------------------------
void CMil::UnHookQue(void)
{
	MilHook1.StartQue = false;
	if (MilHook1.IoFunctionHooked) MsysHookFunction(M_DEFAULT_HOST, M_IO_CHANGE+M_UNHOOK, IoHookFunction, &MilHook1);
	MilHook1.IoFunctionHooked = false;	
	TRACE("UnHookQue.............................................................\n");
}
//----------------------------------------------------------------------
// HookQue - Stop que.
//
//-----------------------------------------------------------------------
void CMil::HookQue(void)
{
	//MilHook1.IoFunctionHooked = false;	
	MilHook1.StartQueCount = 0;
	if (MilHook1.IoFunctionHooked) MsysHookFunction(M_DEFAULT_HOST, M_IO_CHANGE+M_UNHOOK, IoHookFunction, &MilHook1);
	MilHook1.IoFunctionHooked = false;	
	MilHook1.StartQue = true;	
	TRACE("HookQue.............................................................\n");
}

//======================================================================================================//
// Function Name: ApplySettings ()                                                         //
//                                                                                                      //
//======================================================================================================//
void CMil::ApplySettings()
{
	MIL_INT64 YOffset;
	MIL_DOUBLE ExposureTimeAbsInus;
	MIL_DOUBLE AcquisitionLineRateAbsInHz;

	if (MilDigitizer[1] == M_NULL) return;

	// Shear Bar data points
	//--------------------------------------------------//
	CreateShearBarPoints();

	// End-Detect Camera settings
	YOffset = MilHook1.pSettings->VisSettings2.ROIOffsetY;
	ExposureTimeAbsInus = MilHook1.pSettings->VisSettings2.Exposure_uS;  //  600;
	if (MilHook1.pSettings->VisSettings2.TriggerOn == 1)
	{
		MdigControlFeature(MilDigitizer[1], M_FEATURE_VALUE, MIL_TEXT("TriggerMode"), M_TYPE_STRING, MIL_TEXT("On"));
	}
	else
	{
		MdigControlFeature(MilDigitizer[1], M_FEATURE_VALUE, MIL_TEXT("TriggerMode"), M_TYPE_STRING, MIL_TEXT("Off"));
	}
	MdigControlFeature(MilDigitizer[1], M_FEATURE_VALUE, MIL_TEXT("OffsetY"), M_TYPE_INT64, &YOffset);
	MdigControlFeature(MilDigitizer[1], M_FEATURE_VALUE, MIL_TEXT("ExposureTimeAbs"), M_TYPE_DOUBLE, &ExposureTimeAbsInus);
	MdigControl(MilDigitizer[1], M_GRAB_TIMEOUT, M_INFINITE);
	//--------------------------------------------------//

	// Steering
	//--------------------------------------------------//
	if (MilDigitizer[0] == M_NULL) return;
	ExposureTimeAbsInus        = MilHook1.pSettings->VisSettings1.Exposure_uS;

//	pApp->m_Settings.MotionSettings1.dbPvars[7] = data.dbValue;
	MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("ExposureTimeAbs"), M_TYPE_DOUBLE, &ExposureTimeAbsInus);

#ifndef OSCEOLA_LAYOUT
	if (MilHook1.pSettings->VisSettings1.Trigger == 1)
	{
		// FrameStart
		MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("TriggerSelector"), M_TYPE_STRING, MIL_TEXT("FrameStart"));
		MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("TriggerMode"), M_TYPE_STRING, MIL_TEXT("On"));

		// LineStart
		MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("TriggerSelector"), M_TYPE_STRING, MIL_TEXT("LineStart"));
		MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("TriggerMode"), M_TYPE_STRING, MIL_TEXT("On"));
		
	}
	else
	{
		// FrameStart
		MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("TriggerSelector"), M_TYPE_STRING, MIL_TEXT("FrameStart"));
		MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("TriggerMode"), M_TYPE_STRING, MIL_TEXT("Off"));

		// LineStart
		MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("TriggerSelector"), M_TYPE_STRING, MIL_TEXT("LineStart"));
		MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("TriggerMode"), M_TYPE_STRING, MIL_TEXT("Off"));
		TRACE("ApplySettingsTrigger Off...%d \n",MilHook1.pSettings->VisSettings1.Trigger);
	
	}
	MdigControl(MilDigitizer[0], M_GRAB_TIMEOUT, M_INFINITE);
	//--------------------------------------------------//
#else
	TRACE("Mil ApplySettings  BladeSpeed%f \n",MilHook1.pSettings->MotionSettings1.dbPvars[7]);
	AcquisitionLineRateAbsInHz = MilHook1.pSettings->MotionSettings1.dbPvars[7]*MilHook1.pSettings->VisSettings1.dbLineRateScaleFactor;
	if (AcquisitionLineRateAbsInHz < 250) AcquisitionLineRateAbsInHz = 250;
	if (AcquisitionLineRateAbsInHz > 6000) AcquisitionLineRateAbsInHz = 6000;
	TRACE("Line Rate %f \n",AcquisitionLineRateAbsInHz);
	MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("AcquisitionLineRateAbs"), M_TYPE_DOUBLE, &AcquisitionLineRateAbsInHz);

#endif

	//TRACE("\n\n\n\n ApplySettings \n");	
}

/////////////////////////////////////////////////////////////////////////////////
// Functon: FillData()
//
// Description: This function fills in all data points between two points.
// 
//
/////////////////////////////////////////////////////////////////////////////////.
void CMil::FillData(double X0,double Y0,double X1,double Y1, int* Data)
{
	double y;

	if (X0 < 0) X0 = 0;
	if (X1 < 0) X1 = 0;
	if (X0 >= TOTAL_SBAR_POINTS) X0 = TOTAL_SBAR_POINTS-1;
	if (X1 >= TOTAL_SBAR_POINTS) X1 = TOTAL_SBAR_POINTS-1;

	for (int x=(int)X0; x< X1; x++)
	{
		if (X1==X0)
		{
			Data[x] = 0;		
		}
		else
		{
			y = Y0 + (x-X0)*((Y1-Y0)/(X1-X0));
			Data[x] = (int)y;		
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////
// Functon: ShowLanes()
//
// Description: This function shows the reject lanes.
// 
//
/////////////////////////////////////////////////////////////////////////////////.
void CMil::ShowLanes()
{
	//MIL_INT SizeY = 0;
	//m_OverlayOn = true;
	//MdispControl(MilDisplay, M_OVERLAY_SHOW, M_DISABLE);        // Disable the overlay display update to accelerate annotations. 
	//MdispControl(MilDisplay, M_OVERLAY, M_ENABLE);
	//MdispInquire(MilDisplay, M_OVERLAY_ID, &MilOverlayImage);
	//MdispControl(MilDisplay, M_OVERLAY_CLEAR, M_DEFAULT);       // Clear the overlay to transparent.
	//MgraColor(M_DEFAULT, M_COLOR_GREEN);
	//MbufInquire(MilOverlayImage, M_SIZE_Y,&SizeY);
	//TRACE("Overlay size %d \n",SizeY);

	//MgraLine(M_DEFAULT, MilOverlayImage, MilHook1.pSettings->VisSettings2.PosLane1, 0,MilHook1.pSettings->VisSettings2.PosLane1,SizeY);
	//MgraLine(M_DEFAULT, MilOverlayImage, MilHook1.pSettings->VisSettings2.PosLane2, 0,MilHook1.pSettings->VisSettings2.PosLane2,SizeY);
	//MgraLine(M_DEFAULT, MilOverlayImage, MilHook1.pSettings->VisSettings2.PosLane3, 0,MilHook1.pSettings->VisSettings2.PosLane3,SizeY);
	//MgraLine(M_DEFAULT, MilOverlayImage, MilHook1.pSettings->VisSettings2.PosLane4, 0,MilHook1.pSettings->VisSettings2.PosLane4,SizeY);
	//MgraLine(M_DEFAULT, MilOverlayImage, MilHook1.pSettings->VisSettings2.PosLane5, 0,MilHook1.pSettings->VisSettings2.PosLane5,SizeY);
	//MgraLine(M_DEFAULT, MilOverlayImage, MilHook1.pSettings->VisSettings2.PosLane6, 0,MilHook1.pSettings->VisSettings2.PosLane6,SizeY);
	//MgraLine(M_DEFAULT, MilOverlayImage, MilHook1.pSettings->VisSettings2.PosLane7, 0,MilHook1.pSettings->VisSettings2.PosLane7,SizeY);

	//MdispControl(MilDisplay, M_OVERLAY_SHOW, M_ENABLE);

}
/////////////////////////////////////////////////////////////////////////////////
// Functon: ShowLanes()
//
// Description: This function shows the reject lanes.
// 
//
/////////////////////////////////////////////////////////////////////////////////.
void CMil::HideLanes()
{
	//m_OverlayOn = false;
	//MdispControl(MilDisplay, M_OVERLAY_SHOW, M_DISABLE);
}

//======================================================================================================//
// Function Name: ComRelayThreadFunc (LPVOID pParam)                                                     //
//                                                                                                      //
//======================================================================================================//
UINT ComRelayThreadFunc (LPVOID pParam)                                                                      
{            
	RUNTHREADDATASTRUCT* pRunData = (RUNTHREADDATASTRUCT*) pParam;
	CEvent* pEventCamera1 = &pRunData->pHook1->GrabEvent;
	CEvent* pEventPlay = &pRunData->PlayEvent;
	pRunData->MaxDisplayTime = 0;
	//MIL_DOUBLE dbST,dbET;
	CHMIApp* pApp = (CHMIApp*)AfxGetApp();
	CWnd* pWnd = pApp->m_pWndView;

	// Run
	//============================================================================================================//
	while (pRunData->Running)
	{
		// Wait on camera
		pEventCamera1->Lock();

		// Still in Run mode?
		if (!pRunData->Running) break;

		// Start of communications time
		//MappTimer(M_TIMER_READ, &dbST);
		
		// Do PMAC communications
		if (pWnd != NULL && pRunData->pHook1->PmacComComplete)
		{
		    //TRACE("PostMessage (WM_DO_PMAC_COMMUNICATONS... \n");
			pRunData->pHook1->PmacComComplete = false;
			pWnd->PostMessage (WM_DO_PMAC_COMMUNICATONS,1,0);
			//pWnd->PostMessage (WM_DO_PMAC_COMMUNICATONS,(WPARAM)pRunData->pHook1->pBaconBuff,0);
		}
 
		// End of comunicatoins time
		//MappTimer(M_TIMER_READ, &dbET);
		//TRACE("Draw Time: %4.3f \n",(dbET-dbST)*1000);
		//dbET = (dbET-dbST)*1000.0;
		//if ((int)dbET > pRunData->MaxDisplayTime)
		//{
		//	pRunData->MaxDisplayTime = (int)dbET;
		//}
		//pRunData->pMilWnd->m_nDisplayTime = pRunData->MaxDisplayTime;
		//TRACE("Period %f  \n",pRunData->pHook1->Period);
		//TRACE("Period %f Min \n",pRunData->pHook1->PeriodMin);
		//TRACE("Period %f Max \n",pRunData->pHook1->PeriodMax);
	}

	TRACE("Display Thread Exit\n");
	pRunData->EventExit.SetEvent();

	return 0;                                                                                                       
}

//======================================================================================================//
// Function Name: CreateShearBarPoints ()                                                     //
//                                                                                                      //
//======================================================================================================//
void CMil::CreateShearBarPoints()
{

	MIL_ID MilOverlayImage;

	m_X[0] = MilHook1.pSettings->VisSettings2.x[0]; m_Y[0] = MilHook1.pSettings->VisSettings2.y[0];
	m_X[1] = MilHook1.pSettings->VisSettings2.x[1]; m_Y[1] = MilHook1.pSettings->VisSettings2.y[1];
	m_X[2] = MilHook1.pSettings->VisSettings2.x[2]; m_Y[2] = MilHook1.pSettings->VisSettings2.y[2];
	m_X[3] = MilHook1.pSettings->VisSettings2.x[3]; m_Y[3] = MilHook1.pSettings->VisSettings2.y[3];
	m_X[4] = MilHook1.pSettings->VisSettings2.x[4]; m_Y[4] = MilHook1.pSettings->VisSettings2.y[4];


	FillData(      0,m_Y[0],m_X[0],m_Y[0],m_ShearBarData);
	FillData( m_X[0],m_Y[0],m_X[1],m_Y[1],m_ShearBarData);
	FillData( m_X[1],m_Y[1],m_X[2],m_Y[2],m_ShearBarData);
	FillData( m_X[2],m_Y[2],m_X[3],m_Y[3],m_ShearBarData);
	FillData( m_X[3],m_Y[3],m_X[4],m_Y[4],m_ShearBarData);
	FillData( m_X[4],m_Y[4],TOTAL_SBAR_POINTS-1,m_Y[4],m_ShearBarData);

	// Overlay control 
	MdispControl(MilRejectDisplay, M_OVERLAY_SHOW, M_DISABLE);        // Disable the overlay display update to accelerate annotations. 
	MdispControl(MilRejectDisplay, M_OVERLAY, M_ENABLE);
	MdispInquire(MilRejectDisplay, M_OVERLAY_ID, &MilOverlayImage);
	MdispControl(MilRejectDisplay, M_OVERLAY_CLEAR, M_DEFAULT);       // Clear the overlay to transparent.
	
	MgraColor(M_DEFAULT, M_COLOR_GREEN);
	MgraLine(M_DEFAULT, MilOverlayImage,0,m_Y[0],m_X[0],m_Y[0]);
	MgraLine(M_DEFAULT, MilOverlayImage,m_X[0],m_Y[0],m_X[1],m_Y[1]);
	MgraLine(M_DEFAULT, MilOverlayImage,m_X[1],m_Y[1],m_X[2],m_Y[2]);

	MgraLine(M_DEFAULT, MilOverlayImage,m_X[2],m_Y[2],m_X[3],m_Y[3]);
	MgraLine(M_DEFAULT, MilOverlayImage,m_X[3],m_Y[3],m_X[4],m_Y[4]);

	MgraLine(M_DEFAULT, MilOverlayImage,m_X[4],m_Y[4],TOTAL_SBAR_POINTS-1,m_Y[4]);

	m_OverlayOn = false;

}
void CMil::ShowShearBarPoints()
{
	m_OverlayOn = true;
	MdispControl(MilRejectDisplay, M_OVERLAY_SHOW, M_ENABLE);        // Disable the overlay display update to accelerate annotations. 
	//MdispControl(MilRejectDisplay, M_OVERLAY, M_ENABLE);
}
void CMil::HideShearBarPoints()
{
	m_OverlayOn = false;
	MdispControl(MilRejectDisplay, M_OVERLAY_SHOW, M_DISABLE);        // Disable the overlay display update to accelerate annotations. 
	//MdispControl(MilRejectDisplay, M_OVERLAY, M_DISABLE);
}
//----------------------------------------------------------------------
// InitMilCom
//
//-----------------------------------------------------------------------
int CMil::InitMilCom()
{	
	//static int WaitTime = 30;
	static int WaitTime = 3;
	//int WaitTime = 4;
	double dbTimeET;
	CHMIApp* pApp = (CHMIApp*)AfxGetApp();

	// Read Start time
	if (m_dbComAllocTimeST == 0)
	{
		MappTimer(M_TIMER_READ, &m_dbComAllocTimeST);
		return 1;
	}
	
	// Allocate industrial communicatons module
	if (MilCom == M_NULL)
	{
		MappTimer(M_TIMER_READ, &dbTimeET);
		dbTimeET = dbTimeET - m_dbComAllocTimeST; 

#ifdef _DEBUG
		WaitTime = 2;
#endif
		if (dbTimeET > WaitTime)
		{
			MappTimer(M_TIMER_READ, &m_dbComAllocTimeST);
			//AfxMessageBox(_T("McomAlloc... "));
			McomAlloc(M_DEFAULT_HOST, M_COM_PROTOCOL_ETHERNETIP, M_NULL, M_DEFAULT, M_DEFAULT, &MilCom);
			MIL_BOOL State;
			McomInquire(MilCom,M_COM_GET_CONNECTION_STATE,&State);
			if (State==M_FALSE)
			{
				 McomFree(MilCom);
				 MappTimer(M_TIMER_READ, &m_dbComAllocTimeST);
				 MilCom = M_NULL;
				 //AfxMessageBox(_T("MilCom Free"));
			}

			::ZeroMemory (&m_ReadData, sizeof (m_ReadData));
			::ZeroMemory (&m_WriteData, sizeof (m_WriteData));		
			MappTimer(M_TIMER_READ, &dbTimeET);
			dbTimeET = dbTimeET - m_dbComAllocTimeST; 
			TRACE("McomAlloc Time: %4.3f \n",dbTimeET);
		}
		return 2;
	}

	return 0;
}

//----------------------------------------------------------------------
// ReadWriteComData - Called to read and write com data.
//
//-----------------------------------------------------------------------
int CMil::ReadWriteComData()
{	
	int Status = 3;
	int WaitTime = 30;
	//double dbTimeET;
	CHMIApp* pApp = (CHMIApp*)AfxGetApp();

	// Init
	if (InitMilCom()) return Status;

	// Read and write the data
	McomRead(MilCom, M_COM_ETHERNETIP_CONSUMER, 0, sizeof(m_ReadData), &m_ReadData);
	if (m_WriteData.HeartBeat == m_ReadData.HeartBeat)
	{
		Status = 0;
	}
	m_WriteData.HeartBeat = m_ReadData.HeartBeat + 1;
	McomWrite(MilCom, M_COM_ETHERNETIP_PRODUCER , 0, sizeof(m_WriteData), &m_WriteData);

	return Status;
	//MappTimer(M_TIMER_READ, &dbTimeET);
	//TRACE(_T("\n\nm_WriteData Size:............................................................... %d \n"),sizeof(m_WriteData));
	//TRACE(_T("Size: %d \n"),sizeof(m_ReadData));
	//TRACE(_T("Time: %f DATA: %d \n"),(dbTimeET-dbTimeST)*1000,m_ReadData.Echo);

}

//----------------------------------------------------------------------
// SetupCameras IP - Set IP
//
//-----------------------------------------------------------------------
void CMil::SetupCameraIP(MIL_INT64 FixedIPAddress)
{
	//MIL_BOOL LineInverter                 = M_FALSE;
	//MIL_BOOL LineTermination              = M_TRUE;
	//MIL_DOUBLE AcquisitionLineRateAbsInHz = MilHook.pSettings->VisSettings1.LineRate;
	//MIL_DOUBLE ExposureTimeAbsInus        = MilHook.pSettings->VisSettings1.dbExposure_uS;
 //   MIL_DOUBLE LineDebouncerTimeAbsInus   = 0;
	//MIL_INT64 BinningHorizontal           = 2;
	//MIL_INT64 Width                       = CAMERA_SIZE_X;
	//MIL_INT64 Height                      = CAMERA_SIZE_Y;
	//MIL_INT64 XOffset                     = CAMERA0_OFFSET;
	//MIL_DOUBLE LineOutputPulseMinWidthInus = 0;

	// Get Current IP
	MIL_INT64 CurrentIPAddress = 0;
	MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE_AS_STRING, MIL_TEXT("GevInterfaceSelector"), M_TYPE_ENUMERATION, MIL_TEXT("NetworkInterface0"));
	MdigInquireFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("GevCurrentIPAddress"), M_TYPE_INT64, &CurrentIPAddress);
	TRACE(_T("IP:%x \n"),CurrentIPAddress);

	// Get subnet mask
	MIL_INT64 CurrentSubnetMask = 0;
	MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE_AS_STRING, MIL_TEXT("GevInterfaceSelector"), M_TYPE_ENUMERATION, MIL_TEXT("NetworkInterface0"));
	MdigInquireFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("GevCurrentSubnetMask"), M_TYPE_INT64, &CurrentSubnetMask);
	TRACE(_T("CurrentSubnetMask:%x \n"),CurrentSubnetMask);

	// Get Gateway
	MIL_INT64 CurrentDefaultGateway = 0;
	MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE_AS_STRING, MIL_TEXT("GevInterfaceSelector"), M_TYPE_ENUMERATION, MIL_TEXT("NetworkInterface0"));
	MdigInquireFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("GevCurrentDefaultGateway"), M_TYPE_INT64, &CurrentDefaultGateway);
	TRACE(_T("CurrentDefaultGateway:%x \n"),CurrentDefaultGateway);

	// Use  fixed IP,
	MIL_INT64 CurrentIPConfiguration = 0;
	MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE_AS_STRING, MIL_TEXT("GevInterfaceSelector"), M_TYPE_ENUMERATION, MIL_TEXT("NetworkInterface0"));
	MdigInquireFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("GevCurrentIPConfiguration"), M_TYPE_INT64, &CurrentIPConfiguration);
	TRACE(_T("CurrentIPConfiguration:%x \n"),CurrentIPConfiguration);

	// Set IP
	//MIL_INT64 FixedIPAddress = 0xa9fefe01;
	MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE_AS_STRING, MIL_TEXT("GevInterfaceSelector"), M_TYPE_ENUMERATION, MIL_TEXT("NetworkInterface0"));
	MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("GevPersistentIPAddress"), M_TYPE_INT64, &FixedIPAddress);

	// Set subnet mask
	MIL_INT64 FixedSubnetMask = 0xffff0000;
	MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE_AS_STRING, MIL_TEXT("GevInterfaceSelector"), M_TYPE_ENUMERATION, MIL_TEXT("NetworkInterface0"));
	MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("GevPersistentSubnetMask"), M_TYPE_INT64, &FixedSubnetMask);

	// Use  fixed IP,
	CurrentIPConfiguration = 0x5;
	MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE_AS_STRING, MIL_TEXT("GevInterfaceSelector"), M_TYPE_ENUMERATION, MIL_TEXT("NetworkInterface0"));
	MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE, MIL_TEXT("GevCurrentIPConfiguration"), M_TYPE_INT64, &CurrentIPConfiguration);

	// Select User set 1
	MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE_AS_STRING, MIL_TEXT("UserSetDefaultSelector"), M_TYPE_ENUMERATION, MIL_TEXT("UserSet1"));

	// Save Settings
	MdigControlFeature(MilDigitizer[0], M_FEATURE_VALUE_AS_STRING, MIL_TEXT("UserSetSelector"), M_TYPE_ENUMERATION, MIL_TEXT("UserSet1"));
	MdigControlFeature(MilDigitizer[0], M_FEATURE_EXECUTE, MIL_TEXT("UserSetSave"), M_TYPE_COMMAND, M_NULL);


}

