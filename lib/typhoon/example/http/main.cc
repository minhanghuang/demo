#include <iostream>
#include <nlohmann/json.hpp>

#include "typhoon.h"

using namespace trunk::typhoon;

class OkView : public web::RequestHandler {
 public:
  bool handleGet(CivetServer *server, web::Connection *conn) override {
    nlohmann::json json_data;
    json_data["msg"] = "ok";
    Response(conn, json_data, 200);
    return true;
  }

  bool handlePost(CivetServer *server, web::Connection *conn) override {
    nlohmann::json response;
    response["msg"] = "post";
    auto req_info = RequestInfo(conn);

    std::cout << "RequestData:" << RequestData(conn) << std::endl;
    std::cout << "RequestParam:" << RequestParam(conn,"p") << std::endl;
    std::cout << "request_uri:" << req_info->request_uri << std::endl;
    std::cout << "content_length:" <<  req_info->content_length << std::endl;
    Response(conn, response, 200);
    return true;
  }
};

int main() {
  std::cout << "Hello, Typhoon web!" << std::endl;
  OkView view;
  server::Application app;
  app.port = "9999";
  server::HTTPServer server(app);
  server.AddHandler("/ok", view);
  server.Start();
  return 0;
}
