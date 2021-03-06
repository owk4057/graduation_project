#pragma once
#include "Manager.h"

// WarningCreate 대화 상자

class WarningCreate : public CDialogEx
{
	DECLARE_DYNAMIC(WarningCreate)

public:
	WarningCreate(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~WarningCreate();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG10 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	GroupQuery * group_query;
	Query * query;
	string table_show_action;
	CListCtrl table_list;
	afx_msg void OnCbnDropdownCombo2();
	CComboBox query_combo;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnCbnSelchangeCombo2();


	void Init();
};
