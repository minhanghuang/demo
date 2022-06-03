#include <iostream>
#include <vector>

int main(int argc, char *argv[]) {
  std::cout << "core dump demo" << std::endl;
  char *s = "hello world";
  *(s + 1000) = 'x';
  // vector 不生效
  // std::vector<int> a;
  // a.push_back(1);
  // a.at(10);
  return 0;
}
