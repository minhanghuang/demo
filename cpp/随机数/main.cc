#include <iostream>
#include <random>

int main(int argc, char* argv[]) {
  std::cout << "Hello, Random" << std::endl;
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dis(0, 9);
  int random_value = dis(gen);
  std::cout << "random value: " << random_value << std::endl;
  return 0;
}
