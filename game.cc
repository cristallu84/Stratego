#include <iostream>
#include <stdexcept>
#include "exceptions.h"
#include "game.h"

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
    vector<Cell> row0;
    vector<Cell> row1;
    for (int i = 0; i < n; i++) {

        // Initializing player link vectors
        player1.addLink(p1_links[i]);
        player2.addLink(p2_links[i]);

        // Creating a link
        char type = p1_links[i][0];
        int strength = p1_links[i][1];
        unique_ptr<Link> link = make_unique<Link>('a' + i, type, strength, false, 1);

        // Server ports
        if (i == n/2 - 1 || i == n/2) {
            row0.emplace_back('s', 'n', 0, i, nullptr);
            row1.emplace_back('a' + i, 'n', 1, i, std::move(link));
            continue;
        }

        // Creating cells
        row0.emplace_back('a' + i, 'n', 0, i, std::move(link));
        row1.emplace_back('n', 'n', 1, i, nullptr);
    }

    // Player 2 initialization
    vector<Cell> rown_2; // row n - 2
    vector<Cell> rown_1; // row n - 1
    for (int i = 0; i < n; i++) {

        // Creating a link
        char type = p2_links[i][0];
        int strength = p2_links[i][1];
        char name = 'A' + i;
        unique_ptr<Link> link = make_unique<Link>(name, type, strength, false, 1);

        // Server ports
        if (i == n/2 - 1|| i == n/2) {
            rown_1.emplace_back('S', 'n', n - 1, i, nullptr);
            rown_2.emplace_back('A' + i, 'n', n - 2, i, std::move(link));
            continue;
        }

        // Creating cells
        rown_2.emplace_back('n', 'n', n - 2, i, nullptr);
        rown_1.emplace_back('A' + i, 'n', n - 1, i, std::move(link));
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
            theGrid[i][j].notifyObservers();
        }
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

Cell& Grid::findCoord(int r, int c){
    return theGrid[r][c]; 
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

    //check for edge of board 
    if (r >= gridSize){
        this->download(cell, 1);
        return;
        //p1 will download the cell
    }else if(r < 0){
        this->download(cell, 2);
        return;
        //p2 will download the cell 
    }

    if (c < 0 || c >= gridSize){
        return;
        cout << "error";
    }

    Cell& nextcell = theGrid[r][c];
    char nexttype = nextcell.getType();
    int player = this->getTurn(); //1 if p1 and 2 if p2

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
        if (player != 2) { //if the player that goes through the firewall is an opp
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
    } else if (cell.isLink()) { //nextcell is empty and cell hasn't been downloaded yet
        nextcell.upload(make_unique<Link>(link)); //link is attached to the next cell 
        cell.download(); //link is removed from the current cell
    }

    cell.notifyObservers();
    nextcell.notifyObservers();
}

void Grid::reveal(Cell& c){
    Link& l = c.getLink(); 
    std::unique_ptr<Scan> s = std::make_unique<Scan>(l, player1, player2);
    s->execute();
}

void Grid::download(Cell& c, int player) {
    std::unique_ptr<Download> d = std::make_unique<Download>(c, player, player1, player2);
    d->execute();
}


// TODO: Move fighter to init cell if fighter wins
bool Grid::battle(Cell& init, Cell& fighter) { //need to update this
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
        // fighter wins - pFighter downloads the init link
        this->download(init, pFighter);
        return false;
    }else { //l1 > l2 or tie 
        // init wins- pInit downloads the fighter link
        this->download(fighter, pInit);
        return true;
    }   
}


std::vector<std::string> Grid::printAbilities() {
    // Return a vector of strings
    std::vector<std::string> cards;
    for (int i = 1; i <= 5; i++){
        CardType cardtype = this->getPlayer(this->getTurn()).getCard(i).type;
        bool cardused = this->getPlayer(this->getTurn()).getCard(i).used;
        if (cardtype == CardType::Linkboost) {
            cards.emplace_back("Linkboost");
        } else if (cardtype == CardType::Download) {
            cards.emplace_back("Download");
        } else if (cardtype == CardType::Firewall) {
            cards.emplace_back("Firewall");
        } else if (cardtype == CardType::Polarize) {
            cards.emplace_back("Polarize");
        } else if (cardtype == CardType::Scan) {
            cards.emplace_back("Scan");
        }       
        cardused ? cards.emplace_back("Used") : cards.emplace_back("Unused");
    }
    return cards;
}



Player& Grid::getPlayer(int n) {
    return (n == 1) ? player1 : player2;
}

ostream &operator<<(ostream &out, const Grid &g) {
    Player p1 = g.player1;
    Player p2 = g.player2;

    if (g.whoseTurn == 1) {
        
        out << "Player 1:" << endl;
        out << "Downloaded: " << p1.getMyD() << "D, " << p1.getMyV() << "V" << endl;
        out << "Abilities: " << p1.getMyAbil() << endl; // currently no ability counter

        for (int i = 0; i < g.gridSize; i++) {
            if (i == g.gridSize / 2) out << "\n";
            char temp = 'a' + i;
            out << temp << ": " << p1.getMyLink(i) << " ";
        }

        out << '\n';

        out << *g.textDisplay << endl;

        out << "Player 2:" << endl;
        out << "Downloaded: " << p1.getOppD() << "D, " << p1.getOppV() << "V" << endl;
        out << "Abilities: " << p1.getOppAbil() << endl; // currently no ability counter

        for (int i = 0; i < g.gridSize; i++) {
            if (i == g.gridSize / 2) out << "\n";
            char temp = 'A' + i;
            out << temp << ": " << p1.getOppLink(i)<< " ";
        }

    } else {
        
        out << "Player 1:" << endl;
        out << "Downloaded: " << p2.getOppD() << "D, " << p2.getOppV() << "V" << endl;
        out << "Abilities: " << p2.getOppAbil() << endl; // currently no ability counter

        for (int i = 0; i < g.gridSize; i++) {
            if (i == g.gridSize / 2) out << "\n";
            char temp = 'a' + i;
            out << temp << ": " << p2.getOppLink(i) << " ";
        }
        
        out << '\n';

        out << *g.textDisplay << endl;

        out << "Player 2:" << endl;
        out << "Downloaded: " << p2.getMyD() << "D, " << p2.getMyV() << "V" << endl;
        out << "Abilities: " << p2.getMyAbil() << endl; // currently no ability counter

        for (int i = 0; i < g.gridSize; i++) {
            if (i == g.gridSize / 2) out << "\n";
            char temp = 'A' + i;
            out << temp << ": " << p2.getMyLink(i) << " ";
        }
    }
    
    return out;
};