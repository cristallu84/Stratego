#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__
#include <iostream>
#include "observer.h"
#include <vector>
#include "cell.h"
//class Cell; 

class TextDisplay: public Observer{
    std::vector<std::vector<char>> theDisplay;
    const int gridSize; 
    public: 
    TextDisplay(int n);
    void notify(Cell &c) override; 
    ~TextDisplay();
    friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

#endif
