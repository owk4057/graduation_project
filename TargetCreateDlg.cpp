// TargetCreateDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "TargetCreateDlg.h"
#include "afxdialogex.h"


// TargetCreateDlg 대화 상자

IMPLEMENT_DYNAMIC(TargetCreateDlg, CDialogEx)

TargetCreateDlg::TargetCreateDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG9, pParent)
{

}

TargetCreateDlg::~TargetCreateDlg()
{
}

void TargetCreateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT4, min_count_edit);
	DDX_Control(pDX, IDC_EDIT9, max_count_edit);
	DDX_Control(pDX, IDC_EDIT5, min_x_edit);
	DDX_Control(pDX, IDC_EDIT7, max_x_edit);
	DDX_Control(pDX, IDC_EDIT6, min_y_edit);
	DDX_Control(pDX, IDC_EDIT8, max_y_edit);
	DDX_Control(pDX, IDC_LIST1, simulator_info);
	DDX_Control(pDX, IDC_COMBO1, type_a_combo);
	DDX_Control(pDX, IDC_COMBO2, type_b_combo);
}

void TargetCreateDlg::Init(Simulator * simulator)
{
	this->simulator = simulator;
	simulator_info.SetExtendedStyle(LVS_EX_GRIDLINES); // 타이틀 삽입 
	simulator_info.InsertColumn(0, __T("표적 타입"), LVCFMT_CENTER, 100, -1);
	simulator_info.InsertColumn(1, __T("수"), LVCFMT_CENTER, 100, -1);
	simulator_info.InsertItem(0,__T("airliner"));
	simulator_info.InsertItem(1,__T("helicopter"));
	simulator_info.InsertItem(2,__T("fighter"));
	simulator_info.InsertItem(3,__T("fishingboat"));
	simulator_info.InsertItem(4,__T("cruise"));
	simulator_info.InsertItem(5,__T("surface"));
	simulator_info.InsertItem(6,__T("submarine"));
	simulator_info.InsertItem(7,__T("undefined"));

	type_a_combo.InsertString(0, __T("random"));
	type_a_combo.InsertString(1, __T("aerial"));
	type_a_combo.InsertString(2, __T("sea"));
	type_a_combo.InsertString(3, __T("underwater"));
	type_a_combo.SetCurSel(0);

	type_b_combo.InsertString(0, __T("random"));
	type_b_combo.SetCurSel(0);
}

