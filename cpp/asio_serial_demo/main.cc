#include <iostream>

#include "src/parser.h"

void callback(const DataFrame& df) {
  std::cout << "callback: " << std::endl;
}

int main(int argc, char *argv[]) {
  std::cout << "asio serial" << std::endl;
  std::string devname = "/dev/pts/7";
  unsigned int baud_rate = 115200;
  asio::io_context io;

  Parser parser(devname, baud_rate, io, callback);
  parser.Start();

  return 0;
}
