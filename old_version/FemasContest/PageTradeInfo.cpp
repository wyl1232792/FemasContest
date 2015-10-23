// PageTradeInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "FemasContest.h"
#include "PageTradeInfo.h"
#include "afxdialogex.h"


// PageTradeInfo 对话框

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


// PageTradeInfo 消息处理程序


BOOL PageTradeInfo::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	listTrade.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	listTrade.InsertColumn(0, "成交编号", LVCFMT_LEFT, 60);
	listTrade.InsertColumn(1, "合约代码", LVCFMT_LEFT, 60);
	listTrade.InsertColumn(2, "方向", LVCFMT_LEFT, 60);
	listTrade.InsertColumn(3, "开平", LVCFMT_LEFT, 60);
	listTrade.InsertColumn(4, "成交价", LVCFMT_LEFT, 60);
	listTrade.InsertColumn(5, "数量", LVCFMT_LEFT, 60);
	listTrade.InsertColumn(6, "时间", LVCFMT_LEFT, 60);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
