/*
* Copyright (C) Trunk Technology, Inc. - All Rights Reserved
*
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
*
* Written by Huang Minhang <huangminhang@trunk.tech>, 2021/11/9 11:24
*/
#include <iostream>
#include <zmq.h>
#include <unistd.h>


int main() {
    std::cout << "Hello, Simple Client!" << std::endl;
    void *context = zmq_init(1);

    //  连接至服务端的套接字
    printf ("正在连接至hello world服务端...\n");
    void* socket = zmq_socket(context, ZMQ_REQ);
    zmq_connect(socket, "tcp://127.0.0.1:5555");

    for (int i = 0; i < 5; i++) {
        zmq_msg_t request;
        zmq_msg_init_size(&request, 5);
        memcpy(zmq_msg_data(&request), "Hello", 5);
        zmq_send(socket, &request, zmq_msg_size(&request), ZMQ_DONTWAIT); // 非阻塞
        printf("--------sent data: %s %ld \n", (char*)zmq_msg_data(&request), zmq_msg_size(&request));
        zmq_msg_close(&request);
        sleep(1);
        zmq_msg_t reply;
        zmq_msg_init(&reply);
        zmq_recv(socket, &reply,zmq_msg_size(&reply), 0); // 非阻塞
        zmq_msg_close(&reply);
    }

    zmq_close(socket);
    zmq_term(context);
}