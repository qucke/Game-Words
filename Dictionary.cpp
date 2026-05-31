#include "Dictionary.h"
#include <fstream>
#include <iostream>
using namespace std;

Dictionary::Dictionary(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "ВНИМАНИЕ: Не удалось открыть файл словаря '" << filename << "'!\n";
        cerr << "Игра будет пропускать любые слова длиннее 1 буквы (режим отладки).\n";
        return;
    }

    string word;
    while (file >> word) {
        validWords.insert(word);
    }
    file.close();
}

bool Dictionary::isWordUsed(const string& word) const {
    return usedWords.find(word) != usedWords.end();
}

void Dictionary::addUsedWord(const string& word) {
    usedWords.insert(word);
}

bool Dictionary::isValidWord(const string& word) const {
    if (word.length() < 2) return false;
    if (validWords.empty()) return true; 
    return validWords.find(word) != validWords.end();
}