/*
* Copyright (C) Trunk Technology, Inc. - All Rights Reserved
*
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
*
* Written by Huang Minhang <huangminhang@trunk.tech>, 2021/11/22 21:55
*/
#include <iostream>
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
    Header header;
    Data   data;
};

int main(int argc , char ** argv) {
    std::cout << "Hello, UDP Server!" << std::endl;
    asio::io_context io_context;

    udp::socket sock(io_context, udp::endpoint(udp::v4(), 9005));

    while (true) {
        unsigned char recv_buf[maxlength];
        udp::endpoint sender_endpoint;
        while (true) {
            size_t length = sock.receive_from(asio::buffer(recv_buf, maxlength), sender_endpoint);
            auto* pp= (Frame *)recv_buf;
            std::cout << "length:" << length <<std::endl;
            std::cout << "id:" << pp->header.id <<std::endl;
//            std::cout << "version:" << pp->header.version <<std::endl;
            std::cout << "stamp:" << pp->header.stamp <<std::endl;
            std::cout << "user:" << (int)pp->header.user <<std::endl;
            std::cout << "value:" << (int)pp->data.value <<std::endl;
            std::cout << "lis0:" << pp->data.lis[0] <<std::endl;
            std::cout << "lis1:" << pp->data.lis[1] <<std::endl;
            std::cout << "---" <<std::endl;
        }
    }

    return 0;
}

