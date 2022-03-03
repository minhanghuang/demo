#include <csignal>
#include <iostream>
#include <vector>

#include "src/stacktrace.hpp"


int main(int argc, char **argv) {
  RegisterSignal(SIGSEGV);
  RegisterSignal(SIGFPE);
  RegisterSignal(SIGABRT);
  std::vector<int> a{1,2,3};
  std::cout << a.at(100) << std::endl;
  return 0;
}