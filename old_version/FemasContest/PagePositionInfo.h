#pragma once
#include "afxcmn.h"


// PagePositionInfo 对话框

class PagePositionInfo : public CDialogEx
{
	DECLARE_DYNAMIC(PagePositionInfo)

public:
	PagePositionInfo(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~PagePositionInfo();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = PAGE_POSITION_INFO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl listPosition;
};
