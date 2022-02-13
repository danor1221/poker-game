#include "HandValueInv.hpp"



HVI::HVI(std::map<int, int> playerToPoint, int point, int num, std::vector<std::vector<Card>> PlayersCards)
	: playerToPoint(playerToPoint), point(point), num(num), PlayersCards(PlayersCards)
{}

HVI::~HVI()
{}


void HVI::setDrawingPlayerCards(std::vector<int> &drawPlayers)
{
	for (int player : drawPlayers)
	{
		std::vector<int> thisPlayersCardsValue;
		std::vector<int> thisPlayersCardsAValue;
		std::vector<int> thisPlayersCardsSuit;

		// assign memory?
		for (int i = 0; i < 7; ++i)
		{
			thisPlayersCardsValue.push_back((PlayersCards[player][i]).getcardValue());
			thisPlayersCardsAValue.push_back((PlayersCards[player][i]).getActualValue());
			thisPlayersCardsSuit.push_back((PlayersCards[player][i]).getSuit());
		}

		drawPlayersCardsValue.push_back(thisPlayersCardsValue);
		drawPlayersCardsAValue.push_back(thisPlayersCardsAValue);
		drawPlayersCardsSuit.push_back(thisPlayersCardsSuit);
	}
}




void HVI::InvestigateDraw()
{
	for (auto elem : playerToPoint)
	{
		if (elem.second == point)
			drawingPlayers.push_back(elem.first);
	}


	for (std::size_t i = 0; i < drawingPlayers.size(); ++i)
		std::cout << drawingPlayers[i] << std::endl;




	setDrawingPlayerCards(drawingPlayers);
	




	switch (point)
	{
		case 0:
			std::cout << "compare 'high cards'" << std::endl;
			{
			std::vector<std::vector<int>> playersHandCards = vectorOfPlayersHandCards();
			compareHighCard(playersHandCards);
			}
			break;
		case 1:
			std::cout << "compare pair" << std::endl;
			comparePair();
			break;
		case 2:
			std::cout << "compare two pair" << std::endl;
			compareTwoPair();
			break;
		case 3:
			std::cout << "compare trips" << std::endl;
			compareTrips();
			break;
		case 4:
			std::cout << "compare straight" << std::endl;
			compareStraight();
			break;
		case 5:
			std::cout << "compare flush" << std::endl;
			compareFlush();
			break;
		case 6:
			std::cout << "compare full house" << std::endl;
			compareFullHouse();
			break;
		case 7:
			std::cout << "compare quads" << std::endl;
			compareQuads();
			break;
		case 8:
			std::cout << "compare straight flush" << std::endl;
			compareStraight();
			break;
	}
}



std::vector<int> HVI::getWinningPlayer()
{
	return winningPlayer;
}






// This function compares and obtains the highest card out of the player's two cards
void HVI::compareHighCard(std::vector<std::vector<int>> handCards)
{
	int highestCard = -1;
	int plywithHC = -1;

	std::cout << "comparing the high card" << std::endl;


	int numDrw = handCards.size();
	int i = 0;


	for (int drwPly : drawingPlayers)
	{
		std::vector<int>::iterator highCard = std::max_element((handCards[i]).begin(), (handCards[i]).end());
		if (*highCard > highestCard)
		{
			highestCard = *highCard;
			plywithHC = drwPly;
		}
		else if (*highCard == highestCard)
			plywithHC = -1;
		
		i++;
	}



	// winner found
	if (plywithHC != -1)
		winningPlayer.push_back(plywithHC);
	


	// check kicker. This only occurs if highest card of each player is the same
	else
		compareKicker(handCards);
	
}





