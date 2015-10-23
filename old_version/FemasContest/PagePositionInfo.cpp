// PagePositionInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "FemasContest.h"
#include "PagePositionInfo.h"
#include "afxdialogex.h"


// PagePositionInfo 对话框

IMPLEMENT_DYNAMIC(PagePositionInfo, CDialogEx)

PagePositionInfo::PagePositionInfo(CWnd* pParent /*=NULL*/)
	: CDialogEx(PAGE_POSITION_INFO, pParent)
{

}

PagePositionInfo::~PagePositionInfo()
{
}

void PagePositionInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_POSITION, listPosition);
}


BEGIN_MESSAGE_MAP(PagePositionInfo, CDialogEx)
END_MESSAGE_MAP()


// PagePositionInfo 消息处理程序


BOOL PagePositionInfo::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	listPosition.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	listPosition.InsertColumn(0, "合约代码", LVCFMT_LEFT, 60);
	listPosition.InsertColumn(1, "方向", LVCFMT_LEFT, 60);
	listPosition.InsertColumn(2, "占用保证金", LVCFMT_LEFT, 60);
	listPosition.InsertColumn(3, "今持仓", LVCFMT_LEFT, 60);
	listPosition.InsertColumn(4, "今持仓成本", LVCFMT_LEFT, 60);
	listPosition.InsertColumn(5, "昨持仓", LVCFMT_LEFT, 60);
	listPosition.InsertColumn(6, "昨持仓成本", LVCFMT_LEFT, 60);
	listPosition.InsertColumn(7, "冻结保证金", LVCFMT_LEFT, 60);
	listPosition.InsertColumn(8, "开仓冻结持仓", LVCFMT_LEFT, 60);
	listPosition.InsertColumn(9, "平仓冻结持仓", LVCFMT_LEFT, 60);
	listPosition.InsertColumn(10, "冻结权利金", LVCFMT_LEFT, 60);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
