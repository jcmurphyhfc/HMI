//======================================================================
// Sorce file
//
// Written for the ALP machine
// Copyright (C) 2014 Bill Young
//================================================================

#include "stdafx.h"
#define SAVE_GLOBALS          // For VOL globals 
#include "Save.h"


//----------------------------------------------------------------------
// LoadMasterDataFile - Load application settings.
//
bool LoadMasterDataFile (ALLSETTINGS* pData) 
{
	DWORD nBytes;
	BOOL bResult;
	unsigned char* buffer = (unsigned char*)pData;

    // Open the file.
    HANDLE hFile = CreateFile (MASTERDATAFILE, GENERIC_READ,
	FILE_SHARE_READ, NULL, OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL, NULL);

    if (hFile == INVALID_HANDLE_VALUE) {
        //MessageBox (hWnd, TEXT("Couldn't open file"), szAppName, MB_OK);
		TRACE("No data file exists! Creat the file...\n");
		
		hFile = CreateFile (DATAFILE, GENERIC_WRITE,FILE_SHARE_WRITE, NULL, CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL, NULL);
		memset(pData,0,sizeof(ALLSETTINGS));
		//::ZeroMemory (&lf, sizeof (lf));

		pData->HMISettings.bEnableMaster = true;
		pData->HMISettings.bEnableUser = true;
		pData->HMISettings.bBoostPriority = true;
		pData->HMISettings.bFullReset = true;
		pData->HMISettings.nMasterPassword = 577769;
		pData->HMISettings.nPassword = 5777;
		pData->HMISettings.nPmacReset = 0;
		//pData->HMISettings.szLaneName[0] = _T('\0');
		::lstrcpy (pData->HMISettings.szLaneName, _T ("BTC24 Lane 1"));
		bResult = WriteFile(hFile, buffer, sizeof(ALLSETTINGS), &nBytes, NULL) ; 
		TRACE("Bytes Written to new file: %d \n",nBytes);
		CloseHandle(hFile);

		return false;
    }
	bResult = ReadFile(hFile, buffer, sizeof(ALLSETTINGS), &nBytes, NULL) ; 
	TRACE("Bytes Read %d\n",nBytes);
	CloseHandle(hFile);

	return true;
}

//----------------------------------------------------------------------
// LoadDataFile - Load application settings.
//
bool LoadDataFile (ALLSETTINGS* pData) 
{
	DWORD nBytes;
	BOOL bResult;
	unsigned char* buffer = (unsigned char*)pData;

    // Open the file.
    HANDLE hFile = CreateFile (DATAFILE, GENERIC_READ,
		FILE_SHARE_READ, NULL, OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL, NULL);

    if (hFile == INVALID_HANDLE_VALUE) {
        //MessageBox (hWnd, TEXT("Couldn't open file"), szAppName, MB_OK);
		TRACE("No data file exists! Creat the file...\n");
		
		hFile = CreateFile (DATAFILE, GENERIC_WRITE,FILE_SHARE_WRITE, NULL, CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL, NULL);
		memset(pData,0,sizeof(ALLSETTINGS));
		//::ZeroMemory (&lf, sizeof (lf));

		pData->HMISettings.bEnableMaster = true;
		pData->HMISettings.bEnableUser = true;
		pData->HMISettings.bBoostPriority = true;
		pData->HMISettings.bFullReset = true;
		pData->HMISettings.nMasterPassword = 577769;
		pData->HMISettings.nPassword = 5777;
		pData->HMISettings.nPmacReset = 0;
		//pData->HMISettings.szLaneName[0] = _T('\0');
		::lstrcpy (pData->HMISettings.szLaneName, _T ("BTC24 Lane 1"));

		//for (int i=0; i<50; i++){
		//	pData->VisSettings5.dbNUCamerHeightPoints[i] = i+1;
		//	pData->VisSettings6.dbCamerHeightPoints[i] = i+1;
		//}

		bResult = WriteFile(hFile, buffer, sizeof(ALLSETTINGS), &nBytes, NULL) ; 
		TRACE("Bytes Written to new file: %d \n",nBytes);
		CloseHandle(hFile);

		return false;
    }

	////bResult = ReadFile(hFile, &buffer, sizeof(MERGEDATA), &nBytes, NULL) ; 
	//bResult = ReadFile(hFile, buffer, sizeof(MERGEDATA), &nBytes, NULL) ; 
	//DEBUGMSG(TRUE, (TEXT("Bytes Read %d\n"),nBytes));
	//DEBUGMSG(TRUE, (TEXT("Read Count %d \n"),g_MergeData.dwCount));
	//DEBUGMSG(TRUE, (TEXT("Read Threshold %d \n"),g_MergeData.dwThreshold));
	//DEBUGMSG(TRUE, (TEXT("Read Min Blob size %d \n"),g_MergeData.dwMinBlobSize));
	//// Update the settings
	//UpdateSettings ();
	//CloseHandle(hFile);

	bResult = ReadFile(hFile, buffer, sizeof(ALLSETTINGS), &nBytes, NULL) ; 
	TRACE("Bytes Read %d\n",nBytes);
	CloseHandle(hFile);

	return true;
}

