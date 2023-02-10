#include "./canvasback.h"

void Canvasback ::quack() { std::cout << "Quack" << std::endl; }
void Canvasback ::display() {
  std::cout << "I am a Canvasback Duck!" << std::endl;
}
void Canvasback ::fly() { std::cout << "I can fly!" << std::endl; }
Canvasback::~Canvasback() {}
