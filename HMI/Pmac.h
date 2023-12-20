// Pmac.h : header file
//
#pragma once
#include <afxctl.h>

#define VR_PMAC_SENDLINE 0xB0
#define VR_PMAC_GETLINE 0xB1
#define VR_PMAC_FLUSH 0xB3
#define VR_PMAC_GETMEM 0xB4
#define VR_PMAC_SETMEM 0xB5
#define VR_PMAC_SETBIT 0xBA
#define VR_PMAC_SETBITS 0xBB
#define VR_PMAC_PORT 0xBE
#define VR_PMAC_GETRESPONSE 0xBF
#define VR_PMAC_READREADY 0xC2
#define VR_CTRL_RESPONSE 0xC4
#define VR_PMAC_GETBUFFER 0xC5
#define VR_PMAC_WRITEBUFFER 0xC6
#define VR_PMAC_WRITEERROR 0xC7
#define VR_FWDOWNLOAD 0xCB
#define VR_IPADDRESS 0xE0
#define VR_DOWNLOAD  0x40
#define VR_UPLOAD     0xC0
#define ETHERNETCMDSIZE 8
#define DPR_OFFSET_MOTORBITS     112

// SERVO STATUS
// Motor Servo Status ( ? 1st 24 bit word )
typedef union tagSERVOSTATUS
{
	_int32 StatusWord;
	struct {
	USHORT rapid_spd_sel : 1; // B00 - RAPID MOVE SPEED SELECT (IXX90)
	USHORT dac_sign_mag : 1; // B01 - SIGN/MAGNITUDE SERVO (IXX96)
	USHORT sw_capture : 1; // B02 - SOFTWARE HOME CAPTURE (IXX97.0)
	USHORT fe_capture : 1; // B03 - CAPTURE ON FOLLOWING ERROR (IXX97.1)
	USHORT handwheel_ena : 1; // B04 - HANDWHEEL ENABLE FLAG (IXX06.0)
	USHORT hw_mode : 1; // B05 - HANDWHEEL MODE FLAG (IXX06.1)
	USHORT phased_motor : 1; // B06 - PHASED MOTOR ENABLE FLAG (IXX01.0)
	USHORT yenc_phase : 1; // B07 - Y PHASE ENCODER (IXX01.1)
	USHORT user_servo : 1; // B08 - USER WRITEN SERVO ENABLE (IXX59.0)
	USHORT user_phase : 1; // B09 - USER WRITEN PHASE ENABLE (IXX59.1)
	USHORT home_search : 1; // B10 - HOME IN PROGRESS FLAG
	USHORT block_request : 1; // B11 - BLOCK REQUEST FLAG
	USHORT limit_stop : 1; // B12 - Limit Stop Flag
	USHORT desired_vel_0 : 1; // B13 - Desired Velocity = 0
	USHORT data_block_err : 1; // B14 - DATA BLOCK ERROR
	USHORT dwelling : 1; // B15 - Dwell Mode
	USHORT integrator_ena : 1; // B16 - Ixx34
	USHORT run_program : 1; // B17 - MOVE TIMER ACTIVE
	USHORT open_loop : 1; // B18 - OPEN LOOP MODE
	USHORT amp_enabled : 1; // B19 - AMPLIFIER ENABLED FLAG
	USHORT algo_ena : 1; // B20 - EXTENDED ALGO ENABLE FLAG (I3300+50*N)
	USHORT pos_limit : 1; // B21 - POSITIVE POSITION LIMIT
	USHORT neg_limit : 1; // B22 - NEGATIVE POSITION LIMIT
	USHORT activated : 1; // B23 - Ixx00
	USHORT pads : 8; // B24..31 - Not Available
	}Bits;
} SERVOSTATUS;

// MOTOR STATUS
// Motor Status ( ? 2nd 24 bit word )
typedef union tagMOTORSTATUS
{
	_int32 StatusWord;
	struct {
	USHORT in_position : 1; // B00 - IN POSITION
	USHORT warn_ferr : 1; // B01 - SOFT FOLLOWING ERROR
	USHORT fatal_ferr : 1; // B02 - FATAL FOLLOWING ERROR
	USHORT amp_fault : 1; // B03 - AMP FAULT ERROR
	USHORT backlash_dir : 1; // B04 - BACKLASH DIRECTION FLAG
	USHORT amp_i2t_err : 1; // B05 - I2T AMP FAULT
	USHORT integral_ferr : 1; // B06 - INTEGRATED FOLLOWING ERROR FAULT
	USHORT triger_home_flg : 1; // B07 - TRIGGER/HOME MOVE FLAG
	USHORT phase_find_err : 1; // B08 - PHASE FINDING ERROR FLAG
	USHORT tbd09 : 1; // B09 - TBD
	USHORT home_complete : 1; // B10 - HOME COMPLETE FLAG
	USHORT stopped_on_limit : 1; // B11 - POS LIMIT STOP FLAG
	USHORT: 1; // B12 - TBD
	USHORT reset_phase_error : 1; // B13 - TBD
	USHORT encoder_count_error : 1; // B14 - TBD
	USHORT cs_assigned : 1; // B15 - TBD
	USHORT cs_def : 4; // B16..19 - Coord. Sys. Axis Def
	USHORT coord_sys : 4; // B20..23 - MOTOR COORDINATE SYSTEM NUMBER (-1)
	USHORT padm : 8; // B24..31 - Not Available	
	}Bits;
} MOTORSTATUS;

// MOTOR STATUS
// Motor Status ( ? 2nd 24 bit word )
//typedef union tagMOTORSTATUS
//{
//	_int32 StatusWord;
//	struct {
//	USHORT in_position : 1; // B00 - IN POSITION
//	USHORT warn_ferr : 1; // B01 - SOFT FOLLOWING ERROR
//	USHORT fatal_ferr : 1; // B02 - FATAL FOLLOWING ERROR
//	USHORT amp_fault : 1; // B03 - AMP FAULT ERROR
//	USHORT backlash_dir : 1; // B04 - BACKLASH DIRECTION FLAG
//	USHORT amp_i2t_err : 1; // B05 - I2T AMP FAULT
//	USHORT integral_ferr : 1; // B06 - INTEGRATED FOLLOWING ERROR FAULT
//	USHORT triger_home_flg : 1; // B07 - TRIGGER/HOME MOVE FLAG
//	USHORT phase_find_err : 1; // B08 - PHASE FINDING ERROR FLAG
//	USHORT tbd09 : 1; // B09 - TBD
//	USHORT home_complete : 1; // B10 - HOME COMPLETE FLAG
//	USHORT stopped_on_limit : 1; // B11 - POS LIMIT STOP FLAG
//	USHORT: 1; // B12 - TBD
//	USHORT: 1; // B13 - TBD
//	USHORT: 1; // B14 - TBD
//	USHORT cs_assigned : 1; // B15 - TBD
//	USHORT cs_def : 4; // B16..19 - Coord. Sys. Axis Def
//	USHORT coord_sys : 4; // B20..23 - MOTOR COORDINATE SYSTEM NUMBER (-1)
//	USHORT padm : 8; // B24..31 - Not Available	
//	}Bits;
//} MOTORSTATUS;

//// MOTOR DATA
//typedef struct tagMOTORDATA
//{
//	_int32          FollowingErrorWord0;
//	_int32          FollowingErrorWord1;
//	_int32          ServoCommandWord;
//	SERVOSTATUS     ServoStatus;
//	MOTORSTATUS     MotorStatus;
//	_int32          PositionBiasWord0;
//	_int32          PositionBiasWord1;
//	_int32          Velocity;
//	_int32          MasterPositionWord0;
//	_int32          MasterPositionWord1;
//	_int32          PositionWord0;
//	_int32          PositionWord1;
//} MOTORDATA;

