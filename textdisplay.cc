#include "textdisplay.h"

TextDisplay::TextDisplay(int n): theDisplay{}, gridSize{n} {

    theDisplay = std::vector<std::vector<char>> (n, std::vector<char>(n, '.')); 
    //the grid is initialized with all cells turned of so initialize the textdisplay to be all turned off
} 


TextDisplay::~TextDisplay() {}


void TextDisplay::notify(Cell &c){

    int row = c.getRow();
    int col = c.getCol();
    char t = c.getType();
    char firewall = c.getFireWall();

    if (t == 'n'){
        if (firewall != 'n'){
            theDisplay[row][col] = firewall;
        }else{
            theDisplay[row][col] = '.';
        }
    }else{
        theDisplay[row][col] = t; 
    }
}


std::ostream &operator<<(std::ostream &out, const TextDisplay &td){
    
    int n = td.gridSize + 2;
    int p = td.gridSize;
            

    for (int r = 0; r < n; ++r) {
        if (r == 1) {
           out << "\n"; 
        }

        if (r == 0 || r + 1 == n) {
            for (int i = 0; i < p; ++i) {
                out << "=";
            }
        } else {
            for (int c = 0; c < p; ++c) {
                out << td.theDisplay[r - 1][c];
            }
            out << "\n";
        }
        
    }

    return out; 
}
