// HMIDlgApi.h: Defines HMIDlgApi.DLL application interface
// This interface can be included by C or C++ code
//
// This is a part of the Hormel HMI library.
// Copyright (c) Hormel Foods LLC.  All rights reserved.
//
#pragma once

//#include "..\ALP\LIB\EIPCOM.H"
//#include "..\ALP\MIL\INCLUDE\Mil.h"
#include ".\IsiLcdLib\IsiLcdDisplay.h"

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

#define MASTERDATAFILE  _T("D:\\BTCDATA\\BACKUP\\SETTINGS\\SET560432019\\MASTERSETTINGS.BTC")
#define DATAFILE        _T("D:\\BTCDATA\\BTCDATA.BTC")
#define COUNTERFILE     _T("D:\\BTCDATA\\BTCCOUNTERS.BTC")
#define BACKUP_PATH     _T("D:\\BTCDATA\\BACKUP\\SETTINGS\\")
#define BACKUP_FILE     _T("BTCDATABAK.BTC")
#define BACKUP_NAME     _T("SET")
#define BACKUP_EXT      _T(".BTC")


#ifdef    HMI_GLOBALS
#define   HMI_EXT 
#else
#define   HMI_EXT extern
#endif

// Settings messages
#define WM_VISION_SETTINGS_SAVE         WM_USER+0x400
#define WM_VISION_SETTINGS_APPLY        WM_USER+0x401
#define WM_VISION_SETTINGS_CHANGED      WM_USER+0x402
#define WM_VISION_SETTINGS_RESTORE      WM_USER+0x403
#define WM_WAIT_DLG_UPDATE_TIMER        WM_USER+0x404
#define WM_GET_PMAC_VARIABLE            WM_USER+0x405
#define WM_GET_PMAC_MOTOR_POS           WM_USER+0x406
#define WM_BTC_TIMING_CHECK             WM_USER+0x407
#define WM_CLEAR_ALARM                  WM_USER+0x408

#define WM_SETTINGS_LOAD_MASTER         WM_USER+0x40B
#define WM_SETTINGS_LOAD_USER           WM_USER+0x40C
#define WM_SETTINGS_SAVE_USER           WM_USER+0x40D

typedef struct tagHMIOPT {

	BOOL bBoostPriority;
	BOOL bFullReset;
	BOOL bEnableUser;
	BOOL bEnableMaster;
	int nPassword;
	int nMasterPassword;
	int nLaneID;
	TCHAR szLaneName[256];
	char ServerIP[20];
	DWORD dwServerIP;
	int nSpareInts[92];
	int PmacID;
	int nPmacReset;
	double dbDoubels[100];
} HMIOPT;

typedef struct tagALLCOUNTERS {
	int LaneID;
	long TotalSheetCount;
	long SheetCount;
	long SheetCountShift;
	long TotalRunSeconds;
	long LifeTimeRunSeconds;
	long SpareCount4;
	long SpareCount5;
	long SpareCount6;
	long SpareCount7;
	long SpareCount8;
	long SpareCount9;
	long nlInts[100];
	double dbDoubels[100];
} ALLCOUNTERS;

typedef struct tagVISIONSETTINGS1 {
	int     Threshold;
	int     MinBaconSize;
	int     MinBaconWidth;
	int     MinBaconHeight;
	int     MinBlobRadius;
	int     Trigger;
	int     MinBaconRejectSize;
	int     MinBaconRejectWidth;
	int     MinBaconRejectHeight;
	int     SystemEnable;
	int     RejectSuppressionCount;
	int     zznSpareSettings[99];
	int     znSpareArray[1024];
	double  Exposure_uS;
	double  RejectDelay;
	double  RejectDuration;
	//double  zdbSpare3;
	double  dbLineRateScaleFactor;
	double  zdbSpare4;
	double  zdbSpare5;
	double  zdbSpare6;
	double  zdbSpare7;
	double  zdbSpare8;
	double  zdbSpare9;
	double  zdbSpareSettings[100];
	double  zdbSpareArray[1024];
} VISIONSETTINGS1;

