#include <cassert>
#include <iostream>
#include <list>

int main(int argc, char* argv[]) {
  std::cout << "Hello, list." << std::endl;

  {
    std::list<int> l;
    for (int i = 0; i < 10; i++) {
      l.push_back(i);
    }
    assert(l.size() == 10);
    for (const auto& value : l) {
      std::cout << "value: " << value << std::endl;
    }
    int remove_value = 2;
    l.push_back(remove_value);
    assert(l.size() == 11);
    l.remove(remove_value);  // 删除所有符合条件的元素
    assert(l.size() == 9);
    std::cout << "remove: " << remove_value << std::endl;
    for (const auto& value : l) {
      std::cout << "value: " << value << std::endl;
    }
  }
  return 0;
}
