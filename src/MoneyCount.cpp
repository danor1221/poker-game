#include "MoneyCount.hpp"


MoneyCount::MoneyCount()
{
	amountofmoney = 100.0; // can edit buy in later
}

MoneyCount::~MoneyCount()
{}


void MoneyCount::removeSmallBlind()
{
	amountofmoney -= 0.5;
}

void MoneyCount::removeBigBlind()
{
	amountofmoney -= 1.0;
}


void MoneyCount::removeAmount(double amount)
{
	amountofmoney -= amount;
}


void MoneyCount::addAmount(double amount)
{
	amountofmoney += amount;
}




double MoneyCount::getAmount()
{
	return amountofmoney;
}