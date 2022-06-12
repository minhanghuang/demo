#ifndef ASIO_PARSER_H_
#define ASIO_PARSER_H_

#include "models.hpp"
#include "serial.h"

class Parser {
 public:
  Parser(const std::string& devname, unsigned int baud_rate,
         asio::io_context& io_context,
         const std::function<void(const DataFrame&)>& callback);
  ~Parser();
  void Start();

 private:
  void parse(const char* data, unsigned int len);
  void check();
  AsyncSerial serial_port_;
  std::vector<char> buffer_{};
  std::function<void(const DataFrame&)> pub_callback_;
  u_int64_t usual_frame_count_;
  u_int64_t unusual_frame_count_;
};

#endif  // ASIO_PARSER_H_