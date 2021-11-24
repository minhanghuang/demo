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
#include <boost/asio.hpp>
#include <boost/array.hpp>


#define maxlength 1024

using boost::asio::ip::udp;
using namespace boost::asio;

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


int main() {
    std::cout << "Hello, UDP Client!" << std::endl;
    try {

        boost::asio::io_context io_context;

        // 服务器IP
        udp::endpoint receiver_endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 8787);

        // 打开socket
        udp::socket socket(io_context);
        socket.open(udp::v4());

        // 同步发送数据
        boost::array<char, 1> send_buf  = {{ 1 }};
        socket.send_to(boost::asio::buffer(send_buf), receiver_endpoint);

        // 同步接收数据
        char recv_buf[maxlength];
        udp::endpoint sender_endpoint;
        size_t len = socket.receive_from(boost::asio::buffer(recv_buf,maxlength), sender_endpoint);
        auto* pp= (Frame *)recv_buf;
        std::cout << "id:" << pp->header.id <<std::endl;
        std::cout << "version:" << pp->header.version <<std::endl;
        std::cout << "stamp:" << pp->header.stamp <<std::endl;
        std::cout << "user:" << (int)pp->header.user <<std::endl;
        std::cout << "value:" << (int)pp->data.value <<std::endl;
        std::cout << "lis0:" << pp->data.lis[0] <<std::endl;
        std::cout << "lis1:" << pp->data.lis[1] <<std::endl;
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }


    return 0;
}
