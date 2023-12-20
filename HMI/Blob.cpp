//======================================================================
// CPP file
//
// Written for the BTC Merge conveyor
// Copyright (C) 2013 Bill Young
//================================================================
#include "StdAfx.h"
#include "Blob.h"
#include <math.h>

CBlob::CBlob(void)
{
	MilSystem = NULL;
    BlobResult[0] = NULL;
    BlobResult[1] = NULL;
    BlobResult[2] = NULL;
    BlobResult[3] = NULL;
    BlobResult[4] = NULL;
    MilBlobFeatureList = NULL;
	//BlobsCount = 0;
	m_LockSize = 0;
	m_ImageSizeY = 0;
	BadBlobData.TotalBlobs = 0;
	GoodBlobData.TotalBlobs = 0;
	bClearImage = true;
	::ZeroMemory (m_SizeFIFO, sizeof (long)*FIFO_SIZE);
}

CBlob::~CBlob(void)
{
	Free();
}

void CBlob::Alloc(MIL_ID SysId,MIL_ID ImageId)
{
	MilSystem = SysId;

	// Allocate a feature list. 
	MblobAllocFeatureList(MilSystem, &MilBlobFeatureList); 
  
	// Enable the Area and Center Of Gravity feature calculation. 
	MblobSelectFeature(MilBlobFeatureList, M_BOX_Y_MIN+M_SORT1_UP); 
	MblobSelectFeature(MilBlobFeatureList, M_BOX_Y_MAX); 
	MblobSelectFeature(MilBlobFeatureList, M_BOX_X_MIN); 
	MblobSelectFeature(MilBlobFeatureList, M_BOX_X_MAX); 
	MblobSelectFeature(MilBlobFeatureList, M_BOX);
	MblobSelectFeature(MilBlobFeatureList, M_FERET_X); 
	MblobSelectFeature(MilBlobFeatureList, M_FERET_Y); 
	MblobSelectFeature(MilBlobFeatureList, M_AREA); 
	MblobSelectFeature(MilBlobFeatureList, M_CENTER_OF_GRAVITY); 
	//MblobSelectFeature(pMIL->FeatureList, M_FERET_Y); 
 
    // Allocate a blob result buffer.
	MblobAllocResult(MilSystem, &BlobResult[0]); 
	MblobAllocResult(MilSystem, &BlobResult[1]); 
	MblobAllocResult(MilSystem, &BlobResult[2]); 
	MblobAllocResult(MilSystem, &BlobResult[3]); 
	MblobAllocResult(MilSystem, &BlobResult[4]); 

	// Blob control settings
	MblobControl(BlobResult[0], M_FOREGROUND_VALUE, M_NONZERO);
	MblobControl(BlobResult[1], M_FOREGROUND_VALUE, M_NONZERO);
	MblobControl(BlobResult[2], M_FOREGROUND_VALUE, M_NONZERO);
	MblobControl(BlobResult[3], M_FOREGROUND_VALUE, M_NONZERO);
	MblobControl(BlobResult[4], M_FOREGROUND_VALUE, M_NONZERO);

	MblobControl(BlobResult[0], M_RESULT_OUTPUT_UNITS , M_PIXEL );
	MblobControl(BlobResult[1], M_RESULT_OUTPUT_UNITS , M_PIXEL );
	MblobControl(BlobResult[2], M_RESULT_OUTPUT_UNITS , M_PIXEL );
	MblobControl(BlobResult[3], M_RESULT_OUTPUT_UNITS , M_PIXEL );
	MblobControl(BlobResult[4], M_RESULT_OUTPUT_UNITS , M_PIXEL );
	
	MblobControl(BlobResult[0], M_BLOB_IDENTIFICATION , M_INDIVIDUAL );
	MblobControl(BlobResult[1], M_BLOB_IDENTIFICATION , M_INDIVIDUAL );
	MblobControl(BlobResult[2], M_BLOB_IDENTIFICATION , M_INDIVIDUAL );
	MblobControl(BlobResult[3], M_BLOB_IDENTIFICATION , M_INDIVIDUAL );
	MblobControl(BlobResult[4], M_BLOB_IDENTIFICATION , M_INDIVIDUAL );

	MblobControl(BlobResult[0], M_SAVE_RUNS, M_ENABLE);
	MblobControl(BlobResult[1], M_SAVE_RUNS, M_ENABLE);
	MblobControl(BlobResult[2], M_SAVE_RUNS, M_ENABLE);
	MblobControl(BlobResult[3], M_SAVE_RUNS, M_ENABLE);
	MblobControl(BlobResult[4], M_SAVE_RUNS, M_ENABLE);

	// Do first BlobCalculate to prime merge function.
	MbufClear(ImageId, 0x00);
	MblobCalculate(ImageId, M_NULL, MilBlobFeatureList, BlobResult[1]);

}
void CBlob::Free()
{
	if (BlobResult[0]) MblobFree(BlobResult[0]);
	if (BlobResult[1]) MblobFree(BlobResult[1]);
	if (BlobResult[2]) MblobFree(BlobResult[2]);
	if (BlobResult[3]) MblobFree(BlobResult[3]);
	if (BlobResult[4]) MblobFree(BlobResult[4]);
	if (MilBlobFeatureList) MblobFree(MilBlobFeatureList); 
	//MilApplication = NULL;
	MilSystem = NULL;
    BlobResult[0] = NULL;
    BlobResult[1] = NULL;
    BlobResult[2] = NULL;
    BlobResult[3] = NULL;
    BlobResult[4] = NULL;
    MilBlobFeatureList = NULL;

}

int CBlob::GetBlobCount()
{
	return 	GoodBlobData.TotalBlobs;
}
int CBlob::GetEndDetectBlobCount()
{
	return 	BlobData.TotalBlobs;
}
bool CBlob::AnyBlobs()
{
	if (GoodBlobData.TotalBlobs > 0 || BadBlobData.TotalBlobs > 0)
		return 	true;
	else
		return false;
}

