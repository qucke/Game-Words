#pragma once
#include <string>
using namespace std;

class Player {
private:
    string name;
    int score;
    int consecutiveSkips;
public:
    Player(const string& playerName);
    string getName() const;
    int getScore() const;
    int getSkips() const;
    void addScore(int points);
    void skipTurn();
    void resetSkips();
};