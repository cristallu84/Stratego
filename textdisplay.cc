#include "textdisplay.h"

TextDisplay::TextDisplay(int n): theDisplay{}, gridSize{n} {
  theDisplay = std::vector<std::vector<char>> (n, std::vector<char>(n, '.')); 
  //the grid is initialized with all cells turned of so initialize the textdisplay to be all turned off
} 

void TextDisplay::notify(Cell &c){
    int row = c.getRow();
    int col = c.getCol();
    int t = c.getType();
 if (t == 'n'){
    theDisplay[row][col] = '.';
 }else{
    theDisplay[row][col] = t;
 }
}

TextDisplay::~TextDisplay() {}

std::ostream &operator<<(std::ostream &out, const TextDisplay &td){
    for (int r = 0; r < td.gridSize; ++r){
        for (int c = 0; c < td.gridSize; ++c){
            if (r == 0){
                out << "="; 
            }else{
                out << td.theDisplay[r][c];
            }
        }
        out << "\n";
    }
    return out; 
}

