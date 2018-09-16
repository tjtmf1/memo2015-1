// Login.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Memo2.h"
#include "Login.h"
#include "afxdialogex.h"

// CLogin ��ȭ �����Դϴ�.

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


// CLogin �޽��� ó�����Դϴ�.


void CLogin::OnBnClickedSingin()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_register.DoModal();
}


void CLogin::OnBnClickedCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_check_login = false;
	CDialogEx::OnCancel();
}


BOOL CLogin::DestroyWindow()
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	if (m_check_login == false)
	{

	}
	return CDialogEx::DestroyWindow();
}


void CLogin::OnBnClickedLoginBn()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString id, pw;
	m_input_id.GetWindowTextW(id);
	m_input_pw.GetWindowTextW(pw);
	//MessageBox(_T("�α��� �õ�!"), MB_OK);
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
		//AfxMessageBox(_T("������ФФ�"));
		return;
	}
	//AfxMessageBox(_T("���Ἲ��!^^"));
	if (mysql_query(&m_MySql, isIDquery2) == NULL)
	{
		//AfxMessageBox(_T("������û����"));
		//return;
	}

	if ((m_Res = mysql_store_result(&m_MySql)) == NULL)
	{ // ����� m_Res�� ����
		AfxMessageBox(_T("���������ФФ�"));
	}

	//AfxMessageBox(_T("������强��"));
	for (int i = 0; i < mysql_num_rows(m_Res); i++){
		row = mysql_fetch_row(m_Res);
		if (row[0] == id){	//���̵� ����
//AfxMessageBox(_T("���̵� ����"));
			m_id = id;
			//��й�ȣ Ȯ��
			if (mysql_query(&m_MySql, idquery2) == NULL)
			{
				//AfxMessageBox(_T("������û����"));
				//return;
			}
			if ((m_Res2 = mysql_store_result(&m_MySql)) == NULL)
			{ // ����� m_Res�� ����
				//AfxMessageBox(_T("�������??"));
			}
			row2 = mysql_fetch_row(m_Res2);
			pResult2 = row2[0];
			CString str = char2CString(pResult2);
			if (str == password2){
				AfxMessageBox(_T("�α��� ����"));
				m_check_login = true;
				this->EndDialog(IDOK);
				return;
			}
			else{
				//AfxMessageBox(_T("�α��� ����! ��й�ȣ Ʋ����."));
			}
		}
		else{//���̵� ����
			//AfxMessageBox(_T("�α��� ����! ���̵����."));
		}
	}	
	AfxMessageBox(_T("�α��� ����"));
}


BOOL CLogin::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CLogin::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	// �׸��� �޽����� ���ؼ��� CDialogEx::OnPaint()��(��) ȣ������ ���ʽÿ�.
	CRect r;
	GetClientRect(&r);

	dc.FillSolidRect(r, RGB(255, 216, 216));


	

	
}


void CLogin::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if (nIDCtl == IDC_LOGIN_BN)         // �ش� ��ư���� üũ
	{
		CDC bdc1;
		bdc1.Attach(lpDrawItemStruct->hDC);
		RECT rect;
		rect = lpDrawItemStruct->rcItem;     // ��ư ���� ���ϱ�    
		bdc1.Draw3dRect(&rect, RGB(255, 255, 255), RGB(0, 0, 0)); // ��ư�� �ܰ��� �׸���
		bdc1.FillSolidRect(&rect, RGB(0, 255, 0));

		CDialogEx::OnDrawItem(nIDCtl, lpDrawItemStruct);
	}
}
