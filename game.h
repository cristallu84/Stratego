#ifndef __GAME_H__
#define __GAME_H__
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
    Grid();
    ~Grid();

    void init(int n, vector<string> p1_links, vector<string> p2_links);
    Cell& findCell(char l); // Returns the cell with link l
    int getTurn() const; // Returns the turn
    void nextTurn();  // Sets the whoseTurn to the next turn
    void move(char l, string dir); 
    void reveal(Cell& c);
    void download(Cell& c, int player); //downloads a link in cell c, increases the number of downloads for each player and reveals it 
    void battle(Cell& init, Cell& fighter); // Handles the battle feature
    void playAbility(int ID, Cell& c);
    void printAbilities(); 
    Player& getPlayer(int n); 
    friend std::ostream &operator<<(std::ostream &out, const Grid &g);
};

#endif
