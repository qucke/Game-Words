#pragma once

class Cell {
private:
    char letter;
public:
    Cell();
    bool isEmpty() const;
    char getLetter() const;
    void setLetter(char l);
    void clear();
};