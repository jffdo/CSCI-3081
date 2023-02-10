#ifndef DUCK_H_
#define DUCK_H_

#include <iostream>
#include <string>

class Duck {
 public:
  virtual void quack() = 0;
  virtual void display() = 0;
  void swim() { std::cout << "I can swim!" << std::endl; }
  virtual void fly() = 0;

  Duck() : name("NA"), coolness(0), weight(0) {}
  Duck(std::string name, float coolness, double weight) {
    this->name = name;
    this->coolness = coolness;
    this->weight = weight;
  }
  std::string getName() { return name; }
  float getCoolness() { return coolness; }
  double getWeight() { return weight; }

  virtual ~Duck() {}
  Duck(const Duck& other) {
    this->name = other.name;
    this->coolness = other.coolness;
    this->weight = other.weight;
  }
  Duck& operator=(const Duck& other) {
    this->name = other.name;
    this->coolness = other.coolness;
    this->weight = other.weight;
    return *this;
  }
  bool operator<(const Duck& other) { return this->coolness < other.coolness; }

 protected:
  std::string name;
  float coolness;
  double weight;
};
#endif  // DUCK_H_
