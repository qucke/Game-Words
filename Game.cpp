#include "Game.h"
#include <iostream>
using namespace std;

Game::Game(int numPlayers, const string& startWord) : field(5), dict("dict.txt"), currentPlayerIndex(0) {
    for (int i = 0; i < numPlayers; ++i) {
        players.emplace_back("Игрок " + to_string(i + 1));
    }
    field.initCenterWord(startWord);
    dict.addUsedWord(startWord);
}


void Game::clearInputBuffer() const {
    cin.clear();
    int ch;
    while ((ch = cin.get()) != '\n' && ch != EOF) {
        continue;
    }
    cin.clear();
}

void Game::printResults() const {
    cout << "\n=== ИГРА ОКОНЧЕНА ===\n";
    field.display();
    
    int maxScore = -1;
    string winner = "";
    bool draw = false;

    for (const auto& p : players) {
        cout << p.getName() << " набрал(а): " << p.getScore() << " очков.\n";
        if (p.getScore() > maxScore) {
            maxScore = p.getScore();
            winner = p.getName();
            draw = false;
        } else if (p.getScore() == maxScore) {
            draw = true;
        }
    }

    if (draw) {
        cout << "Ничья\n";
    } else {
        cout << "ПОБЕДИТЕЛЬ: " << winner << endl;
    }
}

void Game::play() {
    bool gameOver = false;
    while (!gameOver) {
        field.display();
        Player& currentPlayer = players[currentPlayerIndex];
        cout << "Ход: " << currentPlayer.getName() << " (Очки: " << currentPlayer.getScore() << ")\n";
        cout << "Введите 1, чтобы сделать ход, или 0, чтобы пропустить: ";
        int choice;
        cin >> choice;

        if (choice == 0) {
            currentPlayer.skipTurn();
            cout << currentPlayer.getName() << " пропускает ход.\n";
        } else {
            bool validMove = false;
            while (!validMove) {
                int r, c;
                char letter;
                cout << "Введите строку, столбец и букву (через пробел, например: 1 2 A): ";
                cin >> r >> c >> letter;
                letter = toupper((unsigned char)letter);

                if (!field.placeLetter(r, c, letter)) {
                    cout << "ОШИБКА: Неверные координаты или клетка не примыкает к другим буквам.\n";
                    clearInputBuffer();
                    continue;
                }

                string word;
                cout << "Введите слово, которое вы составили: ";
                cin >> word;
                for (char &w : word) w = toupper((unsigned char)w);

                if (!dict.isValidWord(word) || dict.isWordUsed(word)) {
                    cout << "ОШИБКА: Слово не существует или уже было использовано!\n";
                    field.removeLetter(r, c);
                    clearInputBuffer();
                } else if (!field.canFormWord(word, r, c)) {
                    cout << "ОШИБКА: Невозможно составить слово '" << word << "' по правилам змейки с новой буквой.\n";
                    field.removeLetter(r, c);
                    clearInputBuffer();
                } else {
                    cout << "Отлично! Слово '" << word << "' принято. +" << word.length() << " очков.\n";
                    currentPlayer.addScore(word.length());
                    dict.addUsedWord(word);
                    currentPlayer.resetSkips();
                    validMove = true;
                }
                
                if(!validMove) {
                     cout << "Попробуйте еще раз или введите 0 для пропуска (вместо строки).\n";
                }
            }
        }

        if (field.isFull()) {
            cout << "\nПоле полностью заполнено!\n";
            gameOver = true;
        } else {
            int totalSkips = 0;
            for (const auto& p : players) {
                if (p.getSkips() >= 3) totalSkips++;
            }
            if (totalSkips == players.size()) {
                cout << "\nВсе игроки пропустили ход 3 раза подряд. Ничья!\n";
                gameOver = true;
            }
        }

        if (!gameOver) {
            currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
        }
    }
    
    printResults();
}