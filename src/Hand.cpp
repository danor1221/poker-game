#include "Hand.hpp"


Hand::Hand(std::vector<Player> players)
: players(players)
{
	for (Player player: players)
	{
		numPlayers++;
	}
}
	
Hand::~Hand() 
{}

void Hand::Deal() 
{
	// deal a set of cards for each player
	for (std::size_t i = 0; i < players.size(); ++i)
	{
		SetOfCards individualPlayerssetofcards = SetOfCards();
		individualPlayerssetofcards.dealSetOfCards(cardVector);
		PlayersCards.push_back(individualPlayerssetofcards.getsetofcards());

		// setup the betting space vector here as well
		bettingspace.push_back(BettingSpace());		
	}
}


void Hand::preFlop(std::vector<MoneyCount> moneycount)
{
	// take blinds from players/positions 0 and 1
	(moneycount[0]).removeSmallBlind();
	(moneycount[1]).removeBigBlind();

	(bettingspace[0]).addAmount(0.5);
	(bettingspace[1]).addAmount(1);

	action = true;
	int i = 2;
	int j = i-1;

	int endint = 2; // set the last player to play to end action. Is actually the last player+1

	runTheAction(i, j, endint, moneycount);

	std::cout << "Pre-Flop Action complete" << std::endl;
	std::cout << "Pot stands at *PoundSymbol*" <<  pot << std::endl;
	printTheBettingSpace();

}





void Hand::Flop(std::vector<MoneyCount> moneycount)
{
	// Need to add the flop cards

	SetOfCards flopCardsObj = SetOfCards();
	flopCardsObj.dealFlopCards(cardVector);

	std::vector<Card> flopCards = flopCardsObj.getsetofcards();


	for (std::size_t f = 0; f < players.size(); ++f)
	{
		(PlayersCards[f]).push_back(flopCards[0]);
		(PlayersCards[f]).push_back(flopCards[1]);
		(PlayersCards[f]).push_back(flopCards[2]);
	}


	action = true;
	int i = 0;
	int j = numPlayers-1;

	int endint = numPlayers;

	runTheAction(i, j, endint, moneycount);

	std::cout << "Post-Flop Action complete" << std::endl;
	std::cout << "Pot stands at *PoundSymbol*" <<  pot << std::endl;
	printTheBettingSpace();

}

void Hand::Turn(std::vector<MoneyCount> moneycount)
{
	// Need to add turn card
	SetOfCards turnCardObj = SetOfCards();
	turnCardObj.dealTurnCard(cardVector);

	std::vector<Card> turnCard = turnCardObj.getsetofcards();
	for (std::size_t f = 0; f < players.size(); ++f)
	{
		(PlayersCards[f]).push_back(turnCard[0]);
	}



	action = true;
	int i = 0;
	int j = numPlayers-1;

	int endint = numPlayers;

	runTheAction(i, j, endint, moneycount);

	std::cout << "Turn Action complete" << std::endl;
	std::cout << "Pot stands at *PoundSymbol*" <<  pot << std::endl;
	printTheBettingSpace();
}

void Hand::River(std::vector<MoneyCount> moneycount)
{
	// Need to add River card
	SetOfCards riverCardObj = SetOfCards();
	riverCardObj.dealRiverCard(cardVector);

	std::vector<Card> riverCard = riverCardObj.getsetofcards();
	for (std::size_t f = 0; f < players.size(); ++f)
	{
		(PlayersCards[f]).push_back(riverCard[0]);
	}



	action = true;
	int i = 0;
	int j = numPlayers-1;

	int endint = numPlayers;

	runTheAction(i, j, endint, moneycount);

	std::cout << "River Action complete" << std::endl;
	std::cout << "Pot stands at *PoundSymbol*" <<  pot << std::endl;
	printTheBettingSpace();
}








