#include "./duck.h"

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>
/**
Part A

Prompt: We have given you specifications for a Duck class that has a few
attributes (shown below). Your job is to complete the Duck class and finish the
main method so that the ducks get ordered based on their coolness. Hint: Look at
C++ standard library sort function

DUCK:

variables:
1. name: string - the name of the duck
2. coolness: float - how cool the duck is (float from 1-10)
3. weight: double - average weight of the duck in pounds

functions:
1. default constructor
2. constructor with paramaters
3. getName: returns string
4. getCoolness: returns float
5. getWeight: returns double
*/
/**
Part B

Add the big three to your Duck class: destructor, copy constructor, copy
assignment operator. Add comments explaining what each one does, how they differ
from one other, and differences between each of these and the default
constructor.
*/

/**
Part C

We will now refactor our Duck class to be an abstract parent class (Duck) with
child classes (Mallard, Canvasback, and Rubber). Each class should be its own
file (duck.cc, mallard.cc, canvasback.cc, and rubber.cc) The parent class will
have the following pure virtual methods added: quack: void display: void swim:
void fly: void The child classes have the following behavior: Mallard quack:
prints “Quack!” display: prints “I am a Mallard Duck!” swim: prints “I can
swim!” fly: prints “I can fly!” Canvasback quack: prints “Quack!” display:
prints “I am a Canvasback Duck!” swim: prints “I can swim!” fly: prints “I can
fly!” Rubber quack: prints “Squeak!” display: prints “I am a Rubber Duck!” swim:
prints “I can swim!” fly: prints “I can’t fly!”
1. One of these four added functions can be refactored such that it is not pure
virtual anymore. Refactor that function accordingly.
2. Create an instance of each of the children classes in the main function.
3. You'll also have to comment out the ducks vector, all the push_backs, and
sort from part A. Why?
You can not create an object from a abstract class
*/

/**
Part D

Create five functions that take in two ducks and output something.
You get to define the functions however you want.
Feel free to add new variables to the ducks in order to complete wanted
functionality. In addition to writing the code, comments are required. Comments
should not only detail the logic behind the code, but also explain how the
different classes and methods interact to create an interesting experience. In
the main method, demonstrate each one of your five functions in action. This is
your chance to have fun!

*/
Duck::Duck() : name("NA"), coolness(0), weight(0) {}
Duck::Duck(std::string name, float coolness, double weight) {
  this->name = name;
  this->coolness = coolness;
  this->weight = weight;
}
void Duck::swim() { std::cout << "I can swim!" << std::endl; }
std::string Duck::getName() { return name; }
float Duck::getCoolness() { return coolness; }
double Duck::getWeight() { return weight; }
// The destructor is used to remove dynamically allocated varibles off the heap
Duck::~Duck() {}
// Copy constructor is used to create a copy of an object, Duck d2 = d2 (where
// d2 is a previously defined duck & the Duck class in not abstract)
Duck::Duck(const Duck& other) {
  this->name = other.name;
  this->coolness = other.coolness;
  this->weight = other.weight;
}
// Copy assignment is used to create a copy of an existing object to another
// existing object, d2 = d1, (where d2 are previously defned objects from
// non-abstract class)
Duck& Duck::operator=(const Duck& other) {
  this->name = other.name;
  this->coolness = other.coolness;
  this->weight = other.weight;
  return *this;
}
// Used for the call to std::sort()
bool Duck::operator<(const Duck& other) {
  return this->coolness < other.coolness;
}

// Print status
void Duck::status() {
  std::cout << "----------" << std::endl;
  std::cout << "Name: " << getName() << std::endl;
  std::cout << "Coolness: " << getCoolness() << std::endl;
  std::cout << "Weight: " << getWeight() << std::endl;
  std::cout << "Happiness" << getHappiness() << std::endl;
  std::cout << "----------" << std::endl;
}

