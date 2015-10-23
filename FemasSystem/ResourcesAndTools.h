#pragma once
class ResourcesAndTools
{
public:
	ResourcesAndTools();
	~ResourcesAndTools();
	CString doubleToStr(double n);
	CString intToStr(int n);
	CString intToUnitedStr(int n);
	char *strNetworkStatus[3] = { "未连接", "已连接服务器", "已登录" };
	char *strDirection[2] = { "买入", "卖出" };
	char *strOrderType[5] = { "", "任意价", "限价" , "最优价" , "五档价" };
	char *strOffsetType[5] = { "开仓","平仓","强平","平今","平昨" };
	char *strOrderStatus[7] = { "全部成交","部分成交","部分成交不在队列","未成交","未成交不在队列","已撤单","无应答" };
	char *units[4] = { "万", "亿", "万亿", "兆" };
private:
};

