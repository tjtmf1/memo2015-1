#pragma once
#include "afxwin.h"
#include "myGlobal.h"

// CRegister 대화 상자입니다.

class CRegister : public CDialogEx
{
	DECLARE_DYNAMIC(CRegister)

public:
	CRegister(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CRegister();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_new_id;
	CEdit m_new_pw;
	afx_msg void OnBnClickedN();
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
	afx_msg void OnPaint();
};
