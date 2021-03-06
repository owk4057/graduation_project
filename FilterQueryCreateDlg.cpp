// FilterQueryCreateDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "FilterQueryCreateDlg.h"
#include "afxdialogex.h"


// FilterQueryCreateDlg 대화 상자

IMPLEMENT_DYNAMIC(FilterQueryCreateDlg, CDialogEx)

FilterQueryCreateDlg::FilterQueryCreateDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG5, pParent)
{

}

FilterQueryCreateDlg::~FilterQueryCreateDlg()
{
}

void FilterQueryCreateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT2, query_name_edit);
	DDX_Control(pDX, IDC_EDIT5, where_expr_edit);
	DDX_Control(pDX, IDC_EDIT6, select_expr_edit);
	DDX_Control(pDX, IDC_LIST1, select_expr_list);
	DDX_Control(pDX, IDC_COMBO1, in_stream_combo);
	DDX_Control(pDX, IDC_COMBO2, out_stream_combo);
}


BEGIN_MESSAGE_MAP(FilterQueryCreateDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &FilterQueryCreateDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &FilterQueryCreateDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &FilterQueryCreateDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &FilterQueryCreateDlg::OnBnClickedButton4)
	ON_CBN_DROPDOWN(IDC_COMBO1, &FilterQueryCreateDlg::OnCbnDropdownCombo1)
	ON_CBN_DROPDOWN(IDC_COMBO2, &FilterQueryCreateDlg::OnCbnDropdownCombo2)
END_MESSAGE_MAP()


// FilterQueryCreateDlg 메시지 처리기

//필터 쿼리 생성
void FilterQueryCreateDlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str;
	query_name_edit.GetWindowTextW(str);
	string query_name = (CT2CA)str;
	in_stream_combo.GetWindowTextW(str);
	string in_stream_name = (CT2CA)str;
	out_stream_combo.GetWindowTextW(str);
	string out_stream_name = (CT2CA)str;
	where_expr_edit.GetWindowTextW(str);
	string where_string = (CT2CA)str;

	bool result;
	auto where_func = parser.getWhere(where_string, &result);
	auto in_stream = StreamStorage::getStream(in_stream_name);
	auto out_stream = StreamStorage::getStream(out_stream_name);

	vector<string> select_strings;
	vector<function<any(Event&)>> select_funcs;
	int cnt = select_expr_list.GetCount();
	for (int i = 0; i < cnt; i++) {
		select_expr_list.GetText(i, str);
		string s = (CT2CA)str;
		select_strings.emplace_back(s);
		select_funcs.emplace_back(parser.getSelect(s, &result));
	}
	
	FilterQuery * query = new FilterQuery(query_name,
		in_stream,
		out_stream,
		where_string,
		where_func,
		select_strings,
		select_funcs);
	QueryStorage::addQuery(query_name, query);
}


//선택문 추가
void FilterQueryCreateDlg::OnBnClickedButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str;
	select_expr_edit.GetWindowTextW(str);

	int nSel = select_expr_list.GetCurSel();  // 선택한 문자의 인덱스 얻어옴
	if (nSel >= 0)
		select_expr_list.InsertString(nSel, str);  // 해당 인덱스의 문자열을 삭제
	else
		select_expr_list.InsertString(select_expr_list.GetCount(), str);


}


//선택문 삭제
void FilterQueryCreateDlg::OnBnClickedButton3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nSel = select_expr_list.GetCurSel();  
	if (nSel >= 0)
		select_expr_list.DeleteString(nSel);  
}


//선택문 선택 취소
void FilterQueryCreateDlg::OnBnClickedButton4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
		select_expr_list.SetCurSel(-1);
}


//in_stream drop down
void FilterQueryCreateDlg::OnCbnDropdownCombo1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	in_stream_combo.ResetContent();
	int i = 0;
	for (auto p : StreamStorage::m) 
		in_stream_combo.InsertString(i++, CString(p.second->stream_name.c_str()));
}


//out stream drop down
void FilterQueryCreateDlg::OnCbnDropdownCombo2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	out_stream_combo.ResetContent();
	int i = 0;
	for (auto p : StreamStorage::m) 
		out_stream_combo.InsertString(i++, CString(p.second->stream_name.c_str()));
}
