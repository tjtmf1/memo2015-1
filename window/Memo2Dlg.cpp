
// Memo2Dlg.cpp : ���� ����
//

#include "stdafx.h"
#include "Memo2.h"
#include "Memo2Dlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
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


// CMemo2Dlg ��ȭ ����



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


// CMemo2Dlg �޽��� ó����

BOOL CMemo2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	
	m_loginWindow.DoModal();
	id = m_loginWindow.m_id;

	m_tray = FALSE;
	RegistTray();
	//MessageBox(_T("���� �����ֱ� �õ�!"), MB_OK);
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
			//AfxMessageBox(_T("������ФФ�"));
			return true;
		}
		//AfxMessageBox(_T("���Ἲ��!^^"));
		if (mysql_query(&m_MySql, titlequery2) == NULL)
		{
			 //AfxMessageBox(_T("������û����"));
			//return;
		}

		if ((m_Res = mysql_store_result(&m_MySql)) == NULL)
		{ // ����� m_Res�� ����
			//AfxMessageBox(_T("���������ФФ�"));
		}

		//AfxMessageBox(_T("������强��"));

		for (int i = 0; i < mysql_num_rows(m_Res); i++){
			row = mysql_fetch_row(m_Res);
			pResult = row[0];
			title = char2CString(pResult);
			//AfxMessageBox(title);
			m_list.InsertItem(i, title);
		}

		if (mysql_query(&m_MySql, numquery2) == NULL)
		{
			//AfxMessageBox(_T("������û����"));
			//return;
		}

		if ((m_Res2 = mysql_store_result(&m_MySql)) == NULL)
		{ // ����� m_Res�� ����
			AfxMessageBox(_T("���������ФФ�"));
		}
		for (int i = 0; i < mysql_num_rows(m_Res2); i++){
			row2 = mysql_fetch_row(m_Res2);
			pResult2 = row2[0];
			CString a = char2CString(pResult2);

			v.push_back(a);

			//AfxMessageBox(v.at(i));
		}
	}
	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CMemo2Dlg::OnPaint()
{
	CClientDC dc(this);
	CRect r;
	GetClientRect(&r);
	dc.FillSolidRect(r,RGB(206,251,201));
	m_b1.SetFaceColor(RGB(186, 229, 92));
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
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

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CMemo2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMemo2Dlg::OnBnClickedButton1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_flag = false;
	MakeNewMemo();
}

BOOL CMemo2Dlg::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.


	return CDialogEx::PreCreateWindow(cs);
}


void CMemo2Dlg::MakeNewMemo()
{
	CPostIt* post = new CPostIt;
	m_post_it.push_back(post);
	m_num = m_post_it.size() - 1;
	if (m_flag)
	{
		//MessageBox(_T("���� �����ֱ� �õ�!"), MB_OK);
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
			AfxMessageBox(_T("������ФФ�"));
			return;
		}
		//AfxMessageBox(_T("���Ἲ��!^^"));
		if (mysql_query(&m_MySql, titlequery2) == NULL)
		{
			 //  AfxMessageBox(_T("������û����"));
			//return;
		}

		if ((m_Res = mysql_store_result(&m_MySql)) == NULL)
		{ // ����� m_Res�� ����
			//   AfxMessageBox(_T("���������ФФ�"));
		}

		///AfxMessageBox(_T("������强��"));

		row = mysql_fetch_row(m_Res);
		pResult = row[0];

		m_post_it[m_num]->m_title = char2CString(pResult);


		if (mysql_query(&m_MySql, contentquery2) == NULL)
		{
		// AfxMessageBox(_T("������û����"));
			//return;
		}

		if ((m_Res2 = mysql_store_result(&m_MySql)) == NULL)
		{ // ����� m_Res�� ����
			//   AfxMessageBox(_T("���������ФФ�"));
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
	if (m_tray) // ���� Ʈ���� ���������� �����Ǿ����� Ȯ�� 
	{
		NOTIFYICONDATA  nid;
		nid.cbSize = sizeof(nid);
		nid.hWnd = m_hWnd; // ���� ������ �ڵ�
		nid.uID = IDR_MAINFRAME;

		// �۾� ǥ����(TaskBar)�� ���� ������ �������� �����Ѵ�.
		Shell_NotifyIcon(NIM_DELETE, &nid);
	}
	this->EndDialog(IDOK);
}

BOOL CMemo2Dlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CMemo2Dlg::On32771()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	AfxGetApp()->m_pMainWnd->ShowWindow(SW_SHOW);
}


