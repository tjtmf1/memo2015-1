#pragma once
#include "afxwin.h"
// CCheckSaveMemo 대화 상자입니다.

class CCheckSaveMemo : public CDialogEx
{
	DECLARE_DYNAMIC(CCheckSaveMemo)

public:
	CCheckSaveMemo(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CCheckSaveMemo();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedNotsave();
	afx_msg void OnBnClickedCancel();
	bool m_post_it_close;
	bool m_post_save;
};
