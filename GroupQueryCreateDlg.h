#pragma once
#include "Manager.h"


// GroupQueryCreateDlg 대화 상자

class GroupQueryCreateDlg : public CDialogEx
{
	DECLARE_DYNAMIC(GroupQueryCreateDlg)

public:
	GroupQueryCreateDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~GroupQueryCreateDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG8 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CEdit query_name_edit;
	CEdit select_edit;
	CEdit where_edit;
	CEdit group_by_edit;
	CEdit having_edit;
	CEdit window_edit;
	CListBox select_list;
	CComboBox in_stream_combo;
	CComboBox out_stream_combo;
	CButton time_window_radio;
	CButton count_window_radio;

	Parser parser;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnCbnDropdownCombo1();
	afx_msg void OnCbnDropdownCombo2();
};
