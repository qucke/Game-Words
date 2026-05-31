#include "Player.h"
using namespace std;

Player::Player(const string& playerName) : name(playerName), score(0), consecutiveSkips(0) {}
string Player::getName() const {
    return name; 
}
int Player::getScore() const { 
    return score; 
}
int Player::getSkips() const { 
    return consecutiveSkips; 
}
void Player::addScore(int points) { 
    score += points; 
}
void Player::skipTurn() { 
    consecutiveSkips++; 
}
void Player::resetSkips() { 
    consecutiveSkips = 0; 
}