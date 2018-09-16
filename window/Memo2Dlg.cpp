
// Memo2Dlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "Memo2.h"
#include "Memo2Dlg.h"
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
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMemo2Dlg 대화 상자



CMemo2Dlg::CMemo2Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMemo2Dlg::IDD, pParent)
	, m_num(0)
	, m_tray(false)
	, m_flag(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMemo2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDC_BUTTON1, m_b1);
	DDX_Control(pDX, IDC_BUTTON3, m_b2);
	DDX_Control(pDX, IDC_DELETE, m_b3);
}

BEGIN_MESSAGE_MAP(CMemo2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMemo2Dlg::OnBnClickedButton1)
	ON_COMMAND(ID_32771, &CMemo2Dlg::On32771)
	ON_COMMAND(ID_32772, &CMemo2Dlg::On32772)
	ON_MESSAGE(WM_TRAY_NOTIFICATION, OnTrayNotification)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDCANCEL, &CMemo2Dlg::OnBnClickedCancel)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CMemo2Dlg::OnNMDblclkList1)
	ON_BN_CLICKED(IDC_DELETE, &CMemo2Dlg::OnBnClickedDelete)
	ON_BN_CLICKED(IDC_BUTTON3, &CMemo2Dlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CMemo2Dlg 메시지 처리기

BOOL CMemo2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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
	
	m_loginWindow.DoModal();
	id = m_loginWindow.m_id;

	m_tray = FALSE;
	RegistTray();
	//MessageBox(_T("제목 보여주기 시도!"), MB_OK);
	CString titlequery, temp, title, numquery;
	temp.Format(_T("'"));

	titlequery.Format(_T("select title from content where id='"));
	numquery.Format(_T("select num from content where id='"));
	titlequery = titlequery + id + temp;
	numquery = numquery + id + temp;

	char* titlequery2 = CString2char(titlequery);
	char* numquery2 = CString2char(numquery);
	MYSQL m_MySql;
	MYSQL_RES* m_Res;
	MYSQL_RES* m_Res2;
	MYSQL_ROW row;
	MYSQL_ROW row2;
	char *pResult;
	char *pResult2;

	mysql_init(&m_MySql);

	if (id != "")
	{
		if (mysql_real_connect(&m_MySql, ADDRESS, ID, PASSWD, DBNAME, 3306, NULL, 0) == NULL)
		{
			//AfxMessageBox(_T("연결실패ㅠㅠ"));
			return true;
		}
		//AfxMessageBox(_T("연결성공!^^"));
		if (mysql_query(&m_MySql, titlequery2) == NULL)
		{
			 //AfxMessageBox(_T("쿼리요청성공"));
			//return;
		}

		if ((m_Res = mysql_store_result(&m_MySql)) == NULL)
		{ // 결과를 m_Res에 저장
			//AfxMessageBox(_T("결과저장실패ㅠㅠ"));
		}

		//AfxMessageBox(_T("결과저장성공"));

		for (int i = 0; i < mysql_num_rows(m_Res); i++){
			row = mysql_fetch_row(m_Res);
			pResult = row[0];
			title = char2CString(pResult);
			//AfxMessageBox(title);
			m_list.InsertItem(i, title);
		}

		if (mysql_query(&m_MySql, numquery2) == NULL)
		{
			//AfxMessageBox(_T("쿼리요청성공"));
			//return;
		}

		if ((m_Res2 = mysql_store_result(&m_MySql)) == NULL)
		{ // 결과를 m_Res에 저장
			AfxMessageBox(_T("결과저장실패ㅠㅠ"));
		}
		for (int i = 0; i < mysql_num_rows(m_Res2); i++){
			row2 = mysql_fetch_row(m_Res2);
			pResult2 = row2[0];
			CString a = char2CString(pResult2);

			v.push_back(a);

			//AfxMessageBox(v.at(i));
		}
	}
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMemo2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else if (nID == SC_CLOSE)
	{
		ShowWindow(SW_HIDE);
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMemo2Dlg::OnPaint()
{
	CClientDC dc(this);
	CRect r;
	GetClientRect(&r);
	dc.FillSolidRect(r,RGB(206,251,201));
	m_b1.SetFaceColor(RGB(186, 229, 92));
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
	if (!m_loginWindow.m_check_login)
	{
		this->EndDialog(IDOK);
	}

}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMemo2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMemo2Dlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_flag = false;
	MakeNewMemo();
}

BOOL CMemo2Dlg::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.


	return CDialogEx::PreCreateWindow(cs);
}