void Hand::runTheAction(int i, int j, int endint, std::vector<MoneyCount> moneycount)
{
	while(action)
	{
		// call for player 2 (third player) to make a move then player 3 etc until all is equal. (need to make sure about checking small and big blind positions) After sete action to false and exit while loop and end preFlop stage
		double thisPlayerAmount = (bettingspace[i]).getAmount();
		double previousPlayerAmount = (bettingspace[j]).getAmount();

		int actionChosen = -1;
		actionChosen = (players[i]).action(thisPlayerAmount, previousPlayerAmount);


		printTheBettingSpace();


		if (i == 0)
		{
			// get the human player's input
			// of course i == 0 will need to be edited as players/blinds move
			actionChosen = -1; 

			std::cout << "Enter desired action: 0 for check, 1 for call" << std::endl;
			std::cin >> actionChosen;
		}


		if (actionChosen == 0)
		{
			// this is a check
			std::cout << "Player " << i << " checks" << std::endl;

			i++;
			j++;
		}
		else if (actionChosen == 1)
		{
			// this is a call
			(moneycount[i]).removeAmount(previousPlayerAmount - thisPlayerAmount);
			(bettingspace[i]).addAmount(previousPlayerAmount - thisPlayerAmount);

			std::cout << "Player " << i << " calls" << std::endl;
			i++;
			j++;
		}

		else if (actionChosen == -1)
		{
			std::cout << "error chosing action!" << std::endl;
			i++;
			j++;
		}

		std::cout << "" << std::endl;

		if (i == endint)
		{
			// Big blind just played
			// in order to generalise this, set the most recent player to raise/bet to be the endint integer
			action = false;
		}


		if (i == numPlayers)
		{
			i = 0;
			j = numPlayers-1;
		}
		else if (j == numPlayers)
		{
			i = 1;
			j = 0;
		}
	}

	// At the end of all that action, add money to the pot and clear the betting space values

	for (std::size_t i = 0; i < players.size(); ++i)
	{
		pot += (bettingspace[i]).getAmount();
		(bettingspace[i]).clearAmount();
	}
}





void Hand::findTheWinner()
{
	// vector that holds the points for each player
	std::vector<int> playerPoints;

	// map holding player to playerPoint
	std::map<int, int> playerToPoint;

	// map that holds count of each point type. ed how many flushes etc to detect draws
	std::map<int, int> typeCount;

	// vector of vectors containing cards for each player. IGNORE THIS USE PRIVATE MEMEBER OF HAND.CPP PlayersCards
	std::vector<std::vector<int>> allPlayersCardsAValue;
	std::vector<std::vector<int>> allPlayersCardsSuit;



//	HandValue* handvalue = newHandValue(PlayersCards);



	int n = players.size();

	for (int j = 0; j < n; ++j)
	{
		std::vector<int> thisPlayersCardsAValue;
		std::vector<int> thisPlayersCardsSuit;

		// assign memory?
		for (int i = 0; i < 7; ++i)
		{
			thisPlayersCardsAValue.push_back((PlayersCards[j][i]).getActualValue());
			thisPlayersCardsSuit.push_back((PlayersCards[j][i]).getSuit());
		}
		


		// declare HandValue class object and get point for that player
		HandValue* handvalue = new HandValue(thisPlayersCardsAValue, thisPlayersCardsSuit);
		int playersHandValue = handvalue->getHandValue();
		std::cout << "Player " << j << " has: " << playersHandValue << std::endl;
		delete handvalue;


		// append into vector of player's points, map of player's points, and map holding count of each point type
		playerPoints.push_back(playersHandValue);
		playerToPoint.insert({j, playersHandValue});
		typeCount[playersHandValue] += 1;
	}


	// we will rewrite HandValue class as a namespace set of functions
	// NOTE FOR FUTURE DAN. Use new map playerToPoint to grab those players who have drawn as well as their points. Pass this map into new class? or maybe pass into HandValue class? Then work out who has higher straight or flush or whatever is passed in. Am currently thinking a new class would be more appropriate. Also maybe try to create system that says this person wins with pair of aces or whatever so it actually says that. Also need to add function to Game.cpp that moves winnings about. Note, moneycount has been identified to maybe be passed by reference into some above functions.


	// NEW NOTE. HandValue should be kept but is created once and completes above for loop itself to reduced size of this class. HandValueInv will also be the same


	// Find iterator to max value in playerPoints
	std::vector<int>::iterator result;
	result = std::max_element(playerPoints.begin(), playerPoints.end());


	// check if no. times the max value has been found. If greater than or equal to two need to investigate further
	int numWin = typeCount.find(*(result))->second;
	if (numWin >= 2)
	{
		std::cout << "Draw found need to investigate further" << std::endl;
		HVI::InvestigateDraw(playerToPoint, *(result), winningPlayer, numWin, PlayersCards);// PASS DOWN PlayersCards to see them
	}

	else
		std::cout << "Winner is player: " << std::distance(playerPoints.begin(), result) << " with a " << pointValueToName.find(*(result))->second<< std::endl;




	// findTheWinner should maybe return an integer deciding who the winner is so the Game class can then move winnings to them
	




	// Unhash below for loop to run testHandValue function. Should be run with 9 players.
	/*
	for (int j = 0; j < n; ++j)
	{
		testHandValue(j);
	}
	*/

}







