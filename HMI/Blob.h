//======================================================================
// Header file
//
// Written for the BOV Slicer
// Copyright (C) 2013 Bill Young
//================================================================
#pragma once

#include <mil.h>
//#include "Include\mil.h"
#include "..\HMIDlg\HMIDlgApi.h"

#define MAX_BLOBS       1000                  // Limit
#define MAX_BACON_COUNT   15                  // Buffer limit in DPRAM


#define ALIGN_MAX_C        14.75
//#define ALIGN_MIN_C        11.75
#define ALIGN_SIDE_A       19.82
#define ALIGN_SIDE_B       21.0
#define ALIGN_RADIUS       40.5
#define ALIGN_CTS_PER_REV  8192.0


// User's processing function hook data structure. 
typedef struct tagBLOBRESULTDATASTRUCT {
	long      TotalBlobs;
	MIL_DOUBLE MinX[MAX_BLOBS];                /* X coordinate of left edge          */
    MIL_DOUBLE MaxX[MAX_BLOBS];                /* X coordinate of left edge          */
    MIL_DOUBLE MinY[MAX_BLOBS];                /* X coordinate of left edge          */
    MIL_DOUBLE MaxY[MAX_BLOBS];                /* X coordinate of left edge          */
    MIL_DOUBLE CogY[MAX_BLOBS];                /* Y coordinate of center of gravity. */
    MIL_DOUBLE CogX[MAX_BLOBS];                /* Y coordinate of center of gravity. */
    MIL_DOUBLE Area[MAX_BLOBS];                /* Blob Size.                         */
    MIL_DOUBLE FeretX[MAX_BLOBS];              /* Blob Size.                         */
    MIL_DOUBLE FeretY[MAX_BLOBS];              /* Blob Size.                         */
} BLOBRESULTDATA;

// User's processing function hook data structure. 
//typedef struct tagBLOBSETTINGS {
//	double     dbMinArea;
//	double     dbSplitSize;
//	double     dbScaleX;
//	double     dbScaleY;
//} BLOBSETTINGS;

#define FIFO_SIZE 64

class CBlob
{
public:
	MIL_ID     MilSystem;                      /* System identifier.                 */
    MIL_ID     BlobResult[5];                  /* Blob result buffer identifier.     */
    MIL_ID     MilBlobFeatureList;             /* Feature list identifier.           */
	MIL_ID     MilRejectBlobImage;
    //MIL_INT    TotalBlobs;                     /* Total number of blobs.             */
    //long       BlobsCount;
	//double     MinBlobArea;
	//double     MinBlobWidth;
	//double     MinOffBlobArea;
	//double     MinOffBlobWidth;
	//double     MinBlobSize;
	//int        CalModeEndCount;
	//double     MaxAreaClearOfSides;
	//double     dbScalePPIX;
	//double     dbScalePPIY;
	BLOBRESULTDATA  GoodBlobData;
	BLOBRESULTDATA  BadBlobData;
	BLOBRESULTDATA BlobData;
	bool         bClearImage;
	long         m_LockSize;
	long         m_ImageSizeY;
	long         m_SizeFIFO[FIFO_SIZE];

public:
	CBlob(void);
	~CBlob(void);
	void Alloc(MIL_ID SysId,MIL_ID ImageId);
	void Free();
	double CalculateMotorPos(double In,double Offset,double StartPos,double Pitch);
	//int GetAlignPosX(int Index,VISIONSETTINGS1* pSettings1,VISIONSETTINGS2* pSettings2,VISIONSETTINGS3* pSettings3,VISIONSETTINGS4* pSettings4);
	double CBlob::GetAlignPosX(int Index,VISIONSETTINGS3* pSettings3,MOTIONSETTINGS* pMotion);
	//int GetAlignPosY(int Index,VISIONSETTINGS1* pSettings1,VISIONSETTINGS2* pSettings2,VISIONSETTINGS3* pSettings3,VISIONSETTINGS4* pSettings4);
	//void SetMinSizes(double MinXSize,double MinArea,double MinSize);
	//void SetOffSizes(double MinXSize,double MinArea);
	int FindBlobsMerge(MIL_ID ImageId,VISIONSETTINGS1* pSettings,VISIONSETTINGS2* pSettings2);
	int FillBaconBuffer(VISIONSETTINGS1* pSettings1,VISIONSETTINGS2* pSettings2,
		VISIONSETTINGS3* pSettings3,VISIONSETTINGS4* pSettings4,
		unsigned _int16* BaconBuff,unsigned _int16* BaconBuffRaw,
		unsigned _int16* BaconBuffReject,int* pGoodCount,int* pRejectCount,int BuffSize);
	int FindBaconLockSize(VISIONSETTINGS2* pSettings);
	int GetBlobPosX(int n);
	void ShowGoodBlobs(MIL_ID ImageId);
	void ShowBadBlobs(MIL_ID ImageId);
	void ShowEndDetectBlobData(MIL_ID ImageId,MIL_DOUBLE BackColor,MIL_DOUBLE TextColor);
	void ShowBlobs2(MIL_ID SrcImageId,MIL_ID DstImageId,int Count,double BaconSpeed);
	//int FillBaconBuffer(VISIONSETTINGS2* pSettings,VISIONSETTINGS3* pSettings3,unsigned _int16* BaconBuff,unsigned _int16* BaconBuffRaw,int BuffSize);
	//void ShowBlobsStats(MIL_ID ImageId,BLOBRESULTDATA* pBlobData);
	double InterpolatePos(VISIONSETTINGS3* pSettings,double x);
	double InterpolatePosTrimMode(VISIONSETTINGS4* pSettings,double x);
	double InterpolateXtoY(double x);
	double InterpolateYtoX(double y);
	MIL_INT64 GetLaneBitPosition(int i,VISIONSETTINGS2* pSettings);
	int GetLaneOffsetDelay(int i,VISIONSETTINGS2* pSettings);
	int GetLaneOffsetPassDelay(int i,VISIONSETTINGS2* pSettings);
	int GetLaneDelay(int i);
	int GetLanePassDelay(int i);
	int GetLaneDuration(int i);
	bool InspectEndDetectBlobs(MIL_ID ImageId,ALLSETTINGS* pSettings);
	int GetBlobCount();
	int GetEndDetectBlobCount();
	bool AnyBlobs();
};
