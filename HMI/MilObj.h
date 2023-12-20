#pragma once

#include <mil.h>
#include <afxmt.h>
#include "..\HMIDlg\HMIDlgApi.h"
#include "DisplayUtil.h"
#include "Blob.h"
#include "MilWnd.h"
#include "History.h"
#include "Pmac.h"
#include "HookFunctions.h"

#include <queue>
using namespace std;

#define HISTORY_PATH      _T("D:\\BTCDATA\\HISTORY\\ERRORS.TXT")

// Camera IP address
#define END_CAMERA_IP     MIL_TEXT("169.254.254.1")
#define STEER_CAMERA_IP   MIL_TEXT("169.254.254.2")

#define END_BACON_BAD             M_USER_BIT_STATE+M_USER_BIT0
#define END_BACON_GOOD            M_USER_BIT_STATE+M_USER_BIT1
//#define TIME_BACON_BAD            M_USER_BIT_STATE+M_USER_BIT2


// Reject lane positions
#define POS_LANE1		128
#define POS_LANE2		256
#define POS_LANE3		384
#define POS_LANE4		512
#define POS_LANE5		640
#define POS_LANE6		768
#define POS_LANE7		896

// Reject offsets
#define OFFSET_LANE1	300
#define OFFSET_LANE2	300
#define OFFSET_LANE3	300
#define OFFSET_LANE4	300
#define OFFSET_LANE5	300
#define OFFSET_LANE6	300
#define OFFSET_LANE7	300
#define OFFSET_LANE8	300

// Display size constants
#define BACON_PULSE_TIME          0.01
#define IMAGE_SIZE_X              1024
#define IMAGE_SIZE_Y               470
#define IMAGE2_SIZE_X              512
#define IMAGE2_SIZE_Y              147

#define REJ_IMAGE_SIZE_X           640
#define REJ_IMAGE_SIZE_Y           114
#define REJ_IMAGE2_SIZE_X          514
#define REJ_IMAGE2_SIZE_Y           94 

#define GRAB_LIST_SIZE              16
#define GRAB_LIST_SIZE2              4
#define MAX_MIL_ERRORS             256
#define PULSE_WIDTH_5MSEC      5000000   // 5 ms
#define PULSE_WIDTH_10MSEC    10000000   // 10 ms
#define PULSE_WIDTH_50MSEC    50000000   // 50 ms

#define TOTAL_SBAR_POINTS          640
#define NB_FIXED_POINT             0
#define MAX_PEAKS                  1
#define HMI_SORT_CRITERION         M_PEAK_POSITION+M_SORT_DOWN  //M_PEAK_INTENSITY+M_SORT_DOWN //M_PEAK_POSITION+M_SORT_UP
//#define END_DETECT_START_X         80
//#define END_DETECT_MIN_Y           35
#define END_RECORD                 10
#define MAX_RECORD                240
// Camera present processing function hook data structure. 
typedef struct
{
   MIL_ID MilSystem;
   MIL_INT NbCameras;
   CEvent  CameraPresentEvent;
   //DigHookDataStruct* DigHookDataStrutPtr;
   //bool PrintAdapterInfo;
   //MIL_TEXT_CHAR Adapters[MAX_ADAPTERS][MAX_ADAPTER_DESCRIPTION_LENGTH + 4];
   //MIL_INT BoardType;
} CameraPresentHookDataStruct;

// BTC COM DATA
typedef union tagREADCOMDATA
{
	_int32 Registers[16];
	struct {
		_int32 HeartBeat;
		struct {
			USHORT VfdReady : 1;
			USHORT VfdFaulted : 1;
			USHORT VfdRunning : 1;
			USHORT VfdAtSpeed : 1;
			USHORT Pad1       : 4;
			USHORT Pad2       : 8;
			USHORT Pad3       : 8;
		};
		_int32 FaultCode;
		_int32 Current;
	};

} READCOMDATA;

typedef union tagWRITECOMDATA
{
	_int32 Registers[16];
	struct {
		_int32 HeartBeat;
		struct {
			USHORT VfdRun : 1;
			USHORT VfdReset : 1;
			USHORT Bit2 : 1;
			USHORT Bit3 : 1;
			USHORT Pad1       : 4;
			USHORT Pad2       : 8;
			USHORT Pad3       : 8;
		};
		_int32 VfdSpeedInPerSec;
	};
} WRITECOMDATA;

