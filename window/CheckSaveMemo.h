#pragma once
#include "afxwin.h"
// CCheckSaveMemo ��ȭ �����Դϴ�.

class CCheckSaveMemo : public CDialogEx
{
	DECLARE_DYNAMIC(CCheckSaveMemo)

public:
	CCheckSaveMemo(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CCheckSaveMemo();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedNotsave();
	afx_msg void OnBnClickedCancel();
	bool m_post_it_close;
	bool m_post_save;
};