// MOTOR DATA
typedef struct tagMOTORDATA
{
	_int32          FollowingErrorWord0;
	_int32          FollowingErrorWord1;
	_int32          ServoCommandWord;
	SERVOSTATUS     ServoStatus;
	MOTORSTATUS     MotorStatus;
	_int32          PositionBiasWord0;
	_int32          PositionBiasWord1;
	_int32          Velocity;
	_int32          MasterPositionWord0;
	_int32          MasterPositionWord1;
	_int32          PositionWord0;
	_int32          PositionWord1;
} MOTORDATA;

//-----------------------------------------------------------------------//
//------- MACHINE SPECIFIC DATA -----------------------------------------//
//-----------------------------------------------------------------------//
//#define PMAC_SEND_SIZE    68
//#define DPRAM_OFFSET     116
//#define PMAC_READ_SIZE   528    // 132 DPRAM locations

#define PMAC_SEND_SIZE   24
#define PMAC_READ_SIZE  996   // 249 DPRAM locations
#define DPRAM_OFFSET    116
#define PMAC_READ_SIZE2  48   // 12 DPRAM locations
#define DPRAM_OFFSET2   116
#define MAX_PMAC_DATA    15


//// INPUTS
//typedef union tagBTCINPUTS
//{
//	_int16 IOWord;
//	struct {
//	USHORT In0 : 1;
//	USHORT In1 : 1;
//	USHORT In2 : 1;
//	USHORT In3 : 1;
//	USHORT In4 : 1;
//	USHORT In5 : 1;
//	USHORT In6 : 1;
//	USHORT In7 : 1;
//	USHORT In8 : 1;
//	USHORT In9 : 1;
//	USHORT In10 : 1;
//	USHORT In11 : 1;
//	USHORT In12 : 1;
//	USHORT In13 : 1;
//	USHORT In14 : 1;
//	USHORT In15 : 1;
//	}Bits;
//} BTCINPUTS;
//
//// OUTPUTS
//typedef union tagBTCOUTPUTS
//{
//	_int16 IOWord;
//	struct {
//	USHORT TimeStampAck : 1;
//	USHORT PComAck : 1;
//	USHORT Thin : 1;
//	USHORT Blower : 1;
//	USHORT BTCReady : 1;
//	USHORT KnifeEngage : 1;
//	USHORT BTCBusPower : 1;
//	USHORT BTCReadyManual : 1;
//	USHORT Padding : 8;
//	}Bits;
//} BTCOUTPUTS;
//
//// HALLS
//typedef union tagMOTORHALLS
//{
//	_int16 IOWord;
//	struct {
//	USHORT HallU0 : 1;
//	USHORT HallV0 : 1;
//	USHORT HallW0 : 1;
//	USHORT Therm0 : 1;
//
//	USHORT HallU1 : 1;
//	USHORT HallV1 : 1;
//	USHORT HallW1 : 1;
//	USHORT Therm1 : 1;
//
//	USHORT HallU2 : 1;
//	USHORT HallV2 : 1;
//	USHORT HallW2 : 1;
//	USHORT Therm2 : 1;
//
//	USHORT HallU3 : 1;
//	USHORT HallV3 : 1;
//	USHORT HallW3 : 1;
//	USHORT Therm3 : 1;
//
//	}Bits;
//	struct {
//	USHORT Mtr0 : 4;
//	USHORT Mtr1 : 4;
//	USHORT Mtr2 : 4;
//	USHORT Mtr3 : 4;
//	}UVWT;
//} MOTORHALLS;
//
//// HALLS
//typedef union tagMOTORFLAGS
//{
//	_int16 IOWord;
//	struct {
//	USHORT EStop : 1;
//	USHORT CutterGuard : 1;
//	USHORT DrumDoor : 1;
//	USHORT KnifeDisconnect : 1;
//
//	USHORT AlignHome : 1;
//	USHORT DrumHome : 1;
//	USHORT KnifeHome : 1;
//	USHORT UpperProx : 1;
//
//	USHORT LowerProx : 1;
//	USHORT FlipNose : 1;
//	USHORT HallW2 : 1;
//	USHORT Therm2 : 1;
//
//	USHORT HallU3 : 1;
//	USHORT HallV3 : 1;
//	USHORT HallW3 : 1;
//	USHORT Therm3 : 1;
//
//	}Bits;
//} MOTORFLAGS;
//
//// BTC DATA
//typedef struct tagBTCDATA
//{
//	MOTORDATA Mtr1;
//	MOTORDATA Mtr2;
//	MOTORDATA Mtr3;
//	MOTORDATA Mtr4;
//	MOTORDATA Mtr5;
//	MOTORDATA Mtr6;
//	MOTORDATA Mtr7;
//	MOTORDATA Mtr8;
//	_int16 ComTicks;
//	_int16 DataPeriod;
//	_int16 GlobalStatus;
//	_int16 BtcMode;
//	BTCINPUTS  BtcInputs;
//	BTCOUTPUTS BtcOutputs;
//	MOTORFLAGS Flags1;
//	_int16 Flags2;
//	_int16 CountOnPaper;
//	_int16 Spare0;
//	_int32 SheetCount;
//	_int16 DataErrorCount0;
//	_int16 DataErrorCount1;
//	float  PaperRollSize;
//	MOTORHALLS HallsMotor1to4;
//	MOTORHALLS HallsMotor5to8;
//	_int32 TotalSheetCount;
//	_int32 SheetCountShift;
//	float  PeakCurrentMotor1;
//	float  PeakCurrentMotor2;
//	float  PeakCurrentMotor3;
//	float  PeakCurrentMotor4;
//	float  PeakCurrentMotor5;
//	float  PeakCurrentMotor6;
//	float  PeakCurrentMotor7;
//	float  PeakCurrentMotor8;
//	float  CurrentMotor1;
//	float  CurrentMotor2;
//	float  CurrentMotor3;
//	float  CurrentMotor4;
//	float  CurrentMotor5;
//	float  CurrentMotor6;
//	float  CurrentMotor7;
//	float  CurrentMotor8;
//	_int32 PeakFEMotor1;
//	_int32 PeakFEMotor2;
//	_int32 PeakFEMotor3;
//	_int32 PeakFEMotor4;
//	_int32 PeakFEMotor5;
//	_int32 PeakFEMotor6;
//	_int32 PeakFEMotor7;
//	_int32 PeakFEMotor8;            // DPRAM $6009F
//	_int16 BaconSpeedNotUsed;       // DPRAM $600A0
//	_int16 UnusedStatusWords[17];
//
//} BTCDATA;


// Local Inputs
//----------------------------//

//#define TimeStamp             M1
//#define ServiceDisconnect     M2
//#define BaconSizeGood         M3
//#define BaconSizeBad          M4
//#define RejectVFDFault        M5
//#define InSpare6              M6
////#define EStop               M7   // On Osceola Line 1 - 3 EStop use was (#define EStop M115)
//#define MainEStop             M7
//#define InSpare8              M8
//#define ShuntOverTemp         M9
//#define PaperEye1             M10
//#define PaperEye2             M11
//#define PaperEye3             M12
//#define InSpare13             M13
//#define InSpare14             M14
//#define InSpare15             M15
//#define InSpare16             M16


// INPUTS
typedef union tagBTCINPUTS
{
	_int16 IOWord;
	struct {
	USHORT In0 : 1;
	USHORT In1 : 1;
	USHORT In2 : 1;
	USHORT In3 : 1;
	USHORT RejectVFDFault : 1;
	USHORT In5 : 1;
	USHORT In6 : 1;
	USHORT In7 : 1;
	USHORT In8 : 1;
	USHORT In9 : 1;
	USHORT In10 : 1;
	USHORT In11 : 1;
	USHORT In12 : 1;
	USHORT In13 : 1;
	USHORT In14 : 1;
	USHORT In15 : 1;
	}Bits;
} BTCINPUTS;

