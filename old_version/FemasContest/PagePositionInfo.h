#pragma once
#include "afxcmn.h"


// PagePositionInfo �Ի���

class PagePositionInfo : public CDialogEx
{
	DECLARE_DYNAMIC(PagePositionInfo)

public:
	PagePositionInfo(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~PagePositionInfo();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = PAGE_POSITION_INFO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl listPosition;
};
