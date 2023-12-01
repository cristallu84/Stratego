#include "player.h"

Player::Player(): 
    Abilities{}, 
    MyLinks{}, 
    OppLinks{}, 
    MyD{0},
    MyV{0},
    OppD{0},
    OppV{0},
    OppAbil{0}
{}

void Player::notify(Cell&c){

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

int Player::getOppAbil(){return OppAbil;}

void Player::incrMyD(){++MyD;}

void Player::incrMyV(){++MyV;}

void Player::incrOppD(){++OppD;}

void Player::incrOppV(){++OppV;}

void Player::incrOppAbil(){++OppAbil;}

std::vector<Card> Player::getAbilities() { return Abilities; }

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
        }

        Abilities.emplace_back(abil);
    }
}

void Player::addLink(std::string s){
    MyLinks.emplace_back(s);
}