// BTCWORD
typedef union tagBTCWORD
{
	_int16 IOWord;
	struct {
	USHORT In0 : 1;
	USHORT In1 : 1;
	USHORT In2 : 1;
	USHORT In3 : 1;
	USHORT In4 : 1;
	USHORT In5 : 1;
	USHORT In6 : 1;
	USHORT In7 : 1;
	USHORT In8 : 1;
	USHORT In9 : 1;
	USHORT In10 : 1;
	USHORT In11 : 1;
	USHORT In12 : 1;
	USHORT In13 : 1;
	USHORT In14 : 1;
	USHORT In15 : 1;
	}Bits;
} BTCWORD;

// INPUTS
typedef union tagSLICERINPUTS
{
	_int16 IOWord;
	struct {
	USHORT SafetyEStop : 1;
	USHORT SlicerDisconnect : 1;
	USHORT In3 : 1;
	USHORT TrapKeyStatus : 1;
	USHORT SlicerBellyEye: 1;
	USHORT In6 : 1;
	USHORT BelevatorEstop : 1;
	USHORT In8 : 1;
	USHORT ShuntOverTemp1 : 1;
	USHORT BelevartoPusherBack: 1;
	USHORT ShuntOverTemp2 : 1;
	USHORT BelevatorStart : 1;
	USHORT BelevatorStop : 1;
	USHORT In14 : 1;
	USHORT In15 : 1;
	USHORT In16 : 1;
	};
} SLICERINPUTS;

//M23->X:$6010C,0,1  // FeedStartStop
//M24->X:$6010C,1,1  // TimingTestActive
//M25->X:$6010C,2,1  // MotorsAtHome
//M26->X:$6010C,3,1  // BellyChuteEyeBlocked

// Status Bits
typedef union tagBTCSTATUSBITS
{
	_int16 IOWord;
	struct {
	USHORT FeedStartStop : 1;
	USHORT TimingTestActive : 1;
	USHORT MotorsAtHome : 1;
	USHORT BellyChuteEyeBlocked : 1;
	USHORT BellyJamInSlicer : 1;
	USHORT BellyJamInLoader : 1;
	USHORT BellyPusherStuck : 1;
	USHORT PaperEyeError : 1;
	USHORT PaperOut : 1;
	USHORT ExitVfdRun : 1;
	USHORT AlignHomeFault : 1;
	USHORT FlipperHomeFault : 1;
	USHORT SlicerBladeHomeFault : 1;
	USHORT KnifeHomeFault : 1;
	USHORT DrumHomeFault : 1;
	USHORT TTFault : 1;
	};
} BTCSTATUSBITS;

// Status Bits
typedef union tagPHASESTATUSBITS
{
	_int16 IOWord;
	struct {
	USHORT Mtr1 : 1;
	USHORT Mtr2 : 1;
	USHORT Mtr3 : 1;
	USHORT Mtr4 : 1;
	USHORT Mtr5 : 1;
	USHORT Mtr6 : 1;
	USHORT Mtr7 : 1;
	USHORT Mtr8 : 1;
	USHORT Mtr9 : 1;
	USHORT Mtr10 : 1;
	USHORT Mtr11 : 1;
	USHORT Mtr12 : 1;
	USHORT Mtr13 : 1;
	USHORT Mtr14 : 1;
	USHORT Mtr15 : 1;
	USHORT Mtr16 : 1;
	};
} PHASESTATUSBITS;

// BTC OUTPUTS
//#define RejectVFDReset       M33
//#define RejectVFDRun         M34
//#define MonitorLight         M35
//#define Blower               M36
//#define MasterBusPower       M37
//#define KnifeEngage          M38
//#define BelevatorLight       M39
//#define FlipperrLight        M40
// OLD
//#define SpareOut0            M33
//#define SpareOut1            M34
//#define SpareOut2            M35
//#define Blower               M36
//#define MasterBusPower       M37
//#define KnifeEngage          M38
//#define BelevatorLight       M39
//#define PaperMarking         M40
typedef union tagBTCOUTPUTS
{
	_int16 IOWord;
	struct {
	USHORT RejectVFDReset : 1;
	USHORT RejectVFDRun : 1;
	USHORT MonitorLight : 1;
	USHORT Blower : 1;            
	USHORT MasterBusPower : 1;
	USHORT KnifeEngage : 1;
	USHORT BelevatorLight : 1;
	USHORT FlipperrLight : 1;
	USHORT Padding : 8;
	};
} BTCOUTPUTS;


// SLICER OUTPUTS
//#define Tamper               M45    // Slave output
//#define BellyPusher          M46    // Slave output
//#define BellyStoper          M47    // Slave output
//#define FeedRollersDown      M48    // Slave output
//#define SlaveBusPower        M49    // Slave output
//#define BladeBrake           M50    // Slave output
//#define FeedNoseDown         M51    // Slave output
//#define TrapKeyRelease       M52    // Slave output
typedef union tagSLICEROUTPUTS
{
	_int16 IOWord;
	struct {
	USHORT Tamper : 1;
	USHORT BellyPusher : 1;
	USHORT BellyStopper : 1;
	USHORT FeedRollersDown : 1;
	USHORT SlaveBusPower : 1;
	USHORT BladeBreak : 1;
	USHORT FeedNoseDown : 1;
	USHORT TrapKeyRelease : 1;
	USHORT Padding : 8;
	};
} SLICEROUTPUTS;

// HALLS
typedef union tagMOTORHALLS
{
	_int16 IOWord;
	struct {
	USHORT HallU0 : 1;
	USHORT HallV0 : 1;
	USHORT HallW0 : 1;
	USHORT Therm0 : 1;

	USHORT HallU1 : 1;
	USHORT HallV1 : 1;
	USHORT HallW1 : 1;
	USHORT Therm1 : 1;

	USHORT HallU2 : 1;
	USHORT HallV2 : 1;
	USHORT HallW2 : 1;
	USHORT Therm2 : 1;

	USHORT HallU3 : 1;
	USHORT HallV3 : 1;
	USHORT HallW3 : 1;
	USHORT Therm3 : 1;

	}Bits;
	struct {
	USHORT Mtr0 : 4;
	USHORT Mtr1 : 4;
	USHORT Mtr2 : 4;
	USHORT Mtr3 : 4;
	}UVWT;
} MOTORHALLS;

// HALLS
typedef union tagMOTORFLAGS
{
	_int16 IOWord;
	struct {
	USHORT SafetyAux : 1;
	USHORT DrumDoor : 1;
	USHORT PaperDoor : 1;
	USHORT FlipperPE : 1;

	USHORT AlignHome : 1;
	USHORT DrumHome : 1;
	USHORT KnifeHome : 1;
	USHORT UpperProx2 : 1;

	USHORT LowerProx2 : 1;
	USHORT FlipperGuard : 1;
	USHORT PaperWheel : 1;
	USHORT Therm2 : 1;

	USHORT UpperProx : 1;
	USHORT LowerProx : 1;
	USHORT HallW3 : 1;
	USHORT PaperOut : 1;

	}Bits;
} MOTORFLAGS;

// HALLS
typedef union tagSLAVEMOTORFLAGS
{
	_int16 IOWord;
	struct {

	USHORT Flag0 : 1;
	USHORT Flag1 : 1;
	USHORT Flag2 : 1;
	USHORT BladeHome : 1;

	USHORT Flag4 : 1;
	USHORT BellyDetect : 1;
	USHORT BellyChuteEye : 1;
	USHORT BelevatorHome : 1;

	USHORT Flag8 : 1;
	USHORT Flag9 : 1;
	USHORT Flag10 : 1;
	USHORT Flag11 : 1;

	USHORT Flag12 : 1;
	USHORT Flag13 : 1;
	USHORT Flag14 : 1;
	USHORT Flag15 : 1;

	}Bits;
} SLAVEMOTORFLAGS;


