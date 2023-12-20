/******************************************************************************/
/*
 * File name: MultiCamera.cpp
 * Location:  ...\Matrox Imaging\MILxxx\Examples\BoardSpecific\gigevision\C++\multicamera
 *             
 *
 * Synopsis:  This program detects the number of cameras attached
 *            to a mtxgige system, prints camera vendor information
 *            and starts grabbing from all cameras found using
 *            MdigProcess. It also handles camera removal and addition.
 */


#include <mil.h>
#if M_MIL_USE_WINDOWS
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#endif

#ifndef M_GC_PAYLOAD_SIZE
#define M_GC_PAYLOAD_SIZE  5197L
#endif

#define WINDOW_TITLE          MIL_TEXT("Camera: ")
#define MAX_CAM               32
#define MAX_ADAPTERS          16
#define BUFFERING_SIZE_MAX    3
#define STRING_LENGTH_MAX     128
#define STRING_POS_X          20
#define STRING_POS_Y          20
#define STATS_PRINT_PERIOD    1000
#define USE_FEATURE_BROWSER   0

/* User's processing function and camera detect hook data structure. */
typedef struct
   {
   MIL_ID MilSystem;
   MIL_ID MilDigitizer;
   MIL_ID MilDisplay;
   MIL_ID MilImageDisp;
   MIL_ID MilGrabBufferList[BUFFERING_SIZE_MAX];
   MIL_INT MilGrabBufferListSize;
   MIL_INT ProcessedImageCount;
   MIL_DOUBLE FrameRate;
   MIL_INT ResendRequests;
   MIL_INT PacketSize;
   MIL_INT PacketsMissed;
   MIL_INT CorruptImageCount;
   MIL_INT GrabInProgress;
   MIL_INT PayloadSize;
   MIL_TEXT_PTR CamVendor;
   MIL_TEXT_PTR CamModel;
   MIL_TEXT_PTR CamUniqueId;
   MIL_TEXT_PTR pAdapterName;
   bool IsConnected;
   MIL_INT BoardType;
   } DigHookDataStruct;

/* User's system camera detect hook data structure. */
#define MAX_ADAPTER_DESCRIPTION_LENGTH  512
typedef struct
   {
   MIL_ID MilSystem;
   MIL_INT NbCameras;
   DigHookDataStruct* DigHookDataStrutPtr;
   bool PrintAdapterInfo;
   MIL_TEXT_CHAR Adapters[MAX_ADAPTERS][MAX_ADAPTER_DESCRIPTION_LENGTH + 4];
   MIL_INT BoardType;
   } SysHookDataStruct;

/* User's processing and camera detect hook functions. */
MIL_INT MFTYPE ProcessingFunction(MIL_INT HookType,
   MIL_ID HookId,
   void* HookDataPtr);
MIL_INT MFTYPE CamPresentFunction(MIL_INT HookType,
   MIL_ID HookId,
   void* HookDataPtr);

/* Digitizer allocation and acquisition routines.
   Used to make the example more compact. */
void DigAllocResources(MIL_ID MilSystem, MIL_INT DeviceNum,
   DigHookDataStruct* UserSt,
   bool PrintErrors = true);
void DigFreeResources(DigHookDataStruct* UserSt);
void DigStartAcquisition(DigHookDataStruct* UserSt);
void DigStopAcquisition(DigHookDataStruct* UserSt);
void PrintCameraInfo(SysHookDataStruct* UserSt);
void AddAdapterToList(SysHookDataStruct* UserSt, MIL_TEXT_PTR AdapterName);

