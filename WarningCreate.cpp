// WarningCreate.cpp: 구현 파일
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "WarningCreate.h"
#include "afxdialogex.h"


// WarningCreate 대화 상자

IMPLEMENT_DYNAMIC(WarningCreate, CDialogEx)

WarningCreate::WarningCreate(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG10, pParent)
{

}

WarningCreate::~WarningCreate()
{
}

void WarningCreate::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, table_list);
	DDX_Control(pDX, IDC_COMBO2, query_combo);
}


BEGIN_MESSAGE_MAP(WarningCreate, CDialogEx)
	ON_CBN_DROPDOWN(IDC_COMBO2, &WarningCreate::OnCbnDropdownCombo2)
	ON_BN_CLICKED(IDC_BUTTON1, &WarningCreate::OnBnClickedButton1)
	ON_CBN_SELCHANGE(IDC_COMBO2, &WarningCreate::OnCbnSelchangeCombo2)
END_MESSAGE_MAP()


// WarningCreate 메시지 처리기




void WarningCreate::OnCbnDropdownCombo2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	query_combo.ResetContent();
	int i = 0;
	for (auto p : QueryStorage::query_map) {
		query_combo.InsertString(i++, CString(p.first.c_str()));
	}
}

void WarningCreate::OnCbnSelchangeCombo2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str;
	query_combo.GetLBText(query_combo.GetCurSel(), str);
	string group_query_name = (CT2CA)str;

	GroupQuery * tmp_group_query = QueryStorage::getGroupQuery(group_query_name);
	if (tmp_group_query != NULL && group_query != tmp_group_query) {
		if (group_query != NULL)
			group_query->deleteAction("table_show_action");
		group_query = tmp_group_query;
		group_query->addAction("table_show_action");
	}
}

void WarningCreate::Init() {
	group_query = NULL;
	function<void(vector<list<Event>*>)> table_show = [this](vector<list<Event>*> v)->void {
		table_list.DeleteAllItems();
		while (table_list.DeleteColumn(0));

		for (int i = 0; i<group_query->select_funcs.size(); i++)
			table_list.InsertColumn(i, CString(group_query->select_strings.at(i).c_str()), LVCFMT_LEFT, 100, -1);
		int i = 0;
		for (auto li : v) {
			table_list.InsertItem(i, __T(""));
			int j = 0;
			for (auto f : group_query->select_funcs) {
				string str = String(f(*li));
				table_list.SetItem(i, j++, LVIF_TEXT, CString(str.c_str()), 0, 0, 0, NULL);
			}
			i++;
		}
	};
	ActionStorage::addGroupAction("table_show_action", table_show);
}

void WarningCreate::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
}
