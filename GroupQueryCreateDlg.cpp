// GroupQueryCreateDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "GroupQueryCreateDlg.h"
#include "afxdialogex.h"


// GroupQueryCreateDlg 대화 상자

IMPLEMENT_DYNAMIC(GroupQueryCreateDlg, CDialogEx)

GroupQueryCreateDlg::GroupQueryCreateDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG8, pParent)
{

}

GroupQueryCreateDlg::~GroupQueryCreateDlg()
{
}

void GroupQueryCreateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, group_by_edit);
	DDX_Control(pDX, IDC_EDIT7, having_edit);
	DDX_Control(pDX, IDC_EDIT6, select_edit);
	DDX_Control(pDX, IDC_LIST1, select_list);
	DDX_Control(pDX, IDC_EDIT5, where_edit);
	DDX_Control(pDX, IDC_EDIT2, query_name_edit);
	DDX_Control(pDX, IDC_EDIT8, window_edit);
	DDX_Control(pDX, IDC_RADIO1, time_window_radio);
	DDX_Control(pDX, IDC_RADIO2, count_window_radio);
	DDX_Control(pDX, IDC_COMBO1, in_stream_combo);
	DDX_Control(pDX, IDC_COMBO2, out_stream_combo);
}

BEGIN_MESSAGE_MAP(GroupQueryCreateDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &GroupQueryCreateDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &GroupQueryCreateDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &GroupQueryCreateDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON1, &GroupQueryCreateDlg::OnBnClickedButton1)
	ON_CBN_DROPDOWN(IDC_COMBO1, &GroupQueryCreateDlg::OnCbnDropdownCombo1)
	ON_CBN_DROPDOWN(IDC_COMBO2, &GroupQueryCreateDlg::OnCbnDropdownCombo2)
END_MESSAGE_MAP()


// GroupQueryCreateDlg 메시지 처리기


//선택문 추가
void GroupQueryCreateDlg::OnBnClickedButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str;
	select_edit.GetWindowTextW(str);

	int nSel = select_list.GetCurSel();  // 선택한 문자의 인덱스 얻어옴
	if (nSel >= 0)
		select_list.InsertString(nSel, str);  // 해당 인덱스의 문자열을 삭제
	else
		select_list.InsertString(select_list.GetCount(), str);
}


//선택문 삭제
void GroupQueryCreateDlg::OnBnClickedButton3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nSel = select_list.GetCurSel();  // 선택한 문자의 인덱스 얻어옴

	if (nSel >= 0)
		select_list.DeleteString(nSel);  // 해당 인덱스의 문자열을 삭제
}


//선택문 선택 취소
void GroupQueryCreateDlg::OnBnClickedButton4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	select_list.SetCurSel(-1);
}


//그룹 쿼리 생성
void GroupQueryCreateDlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str;
	query_name_edit.GetWindowTextW(str);
	string query_name = (CT2CA)str;
	in_stream_combo.GetWindowTextW(str);
	string in_stream_name = (CT2CA)str;
	out_stream_combo.GetWindowTextW(str);
	string out_stream_name = (CT2CA)str;
	where_edit.GetWindowTextW(str);
	string where_string = (CT2CA)str;
	group_by_edit.GetWindowTextW(str);
	string group_by_expr = (CT2CA)str;
	having_edit.GetWindowTextW(str);
	string having_string = (CT2CA)str;
	window_edit.GetWindowTextW(str);
	string range_string = (CT2CA)str;
	float range = stof(range_string);
	bool result;

	char  ptr[256];
	strcpy_s(ptr, sizeof(ptr), group_by_expr.c_str());
	char * context;
	vector<string> group_attr_strings;
	char * tok = strtok_s(ptr, ", ", &context);
	group_attr_strings.emplace_back(string(tok));
	while (tok = strtok_s(context, ", ", &context))
		group_attr_strings.emplace_back(string(tok));

	Stream * in_stream = StreamStorage::getStream(in_stream_name);
	Stream * out_stream = StreamStorage::getStream(out_stream_name);

	vector<string> select_strings;
	vector<function<any(list<Event>&)>> select_funcs;
	int cnt = select_list.GetCount();
	for (int i = 0; i < cnt; i++) {
		select_list.GetText(i, str);
		string s = (CT2CA)str;
		select_strings.emplace_back(s);
		select_funcs.emplace_back(parser.getSelectGroup(s, &result));
	}

	auto where_func = parser.getWhere(where_string, &result);
	auto having_func = parser.getHaving(having_string, &result);

	if (IsDlgButtonChecked(IDC_RADIO1)) {
		TimeGroupQuery * query = new TimeGroupQuery(query_name,
			Range_t((int)(range * 10000000)),
			in_stream,
			out_stream,
			group_attr_strings,
			where_string,
			where_func,
			having_string,
			having_func,
			select_strings,
			select_funcs,
			1000);
		QueryStorage::addQuery(query_name, query);
	}
	else if (IsDlgButtonChecked(IDC_RADIO2)) {
		CountGroupQuery * query = new CountGroupQuery(query_name,
			(int)range,
			in_stream,
			out_stream,
			group_attr_strings,
			where_string,
			where_func,
			having_string,
			having_func,
			select_strings,
			select_funcs,
			1000);
		QueryStorage::addQuery(query_name, query);
	}
}


// in stream drop down
void GroupQueryCreateDlg::OnCbnDropdownCombo1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	in_stream_combo.ResetContent();
	int i = 0;
	for (auto p : StreamStorage::m) 
		in_stream_combo.InsertString(i++, CString(p.second->stream_name.c_str()));
}


// out stream drop down
void GroupQueryCreateDlg::OnCbnDropdownCombo2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	out_stream_combo.ResetContent();
	int i = 0;
	for (auto p : StreamStorage::m) 
		out_stream_combo.InsertString(i++, CString(p.second->stream_name.c_str()));
}
