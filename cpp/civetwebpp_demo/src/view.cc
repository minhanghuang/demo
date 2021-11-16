/*
* Copyright (C) Trunk Technology, Inc. - All Rights Reserved
*
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
*
* Written by Huang Minhang <huangminhang@trunk.tech>, 2021/11/15 16:13
*/
#include "view.h"

SimpleWebsocket::SimpleWebsocket(std::string name) : WebSocketBase(std::move(name)) {}

bool OkView::handleGet(CivetServer *server, struct mg_connection *conn)  {
    nlohmann::json json_data;
    json_data["msg"] = "ok";
    std::string s = json_data.dump(0);

    char* c = const_cast<char*>(s.c_str());
    mg_send_http_ok(conn, "application/json; charset=utf-8", s.size());
    mg_write(conn, c, s.size());
    return true;
}

bool OkView::handlePost(CivetServer *server, struct mg_connection *conn) {
    return true;
}

bool OkView::handlePut(CivetServer *server, struct mg_connection *conn) {
    return true;
}
