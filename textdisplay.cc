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

    for (int i = 0; i < n; ++i) {
        out << "=";
    }

    for (int r = 1; r < n; ++r) {
        out << "\n";
        for (int c = 0; c < n; ++c) {
            if (r == (n - 1)) {
                out << "="; 
            } else {
                int r_temp = r - 1;
                out << td.theDisplay[r_temp][c];
            }
        }
    }
    return out; 
}
