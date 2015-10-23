#pragma once
#include "afxcmn.h"


// ContractsDialog 对话框

class ContractsDialog : public CDialogEx
{
	DECLARE_DYNAMIC(ContractsDialog)

public:
	ContractsDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ContractsDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SUBSCRIBE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
//	CListCtrl c;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton1();
	CListCtrl listAvailableContracts;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnClose();
//	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();
};