void HVI::compareKicker(std::vector<std::vector<int>> handCards)
{
	std::cout << "compareKicker() has been called whoop" << std::endl;


	// solve kicker by summing elements of each vector
	int sum1 = 0;
	int sum2 = 0;

	std::vector<int> hand1 = handCards[0];
	std::vector<int> hand2 = handCards[1];

	for (int i = 0; i < 2; ++i)
	{
		sum1 += hand1[i];
		sum2 += hand2[i];
	}

	std::cout << "sum1 is: " << sum1 << std::endl;
	std::cout << "sum2 is: " << sum2 << std::endl;

	if (sum1 > sum2)
	{
		winningPlayer.push_back(drawingPlayers[0]);
		std::cout << "sum1 larger" << std::endl;
	}
	else if (sum1 < sum2)
	{
		winningPlayer.push_back(drawingPlayers[1]);
		std::cout << "sum2 larger" << std::endl;
	}

	// A true draw
	else if (sum2 == sum1)
	{
		winningPlayer.push_back(drawingPlayers[0]);
		winningPlayer.push_back(drawingPlayers[1]);
	}


}






void HVI::comparePair()
{
	// Stage 1
	// check if pair is on board
	if (stageOne(2))
		return;






   	// Stage 2
   	// Find value of each pair. Here we know the pair is not on the board so each player must be checked as they may have different value pairs
   	// Start by getting the player to pair values
   	std::map<int, int> playerToPairValues;
	if (stageTwo(playerToPairValues, 2))
		return;





	// Stage 3
	// No player has a distinct higher pair meaning two players have the same top pair. Solve this by first checking if the two top pairs are in each player's hand, if so, hand is a draw. If each player has 1 card in hand and 1 on board, need to check each player's kicker. Winner is player with higher kicker. If kicker's are the same, hand is a draw.
	else
		stageThree(playerToPairValues, 2);
}













void HVI::compareTwoPair()
{
	// This function is finished and has been fully tested

	std::map<int, int> playerToTopPairValues;
	std::map<int, int> playerToBottomPairValues;


	setTopAndBottomPair(playerToTopPairValues, playerToBottomPairValues);


	bool drawHC = false;
	int WPlayer = maxKeyInMap(playerToTopPairValues, drawHC);


	if (!drawHC)
	{
		winningPlayer.push_back(WPlayer);
		std::cout << "Winner is: " << WPlayer << std::endl;
		return;
	}
	else
	{
		// check lower pair
		drawHC = false;
		WPlayer = maxKeyInMap(playerToBottomPairValues, drawHC);
		
		if (!drawHC)
		{
			winningPlayer.push_back(WPlayer);
			std::cout << "Winner is: " << WPlayer << std::endl;
			return;
		}
		else
		{
			// In here if both pairs are the same
			std::cout << "pairs are the same " << std::endl;
			




			// set drawingPlayers to only the highest pairs (get rid of any players with lower value pairs)
			drawingPlayers = maxKeysInMap(playerToTopPairValues);

			// Reset drawPlayersCards
			drawPlayersCardsAValue.clear();
   			drawPlayersCardsSuit.clear();
   			setDrawingPlayerCards(drawingPlayers);

   			// now reset playerToTopPairValues and playerToBottomPairValue to get rid of any other players with two pair less than our top players
   			playerToTopPairValues.clear();
   			playerToBottomPairValues.clear();
   			setTopAndBottomPair(playerToTopPairValues, playerToBottomPairValues);

   			// Above lines were all necessary for statements in the below if statement






			// SCENARIO 1
			// Check if both pairs lie on the board, if so, compare High card

			std::vector<int> boardCards;
			boardCards = std::vector<int>(drawPlayersCardsAValue[0].begin() + 2, drawPlayersCardsAValue[0].end());
			if ( checkPairExistence( boardCards, playerToTopPairValues.begin()->second ) and checkPairExistence( boardCards, playerToBottomPairValues.begin()->second ))
			{
				std::cout << "both pairs are on the board!!!" << std::endl; 
				std::vector<std::vector<int>> playersHandCards = vectorOfPlayersHandCards();
				compareHighCard(playersHandCards);
				return;
			}







			// SCENARIO 2
			// Check if 1 pair lies on board and 1 pair is split, if so, check kicker

			else if ( XOR( checkPairExistence( boardCards, playerToTopPairValues.begin()->second ), checkPairExistence( boardCards, playerToBottomPairValues.begin()->second ) ) )
			{
				std::cout << "1 pair is split and the other is on the board!!!!" << std::endl;
				std::vector<std::vector<int>> playersHandCards = vectorOfPlayersHandCards();
				compareKicker(playersHandCards);
				return;
			}







			// SCENARIO 3
			// Check if both pairs are split (no pairs on the board), if so, game is a draw

			else if ( !checkPairExistence( boardCards, playerToTopPairValues.begin()->second ) and !checkPairExistence( boardCards, playerToBottomPairValues.begin()->second ))
			{
				std::cout << "both pairs are split!!!" << std::endl;
				// game is a draw
				winningPlayer = drawingPlayers;
				return;
			}
		}
	}
}












