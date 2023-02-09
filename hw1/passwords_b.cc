#include <iostream>
#include <ostream>
#include <string>

int main(int argc, char *argv[]) {
  std::string password1;
  std::string password2;
  bool match = false;
  while (!match) {
    std::cout << "Enter 2 passwords: ";
    std::cin >> password1;
    std::cin >> password2;
    if (password1 == password2) {
      std::cout << "passwords match" << std::endl;
      match = true;
    } else {
      std::cout << "passwords do not match" << std::endl;
    }
  }
  return 0;
}
