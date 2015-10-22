#include "stdafx.h"
#include "TraderHandler.h"


TraderHandler::TraderHandler(CUstpFtdcTraderApi * pUserApi) : m_pUserApi(pUserApi) {}

TraderHandler::~TraderHandler() {}

void TraderHandler::setApi(CUstpFtdcTraderApi * pUserApi)
{
	m_pUserApi = pUserApi;
}

void TraderHandler::OnFrontConnected()
{
}

void TraderHandler::OnFrontDisconnected(int nReason)
{
}

void TraderHandler::OnHeartBeatWarning(int nTimeLapse)
{
}

void TraderHandler::OnPackageStart(int nTopicID, int nSequenceNo)
{
}

void TraderHandler::OnPackageEnd(int nTopicID, int nSequenceNo)
{
}

void TraderHandler::OnRspError(CUstpFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
}

void TraderHandler::OnRspUserLogin(CUstpFtdcRspUserLoginField * pRspUserLogin, CUstpFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
}

void TraderHandler::OnRspUserLogout(CUstpFtdcRspUserLogoutField * pRspUserLogout, CUstpFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
}

void TraderHandler::OnRspUserPasswordUpdate(CUstpFtdcUserPasswordUpdateField * pUserPasswordUpdate, CUstpFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
}

void TraderHandler::OnRspOrderInsert(CUstpFtdcInputOrderField * pInputOrder, CUstpFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
}

void TraderHandler::OnRspOrderAction(CUstpFtdcOrderActionField * pOrderAction, CUstpFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
}

void TraderHandler::OnRspQuoteInsert(CUstpFtdcInputQuoteField * pInputQuote, CUstpFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
}

void TraderHandler::OnRspQuoteAction(CUstpFtdcQuoteActionField * pQuoteAction, CUstpFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
}

void TraderHandler::OnRspForQuote(CUstpFtdcReqForQuoteField * pReqForQuote, CUstpFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
}

void TraderHandler::OnRtnFlowMessageCancel(CUstpFtdcFlowMessageCancelField * pFlowMessageCancel)
{
}

void TraderHandler::OnRtnTrade(CUstpFtdcTradeField * pTrade)
{
}

void TraderHandler::OnRtnOrder(CUstpFtdcOrderField * pOrder)
{
}

void TraderHandler::OnErrRtnOrderInsert(CUstpFtdcInputOrderField * pInputOrder, CUstpFtdcRspInfoField * pRspInfo)
{
}

void TraderHandler::OnErrRtnOrderAction(CUstpFtdcOrderActionField * pOrderAction, CUstpFtdcRspInfoField * pRspInfo)
{
}

void TraderHandler::OnRtnInstrumentStatus(CUstpFtdcInstrumentStatusField * pInstrumentStatus)
{
}

void TraderHandler::OnRtnInvestorAccountDeposit(CUstpFtdcInvestorAccountDepositResField * pInvestorAccountDepositRes)
{
}

void TraderHandler::OnRtnQuote(CUstpFtdcRtnQuoteField * pRtnQuote)
{
}

void TraderHandler::OnErrRtnQuoteInsert(CUstpFtdcInputQuoteField * pInputQuote, CUstpFtdcRspInfoField * pRspInfo)
{
}

void TraderHandler::OnRtnForQuote(CUstpFtdcReqForQuoteField * pReqForQuote)
{
}

void TraderHandler::OnRspQryOrder(CUstpFtdcOrderField * pOrder, CUstpFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
}

void TraderHandler::OnRspQryTrade(CUstpFtdcTradeField * pTrade, CUstpFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
}

void TraderHandler::OnRspQryUserInvestor(CUstpFtdcRspUserInvestorField * pRspUserInvestor, CUstpFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
}

void TraderHandler::OnRspQryTradingCode(CUstpFtdcRspTradingCodeField * pRspTradingCode, CUstpFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
}

void TraderHandler::OnRspQryInvestorAccount(CUstpFtdcRspInvestorAccountField * pRspInvestorAccount, CUstpFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
}

void TraderHandler::OnRspQryInstrument(CUstpFtdcRspInstrumentField * pRspInstrument, CUstpFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
}

void TraderHandler::OnRspQryExchange(CUstpFtdcRspExchangeField * pRspExchange, CUstpFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
}

void TraderHandler::OnRspQryInvestorPosition(CUstpFtdcRspInvestorPositionField * pRspInvestorPosition, CUstpFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
}

void TraderHandler::OnRspSubscribeTopic(CUstpFtdcDisseminationField * pDissemination, CUstpFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
}

void TraderHandler::OnRspQryComplianceParam(CUstpFtdcRspComplianceParamField * pRspComplianceParam, CUstpFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
}

void TraderHandler::OnRspQryTopic(CUstpFtdcDisseminationField * pDissemination, CUstpFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
}

void TraderHandler::OnRspQryInvestorFee(CUstpFtdcInvestorFeeField * pInvestorFee, CUstpFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
}

void TraderHandler::OnRspQryInvestorMargin(CUstpFtdcInvestorMarginField * pInvestorMargin, CUstpFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
}