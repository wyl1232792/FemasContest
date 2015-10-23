
// FemasContestDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FemasContest.h"
#include "FemasContestDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CFemasContestDlg �Ի���



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


// CFemasContestDlg ��Ϣ�������

BOOL CFemasContestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	//�µ�ָ������
	tabOrder.InsertItem(0, _T("�޼�ָ��"));
	tabOrder.InsertItem(1, _T("�м�ָ��"));
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

	//��Ϣ��ѯָ������
	tabInfo.InsertItem(0, _T("�ֲֲ�ѯ"));
	tabInfo.InsertItem(1, _T("ί�в�ѯ"));
	tabInfo.InsertItem(2, _T("�ɽ���ѯ"));
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

	//��Լ��Ϣ�����ʼ��
	listContracts.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	listContracts.InsertColumn(0, "��Լ����", LVCFMT_LEFT, 60);
	listContracts.InsertColumn(1, "�м�", LVCFMT_LEFT, 60);
	listContracts.InsertColumn(2, "��һ��", LVCFMT_LEFT, 60);
	listContracts.InsertColumn(3, "��һ��", LVCFMT_LEFT, 60);
	listContracts.InsertColumn(4, "��һ��", LVCFMT_LEFT, 60);
	listContracts.InsertColumn(5, "��һ��", LVCFMT_LEFT, 60);
	listContracts.InsertColumn(6, "���̼�", LVCFMT_LEFT, 60);
	listContracts.InsertColumn(7, "��߼�", LVCFMT_LEFT, 60);
	listContracts.InsertColumn(8, "��ͼ�", LVCFMT_LEFT, 60);
	listContracts.InsertColumn(9, "��ͣ��", LVCFMT_LEFT, 60);
	listContracts.InsertColumn(10, "��ͣ��", LVCFMT_LEFT, 60);
	listContracts.InsertColumn(11, "����", LVCFMT_LEFT, 60);
	listContracts.InsertColumn(12, "���ս���", LVCFMT_LEFT, 60);
	listContracts.InsertColumn(13, "ˢ��ʱ��", LVCFMT_LEFT, 60);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CFemasContestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CFemasContestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}





void CFemasContestDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	PostQuitMessage(0);
	CDialogEx::OnClose();
}


void CFemasContestDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	pageTabOrder[pageTabOrderIndex]->ShowWindow(SW_HIDE);
	pageTabOrderIndex = tabOrder.GetCurSel();
	pageTabOrder[pageTabOrderIndex]->ShowWindow(SW_SHOW);
}


void CFemasContestDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (contractsDlg.listAvailableContracts.GetItemCount() == 0)
		for (int i = 0; i < g_InstrumentCount; i++)
			contractsDlg.listAvailableContracts.InsertItem(i, g_InstrumentStatus[i].InstrumentID);
	contractsDlg.ShowWindow(SW_SHOW);
}


void CFemasContestDlg::OnTcnSelchangeTabInfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	pageTabInfo[pageTabInfoIndex]->ShowWindow(SW_HIDE);
	pageTabInfoIndex = tabInfo.GetCurSel();
	pageTabInfo[pageTabInfoIndex]->ShowWindow(SW_SHOW);
}


void CFemasContestDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	refreshOrderInfo();
	refreshInvestorAccountInfo();
	refreshPositionInfo();
	refreshTradeInfo();
}
