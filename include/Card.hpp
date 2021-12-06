#pragma once

#include <iostream>
#include <vector>
#include <iterator> // for std::ostream_iterator
#include <algorithm> // for std::ranges::copy depending on lib support
#include <random>
#include <thread>
#include <chrono>


//#include "Game.hpp"



class Card
{
public:
	Card();
	~Card();

	void createCard(std::vector<int> &cardVector);

	int getcardValue();

	void setActualValueAndSuit();

	int getActualValue();
	int getSuit();
	
private:
	int cardValue;

	int actualValue;
	int suit;
};