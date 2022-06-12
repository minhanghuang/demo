#include "parser.h"

Parser::Parser(const std::string& devname, unsigned int baud_rate,
               asio::io_context& io_context,
               const std::function<void(const DataFrame&)>& callback)
    : serial_port_(io_context, devname, baud_rate),
      pub_callback_(callback),
      usual_frame_count_(0),
      unusual_frame_count_(0) {
  buffer_.clear();
  serial_port_.SetCallback(boost::bind(&Parser::parse, this, _1, _2));
}

Parser::~Parser() {
  serial_port_.ClearCallback();
  serial_port_.Close();
  std::function<void(const DataFrame&)> empty;
  pub_callback_.swap(empty);
}

void Parser::Start() {
  std::cout << "Parser Start" << std::endl;
  serial_port_.Start();
}

void Parser::parse(const char* data, unsigned int len) {
  std::cout << "parse: " << data << std::endl;
  //   buffer_.insert(buffer_.end(), data, data + len);
  //   check();
}

void Parser::check() { std::cout << "check" << std::endl; }
