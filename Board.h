#pragma once
#include <vector>
#include <string>
#include "Cell.h"
using namespace std;

class Board {
private:
    int size;
    vector<vector<Cell>> grid;
    bool dfs(int r, int c, const string& word, int index, 
        vector<vector<bool>>& visited, bool usedNewLetter, int newR, int newC) const;
public:
    Board(int s = 5);
    void initCenterWord(const string& word);
    void display() const;
    bool isFull() const;
    bool placeLetter(int r, int c, char letter);
    void removeLetter(int r, int c);
    bool canFormWord(const string& word, int newR, int newC) const;
};