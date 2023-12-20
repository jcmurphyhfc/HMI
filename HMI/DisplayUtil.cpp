//======================================================================
// Sorce file
//
// Written for Bacon One Vision (BOV)
// Copyright (C) 2015 Bill Young
//================================================================

#include "stdafx.h"
#define DISPLAY_GLOBALS 
#include "DisplayUtil.h"

//#include <tchar.h>

//======================================================================================================//
// Function Name: UpdateImageData ()                                                                    //
//                                                                                                      //
//======================================================================================================//
void UpdateImageData(MIL_ID nID, IMAGEDATA* pData)
{
	TCHAR szText[1024];
	int yPos = 1;
	int xPos = 1;
	int ySpace = 15;
	const int SizeX = 200;
	const int SizeY = 80;

	MgraFontScale(M_DEFAULT,1.0,1.0);
	//MgraControl(M_DEFAULT, M_BACKGROUND_MODE, M_TRANSPARENT);
	MgraColor(M_DEFAULT,  TEXT_COLOR);
	MgraBackColor(M_DEFAULT,TITLE_COLOR);

	_stprintf_s(szText,64,_T("%d"),pData->FrameCount);
	MgraText(M_DEFAULT, nID, xPos+382, yPos, szText);	

	yPos+=ySpace+2;
	if (pData->Period > 9999) pData->Period = 9999;
	_stprintf_s(szText,64,_T("%-5d"),(int)pData->Period);
	MgraText(M_DEFAULT, nID, xPos+126, yPos, szText);	

	if (pData->PeriodMin > 9999) pData->PeriodMin = 9999;
	_stprintf_s(szText,64,_T("%-5d"),(int)pData->PeriodMin);
	MgraText(M_DEFAULT, nID, xPos+212, yPos, szText);	

	if (pData->PeriodMax > 9999) pData->PeriodMax = 9999;
	_stprintf_s(szText,64,_T("%-5d"),(int)pData->PeriodMax);
	MgraText(M_DEFAULT, nID, xPos+302, yPos, szText);

	//_stprintf_s(szText,64,_T("%3.2f"),1000.0/pData->Period);
	//MgraText(M_DEFAULT, nID, xPos+376, yPos, szText);

	//_stprintf_s(szText,64,_T("%3.1f"),pData->MaxProc);
	//MgraText(M_DEFAULT, nID, xPos+550, yPos, szText);

	_stprintf_s(szText,64,_T("%3.1f"),pData->MaxProc);
	MgraText(M_DEFAULT, nID, xPos+462, yPos, szText);

	double RPM = 0;
	if (pData->Period > 0)
	{
		RPM = (1000.0/pData->Period)*60;
		RPM += 0.5;
	}
	_stprintf_s(szText,64,_T("%4d"),(int)RPM);
	MgraText(M_DEFAULT, nID, xPos+550, yPos, szText);

}

//======================================================================================================//
// Function Name: UpdateImageData ()                                                                    //
//                                                                                                      //
//======================================================================================================//
void UpdateImageDataSteer(MIL_ID nID, IMAGEDATA* pData)
{
	TCHAR szText[1024];
	int yPos = 1;
	int xPos = 1;
	int ySpace = 15;
	const int SizeX = 200;
	const int SizeY = 80;

	MgraFontScale(M_DEFAULT,1.0,1.0);
	//MgraControl(M_DEFAULT, M_BACKGROUND_MODE, M_TRANSPARENT);
	MgraColor(M_DEFAULT,  TEXT_COLOR);
	MgraBackColor(M_DEFAULT,TITLE_COLOR);

	_stprintf_s(szText,64,_T("%d"),pData->FrameCount);
	MgraText(M_DEFAULT, nID, xPos+382, yPos, szText);	

	yPos+=ySpace+2;
	if (pData->Period > 9999) pData->Period = 9999;
	_stprintf_s(szText,64,_T("%-5d"),(int)pData->Period);
	MgraText(M_DEFAULT, nID, xPos+126, yPos, szText);	

	if (pData->PeriodMin > 9999) pData->PeriodMin = 9999;
	_stprintf_s(szText,64,_T("%-5d"),(int)pData->PeriodMin);
	MgraText(M_DEFAULT, nID, xPos+212, yPos, szText);	

	if (pData->PeriodMax > 9999) pData->PeriodMax = 9999;
	_stprintf_s(szText,64,_T("%-5d"),(int)pData->PeriodMax);
	MgraText(M_DEFAULT, nID, xPos+302, yPos, szText);

	_stprintf_s(szText,64,_T("%3.2f"),1000.0/pData->Period);
	MgraText(M_DEFAULT, nID, xPos+376, yPos, szText);

	_stprintf_s(szText,64,_T("%3.1f"),pData->MaxProc);
	MgraText(M_DEFAULT, nID, xPos+550, yPos, szText);

	//_stprintf_s(szText,64,_T("%3.1f"),pData->MaxProc);
	//MgraText(M_DEFAULT, nID, xPos+462, yPos, szText);

	//_stprintf_s(szText,64,_T("%3.2f"),(1000.0/pData->Period)*60);
	//MgraText(M_DEFAULT, nID, xPos+550, yPos, szText);

}

