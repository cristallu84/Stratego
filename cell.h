#ifndef __CELL_H__
#define __CELL_H__
//#include "subject.h"
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
    char getType(); //Returns the type that occupies the link (a-h, A-H for link, w/m for firewall, n for empty)
    int getRow(); //Returns the value of row
    int getCol(); //Returns the value of col
    Link& getLink(); //Returns a reference to the link that it points to
    void download(); //downloads the link at the cell (detaches a link object from the link ptr)
    void upload(); //uploads a link to the cell (attaches a link object to the link ptr)
    void notifyObservers(); //Alert observers of the new state of the cell 
};

#endif
