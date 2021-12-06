#include <iostream>
#include <vector>

#include "Game.hpp"
/*
#include "Player.hpp"
#include "Hand.hpp"
#include "SetOfCards.hpp"
#include "Card.hpp"
*/


Game::Game(int enterednoPlayers) 
	: noPlayers(enterednoPlayers)
{
	isRunning = true;
	createSetOfPlayers(noPlayers);
}
	
Game::~Game()
{}


void Game::createSetOfPlayers(int enterednoPlayers)
{
	//players.reserve (10); // Reserve memory not to allocate it 10 times...
    for (int i = 0; i < enterednoPlayers; ++i)
    {
	    players.push_back(Player(i));
	    moneycount.push_back(MoneyCount());
    }
}

void Game::nextHand() // Moves the game to the next hand
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
	// need to remember to uncomment below line


	// find winValue for all players
	// designate winner
	// assign winnings

	hand->findTheWinner();


	// delete hand;	
}