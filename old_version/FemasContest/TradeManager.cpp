#include "stdafx.h"
#include "TradeManager.h"


TradeManager::TradeManager()
{
}


TradeManager::~TradeManager()
{
}


TradeExcecutor * TradeManager::createTradeExcecutor()
{
	return nullptr;
}

bool TradeManager::enableTradeExcecutor(char *)
{
	return false;
}

bool TradeManager::enableTradeExcecutor(int id)
{
	return false;
}

bool TradeManager::disableTradeExcecutor(char *)
{
	return false;
}

bool TradeManager::disableTradeExcecutor(int id)
{
	return false;
}

bool TradeManager::deleteTradeExcecutor(char *)
{
	return false;
}

bool TradeManager::deleteTradeExcecutor(int id)
{
	return false;
}
