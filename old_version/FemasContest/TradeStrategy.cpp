#include "stdafx.h"
#include "TradeStrategy.h"


TradeStrategy::TradeStrategy(lastMarketData & lmd, minuteMarketData & mmd)
	:m_LastMarketData(lmd), m_todayMinuteMarketData(mmd)
{
}

TradeStrategy::~TradeStrategy()
{
}

int TradeStrategy::getResult()
{
	return result;
}
