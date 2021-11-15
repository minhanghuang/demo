/*
* Copyright (C) Trunk Technology, Inc. - All Rights Reserved
*
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
*
* Written by Huang Minhang <huangminhang@trunk.tech>, 2021/11/15 16:20
*/
#ifndef CIVETWEBPP_DEMO_SERVER_H
#define CIVETWEBPP_DEMO_SERVER_H
#include <iostream>
#include <memory>
#include "base.h"
#include "view.h"

class HttpServer {
public:
    ~HttpServer();
    explicit HttpServer(int port);
    void init();
    void run();
private:
    const int m_port;
    std::vector<std::string> m_options;
    std::shared_ptr<CivetServer> m_server;
    std::shared_ptr<SimpleWebsocket> m_websocket;
    OkView m_ok_view;
};

#endif//CIVETWEBPP_DEMO_SERVER_H