int MosMain(void)
   {
   MIL_ID MilApplication,
      MilSystem;
   MIL_INT BoardType,
      DevNb,
      Done = M_FALSE,
      ProcessFrameCount = 0,
      MaxCam = MAX_CAM;
   MIL_DOUBLE ProcessFrameRate = 0.0;
   SysHookDataStruct SysUserHookData;
   DigHookDataStruct DigUserHookData[MAX_CAM];
   memset(&SysUserHookData, 0, sizeof(SysUserHookData));
   memset(DigUserHookData, 0, sizeof(DigHookDataStruct)*MAX_CAM);

   /* Allocate defaults. */
   MappAllocDefault(M_DEFAULT, &MilApplication, &MilSystem, M_NULL, M_NULL, M_NULL);

   MsysInquire(MilSystem, M_BOARD_TYPE, &BoardType);

   SysUserHookData.MilSystem = MilSystem;
   SysUserHookData.NbCameras = 0;
   SysUserHookData.DigHookDataStrutPtr = DigUserHookData;
   SysUserHookData.BoardType = BoardType;

   if (((BoardType & M_BOARD_TYPE_MASK) != M_GIGE_VISION) &&
      ((BoardType & M_BOARD_TYPE_MASK) != M_USB3_VISION))
      {
      MosPrintf(MIL_TEXT("This example requires a M_GIGE_VISION or M_USB3_VISION system type.\n"));
      MosPrintf(MIL_TEXT("Please change system type in milconfig.\n"));
      MappFreeDefault(MilApplication, MilSystem, M_NULL, M_NULL, M_NULL);
      MosGetch();
      return -1;
      }

   /* Inquire the number of cameras attached. */
   MsysInquire(MilSystem, M_NUM_CAMERA_PRESENT, &SysUserHookData.NbCameras);
   if (SysUserHookData.NbCameras > MaxCam)
      SysUserHookData.NbCameras = MaxCam;

   /* Allocate and start acquisition on all cameras found at MsysAlloc time. */
   if (SysUserHookData.NbCameras)
      {
      MIL_INT CamerasAllocated = M_FALSE;
      /* Allocate digitizers and other resources. */
      for (DevNb = M_DEV0; DevNb < MAX_CAM; DevNb++)
         {
         DigUserHookData[DevNb].BoardType = BoardType;
         DigAllocResources(MilSystem, DevNb, &DigUserHookData[DevNb], false);
         if (DigUserHookData[DevNb].MilDigitizer)
            {
            CamerasAllocated = M_TRUE;
            if ((BoardType & M_BOARD_TYPE_MASK) == M_GIGE_VISION)
               {
               AddAdapterToList(&SysUserHookData, DigUserHookData[DevNb].pAdapterName);
               }
            }
         }

      if (CamerasAllocated == M_TRUE)
         {
         /* Start acquisition. */
         for (DevNb = M_DEV0; DevNb < MAX_CAM; DevNb++)
            DigStartAcquisition(&DigUserHookData[DevNb]);
         }
      else
         {
         /* Cameras might already be allocated by another process on this or */
         /* another PC. Do a license check to determine if allocation        */
         /* failure was caused by lack of proper license.                    */

         MIL_ID MilRemoteApplication = M_NULL;
         MIL_INT LicenseModules = 0;
         MsysInquire(MilSystem, M_OWNER_APPLICATION, &MilRemoteApplication);

         MappInquire(MilRemoteApplication, M_LICENSE_MODULES, &LicenseModules);
         if (!(LicenseModules & (M_LICENSE_INTERFACE)))
            {
            MosPrintf(MIL_TEXT("Need a GigE Vision license to run this example.\n"));
            MosPrintf(MIL_TEXT("Press <Enter> to end.\n"));
            MosGetch();

            MappFreeDefault(MilApplication, MilSystem, M_NULL, M_NULL, M_NULL);
            return 0;
            }
         }
      }

   /* Register a hook function to the system's camera present event. */
   /* Used to:                                                        */
   /* 1- Allocate and start acquisition on a newly attached camera.   */
   /* 2- Stop acquisition on a camera that has been removed.          */
   /* 3- Resume acquisition on a camera that has been re-connected.   */
   SysHookDataStruct SysUserHookData;

   MsysHookFunction(MilSystem, M_CAMERA_PRESENT, CamPresentFunction, &SysUserHookData);

   /* At this point digitizers have been allocated and acquisition started on all      */
   /* cameras found at MsysAlloc time (if any). The example now waits for the user to  */
   /* add / remove cameras to the system. The camera present hook will then get called */
   /* and everything will get handled from there.                                      */

   while (!MosKbhit())
      PrintCameraInfo(&SysUserHookData);

   MosGetch();

   /* The user is stopping the example, stop acquisition and free everything. */
   for (DevNb = M_DEV0; DevNb < MAX_CAM; DevNb++)
      DigStopAcquisition(&DigUserHookData[DevNb]);

   PrintCameraInfo(&SysUserHookData);

   MosPrintf(MIL_TEXT("\nFreeing:\n"));
   for (DevNb = M_DEV0; DevNb < MAX_CAM; DevNb++)
      DigFreeResources(&DigUserHookData[DevNb]);

   MsysHookFunction(MilSystem, M_CAMERA_PRESENT + M_UNHOOK, CamPresentFunction,
      &SysUserHookData);
   MsysFree(MilSystem);
   MappFree(MilApplication);

   return 0;
   }

