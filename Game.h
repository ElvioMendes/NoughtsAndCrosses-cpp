#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <string>
#include <cctype>
#include "Player.h"
using namespace std;
class Game
{
public:
    Game();
    Game(Player* chosenFirstPlayer, Player* secondPlayer, char startingSymbol);
    string PrintBoard();
    static string Presentation();
    bool MoveAndCheckWin(int position);
    void StartNewGame(Game* thisGame);
    bool IsFinished();
    bool IsPositionEmptyAndValid(int boardPosition);
    static bool IsSymbolValid(string symbol);
    char GiveNoughtValue();
    char GiveCrossValue();
    Player* GiveCurrentPlayer();
    Player* GiveNextOrPreviousPlayer();
private:
    char _boardPositions[3][3];
    const static char NoughtValue = 'O';
    const static char CrossValue = 'X';
    const static char EmptyValue = '-';
    Player* _currentPlayer;
    Player* _nextOrPreviousPlayer;

    static void InitializeBoardPositions(Game* thisGame);
    void NextPlayer();
    static int BoardLineIndex(int boardPosition);
    static int BoardColumnIndex(int boardPosition);
};
#endif // GAME_H

