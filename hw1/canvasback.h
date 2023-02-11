#ifndef CANVASBACK_H_
#define CANVASBACK_H_
#include <string>

#include "./duck.h"

class Canvasback : public Duck {
 public:
  void quack();
  void display();
  void fly();
  ~Canvasback();
  Canvasback();
  Canvasback(std::string name, float coolness, double weight);
};

#endif  // CANVASBACK_H_
