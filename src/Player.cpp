#include "Player.hpp"



Player::Player()
{}

Player::Player(int seatPos)
: seatPos(seatPos)
{}

Player::~Player()
{}


int Player::action(int thisPlayersBettingSpace, int previousPlayersBettingSpace)
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
	else
	{
		std::cout << "Action selection failed!" << std::endl;
		return -1;
	}
}