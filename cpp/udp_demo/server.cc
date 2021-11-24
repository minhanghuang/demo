/*
* Copyright (C) Trunk Technology, Inc. - All Rights Reserved
*
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
*
* Written by Huang Minhang <huangminhang@trunk.tech>, 2021/11/22 21:55
*/
#include <iostream>
#include <boost/asio.hpp>


#define maxlength 1024

using boost::asio::ip::udp;

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
    Header header;
    Data   data;
};

int main(int argc , char ** argv) {
    std::cout << "Hello, UDP Server!" << std::endl;
    Frame frame{};
    frame.header.id = 100;
    frame.header.version = "1.2.3";
    frame.header.stamp = 1.3;
    frame.header.user = 200;
    frame.data.value = 123;
    frame.data.lis[0] = 1.1;
    frame.data.lis[1] = 1.2;
    char* p = (char*)&frame;

    boost::asio::io_context io_context;
    udp::socket sock(io_context, udp::endpoint(udp::v4(), 8787));
    unsigned char data[maxlength];
    udp::endpoint sender_endpoint;
    while (true) {
        size_t length = sock.receive_from(boost::asio::buffer(data, maxlength), sender_endpoint);
        sock.send_to(boost::asio::buffer(p, sizeof(frame)), sender_endpoint);
    }
    return 0;
}

