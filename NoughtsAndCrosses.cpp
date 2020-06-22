#include <iostream>
#include "Player.h"
#include "Game.h"
#include <string>
#include <algorithm>
#include <ctime>
using namespace std;

bool isNullOrWhiteSpace(std::string const& str);

bool matchWords(string s1, string s2);

string ConvertSectoDay(int n);

int main()
{
	long startedTime = time(0);
	std::cout << "Choose a name for player 1\n";
	string player1Name;
	cin >> player1Name;
	while (isNullOrWhiteSpace(player1Name))
	{
		std::cout << "Please choose a non-empty name\n";
		cin >> player1Name;
	}

	std::cout << "Choose a name for Player 2\n";
	string player2Name;
	cin >> player2Name;
	while (isNullOrWhiteSpace(player2Name))
	{
		std::cout << "Please choose a non-empty name\n";
		cin >> player2Name;
	}

	Player* player1 = new Player(player1Name);
	Player* player2 = new Player(player2Name);
	Player* chosenFirstPlayer;
	Player* secondPlayer;

	std::cout << "Please choose who plays first, " << player1->GetName() << " or " << player2->GetName() << ": \n";

	string firstPlayer;
	cin >> firstPlayer;
	while (true)
	{
		if (matchWords(firstPlayer, player1->GetName()))
		{
			chosenFirstPlayer = player1;
			secondPlayer = player2;
			break;
		}

		if (matchWords(firstPlayer, player2->GetName()))
		{
			chosenFirstPlayer = player2;
			secondPlayer = player1;
			break;
		}

		std::cout << "Invalid Name! ";
		std::cout << "Please choose who plays first, " << player1->GetName() << " or " << player2->GetName() << ": \n";
		cin >> firstPlayer;
	}

	Game g;
	std::cout << "First player is " << chosenFirstPlayer->GetName() << ",\nPlease choose your symbol to start, " << g.GiveNoughtValue() << " or " << g.GiveCrossValue() << "\n";

	string symbol;
	while (true)
	{
		cin >> symbol;
		if (g.IsSymbolValid(symbol))
			break;
		std::cout << "Invalid Symbol\nPlease chose your symbol " << g.GiveNoughtValue() << " or " << g.GiveCrossValue() << "\n";
	}


	Game* game = new Game(chosenFirstPlayer, secondPlayer, symbol[0]);
	std::cout << "Chosen symbol: " << chosenFirstPlayer->GetSymbol() << "\n";


	//std::cout << "\n\n\n\n\n\n\n\n\n";
	std::cout << game->Presentation() << "\n";



	while (true)
	{
		while (true)
		{
			std::cout << game->PrintBoard();
			if (game->IsFinished())
			{
				std::cout << "Game finished with a Draw\n";
				std::cout << "Player " << game->GiveCurrentPlayer()->GetName() << ": " << game->GiveCurrentPlayer()->GetVictories() << " victories\n";
				std::cout << "Player " << game->GiveNextOrPreviousPlayer()->GetName() << ": " << game->GiveNextOrPreviousPlayer()->GetVictories() << " victories\n";
				break;
			}

			std::cout << game->GiveCurrentPlayer()->GetName() << " what is your move?\n";
			string chosenPosition;
			cin >> chosenPosition;

			int position;
			try
			{
				position = std::stoi(chosenPosition);
			}
			catch (std::invalid_argument const& e)
			{
				std::cout << "Please enter a numerical value to choose a position" << '\n';
				continue;
			}
			catch (std::out_of_range const& e)
			{
				std::cout << "Please enter a numerical value from 1 to 9 to choose a position" << '\n';
				continue;
			}

			if (game->IsPositionEmptyAndValid(position))
			{
				if (!game->MoveAndCheckWin(position))
					continue;
				game->GiveCurrentPlayer()->SetVictories(game->GiveCurrentPlayer()->GetVictories() + 1);
				std::cout << game->PrintBoard();
				std::cout << "Player " << game->GiveCurrentPlayer()->GetName() << " won!!!\n";
				std::cout << "Player " << game->GiveCurrentPlayer()->GetName() << ": " << game->GiveCurrentPlayer()->GetVictories() << " victories\n";
				std::cout << "Player " << game->GiveNextOrPreviousPlayer()->GetName() << ": " << game->GiveNextOrPreviousPlayer()->GetVictories() << " victories\n";
				break;
			}
			else
			{
				std::cout << "Position not empty or out of range" << '\n';
			}
		}

		std::cout << "Play Again Y/N ?" << '\n';

		string playAgain;
		cin >> playAgain;

		while (!matchWords(playAgain, "Y") && !matchWords(playAgain, "N"))
		{
			std::cout << "Please press Y to play again, or N to exit" << '\n';
			cin >> playAgain;
		}

		if (playAgain == "Y" || playAgain == "y")
		{
			std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nOk, let's play again" << '\n';
			game->StartNewGame(game);
			continue;
		}

		std::cout << "\nGame Finished" << '\n';

		std::cout << "Player " << game->GiveCurrentPlayer()->GetName() << ": " << game->GiveCurrentPlayer()->GetVictories() << " victories\n";
		std::cout << "Player " << game->GiveNextOrPreviousPlayer()->GetName() << ": " << game->GiveNextOrPreviousPlayer()->GetVictories() << " victories\n";

		std::cout << "Total time played: " << ConvertSectoDay(time(0) - startedTime) << '\n';
		break;
	}
	delete player1;
	delete player2;
	delete game;
}


bool isNullOrWhiteSpace(std::string const& str)
{
	return std::find_if(
		str.begin(),
		str.end(),
		[](unsigned char ch) { return !isspace(ch); })
		== str.end();
}

bool matchWords(string s1, string s2) {
	transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
	transform(s2.begin(), s2.end(), s2.begin(), ::tolower);
	if (s1.compare(s2) == 0)
		return true;
	return false;
}

string ConvertSectoDay(int n)
{
	int day = n / (24 * 3600);

	n = n % (24 * 3600);
	int hour = n / 3600;

	n %= 3600;
	int minutes = n / 60;

	n %= 60;
	int seconds = n;

	return to_string(day) + " " + "days " + to_string(hour) + " " + "hours " + to_string(minutes) + " " + "minutes " + to_string(seconds) + " " + "seconds ";
}
