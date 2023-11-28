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

int Cell::getRow() const {return row;}

int Cell::getCol() const {return col;}

Link& Cell::getLink() const{
if (link){ //if the cell is occupied by a link 
    return *link; 
}
}

void Cell::download(){
link = nullptr; 
}

void Cell::upload(std::unique_ptr<Link> l){
link = std::move(l); 
}
void Cell::attach(Observer *o){
    observers.emplace_back(o);
}

void Cell::notifyObservers(){
    for (auto o: observers){
        o->notify(*this);
    }
}