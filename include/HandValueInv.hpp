#pragma once

#include <iostream>
#include <vector>
#include <iterator> // for std::ostream_iterator
#include <algorithm> // for std::ranges::copy depending on lib support
#include <utility>
#include <bits/stdc++.h>

//#include "Game.hpp"
#include "Card.hpp"



class HVI
{
public:
	// might be able to cut num as it isnt used anywhere atm
	HVI(std::map<int, int> playerToPoint, int point, int num, std::vector<std::vector<Card>> PlayersCards);
	~HVI();



	void setDrawingPlayerCards(std::vector<int> &drawPlayers);


	// Function will call the respective handvalue function and adds winner to the winningPlayer vector directly
	void InvestigateDraw();

	// gets winningPlayer
	std::vector<int> getWinningPlayer();



	void compareHighCard(std::vector<std::vector<int>> handCards);
	void compareKicker(std::vector<std::vector<int>> handCards);
	void comparePair();
	void compareTwoPair();
	void compareTrips();
	void compareStraight();
	void compareFlush();
	void compareFullHouse();
	void compareQuads();
	void compareStraightFlush();




	// functions that assimilate comparePair(), compareTrips(), and compareQuads()
	bool stageOne(int len);
	bool stageTwo(std::map<int, int> &playerToSetValues, int len);
	void stageThree(std::map<int, int> &playerToSetValues, int len);






	// Utility functions used by above functions
	template <typename T>
	void findDuplicates(std::vector<T> &vecOfElements, std::map<T, int> &countMap);

	void changeAce(std::map<int, int> &duplicates);

	int maxKeyInMap(std::map<int, int> &inpMap, bool &draw);

	std::vector<int> maxKeysInMap(std::map<int, int> &inpMap);

	void convertAce(std::vector<int> &inpVec);

	std::vector<std::vector<int>> vectorOfPlayersHandCards();

	bool checkIfSetExists(std::vector<int> &inpVec);

	bool checkIfSpecificSetExist(std::vector<int> &inpVec, int len);

	bool checkPairExistence(std::vector<int> inpVec, int value);

	void setTopAndBottomPair(std::map<int, int> &playerToTopPairValues, std::map<int, int> &playerToBottomPairValues);

	bool XOR(bool a, bool b);

	std::vector<int> getStraightCards(std::vector<int> thisPlayersCardsAValue);



private:
	std::map<int, int> playerToPoint;
	int point;
	std::vector<int> winningPlayer;
	int num;
	std::vector<std::vector<Card>> PlayersCards;


	std::vector<int> drawingPlayers;
	std::vector<std::vector<int>> drawPlayersCardsValue;
	std::vector<std::vector<int>> drawPlayersCardsAValue;
	std::vector<std::vector<int>> drawPlayersCardsSuit;
};