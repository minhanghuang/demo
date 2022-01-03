#include <iostream>
#include <nlohmann/json.hpp>
#include <utility>

#include "typhoon.h"

using namespace trunk::typhoon;

class OkWebsocker : public websocket::WebSocketHandler {
 public:
  explicit OkWebsocker(std::string name)
      : WebSocketHandler(std::move(name)) {}
};

int main() {
  std::cout << "Hello, Typhoon websocker!" << std::endl;
  OkWebsocker view("simple");
  server::Application app;
  server::HTTPServer server(app);
  server.AddWebSocketHandler("/ws", view);
  server.Start();
  return 0;
}
