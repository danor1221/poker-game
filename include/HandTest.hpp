#pragma once

#include <iostream>
#include <vector>

#include "Hand.hpp"
#include "Card.hpp"
#include "SetofCards.hpp"
#include "Player.hpp"
#include "MoneyCount.hpp"
#include "BettingSpace.hpp"
#include "HandValue.hpp"
#include "HandValueInv.hpp"



class HandTest : public Hand
{
public:
	HandTest(std::vector<Player> players);
	~HandTest();

	void testDeal();

	void testFlop(std::vector<MoneyCount> &moneycount);
	void testTurn(std::vector<MoneyCount> &moneycount);
	void testRiver(std::vector<MoneyCount> &moneycount);

private:
// Straight Flushes

	std::vector<std::vector<int>> desiredCards{ {15, 30, 12, 11, 10, 41, 33}, 	// pair 	2s
												{1, 13, 12, 11, 10, 41, 33}, 	// SF 		A K Q J 10
												{9, 13, 12, 11, 10, 41, 33}, 	// SF 		K Q J 10 9
												{20, 46, 12, 11, 10, 41, 33} };	// trips 	777

// Quads
/*
	std::vector<std::vector<int>> desiredCards{ {42, 29, 16, 3, 14, 27, 17}, 	// quads 	3333
												{40, 1, 16, 3, 14, 27, 17}, 	// quads 	AAAA
												{4, 50, 16, 3, 14, 27, 17}, 	// Two pair	AA4433 (acc 3 pairs lol)
												{43, 25, 16, 3, 14, 27, 17} };	// Two pair	AA4433
*/
// Full Houses
/*
	std::vector<std::vector<int>> desiredCards{ {26, 47, 13, 8, 21, 35, 42}, 	// FH 		KK888
												{48, 29, 13, 8, 21, 35, 42}, 	// Two pair 998833
												{52, 39, 13, 8, 21, 35, 42}, 	// FH  		KKK88
												{22, 9, 13, 8, 21, 35, 42} };	// FH 		99988
*/
/*
	std::vector<std::vector<int>> desiredCards{ {13, 12, 19, 6, 5, 31, 44}, 	// FH 		66555
												{17, 30, 19, 6, 5, 31, 44}, 	// FH 		66555
												{29, 40, 19, 6, 5, 31, 44}, 	// FH 		66555
												{28, 16, 19, 6, 5, 31, 44} };	// FH 		66555
*/
// Flushes
/*
	std::vector<std::vector<int>> desiredCards{ {13, 37, 31, 32, 33, 34, 25, 26},	// Flush 	5678J
												{39, 52, 31, 32, 33, 34, 25, 26},	// Flush 	5678K
												{46, 7, 31, 32, 33, 34, 25, 26},	// trips 	7s
												{51, 40, 31, 32, 33, 34, 25, 26} };	// HC
*/
/*
	std::vector<std::vector<int>> desiredCards{ {15, 22, 17, 20, 51, 19, 1},	// Flush 	24679
												{37, 43, 17, 20, 51, 19, 1},	// pair 	4s
												{25, 24, 17, 20, 51, 19, 1},	// Flush 	467JQ
												{14, 26, 17, 20, 51, 19, 1} };	// Flush 	467KA
*/
/*
	std::vector<std::vector<int>> desiredCards{ {11, 24, 51, 48, 43, 44, 47},	// Flush 	4589Q
												{41, 29, 51, 48, 43, 44, 47},	// Flush 	4589Q
												{1, 14, 51, 48, 43, 44, 47},	// Flush 	4589Q
												{6, 8, 51, 48, 43, 44, 47} };	// Flush 	4589Q
*/
// Straights
/*
	std::vector<std::vector<int>> desiredCards{ {26, 37, 5, 29, 15, 33, 43},	// HC
												{2, 40, 5, 29, 15, 33, 43},		// straight A2345 (also pair of 2s) (found straight desipte pair present!)
												{36, 49, 5, 29, 15, 33, 43},	// pair 	10s
												{12, 3, 5, 29, 15, 33, 43} };	// pair 	3s
*/
/*
	std::vector<std::vector<int>> desiredCards{ {1, 37, 5, 29, 26, 33, 43},		// HC
												{15, 40, 5, 29, 26, 33, 43},	// straight A2345
												{36, 49, 5, 29, 26, 33, 43},	// pair 	10s
												{13, 6, 5, 29, 26, 33, 43} };	// straight 34567
*/
/*
	std::vector<std::vector<int>> desiredCards{ {1, 14, 7, 22, 21, 31, 45},		// straight 56789 (also pair of As)
												{40, 27, 7, 22, 21, 31, 45},	// straight 56789 (also pair of As)
												{33, 46, 7, 22, 21, 31, 45},	// straight 56789 (also trip 7s)
												{39, 25, 7, 22, 21, 31, 45} };	// straight 56789
*/
// Trips
/*
	std::vector<std::vector<int>> desiredCards{ {11, 13, 3, 14, 35, 38, 28},	// HC
												{22, 27, 3, 14, 35, 38, 28},	// Two pair AA99
												{29, 42, 3, 14, 35, 38, 28},	// trips 	333
												{1, 40, 3, 14, 35, 38, 28} }; 	// trips 	AAA
*/
/*
	std::vector<std::vector<int>> desiredCards{ {11, 13, 3, 14, 27, 38, 28},	// HC
												{40, 4, 3, 14, 27, 38, 28},		// Trips 	AAA
												{29, 24, 3, 14, 27, 38, 28},	// Two Pair AA33
												{1, 44, 3, 14, 27, 38, 28} }; 	// trips 	AAA
*/
/*
	std::vector<std::vector<int>> desiredCards{ {12, 21, 3, 14, 39, 52, 13},	// Trips 	KKK
												{35, 36, 3, 14, 39, 52, 13},	// Trips 	KKK
												{30, 18, 3, 14, 39, 52, 13},	// Trips 	KKK
												{44, 47, 3, 14, 39, 52, 13} }; 	// trips 	KKK
*/
// Two pairs
/*
	std::vector<std::vector<int>> desiredCards{ {39, 38, 18, 26, 50, 12, 27},	// Two pair KKQQ (both split)
												{14, 51, 18, 26, 50, 12, 27},	// Two pair AAQQ (both split)
												{28, 38, 18, 26, 50, 12, 27},	// pair 	QQ
												{29, 30, 18, 26, 50, 12, 27} }; // HC
*/
/*
	std::vector<std::vector<int>> desiredCards{ {1, 39, 18, 26, 50, 12, 27},	// Two pair AAKK (both split)
												{14, 51, 18, 26, 50, 12, 27},	// Two pair AAQQ (both split)
												{28, 38, 18, 26, 50, 12, 27},	// pair 	QQ
												{29, 30, 18, 26, 50, 12, 27} }; // HC
*/
/*
	std::vector<std::vector<int>> desiredCards{ {1, 38, 18, 26, 50, 12, 27},	// Two pair AAQQ (both split)
												{14, 51, 18, 26, 50, 12, 27},	// Two pair AAQQ (both split)
												{28, 38, 18, 26, 50, 12, 27},	// pair 	QQ
												{29, 30, 18, 26, 50, 12, 27} }; // HC
*/
/*
	std::vector<std::vector<int>> desiredCards{ {2, 35, 18, 26, 39, 12, 25},	// Two pair AAQQ (both on board), hand is 9  2
												{15, 49, 18, 26, 39, 12, 25},	// Two pair AAQQ (both on board), hand is 10 2
												{28, 34, 18, 26, 39, 12, 25},	// Two pair AAQQ (both on board), hand is 8  2
												{29, 30, 18, 26, 39, 12, 25} }; // Two pair AAQQ (both on board), hand is 4  3
*/
/*
	std::vector<std::vector<int>> desiredCards{ {3, 35, 18, 26, 39, 12, 25},	// Two pair AAQQ (both on board), hand is 9  3
												{15, 48, 18, 26, 39, 12, 25},	// Two pair AAQQ (both on board), hand is 9  2
												{28, 34, 18, 26, 39, 12, 25},	// Two pair AAQQ (both on board), hand is 8  2
												{29, 30, 18, 26, 39, 12, 25} }; // Two pair AAQQ (both on board), hand is 4  3
*/
// Pairs
/*
	std::vector<std::vector<int>> desiredCards{ {16, 9, 21, 33, 45, 41, 13},	// HC
												{3, 39, 21, 33, 45, 41, 13},	// pair 	KK (1 hand 1 board)
												{14, 27, 21, 33, 45, 41, 13},	// pair 	AA (in hand)
												{22, 15, 21, 33, 45, 41, 13} }; // pair 	22 (1 hand 1 board)
*/
/*
	std::vector<std::vector<int>> desiredCards{ {16, 9, 21, 33, 45, 41, 13},	// HC
												{1, 40, 21, 33, 45, 41, 13},	// pair 	AA (in hand)
												{14, 27, 21, 33, 45, 41, 13},	// pair 	AA (in hand)
												{22, 15, 21, 33, 45, 41, 13} }; // pair 	22 (1 hand 1 board)
*/
/*
	std::vector<std::vector<int>> desiredCards{ {16, 9, 40, 33, 45, 41, 13},	// HC
												{1, 42, 40, 33, 45, 41, 13},	// pair 	AA (1 hand 1 board)
												{14, 10, 40, 33, 45, 41, 13},	// pair 	AA (1 hand 1 board)
												{22, 15, 40, 33, 45, 41, 13} }; // pair 	22 (1 hand 1 board)
*/
// High Cards
/*
	std::vector<std::vector<int>> desiredCards{ {5, 4, 40, 33, 45, 41, 13},		// HC 	5
												{22, 8, 40, 33, 45, 41, 13},	// HC 	9	
												{29, 50, 40, 33, 45, 41, 13},	// HC 	J
												{25, 16, 40, 33, 45, 41, 13} }; // HC 	Q
*/

// Dont know what this last one was
/*

	std::vector<std::vector<int>> desiredCards{ {41, 42, 26, 18, 6, 12, 11}, 	// HC
												{38, 51, 26, 18, 6, 12, 11},	// trips 	QQQ
												{39, 29, 26, 18, 6, 12, 11},	// pair 	KK
												{36, 10, 26, 18, 6, 12, 11} }; 	// pair 	10s
*/
};