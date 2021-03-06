
// MFCApplication2Dlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "MFCApplication2Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};
CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}
void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplication2Dlg 대화 상자
CMFCApplication2Dlg::CMFCApplication2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION2_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}
void CMFCApplication2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB2, event_type_tab);
	DDX_Control(pDX, IDC_TAB3, stream_tab);
	DDX_Control(pDX, IDC_TAB5, query_tab);
	DDX_Control(pDX, IDC_TAB4, result_tab);
	DDX_Control(pDX, IDC_TAB1, simulator_tab);
}
BEGIN_MESSAGE_MAP(CMFCApplication2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB2, &CMFCApplication2Dlg::OnTcnSelchangeTab1)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB3, &CMFCApplication2Dlg::OnTcnSelchangeTab2)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB5, &CMFCApplication2Dlg::OnTcnSelchangeTab3)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CMFCApplication2Dlg::OnTcnSelchangeTab5)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB4, &CMFCApplication2Dlg::OnTcnSelchangeTab4)
END_MESSAGE_MAP()


// CMFCApplication2Dlg 메시지 처리기
BOOL CMFCApplication2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	CRect rect;

	Init();
	//이벤트 타입 탭
	event_type_tab.InsertItem(0, __T("이벤트 타입 추가"));
	event_type_tab.InsertItem(1, __T("이벤트 타입 목록"));
	event_type_tab.SetCurSel(0);
	event_type_tab.GetWindowRect(&rect);

	event_type_create_dlg = new EventTypeCreateDlg;
	event_type_create_dlg->Create(IDD_DIALOG1, &event_type_tab);
	event_type_create_dlg->Init();
	event_type_create_dlg->MoveWindow(0, 20, rect.Width(), rect.Height()-20);
	event_type_create_dlg->ShowWindow(SW_SHOW);
	
	event_type_list_dlg = new EventTypeListDlg;
	event_type_list_dlg->Create(IDD_DIALOG2, &event_type_tab);
	event_type_list_dlg->Init();
	event_type_list_dlg->MoveWindow(0, 20, rect.Width(), rect.Height()-20);
	event_type_list_dlg->ShowWindow(SW_HIDE);
	
	//스트림 탭
	stream_tab.InsertItem(0, __T("스트림 추가"));
	stream_tab.InsertItem(1, __T("스트림 목록"));
	stream_tab.SetCurSel(0);
	stream_tab.GetWindowRect(&rect);

	stream_create_dlg = new StreamCreateDlg;
	stream_create_dlg->Create(IDD_DIALOG3, &stream_tab);
	stream_create_dlg->MoveWindow(0, 20, rect.Width(), rect.Height()-20);
	stream_create_dlg->ShowWindow(SW_SHOW);

	stream_list_dlg = new StreamListDlg;
	stream_list_dlg->Create(IDD_DIALOG4, &stream_tab);
	stream_list_dlg->MoveWindow(0, 20, rect.Width(), rect.Height()-20);
	stream_list_dlg->ShowWindow(SW_HIDE);

	//쿼리 탭
	query_tab.InsertItem(0, __T("필터 쿼리 추가"));
	query_tab.InsertItem(1, __T("그룹 쿼리 추가"));
	query_tab.InsertItem(2, __T("쿼리 목록"));
	query_tab.SetCurSel(0);
	query_tab.GetWindowRect(&rect);

	filter_query_create_dlg = new FilterQueryCreateDlg;
	filter_query_create_dlg->Create(IDD_DIALOG5, &query_tab);
	filter_query_create_dlg->MoveWindow(0, 20, rect.Width(), rect.Height()-20);
	filter_query_create_dlg->ShowWindow(SW_SHOW);

	group_query_create_dlg = new GroupQueryCreateDlg;
	group_query_create_dlg->Create(IDD_DIALOG8, &query_tab);
	group_query_create_dlg->MoveWindow(0, 20, rect.Width(), rect.Height()-20);
	group_query_create_dlg->ShowWindow(SW_HIDE);

	query_list_dlg = new QueryListDlg;
	query_list_dlg->Create(IDD_DIALOG6, &query_tab);
	query_list_dlg->Init();
	query_list_dlg->MoveWindow(0, 20, rect.Width(), rect.Height()-20);
	query_list_dlg->ShowWindow(SW_HIDE);
	
	//결과 탭
	result_tab.InsertItem(0, __T("스트림 출력"));
	result_tab.InsertItem(1, __T("쿼리 그래프 출력"));
	result_tab.InsertItem(2, __T("쿼리 테이블 출력"));
	result_tab.SetCurSel(0);
	result_tab.GetWindowRect(&rect);

	stream_result_dlg = new StreamResultDlg;
	stream_result_dlg->Create(IDD_DIALOG7, &result_tab);
	stream_result_dlg->Init("target_detect_stream");
	stream_result_dlg->MoveWindow(0, 20, rect.Width(), rect.Height()-20);
	stream_result_dlg->ShowWindow(SW_SHOW);

	query_print_dlg = new QueryPrintDlg;
	query_print_dlg->Create(IDD_DIALOG11, &result_tab);
	query_print_dlg->Init();
	query_print_dlg->MoveWindow(0, 20, rect.Width(), rect.Height()-20);
	query_print_dlg->ShowWindow(SW_HIDE);

	warning_create_dlg = new WarningCreate;
	warning_create_dlg->Create(IDD_DIALOG10, &result_tab);
	warning_create_dlg->Init();
	warning_create_dlg->MoveWindow(0, 20, rect.Width(), rect.Height()-20);
	warning_create_dlg->ShowWindow(SW_HIDE);



	//시뮬레이터 탭
	simulator_tab.InsertItem(0, __T("표적 생성"));
	simulator_tab.SetCurSel(0);
	simulator_tab.GetWindowRect(&rect);

	target_create_dlg = new TargetCreateDlg;
	target_create_dlg->Create(IDD_DIALOG9, &simulator_tab);
	target_create_dlg->Init(simulator);
	target_create_dlg->MoveWindow(0, 20, rect.Width(), rect.Height()-20);
	target_create_dlg->ShowWindow(SW_SHOW);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCApplication2Dlg::Init() {
	InitAggregationStorage();
	EventTypeStorage::addEventType("Target", { { "Time_t", "time" },
		{ "int", "id" },
		{ "string", "type" },
		{ "int", "x" },
		{ "int", "y" },
		{ "int", "z" },
		{ "float", "dir" },
		{ "float", "vel" } });
	EventTypeStorage::addEventType("Target_Track", { { "Time_t", "time" },
		{ "int", "id" },
		{ "string", "type" }});
	StreamStorage::addStream("target_detect_stream", "Target", 1000000);
	StreamStorage::addStream("target_track_stream", "Target_Track", 1000000);
	Stream * in_stream = StreamStorage::getStream("target_detect_stream");
	Stream * out_stream = StreamStorage::getStream("target_track_stream");
	
	srand((unsigned int)time(NULL));
	simulator = new Simulator(&q, &q_mtx);
	extractor = new Extractor(in_stream, &q, &q_mtx, convertDataToEvent, 1000);

	bool result;
	Parser parser;
	vector<function<any(list<Event>&)>> select_funcs;
	select_funcs.emplace_back(parser.getSelectGroup("time", &result));
	select_funcs.emplace_back(parser.getSelectGroup("id", &result));
	select_funcs.emplace_back(parser.getSelectGroup("type", &result));
	
	TimeGroupQuery * query = new TimeGroupQuery("target_track_query",
		Range_t(50000000),
		in_stream,
		out_stream,
		{ "id" },
		"",
		parser.getWhere(string(""), &result),
		"",
		parser.getHaving(string(""), &result),
		{ "time", "id", "type" },
		select_funcs,
		1000);
	QueryStorage::addQuery("target_track_query", query);
	extractor->start();
}

