#include <boost/bind.hpp>
#include <boost/noncopyable.hpp>
#include <iostream>
#include <thread>

#include <string>
#include "asio.hpp"
#include "asio/io_context.hpp"

class Read {
 public:
  Read(const std::string& devname, unsigned int baud_rate,
       asio::io_context& io_context)
      : port_(io_context) {
    port_.open(devname);
    port_.set_option(asio::serial_port_base::baud_rate(baud_rate));
    port_.set_option(
        asio::serial_port_base::parity(asio::serial_port_base::parity::none));
    port_.set_option(asio::serial_port_base::character_size(8));
    port_.set_option(asio::serial_port_base::flow_control(
        asio::serial_port_base::flow_control::none));
    port_.set_option(asio::serial_port_base::stop_bits(
        asio::serial_port_base::stop_bits::one));
  }
  ~Read() {
    port_.close();
  }
  void ReadSome() {
    asio::error_code ec;
    port_.read_some(asio::buffer(buf_, buf_size_), ec);
    if (!ec) {
      std::cout << "[Read Some] recv data:" << buf_ << std::endl;
    }
  }
  void AsyncReadSome() {
    port_.async_read_some(asio::buffer(buf_, buf_size_),
                          boost::bind(&Read::AsyncReadEnd, this, _1, _2));
  }

 private:
  void AsyncReadEnd(const asio::error_code& error, size_t bytes_transferred) {
    std::cout << "[Async Read Some] recv data:" << buf_ << std::endl;
    AsyncReadSome();
  }
  static const int buf_size_ = 1024;
  char buf_[Read::buf_size_];
  asio::serial_port port_;
};

int main() {
  asio::io_context io;
  std::string devname = "/dev/pts/8";
  Read read(devname, 9600, io);

  asio::io_context::work worker(io);
  std::thread t([&io]() { io.run(); });

  // 同步 read
  // while (true) {
  //   read.ReadSome();
  // }
  
  // 异步 read
  read.AsyncReadSome();
  t.join();

  return 1; 
}
