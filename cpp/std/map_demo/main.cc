#include <cassert>
#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <utility>

int main(int argc, char* argv[]) {
  std::cout << "Hello, map." << std::endl;

  {
    // 使用insert或者emplace都不会替换原来已经存在的值
    std::unordered_map<std::string, int> m;
    m.insert(std::make_pair("1", 1));
    assert(1 == m.size());
    assert(m["1"] == 1);
    m.insert(std::make_pair("1", 2));
    assert(m["1"] == 1);
    m.emplace(std::make_pair("1", 1));
    assert(m["1"] == 1);
  }

  return 0;
}
