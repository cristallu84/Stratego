#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <vector>
#include <string>

enum class CardType {
    Linkboost,
    Firewall, 
    Download,
    Polarize, 
    Scan
};

struct Card { //Represent the ability cards that Player holds
    CardType type; 
    bool used; 
};

class Player{
    std::vector<Card> Abilities; 
    std::vector<std::string> MyLinks;
    std::vector<std::string> OppLinks;
    
    int MyD;
    int MyV;
    int OppD;
    int OppV;
    int OppAbil;

    public: 
        Player(); 
        bool isWon(); //checks if a player has downloaded 4 Data links
        
        int getMyD(); 
        int getMyV();
        int getOppD();
        int getOppV();
        int getOppAbil();
        
        void incrMyD();
        void incrMyV();
        void incrOppD();
        void incrOppV();
        void incrOppAbil();

        Card getCard(int ID); 
        std::string getMyLink(const int n);
        std::string getOppLink(const int n);
        void usedAbility(const char c);
        void revealed(int index, std::string piece);
        void setAbility(std::string s);
        void addLink(std::string s);
};

#endif