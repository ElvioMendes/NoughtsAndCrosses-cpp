#include "Player.h"
#include <iostream>
#include <string>

using namespace std;

Player::Player() {
    _victories = 0;
}

Player::Player(std::string& name) {
    _name = name;
    _victories = 0;
}

void Player::SetSymbol(char symbol) {
    _symbol = toupper(symbol);
}
void Player::SetVictories(int victories) {
    _victories = victories;
}
string Player::GetName() {
    return _name;
}
string Player::GetSymbol() {
    return _symbol;
}
int Player::GetVictories() {
    return _victories;
}