void HVI::compareTrips()
{
	// Stage 1
	// Check if a triple lies on the board 
	if (stageOne(3))
		return;






	// Stage 2. Find value of the trips that each player holds
	std::map<int, int> playerToTripValues;
	if (stageTwo(playerToTripValues, 3))
		return;






	// Stage 3
	// No player has a distinct higher triple meaning two players have the same top triple. Solve this by first checking if the two top trips have two cards in each player's hand, if so, hand is a draw. If each player has 1 card in hand and 2 on board, need to check each player's kicker. Winner is player with higher kicker. If kicker's are the same, hand is a draw.
	else
		stageThree(playerToTripValues, 3);
}









void HVI::compareStraight()
{
	// check highest card in straight


	int highestStrCard = -1;


	for (int i = 0; i < num; ++i)
	{
		std::vector<int> straightCards = getStraightCards(drawPlayersCardsAValue[i]);

		for (int card : straightCards)
			std::cout << card << " ";

		std::cout<< "" << std::endl;

		if (straightCards[0] > highestStrCard)
		{
			highestStrCard = straightCards[0];
			winningPlayer.clear();
			winningPlayer.push_back(drawingPlayers[i]);
		}
		else if (straightCards[0] == highestStrCard)
		{
			winningPlayer.push_back(drawingPlayers[i]);
		}
	}
}








void HVI::compareFlush()
{
	// check highest card in flush. Has to be the highest card that the Player holds. Ie first two

	int highestFluCard = -1;

	for (int i = 0; i < num; ++i)
	{
		int suit = -1;
		std::map<int, int> duplicateElements;
		std::vector<int> sortedCards;

    	// Get the duplicate elements in vector
    	findDuplicates(drawPlayersCardsSuit[i], duplicateElements);


		// Need to iterate as there is generally other cards of same suit on the board. (other duplicates in duplicateElements)
    	for (auto elem : duplicateElements)
    	{
    		if (elem.second >= 5)
    			suit = elem.first;
		}

		sortedCards = drawPlayersCardsValue[i];
		sort(sortedCards.begin(), sortedCards.end());


		int lowVal = -1;

		if (suit == 1)
			lowVal = 0;
		
		else if (suit == 2)
			lowVal = 13;
		
		else if (suit == 3)
			lowVal = 26;

		else if (suit == 4)
			lowVal = 39;


		for (int card : sortedCards)
			std::cout << card << " ";

		std::cout << "" << std::endl;



		for (int j = 0; j < 7; ++j)
		{
			sortedCards[j] -= lowVal;
		}


		for (int card : sortedCards)
			std::cout << card << " ";

		std::cout << "" << std::endl;
		
		std::vector<int>::iterator low, high, topFlush;
		
		low = std::lower_bound(sortedCards.begin(), sortedCards.end(), 0);
		int lowNum = *low;
		high = std::lower_bound(sortedCards.begin(), sortedCards.end(), 14);
		int highNum = *high;

		std::cout << "have found lowNum and highNum: " << lowNum << " " << highNum << std::endl;


		topFlush = std::max_element( low, high );

		int topFluCard = *topFlush;


		// quickly check for an ace by searching for a 1. If a 1 is present, set topFluCard to 14. The nuts.
		if ( std::find(sortedCards.begin(), sortedCards.end(), 1) != sortedCards.end())
    		topFluCard = 14;


		std::cout << "topFluCard is: " << topFluCard << std::endl;

		if (topFluCard > highestFluCard)
		{
			highestFluCard = topFluCard;
			winningPlayer.clear();
			winningPlayer.push_back(drawingPlayers[i]);
		}
		else if (topFluCard == highestFluCard)
		{
			winningPlayer.push_back(drawingPlayers[i]);
		}


	}
}









