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
	// TODO: �ڴ˴����� return ���
	return data[n];
}

MINUTE_MARKET_DATA_TYPE & minuteMarketData::latestMinute()
{
	// TODO: �ڴ˴����� return ���
	return data[lastIndex];
}

MINUTE_MARKET_DATA_TYPE & minuteMarketData::previousMinute()
{
	// TODO: �ڴ˴����� return ���
	return data[lastIndex - 1];
}
