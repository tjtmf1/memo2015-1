// PostIt.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Memo2.h"
#include "PostIt.h"
#include "afxdialogex.h"


// CPostIt ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CPostIt, CDialogEx)

CPostIt::CPostIt(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPostIt::IDD, pParent)
	, m_stWinMove(false)
	, m_drag(false)
	, color(0)
{

}

CPostIt::~CPostIt()
{
}

void CPostIt::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edit);

	DDX_Control(pDX, IDC_TITLE, m_post_title);
	DDX_Control(pDX, ID_EXIT, m_exit_button);
	DDX_Control(pDX, IDC_SAVEIT, m_save_button);
	DDX_Control(pDX, IDC_ADD, m_add_button);
}


BEGIN_MESSAGE_MAP(CPostIt, CDialogEx)
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_PAINT()
	ON_BN_CLICKED(ID_EXIT, &CPostIt::OnBnClickedExit)
	ON_EN_CHANGE(IDC_EDIT1, &CPostIt::OnEnChangeEdit1)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_ADD, &CPostIt::OnBnClickedAdd)
	ON_BN_CLICKED(IDC_SAVEIT, &CPostIt::OnBnClickedSaveit)
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_32773, &CPostIt::On32773)
	ON_COMMAND(ID_32774, &CPostIt::On32774)
END_MESSAGE_MAP()


// CPostIt �޽��� ó�����Դϴ�.


void CPostIt::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	CRect clientRect;
	GetClientRect(clientRect);
	if (m_edit.GetSafeHwnd() != NULL)
	{
		CRect editrect;
		m_edit.GetWindowRect(editrect);

		ScreenToClient(editrect);
		
		editrect.top = clientRect.top + 50;
		editrect.bottom = clientRect.bottom-30;
		editrect.right = clientRect.right-10;
		m_edit.MoveWindow(editrect);
		m_barRect.SetRect(clientRect.left, clientRect.top, clientRect.right, 50);
		m_memoRect.SetRect(clientRect.left, clientRect.top, clientRect.right, clientRect.bottom);
	}

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	Invalidate(false);
}


BOOL CPostIt::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	CRect editrect;
	m_edit.GetWindowRect(editrect);

	ScreenToClient(editrect);
	clientRect;
	GetClientRect(clientRect);
	editrect.top = clientRect.top + 50;
	editrect.bottom = clientRect.bottom - 30;
	editrect.right = clientRect.right - 10;
	m_edit.MoveWindow(editrect);

	m_barRect.SetRect(clientRect.left, clientRect.top, clientRect.right, 50);
	m_memoRect.SetRect(clientRect.left, clientRect.top, clientRect.right,clientRect.bottom);
	DWORD style = GetWindowLong(m_hWnd, GWL_STYLE);
	style &= ~WS_CAPTION;
	SetWindowLong(m_hWnd, GWL_STYLE, style);
	::SetWindowPos(m_hWnd, 0, 0, 0, 0, 0, 39);
	POINT pt;
	GetCursorPos(&pt);
	MoveWindow(pt.x, pt.y, clientRect.right, clientRect.bottom);
	GotoDlgCtrl(GetDlgItem(IDC_TITLE));

	m_exit_button.LoadBitmaps(IDB_BITMAP2,IDB_BITMAP9,NULL,NULL);
	m_exit_button.SizeToContent();
	m_add_button.LoadBitmaps(IDB_BITMAP6, IDB_BITMAP10, NULL, NULL);
	m_add_button.SizeToContent();
	m_save_button.LoadBitmaps(IDB_BITMAP8, IDB_BITMAP11, NULL, NULL);
	m_save_button.SizeToContent();

	m_post_title.SetWindowTextW(m_title);
	m_edit.SetWindowTextW(m_content);

	
	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


BOOL CPostIt::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	cs.style = WS_POPUP; // WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE;
	cs.x = 20;  // �������� ���� ��ġ
	cs.y = 30;


	return CDialogEx::PreCreateWindow(cs);
}


void CPostIt::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if (m_barRect.left <= point.x && m_barRect.top <= point.y)
	{
		if (m_barRect.right >= point.x&& m_barRect.bottom >= point.y)
		{
			CWnd *pWnd = this;
			HWND hUIWnd = pWnd->m_hWnd;
			::DefWindowProc(hUIWnd, WM_SYSCOMMAND, SC_MOVE + 1, MAKELPARAM(point.x, point.y));
		}
	}
	if (point.x > clientRect.right - 20 && point.x <= clientRect.right&&point.y > clientRect.bottom - 20 && point.y <= clientRect.bottom)
	{
		m_drag = true;
		CWnd *pWnd = this;
		HWND hUIWnd = pWnd->m_hWnd;
		::DefWindowProc(hUIWnd, WM_NCHITTEST, HTBOTTOMRIGHT, MAKELPARAM(point.x, point.y));
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}


