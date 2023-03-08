// this file is just to write some sample code that uses the class
// use this file to test out the class and understand the expected functionality
#include "stack.h"

int twice(int x) {
  return 2*x;
}

bool isEven(int x) {
  return x % 2 == 0;
}

int sum(int a, int b) {
  return a + b;
}

// we've given you some sample code to start out with
// but this is by no means a comprehensive demonstration of the class
// feel free to modify this file as much as you want
int main() {
  // creates a stack initialized with these values
  Stack s1({1, 2, 3, 4, 5});
  // prints out the stack
  std::cout << s1 << std::endl;

  // filters the stack
  s1.filter(isEven);
  std::cout << s1 << std::endl;

  // maps the elements in the stack
  s1.map(twice);
  std::cout << s1 << std::endl;

  // reduces the stack
  std::cout << s1.reduce(sum, 0) << std::endl;

  Stack s2({5, 4, 3, 2, 1});
  std::cout << s2 << std::endl;

  // sorts the stack
  s2.sort();
  std::cout << s2 << std::endl;

  // reverses the stack
  s2.reverse();
  std::cout << s2 << std::endl;
}
