#pragma once
#include "afxwin.h"

// CLoginDialog �Ի���

class CLoginDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CLoginDialog)

public:
	CLoginDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLoginDialog();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOGIN_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
