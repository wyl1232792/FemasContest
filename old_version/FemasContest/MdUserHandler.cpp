#include "stdafx.h"
#include "MdUserHandler.h"

MdUserHandler::MdUserHandler(CUstpFtdcMduserApi * pUserApi) : m_pUserApi(pUserApi)
{
}


MdUserHandler::~MdUserHandler()
{
}

void MdUserHandler::setApi(CUstpFtdcMduserApi * pUserApi)
{
	m_pUserApi = pUserApi;
}

void MdUserHandler::OnFrontConnected()
{
	g_Connection = true;
}

void MdUserHandler::OnFrontDisconnected(int nReason)
{
}

void MdUserHandler::OnHeartBeatWarning(int nTimeLapse)
{
	MessageBox(NULL, "网络延迟异常", "网络异常", MB_OK);
	CUstpFtdcReqUserLoginField loginFeild;
	strcpy(loginFeild.BrokerID, g_BrokerID);
	strcpy(loginFeild.UserID, g_UserID);
	strcpy(loginFeild.Password, g_Password);
	strcpy(loginFeild.UserProductInfo, g_ProductInfo);
	m_pUserApi->ReqUserLogin(&loginFeild, g_nOrLocalID++);
}

void MdUserHandler::OnPackageStart(int nTopicID, int nSequenceNo)
{
}

void MdUserHandler::OnPackageEnd(int nTopicID, int nSequenceNo)
{
}

void MdUserHandler::OnRspError(CUstpFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
}

void MdUserHandler::OnRspUserLogin(CUstpFtdcRspUserLoginField *pRspUserLogin, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	g_nOrLocalID = nRequestID + 1;
	if (pRspInfo->ErrorID)
	{
		printLog("行情线程登录失败");
		MessageBox(NULL, pRspInfo->ErrorMsg, "登录错误", MB_OK);
	}
	else
	{
		//Start subscribe contracts
		//Show The Main Dialog
		dlg.ShowWindow(SW_HIDE);
		mainDlg.ShowWindow(SW_SHOWNORMAL);
		mainDlg.SetFocus();
		printLog("行情线程登录成功");
	}
}

void MdUserHandler::OnRspUserLogout(CUstpFtdcRspUserLogoutField * pRspUserLogout, CUstpFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
	printLog("行情线程登出");
}

void MdUserHandler::OnRspSubscribeTopic(CUstpFtdcDisseminationField * pDissemination, CUstpFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
	printLog("订阅市场行情主题");
}

void MdUserHandler::OnRspQryTopic(CUstpFtdcDisseminationField * pDissemination, CUstpFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
}

void MdUserHandler::OnRtnDepthMarketData(CUstpFtdcDepthMarketDataField * pDepthMarketData)
{
	setListContract(pDepthMarketData);
	saveContractHistory(pDepthMarketData);
}

void MdUserHandler::OnRspSubMarketData(CUstpFtdcSpecificInstrumentField * pSpecificInstrument, CUstpFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
	g_nOrLocalID = nRequestID + 1;
	char s[50] = "订阅合约： ";
	if (pSpecificInstrument != 0)
		strcat(s, pSpecificInstrument->InstrumentID);
	printLog(s);
}

void MdUserHandler::OnRspUnSubMarketData(CUstpFtdcSpecificInstrumentField * pSpecificInstrument, CUstpFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
	g_nOrLocalID = nRequestID + 1;
	char s[50] = "取消订阅合约： ";
	strcat(s, pSpecificInstrument->InstrumentID);
	printLog(s);
}
