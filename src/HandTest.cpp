#include "HandTest.hpp"



HandTest::HandTest(std::vector<Player> players)
	: Hand(players)
{}
	
HandTest::~HandTest() 
{}


void HandTest::testDeal()
{
	std::cout << "number of players is: " << numPlayers << std::endl;
	// deal a specific set of cards for each player
	for (std::size_t i = 0; i < players.size(); ++i)
	{
		SetOfCards individualPlayerssetofcards = SetOfCards(desiredCards, i);
		individualPlayerssetofcards.dealSpecific();
		PlayersCards.push_back(individualPlayerssetofcards.getsetofcards());

		// setup the betting space vector here as well
		bettingspace.push_back(BettingSpace());
	}
}


void HandTest::testFlop(std::vector<MoneyCount> &moneycount)
{
	// add specific flop cards

	SetOfCards flopCardsObj = SetOfCards(desiredCards, 0); // here i is set to 0 as it can be anything
	flopCardsObj.dealSpecificFlop();

	std::vector<Card> flopCards = flopCardsObj.getsetofcards();


	for (std::size_t f = 0; f < players.size(); ++f)
	{
		(PlayersCards[f]).push_back(flopCards[0]);
		(PlayersCards[f]).push_back(flopCards[1]);
		(PlayersCards[f]).push_back(flopCards[2]);
	}




	int firstToAct = seatPosPlayer[0];

	action = true;
	int i = firstToAct;
	int j = seatPosPlayer[numPlayers-1];

	int endint = j+1;

	runTheAction(i, j, endint, moneycount);

	std::cout << "Post-Flop Action complete" << std::endl;
	std::cout << "Pot stands at *PoundSymbol*" <<  pot << std::endl;
	printTheBettingSpace();
}

void HandTest::testTurn(std::vector<MoneyCount> &moneycount)
{
	// add specific turn card

	SetOfCards turnCardObj = SetOfCards(desiredCards, 0);
	turnCardObj.dealSpecificTurn();

	std::vector<Card> turnCard = turnCardObj.getsetofcards();
	

	for (std::size_t f = 0; f < players.size(); ++f)
	{
		(PlayersCards[f]).push_back(turnCard[0]);
	}





	int firstToAct = seatPosPlayer[0];

	action = true;
	int i = firstToAct;
	int j = seatPosPlayer[numPlayers-1];

	int endint = j+1;

	runTheAction(i, j, endint, moneycount);

	std::cout << "Turn Action complete" << std::endl;
	std::cout << "Pot stands at *PoundSymbol*" <<  pot << std::endl;
	printTheBettingSpace();
}

void HandTest::testRiver(std::vector<MoneyCount> &moneycount)
{
	// add specific river card

	SetOfCards riverCardObj = SetOfCards(desiredCards, 0);
	riverCardObj.dealSpecificRiver();

	std::vector<Card> riverCard = riverCardObj.getsetofcards();
	

	for (std::size_t f = 0; f < players.size(); ++f)
	{
		(PlayersCards[f]).push_back(riverCard[0]);
	}





	int firstToAct = seatPosPlayer[0];

	action = true;
	int i = firstToAct;
	int j = seatPosPlayer[numPlayers-1];

	int endint = j+1;

	runTheAction(i, j, endint, moneycount);

	std::cout << "River Action complete" << std::endl;
	std::cout << "Pot stands at *PoundSymbol*" <<  pot << std::endl;
	printTheBettingSpace();
}
