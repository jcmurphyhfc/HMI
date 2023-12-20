#include "StdAfx.h"
#include "HookFunctions.h"
#include "MilObj.h"

//----------------------------------------------------------------------//
// IO Interrupt hook function.
//----------------------------------------------------------------------//
MIL_INT MFTYPE IoHookFunction(MIL_INT HookType, MIL_ID EventId, void *UserDataPtr)
{
   COUNTHOOKDATASTRUCT1* pHookParam = (COUNTHOOKDATASTRUCT1*)UserDataPtr;
   MIL_INT PinNb = 0;
   MIL_INT64 RefStamp;

   // Check if the callback is for M_AUX_IO9
   MsysGetHookInfo(M_DEFAULT_HOST, EventId, M_IO_INTERRUPT_SOURCE, &PinNb);
   //if ((PinNb == M_AUX_IO9) && (pHookParam->FirstImage==false))
   if ((PinNb == M_AUX_IO9))
   {
      MsysGetHookInfo(M_DEFAULT_HOST, EventId,M_REFERENCE_LATCH_VALUE+M_IO_COMMAND_LIST1+M_LATCH1, &RefStamp);
	  pHookParam->CritSect.Lock();

	  //MIL_INT64 diff = RefStamp-pHookParam->LastReferenceStamp;
	  //TRACE("Save RefStamp: %d  ",RefStamp);
	  //TRACE("Change: %d\n",diff);

	  pHookParam->LastReferenceStamp = RefStamp;
	  pHookParam->QueueBacon.push((long)RefStamp);
  	  //TRACE("Save RefStamp: %d \n",RefStamp);
	  pHookParam->CritSect.Unlock();
   }
   return M_NULL;
}
//----------------------------------------------------------------------//

