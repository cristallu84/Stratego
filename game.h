#ifndef __GAME_H__
#define __GAME_H__
#include "cell.h"
#include "player.h"
#include "textdisplay.h"

class Ability{
public: 
    virtual void execute(); 
};

class Firewall: public Ability{
    Cell& cell; 
    public: 
    void execute() override; 
};

class Linkboost: public Ability{
    Link& link; 
    public: 
    void execute() override; 
};

class Download: public Ability{
    Link& link; 
    public: 
    void execute() override; 
};

class Polarize: public Ability{
    Link& link; 
    public: 
    void execute() override; 
};

class Scan: public Ability{
    Link& link; 
    public: 
    void execute() override; 
};

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


    void init(int n);
    Cell& findCell(char l); // Returns the cell with link l
    int getTurn() const; // Returns the turn
    void nextTurn();  // Sets the whoseTurn to the next turn
    void move(char l, string dir); 
    void download(Cell& c); 
    void battle(Cell& init, Cell& fighter); // Handles the battle feature
    void playAbility(int ID, Cell& c);
    void printAbilities(); 
    Player& getPlayer(int n); 
    friend std::ostream &operator<<(std::ostream &out, const Grid &g);
};

#endif
