#pragma once
#include "afxwin.h"


// InsertLimitPage 对话框

class InsertLimitPage : public CDialogEx
{
	DECLARE_DYNAMIC(InsertLimitPage)

public:
	InsertLimitPage(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~InsertLimitPage();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = PAGE_INSERT_LIMIT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonSubmitLimit();
	afx_msg void OnBnClickedRadio3();
	int s_Direction;
//	int s_InstrumentID;
	int s_HedgeFlag;
	int s_OffsetFlag;
//	int s_LimitPrice;
//	int s_Volume;
	CString s_InstrumentID;
	CString s_LimitPrice;
	CString s_Volume;
	afx_msg void OnBnClickedRadio6();
	afx_msg void OnBnClickedRadio7();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio5();
	CComboBox orderType;
	int s_OrderType;
	afx_msg void OnCbnSelchangeComboType();
	CEdit editCount;
	int s_Count;
	virtual BOOL OnInitDialog();
};