/* User's processing function called every time a grab buffer is modified. */
/* ----------------------------------------------------------------------- */

MIL_INT MFTYPE ProcessingFunction(MIL_INT HookType,
   MIL_ID HookId,
   void* HookDataPtr)
   {
   DigHookDataStruct *UserHookDataPtr = (DigHookDataStruct *)HookDataPtr;
   MIL_ID ModifiedBufferId = 0;
   MIL_INT ResendRequests = 0, PacketsMissed = 0, IsCorrupt = 0;

   /* Retrieve the MIL_ID of the grabbed buffer and camera statistics. */
   MdigGetHookInfo(HookId, M_MODIFIED_BUFFER + M_BUFFER_ID, &ModifiedBufferId);
   MdigGetHookInfo(HookId, M_CORRUPTED_FRAME, &IsCorrupt);
   if ((UserHookDataPtr->BoardType & M_BOARD_TYPE_MASK) == M_GIGE_VISION)
      {
      MdigGetHookInfo(HookId, M_GC_PACKETS_RESENDS_NUM, &ResendRequests);
      MdigGetHookInfo(HookId, M_GC_PACKETS_MISSED, &PacketsMissed);
      }

   UserHookDataPtr->ResendRequests += ResendRequests;
   UserHookDataPtr->PacketsMissed += PacketsMissed;

   /* Copy the grabbed frame to display. */
   if (IsCorrupt)
      UserHookDataPtr->CorruptImageCount++;
   else
      {
      UserHookDataPtr->ProcessedImageCount++;
      MbufCopy(ModifiedBufferId, UserHookDataPtr->MilImageDisp);
      }

   return 0;
   }

/* User's camera present function called every time a camera connection state */
/* changes.                                                                   */
/* -------------------------------------------------------------------------- */

MIL_INT MFTYPE CamPresentFunction(MIL_INT HookType,
   MIL_ID HookId,
   void* HookDataPtr)
   {
   SysHookDataStruct *UserHookDataPtr = (SysHookDataStruct *)HookDataPtr;
   MIL_INT IsCamPresent, Number;

   /* Inquire the camera present state (present or not present). */
   MsysGetHookInfo(UserHookDataPtr->MilSystem, HookId, M_CAMERA_PRESENT, &IsCamPresent);
   /* Inquire the camera's digitizer device number . */
   MsysGetHookInfo(UserHookDataPtr->MilSystem, HookId, M_NUMBER, &Number);
   /* Update the number of camera present variable. */
   MsysInquire(UserHookDataPtr->MilSystem, M_NUM_CAMERA_PRESENT,
      &UserHookDataPtr->NbCameras);

   if (IsCamPresent)
      {
      MIL_TEXT_CHAR* UniqueId = NULL;
      MIL_INT Size = 0;

      /* Inquire the camera's Unique Id. */
      MsysGetHookInfo(UserHookDataPtr->MilSystem, HookId, M_GC_UNIQUE_ID_STRING_SIZE,
         &Size);
      UniqueId = new MIL_TEXT_CHAR[Size];
      MsysGetHookInfo(UserHookDataPtr->MilSystem, HookId, M_GC_UNIQUE_ID_STRING,
         UniqueId);

      /* Camera is present. */
      if (UserHookDataPtr->DigHookDataStrutPtr[Number].MilDigitizer == 0)
         {
         /* Newly attached camera; allocate it. */
         DigAllocResources(UserHookDataPtr->MilSystem, Number,
            &UserHookDataPtr->DigHookDataStrutPtr[Number]);
         }
      else if (MosStrcmp(UserHookDataPtr->DigHookDataStrutPtr[Number].CamUniqueId,
         UniqueId) != 0)
         {
         /* New camera added in place of another one, free old dig */
         DigFreeResources(&UserHookDataPtr->DigHookDataStrutPtr[Number]);

         /* Find out if camera was previously allocated on a different device number. */
         for (MIL_INT i = 0; i < MAX_CAM; i++)
         if ((i != Number) &&
            (MosStrcmp(UserHookDataPtr->DigHookDataStrutPtr[Number].CamUniqueId,
            UniqueId) == 0))
            DigFreeResources(&UserHookDataPtr->DigHookDataStrutPtr[i]);

         /* Allocate resources. */
         DigAllocResources(UserHookDataPtr->MilSystem, Number,
            &UserHookDataPtr->DigHookDataStrutPtr[Number]);
         }

      if (UserHookDataPtr->DigHookDataStrutPtr[Number].MilDigitizer)
         {
         if ((UserHookDataPtr->BoardType & M_BOARD_TYPE_MASK) == M_GIGE_VISION)
            AddAdapterToList(UserHookDataPtr,
            UserHookDataPtr->DigHookDataStrutPtr[Number].pAdapterName);
         }
      UserHookDataPtr->DigHookDataStrutPtr[Number].IsConnected = true;
      /* Start acquisition. */
      DigStartAcquisition(&UserHookDataPtr->DigHookDataStrutPtr[Number]);

      delete[] UniqueId;
      }
   else
      {
      /* Camera is not present. */
      if (UserHookDataPtr->DigHookDataStrutPtr[Number].MilDigitizer)
         {
         /* Stop acquisition. */
         DigStopAcquisition(&UserHookDataPtr->DigHookDataStrutPtr[Number]);
         }

      UserHookDataPtr->DigHookDataStrutPtr[Number].IsConnected = false;
      }

   return 0;
   }

