#ifndef _OBSERVER_H_
#define _OBSERVER_H_

class Cell;
class Player;

class Observer {
 public:
  virtual void notify(Cell &c) = 0;
  virtual ~Observer() = default;
};

class PlayerObserver {
 public:
  virtual void notifyPlayer(Player &p) = 0;
  virtual ~PlayerObserver() = default;
};

#endif