void Hand::printThePlayersCards()
{
	std::cout << "Your cards are: " << (PlayersCards[0][0]).getcardValue() << " " << (PlayersCards[0][1]).getcardValue() << std::endl;
}


void Hand::printAllPlayersPersonalCards()
{
	// this is a test function to see all the players personal cards
	for (std::size_t j = 0; j < players.size(); ++j)
	{
		std::cout << "Cards: " << (PlayersCards[j][0]).getcardValue() << " " << (PlayersCards[j][1]).getcardValue() << std::endl;
	}
}

void Hand::printTheBettingSpace()
{
	std::cout << "The betting space for all players is: " << std::endl;
	for (std::size_t j = 0; j < players.size(); ++j)
	{
		std::cout << "Player " << j << ": " << (bettingspace[j]).getAmount() << std::endl;
	}
}

void Hand::printAllFlopPlayersCards()
{
	// this is a test function to see all the players cards
	for (std::size_t j = 0; j < players.size(); ++j)
	{
		std::cout << "Cards: " << (PlayersCards[j][0]).getcardValue() << " " << (PlayersCards[j][1]).getcardValue() << " " << (PlayersCards[j][2]).getcardValue() << " " << (PlayersCards[j][3]).getcardValue() << " " << (PlayersCards[j][4]).getcardValue() << std::endl;
	}
}

void Hand::printAllTurnPlayersCards()
{
	// this is a test function to see all the players cards
	for (std::size_t j = 0; j < players.size(); ++j)
	{
		std::cout << "Cards: " << (PlayersCards[j][0]).getcardValue() << " " << (PlayersCards[j][1]).getcardValue() << " " << (PlayersCards[j][2]).getcardValue() << " " << (PlayersCards[j][3]).getcardValue() << " " << (PlayersCards[j][4]).getcardValue() << " " << (PlayersCards[j][5]).getcardValue() << std::endl;
	}
}

void Hand::printAllRiverPlayersCards()
{
	// this is a test function to see all the players cards
	for (std::size_t j = 0; j < players.size(); ++j)
	{
		std::cout << "Cards: " << (PlayersCards[j][0]).getcardValue() << " " << (PlayersCards[j][1]).getcardValue() << " " << (PlayersCards[j][2]).getcardValue() << " " << (PlayersCards[j][3]).getcardValue() << " " << (PlayersCards[j][4]).getcardValue() << " " << (PlayersCards[j][5]).getcardValue() << " " << (PlayersCards[j][6]).getcardValue() << std::endl;
	}
}




