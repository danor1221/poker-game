#include "HandValue.hpp"


HandValue::HandValue(std::vector<int> thisPlayersCardsAValue, std::vector<int> thisPlayersCardsSuit)
	: thisPlayersCardsAValue(thisPlayersCardsAValue), thisPlayersCardsSuit(thisPlayersCardsSuit)
{}

HandValue::~HandValue()
{}



int HandValue::getHandValue()
{
	// check straight flush
	checkStraightFlush();

	// check hit
	if(checkHit())
		return 8;


	// check quads
	checkQuads();

	if(checkHit())
		return 7;


	// check full house
	checkFullHouse();

	if(checkHit())
		return 6;


	// check flush
	checkFlush();

	if(checkHit())
		return 5;
	

	// check straight
	checkStraight();

	if(checkHit())
		return 4;
	

	// check trips
	checkTrips();

	if(checkHit())
		return 3;


	// check two pair
	checkTwoPair();

	if(checkHit())
		return 2;


	// check pair
	checkPair();

	if(checkHit())
		return 1;



	// highcard...
	return 0;
}







void HandValue::checkStraightFlush()
{
	checkFlush();
	if (hit)
	{
		hit = false;
		checkStraight();
	}
}




void HandValue::checkQuads()
{
	std::map<int, int> duplicateElements;

    // Get the duplicate elements in vector
    findDuplicates(thisPlayersCardsAValue, duplicateElements);


    if ((duplicateElements.begin())->second == 4)
    	hit = true;

}




void HandValue::checkFullHouse()
{
	std::map<int, int> duplicateElements;

    // Get the duplicate elements in vector
    findDuplicates(thisPlayersCardsAValue, duplicateElements);


    // search duplicateElements map for a triple and pair. This aint the fastest way but it works. duplicateElements is never huge so wont be super slow.
	for (auto it = duplicateElements.begin(); it != duplicateElements.end(); ++it)
	{
	    if (it->second == 2)
        {
        	for (auto it = duplicateElements.begin(); it != duplicateElements.end(); ++it)
        	{
        		if (it->second == 3)
        		{
        			hit = true;
        			break;
        		}
        	}
        }
    }
}




void HandValue::checkFlush()
{
	std::map<int, int> duplicateElements;

    // Get the duplicate elements in vector
    findDuplicates(thisPlayersCardsSuit, duplicateElements);


    if ((duplicateElements.begin())->second >= 5)
    	hit = true;
}




void HandValue::checkStraight()
{
	std::vector<int> sortedAValue;

	// Create sorted vector of suits
	sortedAValue = thisPlayersCardsAValue;
	sort(sortedAValue.begin(), sortedAValue.end());


	// Number of 5-blocks to check in 7 cards. n should be 4 if an ace is present
	int n = 3;

	// check for Ace. If Ace is found add 14 to the end of the sortedAValue vector and increment block 5 checker to 4 blocks
	if ( std::find(sortedAValue.begin(), sortedAValue.end(), 1) != sortedAValue.end() )
	{
		sortedAValue.push_back(14);
		n += 1;
	}



	// Iterate 3 times to check each block of 5 out of the 7 cards
	for (int i = 0; i < n; ++i)
	{
		for (int j = i; j < 5+i; ++j)
		{
			if (j == (4+i))
			{
				hit = true;
				goto stop;
			}

			else if (sortedAValue[j+1] != (sortedAValue[j] + 1))
			{
				break;
			}
		}
	}

	// stop is just a thing that goto runs to to exit multiple loops. The semicolon is just a pass statement.
	stop:
		;
}




void HandValue::checkTrips()
{
	std::map<int, int> duplicateElements;

    // Get the duplicate elements in vector
    findDuplicates(thisPlayersCardsAValue, duplicateElements);


    if ((duplicateElements.begin())->second == 3)
    	hit = true;
}



void HandValue::checkTwoPair()
{
	std::map<int, int> duplicateElements;

    // Get the duplicate elements in vector
    findDuplicates(thisPlayersCardsAValue, duplicateElements);


    // check for two pairs. Don't need first statement but that function would return true if given a full house. Ofc a full house would be detected above
    if ( std::all_of( duplicateElements.begin(), duplicateElements.end(), [](std::pair<int, int> i){return i.second == 2;} ) and duplicateElements.size() == 2)
    	hit = true;
}



void HandValue::checkPair()
{
	std::map<int, int> duplicateElements;

    // Get the duplicate elements in vector
    findDuplicates(thisPlayersCardsAValue, duplicateElements);


    if ((duplicateElements.begin())->second == 2)
    	hit = true;
}














/*
 * Generic function to find duplicates elements in vector.
 * It adds the duplicate elements and their duplication count in given map countMap
 */
template <typename T>
void HandValue::findDuplicates(std::vector<T> &vecOfElements, std::map<T, int> &countMap)
{
    // Iterate over the vector and store the frequency of each element in map
    for (auto &elem : vecOfElements)
    {
        auto result = countMap.insert(std::pair<T, int>(elem, 1));
        if (result.second == false)
            result.first->second++;
    }
    // Remove the elements from Map which has 1 frequency count
    for (auto it = countMap.begin(); it != countMap.end();)
    {
        if (it->second == 1)
            it = countMap.erase(it);
        else
            it++;
    }
}