void HVI::compareFullHouse()
{
	// Search for highest full house by first checking higher trip and then higher pair and draw if all the same.
	std::map<int, int> playerToTripValues;
	std::map<int, int> playerToPairValues;


	for (int i = 0; i < num; ++i)
	{
		std::cout << "round " << i << std::endl;
		std::map<int, int> duplicateElements;

    	// Get the duplicate elements in vector of each players cards in turn
    	findDuplicates(drawPlayersCardsAValue[i], duplicateElements);

    	for (auto elem : duplicateElements)
    	{
    		if (elem.second == 2)
    			playerToPairValues.insert({drawingPlayers[i], elem.first});

    		else if (elem.second == 3)
    			playerToTripValues.insert({drawingPlayers[i], elem.first});
    	}
    }





	bool drawHC = false;
	int WPlayer = maxKeyInMap(playerToTripValues, drawHC);


	if (!drawHC)
	{
		winningPlayer.push_back(WPlayer);
		std::cout << "Winner is: " << WPlayer << std::endl;
		return;
	}
	else
	{
		// check pair
		drawHC = false;
		WPlayer = maxKeyInMap(playerToPairValues, drawHC);
		
		if (!drawHC)
		{
			winningPlayer.push_back(WPlayer);
			std::cout << "Winner is: " << WPlayer << std::endl;
			return;
		}
		else
		{
			// Both players have the same full house hence is a draw

			for (int i = 0; i < num; ++i)
				winningPlayer.push_back(drawingPlayers[i]);
		}
	}
}









void HVI::compareQuads()
{
	// Start by checking if the quads lie on the board. If they do then call compareHighCard() to find winner.


	// Stage 1
	// Check if quads lie on the board 
	if (stageOne(4))
		return;




   	// Stage 2. Find value of the quads that each player holds. This is it for this function as for players to have the same quads, they must exist on the board. Hence, there is no stage 3.
	std::map<int, int> playerToQuadValues;
	if (stageTwo(playerToQuadValues, 4))
		return;
}






void HVI::compareStraightFlush()
{
	// Just call compareStraight() as that will do it. Essentially makes this function redundant but we'll keep it for the lols
	compareStraight();
}
















bool HVI::stageOne(int len)
{
	std::vector<int> boardCards;
	boardCards = std::vector<int>(drawPlayersCardsAValue[0].begin() + 2, drawPlayersCardsAValue[0].end());

   	if (checkIfSpecificSetExist(boardCards, len))
   	{
   		// set of length len is on the board
   		std::cout << "set of length " << len << " is on the board" << std::endl;

   		std::vector<std::vector<int>> playersHandCards = vectorOfPlayersHandCards();

   		compareHighCard(playersHandCards);
		return true;
   	}

   	return false;
}




bool HVI::stageTwo(std::map<int, int> &playerToSetValues, int len)
{
	for (int i = 0; i < num; ++i)
	{
		std::map<int, int> duplicateElements;

		// change aces to be highest
		convertAce(drawPlayersCardsAValue[i]);


    	// Get the duplicate elements in vector of each players cards in turn
    	findDuplicates(drawPlayersCardsAValue[i], duplicateElements);


    	// These temporary variables allow us to get the quads as there may be other sets on the board. Use of maxKeysInMap() works to get highest set length
    	std::vector<int> tmp = maxKeysInMap(duplicateElements);

    	playerToSetValues.insert({drawingPlayers[i], tmp[0]});
	}


	// Now check if a player has a distinct higher pair
	bool drawHC = false;
	int WPlayer = maxKeyInMap(playerToSetValues, drawHC);

	if (!drawHC)
	{
		winningPlayer.push_back(WPlayer);
		std::cout << "Winner is: " << WPlayer << std::endl;
		return true;
	}

	return false;
}