bool CBlob::InspectEndDetectBlobs(MIL_ID ImageId,ALLSETTINGS* pSettings)
{
	MIL_INT TotalBlobs = 0;
	MIL_DOUBLE TotalBlobArea = 0;

	// Calculate selected features for each blob.
	MblobCalculate(ImageId, M_NULL, MilBlobFeatureList, BlobResult[0]);

	// Remove small blobs
	MblobSelect(BlobResult[0], M_EXCLUDE, M_AREA, M_LESS_OR_EQUAL, 10, M_NULL); 

	// Get number of blobs found
	BlobData.TotalBlobs = 0;
	MblobGetNumber(BlobResult[0], &TotalBlobs);
	//TRACE("Remaining after merge blobs :%d \n",TotalBlobs);

	// Any blobs or to many blobs?
	if ((TotalBlobs == 0) || (TotalBlobs >= MAX_BLOBS))
	{
		return false;
	}

	// Blob Area
	MblobGetResult(BlobResult[0], M_AREA+M_TYPE_DOUBLE,BlobData.Area);
	BlobData.TotalBlobs =  (long)TotalBlobs;

	// Total Area
	for (int i=0; i< BlobData.TotalBlobs; i++)
	{
		TotalBlobArea += BlobData.Area[i];
	}

	// Inspect
	if (TotalBlobs >= pSettings->VisSettings2.MaxBaconBlobs || TotalBlobArea < pSettings->VisSettings2.MinBaconSize)
	{
		return false;
	}

	// Pass
	return true;

	//MIL_INT TotalBlobs = 0;
	//MIL_DOUBLE TotalBlobArea = 0;

	//// Calculate selected features for each blob.
	//MblobCalculate(ImageId, M_NULL, MilBlobFeatureList, BlobResult[0]);

	//// Remove small blobs
	//MblobSelect(BlobResult[0], M_EXCLUDE, M_AREA, M_LESS_OR_EQUAL, 10, M_NULL); 

	//// Get number of blobs found
	//BlobData.TotalBlobs = 0;
	//MblobGetNumber(BlobResult[0], &TotalBlobs);
	////TRACE("Remaining after merge blobs :%d \n",TotalBlobs);

	//// Any blobs or to many blobs?
	//if ((TotalBlobs == 0) || (TotalBlobs >= MAX_BLOBS))
	//{
	//	return false;
	//}

	//// Blob Area
	//MblobGetResult(BlobResult[0], M_AREA+M_TYPE_DOUBLE,BlobData.Area);
	//BlobData.TotalBlobs =  (long)TotalBlobs;

	//// Total Area
	//for (int i=0; i< BlobData.TotalBlobs; i++)
	//{
	//	TotalBlobArea += BlobData.Area[i];
	//}

	//// Inspect
	//if (TotalBlobs >= pSettings->VisSettings2.MaxBaconBlobs || TotalBlobArea < pSettings->VisSettings2.MinBaconSize)
	//{
	//	return false;
	//}

	// Pass
	return true;

}
//---------------------------------------------------------------------//
// FindBlobsMerge()
//---------------------------------------------------------------------//
int CBlob::FindBlobsMerge(MIL_ID ImageId,VISIONSETTINGS1* pSettings,VISIONSETTINGS2* pSettings2)
{
	MIL_INT SizeX,SizeY;
	MIL_INT TotalBlobs = 0;
	MIL_INT TotalBlobsExcluded = 0;
	MIL_INT TotalRejectBlobs = 0;
	double PosX = 0;
	BadBlobData.TotalBlobs =  0;
	GoodBlobData.TotalBlobs =  0;

	// Get buffer Y size
	MbufInquire(ImageId, M_SIZE_X,&SizeX);
	MbufInquire(ImageId, M_SIZE_Y,&SizeY);
	//TRACE("Blob Image Size X:%d  Blob Image Size Y:%d \n",SizeX,SizeY);
	m_ImageSizeY = SizeY*2;

	// Calculate selected features for each blob.
	MblobCalculate(ImageId, M_NULL, MilBlobFeatureList, BlobResult[0]);

	// Remove and save blobs touching bottom of image from result buffer.
	MblobGetNumber(BlobResult[0], &TotalBlobs);
	//TRACE("Blobs Found: %d \n",TotalBlobs);
	//TRACE("Before Blob Image Size X:%d  Blob Image Size Y:%d  Total%d\n",SizeX,SizeY,TotalBlobs);
	//MblobSelect(BlobResult[0], M_EXCLUDE, M_AREA, M_LESS_OR_EQUAL, 10, M_NULL); 
	MblobSelect(BlobResult[0], M_EXCLUDE, M_BOX_Y_MAX, M_GREATER_OR_EQUAL,(MIL_DOUBLE)(SizeY-1),M_NULL);
	
	// Merge the previous blobs and create two result buffers
	MblobMerge(BlobResult[1],BlobResult[0],BlobResult[2],M_DEFAULT); // Good Bacon
	MblobMerge(BlobResult[1],BlobResult[0],BlobResult[3],M_DEFAULT); // Bad Bacon
	MblobGetNumber(BlobResult[2], &TotalBlobsExcluded);

	// Remove the reject blobs from good bacon result buffer
	MblobSelect(BlobResult[2], M_EXCLUDE, M_AREA, M_LESS_OR_EQUAL, pSettings->MinBaconSize, M_NULL); 
	MblobSelect(BlobResult[2], M_EXCLUDE, M_FERET_X, M_LESS_OR_EQUAL,pSettings->MinBaconWidth,M_NULL);
	MblobSelect(BlobResult[2], M_EXCLUDE, M_FERET_Y, M_LESS_OR_EQUAL,pSettings->MinBaconHeight,M_NULL);
	
	// Remove the reject blobs from bad bacon result buffer
	MblobSelect(BlobResult[3], M_EXCLUDE, M_AREA, M_LESS_OR_EQUAL, pSettings->MinBaconSize, M_NULL); 
	MblobSelect(BlobResult[3], M_EXCLUDE, M_FERET_X, M_LESS_OR_EQUAL,pSettings->MinBaconWidth,M_NULL);
	MblobSelect(BlobResult[3], M_EXCLUDE, M_FERET_Y, M_LESS_OR_EQUAL,pSettings->MinBaconHeight,M_NULL);

	// Bring back only the reject blobs
	MblobGetNumber(BlobResult[2], &TotalBlobs);
	TotalRejectBlobs = TotalBlobsExcluded - TotalBlobs;
	if (TotalRejectBlobs > 0)
	{
		MblobSelect(BlobResult[3], M_INCLUDE_ONLY, M_EXCLUDED_BLOBS, M_NULL,M_NULL,M_NULL);

		// Remove blobs touching bottom of image
		MblobSelect(BlobResult[3], M_EXCLUDE, M_BOX_Y_MAX, M_GREATER_OR_EQUAL,(MIL_DOUBLE)(SizeY*2-1),M_NULL);

		// Remove ghost blobs
		MblobSelect(BlobResult[3], M_EXCLUDE, M_BOX_Y_MAX, M_LESS_OR_EQUAL,(MIL_DOUBLE)(SizeY-1),M_NULL);
		MblobGetNumber(BlobResult[3], &TotalRejectBlobs);
		//TRACE("Remaining Reject Blobs after M_EXCLUDE touching bottom of image operation: %d \n",TotalRejectBlobs);		

		// Remove the really small blobs from bad bacon result buffer
		MblobSelect(BlobResult[3], M_EXCLUDE, M_AREA, M_LESS_OR_EQUAL, pSettings->MinBaconRejectSize, M_NULL); 
		MblobSelect(BlobResult[3], M_EXCLUDE, M_FERET_X, M_LESS_OR_EQUAL,pSettings->MinBaconRejectWidth,M_NULL);
		MblobSelect(BlobResult[3], M_EXCLUDE, M_FERET_Y, M_LESS_OR_EQUAL,pSettings->MinBaconRejectHeight,M_NULL);
		MblobGetNumber(BlobResult[3], &TotalRejectBlobs);
		//TRACE("Remaining Reject Blobs after final M_EXCLUDE: %d \n\n",TotalRejectBlobs);		
	}

	// Remove blobs touching bottom of image
	MblobSelect(BlobResult[2], M_EXCLUDE, M_BOX_Y_MAX, M_GREATER_OR_EQUAL,(MIL_DOUBLE)(SizeY*2-1),M_NULL);
	MblobSelect(BlobResult[3], M_EXCLUDE, M_BOX_Y_MAX, M_GREATER_OR_EQUAL,(MIL_DOUBLE)(SizeY*2-1),M_NULL);

	// Process the good bacon blobs
	//------------------------------------------------------------------------------------//
	MblobGetNumber(BlobResult[2], &TotalBlobs);
	if (TotalBlobs > 0 && TotalBlobs < MAX_BLOBS)
	{
		bClearImage = true;
		GoodBlobData.TotalBlobs =  (long)TotalBlobs;
		//TRACE("Process good blob data GoodBlobData.TotalBlobs %d \n",GoodBlobData.TotalBlobs);
		// Blob Area
		MblobGetResult(BlobResult[2], M_AREA+M_TYPE_DOUBLE,GoodBlobData.Area);
		// Blob Box Min Y
		MblobGetResult(BlobResult[2], M_BOX_Y_MIN+M_TYPE_DOUBLE,GoodBlobData.MinY);
		// Blob Box Max Y
		MblobGetResult(BlobResult[2], M_BOX_Y_MAX+M_TYPE_DOUBLE,GoodBlobData.MaxY);
		// Blob COG X
		MblobGetResult(BlobResult[2], M_CENTER_OF_GRAVITY_X+M_TYPE_DOUBLE,GoodBlobData.CogX); 
		// Blob COG Y
		MblobGetResult(BlobResult[2], M_CENTER_OF_GRAVITY_Y+M_TYPE_DOUBLE,GoodBlobData.CogY); 
		// Blob Box Min X
		MblobGetResult(BlobResult[2], M_BOX_X_MIN+M_TYPE_DOUBLE,GoodBlobData.MinX);
		// Blob Box Max X
		MblobGetResult(BlobResult[2], M_BOX_X_MAX+M_TYPE_DOUBLE,GoodBlobData.MaxX);
		// Blob Box FeretX
		MblobGetResult(BlobResult[2], M_FERET_X+M_TYPE_DOUBLE,GoodBlobData.FeretX);
	
		// Get the total in reject buffer
		//MblobGetNumber(BlobResult[3], &TotalRejectBlobs);	
		TRACE("!!!!! Good blobs :%d    TotalRejectBlobs:%d  \n",TotalBlobs,TotalRejectBlobs);
		for (int i=0;i<TotalBlobs;i++){
			TRACE("Total Blobs:%d Area: %4.2f \n",i,GoodBlobData.Area[i]);
		}

		// Delete the remaining blobs
		//MblobSelect(BlobResult[3], M_DELETE, M_INCLUDED_BLOBS, M_NULL, M_NULL, M_NULL); 
		//MblobGetNumber(BlobResult[3], &TotalRejectBlobs);
		//TRACE("Remaining Reject Blobs after M_DELETE operation: %d \n",TotalRejectBlobs);		

		// Bring back the only the reject blobs
		//MblobSelect(BlobResult[3], M_INCLUDE, M_EXCLUDED_BLOBS, M_NULL, M_NULL, M_NULL); 
		//MblobGetNumber(BlobResult[3], &TotalRejectBlobs);
		//TRACE("Remaining Reject Blobs after M_INCLUDE operation: %d \n",TotalRejectBlobs);		

	}
	//------------------------------------------------------------------------------------//

	
	// Remove blobs touching top of image
	//MblobSelect(BlobResult[3], M_EXCLUDE, M_BOX_Y_MIN, M_LESS_OR_EQUAL,(MIL_DOUBLE)(1.0),M_NULL);

	// Remove blobs touching bottom of image
	//MblobSelect(BlobResult[3], M_EXCLUDE, M_BOX_Y_MAX, M_GREATER_OR_EQUAL,(MIL_DOUBLE)(SizeY*2-1),M_NULL);

	// Process the reject bacon blobs
	//------------------------------------------------------------------------------------//
	if (TotalRejectBlobs > 0 && TotalRejectBlobs < MAX_BLOBS)
	{
	    // Blob Area
		MblobGetResult(BlobResult[3], M_AREA+M_TYPE_DOUBLE,BadBlobData.Area);
		// Blob Box FeretX
		MblobGetResult(BlobResult[3], M_FERET_X+M_TYPE_DOUBLE,BadBlobData.FeretX);
		// Blob Box FeretY
		MblobGetResult(BlobResult[3], M_FERET_Y+M_TYPE_DOUBLE,BadBlobData.FeretY);

		//TRACE("Total Bad blobs: %d \n",TotalRejectBlobs);
		for (int i=0;i<TotalRejectBlobs;i++){
			//TRACE("Blob :%d Area: %4.2f \n",i,BadBlobData.Area[i]);
		}

		bClearImage = true;
		//TRACE("Bad blobs :%d \n",TotalBlobs);
		// Draw the reject blobs and seperate into 8 lanes.
		MbufClear(MilRejectBlobImage,0);
		MgraColor(M_DEFAULT,255);
		MblobDraw(M_DEFAULT, BlobResult[3], MilRejectBlobImage, M_DRAW_BLOBS,M_INCLUDED_BLOBS, M_DEFAULT);
		MgraColor(M_DEFAULT,0);
		MbufInquire(MilRejectBlobImage, M_SIZE_Y,&SizeY);
		MgraLine(M_DEFAULT, MilRejectBlobImage, pSettings2->PosLane1, 0,pSettings2->PosLane1,SizeY);
		MgraLine(M_DEFAULT, MilRejectBlobImage, pSettings2->PosLane2, 0,pSettings2->PosLane2,SizeY);
		MgraLine(M_DEFAULT, MilRejectBlobImage, pSettings2->PosLane3, 0,pSettings2->PosLane3,SizeY);
		MgraLine(M_DEFAULT, MilRejectBlobImage, pSettings2->PosLane4, 0,pSettings2->PosLane4,SizeY);
		MgraLine(M_DEFAULT, MilRejectBlobImage, pSettings2->PosLane5, 0,pSettings2->PosLane5,SizeY);
		MgraLine(M_DEFAULT, MilRejectBlobImage, pSettings2->PosLane6, 0,pSettings2->PosLane6,SizeY);
		MgraLine(M_DEFAULT, MilRejectBlobImage, pSettings2->PosLane7, 0,pSettings2->PosLane7,SizeY);

		// Calculate selected features for each reject blob.
		MblobCalculate(MilRejectBlobImage, M_NULL, MilBlobFeatureList, BlobResult[4]);
		MblobGetNumber(BlobResult[4], &TotalBlobs);
		//TRACE("Bad blobs seperated into lanes:%d \n",TotalBlobs);
		if (TotalBlobs > 0 && TotalBlobs < MAX_BLOBS)
		{
			// Save the count
			BadBlobData.TotalBlobs =  (long)TotalBlobs;
			// Blob Area
			MblobGetResult(BlobResult[4], M_AREA+M_TYPE_DOUBLE,BadBlobData.Area);
			// Blob Box Min Y
			MblobGetResult(BlobResult[4], M_BOX_Y_MIN+M_TYPE_DOUBLE,BadBlobData.MinY);
			// Blob Box Max Y
			MblobGetResult(BlobResult[4], M_BOX_Y_MAX+M_TYPE_DOUBLE,BadBlobData.MaxY);
			// Blob COG X
			MblobGetResult(BlobResult[4], M_CENTER_OF_GRAVITY_X+M_TYPE_DOUBLE,BadBlobData.CogX); 
			// Blob COG Y
			MblobGetResult(BlobResult[4], M_CENTER_OF_GRAVITY_Y+M_TYPE_DOUBLE,BadBlobData.CogY); 
			// Blob Box Min X
			MblobGetResult(BlobResult[4], M_BOX_X_MIN+M_TYPE_DOUBLE,BadBlobData.MinX);
			// Blob Box Max X
			MblobGetResult(BlobResult[4], M_BOX_X_MAX+M_TYPE_DOUBLE,BadBlobData.MaxX);

		}

	}
	//------------------------------------------------------------------------------------//

	// Bring back the blobs touching bottom of image
	MblobSelect(BlobResult[0], M_INCLUDE_ONLY, M_EXCLUDED_BLOBS, M_NULL,M_NULL,M_NULL);

	// Swap result buffers IDs for the next merge
	MIL_ID BlobResultTemp = BlobResult[0];
	BlobResult[0] = BlobResult[1];
	BlobResult[1] = BlobResultTemp;

	return (int)TotalBlobs;

}
//---------------------------------------------------------------------------------------//
// GetLaneBitPosition()
//---------------------------------------------------------------------------------------//
MIL_INT64 CBlob::GetLaneBitPosition(int i,VISIONSETTINGS2* pSettings)
{
	int CogX = (int)BadBlobData.CogX[i];

	if (CogX <= pSettings->PosLane1)
		return M_IO_COMMAND_BIT1;
		//return M_IO_COMMAND_BIT0;

	if (CogX <= pSettings->PosLane2)
		return M_IO_COMMAND_BIT1;

	if (CogX <= pSettings->PosLane3)
		return M_IO_COMMAND_BIT2;

	if (CogX <= pSettings->PosLane4)
		return M_IO_COMMAND_BIT3;

	if (CogX <= pSettings->PosLane5)
		return M_IO_COMMAND_BIT4;

	if (CogX <= pSettings->PosLane6)
		return M_IO_COMMAND_BIT5;

	if (CogX <= pSettings->PosLane7)
		return M_IO_COMMAND_BIT6;

	return M_IO_COMMAND_BIT7;

}
//---------------------------------------------------------------------------------------//
// GetLaneOffsetDelay()
//---------------------------------------------------------------------------------------//
int CBlob::GetLaneOffsetDelay(int i,VISIONSETTINGS2* pSettings)
{
	int CogX = (int)BadBlobData.CogX[i];

	if (CogX <= pSettings->PosLane1)
		return pSettings->OffsetLane1;

	if (CogX <= pSettings->PosLane2)
		return pSettings->OffsetLane2;

	if (CogX <= pSettings->PosLane3)
		return pSettings->OffsetLane3;

	if (CogX <= pSettings->PosLane4)
		return pSettings->OffsetLane4;

	if (CogX <= pSettings->PosLane5)
		return pSettings->OffsetLane5;

	if (CogX <= pSettings->PosLane6)
		return pSettings->OffsetLane6;

	if (CogX <= pSettings->PosLane7)
		return pSettings->OffsetLane7;

	return pSettings->OffsetLane8;

}

