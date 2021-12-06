#include "SetOfCards.hpp"


SetOfCards::SetOfCards() 
{}

SetOfCards::~SetOfCards()
{}


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