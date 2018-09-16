// Login.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Memo2.h"
#include "Login.h"
#include "afxdialogex.h"

// CLogin 대화 상자입니다.

IMPLEMENT_DYNAMIC(CLogin, CDialogEx)

CLogin::CLogin(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLogin::IDD, pParent)
	, m_id(_T(""))
	, m_passwd(_T(""))
{

}

CLogin::~CLogin()
{
}

void CLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ENTER_ID, m_id);
	DDX_Text(pDX, IDC_ENTER_PW, m_passwd);
	DDX_Control(pDX, IDC_LOGIN_BN, m_login);
	DDX_Control(pDX, IDC_ENTER_ID, m_input_id);
	DDX_Control(pDX, IDC_ENTER_PW, m_input_pw);
	DDX_Control(pDX, IDC_STATIC1, s1);
	DDX_Control(pDX, IDC_STATIC2, s2);
}


BEGIN_MESSAGE_MAP(CLogin, CDialogEx)
	ON_BN_CLICKED(IDC_SINGIN, &CLogin::OnBnClickedSingin)
	ON_BN_CLICKED(IDCANCEL, &CLogin::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_LOGIN_BN, &CLogin::OnBnClickedLoginBn)
	ON_WM_PAINT()
	ON_WM_DRAWITEM()
END_MESSAGE_MAP()


// CLogin 메시지 처리기입니다.


void CLogin::OnBnClickedSingin()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_register.DoModal();
}


void CLogin::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_check_login = false;
	CDialogEx::OnCancel();
}


BOOL CLogin::DestroyWindow()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (m_check_login == false)
	{

	}
	return CDialogEx::DestroyWindow();
}


void CLogin::OnBnClickedLoginBn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString id, pw;
	m_input_id.GetWindowTextW(id);
	m_input_pw.GetWindowTextW(pw);
	//MessageBox(_T("로그인 시도!"), MB_OK);
	CString idquery, temp, pwquery, isIDquery;
	temp.Format(_T("'"));

	idquery.Format(_T("select password from member where id='"));
	idquery = idquery + id + temp;
	isIDquery.Format(_T("select id from member"));
	char* idquery2 = CString2char(idquery);
	char* password2 = CString2char(pw);
	char* isIDquery2 = CString2char(isIDquery);

	MYSQL m_MySql;
	MYSQL_RES* m_Res;
	MYSQL_RES* m_Res2;
	MYSQL_ROW row;
	MYSQL_ROW row2;
	char *pResult;
	char *pResult2;
	mysql_init(&m_MySql);

	if (mysql_real_connect(&m_MySql, ADDRESS, ID, PASSWD, DBNAME, 3306, NULL, 0) == NULL)
	{
		//AfxMessageBox(_T("연결실패ㅠㅠ"));
		return;
	}
	//AfxMessageBox(_T("연결성공!^^"));
	if (mysql_query(&m_MySql, isIDquery2) == NULL)
	{
		//AfxMessageBox(_T("쿼리요청성공"));
		//return;
	}

	if ((m_Res = mysql_store_result(&m_MySql)) == NULL)
	{ // 결과를 m_Res에 저장
		AfxMessageBox(_T("결과저장실패ㅠㅠ"));
	}

	//AfxMessageBox(_T("결과저장성공"));
	for (int i = 0; i < mysql_num_rows(m_Res); i++){
		row = mysql_fetch_row(m_Res);
		if (row[0] == id){	//아이디 있음
//AfxMessageBox(_T("아이디 있음"));
			m_id = id;
			//비밀번호 확인
			if (mysql_query(&m_MySql, idquery2) == NULL)
			{
				//AfxMessageBox(_T("쿼리요청성공"));
				//return;
			}
			if ((m_Res2 = mysql_store_result(&m_MySql)) == NULL)
			{ // 결과를 m_Res에 저장
				//AfxMessageBox(_T("결과저장??"));
			}
			row2 = mysql_fetch_row(m_Res2);
			pResult2 = row2[0];
			CString str = char2CString(pResult2);
			if (str == password2){
				AfxMessageBox(_T("로그인 성공"));
				m_check_login = true;
				this->EndDialog(IDOK);
				return;
			}
			else{
				//AfxMessageBox(_T("로그인 실패! 비밀번호 틀렸음."));
			}
		}
		else{//아이디 없음
			//AfxMessageBox(_T("로그인 실패! 아이디없음."));
		}
	}	
	AfxMessageBox(_T("로그인 실패"));
}


BOOL CLogin::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CLogin::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.
	CRect r;
	GetClientRect(&r);

	dc.FillSolidRect(r, RGB(255, 216, 216));


	

	
}


void CLogin::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nIDCtl == IDC_LOGIN_BN)         // 해당 버튼인지 체크
	{
		CDC bdc1;
		bdc1.Attach(lpDrawItemStruct->hDC);
		RECT rect;
		rect = lpDrawItemStruct->rcItem;     // 버튼 영역 구하기    
		bdc1.Draw3dRect(&rect, RGB(255, 255, 255), RGB(0, 0, 0)); // 버튼의 외각선 그리기
		bdc1.FillSolidRect(&rect, RGB(0, 255, 0));

		CDialogEx::OnDrawItem(nIDCtl, lpDrawItemStruct);
	}
}
