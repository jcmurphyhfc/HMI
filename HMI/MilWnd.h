#pragma once

#include <mil.h>
#include "MilWndChild.h"

typedef struct tagMILSTATS {
	double dbMaxTotalProcTime; //
	double dbTotalProcTime;    // Processing time
	double dbTimeStamp;        // Time stamp
	double dbMaxTimeStamp;     // Max
	double dbLastTimeStamp;    // Last 
	double dbDisplayUpdate;    // Display update time
	double dbMaxDisplayUpdate; // 
	short DataAge;             // Age of packet data
	short ComJitter;           // Com Jitter
	short MaxComJitter;        // Com Jitter
	int nMachineStatus;
	unsigned __int16 ResponseTicks;
	unsigned char PacketError;
} MILSTATS;

// CMilWnd frame

class CMilWnd : public CFrameWnd
{
	DECLARE_DYNCREATE(CMilWnd)
public:
	CMilWnd();
	//CMilWnd(const RECT& rect,CWnd* pParentWnd,int nToolBarID);
	CMilWnd(const RECT& rect,CWnd* pParentWnd,int nToolBarID,int IndicatorID);
	virtual ~CMilWnd();
public:
	CWinThread* m_pThread;
	bool 	m_bGrid;
	double m_dbOffset;
	double m_dbZoomX;
	double m_dbZoomY;
	bool   m_bContinue;
	MIL_ID ImageBuffer;
	int    m_nDisplayTime;
	//SERIALCOMTHREADPARMS* m_pSerial[4];

protected:
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;
	CToolBar    m_wndViewToolBar;
	CMilWndChild* m_pMilWnd;
	int m_nToolBarID;
	int m_nCameraID;
	int m_nIndicatorID;

protected:
	DECLARE_MESSAGE_MAP()
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT SelectCamera(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT CalibrateCamera(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT CameraStart(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT CameraStop(WPARAM wParam, LPARAM lParam);

	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnUpdateCursorPosition(CCmdUI *pCmdUI);
	afx_msg void OnSystemCalibrate();

	void UpdateStatusBarStats(MILSTATS* stats);
	void GetBuffValue8(CPoint point,unsigned char* buff);
	void GetBuffValue16(MIL_ID nID,CPoint point,unsigned __int16* buff);

	//afx_msg void OnSystemCalibratelaser();
	//afx_msg void OnLoadCam1();
	//afx_msg void OnLoadCam2();
	//afx_msg void OnLoadCam3();
	//afx_msg void OnLoadCam4();
	//void ShowButtons(void);
	//void ShowButtons2(void);
	//bool GetSysButtons(void);
	//BOOL PeekAndPump ();

	//afx_msg void OnImageResult();
	//afx_msg void OnImageLaneadepth();
	//afx_msg void OnImageLanebdepth();
	//afx_msg void OnImageLanearawdepth();
	//afx_msg void OnImageLabebrawdepth();
	//afx_msg void OnImageLaneaintensity();
	//afx_msg void OnImageLanebintensity();
	//afx_msg void OnUpdateImageLabebrawdepth(CCmdUI *pCmdUI);
	//afx_msg void OnUpdateImageLaneadepth(CCmdUI *pCmdUI);
	//afx_msg void OnUpdateImageLaneaintensity(CCmdUI *pCmdUI);
	//afx_msg void OnUpdateImageLanebdepth(CCmdUI *pCmdUI);
	//afx_msg void OnUpdateImageLanebintensity(CCmdUI *pCmdUI);
	//afx_msg void OnUpdateImageResult(CCmdUI *pCmdUI);
	//afx_msg void OnUpdateImageLanearawdepth(CCmdUI *pCmdUI);
	//afx_msg void OnClipImage();
	//afx_msg void OnUpdateClipImage(CCmdUI *pCmdUI);
	//afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//afx_msg void OnClipBinarize();
	//afx_msg void OnUpdateClipBinarize(CCmdUI *pCmdUI);
	//afx_msg void OnClipImagelow();
	//afx_msg void OnUpdateClipImagelow(CCmdUI *pCmdUI);
	//afx_msg void OnClipEnable();
	//afx_msg void OnImageLiveview();
	//afx_msg void OnUpdateImageLiveview(CCmdUI *pCmdUI);
	//afx_msg void OnImageLaneamodel();
	//afx_msg void OnUpdateImageLaneamodel(CCmdUI *pCmdUI);
	//afx_msg void OnImageLanebmodel();
	//afx_msg void OnUpdateImageLanebmodel(CCmdUI *pCmdUI);
	//afx_msg void OnImageSealLanea();
	//afx_msg void OnUpdateImageSealLanea(CCmdUI *pCmdUI);
	//afx_msg void OnImageSealLaneb();
	//afx_msg void OnUpdateImageSealLaneb(CCmdUI *pCmdUI);

	//afx_msg void OnSystemCalibrateintensity();
	//afx_msg void OnUpdateSystemCalibrateintensity(CCmdUI *pCmdUI);
	//afx_msg void OnSystemCalib();
	//afx_msg void OnUpdateSystemCalib(CCmdUI *pCmdUI);

};

class CLaserWnd : public CFrameWnd
{
	DECLARE_DYNCREATE(CLaserWnd)
public:
	HWND m_hwndChild;
	CLaserWnd();
	CLaserWnd(const RECT& rect,CWnd* pParentWnd);
	virtual ~CLaserWnd();
public:

protected:

protected:
	DECLARE_MESSAGE_MAP()
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
};