//---------------------------------------------------------------------------------------//
// GetLaneOffsetPassDelay()
//---------------------------------------------------------------------------------------//
int CBlob::GetLaneOffsetPassDelay(int i,VISIONSETTINGS2* pSettings)
{
	int CogX = (int)GoodBlobData.CogX[i];

	if (CogX <= pSettings->PosLane1)
		return pSettings->OffsetLane1;

	if (CogX <= pSettings->PosLane2)
		return pSettings->OffsetLane2;

	if (CogX <= pSettings->PosLane3)
		return pSettings->OffsetLane3;

	if (CogX <= pSettings->PosLane4)
		return pSettings->OffsetLane4;

	if (CogX <= pSettings->PosLane5)
		return pSettings->OffsetLane5;

	if (CogX <= pSettings->PosLane6)
		return pSettings->OffsetLane6;

	if (CogX <= pSettings->PosLane7)
		return pSettings->OffsetLane7;

	return pSettings->OffsetLane8;

}

//---------------------------------------------------------------------------------------//
// GetLaneDelay()
//---------------------------------------------------------------------------------------//
int CBlob::GetLaneDelay(int i)
{
	return (int)BadBlobData.MinY[i];
	//return (int)BadBlobData.CogY[i];
}

//---------------------------------------------------------------------------------------//
// GetLanePassDelay()
//---------------------------------------------------------------------------------------//
int CBlob::GetLanePassDelay(int i)
{
	return (int)GoodBlobData.MinY[i];
}
//---------------------------------------------------------------------------------------//
// GetLaneDuration()
//---------------------------------------------------------------------------------------//
int CBlob::GetLaneDuration(int i)
{
	int Delay = (int)(BadBlobData.MaxY[i] - BadBlobData.MinY[i]);
	if (Delay < 150) Delay = 150;
	return Delay;
}

