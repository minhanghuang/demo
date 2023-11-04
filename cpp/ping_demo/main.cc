#include <cstdlib>
#include <iostream>

int main(int argc, char* argv[]) {
  if (2 != argc) {
    std::cout << "used: ./main '8.8.8.8'" << std::endl;
    return EXIT_FAILURE;
  }
  // -c: count 发送次数
  // -s: packetsize 发送字节大小
  // -W: 超时时间 单位:秒
  // 发送一次1个字节大小的包超时时间为2秒
  std::string ping = "ping -c1 -s1 -W 2 ";
  ping += argv[1];
  ping += "  > /dev/null 2>&1";
  std::cout << "command: " << ping << std::endl;
  int x = system(ping.c_str());
  if (x == 0) {
    std::cout << "success" << std::endl;
  } else {
    std::cout << "failed" << std::endl;
  }
  return 0;
}