// User's processing function hook data structure. 
typedef struct tagCOUNTHOOKDATASTRUCT1
{
	bool            StopDigitizer;
	//bool            FirstImage;
	bool*           pRunning;
	int             nID;
	MIL_ID*         GrabImage;
    int             ImageCount;
    int             SuppressionCount;
    CEvent          GrabEvent;
	MIL_ID          nModifyedBuffID;
	MIL_ID			MilRawImage;               /* MIL Image buffer identifier.               */
	MIL_ID			MilRawImageTop;            /* MIL Image buffer identifier.               */
	MIL_ID			MilRawImageBot;            /* MIL Image buffer identifier.               */
	MIL_ID			MilBinImage;               /* MIL Image buffer identifier.               */
	MIL_ID			MilBinImageTop;            /* MIL Image buffer identifier.               */
	MIL_ID			MilBinImageBot;            /* MIL Image buffer identifier.               */
	MIL_ID			MilBinImageBotSeperation;  /* MIL Image buffer identifier.               */
	MIL_ID          MilWorkImage;
	MIL_ID          MilWorkImage2;
	MIL_ID          MilRejectBlobImage;
	MIL_ID          MilDigitizer;
	MIL_ID          MilImage;
	MIL_ID          MilImage2;
	double          BaconSpeed;
	double          dbTimePrev;
	double          Period;
	double          PeriodMax;
	double          PeriodMin;
	double          MaxProcTime;
	double          ComTime;
	double          MaxComTime;
	double          MaxComPeriod;
	double          MaxTimeStampRes;
	long            TotalRejectCount;
	long            LatchDiff;
	int             DisplaySelect;
	bool            MainPage;
	long            TotalBlobCount;
	int             Position;
	long            LockSize;
	CBlob*          pBlob;
	ALLSETTINGS*    pSettings;
	bool            PmacComComplete;
	unsigned _int16 BaconBuff[PMAC_SEND_SIZE/2];
	//bool            SteerTriggerOn;
	bool            EndDetected;
	bool            EndDetectedLatch;
	queue <int>     QueueBacon;
	int             QueueSize;
	CCriticalSection CritSect;
	//MIL_INT64       LastChunkData;
	MIL_INT64       LastReferenceStamp;
	MIL_ID          CmdListId;
	MIL_DOUBLE      AcquisitionLineRateAbsInHz;
	MIL_INT         ImageSizeY;
	MIL_ID          MilSystem;
	bool            IoFunctionHooked;
	bool            StartQue;
	int             StartQueCount;
} COUNTHOOKDATASTRUCT1;

// User's processing function hook data structure. 
typedef struct tagCOUNTHOOKDATASTRUCT2
{
	int             nID;
	MIL_ID  MilImage;               /* MIL Image buffer identifier.               */
	MIL_ID  MilImage2;              /* MIL Image buffer identifier.               */
	MIL_ID  Context;
	MIL_ID  LocatePeak;
	MIL_ID  MilBaconBlobImage;
	MIL_ID  MilImageRejectWork;
	MIL_ID  MilImageRejectWork2;
	MIL_ID  MilImageRejectWorkRedBand;
	MIL_ID  MilImageRejectWorkGreenBand;
	MIL_ID  MilImageRejectWorkBlueBand;
	MIL_ID* MilRecordImages;
	double          dbTimePrev;
	double          Period;
	double          PeriodMax;
	double          PeriodMin;
	double          MaxProcTime;
	bool            MainPage;
	ALLSETTINGS*    pSettings;
	int*            pShearBarData;
	CBlob*          pBlob;
	int             EndDetectLockCount;
	int             GapDetectLatchCount;
	bool            EndDetectLockCountReset;
	bool            PlayImages;
	int             RecordIndex;
	int             PlayIndex;
	int             RecordEndCount;
	int             ImagesRecorded;
	MIL_ID          CmdListId;
	COUNTHOOKDATASTRUCT1* pHook1;
} COUNTHOOKDATASTRUCT2;

// User's thread function hook data structure. 
typedef struct tagRUNTHREADDATASTRUCT{
	bool Running;
	//bool PmacComComplete;
    CEvent  EventExit;
    CEvent  PlayEvent;
	MIL_ID  MilImage;
	MIL_ID  MilImage2;
	MIL_ID  MilWorkImage;
	MIL_ID  MilWorkImage2;
	MIL_ID  MilRejectBlobImage;
	CMilWnd*       pMilWnd;
	CMilWnd*       pMilWnd2;
	int            MaxDisplayTime;
	COUNTHOOKDATASTRUCT1* pHook1;
} RUNTHREADDATASTRUCT;

class CMil
{
public:
	int m_ShearBarData[TOTAL_SBAR_POINTS];
	double m_Y[5];
	double m_X[5];
	bool m_OverlayOn;
	MIL_ID  MilContext[2];
	MIL_ID  MilLocatePeak[2];
	MIL_ID  MilBaconBlobImage;

