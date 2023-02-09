#include <iostream>
#include <ostream>
#include <string>

int main(int argc, char *argv[]) {
  std::string password1;
  std::string password2;
  std::cout << "Enter 2 passwords: ";
  std::cin >> password1 >> password2;

  if (password1 == password2) {
    std::cout << "passwords match" << std::endl;
  } else {
    std::cout << "passwords do not match" << std::endl;
  }
  return 0;
}
