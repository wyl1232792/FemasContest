#pragma once
class NetworkStatus
{
public:
	NetworkStatus();
	~NetworkStatus();
	int ConnectionStatus = 0;
	int OrderLocalId;
	TUstpFtdcDateType TradingDay;
	CUstpFtdcRspInstrumentField InstrumentsAvailable[1000];
	int InstrumentAvailableCount = 0;
};