//M120->X:$078000,16		; HMFL1 flag input status
//M121->X:$078000,17		; PLIM1 flag input status
//M122->X:$078000,18		; MLIM1 flag input status
//M115->X:$078000,19		; USER1 flag input status
//M124->X:$078000,20		; Channel 1 W flag input status
//M125->X:$078000,21		; Channel 1 V flag input status
//M126->X:$078000,22		; Channel 1 U flag input status
//M127->X:$078000,23		; Channel 1 T flag input status

// HALLSFLAGS
typedef union tagHALLSFLAGS
{
	_int16 IOByte;
	struct {
	USHORT HMFL1 : 1;
	USHORT PLIM1 : 1;
	USHORT MLIM1 : 1;
	USHORT USER1 : 1;
	USHORT HallW1 : 1;
	USHORT HallV1 : 1;
	USHORT HallU1 : 1;
	USHORT Therm1 : 1;
	USHORT HMFL2 : 1;
	USHORT PLIM2 : 1;
	USHORT MLIM2 : 1;
	USHORT USER2 : 1;
	USHORT HallW2 : 1;
	USHORT HallV2 : 1;
	USHORT HallU2 : 1;
	USHORT Therm2 : 1;
	};
	struct {
	USHORT AllFlags1 : 4;
	USHORT HallWVUT1 : 4;
	USHORT AllFlags2 : 4;
	USHORT HallWVUT2 : 4;
	};
} FLAGHALLS;

// Encoder Count errors
typedef union tagENCCNTERRORS
{
	_int32 IOWord;
	struct {
	USHORT Byte0 : 8;
	USHORT Byte1 : 8;
	USHORT Byte2 : 8;
	USHORT Byte3 : 8;
	};
} ENCCNTERRORS;

// BTC DATA
typedef struct tagBTCDATA
{
	MOTORDATA Mtr1;
	MOTORDATA Mtr2;
	MOTORDATA Mtr3;
	MOTORDATA Mtr4;
	MOTORDATA Mtr5;
	MOTORDATA Mtr6;
	MOTORDATA Mtr7;
	MOTORDATA Mtr8;
	MOTORDATA Mtr9;
	MOTORDATA Mtr10;
	MOTORDATA Mtr11;
	MOTORDATA Mtr12;
	MOTORDATA Mtr13;
	MOTORDATA Mtr14;
	MOTORDATA Mtr15;
	MOTORDATA Mtr16;
	float  PeakCurrentMotor1;
	float  PeakCurrentMotor2;
	float  PeakCurrentMotor3;
	float  PeakCurrentMotor4;
	float  PeakCurrentMotor5;
	float  PeakCurrentMotor6;
	float  PeakCurrentMotor7;
	float  PeakCurrentMotor8;
	float  CurrentMotor1;
	float  CurrentMotor2;
	float  CurrentMotor3;
	float  CurrentMotor4;
	float  CurrentMotor5;
	float  CurrentMotor6;
	float  CurrentMotor7;
	float  CurrentMotor8;
	_int16 MaxFE1; 
	_int16 MaxFE2;
	_int16 MaxFE3;
	_int16 MaxFE4;
	_int16 MaxFE5;
	_int16 MaxFE6;
	_int16 MaxFE7;
	_int16 MaxFE8;
	_int16 MaxFE9;
	_int16 MaxFE10;
	_int16 MaxFE11;
	_int16 MaxFE12;
	_int16 MaxFE13;
	_int16 MaxFE14;
	_int16 MaxFE15;
	_int16 MaxFE16;
	_int16 GlobalStatus;
	_int16 BtcMode;
	FLAGHALLS Mtr1Mtr2FlagsHalls;
	FLAGHALLS Mtr3Mtr4FlagsHalls;
	FLAGHALLS Mtr5Mtr6FlagsHalls;
	FLAGHALLS Mtr7Mtr8FlagsHalls;
	BTCINPUTS  BtcInputs;
	SLICERINPUTS  SlicerInputs;	
	BTCOUTPUTS BtcOutputs;
	SLICEROUTPUTS SlicerOutputs;
	FLAGHALLS Mtr9Mtr10FlagsHalls;
	FLAGHALLS Mtr11Mtr12FlagsHalls;
	FLAGHALLS Mtr13Mtr14FlagsHalls;
	FLAGHALLS Mtr15Mtr16FlagsHalls;
	float  PeakCurrentMotor9;
	float  PeakCurrentMotor10;
	float  PeakCurrentMotor11;
	float  PeakCurrentMotor12;
	float  PeakCurrentMotor13;
	float  PeakCurrentMotor14;
	float  PeakCurrentMotor15;
	float  PeakCurrentMotor16;
	float  CurrentMotor9;
	float  CurrentMotor10;
	float  CurrentMotor11;
	float  CurrentMotor12;
	float  CurrentMotor13;
	float  CurrentMotor14;
	float  CurrentMotor15;
	float  CurrentMotor16;
	_int16 SlicerGlobalStatus;
	BTCSTATUSBITS StatusBits;
	_int16 ComTicks;
	_int16 DataPeriod;
	float  PaperRollSize;
	_int32 SheetCount;
	_int32 SheetCountShift;
	_int32 TotalSheetCount;
	PHASESTATUSBITS MtrPhaseStatus;
	_int16 BaconSpeed_NOTUSED;
	unsigned char BusVoltage1;
	unsigned char BusVoltage2;
	unsigned char BusVoltage3;
	unsigned char BusVoltage4_NOTUSED;
	float  IGBTTemp;
	_int16 ExitVfdSpeedInPerSec;	
	_int16 RejectVfdSpeedInPerSec;	
	ENCCNTERRORS EncCntErrorsMtr1to4;	
	ENCCNTERRORS EncCntErrorsMtr5to8;	
	ENCCNTERRORS EncCntErrorsMtr9to12;	
	ENCCNTERRORS EncCntErrorsMtr13to16;	
} BTCDATA;

//// Slicer DATA
//typedef struct tagSLICERDATA
//{
//	float  PeakCurrentMotor1;
//	float  PeakCurrentMotor2;
//	float  PeakCurrentMotor3;
//	float  PeakCurrentMotor4;
//	float  PeakCurrentMotor5;
//	float  PeakCurrentMotor6;
//	float  CurrentMotor1;
//	float  CurrentMotor2;
//	float  CurrentMotor3;
//	float  CurrentMotor4;
//	float  CurrentMotor5;
//	float  CurrentMotor6;
//} SLICERDATA;

//-----------------------------------------------------------------------//
//------- END OF MACHINE SPECIFIC DATA ----------------------------------//
//-----------------------------------------------------------------------//


// Ethernet command structure
typedef struct tagEthernetCmd
{
BYTE RequestType;
BYTE Request;
WORD wValue;
WORD wIndex;
WORD wLength;
BYTE bData[1492];
} ETHERNETCMD,*PETHERNETCMD;


//To check for individual error codes the MACROs below are very useful:
#define IS_COMM_MORE(c) ((c & COMM_FAIL) == 0)
#define IS_COMM_EOT(c) ((c & COMM_FAIL) == COMM_EOT)
#define IS_COMM_TIMEOUT(c) ((c & COMM_FAIL) == COMM_TIMEOUT)
#define IS_COMM_BADCKSUM(c) ((c & COMM_FAIL) == COMM_BADCKSUM)
#define IS_COMM_ERROR(c) ((c & COMM_FAIL) == COMM_ERROR)
#define IS_COMM_FAIL(c) ((c & COMM_FAIL) == COMM_FAIL)
#define IS_COMM_ANYERROR(c) ((c & COMM_ANYERR) > 0)
#define IS_COMM_UNSOLICITED(c) ((c & 0xF0000000) == COMM_UNSOLICITED)
#define COMM_CHARS(c) (c & 0x0FFFFFFF) // Returns the number of characters
#define COMM_STATUS(c) (c & 0xF0000000) // Returns the status byte



