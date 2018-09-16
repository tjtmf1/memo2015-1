// Register.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Memo2.h"
#include "Register.h"
#include "afxdialogex.h"


// CRegister 대화 상자입니다.

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


// CRegister 메시지 처리기입니다.


void CRegister::OnBnClickedN()
{

	CString id, pw;
	m_new_id.GetWindowTextW(id);
	m_new_pw.GetWindowTextW(pw);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	MessageBox(_T("회원가입 시도!"), MB_OK);
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
		AfxMessageBox(_T("연결실패ㅠㅠ"));
		return;
	}
	AfxMessageBox(_T("연결성공!^^"));
	if (mysql_query(&m_MySql, addidquery2) == NULL)
	{
		AfxMessageBox(_T("쿼리요청성공"));
		//return;
	}
}


void CRegister::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.
	CRect r;
	GetClientRect(&r);
	dc.FillSolidRect(r, RGB(255, 216, 200));
}
