// ConsoleDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FemasContest.h"
#include "ConsoleDialog.h"
#include "afxdialogex.h"


// ConsoleDialog �Ի���

IMPLEMENT_DYNAMIC(ConsoleDialog, CDialogEx)

ConsoleDialog::ConsoleDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

ConsoleDialog::~ConsoleDialog()
{
}

void ConsoleDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CONSOLE, editConsole);
}


BEGIN_MESSAGE_MAP(ConsoleDialog, CDialogEx)
END_MESSAGE_MAP()


// ConsoleDialog ��Ϣ�������
