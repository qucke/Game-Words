#include "Board.h"
#include <iostream>
using namespace std;

Board::Board(int s) : size(s) {
    grid.resize(size, vector<Cell>(size));
}
bool Board::dfs(int r, int c, const string& word, int index, 
         vector<vector<bool>>& visited, bool usedNewLetter, int newR, int newC) const {
    if (index == word.length()) {
        return usedNewLetter;
    }
    if (r < 0 || r >= size || c < 0 || c >= size || visited[r][c] || grid[r][c].getLetter() != word[index]) {
        return false;
    }
    visited[r][c] = true;
    bool isCurrentNew = (r == newR && c == newC);
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};
    for (int i = 0; i < 4; ++i) {
        if (dfs(r + dr[i], c + dc[i], word, index + 1, visited, usedNewLetter || isCurrentNew, newR, newC)) {
            return true;
        }
    }
    visited[r][c] = false;
    return false;
}
void Board::initCenterWord(const string& word) {
    int midRow = size / 2;
    int startCol = (size - word.length()) / 2;
    for (size_t i = 0; i < word.length(); ++i) {
        grid[midRow][startCol + i].setLetter(word[i]);
    }
}
void Board::display() const {
    cout << "\n  ";
    for (int c = 0; c < size; ++c) cout << c << " ";
    cout << "\n";
    for (int r = 0; r < size; ++r) {
        cout << r << " ";
        for (int c = 0; c < size; ++c) {
            if (grid[r][c].isEmpty()) cout << ". ";
            else cout << grid[r][c].getLetter() << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

bool Board::isFull() const {
    for (int r = 0; r < size; ++r) {
        for (int c = 0; c < size; ++c) {
            if (grid[r][c].isEmpty()) return false;
        }
    }
    return true;
}
bool Board::placeLetter(int r, int c, char letter) {
    if (r < 0 || r >= size || c < 0 || c >= size || !grid[r][c].isEmpty()) {
        return false;
    }   
    bool hasAdjacent = false;
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};
    for (int i = 0; i < 4; ++i) {
        int nr = r + dr[i];
        int nc = c + dc[i];
        if (nr >= 0 && nr < size && nc >= 0 && nc < size && !grid[nr][nc].isEmpty()) {
            hasAdjacent = true;
            break;
        }
    }

    if (!hasAdjacent) return false;
    grid[r][c].setLetter(letter);
    return true;
}
void Board::removeLetter(int r, int c) {
    if (r >= 0 && r < size && c >= 0 && c < size) {
        grid[r][c].clear();
    }
}
bool Board::canFormWord(const string& word, int newR, int newC) const {
    for (int r = 0; r < size; ++r) {
        for (int c = 0; c < size; ++c) {
            if (grid[r][c].getLetter() == word[0]) {
                vector<vector<bool>> visited(size, vector<bool>(size, false));
                if (dfs(r, c, word, 0, visited, false, newR, newC)) {
                    return true;
                }
            }
        }
    }
    return false;
}