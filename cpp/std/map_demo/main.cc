#include <cassert>
#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <utility>

int main(int argc, char* argv[]) {
  std::cout << "Hello, map." << std::endl;

  {
    std::cout << "@@@@@ 使用insert或者emplace都不会替换原来已经存在的值 @@@@@"
              << std::endl;
    std::unordered_map<std::string, int> m;
    m.insert(std::make_pair("1", 1));
    assert(1 == m.size());
    assert(m["1"] == 1);
    m.insert(std::make_pair("1", 2));
    assert(m["1"] == 1);
    m.emplace(std::make_pair("1", 1));
    assert(m["1"] == 1);
  }

  {
    // 删除不存在的元素: 不抛异常 & 返回0
    std::cout << "@@@@@ 删除元素 @@@@@" << std::endl;
    std::unordered_map<std::string, int> a;
    std::cout << "删除空对象: " << a.erase("100") << std::endl;
    for (int i = 0; i < 5; i++) {
      a[std::to_string(i)] = i;
    }
    a["1"] = 1;  // 重复赋值
    std::cout << "删除1: " << a.erase("1") << "剩余元素数量: " << a.size()
              << std::endl;
    std::cout << "删除100: " << a.erase("100") << "剩余元素数量: " << a.size()
              << std::endl;
  }

  return 0;
}
