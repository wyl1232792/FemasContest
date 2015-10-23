#pragma once
#include "USTPFtdcMduserApi.h"
#define MAX_COUNT 1000
class lastMarketData
{
public:
	//the index of all instruments
	int m_InstrumentID;
	//default contructor
	lastMarketData();

	~lastMarketData();

	CUstpFtdcDepthMarketDataField& operator[](int n);
	void push(CUstpFtdcDepthMarketDataField *s);
	CUstpFtdcDepthMarketDataField pop();
	//get the reference of latest data
	CUstpFtdcDepthMarketDataField& last();
	//convert unused data to the minuteMarketDataType
	void pushToMinuteMarketData(minuteMarketData *s);
	int count = 0;
private:
	int pBegin, pEnd;
	CUstpFtdcDepthMarketDataField queue[MAX_COUNT];
public:
//	bool isQuoted;
	int quotedIndex;
};

