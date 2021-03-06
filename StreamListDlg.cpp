// StreamListDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "StreamListDlg.h"
#include "afxdialogex.h"

#include <string>

// StreamListDlg 대화 상자

IMPLEMENT_DYNAMIC(StreamListDlg, CDialogEx)

StreamListDlg::StreamListDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG4, pParent)
{

}

StreamListDlg::~StreamListDlg()
{
}

void StreamListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, stream_list);
	DDX_Control(pDX, IDC_COMBO1, stream_combo);

	stream_list.DeleteAllItems(); // 리스트 스타일 설정 
	stream_list.SetExtendedStyle(LVS_EX_GRIDLINES); // 타이틀 삽입 
	stream_list.InsertColumn(0, _T(""), LVCFMT_LEFT, 140, -1);
	stream_list.InsertColumn(1, _T(""), LVCFMT_CENTER, 109, -1);
}


BEGIN_MESSAGE_MAP(StreamListDlg, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO1, &StreamListDlg::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()


// StreamListDlg 메시지 처리기


void StreamListDlg::update() {
	stream_combo.ResetContent();
	for (auto p : StreamStorage::m) {
		stream_combo.AddString(CString(p.first.c_str()));
	}
	stream_combo.SetCurSel(0);

	CString str;
	stream_combo.GetLBText(0, str);
	string stream_name = (CT2CA)str;
	Stream * stream = StreamStorage::getStream(stream_name);

	stream_list.DeleteAllItems();
	stream_list.InsertItem(0, CString("stream name"));
	stream_list.SetItem(0, 1, LVIF_TEXT, CString(stream_name.c_str()), 0, 0, 0, NULL);
	stream_list.InsertItem(1, CString("event type"));
	stream_list.SetItem(1, 1, LVIF_TEXT, CString(stream->event_type->name.c_str()), 0, 0, 0, NULL);
	stream_list.InsertItem(2, CString("stream size"));
	stream_list.SetItem(2, 1, LVIF_TEXT, CString(to_string(stream->length).c_str()), 0, 0, 0, NULL);
	
}

void StreamListDlg::OnCbnSelchangeCombo1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str;
	stream_combo.GetLBText(stream_combo.GetCurSel(), str);
	string stream_name = (CT2CA)str;
	Stream * stream = StreamStorage::getStream(stream_name);

	stream_list.DeleteAllItems();
	stream_list.InsertItem(0, CString("stream name"));
	stream_list.SetItem(0, 1, LVIF_TEXT, CString(stream_name.c_str()), 0, 0, 0, NULL);
	stream_list.InsertItem(1, CString("event type"));
	stream_list.SetItem(1, 1, LVIF_TEXT, CString(stream->event_type->name.c_str()), 0, 0, 0, NULL);
	stream_list.InsertItem(2, CString("stream size"));
	stream_list.SetItem(2, 1, LVIF_TEXT, CString(to_string(stream->length).c_str()), 0, 0, 0, NULL);
}
