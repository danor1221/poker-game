#include "SetOfCards.hpp"


SetOfCards::SetOfCards() 
{}

SetOfCards::~SetOfCards()
{}





SetOfCards::SetOfCards(std::vector<std::vector<int>> desiredCards, int i)
{
	thisSet = desiredCards[i];
}

void SetOfCards::dealSpecific()
{
	for (int j = 0; j < 2; ++j)
	{
		int nextCard = thisSet[j];
		Card newCard = Card(nextCard);
		setofcards.push_back(newCard);
	}
}

void SetOfCards::dealSpecificFlop()
{
	for (int j = 2; j < 5; ++j)
	{
		int nextCard = thisSet[j];
		Card newCard = Card(nextCard);
		setofcards.push_back(newCard);
	}	
}

void SetOfCards::dealSpecificTurn()
{
	int nextCard = thisSet[5];
	Card newCard = Card(nextCard);
	setofcards.push_back(newCard);
}

void SetOfCards:: dealSpecificRiver()
{
	int nextCard = thisSet[6];
	Card newCard = Card(nextCard);
	setofcards.push_back(newCard);
}





void SetOfCards::dealSetOfCards(std::vector<int> &cardVector)
{
	// run these two lines twice to append 2 cars to this player's set of cards
	for (int j = 0; j < 2; ++j)
	{
		Card newCard = Card();
		newCard.createCard(cardVector);
		setofcards.push_back(newCard);
	}
}


std::vector<Card> SetOfCards::getsetofcards()
{
	return setofcards;
}


void SetOfCards::dealFlopCards(std::vector<int> &cardVector)
{
	// Create three new Card objects which are unique in value
	for (int j = 0; j < 3; ++j)
	{
		Card newCard = Card();
		newCard.createCard(cardVector);
		setofcards.push_back(newCard);
	}
}

void SetOfCards::dealTurnCard(std::vector<int> &cardVector)
{
	// Create a new Card object which is unique in value
	Card newCard = Card();
	newCard.createCard(cardVector);
	setofcards.push_back(newCard);
}

void SetOfCards::dealRiverCard(std::vector<int> &cardVector)
{
	// Create a new Card object which is unique in value
	Card newCard = Card();
	newCard.createCard(cardVector);
	setofcards.push_back(newCard);
}