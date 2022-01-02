#include <iostream>
#include <nlohmann/json.hpp>
#include "typhoon.h"

using namespace trunk::typhoon;

class OkView : public web::RequestHandler {
 public:
  bool handleGet(CivetServer *server, struct mg_connection *conn) override {
    nlohmann::json json_data;
    json_data["msg"] = "ok";
    this->Response(conn,json_data,200);
    return true;
  }

};

int main() {
  std::cout << "Hello, Typhoon web!" << std::endl;
  OkView view;
  server::Application app;
  server::HTTPServer server(app);
  server.AddHandler("/ok",view);
  server.Start();
  return 0;
}
