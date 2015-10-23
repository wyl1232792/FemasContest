// ContractsDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FemasContest.h"
#include "ContractsDialog.h"
#include "afxdialogex.h"


// ContractsDialog �Ի���

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


// ContractsDialog ��Ϣ�������



void ContractsDialog::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void ContractsDialog::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	bool flag = !listAvailableContracts.GetCheck(0);
	for (int i = 0; i < g_InstrumentCount; i++)
		listAvailableContracts.SetCheck(i, flag);
}


void ContractsDialog::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int count = 0;
	for (int i = 0; i < g_InstrumentCount; i++)
		if (listAvailableContracts.GetCheck(i)) {
			isOrdered[i] = true;
			count++;
		}
	if (count > 50) {
		MessageBox("��Լ����", "����", MB_OK);
		return;
	}
	clearSubcribedContracts();
	reSubcribeContracts();
	OnClose();
}


void ContractsDialog::OnBnClickedButton6()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
//	// TODO:  �ڴ������ר�õĴ�������
//
//	return 0;
//}


BOOL ContractsDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	contractsDlg.listAvailableContracts.SetExtendedStyle(LVS_EX_CHECKBOXES);

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}
