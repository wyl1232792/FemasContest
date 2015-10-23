
// FemasContestDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "FemasContest.h"
#include "FemasContestDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CFemasContestDlg 对话框



CFemasContestDlg::CFemasContestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_FEMASCONTEST_DIALOG, pParent)
	, s_Account1(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFemasContestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STATIC_ACC1, s_Account1);
	DDX_Control(pDX, IDC_TAB_ORDER, tabOrder);
	DDX_Control(pDX, IDC_LIST_CONTRACTS, listContracts);
	DDX_Control(pDX, IDC_TAB_INFO, tabInfo);
}

BEGIN_MESSAGE_MAP(CFemasContestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_ORDER, &CFemasContestDlg::OnTcnSelchangeTab1)
	ON_BN_CLICKED(IDC_BUTTON1, &CFemasContestDlg::OnBnClickedButton1)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_INFO, &CFemasContestDlg::OnTcnSelchangeTabInfo)
	ON_WM_TIMER()
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_CONTRACTS, &CFemasContestDlg::OnNMDblclkListContracts)
	ON_BN_CLICKED(IDC_BUTTON2, &CFemasContestDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CFemasContestDlg 消息处理程序

BOOL CFemasContestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	//下单指令区域
	tabOrder.InsertItem(0, _T("限价指令"));
	tabOrder.InsertItem(1, _T("市价指令"));
	CRect rec;
	tabOrder.GetClientRect(rec);
	rec.bottom -= 2;
	rec.top += 28;
	rec.right -= 3;
	pageInsertMarketOrder.Create(PAGE_MARKET_ORDER, &tabOrder);
	pageInsertMarketOrder.MoveWindow(&rec);
	pageInsertMarketOrder.ShowWindow(SW_HIDE);
	pageInsertLimitOrder.Create(PAGE_INSERT_LIMIT, &tabOrder);
	pageInsertLimitOrder.MoveWindow(&rec);
	pageInsertLimitOrder.ShowWindow(SW_SHOW);
	pageTabOrder[0] = &pageInsertLimitOrder;
	pageTabOrder[1] = &pageInsertMarketOrder;
	pageTabOrderIndex = 0;

	//信息查询指令区域
	tabInfo.InsertItem(0, _T("持仓查询"));
	tabInfo.InsertItem(1, _T("委托查询"));
	tabInfo.InsertItem(2, _T("成交查询"));
	tabInfo.GetClientRect(rec);
	rec.bottom -= 2;
	rec.top += 23;
	rec.right -= 3;
	pagePositionInfo.Create(PAGE_POSITION_INFO, &tabInfo);
	pagePositionInfo.MoveWindow(&rec);
	pagePositionInfo.ShowWindow(SW_SHOW);
	pageOrderInfo.Create(PAGE_ORDER_INFO, &tabInfo);
	pageOrderInfo.MoveWindow(&rec);
	pageOrderInfo.ShowWindow(SW_HIDE);
	pageTradeInfo.Create(PAGE_TRADE_INFO, &tabInfo);
	pageTradeInfo.MoveWindow(&rec);
	pageTradeInfo.ShowWindow(SW_HIDE);
	pageTabInfo[0] = &pagePositionInfo;
	pageTabInfo[1] = &pageOrderInfo;
	pageTabInfo[2] = &pageTradeInfo;
	pageTabInfoIndex = 0;

	//合约信息区域初始化
	listContracts.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	listContracts.InsertColumn(0, "合约代码", LVCFMT_LEFT, 60);
	listContracts.InsertColumn(1, "市价", LVCFMT_LEFT, 60);
	listContracts.InsertColumn(2, "卖一价", LVCFMT_LEFT, 60);
	listContracts.InsertColumn(3, "买一价", LVCFMT_LEFT, 60);
	listContracts.InsertColumn(4, "卖一量", LVCFMT_LEFT, 60);
	listContracts.InsertColumn(5, "买一量", LVCFMT_LEFT, 60);
	listContracts.InsertColumn(6, "开盘价", LVCFMT_LEFT, 60);
	listContracts.InsertColumn(7, "最高价", LVCFMT_LEFT, 60);
	listContracts.InsertColumn(8, "最低价", LVCFMT_LEFT, 60);
	listContracts.InsertColumn(9, "涨停板", LVCFMT_LEFT, 60);
	listContracts.InsertColumn(10, "跌停板", LVCFMT_LEFT, 60);
	listContracts.InsertColumn(11, "昨收", LVCFMT_LEFT, 60);
	listContracts.InsertColumn(12, "昨日结算", LVCFMT_LEFT, 60);
	listContracts.InsertColumn(13, "刷新时间", LVCFMT_LEFT, 60);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CFemasContestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CFemasContestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CFemasContestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}





void CFemasContestDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	PostQuitMessage(0);
	CDialogEx::OnClose();
}


void CFemasContestDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	pageTabOrder[pageTabOrderIndex]->ShowWindow(SW_HIDE);
	pageTabOrderIndex = tabOrder.GetCurSel();
	pageTabOrder[pageTabOrderIndex]->ShowWindow(SW_SHOW);
}


void CFemasContestDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	if (contractsDlg.listAvailableContracts.GetItemCount() == 0)
		for (int i = 0; i < g_InstrumentCount; i++)
			contractsDlg.listAvailableContracts.InsertItem(i, g_InstrumentStatus[i].InstrumentID);
	contractsDlg.ShowWindow(SW_SHOW);
}


void CFemasContestDlg::OnTcnSelchangeTabInfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	pageTabInfo[pageTabInfoIndex]->ShowWindow(SW_HIDE);
	pageTabInfoIndex = tabInfo.GetCurSel();
	pageTabInfo[pageTabInfoIndex]->ShowWindow(SW_SHOW);
}


void CFemasContestDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//give candle-line chart
	if (nIDEvent == 1) {
		for (int i = 0; i < g_OrderedInstrumentCount; i++) {
			int iID = pLastMarketData[i]->m_InstrumentID;
			if ((!pMinuteMarketData[i]->isInit) && pLastMarketData[i]->count != 0)
			{
				pMinuteMarketData[i]->avgPrice = pLastMarketData[i]->last().LastPrice;
				pMinuteMarketData[i]->maxChg = abs(pLastMarketData[i]->last().PreSettlementPrice - pLastMarketData[i]->last().LastPrice);
				pMinuteMarketData[i]->maxPosition = pLastMarketData[i]->last().OpenInterest;
				pMinuteMarketData[i]->minPosition = pLastMarketData[i]->last().OpenInterest;
				pMinuteMarketData[i]->maxVolume = 0;
				pMinuteMarketData[i]->lastIndex = 0;
				pMinuteMarketData[i]->operator[](0).avgPrice = pMinuteMarketData[i]->avgPrice;
				pMinuteMarketData[i]->operator[](0).firstPrice = pLastMarketData[i]->last().LastPrice;
				pMinuteMarketData[i]->operator[](0).lastPrice = pLastMarketData[i]->last().LastPrice;
				pMinuteMarketData[i]->operator[](0).firstVolume = pLastMarketData[i]->last().Volume;
				pMinuteMarketData[i]->operator[](0).lastVolume = pLastMarketData[i]->last().Volume;
				pMinuteMarketData[i]->operator[](0).highestPrice = pLastMarketData[i]->last().LastPrice;
				pMinuteMarketData[i]->operator[](0).lowestPrice = pLastMarketData[i]->last().LastPrice;
				pMinuteMarketData[i]->operator[](0).position = pLastMarketData[i]->last().OpenInterest;
				pMinuteMarketData[i]->isInit = true;
			}
			pLastMarketData[i]->pushToMinuteMarketData(pMinuteMarketData[i]);
		}
	}
	if (nIDEvent == 2) {
		refreshInvestorAccountInfo();
		refreshPositionInfo();
		refreshTradeInfo();
	}
	CDialogEx::OnTimer(nIDEvent);
}


void CFemasContestDlg::OnNMDblclkListContracts(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	int index = listContracts.GetSelectionMark();
	chartDlg.focusedInstrumentID = pLastMarketData[index]->m_InstrumentID;
	chartDlg.focusedOrderedInstrumentID = index;
	chartDlg.ShowWindow(SW_SHOW);
	chartDlg.Invalidate();
	chartDlg.paint();
	*pResult = 0;
}


void CFemasContestDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	refreshOrderInfo();
	refreshInvestorAccountInfo();
	refreshPositionInfo();
	refreshTradeInfo();
}
