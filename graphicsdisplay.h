#ifndef __GRAPHICSDISPLAY_H__
#define __GRAPHICSDISPLAY_H__
#include <iostream>
#include <vector>
#include "observer.h"
#include "window.h"
#include "player.h"
#include "string.h"

class Cell;
class Player;

class GraphicsDisplay: public Observer, public PlayerObserver {
  Xwindow *window;
  const int gridSize;
  int playerturn;

 public:
  GraphicsDisplay(Xwindow &window, int n, int playerturn);

  void notify(Cell &c) override;
  void notifyPlayer(Player &p) override;

  ~GraphicsDisplay();
};

#endif
