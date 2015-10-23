#include "stdafx.h"
#include "TraderHandler.h"

UstpTraderHandler::UstpTraderHandler(CUstpFtdcTraderApi * pUserApi) : m_pUserApi(pUserApi){}

UstpTraderHandler::~UstpTraderHandler() {}

void UstpTraderHandler::setApi(CUstpFtdcTraderApi * pUserApi)
{
	m_pUserApi = pUserApi;
}

void UstpTraderHandler::OnFrontConnected()
{
}

void UstpTraderHandler::OnFrontDisconnected(int nReason)
{
}

void UstpTraderHandler::OnHeartBeatWarning(int nTimeLapse)
{
}

void UstpTraderHandler::OnPackageStart(int nTopicID, int nSequenceNo)
{
}

void UstpTraderHandler::OnPackageEnd(int nTopicID, int nSequenceNo)
{
}

void UstpTraderHandler::OnRspError(CUstpFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
}

void UstpTraderHandler::OnRspUserLogin(CUstpFtdcRspUserLoginField * pRspUserLogin, CUstpFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
	g_nOrLocalID = nRequestID + 1;
	if (pRspInfo->ErrorID)
	{
		printLog("交易系统登录失败");
		MessageBox(NULL, pRspInfo->ErrorMsg, "登录错误", MB_OK);
	}
	else
	{
		g_OrderLocalId = atoi(pRspUserLogin->MaxOrderLocalID) + 1;
		printLog((LPTSTR)(LPCTSTR)intToStr(g_OrderLocalId));
		CUstpFtdcQryInstrumentField tmp;
		strcpy(tmp.ExchangeID, g_ExchangeID);
		tmp.ProductID[0] = '\0';
		tmp.InstrumentID[0] = '\0';
		m_pUserApi->ReqQryInstrument(&tmp, g_nOrLocalID++);
		refreshInvestorAccountInfo();
		refreshOrderInfo();
		refreshPositionInfo();
		refreshTradeInfo();
		mainDlg.SetTimer(2, 5000, NULL);
		printLog("交易系统登录成功");
	}
}

void UstpTraderHandler::OnRspUserLogout(CUstpFtdcRspUserLogoutField * pRspUserLogout, CUstpFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
}

void UstpTraderHandler::OnRspUserPasswordUpdate(CUstpFtdcUserPasswordUpdateField * pUserPasswordUpdate, CUstpFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
}

void UstpTraderHandler::OnRspOrderInsert(CUstpFtdcInputOrderField * pInputOrder, CUstpFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
	g_nOrLocalID = nRequestID + 1;
	if (pRspInfo->ErrorID) {
		printLog("报单录入有误");
		printLog(pRspInfo->ErrorMsg);
	}
}

void UstpTraderHandler::OnRspOrderAction(CUstpFtdcOrderActionField * pOrderAction, CUstpFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
	g_nOrLocalID = nRequestID + 1;
	if (pRspInfo->ErrorID) {
		printLog("撤单有误");
		printLog(pRspInfo->ErrorMsg);
	}
}

void UstpTraderHandler::OnRspQuoteInsert(CUstpFtdcInputQuoteField * pInputQuote, CUstpFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
}

void UstpTraderHandler::OnRspQuoteAction(CUstpFtdcQuoteActionField * pQuoteAction, CUstpFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
}

void UstpTraderHandler::OnRspForQuote(CUstpFtdcReqForQuoteField * pReqForQuote, CUstpFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
}

void UstpTraderHandler::OnRtnFlowMessageCancel(CUstpFtdcFlowMessageCancelField * pFlowMessageCancel)
{
}

void UstpTraderHandler::OnRtnTrade(CUstpFtdcTradeField * pTrade)
{
}

void UstpTraderHandler::OnRtnOrder(CUstpFtdcOrderField * pOrder)
{
}

void UstpTraderHandler::OnErrRtnOrderInsert(CUstpFtdcInputOrderField * pInputOrder, CUstpFtdcRspInfoField * pRspInfo)
{
}

void UstpTraderHandler::OnErrRtnOrderAction(CUstpFtdcOrderActionField * pOrderAction, CUstpFtdcRspInfoField * pRspInfo)
{
}

