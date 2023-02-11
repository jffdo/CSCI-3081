#ifndef MALLARD_H_
#define MALLARD_H_
#include "./duck.h"

class Mallard : public Duck {
 public:
  void quack();
  void display();
  void fly();
  ~Mallard();
  Mallard();
  Mallard(std::string name, float coolness, double weight);
};

#endif  // MALLARD_H_
