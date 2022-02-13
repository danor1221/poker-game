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

	SetOfCards(std::vector<std::vector<int>> desiredCards, int i);
	void dealSpecific();
	void dealSpecificFlop();
	void dealSpecificTurn();
	void dealSpecificRiver();

	void dealSetOfCards(std::vector<int> &cardVector);
	std::vector<Card> getsetofcards();

	void dealFlopCards(std::vector<int> &cardVector);
	void dealTurnCard(std::vector<int> &cardVector);
	void dealRiverCard(std::vector<int> &cardVector);

private:
	std::vector<Card> setofcards;
	std::vector<int> thisSet;
};

