#pragma once
#include "afxwin.h"
#include "Register.h"
#include "myGlobal.h"

// CLogin 대화 상자입니다.

class CLogin : public CDialogEx
{
	DECLARE_DYNAMIC(CLogin)

public:
	CLogin(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CLogin();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_LOGIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString m_id;
	CString m_passwd;
	CButton m_login;
	afx_msg void OnBnClickedSingin();
	CRegister m_register;
	bool m_check_login;
	afx_msg void OnBnClickedCancel();
	virtual BOOL DestroyWindow();
	afx_msg void OnBnClickedLoginBn();
	CEdit m_input_id;
	CEdit m_input_pw;
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
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	CStatic s1;
	CStatic s2;
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
};
