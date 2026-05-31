#include "Cell.h"

Cell::Cell() : letter(' ') {}
bool Cell::isEmpty() const { 
    return letter == ' '; 
}
char Cell::getLetter() const { 
    return letter; 
}
void Cell::setLetter(char l) { 
    letter = l; 
}
void Cell::clear() { 
    letter = ' '; 
}