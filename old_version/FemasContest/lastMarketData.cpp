#include "stdafx.h"
#include "lastMarketData.h"


lastMarketData::lastMarketData()
{
	pBegin = 0;
	pEnd = 0;
	quotedIndex = 0;
}

lastMarketData::~lastMarketData()
{
}

CUstpFtdcDepthMarketDataField & lastMarketData::operator[](int n)
{
	return queue[(pBegin + n) % MAX_COUNT];
}

void lastMarketData::push(CUstpFtdcDepthMarketDataField * s)
{
	//automaticly pop the oldest data if the queue is full
	if (count == MAX_COUNT)
		pop();
	count++;
	queue[pEnd++] = *s;
	if (pEnd >= MAX_COUNT)
		pEnd = 0;
}

CUstpFtdcDepthMarketDataField lastMarketData::pop()
{
	if (count == 0)
		return CUstpFtdcDepthMarketDataField();
	count--;
	if (pBegin == MAX_COUNT - 1) {
		pBegin = 0;
		return queue[MAX_COUNT - 1];
	}
	return queue[pBegin++];
}

CUstpFtdcDepthMarketDataField & lastMarketData::last()
{
	// TODO: 在此处插入 return 语句
	return queue[pEnd - 1];
}

void lastMarketData::pushToMinuteMarketData(minuteMarketData * mmd)
{
	for (; quotedIndex != pEnd; quotedIndex = (quotedIndex < MAX_COUNT - 1) ? (quotedIndex + 1) : 0 )
	{
		//translate time to minutetype
		CUstpFtdcDepthMarketDataField &quotedStatus = queue[quotedIndex];
		int h, m, s;
		int timeIndex;
		sscanf(quotedStatus.UpdateTime, "%d:%d:%d", &h, &m, &s);
		if (9 <= h && h <= 11)
			timeIndex = (h - 9) * 60 + m - 15;
		else
			timeIndex = (h - 13) * 60 + m + 135;
		//travel to current minute
		while (timeIndex > mmd->lastIndex)
		{
			mmd->avgPrice = (mmd->avgPrice * mmd->lastIndex + mmd->latestMinute().lastPrice) / (mmd->lastIndex + 1);
			mmd->lastIndex++;
			MINUTE_MARKET_DATA_TYPE &now = mmd->latestMinute();
			MINUTE_MARKET_DATA_TYPE &pre = mmd->previousMinute();
			now.firstPrice = pre.lastPrice;
			now.firstVolume = pre.lastVolume;
			now.lastPrice = pre.lastPrice;
			now.lastVolume = pre.lastVolume;
			now.highestPrice = now.lastPrice;
			now.lowestPrice = now.lastPrice;
			now.position = pre.position;
			now.avgPrice = mmd->avgPrice;
		}
		//set instrument information
		MINUTE_MARKET_DATA_TYPE &current = mmd->latestMinute();
		current.lastPrice = quotedStatus.LastPrice;
		current.lastVolume = quotedStatus.Volume;
		current.highestPrice = max(quotedStatus.LastPrice, current.highestPrice);
		current.lowestPrice = min(quotedStatus.LastPrice, current.lowestPrice);
		current.position = quotedStatus.OpenInterest;
		mmd->maxChg = max(mmd->maxChg, abs(quotedStatus.LastPrice - quotedStatus.PreSettlementPrice));
		mmd->maxPosition = max(mmd->maxPosition, quotedStatus.OpenInterest);
		mmd->minPosition = min(mmd->minPosition, quotedStatus.OpenInterest);
		mmd->maxVolume = max(mmd->maxVolume, current.lastVolume - current.firstVolume);
	}
}
