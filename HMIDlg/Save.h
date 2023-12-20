//======================================================================
// Header file
//
// Written for the ALP machine
// Copyright (C) 2014 Bill Young
//================================================================
#pragma once
#include "HMIDlgApi.h"

#ifdef    SAVE_GLOBALS
#define   SAVE_EXT 
#else
#define   SAVE_EXT extern
#endif


// Default settings
#define MAX_LINE_WIDTH1             8      // Max LASER line width

bool LoadMasterDataFile (ALLSETTINGS* pData);
bool LoadDataFile (ALLSETTINGS* pData);
bool SaveDataFile (ALLSETTINGS* pData); 
bool LoadBackUpDataFile (int nID,ALLSETTINGS* pData);
bool SaveBackUpDataFile (int nID,ALLSETTINGS* pData);
bool LoadCounterFile (ALLCOUNTERS* pData);
bool SaveCounterFile (ALLCOUNTERS* pData); 
