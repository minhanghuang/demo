/*
 * Copyright (C) Trunk Technology, Inc. - All Rights Reserved
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 *
 * Written by Minhang Huang <huangminhang@trunk.tech>, 2022/1/1 22:51
 */
#include "httpserver.h"

#include <utility>

namespace trunk {
namespace typhoon {
namespace server {

HTTPServer::~HTTPServer() {
  mg_exit_library();
}
HTTPServer::HTTPServer(Application app) : app_(std::move(app)) {
  mg_init_library(0);
  std::vector<std::string> options = {
      "document_root",app_.document_root,
      "listening_ports", app_.port,
      "access_control_allow_headers",app_.access_allow_headers,
      "access_control_allow_methods",app_.access_allow_methods,
      "access_control_allow_origin",app_.access_allow_origin,
  };
  server_ = std::make_shared<CivetServer>(options);
}

void HTTPServer::AddHandler(const std::string& uri, CivetHandler* handler) {
  server_->addHandler(uri,handler);
}

void HTTPServer::AddHandler(const std::string& uri, CivetHandler& handler) {
  this->AddHandler(uri, &handler);
}

void HTTPServer::AddWebSocketHandler(const std::string& uri,
                                     CivetWebSocketHandler* handler) {
  server_->addWebSocketHandler(uri,handler);
}

void HTTPServer::AddWebSocketHandler(const std::string& uri,
                                     CivetWebSocketHandler& handler) {
  this->AddWebSocketHandler(uri, &handler);
}

void HTTPServer::Start() {
  while (true) {

  }
}

void HTTPServer::Stop() {

}


} // namespace trunk
} // namespace typhoon
} // namespace server

