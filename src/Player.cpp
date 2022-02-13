#include "Player.hpp"



Player::Player()
{}

Player::Player(int seatPos, int playerNo)
: seatPos(seatPos), playerNo(playerNo)
{}

Player::~Player()
{}


int Player::action(int thisPlayersBettingSpace, int previousPlayersBettingSpace, double &betValue)
{
	if (thisPlayersBettingSpace == previousPlayersBettingSpace)
	{
		// return check
		return 0;
	}
	else if (thisPlayersBettingSpace <= previousPlayersBettingSpace)
	{
		// return call
		return 1;
	}

	// need another program here to decide bet value. This is the complex bit of deciding how the computer plays poker

	else
	{
		std::cout << "Action selection failed!" << std::endl;
		return -1;
	}
}

int Player::getSeatPos()
{
	return seatPos;
}

void Player::shiftPos(int numPlyers)
{
	seatPos -= 1;
	
	// if position -1, set to numPlayers-1
	if (seatPos == -1)
	{
		seatPos = numPlyers - 1;
	}
}


int Player::getPlayerNo()
{
	return playerNo;
}