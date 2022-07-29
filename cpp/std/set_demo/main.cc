#include <iostream>
#include <set>
#include <queue>
#include <unordered_set>

int main(int argc, char *argv[]) {
  std::cout << "C++ Set demo" << std::endl;
  // set
  std::set<int> int_set;
  for (int i = 10; i > 0; i--) {
    int_set.insert(i);
    std::cout << "  insert:" << i << std::endl;
  }

  int_set.insert(-1);

  std::cout << "set排序(不按顺序存储)" << std::endl;
  for (auto it : int_set) {
    std::cout << "  " << it << std::endl;
  }
  std::cout << "set排序" << std::endl;

  // unordered_set
  std::unordered_set<int> int_unset;
  for (int i = 10; i > 0; i--) {
    int_unset.insert(i);
    std::cout << "  insert:" << i << std::endl;
  }

  int_unset.insert(-1);
  int_unset.insert(-99);
  int_unset.insert(99);

  std::cout << "unset排序" << std::endl;
  for (auto it : int_unset) {
    std::cout << "  " << it << std::endl;
  }
  std::cout << "unset排序" << std::endl;
  
  return 0;
}
