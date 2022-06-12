#ifndef ASIO_SERIAL_MODULE_HPP_
#define ASIO_SERIAL_MODULE_HPP_

#include <cstdint>
#include <string>

struct  DataFrame {
  int64_t time_stamp;
  std::string frame_id;  
  std::string sensor_type;         
};

#endif // ASIO_SERIAL_MODULE_HPP_