void CMemo2Dlg::On32772()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
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
		CMenu *pMenu = new CMenu(); //Ȱ��ȭ �� �޴� ����
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
	nid.hWnd = m_hWnd; // ���� ������ �ڵ�
	nid.uID = IDR_MAINFRAME;  // ������ ���ҽ� ID
	nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP; // �÷��� ����
	nid.uCallbackMessage = WM_TRAY_NOTIFICATION; // �ݹ�޽��� ����
	nid.hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME); // ������ �ε�
	CString strTitle;
	GetWindowText(strTitle); // ĸ�ǹٿ� ��µ� ���ڿ� ����
	lstrcpy(nid.szTip, strTitle);
	Shell_NotifyIcon(NIM_ADD, &nid);
	SendMessage(WM_SETICON, (WPARAM)TRUE, (LPARAM)nid.hIcon);
	m_tray = TRUE;
}


void CMemo2Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	if (m_tray) // ���� Ʈ���� ���������� �����Ǿ����� Ȯ�� 
	{
		NOTIFYICONDATA  nid;
		nid.cbSize = sizeof(nid);
		nid.hWnd = m_hWnd; // ���� ������ �ڵ�
		nid.uID = IDR_MAINFRAME;

		// �۾� ǥ����(TaskBar)�� ���� ������ �������� �����Ѵ�.
		Shell_NotifyIcon(NIM_DELETE, &nid);
	}
}


void CMemo2Dlg::OnBnClickedCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CloseMain();
}


void CMemo2Dlg::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
			AfxMessageBox(_T("������ФФ�"));
			return;
		}
		//AfxMessageBox(_T("���Ἲ��!^^"));
		if (mysql_query(&m_MySql, "set names euckr") == NULL)
		{
			//AfxMessageBox(_T("������û����"));
			//return;
		}
		if (mysql_query(&m_MySql, titlequery2) == NULL)
		{
			//   AfxMessageBox(_T("������û����"));
			//return;
		}

		if ((m_Res = mysql_store_result(&m_MySql)) == NULL)
		{ // ����� m_Res�� ����
			//   AfxMessageBox(_T("���������ФФ�"));
		}

		v.erase(v.begin() + node);
		m_list.DeleteItem(node);
		m_list.Invalidate(true);
	}
}


void CMemo2Dlg::OnBnClickedButton3()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	column = m_list.GetNextItem(-1, LVNI_SELECTED);
	if (column >= 0)
	{
		m_num2 = v.at(column);
		m_flag = true;
		MakeNewMemo();
	}
}

void CMemo2Dlg::OnUpdateList(){
	//MessageBox(_T("���� �����ֱ� �õ�!"), MB_OK);
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
			//AfxMessageBox(_T("������ФФ�"));
			return;
		}
		//AfxMessageBox(_T("���Ἲ��!^^"));
		if (mysql_query(&m_MySql, titlequery2) == NULL)
		{
			//AfxMessageBox(_T("������û����"));
			//return;
		}

		if ((m_Res = mysql_store_result(&m_MySql)) == NULL)
		{ // ����� m_Res�� ����
			//AfxMessageBox(_T("���������ФФ�"));
		}

		//AfxMessageBox(_T("������强��"));

		for (int i = 0; i < mysql_num_rows(m_Res); i++){
			row = mysql_fetch_row(m_Res);
			pResult = row[0];
			title = char2CString(pResult);
			//AfxMessageBox(title);
			m_list.InsertItem(i, title);
		}

		if (mysql_query(&m_MySql, numquery2) == NULL)
		{
			//AfxMessageBox(_T("������û����"));
			//return;
		}

		if ((m_Res2 = mysql_store_result(&m_MySql)) == NULL)
		{ // ����� m_Res�� ����
		//	AfxMessageBox(_T("���������ФФ�"));
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
