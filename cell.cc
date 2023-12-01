#include "cell.h"

Cell::Cell(char celltype, char firewall, int row, int col, std::unique_ptr<Link> link): 
celltype{celltype}, 
firewall{firewall},
row{row}, 
col{col}, 
link{std::move(link)}, 
observers{} {}

Cell::Cell() : celltype{' '}, firewall{' '}, row{ 0 }, col{ 0 }, link{ nullptr }, observers{} {}

bool Cell::isLink(){
 if (link.get() == nullptr){
    return false;
 }else{
    return true; 
 }
}

Cell::Cell(const Cell & other) : celltype(other.celltype), firewall(other.firewall),
    row(other.row), col(other.col) {

    if (other.link) {
        link = std::make_unique<Link>(*other.link);
    } else {
        link.reset();
    }

    // Copy observers (assuming Observer objects are not polymorphic)
    observers.clear();
    for (Observer* observer : other.observers) {
        observers.push_back(observer);
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
celltype = 'n';
}

void Cell::upload(std::unique_ptr<Link> l){
link = std::move(l); //attach a smart pointer to the cell 
celltype = link->getName();
}

void Cell::attach(Observer *o){
    observers.emplace_back(o);
}

void Cell::notifyObservers(){
    for (auto o: observers){
        o->notify(*this);
    }
}

