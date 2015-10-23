#pragma once
class TradeExcecutor
{
public:
	TradeExcecutor(int, int);
	~TradeExcecutor();
	void run();
	void caculateOptions();
	void trade();
	void setStatus();
	int getStatus(int);
private:
	int instrumentId;
	int instruentOrderedId;
	int status;
	lastMarketData &m_LastMarketData;
	minuteMarketData &m_todayMinuteMarketData;
	CUstpFtdcRspInvestorPositionField m_LongPosition, m_ShortPosition;
};

