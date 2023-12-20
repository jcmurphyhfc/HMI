//======================================================================
// Sorce file
//
// Written for the ALP machine
// Copyright (C) 2014 Bill Young
//================================================================

//#pragma warning(disable : 4996)
#include "StdAfx.h"
#define HISTORY_GLOBALS          // For globals 
#include "History.h"

CHistory::CHistory(void)
{
	m_strArray.SetSize(1024);
	//m_nUnSavedStringCount = 0;
	//m_nStringsInSaveFile = 0;
	m_nStringCount = 0;
	m_strFileName = _T("");
	m_nPrevMinute = 0;
	m_nPrevHour = 0;
	m_nPrevSecond = 0;
	m_ErrorsPerMin = 0;
	m_LaststrError = _T("");
}

CHistory::~CHistory(void)
{
}

//======================================================================================================//
// Function Name: SetFileName ()                                                                         //
//                                                                                                      //
//======================================================================================================//
void CHistory::SetFileName(LPCTSTR lpName)
{
	m_strFileName = lpName;
	//CString strPrev = m_strFileName;
	//int len = strPrev.GetLength();
	//strPrev.Delete(len-4,4);
	//strPrev += TEXT("LastShift.txt");
	//m_strFileNamePrev = strPrev;
	//TRACE(_T("\n\n\nFile1:%s   File2:%s \n"),m_strFileName,strPrev);
}

//======================================================================================================//
// Function Name: AddStrings ()                                                                         //
//                                                                                                      //
//======================================================================================================//
void CHistory::AddString(LPCTSTR lpName)
{
	CString strError = lpName;
	CTime time = CTime::GetCurrentTime ();
	int nSecond = time.GetSecond ();
	int nMinute = time.GetMinute ();
	int nHour = time.GetHour() % 12;
	int nMonth = time.GetMonth();
	int nDay = time.GetDay();
	int nYear = time.GetYear();

	// Prevent adding the same error every minute except for reset.
	if (strError != _T("BTC Reset"))
	{
		if (m_nPrevMinute == nMinute && m_LaststrError == strError)
		{
			return;
		}
	}
	m_LaststrError = strError; 

	// Prevent adding more than 32 errors per minute
	m_ErrorsPerMin++;
	if (m_nPrevMinute == nMinute  && m_ErrorsPerMin >= 32)
	{
		return;
	}
	if (m_ErrorsPerMin >= 32) m_ErrorsPerMin = 0;

	//TRACE (_T ("Add string ------> %s"),lpName);

	// Save previous time vars
	m_nPrevMinute = nMinute;
	m_nPrevHour = nHour;

	// Format the string
	CString strTime;
	strTime.Format (_T ("%0.2d:%0.2d:%0.2d %d-%d-%d  "), nHour, nMinute, nSecond,nMonth,nDay,nYear);
	strTime += strError;
	strTime += _T("\r\n");

	// Open the string file
	m_nStringCount = 0;
	m_strArray[m_nStringCount++] = strTime;
	LoadStrings();

	// Save the string file
	SaveStringsToFile();
	//TRACE("Time to save %d Strings to file \n",m_nStringCount);

}
//======================================================================================================//
// Function Name: LoadStrings ()                                                                        //
//                                                                                                      //
//======================================================================================================//
void CHistory::LoadStrings()
{
	CStdioFile file;
	CFileException e;
	TCHAR StringBuf[256];

	// Exit if file not set
	if (m_strFileName == _T(""))
		return;
	
	// Get the strings from the file
	//TRACE (_T ("\n Reading strings \n"));
	if (file.Open (m_strFileName, CFile::modeReadWrite |CFile::modeCreate | CFile::modeNoTruncate, &e)) {
		while (file.ReadString (StringBuf,256) && m_nStringCount < 1023)	
		{
			m_strArray[m_nStringCount++] = StringBuf;
		}
	}
	else 
	{
		// Open failed. Tell the user why.
		e.ReportError ();
	}
	file.Close();

}
//======================================================================================================//
// Function Name: SaveStringsToFile ()                                                                        //
//                                                                                                      //
//======================================================================================================//
void CHistory::SaveStringsToFile()
{
	//CString string;
	CStdioFile file;
	CFileException e;

	if (m_strFileName == _T(""))
		return;

	// Save strings
	if (file.Open (m_strFileName, CFile::modeReadWrite | CFile::modeCreate, &e))
	{
		for (int i=0; i<m_nStringCount; i++)
		{
			//TRACE (_T ("Saving string %d ------> %s"),i,m_strArray[i]);
			file.WriteString(m_strArray[i]);			
		}
	}
	else
	{
		// Open failed. Tell the user why.
		e.ReportError ();
	}

	// Close
	file.Close();


	//CString string;
	//CStdioFile file;
	//CFileException e;

	//// Any strings to save?
	//if 	(m_nUnSavedStringCount == 0)
	//	return;
	//if (m_strFileName == _T(""))
	//	return;

	// Save strings
	//if (file.Open (m_strFileName, CFile::modeReadWrite |CFile::modeCreate | CFile::modeNoTruncate, &e))
	//{
	//	file.SeekToEnd();
	//	for (int i=0; i<m_nUnSavedStringCount; i++)
	//	{
	//		//TRACE (_T ("Saving data........................%s"),m_strArray[i]);
	//		file.WriteString(m_strArray[i]);			
	//	}

	//	m_nStringsInSaveFile += m_nUnSavedStringCount;
	//	//TRACE (_T ("Saveing %d strings, Strings in saved file: %d \n"),m_nUnSavedStringCount,m_nStringsInSaveFile);
	//	m_nUnSavedStringCount = 0;

	//}
	//else
	//{
	//	// Open failed. Tell the user why.
	//	e.ReportError ();
	//}

	//// Close
	//file.Close();

}
//======================================================================================================//
// Function Name: ClearStrings ()                                                                        //
//                                                                                                      //
//======================================================================================================//
void CHistory::ClearStrings()
{
	CStdioFile file;
	CFileException e;
	//m_nUnSavedStringCount = 0;
	//m_nStringsInSaveFile = 0;

	if (m_strFileName == _T(""))
		return;

	if (file.Open (m_strFileName, CFile::modeReadWrite | CFile::modeCreate, &e)) {
	}
	else {
		e.ReportError ();
	}
}


