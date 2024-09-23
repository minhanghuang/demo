#include <iostream>

#include <asio.hpp>

#include "frame.h"

#define maxlength 1400

int main(int argc, char** argv) {
  std::cout << "Hello, udp server." << std::endl;
  int port = 9005;
  asio::io_context io_context;
  asio::ip::udp::socket sock(
      io_context, asio::ip::udp::endpoint(asio::ip::udp::v4(), port));
  std::vector<char> buffer(maxlength);
  asio::ip::udp::endpoint sender_endpoint;
  while (true) {
    const size_t length =
        sock.receive_from(asio::buffer(buffer, maxlength), sender_endpoint);
    buffer.resize(length);
    Frame frame;
    frame.Deserialize(buffer);
    std::cout << "length:" << length << std::endl;
    std::cout << "id:" << frame.header.id << std::endl;
    std::cout << "version:" << frame.header.version << std::endl;
    std::cout << "stamp:" << frame.header.stamp << std::endl;
    std::cout << "value:" << frame.data.value << std::endl;
    std::cout << "vector size:" << frame.data.vector_size << std::endl;
    std::cout << "vector" << std::endl;
    for (const auto& it : frame.data.vector_value) {
      std::cout << it << " ";
    }
    std::cout << "\n" << std::endl;
    std::cout << "array" << std::endl;
    for (const auto& it : frame.data.array_value) {
      std::cout << it << " ";
    }
    std::cout << "\n---" << std::endl;
  }
  return 0;
}
