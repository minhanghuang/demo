/*
* Copyright (C) Trunk Technology, Inc. - All Rights Reserved
*
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
*
* Written by Huang Minhang <huangminhang@trunk.tech>, 2021/11/11 17:14
*/
#include "../proto/demo.grpc.pb.h"
#include <grpcpp/grpcpp.h>
#include <iostream>
#include <unistd.h>
#include <memory>

class DemoClient {
public:
    explicit DemoClient(const std::shared_ptr<grpc::Channel> &channel)
        : m_service(demo::HelloService::NewStub(channel)) {}

    int say_hello(const std::string& s) {

        demo::Request request;
        demo::Reply reply;
        grpc::ClientContext context;

        grpc::Status status = m_service->SayHello(&context, request, &reply);

        if (status.ok()) {
            return 1;
        } else {
            std::cout << status.error_code() << ": " << status.error_message() << std::endl;
            return 0;
        }
    }

private:
    std::unique_ptr<demo::HelloService::Stub> m_service;
};

int main(int argc, char **argv) {

    DemoClient client(grpc::CreateChannel("127.0.0.1:9090", grpc::InsecureChannelCredentials()));
    client.say_hello("world");
    sleep(1);
    return 0;
}
