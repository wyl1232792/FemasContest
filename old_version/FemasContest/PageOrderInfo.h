#pragma once
#include "afxcmn.h"


// PageOrderInfo 对话框

class PageOrderInfo : public CDialogEx
{
	DECLARE_DYNAMIC(PageOrderInfo)

public:
	PageOrderInfo(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~PageOrderInfo();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = PAGE_ORDER_INFO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl listOrder;
	afx_msg void OnNMDblclkListOrder(NMHDR *pNMHDR, LRESULT *pResult);
};
