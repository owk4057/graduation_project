// EventTypeCreateDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "EventTypeCreateDlg.h"
#include "afxdialogex.h"

#include <string>

// EventTypeCreateDlg 대화 상자

IMPLEMENT_DYNAMIC(EventTypeCreateDlg, CDialogEx)

EventTypeCreateDlg::EventTypeCreateDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{
}

EventTypeCreateDlg::~EventTypeCreateDlg()
{
}

void EventTypeCreateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, attr_type_combo);
	DDX_Control(pDX, IDC_EDIT1, attr_name_edit);
	DDX_Control(pDX, IDC_BUTTON1, event_type_create_btn);
	DDX_Control(pDX, IDC_BUTTON2, event_type_delete_btn);
	DDX_Control(pDX, IDC_LIST1, attr_list);
	DDX_Control(pDX, IDC_EDIT2, event_type_name_edit);
}

void EventTypeCreateDlg::Init() {
	attr_type_combo.InsertString(0, TEXT("int"));
	attr_type_combo.InsertString(1, TEXT("float"));
	attr_type_combo.InsertString(2, TEXT("string"));
	attr_type_combo.InsertString(3, TEXT("bool"));
	attr_type_combo.InsertString(4, TEXT("Time"));
	attr_type_combo.InsertString(5, TEXT("Time Duration"));
	attr_type_combo.SetCurSel(0);

	attr_list.DeleteAllItems(); // 리스트 스타일 설정 
	attr_list.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT); // 타이틀 삽입 
	attr_list.InsertColumn(0, _T("Attr Type"), LVCFMT_LEFT, 140, -1);
	attr_list.InsertColumn(1, _T("Attr Name"), LVCFMT_CENTER, 109, -1);
}

BEGIN_MESSAGE_MAP(EventTypeCreateDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &EventTypeCreateDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &EventTypeCreateDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &EventTypeCreateDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// EventTypeCreateDlg 메시지 처리기


//이벤트 타입 속성 추가
void EventTypeCreateDlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString attr_name;
	CString attr_type;
	attr_type_combo.GetWindowTextW(attr_type);
	attr_name_edit.GetWindowTextW(attr_name);
	string attr_name_string = (CT2CA)attr_name;

	for (int i = 0; i < attr_list.GetItemCount(); i++) {
		if (attr_name == attr_list.GetItemText(0, 1)) {
			AfxMessageBox(__T("이미 같은 이름의 속성이 존재합니다."));
			return;
		}
	}

	POSITION position = attr_list.GetFirstSelectedItemPosition(); 
	if (position != NULL) {
		int idx = attr_list.GetNextSelectedItem(position);
		attr_list.InsertItem(idx, attr_type); 
		attr_list.SetItem(idx, 1, LVIF_TEXT, attr_name, 0, 0, 0, NULL);
	}
	else {
		int idx = attr_list.GetItemCount();
		attr_list.InsertItem(idx, attr_type);
		attr_list.SetItem(idx, 1, LVIF_TEXT, attr_name, 0, 0, 0, NULL);
	}
}


//이벤트 타입 생성
void EventTypeCreateDlg::OnBnClickedButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	//이벤트 타입 이름 유효성 검사
	CString str;
	event_type_name_edit.GetWindowTextW(str);
	string event_type_name = (CT2CA)str;

	if (EventTypeStorage::getEventType(event_type_name) != NULL) {
		AfxMessageBox(__T("동일한 이름의 이벤트 타입이 이미 존재합니다."));
		return;
	}

	//이벤트 타입 속성 유효성 검사
	bool time_attr_exist = false;
	vector<pair<string, string>> attr_vec;
	int cnt = attr_list.GetItemCount();
	for (int i = 0; i < cnt; i++) {
		string attr_type = (CT2CA)attr_list.GetItemText(i, 0);
		string attr_name = (CT2CA)attr_list.GetItemText(i, 1);
		attr_vec.emplace_back(pair<string, string>(attr_type, attr_name));
		if (attr_name == "time")
			time_attr_exist = true;
	}
	if (!time_attr_exist) {
		AfxMessageBox(__T("Time_t 타입의 time 속성은 반드시 존재해야 합니다."));
		return;
	}
	attr_list.DeleteAllItems();
	EventTypeStorage::addEventType(event_type_name, attr_vec);
}

//이벤트 타입 속성 제거
void EventTypeCreateDlg::OnBnClickedButton3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	POSITION position = attr_list.GetFirstSelectedItemPosition(); 
	while (position != NULL) { 
		int idx = attr_list.GetNextSelectedItem(position);
		attr_list.DeleteItem(idx); 
		position = attr_list.GetFirstSelectedItemPosition();
	}

	
}
