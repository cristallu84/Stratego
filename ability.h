#ifndef __ABILITY_H__
#define __ABILITY_H__
#include "cell.h"
#include "player.h"

class Ability{
public: 
    virtual void execute() = 0;
};

class Firewall: public Ability{
    int turn;
    Cell& cell; 

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
    Player player1;
    Player player2;
    
    public: 
        Download(Cell & cell, Player player1, Player player2);
        void execute() override; 
};

class Polarize: public Ability{
    Link& link; 

    public: 
        Polarize(Link & link);
        void execute() override; 
};

class Scan: public Ability{
    Link& link; 

    public: 
        Scan(Link & link);
        void execute() override; 
};

#endif
