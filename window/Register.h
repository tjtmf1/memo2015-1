#pragma once
#include "afxwin.h"
#include "myGlobal.h"

// CRegister ��ȭ �����Դϴ�.

class CRegister : public CDialogEx
{
	DECLARE_DYNAMIC(CRegister)

public:
	CRegister(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CRegister();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
