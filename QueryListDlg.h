#pragma once
#include "Manager.h"

// QueryListDlg 대화 상자

class QueryListDlg : public CDialogEx
{
	DECLARE_DYNAMIC(QueryListDlg)

public:
	QueryListDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~QueryListDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG6 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CComboBox filter_query_combo;
	CComboBox group_query_combo;
	CListCtrl query_info;
	void Init();
	void Update();
	Query * query;
	afx_msg void OnCbnDropdownCombo1();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnCbnSelchangeCombo2();
	afx_msg void OnCbnDropdownCombo2();
};
