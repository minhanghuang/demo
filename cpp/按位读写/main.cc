#include <cstdint>
#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>

int main(int argc, char* argv[]) {
  std::cout << "Hello, bit" << std::endl;

  std::unordered_map<std::uint16_t, std::string> weather{
      std::pair<std::uint16_t, std::string>(0, "晴天"),
      std::pair<std::uint16_t, std::string>(1, "雨天"),
      std::pair<std::uint16_t, std::string>(2, "雪天"),
      std::pair<std::uint16_t, std::string>(3, "雾天"),
  };

  std::uint16_t mode = 0x000;
  mode = 0b0010;
  mode = 0b0011;
  mode = 0b0100;
  mode = 0b0110;

  {
    std::cout << "\n---1 " << std::endl;
    // 遍历每个位
    for (int i = 0; i < 16; ++i) {
      // 检查第 i 位是否为 1
      bool is_bit_set = (mode & (1 << i)) != 0;
      // 输出结果
      std::cout << "Bit " << i << ": " << (is_bit_set ? "1" : "0") << std::endl;
    }
  }

  {
    std::cout << "\n---2 " << std::endl;
    std::vector<std::uint16_t> weathers;
    weathers.push_back((mode & (1 << 0)) != 0 ? 1 : 0);
    weathers.push_back((mode & (1 << 1)) != 0 ? 1 : 0);
    weathers.push_back((mode & (1 << 2)) != 0 ? 1 : 0);
    weathers.push_back((mode & (1 << 3)) != 0 ? 1 : 0);
    for (const auto& it : weathers) {
      std::cout << "it: " << it << std::endl;
    }
  }

  {
    std::cout << "\n---3 " << std::endl;
    std::vector<std::uint16_t> weathers;
    for (int i = 0; i < 4; i++) {
      if (0 != (mode & (1 << i))) {
        weathers.emplace_back(i);
      }
    }
    for (const auto& it : weathers) {
      std::cout << "it: " << weather.at(it) << std::endl;
    }
  }
  return 0;
}
