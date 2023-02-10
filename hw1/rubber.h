#ifndef RUBBER_H_
#define RUBBER_H_
#include "./duck.h"

class Rubber : public Duck {
  void quack();
  void display();
  void fly();
  ~Rubber();
};

#endif  // RUBBER_H_
