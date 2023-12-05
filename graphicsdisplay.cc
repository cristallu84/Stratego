#include <iostream>
#include "graphicsdisplay.h"
#include "cell.h"
#include "player.h"
using namespace std;

GraphicsDisplay::GraphicsDisplay(Xwindow &window, int n, int playerturn) : window{&window}, gridSize{n}, playerturn{playerturn} {

    window.fillRectangle(100, 100, 298, 298, Xwindow::Gainsboro);

    float cellSize = 300 / gridSize;

    for (int i = 0; i <= gridSize; ++i) {
        window.fillRectangle(i * cellSize + 100, 100, 1, 297, Xwindow::Black);
        window.fillRectangle(100, i * cellSize + 100, 297, 1, Xwindow::Black);
    }

    window.drawString(225, 25, "Player 1");
    window.drawString(160, 50, "D: X");
    window.drawString(215, 50, "V: X");
    window.drawString(265, 50, "Abilities: X");

    // window.drawString(177, 50, "0");  + 17

    for (int i = 0; i < 8; i++) {
        char letter = 'a' + i;
        string s{letter};
        window.drawString(95 + i * 40, 75, s + ": ");
    }

    window.drawString(225, 425, "Player 2");
    window.drawString(160, 450, "D: X");
    window.drawString(215, 450, "V: X");
    window.drawString(265, 450, "Abilities: X");

    for (int i = 0; i < 8; i++) {
        char letter = 'A' + i;
        string s{letter};
        window.drawString(95 + i * 40, 475, s + ": ");
    }
}

void GraphicsDisplay::notifyPlayer(Player &p) {
    string MyD = to_string(p.getMyD());
    string MyV = to_string(p.getMyV());
    string OppD = to_string(p.getOppD());
    string OppV = to_string(p.getOppV());
    string MyAbil = to_string(p.getMyAbil());
    string OppAbil = to_string(p.getOppAbil());

    if (playerturn == 1) {
        window->drawString(177, 50, MyD);
        window->drawString(232, 50, MyV);
        window->drawString(330, 50, MyAbil);

        for (int i = 0; i < 8; i++) {
            window->drawString(110 + i * 40, 75, p.getMyLink(i));
        }

        window->drawString(177, 450, OppD);
        window->drawString(232, 450, OppV);
        window->drawString(330, 450, OppAbil);

        for (int i = 0; i < 8; i++) {
            window->drawString(110 + i * 40, 475, p.getOppLink(i));
        }
    } else {
        window->drawString(177, 50, OppD);
        window->drawString(232, 50, OppV);
        window->drawString(330, 50, OppAbil);

        for (int i = 0; i < 8; i++) {
            window->drawString(110 + i * 40, 75, p.getOppLink(i));
        }

        window->drawString(177, 450, MyD);
        window->drawString(232, 450, MyV);
        window->drawString(330, 450, MyAbil);

        for (int i = 0; i < 8; i++) {
            window->drawString(110 + i * 40, 475, p.getMyLink(i));
        }
    }

    //    std::vector<Card> Abilities; 
    //std::vector<std::string> MyLinks;
    //std::vector<std::string> OppLinks;
    //std::vector<PlayerObserver*> observers;
    
    // window.drawString(232, 50, "1");
    // window.drawString(272, 50, "1");
}

void GraphicsDisplay::notify(Cell &c) {
    int row = c.getRow();
    int column = c.getCol();
    float cellSize = 300 / gridSize;

    if (c.getType() == 's' || c.getType() == 'S') {
        window->fillRectangle(101 + cellSize * column, 101 + cellSize * row, cellSize - 1, cellSize - 1, Xwindow::Powder_Blue);
    } else if (c.getType() != 'n' && (c.getLink().getRevealed() || c.getLink().getPermanentRevealed())) {
        string s{c.getType()};

        if (c.getLink().getType() == 'D') {
            window->fillRectangle(101 + cellSize * column, 101 + cellSize * row, cellSize - 1, cellSize - 1, Xwindow::Dark_Sea_Green);
        } else if (c.getLink().getType() == 'V') {
            window->fillRectangle(101 + cellSize * column, 101 + cellSize * row, cellSize - 1, cellSize - 1, Xwindow::Pink);
        }
       
        window->drawOverlay(116 + cellSize * column, 123 + cellSize * row, s);
    } else if (c.getType() != 'n') {
        string s{c.getType()};
        window->fillRectangle(101 + cellSize * column, 101 + cellSize * row, cellSize - 1, cellSize - 1, Xwindow::Gray);
        window->drawOverlay(116 + cellSize * column, 123 + cellSize * row, s);
    } else {
        window->fillRectangle(101 + cellSize * column, 101 + cellSize * row, cellSize - 1, cellSize - 1, Xwindow::Gainsboro);
    }
}

GraphicsDisplay::~GraphicsDisplay() {}
