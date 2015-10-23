#pragma once

//the show the price&volume information of every minute
struct MINUTE_MARKET_DATA_TYPE
{
	//最高价/最低价
	double highestPrice, lowestPrice;
	//持仓量
	int position;
	//分钟最初/最后成交价
	double firstPrice, lastPrice;
	//当日至该时刻均价
	double avgPrice;
	int firstVolume, lastVolume;
};

class minuteMarketData
{
public:
	//所有合约中的id
	int m_InstrumentID;
	minuteMarketData();
	~minuteMarketData();
	//取数组
	MINUTE_MARKET_DATA_TYPE& operator[](int n);
	//取最新一分钟的状态
	MINUTE_MARKET_DATA_TYPE& latestMinute();
	//取前一分钟状态
	MINUTE_MARKET_DATA_TYPE& previousMinute();
private:
	//存放数据
	MINUTE_MARKET_DATA_TYPE data[271];
public:
	//一天的均价
	double avgPrice;
	//当日最大振幅
	double maxChg;
	//当日最大持仓
	int maxPosition;
	//当日最小持仓
	int minPosition;
	//最后更新状态的所在分钟的id
	int lastIndex;
	//当日数据是否已第一次赋值
	bool isInit;
	//当日一分钟最大成交量
	int maxVolume;
};