// only called for comparePair() and compareTrips()
void HVI::stageThree(std::map<int, int> &playerToSetValues, int len)
{

	std::string s;

	if (len == 2)
		s = "pair is in player's hand";
	else if (len == 3)
		s = "2 of the trip cards are in player's hand";




	// set drawingPlayers to only the highest pairs (get rid of any players with lower value pairs)
	// set drawingPlayers to only the highest trips (get rid of any players with lower value pairs)
	drawingPlayers = maxKeysInMap(playerToSetValues);

	// Also need to reset drawPlayersCards
	drawPlayersCardsAValue.clear();
   	drawPlayersCardsSuit.clear();
   	setDrawingPlayerCards(drawingPlayers);




   	// check if pair is in player's hands
	// check if 2 of the trips cards are in player's hand
	std::vector<int> handCards;

	// Use first element in drawPlayersCardsAValue as either both players have pair in their hands or 1 hand 1 board. It cannot be one of either option
	// Use first element in drawPlayersCardsAValue as either both players have 2 hand 1 board or 1 hand 2 board. It cannot be one of either option
	handCards = std::vector<int>(drawPlayersCardsAValue[0].begin(), drawPlayersCardsAValue[0].begin() + 2);



	// check if pair exists in hand
	// check if 2 of the trips cards exist in hand. Just realised this is impossible. Cannot have 2+ players with same trips with 2 hand 1 board.
   	if (checkIfSpecificSetExist(handCards, 2))
   	{
   		// hand is a draw
   		std::cout << s << std::endl;
   		winningPlayer = drawingPlayers;
   		return;
   	}


   	else
   	{
   		// pair is split between hand and board for both players
   		// triple is split 1 hand 2 board
   		std::vector<std::vector<int>> playersHandCards = vectorOfPlayersHandCards();

   		for (auto &elem : playersHandCards)
   			for (auto &elem2 : elem)
   				std::cout << elem2 << std::endl;

   		compareKicker(playersHandCards);
   	}
}










/*
 * Generic function to find duplicates elements in vector.
 * It adds the duplicate elements and their duplication count in given map countMap
 */
template <typename T>
void HVI::findDuplicates(std::vector<T> &vecOfElements, std::map<T, int> &countMap)
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


// MAKE THIS FUNCTION REDUNDANT AS IT ONLY WORKS FOR PAIRS. REPLACE WITH CONVERTACE() FUNCTION BELOW INSTEAD
void HVI::changeAce(std::map<int, int> &duplicates)
{
	// change a pair of aces to have value 14
    std::map<int, int>::iterator it;
    it = duplicates.find(1);
    if (it != duplicates.end())
    {
    	duplicates.erase(1);
    	duplicates.insert({14, 2});
    }
}




// funtion takes a map decides if there is a unique maximum key value in the map. Returns -1 if not unique and sets draw = true
int HVI::maxKeyInMap(std::map<int, int> &inpMap, bool &draw)
{
	int largest = -1;
	int WPlayer = -1;


	for (auto elem : inpMap)
	{
		std::cout << elem.first << "::" << elem.second << std::endl;

		if (elem.second > largest)
		{
			largest = elem.second;
			WPlayer = elem.first;

			draw = false;
		}
		else if (elem.second == largest)
		{
			draw = true;
		}
	}

	return WPlayer;
}




std::vector<int> HVI::maxKeysInMap(std::map<int, int> &inpMap)
{
	int largest = -1;
	std::vector<int> maxKeys;


	for (auto elem : inpMap)
	{
		if (elem.second > largest)
		{
			largest = elem.second;
			maxKeys.clear();
			maxKeys.push_back(elem.first);
		}
		else if (elem.second == largest)
			maxKeys.push_back(elem.first);
	}

	return maxKeys;
}





void HVI::convertAce(std::vector<int> &inpVec)
{
	std::replace (inpVec.begin(), inpVec.end(), 1, 14);
}



