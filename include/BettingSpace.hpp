#pragma once

#include <iostream>
#include <vector>

//#include "Game.hpp"


class BettingSpace
{
public:
	BettingSpace();
	~BettingSpace();

	void addAmount(double valuetoadd);

	double getAmount();

	void clearAmount();

private:
	double amountinbettingspace;
};