#include "link.h"

Link::Link(char name, char type, int strength, bool revealed, bool permanentRevealed, int moveLength) : 
name{name}, 
type{type}, 
strength{strength}, 
revealed{revealed}, 
permanentRevealed{permanentRevealed},
moveLength{moveLength} {}

Link::Link() : name{' '}, type{' '}, strength{0}, revealed{false}, permanentRevealed{false}, moveLength{1}, diagonal{false} {}

char Link::getName() const { return name;}//Returns the name of a Link (i.e. a-h, A-H)
char Link::getType() const { return type;} //Returns the type of a Link
int Link::getStrength() const {return strength;} //Returns the strength of a Link
int Link::getMoveL() const {return moveLength;} //Returns the strength of a Link
bool Link::getRevealed() const {return revealed;} // Returns if the link is revealed or not on a turn-basis
bool Link::getPermanentRevealed() const {return permanentRevealed;}
void Link::giveBoost() {moveLength++;} //increases moveLength by 1 
void Link::giveDiagonal() {diagonal = true;}
bool Link::isDiagonal() {return diagonal;}
void Link::toggleType() { //changes a virus to a data and vice versa
    if (type == 'V'){
        type = 'D';
    } else if (type == 'D') {
        type = 'V';
    }
} 

void Link::revealbool(){
    if (revealed) {
        revealed = false;
    } else {
        revealed = true;
    }
}

void Link::permanentRevealBool() {
    permanentRevealed = true;
}
