#include "HandValue.hpp"



HandValue::HandValue(std::vector<std::vector<Card>> PlayersCards)
	: PlayersCards(PlayersCards)
{}

HandValue::~HandValue()
{}



void HandValue::getPlayerPointsAndOther(std::vector<int> &playerPoints, std::map<int, int> &playerToPoint, std::map<int, int> &typeCount)
{
	int n = PlayersCards.size();

	for (int j = 0; j < n; ++j)
	{
		// assign memory?
		for (int i = 0; i < 7; ++i)
		{
			thisPlayersCardsAValue.push_back((PlayersCards[j][i]).getActualValue());
			thisPlayersCardsSuit.push_back((PlayersCards[j][i]).getSuit());
		}
		

		// Get point for current player
		int playersHandValue = getHandValue();
		std::cout << "Player " << j << " has: " << playersHandValue << std::endl;


		// append into vector of player's points, map of player's points, and map holding count of each point type
		playerPoints.push_back(playersHandValue);
		playerToPoint.insert({j, playersHandValue});
		typeCount[playersHandValue] += 1;


		// clear vectors for next player
		thisPlayersCardsAValue.clear();
		thisPlayersCardsSuit.clear();
	}
}



int HandValue::getHandValue()
{
	// check straight flush
	if (checkStraightFlush())
		return 8;


	// check quads
	if (checkQuads())
		return 7;


	// check full house
	if (checkFullHouse())
		return 6;


	// check flush
	if (checkFlush())
		return 5;
	

	// check straight
	if (checkStraight())
		return 4;
	

	// check trips
	if (checkTrips())
		return 3;

	
	// check two pair
	if (checkTwoPair())
		return 2;


	// check pair
	if (checkPair())
		return 1;


	// highcard...
	return 0;
}






// Bug in this function where the 5 cards that make up the flush are not the same 5 cards that make the straight. Need to fix this
bool HandValue::checkStraightFlush()
{
	if (checkFlush() and checkStraight())
		return true;

	return false;
}




bool HandValue::checkQuads()
{
	std::map<int, int> duplicateElements;

    // Get the duplicate elements in vector
    findDuplicates(thisPlayersCardsAValue, duplicateElements);


    // Need to iterate as there could be other sets on the board. (other duplicates in duplicateElements)
    for (auto elem : duplicateElements)
    {
    	if (elem.second == 4)
    		return true;
	}

	return false;
}




// Bug in this function when a player has two trips, a full house is not detected.
bool HandValue::checkFullHouse()
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
        			return true;
        		}
        	}
        }
    }

    return false;
}




bool HandValue::checkFlush()
{
	std::map<int, int> duplicateElements;

    // Get the duplicate elements in vector
    findDuplicates(thisPlayersCardsSuit, duplicateElements);


	// Need to iterate as there is generally other cards of same suit on the board. (other duplicates in duplicateElements)
    for (auto elem : duplicateElements)
    {
    	if (elem.second >= 5)
    		return true;
	}

	return false;
}



// There is currently a bug with checking straight where a player has a straight but also a pair which is within the straight. For example, player has 57 and board has 6789A. The bug means a pair of 7s will be found and not a straight as the extra 7 gets in the way of the block of 5 ascending cards. Need to remove duplicates. This may mean iterating fewer than 3 times as no longer 7 cards to check from
bool HandValue::checkStraight()
{
	std::vector<int> sortedAValue;

	// Create sorted vector of card values
	sortedAValue = thisPlayersCardsAValue;






	// Bug Fix on pairs and trips within the straight
	std::map<int, int> duplicateElements;

	// Get the duplicate elements in vector
	findDuplicates(thisPlayersCardsAValue, duplicateElements);

	int numSets = duplicateElements.size();

	// check for pairs
	if ( std::all_of( duplicateElements.begin(), duplicateElements.end(), [](std::pair<int, int> i){return i.second == 2;} ) and duplicateElements.size() >= 1)
    {
    	// remove duplicate pair elements from player's cards
    	for (auto &elem : duplicateElements)
    	{
    		// remove 1 instance of the pair duplicate element
    		auto it = find(sortedAValue.begin(), sortedAValue.end(), elem.first);
    		sortedAValue.erase(it);
    	}
    }

    // check for trips
    for (auto &elem : duplicateElements)
    {
    	if (elem.second == 3)
    	{
    		// remove 1 instance of the trips duplicate element 2 times
    		auto it = find(sortedAValue.begin(), sortedAValue.end(), elem.first);
    		sortedAValue.erase(it);

    		it = find(sortedAValue.begin(), sortedAValue.end(), elem.first);
    		sortedAValue.erase(it);

    		// incremenet numSets by 1
    		numSets += 1;
		}
	}
	// Bug fix on sets being present ends here	




	// Number of 5-blocks to check in 7 cards. n should be 4 if an ace is present. lower n by numSets 
	int n = 3;
	n -= numSets;

	// check for Ace. If Ace is found add 14 to the end of the sortedAValue vector and increment block 5 checker to 4 blocks
	if ( std::find(sortedAValue.begin(), sortedAValue.end(), 1) != sortedAValue.end() )
	{
		sortedAValue.push_back(14);
		n += 1;
	}


    // now actually sort the vector in decending order (this way highest straight for a player is detected)
	sort(sortedAValue.begin(), sortedAValue.end(), std::greater<int>());


	// Iterate 3 times to check each block of 5 out of the 7 cards
	for (int i = 0; i < n; ++i)
	{
		for (int j = i; j < 5+i; ++j)
		{
			if (j == (4+i))
			{
				return true;
			}

			else if (sortedAValue[j+1] != (sortedAValue[j] - 1))
			{
				break;
			}
		}
	}

	return false;
}




bool HandValue::checkTrips()
{
	std::map<int, int> duplicateElements;

    // Get the duplicate elements in vector
    findDuplicates(thisPlayersCardsAValue, duplicateElements);


    // Need to iterate as there could be other sets on the board. (other duplicates in duplicateElements)
    for (auto elem : duplicateElements)
    {
    	if (elem.second == 3)
    		return true;
	}

	return false;
}



bool HandValue::checkTwoPair()
{
	std::map<int, int> duplicateElements;

    // Get the duplicate elements in vector
    findDuplicates(thisPlayersCardsAValue, duplicateElements);


    // check for two pairs. Don't need first statement but that function would return true if given a full house. Ofc a full house would be detected above. Greater than or equal sign is in case 3 sets of pairs come down lol
    if ( std::all_of( duplicateElements.begin(), duplicateElements.end(), [](std::pair<int, int> i){return i.second == 2;} ) and duplicateElements.size() >= 2)
    	return true;

    return false;
}



bool HandValue::checkPair()
{
	std::map<int, int> duplicateElements;

    // Get the duplicate elements in vector
    findDuplicates(thisPlayersCardsAValue, duplicateElements);


    // No need to iterate in this one as we only want to detect 1 pair. If there were more then we would get two pair
    if ((duplicateElements.begin())->second == 2)
    	return true;

    return false;
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