int CBlob::GetBlobPosX(int n)
{
	return (int)GoodBlobData.CogX[n];
}

int CBlob::FindBaconLockSize(VISIONSETTINGS2* pSettings)
{
	//int  Count = 0;
	//long AveSize = 0;

	//if (GoodBlobData.TotalBlobs==0)
	//	return m_LockSize;

	//// Put in size FIFO
	//for (int i=0; i< GoodBlobData.TotalBlobs; i++)
	//{
	//	if (GoodBlobData.Area[i] >= pSettings->SizeLockMin &&
	//		GoodBlobData.Area[i] <= pSettings->SizeLockMax)
	//	{
	//		// Pump the FIFO
	//		for (int ii=0; ii< pSettings->SizeLockCount-1; ii++)
	//		{
	//			m_SizeFIFO[ii] = m_SizeFIFO[ii+1];
	//		}
	//		m_SizeFIFO[pSettings->SizeLockCount-1] = (long)GoodBlobData.Area[i];
	//	}

	//}

	//// Find Ave size
	//for (int i=0; i< pSettings->SizeLockCount; i++)
	//{
	//	if (m_SizeFIFO[i] > 0)
	//	{
	//		Count++;
	//		AveSize += m_SizeFIFO[i];
	//	}
	//}

	//if (Count == pSettings->SizeLockCount)
	//{
	//	m_LockSize = AveSize/Count;
	//}
	//return m_LockSize;
	return 0;
}

