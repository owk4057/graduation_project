#pragma once
#include "Manager.h"

// EventTypeList 대화 상자

class EventTypeListDlg : public CDialogEx
{
	DECLARE_DYNAMIC(EventTypeListDlg)

public:
	EventTypeListDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~EventTypeListDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl event_type_info;
	CComboBox event_type_combo;
	afx_msg void OnCbnSelchangeCombo1();
	void Init();
	EventType * event_type;
	afx_msg void OnCbnDropdownCombo1();
};
