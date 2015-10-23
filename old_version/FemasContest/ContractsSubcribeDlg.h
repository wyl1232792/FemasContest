#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// ContractsSubcribeDlg 对话框

class ContractsSubcribeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ContractsSubcribeDlg)

public:
	ContractsSubcribeDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ContractsSubcribeDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CONTRACTS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
//	CListCtrl listContracts;
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnClose();
//	CListCtrl listAvailableContracts;
//	CListCtrl listAvailableContract;
	CListCtrl listAvailableContracts;
	CEdit cEditx;
};
