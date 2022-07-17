#include <iostream>
#include "singleton.hpp"


int main(int argc, char *argv[]) {
  std::cout << "singleton demo" << std::endl;
  auto s = Sigaction::Instance()->GetName();
  std::cout << "s:" << s << std::endl;
  return 0;
}
