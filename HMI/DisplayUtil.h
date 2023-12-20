//======================================================================
// Header file
//
// Written for the SHAKA Vision system.
// Copyright (C) 2015 Bill Young
//================================================================
#pragma once

#ifdef    DISPLAY_GLOBALS
#define   DISPLAY_EXT 
#else
#define   DISPLAY_EXT extern
#endif

#include <mil.h>
//#include "ALPMil.h"

#define TITLE_COLOR                M_RGB888(40,144,155)
#define TEXT_COLOR                 M_RGB888(0,255,255)
#define TEXT_BACK_COLOR            M_RGB888(0,0,0)
#define LABEL_TEXT_COLOR           M_RGB888(255,255,255)

typedef struct tagIMAGEDATA
{
	int             FrameCount;
	double          Period;
	double          PeriodMax;
	double          PeriodMin;
	double          MaxProc;
} IMAGEDATA;

void UpdateImageData(MIL_ID nID, IMAGEDATA* pData);
void UpdateImageDataSteer(MIL_ID nID, IMAGEDATA* pData);
void DrawImageLabels(MIL_ID nID, LPCTSTR lpName);
void DrawImageLabelsSteer(MIL_ID nID, LPCTSTR lpName);
void DrawSteeringImageLabels(int x,int y, MIL_ID nID);
void DrawSteeringPosition(int x,int y, float Pos,MIL_ID nID);
void DrawBlobCount(int x,int y,long Count,MIL_ID nID);