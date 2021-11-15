/*
* Copyright (C) Trunk Technology, Inc. - All Rights Reserved
*
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
*
* Written by Huang Minhang <huangminhang@trunk.tech>, 2021/11/15 16:20
*/
#include "server.h"

HttpServer::~HttpServer() {
    m_server->close();
}
HttpServer::HttpServer(int port) : m_port(port) {
    std::cout << "port:" << m_port << std::endl;
    mg_init_library(0);
    m_options = {
        "document_root",".",
        "listening_ports", std::to_string(m_port)
    };
    m_server = std::make_shared<CivetServer>(m_options);
    m_websocket = std::make_shared<SimpleWebsocket>("simple");
}
void HttpServer::init() {
    m_server->addHandler("/api/ok/", m_ok_view);
    m_server->addWebSocketHandler("/ws", *m_websocket);
}

void HttpServer::run() {
    while (true) {
        sleep(1);
    }
    mg_exit_library();
}
