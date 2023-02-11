#ifndef DUCK_H_
#define DUCK_H_

#include <iostream>
#include <string>

class Duck {
 public:
  virtual void quack() = 0;
  virtual void display() = 0;
  void swim();
  virtual void fly() = 0;

  Duck();
  Duck(std::string name, float coolness, double weight);
  std::string getName();
  float getCoolness();
  double getWeight();

  virtual ~Duck();
  Duck(const Duck& other);
  Duck& operator=(const Duck& other);
  bool operator<(const Duck& other);

  // getters and setters for new varibles
  int getHappiness() { return happiness; };
  void setHappiness(int mood) { happiness = mood; };
  int getDodgeChance() { return dodgeChance; };
  void setDogetChance(int chance) { dodgeChance = chance; };
  void setCoolness(float coolness) { this->coolness = coolness; };
  void updateWeight(double weight) {
    if (this->weight + weight <= 0) {
      weight = 0;
    } else {
      this->weight = this->weight + weight;
    }
  }
  // new functions (detailed explanation in duck.cc)
  void status();
  void battle(Duck& otherDuck, int wager);
  void updateHappiness(int val);
  void spectateBattle(Duck& duck, Duck& otherDuck);
  void brawl(Duck& duck, Duck& otherDuck);
  void chat(Duck& duck, Duck& otherDuck);
  void statusDisplay(Duck& duck, Duck& otherDuck);
  void training(Duck& duck, Duck& otherDuck);

 protected:
  std::string name;
  float coolness;
  double weight;

  // New varibles for functions
  int happiness = 100;
  int dodgeChance;
};
#endif  // DUCK_H_
