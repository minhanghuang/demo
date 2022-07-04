#ifndef ASIO_SERIAL_PARSER_HPP_
#define ASIO_SERIAL_PARSER_HPP_

#include "module.hpp"
#include "serial.hpp"

class Parser {
public:
  Parser(asio::io_context &io,
         const std::function<void(const DataFrame &)> &callback,
         const std::string &devname, uint32_t baud_rate)
      : serial_(devname, baud_rate, io), callback_(callback) {
    buffer_.clear();
    serial_.SetCallback(boost::bind(&Parser::Run, this, std::placeholders::_1,
                                    std::placeholders::_2));
  };
  ~Parser(){};

  void Start() { serial_.Start(); };

  void Run(const char *data, uint32_t len) {
    std::vector<char> frame;
    buffer_.insert(buffer_.end(), data, data + len);
    std::vector<char>::iterator header = buffer_.begin();
    if (buffer_.size() < 2) {
      return;
    }
    // 遍历 buffer
    for (auto it = buffer_.begin(); it != buffer_.end() - 2; ++it) {
      // std::cout << "for buffer ..." << std::endl;
    }
    buffer_.erase(buffer_.begin(), header);
   callback_(DataFrame());
  }

private:
  AsyncSerial serial_;
  std::vector<char> buffer_{};
  std::function<void(const DataFrame &)> callback_;
};

#endif // ASIO_SERIAL_PARSER_HPP_