std::vector<std::vector<int>> HVI::vectorOfPlayersHandCards()
{
	// reset drawPlayersCards
	drawPlayersCardsAValue.clear();
   	drawPlayersCardsSuit.clear();
   	setDrawingPlayerCards(drawingPlayers);

   	std::vector<std::vector<int>> playersHandCards;

   	for (int j = 0; j < num; ++j)
   	{
   		std::vector<int> tmp;
   		tmp = std::vector<int>(drawPlayersCardsAValue[j].begin(), drawPlayersCardsAValue[j].begin() + 2);
   		convertAce(tmp);
   		playersHandCards.push_back(tmp);
   	}

   	return playersHandCards;
}





// Takes an input vector and checks if a set of any length exists within the input vector. REDUNDANT FUNCTION
bool HVI::checkIfSetExists(std::vector<int> &inpVec)
{
	std::map<int, int> duplicateElements;

	// Get the duplicate elements of the board cards
   	findDuplicates(inpVec, duplicateElements);

   	int sizeMap = duplicateElements.size();


   	if (sizeMap == 1)
   		return true;
   	else
   		return false;
}



// Takes an input vector and length and checks if a set of that length exists within the input vector
bool HVI::checkIfSpecificSetExist(std::vector<int> &inpVec, int len)
{
	std::map<int, int> duplicateElements;

	// Get the duplicate elements of the board cards
   	findDuplicates(inpVec, duplicateElements);


   	for (auto elem : duplicateElements)
   	{
   		if (elem.second == len)
   			return true;
   	}

   	return false;
}






// checks for the existence of a specific pair (specified by value) in a specific vector (specified by inpVec)
bool HVI::checkPairExistence(std::vector<int> inpVec, int value)
{
	std::map<int, int> duplicateElements;

	// Get the duplicate elements of the inpVec
	findDuplicates(inpVec, duplicateElements);


	// have found the pair in question
	if (duplicateElements.find(value) != duplicateElements.end())
		return true;
	
	else
		return false;
}






void HVI::setTopAndBottomPair(std::map<int, int> &playerToTopPairValues, std::map<int, int> &playerToBottomPairValues)
{
	for (int i = 0; i < num; ++i)
	{
		std::cout << "round " << i << std::endl;
		std::map<int, int> duplicateElements;

    	// Get the duplicate elements in vector of each players cards in turn
    	findDuplicates(drawPlayersCardsAValue[i], duplicateElements);

    	int topPair = -1;
    	int bottomPair = -2;


    	// change a pair of aces to have value 14. Player cannot have more than 1 pair of aces
    	changeAce(duplicateElements); // could probably change to the convertAce() functions


    	// get max key in duplicate elements
    	topPair = (duplicateElements.rbegin())->first;
    	bottomPair = topPair;

    	std::cout << "top pair is: " << topPair << std::endl;
    	std::cout << "bottom pair is: " << bottomPair << std::endl;


    	// insert all duplicates into that 
    	for (auto &elem : duplicateElements)
    	{
    		std::cout << "iterate here, elem.first: " << elem.first << std::endl;
    		if (elem.first < topPair)
    		{
    			bottomPair = elem.first;
    			std::cout << "bottom pair is: " << bottomPair << std::endl;
    		}
    	}

    	// append to maps
    	playerToTopPairValues.insert({drawingPlayers[i], topPair});
    	playerToBottomPairValues.insert({drawingPlayers[i], bottomPair});
	}
}




bool HVI::XOR(bool a, bool b)
{
	return ((a + b) % 2);
}






std::vector<int> HVI::getStraightCards(std::vector<int> thisPlayersCardsAValue)
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


	int start;
	int end;


	// Iterate 3 times to check each block of 5 out of the 7 cards
	for (int i = 0; i < n; ++i)
	{
		for (int j = i; j < 5+i; ++j)
		{
			if (j == (4+i))
			{
				start = i;
				end = j;
			}

			else if (sortedAValue[j+1] != (sortedAValue[j] - 1))
			{
				break;
			}
		}
	}


	std::vector<int>::const_iterator st = sortedAValue.begin() + start;
	std::vector<int>::const_iterator en = sortedAValue.begin() + end + 1;
	std::vector<int> straightCards(st, en);


	return straightCards;
}