//
// PMAC communications class
class CPmac
{
public:
	CPmac(void);
	~CPmac(void);
	bool Init(long dwDevice);
	CString m_strIP[4];
    SOCKET m_sock;
    SOCKADDR_IN m_dest_sin;
	CString m_strResponse;

public:
    //IPmacDevice *pmac;
	double		m_I10;
	double		m_ServoFrequency;
	VARIANT_BOOL		m_DPRamPresent;
	//CPmacDeviceEvents	m_pmacdeviceEvents;

private:
	LPUNKNOWN			m_pUnkSink;
	DWORD				m_dwCookie;
	//CPmacDevice			m_pmacdevice;
  	HRESULT				m_hResult;             // Used for interface calls
	long				m_dwDevice;
	bool		        m_bDeviceOpen;
	bool		        m_bSocketOpen;
    LPUNKNOWN			m_pDisp;
	//CPmacDeviceEvents	PmacDeviceEvents;

public:
	void ClosePmac();
	void SetDownloadMsgPtr(CEdit* pWnd);
	void SetProgressMsgPtr(CProgressCtrl* pWnd);
	void SetPmacMsgWnd(HWND hWnd);
	void SelectPmac();
	bool Upload(LPCTSTR lpsz);
	bool Download(LPCTSTR lpsz);
	int Reset(LPCTSTR lpszCmd,BOOL AsciiRingCom);
	int Save(LPCTSTR lpszCmd);
	int SendCommand(LPCTSTR lpszCmd);
	//int GetResponse(LPCTSTR lpszCmd,BSTR *response);
	int GetResponse(LPCTSTR lpszCmd,LPTSTR response);
	int GetResponseBuffer(LPTSTR response);

	int IsPmacOpen();
	//VARIANT_BOOL GetVariable(char ch,long num,long* Data);
	//VARIANT_BOOL GetVariable(char ch,long num,double* Data);
	//VARIANT_BOOL SetVariable(char ch,long num,long Data);
	//VARIANT_BOOL SetVariable(char ch,long num,double Data);
	//VARIANT_BOOL DPRGet(int Offset, short * Data);
	//VARIANT_BOOL DPRGet(int Offset, long * Data);
	//VARIANT_BOOL DPRSet(int Offset, short Data);
	//VARIANT_BOOL DPRSet(int Offset, int Data);
	bool GetVariable(char ch,long num,long* Data);
	bool GetVariable(char ch,long num,double* Data);
	bool SetVariable(char ch,long num,long Data);
	bool SetVariable(char ch,long num,double Data);
	bool DPRGet(int Offset, short * Data);
	bool DPRGet(int Offset, long * Data);
	bool DPRSet(int Offset, short Data);
	bool DPRSet(int Offset, int Data);
	//VARIANT_BOOL DPRGetMem(int Offset,int NumBytes, VARIANT *Data);
	bool DPRGetMem(int Offset,int NumBytes, char* Data);
	bool DPRSetMem(int Offset,int NumBytes, char* Data);
	double DPRFloat(long long d,double scale);
	double DPRFixed( long d[], double scale );
	double GetCommandedPos(int MtrNum,double scale);
	double GetFollowError(int MtrNum,double scale);
	double GetVelocity(int MtrNum,double scale);
	double GetMotorPosition(int MtrNum,double scale);