double CBlob::CalculateMotorPos(double In,double Offset,double StartPos,double Pitch)
{

	//----------------------------------//
	double ImagePos = In;               // Input from vision
	double HomeOffset = Offset;         // Parameter
	double AlignPitch = Pitch;          // Parameter
	double StartPosition = StartPos;    // Parameter
	//----------------------------------//

	if (AlignPitch < 0.1) AlignPitch = 0.1;
	double CtsPerInch = ALIGN_CTS_PER_REV/AlignPitch;
	double ThetaChange;
	double pi = 4*atan(1.0);
	double DegPerRad = 360.0/(2*pi);
	double StartLength = ALIGN_MAX_C + ((StartPosition-HomeOffset)/CtsPerInch);
	double ThetaStart = acos( ((ALIGN_SIDE_A*ALIGN_SIDE_A+ALIGN_SIDE_B*ALIGN_SIDE_B)- StartLength*StartLength)/(2*ALIGN_SIDE_A*ALIGN_SIDE_B) );
	//m_StartLength = StartLength;
	TRACE("StartLength %f \n",StartLength);

	// Degrees of adjustment
	ThetaChange = atan(ImagePos/ALIGN_RADIUS);
	//m_dbOut = ThetaChange*DegPerRad;
	TRACE("ThetaChange %f \n",ThetaChange*DegPerRad);

	// New total length of side C
	double ThetaNew = ThetaStart + ThetaChange;
	double NewLength = (ALIGN_SIDE_A*ALIGN_SIDE_A+ALIGN_SIDE_B*ALIGN_SIDE_B) - (2*ALIGN_SIDE_A*ALIGN_SIDE_B*cos(ThetaNew));
	NewLength = sqrt(NewLength);
	//m_dbPos = NewLength;
	TRACE("NewLength %f \n",NewLength);

	// Result motor position
	double mtrPos = (ALIGN_MAX_C - NewLength);               // Distance retracted from home positoin.
	double mtrPosCts = -((mtrPos*CtsPerInch)-HomeOffset);  // Motor position to achieve new length.
	TRACE("mtrPosCts %f \n",mtrPosCts);
	return mtrPosCts;


}

//-------------------------------------------------------------------------------------------------------------------------------//
// GetAlignPosX(...)
//-------------------------------------------------------------------------------------------------------------------------------//
double CBlob::GetAlignPosX(int Index,VISIONSETTINGS3* pSettings3,MOTIONSETTINGS* pMotion)
{
	double dbAlignPos;
	double CalPos;
	double PosOffset;
	double NewPixelPos;
	double Center;

	if (pSettings3->ImageCenter == 0)
	{
		TRACE("Using LUT\n");		
		CalPos = InterpolateXtoY(GoodBlobData.CogX[Index]);            // Translate pixels to inches
		PosOffset = CalPos - pSettings3->dbAlignOffset;                // Position in inches - offset
		NewPixelPos = InterpolateYtoX(PosOffset);                      // Translate inches to pixel position
		dbAlignPos = InterpolatePos(pSettings3,NewPixelPos);           // Get motor position	
	}
	else
	{
		//TRACE("\nUsing Formula StartPos:%f \n",pMotion->dbPvars[30]);		
		//TRACE("Using Formula Home offset :%f \n",pMotion->dbPvars[31]);		
		//TRACE("Using Formula Pitch :%f \n",pSettings3->Pitch);		

		CalPos = InterpolateXtoY(GoodBlobData.CogX[Index]);           // Translate pixels to inches
		//CalPos = InterpolateXtoY(575); // Test
		Center = InterpolateXtoY(pSettings3->ImageCenter);            // Translate pixels to inches
		//TRACE("CalPos:%f Center:%f  ImagePos: %f \n",CalPos,Center,GoodBlobData.CogX[Index]);
		if (pSettings3->CameraDirection == 0)
		{
			PosOffset = (CalPos-Center) - pSettings3->dbAlignOffset;
			//TRACE("Center:%f CalPos-Center :%f \n",Center,PosOffset);		
		}
		else
		{
			PosOffset = (Center-CalPos) - pSettings3->dbAlignOffset;
			//TRACE("Center:%f Center-CalPos :%f \n",Center,PosOffset);		
		}
		//TRACE("PosOffset :%f AlignOffset:%f \n",PosOffset,pSettings3->dbAlignOffset);	
		//PosOffset = 0; // Test
		dbAlignPos = CalculateMotorPos(PosOffset,pMotion->dbPvars[31],pMotion->dbPvars[30],pSettings3->Pitch);
		//dbAlignPos = CalculateMotorPos(PosOffset,10000,-51440,0.2);     // Calculate motor position
		//TRACE("AveBacPos: %f\n",AveBacPos);		
	}
	return dbAlignPos;
}

