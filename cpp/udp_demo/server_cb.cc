#include <functional>
#include <iostream>
#include <vector>

#include <asio.hpp>

#include "frame.h"
using ReceiveCallback =
    std::function<void(const std::vector<char>&, std::size_t)>;

class UdpServer {
 public:
  UdpServer(asio::io_context& io_context, short port, ReceiveCallback callback)
      : socket_(io_context, asio::ip::udp::endpoint(asio::ip::udp::v4(), port)),
        receive_callback_(callback) {
    buffer_.resize(1500);
    StartReceive();
  }

 private:
  void StartReceive() {
    // 异步接收数据
    socket_.async_receive_from(
        asio::buffer(buffer_), remote_endpoint_,
        [this](asio::error_code ec, std::size_t length) {
          if (!ec && length > 0) {
            if (length > buffer_.size()) {
              buffer_.resize(length);
            }
            // 调用回调函数
            if (receive_callback_) {
              receive_callback_(buffer_, length);
            }
            // 继续接收数据
            StartReceive();
          } else {
            std::cerr << "Receive error: " << ec.message() << std::endl;
            StartReceive();
          }
        });
  }

  asio::ip::udp::socket socket_;
  asio::ip::udp::endpoint remote_endpoint_;
  std::vector<char> buffer_;          // 使用 vector 存储缓冲区
  ReceiveCallback receive_callback_;  // 回调函数
};

int main() {
  int port = 9005;
  try {
    asio::io_context io_context;

    // 定义一个简单的回调函数，用于处理接收到的数据
    ReceiveCallback on_receive = [](const std::vector<char>& message,
                                    std::size_t length) {
      Frame frame;
      frame.Deserialize(message);
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
    };

    // 创建服务器，并传入回调函数
    UdpServer server(io_context, port, on_receive);

    io_context.run();  // 运行 IO 事件循环
  } catch (std::exception& e) {
    std::cerr << "Exception: " << e.what() << std::endl;
  }

  return 0;
}