//======================================================================================================//
// Function Name: DrawImageLabels ()                                                                    //
//                                                                                                      //
//======================================================================================================//
void DrawImageLabels(MIL_ID nID, LPCTSTR lpName)
{
	TCHAR szText[1024];
	int yPos = 1;
	int xPos = 1;
	int ySpace = 15;
	const int SizeX = 200;
	const int SizeY = 80;

	MgraFontScale(M_DEFAULT,1.0,1.0);
	MgraColor(M_DEFAULT,  LABEL_TEXT_COLOR);
	MgraBackColor(M_DEFAULT,TITLE_COLOR);

	_stprintf_s(szText,64,_T("%s"),lpName);
	MgraText(M_DEFAULT, nID, xPos, yPos,szText);	

	_stprintf_s(szText,64,_T("Frame Count:"));
	MgraText(M_DEFAULT, nID, xPos+280, yPos,szText);	

	yPos+=ySpace;
	yPos+=2;
	//_stprintf_s(szText,256,_T("Period(msec) T:      Tmin:      Tmax:      fps:       MaxProc(msec):"));
	  _stprintf_s(szText,256,_T("Period(msec) T:      Tmin:      Tmax:      MaxProc(msec):        RPM"));
	MgraText(M_DEFAULT, nID, xPos, yPos,szText);	

}

//======================================================================================================//
// Function Name: DrawImageLabels ()                                                                    //
//                                                                                                      //
//======================================================================================================//
void DrawImageLabelsSteer(MIL_ID nID, LPCTSTR lpName)
{
	TCHAR szText[1024];
	int yPos = 1;
	int xPos = 1;
	int ySpace = 15;
	const int SizeX = 200;
	const int SizeY = 80;

	MgraFontScale(M_DEFAULT,1.0,1.0);
	MgraColor(M_DEFAULT,  LABEL_TEXT_COLOR);
	MgraBackColor(M_DEFAULT,TITLE_COLOR);

	_stprintf_s(szText,64,_T("%s"),lpName);
	MgraText(M_DEFAULT, nID, xPos, yPos,szText);	

	_stprintf_s(szText,64,_T("Frame Count:"));
	MgraText(M_DEFAULT, nID, xPos+280, yPos,szText);	

	yPos+=ySpace;
	yPos+=2;
	_stprintf_s(szText,256,_T("Period(msec) T:      Tmin:      Tmax:      fps:       MaxProc(msec):"));
	//  _stprintf_s(szText,256,_T("Period(msec) T:      Tmin:      Tmax:      MaxProc(msec):        RPM"));
	MgraText(M_DEFAULT, nID, xPos, yPos,szText);	

}

//======================================================================================================//
// Function Name: DrawSteeringImageLabels ()                                                                    //
//                                                                                                      //
//======================================================================================================//
void DrawSteeringImageLabels(int x,int y, MIL_ID nID)
{
	TCHAR szText[1024];
	int xPos = x;
	int yPos = y;
	//int ySpace = 15;
	//const int SizeX = 200;
	//const int SizeY = 80;

	MgraFontScale(M_DEFAULT,1.5,1.5);
	MgraColor(M_DEFAULT,  LABEL_TEXT_COLOR);
	MgraBackColor(M_DEFAULT,TEXT_BACK_COLOR);

	_stprintf_s(szText,64,_T("Steering Position:"));
	MgraText(M_DEFAULT, nID, xPos, yPos,szText);	
	
}

//======================================================================================================//
// Function Name: DrawSteeringPosition ()                                                                    //
//                                                                                                      //
//======================================================================================================//
void DrawSteeringPosition(int x,int y, float Pos,MIL_ID nID)
{
	TCHAR szText[1024];
	int xPos = x;
	int yPos = y;

	MgraFontScale(M_DEFAULT,1.5,1.5);
	MgraColor(M_DEFAULT,  TEXT_COLOR);
	MgraBackColor(M_DEFAULT,TEXT_BACK_COLOR);

	_stprintf_s(szText,64,_T("%3.2f"),Pos);
	MgraText(M_DEFAULT, nID, xPos, yPos,szText);	
	
}

//======================================================================================================//
// Function Name: DrawBlobCount ()                                                                    //
//                                                                                                      //
//======================================================================================================//
void DrawBlobCount(int x,int y,long Count,MIL_ID nID)
{
	TCHAR szText[1024];
	int xPos = x;
	int yPos = y;

	MgraFontScale(M_DEFAULT,1.0,1.0);
	MgraColor(M_DEFAULT,  TEXT_COLOR);
	MgraBackColor(M_DEFAULT,TEXT_BACK_COLOR);

	_stprintf_s(szText,64,_T("%d"),Count);
	MgraText(M_DEFAULT, nID, xPos, yPos,szText);	
	
}

