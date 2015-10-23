// ContractsDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "FemasContest.h"
#include "ContractsDialog.h"
#include "afxdialogex.h"


// ContractsDialog 对话框

IMPLEMENT_DYNAMIC(ContractsDialog, CDialogEx)

ContractsDialog::ContractsDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_SUBSCRIBE, pParent)
{

}

ContractsDialog::~ContractsDialog()
{
}

void ContractsDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_LIST1, c);
	DDX_Control(pDX, IDC_LIST_CONTRACT_SUBSCRIBE, listAvailableContracts);
}


BEGIN_MESSAGE_MAP(ContractsDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &ContractsDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &ContractsDialog::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &ContractsDialog::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON6, &ContractsDialog::OnBnClickedButton6)
	ON_WM_CLOSE()
//	ON_WM_CREATE()
END_MESSAGE_MAP()


// ContractsDialog 消息处理程序



void ContractsDialog::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
}


void ContractsDialog::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	bool flag = !listAvailableContracts.GetCheck(0);
	for (int i = 0; i < g_InstrumentCount; i++)
		listAvailableContracts.SetCheck(i, flag);
}


void ContractsDialog::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	int count = 0;
	for (int i = 0; i < g_InstrumentCount; i++)
		if (listAvailableContracts.GetCheck(i)) {
			isOrdered[i] = true;
			count++;
		}
	if (count > 50) {
		MessageBox("合约过多", "错误", MB_OK);
		return;
	}
	clearSubcribedContracts();
	reSubcribeContracts();
	OnClose();
}


void ContractsDialog::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	OnClose();
}


void ContractsDialog::OnClose()
{
	this->ShowWindow(SW_HIDE);
	CDialogEx::OnClose();
}


//int ContractsDialog::OnCreate(LPCREATESTRUCT lpCreateStruct)
//{
//	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
//		return -1;
//
//	// TODO:  在此添加您专用的创建代码
//
//	return 0;
//}


BOOL ContractsDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	contractsDlg.listAvailableContracts.SetExtendedStyle(LVS_EX_CHECKBOXES);

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
