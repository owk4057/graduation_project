#pragma once
#include "Manager.h"


// StreamCreateDlg 대화 상자

class StreamCreateDlg : public CDialogEx
{
	DECLARE_DYNAMIC(StreamCreateDlg)

public:
	StreamCreateDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~StreamCreateDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CEdit stream_name_edit;
	CEdit stream_size_edit;
	CButton stream_create_btn;
	afx_msg void OnBnClickedButton1();
	CComboBox event_type_combo;
	afx_msg void OnCbnDropdownCombo1();
};
