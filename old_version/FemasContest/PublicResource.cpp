#include "stdafx.h"

CUstpFtdcTraderApi *traderUserApi;
CUstpFtdcMduserApi *mdUserApi;
MdUserHandler mdSpi(mdUserApi);
UstpTraderHandler tdSpi(traderUserApi);
//a
bool g_Connection = false;
int g_OrderLocalId;
TUstpFtdcDateType g_TradingDay;
//b
//a
TUstpFtdcUserIDType g_UserID;
TUstpFtdcBrokerIDType g_BrokerID;
TUstpFtdcExchangeIDType g_ExchangeID = "CFFEX";
TUstpFtdcPasswordType g_Password;
TUstpFtdcProductInfoType g_ProductInfo = "femas_contest_v0.0";
TUstpFtdcInvestorIDType g_InvestorID = "01937576";
char *mdFrontAddress = "tcp://117.185.125.4:17199";
char *tdFrontAddress = "tcp://117.185.125.4:17198";
//b
//a
char *g_Direction[] = { "买入", "卖出" };
char *g_OrderType[] = { "", "任意价", "限价" , "最优价" , "五档价" };
char *g_OffsetType[] = { "开仓","平仓","强平","平今","平昨" };
char *g_OrderStatus[] = { "全部成交","部分成交","部分成交不在队列","未成交","未成交不在队列","已撤单","无应答" };
char *units[] = {"万", "亿", "万亿", "兆"};
//b
CUstpFtdcDepthMarketDataField g_InstrumentStatus[1000];
bool isOrdered[1000];
CUstpFtdcRspInstrumentField g_InstrumentsInfo[1000];//
int g_InstrumentCount = 0;
int g_OrderedInstrumentCount;
minuteMarketData *pMinuteMarketData[60];
lastMarketData *pLastMarketData[60];
CUstpFtdcOrderField g_Orders[10000];
CUstpFtdcTradeField g_Trades[10000];
CUstpFtdcRspInvestorPositionField g_Positions[1000];
int g_OrderCount = 0;
int g_TradeCount = 0;
int g_PositionCount = 0;

CLoginDialog dlg;
CFemasContestDlg mainDlg;
ConsoleDialog consoleDlg;
ContractsDialog contractsDlg;
ChartDlg chartDlg;

InsertLimitPage pageInsertLimitOrder;
InsertMarketPage pageInsertMarketOrder;
PageOrderInfo pageOrderInfo;
PagePositionInfo pagePositionInfo;
PageTradeInfo pageTradeInfo;
CDialog* pageTabOrder[2];
CDialog* pageTabInfo[3];
int pageTabOrderIndex;
int pageTabInfoIndex;

struct ptrCmp
{
	bool operator()(const char * s1, const char * s2) const
	{
		return strcmp(s1, s2) < 0;
	}
};

std::map<char *, int, ptrCmp> instrumentIndex;

void printLog(char *s)
{
	CString app;
	consoleDlg.editConsole.GetWindowTextA(app);
	app.AppendFormat(">>>%s\r\n", s);
	consoleDlg.editConsole.SetWindowTextA(app);
}

void addInstrument(CUstpFtdcRspInstrumentField newInstrument)
{
	g_InstrumentsInfo[g_InstrumentCount] = newInstrument;
	strcpy(g_InstrumentStatus[g_InstrumentCount++].InstrumentID, newInstrument.InstrumentID);
}

CString doubleToStr(double n)
{
	CString s;
	s.Format("%.1lf", n);
	return s;
}

CString intToStr(int n)
{
	CString s;
	s.Format("%d", n);
	return s;
}

CString intToUnitedStr(int n)
{
	CString s;
	int i = 0;
	while ((n /= 10000) > 100000)
		i++;
	s.Format("%d%s", n, units[i]);
	return s;
}

