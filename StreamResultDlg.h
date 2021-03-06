#pragma once
#include "Manager.h"

// StreamResultDlg 대화 상자

class StreamResultDlg : public CDialogEx
{
	DECLARE_DYNAMIC(StreamResultDlg)

public:
	StreamResultDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~StreamResultDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG7 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	DECLARE_MESSAGE_MAP()

public:
	CListCtrl stream_result_list;

	TimeGroupQuery * query;
	Stream * stream;
	void Init(string stream_name);
	void setQuery(TimeGroupQuery * query) { this->query = query; }
	void update();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnCbnDropdownCombo1();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnStnClickedPic1();
	CComboBox stream_combo;
	CStatic stream_paint;
	CEdit line_cnt_edit;
};
