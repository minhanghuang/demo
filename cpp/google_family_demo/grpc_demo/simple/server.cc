#include <unistd.h>

#include <iostream>

#include <grpcpp/grpcpp.h>

#include "proto/demo.grpc.pb.h"

class HelloServiceImpl : public demo::HelloService::Service {
 public:
  grpc::Status SayHello(::grpc::ServerContext* context,
                        const ::demo::Request* request,
                        ::demo::Reply* response) override {
    std::cout << "say_hello" << std::endl;
    sleep(1);
    return grpc::Status::OK;
  }
};

int main() {
  std::cout << "Hello, Simple Server!" << std::endl;
  std::string address("0.0.0.0:9090");
  HelloServiceImpl service;
  grpc::ServerBuilder builder;
  builder.AddListeningPort(address, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);
  std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
  server->Wait();
  return 0;
}
