#pragma once

#include <iostream>
#include <vector>

//#include "Game.hpp"



class Player
{
public:

	int seatPos;

	Player();
	Player(int seatPos);

	~Player();

	int action(int thisPlayersBettingSpace, int previousPlayersBettingSpace);
};

