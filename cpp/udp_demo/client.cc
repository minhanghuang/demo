#include <unistd.h>

#include <cstring>
#include <iostream>
#include <vector>

#include <asio.hpp>

#include "frame.h"

#define maxlength 1024

int main() {
  std::cout << "Hello, udp client!" << std::endl;
  const std::string host = "127.0.0.1";
  int port = 9005;

  Frame frame;
  frame.header.id = 1;
  std::strcpy(frame.header.version, "002");
  frame.header.stamp = 3.14;
  frame.data.value = 100;
  frame.data.vector_size = 5;
  for (int i = 0; i < frame.data.vector_size; i++) {
    frame.data.vector_value.emplace_back(i + 10.1);
  }
  for (int i = 0; i < 5; i++) {
    frame.data.array_value[i] = i;
    std::cout << "[debug] : " << frame.data.array_value[i] << std::endl;
  }
  std::vector<char> buffer;
  frame.Serialize(&buffer);

  asio::io_context io_context;
  asio::ip::udp::endpoint sender_endpoint(asio::ip::address::from_string(host),
                                          port);
  asio::ip::udp::socket socket(io_context);
  socket.open(asio::ip::udp::v4());

  while (true) {
    socket.send_to(asio::buffer(buffer.data(), frame.Size()), sender_endpoint);
    std::cout << frame.header.id << std::endl;
    std::cout << frame.header.stamp << std::endl;
    std::cout << frame.header.version << std::endl;
    std::cout << frame.data.value << std::endl;
    std::cout << frame.data.vector_size << std::endl;
    std::cout << "---" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
  }

  return 0;
}
