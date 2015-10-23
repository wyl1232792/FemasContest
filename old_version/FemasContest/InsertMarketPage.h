#pragma once
#include "afxwin.h"


// InsertMarketPage �Ի���

class InsertMarketPage : public CDialogEx
{
	DECLARE_DYNAMIC(InsertMarketPage)

public:
	InsertMarketPage(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~InsertMarketPage();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = PAGE_MARKET_ORDER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString s_InstrumentID;
//	CString s_Volume;
	afx_msg void OnBnClickedRadio6();
	int s_HedgeFlag;
	int s_Direction;
	int s_OffsetFlag;
	afx_msg void OnBnClickedRadio7();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio5();
	afx_msg void OnBnClickedButtonSubmitMarket();
	CEdit editVolume;
	CComboBox orderType;
	afx_msg void OnCbnSelchangeComboType();
	int s_OrderType;
	virtual BOOL OnInitDialog();
};