//----------------------------------------------------------------------
// GrabHookHandlerEnd - Process grabed image.
//
//-----------------------------------------------------------------------
MIL_INT MFTYPE GrabHookHandlerCount(MIL_INT HookType, MIL_ID EventId, void* UserDataPtr) 
{
	//TRACE("GrabHookHandlerCount... \n");
	COUNTHOOKDATASTRUCT1* ptrHookData = (COUNTHOOKDATASTRUCT1*)UserDataPtr;
	VISIONSETTINGS1*      pSettings   = &ptrHookData->pSettings->VisSettings1;
	VISIONSETTINGS2*      pSettings2  = &ptrHookData->pSettings->VisSettings2;
	VISIONSETTINGS3*      pSettings3  = &ptrHookData->pSettings->VisSettings3;
	MOTIONSETTINGS*       pMotion     = &ptrHookData->pSettings->MotionSettings1;
	MIL_ID                ModifiedBufferId;
	double                dbTime;
	double                dbProcTime;
	MIL_INT               Status = 0;
	int                   BlobCount;
	bool*                 pRunning = ptrHookData->pRunning;
	MIL_INT64             ReferenceStamp = 0;
	MIL_INT64             ReferenceStampInq = 0;
	MIL_INT64             ReferenceStampDiff = 0; 
	MIL_DOUBLE            Delay;
	MIL_DOUBLE            Duration;
	MIL_INT64             BitPos;
	double                AveBacPos;

	// Measure time
	MappTimer(M_TIMER_READ, &dbTime);
	if (ptrHookData->dbTimePrev)
	{
		ptrHookData->Period = (dbTime - ptrHookData->dbTimePrev)*1000;
		if (ptrHookData->PeriodMax == 0) ptrHookData->PeriodMax = ptrHookData->Period;
		if (ptrHookData->PeriodMin == 0) ptrHookData->PeriodMin = ptrHookData->Period;
		if (ptrHookData->Period > ptrHookData->PeriodMax) ptrHookData->PeriodMax = ptrHookData->Period;
		if (ptrHookData->Period < ptrHookData->PeriodMin) ptrHookData->PeriodMin = ptrHookData->Period;
	}
	ptrHookData->dbTimePrev = dbTime;
	
	// Count
	ptrHookData->ImageCount++;

	// Exit if the digitizer is going to stop
	//---------------------------------------------------//
	if (ptrHookData->StopDigitizer)
	{
		TRACE("Exit on  Stop Dig\n");
		return 0;
	}
	//---------------------------------------------------//

	// Hook the que function
	//---------------------------------------------------//
	if (ptrHookData->StartQue)
	{
		if (!ptrHookData->IoFunctionHooked)
		{
			if (ptrHookData->QueueBacon.size() > 0 || ptrHookData->StartQueCount < 10)
			{
				ptrHookData->StartQueCount++;
				while (ptrHookData->QueueBacon.size() > 0)
				{
					TRACE("Before Pop Que Size:%d  \n",ptrHookData->QueueBacon.size());	
					ptrHookData->QueueBacon.pop();		
					TRACE("After Pop Que Size:%d  \n",ptrHookData->QueueBacon.size());	
				}
			}
			else
			{
				ptrHookData->IoFunctionHooked = true;	
				MsysHookFunction(M_DEFAULT_HOST, M_IO_CHANGE, IoHookFunction, ptrHookData);
			}
		}

	}
	//---------------------------------------------------//

	// Hook info
	MdigGetHookInfo(EventId, M_MODIFIED_BUFFER+M_BUFFER_ID, &ModifiedBufferId);

	// Copy the binarize image bottom to top
	MbufCopy(ptrHookData->MilBinImageBot,ptrHookData->MilBinImageTop);

	// Binarize the image
	MimBinarize(ModifiedBufferId, ptrHookData->MilBinImageBot, M_FIXED+M_GREATER_OR_EQUAL,pSettings->Threshold, M_NULL);	

	// Remove small particles and then remove small holes.
	MimOpen(ptrHookData->MilBinImageBot, ptrHookData->MilBinImageBotSeperation, pSettings->MinBlobRadius, M_BINARY);
	MimClose(ptrHookData->MilBinImageBotSeperation, ptrHookData->MilBinImageBot,pSettings->MinBlobRadius, M_BINARY);

	// Lock the latch queue and get the reference value.
	//if (ptrHookData->SteerTriggerOn)
	if (pSettings->Trigger==1)
	{
		//TRACE("GrabHookHandlenCount  \n");
		//TRACE("Que Size:%d  \n",ptrHookData->QueueBacon.size());	

		// Get the reference value
		ReferenceStamp = 0;
		if (!ptrHookData->QueueBacon.empty())
		{
			ptrHookData->CritSect.Lock();
			ptrHookData->QueueSize = ptrHookData->QueueBacon.size();
			ReferenceStamp = ptrHookData->QueueBacon.front();
			ptrHookData->QueueBacon.pop();
			ptrHookData->CritSect.Unlock();
			MsysIoInquire(ptrHookData->CmdListId, M_REFERENCE_VALUE, &ReferenceStampInq);
			ReferenceStampDiff = ReferenceStampInq - ReferenceStamp;
			ptrHookData->LatchDiff = (long)ReferenceStampDiff;
			if (ptrHookData->QueueSize > 1)
			{
				TRACE("QueueSize: %ld ",ptrHookData->QueueSize);		
				TRACE("ReferenceStamp: %ld ",ReferenceStamp);		
				TRACE("ReferenceStampInq: %ld ",ReferenceStampInq);		
				TRACE("ReferenceStampDiff: %ld \n",ReferenceStampDiff);					
			}
		}

		// Find the Bacon 
		BlobCount = ptrHookData->pBlob->FindBlobsMerge(ptrHookData->MilBinImageBot,pSettings,pSettings2);
		if (BlobCount > 0)
		{
			//TRACE("BlobCount: %d\n",BlobCount);		
			ptrHookData->TotalBlobCount += BlobCount;
			ptrHookData->Position = ptrHookData->pBlob->GetBlobPosX(0);
		}
		if (ptrHookData->pBlob->GoodBlobData.TotalBlobs > 0)
		{
			ptrHookData->SuppressionCount = pSettings->RejectSuppressionCount;
			if (ptrHookData->EndDetectedLatch)
			{
				ptrHookData->EndDetected = false;
				ptrHookData->EndDetectedLatch = false;
			}
		}

		// Register all the reject pulses
		//----------------------------------------------------------------------//
		ptrHookData->TotalRejectCount += ptrHookData->pBlob->BadBlobData.TotalBlobs;		
		if (ptrHookData->pBlob->GoodBlobData.TotalBlobs==0 && pSettings->RejectDuration > 0)
		{
			for (int i=0; i<ptrHookData->pBlob->BadBlobData.TotalBlobs; i++)
			{
				Duration = pSettings->RejectDuration;
				BitPos = M_IO_COMMAND_BIT2;
				Delay = ptrHookData->pBlob->GetLaneDelay(i)+pSettings->RejectDelay;
				TRACE("Reject ReferenceStampDiff: %d \n",ReferenceStampDiff);
				if (ReferenceStampDiff > 117)  // If the differance is greater than 1/2 frame
				{                              // add a delay of one whole frame.
					Delay += 235;              // There are 235 Lines per frame.
				}
				if (ReferenceStamp > 0 && ptrHookData->SuppressionCount == 0 
					&& ptrHookData->EndDetected && pSettings->SystemEnable==1)
				{
					ptrHookData->EndDetectedLatch = true;
					MsysIoCommandRegister(ptrHookData->CmdListId, M_PULSE_HIGH, ReferenceStamp,Delay,Duration,BitPos, &Status);
					//AfxMessageBox(_T("Register"));
					////MsysIoCommandRegister(ptrHookData->CmdListId, M_PULSE_HIGH, ReferenceStamp,Delay+(Duration/2),Duration/3,BitPos, &Status);
					if (Status==M_INVALID)
					{
						TRACE("Reject ReferenceStamp: %d Not valid  \n",ReferenceStamp);
						//AfxMessageBox(_T(" Invalid Register"));
					}
					else
					{
						TRACE("Rject Registered: %d  ",ReferenceStamp);					
						TRACE("Delay:%f   Duration:%f \n",Delay,Duration);					
					}
				}
			}
		}
		//----------------------------------------------------------------------//

		// Find the average bacon position
		//-----------------------------------------------------------//
		double BacPosSum = 0;
		BlobCount = ptrHookData->pBlob->GoodBlobData.TotalBlobs;     // Get count
		for (int i=0; i<BlobCount; i++)                              //
		{                                                            //
			BacPosSum += ptrHookData->pBlob->GetAlignPosX(i,pSettings3,pMotion);
		}                                                            //
		//-----------------------------------------------------------//

		// Load the PMAC buffer with good bacon data for alignment
		//-----------------------------------------------------------//
		if (ptrHookData->PmacComComplete && ptrHookData->BaconBuff[0]==0)
		{
			AveBacPos = 0;
			if (BlobCount > 0)
			{
				AveBacPos = BacPosSum/BlobCount;
				//TRACE("AveBacPos: %f\n",AveBacPos);		
			}
			_int32 PosX = (_int32)AveBacPos;
			_int16* pPos = (_int16*)&PosX;
			unsigned _int16 PosY = (unsigned _int16) ptrHookData->pBlob->GoodBlobData.MinY[0];
			ptrHookData->BaconBuff[0]                = 0xFFFF;          // Data Ready
			ptrHookData->BaconBuff[1]                = 0;               // Always zero
			ptrHookData->BaconBuff[2]                = pPos[0];         // Position X Low byte
			ptrHookData->BaconBuff[3]                = pPos[1];         // Position X High byte
			ptrHookData->BaconBuff[4]                = PosY;            // Position Y
			ptrHookData->BaconBuff[5]                = BlobCount;       // Count
			ptrHookData->BaconBuff[6]                = 0;               // Always zero
			ptrHookData->BaconBuff[7]                = 0;               // Always zero
			ptrHookData->BaconBuff[8]                = 0;               // Always zero
			ptrHookData->BaconBuff[9]                = 0;               // Always zero
			ptrHookData->BaconBuff[10]               = 0;               // Always zero
			ptrHookData->BaconBuff[11]               = 0xFFFF;          // Data ready
			//TRACE("AveBacPos: %d\n",PosX);		
		}

		// Release the communications thread
		ptrHookData->GrabEvent.SetEvent();

		// Save Blob image data
		ptrHookData->pBlob->ShowGoodBlobs(ptrHookData->MilWorkImage);					
		ptrHookData->pBlob->ShowBadBlobs(ptrHookData->MilWorkImage);					
	}

	// Show the Image
	//-------------------------------------------------------------------------------------//
	switch (ptrHookData->DisplaySelect)
	{
		// Live image
		case 0:
		    //TRACE("Live image  \n");
			MbufCopy(ptrHookData->MilRawImageBot,ptrHookData->MilRawImageTop); 
			MbufCopy(ModifiedBufferId,ptrHookData->MilRawImageBot);
			if (ptrHookData->MainPage)
			{
				MimResize(ptrHookData->MilRawImage,ptrHookData->MilImage2,M_FILL_DESTINATION,M_FILL_DESTINATION,M_DEFAULT);
			}
			else
			{		
				MbufCopy(ptrHookData->MilRawImage,ptrHookData->MilImage);
			}
			break;
		// Biniarized image
		case 1:
			if (ptrHookData->MainPage)
			{
				MimResize(ptrHookData->MilBinImage,ptrHookData->MilImage2,M_FILL_DESTINATION,M_FILL_DESTINATION,M_DEFAULT);
			}
			else
			{
				MbufCopy(ptrHookData->MilBinImage,ptrHookData->MilImage);
			}
			break;
		// Result
		case 2:
			if (ptrHookData->MainPage)
			{
				//ptrHookData->pBlob->ShowBlobs2(ptrHookData->MilWorkImage,ptrHookData->MilWorkImage2,BaconCount,ptrHookData->BaconSpeed);
				//MimResize(pRunData->MilWorkImage2,pRunData->MilImage2,M_FILL_DESTINATION,M_FILL_DESTINATION,M_DEFAULT);
				MimResize(ptrHookData->MilWorkImage,ptrHookData->MilImage2,M_FILL_DESTINATION,M_FILL_DESTINATION,M_DEFAULT);
			}
			else
			{
				//ptrHookData->pBlob->ShowGoodBlobs(ptrHookData->MilWorkImage,BaconBuff,BaconBuffRaw,PMAC_FILL_SIZE);					
				//MbufCopy( ptrHookData->MilRejectBlobImage,ptrHookData->MilImage);
				MbufCopy(ptrHookData->MilWorkImage,ptrHookData->MilImage);
			}
			break;
		// Freeze
		case 3:
			break;
		default:
			break;	
	}
	//-------------------------------------------------------------------------------------//

	// Total processing time
	MappTimer(M_TIMER_READ, &dbTime);
	dbProcTime = (dbTime - ptrHookData->dbTimePrev)*1000;
	if (dbProcTime > ptrHookData->MaxProcTime)
		ptrHookData->MaxProcTime = dbProcTime;

//		TRACE("GrabHookHandlenCount  \n");
	if (ptrHookData->SuppressionCount > 0)
	{
		ptrHookData->SuppressionCount--;
	}

	return 0;

}

