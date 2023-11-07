#include <unistd.h>

#include <chrono>
#include <iostream>
#include <memory>

#include <grpcpp/grpcpp.h>

#include "proto/demo.grpc.pb.h"

class DemoClient {
 public:
  explicit DemoClient(const std::shared_ptr<grpc::Channel>& channel)
      : m_service(demo::HelloService::NewStub(channel)) {}

  int say_hello(const std::string& s) {
    demo::Request request;
    demo::Reply reply;
    grpc::ClientContext context;
    grpc::ClientContext context2;
    auto deadline =
        std::chrono::system_clock::now() + std::chrono::milliseconds(100);
    context.set_deadline(deadline);
    context2.set_deadline(deadline);
    std::cout << "hello" << std::endl;
    grpc::Status status = m_service->SayHello(&context, request, &reply);
    std::cout << "hello reply:" << status.error_code() << std::endl;
    status = m_service->SayHello(&context2, request, &reply);
    std::cout << "hello reply:" << status.error_code() << std::endl;

    if (status.ok()) {
      return 1;
    } else {
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      return 0;
    }
  }

 private:
  std::unique_ptr<demo::HelloService::Stub> m_service;
};

int main(int argc, char** argv) {
  DemoClient client(grpc::CreateChannel("127.0.0.1:9090",
                                        grpc::InsecureChannelCredentials()));
  client.say_hello("world");
  sleep(1);
  return 0;
}
