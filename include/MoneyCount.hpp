#pragma once

#include <iostream>
#include <vector>

//#include "Game.hpp"


class MoneyCount
{
public:
	MoneyCount();
	~MoneyCount();

	void removeSmallBlind();
	void removeBigBlind();

	void removeAmount(int amount);

private:
	int amountofmoney;
};