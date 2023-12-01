#ifndef _SUBJECT_H_
#define _SUBJECT_H_
#include "observer.h"
#include <vector>
using namespace std;

class Observer;

class Subject {
   vector<Observer*> observers;

   public:
      void notifyobservers();
      virtual ~Subject() = 0;    

      void attach(Observer* o) {
         observers.emplace_back(o);
      }

      void detach(Observer* o) {
         for (auto it = observers.begin(); it != observers.end();) {
            if (*it == o) it = observers.erase(it);
            else ++it;
         }
      }
};

#endif
