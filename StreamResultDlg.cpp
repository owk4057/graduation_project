// StreamResultDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "StreamResultDlg.h"
#include "afxdialogex.h"


// StreamResultDlg 대화 상자

IMPLEMENT_DYNAMIC(StreamResultDlg, CDialogEx)

StreamResultDlg::StreamResultDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG7, pParent)
{

}

StreamResultDlg::~StreamResultDlg()
{
}

void StreamResultDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, stream_result_list);
	DDX_Control(pDX, IDC_COMBO1, stream_combo);
	DDX_Control(pDX, IDC_EDIT1, line_cnt_edit);
}

void StreamResultDlg::update() {

	stream->mtx.lock();
	stream_result_list.DeleteAllItems();

	auto it = stream->li.rbegin();
	int cnt = GetDlgItemInt(line_cnt_edit.GetDlgCtrlID());

	int i = 0;
	while (i < cnt && it != stream->li.rend() ) {
		stream_result_list.InsertItem(i, __T("abc"));
		int j = 0;
		for (auto p : stream->event_type->v) {
			stream_result_list.SetItem(i, j, LVIF_TEXT, CString(String(it->at(j)).c_str()), 0, 0, 0, NULL);
			j++;
		}
		it++;
		i++;
	}
	stream->mtx.unlock();
}

void StreamResultDlg::Init(string stream_name) {
	stream = StreamStorage::getStream(stream_name);
	stream_result_list.DeleteAllItems(); // 리스트 스타일 설정 
	stream_result_list.SetExtendedStyle(LVS_EX_GRIDLINES); // 타이틀 삽입 
	stream_combo.SetCurSel(0);

	int i = 0;
	for (auto p : stream->event_type->v) {
		string attr_name = p.second;
		stream_result_list.InsertColumn(i++, CString(attr_name.c_str()), LVCFMT_LEFT, 100, -1);
	}
}


BEGIN_MESSAGE_MAP(StreamResultDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &StreamResultDlg::OnBnClickedButton1)
	ON_CBN_DROPDOWN(IDC_COMBO1, &StreamResultDlg::OnCbnDropdownCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO1, &StreamResultDlg::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()


// StreamResultDlg 메시지 처리기


void StreamResultDlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	update();
}


void StreamResultDlg::OnCbnDropdownCombo1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	stream_combo.ResetContent();
	for (auto p : StreamStorage::m) 
		stream_combo.AddString(CString(p.first.c_str()));
}


void StreamResultDlg::OnCbnSelchangeCombo1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str;
	stream_combo.GetLBText(stream_combo.GetCurSel(), str);
	string stream_name = (CT2CA)str;

	if (stream->stream_name != stream_name) {
		stream_result_list.DeleteAllItems();
		for (auto p : stream->event_type->v)
			stream_result_list.DeleteColumn(0);
		stream = StreamStorage::getStream(stream_name);
		int i = 0;
		for (auto p : stream->event_type->v) {
			string attr_name = p.second;
			stream_result_list.InsertColumn(i++, CString(attr_name.c_str()), LVCFMT_LEFT, 100, -1);
		}
	}
}


void StreamResultDlg::OnStnClickedPic1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
