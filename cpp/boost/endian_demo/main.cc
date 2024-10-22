#include <iostream>
#include <vector>

#include <boost/endian/conversion.hpp>

int main(int argc, char* argv[]) {
  std::cout << "Hello, Boost Endian" << std::endl;

  {
    std::cout << "大端转小端" << std::endl;
    std::uint32_t big_endian_data = 0x12345678;  // 假设收到的是大端数据
    std::uint32_t little_endian_data =
        boost::endian::big_to_native(big_endian_data);
    std::cout << "大端数据: " << std::hex << big_endian_data << std::endl;
    std::cout << "转换后的小端数据: " << std::hex << little_endian_data
              << std::endl;
  }

  return 0;
}
