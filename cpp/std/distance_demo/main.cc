#include <iostream>
#include <iterator>
#include <vector>

int main(int argc, char* argv[]) {
  std::cout << "Hello, std::distance" << std::endl;
  /**
    在C++的STL（标准模板库）中，std::distance
    是一个函数模板，用于计算两个迭代器之间的距离。
    它可以用来计算容器中两个元素之间的距离，或者用来计算任意两个迭代器之间的距离。
  */

  std::vector<int> vec = {1, 2, 3, 4, 5};
  std::vector<int>::iterator first = vec.begin();
  std::vector<int>::iterator second = vec.begin() + 3;
  const int dist = std::distance(first, second);
  std::cout << "Distance between first and second: " << dist << std::endl;  // 3

  return 0;
}
