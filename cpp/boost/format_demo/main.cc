#include <iostream>
#include <vector>

#include <boost/format.hpp>

int main(int argc, char* argv[]) {
  std::cout << "Hello, Boost Format" << std::endl;

  {
    std::uint8_t num = 0xa0;
    std::string str = boost::str(boost::format("Byte: 0x%X") %
                                 static_cast<unsigned int>(num));
    std::cout << str << std::endl;
  }

  {
    std::uint16_t num = 0xffee;
    std::string str = boost::str(boost::format("Byte: 0x%X") % num);
    std::cout << str << std::endl;
  }

  return 0;
}
