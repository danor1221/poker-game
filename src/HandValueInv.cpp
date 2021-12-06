#include "HandValueInv.hpp"


void HVI::InvestigateDraw(std::map<int, int> &playerToPoint, int point, std::vector<int> &winningPlayer, int num, std::vector<std::vector<Card>> &PlayersCards)
{
	std::vector<int> drawingPlayers;

	for (auto &elem : playerToPoint)
	{
		if (elem.second == point)
			drawingPlayers.push_back(elem.first);
	}


	for (std::size_t i = 0; i < drawingPlayers.size(); ++i)
		std::cout << drawingPlayers[i] << std::endl;



	// Get the cards for the necessary players
	std::vector<std::vector<int>> drawPlayersCardsAValue;
	std::vector<std::vector<int>> drawPlayersCardsSuit;


	for (int player : drawingPlayers)
	{
		std::vector<int> thisPlayersCardsAValue;
		std::vector<int> thisPlayersCardsSuit;

		// assign memory?
		for (int i = 0; i < 7; ++i)
		{
			thisPlayersCardsAValue.push_back((PlayersCards[player][i]).getActualValue());
			thisPlayersCardsSuit.push_back((PlayersCards[player][i]).getSuit());
		}

		drawPlayersCardsAValue.push_back(thisPlayersCardsAValue);
		drawPlayersCardsSuit.push_back(thisPlayersCardsSuit);
	}




	switch (point)
	{
		case 0:
			std::cout << "compare 'high cards' ughh" << std::endl;
			break;
		case 1:
			std::cout << "compare pair" << std::endl;
			break;
		case 2:
			std::cout << "compare two pair" << std::endl;
			break;
		case 3:
			std::cout << "compare trips" << std::endl;
			break;
		case 4:
			std::cout << "compare straight" << std::endl;
			break;
		case 5:
			std::cout << "compare flush" << std::endl;
			break;
		case 6:
			std::cout << "compare full house" << std::endl;
			break;
		case 7:
			std::cout << "compare quads" << std::endl;
			break;
		case 8:
			std::cout << "compare straight flush" << std::endl;
			break;
	}
}