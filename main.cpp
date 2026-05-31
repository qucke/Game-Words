#include <iostream>
#include <string>
#include <Windows.h>
#include "Game.h"
using namespace std;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int numPlayers;
    cout << "Введите количество игроков: ";
    while (!(cin >> numPlayers) || numPlayers <= 0) {
        cout << "Ошибка! Введите корректное число игроков (больше 0): ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    string startWord;
    bool wordAccepted = false;
    while (!wordAccepted) {
        cout << "Введите начальное слово (ровно 5 заглавных букв): ";
        cin >> startWord;
        if (startWord.length() != 5) {
            cout << "Ошибка! Слово должно состоять ровно из 5 букв (вы ввели " << startWord.length() << "). Попробуйте еще раз.\n\n";
        } else {
            wordAccepted = true;
        }
    }
    Game game(numPlayers, startWord);
    game.play();

    return 0;
}