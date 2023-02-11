#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

#include "./canvasback.h"
#include "./duck.h"
#include "./mallard.h"
#include "./rubber.h"

int main() {
  // std::vector<Duck> ducks;
  // ducks.push_back(Duck(std::string("Fulvous Whistling Duck"), 8.6f, 1.6d));
  // ducks.push_back(Duck(std::string("Domestic Duck"), 2.5f, 2.5d));
  // ducks.push_back(Duck(std::string("CanvasBack"), 5.8f, 2.7d));
  // ducks.push_back(Duck(std::string("Loon"), 10.0f, 10.0d));
  // ducks.push_back(Duck(std::string("Mallard"), 7.6f, 2.5d));

  // std::sort(ducks.begin(), ducks.end());

  // for (int i = ducks.size() - 1; i >= 0; --i) {
  //   std::cout << ducks[i].getName() << ", " << ducks[i].getCoolness()
  //             << std::endl;
  // }
  // output:
  //  Loon, 10
  //  Fulvous Whistling Duck, 8.6
  //  Mallard, 7.6
  //  CanvasBack, 5.8
  //  Domestic Duck, 2.5

  Duck* d1 = new Mallard("Al", 10, 10);
  Duck* d2 = new Canvasback("Bee", 10, 10);
  Duck* d3 = new Rubber("Car", 10, 10);
  std::cout << "----------" << std::endl;
  d1->fly();
  d1->quack();
  d1->swim();
  d1->display();
  std::cout << "----------" << std::endl;
  d2->fly();
  d2->quack();
  d2->swim();
  d2->display();
  std::cout << "----------" << std::endl;
  d3->fly();
  d3->quack();
  d3->swim();
  d3->display();
  std::cout << "----------" << std::endl;
  d1->spectateBattle(*d2, *d3);
  d1->brawl(*d2, *d3);
  d1->chat(*d2, *d3);
  d1->statusDisplay(*d2, *d3);
  d1->training(*d2, *d3);
  delete d1;
  delete d2;
  delete d3;
  return 0;
}