void CPostIt::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	//m_range.CreateRectRgn(clientRect.right - 80, clientRect.right, clientRect.bottom,clientRect.bottom - 50);
	if (point.x>clientRect.right-20&&point.x<=clientRect.right&&point.y>clientRect.bottom-20&&point.y <=clientRect.bottom)
	{
		SetCursor(LoadCursor(NULL,IDC_SIZENWSE));
	}
	if (m_drag == true)
	{
		/*CRect rect;
		POINT pt;
		GetCursorPos(&pt);
		GetWindowRect(&rect);
		SetWindowPos(NULL, 0, 0, pt.x - rect.left, pt.y - rect.top,SWP_NOMOVE | SWP_NOZORDER);*/
		
	}
	CDialogEx::OnMouseMove(nFlags, point);
}


void CPostIt::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	m_drag = false;
	CDialogEx::OnLButtonUp(nFlags, point);
}


void CPostIt::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	// �׸��� �޽����� ���ؼ��� CDialogEx::OnPaint()��(��) ȣ������ ���ʽÿ�.

	
	if (color == 0)
	{
		CDC memodc;
		CBitmap background;
		BITMAP bginfo;
		background.LoadBitmapW(IDB_BITMAP1);
		
		background.GetBitmap(&bginfo);
		memodc.CreateCompatibleDC(&dc);
		memodc.SelectObject(background);
		m_exit_button.LoadBitmaps(IDB_BITMAP2, IDB_BITMAP9, NULL, NULL);
		m_exit_button.SizeToContent();
		m_add_button.LoadBitmaps(IDB_BITMAP6, IDB_BITMAP10, NULL, NULL);
		m_add_button.SizeToContent();
		m_save_button.LoadBitmaps(IDB_BITMAP8, IDB_BITMAP11, NULL, NULL);
		m_save_button.SizeToContent();
		dc.StretchBlt(0, 0, m_memoRect.Width(), m_memoRect.Height(), &memodc, 0, 0, bginfo.bmWidth, bginfo.bmHeight, SRCCOPY);
		dc.FillSolidRect(m_barRect, RGB(255, 234, 136));
	}
	else if (color == 1)
	{
		CDC memodc;
		CBitmap background;
		BITMAP bginfo;
		background.LoadBitmapW(IDB_BITMAP3);
		
		background.GetBitmap(&bginfo);
		memodc.CreateCompatibleDC(&dc);
		memodc.SelectObject(background);
		m_exit_button.LoadBitmaps(IDB_BITMAP5, IDB_BITMAP5, NULL, NULL);
		m_exit_button.SizeToContent();
		m_add_button.LoadBitmaps(IDB_BITMAP7, IDB_BITMAP7, NULL, NULL);
		m_add_button.SizeToContent();
		m_save_button.LoadBitmaps(IDB_BITMAP4, IDB_BITMAP4, NULL, NULL);
		m_save_button.SizeToContent();
		dc.StretchBlt(0, 0, m_memoRect.Width(), m_memoRect.Height(), &memodc, 0, 0, bginfo.bmWidth, bginfo.bmHeight, SRCCOPY);
		dc.FillSolidRect(m_barRect, RGB(0, 216, 255));
	}
	
	
}


void CPostIt::OnBnClickedExit()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_check_wnd.DoModal();
	if (m_check_wnd.m_post_it_close)
	{
		if (m_check_wnd.m_post_save)
		{
			saveMemo();
		}
		this->EndDialog(IDOK);
	}
}


void CPostIt::OnEnChangeEdit1()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.
	CRect rc;
	CWnd* pWnd = GetDlgItem(IDC_EDIT1);
	pWnd->GetWindowRect(rc);
	ScreenToClient(rc);
	CFont editFont;
	editFont.CreatePointFont(100, TEXT("����"));
	GetDlgItem(IDC_EDIT1)->SetFont(&editFont);
	InvalidateRect(rc,false);
	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


HBRUSH CPostIt::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  ���⼭ DC�� Ư���� �����մϴ�.
	switch (nCtlColor)
	{
	case CTLCOLOR_EDIT:
	{
		if (pWnd->GetDlgCtrlID() == IDC_EDIT1)
		{
			pDC->SetTextColor(RGB(0, 0, 0));
			pDC->SetBkMode(TRANSPARENT);
			pDC->SelectStockObject(NULL_BRUSH);
			return NULL;
		}
	}
	}
	// TODO:  �⺻���� �������� ������ �ٸ� �귯�ø� ��ȯ�մϴ�.
	return hbr;
}