void CMemo2Dlg::MakeNewMemo()
{
	CPostIt* post = new CPostIt;
	m_post_it.push_back(post);
	m_num = m_post_it.size() - 1;
	if (m_flag)
	{
		//MessageBox(_T("제목 보여주기 시도!"), MB_OK);
		CString titlequery, temp, numquery, contentquery;

		titlequery.Format(_T("select title from content where num="));
		numquery.Format(_T("select content from content where num="));
		
		titlequery = titlequery + m_num2;
		contentquery = numquery + m_num2;

		char* titlequery2 = CString2char(titlequery);
		char* contentquery2 = CString2char(contentquery);
		MYSQL m_MySql;
		MYSQL_RES* m_Res;
		MYSQL_RES* m_Res2;
		MYSQL_ROW row;
		MYSQL_ROW row2;
		char *pResult;
		char *pResult2;

		mysql_init(&m_MySql);
		mysql_query(&m_MySql, "set names utf8");
		if (mysql_real_connect(&m_MySql, ADDRESS, ID, PASSWD, DBNAME, 3306, NULL, 0) == NULL)
		{
			AfxMessageBox(_T("연결실패ㅠㅠ"));
			return;
		}
		//AfxMessageBox(_T("연결성공!^^"));
		if (mysql_query(&m_MySql, titlequery2) == NULL)
		{
			 //  AfxMessageBox(_T("쿼리요청성공"));
			//return;
		}

		if ((m_Res = mysql_store_result(&m_MySql)) == NULL)
		{ // 결과를 m_Res에 저장
			//   AfxMessageBox(_T("결과저장실패ㅠㅠ"));
		}

		///AfxMessageBox(_T("결과저장성공"));

		row = mysql_fetch_row(m_Res);
		pResult = row[0];

		m_post_it[m_num]->m_title = char2CString(pResult);


		if (mysql_query(&m_MySql, contentquery2) == NULL)
		{
		// AfxMessageBox(_T("쿼리요청성공"));
			//return;
		}

		if ((m_Res2 = mysql_store_result(&m_MySql)) == NULL)
		{ // 결과를 m_Res에 저장
			//   AfxMessageBox(_T("결과저장실패ㅠㅠ"));
		}

		row2 = mysql_fetch_row(m_Res2);
		pResult2 = row2[0];
		m_post_it[m_num]->m_content = char2CString(pResult2);
	}

	m_post_it[m_num]->m_flag = m_flag;
	m_post_it[m_num]->m_num = m_num2;
	m_post_it[m_num]->m_id = id;
	m_post_it[m_num]->m_index = column;
	m_post_it[m_num]->Create(IDD_DIALOG1, ((CMemo2Dlg*)GetParent()));
	m_post_it[m_num]->ShowWindow(SW_SHOW);

	m_post_it[m_num]->SetFocus();
	
}


void CMemo2Dlg::CloseMain()
{
	if (m_tray) // 현재 트레이 아이콘으로 설정되었는지 확인 
	{
		NOTIFYICONDATA  nid;
		nid.cbSize = sizeof(nid);
		nid.hWnd = m_hWnd; // 메인 윈도우 핸들
		nid.uID = IDR_MAINFRAME;

		// 작업 표시줄(TaskBar)의 상태 영역에 아이콘을 삭제한다.
		Shell_NotifyIcon(NIM_DELETE, &nid);
	}
	this->EndDialog(IDOK);
}

BOOL CMemo2Dlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CMemo2Dlg::On32771()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	AfxGetApp()->m_pMainWnd->ShowWindow(SW_SHOW);
}


void CMemo2Dlg::On32772()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	this->DestroyWindow();
}


LRESULT CMemo2Dlg::OnTrayNotification(WPARAM wParam, LPARAM lParam)
{
	switch (lParam)
	{
	case WM_RBUTTONDOWN:
	{
		CPoint ptMouse;
		::GetCursorPos(&ptMouse);
		CMenu menu;
		menu.LoadMenu(IDR_MAINFRAME);
		CMenu *pMenu = new CMenu(); //활성화 할 메뉴 지정
		pMenu->LoadMenuW(IDR_MENU1);
		pMenu->GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,
			ptMouse.x, ptMouse.y, this);
	}
	break;
	case WM_LBUTTONDBLCLK:
	{
		ShowWindow(SW_SHOW);
	}
	break;
	}
	return 1;
}

void CMemo2Dlg::RegistTray()
{
	NOTIFYICONDATA  nid;
	nid.cbSize = sizeof(nid);
	nid.hWnd = m_hWnd; // 메인 윈도우 핸들
	nid.uID = IDR_MAINFRAME;  // 아이콘 리소스 ID
	nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP; // 플래그 설정
	nid.uCallbackMessage = WM_TRAY_NOTIFICATION; // 콜백메시지 설정
	nid.hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME); // 아이콘 로드
	CString strTitle;
	GetWindowText(strTitle); // 캡션바에 출력된 문자열 얻음
	lstrcpy(nid.szTip, strTitle);
	Shell_NotifyIcon(NIM_ADD, &nid);
	SendMessage(WM_SETICON, (WPARAM)TRUE, (LPARAM)nid.hIcon);
	m_tray = TRUE;
}


