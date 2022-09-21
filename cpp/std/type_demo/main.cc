#include <iostream>

int main(int argc, char *argv[]) {
  std::cout << "Hello C++ type!" << std::endl;
  std::string str = "9876";
  std::cout << "str: " << typeid(str).name() << std::endl;
  int i64;
  std::cout << "int: " << typeid(i64).name() << std::endl;

  return 0;
}
