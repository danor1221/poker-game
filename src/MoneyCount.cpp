#include "MoneyCount.hpp"


MoneyCount::MoneyCount()
{
	amountofmoney = 100; // can edit buy in later
}

MoneyCount::~MoneyCount()
{}


void MoneyCount::removeSmallBlind()
{
	amountofmoney -= 0.5;
}

void MoneyCount::removeBigBlind()
{
	amountofmoney -= 1;
}


void MoneyCount::removeAmount(int amount)
{
	amountofmoney -= amount;
}