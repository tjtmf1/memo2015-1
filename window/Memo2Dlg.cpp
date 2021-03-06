
// Memo2Dlg.cpp : 姥薄 督析
//

#include "stdafx.h"
#include "Memo2.h"
#include "Memo2Dlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 誓遂 覗稽益轡 舛左拭 紫遂鞠澗 CAboutDlg 企鉢 雌切脊艦陥.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 企鉢 雌切 汽戚斗脊艦陥.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 走据脊艦陥.

// 姥薄脊艦陥.
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


// CMemo2Dlg 企鉢 雌切



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


// CMemo2Dlg 五獣走 坦軒奄

BOOL CMemo2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 獣什奴 五敢拭 "舛左..." 五敢 牌鯉聖 蓄亜杯艦陥.

	// IDM_ABOUTBOX澗 獣什奴 誤敬 骨是拭 赤嬢醤 杯艦陥.
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

	// 戚 企鉢 雌切税 焼戚嬬聖 竺舛杯艦陥.  誓遂 覗稽益轡税 爽 但戚 企鉢 雌切亜 焼諌 井酔拭澗
	//  覗傾績趨滴亜 戚 拙穣聖 切疑生稽 呪楳杯艦陥.
	SetIcon(m_hIcon, TRUE);			// 笛 焼戚嬬聖 竺舛杯艦陥.
	SetIcon(m_hIcon, FALSE);		// 拙精 焼戚嬬聖 竺舛杯艦陥.

	// TODO: 食奄拭 蓄亜 段奄鉢 拙穣聖 蓄亜杯艦陥.
	
	m_loginWindow.DoModal();
	id = m_loginWindow.m_id;

	m_tray = FALSE;
	RegistTray();
	//MessageBox(_T("薦鯉 左食爽奄 獣亀!"), MB_OK);
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
			//AfxMessageBox(_T("尻衣叔鳶ばば"));
			return true;
		}
		//AfxMessageBox(_T("尻衣失因!^^"));
		if (mysql_query(&m_MySql, titlequery2) == NULL)
		{
			 //AfxMessageBox(_T("汀軒推短失因"));
			//return;
		}

		if ((m_Res = mysql_store_result(&m_MySql)) == NULL)
		{ // 衣引研 m_Res拭 煽舌
			//AfxMessageBox(_T("衣引煽舌叔鳶ばば"));
		}

		//AfxMessageBox(_T("衣引煽舌失因"));

		for (int i = 0; i < mysql_num_rows(m_Res); i++){
			row = mysql_fetch_row(m_Res);
			pResult = row[0];
			title = char2CString(pResult);
			//AfxMessageBox(title);
			m_list.InsertItem(i, title);
		}

		if (mysql_query(&m_MySql, numquery2) == NULL)
		{
			//AfxMessageBox(_T("汀軒推短失因"));
			//return;
		}

		if ((m_Res2 = mysql_store_result(&m_MySql)) == NULL)
		{ // 衣引研 m_Res拭 煽舌
			AfxMessageBox(_T("衣引煽舌叔鳶ばば"));
		}
		for (int i = 0; i < mysql_num_rows(m_Res2); i++){
			row2 = mysql_fetch_row(m_Res2);
			pResult2 = row2[0];
			CString a = char2CString(pResult2);

			v.push_back(a);

			//AfxMessageBox(v.at(i));
		}
	}
	return TRUE;  // 匂朕什研 珍闘継拭 竺舛馬走 省生檎 TRUE研 鋼発杯艦陥.
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

// 企鉢 雌切拭 置社鉢 舘蓄研 蓄亜拝 井酔 焼戚嬬聖 益軒形檎
//  焼掘 坪球亜 琶推杯艦陥.  庚辞/坂 乞季聖 紫遂馬澗 MFC 誓遂 覗稽益轡税 井酔拭澗
//  覗傾績趨滴拭辞 戚 拙穣聖 切疑生稽 呪楳杯艦陥.

