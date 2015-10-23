// PageOrderInfo.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FemasContest.h"
#include "PageOrderInfo.h"
#include "afxdialogex.h"


// PageOrderInfo �Ի���

IMPLEMENT_DYNAMIC(PageOrderInfo, CDialogEx)

PageOrderInfo::PageOrderInfo(CWnd* pParent /*=NULL*/)
	: CDialogEx(PAGE_ORDER_INFO, pParent)
{

}

PageOrderInfo::~PageOrderInfo()
{
}

void PageOrderInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_ORDER, listOrder);
}


BEGIN_MESSAGE_MAP(PageOrderInfo, CDialogEx)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_ORDER, &PageOrderInfo::OnNMDblclkListOrder)
END_MESSAGE_MAP()


// PageOrderInfo ��Ϣ�������


BOOL PageOrderInfo::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	listOrder.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	listOrder.InsertColumn(0, "ϵͳ����", LVCFMT_LEFT, 60);
	listOrder.InsertColumn(1, "��Լ����", LVCFMT_LEFT, 60);
	listOrder.InsertColumn(2, "��������", LVCFMT_LEFT, 60);
	listOrder.InsertColumn(3, "����", LVCFMT_LEFT, 45);
	listOrder.InsertColumn(4, "��ƽ", LVCFMT_LEFT, 45);
	listOrder.InsertColumn(5, "�۸�", LVCFMT_LEFT, 60);
	listOrder.InsertColumn(6, "����", LVCFMT_LEFT, 60);
	listOrder.InsertColumn(7, "����ʱ��", LVCFMT_LEFT, 60);
	listOrder.InsertColumn(8, "״̬", LVCFMT_LEFT, 45);
	listOrder.InsertColumn(9, "�ɽ�����", LVCFMT_LEFT, 60);
	listOrder.InsertColumn(10, "ʣ������", LVCFMT_LEFT, 60);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void PageOrderInfo::OnNMDblclkListOrder(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int ans = MessageBoxA("�Ƿ����ûر���", "ȷ��", MB_YESNO);
	if (ans == 6) {
		reqOrderAction((LPTSTR)(LPCTSTR)listOrder.GetItemText(listOrder.GetSelectionMark(), 0));
		MessageBoxA("�����ɹ�", "�ɹ�", MB_OK);
	}
	*pResult = 0;
}
