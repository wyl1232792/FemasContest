#pragma once
class TradeManager
{
public:
	TradeManager();
	~TradeManager();
	TradeExcecutor* createTradeExcecutor();
	bool enableTradeExcecutor(char*);
	bool enableTradeExcecutor(int id);
	bool disableTradeExcecutor(char*);
	bool disableTradeExcecutor(int id);
	bool deleteTradeExcecutor(char *);
	bool deleteTradeExcecutor(int id);

private:
	TradeExcecutor* m_tradeExcecutor[200];
	int tradeExcecutorCount;
};

