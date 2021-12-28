/*
 * Copyright (C) Trunk Technology, Inc. - All Rights Reserved
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 *
 * Written by Minhang Huang <huangminhang@trunk.tech>, 2021/12/27 17:41
 */
//#include <boost/asio.hpp>
#include <iostream>
#include <unistd.h>
#include <asio.hpp>

int main() {
  namespace ip = asio::ip;
  asio::io_context io_context;

  ip::udp::endpoint broadcast_endpoint(ip::address_v4::broadcast(), 8888);

  ip::udp::socket socket(io_context, ip::udp::endpoint(ip::udp::v4(), 0));
  socket.set_option(asio::socket_base::broadcast(true));

  int i = 1;
  while (true) {
    std::string buf = "ssss" + std::to_string(i);
    socket.send_to(asio::buffer(buf, sizeof(buf) + 1),broadcast_endpoint);
    sleep(1);
    std::cout << "----" << std::endl;
    i++;
  }
}