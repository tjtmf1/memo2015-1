#pragma once
#include "afxwin.h"
#include "Memo2Dlg.h"
#include "CheckSaveMemo.h"
// CPostIt 대화 상자입니다.

class CPostIt : public CDialogEx
{
	DECLARE_DYNAMIC(CPostIt)

public:
	CPostIt(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CPostIt();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_edit;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	CRect clientRect;
	CRect m_barRect;
	bool m_stWinMove;
	POINT m_stMove;
	CRect m_post_size;
	CRect m_memoRect;
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnBnClickedExit();
	afx_msg void OnEnChangeEdit1();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CEdit m_post_title;
	afx_msg void OnBnClickedAdd();
	POINT m_mouse_move;
	afx_msg void OnEnKillfocusEdit2();
	bool m_title_focus;

	CCheckSaveMemo m_check_wnd;

	int m_close_wnd;
	void closeWindow();
	void saveMemo();
	CBitmapButton m_exit_button;
	CBitmapButton m_save_button;
	CBitmapButton m_add_button;

	CRgn m_range;
	CRect rgn_rect;
	bool m_drag; 

	CString m_num;
	bool m_flag;
	CString m_content;
	CString m_title;

	CString m_id;
	int m_index;

	int color;

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
	afx_msg void OnBnClickedSaveit();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void On32773();
	afx_msg void On32774();
};
