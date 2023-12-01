#include "ability.h"

Firewall::Firewall(Cell &c, int turn) : cell{c}, turn{turn} {}
void Firewall::execute() { cell.setFireWall(turn); }

Linkboost::Linkboost(Link & l): link{l} {}
void Linkboost::execute() {link.giveBoost(); }

Download::Download(Cell & c, int turn, Player& Player1, Player& Player2):
    cell{c}, turn{turn}, Player1{Player1}, Player2{Player2} {}

void Download::execute() { 
    Link& l = cell.getLink(); 
    std::unique_ptr<Scan> s = std::make_unique<Scan>(l, Player1, Player2);
    s->execute();

    if (cell.getLink().getType() == 'V'){
        if (turn == 2){
            Player1.incrMyV();
            Player2.incrOppV();
            //increase player's number of virus downloaded in p1
            //increase opp's number of virus downloaded (p2)
        }else if (turn == 1){ //player 2 is downloading a V
            Player2.incrMyV();
            Player1.incrOppV();
            //increase player's number of virus downloaded in p2
            //increase opp's number of virus downloaded (p1)
        }
    } else if (cell.getLink().getType() == 'D'){
        if (turn == 2){ //player 1 is downloading a D
            Player1.incrMyD();
            Player2.incrOppD();
            //increase player's number of data downloaded in p1
            //increase opp's number of data downloaded (p2)
        }else if (turn == 1){ //player 2 is downloading a D
            Player2.incrMyD();  //increase p2's number of data downloaded
            Player1.incrOppD(); //increase p1's opp number of data downloaded 
        }
    }
    //removes the link from the cell 
    cell.download(); 
}

Polarize::Polarize(Link & link, Player& Player1, Player& Player2) : link{link}, Player1{Player1}, Player2{Player2} {}
void Polarize::execute() {
    link.toggleType();
    char newtype = link.getType(); 
    char linkname = link.getName(); 
    if (linkname >= 'a' && linkname <= 'h'){ //the link is player 1's link 
        int ID = linkname - 97;
        Player1.polarizeUpdate(newtype, ID, true);
        Player2.polarizeUpdate(newtype, ID, false);
        //update p1's MyLinks
        //update p1's OppLinks if it isn't a Q
    }else{ //the link is player2's link 
        int ID = linkname - 65;
        Player1.polarizeUpdate(newtype, ID, false);
        Player2.polarizeUpdate(newtype, ID, true);
        //update p2's MyLinks
        //update p2's OppLinks 

    }
}

Scan::Scan(Link & link, Player& Player1, Player& Player2) : link{link}, Player1{Player1}, Player2{Player2} {} 
void Scan::execute() { 
    char type = link.getName();
    string piece; 
    piece += link.getType();
    piece += link.getStrength();
    int index;

    if (type >= 'a' && type <= 'h'){
        index = type - 61; 
        Player2.revealed(index, piece); //reveal the cell to player 2 
    } else if (type >= 'A' && type <= 'H'){
        index = type - 41;
        Player1.revealed(index, piece); //reveal the cell to player 1
    }
    link.revealbool(); //need to use reveal on the cell which is in grid 
}

