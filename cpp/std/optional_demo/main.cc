#include <cassert>
#include <iostream>
#include <optional>
#include <string>

std::optional<std::string> Create(const std::string& s) {
  if (s.empty()) {
    return {};
  }
  // return s; // or
  return std::make_optional<std::string>(s);
}

int main(int argc, char* argv[]) {
  std::cout << "Hello, Optional." << std::endl;
  {
    std::cout << "######### 判断是否存在 ########" << std::endl;
    auto opt_str = Create("");
    assert(opt_str == std::nullopt);
    assert(opt_str.value_or("null") == "null");
    if (opt_str) {
      std::cout << "不为空: " << opt_str.value() << std::endl;
    } else {
      std::cout << "空: " << opt_str.value_or("null") << "(给默认值)"
                << std::endl;
    }

    opt_str = Create("abc");
    assert(opt_str != std::nullopt);
    assert(opt_str.value() == "abc");
    if (opt_str) {
      std::cout << "不为空: " << opt_str.value() << std::endl;
    } else {
      std::cout << "空: " << opt_str.value_or("null") << "(给默认值)"
                << std::endl;
    }
  }
  return 0;
}
