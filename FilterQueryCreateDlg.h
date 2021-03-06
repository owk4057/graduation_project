#pragma once
#include "Manager.h"


// FilterQueryCreateDlg 대화 상자

class FilterQueryCreateDlg : public CDialogEx
{
	DECLARE_DYNAMIC(FilterQueryCreateDlg)

public:
	FilterQueryCreateDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~FilterQueryCreateDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG5 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();

	CEdit query_name_edit;
	CEdit where_expr_edit;
	CEdit select_expr_edit;
	CListBox select_expr_list;
	CEdit select_as_edit;
	Parser parser;
	CComboBox in_stream_combo;
	CComboBox out_stream_combo;
	afx_msg void OnCbnDropdownCombo1();
	afx_msg void OnCbnDropdownCombo2();
};
