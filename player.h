#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <vector>
#include <string>
#include "observer.h"


class Player: public Observer{
    std::vector<char> Abilities; 
    std::vector<std::string> MyLinks;
    std::vector<std::string> OppLinks;
    
    int MyD;
    int MyV;
    int OppD;
    int OppV;
    int OppAbil;

    public: 
    void notify(Cell &c);
    bool isWon();
    int getMyD(); 
    int getMyV();
    int getOppD();
    int getOppV();
    int getOppAbil();
    void setAbility(std::string s);
    void addLink(std::string s);
};

#endif