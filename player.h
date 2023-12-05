#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <vector>
#include <string>
#include "subject.h"
#include "observer.h"
#include <iostream>
#include "exceptions.h"

enum class CardType {
    Linkboost,
    Firewall, 
    Download,
    Polarize, 
    Scan,
    Diagonal,
    PlayerSwap,
    MoveSPort
};

struct Card { //Represent the ability cards that Player holds
    CardType type; 
    bool used; 
};

class Player{
    std::vector<Card> Abilities; 
    std::vector<std::string> MyLinks;
    std::vector<std::string> OppLinks;
    std::vector<PlayerObserver*> observers;
    
    int MyD;
    int MyV;
    int OppD;
    int OppV;
    int MyAbil;
    int OppAbil;

    int Turn;

    public: 
        Player(); 
        std::string gameState(); //returns whether player has won, lost or none
        
        int getMyD(); 
        int getMyV();
        int getOppD();
        int getOppV();
        int getMyAbil();
        int getOppAbil();
        int getTurn();
        
        void incrMyD();
        void incrMyV();
        void incrOppD();
        void incrOppV();
        void decrMyAbil();
        void decrOppAbil();
        void switchTurn();

        void polarizeUpdate(char newtype, int ID, bool mine);

        Card& getCard(int ID); 
        std::string getMyLink(const int n);
        std::string getOppLink(const int n);
        void usedAbility(const char c);
        void revealed(int index, std::string piece);
        void setAbility(std::string s);
        void addLink(std::string s);
        std::vector<std::string> printAbilities(); 
        
        void attach(PlayerObserver *o);
        void notifyObservers();
};

#endif