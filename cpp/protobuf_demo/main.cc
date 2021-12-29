#include "src/hello.pb.h"
#include <iostream>

int main() {
  std::cout << "Hello, PB!" << std::endl;
  hello::HelloMessage msg;
  msg.set_a(1);
  msg.set_b(2);
  std::cout << msg.DebugString() << std::endl;
  return 0;
}
