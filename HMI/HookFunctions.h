#pragma once
#include <mil.h>
//#include <afxmt.h>
//#include "..\HMIDlg\HMIDlgApi.h"
//#include "DisplayUtil.h"
//#include "Blob.h"
//#include "MilWnd.h"
//#include "History.h"

/* Auxiliary I/O change callback structure. */
//typedef struct _IOHOOK_PARAM 
//{
//   MIL_ID MilSystem;
//   MIL_ID CmdListId;
//   MIL_INT64 Operation;
//   MIL_DOUBLE Delay;
//} IOHOOK_PARAM, *PIOHOOK_PARAM;

MIL_INT MFTYPE CamPresentFunction(MIL_INT HookType, MIL_ID HookId, void* HookDataPtr);
MIL_INT MFTYPE DisplayErrorExt(MIL_INT HookType, MIL_ID EventId, void* UserDataPtr);
MIL_INT MFTYPE GrabHookHandlerCount(MIL_INT HookType, MIL_ID EventId, void* UserDataPtr);
MIL_INT MFTYPE IoHookFunction(MIL_INT HookType, MIL_ID EventId, void *UserDataPtr);
MIL_INT MFTYPE GrabHookHandlerEndDetect(MIL_INT HookType, MIL_ID EventId, void* UserDataPtr);

