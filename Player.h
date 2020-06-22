#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <string>

using namespace std;

class Player
{
public:
    Player();
    Player(std::string& name);

    void SetSymbol(char symbol);
    void SetVictories(int victories);
    string GetName();
    string GetSymbol();
    int GetVictories();
private:
    string _name;
    string _symbol;
    int _victories;

};

#endif //PLAYER_H

