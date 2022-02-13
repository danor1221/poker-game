#pragma once

#include <iostream>
#include <vector>

//#include "Game.hpp"



class Player
{
public:


	Player();
	Player(int seatPos, int playerNo);

	~Player();

	int action(int thisPlayersBettingSpace, int previousPlayersBettingSpace, double &betValue);

	int getSeatPos();
	void shiftPos(int numPlyers);

	int getPlayerNo();
	

private:
	// seatPos is set when creating player
	int seatPos;
	int playerNo;
};

