#include <chrono>
#include <iostream>
#include <vector>

int main(int argc, char* argv[]) {
  std::cout << "Hello Time." << std::endl;
  // 1.时间差
  std::chrono::system_clock::time_point start =
      std::chrono::system_clock::now();
  std::vector<int> tmp1;
  for (int i = 0; i < 10000; i++) {
    tmp1.emplace_back(1);
  }
  std::chrono::system_clock::time_point end = std::chrono::system_clock::now();
  std::chrono::duration<double> diff = end - start;
  std::cout << "1. 时间差: " << diff.count() << "s" << std::endl;
  return 0;
}