//获取accountField后设置填入账户信息域
void setAccountInfo(CUstpFtdcRspInvestorAccountField * s)
{
	mainDlg.SetDlgItemTextA(IDC_STATIC_ACC1, (LPTSTR)(s->InvestorID));
	mainDlg.SetDlgItemTextA(IDC_STATIC_ACC2, (LPTSTR)(s->AccountID));
	mainDlg.SetDlgItemTextA(IDC_STATIC_ACC3, doubleToStr(s->PreBalance));
	mainDlg.SetDlgItemTextA(IDC_STATIC_ACC4, doubleToStr(s->Deposit));
	mainDlg.SetDlgItemTextA(IDC_STATIC_ACC5, doubleToStr(s->Withdraw));
	mainDlg.SetDlgItemTextA(IDC_STATIC_ACC6, doubleToStr(s->CloseProfit));
	mainDlg.SetDlgItemTextA(IDC_STATIC_ACC7, doubleToStr(s->PositionProfit));
	mainDlg.SetDlgItemTextA(IDC_STATIC_ACC8, doubleToStr(s->Fee));
	mainDlg.SetDlgItemTextA(IDC_STATIC_ACC9, doubleToStr(s->Margin));
	mainDlg.SetDlgItemTextA(IDC_STATIC_ACC10, doubleToStr(s->Available));
	mainDlg.SetDlgItemTextA(IDC_STATIC_ACC11, doubleToStr(s->LongMargin));
	mainDlg.SetDlgItemTextA(IDC_STATIC_ACC12, doubleToStr(s->ShortMargin));
	mainDlg.SetDlgItemTextA(IDC_STATIC_ACC13, doubleToStr(s->DynamicRights));
	mainDlg.SetDlgItemTextA(IDC_STATIC_ACC14, doubleToStr(s->FrozenMargin));
	mainDlg.SetDlgItemTextA(IDC_STATIC_ACC15, doubleToStr(s->FrozenFee));
	mainDlg.SetDlgItemTextA(IDC_STATIC_ACC16, doubleToStr(s->FrozenPremium));
	mainDlg.SetDlgItemTextA(IDC_STATIC_ACC17, doubleToStr(s->Premium));
	mainDlg.SetDlgItemTextA(IDC_STATIC_ACC18, doubleToStr(s->Risk));
}

//向服务器发送查询账户资金指令
void refreshInvestorAccountInfo()
{
	CUstpFtdcQryInvestorAccountField iaf;
	memset(&iaf, 0, sizeof(iaf));
	strcpy(iaf.BrokerID, g_BrokerID);
	strcpy(iaf.InvestorID, g_InvestorID);
	strcpy(iaf.UserID, g_UserID);
	traderUserApi->ReqQryInvestorAccount(&iaf, g_nOrLocalID++);
}

void refreshOrderInfo()
{
	g_OrderCount = 0;
	pageOrderInfo.listOrder.DeleteAllItems();
	CUstpFtdcQryOrderField qof;
	memset(&qof, 0, sizeof(qof));
	strcpy(qof.BrokerID, g_BrokerID);
	strcpy(qof.ExchangeID, g_ExchangeID);
	strcpy(qof.InvestorID, g_InvestorID);
	strcpy(qof.UserID, g_UserID);
	traderUserApi->ReqQryOrder(&qof, g_nOrLocalID++);
}

void refreshTradeInfo()
{
	g_TradeCount = 0;
	pageTradeInfo.listTrade.DeleteAllItems();
	CUstpFtdcQryTradeField qtf;
	memset(&qtf, 0, sizeof(qtf));
	strcpy(qtf.BrokerID, g_BrokerID);
	strcpy(qtf.ExchangeID, g_ExchangeID);
	strcpy(qtf.InvestorID, g_InvestorID);
	strcpy(qtf.UserID, g_UserID);
	traderUserApi->ReqQryTrade(&qtf, g_nOrLocalID++);
}

void refreshPositionInfo()
{
	g_PositionCount = 0;
	pagePositionInfo.listPosition.DeleteAllItems();
	CUstpFtdcQryInvestorPositionField qipf;
	memset(&qipf, 0, sizeof(qipf));
	strcpy(qipf.BrokerID, g_BrokerID);
	strcpy(qipf.ExchangeID, g_ExchangeID);
	strcpy(qipf.InvestorID, g_InvestorID);
	strcpy(qipf.UserID, g_UserID);
	traderUserApi->ReqQryInvestorPosition(&qipf, g_nOrLocalID++);
}

void addPositionRecord(CUstpFtdcRspInvestorPositionField *s)
{
	pagePositionInfo.listPosition.InsertItem(0, s->InstrumentID);
	pagePositionInfo.listPosition.SetItemText(0, 1, g_Direction[s->Direction - '0']);
	pagePositionInfo.listPosition.SetItemText(0, 2, doubleToStr(s->UsedMargin));
	pagePositionInfo.listPosition.SetItemText(0, 3, intToStr(s->Position));
	pagePositionInfo.listPosition.SetItemText(0, 4, doubleToStr(s->PositionCost));
	pagePositionInfo.listPosition.SetItemText(0, 5, intToStr(s->YdPosition));
	pagePositionInfo.listPosition.SetItemText(0, 6, doubleToStr(s->YdPositionCost));
	pagePositionInfo.listPosition.SetItemText(0, 7, doubleToStr(s->FrozenMargin));
	pagePositionInfo.listPosition.SetItemText(0, 8, intToStr(s->FrozenPosition));
	pagePositionInfo.listPosition.SetItemText(0, 9, intToStr(s->FrozenClosing));
	pagePositionInfo.listPosition.SetItemText(0, 10, doubleToStr(s->FrozenPremium));
}

