// PagePositionInfo.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FemasContest.h"
#include "PagePositionInfo.h"
#include "afxdialogex.h"


// PagePositionInfo �Ի���

IMPLEMENT_DYNAMIC(PagePositionInfo, CDialogEx)

PagePositionInfo::PagePositionInfo(CWnd* pParent /*=NULL*/)
	: CDialogEx(PAGE_POSITION_INFO, pParent)
{

}

PagePositionInfo::~PagePositionInfo()
{
}

void PagePositionInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_POSITION, listPosition);
}


BEGIN_MESSAGE_MAP(PagePositionInfo, CDialogEx)
END_MESSAGE_MAP()


// PagePositionInfo ��Ϣ�������


BOOL PagePositionInfo::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	listPosition.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	listPosition.InsertColumn(0, "��Լ����", LVCFMT_LEFT, 60);
	listPosition.InsertColumn(1, "����", LVCFMT_LEFT, 60);
	listPosition.InsertColumn(2, "ռ�ñ�֤��", LVCFMT_LEFT, 60);
	listPosition.InsertColumn(3, "��ֲ�", LVCFMT_LEFT, 60);
	listPosition.InsertColumn(4, "��ֲֳɱ�", LVCFMT_LEFT, 60);
	listPosition.InsertColumn(5, "��ֲ�", LVCFMT_LEFT, 60);
	listPosition.InsertColumn(6, "��ֲֳɱ�", LVCFMT_LEFT, 60);
	listPosition.InsertColumn(7, "���ᱣ֤��", LVCFMT_LEFT, 60);
	listPosition.InsertColumn(8, "���ֶ���ֲ�", LVCFMT_LEFT, 60);
	listPosition.InsertColumn(9, "ƽ�ֶ���ֲ�", LVCFMT_LEFT, 60);
	listPosition.InsertColumn(10, "����Ȩ����", LVCFMT_LEFT, 60);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}
