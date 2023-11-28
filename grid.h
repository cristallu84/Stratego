#ifndef __GRID_H__
#define __GRID_H__
#include "cell.h"
#include "player.h"
#include "textdisplay.h"

class Grid{
std::vector<std::vector<Cell>> theGrid; 
int gridSize;
TextDisplay *textDisplay; 
//GraphicsDisplay *GraphicsDisplay;
Player player1;
Player player2; 
int whoseTurn; 
public: 
void init(int n);
Cell& findCell(char l);
int getTurn(); 
void nextTurn(); 
void move(char l, char dir); 
void download(Cell& c); 
void battle(Cell& initi, Cell& fighter);
void playAbility(int ID, Cell& c);
void printAbilities(); 
Player& getPlayer(int n); 
};


#endif