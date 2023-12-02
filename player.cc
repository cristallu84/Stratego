#include "player.h"

Player::Player(): 
    Abilities{}, 
    MyLinks{}, 
    OppLinks{}, 
    MyD{0},
    MyV{0},
    OppD{0},
    OppV{0},
    MyAbil{5},
    OppAbil{5}
{
    std::vector<std::string> v(8,"?");
    OppLinks = v;
}

bool Player::isWon(){
if (MyD == 4){
    return true; 
}else{
    return false; 
}
}

int Player::getMyD(){return MyD;}

int Player::getMyV(){return MyV;}

int Player::getOppD(){return OppD;}

int Player::getOppV(){return OppV;}

int Player::getMyAbil(){return MyAbil;}

int Player::getOppAbil(){return OppAbil;}

void Player::incrMyD(){++MyD;}

void Player::incrMyV(){++MyV;}

void Player::incrOppD(){++OppD;}

void Player::incrOppV(){++OppV;}

void Player::decrMyAbil(){--MyAbil;}

void Player::decrOppAbil(){--OppAbil;}

void Player::polarizeUpdate(char newtype, int ID, bool mine){
if (mine){
    MyLinks[ID][0] = newtype;
}else{
    if (OppLinks[ID][0] != '?'){ //it has been revealed
    OppLinks[ID][0] = newtype; 
    }
}
}

Card& Player::getCard(int ID){
    return Abilities[ID - 1];
}

std::string Player::getMyLink(const int n) { return MyLinks[n]; }

std::string Player::getOppLink(const int n) { return OppLinks[n]; }

void Player::usedAbility(const char c) {
    for (auto &card: Abilities) {
        if (card.used) {
            continue;
        } else if (c == 'L' && card.type == CardType::Linkboost) {
            card.used = true;
            break;
        } else if (c == 'F' && card.type == CardType::Firewall) {
            card.used = true;
            break;
        } else if (c == 'D' && card.type == CardType::Download) {
            card.used = true;
            break;
        } else if (c == 'P' && card.type == CardType::Polarize) {
            card.used = true;
            break;
        } else if (c == 'S' && card.type == CardType::Scan) {
            card.used = true;
            break;
        }
    }
}


void Player::revealed(int index, std::string piece){
    OppLinks[index] = piece; 
}

void Player::setAbility(std::string s){ //adds abilities to hand 
    
    for (char c: s) {
        Card abil;

        if (c == 'L'){ //Linkboost card
            abil =  {CardType::Linkboost, false};
        } else if (c == 'F'){ //Firewall card
            abil = {CardType::Firewall, false};
        } else if (c == 'D'){ //Download card
            abil = {CardType::Download, false};
        } else if (c == 'P'){ //Polarize card
            abil = {CardType::Polarize, false};
        } else if (c == 'S'){//Scan card 
            abil = {CardType::Scan, false};
        } else if (c == 'd'){ //Diagonal card
            abil = {CardType::Diagonal, false};
        }else if (c == 'p'){ //PlayerSwap card
            abil = {CardType::PlayerSwap, false};
        }else if (c == 'm'){ //Move S port card
            abil = {CardType::MoveSPort, false};
        }

        Abilities.emplace_back(abil);
    }
}

void Player::addLink(std::string s){
    MyLinks.emplace_back(s);
}