	// Low level functions
	bool PmacSockGetResponse(LPCTSTR lpsz);
	bool PmacSockGetResponseBuffer();
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//////////////////// OLD PMAC SERVER CODE /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// OLD
/////////////////////////////////////////////////////////////////////////////////////////
//#include <afxctl.h>
//#include "PmacDevice.h"
//
////#import "C:\\Windows\\System32\\PcommServer.exe" no_namespace
//
//// DPRAM data buffer size
//#define PMAC_SEND_SIZE   24
//#define PMAC_READ_SIZE  996   // 249 DPRAM locations
//#define DPRAM_OFFSET    116
//#define PMAC_READ_SIZE2  48   // 12 DPRAM locations
//#define DPRAM_OFFSET2   116
//#define MAX_PMAC_DATA    15
//
//// SERVO STATUS
//// Motor Servo Status ( ? 1st 24 bit word )
//typedef union tagSERVOSTATUS
//{
//	_int32 StatusWord;
//	struct {
//	USHORT rapid_spd_sel : 1; // B00 - RAPID MOVE SPEED SELECT (IXX90)
//	USHORT dac_sign_mag : 1; // B01 - SIGN/MAGNITUDE SERVO (IXX96)
//	USHORT sw_capture : 1; // B02 - SOFTWARE HOME CAPTURE (IXX97.0)
//	USHORT fe_capture : 1; // B03 - CAPTURE ON FOLLOWING ERROR (IXX97.1)
//	USHORT handwheel_ena : 1; // B04 - HANDWHEEL ENABLE FLAG (IXX06.0)
//	USHORT hw_mode : 1; // B05 - HANDWHEEL MODE FLAG (IXX06.1)
//	USHORT phased_motor : 1; // B06 - PHASED MOTOR ENABLE FLAG (IXX01.0)
//	USHORT yenc_phase : 1; // B07 - Y PHASE ENCODER (IXX01.1)
//	USHORT user_servo : 1; // B08 - USER WRITEN SERVO ENABLE (IXX59.0)
//	USHORT user_phase : 1; // B09 - USER WRITEN PHASE ENABLE (IXX59.1)
//	USHORT home_search : 1; // B10 - HOME IN PROGRESS FLAG
//	USHORT block_request : 1; // B11 - BLOCK REQUEST FLAG
//	USHORT limit_stop : 1; // B12 - Limit Stop Flag
//	USHORT desired_vel_0 : 1; // B13 - Desired Velocity = 0
//	USHORT data_block_err : 1; // B14 - DATA BLOCK ERROR
//	USHORT dwelling : 1; // B15 - Dwell Mode
//	USHORT integrator_ena : 1; // B16 - Ixx34
//	USHORT run_program : 1; // B17 - MOVE TIMER ACTIVE
//	USHORT open_loop : 1; // B18 - OPEN LOOP MODE
//	USHORT amp_enabled : 1; // B19 - AMPLIFIER ENABLED FLAG
//	USHORT algo_ena : 1; // B20 - EXTENDED ALGO ENABLE FLAG (I3300+50*N)
//	USHORT pos_limit : 1; // B21 - POSITIVE POSITION LIMIT
//	USHORT neg_limit : 1; // B22 - NEGATIVE POSITION LIMIT
//	USHORT activated : 1; // B23 - Ixx00
//	USHORT pads : 8; // B24..31 - Not Available
//	}Bits;
//} SERVOSTATUS;
//
//// MOTOR STATUS
//// Motor Status ( ? 2nd 24 bit word )
//typedef union tagMOTORSTATUS
//{
//	_int32 StatusWord;
//	struct {
//	USHORT in_position : 1; // B00 - IN POSITION
//	USHORT warn_ferr : 1; // B01 - SOFT FOLLOWING ERROR
//	USHORT fatal_ferr : 1; // B02 - FATAL FOLLOWING ERROR
//	USHORT amp_fault : 1; // B03 - AMP FAULT ERROR
//	USHORT backlash_dir : 1; // B04 - BACKLASH DIRECTION FLAG
//	USHORT amp_i2t_err : 1; // B05 - I2T AMP FAULT
//	USHORT integral_ferr : 1; // B06 - INTEGRATED FOLLOWING ERROR FAULT
//	USHORT triger_home_flg : 1; // B07 - TRIGGER/HOME MOVE FLAG
//	USHORT phase_find_err : 1; // B08 - PHASE FINDING ERROR FLAG
//	USHORT tbd09 : 1; // B09 - TBD
//	USHORT home_complete : 1; // B10 - HOME COMPLETE FLAG
//	USHORT stopped_on_limit : 1; // B11 - POS LIMIT STOP FLAG
//	USHORT: 1; // B12 - TBD
//	USHORT reset_phase_error : 1; // B13 - TBD
//	USHORT encoder_count_error : 1; // B14 - TBD
//	USHORT cs_assigned : 1; // B15 - TBD
//	USHORT cs_def : 4; // B16..19 - Coord. Sys. Axis Def
//	USHORT coord_sys : 4; // B20..23 - MOTOR COORDINATE SYSTEM NUMBER (-1)
//	USHORT padm : 8; // B24..31 - Not Available	
//	}Bits;
//} MOTORSTATUS;
//
//// MOTOR DATA
//typedef struct tagMOTORDATA
//{
//	_int32          FollowingErrorWord0;
//	_int32          FollowingErrorWord1;
//	_int32          ServoCommandWord;
//	SERVOSTATUS     ServoStatus;
//	MOTORSTATUS     MotorStatus;
//	_int32          PositionBiasWord0;
//	_int32          PositionBiasWord1;
//	_int32          Velocity;
//	_int32          MasterPositionWord0;
//	_int32          MasterPositionWord1;
//	_int32          PositionWord0;
//	_int32          PositionWord1;
//} MOTORDATA;
//
//// Local Inputs
////----------------------------//
////#define TimeStamp             M1
////#define ServiceDisconnect     M2
////#define BaconSizeGood         M3
////#define BaconSizeBad          M4
////#define InSpare5              M5
////#define InSpare6              M6
////#define EStop                 M7
////#define InSpare8              M8
////#define ShuntOverTemp         M9
////#define PaperMin              M10
////#define PaperMid              M11
////#define PaperMax              M12
////#define InSpare13             M13
////#define InSpare14             M14
////#define InSpare15             M15
////#define InSpare16             M16
//
//// INPUTS
//typedef union tagBTCINPUTS
//{
//	_int16 IOWord;
//	struct {
//	USHORT In0 : 1;
//	USHORT In1 : 1;
//	USHORT In2 : 1;
//	USHORT In3 : 1;
//	USHORT In4 : 1;
//	USHORT In5 : 1;
//	USHORT In6 : 1;
//	USHORT In7 : 1;
//	USHORT In8 : 1;
//	USHORT In9 : 1;
//	USHORT In10 : 1;
//	USHORT In11 : 1;
//	USHORT In12 : 1;
//	USHORT In13 : 1;
//	USHORT In14 : 1;
//	USHORT In15 : 1;
//	}Bits;
//} BTCINPUTS;
//
//// INPUTS
//typedef union tagSLICERINPUTS
//{
//	_int16 IOWord;
//	struct {
//	USHORT SafetyEStop : 1;
//	USHORT SlicerDisconnect : 1;
//	USHORT In3 : 1;
//	USHORT TrapKeyStatus : 1;
//	USHORT SlicerBellyEye: 1;
//	USHORT In6 : 1;
//	USHORT BelevatorEstop : 1;
//	USHORT In8 : 1;
//	USHORT ShuntOverTemp1 : 1;
//	USHORT BelevartoPusherBack: 1;
//	USHORT ShuntOverTemp2 : 1;
//	USHORT BelevatorStart : 1;
//	USHORT BelevatorStop : 1;
//	USHORT In14 : 1;
//	USHORT In15 : 1;
//	USHORT In16 : 1;
//	};
//} SLICERINPUTS;
//
////M23->X:$6010C,0,1  // FeedStartStop
////M24->X:$6010C,1,1  // TimingTestActive
////M25->X:$6010C,2,1  // MotorsAtHome
////M26->X:$6010C,3,1  // BellyChuteEyeBlocked
//
//// Status Bits
//typedef union tagBTCSTATUSBITS
//{
//	_int16 IOWord;
//	struct {
//	USHORT FeedStartStop : 1;
//	USHORT TimingTestActive : 1;
//	USHORT MotorsAtHome : 1;
//	USHORT BellyChuteEyeBlocked : 1;
//	USHORT BellyJamInSlicer : 1;
//	USHORT BellyJamInLoader : 1;
//	USHORT BellyPusherStuck : 1;
//	USHORT PaperEyeError : 1;
//	USHORT PaperOut : 1;
//	USHORT ExitVfdRun : 1;
//	USHORT In10 : 1;
//	USHORT In11 : 1;
//	USHORT In12 : 1;
//	USHORT In13 : 1;
//	USHORT In14 : 1;
//	USHORT In15 : 1;
//	};
//} BTCSTATUSBITS;
//
//// Status Bits
//typedef union tagPHASESTATUSBITS
//{
//	_int16 IOWord;
//	struct {
//	USHORT Mtr1 : 1;
//	USHORT Mtr2 : 1;
//	USHORT Mtr3 : 1;
//	USHORT Mtr4 : 1;
//	USHORT Mtr5 : 1;
//	USHORT Mtr6 : 1;
//	USHORT Mtr7 : 1;
//	USHORT Mtr8 : 1;
//	USHORT Mtr9 : 1;
//	USHORT Mtr10 : 1;
//	USHORT Mtr11 : 1;
//	USHORT Mtr12 : 1;
//	USHORT Mtr13 : 1;
//	USHORT Mtr14 : 1;
//	USHORT Mtr15 : 1;
//	USHORT Mtr16 : 1;
//	};
//} PHASESTATUSBITS;
//
//// BTC OUTPUTS
////#define SpareOut0            M33
////#define SpareOut1            M34
////#define SpareOut2            M35
////#define Blower               M36
////#define MasterBusPower       M37
////#define KnifeEngage          M38
////#define BelevatorLight       M39
////#define PaperMarking         M40
//typedef union tagBTCOUTPUTS
//{
//	_int16 IOWord;
//	struct {
//	USHORT SpareOut0 : 1;
//	USHORT SpareOut1 : 1;
//	USHORT SpareOut2 : 1;
//	USHORT Blower : 1;            
//	USHORT MasterBusPower : 1;
//	USHORT KnifeEngage : 1;
//	USHORT BelevatorLight : 1;
//	USHORT PaperMarking : 1;
//	USHORT Padding : 8;
//	};
//} BTCOUTPUTS;
//
//
//// SLICER OUTPUTS
////#define Tamper               M45    // Slave output
////#define BellyPusher          M46    // Slave output
////#define BellyStoper          M47    // Slave output
////#define FeedRollersDown      M48    // Slave output
////#define SlaveBusPower        M49    // Slave output
////#define BladeBrake           M50    // Slave output
////#define FeedNoseDown         M51    // Slave output
////#define TrapKeyRelease       M52    // Slave output
//typedef union tagSLICEROUTPUTS
//{
//	_int16 IOWord;
//	struct {
//	USHORT Tamper : 1;
//	USHORT BellyPusher : 1;
//	USHORT BellyStopper : 1;
//	USHORT FeedRollersDown : 1;
//	USHORT SlaveBusPower : 1;
//	USHORT BladeBreak : 1;
//	USHORT FeedNoseDown : 1;
//	USHORT TrapKeyRelease : 1;
//	USHORT Padding : 8;
//	};
//} SLICEROUTPUTS;
//
//// HALLS
//typedef union tagMOTORHALLS
//{
//	_int16 IOWord;
//	struct {
//	USHORT HallU0 : 1;
//	USHORT HallV0 : 1;
//	USHORT HallW0 : 1;
//	USHORT Therm0 : 1;
//
//	USHORT HallU1 : 1;
//	USHORT HallV1 : 1;
//	USHORT HallW1 : 1;
//	USHORT Therm1 : 1;
//
//	USHORT HallU2 : 1;
//	USHORT HallV2 : 1;
//	USHORT HallW2 : 1;
//	USHORT Therm2 : 1;
//
//	USHORT HallU3 : 1;
//	USHORT HallV3 : 1;
//	USHORT HallW3 : 1;
//	USHORT Therm3 : 1;
//
//	}Bits;
//	struct {
//	USHORT Mtr0 : 4;
//	USHORT Mtr1 : 4;
//	USHORT Mtr2 : 4;
//	USHORT Mtr3 : 4;
//	}UVWT;
//} MOTORHALLS;
//
//// HALLS
//typedef union tagMOTORFLAGS
//{
//	_int16 IOWord;
//	struct {
//	USHORT SafetyAux : 1;
//	USHORT DrumDoor : 1;
//	USHORT PaperDoor : 1;
//	USHORT FlipperPE : 1;
//
//	USHORT AlignHome : 1;
//	USHORT DrumHome : 1;
//	USHORT KnifeHome : 1;
//	USHORT UpperProx2 : 1;
//
//	USHORT LowerProx2 : 1;
//	USHORT FlipperGuard : 1;
//	USHORT PaperWheel : 1;
//	USHORT Therm2 : 1;
//
//	USHORT UpperProx : 1;
//	USHORT LowerProx : 1;
//	USHORT HallW3 : 1;
//	USHORT PaperOut : 1;
//
//	}Bits;
//} MOTORFLAGS;
//
//// HALLS
//typedef union tagSLAVEMOTORFLAGS
//{
//	_int16 IOWord;
//	struct {
//
//	USHORT Flag0 : 1;
//	USHORT Flag1 : 1;
//	USHORT Flag2 : 1;
//	USHORT BladeHome : 1;
//
//	USHORT Flag4 : 1;
//	USHORT BellyDetect : 1;
//	USHORT BellyChuteEye : 1;
//	USHORT BelevatorHome : 1;
//
//	USHORT Flag8 : 1;
//	USHORT Flag9 : 1;
//	USHORT Flag10 : 1;
//	USHORT Flag11 : 1;
//
//	USHORT Flag12 : 1;
//	USHORT Flag13 : 1;
//	USHORT Flag14 : 1;
//	USHORT Flag15 : 1;
//
//	}Bits;
//} SLAVEMOTORFLAGS;
//
//
////M120->X:$078000,16		; HMFL1 flag input status
////M121->X:$078000,17		; PLIM1 flag input status
////M122->X:$078000,18		; MLIM1 flag input status
////M115->X:$078000,19		; USER1 flag input status
////M124->X:$078000,20		; Channel 1 W flag input status
////M125->X:$078000,21		; Channel 1 V flag input status
////M126->X:$078000,22		; Channel 1 U flag input status
////M127->X:$078000,23		; Channel 1 T flag input status
//
//// HALLSFLAGS
//typedef union tagHALLSFLAGS
//{
//	_int16 IOByte;
//	struct {
//	USHORT HMFL1 : 1;
//	USHORT PLIM1 : 1;
//	USHORT MLIM1 : 1;
//	USHORT USER1 : 1;
//	USHORT HallW1 : 1;
//	USHORT HallV1 : 1;
//	USHORT HallU1 : 1;
//	USHORT Therm1 : 1;
//	USHORT HMFL2 : 1;
//	USHORT PLIM2 : 1;
//	USHORT MLIM2 : 1;
//	USHORT USER2 : 1;
//	USHORT HallW2 : 1;
//	USHORT HallV2 : 1;
//	USHORT HallU2 : 1;
//	USHORT Therm2 : 1;
//	};
//	struct {
//	USHORT AllFlags1 : 4;
//	USHORT HallWVUT1 : 4;
//	USHORT AllFlags2 : 4;
//	USHORT HallWVUT2 : 4;
//	};
//} FLAGHALLS;
//
//// Encoder Count errors
//typedef union tagENCCNTERRORS
//{
//	_int32 IOWord;
//	struct {
//	USHORT Byte0 : 8;
//	USHORT Byte1 : 8;
//	USHORT Byte2 : 8;
//	USHORT Byte3 : 8;
//	};
//} ENCCNTERRORS;
//
//// BTC DATA
//typedef struct tagBTCDATA
//{
//	MOTORDATA Mtr1;
//	MOTORDATA Mtr2;
//	MOTORDATA Mtr3;
//	MOTORDATA Mtr4;
//	MOTORDATA Mtr5;
//	MOTORDATA Mtr6;
//	MOTORDATA Mtr7;
//	MOTORDATA Mtr8;
//	MOTORDATA Mtr9;
//	MOTORDATA Mtr10;
//	MOTORDATA Mtr11;
//	MOTORDATA Mtr12;
//	MOTORDATA Mtr13;
//	MOTORDATA Mtr14;
//	MOTORDATA Mtr15;
//	MOTORDATA Mtr16;
//	float  PeakCurrentMotor1;
//	float  PeakCurrentMotor2;
//	float  PeakCurrentMotor3;
//	float  PeakCurrentMotor4;
//	float  PeakCurrentMotor5;
//	float  PeakCurrentMotor6;
//	float  PeakCurrentMotor7;
//	float  PeakCurrentMotor8;
//	float  CurrentMotor1;
//	float  CurrentMotor2;
//	float  CurrentMotor3;
//	float  CurrentMotor4;
//	float  CurrentMotor5;
//	float  CurrentMotor6;
//	float  CurrentMotor7;
//	float  CurrentMotor8;
//	_int16 MaxFE1; 
//	_int16 MaxFE2;
//	_int16 MaxFE3;
//	_int16 MaxFE4;
//	_int16 MaxFE5;
//	_int16 MaxFE6;
//	_int16 MaxFE7;
//	_int16 MaxFE8;
//	_int16 MaxFE9;
//	_int16 MaxFE10;
//	_int16 MaxFE11;
//	_int16 MaxFE12;
//	_int16 MaxFE13;
//	_int16 MaxFE14;
//	_int16 MaxFE15;
//	_int16 MaxFE16;
//	_int16 GlobalStatus;
//	_int16 BtcMode;
//	FLAGHALLS Mtr1Mtr2FlagsHalls;
//	FLAGHALLS Mtr3Mtr4FlagsHalls;
//	FLAGHALLS Mtr5Mtr6FlagsHalls;
//	FLAGHALLS Mtr7Mtr8FlagsHalls;
//	BTCINPUTS  BtcInputs;
//	SLICERINPUTS  SlicerInputs;	
//	BTCOUTPUTS BtcOutputs;
//	SLICEROUTPUTS SlicerOutputs;
//	FLAGHALLS Mtr9Mtr10FlagsHalls;
//	FLAGHALLS Mtr11Mtr12FlagsHalls;
//	FLAGHALLS Mtr13Mtr14FlagsHalls;
//	FLAGHALLS Mtr15Mtr16FlagsHalls;
//	float  PeakCurrentMotor9;
//	float  PeakCurrentMotor10;
//	float  PeakCurrentMotor11;
//	float  PeakCurrentMotor12;
//	float  PeakCurrentMotor13;
//	float  PeakCurrentMotor14;
//	float  PeakCurrentMotor15;
//	float  PeakCurrentMotor16;
//	float  CurrentMotor9;
//	float  CurrentMotor10;
//	float  CurrentMotor11;
//	float  CurrentMotor12;
//	float  CurrentMotor13;
//	float  CurrentMotor14;
//	float  CurrentMotor15;
//	float  CurrentMotor16;
//	_int16 SlicerGlobalStatus;
//	BTCSTATUSBITS StatusBits;
//	_int16 ComTicks;
//	_int16 DataPeriod;
//	float  PaperRollSize;
//	_int32 SheetCount;
//	_int32 SheetCountShift;
//	_int32 TotalSheetCount;
//	PHASESTATUSBITS MtrPhaseStatus;
//	_int16 BaconSpeed_NOTUSED;
//	unsigned char BusVoltage1;
//	unsigned char BusVoltage2;
//	unsigned char BusVoltage3;
//	unsigned char BusVoltage4_NOTUSED;
//	float  IGBTTemp;
//	_int16 ExitVfdSpeedInPerSec;	
//	_int16 RejectVfdSpeedInPerSec;	
//	ENCCNTERRORS EncCntErrorsMtr1to4;	
//	ENCCNTERRORS EncCntErrorsMtr5to8;	
//	ENCCNTERRORS EncCntErrorsMtr9to12;	
//	ENCCNTERRORS EncCntErrorsMtr13to16;	
//} BTCDATA;
//
////// Slicer DATA
////typedef struct tagSLICERDATA
////{
////	float  PeakCurrentMotor1;
////	float  PeakCurrentMotor2;
////	float  PeakCurrentMotor3;
////	float  PeakCurrentMotor4;
////	float  PeakCurrentMotor5;
////	float  PeakCurrentMotor6;
////	float  CurrentMotor1;
////	float  CurrentMotor2;
////	float  CurrentMotor3;
////	float  CurrentMotor4;
////	float  CurrentMotor5;
////	float  CurrentMotor6;
////} SLICERDATA;
//
//#define COMM_EOT          0x80000000    // An acknowledge character (ACK ASCII 9) was received indicating end of transmission from PMAC to Host PC.
//#define COMM_TIMEOUT      0xC0000000    // A timeout occurred. The time for the PC to wait for PMAC to respond had been exceeded.
//#define COMM_BADCKSUM     0xD0000000    // Used when using Checksum communication. If a bad checksum occurred this error will be returned.
//#define COMM_ERROR        0xE0000000    // Unable to communicate.
//#define COMM_FAIL         0xF0000000    // Serious failure.
//#define COMM_ANYERR       0x70000000    // Some error occurred.
//#define COMM_UNSOLICITED  0x10000000    // An unsolicited response has been received from PMAC. Usually caused by PLC’s or Motion Programs that have “SEND” or “COMMAND” statements.
//
////To check for individual error codes the MACROs below are very useful:
//#define IS_COMM_MORE(c) ((c & COMM_FAIL) == 0)
//#define IS_COMM_EOT(c) ((c & COMM_FAIL) == COMM_EOT)
//#define IS_COMM_TIMEOUT(c) ((c & COMM_FAIL) == COMM_TIMEOUT)
//#define IS_COMM_BADCKSUM(c) ((c & COMM_FAIL) == COMM_BADCKSUM)
//#define IS_COMM_ERROR(c) ((c & COMM_FAIL) == COMM_ERROR)
//#define IS_COMM_FAIL(c) ((c & COMM_FAIL) == COMM_FAIL)
//#define IS_COMM_ANYERROR(c) ((c & COMM_ANYERR) > 0)
//#define IS_COMM_UNSOLICITED(c) ((c & COMM_UNSOLICITED) == COMM_UNSOLICITED)
//
//#define COMM_CHARS(c) (c & 0x0FFFFFFF) // Returns the number of characters
//#define COMM_STATUS(c) (c & 0xF0000000) // Returns the status byte
//
//
//class CPmacDeviceEvents : public CCmdTarget
//{
//	DECLARE_DYNCREATE(CPmacDeviceEvents)
//
//// Operations
//public:
//	CPmacDeviceEvents();           // protected constructor used by dynamic creation
//	virtual ~CPmacDeviceEvents();
//
//// Attributes
//public:
//	HWND m_hWnd;
//	UINT m_msgProgress;
//	UINT m_msgDownloadMessage;
//	UINT m_msgError;
//	UINT m_msgInterrupt;
//	UINT m_msgUnSolicited;
//	UINT m_msgDataReady;
//	CProgressCtrl* m_pProgress;
//	CEdit* m_pMessage;
//
//// Operations
//public:
//
//// Overrides
//	// ClassWizard generated virtual function overrides
//	//{{AFX_VIRTUAL(CPmacDeviceEvents)
//	public:
//	virtual void OnFinalRelease();
//	//}}AFX_VIRTUAL
//
//// Implementation
////protected:
////	virtual ~CPmacDeviceEvents();
//
//	// Generated message map functions
//	//{{AFX_MSG(CPmacDeviceEvents)
//		// NOTE - the ClassWizard will add and remove member functions here.
//	//}}AFX_MSG
//
//	DECLARE_MESSAGE_MAP()
//	// Generated OLE dispatch map functions
//	//{{AFX_DISPATCH(CPmacDeviceEvents)
//		// NOTE - the ClassWizard will add and remove member functions here.
//	//}}AFX_DISPATCH
//    afx_msg void OnProgress(long Device,long dwPercent);
//    afx_msg void OnMessage(long Device,LPCTSTR Msg,BOOL bNewLine);
//    afx_msg void OnError(long Device,LPCTSTR FileName,long ErrorID,long LineNum,LPCTSTR Line);
//    afx_msg void OnInterrupt(long Device,long dwLevel);
//	afx_msg void OnUnSolicited(long lDevice,LPCTSTR Msg);
//    afx_msg void OnDataReady(long lDevice);
//	DECLARE_DISPATCH_MAP()
//	DECLARE_INTERFACE_MAP()
//};
//
////
//// PMAC communications class
//class CPmac
//{
//public:
//	CPmac(void);
//	~CPmac(void);
//	bool Init(long dwDevice);
//
//public:
//    IPmacDevice *pmac;
//	double		m_I10;
//	double		m_ServoFrequency;
//	VARIANT_BOOL		m_DPRamPresent;
//	CPmacDeviceEvents	m_pmacdeviceEvents;
//
//private:
//	LPUNKNOWN			m_pUnkSink;
//	DWORD				m_dwCookie;
//	CPmacDevice			m_pmacdevice;
//  	HRESULT				m_hResult;             // Used for interface calls
//	long				m_dwDevice;
//	VARIANT_BOOL		m_bDeviceOpen;
//    LPUNKNOWN			m_pDisp;
//	//CPmacDeviceEvents	PmacDeviceEvents;
//
//public:
//	void SetDownloadMsgPtr(CEdit* pWnd);
//	void SetProgressMsgPtr(CProgressCtrl* pWnd);
//	void SetPmacMsgWnd(HWND hWnd);
//	void SelectPmac();
//	bool Upload(LPCTSTR lpsz);
//	bool Download(LPCTSTR lpsz);
//	int Reset(LPCTSTR lpszCmd,BOOL AsciiRingCom);
//	int Save(LPCTSTR lpszCmd);
//	int SendCommand(LPCTSTR lpszCmd);
//	int GetResponse(LPCTSTR lpszCmd,BSTR *response);
//	int IsPmacOpen();
//	VARIANT_BOOL GetVariable(char ch,long num,long* Data);
//	VARIANT_BOOL GetVariable(char ch,long num,double* Data);
//	VARIANT_BOOL SetVariable(char ch,long num,long Data);
//	VARIANT_BOOL SetVariable(char ch,long num,double Data);
//	VARIANT_BOOL DPRGet(int Offset, short * Data);
//	VARIANT_BOOL DPRGet(int Offset, long * Data);
//	VARIANT_BOOL DPRSet(int Offset, short Data);
//	VARIANT_BOOL DPRSet(int Offset, long Data);
//	VARIANT_BOOL DPRGetMem(int Offset,int NumBytes, VARIANT *Data);
//	VARIANT_BOOL DPRSetMem(int Offset,int NumBytes, VARIANT *Data);
//	double DPRFloat(long long d,double scale);
//	double DPRFixed( long d[], double scale );
//	double GetCommandedPos(int MtrNum,double scale);
//	double GetFollowError(int MtrNum,double scale);
//	double GetVelocity(int MtrNum,double scale);
//	double GetMotorPosition(int MtrNum,double scale);
//
//};
//
