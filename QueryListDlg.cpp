// QueryListDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "QueryListDlg.h"
#include "afxdialogex.h"


// QueryListDlg 대화 상자

IMPLEMENT_DYNAMIC(QueryListDlg, CDialogEx)

QueryListDlg::QueryListDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG6, pParent)
{

}

QueryListDlg::~QueryListDlg()
{
}

void QueryListDlg::Init() {
	for (auto p : QueryStorage::query_map) 
		filter_query_combo.InsertString(filter_query_combo.GetCount(), CString(p.first.c_str()));
	for (auto p : QueryStorage::query_map) 
		group_query_combo.InsertString(group_query_combo.GetCount(), CString(p.first.c_str()));

	filter_query_combo.SetCurSel(0);
	group_query_combo.SetCurSel(0);
	
	query_info.SetExtendedStyle(LVS_EX_GRIDLINES); // 타이틀 삽입 
	query_info.InsertColumn(0, __T("쿼리 속성"), LVCFMT_CENTER, 100, -1);
	query_info.InsertColumn(1, __T("값"), LVCFMT_CENTER, 100, -1);
	for (int i=0; i<10; i++)
		query_info.InsertItem(i, __T(""));
}
void QueryListDlg::Update() {

}
void QueryListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, filter_query_combo);
	DDX_Control(pDX, IDC_COMBO2, group_query_combo);
	DDX_Control(pDX, IDC_LIST1, query_info);
}


BEGIN_MESSAGE_MAP(QueryListDlg, CDialogEx)
	ON_CBN_DROPDOWN(IDC_COMBO1, &QueryListDlg::OnCbnDropdownCombo1)
	ON_BN_CLICKED(IDC_BUTTON1, &QueryListDlg::OnBnClickedButton1)
	ON_CBN_SELCHANGE(IDC_COMBO1, &QueryListDlg::OnCbnSelchangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO2, &QueryListDlg::OnCbnSelchangeCombo2)
	ON_CBN_DROPDOWN(IDC_COMBO2, &QueryListDlg::OnCbnDropdownCombo2)
END_MESSAGE_MAP()


// QueryListDlg 메시지 처리기


//필터 쿼리 드롭다운
void QueryListDlg::OnCbnDropdownCombo1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	filter_query_combo.ResetContent();
	for (auto p : QueryStorage::query_map) {
		filter_query_combo.InsertString(filter_query_combo.GetCount(), CString(p.first.c_str()));
	}
}

//그룹 쿼리 드롭다운
void QueryListDlg::OnCbnDropdownCombo2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	group_query_combo.ResetContent();
	for (auto p : QueryStorage::query_map) {
		group_query_combo.InsertString(group_query_combo.GetCount(), CString(p.first.c_str()));
	}
}

//쿼리 삭제 버튼 클릭시
void QueryListDlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str;
	int idx = filter_query_combo.GetCurSel();
	if (0 <= idx) {
		filter_query_combo.GetLBText(idx, str);
		filter_query_combo.DeleteString(idx);
		QueryStorage::deleteQuery((string)(CT2A)str);
	}
	idx = group_query_combo.GetCurSel();
	if (0 <= idx) {
		group_query_combo.GetLBText(idx, str);
		group_query_combo.DeleteString(idx);
		QueryStorage::deleteQuery((string)(CT2A)str);
	}
}


//필터 쿼리 선택
void QueryListDlg::OnCbnSelchangeCombo1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	group_query_combo.SetCurSel(-1);
	CString str;
	int idx = filter_query_combo.GetCurSel();
	filter_query_combo.GetLBText(idx, str);
	string query_name = (CT2CA)str;
	query = QueryStorage::getFilterQuery(query_name);

	query_info.SetItem(0, 0, LVIF_TEXT, CString("쿼리 이름"), 0, 0, 0, NULL);
	query_info.SetItem(0, 1, LVIF_TEXT, CString(query_name.c_str()), 0, 0, 0, NULL);

	query_info.SetItem(1, 0, LVIF_TEXT, CString("쿼리 타입"), 0, 0, 0, NULL);
	query_info.SetItem(1, 1, LVIF_TEXT, CString(query->getQueryType().c_str()), 0, 0, 0, NULL);

	query_info.SetItem(2, 0, LVIF_TEXT, CString("입력 스트림"), 0, 0, 0, NULL);
	query_info.SetItem(2, 1, LVIF_TEXT, CString(query->in_stream->stream_name.c_str()), 0, 0, 0, NULL);

	query_info.SetItem(3, 0, LVIF_TEXT, CString("출력 스트림"), 0, 0, 0, NULL);
	if (query->out_stream != NULL)
		query_info.SetItem(3, 1, LVIF_TEXT, CString(query->out_stream->stream_name.c_str()), 0, 0, 0, NULL);
	else
		query_info.SetItem(3, 1, LVIF_TEXT, CString("없음"), 0, 0, 0, NULL);
}

//그룹 쿼리 선택
void QueryListDlg::OnCbnSelchangeCombo2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	filter_query_combo.SetCurSel(-1);
	CString str;
	int idx = group_query_combo.GetCurSel();
	group_query_combo.GetLBText(idx, str);
	string query_name = (CT2CA)str;
	query = QueryStorage::getGroupQuery(query_name);

	query_info.SetItem(0, 0, LVIF_TEXT, CString("쿼리 이름"), 0, 0, 0, NULL);
	query_info.SetItem(0, 1, LVIF_TEXT, CString(query_name.c_str()), 0, 0, 0, NULL);

	query_info.SetItem(1, 0, LVIF_TEXT, CString("쿼리 타입"), 0, 0, 0, NULL);
	query_info.SetItem(1, 1, LVIF_TEXT, CString(query->getQueryType().c_str()), 0, 0, 0, NULL);

	query_info.SetItem(2, 0, LVIF_TEXT, CString("입력 스트림"), 0, 0, 0, NULL);
	query_info.SetItem(2, 1, LVIF_TEXT, CString(query->in_stream->stream_name.c_str()), 0, 0, 0, NULL);

	query_info.SetItem(3, 0, LVIF_TEXT, CString("출력 스트림"), 0, 0, 0, NULL);
	if (query->out_stream != NULL)
		query_info.SetItem(3, 1, LVIF_TEXT, CString(query->out_stream->stream_name.c_str()), 0, 0, 0, NULL);
	else
		query_info.SetItem(3, 1, LVIF_TEXT, CString("없음"), 0, 0, 0, NULL);

}


