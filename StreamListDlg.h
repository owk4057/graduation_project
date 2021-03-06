#pragma once
#include "Manager.h"


// StreamListDlg 대화 상자

class StreamListDlg : public CDialogEx
{
	DECLARE_DYNAMIC(StreamListDlg)

public:
	StreamListDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~StreamListDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl stream_list;
	CComboBox stream_combo;
	afx_msg void OnCbnSelchangeCombo1();
	void update();
};
