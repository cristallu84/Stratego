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
    bool outBound(int r, int c); // Checks if out of bounds
    bool isLink(char l); // Check if link exists
    bool onBoard(char l); // Check if cell is on the board
    bool link_in_player(char l, int p); // Check if link is player's link

    public:
    Grid();
    ~Grid();


    void init(int n);
    Cell& findCell(char l); // Returns the cell with link l
    int getTurn() const; // Returns the turn
    void nextTurn();  // Sets the whoseTurn to the next turn
    void move(char l, string dir); 
    void reveal(Cell& c);
    void download(Cell& c, int player); //downloads a link in cell c, increases the number of downloads for each player and reveals it 
    void battle(Cell& init, Cell& fighter); // Handles the battle feature
    void printAbilities(); 
    Player& getPlayer(int n);

    void linkBoost(char c);
    void firewall(int r, int c);
    void download(char c);
    void polarize(char c);
    void scan(char c);

    friend std::ostream &operator<<(std::ostream &out, const Grid &g);
};

#endif
