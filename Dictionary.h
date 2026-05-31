#pragma once
#include <string>
#include <unordered_set>
using namespace std;

class Dictionary {
private:
    unordered_set<string> validWords;
    unordered_set<string> usedWords;
public:
    Dictionary(const string& filename);
    bool isWordUsed(const string& word) const;
    void addUsedWord(const string& word);
    bool isValidWord(const string& word) const;
};