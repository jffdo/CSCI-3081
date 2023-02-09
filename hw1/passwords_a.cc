#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
  std::string password;
  int age;
  bool access = false;
  while (!access) {
    std::cout << "Enter password and name: ";
    std::cin >> password;
    std::cin >> age;
    if (password.size() < 8 && age >= 18) {
      std::cout << "Pasword too short, access denied" << std::endl;
    } else if (password.size() >= 8 && age < 18) {
      std::cout << "Too youg, access denied" << std::endl;
    } else if (password.size() < 8 && age < 18) {
      std::cout << "Access denied" << std::endl;
    } else {
      std::cout << "Access granted" << std::endl;
      access = true;
    }
  }
  return 0;
}
