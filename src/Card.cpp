#include "Card.hpp"


Card::Card()
{}

Card::~Card()
{}

void Card::createCard(std::vector<int> &cardVector)
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_int_distribution<int> distribution(1,cardVector.size());

    int index;
    index = distribution(generator);

    cardValue = cardVector[index-1];
    cardVector.erase(cardVector.begin()+index-1);


    //using namespace std::this_thread;
    //using namespace std::chrono;
    //sleep_for(nanoseconds(index));


    // need to put in a sleep command or do something else as cards being dealt are not completely random as they are based on time

    setActualValueAndSuit();
}

int Card::getcardValue()
{
    return cardValue;
}

void Card::setActualValueAndSuit()
{
    if (cardValue <= 13)
    {
        // Hearts
        actualValue = cardValue;
        suit = 1;
    }
    else if (cardValue > 13 and cardValue <= 26)
    {
        // Diamonds
        actualValue = cardValue - 13;
        suit = 2;
    }
    else if (cardValue > 26 and cardValue <= 39)
    {
        // Spades
        actualValue = cardValue - 26;
        suit = 3;
    }
    else if (cardValue > 39)
    {
        // Clubs
        actualValue = cardValue - 39;
        suit = 4;
    }
}

int Card::getActualValue()
{
    return actualValue;
}

int Card::getSuit()
{
    return suit;
}