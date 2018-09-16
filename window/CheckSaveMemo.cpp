// CheckSaveMemo.cpp : 구현 파일입니다.
//
#include "stdafx.h"

#include "Memo2.h"
#include "CheckSaveMemo.h"
#include "afxdialogex.h"


// CCheckSaveMemo 대화 상자입니다.

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


// CCheckSaveMemo 메시지 처리기입니다.


void CCheckSaveMemo::OnBnClickedSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_post_it_close = true;
	m_post_save = true;
	//((CPostIt*)GetParent())->saveMemo();
	CDialogEx::OnCancel();
}


void CCheckSaveMemo::OnBnClickedNotsave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_post_it_close = true;
	m_post_save = false;
	CDialogEx::OnCancel();
}

void CCheckSaveMemo::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_post_save = false;
	CDialogEx::OnCancel();
}
