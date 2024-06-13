#include <cassert>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

int main(int argc, char* argv[]) {
  std::cout << "Hello, std::move" << std::endl;
  {
    std::cout << "########## 标准数据类型: std::move不会改变其值 #########"
              << std::endl;
    int a = 10;
    int b;
    b = std::move(a);
    std::cout << "a: " << a << "   "
              << "b: " << b << std::endl;
    assert(a == 10);
    assert(b == 10);
  }

  {
    std::cout << "########## 复杂数据类型: std::move会改变其值 #########"
              << std::endl;
    std::unordered_map<std::string, std::string> c;
    std::unordered_map<std::string, std::string> d;
    c.insert({"1", "1"});
    c.insert({"2", "2"});
    d = std::move(c);
    assert(c.size() == 0);  // 清空
    assert(d.size() == 2);
    assert(d["1"] == "1");
    assert(d["2"] == "2");
  }

  return 0;
}
