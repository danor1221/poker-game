#include <iostream>
#include <vector>

#include "Game.hpp"
/*
#include "Player.hpp"
#include "Hand.hpp"
#include "SetOfCards.hpp"
#include "Card.hpp"
*/


Game::Game(int enterednoPlayers, int testFlag) 
	: noPlayers(enterednoPlayers)
{
	isRunning = true;
	createSetOfPlayers(noPlayers);

	if (testFlag == 1) // probs can directly set
		testCards = true;
	else
		testCards = false;
}
	
Game::~Game()
{}


void Game::createSetOfPlayers(int enterednoPlayers)
{
	//players.reserve (10); // Reserve memory not to allocate it 10 times...
    for (int i = 0; i < enterednoPlayers; ++i)
    {
	    players.push_back(Player(i, i));
	    moneycount.push_back(MoneyCount());
    }
}

void Game::nextHand() // Moves the game to the next hand
{
	if (!testCards)
	{
		Hand* hand = new Hand(players);

		hand->Deal(); // call the function that deals a set of cards

		hand->printAllPlayersPersonalCards();
		hand->printThePlayersCards();

		hand->preFlop(moneycount);

		hand->Flop(moneycount);

		hand->printAllFlopPlayersCards();

		hand->Turn(moneycount);

		hand->printAllTurnPlayersCards();

		hand->River(moneycount);

		hand->printAllRiverPlayersCards();
		
		hand->findTheWinner();

		std::vector<int> winner;
		winner = hand->getWinningPlayer();

		double winnings;
		winnings = hand->getPot();

		delete hand;




		int len = winner.size();
		if (len > 1)
		{
			// assign winnings to drawing players
			for (int winPly : winner)
				moneycount[winPly].addAmount(winnings/len);
		}


		else
		{
			// assign winnings
			moneycount[winner[0]].addAmount(winnings);
		}



		int i = 0;
		for (auto chips : moneycount)
		{
			std::cout << "player " << i << " has " << chips.getAmount() << std::endl;
			i++;
		}



		// move players around table, or shift blinds positions
		for (Player &player : players)
			player.shiftPos(noPlayers);
	}




















	else if (testCards)
	{
		// run test Hand
		HandTest* handtest = new HandTest(players);

		handtest->testDeal();

		handtest->printAllPlayersPersonalCards();
		handtest->printThePlayersCards();

		handtest->preFlop(moneycount);

		handtest->testFlop(moneycount);

		handtest->printAllFlopPlayersCards();

		handtest->testTurn(moneycount);

		handtest->printAllTurnPlayersCards();

		handtest->testRiver(moneycount);

		handtest->printAllRiverPlayersCards();

		handtest->findTheWinner();

		std::vector<int> winner;
		winner = handtest->getWinningPlayer();

		double winnings;
		winnings = handtest->getPot();

		delete handtest;




		int len = winner.size();
		if (len > 1)
		{
			// assign winnings to drawing players
			for (int winPly : winner)
				moneycount[winPly].addAmount(winnings/len);
		}


		else
		{
			// assign winnings
			moneycount[winner[0]].addAmount(winnings);
		}



		int i = 0;
		for (auto chips : moneycount)
		{
			std::cout << "player " << i << " has " << chips.getAmount() << std::endl;
			i++;
		}



		// move players around table, or shift blinds positions
		for (Player &player : players)
			player.shiftPos(noPlayers);
	}
}