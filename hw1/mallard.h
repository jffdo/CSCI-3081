#ifndef MALLARD_H_
#define MALLARD_H_
#include "./duck.h"

class Mallard : public Duck {
  void quack();
  void display();
  void fly();
  ~Mallard();
};

#endif  // MALLARD_H_
