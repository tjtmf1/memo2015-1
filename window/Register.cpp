// Register.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Memo2.h"
#include "Register.h"
#include "afxdialogex.h"


// CRegister ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CRegister, CDialogEx)

CRegister::CRegister(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRegister::IDD, pParent)
{

}

CRegister::~CRegister()
{
}

void CRegister::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_NEW_ID, m_new_id);
	DDX_Control(pDX, IDC_NEW_PW, m_new_pw);
}


BEGIN_MESSAGE_MAP(CRegister, CDialogEx)
	ON_BN_CLICKED(IDC_N, &CRegister::OnBnClickedN)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CRegister �޽��� ó�����Դϴ�.


void CRegister::OnBnClickedN()
{

	CString id, pw;
	m_new_id.GetWindowTextW(id);
	m_new_pw.GetWindowTextW(pw);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	MessageBox(_T("ȸ������ �õ�!"), MB_OK);
	CString addidquery, temp1, temp2, password;
	temp1.Format(_T("','"));
	temp2.Format(_T("')"));
	
	addidquery.Format(_T("insert into member(id,password) values('"));
	addidquery = addidquery + id + temp1 + pw + temp2;
	char* addidquery2 = CString2char(addidquery);


	MYSQL m_MySql;
	mysql_init(&m_MySql);

	if (mysql_real_connect(&m_MySql, ADDRESS, ID, PASSWD, DBNAME, 3306, NULL, 0) == NULL)
	{
		AfxMessageBox(_T("������ФФ�"));
		return;
	}
	AfxMessageBox(_T("���Ἲ��!^^"));
	if (mysql_query(&m_MySql, addidquery2) == NULL)
	{
		AfxMessageBox(_T("������û����"));
		//return;
	}
}


void CRegister::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	// �׸��� �޽����� ���ؼ��� CDialogEx::OnPaint()��(��) ȣ������ ���ʽÿ�.
	CRect r;
	GetClientRect(&r);
	dc.FillSolidRect(r, RGB(255, 216, 200));
}
