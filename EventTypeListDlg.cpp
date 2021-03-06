// EventTypeList.cpp: 구현 파일
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "EventTypeListDlg.h"
#include "afxdialogex.h"


// EventTypeList 대화 상자

IMPLEMENT_DYNAMIC(EventTypeListDlg, CDialogEx)

EventTypeListDlg::EventTypeListDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

}

EventTypeListDlg::~EventTypeListDlg()
{
}

void EventTypeListDlg::Init() {
	event_type_info.DeleteAllItems(); // 리스트 스타일 설정 
	event_type_info.SetExtendedStyle(LVS_EX_GRIDLINES); // 타이틀 삽입 
	event_type_info.InsertColumn(0, _T("Attr Type"), LVCFMT_LEFT, 140, -1);
	event_type_info.InsertColumn(1, _T("Attr Name"), LVCFMT_CENTER, 109, -1);

	int i = 0;
	for (auto p : EventTypeStorage::m) 
		event_type_combo.InsertString(i++, CString(p.first.c_str()));
	event_type_combo.SetCurSel(0);

	CString str;
	event_type_combo.GetLBText(0, str);
	string event_type_name = (CT2CA)str;
	event_type = EventTypeStorage::getEventType(event_type_name);
	i = 0;
	for (auto p : event_type->v) {
		event_type_info.InsertItem(i, CString(p.first.c_str()));
		event_type_info.SetItem(i++, 1, LVIF_TEXT, CString(p.second.c_str()), 0, 0, 0, NULL);
	}
}


void EventTypeListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, event_type_info);
	DDX_Control(pDX, IDC_COMBO1, event_type_combo);
}


BEGIN_MESSAGE_MAP(EventTypeListDlg, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO1, &EventTypeListDlg::OnCbnSelchangeCombo1)
	ON_CBN_DROPDOWN(IDC_COMBO1, &EventTypeListDlg::OnCbnDropdownCombo1)
END_MESSAGE_MAP()


// EventTypeList 메시지 처리기


void EventTypeListDlg::OnCbnSelchangeCombo1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str;
	event_type_combo.GetLBText(event_type_combo.GetCurSel(), str);
	string event_type_name = (CT2CA)str;
	event_type = EventTypeStorage::getEventType(event_type_name);

	event_type_info.DeleteAllItems();
	int i = 0;
	for (auto p : event_type->v) {
		event_type_info.InsertItem(i, CString(p.first.c_str()));
		event_type_info.SetItem(i++, 1, LVIF_TEXT, CString(p.second.c_str()), 0, 0, 0, NULL);
	}
}



void EventTypeListDlg::OnCbnDropdownCombo1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	event_type_combo.ResetContent();
	int i = 0;
	for (auto p : EventTypeStorage::m) {
		event_type_combo.InsertString(i++, CString(p.first.c_str()));
	}
}