	CMil(void);
	~CMil(void);
	BOOL InitInstance(bool* pbSplash,ALLSETTINGS* pSettings);
	BOOL MILShowError;
	int      MilErrorMessageCount;
	CString  CErrorMessage;
	RUNTHREADDATASTRUCT RunThreadData;
	MIL_ID  MilApplication;            /* MIL Application identifier.                */
	MIL_ID  MilSystem;                 /* MIL System identifier.                     */
	MIL_ID  MilDisplay;                /* MIL Display identifier.                    */
	MIL_ID  MilDisplay2;               /* MIL Display identifier.                    */
	MIL_ID  MilOverlayImage;
	MIL_ID  MilRejectDisplay;          /* MIL Display identifier.                    */
	MIL_ID  MilRejectDisplay2;         /* MIL Display identifier.                    */
	MIL_ID  MilDigitizer[4];           /* MIL Digitizer identifier.                  */
	MIL_ID  MilImageFull;              /* MIL Image buffer identifier.               */
	MIL_ID  MilImage;                  /* MIL Image buffer identifier.               */
	MIL_ID  MilImage2;                 /* MIL Image buffer identifier.               */
	MIL_ID  MilImageReject;            /* MIL Image buffer identifier.               */
	MIL_ID  MilImageRejectWork;        /* MIL Image buffer identifier.               */
	MIL_ID  MilImageRejectWork2;        /* MIL Image buffer identifier.               */
	MIL_ID  MilImageRejectWorkRedBand;
	MIL_ID  MilImageRejectWorkGreenBand;
	MIL_ID  MilImageRejectWorkBlueBand;
	MIL_ID  MilImageReject2;           /* MIL Image buffer identifier.               */
	MIL_ID  MilWorkImage;              /* MIL Image buffer identifier.               */
	MIL_ID  MilWorkImage2;             /* MIL Image buffer identifier.               */
	MIL_ID  MilRejectBlobImage;             /* MIL Image buffer identifier.               */
	MIL_ID MilRecordImages[MAX_RECORD];
	MIL_ID  CmdListId;                 /* Mil command list identifier.               */ 
    MIL_ID          MilCom;            /* Industrial communication identifier.       */
	int     CameraTrigSel;
	int     RecodIndex;
	int     PlayIndex;
	MIL_ID  MilGrabBuff0[GRAB_LIST_SIZE];          /* MIL Image child buffer identifiers         */
	MIL_ID  MilGrabBuff1[GRAB_LIST_SIZE2];         /* MIL Image child buffer identifiers         */
	COUNTHOOKDATASTRUCT1 MilHook1;
	COUNTHOOKDATASTRUCT2 MilHook2;
	CHistory     m_History;
	int          m_nErrorCount;
	CBlob        m_Blob;
	CBlob        m_EndBlob;
	bool*        m_pbSplash;
	bool         m_NewCamera;
	bool         m_bInitOK;
	double m_dbComAllocTimeST;
	READCOMDATA   m_ReadData;
	WRITECOMDATA  m_WriteData;

    CameraPresentHookDataStruct SysUserHookData;
	//IOHOOK_PARAM IoHookData;

// Member functions
public:
	void ShowLanes();
	void HideLanes();
	long MFTYPE DisplayError(MIL_INT HookType,MIL_ID EventId,void* UserDataPtr);
	void StopDigitizer(void);
	void UnHookQue(void);
	void HookQue(void);
	void StartDigitizer(void);
	void ApplySettings();
	void FillData(double X0,double Y0,double X1,double Y1, int* Data);
	void CreateShearBarPoints();
	void ShowShearBarPoints();
	void HideShearBarPoints();
	int ReadWriteComData(void);
	int InitMilCom(void);
	void SetupCameraIP(MIL_INT64 FixedIPAddress);
};

// Utility Functions
static UINT ComRelayThreadFunc (LPVOID);
bool FillMissingData(int MaxGapFill,int GapElavation,MIL_INT* pLaserPos,int xStart,int XEnd);
long CreateBaconBlob(int MinX,MIL_INT* LaserPos,int* SBarPos,MIL_ID DstID);

//// Utility Functions
//static UINT DisplayThreadFunc (LPVOID);
////bool FillMissingData(int MaxGapFill,int GapElavation,MIL_INT* pLaserPos,int Size);
//long CreateBaconBlob(int MinX,MIL_INT* LaserPos,int* SBarPos,MIL_ID DstID);

//#include <iostream>

//void CQueTestDlg::OnBnClickedButton1()
//{
	//std::queue<int> ref;
	//using namespace std;
	//static queue <int> q1;

	//q1.push(1);
	//q1.push(2);