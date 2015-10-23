// PageOrderInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "FemasContest.h"
#include "PageOrderInfo.h"
#include "afxdialogex.h"


// PageOrderInfo 对话框

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


// PageOrderInfo 消息处理程序


BOOL PageOrderInfo::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	listOrder.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	listOrder.InsertColumn(0, "系统报单", LVCFMT_LEFT, 60);
	listOrder.InsertColumn(1, "合约代码", LVCFMT_LEFT, 60);
	listOrder.InsertColumn(2, "报单类型", LVCFMT_LEFT, 60);
	listOrder.InsertColumn(3, "方向", LVCFMT_LEFT, 45);
	listOrder.InsertColumn(4, "开平", LVCFMT_LEFT, 45);
	listOrder.InsertColumn(5, "价格", LVCFMT_LEFT, 60);
	listOrder.InsertColumn(6, "数量", LVCFMT_LEFT, 60);
	listOrder.InsertColumn(7, "报入时间", LVCFMT_LEFT, 60);
	listOrder.InsertColumn(8, "状态", LVCFMT_LEFT, 45);
	listOrder.InsertColumn(9, "成交数量", LVCFMT_LEFT, 60);
	listOrder.InsertColumn(10, "剩余数量", LVCFMT_LEFT, 60);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void PageOrderInfo::OnNMDblclkListOrder(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	int ans = MessageBoxA("是否撤销该回报？", "确认", MB_YESNO);
	if (ans == 6) {
		reqOrderAction((LPTSTR)(LPCTSTR)listOrder.GetItemText(listOrder.GetSelectionMark(), 0));
		MessageBoxA("报单成功", "成功", MB_OK);
	}
	*pResult = 0;
}
