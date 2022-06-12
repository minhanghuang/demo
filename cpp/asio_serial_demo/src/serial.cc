#include "serial.h"

AsyncSerial::AsyncSerial(asio::io_context& io_context,
                         const std::string& devname, unsigned int baud_rate)
    : io_(io_context), port_(io_context) {
  std::cout << devname << std::endl;
  std::cout << baud_rate << std::endl;
  port_.open(devname);
  port_.set_option(asio::serial_port_base::baud_rate(baud_rate));
  port_.set_option(
      asio::serial_port_base::parity(asio::serial_port_base::parity::none));
  port_.set_option(asio::serial_port_base::character_size(8));
  port_.set_option(asio::serial_port_base::flow_control(
      asio::serial_port_base::flow_control::none));
  port_.set_option(asio::serial_port_base::stop_bits(
      asio::serial_port_base::stop_bits::one));
  io_.post(boost::bind(&AsyncSerial::DoRead, this));

  asio::io_context::work worker(io_);
  std::thread t([&]() { io_.run(); });
  t_.swap(t);
}

AsyncSerial::~AsyncSerial() { Close(); }

void AsyncSerial::DoRead() {
  port_.async_read_some(asio::buffer(read_buffer_, ReadBufferSize),
                        boost::bind(&AsyncSerial::ReadEnd, this, _1, _2));
}

void AsyncSerial::ReadEnd(const asio::error_code& error,
                          size_t bytes_transferred) {
  if (error) {
    std::cout << "ReadEnd error:" << error.message() << std::endl;
    DoClose();
  } else {
    std::cout << "recevice: " << read_buffer_ << std::endl;
    if (callback_) {
      callback_(read_buffer_, bytes_transferred);
    }    
    DoRead();
  }
}

void AsyncSerial::DoClose() {
  asio::error_code ec;
  port_.cancel(ec);
  port_.close(ec);
}

void AsyncSerial::SetCallback(
    const std::function<void(const char*, size_t)>& callback) {
  callback_ = callback;
}

void AsyncSerial::ClearCallback() {
  std::function<void(const char*, size_t)> empty;
  callback_.swap(empty);
}

void AsyncSerial::Close() {
  io_.post(boost::bind(&AsyncSerial::DoClose, this));
  io_.reset();
} 

void AsyncSerial::Start() {
  t_.join();
}