//----------------------------------------------------------------------
// CamPresentFunction - User's camera present function called every time a camera connection state
//
//-----------------------------------------------------------------------
MIL_INT MFTYPE CamPresentFunction(MIL_INT HookType, MIL_ID HookId, void* HookDataPtr)
{
   CameraPresentHookDataStruct *UserHookDataPtr = (CameraPresentHookDataStruct*)HookDataPtr;
   MIL_INT IsCamPresent, Number;

   /* Inquire the camera present state (present or not present). */
   MsysGetHookInfo(UserHookDataPtr->MilSystem, HookId, M_CAMERA_PRESENT, &IsCamPresent);

   /* Inquire the camera's digitizer device number . */
   MsysGetHookInfo(UserHookDataPtr->MilSystem, HookId, M_NUMBER, &Number);

   /* Update the number of camera present variable. */
   MsysInquire(UserHookDataPtr->MilSystem, M_NUM_CAMERA_PRESENT,
      &UserHookDataPtr->NbCameras);

   TRACE(".......................................................Cameras present %d \n",UserHookDataPtr->NbCameras);

   if (IsCamPresent && UserHookDataPtr->NbCameras==2)
   {
      MIL_TEXT_CHAR* UniqueId = NULL;
      MIL_INT Size = 0;
	  UserHookDataPtr->CameraPresentEvent.SetEvent();
	  TRACE(".......................................................All cameras are present! \n");

      ///* Inquire the camera's Unique Id. */
      //MsysGetHookInfo(UserHookDataPtr->MilSystem, HookId, M_GC_UNIQUE_ID_STRING_SIZE,
      //   &Size);
      //UniqueId = new MIL_TEXT_CHAR[Size];
      //MsysGetHookInfo(UserHookDataPtr->MilSystem, HookId, M_GC_UNIQUE_ID_STRING,
      //   UniqueId);

      ///* Camera is present. */
      //if (UserHookDataPtr->DigHookDataStrutPtr[Number].MilDigitizer == 0)
      //   {
      //   /* Newly attached camera; allocate it. */
      //   DigAllocResources(UserHookDataPtr->MilSystem, Number,
      //      &UserHookDataPtr->DigHookDataStrutPtr[Number]);
      //   }
      //else if (MosStrcmp(UserHookDataPtr->DigHookDataStrutPtr[Number].CamUniqueId,
      //   UniqueId) != 0)
      //   {
      //   /* New camera added in place of another one, free old dig */
      //   DigFreeResources(&UserHookDataPtr->DigHookDataStrutPtr[Number]);

      //   /* Find out if camera was previously allocated on a different device number. */
      //   for (MIL_INT i = 0; i < MAX_CAM; i++)
      //   if ((i != Number) &&
      //      (MosStrcmp(UserHookDataPtr->DigHookDataStrutPtr[Number].CamUniqueId,
      //      UniqueId) == 0))
      //      DigFreeResources(&UserHookDataPtr->DigHookDataStrutPtr[i]);

      //   /* Allocate resources. */
      //   DigAllocResources(UserHookDataPtr->MilSystem, Number,
      //      &UserHookDataPtr->DigHookDataStrutPtr[Number]);
      //   }

      //if (UserHookDataPtr->DigHookDataStrutPtr[Number].MilDigitizer)
      //   {
      //   if ((UserHookDataPtr->BoardType & M_BOARD_TYPE_MASK) == M_GIGE_VISION)
      //      AddAdapterToList(UserHookDataPtr,
      //      UserHookDataPtr->DigHookDataStrutPtr[Number].pAdapterName);
      //   }
      //UserHookDataPtr->DigHookDataStrutPtr[Number].IsConnected = true;
      ///* Start acquisition. */
      //DigStartAcquisition(&UserHookDataPtr->DigHookDataStrutPtr[Number]);

      //delete[] UniqueId;
   }
   //else
   //{
//	   	  TRACE("................................................Camera is NOT present... \n");

      ///* Camera is not present. */
      //if (UserHookDataPtr->DigHookDataStrutPtr[Number].MilDigitizer)
      //   {
      //   /* Stop acquisition. */
      //   DigStopAcquisition(&UserHookDataPtr->DigHookDataStrutPtr[Number]);
      //   }

      //UserHookDataPtr->DigHookDataStrutPtr[Number].IsConnected = false;
   //}

   return 0;
}

