#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// ContractsSubcribeDlg �Ի���

class ContractsSubcribeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ContractsSubcribeDlg)

public:
	ContractsSubcribeDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ContractsSubcribeDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CONTRACTS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
