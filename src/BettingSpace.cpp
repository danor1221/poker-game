#include "BettingSpace.hpp"


BettingSpace::BettingSpace()
{
	amountinbettingspace = 0.0;
}

BettingSpace::~BettingSpace()
{}


void BettingSpace::addAmount(double valuetoadd)
{
	amountinbettingspace += valuetoadd;
}

double BettingSpace::getAmount()
{
	return amountinbettingspace;
}

void BettingSpace::clearAmount()
{
	amountinbettingspace = 0.0;
}