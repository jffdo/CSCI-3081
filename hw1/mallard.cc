#include "./mallard.h"
void Mallard ::quack() { std::cout << "Quack!" << std::endl; }
void Mallard ::display() { std::cout << "I am a Mallard Duck!" << std::endl; }
void Mallard ::fly() { std::cout << "I can fly!" << std::endl; }
Mallard::~Mallard() {}
Mallard::Mallard(std::string name, float coolness, double weight) {
  this->name = name;
  this->coolness = coolness;
  this->weight = weight;
  dodgeChance = 1;
}
Mallard::Mallard() {
  name = "NA";
  coolness = 0;
  weight = 0;
  dodgeChance = 1;
}
