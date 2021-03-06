#pragma once
#include "simul.h"


// TargetCreateDlg 대화 상자

class TargetCreateDlg : public CDialogEx
{
	DECLARE_DYNAMIC(TargetCreateDlg)

public:
	TargetCreateDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~TargetCreateDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG9 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	void Init(Simulator * simulator);
	Simulator * simulator;
	CEdit min_count_edit;
	CEdit max_count_edit;
	CEdit min_x_edit;
	CEdit max_x_edit;
	CEdit min_y_edit;
	CEdit max_y_edit;
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton3();
	CListCtrl simulator_info;
	CComboBox type_a_combo;
	CComboBox type_b_combo;
	afx_msg void OnCbnDropdownCombo1();
	afx_msg void OnCbnSelchangeCombo1();
};
