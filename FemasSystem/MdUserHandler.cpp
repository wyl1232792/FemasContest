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
}

void MdUserHandler::OnFrontDisconnected(int nReason)
{
}

void MdUserHandler::OnHeartBeatWarning(int nTimeLapse)
{
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
}

void MdUserHandler::OnRspUserLogout(CUstpFtdcRspUserLogoutField * pRspUserLogout, CUstpFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
}

void MdUserHandler::OnRspSubscribeTopic(CUstpFtdcDisseminationField * pDissemination, CUstpFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
}

void MdUserHandler::OnRspQryTopic(CUstpFtdcDisseminationField * pDissemination, CUstpFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
}

void MdUserHandler::OnRtnDepthMarketData(CUstpFtdcDepthMarketDataField * pDepthMarketData)
{
}

void MdUserHandler::OnRspSubMarketData(CUstpFtdcSpecificInstrumentField * pSpecificInstrument, CUstpFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
}

void MdUserHandler::OnRspUnSubMarketData(CUstpFtdcSpecificInstrumentField * pSpecificInstrument, CUstpFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
}
