#include <iostream>
#include <stdexcept>
#include "grid.h"

using namespace std;

void Grid::initAbilities(std::vector<std::string>& file_links) {

    if (file_links.size() != 8) { throw incorrect_init(); }


    int countD = 0;
    int countV = 0;

    vector<bool> virus = {false, false, false, false};
    vector<bool> data = {false, false, false, false};

    for (string element: file_links) {
        
        if (countD > 4 || countV > 4) { throw incorrect_init(); }
        
        char type = element[0];
        char strength = element[1];

        if (type != 'D' && type != 'V') {
            throw incorrect_init();
        } else if (strength > 52 || strength < 48) {
            throw incorrect_init();
        } else if (type == 'D') {
            if (data[strength - 1]) { throw incorrect_init(); }
            data[strength - 1] = true; 
            ++countD;
        } else if (type == 'V') {
            if (virus[strength - 1]) { throw incorrect_init(); }
            virus[strength - 1] = true; 
            ++countV;
        }
    }
}

// Checks if the coordinates given are within the board
bool Grid::outBound(int row, int col, int player) {
    if (col < 0 || col >= gridSize) {
        return true;
    } else if (player == 1 && row < 0) {
        return true;
    } else if (player == 2 && row >= gridSize) {
        return true;
    }
    return false;
}

// Checks if the link exists
bool Grid::isLink(char c) {
    if ((c >= 'a' && c <= 'h')
        || (c >= 'A' && c <= 'H')) {
        return true;
    } else {
        return false;
    }
}

// Checks if the link is currently on the board
bool Grid::linkOnBoard(char l) {
    try {
        this->findCell(l);
    } catch (const not_on_board& e) {
        return false;
    }
    return true;
}

bool Grid::linkOfPlayer(char l, int p) {
    if (p == 1) {
        for (int i = 'a'; i <= 'h'; ++i) {
            if (l == i) {
                return true;
            }
        }
        return false; 
    } else {
        for (int i = 'A'; i <= 'H'; ++i) {
            if (l == i) {
                return true;
            }
        }
        return false;
    }
}


// --------- Exceptions helpers above --------------


Grid::Grid() : theGrid{}, gridSize{0}, textDisplay{}, graphicsDisplay{}, player1{}, player2{}, whoseTurn{1} {}

Grid::~Grid() {
    theGrid.clear();
    gridSize = 0;
    delete graphicsDisplay;
    delete textDisplay;
}

void Grid::init(int n, vector<string> p1_links, vector<string> p2_links, bool graphics, Xwindow& window) {

    gridSize = n;
    textDisplay = new TextDisplay(n);

    if (graphics) {
        graphicsDisplay = new GraphicsDisplay(window, n, whoseTurn);
    }

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
        unique_ptr<Link> link = make_unique<Link>('a' + i, type, strength, true, false, 1);

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
        unique_ptr<Link> link = make_unique<Link>(name, type, strength, false, false, 1);

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
            if (graphics){
                theGrid[i][j].attach(graphicsDisplay);
            }
            theGrid[i][j].notifyObservers();
        }
    }
    if (graphics){
        player1.attach(graphicsDisplay);
        player2.attach(graphicsDisplay);
    }

    player1.notifyObservers();   
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

    // Case link is not on the board
    if ((l >= 'a' && l <= 'h') ||
    (l >= 'A' && l <= 'H')) {
        throw not_on_board();
    }

    // Case link does not exist
    throw not_link();
}

Cell& Grid::findCoord(int r, int c){
    if (!((r >= 0 && r <= 7) && (c >= 0 && c <= 7))){
       throw invalid_input();
    }
    return theGrid[r][c]; 
}

// Returns the turn
int Grid::getTurn() const { return whoseTurn; } 

// Sets the whoseTurn to the next turn
void Grid::nextTurn() {
    if (this->getTurn() == 1) {
        whoseTurn = 2;
        player1.setTurn(2);
        player2.setTurn(2);
        player2.notifyObservers();
    } else {
        whoseTurn = 1;
        player1.setTurn(1);
        player2.setTurn(1);
        player1.notifyObservers();
    }
    // Flips revealed cells for graphic display
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            if (theGrid[i][j].getType() != 'n' && theGrid[i][j].getType() != 's' && theGrid[i][j].getType() != 'S') {
                theGrid[i][j].getLink().revealbool();
                theGrid[i][j].notifyObservers();
            }
        }
    }
}

