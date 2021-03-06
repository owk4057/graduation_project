#pragma once

#include "Manager.h"
// EventTypeCreateDlg 대화 상자

class EventTypeCreateDlg : public CDialogEx
{
	DECLARE_DYNAMIC(EventTypeCreateDlg)

public:
	EventTypeCreateDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~EventTypeCreateDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	
	DECLARE_MESSAGE_MAP()
public:
	CComboBox attr_type_combo;
	CEdit attr_name_edit;
	CEdit event_type_name_edit;
	CButton event_type_create_btn;
	CButton event_type_delete_btn;
	CListCtrl attr_list;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();

	string attr_type_arr[6] = { "bool", "int", "float", "string", "Time", "Time Duration" };
	regex attr_ex = regex("[a-zA-Z_]+");
	void Init();
};
