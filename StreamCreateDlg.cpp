// StreamCreateDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "StreamCreateDlg.h"
#include "afxdialogex.h"


// StreamCreateDlg 대화 상자

IMPLEMENT_DYNAMIC(StreamCreateDlg, CDialogEx)

StreamCreateDlg::StreamCreateDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG3, pParent)
{

}

StreamCreateDlg::~StreamCreateDlg()
{
}

void StreamCreateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, stream_name_edit);
	DDX_Control(pDX, IDC_EDIT3, stream_size_edit);
	DDX_Control(pDX, IDC_BUTTON1, stream_create_btn);
	DDX_Control(pDX, IDC_COMBO1, event_type_combo);
}


BEGIN_MESSAGE_MAP(StreamCreateDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &StreamCreateDlg::OnBnClickedButton1)
	ON_CBN_DROPDOWN(IDC_COMBO1, &StreamCreateDlg::OnCbnDropdownCombo1)
END_MESSAGE_MAP()


// StreamCreateDlg 메시지 처리기


//스트림 생성
void StreamCreateDlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str;
	stream_name_edit.GetWindowTextW(str);
	string stream_name = (CT2CA)str;
	event_type_combo.GetWindowTextW(str);
	string event_type_name = (CT2CA)str;
	stream_size_edit.GetWindowTextW(str);
	string stream_size_s = (CT2CA)str;

	StreamStorage::addStream(stream_name, event_type_name, atoi(stream_size_s.c_str()));
}


void StreamCreateDlg::OnCbnDropdownCombo1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	event_type_combo.ResetContent();
	int i = 0;
	for (auto p : EventTypeStorage::m) 
		event_type_combo.InsertString(i++, CString(p.second->getName().c_str()));
}