BEGIN_MESSAGE_MAP(TargetCreateDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &TargetCreateDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON4, &TargetCreateDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON3, &TargetCreateDlg::OnBnClickedButton3)
	ON_CBN_DROPDOWN(IDC_COMBO1, &TargetCreateDlg::OnCbnDropdownCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO1, &TargetCreateDlg::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()


// TargetCreateDlg 메시지 처리기

//표적 추가
void TargetCreateDlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str;

	int type_a = type_a_combo.GetCurSel();
	int type_b = type_b_combo.GetCurSel();

	min_count_edit.GetWindowTextW(str);
	int min_count = stoi((string)(CT2CA)str);
	max_count_edit.GetWindowTextW(str);
	int max_count = stoi((string)(CT2CA)str);

	min_x_edit.GetWindowTextW(str);
	int min_x = stoi((string)(CT2CA)str) * 1000;
	max_x_edit.GetWindowTextW(str);
	int max_x = stoi((string)(CT2CA)str) * 1000;
	min_y_edit.GetWindowTextW(str);
	int min_y = stoi((string)(CT2CA)str) * 1000;
	max_y_edit.GetWindowTextW(str);
	int max_y = stoi((string)(CT2CA)str) * 1000;

	if (max_x < min_x || max_y < min_y || max_count < min_count) {
		AfxMessageBox(__T("입력값이 잘못되었습니다."));
		return;
	}

	int count = rand() % (max_count - min_count) + min_count;
	simulator->Add({type_a,type_b}, count, Rect(min_x , min_y, max_x, max_y));

	simulator_info.SetItem(0, 1, LVIF_TEXT, CString(to_string(simulator->target_type_map.at("airliner")).c_str()), 0, 0, 0, NULL);
	simulator_info.SetItem(1, 1, LVIF_TEXT, CString(to_string(simulator->target_type_map.at("helicopter")).c_str()), 0, 0, 0, NULL);
	simulator_info.SetItem(2, 1, LVIF_TEXT, CString(to_string(simulator->target_type_map.at("fighter")).c_str()), 0, 0, 0, NULL);
	simulator_info.SetItem(3, 1, LVIF_TEXT, CString(to_string(simulator->target_type_map.at("fishingboat")).c_str()), 0, 0, 0, NULL);
	simulator_info.SetItem(4, 1, LVIF_TEXT, CString(to_string(simulator->target_type_map.at("cruise")).c_str()), 0, 0, 0, NULL);
	simulator_info.SetItem(5, 1, LVIF_TEXT, CString(to_string(simulator->target_type_map.at("surface")).c_str()), 0, 0, 0, NULL);
	simulator_info.SetItem(6, 1, LVIF_TEXT, CString(to_string(simulator->target_type_map.at("submarine")).c_str()), 0, 0, 0, NULL);
	simulator_info.SetItem(7, 1, LVIF_TEXT, CString(to_string(simulator->target_type_map.at("undefined")).c_str()), 0, 0, 0, NULL);
}
void TargetCreateDlg::OnBnClickedButton4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	simulator->start();
}
void TargetCreateDlg::OnBnClickedButton3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	simulator->clear();
	simulator_info.SetItem(0, 1, LVIF_TEXT, CString(to_string(simulator->target_type_map.at("airliner")).c_str()), 0, 0, 0, NULL);
	simulator_info.SetItem(1, 1, LVIF_TEXT, CString(to_string(simulator->target_type_map.at("helicopter")).c_str()), 0, 0, 0, NULL);
	simulator_info.SetItem(2, 1, LVIF_TEXT, CString(to_string(simulator->target_type_map.at("fighter")).c_str()), 0, 0, 0, NULL);
	simulator_info.SetItem(3, 1, LVIF_TEXT, CString(to_string(simulator->target_type_map.at("fishingboat")).c_str()), 0, 0, 0, NULL);
	simulator_info.SetItem(4, 1, LVIF_TEXT, CString(to_string(simulator->target_type_map.at("cruise")).c_str()), 0, 0, 0, NULL);
	simulator_info.SetItem(5, 1, LVIF_TEXT, CString(to_string(simulator->target_type_map.at("surface")).c_str()), 0, 0, 0, NULL);
	simulator_info.SetItem(6, 1, LVIF_TEXT, CString(to_string(simulator->target_type_map.at("submarine")).c_str()), 0, 0, 0, NULL);
	simulator_info.SetItem(7, 1, LVIF_TEXT, CString(to_string(simulator->target_type_map.at("undefined")).c_str()), 0, 0, 0, NULL);
}


void TargetCreateDlg::OnCbnDropdownCombo1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void TargetCreateDlg::OnCbnSelchangeCombo1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int idx = type_a_combo.GetCurSel();

	type_b_combo.ResetContent();
	if (idx == 0) {
		type_b_combo.InsertString(0, __T("random"));
	}
	else if (idx == 1) {
		type_b_combo.InsertString(0, __T("random"));
		type_b_combo.InsertString(1, __T("airliner"));
		type_b_combo.InsertString(2, __T("helicopter"));
		type_b_combo.InsertString(3, __T("fighter"));
	}
	else if (idx == 2) {
		type_b_combo.InsertString(0, __T("random"));
		type_b_combo.InsertString(1, __T("fishing boat"));
		type_b_combo.InsertString(2, __T("cruise"));
		type_b_combo.InsertString(3, __T("surface"));
	}
	else if (idx == 3) {
		type_b_combo.InsertString(0, __T("random"));
		type_b_combo.InsertString(1, __T("submarine"));
	}
	type_b_combo.SetCurSel(0);
}
