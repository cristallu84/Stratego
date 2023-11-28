#include "textdisplay.h"

TextDisplay::TextDisplay(int n): theDisplay{}, gridSize{n} {

    theDisplay = std::vector<std::vector<char>> (n, std::vector<char>(n, '.')); 
    //the grid is initialized with all cells turned of so initialize the textdisplay to be all turned off
} 


TextDisplay::~TextDisplay() {}


void TextDisplay::notify(Cell &c){

    int row = c.getRow();
    int col = c.getCol();
    int t = c.getType();

    theDisplay[row][col] = (t == 'n') ? '.' : t;
}


std::ostream &operator<<(std::ostream &out, const TextDisplay &td){
    
    int n = td.gridSize + 2;

    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c) {
            if (r == 0 || r == (n - 1)) {
                out << "="; 
            } else {
                int r_temp = r - 1;
                out << td.theDisplay[r_temp][c];
            }
        }
        out << "\n";
    }
    return out; 
}
