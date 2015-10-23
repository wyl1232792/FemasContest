// InsertMarketPage.cpp : 实现文件
//

#include "stdafx.h"
#include "FemasContest.h"
#include "InsertMarketPage.h"
#include "afxdialogex.h"


// InsertMarketPage 对话框

IMPLEMENT_DYNAMIC(InsertMarketPage, CDialogEx)

InsertMarketPage::InsertMarketPage(CWnd* pParent /*=NULL*/)
	: CDialogEx(PAGE_MARKET_ORDER, pParent)
	, s_InstrumentID(_T(""))
{

	s_HedgeFlag = 0;
	s_Direction = 0;
	s_OffsetFlag = 0;
	s_OrderType = 0;
}

InsertMarketPage::~InsertMarketPage()
{
}

void InsertMarketPage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_INSTRUMENT_ID, s_InstrumentID);
	//  DDX_Text(pDX, IDC_VOLUME, s_Volume);
	DDX_Control(pDX, IDC_VOLUME, editVolume);
	DDX_Control(pDX, IDC_COMBO_TYPE, orderType);
}


BEGIN_MESSAGE_MAP(InsertMarketPage, CDialogEx)
	ON_BN_CLICKED(IDC_RADIO6, &InsertMarketPage::OnBnClickedRadio6)
	ON_BN_CLICKED(IDC_RADIO7, &InsertMarketPage::OnBnClickedRadio7)
	ON_BN_CLICKED(IDC_RADIO1, &InsertMarketPage::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &InsertMarketPage::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &InsertMarketPage::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO5, &InsertMarketPage::OnBnClickedRadio5)
	ON_BN_CLICKED(IDC_BUTTON_SUBMIT_MARKET, &InsertMarketPage::OnBnClickedButtonSubmitMarket)
	ON_CBN_SELCHANGE(IDC_COMBO_TYPE, &InsertMarketPage::OnCbnSelchangeComboType)
END_MESSAGE_MAP()


// InsertMarketPage 消息处理程序


void InsertMarketPage::OnBnClickedRadio6()
{
	// TODO: 在此添加控件通知处理程序代码
	s_HedgeFlag = USTP_FTDC_CHF_Speculation;
}


void InsertMarketPage::OnBnClickedRadio7()
{
	// TODO: 在此添加控件通知处理程序代码
	s_HedgeFlag = USTP_FTDC_CHF_Hedge;
}


void InsertMarketPage::OnBnClickedRadio1()
{
	// TODO: 在此添加控件通知处理程序代码
	s_Direction = USTP_FTDC_D_Buy;
}


void InsertMarketPage::OnBnClickedRadio2()
{
	// TODO: 在此添加控件通知处理程序代码
	s_Direction = USTP_FTDC_D_Sell;
}


void InsertMarketPage::OnBnClickedRadio3()
{
	// TODO: 在此添加控件通知处理程序代码
	s_OffsetFlag = USTP_FTDC_OF_Open;
}


void InsertMarketPage::OnBnClickedRadio5()
{
	// TODO: 在此添加控件通知处理程序代码
	s_OffsetFlag = USTP_FTDC_OF_Close;
}


void InsertMarketPage::OnBnClickedButtonSubmitMarket()
{
	// TODO: 在此添加控件通知处理程序代码
	CUstpFtdcInputOrderField tmp;
	CString s_Volume;
	memset(&tmp, 0, sizeof(tmp));
	GetDlgItem(IDC_EDIT_INSTRUMENT_ID)->GetWindowTextA(s_InstrumentID);
	editVolume.GetWindowTextA(s_Volume);
	strcpy(tmp.InstrumentID, s_InstrumentID);
	tmp.HedgeFlag = s_HedgeFlag;
	tmp.Direction = s_Direction;
	tmp.OffsetFlag = s_OffsetFlag;
	tmp.Volume = _ttoi(s_Volume);
	insertMarketOrder(&tmp, s_OrderType);
	MessageBox("报单录入成功", "消息", MB_OK);
}


void InsertMarketPage::OnCbnSelchangeComboType()
{
	// TODO: 在此添加控件通知处理程序代码
	s_OrderType = orderType.GetCurSel();
}


BOOL InsertMarketPage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	orderType.AddString("剩余五档成交");
	orderType.AddString("最优价成交");
	orderType.AddString("普通市价");
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
