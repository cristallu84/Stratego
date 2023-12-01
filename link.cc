#include "link.h"

Link::Link(char name, char type, int strength, bool revealed, int moveLength): 
name{name}, 
type{type}, 
strength{strength}, 
revealed{revealed}, 
moveLength{moveLength} {}

Link::Link() : name{' '}, type{' '}, strength{0}, revealed{false}, moveLength{1} {}

char Link::getName() const { return name;}//Returns the name of a Link (i.e. a-h, A-H)
char Link::getType() const { return type;} //Returns the type of a Link
int Link::getStrength() const {return strength;} //Returns the strength of a Link
int Link::getMoveL() const {return moveLength;} //Returns the strength of a Link
void Link::giveBoost() {moveLength++;} //increases moveLength by 1 
void Link::toggleType() { //changes a virus to a data and vice versa
    if (type == 'V'){
        type = 'D';
    } else if (type == 'D') {
        type = 'V';
    }
} 

void Link::revealbool(){
    revealed = true; 
}