BOOL CPostIt::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	if (::GetDlgCtrlID(pMsg->hwnd) == IDC_EDIT1)
	{
		// ����Ʈ ��Ʈ�� IDC_EDIT1 ���� �̺�Ʈ �߿��� �Ʒ� �̺�Ʈ�� �߻��ϸ�
		// ����Ʈ ��Ʈ�� ������ŭ �θ� �������� ȭ���� �����Ѵ�.
		switch (pMsg->message)
		{
		case WM_LBUTTONDOWN:
		case WM_LBUTTONUP:
		case WM_KILLFOCUS:
		{
			CRect rc;
			CWnd* pWnd = GetDlgItem(IDC_EDIT1);
			pWnd->GetWindowRect(rc);
			ScreenToClient(rc);
			InvalidateRect(rc);
		}
		}
	}
	if (::GetDlgCtrlID(pMsg->hwnd) == IDC_DELETE)
	{
		// ����Ʈ ��Ʈ�� IDC_EDIT1 ���� �̺�Ʈ �߿��� �Ʒ� �̺�Ʈ�� �߻��ϸ�
		// ����Ʈ ��Ʈ�� ������ŭ �θ� �������� ȭ���� �����Ѵ�.
		switch (pMsg->message)
		{
		case WM_LBUTTONDOWN:
		case WM_LBUTTONUP:
		case WM_KILLFOCUS:
		{
			CRect rc;
			CWnd* pWnd = GetDlgItem(IDC_DELETE);
			pWnd->GetWindowRect(rc);
			ScreenToClient(rc);
			InvalidateRect(rc);
		}
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CPostIt::OnBnClickedAdd()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	((CMemo2Dlg*)GetParent())->MakeNewMemo();
}

void CPostIt::closeWindow()
{
	saveMemo();
	this->EndDialog(IDOK);
}


void CPostIt::saveMemo()
{
	if (m_flag){   //���� �ִ� �޸𿩼� �����ؾ��ϴ� ���
		CString titlequery, temp1, temp2, temp3, temp4;
		temp1.Format(_T("',"));
		temp2.Format(_T("'"));
		temp3.Format(_T("content='"));
		temp4.Format(_T("' where num="));
		m_post_title.GetWindowTextW(m_title);
		m_edit.GetWindowTextW(m_content);

		titlequery.Format(_T("update content set title='"));
		titlequery = titlequery + m_title + temp1 + temp3 + m_content + temp4 + m_num;

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
		((CMemo2Dlg*)GetParent())->m_list.DeleteItem(m_index);
		((CMemo2Dlg*)GetParent())->m_list.InsertItem(m_index,m_title);
		((CMemo2Dlg*)GetParent())->m_list.Invalidate(false);
	}
	else{   //���ο� �޸𿩼� �޸� �߰��ؾ��ϴ� ���
		CTime t = CTime::GetCurrentTime();
		CString date = t.Format("%Y") + "-" + t.Format("%m") + "-" + t.Format("%d");

		//MessageBox(_T("�޸����� �õ�!"), MB_OK);
		CString insertquery, temp1, temp2, pwquery;
		temp1.Format(_T("','"));
		temp2.Format(_T("')"));
		insertquery.Format(_T("insert into content(id,date,title,content) values('"));
		m_post_title.GetWindowTextW(m_title);
		m_edit.GetWindowTextW(m_content);
		insertquery = insertquery + m_id + temp1 + date + temp1 + m_title + temp1 + m_content + temp2;
		//AfxMessageBox(m_title);
		//AfxMessageBox(m_content);
		char* insertquery2 = CString2char(insertquery);
		//MessageBox(insertquery, MB_OK);
		MYSQL m_MySql;
		mysql_init(&m_MySql);
		((CMemo2Dlg*)GetParent())->column = ((CMemo2Dlg*)GetParent())->v.size();
		((CMemo2Dlg*)GetParent())->m_list.InsertItem(((CMemo2Dlg*)GetParent())->column,m_title);

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
		if (mysql_query(&m_MySql, insertquery2) == NULL)
		{
		//	AfxMessageBox(_T("������û����"));
			//return;
		}
	}
}


void CPostIt::OnBnClickedSaveit()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	saveMemo();
}


void CPostIt::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CPoint ptMouse;
	::GetCursorPos(&ptMouse);
	CMenu menu;
	menu.LoadMenu(IDR_MAINFRAME);
	CMenu *pMenu = new CMenu(); //Ȱ��ȭ �� �޴� ����
	pMenu->LoadMenuW(IDR_MENU1);
	pMenu->GetSubMenu(1)->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,
		ptMouse.x, ptMouse.y, this);
	CDialogEx::OnRButtonDown(nFlags, point);
}


void CPostIt::On32773()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	color = 0;
	Invalidate(false);
}


void CPostIt::On32774()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	color = 1;
	Invalidate(false);
}
