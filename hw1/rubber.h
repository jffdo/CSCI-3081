#ifndef RUBBER_H_
#define RUBBER_H_
#include "./duck.h"

class Rubber : public Duck {
 public:
  void quack();
  void display();
  void fly();
  ~Rubber();
  Rubber(std::string name, float coolness, double weight);
  Rubber();
};

#endif  // RUBBER_H_
