#ifndef CANVASBACK_H_
#define CANVASBACK_H_
#include <string>

#include "./duck.h"

class Canvasback : public Duck {
  void quack();
  void display();
  void fly();
  ~Canvasback();
};

#endif  // CANVASBACK_H_