void CMemo2Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (m_tray) // 현재 트레이 아이콘으로 설정되었는지 확인 
	{
		NOTIFYICONDATA  nid;
		nid.cbSize = sizeof(nid);
		nid.hWnd = m_hWnd; // 메인 윈도우 핸들
		nid.uID = IDR_MAINFRAME;

		// 작업 표시줄(TaskBar)의 상태 영역에 아이콘을 삭제한다.
		Shell_NotifyIcon(NIM_DELETE, &nid);
	}
}


void CMemo2Dlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CloseMain();
}


void CMemo2Dlg::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;

	 column = m_list.GetNextItem(-1,LVNI_SELECTED);
	 if (column >= 0)
	 {
		 m_num2 = v.at(column);
		 m_flag = true;
		 MakeNewMemo();
	 }
}


void CMemo2Dlg::OnBnClickedDelete()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int node = m_list.GetNextItem(-1, LVNI_SELECTED);
	if (node >= 0)
	{
		CString num = v[node];
		CString titlequery;

		titlequery.Format(_T("delete from content where num="));
		titlequery = titlequery + num;

		char* titlequery2 = CString2char(titlequery);

		MYSQL m_MySql;
		MYSQL_RES* m_Res;
		MYSQL_ROW row;
		char *pResult;

		mysql_init(&m_MySql);

		if (mysql_real_connect(&m_MySql, ADDRESS, ID, PASSWD, DBNAME, 3306, NULL, 0) == NULL)
		{
			AfxMessageBox(_T("연결실패ㅠㅠ"));
			return;
		}
		//AfxMessageBox(_T("연결성공!^^"));
		if (mysql_query(&m_MySql, "set names euckr") == NULL)
		{
			//AfxMessageBox(_T("쿼리요청성공"));
			//return;
		}
		if (mysql_query(&m_MySql, titlequery2) == NULL)
		{
			//   AfxMessageBox(_T("쿼리요청성공"));
			//return;
		}

		if ((m_Res = mysql_store_result(&m_MySql)) == NULL)
		{ // 결과를 m_Res에 저장
			//   AfxMessageBox(_T("결과저장실패ㅠㅠ"));
		}

		v.erase(v.begin() + node);
		m_list.DeleteItem(node);
		m_list.Invalidate(true);
	}
}


void CMemo2Dlg::OnBnClickedButton3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	column = m_list.GetNextItem(-1, LVNI_SELECTED);
	if (column >= 0)
	{
		m_num2 = v.at(column);
		m_flag = true;
		MakeNewMemo();
	}
}

void CMemo2Dlg::OnUpdateList(){
	//MessageBox(_T("제목 보여주기 시도!"), MB_OK);
	CString titlequery, temp, title, numquery;
	temp.Format(_T("'"));
	char* titlequery2 = CString2char(titlequery);
	char* numquery2 = CString2char(numquery);
	MYSQL m_MySql;
	MYSQL_RES* m_Res;
	MYSQL_RES* m_Res2;
	MYSQL_ROW row;
	MYSQL_ROW row2;
	char *pResult;
	char *pResult2;

	mysql_init(&m_MySql);

	if (id != "")
	{
		if (mysql_real_connect(&m_MySql, ADDRESS, ID, PASSWD, DBNAME, 3306, NULL, 0) == NULL)
		{
			//AfxMessageBox(_T("연결실패ㅠㅠ"));
			return;
		}
		//AfxMessageBox(_T("연결성공!^^"));
		if (mysql_query(&m_MySql, titlequery2) == NULL)
		{
			//AfxMessageBox(_T("쿼리요청성공"));
			//return;
		}

		if ((m_Res = mysql_store_result(&m_MySql)) == NULL)
		{ // 결과를 m_Res에 저장
			//AfxMessageBox(_T("결과저장실패ㅠㅠ"));
		}

		//AfxMessageBox(_T("결과저장성공"));

		for (int i = 0; i < mysql_num_rows(m_Res); i++){
			row = mysql_fetch_row(m_Res);
			pResult = row[0];
			title = char2CString(pResult);
			//AfxMessageBox(title);
			m_list.InsertItem(i, title);
		}

		if (mysql_query(&m_MySql, numquery2) == NULL)
		{
			//AfxMessageBox(_T("쿼리요청성공"));
			//return;
		}

		if ((m_Res2 = mysql_store_result(&m_MySql)) == NULL)
		{ // 결과를 m_Res에 저장
		//	AfxMessageBox(_T("결과저장실패ㅠㅠ"));
		}
		for (int i = 0; i < mysql_num_rows(m_Res2); i++){
			row2 = mysql_fetch_row(m_Res2);
			pResult2 = row2[0];
			CString a = char2CString(pResult2);

			//v.push_back(a);

			//AfxMessageBox(v.at(i));
		}
	}
	m_list.Invalidate(false);

}
