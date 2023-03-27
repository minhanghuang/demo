#include <iostream>
#include <nlohmann/json.hpp>
#include <typhoon/typhoon.h>

class MyApi1 : public typhoon::RequestHandler {
public:
  void Get(typhoon::Application *app, typhoon::Connection *conn) override {
    std::cout << "simple get" << std::endl;
    Response(app, conn, "simple http get");
  }

  void Post(typhoon::Application *app, typhoon::Connection *conn) override {
    std::cout << "simple post" << std::endl;
    auto data = GetRequestData(conn);
    std::cout << "data: " << data << std::endl;
    Response(app, conn, "simple http post");
  }
};

int main() {
  std::cout << "Hello, Typhoon!" << std::endl;
  typhoon::Options options;
  options.port = 9900;
  std::cout << "typhoon simple http: " << options.port << std::endl;
  typhoon::Server server(options);
  auto api = std::make_shared<MyApi1>();
  server.AddHandle("/api/simple/", api);
  server.Spin();
  return 0;
}
