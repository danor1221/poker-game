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

	void removeAmount(double amount);

	void addAmount(double amount);


	double getAmount();

private:
	double amountofmoney;
};



// This class should probably have a variable that attributes it to specific players