void CMFCApplication2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCApplication2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCApplication2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication2Dlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int sel = event_type_tab.GetCurSel();

	switch (sel) {
	case 0 :
		event_type_create_dlg->ShowWindow(SW_SHOW);
		event_type_list_dlg->ShowWindow(SW_HIDE);
		break;
	case 1 :
		event_type_create_dlg->ShowWindow(SW_HIDE);
		event_type_list_dlg->ShowWindow(SW_SHOW);
		break;
	}
	*pResult = 0;
}


void CMFCApplication2Dlg::OnTcnSelchangeTab2(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int sel = stream_tab.GetCurSel();

	switch (sel) {
	case 0 :
		stream_create_dlg->ShowWindow(SW_SHOW);
		stream_list_dlg->ShowWindow(SW_HIDE);
		break;
	case 1 :
		stream_list_dlg->update();
		stream_create_dlg->ShowWindow(SW_HIDE);
		stream_list_dlg->ShowWindow(SW_SHOW);
		break;
	}
	*pResult = 0;
}


void CMFCApplication2Dlg::OnTcnSelchangeTab3(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int sel = query_tab.GetCurSel();

	switch (sel) {
	case 0 :
		filter_query_create_dlg->ShowWindow(SW_SHOW);
		group_query_create_dlg->ShowWindow(SW_HIDE);
		query_list_dlg->ShowWindow(SW_HIDE);
		break;
	case 1 :
		filter_query_create_dlg->ShowWindow(SW_HIDE);
		group_query_create_dlg->ShowWindow(SW_SHOW);
		query_list_dlg->ShowWindow(SW_HIDE);
		break;
	case 2 :
		filter_query_create_dlg->ShowWindow(SW_HIDE);
		group_query_create_dlg->ShowWindow(SW_HIDE);
		query_list_dlg->ShowWindow(SW_SHOW);
		break;
	}
	*pResult = 0;
}


void CMFCApplication2Dlg::OnTcnSelchangeTab5(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int sel = simulator_tab.GetCurSel();

	switch (sel) {
	case 0 :
		target_create_dlg->ShowWindow(SW_SHOW);
		break;
	case 1 :
		target_create_dlg->ShowWindow(SW_HIDE);
		break;
	}
	*pResult = 0;
}


void CMFCApplication2Dlg::OnTcnSelchangeTab4(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int sel = result_tab.GetCurSel();

	switch (sel) {
	case 0 :
		stream_result_dlg->ShowWindow(SW_SHOW);
		query_print_dlg->ShowWindow(SW_HIDE);
		warning_create_dlg->ShowWindow(SW_HIDE);
		break;
	case 1 :
		stream_result_dlg->ShowWindow(SW_HIDE);
		query_print_dlg->ShowWindow(SW_SHOW);
		warning_create_dlg->ShowWindow(SW_HIDE);
		break;
	case 2 :
		stream_result_dlg->ShowWindow(SW_HIDE);
		query_print_dlg->ShowWindow(SW_HIDE);
		warning_create_dlg->ShowWindow(SW_SHOW);
		break;
	}
	*pResult = 0;
}
