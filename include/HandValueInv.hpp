#pragma once

#include <iostream>
#include <vector>
#include <iterator> // for std::ostream_iterator
#include <algorithm> // for std::ranges::copy depending on lib support
#include <bits/stdc++.h>

//#include "Game.hpp"
#include "Card.hpp"



namespace HVI
{
	// Function will call the respective handvalue function and adds winner to the winningPlayer vector directly (passed by reference)
	void InvestigateDraw(std::map<int, int> &playerToPoint, int point, std::vector<int> &winningPlayer, int num, std::vector<std::vector<Card>> &PlayersCards);


	// need to pass in the players cards as well
	void compareHighCard(std::map<int, int> &drawingPlayers, std::vector<int> &winningPlayer, std::vector<std::vector<int>> &drawPlayersCardsAValue, std::vector<std::vector<int>> &drawPlayersCardsSuit);
	void comparePair(std::map<int, int> &drawingPlayers, std::vector<int> &winningPlayer);
	void compareTwoPair(std::map<int, int> &drawingPlayers, std::vector<int> &winningPlayer);
	void compareTrips(std::map<int, int> &drawingPlayers, std::vector<int> &winningPlayer);
	void compareStraight(std::map<int, int> &drawingPlayers, std::vector<int> &winningPlayer);
	void compareFlush(std::map<int, int> &drawingPlayers, std::vector<int> &winningPlayer);
	void compareFullHouse(std::map<int, int> &drawingPlayers, std::vector<int> &winningPlayer);
	void compareQuads(std::map<int, int> &drawingPlayers, std::vector<int> &winningPlayer);
	void compareStraightFlush(std::map<int, int> &drawingPlayers, std::vector<int> &winningPlayer);
}