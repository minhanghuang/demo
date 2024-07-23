#include <cstdlib>
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
  std::cout << "Hello, env" << std::endl;

  {
    const char* value = std::getenv("PYTHONPATH");
    std::cout << "value: " << value << std::endl;
  }

  {
    const char* value = std::getenv("xxxxx");
    if (nullptr != value) {
      std::cout << "value: " << value << std::endl;
    } else {
      std::cout << "value: None" << std::endl;
    }
  }

  {
    // 不建议使用std::string来接收, 当变量不存在时,会抛异常
    // const std::string value = std::getenv("xxx");
    const char* value = std::getenv("xxx");
    if (nullptr != value) {
      std::string str;
      str = value;
      std::cout << "value: " << str << std::endl;
    } else {
      std::cout << "value: None" << std::endl;
    }
  }

  return 0;
}
