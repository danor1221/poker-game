#pragma once

#include <iostream>
#include <vector>

#include "Player.hpp"
#include "MoneyCount.hpp"
#include "Hand.hpp"

//class Hand;
//class Player;






class Game
{
public:

	Game(int enterednoPlayers);
	~Game();

	void createSetOfPlayers(int enterednoPlayers);
	void nextHand(); // Moves the game to the next hand

	bool running()
	{
		return isRunning;
	}

	void setRunningFalse()
	{
		isRunning = false;
	}

private:
	int noPlayers;
	bool isRunning;
	std::vector<Player> players;
	std::vector<MoneyCount> moneycount;
};
