#include <iostream>
#include <vector>
#include <iterator> // for std::ostream_iterator
#include <algorithm> // for std::ranges::copy depending on lib support
#include <random>
#include <thread>
#include <chrono>
#include <bits/stdc++.h>

#include "Game.hpp"


/*
std::ostream& operator<< (std::ostream& out, const std::vector<Player>& v) {
    if ( !v.empty() ) {
        out << '[';
        std::ranges::copy(v, std::ostream_iterator<Player>(out, ", "));
        out << "\b\b]"; // use two ANSI backspace characters '\b' to overwrite final ", "
    }
    return out;
}
*/







Game* game = nullptr;

int main()
{
	std::cout << "Enter number of players: " << std::endl;

	int enterednoPlayers;
	std::cin >> enterednoPlayers;

	game = new Game(enterednoPlayers);

/*
	std::vector<Player> path;
	// ...
	for (Player i : game->players)
	    std::cout << i.seatPos << ' ';
*/

	// instantiate (enterednoPlayer) number of players in order
	// instantiate a hand
	// deal a set of cards to each player





	while(game->running())
	{
		// call next hand
		game->nextHand();
		game->setRunningFalse();
	}





	int entersometing;
	std::cin >> entersometing;

    


	return 0;
}