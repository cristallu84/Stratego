#include "ability.h"

Firewall::Firewall(Cell &c, int turn) : cell{c}, turn{turn} {}
void Firewall::execute() { cell.setFireWall(turn); }

Linkboost::Linkboost(Link & l): link{link} {}
void Linkboost::execute() { link.giveBoost(); }

Download::Download(Cell & cell, Player player1, Player player2) : 
    cell{cell}, player1{player1}, player2{player2}  {}

void Download::execute() {

    if (cell.getLink().getType() == 'V'){
        player1.incrMyV();
        player2.incrOppV();
        
    } else if (cell.getLink().getType() == 'D'){
        player1.incrMyD();
        player2.incrOppD();
    }
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