// The battle function. The majority of the new functions use this. This outputs
// the outcome of the battle of the two ducks. A rand is used to create 50%
// chance of an attack. If the attack lands, another rand is used to create a
// dodge effect using the ducks base dodge value. An optional paramater wager is
// added to chane how much coolness is lost.
void Duck::battle(Duck& otherDuck, int wager = 10) {
  std::srand(time(0));
  int attackFirst = std::rand() % 2;
  std::cout << "The attacker " << getName() << " shouts the battle cry,  ";
  quack();
  if (attackFirst) {
    if (std::rand() % 10 <= otherDuck.getDodgeChance()) {
      std::cout << "The defender " << otherDuck.getName()
                << " dodges and shouts the battle cry, ";
      otherDuck.display();
      std::cout << "Crowd Cheers!" << getName() << " Coolness -" << wager
                << std::endl;
      updateHappiness(-30);
      coolness -= wager;
      std::cout << otherDuck.getName() << " Coolness +" << wager << std::endl;
      otherDuck.setCoolness(otherDuck.getCoolness() + wager);
      otherDuck.updateHappiness(10);
    } else {
      std::cout << "The defender " << otherDuck.getName()
                << " is injured and grunts, but ";
      otherDuck.display();
      std::cout << "Crowd Cheers! " << getName() << " Coolness +" << wager
                << std::endl;
      coolness += wager;
      updateHappiness(10);
      std::cout << otherDuck.getName() << " Coolness -" << wager << std::endl;
      otherDuck.setCoolness(otherDuck.getCoolness() - wager);
      otherDuck.updateHappiness(-30);
    }
  } else {
    std::cout << "Unexpected Miss against " << otherDuck.getName() << "!"
              << std::endl;
    std::cout << "Crowd Boos! " << getName() << " Coolness -" << wager
              << std::endl;
    coolness -= wager;
    updateHappiness(-20);
  }
  std::cout << "----------" << std::endl;
}
// This function adds the val to happiness total. Sets a 0 lower and 100 upper
// limit.
void Duck::updateHappiness(int val) {
  if (getHappiness() + val >= 100) {
    setHappiness(100);
  } else if (getHappiness() + val <= 0) {
    setHappiness(0);
  } else {
    setHappiness(getHappiness() + val);
  }
}
// This function creates a battle betwee the 2 ducks. The duck object itself
// gains weight and happiness
void Duck::spectateBattle(Duck& duck, Duck& otherDuck) {
  double weightIncrease = 30;
  int happiness = 20;
  std::cout << getName() << " says, ";
  quack();
  std::cout << "Currently spectating the battle of " << duck.getName()
            << " vs. " << otherDuck.getName() << std::endl;
  duck.battle(otherDuck);
  std::cout << getName() << " mood increased +" << happiness << std::endl;
  updateHappiness(happiness);
  std::cout << getName() << " weight increased +" << happiness << std::endl;
  updateWeight(weightIncrease);
  std::cout << "----------" << std::endl;
}
// This function use rand to call rand many battles, if the other 2 happiness is
// low enough "this" duck is battled instead
void Duck::brawl(Duck& duck, Duck& otherDuck) {
  std::cout << getName() << " starts a brawl between " << duck.getName()
            << " and " << otherDuck.getName() << "!" << std::endl;
  std::cout << "----------" << std::endl;
  std::srand(time(0));
  for (int i = 0; i < (std::rand() % 7) + 1; ++i) {
    if (getHappiness() <= 10) {
      std::cout << getName() << " is unhappy and cancels the brawl!"
                << std::endl;
      break;
    }
    if (duck.getHappiness() <= 10 || otherDuck.getHappiness() <= 10) {
      std::cout << duck.getName() << " and " << otherDuck.getName()
                << " are unhappy and bring " << getName() << " into the brawl!"
                << std::endl;
      battle(duck);
      battle(otherDuck);
    } else {
      duck.battle(otherDuck);
    }
  }
}
// This uses the rand to create diffrent outcomes depending on the value.
// Possible calls to battle, brawl, or weight increse for ducks
void Duck::chat(Duck& duck, Duck& otherDuck) {
  std::cout << "----------" << std::endl;
  std::cout << getName() << " starts a friendly chat with " << duck.getName()
            << " and " << otherDuck.getName() << std::endl;
  std::cout << "----------" << std::endl;
  setCoolness(getCoolness() + 30);
  duck.setCoolness(getCoolness() + 30);
  otherDuck.setCoolness(getCoolness() + 30);
  updateHappiness(20);
  duck.updateHappiness(20);
  otherDuck.updateHappiness(20);
  std::srand(time(0));
  if (std::rand() % 100 >= 60) {
    std::cout << duck.getName() << " gets insulted by " << otherDuck.getName()
              << "!" << std::endl;
    spectateBattle(duck, otherDuck);
  }
  if (std::rand() % 100 >= 60) {
    std::cout << getName() << " gets into an argument with "
              << otherDuck.getName() << "!" << std::endl;
    brawl(duck, otherDuck);
  }
  if (std::rand() % 100 >= 50) {
    std::cout << getName() << " compliments " << duck.getName()
              << " with snacks!" << std::endl;
    duck.updateWeight(10);
    duck.updateHappiness(10);
  }
  if (std::rand() % 100 >= 50) {
    std::cout << getName() << " compliments " << otherDuck.getName()
              << " with snacks!" << std::endl;
    duck.updateWeight(10);
    duck.updateHappiness(10);
  }
  std::cout << "The ducks enjoyed the conversation" << std::endl;
  std::cout << "----------" << std::endl;
}
// This function calls the status function to display, name, coolness, weight,
// and happiness
void Duck::statusDisplay(Duck& duck, Duck& otherDuck) {
  std::cout << getName() << " compares the stats of " << duck.getName()
            << " and " << otherDuck.getName() << std::endl;
  duck.status();
  otherDuck.status();
  status();
  if (coolness >= duck.getCoolness() && coolness >= otherDuck.getCoolness()) {
    std::cout << getName() << " feels satisfied!" << std::endl;
    updateHappiness(5);
    std::cout << "----------" << std::endl;
  }
}
// This function calls the battle function with a rand wager. Also reduces the
// weight of ducks
void Duck::training(Duck& duck, Duck& otherDuck) {
  int trainingVal = 5;
  std::cout << getName() << " starts training " << duck.getName() << " and "
            << otherDuck.getName() << " with a friendly battle! " << std::endl;

  std::srand(time(0));
  int wager = std::rand() % 20 + 10;
  std::cout << duck.getName() << " wagers " << wager << " of thier coolness!"
            << std::endl;
  duck.battle(otherDuck, wager);
  std::cout << getName() << " weight decreased -" << trainingVal << std::endl;
  updateWeight(-5);
  std::cout << duck.getName() << " weight decreased -" << trainingVal
            << std::endl;
  duck.updateWeight(-5);
  std::cout << otherDuck.getName() << " weight decreased -" << trainingVal
            << std::endl;
  otherDuck.updateWeight(-5);
}
