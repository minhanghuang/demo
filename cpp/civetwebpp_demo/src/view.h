/*
* Copyright (C) Trunk Technology, Inc. - All Rights Reserved
*
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
*
* Written by Huang Minhang <huangminhang@trunk.tech>, 2021/11/15 16:13
*/
#ifndef CIVETWEBPP_DEMO_VIEW_H
#define CIVETWEBPP_DEMO_VIEW_H
#include "base.h"
#include <utility>

class OkView : public trunk::infra::http::HttpBase {
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
    bool handlePost(CivetServer *server, struct mg_connection *conn) override {
        return true;
    }
    bool handlePut(CivetServer *server, struct mg_connection *conn) override {
        return true;
    }
};

class SimpleWebsocket : public trunk::infra::http::WebSocketBase {
public:
    explicit SimpleWebsocket(std::string name);
};

#endif//CIVETWEBPP_DEMO_VIEW_H
