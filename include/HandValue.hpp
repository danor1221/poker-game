#pragma once

#include <iostream>
#include <vector>
#include <iterator> // for std::ostream_iterator
#include <algorithm> // for std::ranges::copy depending on lib support
#include <bits/stdc++.h>

//#include "Game.hpp"
#include "Card.hpp"



class HandValue
{
public:
	HandValue(std::vector<std::vector<Card>> PlayersCards);
	~HandValue();

	// gets by reference
	void getPlayerPointsAndOther(std::vector<int> &playerPoints, std::map<int, int> &playerToPoint, std::map<int, int> &typeCount);


	int getHandValue();




	bool checkStraightFlush();
	bool checkQuads();
	bool checkFullHouse();
	bool checkFlush();
	bool checkStraight();
	bool checkTrips();
	bool checkTwoPair();
	bool checkPair();

	template <typename T>
	static void findDuplicates(std::vector<T> &vecOfElements, std::map<T, int> &countMap);


	static void testPrint()
	{
		std::cout << "Testing this" << std::endl;
	}

private:
	std::vector<int> thisPlayersCardsAValue;
	std::vector<int> thisPlayersCardsSuit;

	std::vector<std::vector<Card>> PlayersCards;
};

