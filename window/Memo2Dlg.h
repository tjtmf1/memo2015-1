
// Memo2Dlg.h : 헤더 파일
//

#pragma once
#include "PostIt.h"
#include <vector>
#include "Login.h"
#include "afxcmn.h"
#include "afxwin.h"
#define WM_TRAY_NOTIFICATION WM_APP+1

using namespace std;

class CPostIt;
// CMemo2Dlg 대화 상자
class CMemo2Dlg : public CDialogEx
{
// 생성입니다.
public:
	CMemo2Dlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_MEMO2_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	vector<CPostIt*> m_post_it;
	int m_num;
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	CLogin m_loginWindow;
	void MakeNewMemo();
	void CloseMain();

	CString id;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void On32771();
	afx_msg void On32772();

	afx_msg LRESULT OnTrayNotification(WPARAM, LPARAM);
	bool m_tray;
	void RegistTray();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedCancel();
	CListCtrl m_list;
	CString m_num2;

	vector<CString> v;

	bool m_flag;

	CString char2CString(char* inp)
	{
		int len;
		CString str;
		BSTR buf;

		len = MultiByteToWideChar(CP_ACP, 0, inp, (int)strlen(inp), NULL, NULL);
		buf = SysAllocStringLen(NULL, len);
		MultiByteToWideChar(CP_ACP, 0, inp, (int)strlen(inp), buf, len);
		str.Format(_T("%s"), buf);

		return str;
	}
	char* CString2char(CString& str)
	{
		long len = str.GetLength();
		len = len * 2;
		char* szTemp = new char[len + 1];
		memset(szTemp, 0, len + 1);
		USES_CONVERSION;
		strcpy_s(szTemp, len, T2A(str));

		return szTemp;
	}

	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
	int column;
	afx_msg void OnBnClickedDelete();
	afx_msg void OnBnClickedButton3();
	void OnUpdateList();
	CMFCButton m_b1;
	CButton m_b2;
	CButton m_b3;
};
