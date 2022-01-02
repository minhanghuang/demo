/*
 * Copyright (C) Trunk Technology, Inc. - All Rights Reserved
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 *
 * Written by Minhang Huang <huangminhang@trunk.tech>, 2022/1/1 22:51
 */
#ifndef TYPHOON_HTTPSERVER_H_
#define TYPHOON_HTTPSERVER_H_
#include <memory>
#include <vector>
#include "CivetServer.h"


namespace trunk {
namespace typhoon {
namespace server {

struct Application {
  std::string port = "8080";
  std::string document_root = "."; // file server
  std::string access_allow_headers = "*";
  std::string access_allow_methods = "*";
  std::string access_allow_origin = "*";
};

class HTTPServer {
 public:
  ~HTTPServer();
  explicit HTTPServer(Application app);
  void AddHandler(const std::string& uri, CivetHandler* handler);
  void AddHandler(const std::string& uri, CivetHandler& handler);
  void AddWebSocketHandler(const std::string &uri,
                           CivetWebSocketHandler *handler);
  void AddWebSocketHandler(const std::string &uri,
                           CivetWebSocketHandler &handler);
  void Start();
  void Stop();

 private:
  Application app_;
  std::shared_ptr<CivetServer> server_;

};

} // namespace trunk
} // namespace typhoon
} // namespace server

#endif  // TYPHOON_HTTPSERVER_H_
