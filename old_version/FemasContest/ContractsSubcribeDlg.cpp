// ContractsSubcribeDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "FemasContest.h"
#include "ContractsSubcribeDlg.h"
#include "afxdialogex.h"


// ContractsSubcribeDlg 对话框

IMPLEMENT_DYNAMIC(ContractsSubcribeDlg, CDialogEx)

ContractsSubcribeDlg::ContractsSubcribeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_CONTRACTS, pParent)
{

}

ContractsSubcribeDlg::~ContractsSubcribeDlg()
{
}

void ContractsSubcribeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_LIST2, listContracts);
	//  DDX_Control(pDX, IDC_LIST2, listAvailableContracts);
	//  DDX_Control(pDX, IDC_LIST_AVAILABLE_CONTRACT, listAvailableContract);
	DDX_Control(pDX, IDC_LIST_AVAILABLE_CONTRACT, listAvailableContracts);
	DDX_Control(pDX, IDC_EDIT1, cEditx);
}


BEGIN_MESSAGE_MAP(ContractsSubcribeDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON5, &ContractsSubcribeDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON4, &ContractsSubcribeDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON3, &ContractsSubcribeDlg::OnBnClickedButton3)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// ContractsSubcribeDlg 消息处理程序

BOOL ContractsSubcribeDlg::OnInitDialog()
{
	contractsDlg.listAvailableContracts.SetExtendedStyle(LVS_EX_CHECKBOXES);
	contractsDlg.listAvailableContracts.InsertColumn(0, "合约代码", LVCFMT_LEFT, 60);
	cEditx.SetWindowTextA("aweg");
	return TRUE;
}


void ContractsSubcribeDlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	OnClose();
}


void ContractsSubcribeDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	for (int i = 0; i < g_InstrumentCount; i++)
		isOrdered[i] = (bool)listAvailableContracts.GetCheck(i);
	clearSubcribedContracts();
	reSubcribeContracts();
	OnClose();
}


void ContractsSubcribeDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	bool flag = !listAvailableContracts.GetCheck(0);
	for (int i = 0; i < g_InstrumentCount; i++)
		listAvailableContracts.SetCheck(i, flag);
}


void ContractsSubcribeDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	this->ShowWindow(SW_HIDE);
	CDialogEx::OnClose();
}