//-------------------------------------------------------------------------------------------------------------------------------//
// FillBaconBuffer(...)
//-------------------------------------------------------------------------------------------------------------------------------//
int CBlob::FillBaconBuffer(VISIONSETTINGS1* pSettings1,VISIONSETTINGS2* pSettings2,VISIONSETTINGS3* pSettings3,VISIONSETTINGS4* pSettings4,
	unsigned _int16* BaconBuff,unsigned _int16* BaconBuffRaw,
	unsigned _int16* BaconBuffReject,int* pGoodCount,int* pRejectCount,int BuffSize)
{
	double DelayPos;
	int    FillIndex = 2;
	int    FillIndex2 = 2;
	int    BaconCount = 0;
	int    BaconGoodCount = 0;
	int    BaconBadCount = 0;
	double dbAlignPos;
	unsigned _int16 AlignPos;
	double CalPos;
	double PosOffset;
	double NewPixelPos;
	*pRejectCount = BaconBadCount;

	// Any found?
	if (GoodBlobData.TotalBlobs==0)
	{
		BaconBuff[0]          = 0xFFFF;  // Data Ready
		BaconBuff[1]          = 0;       // Count
		BaconBuff[BuffSize]   = 0;       // Count       32
		BaconBuff[BuffSize+1] = 0xFFFF;  // Data Ready  33
		return BaconCount;
	}

	// Buffer limit
	if (GoodBlobData.TotalBlobs > MAX_BACON_COUNT)
	{
		GoodBlobData.TotalBlobs = MAX_BACON_COUNT;
	}

	// Fill
	for (int i=0; i< GoodBlobData.TotalBlobs; i++)
	{

		// X,Y Positions for display
		//-------------------------------------------------------------//
		BaconBuffRaw[FillIndex] = (unsigned _int16)GoodBlobData.MinY[i];   // Raw Y
		BaconBuffRaw[FillIndex+1] = (unsigned _int16)GoodBlobData.CogX[i]; // Raw X
		if ((FillIndex + 2) < BuffSize)                                // Limit buffer index
		{                                                              //
			FillIndex += 2;                                            // Inc index
		}                                                              //
		BaconCount++;                                                  // Count
		//-------------------------------------------------------------//
			
		//TRACE("GoodBlobData.Area[%d]=%f pSettings1->MinBaconPassSize=%d \n",i,GoodBlobData.Area[i],pSettings1->MinBaconRejectSize);
		if ((GoodBlobData.Area[i] > (MIL_DOUBLE)pSettings1->MinBaconRejectSize &&
			GoodBlobData.FeretX[i] > (MIL_DOUBLE)pSettings1->MinBaconRejectWidth &&
			(GoodBlobData.MaxY[i]-GoodBlobData.MinY[i]) > (MIL_DOUBLE)pSettings1->MinBaconRejectHeight) || pSettings1->MinBaconRejectSize==0)
		{
			// X,Y Positions for bacon alignment
			//-------------------------------------------------------------//
			DelayPos = m_ImageSizeY - GoodBlobData.MinY[i];                    //
			BaconBuff[FillIndex2] = (unsigned _int16)DelayPos;             // Y Position
			CalPos = InterpolateXtoY(GoodBlobData.CogX[i]);                    // Translate pixels to inches
			PosOffset = CalPos - pSettings3->dbAlignOffset;                // Position in inches - offset
			NewPixelPos = InterpolateYtoX(PosOffset);                      // Translate inches to pixel position
			dbAlignPos = InterpolatePos(pSettings3,NewPixelPos);           // Get motor position
			if (dbAlignPos > 0) dbAlignPos = 0;                            // Limit check
			dbAlignPos = abs((long)dbAlignPos);                            // Pos number
			AlignPos = (unsigned _int16)dbAlignPos;                        // 
			BaconBuff[FillIndex2+1] = AlignPos;                            // X Position
			if ((FillIndex2 + 2) < BuffSize)                               // Index limit
			{                                                              //
				FillIndex2 += 2;                                           //
			}                                                              //
			BaconGoodCount++;                                              // Count
			//-------------------------------------------------------------//

		}
		else
		{
			// Y Positions for bacon reject
			//-------------------------------------------------------------//
			BaconBuffReject[BaconBadCount] = (unsigned _int16)GoodBlobData.MinY[i];   // Y
			//TRACE("Reject GoodBlobData.Area[%d]=%f pSettings1->MinBaconPassSize=%d \n",i,BlobData.Area[i],pSettings1->MinBaconPassSize);
			//TRACE("Reject Pos Y %d \n",BaconBuffReject[BaconBadCount]);
			BaconBadCount++;
			if (BaconBadCount >= BuffSize) BaconBadCount = BuffSize;

		}

	}
	//--------------------------------------------------------------------//

	// Set good bacon and bad baocn count.
	//--------------------------------------------------------------------//
    BaconBuff[0]          = 0xFFFF;          // Data Ready
	BaconBuff[1]          = 0;               // Always zero
	BaconBuff[BuffSize]   = BaconGoodCount;  // Count
	BaconBuff[BuffSize+1] = 0xFFFF;          // Data Ready
	*pGoodCount = BaconGoodCount;
	*pRejectCount = BaconBadCount;
	//TRACE("*pRejectCount %d \n",*pRejectCount);
	return BaconCount;

	//TRACE("m_ImageSizeY %d Raw Pos: %f \n",m_ImageSizeY,SplitPos);
	//TRACE("m_ImageSizeY %d Corrected Pos: %f \n",m_ImageSizeY,SplitPos);
	//TRACE("Align offsset setting.......................... %4.1f \n",pSettings3->dbAlignOffset);
	//TRACE("Motor Position %d \n",AlignPos);

}
void CBlob::ShowEndDetectBlobData(MIL_ID ImageId,MIL_DOUBLE BackColor,MIL_DOUBLE TextColor)
{
	//if (BlobData.TotalBlobs == 0)
	//	return;
	MIL_DOUBLE TotalBlobArea = 0;
	TCHAR szText[1024];


	MgraFontScale(M_DEFAULT,1.0,1.0);
	//MgraColor(M_DEFAULT,  M_RGB888(255,0,0));
	//MgraBackColor(M_DEFAULT,M_RGB888(255,255,255));
	MgraColor(M_DEFAULT,  TextColor);
	MgraBackColor(M_DEFAULT,BackColor);
	MgraControl(M_DEFAULT, M_BACKGROUND_MODE, M_TRANSPARENT);

	// Total Area
	for (int i=0; i< BlobData.TotalBlobs; i++)
	{
		TotalBlobArea += BlobData.Area[i];
	}

	// Draw
	_stprintf_s(szText,64,_T("Count:%d"),(long)BlobData.TotalBlobs);
	MgraText(M_DEFAULT, ImageId, 5, 5, szText);
	_stprintf_s(szText,64,_T("Size:%d"),(long)TotalBlobArea);
	MgraText(M_DEFAULT, ImageId, 5, 22, szText);
		

}
//void CBlob::ShowBlobs2(MIL_ID SrcImageId,MIL_ID DstImageId,int Count,double BaconSpeed)
//{
//	//TCHAR szText[1024];
//	int y = 2;
//
//	if (BlobData.TotalBlobs == 0)
//		return;
//
//	MbufClear(SrcImageId,0);
//	MgraColor(M_DEFAULT,M_RGB888(255,255,255));
//	MblobDraw(M_DEFAULT, BlobResult[2], SrcImageId, M_DRAW_BLOBS,M_INCLUDED_BLOBS, M_DEFAULT);
//
//	// Resize to mini display size
//	MimResize(SrcImageId,DstImageId,M_FILL_DESTINATION,M_FILL_DESTINATION,M_DEFAULT);
//
//	// Set the drawing mode
//	MgraFontScale(M_DEFAULT,1.0,1.0);
//	MgraColor(M_DEFAULT,  M_RGB888(0,255,0));
//	MgraBackColor(M_DEFAULT,M_RGB888(0,0,0));
//	MgraControl(M_DEFAULT, M_BACKGROUND_MODE,M_OPAQUE );
//
//	// Show the count and speed
//	//_stprintf_s(szText,64,_T("Count:%d           Speed:%5.1f SPM"),Count,BaconSpeed);
//	//MgraText(M_DEFAULT, DstImageId, 2,y, szText);	
//	//y += 16;
//
//	// Show source blobs
//	//for (int i=0; i< BlobData.TotalBlobs; i++)
//	//{
//	//	_stprintf_s(szText,64,_T("B:%d S:%d"),i,(long)BlobData.Area[i]);
//	//	MgraText(M_DEFAULT, DstImageId, 2, y, szText);
//	//	y += 16;
//
//	//}
//
//
//}

