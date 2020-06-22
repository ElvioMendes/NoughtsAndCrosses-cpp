#include "Game.h"
#include <iostream>
#include <string>
#include <algorithm>
#include "Player.h"
using namespace std;

Game::Game() {
}

Game::Game(Player* chosenFirstPlayer, Player* secondPlayer, char startingSymbol) {

    _currentPlayer = chosenFirstPlayer;
    _nextOrPreviousPlayer = secondPlayer;

    if (toupper(startingSymbol) == NoughtValue)
    {
        chosenFirstPlayer->SetSymbol(NoughtValue);
        secondPlayer->SetSymbol(CrossValue);
    }
    else
    {
        chosenFirstPlayer->SetSymbol(CrossValue);
        secondPlayer->SetSymbol(NoughtValue);
    }

    InitializeBoardPositions(this);
}

void Game::InitializeBoardPositions(Game* thisGame)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            thisGame->_boardPositions[i][j] = thisGame->EmptyValue;
        }
    }
}

string Game::PrintBoard()
{
    string boardLines = "";

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            boardLines += _boardPositions[i][j];
        }
        boardLines += "\n";
    }

    return "\nBoard:\n" + boardLines + "\n";
}

string Game::Presentation()
{
    return R"(
The Board is composed of 9 positions in the format below :

    1 | 2 | 3
    4 | 5 | 6
    7 | 8 | 9

In order to chose your move, please adopt this numbering convention and choose a free position.
        )";
}

bool Game::MoveAndCheckWin(int position)
{
    char currentPlayerSymbol = (char)_currentPlayer->GetSymbol()[0];
    _boardPositions[BoardLineIndex(position)][BoardColumnIndex(position)] = currentPlayerSymbol;

    bool completesALine = (
        _boardPositions[0][0] == currentPlayerSymbol && _boardPositions[0][1] == currentPlayerSymbol && _boardPositions[0][2] == currentPlayerSymbol ||
        _boardPositions[2][0] == currentPlayerSymbol && _boardPositions[2][1] == currentPlayerSymbol && _boardPositions[2][2] == currentPlayerSymbol ||
        _boardPositions[0][0] == currentPlayerSymbol && _boardPositions[1][0] == currentPlayerSymbol && _boardPositions[2][0] == currentPlayerSymbol ||
        _boardPositions[1][0] == currentPlayerSymbol && _boardPositions[1][1] == currentPlayerSymbol && _boardPositions[1][2] == currentPlayerSymbol ||
        _boardPositions[0][1] == currentPlayerSymbol && _boardPositions[1][1] == currentPlayerSymbol && _boardPositions[2][1] == currentPlayerSymbol ||
        _boardPositions[0][2] == currentPlayerSymbol && _boardPositions[1][2] == currentPlayerSymbol && _boardPositions[2][2] == currentPlayerSymbol ||
        _boardPositions[0][0] == currentPlayerSymbol && _boardPositions[1][1] == currentPlayerSymbol && _boardPositions[2][2] == currentPlayerSymbol ||
        _boardPositions[2][0] == currentPlayerSymbol && _boardPositions[1][1] == currentPlayerSymbol && _boardPositions[0][2] == currentPlayerSymbol);

    if (completesALine)
        return true;

    NextPlayer();
    return false;
}

void Game::StartNewGame(Game* thisGame)
{
    NextPlayer();
    InitializeBoardPositions(thisGame);
}

bool Game::IsFinished()
{

    for (int i = 0; i <= 2; i++)
    {
        for (int j = 0; j <= 2; j++)
        {
            if (_boardPositions[i][j] == EmptyValue)
            {
                return false;
            }
        }
    }
    return true;
}

void Game::NextPlayer()
{
    Player* aux = _currentPlayer;
    _currentPlayer = _nextOrPreviousPlayer;
    _nextOrPreviousPlayer = aux;

}

bool Game::IsPositionEmptyAndValid(int boardPosition)
{
    if (boardPosition < 1 || boardPosition > 9)
    {
        return false;
    }
    int line = BoardLineIndex(boardPosition);
    int column = BoardColumnIndex(boardPosition);

    return _boardPositions[line][column] == EmptyValue;
}

int Game::BoardLineIndex(int boardPosition)
{
    return (boardPosition - 1) / 3;
}

int Game::BoardColumnIndex(int boardPosition)
{
    return boardPosition - (BoardLineIndex(boardPosition) * 3) - 1;
}

bool Game::IsSymbolValid(string symbol)
{
    return (toupper(symbol[0]) == NoughtValue || toupper(symbol[0]) == CrossValue) && symbol.length() == 1;
}

char Game::GiveNoughtValue()
{

    return NoughtValue;
}

char Game::GiveCrossValue()
{
    return CrossValue;
}

Player* Game::GiveCurrentPlayer()
{
    return _currentPlayer;
}

Player* Game::GiveNextOrPreviousPlayer()
{
    return _nextOrPreviousPlayer;
}