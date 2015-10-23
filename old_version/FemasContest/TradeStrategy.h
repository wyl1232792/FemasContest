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
	int option[10];//�������ֶ� ���Է����ָ��Ȩ��
private:
};

