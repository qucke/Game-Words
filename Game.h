#pragma once
#include <vector>
#include <string>
#include "Board.h"
#include "Dictionary.h"
#include "Player.h"
using namespace std;

class Game {
private:
    Board field;
    Dictionary dict;
    vector<Player> players;
    int currentPlayerIndex;
    void printResults() const;
    void clearInputBuffer() const;
public:
    Game(int numPlayers, const string& startWord);
    void play();
};