void DigAllocGigEVisionResources(DigHookDataStruct* UserSt, bool PrintErrors)
   {
   MIL_INT Len = 0;
   MdigInquire(UserSt->MilDigitizer, M_GC_PACKET_SIZE, &UserSt->PacketSize);
   MdigInquire(UserSt->MilDigitizer, M_GC_INTERFACE_NAME_SIZE, &Len);
   if (Len)
      {
      UserSt->pAdapterName = new MIL_TEXT_CHAR[Len];
      MdigInquire(UserSt->MilDigitizer, M_GC_INTERFACE_NAME, UserSt->pAdapterName);
      }
   }

/* Allocates digitizer plus all other resources needed for image acquisition and */
/* camera state changes.                                                         */
/* ------------------------------------------------------------------------------*/

void DigAllocResources(MIL_ID MilSystem, MIL_INT DeviceNum, DigHookDataStruct* UserSt,
   bool PrintErrors)
   {
   MIL_INT VendorStLen, ModelStLen, UniqueIdLen;
   MIL_INT SizeBand = 0, BufType = 0;
   MIL_INT64 BufFormat = 0;

   /* In cases where the preferred method for device allocation requires allocating with     */
   /* a user-defined name the following code can be used. "MyCameraName" must be replaced    */
   /* with the actual camera name written in the camera.                                     */

   /* MIL_TEXT_CHAR MyCameraName[64] = {'\0'};                                               */

   /* MosSprintf(MyCameraName, 64, MIL_TEXT("MyCameraName%d"), DeviceNum);                   */
   /* MdigAlloc(MilSystem, M_GC_CAMERA_ID(MIL_TEXT("MyCameraName")), MIL_TEXT("M_DEFAULT"),  */
   /*    M_GC_DEVICE_USER_NAME, &MilDigitizer);                                              */

   if (PrintErrors)
      MdigAlloc(MilSystem, DeviceNum, MIL_TEXT("M_DEFAULT"), M_DEV_NUMBER,
      &UserSt->MilDigitizer);
   else
      {
      MappControl(M_DEFAULT, M_ERROR, M_PRINT_DISABLE);
      MdigAlloc(MilSystem, DeviceNum, MIL_TEXT("M_DEFAULT"), M_DEV_NUMBER,
         &UserSt->MilDigitizer);
      MappControl(M_DEFAULT, M_ERROR, M_PRINT_ENABLE);
      }

   if (UserSt->MilDigitizer)
      {
      MIL_INT Len = 0;
      UserSt->MilSystem = MilSystem;
      UserSt->IsConnected = true;

      /* Disable MdigProcess grab monitor since disconnecting a camera will result in an  */
      /* error message.                                                                   */
      MdigControl(UserSt->MilDigitizer, M_PROCESS_GRAB_MONITOR, M_DISABLE);
      /* Disable corrupted frame errors as they are handled from the MdigProcess hook     */
      /* function.                                                                        */
      MdigControl(UserSt->MilDigitizer, M_CORRUPTED_FRAME_ERROR, M_DISABLE);

      /* Inquire information related to the camera being allocated. */
      MdigInquire(UserSt->MilDigitizer, M_CAMERA_VENDOR_SIZE, &VendorStLen);
      MdigInquire(UserSt->MilDigitizer, M_CAMERA_MODEL_SIZE, &ModelStLen);

      UserSt->CamVendor = new MIL_TEXT_CHAR[VendorStLen];
      UserSt->CamModel = new MIL_TEXT_CHAR[ModelStLen];

      MdigInquire(UserSt->MilDigitizer, M_CAMERA_VENDOR, UserSt->CamVendor);
      MdigInquire(UserSt->MilDigitizer, M_CAMERA_MODEL, UserSt->CamModel);

      MdigInquire(UserSt->MilDigitizer, M_GC_UNIQUE_ID_STRING_SIZE, &UniqueIdLen);
      UserSt->CamUniqueId = new MIL_TEXT_CHAR[UniqueIdLen];
      MdigInquire(UserSt->MilDigitizer, M_GC_UNIQUE_ID_STRING, UserSt->CamUniqueId);

      if ((UserSt->BoardType & M_BOARD_TYPE_MASK) == M_GIGE_VISION)
         DigAllocGigEVisionResources(UserSt, PrintErrors);

      /* Pop-up the MIL feature browser; exposes GigE device features.                */
#if (USE_FEATURE_BROWSER == 1)
      MdigControl(UserSt->MilDigitizer, M_GC_FEATURE_BROWSER, M_OPEN + M_ASYNCHRONOUS);
#endif

      /* Allocate displays and buffers; everything necessary to run MdigProcess. */
      MdispAlloc(MilSystem, M_DEFAULT, MIL_TEXT("M_DEFAULT"), M_DEFAULT,
         &UserSt->MilDisplay);
      MdispControl(UserSt->MilDisplay, M_TITLE,
         M_PTR_TO_DOUBLE(UserSt->CamModel));

      /* Allocate a buffer format that matches the camera's pixel format. */
      MdigInquire(UserSt->MilDigitizer, M_SIZE_BAND, &SizeBand);
      MdigInquire(UserSt->MilDigitizer, M_TYPE, &BufType);
      MdigInquire(UserSt->MilDigitizer, M_SOURCE_DATA_FORMAT, &BufFormat);

      MbufAllocColor(MilSystem,
         SizeBand,
         MdigInquire(UserSt->MilDigitizer, M_SIZE_X, M_NULL),
         MdigInquire(UserSt->MilDigitizer, M_SIZE_Y, M_NULL),
         BufType,
         M_IMAGE + M_GRAB + M_DISP + BufFormat,
         &UserSt->MilImageDisp);

      MbufClear(UserSt->MilImageDisp, M_COLOR_BLACK);
      MdispSelect(UserSt->MilDisplay, UserSt->MilImageDisp);

      for (MIL_INT i = 0; i < BUFFERING_SIZE_MAX; i++)
         {
         MbufAllocColor(MilSystem,
            SizeBand,
            MdigInquire(UserSt->MilDigitizer, M_SIZE_X, M_NULL),
            MdigInquire(UserSt->MilDigitizer, M_SIZE_Y, M_NULL),
            BufType,
            M_GRAB + M_IMAGE + BufFormat,
            &UserSt->MilGrabBufferList[i]);
         if (UserSt->MilGrabBufferList[i])
            {
            UserSt->MilGrabBufferListSize++;
            MbufClear(UserSt->MilGrabBufferList[i], 0);
            }
         }
      }
   }

