#include "src/module.hpp"
#include "src/parser.hpp"
#include <iostream>

void callback(const DataFrame &data) { std::cout << "callback: " << std::endl; }

int main(int argc, char *argv[]) {
  std::cout << "asio serial" << std::endl;
  if (argc != 2) {
    std::cout << "需要传入串口号" << std::endl;
    return -1;
  }
  std::string port = argv[1];
  asio::io_context io;
  Parser parser(io, callback, port, 115200);
  parser.Start();
  return 0;
}