void CMemo2Dlg::OnPaint()
{
	CClientDC dc(this);
	CRect r;
	GetClientRect(&r);
	dc.FillSolidRect(r,RGB(206,251,201));
	m_b1.SetFaceColor(RGB(186, 229, 92));
	if (IsIconic())
	{
		CPaintDC dc(this); // 益軒奄研 是廃 巨郊戚什 珍努什闘脊艦陥.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 適虞戚情闘 紫唖莫拭辞 焼戚嬬聖 亜錘汽拭 限嫡艦陥.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 焼戚嬬聖 益験艦陥.
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

// 紫遂切亜 置社鉢吉 但聖 塊澗 疑照拭 朕辞亜 妊獣鞠亀系 獣什奴拭辞
//  戚 敗呪研 硲窒杯艦陥.
HCURSOR CMemo2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMemo2Dlg::OnBnClickedButton1()
{
	// TODO: 食奄拭 珍闘継 硝顕 坦軒奄 坪球研 蓄亜杯艦陥.
	m_flag = false;
	MakeNewMemo();
}

BOOL CMemo2Dlg::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 食奄拭 働呪鉢吉 坪球研 蓄亜 貢/暁澗 奄沙 適掘什研 硲窒杯艦陥.


	return CDialogEx::PreCreateWindow(cs);
}


void CMemo2Dlg::MakeNewMemo()
{
	CPostIt* post = new CPostIt;
	m_post_it.push_back(post);
	m_num = m_post_it.size() - 1;
	if (m_flag)
	{
		//MessageBox(_T("薦鯉 左食爽奄 獣亀!"), MB_OK);
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
			AfxMessageBox(_T("尻衣叔鳶ばば"));
			return;
		}
		//AfxMessageBox(_T("尻衣失因!^^"));
		if (mysql_query(&m_MySql, titlequery2) == NULL)
		{
			 //  AfxMessageBox(_T("汀軒推短失因"));
			//return;
		}

		if ((m_Res = mysql_store_result(&m_MySql)) == NULL)
		{ // 衣引研 m_Res拭 煽舌
			//   AfxMessageBox(_T("衣引煽舌叔鳶ばば"));
		}

		///AfxMessageBox(_T("衣引煽舌失因"));

		row = mysql_fetch_row(m_Res);
		pResult = row[0];

		m_post_it[m_num]->m_title = char2CString(pResult);


		if (mysql_query(&m_MySql, contentquery2) == NULL)
		{
		// AfxMessageBox(_T("汀軒推短失因"));
			//return;
		}

		if ((m_Res2 = mysql_store_result(&m_MySql)) == NULL)
		{ // 衣引研 m_Res拭 煽舌
			//   AfxMessageBox(_T("衣引煽舌叔鳶ばば"));
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
	if (m_tray) // 薄仙 闘傾戚 焼戚嬬生稽 竺舛鞠醸澗走 溌昔 
	{
		NOTIFYICONDATA  nid;
		nid.cbSize = sizeof(nid);
		nid.hWnd = m_hWnd; // 五昔 制亀酔 輩級
		nid.uID = IDR_MAINFRAME;

		// 拙穣 妊獣匝(TaskBar)税 雌殿 慎蝕拭 焼戚嬬聖 肢薦廃陥.
		Shell_NotifyIcon(NIM_DELETE, &nid);
	}
	this->EndDialog(IDOK);
}

BOOL CMemo2Dlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 食奄拭 働呪鉢吉 坪球研 蓄亜 貢/暁澗 奄沙 適掘什研 硲窒杯艦陥.
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CMemo2Dlg::On32771()
{
	// TODO: 食奄拭 誤敬 坦軒奄 坪球研 蓄亜杯艦陥.
	AfxGetApp()->m_pMainWnd->ShowWindow(SW_SHOW);
}


void CMemo2Dlg::On32772()
{
	// TODO: 食奄拭 誤敬 坦軒奄 坪球研 蓄亜杯艦陥.
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
		CMenu *pMenu = new CMenu(); //醗失鉢 拝 五敢 走舛
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
	nid.hWnd = m_hWnd; // 五昔 制亀酔 輩級
	nid.uID = IDR_MAINFRAME;  // 焼戚嬬 軒社什 ID
	nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP; // 巴掘益 竺舛
	nid.uCallbackMessage = WM_TRAY_NOTIFICATION; // 紬拷五獣走 竺舛
	nid.hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME); // 焼戚嬬 稽球
	CString strTitle;
	GetWindowText(strTitle); // 銚芝郊拭 窒径吉 庚切伸 条製
	lstrcpy(nid.szTip, strTitle);
	Shell_NotifyIcon(NIM_ADD, &nid);
	SendMessage(WM_SETICON, (WPARAM)TRUE, (LPARAM)nid.hIcon);
	m_tray = TRUE;
}


void CMemo2Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 食奄拭 五獣走 坦軒奄 坪球研 蓄亜杯艦陥.
	if (m_tray) // 薄仙 闘傾戚 焼戚嬬生稽 竺舛鞠醸澗走 溌昔 
	{
		NOTIFYICONDATA  nid;
		nid.cbSize = sizeof(nid);
		nid.hWnd = m_hWnd; // 五昔 制亀酔 輩級
		nid.uID = IDR_MAINFRAME;

		// 拙穣 妊獣匝(TaskBar)税 雌殿 慎蝕拭 焼戚嬬聖 肢薦廃陥.
		Shell_NotifyIcon(NIM_DELETE, &nid);
	}
}