void Hand::testHandValue(int playerno)
{
	// playerno will determine what each player will be thought to have.

	if (playerno == 0) // currently set to 99 to not run this as straight flush aint working just yet. Similar with others below.
	{
		
		// Give player 0 quads straight flush
		std::vector<int> thisPlayersCardsValue {1, 13, 12, 11, 10, 5, 4};
		std::vector<int> thisPlayersCardsAValue {1, 13, 12, 11, 10, 5, 4};
		std::vector<int> thisPlayersCardsSuit {1, 1, 1, 1, 1, 4, 4};
		
		/* // Test case with 6 clubs
		std::vector<int> thisPlayersCardsValue {3, 46, 47, 48, 49, 52, 50};
		std::vector<int> thisPlayersCardsAValue {3, 7, 8, 9, 10, 13, 11};
		std::vector<int> thisPlayersCardsSuit {1, 4, 4, 4, 4, 4, 4};
		*/

		HandValue* handvalue = new HandValue(thisPlayersCardsAValue, thisPlayersCardsSuit);

		int playersHandValue = handvalue->getHandValue();

		std::cout << "Player " << playerno << " should have 8, program finds: " << playersHandValue << " (straight flush)" << std::endl;
	}

	else if (playerno == 1)
	{
		// Give player 1 quad kings
		std::vector<int> thisPlayersCardsValue {1, 2, 5, 13, 26, 39, 52};
		std::vector<int> thisPlayersCardsAValue {1, 2, 18, 13, 13, 13, 13};
		std::vector<int> thisPlayersCardsSuit {1, 1, 2, 1, 2, 3, 4};

		HandValue* handvalue = new HandValue(thisPlayersCardsAValue, thisPlayersCardsSuit);

		int playersHandValue = handvalue->getHandValue();

		std::cout << "Player " << playerno << " should have 7, program finds: " << playersHandValue << " (quads)" << std::endl;
	}

	else if (playerno == 2)
	{
		// Give player 2 full house 3 10s, 2 4s
		std::vector<int> thisPlayersCardsValue {10, 23, 36, 17, 43, 1, 15};
		std::vector<int> thisPlayersCardsAValue {10, 10, 10, 4, 4, 1, 2};
		std::vector<int> thisPlayersCardsSuit {1, 2, 3, 2, 4, 1, 2};

		HandValue* handvalue = new HandValue(thisPlayersCardsAValue, thisPlayersCardsSuit);

		int playersHandValue = handvalue->getHandValue();

		std::cout << "Player " << playerno << " should have 6, program finds: " << playersHandValue << " (full house)" << std::endl;
	}

	else if (playerno == 3)
	{
		// Give player 3 flush. Clubs king queen 9 6 4
		std::vector<int> thisPlayersCardsValue {28, 43, 48, 45, 10, 52, 51};
		std::vector<int> thisPlayersCardsAValue {2, 4, 9, 6, 10, 13, 12};
		std::vector<int> thisPlayersCardsSuit {3, 4, 4, 4, 1, 4, 4};

		HandValue* handvalue = new HandValue(thisPlayersCardsAValue, thisPlayersCardsSuit);

		int playersHandValue = handvalue->getHandValue();

		std::cout << "Player " << playerno << " should have 5, program finds: " << playersHandValue << " (flush)" << std::endl;
	}

	else if (playerno == 4)
	{
		// Give player 4 straight
		std::vector<int> thisPlayersCardsValue {4, 5, 19, 20, 34, 52, 12};
		std::vector<int> thisPlayersCardsAValue {4, 5, 6, 7, 8, 13, 12};
		std::vector<int> thisPlayersCardsSuit {1, 1, 2, 2, 3, 4, 1};

		HandValue* handvalue = new HandValue(thisPlayersCardsAValue, thisPlayersCardsSuit);

		int playersHandValue = handvalue->getHandValue();

		std::cout << "Player " << playerno << " should have 4, program finds: " << playersHandValue << " (straight)" << std::endl;
	}

	else if (playerno == 5)
	{
		// Give player 5 trip 7s
		std::vector<int> thisPlayersCardsValue {35, 33, 7, 41, 46, 39, 23};
		std::vector<int> thisPlayersCardsAValue {9, 7, 7, 2, 7, 13, 10};
		std::vector<int> thisPlayersCardsSuit {3, 3, 1, 4, 4, 3, 2};

		HandValue* handvalue = new HandValue(thisPlayersCardsAValue, thisPlayersCardsSuit);

		int playersHandValue = handvalue->getHandValue();

		std::cout << "Player " << playerno << " should have 3, program finds: " << playersHandValue << " (trips)" << std::endl;
	}

	else if (playerno == 6)
	{
		// Give player 6 two pair of aces and 3s
		std::vector<int> thisPlayersCardsValue {6, 1, 43, 27, 16, 29, 25};
		std::vector<int> thisPlayersCardsAValue {6, 1, 4, 1, 3, 3, 12};
		std::vector<int> thisPlayersCardsSuit {1, 1, 4, 3, 2, 3, 2};

		HandValue* handvalue = new HandValue(thisPlayersCardsAValue, thisPlayersCardsSuit);

		int playersHandValue = handvalue->getHandValue();

		std::cout << "Player " << playerno << " should have 2, program finds: " << playersHandValue << " (two pair)" << std::endl;
	}

	else if (playerno == 7)
	{
		// Give player 7 pair of jacks
		std::vector<int> thisPlayersCardsValue {8, 50, 25, 24, 30, 2, 27};
		std::vector<int> thisPlayersCardsAValue {8, 11, 12, 11, 4, 2, 1};
		std::vector<int> thisPlayersCardsSuit {1, 4, 2, 2, 3, 1, 3};

		HandValue* handvalue = new HandValue(thisPlayersCardsAValue, thisPlayersCardsSuit);

		int playersHandValue = handvalue->getHandValue();

		std::cout << "Player " << playerno << " should have 1, program finds: " << playersHandValue << " (pair)" << std::endl;
	}

	else if (playerno == 8)
	{
		// Give player 8 nothing
		std::vector<int> thisPlayersCardsValue {13, 38, 22, 36, 44, 43, 2};
		std::vector<int> thisPlayersCardsAValue {13, 12, 9, 10, 5, 4, 2};
		std::vector<int> thisPlayersCardsSuit {1, 3, 2, 3, 4, 4, 1};

		HandValue* handvalue = new HandValue(thisPlayersCardsAValue, thisPlayersCardsSuit);

		int playersHandValue = handvalue->getHandValue();

		std::cout << "Player " << playerno << " should have 0, program finds: " << playersHandValue << " (nothing/highcard)" << std::endl;
	}
}