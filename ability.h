#ifndef __ABILITY_H__
#define __ABILITY_H__
#include "cell.h"
#include "player.h"
#include "exceptions.h"

class Ability{
public: 
    virtual void execute() = 0;
};

class Firewall: public Ability{
    Cell& cell; 
    int turn;

    public: 
        Firewall(Cell & cell, int turn);
        void execute() override; 
};

class Linkboost: public Ability {
    Link& link;

    public: 
        Linkboost(Link & link);
        void execute() override; 
};

class Download: public Ability{
    Cell& cell; 
    int turn;
    Player& Player1;
    Player& Player2;
    
    
    public: 
        Download(Cell & cell, int turn, Player& Player1, Player& Player2);
        void execute() override; 
};

class Polarize: public Ability{
    Link& link; 
    Player& Player1;
    Player& Player2;
    
    public: 
        Polarize(Link & link, Player& Player1, Player& Player2);
        void execute() override; 
};

class Scan: public Ability{
    Link& link; 
    Player& Player1;
    Player& Player2;

    public: 
        Scan(Link & link, Player& Player1, Player& Player2);
        void execute() override; 
};

class Diagonal: public Ability{
    Link& link; 

    public: 
        Diagonal(Link & link);
        void execute() override; 
};

class PlayerSwap: public Ability{
    Player& Player1;
    Player& Player2;
    public: 
        PlayerSwap(Player& Player1, Player& Player2);
        void execute() override; 
};

class MoveSPort: public Ability{
    Cell& sPort; 
    Cell& location;

    public: 
        MoveSPort(Cell & sPort, Cell& location);
        void execute() override; 
};
#endif
