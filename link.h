#ifndef __LINK_H__
#define __LINK_H__
class Link{
    char name;
    char type; 
    int strength;
    bool revealed; 
    int moveLength; 

    public: 
    Link(char name, char type, int strength, bool revealed, int moveLength); //ctor
    Link(); //default ctor
    char getName() const; //Returns the name of a Link (i.e. a-h, A-H)
    char getType() const; //Returns the type of a Link
    int getStrength() const; //Returns the strength of a Link
    int getMoveL() const; 
    void giveBoost(); //increases moveLength by 1 
    void toggleType(); //changes a virus to a data and vice versa
    void revealbool(); // changes reveal to true
};

#endif
