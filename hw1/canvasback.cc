#include "./canvasback.h"

void Canvasback ::quack() { std::cout << "Quack" << std::endl; }
void Canvasback ::display() {
  std::cout << "I am a Canvasback Duck!" << std::endl;
}
void Canvasback ::fly() { std::cout << "I can fly!" << std::endl; }
Canvasback::~Canvasback() {}
Canvasback::Canvasback() {
  name = "NA";
  coolness = 0;
  weight = 0;
  dodgeChance = 1;
}
Canvasback::Canvasback(std::string name, float coolness, double weight) {
  this->name = name;
  this->coolness = coolness;
  this->weight = weight;
  dodgeChance = 1;
}
