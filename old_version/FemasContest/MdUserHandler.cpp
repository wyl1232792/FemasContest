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
	MessageBox(NULL, "�����ӳ��쳣", "�����쳣", MB_OK);
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
		printLog("�����̵߳�¼ʧ��");
		MessageBox(NULL, pRspInfo->ErrorMsg, "��¼����", MB_OK);
	}
	else
	{
		//Start subscribe contracts
		//Show The Main Dialog
		dlg.ShowWindow(SW_HIDE);
		mainDlg.ShowWindow(SW_SHOWNORMAL);
		mainDlg.SetFocus();
		printLog("�����̵߳�¼�ɹ�");
	}
}

void MdUserHandler::OnRspUserLogout(CUstpFtdcRspUserLogoutField * pRspUserLogout, CUstpFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
	printLog("�����̵߳ǳ�");
}

void MdUserHandler::OnRspSubscribeTopic(CUstpFtdcDisseminationField * pDissemination, CUstpFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
	printLog("�����г���������");
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
	char s[50] = "���ĺ�Լ�� ";
	if (pSpecificInstrument != 0)
		strcat(s, pSpecificInstrument->InstrumentID);
	printLog(s);
}

void MdUserHandler::OnRspUnSubMarketData(CUstpFtdcSpecificInstrumentField * pSpecificInstrument, CUstpFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
	g_nOrLocalID = nRequestID + 1;
	char s[50] = "ȡ�����ĺ�Լ�� ";
	strcat(s, pSpecificInstrument->InstrumentID);
	printLog(s);
}