//======================================================================================================//
// Function Name: ShowStrings ()                                                                        //
//                                                                                                      //
//======================================================================================================//
int CHistory::ShowStrings(CWnd* pWnd)
{
	CString string;
	//TRACE (_T ("String count:%d "), m_nStringCount);

	// Exit
	if (m_strFileName == _T(""))
		return 0;

	// Get the strings
	m_nStringCount = 0;
	LoadStrings();

	// Show the last 1023 strings
	string.Format(_T("Total Faults:%d"),m_nStringCount);
	string += _T("\r\n");
	for (int i=0; i<m_nStringCount; i++)
	{
		string += m_strArray[i];
	}
	pWnd->SetWindowText(string);

	return m_nStringCount;

	//CString string;
	//CStdioFile file;
	//CFileException e;
	//TCHAR StringBuf[256];
	//CStringArray strArray;
	//strArray.SetSize(1024);
	//int TotalStrings = 0;
	////TRACE (_T ("String count:%d "), m_nStringCount);
	//if (m_strFileName == _T(""))
	//	return 0;

	//// Get the strings from the file
	////TRACE (_T ("\n Reading strings \n"));
	//if (file.Open (m_strFileName, CFile::modeReadWrite |CFile::modeCreate | CFile::modeNoTruncate, &e)) {
	//	m_nStringsInSaveFile = 0;
	//	while (file.ReadString (StringBuf,256))	
	//	{
	//		//strArray[m_nStringsInSaveFile] = StringBuf;
	//		//if (m_nStringsInSaveFile < 1023) m_nStringsInSaveFile++;			
	//		TotalStrings++;
	//		if (m_nStringsInSaveFile < 1023){
	//			strArray[m_nStringsInSaveFile] = StringBuf;
	//			m_nStringsInSaveFile++;
	//		}
	//		else{
	//			for (int i=0;i<1022;i++){
	//				strArray[i] = strArray[i+1];
	//			}
	//			strArray[1022] = StringBuf;
	//		}
	//	}
	//}
	//else {
	//	// Open failed. Tell the user why.
	//	e.ReportError ();
	//}

	//// Show the last 1023 strings
	//string.Format(_T("Total Faults:%d"),TotalStrings);
	//string += _T("\r\n");
	//for (int i=m_nStringsInSaveFile; i>0; i--)
	//{
	//	string += strArray[i-1];
	//}
	//pWnd->SetWindowText(string);

	//return m_nUnSavedStringCount;

}

