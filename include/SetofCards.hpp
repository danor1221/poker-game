#pragma once

#include <iostream>
#include <vector>

//#include "Game.hpp"
#include "Card.hpp"


class SetOfCards
{
public:
	SetOfCards();
	~SetOfCards();

	void dealSetOfCards(std::vector<int> &cardVector);
	std::vector<Card> getsetofcards();

	void dealFlopCards(std::vector<int> &cardVector);
	void dealTurnCard(std::vector<int> &cardVector);
	void dealRiverCard(std::vector<int> &cardVector);

private:
	std::vector<Card> setofcards;
};

