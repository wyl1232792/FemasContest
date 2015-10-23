#pragma once
#include "afxwin.h"

// CLoginDialog 对话框

class CLoginDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CLoginDialog)

public:
	CLoginDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLoginDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOGIN_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedLoginbutton2();
	afx_msg void OnBnClickedLoginbutton();
	CString s_BrokerID;
	CString s_UserID;
	CString s_Password;
	CString s_InvestorID;
	virtual BOOL OnInitDialog();
};
