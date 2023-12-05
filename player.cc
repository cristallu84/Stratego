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
    OppAbil{5},
    Turn{1}
{
    std::vector<std::string> v(8,"?");
    OppLinks = v;
}

std::string Player::gameState(){
if (MyD == 4){
    return "Won"; 
}else if (MyV == 4){
    return "Lost"; 
}else{
    return "None";
}
}

int Player::getMyD(){return MyD;}

int Player::getMyV(){return MyV;}

int Player::getOppD(){return OppD;}

int Player::getOppV(){return OppV;}

int Player::getMyAbil(){return MyAbil;}

int Player::getOppAbil(){return OppAbil;}

int Player::getTurn(){return Turn;}

void Player::incrMyD(){++MyD;}

void Player::incrMyV(){++MyV;}

void Player::incrOppD(){++OppD;}

void Player::incrOppV(){++OppV;}

void Player::decrMyAbil(){--MyAbil;}

void Player::decrOppAbil(){--OppAbil;}

void Player::switchTurn() {
    if (Turn == 1) {
        Turn = 2;
    } else {
        Turn = 1;
    }
}

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
    
    if (s.length() != 5) { throw incorrect_init();  } 

    std::string allowedAbilities = "LPFSDdpm";

    std::vector<int> count = {0, 0, 0, 0, 0, 0, 0, 0};

    // check if abilities is wrong and then throw
    for (char c: s) {

        if (allowedAbilities.find(c) == std::string::npos) {

            throw incorrect_init();
        } else {

            ++count[allowedAbilities.find(c)];
        
            if (count[allowedAbilities.find(c)] >= 2) {
                throw incorrect_init();
            }
        }
    }

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

std::vector<std::string> Player::printAbilities() {
    // Return a vector of strings
    std::vector<std::string> cards;
    for (int i = 1; i <= 5; i++){
        CardType cardtype = this->getCard(i).type;
        bool cardused = this->getCard(i).used;
        if (cardtype == CardType::Linkboost) {
            cards.emplace_back("Linkboost");
        } else if (cardtype == CardType::Download) {
            cards.emplace_back("Download");
        } else if (cardtype == CardType::Firewall) {
            cards.emplace_back("Firewall");
        } else if (cardtype == CardType::Polarize) {
            cards.emplace_back("Polarize");
        } else if (cardtype == CardType::Scan) {
            cards.emplace_back("Scan");
        } else if (cardtype == CardType::Diagonal){
            cards.emplace_back("Diagonal");
        } else if (cardtype == CardType::PlayerSwap){
            cards.emplace_back("PlayerSwap");
        } else if (cardtype == CardType::MoveSPort){
            cards.emplace_back("MoveSPort");
        }         
        cardused ? cards.emplace_back("Used") : cards.emplace_back("Unused");
    }
    return cards;
}

void Player::attach(PlayerObserver *o){
    observers.emplace_back(o);
}

void Player::notifyObservers(){
    for (auto o: observers){
        o->notifyPlayer(*this);
    }
}