//----------------------------------------------------------------------//
// MIL: Hook-handler function: DisplayError()
//----------------------------------------------------------------------//
MIL_INT MFTYPE DisplayErrorExt(MIL_INT HookType, MIL_ID EventId, void* UserDataPtr)
{
	CMil* pMil = (CMil*)UserDataPtr;
	return pMil->DisplayError(HookType, EventId, M_NULL);
}
//----------------------------------------------------------------------//

//----------------------------------------------------------------------
// GrabHookHandlerEnd - Process grabed image.
//
//-----------------------------------------------------------------------
MIL_INT MFTYPE GrabHookHandlerEndDetect(MIL_INT HookType, MIL_ID EventId, void* UserDataPtr) 
{
	COUNTHOOKDATASTRUCT2* ptrHookData = (COUNTHOOKDATASTRUCT2*)UserDataPtr;
	CBlob* pBlob = ptrHookData->pBlob;
	MIL_ID ModifiedBufferId;
	long BaconBlobSize;
	double dbTime;
	double dbProcTime;
	bool BaconIsDetected;
	MIL_DOUBLE TextColor;
	int *pShearBarData = ptrHookData->pShearBarData;
	MIL_INT PeakBuff[MAX_PEAKS+1];
	MIL_INT LaserPointsSrc[TOTAL_SBAR_POINTS+1];

	// Measure time
	MappTimer(M_TIMER_READ, &dbTime);
	if (ptrHookData->dbTimePrev)
	{
		ptrHookData->Period = (dbTime - ptrHookData->dbTimePrev)*1000;
		if (ptrHookData->PeriodMax == 0) ptrHookData->PeriodMax = ptrHookData->Period;
		if (ptrHookData->PeriodMin == 0) ptrHookData->PeriodMin = ptrHookData->Period;
		if (ptrHookData->Period > ptrHookData->PeriodMax) ptrHookData->PeriodMax = ptrHookData->Period;
		if (ptrHookData->Period < ptrHookData->PeriodMin) ptrHookData->PeriodMin = ptrHookData->Period;
	}
	ptrHookData->dbTimePrev = dbTime;

	// Hook info
	MdigGetHookInfo(EventId, M_MODIFIED_BUFFER+M_BUFFER_ID, &ModifiedBufferId);

	// Find the LASER line
	MimLocatePeak1d(ptrHookData->Context,ModifiedBufferId,ptrHookData->LocatePeak,
		ptrHookData->pSettings->VisSettings2.NominalLaserWidth,
		ptrHookData->pSettings->VisSettings2.LaserWidthDelta,
		ptrHookData->pSettings->VisSettings2.MinLaserIntensity,
		M_DEFAULT, M_DEFAULT);

	// Get the LASER positions	
	for (int i=ptrHookData->pSettings->VisSettings2.x[0];i<ptrHookData->pSettings->VisSettings2.x[4];i++)
	{
		MimGetResultSingle(ptrHookData->LocatePeak,M_ALL,i,M_PEAK_POSITION+M_INCLUDE_MISSING_DATA+M_TYPE_MIL_INT ,PeakBuff);
		if (PeakBuff[0] < ptrHookData->pSettings->VisSettings2.MinPosY)
		{
			LaserPointsSrc[i] = -1;
		}
		else
		{
			LaserPointsSrc[i] = PeakBuff[0];
		}
	}

	// Fill in the gaps
	FillMissingData(ptrHookData->pSettings->VisSettings2.MaxGapFillX,ptrHookData->pSettings->VisSettings2.MaxGapFillY,
		LaserPointsSrc,ptrHookData->pSettings->VisSettings2.x[0],ptrHookData->pSettings->VisSettings2.x[4]);

	// Create the bacon blob
	BaconBlobSize = CreateBaconBlob(ptrHookData->pSettings->VisSettings2.x[0],
		LaserPointsSrc,
		pShearBarData,
		ptrHookData->MilBaconBlobImage);

	// Inspect Bacon
	BaconIsDetected = pBlob->InspectEndDetectBlobs(ptrHookData->MilBaconBlobImage,ptrHookData->pSettings);

	// Apply an erosion operation for display effects.
	MimErode(ptrHookData->MilBaconBlobImage,ptrHookData->MilBaconBlobImage,1, M_BINARY);

	// Copy the raw image to all three bands
	MbufCopy(ModifiedBufferId,ptrHookData->MilImageRejectWork);

	// Bacon good
	//------------------------------------------------------------------------------------------//
	if (BaconIsDetected)
	{
		// Bacon is detected so set the lock
		if (ptrHookData->EndDetectLockCountReset == true)
		{
			ptrHookData->EndDetectLockCount = ptrHookData->pSettings->VisSettings2.EndDetectLockCount;
			ptrHookData->EndDetectLockCountReset = false;
		}

		// Set the bacon status output
		if (ptrHookData->GapDetectLatchCount <= 0)
		{
			// Bacon good Output ON
			MsysControl(M_DEFAULT_HOST,END_BACON_GOOD, M_ON);
			MsysControl(M_DEFAULT_HOST,END_BACON_BAD, M_OFF);

			// Show the laser position
			MgraColor(M_DEFAULT, M_COLOR_RED);
			MimDraw(M_DEFAULT, ptrHookData->LocatePeak,M_NULL, ptrHookData->MilImageRejectWork, M_DRAW_PEAKS+M_1D_COLUMNS+M_LINES, (MIL_DOUBLE)0,1, M_FIXED_POINT+NB_FIXED_POINT);

			// Show blob in green
			MimArith(ptrHookData->MilBaconBlobImage,ptrHookData->MilImageRejectWorkGreenBand,ptrHookData->MilImageRejectWorkGreenBand, M_OR);			
			TextColor = M_RGB888(0,255,0);
		}
		else
		{
			// Bacon good Output OFF
			MsysControl(M_DEFAULT_HOST,END_BACON_GOOD, M_OFF);
			MsysControl(M_DEFAULT_HOST,END_BACON_BAD, M_ON);

			// Show the laser position in green
			MgraColor(M_DEFAULT, M_COLOR_GREEN);
			MimDraw(M_DEFAULT, ptrHookData->LocatePeak,M_NULL, ptrHookData->MilImageRejectWork, M_DRAW_PEAKS+M_1D_COLUMNS+M_LINES, (MIL_DOUBLE)0,1, M_FIXED_POINT+NB_FIXED_POINT);

			// Show blob in Yellow
			MimArith(ptrHookData->MilBaconBlobImage,ptrHookData->MilImageRejectWorkGreenBand,ptrHookData->MilImageRejectWorkGreenBand, M_OR);			
			MimArith(ptrHookData->MilBaconBlobImage,ptrHookData->MilImageRejectWorkRedBand,ptrHookData->MilImageRejectWorkRedBand, M_OR);			
			//TextColor = M_RGB888(0,0,255);
			TextColor = M_RGB888(255,255,0);

		
		}
		ptrHookData->GapDetectLatchCount--;

		//// Show the laser position
		//MgraColor(M_DEFAULT, M_COLOR_RED);
		//MimDraw(M_DEFAULT, ptrHookData->LocatePeak,M_NULL, ptrHookData->MilImageRejectWork, M_DRAW_PEAKS+M_1D_COLUMNS+M_LINES, (MIL_DOUBLE)0,1, M_FIXED_POINT+NB_FIXED_POINT);

		//// Show blob in green
		//MimArith(ptrHookData->MilBaconBlobImage,ptrHookData->MilImageRejectWorkGreenBand,ptrHookData->MilImageRejectWorkGreenBand, M_OR);			
		//TextColor = M_RGB888(0,255,0);

	}
	// Bacon is bad, No blobs or to many to be good bacon.
	//------------------------------------------------------------------------------------------//
	else
	{
		// Check the lock
		if (ptrHookData->EndDetectLockCount == 0)
		{
			// Output OFF
			MsysControl(M_DEFAULT_HOST,END_BACON_GOOD, M_OFF);
			MsysControl(M_DEFAULT_HOST,END_BACON_BAD, M_ON);

			// Show blob in red
			MimArith(ptrHookData->MilBaconBlobImage,ptrHookData->MilImageRejectWorkRedBand,ptrHookData->MilImageRejectWorkRedBand, M_OR);			
			TextColor = M_RGB888(255,0,0);
			ptrHookData->EndDetectLockCountReset = true;               // Reset the lock counter.

			// Latch the bad bacon event
			ptrHookData->GapDetectLatchCount  = ptrHookData->pSettings->VisSettings2.GapDetectLatchCount;
			ptrHookData->pHook1->EndDetected = true;

		}
		else
		{
			// Keep output ON
			MsysControl(M_DEFAULT_HOST,END_BACON_GOOD, M_ON);               // ON !
			MsysControl(M_DEFAULT_HOST,END_BACON_BAD, M_OFF);

			// Show blob in blue
			MimArith(ptrHookData->MilBaconBlobImage,ptrHookData->MilImageRejectWorkBlueBand,ptrHookData->MilImageRejectWorkBlueBand, M_OR);					
			TextColor = M_RGB888(0,0,255);
		}

		// Show the laser position in green
		MgraColor(M_DEFAULT, M_COLOR_GREEN);
		MimDraw(M_DEFAULT, ptrHookData->LocatePeak,M_NULL, ptrHookData->MilImageRejectWork, M_DRAW_PEAKS+M_1D_COLUMNS+M_LINES, (MIL_DOUBLE)0,1, M_FIXED_POINT+NB_FIXED_POINT);

	}
	//TRACE("BaconBlobSize %ld \n",BaconBlobSize);
	// Decrement the lock
	if (ptrHookData->EndDetectLockCount > 0)
	{
		ptrHookData->EndDetectLockCount--;
	}

	// Record images
	if (ptrHookData->RecordIndex < MAX_RECORD)
	{
		TRACE("RecordIndex \n");
		if (pBlob->GetEndDetectBlobCount() > 0 )
		//if (BaconIsDetected)
		{
			// Copy the image
			MbufCopy(ptrHookData->MilImageRejectWork,ptrHookData->MilRecordImages[ptrHookData->ImagesRecorded]);
			ptrHookData->RecordIndex++;
			ptrHookData->ImagesRecorded++;
			//TRACE("Recording Images recorded %d \n",ptrHookData->ImagesRecorded);
		}
		else
		{
			// Keep recording
			if (ptrHookData->RecordEndCount < END_RECORD && ptrHookData->ImagesRecorded > 0)
			{
				MbufCopy(ptrHookData->MilImageRejectWork,ptrHookData->MilRecordImages[ptrHookData->ImagesRecorded]);
				ptrHookData->RecordEndCount++;
				ptrHookData->RecordIndex++;
				ptrHookData->ImagesRecorded++;
			}
			// Done recording
			else
			{
				if (ptrHookData->ImagesRecorded > 0)
				{
					ptrHookData->RecordIndex = MAX_RECORD;
					//TRACE("Images recorded %d \n",ptrHookData->ImagesRecorded);
				}
			}		
		}
	}

	// Main page
	if (ptrHookData->MainPage)
	{
		MimResize(ptrHookData->MilImageRejectWork,ptrHookData->MilImageRejectWork2,M_FILL_DESTINATION,M_FILL_DESTINATION,M_DEFAULT);
		pBlob->ShowEndDetectBlobData(ptrHookData->MilImageRejectWork2,M_RGB888(0,0,0),TextColor);
		//MimResize(ptrHookData->MilImageRejectWork,ptrHookData->MilImage2,M_FILL_DESTINATION,M_FILL_DESTINATION,M_DEFAULT);
		MbufCopy(ptrHookData->MilImageRejectWork2,ptrHookData->MilImage2);
	}
	// Vision page
	else
	{
		if (ptrHookData->PlayImages)
		{
			//pBlob->ShowEndDetectBlobData(ptrHookData->MilImageRejectWork,M_RGB888(0,0,0),TextColor);
			MbufCopy(ptrHookData->MilRecordImages[ptrHookData->PlayIndex++],ptrHookData->MilImage);
			TRACE("pLAY \n");
			if (ptrHookData->PlayIndex >= ptrHookData->ImagesRecorded) ptrHookData->PlayIndex = 0;
			//if (ptrHookData->PlayIndex >= MAX_RECORD) ptrHookData->PlayIndex = 0;

		}
		else
		{
			pBlob->ShowEndDetectBlobData(ptrHookData->MilImageRejectWork,M_RGB888(0,0,0),TextColor);
			MbufCopy(ptrHookData->MilImageRejectWork,ptrHookData->MilImage);
		}
	}

	// Total processing time
	MappTimer(M_TIMER_READ, &dbTime);
	dbProcTime = (dbTime - ptrHookData->dbTimePrev)*1000;
	if (dbProcTime > ptrHookData->MaxProcTime) ptrHookData->MaxProcTime = dbProcTime;
	//TRACE("Total processing time: %4.2f     Period: %4.2f      Period Min: %4.2f   Perion Max: %4.2f\n",dbProcTime,
	//	ptrHookData->Period,ptrHookData->PeriodMin,ptrHookData->PeriodMax);

	return 0;

}