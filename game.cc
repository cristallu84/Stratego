#include <iostream>
#include "game.h"
using namespace std;


// TODO: Add further init procedures
Grid::Grid() : theGrid{}, gridSize{0}, textDisplay{}, player1{}, player2{}, whoseTurn{1} {}

Grid::~Grid() {}

// TODO: implement grid initition
void Grid::init(int n) {
    //IMPL
}

// Returns the cell with link l
Cell& Grid::findCell(char l) { //implement a case where cell cannot be found (e.g. the link has been eaten)
    for (int r = 0; r < gridSize; ++r) {
        for (int c = 0; c < gridSize; ++c) {
            if (theGrid[r][c].getType() == l) {
                return theGrid[r][c];
            }
        }
    }
}

// Returns the turn
int Grid::getTurn() const { return whoseTurn; } 

// Sets the whoseTurn to the next turn
void Grid::nextTurn() {
    if (this->getTurn() == 1) {
        whoseTurn = 2;
    } else {
        whoseTurn = 1;
    }
}

// TODO: Implement
void Grid::move(char l, string dir){
    Cell& cell = this->findCell(l);
    int r = cell.getRow();
    int c = cell.getCol(); 
    Link& link = cell.getLink(); 
    int length = link.getMoveL();
    if (dir == "up"){
        r = r - length;
    }else if (dir == "down"){
        r = r + length;
    }else if (dir == "left"){
        c = c - length;
    }else if (dir == "right"){
        c = c + length;
    }
    Cell& nextcell = theGrid[r][c];

    if (nextcell.isLink()){ //if a link occupies the cell then battle
        battle(cell, theGrid[r][c]);
    }else if (nextcell.getType() == 'm'){ //if the cell is occupied by a firewall from p1 

    }else if (nextcell.getType() == 'w'){ //if the cell is occupied by a firewall from p2

    }else if (nextcell.getType() == 's'){
        
    }
}

// TODO: Implement
void Grid::download(Cell& c) {
    c.download(); 
}


// TODO: Move fighter to init cell if fighter wins
void Grid::battle(Cell& init, Cell& fighter) {
    // init = battle initiating player cell and link
    //get strength of both links at the cells 
    int l1 = init.getLink().getStrength();
    int l2 = fighter.getLink().getStrength();

    //reveal the fighters 
    init.getLink().reveal(); 
    fighter.getLink().reveal();
    
    //find which player initiated the battle 
    int pInit;
    int pFighter;

    if (this->getTurn() == 1) {
        pInit = 1;
        pFighter = 2;
    } else {
        pInit = 2;
        pFighter = 1;
    }

    if (l2 > l1) {
        // fighter wins
        //get the type of the link to add it to OppLinks 
        string s = init.getLink().getType() + 
            std::to_string(init.getLink().getStrength());

        this->getPlayer(pFighter).addLink(s);
        init.download();

        // MOVE FIGHTER TO INIT POSITION - fighter stays and init is downloaded 


    } else {
        // init wins
        string s = fighter.getLink().getType() + 
            std::to_string(fighter.getLink().getStrength());

        this->getPlayer(pInit).addLink(s);
        fighter.download();
        //MOVE INIT TO FIGHTER POSITION 
    }
}

// TODO: Implement
void Grid::playAbility(int ID, Cell& c) {
    // IMPL
}

// TODO: Impl. and add method to fetch abilities from player
void Grid::printAbilities() {
    int p = this->getTurn();
    // UNFINISHED 
}

Player& Grid::getPlayer(int n) {
    if (n == 1) {
        return this->player1;
    } else {
        return this->player2;
    }
}

ostream &operator<<(ostream &out, const Grid &g) {
  out << *g.textDisplay << endl;
  return out;
};