typedef struct tagVISIONSETTINGS2 {
	int     x[5];
	int     y[5];
	int NominalLaserWidth;
	int LaserWidthDelta;
	int MinLaserIntensity;
	int MinBaconSize;
	int MaxBaconBlobs;
	int EndDetectLockCount;
	int GapDetectCount;
	int MaxGapFillX;
	int MaxGapFillY;
	int MinPosY;
	int ROIOffsetY;	
	int Exposure_uS;
	int TriggerOn;
	int EndDetectEnable;
	int GapDetectLatchCount;
	int znSpareSettings[70];
	int     PosLane1;
	int     PosLane2;
	int     PosLane3;
	int     PosLane4;
	int     PosLane5;
	int     PosLane6;
	int     PosLane7;
	int     OffsetLane1;
	int     OffsetLane2;
	int     OffsetLane3;
	int     OffsetLane4;
	int     OffsetLane5;
	int     OffsetLane6;
	int     OffsetLane7;
	int     OffsetLane8;
	int     znSpareArray[1024];
	double  zdbSpare0;
	double  zdbSpare1;
	double  zdbSpare2;
	double  zdbSpare3;
	double  zdbSpare4;
	double  zdbSpare5;
	double  zdbSpare6;
	double  zdbSpare7;
	double  zdbSpare8;
	double  zdbSpare9;
	double  zdbSpareSettings[100];
	double  zdbSpareArray[1024];
} VISIONSETTINGS2;

typedef struct tagVISIONSETTINGS3 {
	int     zzX0;
	int     zzX1;
	int     zzY0;
	int     zzY1;
	int     zztold;
	int     zMinBaconSize;
	int     zMinBaconWidth;
	int     zMinBaconHeight;
	int     ImageCenter;
	int     CameraDirection;
	int     znSpareSettings[100];
	int     znSpareArray[1024];
	double  MotorPosY0;
	double  MotorPosY1;
	double  ImagePosX0;
	double  ImagePosX1;
	double  dbAlignOffset;
	double  ImagePosX2;
	double  MotorPosY2;
	double  Pitch;
	double  zdbSpare8;
	double  zdbSpare9;
	double  zdbSpareSettings[100];
	double  zdbSpareArray[1024];
} VISIONSETTINGS3;

typedef struct tagVISIONSETTINGS4 {
	int     TrimModeEnable;
	int     zzX1;
	int     zzY0;
	int     zzY1;
	int     zztold;
	int     zMinBaconSize;
	int     zMinBaconWidth;
	int     zMinBaconHeight;
	int     zSpare8;
	int     zSpare9;
	int     znSpareSettings[100];
	int     znSpareArray[1024];
	double  MotorPosY0;
	double  MotorPosY1;
	double  ImagePosX0;
	double  ImagePosX1;
	double  dbTrimLength;
	double  zdbSpare5;
	double  zdbSpare6;
	double  zdbSpare7;
	double  zdbSpare8;
	double  zdbSpare9;
	double  zdbSpareSettings[100];
	double  zdbSpareArray[1024];
} VISIONSETTINGS4;

typedef struct tagMOTIONSETTINGS {
	int     Spare0;
	int     Spare1;
	int     Spare2;
	int     Spare3;
	int     Spare4;
	int     Spare5;
	int     Spare6;
	int     Spare7;
	int     Spare8;
	int     Spare9;
	int     nSpareSettings[100];
	int     nSpareArray[1024];
	double  dbSpare0;
	double  dbSpare1;
	double  dbSpare2;
	double  dbSpare3;
	double  dbSpare4;
	double  dbSpare5;
	double  dbSpare6;
	double  dbSpare7;
	double  dbSpare8;
	double  dbSpare9;
	double  dbSpareSettings[100];
	double  dbPvars[1024];
} MOTIONSETTINGS;

