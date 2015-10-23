// InsertLimitPage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FemasContest.h"
#include "InsertLimitPage.h"
#include "afxdialogex.h"


// InsertLimitPage �Ի���

IMPLEMENT_DYNAMIC(InsertLimitPage, CDialogEx)

InsertLimitPage::InsertLimitPage(CWnd* pParent /*=NULL*/)
	: CDialogEx(PAGE_INSERT_LIMIT, pParent)
	, s_Direction('0')
	, s_HedgeFlag('0')
	, s_OffsetFlag('0')
{

	s_OrderType = 0;
	s_Count = 0;
}

InsertLimitPage::~InsertLimitPage()
{
}

void InsertLimitPage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_INTRUMENTID, s_InstrumentID);
	DDX_Text(pDX, IDC_EDIT_PRICE, s_LimitPrice);
	DDX_Text(pDX, IDC_EDIT_VOLUME, s_Volume);
	DDX_Control(pDX, IDC_COMBO_TYPE, orderType);
	DDX_Control(pDX, IDC_EDIT_COUNT, editCount);
}


BEGIN_MESSAGE_MAP(InsertLimitPage, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SUBMIT_LIMIT, &InsertLimitPage::OnBnClickedButtonSubmitLimit)
	ON_BN_CLICKED(IDC_RADIO3, &InsertLimitPage::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO6, &InsertLimitPage::OnBnClickedRadio6)
	ON_BN_CLICKED(IDC_RADIO7, &InsertLimitPage::OnBnClickedRadio7)
	ON_BN_CLICKED(IDC_RADIO1, &InsertLimitPage::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &InsertLimitPage::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO5, &InsertLimitPage::OnBnClickedRadio5)
	ON_CBN_SELCHANGE(IDC_COMBO_TYPE, &InsertLimitPage::OnCbnSelchangeComboType)
END_MESSAGE_MAP()


// InsertLimitPage ��Ϣ�������


void InsertLimitPage::OnBnClickedButtonSubmitLimit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CUstpFtdcInputOrderField tmp;
	memset(&tmp, 0, sizeof(tmp));
	CString cs;
	editCount.GetWindowTextA(cs);
	s_Count = _ttoi(cs);
	GetDlgItem(IDC_EDIT_INTRUMENTID)->GetWindowTextA(s_InstrumentID);
	GetDlgItem(IDC_EDIT_PRICE)->GetWindowTextA(s_LimitPrice);
	GetDlgItem(IDC_EDIT_VOLUME)->GetWindowTextA(s_Volume);
	strcpy(tmp.InstrumentID, s_InstrumentID);
	tmp.HedgeFlag = s_HedgeFlag;
	tmp.Direction = s_Direction;
	tmp.OffsetFlag = s_OffsetFlag;
	tmp.LimitPrice = _ttol(s_LimitPrice);
	tmp.Volume = _ttoi(s_Volume);
	insertLimitOrder(&tmp, s_OrderType, s_Count);
	MessageBox("����¼��ɹ�", "��Ϣ", MB_OK);
}


void InsertLimitPage::OnBnClickedRadio3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	s_OffsetFlag = USTP_FTDC_OF_Open;
}


void InsertLimitPage::OnBnClickedRadio6()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	s_HedgeFlag = USTP_FTDC_CHF_Speculation;
}


void InsertLimitPage::OnBnClickedRadio7()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	s_HedgeFlag = USTP_FTDC_CHF_Hedge;
}


void InsertLimitPage::OnBnClickedRadio1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	s_Direction = USTP_FTDC_D_Buy;
}


void InsertLimitPage::OnBnClickedRadio2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	s_Direction = USTP_FTDC_D_Sell;
}


void InsertLimitPage::OnBnClickedRadio5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	s_OffsetFlag = USTP_FTDC_OF_Close;
}


void InsertLimitPage::OnCbnSelchangeComboType()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	s_OrderType = orderType.GetCurSel();
}


BOOL InsertLimitPage::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	orderType.InsertString(0, "��ͨ�޼�");
	orderType.InsertString(1, "FAK");
	orderType.InsertString(2, "FOK");
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}
