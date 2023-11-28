#ifndef __CELL_H__
#define __CELL_H__
#include "subject.h"
#include "link.h"
#include "observer.h"
#include <vector>
#include <memory>

class Cell{ 
    char celltype; 
    const int row; 
    const int col; 
    std::unique_ptr<Link> link;
    std::vector<Observer*> observers; 
    public: 
    Cell(); 
    bool isLink(); //Returns true if a Link occupies the cell
    char getType() const; //Returns the type that occupies the link (a-h, A-H for link, w/m for firewall, n for empty)
    int getRow() const; //Returns the value of row
    int getCol() const; //Returns the value of col
    Link& getLink() const; //Returns a reference to the link that it points to
    void download(); //downloads the link at the cell (detaches a link object from the link ptr)
    void upload(std::unique_ptr<Link> l); //uploads a link to the cell (attaches a link object to the link ptr)
    void attach(Observer *o);
    void notifyObservers(); //Alert observers of the new state of the cell 
};

#endif