void addOrderRecord(CUstpFtdcOrderField *s)
{
	pageOrderInfo.listOrder.InsertItem(0, s->OrderSysID);
	pageOrderInfo.listOrder.SetItemText(0, 1, s->InstrumentID);
	pageOrderInfo.listOrder.SetItemText(0, 2, g_OrderType[s->OrderPriceType - '0']);
	pageOrderInfo.listOrder.SetItemText(0, 3, g_Direction[s->Direction - '0']);
	pageOrderInfo.listOrder.SetItemText(0, 4, g_OffsetType[s->OffsetFlag - '0']);
	pageOrderInfo.listOrder.SetItemText(0, 5, doubleToStr(s->LimitPrice));
	pageOrderInfo.listOrder.SetItemText(0, 6, intToStr(s->Volume));
	pageOrderInfo.listOrder.SetItemText(0, 7, s->InsertTime);
	pageOrderInfo.listOrder.SetItemText(0, 8, g_OrderStatus[s->OrderStatus - '0']);
	pageOrderInfo.listOrder.SetItemText(0, 9, intToStr(s->VolumeTraded));
	pageOrderInfo.listOrder.SetItemText(0, 10, intToStr(s->VolumeRemain));
}

void addTradeRecord(CUstpFtdcTradeField *s)
{
	pageTradeInfo.listTrade.InsertItem(0, s->TradeID);
	pageTradeInfo.listTrade.SetItemText(0, 1, s->InstrumentID);
	pageTradeInfo.listTrade.SetItemText(0, 2, g_Direction[s->Direction - '0']);
	pageTradeInfo.listTrade.SetItemText(0, 3, g_OffsetType[s->OffsetFlag - '0']);
	pageTradeInfo.listTrade.SetItemText(0, 4, doubleToStr(s->TradePrice));
	pageTradeInfo.listTrade.SetItemText(0, 5, intToStr(s->TradeVolume));
	pageTradeInfo.listTrade.SetItemText(0, 6, s->TradeTime);
}



void reSubcribeContracts()
{
	char tmp[20];
	char *s[] = {tmp};
	for (int i = 0; i < g_InstrumentCount; i++)
		if (isOrdered[i]) {
			strcpy(tmp, g_InstrumentStatus[i].InstrumentID);
			instrumentIndex.insert(std::map<char *, int, ptrCmp>::value_type(g_InstrumentStatus[i].InstrumentID, g_OrderedInstrumentCount));
			mainDlg.listContracts.InsertItem(g_OrderedInstrumentCount, (LPTSTR)g_InstrumentStatus[i].InstrumentID);
			pMinuteMarketData[g_OrderedInstrumentCount] = new minuteMarketData();
			pMinuteMarketData[g_OrderedInstrumentCount]->m_InstrumentID = i;
			pLastMarketData[g_OrderedInstrumentCount] = new lastMarketData();
			pLastMarketData[g_OrderedInstrumentCount]->m_InstrumentID = i;
			mdUserApi->SubMarketData(s, 1);
			g_OrderedInstrumentCount++;
		}
	mainDlg.SetTimer(1, 500, NULL);
}

void clearSubcribedContracts()
{
	char tmp[20];
	char *s[] = { tmp };
	for (int i = 0; i < mainDlg.listContracts.GetItemCount(); i++) {
			strcpy(tmp, mainDlg.listContracts.GetItemText(i, 0));
			mdUserApi->UnSubMarketData(s, 1);
	}
	mainDlg.listContracts.DeleteAllItems();
	g_OrderedInstrumentCount = 0;
	instrumentIndex.clear();
}

void setListContract(CUstpFtdcDepthMarketDataField * pDepthMarketData)
{
	int i = instrumentIndex[pDepthMarketData->InstrumentID];
	g_InstrumentStatus[pLastMarketData[i]->m_InstrumentID] = *pDepthMarketData;
	mainDlg.listContracts.SetItemText(i, 1, doubleToStr(pDepthMarketData->LastPrice));
	mainDlg.listContracts.SetItemText(i, 2, doubleToStr(pDepthMarketData->BidPrice1));
	mainDlg.listContracts.SetItemText(i, 3, doubleToStr(pDepthMarketData->AskPrice1));
	mainDlg.listContracts.SetItemText(i, 4, intToStr(pDepthMarketData->BidVolume1));
	mainDlg.listContracts.SetItemText(i, 5, intToStr(pDepthMarketData->AskVolume1));
	mainDlg.listContracts.SetItemText(i, 6, doubleToStr(pDepthMarketData->OpenPrice));
	mainDlg.listContracts.SetItemText(i, 7, doubleToStr(pDepthMarketData->HighestPrice));
	mainDlg.listContracts.SetItemText(i, 8, doubleToStr(pDepthMarketData->LowestPrice));
	mainDlg.listContracts.SetItemText(i, 9, doubleToStr(pDepthMarketData->UpperLimitPrice));
	mainDlg.listContracts.SetItemText(i, 10, doubleToStr(pDepthMarketData->LowerLimitPrice));
	mainDlg.listContracts.SetItemText(i, 11, doubleToStr(pDepthMarketData->PreClosePrice));
	mainDlg.listContracts.SetItemText(i, 12, doubleToStr(pDepthMarketData->PreSettlementPrice));
	mainDlg.listContracts.SetItemText(i, 13, pDepthMarketData->UpdateTime);
}

