/*
* Copyright (C) Trunk Technology, Inc. - All Rights Reserved
*
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
*
* Written by Huang Minhang <huangminhang@trunk.tech>, 2021/11/22 21:55
*/
#include <iostream>
#include <vector>
#include <unistd.h>
#include <asio.hpp>


#define maxlength 1024

using asio::ip::udp;

struct Header {
    int id;
    std::string version;
    float stamp;
    uint8_t user;
    int na;
};

struct Data {
    int value;
    float lis[19];
};

struct Frame {
//    Header header;
//    Data   data;
    int q;
};


int main() {
    std::cout << "Hello, UDP Client!" << std::endl;

    Frame frame{};
//    frame.header.id = 100;
//    frame.header.version = "1.2.3";
//    frame.header.stamp = 1.3;
//    frame.header.user = 200;
//    frame.header.na = 0;
//    frame.data.value = 123;
//    frame.data.lis[0] = 1.1;
//    frame.data.lis[1] = 1.2;
    char* p = (char*)&frame;

    asio::io_context io_context;
    udp::endpoint sender_endpoint(asio::ip::address::from_string("192.168.0.192"), 9005);
    udp::socket socket(io_context);
    socket.open(udp::v4());

    while (true) {
        socket.send_to(asio::buffer(p, sizeof(frame)), sender_endpoint);
        std::cout << "send: " << frame.q++ << std::endl;
        sleep(1);
    }

    return 0;
}
