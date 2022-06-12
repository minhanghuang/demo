#ifndef ASIO_SERIAL_HPP_
#define ASIO_SERIAL_HPP_

#include "asio.hpp"
#include <boost/bind.hpp>
#include <cstdint>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

class AsyncSerial {
public:
  AsyncSerial(const std::string &devname, uint32_t baud_rate,
              asio::io_context &io_ctx)
      : io_(io_ctx), port_(io_ctx) {
    port_.open(devname);
    port_.set_option(asio::serial_port_base::baud_rate(baud_rate));
    port_.set_option(
        asio::serial_port_base::parity(asio::serial_port_base::parity::none));
    port_.set_option(asio::serial_port_base::character_size(8));
    port_.set_option(asio::serial_port_base::flow_control(
        asio::serial_port_base::flow_control::none));
    port_.set_option(asio::serial_port_base::stop_bits(
        asio::serial_port_base::stop_bits::one));
    io_.post(boost::bind(&AsyncSerial::Poll, this));

    asio::io_context::work worker(io_);
    std::thread t([&]() { io_.run(); });
    t_.swap(t);
  }
  ~AsyncSerial() {}

  void Poll() {
    port_.async_read_some(asio::buffer(read_buffer_, BUFFER_SIZE),
                          boost::bind(&AsyncSerial::Read, this,
                                      std::placeholders::_1,
                                      std::placeholders::_2));
  }

  void Read(const asio::error_code &error, size_t bytes_transferred) {
    if (error) {
      DoClose();
    } else {
      if (callback_) {
        callback_(read_buffer_, bytes_transferred);
      }
      Poll();
    }
  }

  void SetCallback(const std::function<void(const char *, size_t)> &callback) {
    callback_ = callback;
  }

  void Close() {
    io_.post(boost::bind(&AsyncSerial::DoClose, this));
    io_.reset();
  }

  void Start() { t_.join(); }

private:
  void DoClose() {
    asio::error_code ec;
    port_.cancel(ec);
    port_.close(ec);
  }
  static constexpr int BUFFER_SIZE = 4096;
  char read_buffer_[AsyncSerial::BUFFER_SIZE];
  std::function<void(const char *, size_t)> callback_;
  asio::io_context &io_;
  asio::serial_port port_;
  std::thread t_;
};

#endif // ASIO_SERIAL_HPP_