void UstpTraderHandler::OnRtnInstrumentStatus(CUstpFtdcInstrumentStatusField * pInstrumentStatus)
{
}

void UstpTraderHandler::OnRtnInvestorAccountDeposit(CUstpFtdcInvestorAccountDepositResField * pInvestorAccountDepositRes)
{
}

void UstpTraderHandler::OnRtnQuote(CUstpFtdcRtnQuoteField * pRtnQuote)
{
}

void UstpTraderHandler::OnErrRtnQuoteInsert(CUstpFtdcInputQuoteField * pInputQuote, CUstpFtdcRspInfoField * pRspInfo)
{
}

void UstpTraderHandler::OnRtnForQuote(CUstpFtdcReqForQuoteField * pReqForQuote)
{
}

void UstpTraderHandler::OnRspQryOrder(CUstpFtdcOrderField * pOrder, CUstpFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
	g_nOrLocalID = nRequestID + 1;
	if (pRspInfo->ErrorID) {
		printLog("报单查询有误");
		printLog(pRspInfo->ErrorMsg);
	}
	else {
		if (pOrder == 0)
			return;
		g_Orders[g_OrderCount++] = *pOrder;
		addOrderRecord(pOrder);
	}
}

void UstpTraderHandler::OnRspQryTrade(CUstpFtdcTradeField * pTrade, CUstpFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
	g_nOrLocalID = nRequestID + 1;
	if (pRspInfo->ErrorID) {
		printLog("成交查询有误");
		printLog(pRspInfo->ErrorMsg);
	}
	else {
		if (pTrade == 0)
			return;
		g_Trades[g_TradeCount++] = *pTrade;
		addTradeRecord(pTrade);
	}
}

void UstpTraderHandler::OnRspQryUserInvestor(CUstpFtdcRspUserInvestorField * pRspUserInvestor, CUstpFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
}

void UstpTraderHandler::OnRspQryTradingCode(CUstpFtdcRspTradingCodeField * pRspTradingCode, CUstpFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
}

void UstpTraderHandler::OnRspQryInvestorAccount(CUstpFtdcRspInvestorAccountField * pRspInvestorAccount, CUstpFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
	printLog("查询资金账户");
	g_nOrLocalID = nRequestID + 1;
	//
	if (pRspInfo->ErrorID != 0)
		return;
	setAccountInfo(pRspInvestorAccount);
}

void UstpTraderHandler::OnRspQryInstrument(CUstpFtdcRspInstrumentField * pRspInstrument, CUstpFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
	g_nOrLocalID = nRequestID + 1;
	addInstrument(*pRspInstrument);
}

void UstpTraderHandler::OnRspQryExchange(CUstpFtdcRspExchangeField * pRspExchange, CUstpFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
}

void UstpTraderHandler::OnRspQryInvestorPosition(CUstpFtdcRspInvestorPositionField * pRspInvestorPosition, CUstpFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
	g_nOrLocalID = nRequestID + 1;
	if (pRspInfo->ErrorID) {
		printLog("持仓查询有误");
		printLog(pRspInfo->ErrorMsg);
	}
	else {
		if (pRspInvestorPosition == 0)
			return;
		g_Positions[g_PositionCount++] = *pRspInvestorPosition;
		addPositionRecord(pRspInvestorPosition);
	}
}

void UstpTraderHandler::OnRspSubscribeTopic(CUstpFtdcDisseminationField * pDissemination, CUstpFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
}

void UstpTraderHandler::OnRspQryComplianceParam(CUstpFtdcRspComplianceParamField * pRspComplianceParam, CUstpFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
}

void UstpTraderHandler::OnRspQryTopic(CUstpFtdcDisseminationField * pDissemination, CUstpFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
}

void UstpTraderHandler::OnRspQryInvestorFee(CUstpFtdcInvestorFeeField * pInvestorFee, CUstpFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
}

void UstpTraderHandler::OnRspQryInvestorMargin(CUstpFtdcInvestorMarginField * pInvestorMargin, CUstpFtdcRspInfoField * pRspInfo, int nRequestID, bool bIsLast)
{
}