void CMemo2Dlg::OnBnClickedCancel()
{
	// TODO: 食奄拭 珍闘継 硝顕 坦軒奄 坪球研 蓄亜杯艦陥.
	CloseMain();
}


void CMemo2Dlg::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 食奄拭 珍闘継 硝顕 坦軒奄 坪球研 蓄亜杯艦陥.
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
	// TODO: 食奄拭 珍闘継 硝顕 坦軒奄 坪球研 蓄亜杯艦陥.
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
			AfxMessageBox(_T("尻衣叔鳶ばば"));
			return;
		}
		//AfxMessageBox(_T("尻衣失因!^^"));
		if (mysql_query(&m_MySql, "set names euckr") == NULL)
		{
			//AfxMessageBox(_T("汀軒推短失因"));
			//return;
		}
		if (mysql_query(&m_MySql, titlequery2) == NULL)
		{
			//   AfxMessageBox(_T("汀軒推短失因"));
			//return;
		}

		if ((m_Res = mysql_store_result(&m_MySql)) == NULL)
		{ // 衣引研 m_Res拭 煽舌
			//   AfxMessageBox(_T("衣引煽舌叔鳶ばば"));
		}

		v.erase(v.begin() + node);
		m_list.DeleteItem(node);
		m_list.Invalidate(true);
	}
}


void CMemo2Dlg::OnBnClickedButton3()
{
	// TODO: 食奄拭 珍闘継 硝顕 坦軒奄 坪球研 蓄亜杯艦陥.
	column = m_list.GetNextItem(-1, LVNI_SELECTED);
	if (column >= 0)
	{
		m_num2 = v.at(column);
		m_flag = true;
		MakeNewMemo();
	}
}

void CMemo2Dlg::OnUpdateList(){
	//MessageBox(_T("薦鯉 左食爽奄 獣亀!"), MB_OK);
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
			//AfxMessageBox(_T("尻衣叔鳶ばば"));
			return;
		}
		//AfxMessageBox(_T("尻衣失因!^^"));
		if (mysql_query(&m_MySql, titlequery2) == NULL)
		{
			//AfxMessageBox(_T("汀軒推短失因"));
			//return;
		}

		if ((m_Res = mysql_store_result(&m_MySql)) == NULL)
		{ // 衣引研 m_Res拭 煽舌
			//AfxMessageBox(_T("衣引煽舌叔鳶ばば"));
		}

		//AfxMessageBox(_T("衣引煽舌失因"));

		for (int i = 0; i < mysql_num_rows(m_Res); i++){
			row = mysql_fetch_row(m_Res);
			pResult = row[0];
			title = char2CString(pResult);
			//AfxMessageBox(title);
			m_list.InsertItem(i, title);
		}

		if (mysql_query(&m_MySql, numquery2) == NULL)
		{
			//AfxMessageBox(_T("汀軒推短失因"));
			//return;
		}

		if ((m_Res2 = mysql_store_result(&m_MySql)) == NULL)
		{ // 衣引研 m_Res拭 煽舌
		//	AfxMessageBox(_T("衣引煽舌叔鳶ばば"));
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
