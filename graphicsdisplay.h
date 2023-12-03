#ifndef __GRAPHICSDISPLAY_H__
#define __GRAPHICSDISPLAY_H__
#include <iostream>
#include <vector>
#include "observer.h"
#include "window.h"
class Cell;

class GraphicsDisplay: public Observer {
  Xwindow *window;
  const int gridSize;
 public:
  GraphicsDisplay(Xwindow &window, int n);

  void notify(Cell &c) override;

  ~GraphicsDisplay();
};

#endif
