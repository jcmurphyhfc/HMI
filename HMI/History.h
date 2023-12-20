//======================================================================
// Header file
//
// Written for the BOV machine
// Copyright (C) 2015 Bill Young
//================================================================
#pragma once

#ifdef    HISTORY_GLOBALS
#define   HISTORY_EXT 
#else
#define   HISTORY_EXT extern
#endif

#pragma once

class CHistory
{
public:
	CHistory(void);
	~CHistory(void);

//Member variables
public:
	//int          m_nUnSavedStringCount;
	//int          m_nStringsInSaveFile;
	int          m_nStringCount;
	CString      m_strFileName;
	CStringArray m_strArray;

	int m_nPrevMinute;
	int m_nPrevHour;
	int m_nPrevSecond;
	int m_ErrorsPerMin;
	CString m_LaststrError;
	//int m_nPrevMonth = time.GetMonth();
	//int m_nPrevDay = time.GetDay();
	//int m_nPrevYear = time.GetYear();


//Member functions
public:
	void SetFileName(LPCTSTR lpName);
	void AddString(LPCTSTR lpName);
	void SaveStringsToFile();
	void LoadStrings();
	void ClearStrings();
	int ShowStrings(CWnd* pWnd);
};


////#define ALPDATAFILE       _T ("D:\\ALPDATA\\DATA.txt")
////#define ALPHOPPERDATAFILE _T ("D:\\ALPDATA\\HOPPDATA.txt")
//
//class CAlpResults
//{
//public:
//	int          m_nStringsInSaveFile1;
//	double       m_dbTotalWeight;
//	double       m_dbTotalWeightError;
//	int          m_nCountWeights;
//	double       m_dbTotalError;
//	int          m_nStringsInSaveFile2;
//	CString      m_strFileName;
//	CString      m_strFileNamePrev;
//	CWnd*        m_pWnd;
//
//public:
//	CAlpResults();
//	~CAlpResults(void);
//	void SetFileName(LPCTSTR lpName);
//	double  GetWeight(LPCTSTR lpName);
//	double  GetWeightError(LPCTSTR lpName);
//	//void SetFileNamePrev(LPCTSTR lpName);
//	//void ReadStrings(CEdit* pEdit);
//	int ShowStrings(CEdit* pEdit);
//	void ShowStringsPrev(CEdit* pEdit);
//	void SaveStrings();
//	void SaveStringsPrev();
//	//void SaveStringsPrev();
//	void AddString(double dbVolume,double dbWeight,double dbDensity,double dbTargetVolume);
//	void AddString(double dbWeight,double dbTargetWeight);
//	void ClearStrings();
//
//};

//======================================================================================================//