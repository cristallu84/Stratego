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
    char nexttype = nextcell.getType();
    int player = this->getTurn(); //1 if p1 and 2 if p2

    //check for edge of board 
    if (r >= gridSize){
        this->download(cell, 1);
        //p1 will download the cell
    }else if(r < 0){
        this->download(cell, 2);
        //p2 will download the cell 
    }

    //check for firewall
    if (nextcell.getFireWall() == 'm'){ //if the cell is occupied by a firewall from p1 
        if (player != 1){ //if the player that goes through the firewall is an opp
            this->reveal(cell);
            if (link.getType() == 'V'){ //if it is a virus
                this->download(cell, 2); //player 2 downloads it 
            }//if it is not a virus, it will continue to check if the cell is empty
        }else{
            //error
        }
    }else if (nextcell.getFireWall() == 'w'){ //if the cell is occupied by a firewall from p2
        if (player != 2){ //if the player that goes through the firewall is an opp
            this->reveal(cell); //reveal the link
            if (link.getType() == 'V'){ //if it is a virus
                this->download(cell, 1); //player 1 downloads it 
            } //if it is not a virus, it will continue to check if the cell is empty
        }else{
            //error
        }
    }

    //check for link 
    if (nextcell.isLink() && cell.isLink()){ //if a link occupies the next cell and the current cell didn't get downloaded from firewall
        battle(cell, theGrid[r][c]);
    }

    //check for serverport
    if (nexttype == 's'){
        if (player != 1){ //if the player that goes through the firewall is p2
            this->download(cell, 1); //player 1 downloads it 
        }else{
            //error
        }
    }else if (nexttype == 'S'){
        if (player != 2){ //if the player that goes through the firewall is p2
            this->download(cell, 2); //player 2 downloads it 
        }else{
            //error
        }
    }else if (nexttype == 'n'){ //cell is empty
        cell.download(); //link is removed from the current cell
        nextcell.upload(make_unique<Link>(link)); //link is attached to the next cell 
    }

}

void Grid::reveal(Cell& c){
    char type = c.getType();
    string piece; 
    piece += c.getLink().getType();
    piece += c.getLink().getStrength();
    int index; 

    if (type >= 'a' && type <= 'h'){
        index = type - 61; 
        player2.revealed(index, piece); //reveal the cell to player 2 
    }else if (type >= 'A' && type <= 'H'){
        index = type - 41;
        player1.revealed(index, piece);//reveal the cell to player 1
    }
}

// TODO: Implement
void Grid::download(Cell& c, int player) {
    this->reveal(c); //reveals cell c 

    //adding it to the player's count of downloads
    if (c.getLink().getType() == 'V'){
        if (player == 1){ //player 1 is downloading a V
            player1.incrMyV();
            player2.incrOppV();
            //increase player's number of virus downloaded in p1
            //increase opp's number of virus downloaded (p2)
        }else if (player == 2){ //player 2 is downloading a V
            player2.incrMyV();
            player1.incrOppV();
            //increase player's number of virus downloaded in p2
            //increase opp's number of virus downloaded (p1)
        }
    }else if (c.getLink().getType() == 'D'){
        if (player == 1){ //player 1 is downloading a D
            player1.incrMyD();
            player2.incrOppD();
            //increase player's number of data downloaded in p1
            //increase opp's number of data downloaded (p2)
        }else if (player == 2){ //player 2 is downloading a D
            player2.incrMyD();  //increase p2's number of data downloaded
            player1.incrOppD(); //increase p1's opp number of data downloaded 

        }
    }
    //removes the link from the cell 
    c.download(); 
}


// TODO: Move fighter to init cell if fighter wins
void Grid::battle(Cell& init, Cell& fighter) {
    // init = battle initiating player cell and link
    //get strength of both links at the cells 
    int l1 = init.getLink().getStrength();
    int l2 = fighter.getLink().getStrength();

    //reveal the fighters 
    this->reveal(init);
    this->reveal(fighter);
    
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