//-------------------------------------------------------------------------------------------------------------//
// ShowGoodBlobs(MIL_ID ImageId)
//-------------------------------------------------------------------------------------------------------------//
void CBlob::ShowGoodBlobs(MIL_ID ImageId)
{
	if (GoodBlobData.TotalBlobs == 0)
	{
		return;
	}
	//TRACE("Results Show Good Blobs:%d     \n",GoodBlobData.TotalBlobs);

	TCHAR szText[1024];
	double Width;
	double Height;

	// Show bacon in white
	MbufClear(ImageId,0);
	bClearImage = false;
	MgraColor(M_DEFAULT,M_RGB888(255,255,255));
	MblobDraw(M_DEFAULT, BlobResult[2], ImageId, M_DRAW_BLOBS,M_INCLUDED_BLOBS, M_DEFAULT);

	// Show box center in green
	MgraColor(M_DEFAULT,M_RGB888(0,255,0));
	MblobDraw(M_DEFAULT, BlobResult[2], ImageId, M_DRAW_BOX_CENTER+M_DRAW_BOX,M_INCLUDED_BLOBS, M_DEFAULT);

	// Set the font scale
	MgraFontScale(M_DEFAULT,1.0,1.0);
	//MgraColor(M_DEFAULT,  M_RGB888(0,255,105));
	MgraColor(M_DEFAULT,  M_RGB888(0,0,105));
	MgraBackColor(M_DEFAULT,M_RGB888(255,255,255));

	// Show source blobs
	MgraControl(M_DEFAULT, M_BACKGROUND_MODE, M_TRANSPARENT);
	for (int i=0; i< GoodBlobData.TotalBlobs; i++)
	{
		_stprintf_s(szText,64,_T("Size:%d"),(long)GoodBlobData.Area[i]);
		MgraText(M_DEFAULT, ImageId, GoodBlobData.CogX[i]-30, GoodBlobData.CogY[i]-28, szText);

		Width = GoodBlobData.MaxX[i] - GoodBlobData.MinX[i];
		Height = GoodBlobData.MaxY[i] - GoodBlobData.MinY[i];
		//_stprintf_s(szText,64,_T("W:%d H:%d"),(long)GoodBlobData.Feret[i]);
		_stprintf_s(szText,64,_T("H:%d W:%d"),(long)Height,(long)Width);
		MgraText(M_DEFAULT, ImageId, GoodBlobData.CogX[i]-35, GoodBlobData.CogY[i]+20, szText);	

	}

	MgraColor(M_DEFAULT,  M_RGB888(0,255,0));
	_stprintf_s(szText,64,_T("Good:%d"),GoodBlobData.TotalBlobs);
	MgraText(M_DEFAULT, ImageId, 2,2, szText);	
	//TRACE("BaconCount:%d \n",BaconCount);

}
//-------------------------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------------------------//
// ShowBadBlobs(MIL_ID ImageId)
//-------------------------------------------------------------------------------------------------------------//
void CBlob::ShowBadBlobs(MIL_ID ImageId)
{
	if (BadBlobData.TotalBlobs == 0)
	{
		return;
	}
	TRACE("BadBlobData:%d     \n",BadBlobData.TotalBlobs);

	TCHAR szText[1024];
	//double Width;
	//double Height;

	// Show bacon in white
	if (bClearImage)
	{
		MbufClear(ImageId,0);
	}

	MgraColor(M_DEFAULT,M_RGB888(255,0,0));
	MblobDraw(M_DEFAULT, BlobResult[4], ImageId, M_DRAW_BLOBS,M_INCLUDED_BLOBS, M_DEFAULT);

	// Show box center in green
	MgraColor(M_DEFAULT,M_RGB888(255,255,255));
	MblobDraw(M_DEFAULT, BlobResult[4], ImageId, M_DRAW_BOX_CENTER+M_DRAW_BOX,M_INCLUDED_BLOBS, M_DEFAULT);

	// Set the font scale
	MgraFontScale(M_DEFAULT,1.0,1.0);
	MgraColor(M_DEFAULT,  M_RGB888(255,255,255));
	MgraBackColor(M_DEFAULT,M_RGB888(255,255,255));

	// Show source blobs
	MgraControl(M_DEFAULT, M_BACKGROUND_MODE, M_TRANSPARENT);
	for (int i=0; i< BadBlobData.TotalBlobs; i++)
	{
		_stprintf_s(szText,64,_T("Size:%d"),(long)BadBlobData.Area[i]);
		MgraText(M_DEFAULT, ImageId, BadBlobData.CogX[i]-10, BadBlobData.CogY[i]-18, szText);

		//Width = BadBlobData.MaxX[i] - BadBlobData.MinX[i];
		//Height = BadBlobData.MaxY[i] - BadBlobData.MinY[i];
		//_stprintf_s(szText,64,_T("W:%d H:%d"),(long)BadBlobData.Feret[i]);
		//_stprintf_s(szText,64,_T("H:%d W:%d"),(long)Height,(long)Width);
		//MgraText(M_DEFAULT, ImageId, BadBlobData.CogX[i]-35, BadBlobData.CogY[i]+20, szText);	

	}
	// Sho bad count
	MgraColor(M_DEFAULT,  M_RGB888(255,0,0));
	_stprintf_s(szText,64,_T("Bad:%d"),BadBlobData.TotalBlobs);
	MgraText(M_DEFAULT, ImageId, 2,22, szText);	
	//TRACE("BaconCount:%d \n",BaconCount);

}
//-------------------------------------------------------------------------------------------------------------//
void CBlob::ShowBlobs2(MIL_ID SrcImageId,MIL_ID DstImageId,int Count,double BaconSpeed)
{
	TCHAR szText[1024];
	int y = 2;

	if (GoodBlobData.TotalBlobs == 0)
		return;

	MbufClear(SrcImageId,0);
	MgraColor(M_DEFAULT,M_RGB888(255,255,255));
	MblobDraw(M_DEFAULT, BlobResult[2], SrcImageId, M_DRAW_BLOBS,M_INCLUDED_BLOBS, M_DEFAULT);

	// Resize to mini display size
	MimResize(SrcImageId,DstImageId,M_FILL_DESTINATION,M_FILL_DESTINATION,M_DEFAULT);

	// Set the drawing mode
	MgraFontScale(M_DEFAULT,1.0,1.0);
	MgraColor(M_DEFAULT,  M_RGB888(0,255,0));
	MgraBackColor(M_DEFAULT,M_RGB888(0,0,0));
	MgraControl(M_DEFAULT, M_BACKGROUND_MODE,M_OPAQUE );

	// Show the count
	_stprintf_s(szText,64,_T("Count:%d"),Count);
	MgraText(M_DEFAULT, DstImageId, 2,y, szText);	
	y += 16;

	// Show the size
	_stprintf_s(szText,64,_T("Size:%d"),(long)GoodBlobData.Area[0]);
	MgraText(M_DEFAULT, DstImageId, 2, y, szText);

	// Show the count and speed
	//_stprintf_s(szText,64,_T("Count:%d           Speed:%5.1f SPM"),Count,BaconSpeed);
	//MgraText(M_DEFAULT, DstImageId, 2,y, szText);	
	//y += 16;

	// Show source blobs
	//for (int i=0; i< GoodBlobData.TotalBlobs; i++)
	//{
	//	_stprintf_s(szText,64,_T("B:%d S:%d"),i,(long)GoodBlobData.Area[i]);
	//	MgraText(M_DEFAULT, DstImageId, 2, y, szText);
	//	y += 16;

	//}


}
/////////////////////////////////////////////////////////////////////////////////
// Functon: InterpolatePos()
//
// Description: This function uses linear interpolation to convert pixel
//              position to Motor positon.
//
/////////////////////////////////////////////////////////////////////////////////.
double CBlob::InterpolatePos(VISIONSETTINGS3* pSettings,double x)
{
	double y;

	double x0;
	double x1;
	double x2;
	double y0;
	double y1;
	double y2;

	x0 = pSettings->ImagePosX0;
	x1 = pSettings->ImagePosX1;
	x2 = pSettings->ImagePosX2;
	y0 = pSettings->MotorPosY0;
	y1 = pSettings->MotorPosY1;
	y2 = pSettings->MotorPosY2;

	if (x <= x0)
	{
		return y0;
	}
	if (x >= x2)
	{
		return y2;
	}

	if (x <= x1)
	{
		y = y0 + (x-x0)*((y1-y0)/(x1-x0));
	}
	else
	{
		y = y1 + (x-x1)*((y2-y1)/(x2-x1));	
	}
	return y;

}