typedef struct tagALLSETTINGS {
	HMIOPT         HMISettings;
	VISIONSETTINGS1 VisSettings1;
	VISIONSETTINGS2 VisSettings2;
	VISIONSETTINGS3 VisSettings3;
	VISIONSETTINGS4 VisSettings4;
	MOTIONSETTINGS MotionSettings1;
	MOTIONSETTINGS MotionSettings2;
	MOTIONSETTINGS MotionSettings3;
	MOTIONSETTINGS MotionSettings4;
	MOTIONSETTINGS MotionSettings5;
	int     Spare0;
	int     Spare1;
	int     Spare2;
	int     Spare3;
	int     Spare4;
	int     Spare5;
	int     Spare6;
	int     Spare7;
	int     Spare8;
	int     Spare9;
	int     nSpareSettings[1024];
	double dbSpare0;
	double dbSpare1;
	double dbSpare2;
	double dbSpare3;
	double dbSpare4;
	double dbSpare5;
	double dbSpare6;
	double dbSpare7;
	double dbSpare8;
	double dbSpare9;
	double dbSpareSettings[1024];
} ALLSETTINGS;

typedef struct tagKEYPADDATA {
	double dbValue;
	double dbIncrement;
	int nDecimalPlaces;
	double dbMin;
	double dbMax;
	bool bPassWord;
	LPCTSTR lpTitle;
} KEYPADDATA;

#if 0

typedef struct tagSTATUSTEXT {
	CString strText;
	COLORREF clrText;
	COLORREF clrTextBk;
} STATUSTEXT;



#endif

BOOL WINAPI YesNoDlg(LPCTSTR lpMsg=NULL);
CIsiLcdDisplay* WINAPI CreateIsLCDWnd(CWnd* pParentWnd,const CRect& rect,int NumDig);
bool LoadMasterAppSettingFile (ALLSETTINGS* pData);
bool LoadAppSettingFile (ALLSETTINGS* pData);
bool SaveAppSettingFile (ALLSETTINGS* pData);
bool WINAPI OkDlg(LPCTSTR lpMsg=NULL,bool bXOk=false);
bool WINAPI GetHMIOptDlg(HMIOPT* lpData);
bool LoadAppCounterFile (ALLCOUNTERS* pData);
bool SaveAppCounterFile (ALLCOUNTERS* pData);
bool WINAPI GetNumDlg(KEYPADDATA* lpData);

CWnd* WINAPI DlgWait(int Timer);
CWnd* WINAPI DlgUserSettings(ALLSETTINGS* pData,CWnd* pWndParent,CWnd** ppBackPtr);
CWnd* WINAPI DlgSettings(ALLSETTINGS* pData,CWnd* pWndParent,CWnd** ppBackPtr);
CWnd* WINAPI DlgMotionSettings(MOTIONSETTINGS* pData,CWnd* pWndParent,CWnd** ppBackPtr);
CWinThread* WINAPI DoSplash(CWinApp* pApp,int nTime,bool* pbSplash);


//bool WINAPI DoCalDlg(CWnd* pWndParent,bool bRun,bool* pbContinue);
//int WINAPI SetPageDataPointer(int nPage,void* pdata);
//bool LoadBackUpAppSettingFile (int nID,ALLSETTINGS* pData);
//bool SaveBackUpUpAppSettingFile (int nID,ALLSETTINGS* pData);
//int WINAPI PlaneSelectDlg();
//CWnd* WINAPI MsgDlg(LPCTSTR lpMsg,int Time);



//// GDIsLCDCtrl.h : Declaration of the CGDIsLCDCtrl ActiveX Control class.
//class CParentWindow : public CWnd
//{
//public:
//	BOOL m_bInit;
//    CParentWindow ();
//	CParentWindow (CWnd* pWndParent,CWnd* pWnd);
//	virtual ~CParentWindow();
//	void Init();
//	//CIsiLcdDisplay m_ledTime2;
//
//protected:
//    afx_msg void OnPaint ();
//    DECLARE_MESSAGE_MAP ()
//public:
//	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
//	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
//	virtual void PostNcDestroy();
//};

#ifdef __cplusplus
}
#endif
