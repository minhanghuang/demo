/*
* Copyright (C) Trunk Technology, Inc. - All Rights Reserved
*
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
*
* Written by Huang Minhang <huangminhang@trunk.tech>, 2021/11/6 17:39
*/
#include <iostream>
#include <zmq.h>
#include <unistd.h>


int main() {
    std::cout << "Hello, Simple Server!" << std::endl;
    void *context = zmq_init(3);
    void *responder = zmq_socket(context, ZMQ_REP);
    zmq_bind(responder, "tcp://127.0.0.1:5555");
    std::cout << "start" << std::endl;
    int ret;
    while (true) {
        //  等待客户端请求
        zmq_msg_t request;
        zmq_msg_init(&request);
        ret = zmq_recv(responder, &request,zmq_msg_size(&request), 0);
        if (ret != -1) {
            std::cout << "收到:" << ret <<std::endl;
            printf("--------sent data: %s %ld \n", (char*)zmq_msg_data(&request), zmq_msg_size(&request));
        }
        zmq_msg_close(&request);
        //  返回应答
        zmq_msg_t reply;
        zmq_msg_init_size (&reply, 5);
        memcpy(zmq_msg_data (&reply), "World", 5);
        zmq_send(responder, &reply, zmq_msg_size(&reply),ZMQ_DONTWAIT);
        zmq_msg_close(&reply);
    }

    //  程序不会运行到这里，以下只是演示我们应该如何结束
    zmq_close (responder);
    zmq_term (context);
    return 0;
}