/////////////////////////////////////////////////////////////////////////////////
// Functon: InterpolatePosTrimMode()
//
// Description: This function uses linear interpolation to convert pixel
//              position to Motor positon.
//
/////////////////////////////////////////////////////////////////////////////////.
double CBlob::InterpolatePosTrimMode(VISIONSETTINGS4* pSettings,double x)
{
	double y;

	double x0;
	double x1;
	double y0;
	double y1;

	x0 = pSettings->ImagePosX0;
	x1 = pSettings->ImagePosX1;
	y0 = pSettings->MotorPosY0;
	y1 = pSettings->MotorPosY1;

	if (x <= x0)
	{
		return y0;
	}
	if (x >= x1)
	{
		return y1;
	}
	y = y0 + (x-x0)*((y1-y0)/(x1-x0));

	return y;

}

/////////////////////////////////////////////////////////////////////////////////
// Functon: InterpolateXtoY()
//
// Description: This function uses linear interpolation to convert pixel
//              position to position in inches
//
/////////////////////////////////////////////////////////////////////////////////.
double CBlob::InterpolateXtoY(double x)
{
	//----------------------------------  0    1    2    3    4    5    6    7    8    9    10    11    12  13  //
	static const double PointsX[14] = { 174, 221, 270, 320, 372, 426, 479, 534, 588, 641,  694,  745,  793, 841 };
	static const double PointsY[14] = { 0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0 };
	double y;
	double x0;
	double x1;
	double y0;
	double y1;

	if (x <= PointsX[0])
	{
		return PointsY[0];
	}
	if (x >= PointsX[13])
	{
		return PointsY[13];
	}

	// Assume last point will be used
	x0 = PointsX[12]; x1 = PointsX[13];
	y0 = PointsY[12]; y1 = PointsY[13];

	// Find the interpolation points
	for (int i=0; i<13; i++)
	{
		if ((x >= PointsX[i]) && (x <= PointsX[i+1]))
		{
			x0 = PointsX[i]; x1 = PointsX[i+1];
			y0 = PointsY[i]; y1 = PointsY[i+1];
			break;
		}
	}

	// Result
	y = y0 + (x-x0)*((y1-y0)/(x1-x0));

	return y;

}
/////////////////////////////////////////////////////////////////////////////////
// Functon: InterpolateYtoX()
//
// Description: This function uses linear interpolation to convert
//              position in inches to pixel positoin.
//
/////////////////////////////////////////////////////////////////////////////////.
double CBlob::InterpolateYtoX(double x)
{
	//----------------------------------  0    1    2    3    4    5    6    7    8    9    10    11    12  13  //
	static const double PointsY[14] = { 174, 221, 270, 320, 372, 426, 479, 534, 588, 641,  694,  745,  793, 841 };
	static const double PointsX[14] = { 0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0 };
	double y;
	double x0;
	double x1;
	double y0;
	double y1;
	if (x <= PointsX[0])
	{
		return PointsY[0];
	}
	if (x >= PointsX[13])
	{
		return PointsY[13];
	}

	// Assume last point will be used
	x0 = PointsX[12]; x1 = PointsX[13];
	y0 = PointsY[12]; y1 = PointsY[13];

	// Find the interpolation point
	for (int i=0; i<13; i++)
	{
		if ((x >= PointsX[i]) && (x <= PointsX[i+1]))
		{
			x0 = PointsX[i]; x1 = PointsX[i+1];
			y0 = PointsY[i]; y1 = PointsY[i+1];
			break;
		}
	}

	// Result
	y = y0 + (x-x0)*((y1-y0)/(x1-x0));

	return y;

}