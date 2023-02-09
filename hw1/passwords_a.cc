#include <iostream>
#include <iterator>
#include <ostream>
#include <string>

int main(int argc, char *argv[]) {
  std::string password;
  int age;
  std::cout << "Enter password and name: ";
  std::cin >> password >> age;

  if (password.size() < 8 && age >= 18) {
    std::cout << "Pasword too short, access denied" << std::endl;
  } else if (password.size() >= 8 && age < 18) {
    std::cout << "Too youg, access denied" << std::endl;
  } else if (password.size() < 8 && age < 18) {
    std::cout << "Access denied" << std::endl;
  }
  return 0;
}
