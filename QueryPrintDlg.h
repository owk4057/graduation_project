#pragma once
#include "Manager.h"
#include "simul.h"


// QueryPrintDlg 대화 상자

typedef struct __Track {
	vector<tuple<int, int, Time_t>> pos_vec;
	int type_a;
	int id;
}Track;
class QueryPrintDlg : public CDialogEx
{
	DECLARE_DYNAMIC(QueryPrintDlg)

public:
	QueryPrintDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~QueryPrintDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG11 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	DECLARE_MESSAGE_MAP()
public:
	CComboBox query_combo;
	CStatic query_screen;
	CClientDC * dc;

	string selected_query_name;
	GroupQuery * selected_query;

	void Init();
	CBrush brush;
	CPen red_pen;
	CPen green_pen;
	CPen blue_pen;
	vector<CPen*> pen_vec;
	void ClearScreen() {
		dc->SelectObject(&brush);
		dc->Rectangle(0, 0, 800, 600);
	}
	function<void(vector<list<Event>*>)> DrawTrack;
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnCbnDropdownCombo1();
	CEdit min_x_edit;
	CEdit min_y_edit;
	CEdit max_x_edit;
	CEdit max_y_edit;
	afx_msg void OnBnClickedButton2();

	//미터 단위
	int min_x;
	int max_x;
	int min_y;
	int max_y;
	int width;
	int height;
};
