// CheckSaveMemo.cpp : ���� �����Դϴ�.
//
#include "stdafx.h"

#include "Memo2.h"
#include "CheckSaveMemo.h"
#include "afxdialogex.h"


// CCheckSaveMemo ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CCheckSaveMemo, CDialogEx)

CCheckSaveMemo::CCheckSaveMemo(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCheckSaveMemo::IDD, pParent),
	m_post_it_close(false)
{

}

CCheckSaveMemo::~CCheckSaveMemo()
{
}

void CCheckSaveMemo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCheckSaveMemo, CDialogEx)
	ON_BN_CLICKED(IDC_SAVE, &CCheckSaveMemo::OnBnClickedSave)
	ON_BN_CLICKED(IDC_NOTSAVE, &CCheckSaveMemo::OnBnClickedNotsave)
	ON_BN_CLICKED(IDCANCEL, &CCheckSaveMemo::OnBnClickedCancel)
END_MESSAGE_MAP()


// CCheckSaveMemo �޽��� ó�����Դϴ�.


void CCheckSaveMemo::OnBnClickedSave()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_post_it_close = true;
	m_post_save = true;
	//((CPostIt*)GetParent())->saveMemo();
	CDialogEx::OnCancel();
}


void CCheckSaveMemo::OnBnClickedNotsave()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_post_it_close = true;
	m_post_save = false;
	CDialogEx::OnCancel();
}

void CCheckSaveMemo::OnBnClickedCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_post_save = false;
	CDialogEx::OnCancel();
}
