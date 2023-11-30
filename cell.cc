#include "cell.h"

Cell::Cell(): celltype{' '}, row{}, col{}, link{nullptr}, observers{} {}

bool Cell::isLink(){
 if (link.get() == nullptr){
    return false;
 }else{
    return true; 
 }
}

char Cell::getType() const {return celltype;}

char Cell::getFireWall() const {return firewall;}

void Cell::setFireWall(int n) {
    firewall = (n == 1) ? 'w' : 'm';    
}

int Cell::getRow() const {return row;}

int Cell::getCol() const {return col;}

Link& Cell::getLink() const{
if (link){ //if the cell is occupied by a link 
    return *link; 
}
}

void Cell::download(){
link = nullptr; //remove the link from the board 
}

void Cell::upload(std::unique_ptr<Link> l){
link = std::move(l); //attach a smart pointer to the cell 
}

void Cell::attach(Observer *o){
    observers.emplace_back(o);
}

void Cell::notifyObservers(){
    for (auto o: observers){
        o->notify(*this);
    }
}