#pragma once
#include "afxcmn.h"


// PageTradeInfo �Ի���

class PageTradeInfo : public CDialogEx
{
	DECLARE_DYNAMIC(PageTradeInfo)

public:
	PageTradeInfo(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~PageTradeInfo();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = PAGE_TRADE_INFO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl listTrade;
};
