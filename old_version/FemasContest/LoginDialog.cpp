// LoginDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "FemasContest.h"
#include "LoginDialog.h"
#include "afxdialogex.h"


// CLoginDialog 对话框

IMPLEMENT_DYNAMIC(CLoginDialog, CDialogEx)

CLoginDialog::CLoginDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_LOGIN_DIALOG, pParent)
	, s_BrokerID(_T(""))
	, s_UserID(_T(""))
	, s_Password(_T(""))
	, s_InvestorID(_T(""))
{

}

CLoginDialog::~CLoginDialog()
{
}

void CLoginDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_BROKER_ID_EDIT, s_BrokerID);
	DDX_Text(pDX, IDC_USERID_EDIT, s_UserID);
	DDX_Text(pDX, IDC_PASSWORD_EDIT, s_Password);
	DDX_Text(pDX, IDC_EDIT_INVESTOR_ID, s_InvestorID);
}


BEGIN_MESSAGE_MAP(CLoginDialog, CDialogEx)
	ON_BN_CLICKED(IDC_LoginButton2, &CLoginDialog::OnBnClickedLoginbutton2)
	ON_BN_CLICKED(IDC_LoginButton, &CLoginDialog::OnBnClickedLoginbutton)
END_MESSAGE_MAP()


// CLoginDialog 消息处理程序


void CLoginDialog::OnBnClickedLoginbutton2()
{
	// TODO: 在此添加控件通知处理程序代码
	PostQuitMessage(0);
}


void CLoginDialog::OnBnClickedLoginbutton()
{
	if (!g_Connection)
	{
		MessageBox("请确认此时为交易时段", "服务器连接错误", MB_OK);
		return;
	}

	GetDlgItem(IDC_BROKER_ID_EDIT)->GetWindowTextA(s_BrokerID);
	GetDlgItem(IDC_USERID_EDIT)->GetWindowTextA(s_UserID);
	GetDlgItem(IDC_PASSWORD_EDIT)->GetWindowTextA(s_Password);
	GetDlgItem(IDC_EDIT_INVESTOR_ID)->GetWindowTextA(s_InvestorID);
	strcpy(g_BrokerID, (LPCTSTR)s_BrokerID);
	strcpy(g_UserID, (LPCTSTR)s_UserID);
	strcpy(g_Password, (LPCTSTR)s_Password);
	strcpy(g_InvestorID, (LPCTSTR)s_InvestorID);
	CUstpFtdcReqUserLoginField loginFeild;
	strcpy(loginFeild.BrokerID, g_BrokerID);
	strcpy(loginFeild.UserID, g_UserID);
	strcpy(loginFeild.Password, g_Password);
	strcpy(loginFeild.UserProductInfo, g_ProductInfo);
	if (traderUserApi->ReqUserLogin(&loginFeild, 0) || mdUserApi->ReqUserLogin(&loginFeild, g_nOrLocalID++))
		MessageBox("登录失败", "登录失败", MB_OK);
}

BOOL CLoginDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	CFileFind finder;   //查找是否存在ini文件，若不存在，则生成一个新的默认设置的ini文件，这样就保证了我们更改后的设置每次都可用  
	BOOL ifFind = finder.FindFile(_T("user.ini"));
	if (!ifFind)
	{
		WritePrivateProfileStringA("User Info", "BrokerID", "", ".//user.ini");
		WritePrivateProfileStringA("User Info", "UserID", "", ".//user.ini");
		WritePrivateProfileStringA("User Info", "InvestorID", "", ".//user.ini");
		WritePrivateProfileStringA("User Info", "PassWord", "", ".//user.ini");
	}
	GetPrivateProfileStringA("User Info", "BrokerID", "", s_BrokerID.GetBuffer(50), 50, ".//user.ini");
	GetPrivateProfileStringA("User Info", "UserID", "", s_UserID.GetBuffer(50), 50, ".//user.ini");
	GetPrivateProfileStringA("User Info", "InvestorID", "", s_InvestorID.GetBuffer(50), 50, ".//user.ini");
	GetPrivateProfileStringA("User Info", "PassWord", "", s_Password.GetBuffer(50), 50, ".//user.ini");
	GetDlgItem(IDC_BROKER_ID_EDIT)->SetWindowTextA(s_BrokerID);
	GetDlgItem(IDC_USERID_EDIT)->SetWindowTextA(s_UserID);
	GetDlgItem(IDC_PASSWORD_EDIT)->SetWindowTextA(s_Password);
	GetDlgItem(IDC_EDIT_INVESTOR_ID)->SetWindowTextA(s_InvestorID);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
