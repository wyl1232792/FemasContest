#pragma once
class TradeStrategy
{
public:
	TradeStrategy(lastMarketData &lmd, minuteMarketData &mmd);
	~TradeStrategy();
	int getResult();
	virtual void run() = 0;
protected:
	lastMarketData &m_LastMarketData;
	minuteMarketData &m_todayMinuteMarketData;
	int result;
	int option[10];//留出的字段 可以分情况指定权重
private:
};

