// QueryPrintDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "QueryPrintDlg.h"
#include "afxdialogex.h"


// QueryPrintDlg 대화 상자

IMPLEMENT_DYNAMIC(QueryPrintDlg, CDialogEx)

QueryPrintDlg::QueryPrintDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG11, pParent)
{

}

QueryPrintDlg::~QueryPrintDlg()
{
}

void QueryPrintDlg::Init() {
	width = 800;
	height = 400;
	//meter
	min_x = 0;
	min_y = 0;
	max_x = 16000;
	max_y = 12000;
	query_screen.MoveWindow(CRect(0, 80, width, height+80));
	CRgn rgn;
	CRect rect;
	query_screen.GetClientRect(&rect);
	dc = new CClientDC(&query_screen);
	rgn.CreateRectRgnIndirect(&rect);
	dc->SelectClipRgn(&rgn);

	brush.CreateSolidBrush(RGB(0, 0, 0));
	pen_vec.emplace_back(new CPen(PS_SOLID, 1, RGB(0, 0, 0)));
	pen_vec.emplace_back(new CPen(PS_SOLID, 1, RGB(255, 0, 0)));
	pen_vec.emplace_back(new CPen(PS_SOLID, 1, RGB(0, 255, 0)));
	pen_vec.emplace_back(new CPen(PS_SOLID, 1, RGB(0, 0, 255)));

	int i = 0;
	for (auto p : QueryStorage::query_map) {
		if (p.second->in_event_type->name == "Target" &&
			p.second->query_type.type_a == group_type &&
			((GroupQuery *)p.second)->group_attr_strings == vector<string>(1, string("id")));
			query_combo.InsertString(i++, CString(p.first.c_str()));
	}

	DrawTrack  = [this](vector<list<Event>*> v) {
		int x_idx = selected_query->in_event_type->getIdx("x");
		int y_idx = selected_query->in_event_type->getIdx("y");
		this->ClearScreen();
		for (auto li : v) {
			Type type = getType(String(li->begin()->at("type")));
			dc->SelectObject(pen_vec.at(type.a));
			auto it = li->rbegin();
			int x = (Int(it->at(x_idx)) - min_x) * width / (max_x - min_x);
			int y = (Int(it->at(y_idx)) - min_y) * height / (max_y - min_y);
			this->dc->MoveTo(x, y);
			this->dc->Rectangle(x - 3, y - 3, x + 3, y + 3);
			it++;

			while (it != li->rend()) {
				x = (Int(it->at(x_idx)) - min_x) * width / (max_x - min_x);
				y = (Int(it->at(y_idx)) - min_y) * height / (max_y - min_y);
				this->dc->LineTo(x, y);
				this->dc->Rectangle(x - 2, y - 2, x + 2, y + 2);
				it++;
			}
		}
	};

	ActionStorage::addGroupAction("draw_track", DrawTrack);
	
	CString str;
	query_combo.SetCurSel(0);
	query_combo.GetLBText(0, str);
	selected_query_name = (CT2CA)str;
	selected_query = QueryStorage::getGroupQuery(selected_query_name);
	selected_query->addAction("draw_track");
}
void QueryPrintDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, query_combo);
	DDX_Control(pDX, IDC_PIC2, query_screen);
	DDX_Control(pDX, IDC_EDIT1, min_x_edit);
	DDX_Control(pDX, IDC_EDIT10, min_y_edit);
	DDX_Control(pDX, IDC_EDIT2, max_x_edit);
	DDX_Control(pDX, IDC_EDIT3, max_y_edit);
}


BEGIN_MESSAGE_MAP(QueryPrintDlg, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO1, &QueryPrintDlg::OnCbnSelchangeCombo1)
	ON_CBN_DROPDOWN(IDC_COMBO1, &QueryPrintDlg::OnCbnDropdownCombo1)
	ON_BN_CLICKED(IDC_BUTTON2, &QueryPrintDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// QueryPrintDlg 메시지 처리기


void QueryPrintDlg::OnCbnSelchangeCombo1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str;
	query_combo.GetLBText(query_combo.GetCurSel(), str);
	string tmp_query_name = (CT2CA)str;
	
	if (selected_query_name != tmp_query_name) {
		selected_query_name = tmp_query_name;
		selected_query->deleteAction("draw_track");
		selected_query = QueryStorage::getGroupQuery(tmp_query_name);
		selected_query->addAction("draw_track");
	}
}



void QueryPrintDlg::OnCbnDropdownCombo1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	query_combo.ResetContent();
	int i = 0;
	for (auto p : QueryStorage::query_map) {
		if (p.second->in_event_type->name == "Target" &&
			p.second->query_type.type_a == group_type &&
			((GroupQuery *)p.second)->group_attr_strings == vector<string>(1, string("id")));
			query_combo.InsertString(i++, CString(p.first.c_str()));
	}
}


void QueryPrintDlg::OnBnClickedButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int tmp_min_x = GetDlgItemInt(min_x_edit.GetDlgCtrlID());
	int tmp_max_x = GetDlgItemInt(max_x_edit.GetDlgCtrlID());
	int tmp_min_y = GetDlgItemInt(min_y_edit.GetDlgCtrlID());
	int tmp_max_y = GetDlgItemInt(max_y_edit.GetDlgCtrlID());

	if (tmp_max_x < tmp_min_x || tmp_max_y < tmp_min_y) {
		AfxMessageBox(__T("범위가 잘못되었습니다."));
		return;
	}

	min_x = tmp_min_x * 1000;
	max_x = tmp_max_x * 1000;
	min_y = tmp_min_y * 1000;
	max_y = tmp_max_y * 1000;
}
