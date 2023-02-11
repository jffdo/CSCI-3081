#include "./rubber.h"
void Rubber ::quack() { std::cout << "Squeak!" << std::endl; }
void Rubber ::display() { std::cout << "I am a Rubber Duck!" << std::endl; }
void Rubber ::fly() { std::cout << "I can't fly!" << std::endl; }
Rubber::~Rubber() {}
Rubber::Rubber(std::string name, float coolness, double weight) {
  this->name = name;
  this->weight = weight;
  this->coolness = coolness;
  dodgeChance = 5;
}
Rubber::Rubber() {
  name = "NA";
  coolness = 0;
  weight = 0;
  dodgeChance = 5;
}
