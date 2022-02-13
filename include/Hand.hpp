#pragma once

#include <iostream>
#include <vector>
/*
#include "Game.hpp"
#include "SetOfCards.hpp"
#include "Player.hpp"
#include "MoneyCount.hpp"
*/
#include "Card.hpp" // added
#include "SetofCards.hpp" // added
#include "Player.hpp" // added
#include "MoneyCount.hpp" // added
#include "BettingSpace.hpp"
#include "HandValue.hpp"
#include "HandValueInv.hpp"


class Hand
{
public:

	Hand(std::vector<Player> players);
	~Hand();

	void Deal();

	void preFlop(std::vector<MoneyCount> &moneycount); // This vector should probably be passed in by reference
	void Flop(std::vector<MoneyCount> &moneycount);
	void Turn(std::vector<MoneyCount> &moneycount);
	void River(std::vector<MoneyCount> &moneycount);

	// This function runs the calling/betting/raising/checking/folding while loop. i and j are the starting and previous players. used to define where the action starts and previous players currently helping the decide moves. endint is the current endpoint of the action. When raising and betting is implemented, whoever raises/bets most recently becomes the endint.
	void runTheAction(int i, int j, int endint, std::vector<MoneyCount> &moneycount);

	void findTheWinner();


	// Get function to get the pot value and winning player(s) before this instance of Hand is deleted
	std::vector<int> getWinningPlayer();
	double getPot();


	void printThePlayersCards();

	void printAllPlayersPersonalCards();
	void printTheBettingSpace();
	void printAllFlopPlayersCards();
	void printAllTurnPlayersCards();
	void printAllRiverPlayersCards();

	void testHandValue(int playerno);


protected:

	std::vector<Player> players;
	std::vector<std::vector<Card>> PlayersCards;
	std::vector<BettingSpace> bettingspace;
	std::vector<int> cardVector{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52};

	std::map<int, std::string> pointValueToName{ {0, "nothing"}, {1, "pair"}, {2, "two pair"}, {3, "trips"}, {4, "straight"}, {5, "flush"}, {6, "full house"}, {7, "quads"}, {8, "straight flush"} };

	std::map<int, int> seatPosPlayer;
	
	bool action;
	double pot = 0.0;
	int numPlayers = 0;

	std::vector<int> winningPlayer; // This is a vector in case of actual draws

	Player humanPly;
};