////======================================================================================================//
//// Function Name: UpdateModelData ()                                                                    //
////                                                                                                      //
////======================================================================================================//
//void UpdateModelPositionError(int x,int y,MIL_ID nID, MODELDATA* pResults0,MODELDATA* pResults1,DISPLAYPARAM* pDisplay)
//{
//	TCHAR szText[256];
//	int yPos = y;
//	int xPos = x;
//	int ySpace = 15;
//
//	const int SizeX = 250;
//	const int SizeY = 34;
//
//	MIL_ID ROI0,ROI1;
//	MbufChildColor2d(nID, M_ALL_BANDS, x-1, y-1, SizeX+2,SizeY+2, &ROI0);
//	MbufChildColor2d(nID, M_ALL_BANDS, x, y, SizeX,SizeY, &ROI1);
//	MbufClear(ROI0,M_COLOR_RED);
//	MbufClear(ROI1,20);
//	MbufFree(ROI0);
//	MbufFree(ROI1);
//
//	double xError = (pResults0->XPosition - pResults1->XPosition)*pDisplay->ResultScaleX; //*SCALE_X1;
//	double yError = (pResults0->YPosition - pResults1->YPosition)*pDisplay->ResultScaleY; //*SCALE_Y1;
//
//	MgraFontScale(M_DEFAULT,1.0,1.0);
//	MgraControl(M_DEFAULT, M_BACKGROUND_MODE, M_OPAQUE);
//	MgraColor(M_DEFAULT, M_COLOR_CYAN);
//
//	if (pResults1->NumModels == 0)
//	{
//		_stprintf_s(szText,64,_T("No Model found"));
//		MgraText(M_DEFAULT, nID, xPos, yPos, szText);	
//		return;	
//	}
//
//	_stprintf_s(szText,64,_T("X Model A-B Offset: %4.2f mm"),xError);
//	MgraText(M_DEFAULT, nID, xPos, yPos, szText);	
//	yPos+=ySpace;
//
//	_stprintf_s(szText,64,_T("Y Model A-B Offset: %4.2f mm"),yError);
//	MgraText(M_DEFAULT, nID, xPos, yPos, szText);	
//	yPos+=ySpace;
//
//}
//
////#define M_COLOR_BLACK                                 M_RGB888(0,0,0)
////#define M_COLOR_RED                                   M_RGB888(255,0,0)
////#define M_COLOR_GREEN                                 M_RGB888(0,255,0)
////#define M_COLOR_BLUE                                  M_RGB888(0,0,255)
////#define M_COLOR_YELLOW                                M_RGB888(255,255,0)
////#define M_COLOR_MAGENTA                               M_RGB888(255,0,255)
////#define M_COLOR_CYAN                                  M_RGB888(0,255,255)
////#define M_COLOR_WHITE                                 M_RGB888(255,255,255)
////#define M_COLOR_GRAY                                  M_RGB888(128,128,128)
////#define M_COLOR_BRIGHT_GRAY                           M_RGB888(192,192,192)
////#define M_COLOR_LIGHT_GRAY                            M_RGB888(160,160,164)
////#define M_COLOR_LIGHT_GREEN                           M_RGB888(192,220,192)
////#define M_COLOR_LIGHT_BLUE                            M_RGB888(166,202,240)
////#define M_COLOR_LIGHT_WHITE                           M_RGB888(255,251,240)
////#define M_COLOR_DARK_RED                              M_RGB888(128,0,0)
////#define M_COLOR_DARK_GREEN                            M_RGB888(0,128,0)
////#define M_COLOR_DARK_BLUE                             M_RGB888(0,0,128)
////#define M_COLOR_DARK_YELLOW                           M_RGB888(128,128,0)
////#define M_COLOR_DARK_MAGENTA                          M_RGB888(128,0,128)
////#define M_COLOR_DARK_CYAN                             M_RGB888(0,128,128)
//
////======================================================================================================//
//// Function Name: UpdateLaneResultData ()                                                                    //
////                                                                                                      //
////======================================================================================================//
//void UpdateLaneResultData(int x,int y,int SizeX,int SizeY,MIL_ID nID, LANERESULTDATA* pResults)
//{
//	TCHAR szText[256];
//	int yPos = y;
//	int xPos = x;
//	int ySpace = 25;
//
//	MIL_ID ROI;
//	MbufChildColor2d(nID, M_ALL_BANDS, xPos, yPos, SizeX,SizeY, &ROI);
//	//MbufClear(ROI,0);
//	MbufFree(ROI);
//
//	MgraColor(M_DEFAULT,M_COLOR_CYAN);//M_COLOR_WHITE
//	xPos += 2;
//
//	MgraFontScale(M_DEFAULT,1.5,1.5);
//	//MgraFontScale(M_DEFAULT,2.0,2.0);
//	MgraControl(M_DEFAULT, M_BACKGROUND_MODE, M_OPAQUE);
//
//	// Fill
//	_stprintf_s(szText,256,_T("%8.3f"),pResults->FillClearance);
//	MgraText(M_DEFAULT, nID, xPos, yPos, szText);	
//	yPos+=ySpace;	
//
//	_stprintf_s(szText,256,_T("%8.3f"),pResults->RimHeight);
//	MgraText(M_DEFAULT, nID, xPos, yPos, szText);	
//	yPos+=ySpace;
//
//	_stprintf_s(szText,256,_T("%8.3f"),pResults->RawHeight);
//	MgraText(M_DEFAULT, nID, xPos, yPos, szText);	
//	yPos+=ySpace;
//
//	_stprintf_s(szText,256,_T("%8.1f"),pResults->Volume);
//	MgraText(M_DEFAULT, nID, xPos, yPos, szText);	
//	yPos+=ySpace;
//
//	_stprintf_s(szText,256,_T("%8d"),pResults->TotalBlobArea);
//	MgraText(M_DEFAULT, nID, xPos, yPos, szText);	
//	yPos+=ySpace;
//
//	_stprintf_s(szText,256,_T("%8d"),pResults->MaxBlobArea);
//	MgraText(M_DEFAULT, nID, xPos, yPos, szText);	
//	yPos+=ySpace;
//
//	_stprintf_s(szText,256,_T("%8d"),pResults->TotalInspected);
//	MgraText(M_DEFAULT, nID, xPos, yPos, szText);	
//	yPos+=ySpace;
//
//	_stprintf_s(szText,256,_T("%8.1f"),pResults->PercentPass);
//	MgraText(M_DEFAULT, nID, xPos, yPos, szText);	
//	yPos+=ySpace;
//
//
//}
//
////======================================================================================================//
//// Function Name: Draw3DRect ()                                                               //
////                                                                                                      //
////======================================================================================================//
//void Draw3DRect(int x,int y,int SizeX,int SizeY,MIL_ID nID,MIL_DOUBLE clrTop,MIL_DOUBLE cltBottom)
//{
//	TCHAR szText[256];
//	int yPos = y+4;
//	int xPos = x+4;
//	int ySpace = 25;
//
//	MIL_ID ROI;
//	MbufChildColor2d(nID, M_ALL_BANDS, x, y, SizeX,SizeY, &ROI);
//	MbufClear(ROI,0);
//
//
//	MgraFontScale(M_DEFAULT,1.0,1.0);
//	//MgraFontScale(M_DEFAULT,2.0,2.0);
//
//	MgraControl(M_DEFAULT, M_BACKGROUND_MODE, M_TRANSPARENT);
//
//	//// Fill
//	MgraColor(M_DEFAULT, M_COLOR_GREEN);
//	_stprintf_s(szText,64,_T("Fill Clearance                    in."));
//	MgraText(M_DEFAULT, nID, xPos, yPos, szText);	
//	yPos+=ySpace;
//	MgraColor(M_DEFAULT, clrTop);
//	MgraLine(M_DEFAULT, nID, x+4, yPos-1,x+SizeX-3,yPos-1);
//
//	// Rim Height
//	MgraColor(M_DEFAULT, M_COLOR_GREEN);
//	_stprintf_s(szText,64,_T("Rim Height                        in."));
//	MgraText(M_DEFAULT, nID, xPos, yPos, szText);	
//	yPos+=ySpace;
//	MgraColor(M_DEFAULT, clrTop);
//	MgraLine(M_DEFAULT, nID, x+4, yPos-1,x+SizeX-3,yPos-1);
//
//	// Model Search Time
//	MgraColor(M_DEFAULT, M_COLOR_GREEN);
//	_stprintf_s(szText,64,_T("Raw Height                        in."));
//	MgraText(M_DEFAULT, nID, xPos, yPos, szText);	
//	yPos+=ySpace;
//	MgraColor(M_DEFAULT, clrTop);
//	MgraLine(M_DEFAULT, nID, x+4, yPos-1,x+SizeX-3,yPos-1);
//
//	// Volume
//	MgraColor(M_DEFAULT, M_COLOR_GREEN);
//	_stprintf_s(szText,64,_T("Volume                             CC"));
//	MgraText(M_DEFAULT, nID, xPos, yPos, szText);	
//	yPos+=ySpace;
//	MgraColor(M_DEFAULT, clrTop);
//	MgraLine(M_DEFAULT, nID, x+4, yPos-1,x+SizeX-3,yPos-1);
//
//	// Blob Area
//	MgraColor(M_DEFAULT, M_COLOR_GREEN);
//	_stprintf_s(szText,64,_T("Total Blob Area                 Pixel"));
//	MgraText(M_DEFAULT, nID, xPos, yPos, szText);	
//	yPos+=ySpace;
//	MgraColor(M_DEFAULT, clrTop);
//	MgraLine(M_DEFAULT, nID, x+4, yPos-1,x+SizeX-3,yPos-1);
//
//	// Blob Count
//	MgraColor(M_DEFAULT, M_COLOR_GREEN);
//	_stprintf_s(szText,64,_T("Max Blob Area                   Pixel"));
//	MgraText(M_DEFAULT, nID, xPos, yPos, szText);	
//	yPos+=ySpace;
//	MgraColor(M_DEFAULT, clrTop);
//	MgraLine(M_DEFAULT, nID, x+4, yPos-1,x+SizeX-3,yPos-1);
//
//	// Total inspected
//	MgraColor(M_DEFAULT, M_COLOR_GREEN);
//	_stprintf_s(szText,64,_T("Total Inspected                         "));
//	MgraText(M_DEFAULT, nID, xPos, yPos, szText);	
//	yPos+=ySpace;
//	MgraColor(M_DEFAULT, clrTop);
//	MgraLine(M_DEFAULT, nID, x+4, yPos-1,x+SizeX-3,yPos-1);
//
//	// Rim
//	MgraColor(M_DEFAULT, M_COLOR_GREEN);
//	_stprintf_s(szText,64,_T("Pass Percent                       %%"));
//	MgraText(M_DEFAULT, nID, xPos, yPos, szText);	
//	yPos+=ySpace;
//	MgraColor(M_DEFAULT, clrTop);
//	MgraLine(M_DEFAULT, nID, x+4, yPos-1,x+SizeX-3,yPos-1);
//
//	// Vertical line
//	MgraLine(M_DEFAULT, nID, x+RESULTS_POS_X-1, y,x+RESULTS_POS_X-1,yPos);
//
//	MbufFree(ROI);
//
//	MgraColor(M_DEFAULT, clrTop);
//	MgraLine(M_DEFAULT, nID, x, y,x+SizeX,y);
//	MgraLine(M_DEFAULT, nID, x, y+1,x+SizeX,y+1);
//	MgraLine(M_DEFAULT, nID, x, y+2,x+SizeX,y+2);
//
//	MgraColor(M_DEFAULT, cltBottom);
//	MgraLine(M_DEFAULT, nID, x, y+SizeY,x+SizeX,y+SizeY);
//	MgraLine(M_DEFAULT, nID, x, y+SizeY-1,x+SizeX,y+SizeY-1);
//	MgraLine(M_DEFAULT, nID, x, y+SizeY-2,x+SizeX,y+SizeY-2);
//
//	MgraColor(M_DEFAULT, clrTop);
//	MgraLine(M_DEFAULT, nID, x  , y,x,y+SizeY-1);
//	MgraLine(M_DEFAULT, nID, x+1, y,x+1,y+SizeY-2);
//	MgraLine(M_DEFAULT, nID, x+2, y,x+2,y+SizeY-3);
//
//	MgraColor(M_DEFAULT, cltBottom);
//	MgraLine(M_DEFAULT, nID, x+SizeX, y+SizeY,x+SizeX,y+1);
//	MgraLine(M_DEFAULT, nID, x+SizeX-1,y+SizeY,x+SizeX-1,y+2);
//	MgraLine(M_DEFAULT, nID, x+SizeX-2, y+SizeY,x+SizeX-2,y+3);
//
//
//	//MgraColor(M_DEFAULT, M_COLOR_DARK_GREEN);
//	//MgraColor(M_DEFAULT, clrTop);
//
//	// Draw the lines
//	//MgraLine(M_DEFAULT, nID, x+3, y+20,x+SizeX-3,y+20);
//	//MgraLine(M_DEFAULT, nID, xPos, yPos+ySpace*2+1,SizeX,ySpace*2+1);
//	//MgraLine(M_DEFAULT, nID, xPos, yPos+ySpace*3+1,SizeX,ySpace*3+1);
//
//
//}
//
//
//
////======================================================================================================//
//// Function Name: UpdateResultData ()                                                                    //
////                                                                                                      //
////======================================================================================================//
//void UpdateResultData(int x,int y,int SizeX,int SizeY,MIL_ID nID, RESULTDATA* pResults)
//{
//	TCHAR szText[256];
//	int yPos = y;
//	int xPos = x;
//	int ySpace = 18;
//
//	//MIL_ID ROI;
//	//MbufChildColor2d(nID, M_ALL_BANDS, xPos, yPos, SizeX,SizeY, &ROI);
//	//MbufClear(ROI,0);
//	//MbufFree(ROI);
//
//	MgraColor(M_DEFAULT, M_COLOR_CYAN);
//	xPos += 2;
//
//	MgraFontScale(M_DEFAULT,1.0,1.0);
//	MgraControl(M_DEFAULT, M_BACKGROUND_MODE, M_OPAQUE);
//
//	// 
//	_stprintf_s(szText,64,_T("%6.3f"),pResults->FillSetting);
//	MgraText(M_DEFAULT, nID, xPos, yPos, szText);	
//	yPos+=ySpace;
//
//	// 
//	_stprintf_s(szText,64,_T("%6.1f"),pResults->LocateLaserTime);
//	MgraText(M_DEFAULT, nID, xPos, yPos, szText);	
//	yPos+=ySpace;
//
//	_stprintf_s(szText,64,_T("%6.1f"),pResults->ExtractTime);
//	MgraText(M_DEFAULT, nID, xPos, yPos, szText);	
//	yPos+=ySpace;
//
//	_stprintf_s(szText,64,_T("%6.1f"),pResults->AlignTime);
//	MgraText(M_DEFAULT, nID, xPos, yPos, szText);	
//	yPos+=ySpace;
//
//	_stprintf_s(szText,64,_T("%6.1f"),pResults->TotalModelSearchTime);
//	MgraText(M_DEFAULT, nID, xPos, yPos, szText);	
//	yPos+=ySpace;
//
//	_stprintf_s(szText,64,_T("%6.1f"),pResults->TotalProcessingTime);
//	MgraText(M_DEFAULT, nID, xPos, yPos, szText);	
//	yPos+=ySpace;
//
//	_stprintf_s(szText,64,_T("%6.1f"),pResults->MaxTotalProcessingTime);
//	MgraText(M_DEFAULT, nID, xPos, yPos, szText);	
//	yPos+=ySpace;
//
//	_stprintf_s(szText,64,_T("%6.3f"),pResults->MinRimHeight);
//	MgraText(M_DEFAULT, nID, xPos, yPos, szText);	
//	yPos+=ySpace;
//
//	_stprintf_s(szText,64,_T("%6.3f"),pResults->MaxRimHeight);
//	MgraText(M_DEFAULT, nID, xPos, yPos, szText);	
//	yPos+=ySpace;
//
//	_stprintf_s(szText,64,_T("%12d"),pResults->SyncCount);
//	MgraText(M_DEFAULT, nID, xPos, yPos, szText);	
//	yPos+=ySpace;
//
//	_stprintf_s(szText,64,_T("%12d"),pResults->TotalInspected);
//	MgraText(M_DEFAULT, nID, xPos, yPos, szText);	
//	yPos+=ySpace;
//
//	
//}
//
////======================================================================================================//
//// Function Name: DrawResult3DRect ()                                                               //
////                                                                                                      //
////======================================================================================================//
//void DrawResult3DRect(int x,int y,int SizeX,int SizeY,MIL_ID nID,MIL_DOUBLE clrTop,MIL_DOUBLE cltBottom)
//{
//	TCHAR szText[256];
//	int yPos = y+4;
//	int xPos = x+4;
//	int ySpace = 18;
//
//	MIL_ID ROI;
//	MbufChildColor2d(nID, M_ALL_BANDS, x, y, SizeX,SizeY, &ROI);
//	MbufClear(ROI,0);
//
//	MgraFontScale(M_DEFAULT,1.0,1.0);
//	//MgraFontScale(M_DEFAULT,2.0,2.0);
//	MgraControl(M_DEFAULT, M_BACKGROUND_MODE, M_TRANSPARENT);
//
//	// Fill
//	MgraColor(M_DEFAULT, M_COLOR_GREEN);
//	_stprintf_s(szText,64,_T("Fill Setting:                 in."));
//	MgraText(M_DEFAULT, nID, xPos, yPos, szText);	
//	yPos+=ySpace;
//	MgraColor(M_DEFAULT, clrTop);
//	MgraLine(M_DEFAULT, nID, x+4, yPos-1,x+SizeX-3,yPos-1);
//
//	// Laser
//	MgraColor(M_DEFAULT, M_COLOR_GREEN);
//	_stprintf_s(szText,64,_T("Locate Laser Time            msec"));
//	MgraText(M_DEFAULT, nID, xPos, yPos, szText);	
//	yPos+=ySpace;
//	MgraColor(M_DEFAULT, clrTop);
//	MgraLine(M_DEFAULT, nID, x+4, yPos-1,x+SizeX-3,yPos-1);
//
//	// 
//	MgraColor(M_DEFAULT, M_COLOR_GREEN);
//	_stprintf_s(szText,64,_T("Extract Time                 msec"));
//	MgraText(M_DEFAULT, nID, xPos, yPos, szText);	
//	yPos+=ySpace;
//	MgraColor(M_DEFAULT, clrTop);
//	MgraLine(M_DEFAULT, nID, x+4, yPos-1,x+SizeX-3,yPos-1);
//
//	// 
//	MgraColor(M_DEFAULT, M_COLOR_GREEN);
//	_stprintf_s(szText,64,_T("Align Time                   msec"));
//	MgraText(M_DEFAULT, nID, xPos, yPos, szText);	
//	yPos+=ySpace;
//	MgraColor(M_DEFAULT, clrTop);
//	MgraLine(M_DEFAULT, nID, x+4, yPos-1,x+SizeX-3,yPos-1);
//
//	//
//	MgraColor(M_DEFAULT, M_COLOR_GREEN);
//	_stprintf_s(szText,64,_T("Total Search Time            msec"));
//	MgraText(M_DEFAULT, nID, xPos, yPos, szText);	
//	yPos+=ySpace;
//	MgraColor(M_DEFAULT, clrTop);
//	MgraLine(M_DEFAULT, nID, x+4, yPos-1,x+SizeX-3,yPos-1);
//
//	//
//	MgraColor(M_DEFAULT, M_COLOR_GREEN);
//	_stprintf_s(szText,64,_T("Processing Time              msec"));
//	MgraText(M_DEFAULT, nID, xPos, yPos, szText);	
//	yPos+=ySpace;
//	MgraColor(M_DEFAULT, clrTop);
//	MgraLine(M_DEFAULT, nID, x+4, yPos-1,x+SizeX-3,yPos-1);
//
//	// Max
//	MgraColor(M_DEFAULT, M_COLOR_GREEN);
//	_stprintf_s(szText,64,_T("Max Proc Time                msec"));
//	MgraText(M_DEFAULT, nID, xPos, yPos, szText);	
//	yPos+=ySpace;
//	MgraColor(M_DEFAULT, clrTop);
//	MgraLine(M_DEFAULT, nID, x+4, yPos-1,x+SizeX-3,yPos-1);
//
//	// Min Rim
//	MgraColor(M_DEFAULT, M_COLOR_GREEN);
//	_stprintf_s(szText,64,_T("Min Rim:                      in."));
//	MgraText(M_DEFAULT, nID, xPos, yPos, szText);	
//	yPos+=ySpace;
//	MgraColor(M_DEFAULT, clrTop);
//	MgraLine(M_DEFAULT, nID, x+4, yPos-1,x+SizeX-3,yPos-1);
//
//	// Max Rim
//	MgraColor(M_DEFAULT, M_COLOR_GREEN);
//	_stprintf_s(szText,64,_T("Max Rim:                      in."));
//	MgraText(M_DEFAULT, nID, xPos, yPos, szText);	
//	yPos+=ySpace;
//	MgraColor(M_DEFAULT, clrTop);
//	MgraLine(M_DEFAULT, nID, x+4, yPos-1,x+SizeX-3,yPos-1);
//
//	// Count
//	MgraColor(M_DEFAULT, M_COLOR_GREEN);
//	_stprintf_s(szText,64,_T("Sync Count:"));
//	MgraText(M_DEFAULT, nID, xPos, yPos, szText);	
//	yPos+=ySpace;
//	MgraColor(M_DEFAULT, clrTop);
//	MgraLine(M_DEFAULT, nID, x+4, yPos-1,x+SizeX-3,yPos-1);
//
//	// Count
//	MgraColor(M_DEFAULT, M_COLOR_GREEN);
//	_stprintf_s(szText,64,_T("Trigger Count:"));
//	MgraText(M_DEFAULT, nID, xPos, yPos, szText);	
//	yPos+=ySpace;
//	MgraColor(M_DEFAULT, clrTop);
//	//MgraLine(M_DEFAULT, nID, x+4, yPos-1,x+SizeX-3,yPos-1);
//
//	// Vertical line
//	MgraLine(M_DEFAULT, nID, x+RESULTS_POS_X-1, y,x+RESULTS_POS_X-1,yPos);
//
//	MbufFree(ROI);
//
//
//	MgraColor(M_DEFAULT, clrTop);
//	MgraLine(M_DEFAULT, nID, x, y,x+SizeX,y);
//	MgraLine(M_DEFAULT, nID, x, y+1,x+SizeX,y+1);
//	MgraLine(M_DEFAULT, nID, x, y+2,x+SizeX,y+2);
//
//	MgraColor(M_DEFAULT, cltBottom);
//	MgraLine(M_DEFAULT, nID, x, y+SizeY,x+SizeX,y+SizeY);
//	MgraLine(M_DEFAULT, nID, x, y+SizeY-1,x+SizeX,y+SizeY-1);
//	MgraLine(M_DEFAULT, nID, x, y+SizeY-2,x+SizeX,y+SizeY-2);
//
//	MgraColor(M_DEFAULT, clrTop);
//	MgraLine(M_DEFAULT, nID, x  , y,x,y+SizeY-1);
//	MgraLine(M_DEFAULT, nID, x+1, y,x+1,y+SizeY-2);
//	MgraLine(M_DEFAULT, nID, x+2, y,x+2,y+SizeY-3);
//
//	MgraColor(M_DEFAULT, cltBottom);
//	MgraLine(M_DEFAULT, nID, x+SizeX, y+SizeY,x+SizeX,y+1);
//	MgraLine(M_DEFAULT, nID, x+SizeX-1,y+SizeY,x+SizeX-1,y+2);
//	MgraLine(M_DEFAULT, nID, x+SizeX-2, y+SizeY,x+SizeX-2,y+3);
//
//
//}
//
//
////======================================================================================================//
//// Function Name: Draw3DLabel ()                                                               //
////                                                                                                      //
////======================================================================================================//
//void Draw3DLabel(int x,int y,int SizeX,int SizeY,LPCTSTR lpName,MIL_ID nID)
//{
//	TCHAR szText[256];
//	int yPos = y;
//	int xPos = x+4;
//	int ySpace = 18;
//
//	MIL_ID ROI;
//	MbufChildColor2d(nID, M_ALL_BANDS, x, y, SizeX,SizeY, &ROI);
//	MbufClear(ROI,M_COLOR_GRAY);
//	MbufFree(ROI);
//
//	MgraFontScale(M_DEFAULT,2.0,2.0);
//	MgraControl(M_DEFAULT, M_BACKGROUND_MODE, M_TRANSPARENT);
//
//	// Lable
//	MgraColor(M_DEFAULT, M_COLOR_WHITE);
//	//_stprintf_s(szText,64,_T("Title"));
//	_stprintf_s(szText,64,lpName);
//	MgraText(M_DEFAULT, nID, xPos, yPos, szText);	
//
//
//	MgraColor(M_DEFAULT, M_COLOR_WHITE);
//	MgraLine(M_DEFAULT, nID, x, y,x+SizeX,y);
//	MgraLine(M_DEFAULT, nID, x, y+1,x+SizeX,y+1);
//	MgraLine(M_DEFAULT, nID, x, y+2,x+SizeX,y+2);
//
//	MgraColor(M_DEFAULT, M_COLOR_LIGHT_GRAY);
//	MgraLine(M_DEFAULT, nID, x, y+SizeY,x+SizeX,y+SizeY);
//	MgraLine(M_DEFAULT, nID, x, y+SizeY-1,x+SizeX,y+SizeY-1);
//	MgraLine(M_DEFAULT, nID, x, y+SizeY-2,x+SizeX,y+SizeY-2);
//
//	MgraColor(M_DEFAULT, M_COLOR_WHITE);
//	MgraLine(M_DEFAULT, nID, x  , y,x,y+SizeY-1);
//	MgraLine(M_DEFAULT, nID, x+1, y,x+1,y+SizeY-2);
//	MgraLine(M_DEFAULT, nID, x+2, y,x+2,y+SizeY-3);
//
//	MgraColor(M_DEFAULT, M_COLOR_LIGHT_GRAY);
//	MgraLine(M_DEFAULT, nID, x+SizeX, y+SizeY,x+SizeX,y+1);
//	MgraLine(M_DEFAULT, nID, x+SizeX-1,y+SizeY,x+SizeX-1,y+2);
//	MgraLine(M_DEFAULT, nID, x+SizeX-2, y+SizeY,x+SizeX-2,y+3);
//
//
//}
//
////======================================================================================================//
//// Function Name: Draw3DResultRect ()                                                               //
////                                                                                                      //
////======================================================================================================//
//void Draw3DResultRect(int x,int y,int SizeX,int SizeY,MIL_ID nID,MIL_DOUBLE clrTop,MIL_DOUBLE cltBottom)
//{
//	//TCHAR szText[256];
//	int yPos = y+4;
//	int xPos = x+4;
//	int ySpace = 18;
//
//	MIL_ID ROI;
//	MbufChildColor2d(nID, M_ALL_BANDS, x, y, SizeX,SizeY, &ROI);
//	MbufClear(ROI,0);
//
//	MgraFontScale(M_DEFAULT,2.0,2.0);
//	MgraControl(M_DEFAULT, M_BACKGROUND_MODE, M_TRANSPARENT);
//	MbufFree(ROI);
//
//
//	MgraColor(M_DEFAULT, clrTop);
//	MgraLine(M_DEFAULT, nID, x, y,x+SizeX,y);
//	MgraLine(M_DEFAULT, nID, x, y+1,x+SizeX,y+1);
//	MgraLine(M_DEFAULT, nID, x, y+2,x+SizeX,y+2);
//
//	MgraColor(M_DEFAULT, cltBottom);
//	MgraLine(M_DEFAULT, nID, x, y+SizeY,x+SizeX,y+SizeY);
//	MgraLine(M_DEFAULT, nID, x, y+SizeY-1,x+SizeX,y+SizeY-1);
//	MgraLine(M_DEFAULT, nID, x, y+SizeY-2,x+SizeX,y+SizeY-2);
//
//	MgraColor(M_DEFAULT, clrTop);
//	MgraLine(M_DEFAULT, nID, x  , y,x,y+SizeY-1);
//	MgraLine(M_DEFAULT, nID, x+1, y,x+1,y+SizeY-2);
//	MgraLine(M_DEFAULT, nID, x+2, y,x+2,y+SizeY-3);
//
//	MgraColor(M_DEFAULT, cltBottom);
//	MgraLine(M_DEFAULT, nID, x+SizeX, y+SizeY,x+SizeX,y+1);
//	MgraLine(M_DEFAULT, nID, x+SizeX-1,y+SizeY,x+SizeX-1,y+2);
//	MgraLine(M_DEFAULT, nID, x+SizeX-2, y+SizeY,x+SizeX-2,y+3);
//
//
//}
//
////======================================================================================================//
//// Function Name: DrawDouble ()                                                                    //
////                                                                                                      //
////======================================================================================================//
//void DrawDouble(int x,int y,int SizeX,int SizeY,MIL_ID nID, double dbValue)
//{
//	TCHAR szText[256];
//	int yPos = y;
//	int xPos = x;
//
//	MIL_ID ROI;
//	MbufChildColor2d(nID, M_ALL_BANDS, xPos, yPos, SizeX,SizeY, &ROI);
//	MbufClear(ROI,0);
//	MbufFree(ROI);
//	MgraColor(M_DEFAULT,M_COLOR_CYAN);//M_COLOR_WHITE
//	xPos += 2;
//
//	MgraFontScale(M_DEFAULT,2.0,2.0);
//	MgraControl(M_DEFAULT, M_BACKGROUND_MODE, M_OPAQUE);
//	_stprintf_s(szText,64,_T("%4.3f"),dbValue);
//	MgraText(M_DEFAULT, nID, xPos, yPos, szText);	
//
//}
//
//
////======================================================================================================//
//// Function Name: UpdateLanePassFail ()                                                                    //
////                                                                                                      //
////======================================================================================================//
//void UpdateLanePassFail(int x,int y,MIL_ID nID, LANERESULTDATA* pResults)
//{
//	TCHAR szText[256];
//	int yPos = y;
//	int xPos = x;
//	int ySpace = 25;
//
//	MgraFontScale(M_DEFAULT,1.25,1.25);
//	MgraControl(M_DEFAULT, M_BACKGROUND_MODE, M_OPAQUE);
//
//	// No Tray
//	if (pResults->LaneStatus == TRAY_NO_TRAY)
//	{
//		MgraColor(M_DEFAULT,M_COLOR_RED);
//		_stprintf_s(szText,256,_T("               "));
//		MgraText(M_DEFAULT, nID, xPos, yPos, szText);	
//		yPos+=ySpace;	
//		MgraText(M_DEFAULT, nID, xPos, yPos, szText);	
//		yPos+=ySpace;	
//		MgraText(M_DEFAULT, nID, xPos, yPos, szText);	
//		yPos+=ySpace;	
//		MgraText(M_DEFAULT, nID, xPos, yPos, szText);	
//		yPos+=ySpace;	
//		return;
//	}
//
//	// Fill
//	switch (pResults->FillClearanceStatus)
//	{
//	case STATUS_PASS:
//		MgraColor(M_DEFAULT,M_COLOR_GREEN);
//		_stprintf_s(szText,256,_T("FILL:      PASS"));
//		break;
//	case STATUS_FAIL:
//		MgraColor(M_DEFAULT,M_COLOR_RED);
//		_stprintf_s(szText,256,_T("FILL:      FAIL"));
//		break;
//	case STATUS_OFF:
//		MgraColor(M_DEFAULT,M_COLOR_WHITE);
//		_stprintf_s(szText,256,_T("FILL:      OFF "));
//		break;	
//	}
//	MgraText(M_DEFAULT, nID, xPos, yPos, szText);	
//	yPos+=ySpace;	
//
//	// Total Blob area
//	if (pResults->PassTotalBlobArea)
//	{
//		MgraColor(M_DEFAULT,M_COLOR_GREEN);
//		_stprintf_s(szText,256,_T("TOTAL AREA:PASS"));
//	}
//	else
//	{
//		MgraColor(M_DEFAULT,M_COLOR_RED);
//		_stprintf_s(szText,256,_T("TOTAL AREA:FAIL"));
//	}
//	MgraText(M_DEFAULT, nID, xPos, yPos, szText);	
//	yPos+=ySpace;	
//
//	// Max Blob area
//	if (pResults->PassMaxBlobArea)
//	{
//		MgraColor(M_DEFAULT,M_COLOR_GREEN);
//		_stprintf_s(szText,256,_T("MAX AREA:  PASS"));
//	}
//	else
//	{
//		MgraColor(M_DEFAULT,M_COLOR_RED);
//		_stprintf_s(szText,256,_T("MAX AREA:  FAIL"));
//	}
//	MgraText(M_DEFAULT, nID, xPos, yPos, szText);	
//	yPos+=ySpace;	
//
//	// Crossed seal
//	switch (pResults->SealCrossedStatus)
//	{
//	case STATUS_PASS:
//		MgraColor(M_DEFAULT,M_COLOR_GREEN);
//		_stprintf_s(szText,256,_T("X-SEAL:    PASS"));
//		break;
//	case STATUS_FAIL:
//		MgraColor(M_DEFAULT,M_COLOR_RED);
//		_stprintf_s(szText,256,_T("X-SEAL:    FAIL"));
//		break;
//	case STATUS_OFF:
//		MgraColor(M_DEFAULT,M_COLOR_WHITE);
//		_stprintf_s(szText,256,_T("X-SEAL:    OFF "));
//		break;	
//	}
//	MgraText(M_DEFAULT, nID, xPos, yPos, szText);	
//	yPos+=ySpace;	
//}

//======================================================================================================//
// Function Name: DrawFatLine ()                                                               //
//                                                                                                      //
//======================================================================================================//
void DrawFatLine(int x,int y,int XEnd,int YEnd,MIL_ID nID)
{
	MgraColor(M_DEFAULT, M_COLOR_BRIGHT_GRAY);
	MgraLine(M_DEFAULT, nID, x, y,XEnd,YEnd);

	MgraColor(M_DEFAULT, M_COLOR_WHITE);
	MgraLine(M_DEFAULT, nID, x, y+1,XEnd,YEnd+1);

	MgraColor(M_DEFAULT, M_COLOR_WHITE);
	MgraLine(M_DEFAULT, nID, x, y+2,XEnd,YEnd+2);

	MgraColor(M_DEFAULT, M_COLOR_BRIGHT_GRAY);
	MgraLine(M_DEFAULT, nID, x, y+3,XEnd,YEnd+3);

	MgraColor(M_DEFAULT, M_COLOR_BLACK);
	MgraLine(M_DEFAULT, nID, x, y+4,XEnd,YEnd+4);
}
