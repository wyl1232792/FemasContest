// PageTradeInfo.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FemasContest.h"
#include "PageTradeInfo.h"
#include "afxdialogex.h"


// PageTradeInfo �Ի���

IMPLEMENT_DYNAMIC(PageTradeInfo, CDialogEx)

PageTradeInfo::PageTradeInfo(CWnd* pParent /*=NULL*/)
	: CDialogEx(PAGE_TRADE_INFO, pParent)
{

}

PageTradeInfo::~PageTradeInfo()
{
}

void PageTradeInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_TRADE, listTrade);
}


BEGIN_MESSAGE_MAP(PageTradeInfo, CDialogEx)
END_MESSAGE_MAP()


// PageTradeInfo ��Ϣ�������


BOOL PageTradeInfo::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	listTrade.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	listTrade.InsertColumn(0, "�ɽ����", LVCFMT_LEFT, 60);
	listTrade.InsertColumn(1, "��Լ����", LVCFMT_LEFT, 60);
	listTrade.InsertColumn(2, "����", LVCFMT_LEFT, 60);
	listTrade.InsertColumn(3, "��ƽ", LVCFMT_LEFT, 60);
	listTrade.InsertColumn(4, "�ɽ���", LVCFMT_LEFT, 60);
	listTrade.InsertColumn(5, "����", LVCFMT_LEFT, 60);
	listTrade.InsertColumn(6, "ʱ��", LVCFMT_LEFT, 60);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}