//----------------------------------------------------------------------
// SaveDataFile - Save application settings.
//
bool SaveDataFile (ALLSETTINGS* pData) 
{
	DWORD nBytes;
	BOOL bResult;
	unsigned char* buffer = (unsigned char*)pData;

	// Open the file.
	HANDLE hFile = CreateFile (DATAFILE, GENERIC_WRITE,FILE_SHARE_WRITE, NULL, OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        //MessageBox (hWnd, TEXT("Couldn't open file"), szAppName, MB_OK);
		TRACE("Error File not found!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
        return false;
    }
	bResult = WriteFile(hFile, buffer, sizeof(ALLSETTINGS), &nBytes, NULL) ; 
	TRACE("Save the data file... Bytes Written: %d \n",nBytes);
	CloseHandle(hFile);

	return true;
}

//----------------------------------------------------------------------
// SaveBackUpDataFile - Save backup application settings.
//
//----------------------------------------------------------------------
bool SaveBackUpDataFile (int nID,ALLSETTINGS* pData)
{
	DWORD nBytes;
	BOOL bResult;
	unsigned char* buffer = (unsigned char*)pData;
	CString strFile,strBackup;
	strBackup = BACKUP_PATH;
	strBackup += BACKUP_NAME;
	strFile.Format(_T("%d"),nID);
	strFile += BACKUP_EXT;
	strBackup += strFile;
	TRACE(_T("Backup File: %s \n"),strBackup);

	// Open the file.
	HANDLE hFile = CreateFile (strBackup, GENERIC_WRITE,FILE_SHARE_WRITE, NULL, CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
		TRACE("Error File not found!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
        return false;
    }

	// Save the parameter file
	bResult = WriteFile(hFile, buffer, sizeof(ALLSETTINGS), &nBytes, NULL) ; 
	TRACE("Save the data file... Bytes Written: %d \n",nBytes);
	CloseHandle(hFile);

	// Remove the path for display
	strBackup = BACKUP_NAME;
	strBackup += strFile;
	strBackup += _T(" Saved!");
	OkDlg(strBackup,false);

	return true;
}
// LoadBackUpDataFile - Load backup application settings.
//
bool LoadBackUpDataFile (int nID,ALLSETTINGS* pData)
{
	DWORD nBytes;
	BOOL bResult;
	unsigned char* buffer = (unsigned char*)pData;
	CString strFile,strBackup;
	strBackup = BACKUP_PATH;
	strBackup += BACKUP_NAME;
	strFile.Format(_T("%d"),nID);
	strFile += BACKUP_EXT;
	strBackup += strFile;
	TRACE(_T("Backup File: %s \n"),strBackup);

    // Open the file.
    HANDLE hFile = CreateFile (strBackup, GENERIC_READ,
		FILE_SHARE_READ, NULL, OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        //MessageBox (hWnd, TEXT("Couldn't open file"), szAppName, MB_OK);
		//TRACE("No data file exists! Creat the file...\n");
		OkDlg(_T("Data file does not exist!"),true);
		CloseHandle(hFile);
		return false;
    }

	// Load the parameter file
	bResult = ReadFile(hFile, buffer, sizeof(ALLSETTINGS), &nBytes, NULL) ; 
	TRACE("Bytes Read %d\n",nBytes);
	CloseHandle(hFile);

	// Remove the path for display
	strBackup = BACKUP_NAME;
	strBackup += strFile;
	strBackup += _T(" Loaded!");
	OkDlg(strBackup,false);
	return true;
}


//----------------------------------------------------------------------
// LoadCounterFile - Load application settings.
//
bool LoadCounterFile (ALLCOUNTERS* pData) 
{
	DWORD nBytes;
	BOOL bResult;
	unsigned char* buffer = (unsigned char*)pData;

    // Open the file.
    HANDLE hFile = CreateFile (COUNTERFILE, GENERIC_READ,
		FILE_SHARE_READ, NULL, OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL, NULL);

    if (hFile == INVALID_HANDLE_VALUE) {
        //MessageBox (hWnd, TEXT("Couldn't open file"), szAppName, MB_OK);
		//TRACE("No data file exists! Creat the file...\n");
		
		hFile = CreateFile (COUNTERFILE, GENERIC_WRITE,FILE_SHARE_WRITE, NULL, CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL, NULL);
		memset(pData,0,sizeof(ALLCOUNTERS));
		//::ZeroMemory (&lf, sizeof (lf));

		bResult = WriteFile(hFile, buffer, sizeof(ALLCOUNTERS), &nBytes, NULL) ; 
		TRACE("Bytes Written to new file: %d \n",nBytes);
		CloseHandle(hFile);

		return false;
    }


	bResult = ReadFile(hFile, buffer, sizeof(ALLCOUNTERS), &nBytes, NULL) ; 
	TRACE("Bytes Read %d\n",nBytes);
	CloseHandle(hFile);

	return true;
}

//----------------------------------------------------------------------
// SaveCounterFile - Save application settings.
//
bool SaveCounterFile (ALLCOUNTERS* pData) 
{
	DWORD nBytes;
	BOOL bResult;
	unsigned char* buffer = (unsigned char*)pData;

	// Open the file.
	HANDLE hFile = CreateFile (COUNTERFILE, GENERIC_WRITE,FILE_SHARE_WRITE, NULL, OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        //MessageBox (hWnd, TEXT("Couldn't open file"), szAppName, MB_OK);
		//TRACE("Error File not found!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
        return false;
    }
	bResult = WriteFile(hFile, buffer, sizeof(ALLCOUNTERS), &nBytes, NULL) ; 
	//TRACE("Save the data file... Bytes Written: %d \n",nBytes);
	CloseHandle(hFile);

	return true;
}
