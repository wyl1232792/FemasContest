#pragma once
#include "afxwin.h"


// ConsoleDialog �Ի���

class ConsoleDialog : public CDialogEx
{
	DECLARE_DYNAMIC(ConsoleDialog)

public:
	ConsoleDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ConsoleDialog();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEdit editConsole;
};
