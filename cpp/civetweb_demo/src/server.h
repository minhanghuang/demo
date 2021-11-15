/*
* Copyright (C) Trunk Technology, Inc. - All Rights Reserved
*
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
*
* Written by Huang Minhang <huangminhang@trunk.tech>, 2021/11/14 21:07
*/
#ifndef CIVETWEB_DEMO_SERVER_H
#define CIVETWEB_DEMO_SERVER_H

#include <memory>
#include <unistd.h>
#include <nlohmann/json.hpp>
#include "CivetServer.h"


class OkView : public CivetHandler{
public:
    bool handleGet(CivetServer *server, struct mg_connection *conn) override {
        nlohmann::json json_data;
        json_data["msg"] = "ok";
        std::string s = json_data.dump(0);

        char* c = const_cast<char*>(s.c_str());
        mg_send_http_ok(conn, "application/json; charset=utf-8", s.size());
        mg_write(conn, c, s.size());
        return true;
    }
    bool handlePost(CivetServer *server, struct mg_connection *conn) {
        return true;
    }
    bool handlePut(CivetServer *server, struct mg_connection *conn) {
        return true;
    }
};

class HttpServer {
public:
    HttpServer() {
    }
    ~HttpServer() {
    }

    void run() {
        mg_init_library(0);
        std::vector<std::string> options = {
            "document_root",".",
            "listening_ports","10022"
        };
        CivetServer m_server(options);
        OkView ok_view;
        m_server.addHandler("/api/ok/", ok_view);
        while (true) {
            sleep(1);
        }
        mg_exit_library();
    }

private:
//    std::unique_ptr<CivetServer> m_server;
};

#endif//CIVETWEB_DEMO_SERVER_H