/* Free digitizer and all other resources allocated.  */
/* -------------------------------------------------- */

void DigFreeResources(DigHookDataStruct* UserSt)
   {
   if (UserSt->MilDigitizer)
      {
      for (MIL_INT i = 0; i < UserSt->MilGrabBufferListSize; i++)
         MbufFree(UserSt->MilGrabBufferList[i]);

      MbufFree(UserSt->MilImageDisp);
      MdispFree(UserSt->MilDisplay);

#if (USE_FEATURE_BROWSER == 1)
      /* Close the MIL feature browser; exposes GigE device features.                */
      MdigControl(UserSt->MilDigitizer, M_GC_FEATURE_BROWSER, M_CLOSE);
#endif

      MdigFree(UserSt->MilDigitizer);

      delete[] UserSt->CamVendor;
      delete[] UserSt->CamModel;
      delete[] UserSt->CamUniqueId;
      delete[] UserSt->pAdapterName;
      memset(UserSt, 0, sizeof(DigHookDataStruct));
      }
   }

/* Starts MdigProcess. */
/* ------------------- */

void DigStartAcquisition(DigHookDataStruct* UserSt)
   {
   if (UserSt->MilDigitizer)
      {
      UserSt->GrabInProgress = M_TRUE;
      MdigProcess(UserSt->MilDigitizer, UserSt->MilGrabBufferList,
         UserSt->MilGrabBufferListSize, M_START, M_DEFAULT,
         ProcessingFunction, UserSt);

      MdigInquire(UserSt->MilDigitizer, M_GC_PAYLOAD_SIZE, &UserSt->PayloadSize);
      }
   }

