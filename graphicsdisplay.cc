#include <iostream>
#include "graphicsdisplay.h"
#include "cell.h"
using namespace std;

GraphicsDisplay::GraphicsDisplay(Xwindow &window, int n) : window{&window}, gridSize{n} {
    window.fillRectangle(100, 100, 300, 300, Xwindow::White);

    int cellSize = 300 / gridSize;

    for (int i = 0; i < gridSize; ++i) {
        window.fillRectangle(i * cellSize + 100, 100, 1, 299, Xwindow::Black);
        window.fillRectangle(100, i * cellSize + 100, 299, 1, Xwindow::Black);
    }

    window.fillRectangle(399, 100, 1, 300, Xwindow::Black);
    window.fillRectangle(100, 399, 300, 1, Xwindow::Black);

    window.drawString(225, 25, "Player 1");
}

void GraphicsDisplay::notify(Cell &c) {
}

GraphicsDisplay::~GraphicsDisplay() {}
