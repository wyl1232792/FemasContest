// InsertMarketPage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FemasContest.h"
#include "InsertMarketPage.h"
#include "afxdialogex.h"


// InsertMarketPage �Ի���

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


// InsertMarketPage ��Ϣ�������


void InsertMarketPage::OnBnClickedRadio6()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	s_HedgeFlag = USTP_FTDC_CHF_Speculation;
}


void InsertMarketPage::OnBnClickedRadio7()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	s_HedgeFlag = USTP_FTDC_CHF_Hedge;
}


void InsertMarketPage::OnBnClickedRadio1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	s_Direction = USTP_FTDC_D_Buy;
}


void InsertMarketPage::OnBnClickedRadio2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	s_Direction = USTP_FTDC_D_Sell;
}


void InsertMarketPage::OnBnClickedRadio3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	s_OffsetFlag = USTP_FTDC_OF_Open;
}


void InsertMarketPage::OnBnClickedRadio5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	s_OffsetFlag = USTP_FTDC_OF_Close;
}


void InsertMarketPage::OnBnClickedButtonSubmitMarket()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	MessageBox("����¼��ɹ�", "��Ϣ", MB_OK);
}


void InsertMarketPage::OnCbnSelchangeComboType()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	s_OrderType = orderType.GetCurSel();
}


BOOL InsertMarketPage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	orderType.AddString("ʣ���嵵�ɽ�");
	orderType.AddString("���ż۳ɽ�");
	orderType.AddString("��ͨ�м�");
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}
