#include "ability.h"

Firewall::Firewall(Cell &c, int turn) : cell{c}, turn{turn} {}
void Firewall::execute() { cell.setFireWall(turn); }

Linkboost::Linkboost(Link & l): link{link} {}
void Linkboost::execute() { link.giveBoost(); }

Download::Download(Cell & cell, Player player1, Player player2, int player) : 
    cell{cell}, player1{player1}, player2{player2}, player{player}  {}

void Download::execute() {
    //adding it to the player's count of downloads
    if (cell.getLink().getType() == 'V'){
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
    } else if (cell.getLink().getType() == 'D'){
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
    cell.download(); 
}

Polarize::Polarize(Link & link) : link{link} {}
void Polarize::execute() {
    link.toggleType();
}

Scan::Scan(Link & link) : link{link} {}
void Scan::execute() { 
    link.revealbool();
}

