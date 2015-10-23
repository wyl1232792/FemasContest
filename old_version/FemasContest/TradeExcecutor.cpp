#include "stdafx.h"
#include "TradeExcecutor.h"


TradeExcecutor::TradeExcecutor(int instrumentId, int instrumentOrderedId)
	:m_LastMarketData(*pLastMarketData[instrumentOrderedId]), m_todayMinuteMarketData(*pMinuteMarketData[instrumentOrderedId])
{
}


TradeExcecutor::~TradeExcecutor()
{
}

void TradeExcecutor::run()
{
	caculateOptions();
	trade();
}

void TradeExcecutor::caculateOptions()
{
}

void TradeExcecutor::trade()
{
}

void TradeExcecutor::setStatus()
{
}

int TradeExcecutor::getStatus(int s)
{
	return 0;
}
