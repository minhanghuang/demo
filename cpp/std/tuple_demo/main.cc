#include <iostream>
#include <tuple>

std::tuple<int, double, std::string, float> GetValues() {
  return std::make_tuple(42, 6.6666, "Hello", 3.14);
}

int main(int argc, char* argv[]) {
  std::cout << "Hello, std::tuple" << std::endl;
  {
    int int_value;
    double double_value;
    std::string string_value;
    float float_value;
    std::tie(int_value, double_value, string_value, float_value) = GetValues();
    std::cout << "int value:" << int_value << std::endl;
    std::cout << "double value:" << double_value << std::endl;
    std::cout << "string value:" << string_value << std::endl;
    std::cout << "float value:" << float_value << std::endl;
  }
  return 0;
}
