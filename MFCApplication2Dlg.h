
// MFCApplication2Dlg.h: 헤더 파일
//

#pragma once

#include "EventTypeCreateDlg.h"
#include "EventTypeListDlg.h"
#include "StreamCreateDlg.h"
#include "StreamListDlg.h"
#include "FilterQueryCreateDlg.h"
#include "GroupQueryCreateDlg.h"
#include "QueryListDlg.h"
#include "QueryPrintDlg.h"
#include "StreamResultDlg.h"
#include "TargetCreateDlg.h"
#include "WarningCreate.h"

#include "simul.h"
#include "Manager.h"
#include "Extractor.h"
#include "AggregationFuncs.h"

// CMFCApplication2Dlg 대화 상자
class CMFCApplication2Dlg : public CDialogEx
{
// 생성입니다.
public:
	CMFCApplication2Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION2_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl event_type_tab;
	CTabCtrl stream_tab;
	CTabCtrl query_tab;
	CTabCtrl result_tab;

	EventTypeCreateDlg * event_type_create_dlg;
	EventTypeListDlg * event_type_list_dlg;
	StreamCreateDlg * stream_create_dlg;
	StreamListDlg * stream_list_dlg;
	FilterQueryCreateDlg * filter_query_create_dlg;
	QueryListDlg * query_list_dlg;
	StreamResultDlg * stream_result_dlg;
	GroupQueryCreateDlg * group_query_create_dlg;
	TargetCreateDlg * target_create_dlg;
	QueryPrintDlg * query_print_dlg;
	WarningCreate * warning_create_dlg;
	
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTcnSelchangeTab2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTcnSelchangeTab3(NMHDR *pNMHDR, LRESULT *pResult);

	void Init();
	Simulator * simulator;
	queue<Data> q;
	mutex q_mtx;
	Extractor * extractor;
	CTabCtrl simulator_tab;
	afx_msg void OnTcnSelchangeTab5(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTcnSelchangeTab4(NMHDR *pNMHDR, LRESULT *pResult);
};
