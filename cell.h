#ifndef __CELL_H__
#define __CELL_H__
#include "subject.h"
#include "link.h"
#include "observer.h"
#include <vector>
#include <memory>

class Cell{ 
    char celltype; //a-h for link of p1, A-H for link of p2, s or S for server port, n for empty 
    char firewall; //m for player1, w for player 2, n for empty
    int row; 
    int col; 
    std::unique_ptr<Link> link;
    std::vector<Observer*> observers; 

    public: 
        Cell(char celltype, char firewall, int row, int col, std::unique_ptr<Link> link); 
        Cell(); //default ctor
        bool isLink(); //Returns true if a Link occupies the cell
        char getType() const; //Returns the type that occupies the link (a-h, A-H for link, w/m for firewall, n for empty)
        char getFireWall() const; //Returns w/m for firewall,  and n if no firewall
        void setFireWall(int n); // Updates firewall
        int getRow() const; //Returns the value of row
        int getCol() const; //Returns the value of col
        Link& getLink() const; //Returns a reference to the link that it points to
        void download(); //downloads the link at the cell (detaches a link object from the link ptr)
        void upload(std::unique_ptr<Link> l); //uploads a link to the cell (attaches a link object to the link ptr)
        void attach(Observer *o);
        void notifyObservers(); //Alert observers of the new state of the cell 
        

        #include "cell.h"

    // Copy constructor
    Cell(const Cell& other)
        : celltype(other.celltype), firewall(other.firewall),
        row(other.row), col(other.col) {
        // Perform a deep copy of the Link object
        if (other.link) {
            link = std::make_unique<Link>(*other.link);
        } else {
            link.reset();
        }

        // Copy observers (assuming Observer objects are not polymorphic)
        observers.clear();
        for (Observer* observer : other.observers) {
            observers.push_back(observer);
        }
    }

    // Copy assignment operator
    Cell& operator=(const Cell& other) {
    if (this != &other) { // Avoid self-assignment
        // Copy primitive types
        celltype = other.celltype;
        firewall = other.firewall;
        row = other.row;
        col = other.col;

        // Perform a deep copy of the Link object
        if (other.link) {
            link = std::make_unique<Link>(*other.link);
        } else {
            link.reset();
        }

        // Copy observers (assuming Observer objects are not polymorphic)
        observers.clear();
        for (Observer* observer : other.observers) {
            observers.push_back(observer);
        }
    }
    return *this;
}

};


#endif
