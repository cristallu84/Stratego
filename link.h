#ifndef __CELL_H__
#define __CELL_H__
class Link{
    char name;
    char type; 
    int strength;
    bool revealed; 
    int moveLength; 
    public: 
    Link(); //default ctor
    char getName() const; //Returns the name of a Link (i.e. a-h, A-H)
    char getType() const; //Returns the type of a Link
    int getStrength() const; //Returns the strength of a Link
    void giveBoost(); //increases moveLength by 1 
    void toggleType(); //changes a virus to a data and vice versa
};

#endif
