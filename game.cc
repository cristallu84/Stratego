#include <iostream>
#include <stdexcept>
#include "exceptions.h"
#include "game.h"
#include "exceptions.h"
#include "ability.h"

using namespace std;

// TODO: Add further init procedures
Grid::Grid() : theGrid{}, gridSize{0}, textDisplay{}, player1{}, player2{}, whoseTurn{1} {}

Grid::~Grid() {
    theGrid.clear();
    gridSize = 0;
    delete textDisplay;
}

// TODO: implement grid initition
void Grid::init(int n, vector<string> p1_links, vector<string> p2_links) {
    gridSize = n;
    textDisplay = new TextDisplay(n);
    // unique_ptr<TextDisplay> textDisplay = make_unique<TextDisplay>(n);
    // unique_ptr<GraphicsDisplay> graphicsDisplay = make_unique<GraphicsDisplay>(n);

    // Player 1 initialization
    std::vector<Cell> row0;
    std::vector<Cell> row1;
    for (int i = 0; i < n; i++) {

        // Initializing player link vectors
        player1.addLink(p1_links[i]);
        player2.addLink(p2_links[i]);
        
        // Creating a link
        char type = p1_links[i][0];
        int strength = p1_links[i][1];
        unique_ptr<Link> link = make_unique<Link>('a' + i, type, strength, false, 1);

        // Server ports
        if (i == n/2 || i == n/2 + 1) {
            row0.emplace_back('s', 'n', 0, i, nullptr);
            row1.emplace_back('a' + i, 'n', 0, i, std::move(link));
        }

        // Creating cells
        row0.emplace_back('a' + i, 'n', 0, i, std::move(link));
        row1.emplace_back('n', 'n', 0, i, nullptr);
    }

    // Player 2 initialization
    std::vector<Cell> rown_2; // row n - 2
    std::vector<Cell> rown_1; // row n - 1
    for (int i = 0; i < n; i++) {

        // Creating a link
        char type = p2_links[i][0];
        int strength = p2_links[i][1];
        unique_ptr<Link> link = make_unique<Link>('A' + i, type, strength, false, 1);

        // Server ports
        if (i == n/2 || i == n/2 + 1) {
            rown_1.emplace_back('S', 'n', n-1, i, nullptr);
            rown_2.emplace_back('A' + i, 'n', n, i, std::move(link));
        }

        // Creating cells
        rown_2.emplace_back('n', 'n', 0, i, nullptr);
        rown_1.emplace_back('A' + i, 'n', 0, i, std::move(link));
    }

    // Creating grid
    for (int i = 0; i < n; i++) {
        if (i == 0) theGrid.emplace_back(row0);
        else if (i == 1) theGrid.emplace_back(row1);
        else if (i == n - 2) theGrid.emplace_back(rown_2);
        else if (i == n - 1) theGrid.emplace_back(rown_1);
        else {
            // Creating empty row
            std::vector<Cell> row;
            for (int j = 0; j < n; j++) {
                row.emplace_back('n', 'n', i, j, nullptr);
            }
            theGrid.emplace_back(row);
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            theGrid[i][j].attach(textDisplay);
            // theGrid[i][j].attach(graphicsDisplay);
        }
    }
}

// Checks if the coordinates given are within the board
bool Grid::outBound(int r, int c) {
    if (r >= gridSize || c >= gridSize) {
        return false;
    }
    return true;
}


// Checks if the link exists
bool Grid::isLink(char c) {
    if (c >= 41 && c <= 48) {
        return true;
    } else if (c >= 61 && c <= 68) {
        return true;
    } else {
        return false;
    }
}

// Checks if the link is currently on the board
bool Grid::onBoard(char l) {
    try {
        Cell & c = this->findCell(l);
    } catch (const not_on_board& e) {
        return false;
    }
    return true;
}

bool Grid::link_in_player(char l, int p) {
    if (p == 1) {
        for (int i = 41; i <= 48; ++i) {
            if (l == i) {
                return true;
            }
        }
        return false; 
    } else {
        for (int i = 61; i <= 68; ++i) {
            if (l == i) {
                return true;
            }
        }
        return false;
    }
}

// Returns the cell with link l
Cell& Grid::findCell(char l) {
    for (int r = 0; r < gridSize; ++r) {
        for (int c = 0; c < gridSize; ++c) {
            if (theGrid[r][c].getType() == l) {
                return theGrid[r][c];
            }
        }
    }
    // case where cell is not found
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

void Grid::move(char l, string dir){
    Cell& cell = this->findCell(l);
    int r = cell.getRow();
    int c = cell.getCol(); 
    Link& link = cell.getLink(); 
    int length = link.getMoveL();
    if (dir == "up"){
        r = r - length;
    } else if (dir == "down"){
        r = r + length;
    } else if (dir == "left"){
        c = c - length;
    } else if (dir == "right"){
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
        } else {
            //error
        }
    } else if (nextcell.getFireWall() == 'w'){ //if the cell is occupied by a firewall from p2
        if (player != 2){ //if the player that goes through the firewall is an opp
            this->reveal(cell); //reveal the link
            if (link.getType() == 'V'){ //if it is a virus
                this->download(cell, 1); //player 1 downloads it 
            } //if it is not a virus, it will continue to check if the cell is empty
        } else {
            //error
        }
    }

    //check for link 
    if (nextcell.isLink() && cell.isLink()) { //if a link occupies the next cell and the current cell didn't get downloaded from firewall
        battle(cell, theGrid[r][c]);
    }

    //check for serverport
    if (nexttype == 's') {
        if (player != 1) { //if the player that goes through the firewall is p2
            this->download(cell, 1); //player 1 downloads it 
        } else {
            //error
        }
    } else if (nexttype == 'S') {
        if (player != 2){ //if the player that goes through the firewall is p2
            this->download(cell, 2); //player 2 downloads it 
        }else{
            //error
        }
    } else if (nexttype == 'n') { //cell is empty
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
    } else if (type >= 'A' && type <= 'H'){
        index = type - 41;
        player1.revealed(index, piece); //reveal the cell to player 1
    }
}

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
    } else if (c.getLink().getType() == 'D'){
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


// TODO: Impl. and add method to fetch abilities from player
void Grid::printAbilities() {
    int p = this->getTurn();
    // UNFINISHED 
}

void Grid::linkBoost(char c) {

    Linkboost lb(this->findCell(c).getLink());
    lb.execute();
}


void Grid::firewall(int r, int c) {

    Firewall f(theGrid[r][c], this->getTurn());
    f.execute();
}


void Grid::download_ability(char c) {
   
    if (this->getTurn() == 1) {
        Download d(this->findCell(c), player1, player2);
        d.execute();
    } else {
        Download d (this->findCell(c), player2, player1);
        d.execute();
    }
}


void Grid::polarize(char c) {

    Polarize p(this->findCell(c).getLink());
    p.execute();
}


void Grid::scan(char c) {

    Scan s(this->findCell(c).getLink());
    s.execute();
}

Player& Grid::getPlayer(int n) {
    return (n == 1) ? player1 : player2;
}

ostream &operator<<(ostream &out, const Grid &g) {
  out << *g.textDisplay << endl;
  return out;
};