/* Stops MdigProcess. */
/* ------------------ */

void DigStopAcquisition(DigHookDataStruct* UserSt)
   {
   if (UserSt->GrabInProgress)
      {
      MdigProcess(UserSt->MilDigitizer, UserSt->MilGrabBufferList,
         UserSt->MilGrabBufferListSize, M_STOP, M_DEFAULT,
         ProcessingFunction, UserSt);
      UserSt->GrabInProgress = M_FALSE;
      }
   }

/* Print camera state information. */
/* ------------------ */
void PrintCameraInfo(SysHookDataStruct* UserSt)
   {
   if (UserSt->NbCameras)
      {
      MIL_TEXT_CHAR Str[] = MIL_TEXT("                           ");
      MosSleep(STATS_PRINT_PERIOD);
#if M_MIL_USE_WINDOWS
      system("cls");
#endif
      MosPrintf(MIL_TEXT("This example shows how to handle camera connect / ")
         MIL_TEXT("disconnect events.\n\n"));
      MosPrintf(MIL_TEXT("%d camera%s detected.\n"), UserSt->NbCameras,
         UserSt->NbCameras > 1 ? MIL_TEXT("s") : MIL_TEXT(""));
      MosPrintf(MIL_TEXT("You can proceed to add / remove cameras to your ")
         MIL_TEXT("system at anytime.\n\n"));
      MosPrintf(MIL_TEXT("%s----------------------------------------------------\n"), Str);
      MosPrintf(MIL_TEXT("%s                  Camera statistics                 \n"), Str);
      MosPrintf(MIL_TEXT("%s-------------------------------------+--------------\n"), Str);
      MosPrintf(MIL_TEXT("%s                Frame                |    Packet    \n"), Str);
      MosPrintf(MIL_TEXT("%s-------------------------------------+--------------\n"), Str);
      MosPrintf(MIL_TEXT("%-14s%-13s%9s%8s%11s%8s%8s%8s\n"), MIL_TEXT("Model"),
         MIL_TEXT("State"), MIL_TEXT("Grabbed"), MIL_TEXT("Rate"),
         MIL_TEXT("Bandwidth"), MIL_TEXT("Corrupt"), MIL_TEXT("|  Size"),
         MIL_TEXT("Resends"));
      MosPrintf(MIL_TEXT("----------------------------")
         MIL_TEXT("------------------------------------+--------------\n"));

      for (MIL_INT i = 0; i < MAX_CAM; i++)
         {
         if (UserSt->DigHookDataStrutPtr[i].MilDigitizer)
            {
            DigHookDataStruct* DigStPtr = &UserSt->DigHookDataStrutPtr[i];

            if (DigStPtr->IsConnected)
               MdigInquire(DigStPtr->MilDigitizer, M_PROCESS_FRAME_RATE, &DigStPtr->FrameRate);
            else
               DigStPtr->FrameRate = 0;

            MosPrintf(MIL_TEXT("%-14.13s%-13.12s%9d%8.1f%11.1f%8d%8d%8d\n"),
               DigStPtr->CamModel,
               DigStPtr->IsConnected ? MIL_TEXT("Connected") : MIL_TEXT("Disconnected"),
               DigStPtr->ProcessedImageCount,
               DigStPtr->FrameRate,
               (DigStPtr->PayloadSize*DigStPtr->FrameRate / 1e6),
               DigStPtr->CorruptImageCount,
               DigStPtr->PacketSize,
               DigStPtr->ResendRequests);
            }
         }

      MosPrintf(MIL_TEXT("----------------------------")
         MIL_TEXT("---------------------------------------------------\n\n"));

      if ((UserSt->BoardType & M_BOARD_TYPE_MASK) == M_GIGE_VISION)
         {
         MosPrintf(MIL_TEXT("Network adapter statistics\n\n"));
         MIL_DOUBLE AdapterBandwidth = 0;
         for (MIL_INT i = 0; i < MAX_ADAPTERS; i++)
            {
            AdapterBandwidth = 0;
            if (UserSt->Adapters[i][0] != '\0')
               {
               DigHookDataStruct* DigStPtr = NULL;
               for (MIL_INT j = 0; j < MAX_CAM; j++)
                  {
                  DigStPtr = &(UserSt->DigHookDataStrutPtr[j]);
                  if (DigStPtr->MilDigitizer &&
                     MosStrcmp(DigStPtr->pAdapterName, UserSt->Adapters[i]) == 0)
                     {
                     AdapterBandwidth += (DigStPtr->PayloadSize*DigStPtr->FrameRate / 1e6);
                     }
                  }

               MosPrintf(MIL_TEXT("\n%-50.49s%.1f (MB/s) connected to:\n"), UserSt->Adapters[i],
                  AdapterBandwidth);
               MosPrintf(MIL_TEXT("----------------------------")
                  MIL_TEXT("---------------------------------------------------\n"));

               for (MIL_INT j = 0; j < MAX_CAM; j++)
                  {
                  DigStPtr = &(UserSt->DigHookDataStrutPtr[j]);
                  if (DigStPtr->MilDigitizer &&
                     MosStrcmp(DigStPtr->pAdapterName, UserSt->Adapters[i]) == 0)
                     MosPrintf(MIL_TEXT("%s %s\n"), DigStPtr->CamVendor, DigStPtr->CamModel);
                  }
               }
            }
         }
      }
   else
      {
#if M_MIL_USE_WINDOWS
      system("cls");
#endif
      MosPrintf(MIL_TEXT("This example shows how to handle camera connect / ")
         MIL_TEXT("disconnect events.\n\n"));
      MosPrintf(MIL_TEXT("%d camera detected.\n"), UserSt->NbCameras);
      MosPrintf(MIL_TEXT("You can proceed to add / remove cameras to your system ")
         MIL_TEXT("anytime.\n\n"));
      MosPrintf(MIL_TEXT("\r|"));
      MosSleep(STATS_PRINT_PERIOD / 4);
      MosPrintf(MIL_TEXT("\r/"));
      MosSleep(STATS_PRINT_PERIOD / 4);
      MosPrintf(MIL_TEXT("\r-"));
      MosSleep(STATS_PRINT_PERIOD / 4);
      MosPrintf(MIL_TEXT("\r\\"));
      MosSleep(STATS_PRINT_PERIOD / 4);
      }
   }

void AddAdapterToList(SysHookDataStruct* UserSt, MIL_TEXT_PTR AdapterName)
   {
   /* Start by searching if adapter is already in list. */
   for (MIL_INT i = 0; i < MAX_ADAPTERS; i++)
      {
      if (MosStrcmp(UserSt->Adapters[i], AdapterName) == 0)
         return;
      }

   /* Adapter is not in list; add it. */
   for (MIL_INT i = 0; i < MAX_ADAPTERS; i++)
      {
      if (UserSt->Adapters[i][0] == '\0')
         {
         MosStrcpy(UserSt->Adapters[i], MAX_ADAPTER_DESCRIPTION_LENGTH + 4, AdapterName);
         return;
         }
      }
   }
