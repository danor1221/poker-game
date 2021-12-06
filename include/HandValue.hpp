#pragma once

#include <iostream>
#include <vector>
#include <iterator> // for std::ostream_iterator
#include <algorithm> // for std::ranges::copy depending on lib support
#include <bits/stdc++.h>

//#include "Game.hpp"



class HandValue
{
public:
	HandValue(std::vector<int> thisPlayersCardsAValue, std::vector<int> thisPlayersCardsSuit);
	~HandValue();

	int getHandValue();


	bool checkHit()
	{
		return hit;
	}



	void checkStraightFlush();
	void checkQuads();
	void checkFullHouse();
	void checkFlush();
	void checkStraight();
	void checkTrips();
	void checkTwoPair();
	void checkPair();

	template <typename T>
	void findDuplicates(std::vector<T> &vecOfElements, std::map<T, int> &countMap);




private:
	std::vector<int> thisPlayersCardsValue;
	std::vector<int> thisPlayersCardsAValue;
	std::vector<int> thisPlayersCardsSuit;

	bool hit = false;
};