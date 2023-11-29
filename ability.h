#ifndef __ABILITY_H__
#define __ABILITY_H__
#include "cell.h"

class Ability{
public: 
    virtual void execute() = 0;
};

class Firewall: public Ability{
    Cell& cell; 
    public: 
    Firewall();
    void execute() override; 
};

class Linkboost: public Ability{
    Link& link; 
    public: 
    Linkboost();
    void execute() override; 
};

class Download: public Ability{
    Link& link; 
    public: 
    Download();
    void execute() override; 
};

class Polarize: public Ability{
    Link& link; 
    public: 
    Polarize();
    void execute() override; 
};

class Scan: public Ability{
    Link& link; 
    public: 
    Scan();
    void execute() override; 
};

#endif
