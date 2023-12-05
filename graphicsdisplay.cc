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

    window.drawString(225, 20, "Player 1");
    window.drawString(160, 40, "D: X");
    window.drawString(215, 40, "V: X");
    window.drawString(265, 40, "Abilities: X");

    // window.drawString(177, 50, "0");  + 17

    for (int i = 0; i < 8; i++) {
        char letter = 'a' + i;
        string s{letter};
        window.drawString(95 + i * 40, 60, s + ": ");
    }

    window.drawString(225, 420, "Player 2");
    window.drawString(160, 440, "D: X");
    window.drawString(215, 440, "V: X");
    window.drawString(265, 440, "Abilities: X");

    for (int i = 0; i < 8; i++) {
        char letter = 'A' + i;
        string s{letter};
        window.drawString(95 + i * 40, 460, s + ": ");
    }
}

void GraphicsDisplay::notifyPlayer(Player &p) {
    string MyD = to_string(p.getMyD());
    string MyV = to_string(p.getMyV());
    string OppD = to_string(p.getOppD());
    string OppV = to_string(p.getOppV());
    string MyAbil = to_string(p.getMyAbil());
    string OppAbil = to_string(p.getOppAbil());

    if (p.getTurn() == 1) {
        window->drawString(177, 40, MyD);
        window->drawString(232, 40, MyV);
        window->drawString(330, 40, MyAbil);

        for (int i = 0; i < 8; i++) {
            window->drawString(110 + i * 40, 60, p.getMyLink(i));
        }

        window->drawString(177, 440, OppD);
        window->drawString(232, 440, OppV);
        window->drawString(330, 440, OppAbil);

        for (int i = 0; i < 8; i++) {
            window->drawString(110 + i * 40, 460, p.getOppLink(i));
            if (p.getOppLink(i) == "?") {
                window->drawString(115 + i * 40, 460, " ");
            }
        } 

        //vector<string> cards = p.printAbilities();
        //for (std::vector<std::string>::size_type i = 0; i < cards.size(); i += 2) {
        //    window->drawString(20 + i * 50, 80, cards[i] + " - " + cards[i + 1]);
        //}

    } else {
        window->drawString(177, 40, OppD);
        window->drawString(232, 40, OppV);
        window->drawString(330, 40, OppAbil);

        for (int i = 0; i < 8; i++) {
            window->drawString(110 + i * 40, 60, p.getOppLink(i));
            if (p.getOppLink(i) == "?") {
                window->drawString(115 + i * 40, 60, " ");
            }
        }

        window->drawString(177, 440, MyD);
        window->drawString(232, 440, MyV);
        window->drawString(330, 440, MyAbil);

        for (int i = 0; i < 8; i++) {
            window->drawString(110 + i * 40, 460, p.getMyLink(i));
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
