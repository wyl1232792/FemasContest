#pragma once
class Settings
{
public:
	Settings();
	~Settings();
	TUstpFtdcUserIDType g_UserID;
	TUstpFtdcBrokerIDType g_BrokerID;
	TUstpFtdcExchangeIDType g_ExchangeID;
	TUstpFtdcPasswordType g_Password;
	TUstpFtdcProductInfoType g_ProductInfo;
	TUstpFtdcInvestorIDType g_InvestorID;
	char mdFrontAddress[50];
	char tdFrontAddress[50];
};