void Grid::move(char l, string dir){
    //checks if l is a link 
    if (!(isLink(l))) { throw not_link(); }

    //checks if the link that wants to be moved belongs to the player
    if (!(linkOfPlayer(l, this->getTurn()))) { throw not_your_link(); } 
    
    //checks if the link exists on the board (has not been downloaded)
    if (!(linkOnBoard(l))) { throw not_on_board(); }
    
    //checks if the direction entered is valid 
    if (dir != "up" && 
        dir != "down" && 
        dir !="left" &&
        dir != "right" &&
        dir != "up-right" &&
        dir != "up-left" &&
        dir != "down-right" &&
        dir != "down-left") { throw invalid_input(); }
    
    Cell& cell = this->findCell(l);
    int r = cell.getRow();
    int c = cell.getCol(); 
    Link& link = cell.getLink(); 
    int length = link.getMoveL();
    int turn = this->getTurn(); //1 if p1 and 2 if p2
    
    if (dir == "up"){
        r = r - length;
    } else if (dir == "down") {
        r = r + length;
    } else if (dir == "left") {
        c = c - length;
    } else if (dir == "right") {
        c = c + length;
    } else if (link.isDiagonal()) {
        if (dir == "up-right") {
            r = r - length;
            c = c + length;
        } else if (dir == "up-left") {
            r = r - length;
            c = c - length;
        } else if (dir == "down-right") {
            r = r + length;
            c = c + length;
        } else if (dir == "down-left") {
            r = r + length;
            c = c - length;
        }
    } else { //they're trying to move diagonally, but the link can't do that
        throw not_diagonal_link(); 
    }

    //the link is being moved outside of the grid 
    if (outBound(r, c, turn)) { throw out_bounds(); }

    //check for the north and south borders of the board
    if (r >= gridSize){ //reaches the player2's border
        if (turn == 1){
            this->download(cell, 1); //p1 will download the cell
        return;
        }else{ //player 2 is trying to move into its own border
            throw wrong_player();
        }
    } else if (r < 0){ //reaches player1's border
        if (turn == 2){
            this->download(cell, 2);  //p2 will download the cell 
            return;
        }else{ //player 1 is trying to move into its own border
            throw wrong_player();
        }
        
    }

    Cell& nextcell = theGrid[r][c];
    char nexttype = nextcell.getType();
    //player tries to move onto a cell that is occupied by one of their own links
    if (nextcell.isLink() && ((nexttype >= 'a' && nexttype <= 'h' && turn == 1) 
    || (nexttype >= 'A' && nexttype <= 'H' && turn == 2))){
        throw cell_occupied();
    }


    //check for firewall
    if (nextcell.getFireWall() == 'm'){ //if the cell is occupied by a firewall from p1 
        if (turn != 1){ //if the player that goes through the firewall is an opp
            this->reveal(cell);
            if (link.getType() == 'V'){ //if it is a virus
                this->download(cell, 2); //player 2 downloads it 
            }//if it is not a virus, it will continue to check if the cell is empty
        } 
        //else player1 goes through his own firewall or its a Data - nothing occurs
    } else if (nextcell.getFireWall() == 'w'){ //if the cell is occupied by a firewall from p2
        if (turn != 2) { //if the player that goes through the firewall is an opp
            this->reveal(cell); //reveal the link
            if (link.getType() == 'V'){ //if it is a virus
                this->download(cell, 1); //player 1 downloads it 
            } //if it is not a virus, it will continue to check if the cell is empty
        }
        //player 2 goes through his own firewall or its a Data - nothing occurs
    }

    //check for link 
    if (nextcell.isLink() && cell.isLink()) { //if a link occupies the next cell and the current cell didn't get downloaded from firewall
        battle(cell, theGrid[r][c]);
    }

    //check for serverport
    if (nexttype == 's') { //p1 serverport
        if (turn != 1) { //if the player that goes through the firewall is not p1
            this->download(cell, 1); //player 1 downloads it 
        } else { //player 1 is trying to go into its own server port
            throw wrong_player();
        }
    } else if (nexttype == 'S') { //p2 serverport 
        if (turn != 2){ //if the player that goes through the firewall is p2
            this->download(cell, 2); //player 2 downloads it 
        }else{ //player 2 is trying to go into its own server port
            throw wrong_player();
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
void Grid::battle(Cell& init, Cell& fighter) { //need to update this
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
    }else { //l1 > l2 or tie 
        // init wins- pInit downloads the fighter link
        this->download(fighter, pInit);
    }   
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



