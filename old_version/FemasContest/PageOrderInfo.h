#pragma once
#include "afxcmn.h"


// PageOrderInfo �Ի���

class PageOrderInfo : public CDialogEx
{
	DECLARE_DYNAMIC(PageOrderInfo)

public:
	PageOrderInfo(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~PageOrderInfo();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = PAGE_ORDER_INFO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl listOrder;
	afx_msg void OnNMDblclkListOrder(NMHDR *pNMHDR, LRESULT *pResult);
};
