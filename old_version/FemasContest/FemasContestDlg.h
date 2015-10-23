
// FemasContestDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"


// CFemasContestDlg 对话框
class CFemasContestDlg : public CDialogEx
{
// 构造
public:
	CFemasContestDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FEMASCONTEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString s_Account1;
	afx_msg void OnClose();
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	CTabCtrl tabOrder;
	// 合约列表控件变量
	CListCtrl listContracts;
	afx_msg void OnLvnItemchangedListContracts(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton1();
	CTabCtrl tabInfo;
	afx_msg void OnTcnSelchangeTabInfo(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnNMDblclkListContracts(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton2();
};