void saveContractHistory(CUstpFtdcDepthMarketDataField * pDepthMarketData)
{
	int i = instrumentIndex[pDepthMarketData->InstrumentID];
	pLastMarketData[i]->push(pDepthMarketData);
}

//调用此函数只需要填核心要素
void insertLimitOrder(CUstpFtdcInputOrderField *pInputOrder, int type, int count)
{
	strcpy(pInputOrder->BrokerID, g_BrokerID);
	strcpy(pInputOrder->ExchangeID, g_ExchangeID);
	strcpy(pInputOrder->InvestorID, g_InvestorID);
	strcpy(pInputOrder->UserID, g_UserID);
	pInputOrder->OrderPriceType = USTP_FTDC_OPT_LimitPrice;
	if (type == 0) {
		pInputOrder->TimeCondition = USTP_FTDC_TC_GFD;
		pInputOrder->VolumeCondition = USTP_FTDC_VC_AV;
	}
	else if (type == 1)
	{
		pInputOrder->TimeCondition = USTP_FTDC_TC_IOC;
		pInputOrder->VolumeCondition = USTP_FTDC_VC_AV;
	}
	else if (type = 2)
	{
		pInputOrder->TimeCondition = USTP_FTDC_TC_IOC;
		pInputOrder->VolumeCondition = USTP_FTDC_VC_CV;
	}
	pInputOrder->ForceCloseReason = USTP_FTDC_FCR_NotForceClose;
	for (int i = 0; i < count; i++) {
		sprintf(pInputOrder->UserOrderLocalID, "%09d", g_OrderLocalId++);
		traderUserApi->ReqOrderInsert(pInputOrder, g_nOrLocalID++);
	}
}

void insertMarketOrder(CUstpFtdcInputOrderField *pInputOrder, int type)
{
	strcpy(pInputOrder->BrokerID, g_BrokerID);
	strcpy(pInputOrder->ExchangeID, g_ExchangeID);
	strcpy(pInputOrder->InvestorID, g_InvestorID);
	strcpy(pInputOrder->UserID, g_UserID);
	if (type == 0) {
		pInputOrder->OrderPriceType = USTP_FTDC_OPT_AnyPrice;
		pInputOrder->TimeCondition = USTP_FTDC_TC_IOC;
		pInputOrder->VolumeCondition = USTP_FTDC_VC_AV;
	}
	else if (type == 1)
	{
		pInputOrder->OrderPriceType = USTP_FTDC_OPT_FiveLevelPrice;
		pInputOrder->TimeCondition = USTP_FTDC_TC_IOC;
		pInputOrder->VolumeCondition = USTP_FTDC_VC_AV;
	}
	else if (type = 2)
	{
		pInputOrder->OrderPriceType = USTP_FTDC_OPT_BestPrice;
		pInputOrder->TimeCondition = USTP_FTDC_TC_IOC;
		pInputOrder->VolumeCondition = USTP_FTDC_VC_AV;
	}
	pInputOrder->ForceCloseReason = USTP_FTDC_FCR_NotForceClose;
	sprintf(pInputOrder->UserOrderLocalID, "%09d", g_OrderLocalId++);
	traderUserApi->ReqOrderInsert(pInputOrder, g_nOrLocalID++);
}

void reqOrderAction(TUstpFtdcOrderSysIDType s)
{
	CUstpFtdcOrderActionField g;
	memset(&g, 0, sizeof(g));
	strcpy(g.ExchangeID, g_ExchangeID);
	strcpy(g.BrokerID, g_BrokerID);
	strcpy(g.UserID, g_UserID);
	strcpy(g.InvestorID, g_InvestorID);

	printLog((LPTSTR)(LPCTSTR)intToStr(g_OrderLocalId));
	sprintf(g.UserOrderActionLocalID, "%09d", g_OrderLocalId++);
	g.ActionFlag = USTP_FTDC_AF_Delete;
	strcpy(g.OrderSysID, s);
	traderUserApi->ReqOrderAction(&g, g_nOrLocalID++);
}