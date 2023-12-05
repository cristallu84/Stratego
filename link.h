#ifndef __LINK_H__
#define __LINK_H__
class Link{
    char name;
    char type; 
    int strength;
    bool revealed; 
    bool permanentRevealed;
    int moveLength; 
    bool diagonal;

    public: 
    Link(char name, char type, int strength, bool revealed, bool permanentRevealed, int moveLength); //ctor
    Link(); //default ctor
    char getName() const; //Returns the name of a Link (i.e. a-h, A-H)
    char getType() const; //Returns the type of a Link
    int getStrength() const; //Returns the strength of a Link
    int getMoveL() const;  //Returns the length that the cell moves
    bool getRevealed() const; // Returns if the link is revealed or not on a turn-basis
    bool getPermanentRevealed() const;
    void giveBoost(); //increases moveLength by 1 
    void giveDiagonal(); //indicates if a link is able to move diagonally or not 
    bool isDiagonal(); //returns true if the link can move diagonally, false otherwise
    void toggleType(); //changes a virus to a data and vice versa
    void permanentRevealBool();
    void revealbool(); // flips reveal
};

#endif
