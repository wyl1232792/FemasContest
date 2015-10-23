#include "stdafx.h"
#include "minuteMarketData.h"


minuteMarketData::minuteMarketData()
{
	avgPrice = 0.0;
	maxPosition = 0;
	minPosition = 0;
	isInit = false;
}


minuteMarketData::~minuteMarketData()
{
}

MINUTE_MARKET_DATA_TYPE & minuteMarketData::operator[](int n)
{
	// TODO: 在此处插入 return 语句
	return data[n];
}

MINUTE_MARKET_DATA_TYPE & minuteMarketData::latestMinute()
{
	// TODO: 在此处插入 return 语句
	return data[lastIndex];
}

MINUTE_MARKET_DATA_TYPE & minuteMarketData::previousMinute()
{
	// TODO: 在此处插入 return 语句
	return data[lastIndex - 1];
}
