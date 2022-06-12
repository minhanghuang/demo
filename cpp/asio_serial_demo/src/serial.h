#ifndef ASIO_SERIAL_H_
#define ASIO_SERIAL_H_
#include <string>
#include <iostream>

#include <boost/bind.hpp>
#include <boost/noncopyable.hpp>

#include "asio.hpp"
#include "asio/io_context.hpp"

class AsyncSerial : private boost::noncopyable {
 public:
  AsyncSerial(asio::io_context& io_context, const std::string& devname,
              unsigned int baud_rate);
  ~AsyncSerial();
  void SetCallback(const std::function<void(const char*, size_t)>& callback);
  void ClearCallback();
  void ReadEnd(const asio::error_code& error, size_t bytes_transferred);
  void Close();
  void Start();

 private:
  void DoRead();
  void DoClose();
  static const int ReadBufferSize = 4096;
  char read_buffer_[AsyncSerial::ReadBufferSize];
  asio::io_context& io_;
  asio::serial_port port_;
  std::function<void(const char*, size_t)> callback_;
  std::thread t_;
};

#endif  // ASIO_SERIAL_H_